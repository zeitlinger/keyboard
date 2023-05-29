package  combo

import BLOCKED
import Symbols
import readTables
import java.io.File


fun main() {
    val config = File("/home/gregor/source/keyboard/combo14.md")

    val outputFile = File("/home/gregor/source/mini-ryoku/qmk/combos.def")

    run(config, outputFile)
}

private val layerTrigger: Map<String, List<String>> = mapOf(
        "Base" to emptyList(),
        "Right" to listOf("LT(1,KC_BSPC)"),
        "Left" to listOf("LT(2,KC_SPC)"),
        "Both" to listOf("LT(1,KC_BSPC)", "LT(2,KC_SPC)")
)

const val comboDef = "COMB(C_%d,\t%s,\t%s)"

data class Hand(val skip: Int, val opposingSkip: Int, val translateComboIndex: (Int) -> Int)

val hands = listOf(
        Hand(0, 4) { i -> i + 3 },
        Hand(4, 0) { i -> 8 - i },
)

enum class Modifier {
    Alt, Shift, Ctrl
}

data class ModTrigger(val mods: List<Modifier>, val triggers: List<Int>, val qmkTemplate: String)

private val modTriggers: List<ModTrigger> = listOf(
        ModTrigger(listOf(Modifier.Shift), listOf(1, 2), "S(%s)"),
        ModTrigger(listOf(Modifier.Ctrl), listOf(2, 3), "C(%s)"),
        ModTrigger(listOf(Modifier.Alt), listOf(3, 4), "A(%s)"),
        ModTrigger(listOf(Modifier.Shift, Modifier.Ctrl), listOf(1, 2, 3), "RCS(%s)"),
        ModTrigger(listOf(Modifier.Shift, Modifier.Alt), listOf(1, 4), "LSA(%s)"),
        ModTrigger(listOf(Modifier.Ctrl, Modifier.Alt), listOf(2, 3, 4), "LCA(%s)"),
        ModTrigger(listOf(Modifier.Shift, Modifier.Shift, Modifier.Alt), listOf(1, 2, 3, 4), "MEH(%s)"),
)

data class Layer(val name: String, val output: List<List<String>>)

private const val comboTrigger = "\uD83D\uDC8E"

data class Combo(val result: String, val triggers: List<String>)

data class ComboInput(val base: List<String>, val opposingBase: List<String>,
                      val layerBase: List<String>, val opposingLayerBase: List<String>,
                      val definition: List<String>) {
    fun generate(hand: Hand, layerCombos: List<String>): List<Combo> {
        val comboIndexes = definition.mapIndexedNotNull { index, s -> if (s == comboTrigger) index else null }
        return definition.flatMapIndexed { comboIndex, s ->
            if (!(s.isBlank() || s == BLOCKED || s == comboTrigger)) {
                val keys = base.filterIndexed { index, _ -> index == comboIndex || index in comboIndexes }
                val layerKeys = layerBase.filterIndexed { index, _ -> index == comboIndex || index in comboIndexes }
                comboWithMods(Combo(s, keys + layerCombos), opposingBase, hand) +
                        comboWithMods(Combo(s, layerKeys), opposingLayerBase, hand)
            } else emptyList()
        }.distinct()
    }
}

fun comboWithMods(combo: Combo, base: List<String>, hand: Hand): List<Combo> {
    return listOfNotNull(combo.takeIf { it.triggers.size > 1 }) +
            modTriggers.map { modTrigger ->
                val keys = modTrigger.triggers.map { base[hand.translateComboIndex(it)] }
                Combo(modTrigger.qmkTemplate.format(combo.result), combo.triggers + keys)
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
                .map { toQmk(it) }

fun toQmk(key: String): String {
    return when {
        key == BLOCKED || key == comboTrigger -> key
        "a" <= key && key <= "z" -> "KC_${key.uppercase()}"
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

            val layerCombos = layerTrigger.getValue(layer.name)

            //also combos for regular keys

            activationParts.flatMap { def ->
                hands.flatMap { hand ->
                    comboInput(base, layerBase, def, hand.skip, hand.opposingSkip).generate(hand, layerCombos)
                }
            }
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
    val defs = combos.mapIndexed { index, combo -> comboDef.format(index, combo.result, combo.triggers.joinToString(", ")) }

    outputFile.writeText(
            (listOf("// file is generated from ${config.name}") + defs).joinToString("\n")
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



