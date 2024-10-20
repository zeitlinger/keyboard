import java.io.File


fun readTables(config: File): Tables = config
    .readText()
    .split("\n\\s*\n".toRegex())
    .filter { it.startsWith("|") }
    .associate { tableLines ->
        val lines = tableLines
            .split("\n")
            .filter { validLine(it) }
        val header = tableLine(lines[0])
        val map = lines
            .drop(1)
            .split { it.contains("| --") }
            .filter { it.isNotEmpty() }
            .map { it.map(::tableLine) }
        header[0] to MultiTableWithHeader(header, map)
    }.let { Tables(it) }

private fun validLine(line: String) = when {
    line.isBlank() -> false
    line.contains("| --") -> true
    line.contains("---") -> false
    line.contains("|--") -> false
    else -> true
}

private fun tableLine(tableLine: String) = tableLine.split("|")
    .drop(1) // initial |
    .dropLast(1) // last |
    .map { it.trim() }

enum class CustomCommandType {
    OnPress,
    OnTap
}

data class CustomCommand(
    val type: CustomCommandType,
    val cStatements: List<String>,
)

data class CustomKey(var key: QmkKey, val targetLayerName: LayerName?, val command: CustomCommand?, val originalKey: QmkKey?)

data class Symbols(
    val mapping: Map<String, String>,
    val customKeycodes: MutableMap<String, CustomKey>,
) {
    fun replace(key: String, pos: KeyPosition, translator: QmkTranslator): String {
        val value = mapping[key]
        if (value != null) {
            customKeycodes[value]?.targetLayerName?.let { translator.reachLayer(it, pos, LayerActivation.Toggle) }
            return value
        }
        return key
    }
}

typealias Table = List<List<String>>

typealias MultiTable = List<Table>

data class MultiTableWithHeader(val header: List<String>, val content: MultiTable)

data class Tables(val content: Map<String, MultiTableWithHeader>) {

    fun get(name: LayerName): MultiTableWithHeader = content.getValue(name)

    fun getSingle(name: String): Table = get(name).content.single()
    fun getOptional(name: String): Table? = content[name]?.content?.singleOrNull()
    fun getMulti(name: String): MultiTableWithHeader = get(name)

    fun getMappingTable(
        name: String,
    ): Map<String, String> = getSingle(name).associate { it[0] to it[1] }
}

fun <T> List<T>.split(predicate: (T) -> Boolean): List<List<T>> {
    val idx = this.indexOfFirst(predicate)
    return if (idx == -1) {
        listOf(this)
    } else {
        return listOf(this.take(idx)) + this.drop(idx + 1).split(predicate)
    }
}
