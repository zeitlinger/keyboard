import java.io.File

const val mainLayerTemplate =
        "\t[%d] = LAYOUT_split_3x5_2(\n" +
                "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
                "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
                "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
                "                            %s, %s, %s, %s),"

fun generateBase(layers: List<Layer>): String {
    return layers
            .filter { !it.option.flags.contains(LayerFlag.Hidden) }
            .sortedBy { it.number }
            .joinToString("\n") { layer ->
                mainLayerTemplate.format(*listOf(layer.number).plus(layer.baseRows.map { it.map { it.keyWithModifier } }
                        .flatten()).toTypedArray())
            }
}

fun getFallback(
        key: String,
        translator: QmkTranslator,
        pos: KeyPosition
): String {
    val option = translator.layerOption[pos.layerName]?:throw IllegalStateException("can't find layer at $pos")
    if (!(key.isBlank() || key == layerBlocked)) {
        return key
    }
    val left = pos.column < pos.columns / 2
    val fallbackLayer = if (left) option.leftFallbackLayer else option.rightFallbackLayer
    return when {
        fallbackLayer == null || pos.layerName == baseLayerName -> qmkNo
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

fun run(
        config: File,
        comboFile: File,
        layoutFile: File,
        layoutTemplate: File,
        timeoutFile: File,
        timerTemplate: File
) {
    val tables = readTables(config)

    val symbols = readSymbols(tables)
    val nonThumbs = getKeyTable(tables.getMulti("Layer").content)
    val thumbs = getKeyTable(tables.getMulti("Thumb").content)
    val options = options(tables, nonThumbs, thumbs)

    val layerOptions = tables.getSingle("LayerOptions")
            .associateBy { it[0] }
            .mapValues {
                LayerOption(
                        modifierTypes(it.value[1]),
                        modifierTypes(it.value[2]),
                        it.value[3].ifBlank { null },
                        it.value[4].ifBlank { null },
                        if (it.value[5] == "Hidden") setOf(LayerFlag.Hidden) else emptySet()
                )
            }

    val layerNumbers = layerOptions
            .filterNot { it.value.flags.contains(LayerFlag.Hidden) }
            .asIterable().mapIndexed { index, entry -> entry.key to index }.toMap()
    val translator = QmkTranslator(symbols, layerOptions, nonThumbs, thumbs, layerNumbers, mutableMapOf(), null, options)

    val layers = nonThumbs.entries.map { (layerName, content) ->
        readLayer(content, translator, layerName, layerNumbers.getOrDefault(layerName, -1))
    }

//    printMissingAndUnexpected(translator, layers, symbols)

    val combos = generateAllCombos(layers, options, translator.homeRowThumbCombo)
    val comboLines = combos.map { combo ->
        combo.type.template.format(
                combo.name.padEnd(35),
                combo.result.padEnd(35),
                combo.triggers.joinToString(", ") { it.keyWithModifier }
        )
    }.sorted()

    val timeouts = combos.filter { it.timeout != null }.map {
        "case ${it.name}: return ${it.timeout};"
    }.sorted()

    val generationNote =
            "file is generated from ${config.name} using https://github.com/zeitlinger/keyboard/blob/main/generateKeyboard.kt"

    replaceTemplate(
            layoutTemplate, layoutFile, mapOf(
            "generationNote" to generationNote,
            "layers" to generateBase(layers),
            "layerNumbers" to layerNumbers.entries
                    .joinToString("\n") { "#define _${it.key.uppercase()} ${it.value}" },
            "custom0" to symbols.userKeycodes[0],
            "customRest" to symbols.userKeycodes.drop(1).joinToString(",\n    ")
    )
    )

    replaceTemplate(
            timerTemplate, timeoutFile, mapOf(
            "generationNote" to generationNote,
            "timeouts" to timeouts.joinToString("\n    ")
    )
    )

    comboFile.writeText((listOf("// $generationNote") + comboLines).joinToString("\n"))
}

private fun options(tables: Tables, nonThumbs: Map<String, MultiTable>, thumbs: Map<String, MultiTable>): Options {
    val firstNonThumb = nonThumbs.entries.first().value[0]

    val homeRowPositions = tables.getSingle("Home Row Modifiers")
            .associate { fingerPos(it[1]) - firstNonThumb[0].size / 2 to Modifier.ofLong(it[0]) } // we ignore the first row
    val firstThumb = thumbs.entries.first().value[0]
    return Options(
            firstNonThumb.size,
            firstNonThumb[0].size,
            firstThumb[0].size,
            tables.getOptional("Base Layer One Shot Mod Combos")
                    ?.let { createModTriggers(it, homeRowOneShotTriggers) },
            tables.getOptional("Base Layer Thumb Mod Combos")
                    ?.let { createThumbModTriggers(it, homeRowThumbTriggers, homeRowPositions) },
            homeRowPositions
    )
}

private fun replaceTemplate(src: File, dst: File, vars: Map<String, String>) {
    dst.writeText(vars.entries.fold(src.readText()) { acc, entry ->
        acc.replace("\${${entry.key}}", entry.value)
    })
}

private fun getKeyTable(layerContent: MultiTable): Map<String, MultiTable> = layerContent
        .groupBy { it[0][0] }
        .mapValues { it.value.map { it.map { it.drop(1) } } } // First column
        .toMap()

private fun readSymbols(tables: Tables): Symbols {
    val userKeycodes = mutableListOf<String>()
    val symTable = tables.getMappingTable("Symbol").mapValues {
        val command = it.value
                """custom:([A-Z_]+)""".toRegex().find(command)?.let {
                    userKeycodes.add(it.groupValues[1])
                    command.replace("custom:", "")
                } ?: command
    }
    return Symbols(symTable, userKeycodes)
}
