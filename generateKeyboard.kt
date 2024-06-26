import java.io.File

data class GitFile(
    val file: File,
    val gitTemplate: String,
)

data class GeneratorArgs(
    val configFile: GitFile,
    val generatorDir: GitFile,
    val dstDir: File,
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

const val layerBlocked = "🛑"
const val baseLayerName = "Base"

data class Options(
    val rows: Int,
    val nonThumbColumns: Int,
    val homeRowPositions: Map<Int, Modifier>?,
)

enum class LayerActivation(val prefix: String?, val method: String?) {
    Toggle("#", null),
    Hold("*", "MO"),
    OneShot("@", "OSL"),
    TapHold(null, null),
    ModTap(null, null),
}

enum class LayerFlag { Shifted, Toggle }

typealias LayerName = String

data class LayerRef(val name: LayerName, val number: Int?, val option: LayerOption) {
    fun const() = name.const()
}

data class LayerOption(
    val leftModifier: Map<HomeRowType, LayerName?>,
    val rightModifier: Map<HomeRowType, LayerName?>,
    val leftFallbackLayer: LayerName?,
    val rightFallbackLayer: LayerName?,
    var flags: Set<LayerFlag>,
    var reachable: Set<LayerActivation>,
)

data class Key(
    val key: QmkKey,
    val pos: KeyPosition,
    val keyWithModifier: QmkKey = key,
    val comboTimeout: Int? = null,
) {
    fun isBlocked(): Boolean = keyWithModifier.isNo
}


typealias Rows = List<List<Key>>

data class Layer(
    val name: LayerName,
    val rows: Rows,
    val combos: List<Rows>,
    val number: Int,
    val option: LayerOption,
)
