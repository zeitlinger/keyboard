enum class Modifier(val mask: String, val leftKey: String) {
    Ctrl("MOD_LCTL", "KC_LCTL"),
    Shift("MOD_LSFT", "KC_LSFT"),
    Alt("MOD_LALT", "KC_LALT");

    val short = this.name[0].uppercase()

    companion object {
        fun ofLong(value: String): Modifier = valueOf(value)
    }
}

enum class HomeRowType {
    HomeRow, OneShotHomeRow, BottomRow;

    fun matchesRow(row: Int): Boolean = when (this) {
        HomeRow -> row == 1
        OneShotHomeRow -> row == 1
        BottomRow -> row == 2
    }
}

data class LayerModTab(val layer: LayerRef, val mod: Modifier)

fun targetLayerOnHold(
    modTapKeyTargetLayers: MutableMap<String, LayerModTab>,
    layer: String,
    mods: String
): String {
    return modTapKeyTargetLayers.entries.joinToString("\n            ") {
        val modTab = it.value
        "case ${it.key}: layer_$layer(${modTab.layer.const()}); ${mods}_mods(MOD_BIT(${modTab.mod.leftKey})); return false;"
    }
}

fun modifierTypes(s: String): Map<HomeRowType, LayerName?> = s.split(",")
    .filter { it.isNotBlank() }.associate { def ->
        val parts = def.split("+")
        HomeRowType.valueOf(parts[0]) to parts.getOrNull(1)
    }

data class ModTriggers(val timeout: Int, val triggers: List<ModTrigger>)
data class ModTrigger(val fingers: List<Int>, val command: String, val name: String, val timeoutDelta: Int)

fun addModTab(key: String, pos: KeyPosition, translator: QmkTranslator): String {
    val layerOption = translator.layerOptions.getValue(pos.layerName)
    val column = pos.column
    val mod = translator.options.homeRowPositions[fingerIndex(pos.column, pos.columns)]
    return when {
        mod == null || key == layerBlocked -> key
        column < pos.columns / 2 -> applyModTap(key, mod, layerOption.leftModifier, pos, translator)
        column >= pos.columns / 2 -> applyModTap(key, mod, layerOption.rightModifier, pos, translator)
        else -> key
    }
}

private fun applyModTap(
    key: String,
    mod: Modifier,
    homeRowType: Map<HomeRowType, LayerName?>,
    pos: KeyPosition,
    translator: QmkTranslator
): String = homeRowType.entries
    .firstOrNull { it.key.matchesRow(pos.row) }
    ?.let { modEntry ->
        val targetLayer = modEntry.value
        val modTapKey = modTapKey(key, mod, modEntry.key, pos)
        setCustomKeyCommand(translator, key, modTapKey)
        if (modTapKey != key && targetLayer != null) {
            val layer = translator.layer(targetLayer, pos)
            translator.modTapKeyTargetLayers[modTapKey] = LayerModTab(layer, mod)
        }

        modTapKey
    } ?: key

fun setCustomKeyCommand(translator: QmkTranslator, key: String, command: String) {
    translator.symbols.customKeycodes.entries.find { it.key == key }?.let { it.value.key = command }
}

private fun modTapKey(key: String, mod: Modifier, type: HomeRowType, pos: KeyPosition): String = when {
    type == HomeRowType.OneShotHomeRow -> "OSM(${mod.mask})"
        .also { if (key != qmkNo) throw IllegalStateException("key $key not allowed for one shot modifier") }

    key == qmkNo -> mod.leftKey
    else -> {
        assertSimpleKey(key, pos)
        when (mod) {
            Modifier.Alt -> "ALT_T($key)"
            Modifier.Ctrl -> "CTL_T($key)"
            Modifier.Shift -> "SFT_T($key)"
        }
    }
}

fun assertSimpleKey(key: String, pos: KeyPosition): String {
    if (key.contains("(")) throw IllegalStateException("key $key not allowed for modifier at $pos")
    return key
}

fun addCustomIfNotSimpleKey(key: String, translator: QmkTranslator): String =
    if (key.contains("(")) {
        tapCustomKey(translator, key)
    } else {
        key
    }

fun tapCustomKey(translator: QmkTranslator, key: String): String {
    val custom = "_TAP_${comboName(key)}"
    translator.symbols.customKeycodes[custom] = CustomKey(custom, null, key)
    return custom
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
val homeRowThumbTriggers: Map<List<Modifier>, String> = createModTemplate("LM(%%s, %s)")

fun generateModCombos(
    name: String,
    layerTrigger: List<Key>,
    opposingBase: List<Key>,
    layer: Layer?,
    hand: Hand,
    triggers: ModTriggers,
    options: Options,
): List<Combo> {
    val columns = hand.columns(options) / 2
    return triggers.triggers.mapNotNull { modTrigger ->
        val comboKeys = modTrigger.fingers.map {
            val row = it / columns
            val column = it % columns
            val targetCol = if (hand.isRight) columns - column - 1 else column
            opposingBase[row * columns + targetCol]
        }

        val command = layer?.let { modTrigger.command.format(layer.name.const()) } ?: modTrigger.command
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

