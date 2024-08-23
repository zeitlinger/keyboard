fun qmkTranslator(tables: Tables): QmkTranslator {
    val implicitKeys = mutableListOf<QmkKey>()
    val noHoldKeys = mutableListOf<QmkKey>()
    val symbols = readSymbols(tables, implicitKeys, noHoldKeys)
    val nonThumbs = getKeyTable(tables.getMulti("Layer").content)
    val columns = nonThumbs.values.first()[0][0].size
    val options = options(tables, nonThumbs, columns)

    val layerOptions = layerOption(tables)

    val layerNumbers = layerOptions
        .asIterable().mapIndexed { index, entry -> entry.key to index }.toMap()
    return QmkTranslator(
        symbols,
        layerOptions,
        nonThumbs,
        layerNumbers,
        options,
        mutableListOf(),
        mutableListOf(),
        implicitKeys,
        mutableListOf(),
        mutableMapOf(),
        noHoldKeys,
        mutableMapOf(),
        mutableMapOf(),
        mutableListOf(),
    )
}


private fun getKeyTable(layerContent: MultiTable): Map<LayerName, MultiTable> = layerContent
    .groupBy { it[0][0] }
    .mapValues { it.value.map { it.map { it.drop(1) } } } // First column
    .toMap()

private fun readSymbols(tables: Tables, implicitKeys: MutableList<QmkKey>, noHoldKeys: MutableList<QmkKey>): Symbols {
    val customKeycodes = mutableMapOf<String, CustomKey>()

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
                val qmkKey = QmkKey(custom)
                if (props["NoHold"] != null) {
                    noHoldKeys += qmkKey
                }
                customKeycodes[custom] = CustomKey(qmkKey, props["LayerHint"], null)
                listOf(key to custom)
            }

            value == "<implicit>" -> {
                implicitKeys += QmkKey(key)
                emptyList()
            }

            else -> {
                listOf(key to value)
            }
        }
    }.toMap()
    return Symbols(
        symTable,
        customKeycodes,
    )
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
                "DirectCombo" -> setOf(LayerFlag.DirectCombo)
                "" -> emptySet()
                else -> throw IllegalStateException("unknown flag ${it.value[5]}")
            },
            it.value[6].takeUnless { it.isBlank() }?.toInt(),
            mutableMapOf(),
        )
    }

private fun options(
    tables: Tables,
    keys: Map<LayerName, MultiTable>,
    columns: Int,
): Options {
    val first = keys.entries.first().value[0]

    val homeRowPositions = tables.getOptional("Home Row Modifiers")
        ?.associate {
            fingerPos(
                it[1],
                columns
            ) - first[0].size / 2 to Modifier.ofLong(it[0])
        } // we ignore the first row
    return Options(
        first.size,
        first[0].size,
        homeRowPositions
    )
}
