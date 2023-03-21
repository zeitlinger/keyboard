import java.io.File
import java.lang.IllegalStateException

// todo
// auto-start https://github.com/jtroo/kanata/discussions/130

fun main(args: Array<String>) {
    val config = File("/home/gregor/source/keyboard/keyboard14.md")

//    val config = args.getOrNull(0) ?: throw IllegalArgumentException("config file must be the first argument")
//    val outputFile = args.getOrNull(1) ?: throw IllegalArgumentException("output file must be the second argument")
    val outputFile = File("/home/gregor/source/keyboard/keyboard14.kbd")
    val enterKeyboardFile = File("/home/gregor/source/keyboard/keyboard14-enter.kbd")
//    val device = args.getOrNull(2) // defaults to all keyboards

    run(config, outputFile, enterKeyboardFile)
}

private const val BLOCKED = "XX"

typealias Table = List<List<String>>

data class Tables(val content: List<Table>) {

    fun get(name: String): Table = content.single { it[0][0] == name }

    fun getMappingTable(
        name: String,
    ): Map<String, String> = content.single { it[0][0] == name }.drop(1).associate { it[0] to it[1] }
}

data class LayerKey(val layer: Layer, val key: String, val command: String) {
    fun getAliasName(allWithKey: List<LayerKey>) =
        when {
            layer.shortName.isEmpty() || allWithKey.size == 1 -> key
            allWithKey.filter { it.layer == layer }.size > 1 -> {
                "${layer.shortName}_$key${allWithKey.indexOf(this)}"
            }
            else -> "${layer.shortName}_$key"
        }
}

data class Alias(val name: String, val command: String) {
    val reference = "@$name"
}

data class Layer(val name: String, val activationKeys: Set<String>, val output: List<String>) {
    val shortName = activationKeys.sorted().joinToString("")
}


data class Thumb(val inputKey: String, val tap: String, val hold: String)

data class Symbols(val mapping: Map<String, String>) {
    fun replace(key: String): String = mapping.getOrDefault(key, key).let { it.ifBlank { BLOCKED } }
}

data class GeneratedKeyboard(val aliases: List<Alias>, val layerKeys: List<Pair<Layer, List<List<String>>>>)

data class Generator(
    val options: Map<String, String>,
    val thumbs: List<Thumb>,
    val layers: List<Layer>,
    val customAlias: Map<String, String>,
) {

    private fun statement(header: String, body: String): String = "($header\n$body\n)\n"

    private fun generate(
        header: String,
        rows: List<List<String>>,
    ): String = statement(header, rows.joinToString("\n") { "  ${it.joinToString(" ")}" })


    fun generatedKeyboard(homeRowHold: List<String>): GeneratedKeyboard {
        val layerActivation = layers.map { layer ->
            val homeRow = getLayerKeys(layer, layer.output, homeRowHold, layer.activationKeys)
            val thumbRow = getLayerKeys(layer, thumbs.map { it.tap }, thumbs.map { it.hold }, emptySet()
            )
            val exitRow = listOf(LayerKey(layer, "lrld-next", "lrld-next"))

            layer to listOf(homeRow, thumbRow, exitRow)
        }

        val byCommand = layerActivation.flatMap { it.second }.flatten().groupBy { it.command }

        val byKey = layerActivation.flatMap { it.second }.flatten().groupBy { it.key }

        data class KeyWithAlias(val key: String, val alias: Alias?)

        data class LayerKeyWithAlias(val layer: Layer, val keys: List<List<KeyWithAlias>>)

        val keyWithAlias = layerActivation.map { row ->
            val layer = row.first
            LayerKeyWithAlias(layer, row.second.map { commands ->
                commands.map { command ->
                    val key = command.key
                    val cmd = command.command
                    val allWithCommand = byCommand.getValue(cmd)

                    val primaryCommand =
                        allWithCommand.minWith(compareBy<LayerKey> { it.command.length }.thenBy { it.command })
                    val alias = Alias(primaryCommand.getAliasName(byKey.getValue(key)), cmd)
                    when {
                        key == cmd -> KeyWithAlias(key, null)
                        command == primaryCommand -> KeyWithAlias(alias.reference, alias)
                        else -> KeyWithAlias(alias.reference, null)
                    }
                }
            })
        }
        val aliases = keyWithAlias.flatMap { it.keys }.flatten().mapNotNull { it.alias }
        val layerKeys =
            keyWithAlias.map { layerKeys -> layerKeys.layer to layerKeys.keys.map { row -> row.map { it.key } } }
        return GeneratedKeyboard(aliases, layerKeys)
    }

    fun defAlias(
        aliasMap: Map<String, List<Alias>>,
    ) = statement("defalias", aliasMap.map { entry ->
        val section = entry.value.joinToString("\n") { alias -> "  ${alias.name} ${alias.command}" }
        "  ;; ${entry.key}\n$section"
    }.joinToString("\n\n"))

    private fun getLayerKeys(
        current: Layer,
        keys: List<String>,
        hold: List<String>,
        excludeHold: Set<String>,
    ): List<LayerKey> = keys.zip(hold).map { (key, hold) ->
        when {
            key == BLOCKED -> Unit
            isLayerNameOrRef(key) -> throw IllegalStateException("Upper case is reserved for layers: $key")
            key.all { it.isDigit() } && key.length > 1 -> throw IllegalStateException("Use custom alias for direct keycode: $key")
        }

        val tap = customAlias.getOrDefault(key, key)
        val holdCommand = getHoldCommand(current, hold)
        val noHold = excludeHold.contains(hold) || holdCommand == null
        val isBlocked = tap == BLOCKED
        when {
            noHold && isBlocked -> LayerKey(current, BLOCKED, BLOCKED)
            noHold -> LayerKey(current, key, tap)
            isBlocked -> LayerKey(current, holdCommand!!, holdCommand)
            else -> LayerKey(current, key, (holdCommand?.let { "(tap-hold-release 200 200 $tap $it)" } ?: tap))
        }
    }

    private fun getHoldCommand(current: Layer, hold: String): String? {
        val parts = hold.split("+")
        val layerCommands = parts.filter { isLayerNameOrRef(it) }.toSet()

        val layer = layerCommands.takeUnless { it.isEmpty() }?.let { getNextLayer(current, it) }

        val commands = parts - layerCommands + listOfNotNull(layer)

        return if (commands.size > 1) "(multi ${commands.joinToString(" ")})" else commands.firstOrNull()
    }

    private fun getNextLayer(current: Layer, hold: Set<String>): String? =
        if (current.activationKeys.containsAll(hold)) {
            null
        } else {
            val want = (current.activationKeys + hold).toSet()
            layers.singleOrNull { it.activationKeys == want }?.let { "@${it.name}" }
        }

    fun defSrc(homePos: List<String>): String = generate(
        "defsrc", listOf(
            homePos,
            thumbs.map { it.inputKey },
            listOf(options["Exit Layout"] ?: throw IllegalStateException("Exit Layout key not defined"))
        )
    )

    fun defLayer(layer: Layer, layerKeys: List<List<String>>): String {
        return generate("deflayer ${layer.name}", layerKeys)
    }
}

private fun run(config: File, outputFile: File, enterKeyboardFile: File) {
    val tables = readTables(config)

    val symbols = Symbols(tables.getMappingTable("Symbol"))
    val customAlias = tables.getMappingTable("Alias")
    val layerTable = tables.get("Layer")
    val layers = readLayers(layerTable.drop(2), symbols) // Header + Hold
    val thumbs = readThumbs(tables.get("Thumb Pos"), symbols)

    val options = tables.getMappingTable("Option")
    val generator = Generator(options, thumbs, layers, customAlias)
    val homeRowHold = layerTable[1].drop(2)
    val layerToggle = generator.layers.map { Alias(it.name, "(layer-while-held ${it.name})") }
    val generatedKeyboard = generator.generatedKeyboard(homeRowHold)

    val aliasMap = mapOf(
        "layer aliases" to layerToggle,
        "layer keys" to generatedKeyboard.aliases,
    )

    val defAlias = generator.defAlias(aliasMap)
    val defSrc = generator.defSrc(getInputKeys(layerTable[0].drop(2)))
    val layerOutput = generatedKeyboard.layerKeys.joinToString("\n") { generator.defLayer(it.first, it.second) }

    outputFile.writeText(
        listOf(
            ";; file is generated from ${config.name}",
            defAlias,
            defSrc,
            layerOutput
        ).joinToString("\n\n")
    )

    enterKeyboardFile.writeText(
        File("enter-keyboard-template.kbd")
            .readText()
            .replace("\$enterKey", options.getValue("Enter Layout"))
    )
}

fun readLayers(table: List<List<String>>, symbols: Symbols): List<Layer> {
    return table.map { layerLine ->
        val name = layerLine[0]
        if (!name[0].isUpperCase() || !name[0].isLetter()) {
            throw IllegalStateException("Illegal layer name (must start with upper case alpha): $name")
        }
        val keys = layerLine[1].toCharArray().map { it.toString() }.toSet()
        val mapping = layerLine.drop(2)
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

fun getInputKeys(list: List<String>): List<String> = list.map { it.substringAfter("(").substringBefore(")") }

fun readTables(config: File): Tables =
    config.readText().split("\n\\s*\n".toRegex()).filter { it.startsWith("|") }.map { tableLines ->
        val entries = tableLines.split("\n").filterIndexed { index, line ->
            index != 1               // below header
                && line.isNotBlank() // last block can contain empty line at end
        }
        entries.map { tableLine ->
            tableLine.split("|").drop(1) // initial |
                .dropLast(1) // last |
                .map { it.trim() }
        }

    }.let { Tables(it) }

private fun isLayerNameOrRef(name: String) = name[0].isUpperCase()


