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

data class ModTriggers(val timeout: Int, val triggers: List<ModTrigger>)
data class ModTrigger(val triggers: List<Int>, val command: String, val name: String, val timeoutDelta: Int = 0)

fun addModTab(key: String, pos: KeyPosition, translator: QmkTranslator): String {
    val layerOption = translator.layerOption.getValue(pos.layerName)
    val column = pos.column
    val fingerIndex = if (pos.column >= pos.columns / 2) {
        pos.columns - pos.column - 1
    } else {
        pos.column
    }
    val mod = translator.options.homeRowPositions[fingerIndex]
    val row = pos.row
    return when {
        key == layerBlocked -> key

        column < pos.columns / 2 && layerOption.leftModifier.any { it.matchesRow(row) } -> if (key == qmkNo) {
            when (mod) {
                "Alt" -> "KC_LALT"
                "Ctrl" -> "KC_LCTL"
                "Shift" -> "KC_LSFT"
                else -> key
            }
        } else {
            when (mod) {
                "Alt" -> "LALT_T($key)"
                "Ctrl" -> "LCTL_T($key)"
                "Shift" -> "LSFT_T($key)"
                else -> key
            }
        }

        column >= pos.columns / 2 && layerOption.rightModifier.any { it.matchesRow(row) } -> if (key == qmkNo) {
            when (mod) {
                "Shift" -> "KC_RSFT"
                "Ctrl" -> "KC_RCTL"
                "Alt" -> "KC_LALT"
                else -> key
            }
        } else {
            when (mod) {
                "Shift" -> "RSFT_T($key)"
                "Ctrl" -> "RCTL_T($key)"
                "Alt" -> "LALT_T($key)"
                else -> key
            }
        }

        else -> key
    }
}

fun createModTriggers(mappingTable: Table, template: Map<String, String>): ModTriggers {
    val timeout = mappingTable[1][1].toIntOrNull() ?: 0
    val modTriggers = mappingTable.drop(2).map { (triggers, fingers, timeoutDelta) ->
        val key = triggers.split("-").map {
            when (it) {
                "Shift" -> "S"
                "Ctrl" -> "C"
                "Alt" -> "A"
                else -> throw IllegalStateException("unknown modifier $it")
            }
        }.sortedBy {
            when (it) {
                "C" -> 0
                "S" -> 1
                "A" -> 2
                else -> throw IllegalStateException("unknown modifier $it")
            }
        }.joinToString("")

        val fingerIndexes = fingers.split(", ").map { finger ->
            fingerPos(finger)
        }

        ModTrigger(fingerIndexes, template.getValue(key), key, timeoutDelta.toIntOrNull() ?: 0)
    }
    return ModTriggers(timeout, modTriggers)
}

fun fingerPos(finger: String) = when (finger) {
    "Pinky" -> 0
    "Ring" -> 1
    "Middle" -> 2
    "Index" -> 3
    else -> throw IllegalStateException("unknown finger $finger")
}

val homeRowOneShotTriggers: Map<String, String> = mapOf(
        "A" to "OSM(MOD_LALT)",
        "C" to "OSM(MOD_LCTL)",
        "S" to "OSM(MOD_LSFT)",
        "CS" to "OSM(MOD_LCTL | MOD_LSFT)",
        "SA" to "OSM(MOD_LSFT | MOD_LALT)",
        "CA" to "OSM(MOD_LCTL | MOD_LALT)",
        "CSA" to "OSM(MOD_LCTL | MOD_LALT | MOD_LSFT)"
)

val homeRowThumbTriggers: Map<String, String> = mapOf(
        "A" to "LM(%d, MOD_LALT)",
        "C" to "LM(%d, MOD_LCTL)",
        "S" to "LM(%d, MOD_LSFT)",
        "CS" to "LM(%d, MOD_LCTL | MOD_LSFT)",
        "SA" to "LM(%d, MOD_LSFT | MOD_LALT)",
        "CA" to "LM(%d, MOD_LCTL | MOD_LALT)",
        "CSA" to "LM(%d, MOD_LCTL | MOD_LALT | MOD_LSFT)"
)

fun generateModCombos(
        name: String,
        layerTrigger: List<Key>,
        opposingBase: List<Key>,
        layer: Layer?,
        hand: Hand,
        triggers: ModTriggers,
): List<Combo> {
    val layerIndex = layer?.number
    return triggers.triggers.mapNotNull { modTrigger ->
        val comboKeys = modTrigger.triggers.map { opposingBase[hand.translateComboIndex(it)] }

        val command = layer?.let { modTrigger.command.format(layerIndex) } ?: modTrigger.command
        val allKeys = layerTrigger + comboKeys

        when {
            allKeys.size < 2 -> null //no combo needed
            comboKeys.isEmpty() -> Combo(
                    ComboType.Combo,
                    comboName(name),
                    command,
                    allKeys,
                    null
            ).takeUnless { hand.isRight } // combo for layer is only needed once
            else -> Combo(ComboType.Combo, comboName(name, hand.name, modTrigger.name), command, allKeys, triggers.timeout + modTrigger.timeoutDelta)
        }
    }
}

