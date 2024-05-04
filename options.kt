fun qmkTranslator(args: GeneratorArgs): QmkTranslator {
    val tables = readTables(args.configFile.file)
    val symbols = readSymbols(tables)
    val nonThumbs = getKeyTable(tables.getMulti("Layer").content)
    val thumbs = getKeyTable(tables.getMulti("Thumb").content)
    val columns = nonThumbs.values.first()[0][0].size
    val options = options(tables, nonThumbs, thumbs, columns)

    val layerOptions = layerOption(tables)

    val layerNumbers = layerOptions
        .filterNot { it.value.flags.contains(LayerFlag.Hidden) }
        .asIterable().mapIndexed { index, entry -> entry.key to index }.toMap()
    return QmkTranslator(
        symbols,
        layerOptions,
        nonThumbs,
        thumbs,
        layerNumbers,
        mutableMapOf(),
        null,
        options,
        mutableMapOf(),
        mutableListOf(),
        mutableListOf()
    )
}


private fun getKeyTable(layerContent: MultiTable): Map<LayerName, MultiTable> = layerContent
    .groupBy { it[0][0] }
    .mapValues { it.value.map { it.map { it.drop(1) } } } // First column
    .toMap()

private fun readSymbols(tables: Tables): Symbols {
    val customKeycodes = mutableMapOf<String, CustomKey>()
    val implicitKeys = mutableListOf<String>()
    val symTable = tables.getMappingTable("Symbol").flatMap { entry ->
        val key = entry.key
        val value = entry.value
        val matchResult = """custom:([A-Z_]+)( +LayerHint:(.+))?$""".toRegex().find(value)
        when {
            matchResult != null -> {
                val command = matchResult.groupValues[1]
                customKeycodes[command] =
                    CustomKey(command, matchResult.groupValues[3].takeIf { it.isNotBlank() }, null)
                listOf(key to command)
            }

            value == "<implicit>" -> {
                implicitKeys += key
                emptyList()
            }

            else -> {
                listOf(key to value)
            }
        }
    }.toMap()
    return Symbols(symTable, customKeycodes, implicitKeys, mutableListOf())
}


private fun layerOption(tables: Tables): Map<LayerName, LayerOption> = tables.getSingle("LayerOptions")
    .associateBy { it[0] }
    .mapValues {
        LayerOption(
            modifierTypes(it.value[1]),
            modifierTypes(it.value[2]),
            it.value[3].ifBlank { null },
            it.value[4].ifBlank { null },
            when (it.value[5]) {
                "Shifted" -> setOf(LayerFlag.Shifted)
                "Hidden" -> setOf(LayerFlag.Hidden)
                "OSL to toggle" -> setOf(LayerFlag.OslToToggle)
                "OneShot" -> setOf(LayerFlag.OneShot)
                "No OneShot" -> setOf(LayerFlag.NoOneShot)
                "" -> emptySet()
                else -> throw IllegalStateException("unknown flag ${it.value[5]}")
            },
            emptySet(),
        )
    }

private fun options(
    tables: Tables,
    nonThumbs: Map<LayerName, MultiTable>,
    thumbs: Map<LayerName, MultiTable>,
    columns: Int,
): Options {
    val firstNonThumb = nonThumbs.entries.first().value[0]

    val homeRowPositions = tables.getOptional("Home Row Modifiers")
        ?.associate { fingerPos(it[1], columns) - firstNonThumb[0].size / 2 to Modifier.ofLong(it[0]) } // we ignore the first row
    val firstThumb = thumbs.entries.first().value[0]
    return Options(
        firstNonThumb.size,
        firstNonThumb[0].size,
        firstThumb[0].size,
        tables.getOptional("Base Layer One Shot Mod Combos")
            ?.let { createModTriggers(it, homeRowOneShotTriggers, columns) },
        homeRowPositions?.let { h -> tables.getOptional("Base Layer Thumb Mod Combos")
            ?.let { createThumbModTriggers(it, homeRowThumbTriggers, h) }},
        homeRowPositions
    )
}
