enum class ComboType(val template: String) {
    Combo("COMB(%s, %s, %s)"), Substitution("SUBS(%s, %s, %s)")
}

data class Combo(
    val type: ComboType,
    var name: String,
    val result: String,
    val triggers: List<Key>,
    val timeout: Int?,
) {
    companion object {
        fun of(type: ComboType, name: String, result: String, triggers: List<Key>, timeout: Int? = 0): Combo {
            if (triggers.any { it.keyWithModifier == "KC_NO" }) {
                throw IllegalStateException("no KC_NO allowed in combo triggers:\n$name\n${triggers.joinToString("\n")}")
            }
            return Combo(type, name, result, triggers.sortedBy { it.keyWithModifier }, timeout)
        }
    }
}

const val comboTrigger = "\uD83D\uDC8E" // 💎

fun getSubstitutionCombo(key: String): String? =
    if (key.startsWith("\"") && key.endsWith("\"")) key else null

fun generateAllCombos(layers: List<Layer>, translator: QmkTranslator): List<Combo> =
    layers.flatMap { layer ->
        generateCombos(translator, layer, layer.combos, layer.rows, layers)
    }.also { checkForDuplicateCombos(it) }

private fun checkForDuplicateCombos(combos: List<Combo>) {
    combos.groupBy { it.triggers }
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

private fun generateCombos(
    translator: QmkTranslator,
    layer: Layer,
    activationParts: List<Rows>,
    layerBase: Rows,
    layers: List<Layer>,
): List<Combo> {
    val options = translator.options
    return hands.flatMap { hand ->
        activationParts
            .filter { hand.applies(it, options) }
            .flatMap { def ->
                generateCustomCombos(
                    def,
                    getLayerPart(layerBase, hand, options),
                    layer,
                    hand,
                    translator,
                    layers
                )
            }
    }.distinct()
}

private fun generateCustomCombos(
    def: Rows,
    layerBase: List<Key>,
    layer: Layer,
    hand: Hand,
    translator: QmkTranslator,
    layers: List<Layer>,
): List<Combo> {
    val definition = getLayerPart(def, hand, translator.options)
    val comboIndexes = definition.mapIndexedNotNull { index, s -> if (s.key == comboTrigger) index else null }

    return definition.flatMapIndexed { comboIndex, k ->
        val key = k.key
        if (!(k.isBlocked() || key == comboTrigger || key == "KC_TRNS" || key == qmkNo)) {
            val keys = layerBase
                .filterIndexed { index, _ -> index == comboIndex || index in comboIndexes }

            val substitutionCombo = getSubstitutionCombo(key)
            val type = if (substitutionCombo != null) ComboType.Substitution else ComboType.Combo
            val name = comboName(layer.name, key)
            val content = substitutionCombo ?: key
            combos(type, name, content, keys, k.comboTimeout, translator, layers, layer)
        } else emptyList()
    }.filter { it.triggers.size > 1 }
}

private fun combos(
    type: ComboType,
    name: String,
    content: String,
    triggers: List<Key>,
    timeout: Int?,
    translator: QmkTranslator,
    layers: List<Layer>,
    layer: Layer,
): List<Combo> {
    val combo = Combo.of(
        type,
        name,
        content,
        triggers,
        timeout
    )
    val shiftLayer = layers.singleOrNull { l ->
        LayerFlag.Shifted in l.option.flags &&
                fallbackLayer(triggers[0].pos, l.option) == layer.name
    }

    return when {
        shiftLayer != null && isLetter(content) -> {
            listOf(combo) + combos(
                type,
                "S$name",
                shifted(content),
                triggers.map { t ->
                    val position = t.pos.layerRelative()
                    shiftLayer.rows.flatten().first { it.pos.layerRelative() == position }
                },
                timeout,
                translator,
                emptyList(), // prevent recursion
                layer
            )
        }

        else -> listOf(combo)
    }
}

fun shifted(content: String) = addMods("S", content)

fun isLetter(content: String) = content.startsWith("KC_") && content.length == 4 && content[3].isLetter()

fun comboName(vararg parts: String?): String {
    return "C_${
        parts.filterNotNull().joinToString("_") {
            it.uppercase()
                .replace(".", "_")
                .replace(Regex("[()\"]"), "")
        }
    }"
}


private fun getLayerPart(layerBase: Rows, hand: Hand, options: Options): List<Key> =
    layerBase.map { it.drop(hand.skip(options)).take(hand.comboColumns(options)) }.flatten()
