import java.io.File

data class Layer(val name: String, val activationKeys: List<String>, val output: List<String>)

data class Thumb(val inputKey: String, val tab: String, val hold: String)

data class Symbols(val mapping: Map<String, String>) {
    fun replace(key: String): String = mapping.getOrDefault(key, key).let { it.ifBlank { "XX" } }
}


fun main(args: Array<String>) {
    val config = "/home/gregor/source/keyboard/keyboard14.md" //todo
//    val config = args.getOrNull(0) ?: throw IllegalArgumentException("config file must be the first argument")
//    val output = args.getOrNull(1) ?: throw IllegalArgumentException("output file must be the second argument")
//    val device = args.getOrNull(2) ?: throw IllegalArgumentException("device must be the third argument")

    val tables = readTables(config)

    val symbols = Symbols(tables.single { it[0][0] == "Symbol" }.drop(1).associate { it[0] to it[1] })
    val layerTable = tables.single { it[0][0] == "Layer" }
    val layers = readLayers(layerTable, symbols)
    val thumbs = readThumbs(tables.single { it[0][0] == "Thumb Pos" }, symbols)

    val options = tables.single { it[0][0] == "Option" }.drop(1).associate { it[0] to it[1] }

    val homePos = getInputKeys(layerTable[0].drop(2)).joinToString(" ")
    val thumbPos = thumbs.joinToString(" ") { it.inputKey }

    println("(defsrc\n$homePos\n$thumbPos\n${options["Exit Layout"]}\n)")

    for (layer in layers) {
        val mapping = layer.output.joinToString(" ")
        println("(deflayer ${layer.name}\n$mapping\n)\n")
    }
}

fun readLayers(table: List<List<String>>, symbols: Symbols): List<Layer> {
    return table
        .drop(1) // header
        .map { layerLine ->
            val name = layerLine[0]
            val keys = layerLine[1].toCharArray().map { it.toString() }
            val mapping = layerLine
                .drop(2)
                .map { symbols.replace(it.substringBefore(" ")) } // part after space is only for illustration
            Layer(name, keys, mapping)
        }
}

fun readThumbs(table: List<List<String>>, symbols: Symbols): List<Thumb> {
    val lines = table.map { it.drop(1) } // discard the row header

    val inputKeys = getInputKeys(lines[0])

    return inputKeys.mapIndexed { index, inputKey ->
        Thumb(
            inputKey,
            symbols.replace(lines[1][index]),
            symbols.replace(lines[2][index]),
        )
    }
}

fun getInputKeys(list: List<String>): List<String> = list
    .map { it.substringAfter("(").substringBefore(")") }

fun readTables(config: String): List<List<List<String>>> = File(config)
    .readText()
    .split("\n\\s*\n".toRegex())
    .filter { it.startsWith("|") }
    .map { tableLines ->
        val entries = tableLines
            .split("\n")
            .filterIndexed { index, line ->
                index != 1               // below header
                    && line.isNotBlank() // last block can contain empty line at end
            }
        entries
            .map { tableLine ->
                tableLine
                    .split("|")
                    .drop(1) // initial |
                    .dropLast(1) // last |
                    .map { it.trim() }
            }
    }
