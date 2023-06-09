import java.io.File


const val blocked = "XX"

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


const val inputBlocked = "❌"

data class Symbols(val mapping: Map<String, String>) {
    fun replace(key: String): String = mapping.getOrDefault(key, key)
            .let { it.ifBlank { blocked } }
            .let { if (it == inputBlocked) blocked else it }
}

typealias Table = List<List<String>>

data class Tables(val content: List<Table>) {

    fun get(name: String): Table = content.single { it[0][0] == name }

    fun getMappingTable(
            name: String,
    ): Map<String, String> = get(name).drop(1).associate { it[0] to it[1] }
}
