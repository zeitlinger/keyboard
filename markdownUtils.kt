import java.io.File


const val BLOCKED = "XX"

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


data class Symbols(val mapping: Map<String, String>) {
    fun replace(key: String): String = mapping.getOrDefault(key, key)
            .let { it.ifBlank { BLOCKED } }
            .let { if (it == "❌") BLOCKED else it }
}

typealias Table = List<List<String>>

data class Tables(val content: List<Table>) {

    fun get(name: String): Table = content.single { it[0][0] == name }

    fun getMappingTable(
            name: String,
    ): Map<String, String> = content.single { it[0][0] == name }.drop(1).associate { it[0] to it[1] }
}
