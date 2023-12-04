const val thumbRows = 1

data class KeyPosition(
        val row: Int,
        val column: Int,
        val layerName: String,
        val thumb: Boolean,
        val columns: Int,
)

fun readLayer(
        content: MultiTable,
        translator: QmkTranslator,
        layerName: String,
        layerIndex: Int
): Layer {
    val data = translateTable(content, translator, layerName, false)
    val base = data[0]
    val option = translator.layerOption.getValue(layerName)

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

        def.contains(" ") && !def.startsWith("\"") -> {
            val parts = def.split(" ")
            val right = parts[1]
            val left = parts[0]
            when {
                def.startsWith("ComboLayer:") -> {
                    val trigger = left.split(":")[1]        .split(",")
                    val layerName = trigger[0]
                    val timeout = trigger.getOrNull(1)?.toIntOrNull()
                    translator.layerOption[layerName]?.let {
                        val key = translateKey(translator, pos, right)
                        translator.comboLayerTrigger[layerName] = key.copy(comboTimeout = timeout)
                        key
                    } ?: throw IllegalArgumentException("unknown layer $layerName in $pos")
                }

                def.startsWith("HomeRowThumbCombo:") -> {
                    val targetLayer = left.split(":")[1]
                    val key = translateKey(translator, pos, right)
                    translator.homeRowThumbCombo = HomeRowCombo(targetLayer, key)
                    key
                }

                parts.size == 2 && right[0].isDigit() -> {
                    translateKey(translator, pos, left)
                            .copy(comboTimeout = right.toInt())
                }

                else -> throw IllegalArgumentException("unknown command '$def' in $pos")
            }
        }

        def.contains("+") && def.length > 1 -> {
            val parts = def.split("+")
            val key = translateKey(translator, pos, parts[0]).key
            Key("LT(${translator.mustTranslateLayer(parts[1])},$key)")
        }

        def.contains("-") && def.length > 1 -> {
            val parts = def.split("-")
            val modifier = parts[0]
            val key = translateKey(translator, pos, parts[1]).key
            Key(
                    when (modifier) {
                        "A" -> "A(${key})"
                        "C" -> "C(${key})"
                        "S" -> "S(${key})"
                        "CS" -> "RCS(${key})"
                        else -> throw IllegalStateException("unknown modifier '$modifier'")
                    }
            )
        }

        def.isNotBlank() && def[0].isUpperCase() && !def.contains("_") -> { //skip QMK keycodes
            Key("MO(${translator.mustTranslateLayer(def)})")
        }

        else -> translateSimpleKey(translator, def, pos)
    }
}

private fun translateSimpleKey(translator: QmkTranslator, def: String, pos: KeyPosition): Key {
    val key = translator.toQmk(def, pos)
    return Key(key, addModTab(key, pos, translator))
}

private fun translateTable(
        tables: MultiTable,
        translator: QmkTranslator,
        layerName: String,
        thumb: Boolean,
): List<Rows> = tables.map { table ->
    table.mapIndexed { rowNumber, row ->
        row.mapIndexed { column, def ->
            translateKey(translator, KeyPosition(rowNumber, column, layerName, thumb,
                    if (thumb) translator.options.thumbColumns else translator.options.nonThumbColumns), def)
        }
    }
}

