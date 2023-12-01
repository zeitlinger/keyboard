enum class ComboType(val template: String) {
    Combo("COMB(%s, %s, %s)"), Substitution("SUBS(%s, %s, %s)")
}

data class Combo(val type: ComboType, val name: String, val result: String, val triggers: List<Key>, val timeout: Int?)

data class HomeRowCombo(val targetLayer: String, val key: Key)

const val comboTrigger = "\uD83D\uDC8E" // 💎

fun getSubstitutionCombo(key: String): String? =
    if (key.startsWith("\"") && key.endsWith("\"")) key else null

fun generateAllCombos(layers: List<Layer>, features: Set<Feature>, homeRowCombo: HomeRowCombo?): List<Combo> {
    val baseLayer = layers[0]

    val homeRowCombos = homeRowCombo?.let { hr ->
        val homeRowLayer =
            layers.find { it.name == hr.targetLayer } ?: throw IllegalStateException("unknown layer ${hr.targetLayer}")

        hands.filter { !it.isThumb && !it.isFull }.flatMap { hand ->
            generateModCombos(
                listOf(hr.key),
                getLayerPart(baseLayer.baseRows, hand),
                homeRowLayer,
                hand,
                homeRowTriggers
            )
        }
    } ?: emptyList()

    return homeRowCombos + layers.flatMap { layer ->
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
    extraKeys: List<Key>
): List<Combo> = hands.flatMap { hand ->
    val modCombos =
        if (features.contains(Feature.ModCombo) && layer.number == 0 && !hand.isThumb && extraKeys.isEmpty()) {
            generateModCombos(listOf(), getLayerPart(layer.baseRows, hand), layer, hand, modTriggers)
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
    layerBase: List<Key>,
    layer: Layer,
    hand: Hand,
    extraKeys: List<Key>
): List<Combo> {
    val definition = getLayerPart(def, hand)
    val comboIndexes = definition.mapIndexedNotNull { index, s -> if (s.key == comboTrigger) index else null }

    return definition.flatMapIndexed { comboIndex, k ->
        val key = k.key
        if (!(k.isBlocked() || key == comboTrigger || key == "KC_TRNS")) {
            val keys = layerBase
                .filterIndexed { index, _ -> index == comboIndex || index in comboIndexes } + extraKeys

            val substitutionCombo = getSubstitutionCombo(key)
            val type = if (substitutionCombo != null) ComboType.Substitution else ComboType.Combo
            val name = comboName(layer.name, key)
            val content = substitutionCombo ?: key
            listOf(Combo(type, name, content, keys, k.comboTimeout))
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


private fun getLayerPart(layerBase: Rows, hand: Hand): List<Key> =
    layerBase.map { it.drop(hand.skip).take(hand.comboColumns) }.flatten()
