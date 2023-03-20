import java.io.File
import java.lang.IllegalStateException

//todo
//mouse accelerator
//uleo layer keys

typealias Table = List<List<String>>

data class Tables(val content: List<Table>) {

    fun get(name: String): Table = content.single { it[0][0] == name }

    fun getMappingTable(
        name: String,
    ): Map<String, String> = content.single { it[0][0] == name }.drop(1).associate { it[0] to it[1] }
}

data class Alias(val name: String, val command: String)

data class Layer(val name: String, val activationKeys: Set<String>, val output: List<String>) {
    val thumbHoldSuffix get() = activationKeys.sorted().joinToString("")
}

data class Thumb(val inputKey: String, val tap: String, val hold: String)

private const val BLOCKED = "XX"

data class Symbols(val mapping: Map<String, String>) {
    fun replace(key: String): String = mapping.getOrDefault(key, key).let { it.ifBlank { BLOCKED } }
}

data class Generator(val options: Map<String, String>, val thumbs: List<Thumb>, val layers: List<Layer>) {

    private fun statement(header: String, body: String): String = "($header\n$body\n)\n"

    private fun generate(
        header: String,
        homeRow: List<String>,
        thumbRow: List<String>,
    ): String {
        return statement(
            header, homeRow.joinToString(" ") +
                "\n${thumbRow.joinToString(" ")}" +
                "\n${options["Exit Layout"]}"
        )
    }

    fun defAlias(homeRowHold: List<String>, customAlias: Map<String, String>): String {
        val layerToggle = layers.map { Alias(it.name, "(layer-while-held ${it.name})") }
        val layerActivation =
            layers.flatMap { layer ->
                getLayerActivation(layer, layer.output, homeRowHold, layer.activationKeys, "") +
                    getLayerActivation(
                        layer,
                        thumbs.map { it.tap },
                        thumbs.map { it.hold },
                        emptySet(),
                        layer.thumbHoldSuffix
                    )
            }

        val body = mapOf(
            "layer aliases" to layerToggle,
            "custom alias" to customAlias.map { Alias(it.key, it.value) },
            "layer activation" to layerActivation,
        )
            .map { entry ->
                val section =
                    entry.value.joinToString("\n") { alias -> "  ${alias.name} ${alias.command}" }
                "  ;; ${entry.key}\n$section"
            }
            .joinToString("\n\n")

        return statement("defalias", body)
    }

    private fun getLayerActivation(
        current: Layer,
        keys: List<String>,
        hold: List<String>,
        excludeHold: Set<String>,
        layerSuffix: String,
    ): List<Alias> =
        keys.zip(hold)
            .filterNot { it.first == BLOCKED }
            .map { (key, hold) ->
                val command = if (excludeHold.contains(hold)) {
                    key
                } else {
                    val holdDef = resolveHold(current, hold)
                    holdDef?.let { "(tap-hold-release 200 200 $key $it)" } ?: key

                    //todo umlauts
                    //todo remove super alt ctl O on one O side
                }.replace("_", "") // to avoid duplicate aliases
                Alias("$key$layerSuffix", command)
            }

    private fun resolveHold(current: Layer, hold: String): String? = when {
        hold.contains("+") -> {
            val commands = hold
                .split("+")
                .map { resolveHold(current, it) }
                .joinToString(" ")
            "(multi $commands)"
        }

        hold[0].isUpperCase() -> getNextLayer(current, hold)
        else -> hold
    }

    private fun getNextLayer(current: Layer, hold: String): String? {
        val want = (current.activationKeys + listOf(hold)).toSet()
        val next = layers.singleOrNull { it.activationKeys == want }?.name
        return next?.let { "@$it" }
    }

    fun defSrc(homePos: List<String>): String {
        val thumbPos = thumbs.map { it.inputKey }

        return generate("defsrc", homePos, thumbPos)
    }

    fun defLayer(layer: Layer): String {
        val homeRow = layer.output.map { createOutputKey(it) }
        val suffix = layer.thumbHoldSuffix
        val thumbRow = thumbs.map { "@${it.tap}$suffix" }

        return generate("deflayer ${layer.name}", homeRow, thumbRow)
    }
}

fun main(args: Array<String>) {
    val config = "/home/gregor/source/keyboard/keyboard14.md"
//    val config = args.getOrNull(0) ?: throw IllegalArgumentException("config file must be the first argument")
//    val outputFile = args.getOrNull(1) ?: throw IllegalArgumentException("output file must be the second argument")
    val outputFile = "/home/gregor/source/keyboard/keyboard14.kbd"
//    val device = args.getOrNull(2) ?: throw IllegalArgumentException("device must be the third argument")

    val tables = readTables(config)

    val symbols = Symbols(tables.getMappingTable("Symbol"))
    val customAlias = tables.getMappingTable("Alias")
    val layerTable = tables.get("Layer")
    val layers = readLayers(layerTable, symbols)
    val thumbs = readThumbs(tables.get("Thumb Pos"), symbols)

    val options = tables.getMappingTable("Option")
    val generator = Generator(options, thumbs, layers)

    val alias = generator.defAlias(layerTable[1].drop(2), customAlias);
    val defSrc = generator.defSrc(getInputKeys(layerTable[0].drop(2)))
    val layerOutput = layers.joinToString("\n") { generator.defLayer(it) }

    write(outputFile, alias, defSrc, layerOutput)
}

fun write(outputFile: String, vararg output: String) {
    File(outputFile).writeText(output.joinToString("\n\n"))
}

fun createOutputKey(key: String): String {
    val number = key.all { it.isDigit() }
    return when {
        key.startsWith("(") -> key // a mouse command
        key == BLOCKED -> key
        number && key.length == 1 -> "@$key"
        number || key[0].isUpperCase() -> {
            // keycodes and custom commands are not handled yet
            println("cannot handle $key")
            //todo mouse
            //todo keycode
            BLOCKED
        }

        else -> "@$key"
    }
}

fun readLayers(table: List<List<String>>, symbols: Symbols): List<Layer> {
    return table
        .drop(2) // header + Hold
        .map { layerLine ->
            val name = layerLine[0]
            if (!name[0].isUpperCase() || !name[0].isLetter()) {
                throw IllegalStateException("Illegal layer name (must start with upper case alpha): $name")
            }
            val keys = layerLine[1].toCharArray().map { it.toString() }.toSet()
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

fun readTables(config: String): Tables = File(config)
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

    }.let { Tables(it) }
