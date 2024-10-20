data class KeyPosition(
    val tableIndex: Int,
    val row: Int,
    val column: Int,
    val layerName: LayerName,
    val columns: Int,
) {
    fun layerRelative() = copy(layerName = "relative")
}

fun readLayer(
    content: MultiTable,
    translator: QmkTranslator,
    layerName: LayerName,
    layerIndex: Int,
): Layer {
    val data = translateTable(content, translator, layerName)
    val base = data[0]
    val option = translator.layerOptions.getValue(layerName)

    val combos = data.drop(1)

    return Layer(
        layerName,
        base,
        combos,
        layerIndex,
        option
    )
}

fun translateKey(
    translator: QmkTranslator,
    pos: KeyPosition,
    command: String,
    recordUsage: Boolean = true,
): Key = getFallbackIfNeeded(command, translator, pos, null, recordUsage)
    .let { def ->
        findLayerActivationKey(def, translator, pos) ?: when {
            //comes first, so that we can override the meaning of + and -
            def == qmkNo || translator.symbols.mapping.containsKey(def) -> translateSimpleKey(translator, def, pos)
            def.contains(" ") && !def.startsWith("\"") -> spaceSeparatedHint(def, translator, pos)
            def.contains("+") && !def.startsWith("+") -> layerTapHoldKey(def, translator, pos)

            def.contains("-") && def.length > 1 -> when {
                def == "--" -> layerOffKey(translator, pos, pos.layerName)
                else -> keyWithModifier(def, translator, pos)
            }

            def.contains("/") && def.length > 1 -> {
                val parts = def.split("/")
                val up = parts[0].trim()
                val down = parts[1].trim()
                val key = layerKey(translator, pos, down, LayerActivation.Hold)
                translator.reachLayer(up, pos, LayerActivation.Hidden)
                if (translator.oneShotOnUpLayer.none { it.down == down }) {
                    translator.oneShotOnUpLayer.add(OneShotOnUpLayer(down, up, key))
                }
                key
            }

            else -> translateSimpleKey(translator, def, pos)
        }
    }

private fun findLayerActivationKey(def: String, translator: QmkTranslator, pos: KeyPosition): Key? {
    return LayerActivation.entries
        .firstOrNull { def.length > 1 && def[1] != ' ' && it.prefix != null && def.startsWith(it.prefix) }
        ?.let { activation -> layerKey(translator, pos, def.substring(1), activation) }
}

fun spaceSeparatedHint(def: String, translator: QmkTranslator, pos: KeyPosition): Key {
    val parts = def.split(" ")
    val right = parts[1].trim()
    val left = parts[0].trim()
    return when {
        parts.size == 2 && right[0].isDigit() -> translateKey(translator, pos, left).copy(comboTimeout = right.toInt())
        else -> throw IllegalArgumentException("unknown command '$def' in $pos")
    }
}

private fun layerTapHoldKey(def: String, translator: QmkTranslator, pos: KeyPosition): Key {
    val parts = def.split("+")
    val key = addCustomIfNotSimpleKey(translateKey(translator, pos, parts[0]).key, pos, translator)
    if (key in translator.noHoldKeys) {
        throw IllegalArgumentException("key $key not allowed for tap hold at $pos")
    }
    val command = QmkKey("LT(${translator.reachLayer(parts[1], pos, LayerActivation.TapHold).const()},$key)")
    translator.layerTapHold.add(command)
    return setCustomKeyCommand(translator, key, command, pos)
}

fun layerKey(
    translator: QmkTranslator,
    pos: KeyPosition,
    layer: String,
    activation: LayerActivation,
): Key {
    return when {
        activation == LayerActivation.Toggle -> layerOnKey(translator, pos, layer)
        activation.method != null -> Key(
            QmkKey(
                "${activation.method}(${
                    translator.reachLayer(layer, pos, activation).const()
                })"
            ),
            pos
        )

        else -> throw IllegalArgumentException("unsupported layer activation $activation")
    }
}

fun layerOnKey(translator: QmkTranslator, pos: KeyPosition, layer: String): Key {
    translator.layerOptions.getValue(layer).toggleOn = true
    return toggleKey(translator, layer, pos)
}

fun layerOffKey(translator: QmkTranslator, pos: KeyPosition, layer: String): Key {
    translator.layerOptions.getValue(layer).toggleOff = true
    return toggleKey(translator, baseLayerName, pos)
}

fun toggleKey(translator: QmkTranslator, layer: String, pos: KeyPosition): Key {
    return Key(QmkKey("TO(${translator.reachLayer(layer, pos, LayerActivation.Toggle).const()})"), pos)
}

fun keyWithModifier(def: String, translator: QmkTranslator, pos: KeyPosition): Key {
    val parts = def.split("-")
    val modifier = parts[0].toCharArray().map { Modifier.ofShort(it.toString()) }.toTypedArray()
    val target = parts[1]
    val key = translateKey(translator, pos, target, false)
    return if (key.keyWithModifier.key.contains("(")) {
        Key(tapCustomKey(translator, addMods(key.key, *modifier), pos), pos)
    } else {
        Key(addMods(key.key, *modifier), pos)
    }
}

fun addMods(key: QmkKey, vararg modifier: Modifier): QmkKey =
    QmkKey(
        if (modifier.size == 1) "${modifier[0].short}($key)" else
            when (modifier.toSet()) {
                setOf(Modifier.Alt, Modifier.Ctrl) -> "LCA(${key})"
                setOf(Modifier.Shift, Modifier.Ctrl) -> "RCS(${key})"
                else -> throw IllegalStateException("unknown modifier '$modifier'")
            }
    )

fun translateSimpleKey(translator: QmkTranslator, def: String, pos: KeyPosition): Key {
    val key = translator.toQmk(def, pos)
    return Key(key, pos, addModTab(key, pos, translator))
}

fun translateTable(
    tables: MultiTable,
    translator: QmkTranslator,
    layerName: LayerName,
): List<Rows> = tables.mapIndexed { tableIndex, table ->
    table.mapIndexed { rowNumber, row ->
        row.mapIndexed { column, def ->
            translateKey(
                translator, KeyPosition(
                    tableIndex, rowNumber, column, layerName, translator.options.nonThumbColumns
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
    if (srcLayerOption != null && (key.contains("*") || key.contains("@"))) {
        return qmkNo
    }
    if (key.isNotBlank()) {
        val k = key.substringBeforeLast("+").substringBefore(" ")
        if (recordUsage) {
            translator.gotKey(key, pos)
        }
        if (srcLayerOption != null) {
            if (srcLayerOption.flags.contains(LayerFlag.Shifted)) {
                return shifted(translateKey(translator, pos, k, false).key).key
            }
            return k
        }
        return key
    }
    val option = (translator.layerOptions[pos.layerName] ?: throw IllegalStateException("can't find layer at $pos"))
    val fallbackLayer = fallbackLayer(pos, option)

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

fun fallbackLayer(pos: KeyPosition, option: LayerOption): LayerName? {
    val left = pos.column < pos.columns / 2
    return if (left) option.leftFallbackLayer else option.rightFallbackLayer
}
