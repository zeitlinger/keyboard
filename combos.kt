enum class ComboType(val template: String) {
    Combo("COMB(%s, %s, %s)"), Substitution("SUBS(%s, %s, %s)")
}

data class Combo(val type: ComboType, val name: String, val result: String, val triggers: List<String>)

const val comboTrigger = "\uD83D\uDC8E" // 💎

fun getSubstitutionCombo(key: String): String? =
    if (key.startsWith("\"") && key.endsWith("\"")) key else null

fun generateCombos(layers: List<Layer>, features: Set<Feature>): List<Combo> {
    val baseLayer = layers[0]

    return layers.flatMap { layer ->

        val combos = generateCombos(features, layer, layer.combos, layer.baseRows, listOf())
        val baseLayerCombos = layer.comboTrigger?.let { trigger ->
            generateCombos(
                features,
                baseLayer,
                listOf(layer.baseRows) + layer.combos,
                baseLayer.baseRows,
                listOf(trigger)
            )
        } ?: emptyList()
        combos + baseLayerCombos
    }
}

private fun generateCombos(
    features: Set<Feature>,
    layer: Layer,
    activationParts: List<Rows>,
    layerBase: Rows,
    extraKeys: List<String>
): List<Combo> = hands.flatMap { hand ->
    val modCombos =
        if (features.contains(Feature.ModCombo) && layer.number == 0 && !hand.isThumb && extraKeys.isEmpty()) {
            generateModCombos(listOf(), getLayerPart(layer.baseRows, hand), layer, hand)
        } else {
            emptyList()
        }

    val customCombos = activationParts
        .filter { hand.applies(it) }
        .flatMap { def ->
            generateCustomCombos(
                def,
                getLayerPart(layerBase.drop(hand.baseLayerRowSkip), hand),
                layer,
                hand,
                extraKeys,
            )
        }
    customCombos + modCombos
}.distinct()

private fun generateCustomCombos(
    def: Rows,
    layerBase: List<String>,
    layer: Layer,
    hand: Hand,
    extraKeys: List<String>
): List<Combo> {
    val definition = getLayerPart(def, hand)
    val comboIndexes = definition.mapIndexedNotNull { index, s -> if (s == comboTrigger) index else null }

    return definition.flatMapIndexed { comboIndex, key ->
        if (!(key.isBlank() || key.isBlocked() || key == comboTrigger || key == "KC_TRNS")) {
            val keys = layerBase
                .filterIndexed { index, _ -> index == comboIndex || index in comboIndexes } + extraKeys

            val substitutionCombo = getSubstitutionCombo(key)
            val type = if (substitutionCombo != null) ComboType.Substitution else ComboType.Combo
            val name = comboName(layer.name, key)
            val content = substitutionCombo ?: key
            listOf(Combo(type, name, content, keys))
        } else emptyList()
    }.filter { it.triggers.size > 1 }
}

fun comboName(vararg parts: String?): String {
    return "C_${
        parts.filterNotNull().joinToString("_") {
            it.uppercase()
                .replace(".", "_")
                .replace(Regex("[()\"]"), "")
        }
    }"
}


private fun getLayerPart(layerBase: List<List<String>>, hand: Hand) =
    layerBase.map { it.drop(hand.skip).take(hand.comboColumns) }.flatten()
