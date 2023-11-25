import org.hjson.JsonValue
import java.io.File
import java.io.FileReader

fun main() {
    val config = File("/home/gregor/source/keyboard/README.md")
    val layoutTemplate = File("/home/gregor/source/keyboard/layout.h")

    val comboFile = File("/home/gregor/source/mini-ryoku/qmk/combos.def")
    val layoutFile = File("/home/gregor/source/mini-ryoku/qmk/layout.h")
    val features = setOf<Feature>()

    run(config, comboFile, layoutFile, layoutTemplate, features)
}

const val mainLayerTemplate =
    "\t[%d] = LAYOUT_split_3x5_2(" +
            "%s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s, " +
            "%s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s, " +
            "%s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s, " +
            "%s, %s, %s, %s),"

const val keyboardRows = 3
const val thumbRows = 1

enum class Feature {
    ModCombo
}

class QmkTranslator(val symbols: Symbols, private val layerNames: Map<String, Int>) {

    private val map: Map<String, String>

    init {
        val files = mapOf(
            "/home/gregor/qmk_firmware/data/constants/keycodes/keycodes_0.0.1_basic.hjson" to "keycodes",
            "/home/gregor/qmk_firmware/data/constants/keycodes/extras/keycodes_us_0.0.1.hjson" to "aliases",
        )
        map = files.flatMap { file ->
            val aliases = JsonValue.readHjson(FileReader(file.key))
                .asObject().get(file.value).asObject()
            aliases.mapNotNull {
                val o = it.value.asObject()
                val key = o.get("key").asString()
                key.takeUnless { it.contains("KP_") || it.contains("NONUS_") }?.let { o.get("label").asString() to it }
            }
        }.toMap()
    }

    fun toQmk(key: String): String = key
        .let { symbols.replace(it) }
        .let { translatedKey -> map.getOrDefault(translatedKey.replaceFirstChar { it.titlecase() }, translatedKey) }
        .let {
            when {
                getSubstitutionCombo(it) != null -> it
                else -> assertQmk(it)
            }
        }

    fun mustTranslateLayer(key: String): Int = layerNames.getValue(key)
}

data class Hand(
    val name: String,
    val columns: Int,
    val baseLayerRowSkip: Int,
    val skip: Int,
    val translateComboIndex: (Int) -> Int
) {
    fun applies(rows: Rows): Boolean {
        if (this.columns != rows[0].size) {
            return false
        }

        val half = this.columns / 2
        val halves = listOf(0, half).map { drop ->
            rows.map { it.drop(drop).take(half) }.flatten()
        }

        val isFull = halves
            .any {
                val comboTriggers = it.filter { it == comboTrigger }.size
                val used = it.filter { it != blocked }.size
                used > 0 && comboTriggers == used
            }
        return this.isFull == isFull
    }

    val isRight = this.name.startsWith("right")
    val isThumb = this.name.contains("thumb")
    private val isFull = this.name.contains("both")
    val comboColumns = if (isFull) this.columns else this.columns / 2
}

val hands = listOf(
    Hand("left", 8, 0, 0) { i -> i + 3 },
    Hand("right", 8, 0, 4) { i -> 8 - i },
    Hand("left thumb", 4, 3, 0) { i -> i + 1 },
    Hand("right thumb", 4, 3, 2) { i -> 4 - i },
    Hand("both thumbs", 4, 3, 0) { i -> i },
)

enum class Modifier {
    Alt, Shift, Ctrl
}

data class ModTrigger(val mods: List<Modifier>, val triggers: List<Int>, val command: String, val name: String?)

private const val qmkNo = "KC_NO"

typealias Rows = List<List<String>>

data class Layer(
    val name: String,
    val baseRows: Rows,
    val combos: List<Rows>,
    val number: Int,
    val comboTrigger: String?,
)

val qmkPrefixes = setOf(
    "KC_",
    "LT(",
    "MO(",
    "LCTL(",
    "RCS(",
    "RALT(",
    "LALT(",
    "LSFT(",
    "LALT_T(",
    "LCTL_T(",
    "RCTL_T(",
    "RALT_T(",
    "LSFT_T(",
    "RSFT_T(",
)

fun assertQmk(key: String): String {
    return when {
        key == blocked || key == comboTrigger || qmkPrefixes.any { key.startsWith(it) } -> key
        else -> throw IllegalStateException("key not translated $key")
    }
}


val specialLayers = listOf("FnMou", "Sym", "Media", "Alt", "Ctrl")

data class Generator(
    val layers: List<Layer>,
) {

    fun generateBase(): String {
        return layers.mapIndexed { index, layer ->
            val def = layer.baseRows.flatten()
            val qmk = def
                .map { if (it == blocked) qmkNo else it }

            mainLayerTemplate.format(*listOf(index).plus<Any>(qmk).toTypedArray())
        }.joinToString("\n")
    }

}

private fun run(config: File, comboFile: File, layoutFile: File, layoutTemplate: File, features: Set<Feature>) {
    val tables = readTables(config)

    val symbols = Symbols(tables.getMappingTable("Symbol"))
    val thumbs = tables.get("Thumb").drop(1) // Header
        .groupBy { it[0] }
        .toMap()
    val layerContent = tables.get("Layer")
    val layerNames = layerContent.drop(1).map { it[0] }.toSet().mapIndexed { index, s -> s to index }.toMap()

    val translator = QmkTranslator(symbols, layerNames)

    val layers = readLayers(layerContent, thumbs, translator)
    val layerNumbers = layers.joinToString("\n") { "#define _${it.name.uppercase()} ${it.number}" }

//    printMissingAndUnexpected(translator, layers, symbols)

    val generator = Generator(layers)
    val combos = generateCombos(generator.layers, features).map { combo ->
        combo.type.template.format(
            combo.name.padEnd(20),
            combo.result.padEnd(50),
            combo.triggers
                .joinToString(", ")
        )
    }

    val generationNote =
        "file is generated from ${config.name} using https://github.com/zeitlinger/keyboard/blob/main/generateKeyboard.kt"

    val base = layoutTemplate.readText()
        .replace("\${generationNote}", generationNote)
        .replace("\${layers}", generator.generateBase())
        .replace("\${layerNumbers}", layerNumbers)

    layoutFile.writeText(base)

    comboFile.writeText((listOf("// $generationNote") + combos).joinToString("\n"))

}
//
//private fun printMissingAndUnexpected(
//    translator: QmkTranslator,
//    layers: List<Layer>,
//    symbols: Symbols
//) {
//    val gotKeys = thumbs.map { translator.toQmk(it.baseKey) } +
//            layers.map { it.baseRows.flatten() + it.combos.flatten().flatten() }.flatten()
//                .filterNot { it == blocked || it == comboTrigger }
//
//    val want =
//        symbols.mapping.values +
//                (CharRange('!', '~')
//                    .map { it.toString() }
//                    .filter { it.lowercase() == it }
//                    .map { translator.toQmk(it) }) +
//                (1..12).map { "KC_F$it" }
//                    .toSet()
//
//    val missing = (want - gotKeys.toSet()).map { translator.toLabel(it) }
//    val unexpected = (gotKeys.toSet() - want.toSet()).map { translator.toLabel(it) }
//    println("expected: ${want.size}")
//    println("missing: $missing")
//    println("unexpected: $unexpected")
//    val dups = gotKeys.filter { k -> gotKeys.filter { k == it }.size > 1 }
//        .map { translator.toLabel(it) }.distinct()
//    println("duplicates: $dups")
//}

fun readLayers(
    layerContent: Table,
    thumbs: Map<String, List<List<String>>>,
    translator: QmkTranslator
): List<Layer> {
    val comboLayerTrigger = mutableMapOf<Int, String>()
    val layerByName = layerContent.drop(1) // Header
        .groupBy { it[0] }
        .toMap()
    return layerByName.entries.mapIndexed { layerNumber, (layerName, content) ->
        val data = translateTable(content, translator, comboLayerTrigger)
        val base = data.take(keyboardRows)
            .mapIndexed { row, def ->
                if (row == 1 && layerNumber > 0) {
                    addModTab(def)
                } else {
                    def
                }
            }


        val combos = data.drop(keyboardRows).chunked(keyboardRows)

        val thumbData = translateTable(thumbs.getValue(layerName), translator, comboLayerTrigger)
        val baseThumb = listOf(thumbData[0])
        val comboThumb = thumbData.drop(thumbRows).chunked(thumbRows)

        val baseRows = (base + baseThumb)
        Layer(
            layerName, baseRows,
            combos + comboThumb,
            layerNumber,
            comboLayerTrigger[layerNumber]
        )
    }
}

private fun translateCommand(
    command: String,
    comboLayerTrigger: MutableMap<Int, String>,
    translator: QmkTranslator
): String = when {
    translator.symbols.mapping.containsKey(command) -> {
        command // is translated later
    }

    command.startsWith("ComboLayer:") -> {
        val parts = command.split(" ")
        val trigger = translator.mustTranslateLayer(parts[0].split(":")[1])
        val key = translateCommand(parts[1], comboLayerTrigger, translator)
        comboLayerTrigger[trigger] = key
        key
    }

    command.contains("+") && command.length > 1 -> {
        val parts = command.split("+")
        "LT(${translator.mustTranslateLayer(parts[1])},${translator.toQmk(parts[0])})"
    }

    command.contains("-") && command.length > 1 -> {
        val parts = command.split("-")
        val modifier = parts[0]
        val key = translator.toQmk(parts[1])
        when (modifier) {
            "A" -> "LALT(${key})"
            "C" -> "LCTL(${key})"
            "S" -> "LSFT(${key})"
            "CS" -> "RCS(${key})"
            else -> throw IllegalStateException("unknown modifier $modifier")
        }
    }

    command.isNotBlank() && command[0].isUpperCase() -> {
        "MO(${translator.mustTranslateLayer(command)})"
    }

    else -> {
        command
    }
}

fun addModTab(row: List<String>): List<String> {
    return row.mapIndexed { index, key ->
        if ("(" in key || key == blocked) {
            key
        } else {
            when (index) {
                1, 6 -> "LALT_T($key)"
                2 -> "LCTL_T($key)"
                3 -> "LSFT_T($key)"
                4 -> "RSFT_T($key)"
                5 -> "RCTL_T($key)"
                else -> key
            }
        }
    }
}

private fun translateTable(
    content: List<List<String>>,
    translator: QmkTranslator,
    comboLayerTrigger: MutableMap<Int, String>
) = content.map { it.drop(1) }
    .map { row ->
        row
            .map { translateCommand(it, comboLayerTrigger, translator) }
            .map { translator.toQmk(it) }
    }



