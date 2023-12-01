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
    val option = translator.options.getValue(pos.layerName)
    if (!key.isBlocked()) {
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

fun run(config: File, comboFile: File, layoutFile: File, layoutTemplate: File, features: Set<Feature>) {
    val tables = readTables(config)

    val symbols = readSymbols(tables)
    val thumbs = getKeyTable(tables.get("Thumb"))
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

    val nonThumbs = getKeyTable(tables.get("Layer"))
    val layerNumbers = options
        .filterNot { it.value.flags.contains(LayerFlag.Hidden) }
        .asIterable().mapIndexed { index, entry -> entry.key to index }.toMap()
    val translator = QmkTranslator(symbols, options, nonThumbs, thumbs, layerNumbers, mutableMapOf(), null)

    val layers = nonThumbs.entries.map { (layerName, content) ->
        readLayer(content, translator, layerName, layerNumbers.getOrDefault(layerName, -1))
    }

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
        .replace("\${layers}", generateBase(layers))
        .replace("\${layerNumbers}", layerNumbers.entries
            .joinToString("\n") { "#define _${it.key.uppercase()} ${it.value}" })
        .replace("\${custom0}", symbols.userKeycodes[0])
        .replace("\${customRest}", symbols.userKeycodes.drop(1).joinToString(",\n    "))

    layoutFile.writeText(base)

    comboFile.writeText((listOf("// $generationNote") + combos).joinToString("\n"))
}

private fun getKeyTable(layerContent: Table): Map<String, List<List<String>>> = layerContent.drop(1) // Header
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
