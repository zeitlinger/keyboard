const val keyboardRows = 3
const val thumbRows = 1

data class KeyPosition(
        val row: Int,
        val column: Int,
        val layerName: String,
        val thumb: Boolean,
        val columns: Int,
)

fun readLayer(
        content: List<List<String>>,
        translator: QmkTranslator,
        layerName: String,
        layerIndex: Int
): Layer {
    val data = translateTable(content, translator, layerName, false)
    val base = data.take(keyboardRows)
    val option = translator.layerOption.getValue(layerName)

    val combos = data.drop(keyboardRows).chunked(keyboardRows)

    val thumbData = translateTable(
            translator.getThumbContent(layerName),
            translator,
            layerName,
            true,
    )
    val baseThumb = listOf(thumbData[0])
    val comboThumb = thumbData.drop(thumbRows).chunked(thumbRows)

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
            when {
                def.startsWith("ComboLayer:") -> {
                    val trigger = parts[0].split(":")[1]
                    val key = translateKey(translator, pos, parts[1])
                    translator.comboLayerTrigger[trigger] = key
                    key
                }

                def.startsWith("HomeRowThumbCombo:") -> {
                    val targetLayer = parts[0].split(":")[1]
                    val key = translateKey(translator, pos, parts[1])
                    translator.homeRowThumbCombo = HomeRowCombo(targetLayer, key)
                    key
                }

                parts.size == 2 && parts[1][0].isDigit() -> {
                    translateKey(translator, pos, parts[0])
                            .copy(comboTimeout = parts[1].toInt())
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
                        else -> throw IllegalStateException("unknown modifier $modifier")
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
    val key = translator.toQmk(def)
    return Key(key, addModTab(key, pos, translator))
}

private fun translateTable(
        content: List<List<String>>,
        translator: QmkTranslator,
        layerName: String,
        thumb: Boolean,
): Rows = content.mapIndexed { rowNumber, row ->
    row.mapIndexed { column, def ->
        translateKey(translator, KeyPosition(rowNumber, column, layerName, thumb,
                if (thumb) translator.options.thumbColumns else translator.options.nonThumbColumns), def)
    }
}

