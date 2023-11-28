
const val keyboardRows = 3
const val thumbRows = 1

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
        val data = translateTable(content, translator)
        val base = data.take(keyboardRows)
        val option = options.getValue(layerName)
        val baseWithMods = base
            .mapIndexed { row, def ->
                addModTab(row, def, option)
            }


        val combos = data.drop(keyboardRows).chunked(keyboardRows)

        val thumbData = translateTable(
            thumbs[layerName] ?: listOf(List(5) { " " }),
            translator
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
            (baseWithMods + baseThumb),
            combos + comboThumb,
            layerNumber,
            translator.comboLayerTrigger[layerName],
            option
        )
    }
}

private fun translateCommand(
    command: String,
    translator: QmkTranslator
): String = when {
    translator.symbols.mapping.containsKey(command) -> {
        command // is translated later
    }

    command.startsWith("ComboLayer:") -> {
        val parts = command.split(" ")
        val trigger = parts[0].split(":")[1]
        val key = translateCommand(parts[1], translator)
        translator.comboLayerTrigger[trigger] = key
        key
    }

    command.startsWith("HomeRowMods:") -> {
        val parts = command.split(" ")
        val targetLayer = parts[0].split(":")[1]
        val key = translateCommand(parts[1], translator)
        translator.homeRowCombo = HomeRowCombo(targetLayer, key)
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
    translator: QmkTranslator
) = content.map { it.drop(1) }
    .map { row ->
        row
            .map { translateCommand(it, translator) }
            .map { translator.toQmk(it) }
    }
