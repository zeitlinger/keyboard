import java.io.File

const val mainLayerTemplate =
    "\t[%d] = LAYOUT_split_3x5_2(\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "                            %s, %s, %s, %s),"

fun generateBase(layers: List<Layer>, options: Map<String, LayerOption>): String {
    val fallback = layers.associateBy { it.name }.mapValues { it.value.baseRows }

    return layers
        .filter { !it.option.flags.contains(LayerFlag.Hidden) }
        .joinToString("\n") { layer ->
            val qmk = layer.baseRows
                .mapIndexed { rowIndex, row ->
                    row.mapIndexed { columnIndex, key ->
                        val left = columnIndex < row.size / 2
                        getFallback(key, layer.name, fallback, options, rowIndex, columnIndex, left).keyWithModifier
                    }
                }.flatten()

            mainLayerTemplate.format(*listOf(layer.number).plus<Any>(qmk).toTypedArray())
        }
}

private fun getFallback(
    key: Key,
    layer: String,
    fallback: Map<String, Rows>,
    options: Map<String, LayerOption>,
    rowIndex: Int,
    columnIndex: Int,
    left: Boolean
): Key {
    val option = options.getValue(layer)
    if (!key.isBlocked()) {
        return key
    }
    val fallbackLayer = if (left) option.leftFallbackLayer else option.rightFallbackLayer
    return when {
        fallbackLayer == null || layer == baseLayerName -> Key(qmkNo)
        else -> getFallback(
            fallback.getValue(fallbackLayer)[rowIndex][columnIndex],
            fallbackLayer,
            fallback,
            options,
            rowIndex,
            columnIndex,
            left
        )
    }
}

fun run(config: File, comboFile: File, layoutFile: File, layoutTemplate: File, features: Set<Feature>) {
    val tables = readTables(config)

    val symbols = readSymbols(tables)
    val thumbs = tables.get("Thumb").drop(1) // Header
        .groupBy { it[0] }
        .toMap()
    val layerContent = tables.get("Layer")
    val layerNames = layerContent.drop(1).map { it[0] }.toSet().mapIndexed { index, s -> s to index }.toMap()
    val options = tables.get("Options")
        .drop(1)
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

    val translator = QmkTranslator(symbols, layerNames, options)
    val layers = readLayers(layerContent, thumbs, translator, options)
    val layerNumbers = layers
        .filter { !it.option.flags.contains(LayerFlag.Hidden) }
        .joinToString("\n") { "#define _${it.name.uppercase()} ${it.number}" }

//    printMissingAndUnexpected(translator, layers, symbols)

    val combos = generateAllCombos(layers, features, translator.homeRowCombo).map { combo ->
        combo.type.template.format(
            combo.name.padEnd(35),
            combo.result.padEnd(35),
            combo.triggers.joinToString(", ") { it.keyWithModifier }
        )
    }.sorted()

    val generationNote =
        "file is generated from ${config.name} using https://github.com/zeitlinger/keyboard/blob/main/generateKeyboard.kt"

    val base = layoutTemplate.readText()
        .replace("\${generationNote}", generationNote)
        .replace("\${layers}", generateBase(layers, options))
        .replace("\${layerNumbers}", layerNumbers)
        .replace("\${custom0}", symbols.userKeycodes[0])
        .replace("\${customRest}", symbols.userKeycodes.drop(1).joinToString(",\n    "))

    layoutFile.writeText(base)

    comboFile.writeText((listOf("// $generationNote") + combos).joinToString("\n"))
}

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
