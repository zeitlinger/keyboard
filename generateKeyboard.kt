import java.io.File

data class GeneratorArgs(
    val config: File,
    val comboFile: File,
    val layoutFile: File,
    val layoutTemplate: File,
    val generatedFile: File,
    val generatedTemplate: File,
)

fun main() {
    val target = "/home/gregor/source/mini-ryoku"
    val src = "$target/keyboard"

    run(
        GeneratorArgs(
            File("$src/README.md"),
            File("$target/qmk/combos.def"),
            File("$target/qmk/layout.h"),
            File("$src/layout.h"),
            File("$target/qmk/generated.c"),
            File("$src/generated.c")
        )
    )
}

const val layerBlocked = "❌"
const val baseLayerName = "Base"

data class Options(
    val nonThumbRows: Int,
    val nonThumbColumns: Int,
    val thumbColumns: Int,
    val oneShotTriggers: ModTriggers?,
    val homeRowThumbCombos: ModTriggers?,
    val homeRowPositions: Map<Int, Modifier>,
)

enum class LayerFlag { Hidden }

typealias LayerName = String

data class LayerOption(
    val leftModifier: Map<ModifierType, LayerName?>,
    val rightModifier: Map<ModifierType, LayerName?>,
    val leftFallbackLayer: LayerName?,
    val rightFallbackLayer: LayerName?,
    val flags: Set<LayerFlag>,
)

data class Key(
    val key: String,
    val keyWithModifier: String = key,
    val comboTimeout: Int? = null,
) {
    fun isBlocked(): Boolean = keyWithModifier == qmkNo
}


typealias Rows = List<List<Key>>

data class Layer(
    val name: LayerName,
    val baseRows: Rows,
    val combos: List<Rows>,
    val number: Int,
    val comboTrigger: Key?,
    val option: LayerOption,
)

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


