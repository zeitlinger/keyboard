enum class ComboType(val template: String) {
    Combo("COMB(%s, %s, %s)"), Substitution("SUBS(%s, %s, %s)")
}

data class Combo(
    val type: ComboType,
    var name: String,
    val result: QmkKey,
    val triggers: List<Key>,
    val timeout: Int?,
) {
    companion object {
        fun of(type: ComboType, name: String, result: QmkKey, triggers: List<Key>, timeout: Int? = 0): Combo {
            if (triggers.any { it.keyWithModifier.isNo }) {
                throw IllegalStateException("no KC_NO allowed in combo triggers:\n$name\n${triggers.joinToString("\n")}")
            }
            return Combo(type, name, result, triggers.sortedBy { it.keyWithModifier.key }, timeout)
        }
    }
}

const val comboTrigger = "\uD83D\uDC8E" // 💎

fun generateAllCombos(layers: List<Layer>, translator: QmkTranslator): List<Combo> =
    layers.flatMap { layer ->
        layerCombos(translator, layer, layer.combos, layer.rows, layers)
    }.also { checkForDuplicateCombos(it) }

private fun checkForDuplicateCombos(combos: List<Combo>) {
    combos.groupBy { it.triggers.map { it.key.key } }
        .filter { it.value.size > 1 }
        .forEach { (triggers, combos) ->
            throw IllegalStateException(
                "duplicate triggers\n${triggers.joinToString("\n")} in\n${
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

    val direct = layer.option.reachable.entries.flatMapIndexed { index, (position, activation) ->
        val base = layers[0]
        layerBase.flatten()
            // only if the layer can be reached directly from the base layer
            .filter { it.isReal() &&
                    it.key !in translator.symbols.noHoldKeys &&
                    position.layerName == baseLayerName &&
                    activation != LayerActivation.Toggle }
            .flatMap { key ->
                val triggers = listOf(key.pos, position).map { base.get(it) }
//                if (LayerActivation.entries.any { it.method != null && triggers[0].key.key.startsWith(it.method) }) {
//                    emptyList()
//                } else {
                    keyCombos(key, triggers, translator, layer, layers, index.toString(), false)
//                }
            }
    }
    return custom + direct
}

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

            keyCombos(key, keys, translator, layer, layers, "", true)
        } else emptyList()
    }.filter { it.triggers.size > 1 }
}

private fun keyCombos(
    key: Key,
    triggers: List<Key>,
    translator: QmkTranslator,
    layer: Layer,
    layers: List<Layer>,
    suffix: String,
    generateDirect: Boolean,
): List<Combo> {
    val qmkKey = key.key
    val type = if (qmkKey.substitutionCombo != null) ComboType.Substitution else ComboType.Combo
    val name = comboName(layer.name, qmkKey.key) + suffix
    return combos(type, name, qmkKey, triggers, key.comboTimeout, translator, layers, layer, generateDirect)
}

private fun combos(
    type: ComboType,
    name: String,
    content: QmkKey,
    triggers: List<Key>,
    timeout: Int?,
    translator: QmkTranslator,
    layers: List<Layer>,
    layer: Layer,
    generateDirect: Boolean,
): List<Combo> {
    val keyTimeout =
        timeout ?: layer.option.comboTimeout ?: throw IllegalStateException("no timeout for layer ${layer.name}")
    val combo = Combo.of(
        type,
        name,
        content,
        triggers,
        keyTimeout
    )

    val direct = if(generateDirect) layer.option.reachable.keys.mapIndexed { index, position ->
        val base = layers[0]
        Combo.of(
            type,
            "D${index}_$name",
            content,
            (triggers.map { it.pos } + position).map { base.get(it) },
            keyTimeout,
        )
    }  else emptyList()

    val combos = listOf(combo) + direct

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
                "S_$name",
                shifted(content),
                triggers.map { t ->
                    val position = t.pos.layerRelative()
                    shiftLayer.rows.flatten().first { it.pos.layerRelative() == position }
                },
                shiftLayerTimeout,
                translator,
                emptyList(), // prevent recursion
                layer,
                false
            )
            val directShifted = combos(
                type,
                "DS_$name",
                shifted(content),
                triggers + layer.get(shiftLayer.option.reachable.keys.single()),
                shiftLayerTimeout,
                translator,
                emptyList(), // prevent recursion
                layer,
                false
            )
            combos + shifted + directShifted
        }

        else -> combos
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
