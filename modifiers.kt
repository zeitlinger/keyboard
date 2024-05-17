enum class Modifier(val mask: String, val leftKey: String) {
    Ctrl("MOD_LCTL", "KC_LCTL"),
    Shift("MOD_LSFT", "KC_LSFT"),
    Alt("MOD_LALT", "KC_LALT");

    val short = this.name[0].uppercase()

    companion object {
        fun ofLong(value: String): Modifier = valueOf(value)
        fun ofShort(value: String): Modifier = entries.single { it.short == value }
    }
}

enum class HomeRowType(val row: Int, val oneShot: Boolean) {
    TopRow(0, false),
    OneShotTopRow(0, true),
    HomeRow(1, false),
    OneShotHomeRow(1, true),
    BottomRow(2, false),
    OneShotBottomRow(2, true);
}

fun modifierTypes(s: String): Map<HomeRowType, LayerName?> = s.split(",")
    .filter { it.isNotBlank() }.associate { def ->
        val parts = def.split("+")
        HomeRowType.valueOf(parts[0]) to parts.getOrNull(1)
    }

fun addModTab(key: String, pos: KeyPosition, translator: QmkTranslator): String {
    val layerOption = translator.layerOptions.getValue(pos.layerName)
    val column = pos.column
    val mod = translator.options.homeRowPositions?.get(fingerIndex(pos.column, pos.columns))
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
    translator: QmkTranslator,
): String = homeRowType.entries
    .firstOrNull { pos.row == it.key.row }
    ?.let { modEntry ->
        val targetLayer = modEntry.value
        val modTapKey = modTapKey(key, mod, modEntry.key, translator, pos, targetLayer)
        setCustomKeyCommand(translator, key, modTapKey, pos)
        when {
            modTapKey != key && targetLayer != null -> {
                if (key != qmkNo) throw IllegalStateException("key $key not allowed for mod tap with layer switch at $pos")
                "LM(${translator.reachLayer(targetLayer, pos, LayerActivation.ModTap).const()}, ${mod.mask})"
            }
            else -> modTapKey
        }

    } ?: key

fun setCustomKeyCommand(translator: QmkTranslator, key: String, command: String, pos: KeyPosition): Key {
    translator.symbols.customKeycodes.entries.find { it.key == key }?.let { it.value.key = command }
    translator.symbols.ignoreMissing.add(key)
    return Key(command, pos)
}

private fun modTapKey(
    key: String,
    mod: Modifier,
    type: HomeRowType,
    translator: QmkTranslator,
    pos: KeyPosition,
    targetLayer: LayerName?,
): String = when {
    key in translator.symbols.noHoldKeys -> throw IllegalStateException("key $key not allowed for mod tap at $pos")
    type.oneShot -> "OSM(${mod.mask})"
        .also { if (key != qmkNo) throw IllegalStateException("key $key not allowed for one shot modifier at $pos") }

    key == qmkNo -> {
        when {
            targetLayer != null -> {
                val name = "_${targetLayer}_${mod.short}".uppercase()
                translator.symbols.customKeycodes[name] = CustomKey(name, null, null)
                name
            }
            else -> mod.leftKey
        }
    }
    else -> {
        val simpleKey = addCustomIfNotSimpleKey(key, translator)
        when (mod) {
            Modifier.Alt -> "ALT_T($simpleKey)"
            Modifier.Ctrl -> "CTL_T($simpleKey)"
            Modifier.Shift -> "SFT_T($simpleKey)"
        }
    }
}

fun addCustomIfNotSimpleKey(key: String, translator: QmkTranslator): String =
    if (key.contains("(")) {
        translator.symbols.ignoreMissing.add(key)
        tapCustomKey(translator, key)
    } else {
        key
    }

fun tapCustomKey(translator: QmkTranslator, key: String): String {
    return customCommand(translator, "_TAP_${comboName(key)}", CustomCommandType.OnTap, listOf("tap_code16($key)"))
}

fun customCommand(translator: QmkTranslator, name: String, type: CustomCommandType, cStatements: List<String>): String {
    translator.symbols.customKeycodes[name] = CustomKey(name, null, CustomCommand(type, cStatements))
    return name
}

private fun fingerIndex(column: Int, columns: Int): Int = if (column >= columns / 2) {
    columns - column - 1
} else {
    column
}

fun fingerPos(finger: String, columns: Int): Int = when (finger) {
    "Pinky" -> (columns / 2)
    "Ring" -> (columns / 2) + 1
    "Middle" -> (columns / 2) + 2
    "Index" -> (columns / 2) + 3
    "Lower Index" -> 2 * (columns / 2) + 3
    else -> throw IllegalStateException("unknown finger $finger")
}
