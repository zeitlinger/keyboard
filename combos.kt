enum class ComboType(val template: String) {
    Combo("COMB(%s, %s, %s)"), Substitution("SUBS(%s, %s, %s)")
}

data class Combo(val type: ComboType, val name: String, val result: String, val triggers: List<Key>, val timeout: Int?)

data class HomeRowCombo(val targetLayer: String, val key: Key)

const val comboTrigger = "\uD83D\uDC8E" // 💎

fun getSubstitutionCombo(key: String): String? =
        if (key.startsWith("\"") && key.endsWith("\"")) key else null

fun generateAllCombos(layers: List<Layer>, options: Options, homeRowCombo: HomeRowCombo?): List<Combo> =
        homeRowCombos(homeRowCombo, layers, options) + layerCombos(layers, options).also { combos ->
            combos.groupBy { it.triggers }.filter { it.value.size > 1 }.forEach { (triggers, combos) ->
                throw IllegalStateException("duplicate triggers ${triggers.joinToString(", ") { it.key }} in ${combos.joinToString(", ") { it.name }}")
            }
        }

private fun layerCombos(layers: List<Layer>, options: Options) = layers.flatMap { layer ->
    val combos = generateCombos(options, layer, layer.combos, layer.baseRows, listOf())
    val baseLayerCombos = directLayerCombos(layer, options, layers)
    combos + baseLayerCombos
}

private fun directLayerCombos(
        layer: Layer,
        options: Options,
        layers: List<Layer>
): List<Combo> {
    val baseLayerCombos = layer.comboTrigger?.let { trigger ->
        generateCombos(
                options,
                layers[0],
                listOf(layer.baseRows) + layer.combos,
                layers[0].baseRows,
                listOf(trigger)
        )
    } ?: emptyList()
    return baseLayerCombos
}

private fun homeRowCombos(
        homeRowCombo: HomeRowCombo?,
        layers: List<Layer>,
        options: Options
): List<Combo> {
    val homeRowCombos = homeRowCombo?.let { hr ->
        val homeRowLayer =
                layers.find { it.name == hr.targetLayer }
                        ?: throw IllegalStateException("unknown layer ${hr.targetLayer}")

        hands.filter { !it.isThumb && !it.isFull }.flatMap { hand ->
            generateModCombos(
                    homeRowLayer.name,
                    listOf(hr.key),
                    getLayerPart(layers[0].baseRows, hand),
                    homeRowLayer,
                    hand,
                    homeRowThumbTriggers,
                    options.homeRowThumbComboTimeout,
            )
        }
    } ?: emptyList()
    return homeRowCombos
}

private fun generateCombos(
        options: Options,
        layer: Layer,
        activationParts: List<Rows>,
        layerBase: Rows,
        extraKeys: List<Key>
): List<Combo> = hands.flatMap { hand ->
    val modCombos =
            if (options.homeRowComboTimeout != null && layer.number == 0 && !hand.isThumb && !hand.isFull && extraKeys.isEmpty()) {
                generateModCombos(
                        "OSM",
                        listOf(),
                        getLayerPart(layer.baseRows, hand),
                        layer,
                        hand,
                        homeRowTriggers,
                        options.homeRowComboTimeout
                )
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
