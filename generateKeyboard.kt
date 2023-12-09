import java.io.File

data class GeneratorArgs(
    val config: File,
    val comboFile: File,
    val layoutFile: File,
    val layoutTemplate: File,
    val generatedFile: File,
    val generatedTemplate: File,
    val gitTemplate: String
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
            File("$src/generated.c"),
            "https://github.com/zeitlinger/keyboard/blob/%s/README.md"
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
