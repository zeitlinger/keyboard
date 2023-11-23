enum class ComboType(val template: String) {
    Combo("COMB(%s, %s, %s)"), Substitution("SUBS(%s, %s, %s)")
}

data class Combo(val type: ComboType, val name: String, val result: String, val triggers: List<String>)

const val comboTrigger = "\uD83D\uDC8E" // 💎

private val modTriggers: List<ModTrigger> = listOf(
    ModTrigger(emptyList(), emptyList(), "MO(%d)", null),
    ModTrigger(listOf(Modifier.Shift), listOf(1, 2), "LM(%d, MOD_LSFT)", "S"),
    ModTrigger(listOf(Modifier.Ctrl), listOf(2, 4), "LM(%d, MOD_LCTL)", "C"),
    ModTrigger(listOf(Modifier.Alt), listOf(1, 4), "LM(%d, MOD_LALT)", "A"),
    ModTrigger(listOf(Modifier.Shift, Modifier.Ctrl), listOf(1, 2, 3), "LM(%d, MOD_LCTL | MOD_LSFT)", "CS"),
    ModTrigger(listOf(Modifier.Shift, Modifier.Alt), listOf(1, 2, 4), "LM(%d, MOD_LSFT | MOD_LALT)", "SA"),
    ModTrigger(listOf(Modifier.Ctrl, Modifier.Alt), listOf(2, 3, 4), "LM(%d, MOD_LCTL | MOD_LALT)", "CA"),
    ModTrigger(
        listOf(Modifier.Shift, Modifier.Shift, Modifier.Alt),
        listOf(1, 2, 3, 4),
        "LM(%d, MOD_LCTL | MOD_LALT | MOD_LSFT)",
        "CSA"
    ),
)

private fun getSubstitutionCombo(key: String): String? =
    if (key.startsWith("\"") && key.endsWith("\"")) key else null

fun generateCombos(layers: List<Layer>, features: Set<Feature>): List<Combo> {
    val baseRows = layers[0].baseRows

    return layers.flatMap { layer ->
        val activationParts = layer.combos
        val layerBase = layer.baseRows

        hands.flatMap { hand ->
            val modCombos =
                if (features.contains(Feature.ModCombo) && layer.number == 0 && !hand.isThumb) {
                    generateModCombos(listOf(), getLayerPart(baseRows, hand), layer, hand)
                } else {
                    emptyList()
                }

            val customCombos = activationParts
                .filter { hand.applies(it) }
                .flatMap { def ->
                    generateCustomCombos(
                        def,
                        getLayerPart(layerBase.drop(hand.baseLayerRowSkip), hand),
                        layer, hand,
                    )
                }
            customCombos + modCombos
        }.distinct()
    }
}

private fun generateModCombos(
    layerTrigger: List<String>,
    opposingBase: List<String>,
    layer: Layer,
    hand: Hand
): List<Combo> {
    return if (layer.name in specialLayers) emptyList() else comboWithMods(
        opposingBase, hand,
        layer.name, layer.number, layerTrigger
    )
}

private fun generateCustomCombos(def: Rows, layerBase: List<String>, layer: Layer, hand: Hand): List<Combo> {
    val definition = getLayerPart(def, hand)
    val comboIndexes = definition.mapIndexedNotNull { index, s -> if (s == comboTrigger) index else null }

    return definition.flatMapIndexed { comboIndex, key ->
        if (!(key.isBlank() || key == blocked || key == comboTrigger)) {
            val layerKeys = layerBase
                .filterIndexed { index, _ -> index == comboIndex || index in comboIndexes }
                .map { assertQmk(it) }

            val substitutionCombo = getSubstitutionCombo(key)
            val type = if (substitutionCombo != null) ComboType.Substitution else ComboType.Combo
            val name = comboName(layer.name, key)
            val content = substitutionCombo ?: assertQmk(key)
            listOf(Combo(type, name, content, layerKeys))
        } else emptyList()
    }.filter { it.triggers.size > 1 }
}

private fun comboName(vararg parts: String?): String {
    return "C_${
        parts.filterNotNull().joinToString("_") {
            it.uppercase()
                .replace(".", "_")
                .replace(Regex("[()\"]"), "")
        }
    }"
}

private fun comboWithMods(
    base: List<String>,
    hand: Hand,
    layerName: String,
    layerIndex: Int,
    layerTrigger: List<String>
): List<Combo> {
    return modTriggers.mapNotNull { modTrigger ->
        val comboKeys = modTrigger.triggers.map { base[hand.translateComboIndex(it)] }
            .map { assertQmk(it) }

        val command = modTrigger.command.format(layerIndex)
        val allKeys = layerTrigger + comboKeys

        when {
            allKeys.size < 2 -> null //no combo needed
            comboKeys.isEmpty() -> Combo(
                ComboType.Combo,
                comboName(layerName),
                command,
                allKeys
            ).takeUnless { hand.isRight } // combo for layer is only needed once
            else -> Combo(ComboType.Combo, comboName(layerName, hand.name, modTrigger.name), command, allKeys)
        }
    }
}

private fun getLayerPart(layerBase: List<List<String>>, hand: Hand) =
    layerBase.map { it.drop(hand.skip).take(hand.comboColumns) }.flatten()
