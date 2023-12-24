data class KeyPosition(
    val row: Int,
    val column: Int,
    val layerName: LayerName,
    val thumb: Boolean,
    val columns: Int,
)

fun readLayer(
    content: MultiTable,
    translator: QmkTranslator,
    layerName: LayerName,
    layerIndex: Int,
): Layer {
    val data = translateTable(content, translator, layerName, false)
    val base = data[0]
    val option = translator.layerOptions.getValue(layerName)

    val combos = data.drop(1)

    val thumbData = translateTable(
        translator.getThumbContent(layerName),
        translator,
        layerName,
        true,
    )
    val baseThumb = thumbData[0]
    val comboThumb = thumbData.drop(1)

    return Layer(
        layerName,
        (base + baseThumb),
        combos + comboThumb,
        layerIndex,
        translator.comboLayerTrigger[layerName],
        option
    )
}

fun translateKey(
    translator: QmkTranslator,
    pos: KeyPosition,
    s: String,
): Key = getFallback(s, translator, pos).let { def ->
    when {
        //comes first, so that we can override the meaning of + and -
        def == qmkNo || translator.symbols.mapping.containsKey(def) -> translateSimpleKey(translator, def, pos)
        def.contains(" ") && !def.startsWith("\"") -> spaceSeparatedHint(def, translator, pos)
        def.contains("+") && def.length > 1 -> layerTapHoldKey(def, translator, pos)
        def.contains("-") && def.length > 1 -> keyWithModifier(def, translator, pos)
        def.startsWith("=") && def.length > 1 -> layerKey(
            translator,
            pos,
            def.substring(1),
            LayerActivation.Toggle
        )

        def.startsWith("*") && def.length > 1 -> layerKey(
            translator,
            pos,
            def.substring(1),
            LayerActivation.Hold
        )
        //skip QMK keycodes
        def.isNotBlank() && def[0].isUpperCase() && !def.contains("_") -> layerKey(
            translator,
            pos,
            def,
            LayerActivation.OneShot
        )

        else -> translateSimpleKey(translator, def, pos)
    }
}

fun spaceSeparatedHint(def: String, translator: QmkTranslator, pos: KeyPosition): Key {
    val parts = def.split(" ")
    val right = parts[1].trim()
    val left = parts[0].trim()
    return when {
        def.startsWith("ComboLayer:") -> {
            comboLayer(left, translator, pos, right)
        }

        def.startsWith("HomeRowThumbCombo:") -> {
            val targetLayer = left.split(":")[1]
            val key = translateKey(translator, pos, right)
            translator.homeRowThumbCombo = HomeRowCombo(targetLayer, key)
            key
        }

        parts.size == 2 && right[0].isDigit() -> translateKey(translator, pos, left).copy(comboTimeout = right.toInt())
        else -> throw IllegalArgumentException("unknown command '$def' in $pos")
    }
}

private fun layerTapHoldKey(def: String, translator: QmkTranslator, pos: KeyPosition): Key {
    val parts = def.split("+")
    val key = addCustomIfNotSimpleKey(translateKey(translator, pos, parts[0]).key, translator)
    val command = "LT(${translator.reachLayer(parts[1], pos, LayerActivation.TapHold).const()},$key)"
    translator.layerTapHold.add(command)
    setCustomKeyCommand(translator, key, command)
    return Key(command)
}

fun layerKey(
    translator: QmkTranslator,
    pos: KeyPosition,
    layer: String,
    activation: LayerActivation,
): Key {
    val layerOption = translator.layerOptions.getValue(layer)
    val layerActivation = adjustFallback(activation, translator.layerOptions.getValue(pos.layerName))
    if (layerActivation == LayerActivation.Toggle && pos.layerName == layer) {
        layerOption.flags += LayerFlag.Toggle
    }
    if (layerOption.flags.contains(LayerFlag.Hidden)) {
        throw IllegalArgumentException("can't toggle hidden layer $layer at $pos")
    }
    return Key("${layerActivation.method}(${translator.reachLayer(layer, pos, activation).const()})")
}

fun comboLayer(left: String, translator: QmkTranslator, pos: KeyPosition, right: String): Key {
    val trigger = left.split(":")[1].split(",")
    val layerName = trigger[0]
    val timeout = trigger.getOrNull(1)?.toIntOrNull()
    translator.reachLayer(layerName, pos, LayerActivation.ComboLayer)
    return translator.layerOptions[layerName]?.let {
        val key = translateKey(translator, pos, right)
        translator.comboLayerTrigger[layerName] = key.copy(comboTimeout = timeout)
        key
    } ?: throw IllegalArgumentException("unknown layer $layerName in $pos")
}


fun keyWithModifier(def: String, translator: QmkTranslator, pos: KeyPosition): Key {
    val parts = def.split("-")
    val modifier = parts[0]
    val key = translateKey(translator, pos, parts[1])
    return if (key.keyWithModifier.contains("(")) {
        val tapCustomKey = tapCustomKey(translator, addMods(modifier, key.key))
        Key(translateKey(translator, pos, tapCustomKey).keyWithModifier)
    } else {
        val s = key.key
        Key(addMods(modifier, s))
    }
}

fun addMods(modifier: String, key: String) =
    when (modifier) {
        "A" -> "A(${key})"
        "C" -> "C(${key})"
        "S" -> "S(${key})"
        "CA" -> "LCA(${key})"
        "CS" -> "RCS(${key})"
        else -> throw IllegalStateException("unknown modifier '$modifier'")
    }

fun translateSimpleKey(translator: QmkTranslator, def: String, pos: KeyPosition): Key {
    val key = translator.toQmk(def, pos)
    return Key(key, addModTab(key, pos, translator))
}

fun translateTable(
    tables: MultiTable,
    translator: QmkTranslator,
    layerName: LayerName,
    thumb: Boolean,
): List<Rows> = tables.map { table ->
    table.mapIndexed { rowNumber, row ->
        row.mapIndexed { column, def ->
            translateKey(
                translator, KeyPosition(
                    rowNumber, column, layerName, thumb,
                    if (thumb) translator.options.thumbColumns else translator.options.nonThumbColumns
                ), def
            )
        }
    }
}

fun adjustFallback(activation: LayerActivation, option: LayerOption): LayerActivation = when {
    option.flags.contains(LayerFlag.OslToToggle) -> LayerActivation.Toggle
    else -> activation
}

fun getFallback(
    key: String,
    translator: QmkTranslator,
    pos: KeyPosition,
): String {
    if (key == qmkNo || key == layerBlocked) {
        return qmkNo
    }
    val option = translator.layerOptions[pos.layerName] ?: throw IllegalStateException("can't find layer at $pos")
    if (key.isNotBlank()) {
        return key
    }
    val left = pos.column < pos.columns / 2
    val fallbackLayer = if (left) option.leftFallbackLayer else option.rightFallbackLayer
    return when {
        pos.thumb || fallbackLayer == null || pos.layerName == baseLayerName -> qmkNo
        else -> {
            val newPos = pos.copy(layerName = fallbackLayer)
            getFallback(
                translator.getKey(newPos),
                translator,
                newPos
            )
        }
    }
}
