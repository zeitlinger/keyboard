enum class Modifier {
    Alt, Shift, Ctrl
}

enum class ModifierType {
    HomeRow, BottomRow;

    fun matchesRow(row: Int): Boolean = when (this) {
        HomeRow -> row == 1
        BottomRow -> row == 2
    }
}

fun modifierTypes(s: String): List<ModifierType> = s.split(",")
    .filter { it.isNotBlank() }
    .map { mod ->
        when (mod.trim()) {
            "HomeRow" -> ModifierType.HomeRow
            "BottomRow" -> ModifierType.BottomRow
            else -> throw IllegalStateException("unknown modifier type $mod")
        }
    }

data class ModTrigger(val triggers: List<Int>, val command: String, val name: String?)

fun addModTab(rowNumber: Int, row: List<String>, option: LayerOption): List<String> {
    return row.mapIndexed { index, key ->
        when {
            "(" in key || key == layerBlocked -> {
                key
            }

            index < 4 && option.leftModifier.any { it.matchesRow(rowNumber) } -> {
                if (key == blocked) {
                    when (index) {
                        1 -> "KC_LALT"
                        2 -> "KC_LCTL"
                        3 -> "KC_LSFT"
                        else -> key
                    }
                } else {
                    when (index) {
                        1 -> "LALT_T($key)"
                        2 -> "LCTL_T($key)"
                        3 -> "LSFT_T($key)"
                        else -> key
                    }
                }
            }

            index >= 4 && option.rightModifier.any { it.matchesRow(rowNumber) } -> {
                if (key == blocked) {
                    when (index) {
                        4 -> "KC_RSFT"
                        5 -> "KC_RCTL"
                        6 -> "KC_LALT"
                        else -> key
                    }
                } else {
                    when (index) {
                        4 -> "RSFT_T($key)"
                        5 -> "RCTL_T($key)"
                        6 -> "LALT_T($key)"
                        else -> key
                    }
                }
            }

            else -> key
        }
    }
}

val modTriggers: List<ModTrigger> = listOf(
    ModTrigger(emptyList(), "MO(%d)", null),
    ModTrigger(listOf(1, 2), "LM(%d, MOD_LSFT)", "S"),
    ModTrigger(listOf(2, 4), "LM(%d, MOD_LCTL)", "C"),
    ModTrigger(listOf(1, 4), "LM(%d, MOD_LALT)", "A"),
    ModTrigger(listOf(1, 2, 3), "LM(%d, MOD_LCTL | MOD_LSFT)", "CS"),
    ModTrigger(listOf(1, 2, 4), "LM(%d, MOD_LSFT | MOD_LALT)", "SA"),
    ModTrigger(listOf(2, 3, 4), "LM(%d, MOD_LCTL | MOD_LALT)", "CA"),
    ModTrigger(
        listOf(1, 2, 3, 4),
        "LM(%d, MOD_LCTL | MOD_LALT | MOD_LSFT)",
        "CSA"
    ),
)

val homeRowTriggers: List<ModTrigger> = listOf(
    ModTrigger(emptyList(), "MO(%d)", null),
    ModTrigger(listOf(1), "LM(%d, MOD_LALT)", "A"),
    ModTrigger(listOf(2), "LM(%d, MOD_LCTL)", "C"),
    ModTrigger(listOf(3), "LM(%d, MOD_LSFT)", "S"),
    ModTrigger(listOf(2, 3), "LM(%d, MOD_LCTL | MOD_LSFT)", "CS"),
    ModTrigger(listOf(1, 3), "LM(%d, MOD_LSFT | MOD_LALT)", "SA"),
    ModTrigger(listOf(1, 2), "LM(%d, MOD_LCTL | MOD_LALT)", "CA"),
    ModTrigger(
        listOf(1, 2, 3),
        "LM(%d, MOD_LCTL | MOD_LALT | MOD_LSFT)",
        "CSA"
    ),
)

fun generateModCombos(
    layerTrigger: List<String>,
    opposingBase: List<String>,
    layer: Layer,
    hand: Hand,
    template: List<ModTrigger>
): List<Combo> {
    val layerName = layer.name
    val layerIndex = layer.number
    return template.mapNotNull { modTrigger ->
        val comboKeys = modTrigger.triggers.map { opposingBase[hand.translateComboIndex(it)] }

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

