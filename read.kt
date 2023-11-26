fun readLayers(
    layerContent: Table,
    thumbs: Map<String, List<List<String>>>,
    translator: QmkTranslator,
    options: Map<String, Option>
): List<Layer> {
    val comboLayerTrigger = mutableMapOf<Int, String>()
    val layerByName = layerContent.drop(1) // Header
        .groupBy { it[0] }
        .toMap()
    return layerByName.entries.mapIndexed { layerNumber, (layerName, content) ->
        val data = translateTable(content, translator, comboLayerTrigger)
        val base = data.take(keyboardRows)
            .mapIndexed { row, def ->
                addModTab(row, def, options.getValue(layerName))
            }


        val combos = data.drop(keyboardRows).chunked(keyboardRows)

        val thumbData = translateTable(thumbs[layerName] ?: listOf(List(5) { " " }), translator, comboLayerTrigger)
//        val baseThumb = listOf(thumbData.getOrElse(0) { _ -> listOf(" ").repeat(4) })
        val baseThumb = listOf(thumbData[0])
        val comboThumb = thumbData.drop(thumbRows).chunked(thumbRows)

        val baseRows = (base + baseThumb)
        Layer(
            layerName, baseRows,
            combos + comboThumb,
            layerNumber,
            comboLayerTrigger[layerNumber]
        )
    }
}

private fun translateCommand(
    command: String,
    comboLayerTrigger: MutableMap<Int, String>,
    translator: QmkTranslator
): String = when {
    translator.symbols.mapping.containsKey(command) -> {
        command // is translated later
    }

    command.startsWith("ComboLayer:") -> {
        val parts = command.split(" ")
        val trigger = translator.mustTranslateLayer(parts[0].split(":")[1])
        val key = translateCommand(parts[1], comboLayerTrigger, translator)
        comboLayerTrigger[trigger] = key
        key
    }

    command.contains("+") && command.length > 1 -> {
        val parts = command.split("+")
        "LT(${translator.mustTranslateLayer(parts[1])},${translator.toQmk(parts[0])})"
    }

    command.contains("-") && command.length > 1 -> {
        val parts = command.split("-")
        val modifier = parts[0]
        val key = translator.toQmk(parts[1])
        when (modifier) {
            "A" -> "LALT(${key})"
            "C" -> "LCTL(${key})"
            "S" -> "LSFT(${key})"
            "CS" -> "RCS(${key})"
            else -> throw IllegalStateException("unknown modifier $modifier")
        }
    }

    command.isNotBlank() && command[0].isUpperCase() -> {
        "MO(${translator.mustTranslateLayer(command)})"
    }

    else -> {
        command
    }
}

private fun translateTable(
    content: List<List<String>>,
    translator: QmkTranslator,
    comboLayerTrigger: MutableMap<Int, String>
) = content.map { it.drop(1) }
    .map { row ->
        row
            .map { translateCommand(it, comboLayerTrigger, translator) }
            .map { translator.toQmk(it) }
    }
