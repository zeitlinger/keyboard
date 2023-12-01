const val keyboardRows = 3
const val thumbRows = 1

data class KeyPosition(
    val row: Int,
    val column: Int,
    val layerName: String
)

fun readLayers(
    layerContent: Table,
    thumbs: Map<String, List<List<String>>>,
    translator: QmkTranslator,
    options: Map<String, LayerOption>
): List<Layer> {
    val layerByName = layerContent.drop(1) // Header
        .groupBy { it[0] }
        .toMap()
    var layerNumber = -1
    return layerByName.entries.map { (layerName, content) ->
        val data = translateTable(content, translator, layerName)
        val base = data.take(keyboardRows)
        val option = options.getValue(layerName)

        val combos = data.drop(keyboardRows).chunked(keyboardRows)

        val thumbData = translateTable(
            thumbs[layerName] ?: listOf(List(5) { "" }),
            translator,
            layerName
        )
//        val baseThumb = listOf(thumbData.getOrElse(0) { _ -> listOf(" ").repeat(4) })
        val baseThumb = listOf(thumbData[0])
        val comboThumb = thumbData.drop(thumbRows).chunked(thumbRows)

        if (!option.flags.contains(LayerFlag.Hidden)) {
            layerNumber++
        }

        Layer(
            layerName,
            (base + baseThumb),
            combos + comboThumb,
            layerNumber,
            translator.comboLayerTrigger[layerName],
            option
        )
    }
}

private fun translateCommand(
    translator: QmkTranslator,
    pos: KeyPosition,
    def: String,
): Key =
    //comes first, so that we can override the meaning of + and -
    when {
    translator.symbols.mapping.containsKey(def) -> translateSimpleKey(translator, def, pos)

    def.contains(" ") && !def.startsWith("\"") -> {
        val parts = def.split(" ")
        when {
            def.startsWith("ComboLayer:") -> {
                val trigger = parts[0].split(":")[1]
                val key = translateCommand(translator, pos, parts[1])
                translator.comboLayerTrigger[trigger] = key
                key
            }

            def.startsWith("HomeRowMods:") -> {
                val targetLayer = parts[0].split(":")[1]
                val key = translateCommand(translator, pos, parts[1])
                translator.homeRowCombo = HomeRowCombo(targetLayer, key)
                key
            }

            parts.size == 2 && parts[1].startsWith("c") -> {
                val key = translateCommand(translator, pos, parts[0])
                val timeout = parts[1].drop(1).toInt()
                //todo
//                translator.comboTimeout[key] = timeout
                key
            }

            else -> throw IllegalArgumentException("unknown command '$pos'")
        }
    }

    def.contains("+") && def.length > 1 -> {
        val parts = def.split("+")
        val key = translateCommand(translator, pos, parts[0]).key
        Key("LT(${translator.mustTranslateLayer(parts[1])},$key)")
    }

    def.contains("-") && def.length > 1 -> {
        val parts = def.split("-")
        val modifier = parts[0]
        val key = translateCommand(translator, pos, parts[1]).key
        Key(
            when (modifier) {
                "A" -> "LALT(${key})"
                "C" -> "LCTL(${key})"
                "S" -> "LSFT(${key})"
                "CS" -> "RCS(${key})"
                else -> throw IllegalStateException("unknown modifier $modifier")
            }
        )
    }

    def.isNotBlank() && def[0].isUpperCase() -> {
        Key("MO(${translator.mustTranslateLayer(def)})")
    }

    else -> translateSimpleKey(translator, def, pos)
}

private fun translateSimpleKey(translator: QmkTranslator, def: String, pos: KeyPosition): Key {
    val key = translator.toQmk(def)
    return Key(key, addModTab(key, pos, translator.options.getValue(pos.layerName)))
}

private fun translateTable(
    content: List<List<String>>,
    translator: QmkTranslator,
    layerName: String
): Rows = content.map { it.drop(1) }
    .mapIndexed { rowNumber, row ->
        row
            .mapIndexed { column, def -> translateCommand(translator, KeyPosition(rowNumber, column, layerName), def) }
    }
