enum class ComboType(val template: String) {
    Combo("COMB(%s, %s, %s)"), Substitution("SUBS(%s, %s, %s)")
}

enum class ComboSource {
    Base, Layer, Shifted, Direct, DirectShifted
}

data class Combo(
    val type: ComboType,
    var name: String,
    val result: QmkKey,
    val triggers: List<Key>,
    val timeout: Int?,
) {
    companion object {
        fun of(
            type: ComboType,
            source: ComboSource,
            name: String,
            result: QmkKey,
            triggers: List<Key>,
            timeout: Int? = 0
        ): List<Combo> {
            if (name.contains("DEAD")) {
                return emptyList()
            }
            if (triggers.any { it.keyWithModifier.isNo }) {
                throw IllegalStateException(
                    "no KC_NO allowed in $source combo triggers:\n$name\n${
                        triggers.joinToString(
                            "\n"
                        )
                    }"
                )
            }
            return listOf(Combo(type, name, result, triggers.sortedBy { it.keyWithModifier.key }, timeout))
        }
    }
}

const val comboTrigger = "\uD83D\uDC8E" // 💎

val goodComboLayers: Map<String, (Int) -> Boolean> = mapOf(
    "Nav" to { true },
    "FnSym" to { true },
//    "Left" to { it < 4 },
//    "Right" to { it >= 4 },
)

fun generateAllCombos(layers: List<Layer>, translator: QmkTranslator): List<Combo> {
    val lists = layers.map { layer ->
        layerCombos(translator, layer, layer.combos, layer.rows, layers)
    }
    val goodTriggers: Set<Set<KeyPosition>> = combo2Positions(lists[0])
    val goodValues = combo2Values(lists[0])

    for (layer in layers.zip(lists).subList(1, lists.size)) {
        val layerName = layer.first.name

        val pred = goodComboLayers[layerName]
        if (pred == null) {
            continue
        }

        val positions = combo2Positions(layer.second)
        val missing = (goodTriggers - positions).filter { pred(it.iterator().next().column) }

        if (missing.isNotEmpty()) {
            val text = missing.joinToString("\n") {
                val indexOf = goodTriggers.indexOf(it)
                goodValues[indexOf]
            }
            println("missing combos in layer $layerName:\n$text")
        }
    }

    return lists.flatten().also { checkForDuplicateCombos(it) }
}

private fun combo2Positions(combos: List<Combo>): Set<Set<KeyPosition>> = combos
    .filter { it.triggers.size == 2 }
    .map { combo ->
        combo.triggers
            .map { it.pos.copy(layerName = "Base") }
            .toSet()
    }.toSet()

private fun combo2Values(combos: List<Combo>): List<String> = combos
    .filter { it.triggers.size == 2 && !it.name.startsWith("S_") }
    .map { combo ->
        combo.result.key
    }

private fun checkForDuplicateCombos(combos: List<Combo>) {
    combos.groupBy { it.triggers.map { it.key.key } }
        .filter { it.value.size > 1 }
        .forEach { (triggers, combos) ->
            throw IllegalStateException(
                "duplicate triggers\n${triggers.joinToString("\n")}\nin\n${
                    combos.joinToString(
                        ", "
                    ) { it.name }
                }"
            )
        }

    combos.groupBy { it.name }
        .filter { it.value.size > 1 }
        .forEach { (_, combos) ->
            combos.mapIndexed { index, combo -> "${combo.name}_$index".also { combo.name = it } }
        }
}

private fun layerCombos(
    translator: QmkTranslator,
    layer: Layer,
    activationParts: List<Rows>,
    layerBase: Rows,
    layers: List<Layer>,
): List<Combo> {
    val options = translator.options
    val custom = hands.flatMap { hand ->
        activationParts
            .filter { hand.applies(it, options) }
            .flatMap { def ->
                customLayerCombos(
                    def,
                    getLayerPart(layerBase, hand, options),
                    layer,
                    hand,
                    translator,
                    layers
                )
            }
    }.distinct()

    val directLeft = if (LayerFlag.DirectComboLeft in layer.option.flags) {
        directCombos(layer, layers, layerBase, translator) {
            it.pos.column < options.nonThumbColumns / 2
        }
    } else emptyList()
    val directRight = if (LayerFlag.DirectComboRight in layer.option.flags) {
        directCombos(layer, layers, layerBase, translator) {
            it.pos.column >= options.nonThumbColumns / 2
        }
    } else emptyList()

    return custom + directLeft + directRight
}

private fun directCombos(
    layer: Layer,
    layers: List<Layer>,
    layerBase: Rows,
    translator: QmkTranslator,
    filter: (Key) -> Boolean,
): List<Combo> {
    val layerTriggers = firstNonToggleActivation(
        layer,
        layers,
    )

    val base = layers.first { LayerFlag.Alternate !in it.option.flags }
    return layerBase.flatten()
        // only if the layer can be reached directly from the base layer
        .filter { it.isReal() && it.key !in translator.noHoldKeys && filter(it) }
        .flatMap { key ->
            val triggers = (listOf(key.pos) + layerTriggers).map { base.get(it) }
//            if (LayerActivation.entries.any { it.method != null && triggers[0].key.key.startsWith(it.method) }) {
//                emptyList()
//            } else {
            keyCombos(key, ComboSource.Direct, triggers, translator, layer, layers)
//            }
        }
}

private fun firstNonToggleActivation(layer: Layer, layers: List<Layer>): List<KeyPosition> =
    layer.option.reachable.entries.firstOrNull { !it.value.isToggle() }
        ?.let { entry ->
            val keyPosition = entry.key
            val layerName = keyPosition.layerName
            if (layerName == baseLayerName) {
                listOf(keyPosition)
            } else {
                listOf(keyPosition) + firstNonToggleActivation(
                    layers.single { it.name == layerName },
                    layers,
                )
            }
        }
        ?: emptyList()

private fun customLayerCombos(
    def: Rows,
    layerBase: List<Key>,
    layer: Layer,
    hand: Hand,
    translator: QmkTranslator,
    layers: List<Layer>,
): List<Combo> {
    val definition = getLayerPart(def, hand, translator.options)
    val comboIndexes = definition.mapIndexedNotNull { index, s -> if (s.key.key == comboTrigger) index else null }

    return definition.flatMapIndexed { comboIndex, key ->
        if (key.isReal()) {
            val keys = layerBase
                .filterIndexed { index, _ -> index == comboIndex || index in comboIndexes }

            val source = if (layer.name == baseLayerName) ComboSource.Base else ComboSource.Layer
            keyCombos(key, source, keys, translator, layer, layers)
        } else emptyList()
    }.filter { it.triggers.size > 1 }
}

private fun keyCombos(
    key: Key,
    source: ComboSource,
    triggers: List<Key>,
    translator: QmkTranslator,
    layer: Layer,
    layers: List<Layer>,
): List<Combo> {
    val qmkKey = translator.originalKeys[key.pos] ?: key.key
    val type = if (qmkKey.substitution != null) ComboType.Substitution else ComboType.Combo
    val name = comboName(layer.name, qmkKey.key)
    return combos(type, source, name, qmkKey, triggers, key.comboTimeout, translator, layers, layer)
}

private fun combos(
    type: ComboType,
    source: ComboSource,
    name: String,
    content: QmkKey,
    triggers: List<Key>,
    timeout: Int?,
    translator: QmkTranslator,
    layers: List<Layer>,
    layer: Layer,
): List<Combo> {
    val keyTimeout =
        timeout ?: layer.option.comboTimeout ?: throw IllegalStateException("no timeout for layer ${layer.name}")
    val combo = Combo.of(
        type,
        source,
        name,
        content,
        triggers,
        keyTimeout
    )

    val shiftLayer = layers.singleOrNull { l ->
        LayerFlag.Shifted in l.option.flags &&
                fallbackLayer(triggers[0].pos, l.option) == layer.name
    }

    return when {
        shiftLayer != null && isLetter(content) -> {
            val shiftLayerTimeout =
                shiftLayer.option.comboTimeout ?: throw IllegalStateException("no timeout for layer ${shiftLayer.name}")
            val shifted = combos(
                type,
                ComboSource.Shifted,
                "S_$name",
                shifted(content),
                triggers.map { t ->
                    val position = t.pos.layerRelative()
                    shiftLayer.rows.flatten().first { it.pos.layerRelative() == position }
                },
                shiftLayerTimeout,
                translator,
                emptyList(), // prevent recursion
                layer
            )
            val directShifted = combos(
                type,
                ComboSource.DirectShifted,
                "DS_$name",
                shifted(content),
                triggers + layer.get(shiftLayer.option.reachable.keys.single()),
                shiftLayerTimeout,
                translator,
                emptyList(), // prevent recursion
                layer
            )
            combo + shifted + directShifted
        }

        else -> combo
    }
}

fun shifted(content: QmkKey): QmkKey = addMods(content, Modifier.Shift)

fun isLetter(content: QmkKey) = content.key.startsWith("KC_") && content.key.length == 4 && content.key[3].isLetter()

fun comboName(vararg parts: String): String {
    return "C_${
        parts.toList().joinToString("_") {
            it.uppercase()
                .replace(".", "_")
                .replace(Regex("[()\", ]"), "")
        }
    }"
}


private fun getLayerPart(layerBase: Rows, hand: Hand, options: Options): List<Key> =
    layerBase.map { it.drop(hand.skip(options)).take(hand.comboColumns(options)) }.flatten()
