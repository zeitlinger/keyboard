import kotlin.streams.toList

fun qmkTranslator(tables: Tables): QmkTranslator {
    val implicitKeys = mutableListOf<QmkKey>()
    val noHoldKeys = mutableListOf<QmkKey>()
    val magics = mutableListOf<MagicInfo>()
    val symbols = readSymbols(tables, implicitKeys, noHoldKeys, magics)
    val nonThumbs = getKeyTable(tables.getMulti("Layer").content)
    val columns = nonThumbs.values.first()[0][0].size
    val options = options(tables, nonThumbs, columns)

    val layerOptions = layerOption(tables)

    val layerNumbers =
        layerOptions
            .asIterable()
            .mapIndexed { index, entry -> entry.key to index }
            .toMap()
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
        magics,
        mutableMapOf(),
        mutableListOf(),
    )
}

private fun getKeyTable(layerContent: MultiTable): Map<LayerName, MultiTable> =
    layerContent
        .groupBy { it[0][0] }
        .mapValues { it.value.map { it.map { it.drop(1) } } } // First column
        .toMap()

@OptIn(ExperimentalStdlibApi::class)
private fun readSymbols(
    tables: Tables,
    implicitKeys: MutableList<QmkKey>,
    noHoldKeys: MutableList<QmkKey>,
    magics: MutableList<MagicInfo>,
): Symbols {
    val customKeycodes = mutableMapOf<String, CustomKey>()

    val symTable =
        tables
            .getMappingTable("Symbol")
            .flatMap { entry ->
                val key = entry.key
                val value = entry.value
                val props: Map<String, String?> =
                    value.split(" ").associate { e ->
                        e.split(":").let { it[0] to it.getOrElse(1) { "true" } }
                    }
                val custom = props["custom"]
                val unicode = props["unicode"]
                val magic =
                    if (value.startsWith(
                            "magic:",
                        )
                    ) {
                        value.substringAfter("magic:").split(":", limit = 2)
                    } else {
                        null
                    }
                when {
                    unicode != null -> {
                        val codepoint =
                            key
                                .codePoints()
                                .toList()
                                .single()
                                .toHexString(HexFormat.UpperCase)
                                .trimStart('0')
                                .padStart(4, '0')
                        val name = "U$codepoint"
                        customKeycodes[name] =
                            CustomKey(
                                QmkKey.of(name),
                                null,
                                CustomCommand(
                                    CustomCommandType.OnPress,
                                    listOf("register_unicode(0x$codepoint)"),
                                ),
                                null,
                            )
                        listOf(key to name)
                    }

                    magic != null -> {
                        val keycode = magic[0]
                        val default = magic.getOrNull(1)
                        val qmkKey = QmkKey.of(keycode)
                        customKeycodes[keycode] = CustomKey(qmkKey, null, null, null)
                        magics += MagicInfo(keycode, default)
                        listOf(key to keycode)
                    }

                    custom != null -> {
                        val qmkKey = QmkKey.of(custom)
                        if (props["NoHold"] != null) {
                            noHoldKeys += qmkKey
                        }
                        customKeycodes[custom] = CustomKey(qmkKey, props["LayerHint"], null, null)
                        listOf(key to custom)
                    }

                    value == "<implicit>" -> {
                        implicitKeys += QmkKey.of(key)
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
        mutableSetOf(),
    )
}

private fun layerOption(tables: Tables): Map<LayerName, LayerOption> =
    tables
        .getSingle("LayerOptions")
        .associateBy { it[0] }
        .mapValues {
            LayerOption(
                modifierTypes(it.value[1]),
                modifierTypes(it.value[2]),
                it.value[3].ifBlank { null },
                it.value[4].ifBlank { null },
                it.value[5]
                    .split(",")
                    .filter { it.isNotBlank() }
                    .map { LayerFlag.valueOf(it) }
                    .toSet(),
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

    val homeRowPositions =
        tables
            .getOptional("Home Row Modifiers")
            ?.associate {
                fingerPos(
                    it[1],
                    columns,
                ) - first[0].size / 2 to Modifier.ofLong(it[0])
            } // we ignore the first row
    return Options(
        first.size,
        first[0].size,
        homeRowPositions,
    )
}
