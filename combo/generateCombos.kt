package  combo

import Symbols
import blocked
import org.hjson.JsonValue
import readTables
import java.io.File
import java.io.FileReader

//todo
//direct shortcut for combos

fun main() {
    val config = File("/home/gregor/source/keyboard/combo14.md")
    val layoutTemplate = File("/home/gregor/source/keyboard/combo/layout.h")

    val comboFile = File("/home/gregor/source/mini-ryoku/qmk/combos.def")
    val layoutFile = File("/home/gregor/source/mini-ryoku/qmk/layout.h")

    run(config, comboFile, layoutFile, layoutTemplate)
}

const val comboDef = "COMB(%s, %s, %s)"

const val mainLayerTemplate =
    "\t[%d] = LAYOUT_split_3x5_2(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s, %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s, %s, %s, %s, %s),"

data class Hand(val name: String, val skip: Int, val opposingSkip: Int, val translateComboIndex: (Int) -> Int) {
    val isRight = this.name == "right"
}

data class Thumb(val name: String, val position: Int, val keyTemplate: String)

val hands = listOf(
    Hand("left", 0, 4) { i -> i + 3 },
    Hand("right", 4, 0) { i -> 8 - i },
)

enum class Modifier {
    Alt, Shift, Ctrl
}

data class ModTrigger(val mods: List<Modifier>, val triggers: List<Int>, val command: String, val name: String?)

private const val qmkNo = "KC_NO"

private val modTriggers: List<ModTrigger> = listOf(
    ModTrigger(emptyList(), emptyList(), "MO(%d)", null),
    ModTrigger(listOf(Modifier.Shift), listOf(1, 2), "LM(%d, MOD_LSFT)", "S"),
    ModTrigger(listOf(Modifier.Ctrl), listOf(2, 3), "LM(%d, MOD_LCTL)", "C"),
    ModTrigger(listOf(Modifier.Alt), listOf(3, 4), "LM(%d, MOD_LALT)", "A"),
    ModTrigger(listOf(Modifier.Shift, Modifier.Ctrl), listOf(1, 2, 3), "LM(%d, MOD_LCTL | MOD_LSFT)", "CS"),
    ModTrigger(listOf(Modifier.Shift, Modifier.Alt), listOf(1, 4), "LM(%d, MOD_LSFT | MOD_LALT)", "SA"),
    ModTrigger(listOf(Modifier.Ctrl, Modifier.Alt), listOf(2, 3, 4), "LM(%d, MOD_LCTL | MOD_LALT)", "CA"),
    ModTrigger(
        listOf(Modifier.Shift, Modifier.Shift, Modifier.Alt),
        listOf(1, 2, 3, 4),
        "LM(%d, MOD_LCTL | MOD_LALT | MOD_LSFT)",
        "CSA"
    ),
)

typealias Rows = List<List<String>>

data class Layer(
    val number: Int,
    val name: String,
    val baseRows: Rows,
    val combos: List<Rows>,
    val activation: Set<Thumb>
)

private const val comboTrigger = "\uD83D\uDC8E"


data class Combo(val name: String, val result: String, val triggers: List<String>)

fun generateModCombos(layerTrigger: List<String>, opposingBase: List<String>, layer: Layer, hand: Hand): List<Combo> {
    return comboWithMods(
        opposingBase, hand,
        layer.name, layer.number, layerTrigger
    )
}

fun generateCustomCombos(def: Rows, layerBase: List<String>, layer: Layer, hand: Hand): List<Combo> {
    val definition = getLayerPart(def, hand.skip)
    val comboIndexes = definition.mapIndexedNotNull { index, s -> if (s == comboTrigger) index else null }

    return definition.flatMapIndexed { comboIndex, key ->
        if (!(key.isBlank() || key == blocked || key == comboTrigger)) {
            val layerKeys = layerBase
                .filterIndexed { index, _ -> index == comboIndex || index in comboIndexes }
                .map { toQmk(it) }

            listOf(Combo(comboName(layer.name, key), toQmk(key), layerKeys))
        } else emptyList()
    }.filter { it.triggers.size > 1 }
}

fun comboName(vararg parts: String?): String {
    return "C_${parts.filterNotNull().joinToString("_") { it.uppercase() }}"
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
            .map { toQmk(it) }

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

private fun getLayerPart(layerBase: List<List<String>>, skip: Int) =
    layerBase.map { it.drop(skip).take(4) }.flatten()

fun toQmk(key: String): String {
    return when {
        key == blocked || key == comboTrigger || key.startsWith("KC_") || key.startsWith("LT(") -> key
        else -> throw IllegalStateException("key not translated $key")
    }
}


data class Generator(
    val layers: List<Layer>,
    val customAlias: Map<String, String>,
    val thumbs: List<Thumb>,
) {

    fun generateBase(): String {
        return layers.map { layer ->
            val def = layer.baseRows.flatten() +
                    thumbs.map { thumb -> translateThumb(thumb, layer) }
            val qmk = def
                .map { toQmk(it) }
                .map { if (it == blocked) qmkNo else it }

            mainLayerTemplate.format(*listOf(layer.number).plus<Any>(qmk).toTypedArray())
        }.joinToString("\n")
    }

    private fun translateThumb(thumb: Thumb, layer: Layer): String {
        return targetLayer(thumb, layer, layers)?.let { thumb.keyTemplate.format(it.number) } ?: "KC_TRNS"
    }

    fun generateCombos(): List<Combo> {
        val baseRows = layers[0].baseRows

        return layers.flatMap { layer ->
            val activationParts = layer.combos
            val layerBase = layer.baseRows

            val layerTrigger = layer.activation.map { translateThumb(it, layers[0]) }

            layerBase.flatten().zip(baseRows.flatten()).mapNotNull { (layerKey, baseKey) ->
                if ("KC_A" <= layerKey && layerKey <= "KC_Z" && layerKey != baseKey) {
                    Combo(comboName(layerKey), layerKey, listOf(baseKey) + layerTrigger)
                } else null
            } + hands.flatMap { hand ->
                generateModCombos(layerTrigger, getLayerPart(baseRows, hand.opposingSkip), layer, hand) +
                        activationParts.flatMap { def ->
                            generateCustomCombos(
                                def,
                                getLayerPart(layerBase, hand.skip),
                                layer, hand,
                            )
                        }
            }.distinct()
        }
    }
}


private fun targetLayer(thumb: Thumb, currentLayer: Layer, layers: List<Layer>): Layer? {
    val wantSize = currentLayer.activation.size + 1
    val want = currentLayer.activation + setOf(thumb)
    return layers.singleOrNull { it.activation.size == wantSize && it.activation == want }
}

private fun run(config: File, comboFile: File, layoutFile: File, layoutTemplate: File) {
    val tables = readTables(config)

    val symbols = Symbols(tables.getMappingTable("Symbol"))
    val customAlias = tables.getMappingTable("Alias")
    val layerTable = tables.get("Layer")
    val thumbs = tables.get("Thumb").drop(1).mapIndexed { index, line ->
        Thumb(line[0], index, line[1])
    }
    val layerActivation = tables.getMappingTable("Layer Activation")
        .mapValues {
            it.value.toCharArray().map { thumbName -> thumbs.single { thumb -> thumb.name == thumbName.toString() } }
                .toSet()
        }
    val layerContent = layerTable.drop(1) // Header
        .groupBy { it[0] }
        .toMap()

    val layers = readLayers(layerContent, symbols, layerActivation)

    val generator = Generator(layers, customAlias, thumbs)
    val defs = generator.generateCombos().map { combo ->
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
        (listOf("// file is generated from ${config.name} using https://github.com/zeitlinger/keyboard/blob/main/combo/generateCombos.kt") + defs).joinToString(
            "\n"
        )
    )

}

fun readLayers(
    table: Map<String, List<List<String>>>,
    symbols: Symbols,
    layerActivation: Map<String, Set<Thumb>>
): List<Layer> {
    val files = mapOf(
        "/home/gregor/qmk_firmware/data/constants/keycodes/keycodes_0.0.1_basic.hjson" to "keycodes",
        "/home/gregor/qmk_firmware/data/constants/keycodes/extras/keycodes_us_0.0.1.hjson" to "aliases",
    )
    val map = files.flatMap { file ->
        val aliases = JsonValue.readHjson(FileReader(file.key))
            .asObject().get(file.value).asObject()
        aliases.mapNotNull {
            val o = it.value.asObject()
            val key = o.get("key").asString()
            key.takeUnless { it.contains("KP_") || it.contains("NONUS_") }?.let { o.get("label").asString() to it }
        }
    }.toMap()

    fun translateQmk(key: String): String = map.getOrDefault(key.replaceFirstChar { it.titlecase() }, key)

    return table.entries.mapIndexed { index, (name, content) ->
        val data = dropFirstCol(content)
            .map { it.map { s -> translateQmk(symbols.replace(s.substringBefore(" "))) } } // part after space is only for illustration
        val base = data.take(2)
        val combos = data.drop(2).chunked(2)
        Layer(index, name, base, combos, layerActivation.getValue(name))
    }
}

private fun dropFirstCol(hold: List<List<String>>): List<List<String>> =
    hold.map { it.drop(1) }



