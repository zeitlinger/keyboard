package  combo

import blocked
import Symbols
import readTables
import java.io.File


fun main() {
    val config = File("/home/gregor/source/keyboard/combo14.md")

    val outputFile = File("/home/gregor/source/mini-ryoku/qmk/combos.def")

    run(config, outputFile)
}

private val layerTriggers: Map<String, List<String>> = mapOf(
        "Base" to emptyList(),
        "Right" to listOf("LT(1,KC_BSPC)"),
        "Left" to listOf("LT(2,KC_SPC)"),
        "Both" to listOf("LT(1,KC_BSPC)", "LT(2,KC_SPC)")
)

const val comboDef = "COMB(%s, %s, %s)"

data class Hand(val name: String, val skip: Int, val opposingSkip: Int, val translateComboIndex: (Int) -> Int)

val hands = listOf(
        Hand("left", 0, 4) { i -> i + 3 },
        Hand("right", 4, 0) { i -> 8 - i },
)

enum class Modifier {
    Alt, Shift, Ctrl
}

data class ModTrigger(val mods: List<Modifier>, val triggers: List<Int>, val command: String, val name: String)

private const val customCombo = "KC_NO"

private val modTriggers: List<ModTrigger> = listOf(
        ModTrigger(listOf(Modifier.Shift), listOf(1, 2), "LM(%d, MOD_LSFT)", "S"),
        ModTrigger(listOf(Modifier.Ctrl), listOf(2, 3), "LM(%d, MOD_LCTL)", "C"),
        ModTrigger(listOf(Modifier.Alt), listOf(3, 4), "LM(%d, MOD_LALT)", "A"),
        ModTrigger(listOf(Modifier.Shift, Modifier.Ctrl), listOf(1, 2, 3), "LM(%d, MOD_LCTL | MOD_LSFT)", "CS"),
        ModTrigger(listOf(Modifier.Shift, Modifier.Alt), listOf(1, 4), "LM(%d, MOD_LSFT | MOD_LALT)", "SA"),
        ModTrigger(listOf(Modifier.Ctrl, Modifier.Alt), listOf(2, 3, 4), "LM(%d, MOD_LCTL | MOD_LALT)", "CA"),
        ModTrigger(listOf(Modifier.Shift, Modifier.Shift, Modifier.Alt), listOf(1, 2, 3, 4), "LM(%d, MOD_LCTL | MOD_LALT | MOD_LSFT)", "CSA"),
)

data class Layer(val name: String, val output: List<List<String>>)

private const val comboTrigger = "\uD83D\uDC8E"


data class Combo(val name: String, val result: String, val triggers: List<String>)

data class ComboInput(val base: List<String>, val opposingBase: List<String>,
                      val layerBase: List<String>, val opposingLayerBase: List<String>,
                      val definition: List<String>) {
    fun generate(hand: Hand, layerTrigger: List<String>, layerName: String, layerIndex: Int): List<Combo> {
        val comboIndexes = definition.mapIndexedNotNull { index, s -> if (s == comboTrigger) index else null }

        return comboWithMods(Combo(layerName, customCombo, layerTrigger), opposingBase, hand, layerName, layerIndex) +
                definition.flatMapIndexed { comboIndex, key ->
                    if (!(key.isBlank() || key == blocked || key == comboTrigger)) {
                        val layerKeys = layerBase
                                .filterIndexed { index, _ -> index == comboIndex || index in comboIndexes }
                                .map { toQmk(it) }

                        listOf(Combo(comboName(layerName, key), toQmk(key), layerKeys))
                    } else emptyList()
                }.filter { it.triggers.size > 1 }
    }
}

fun comboName(layer: String, key: String): String {
    return "C_${layer.uppercase()}_${key.uppercase()}"
}

fun comboWithMods(combo: Combo, base: List<String>, hand: Hand, layerName: String, layerIndex: Int): List<Combo> {
    return listOfNotNull(combo.takeIf { it.triggers.size > 1 }) +
            modTriggers.map { modTrigger ->
                val keys = modTrigger.triggers.map { base[hand.translateComboIndex(it)] }
                        .map { toQmk(it) }

                val command = modTrigger.command.format(layerIndex)
                Combo(comboName("${layerName}_${hand.name}", modTrigger.name), command, combo.triggers + keys)
            }
}

fun comboInput(base: List<List<String>>, layerBase: List<List<String>>, definition: List<List<String>>,
               skip: Int, opposingSkip: Int): ComboInput =
        ComboInput(
                getLayerPart(base, skip), getLayerPart(base, opposingSkip),
                getLayerPart(layerBase, skip), getLayerPart(layerBase, opposingSkip),
                getLayerPart(definition, skip))

private fun getLayerPart(layerBase: List<List<String>>, skip: Int) =
        layerBase.map { it.drop(skip).take(4) }.flatten()

fun toQmk(key: String): String {
    return when {
        key == blocked || key == comboTrigger -> key
        "a" <= key && key <= "z" -> "KC_${key.uppercase()}"
        "0" <= key && key <= "9" -> "KC_${key.uppercase()}"
        else -> throw IllegalStateException("key not translated $key")
    }
}


data class Generator(
        val layers: List<Layer>,
        val customAlias: Map<String, String>,
) {


    fun generatedKeyboard(): List<Combo> {
        val base = layers[0].output.take(2)

        val combos = layers.flatMap { layer ->
            val activationParts = layer.output.chunked(2)
            val layerBase = activationParts[0]

            val layerIndex = layerTriggers.keys.indexOf(layer.name)
            val layerTrigger = layerTriggers.getValue(layer.name)

            activationParts.flatMap { def ->
                hands.flatMap { hand ->
                    comboInput(base, layerBase, def, hand.skip, hand.opposingSkip).generate(hand, layerTrigger, layer.name, layerIndex)
                }
            }.distinct()
        }
        return combos
    }
}

private fun run(config: File, outputFile: File) {
    val tables = readTables(config)

    val symbols = Symbols(tables.getMappingTable("Symbol"))
    val customAlias = tables.getMappingTable("Alias")
    val layerTable = tables.get("Layer")
    val layerContent = layerTable.drop(1) // Header
            .groupBy { it[0] }
//            .mapValues { it.value.map { it.drop(1) } }
            .toMutableMap()

    val layers = readLayers(layerContent, symbols)

    val generator = Generator(layers, customAlias)
    val combos = generator.generatedKeyboard()
    val defs = combos.map { combo ->
        comboDef.format(
                combo.name.padEnd(20),
                combo.result.padEnd(50),
                combo.triggers
                        .joinToString(", "))
    }

    outputFile.writeText(
            (listOf("// file is generated from ${config.name} using /home/gregor/source/keyboard/combo/generateCombos.kt") + defs).joinToString("\n")
    )

}

fun readLayers(table: Map<String, List<List<String>>>, symbols: Symbols): List<Layer> {
    return table.map { (name, content) ->
        val mapping = dropFirstCol(content)
                .map { it.map { symbols.replace(it.substringBefore(" ")) } } // part after space is only for illustration
        Layer(name, mapping)
    }
}

private fun dropFirstCol(hold: List<List<String>>): List<List<String>> =
        hold.map { it.drop(1) }



