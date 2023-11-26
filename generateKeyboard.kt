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
    "\t[%d] = LAYOUT_split_3x5_2(\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "                            %s, %s, %s, %s),"

const val keyboardRows = 3
const val thumbRows = 1

const val layerBlocked = "❌"
const val baseLayerName = "Base"

enum class Feature {
    ModCombo
}

data class Option(
    val leftModifier: ModifierType,
    val rightModifier: ModifierType,
    val leftFallbackLayer: String?,
    val rightFallbackLayer: String?
)

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

const val qmkNo = "KC_NO"

typealias Rows = List<List<String>>

data class Layer(
    val name: String,
    val baseRows: Rows,
    val baseRowsWithMods: Rows,
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
        key.isBlocked() || key == comboTrigger || qmkPrefixes.any { key.startsWith(it) } -> key
        else -> throw IllegalStateException("key not translated $key")
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
    val options = tables.get("Options")
        .drop(1)
        .associateBy { it[0] }
        .mapValues {
            Option(
                modifierType(it.value[1]),
                modifierType(it.value[2]),
                it.value[3].ifBlank { null },
                it.value[4].ifBlank { null },
            )
        }

    val translator = QmkTranslator(symbols, layerNames)

    val layers = readLayers(layerContent, thumbs, translator, options)
    val layerNumbers = layers.joinToString("\n") { "#define _${it.name.uppercase()} ${it.number}" }

//    printMissingAndUnexpected(translator, layers, symbols)

    val combos = generateCombos(layers, features).map { combo ->
        combo.type.template.format(
            combo.name.padEnd(35),
            combo.result.padEnd(35),
            combo.triggers
                .joinToString(", ")
        )
    }.sorted()

    val generationNote =
        "file is generated from ${config.name} using https://github.com/zeitlinger/keyboard/blob/main/generateKeyboard.kt"

    val base = layoutTemplate.readText()
        .replace("\${generationNote}", generationNote)
        .replace("\${layers}", generateBase(layers, options))
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


fun String.isBlocked() = this == blocked || this == layerBlocked


