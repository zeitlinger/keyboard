fun qmkTranslator(tables: Tables): QmkTranslator {
    val symbols = readSymbols(tables)
    val nonThumbs = getKeyTable(tables.getMulti("Layer").content)
    val thumbs = getKeyTable(tables.getMulti("Thumb").content)
    val columns = nonThumbs.values.first()[0][0].size
    val options = options(tables, nonThumbs, thumbs, columns)

    val layerOptions = layerOption(tables)

    val layerNumbers = layerOptions
        .asIterable().mapIndexed { index, entry -> entry.key to index }.toMap()
    return QmkTranslator(
        symbols,
        layerOptions,
        nonThumbs,
        thumbs,
        layerNumbers,
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
    val noHoldKeys = mutableListOf<String>()
    val symTable = tables.getMappingTable("Symbol").flatMap { entry ->
        val key = entry.key
        val value = entry.value
        val props: Map<String, String?> =
            value.split(" ").associate { e ->
                e.split(":").let { it[0] to it.getOrElse(1) { "true" } }
            }
        val custom = props["custom"]
        when {
            custom != null -> {
                if (props["NoHold"] != null) {
                    noHoldKeys += custom
                }
                customKeycodes[custom] = CustomKey(custom, props["LayerHint"], null)
                listOf(key to custom)
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
    return Symbols(symTable, customKeycodes, implicitKeys, mutableListOf(), mutableMapOf(), noHoldKeys, mutableMapOf())
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
        ?.associate {
            fingerPos(
                it[1],
                columns
            ) - firstNonThumb[0].size / 2 to Modifier.ofLong(it[0])
        } // we ignore the first row
    val firstThumb = thumbs.entries.first().value[0]
    return Options(
        firstNonThumb.size,
        firstNonThumb[0].size,
        firstThumb[0].size,
        homeRowPositions
    )
}
