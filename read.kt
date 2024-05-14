data class KeyPosition(
    val tableIndex: Int,
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
        option
    )
}

fun translateKey(
    translator: QmkTranslator,
    pos: KeyPosition,
    command: String,
    recordUsage: Boolean = true,
): Key = getFallbackIfNeeded(command, translator, pos, null, recordUsage).let { def ->
    when {
        //comes first, so that we can override the meaning of + and -
        def == qmkNo || translator.symbols.mapping.containsKey(def) -> translateSimpleKey(translator, def, pos)
        def.contains(" ") && !def.startsWith("\"") -> spaceSeparatedHint(def, translator, pos)
        def.contains("+") && !def.startsWith("+") -> layerTapHoldKey(def, translator, pos)

        def.contains("-") && def.length > 1 -> when {
            def == "--" -> layerKey(translator, pos, pos.layerName, LayerActivation.Toggle)
            else -> keyWithModifier(def, translator, pos)
        }

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
            LayerActivation.Toggle
        )

        else -> translateSimpleKey(translator, def, pos)
    }
}

fun spaceSeparatedHint(def: String, translator: QmkTranslator, pos: KeyPosition): Key {
    val parts = def.split(" ")
    val right = parts[1].trim()
    val left = parts[0].trim()
    val base = translateKey(translator, pos, left)
    return when {
        parts.size == 2 && right[0].isDigit() -> base.copy(comboTimeout = right.toInt())
        parts.size == 2 && right.startsWith("@") -> base.also {
            val target = translateKey(translator, pos, right.substringAfter("@"), false)
            translator.symbols.altRepeat[base.key] = target.key
        }

        else -> throw IllegalArgumentException("unknown command '$def' in $pos")
    }
}

private fun layerTapHoldKey(def: String, translator: QmkTranslator, pos: KeyPosition): Key {
    val parts = def.split("+")
    val key = addCustomIfNotSimpleKey(translateKey(translator, pos, parts[0]).key, translator)
    if (key in translator.symbols.noHoldKeys) {
        throw IllegalArgumentException("key $key not allowed for tap hold at $pos")
    }
    val command = "LT(${translator.reachLayer(parts[1], pos, LayerActivation.TapHold).const()},$key)"
    translator.layerTapHold.add(command)
    return setCustomKeyCommand(translator, key, command)
}

fun layerKey(
    translator: QmkTranslator,
    pos: KeyPosition,
    layer: String,
    activation: LayerActivation,
): Key {
    val layerOption = translator.layerOptions.getValue(layer)
    translator.layerOptions.getValue(pos.layerName)
    if (activation == LayerActivation.Toggle && pos.layerName == layer) {
        layerOption.flags += LayerFlag.Toggle
    }
    return when (activation) {
        LayerActivation.Toggle -> toggleLayerKey(translator, layer, pos, null)
        LayerActivation.Hold -> Key(
            "${activation.method}(${
                translator.reachLayer(layer, pos, activation).const()
            })"
        )

        else -> throw IllegalArgumentException("unsupported layer activation $activation")
    }
}

fun toggleLayerKey(translator: QmkTranslator, layer: String, pos: KeyPosition, modifier: Modifier?): Key {
    translator.reachLayer(layer, pos, LayerActivation.Hold)
    val mod = modifier?.let { "add_oneshot_mods(MOD_BIT(${it.leftKey}))" }
    val prefix = modifier?.short ?: "L"
    val key = "${prefix}_${layer.uppercase()}"
    val command =
        customCommand(translator, key, CustomCommandType.OnPress, listOfNotNull("layer_invert(${layer.const()})", mod))
    return setCustomKeyCommand(translator, key, command)
}

fun keyWithModifier(def: String, translator: QmkTranslator, pos: KeyPosition): Key {
    val parts = def.split("-")
    val modifier = parts[0]
    val target = parts[1]
    if (translator.layerOptions[target] != null) {
        return toggleLayerKey(translator, target, pos, Modifier.ofShort(modifier))
    }
    val key = translateKey(translator, pos, target, false)
    return if (key.keyWithModifier.contains("(")) {
        val tapCustomKey = tapCustomKey(translator, addMods(modifier, key.key))
        Key(translateKey(translator, pos, tapCustomKey, false).keyWithModifier)
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
): List<Rows> = tables.mapIndexed { tableIndex, table ->
    table.mapIndexed { rowNumber, row ->
        row.mapIndexed { column, def ->
            translateKey(
                translator, KeyPosition(
                    tableIndex, rowNumber, column, layerName, thumb,
                    if (thumb) translator.options.thumbColumns else translator.options.nonThumbColumns
                ), def
            )
        }
    }
}

fun getFallbackIfNeeded(
    key: String,
    translator: QmkTranslator,
    pos: KeyPosition,
    srcLayerOption: LayerOption?,
    recordUsage: Boolean,
): String {
    if (key == qmkNo || key == layerBlocked) {
        return qmkNo
    }
    if (srcLayerOption != null && key.contains("*")) {
        return qmkNo
    }
    if (key.isNotBlank()) {
        val k = key.substringBeforeLast("+").substringBefore(" ")
        if (recordUsage) {
            translator.gotKey(key)
        }
        if (srcLayerOption != null) {
            if (srcLayerOption.flags.contains(LayerFlag.Shifted)) {
                return "S(${translateKey(translator, pos, k, false).key})"
            }
            return k
        }
        return key
    }
    val left = pos.column < pos.columns / 2
    val fallbackLayer = if (left) {
        (translator.layerOptions[pos.layerName]
            ?: throw IllegalStateException("can't find layer at $pos")).leftFallbackLayer
    } else {
        (translator.layerOptions[pos.layerName]
            ?: throw IllegalStateException("can't find layer at $pos")).rightFallbackLayer
    }
    return when {
        fallbackLayer == null || pos.layerName == baseLayerName || pos.tableIndex > 0 -> qmkNo
        else -> {
            val newPos = pos.copy(layerName = fallbackLayer)
            getFallbackIfNeeded(
                translator.getKey(newPos),
                translator,
                newPos,
                translator.layerOptions[pos.layerName] ?: throw IllegalStateException("can't find layer at $pos"),
                false
            )
        }
    }
}
