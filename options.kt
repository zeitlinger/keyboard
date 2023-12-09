fun qmkTranslator(args: GeneratorArgs): QmkTranslator {
    val tables = readTables(args.config)
    val symbols = readSymbols(tables)
    val nonThumbs = getKeyTable(tables.getMulti("Layer").content)
    val thumbs = getKeyTable(tables.getMulti("Thumb").content)
    val options = options(tables, nonThumbs, thumbs)

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
        mutableMapOf()
    )
}


private fun getKeyTable(layerContent: MultiTable): Map<LayerName, MultiTable> = layerContent
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


private fun layerOption(tables: Tables): Map<LayerName, LayerOption> {
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
    return layerOptions
}

private fun options(
    tables: Tables,
    nonThumbs: Map<LayerName, MultiTable>,
    thumbs: Map<LayerName, MultiTable>
): Options {
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