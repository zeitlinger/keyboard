package  combo

import Symbols
import Table
import blocked
import org.hjson.JsonValue
import readTables
import java.io.File
import java.io.FileReader

//SUBS(C_THE,   "the ",    KC_F13)
//SUBS(C_AND,   "and ",    KC_F14)
//SUBS(C_ING,   "ing",    KC_F15)
//SUBS(C_ING,   "that ",    KC_F16)
//SUBS(C_ING,   "have ",    KC_F17)
//SUBS(C_ING,   "with ",    KC_F19)
//SUBS(C_ING,   "this ",    KC_F20)
//SUBS(C_ING,   "from ",    KC_F21)
//SUBS(C_ING,   "they ",    KC_F22)
//SUBS(C_ING,   "you ",    KC_F23)


fun main() {
    val config = File("/home/gregor/source/keyboard/aptex.md")
    val layoutTemplate = File("/home/gregor/source/keyboard/combo/layout.h")

    val comboFile = File("/home/gregor/source/mini-ryoku/qmk/combos.def")
    val layoutFile = File("/home/gregor/source/mini-ryoku/qmk/layout.h")

    run(config, comboFile, layoutFile, layoutTemplate)
}

const val comboDef = "COMB(%s, %s, %s)"

const val mainLayerTemplate =
    "\t[%d] = LAYOUT_split_3x5_2(%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s),"

const val keyboardRows = 3

class QmkTranslator(private val symbols: Symbols, private val layerNames: Map<String, Int>) {

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
        .let { layerNames.entries.fold(it) { acc, name -> acc.replace(name.key, "${name.value}") } }
        .let { translatedKey -> map.getOrDefault(translatedKey.replaceFirstChar { it.titlecase() }, translatedKey) }

    fun toLabel(key: String): String = map.entries.firstOrNull { it.value == key }?.key ?: key

}

data class Hand(
    val name: String,
    val columns: Int,
    val baseLayerRowSkip: Int,
    val skip: Int,
    val opposingSkip: Int,
    val translateComboIndex: (Int) -> Int
) {
    val isRight = this.name.startsWith("right")
}

data class Thumb(val name: String, val position: Int, val key: String)

val hands = listOf(
    Hand("left", 10, 0, 0, 5) { i -> i + 4 },
    Hand("right", 10, 0, 5, 0) { i -> 10 - i },
    Hand("left thumb", 4, 3, 0, 2) { i -> i + 1 },
    Hand("right thumb", 4, 3, 2, 0) { i -> 4 - i },
)

enum class Modifier {
    Alt, Shift, Ctrl
}

data class ModTrigger(val mods: List<Modifier>, val triggers: List<Int>, val command: String, val name: String?)

private const val qmkNo = "KC_NO"

private val modTriggers: List<ModTrigger> = listOf(
    ModTrigger(emptyList(), emptyList(), "MO(%d)", null),
    ModTrigger(listOf(Modifier.Shift), listOf(2, 3), "LM(%d, MOD_LSFT)", "S"),
    ModTrigger(listOf(Modifier.Ctrl), listOf(1, 4), "LM(%d, MOD_LCTL)", "C"),
    ModTrigger(listOf(Modifier.Alt), listOf(3, 4), "LM(%d, MOD_LALT)", "A"),
    ModTrigger(listOf(Modifier.Shift, Modifier.Ctrl), listOf(1, 2, 3), "LM(%d, MOD_LCTL | MOD_LSFT)", "CS"),
    ModTrigger(listOf(Modifier.Shift, Modifier.Alt), listOf(2, 3, 4), "LM(%d, MOD_LSFT | MOD_LALT)", "SA"),
    ModTrigger(listOf(Modifier.Ctrl, Modifier.Alt), listOf(1, 3, 4), "LM(%d, MOD_LCTL | MOD_LALT)", "CA"),
    ModTrigger(
        listOf(Modifier.Shift, Modifier.Shift, Modifier.Alt),
        listOf(1, 2, 3, 4),
        "LM(%d, MOD_LCTL | MOD_LALT | MOD_LSFT)",
        "CSA"
    ),
)

typealias Rows = List<List<String>>

data class Layer(
    val name: String,
    val baseRows: Rows,
    val combos: List<Rows>,
)

private const val comboTrigger = "\uD83D\uDC8E" // 💎

data class Combo(val name: String, val result: String, val triggers: List<String>)

//fun generateModCombos(layerTrigger: List<String>, opposingBase: List<String>, layer: Layer, hand: Hand): List<Combo> {
//    return if (layer.name == mouseLayer) emptyList() else comboWithMods(
//        opposingBase, hand,
//        layer.name, layer.number, layerTrigger
//    )
//}

fun generateCustomCombos(def: Rows, layerBase: List<String>, layer: Layer, hand: Hand): List<Combo> {
    val definition = getLayerPart(def, hand)
    val comboIndexes = definition.mapIndexedNotNull { index, s -> if (s == comboTrigger) index else null }

    return definition.flatMapIndexed { comboIndex, key ->
        if (!(key.isBlank() || key == blocked || key == comboTrigger)) {
            val layerKeys = layerBase
                .filterIndexed { index, _ -> index == comboIndex || index in comboIndexes }
                .map { assertQmk(it) }

            listOf(Combo(comboName(layer.name, key), assertQmk(key), layerKeys))
        } else emptyList()
    }.filter { it.triggers.size > 1 }
}

fun comboName(vararg parts: String?): String {
    return "C_${
        parts.filterNotNull().joinToString("_") {
            it.uppercase().replace("(", "").replace(")", "")
        }
    }"
}

fun comboWithMods(
    base: List<String>,
    hand: Hand,
    layerName: String,
    layerIndex: Int,
    layerTrigger: List<String>
): List<Combo> {
    return modTriggers.mapNotNull { modTrigger ->
        val comboKeys = modTrigger.triggers.map { base[hand.translateComboIndex(it)] }
            .map { assertQmk(it) }

        val command = modTrigger.command.format(layerIndex)
        val allKeys = layerTrigger + comboKeys

        when {
            allKeys.size < 2 -> null //no combo needed
            comboKeys.isEmpty() -> Combo(
                comboName(layerName),
                command,
                allKeys
            ).takeUnless { hand.isRight } // combo for layer is only needed once
            else -> Combo(comboName(layerName, hand.name, modTrigger.name), command, allKeys)
        }
    }
}

private fun getLayerPart(layerBase: List<List<String>>, hand: Hand) =
    layerBase.map { it.drop(hand.skip).take(hand.columns / 2) }.flatten()

val qmkPrefixes = setOf(
    "KC_", "LT(", "MO(", "LCTL(", "RCS(", "RALT(", "LALT(", "LALT_T(", "LCTL_T(", "RCTL_T(", "RALT_T(", "LSFT_T(", "RSFT_T(",
)

fun assertQmk(key: String): String {
    return when {
        key == blocked || key == comboTrigger || qmkPrefixes.any { key.startsWith(it) } -> key
        else -> throw IllegalStateException("key not translated $key")
    }
}


private val sparseLayers = listOf("ComboM", "Media")

data class Generator(
    val layers: List<Layer>,
) {

    fun generateBase(): String {
        return layers.mapIndexed { index, layer ->
            val def = layer.baseRows.flatten()
            val qmk = def
                .map { assertQmk(it) }
                .map { if (it == blocked) qmkNo else it }

            mainLayerTemplate.format(*listOf(index).plus<Any>(qmk).toTypedArray())
        }.joinToString("\n")
    }

    fun generateCombos(): List<Combo> {
        val baseRows = layers[0].baseRows

        return layers.flatMap { layer ->
            val activationParts = layer.combos
            val layerBase = layer.baseRows

            val zip = layerBase.flatten().zip(baseRows.flatten())
            hands.flatMap { hand ->
                activationParts
                    .map { it.filter { hand.columns == it.size } }
                    .flatMap { def ->
                        generateCustomCombos(
                            def,
                            getLayerPart(layerBase.drop(hand.baseLayerRowSkip), hand),
                            layer, hand,
                        )
                    }
            }.distinct()
        }
    }
}

private fun run(config: File, comboFile: File, layoutFile: File, layoutTemplate: File) {
    val tables = readTables(config)

    val symbols = Symbols(tables.getMappingTable("Symbol"))
    val thumbs = tables.get("Thumb").drop(1) // Header
        .groupBy { it[0] }
        .toMap()
    val layerContent = tables.get("Layer")
    val layerNames = layerContent.drop(1).map { it[0] }.toSet().mapIndexed { index, s -> s to index }.toMap()

    val translator = QmkTranslator(symbols, layerNames)

    val layers = readLayers(layerContent, thumbs, translator)

//    printMissingAndUnexpected(translator, layers, symbols)

    val generator = Generator(layers)
    val combos = generator.generateCombos().map { combo ->
        comboDef.format(
            combo.name.padEnd(20),
            combo.result.padEnd(50),
            combo.triggers
                .joinToString(", ")
        )
    }

    val base = layoutTemplate.readText()
        .replace("\${configName}", config.name)
        .replace("\${layers}", generator.generateBase())

    layoutFile.writeText(base)

    comboFile.writeText(
        (listOf("// file is generated from ${config.name} using https://github.com/zeitlinger/keyboard/blob/main/combo/generateCombos.kt") + combos).joinToString(
            "\n"
        )
    )

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
    val layerByName = layerContent.drop(1) // Header
        .groupBy { it[0] }
        .toMap()
//    val baseLayerName = layerContent[1][0]

    return layerByName.entries.mapIndexed { layerNumber, (layerName, content) ->
        if (content.take(keyboardRows).flatten().any { it.isBlank() } && layerName !in sparseLayers) {
            throw IllegalStateException("base row key missing in $layerName")
        }

        val data = translateTable(content, translator)
        val base = data.take(keyboardRows).mapIndexed { row, def ->
            if (row == 1 && layerNumber > 0) {
                addModTab(def)
            } else {
                def
            }
        }
        val combos = data.drop(keyboardRows).chunked(keyboardRows)

        val thumbData = translateTable(thumbs.getValue(layerName), translator)
        val baseThumb = listOf(thumbData[0])
        val comboThumb = listOf(thumbData.drop(1))

//        val inputLayer = layerActivation.single { it.name == name }
//        val activation = inputLayer.activation.map { thumb -> baseThumbs.single { it.name == thumb.name } }.toSet()
        Layer(
            layerName, base + baseThumb,
            combos + comboThumb
        )
    }
}

fun addModTab(row: List<String>): List<String> {
    return row.mapIndexed { index, key ->
        if ("(" in key || key == blocked) {
            key
        } else {
            when (index) {
                1, 8 -> "LALT_T($key)"
                2 -> "LCTL_T($key)"
                3 -> "LSFT_T($key)"
                6 -> "RSFT_T($key)"
                7 -> "RCTL_T($key)"
                else -> key
            }
        }
    }
}

private fun translateTable(
    content: List<List<String>>,
    translator: QmkTranslator
) = content.map { it.drop(1) }
    .map { it.map { s -> translator.toQmk(s) } }



