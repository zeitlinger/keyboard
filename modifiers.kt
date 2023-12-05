enum class Modifier(val mask: String) {
    Ctrl("MOD_LCTL"), Shift("MOD_LSFT"), Alt("MOD_LALT");

    val short = this.name[0].uppercase()

    companion object {
        fun ofShort(value: String): Modifier = entries.single { it.short == value }

        fun ofLong(value: String): Modifier = valueOf(value)
    }
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
data class ModTrigger(val fingers: List<Int>, val command: String, val name: String, val timeoutDelta: Int)

fun addModTab(key: String, pos: KeyPosition, translator: QmkTranslator): String {
    val layerOption = translator.layerOption.getValue(pos.layerName)
    val column = pos.column
    val mod = translator.options.homeRowPositions[fingerIndex(pos.column, pos.columns)]
    val row = pos.row
    return when {
        key == layerBlocked -> key

        column < pos.columns / 2 && layerOption.leftModifier.any { it.matchesRow(row) } -> applyModTap(key, mod)
        column >= pos.columns / 2 && layerOption.rightModifier.any { it.matchesRow(row) } -> applyModTap(key, mod)
        else -> key
    }
}

private fun applyModTap(key: String, mod: Modifier?) = if (key == qmkNo) {
    when (mod) {
        Modifier.Alt -> "KC_LALT"
        Modifier.Ctrl -> "KC_LCTL"
        Modifier.Shift -> "KC_LSFT"
        else -> key
    }
} else {
    when (mod) {
        Modifier.Alt -> "ALT_T($key)"
        Modifier.Ctrl -> "CTL_T($key)"
        Modifier.Shift -> "SFT_T($key)"
        else -> key
    }
}

private fun fingerIndex(column: Int, columns: Int): Int = if (column >= columns / 2) {
    columns - column - 1
} else {
    column
}

fun createModTriggers(mappingTable: Table, template: Map<String, String>): ModTriggers {
    val timeout = getModTimeout(mappingTable)
    val modTriggers = mappingTable.drop(1).map { (triggers, fingers, timeoutDelta) ->
        val key = triggers.split("-").map {
            Modifier.ofLong(it)
        }.sorted().joinToString("") { it.short }

        val fingerIndexes = fingers.split(", ").map { finger ->
            fingerPos(finger)
        }

        ModTrigger(fingerIndexes, template.getValue(key), key, timeoutDelta.toIntOrNull() ?: 0)
    }
    return ModTriggers(timeout, modTriggers)
}

private fun getModTimeout(mappingTable: Table) = mappingTable[0][1].toIntOrNull() ?: 0

fun createThumbModTriggers(
    mappingTable: Table,
    template: Map<String, String>,
    homeRowPositions: Map<Int, Modifier>
): ModTriggers {
    val modTriggers = template.map { (keys, command) ->
        val fingers = keys.toCharArray().map { key ->
            val mod = Modifier.ofShort(key.toString())
            homeRowPositions.entries.single { it.value == mod }.key
        }
        ModTrigger(fingers, command, keys, 0)
    }
    return ModTriggers(getModTimeout(mappingTable), modTriggers)
}


fun fingerPos(finger: String): Int = when (finger) {
    "Pinky" -> 4
    "Ring" -> 5
    "Middle" -> 6
    "Index" -> 7
    "Lower Index" -> 11
    else -> throw IllegalStateException("unknown finger $finger")
}

val modifierPermutations = listOf(
    listOf(Modifier.Alt),
    listOf(Modifier.Ctrl),
    listOf(Modifier.Shift),
    listOf(Modifier.Alt, Modifier.Ctrl),
    listOf(Modifier.Shift, Modifier.Alt),
    listOf(Modifier.Ctrl, Modifier.Alt),
    listOf(Modifier.Shift, Modifier.Alt, Modifier.Ctrl)
)

fun createModTemplate(template: String): Map<String, String> {
    return modifierPermutations.associate { mods ->
        mods.joinToString("") { it.short } to template.format(mods.joinToString(" | ") { it.mask })
    }
}

val homeRowOneShotTriggers: Map<String, String> = createModTemplate("OSM(%s)")
val homeRowThumbTriggers: Map<String, String> = createModTemplate("LM(%%d, %s)")

fun generateModCombos(
    name: String,
    layerTrigger: List<Key>,
    opposingBase: List<Key>,
    layer: Layer?,
    hand: Hand,
    triggers: ModTriggers,
    options: Options,
): List<Combo> {
    val layerIndex = layer?.number
    val columns = hand.columns(options) / 2
    return triggers.triggers.mapNotNull { modTrigger ->
        val comboKeys = modTrigger.fingers.map {
            val row = it / columns
            val column = it % columns
            val targetCol = if (hand.isRight) columns - column - 1 else column
            opposingBase[row * columns + targetCol]
        }

        val command = layer?.let { modTrigger.command.format(layerIndex) } ?: modTrigger.command
        val allKeys = layerTrigger + comboKeys

        when {
            allKeys.size < 2 -> null //no combo needed
            comboKeys.isEmpty() -> Combo.of(
                ComboType.Combo,
                comboName(name),
                command,
                allKeys,
                null
            ).takeUnless { hand.isRight } // combo for layer is only needed once
            else -> Combo.of(
                ComboType.Combo,
                comboName(name, hand.name, modTrigger.name),
                command,
                allKeys,
                triggers.timeout + modTrigger.timeoutDelta
            )
        }
    }
}

