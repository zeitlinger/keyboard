import java.io.File


fun readTables(config: File): Tables = config
        .readText()
        .split("\n\\s*\n".toRegex())
        .filter { it.startsWith("|") }
        .map { tableLines ->
            val map = tableLines
                    .split("\n")
//                    .drop(1) // header
                    .filter { it.isNotBlank() && !it.contains(":--") && !it.contains("|--") }// last block can contain empty line at end
                    .split { it.contains("| --") }
                    .filter { it.isNotEmpty() }
                    .map(::toTable)
            val name = map[0][0][0]
            name to map
        }.toMap().let { Tables(it) }

private fun toTable(tableLines: List<String>): Table = tableLines.map { tableLine ->
    tableLine.split("|")
            .drop(1) // initial |
            .dropLast(1) // last |
            .map { it.trim() }
}

data class Symbols(val mapping: Map<String, String>, val userKeycodes: List<String>) {
    fun replace(key: String): String = mapping.getOrDefault(key, key)
}

typealias Table = List<List<String>>

typealias MultiTable = List<Table>

data class Tables(val content: Map<String, MultiTable>) {

    fun get(name: String): MultiTable = content.getValue(name)

    fun getWithoutHeader(name: String): Table = get(name).single().drop(1)
    fun getMultiWithoutHeader(name: String): MultiTable = get(name).mapIndexed { index, lists ->
        lists.drop(if (index == 0) 1 else 0)
    }

    fun getMappingTable(
            name: String,
    ): Map<String, String> = getWithoutHeader(name).associate { it[0] to it[1] }
}

fun <T> List<T>.split(predicate: (T) -> Boolean): List<List<T>> {
    val idx = this.indexOfFirst(predicate)
    return if (idx == -1) {
        listOf(this)
    } else {
        return listOf(this.take(idx)) + this.drop(idx + 1).split(predicate)
    }
}
