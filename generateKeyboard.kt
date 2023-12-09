import java.io.File

data class GitFile(
    val file: File,
    val gitTemplate: String,
)

data class GeneratorArgs(
    val configFile: GitFile,
    val generatorDir: GitFile,
    val dstDir: File
)

fun main() {
    val target = "/home/gregor/source/mini-ryoku"
    val src = "$target/keyboard"
    val gitTemplate = "https://github.com/zeitlinger/keyboard/blob/%s/%s"
    run(
        GeneratorArgs(
            GitFile(File("$src/README.md"), gitTemplate),
            GitFile(File(src), gitTemplate),
            File(target),
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
    val leftModifier: Map<HomeRowType, LayerName?>,
    val rightModifier: Map<HomeRowType, LayerName?>,
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
