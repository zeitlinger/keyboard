import java.io.File

fun main() {
    val config = File("/home/gregor/source/keyboard/README.md")
    val layoutTemplate = File("/home/gregor/source/keyboard/layout.h")
    val timerTemplate = File("/home/gregor/source/keyboard/timeout.c")

    val comboFile = File("/home/gregor/source/mini-ryoku/qmk/combos.def")
    val layoutFile = File("/home/gregor/source/mini-ryoku/qmk/layout.h")
    val timeoutFile = File("/home/gregor/source/mini-ryoku/qmk/custom_timeout.c")

    run(config, comboFile, layoutFile, layoutTemplate, timeoutFile, timerTemplate)
}

const val layerBlocked = "❌"
const val baseLayerName = "Base"

data class Options(
    val homeRowComboTimeout: Int?,
    val homeRowThumbComboTimeout: Int?,
)

enum class LayerFlag { Hidden }

data class LayerOption(
    val leftModifier: List<ModifierType>,
    val rightModifier: List<ModifierType>,
    val leftFallbackLayer: String?,
    val rightFallbackLayer: String?,
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
    val name: String,
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


