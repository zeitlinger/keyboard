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
    val option = translator.layerOption.getValue(pos.layerName)
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
    val thumbs = getKeyTable(tables.getWithoutHeader("Thumb"))
    val homeRowPositions = tables.getWithoutHeader("Home Row Modifiers")
            .associate { fingerPos(it[1]) to Modifier.ofLong(it[0]) }
    val options = Options(
            createModTriggers(tables.getWithoutHeader("Base Layer One Shot Mod Combos"), homeRowOneShotTriggers),
            createThumbModTriggers(tables.getWithoutHeader("Base Layer Thumb Mod Combos"), homeRowThumbTriggers, homeRowPositions),
            homeRowPositions
    )

    val layerOptions = tables.getWithoutHeader("LayerOptions")
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

    val nonThumbs = getKeyTable(tables.getWithoutHeader("Layer"))
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

private fun replaceTemplate(src: File, dst: File, vars: Map<String, String>) {
    dst.writeText(vars.entries.fold(src.readText()) { acc, entry ->
        acc.replace("\${${entry.key}}", entry.value)
    })
}

private fun getKeyTable(layerContent: Table): Map<String, List<List<String>>> = layerContent
    .groupBy { it[0] }
    .mapValues { it.value.map { it.drop(1) } } // First column
    .toMap()

private fun readSymbols(tables: Tables): Symbols {
    val userKeycodes = mutableListOf<String>()
    val symTable = tables.getMappingTable("Symbol").mapValues {
        val command = it.value
        when {
            command.startsWith("custom:") -> {
                val key = command.split(":")[1]
                userKeycodes.add(key)
                key
            }

            else -> command
        }
    }
    return Symbols(symTable, userKeycodes)
}
