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

fun modifierTypes(s: String): Map<ModifierType, LayerName?> = s.split(",")
    .filter { it.isNotBlank() }.associate { def ->
        val parts = def.split("+")
        ModifierType.valueOf(parts[0]) to parts.getOrNull(1)
    }

data class ModTriggers(val timeout: Int, val triggers: List<ModTrigger>)
data class ModTrigger(val fingers: List<Int>, val command: String, val name: String, val timeoutDelta: Int)

fun addModTab(key: String, pos: KeyPosition, translator: QmkTranslator): String {
    val layerOption = translator.layerOptions.getValue(pos.layerName)
    val column = pos.column
    val mod = translator.options.homeRowPositions[fingerIndex(pos.column, pos.columns)]
    return when {
        key == layerBlocked -> key
        column < pos.columns / 2 -> applyModTap(key, mod, layerOption.leftModifier, pos, translator)
        column >= pos.columns / 2 -> applyModTap(key, mod, layerOption.rightModifier, pos, translator)
        else -> key
    }
}

private fun applyModTap(
    key: String,
    mod: Modifier?,
    modifierType: Map<ModifierType, LayerName?>,
    pos: KeyPosition,
    translator: QmkTranslator
): String = modifierType.entries
    .firstOrNull { it.key.matchesRow(pos.row) }
    ?.let { modEntry ->
        val targetLayer = modEntry.value
        val modTapKey = modTapKey(key, mod)
        if (modTapKey != key && targetLayer != null) {
            translator.modTapKeyTargetLayers[modTapKey] = translator.mustTranslateLayer(targetLayer)
        }

        modTapKey
    } ?: key

private fun modTapKey(key: String, mod: Modifier?): String = when (key) {
    qmkNo -> when (mod) {
        Modifier.Alt -> "KC_LALT"
        Modifier.Ctrl -> "KC_LCTL"
        Modifier.Shift -> "KC_LSFT"
        else -> key
    }
    else -> when (mod) {
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

fun createModTriggers(mappingTable: Table, template: Map<List<Modifier>, String>): ModTriggers {
    val timeout = getModTimeout(mappingTable)
    val modTriggers = mappingTable.drop(1).map { (triggers, fingers, timeoutDelta) ->
        val modifiers = triggers.split("-").map {
            Modifier.ofLong(it)
        }.sorted()

        val fingerIndexes = fingers.split(", ").map { finger ->
            fingerPos(finger)
        }

        ModTrigger(fingerIndexes, template.getValue(modifiers), modPrefix(modifiers), timeoutDelta.toIntOrNull() ?: 0)
    }
    return ModTriggers(timeout, modTriggers)
}

private fun getModTimeout(mappingTable: Table) = mappingTable[0][1].toIntOrNull() ?: 0

fun createThumbModTriggers(
    mappingTable: Table,
    template: Map<List<Modifier>, String>,
    homeRowPositions: Map<Int, Modifier>
): ModTriggers {
    val modTriggers = template.map { (modifiers, command) ->
        val fingers = modifiers.map { mod ->
            homeRowPositions.entries.single { it.value == mod }.key
        }
        ModTrigger(fingers, command, modPrefix(modifiers), 0)
    }
    return ModTriggers(getModTimeout(mappingTable), modTriggers)
}

private fun modPrefix(keys: List<Modifier>) = keys.joinToString("") { it.short }


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
    listOf(Modifier.Ctrl, Modifier.Shift),
    listOf(Modifier.Shift, Modifier.Alt, Modifier.Ctrl)
)

fun createModTemplate(template: String): Map<List<Modifier>, String> {
    return modifierPermutations.associateWith { mods -> template.format(mods.joinToString(" | ") { it.mask }) }
}

val homeRowOneShotTriggers: Map<List<Modifier>, String> = createModTemplate("OSM(%s)")
val homeRowThumbTriggers: Map<List<Modifier>, String> = createModTemplate("LM(%%d, %s)")

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

