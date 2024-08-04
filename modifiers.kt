enum class Modifier(val mask: String, val leftKey: QmkKey, val tapKey: String, val short: String) {
    Ctrl("MOD_LCTL", QmkKey("KC_LCTL"), "CTL_T", "C"),
    Shift("MOD_LSFT", QmkKey("KC_LSFT"), "SFT_T", "S"),
    Alt("MOD_LALT", QmkKey("KC_LALT"), "ALT_T", "A"),;

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

fun addModTab(key: QmkKey, pos: KeyPosition, translator: QmkTranslator): QmkKey {
    val layerOption = translator.layerOptions.getValue(pos.layerName)
    val column = pos.column
    val mod = translator.options.homeRowPositions?.get(fingerIndex(pos.column, pos.columns))
    return when {
        mod == null -> key
        column < pos.columns / 2 -> applyModTap(key, mod, layerOption.leftModifier, pos, translator)
        column >= pos.columns / 2 -> applyModTap(key, mod, layerOption.rightModifier, pos, translator)
        else -> key
    }
}

private fun applyModTap(
    key: QmkKey,
    mod: Modifier,
    homeRowType: Map<HomeRowType, LayerName?>,
    pos: KeyPosition,
    translator: QmkTranslator,
): QmkKey = homeRowType.entries
    .firstOrNull { pos.row == it.key.row }
    ?.let { modEntry ->
        val targetLayer = modEntry.value
        val modTapKey = modTapKey(key, mod, modEntry.key, translator, pos, targetLayer)
        setCustomKeyCommand(translator, key, modTapKey, pos)
        when {
            modTapKey != key && targetLayer != null -> {
                if (!key.isNo) throw IllegalStateException("key $key not allowed for mod tap with layer switch at $pos")
                QmkKey("LM(${translator.reachLayer(targetLayer, pos, LayerActivation.ModTap).const()}, ${mod.mask})")
            }
            else -> modTapKey
        }
    } ?: key

fun setCustomKeyCommand(translator: QmkTranslator, key: QmkKey, command: QmkKey, pos: KeyPosition): Key {
    translator.symbols.customKeycodes.entries.find { it.key == key.key }?.let { it.value.key = command }
    translator.ignoreMissing.add(key)
    return Key(command, pos)
}

private fun modTapKey(
    key: QmkKey,
    mod: Modifier,
    type: HomeRowType,
    translator: QmkTranslator,
    pos: KeyPosition,
    targetLayer: LayerName?,
): QmkKey = when {
    key in translator.noHoldKeys -> throw IllegalStateException("key $key not allowed for mod tap at $pos")
    type.oneShot -> QmkKey("OSM(${mod.mask})")
        .also { if (!key.isNo) throw IllegalStateException("key $key not allowed for one shot modifier at $pos") }

    key.isNo -> {
        when {
            targetLayer != null -> {
                val name = QmkKey("_${targetLayer}_${mod.short}".uppercase())
                translator.symbols.customKeycodes[name.key] = CustomKey(name, null, null)
                name
            }
            else -> mod.leftKey
        }
    }
    else -> {
        val simpleKey = addCustomIfNotSimpleKey(key, translator)
        QmkKey("${mod.tapKey}($simpleKey)")
    }
}

fun addCustomIfNotSimpleKey(key: QmkKey, translator: QmkTranslator): QmkKey =
    if (key.key.contains("(")) {
        translator.ignoreMissing.add(key)
        tapCustomKey(translator, key)
    } else {
        key
    }

fun tapCustomKey(translator: QmkTranslator, key: QmkKey): QmkKey {
    return customCommand(translator, QmkKey("_TAP_${comboName(key.key)}"), CustomCommandType.OnTap, listOf(tap(key)))
}

fun tap(key: QmkKey) = "tap_code16($key)"

fun customCommand(translator: QmkTranslator, qmkKey: QmkKey, type: CustomCommandType, cStatements: List<String>): QmkKey {
    translator.symbols.customKeycodes[qmkKey.key] = CustomKey(qmkKey, null, CustomCommand(type, cStatements))
    return qmkKey
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
