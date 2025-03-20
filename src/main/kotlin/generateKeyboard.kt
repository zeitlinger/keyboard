import java.io.File

data class GitFile(
    val file: File,
)

data class GeneratorArgs(
    val configFile: GitFile,
    val generatorDir: GitFile,
    val dstDir: File,
    val versionString: String,
    val printStats: Boolean ,
)

val gitTemplate = "https://github.com/zeitlinger/keyboard/blob/main/%s"
val gitVersionTemplate = "https://github.com/zeitlinger/keyboard/blob/%s/%s"

fun main() {
    val cfg = File("README.md")
    val res = File("src/main/resources")
    run(
        GeneratorArgs(
            GitFile(cfg),
            GitFile(res),
            File("qmk"),
            "use target/qmk to build the firmware to get the git version",
            true,
        )
    )
    "cp -r qmk target/".runCommand()
    run(
        GeneratorArgs(
            GitFile(cfg),
            GitFile(res),
            File("target/qmk"),
            readGitVersion(GitFile(cfg), cfg.name),
            false,
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
    TapToggle("$", "TT"),
    OneShot("@", "OSL"),
    ChangeDefault(">", "DF"),
    Hidden(null, null),
    TapHold(null, null),
    ModTap(null, null);
}

enum class LayerFlag { Shifted, DirectComboLeft, DirectComboRight, TriLayer }

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
    val comboTimeout: Int?,
    var reachable: MutableMap<KeyPosition, LayerActivation>,
    var toggleOn: Boolean = false,
    var toggleOff: Boolean = false,
)

data class Key(
    val key: QmkKey,
    val pos: KeyPosition,
    val keyWithModifier: QmkKey = key,
    val comboTimeout: Int? = null,
) {
    fun isBlocked(): Boolean = keyWithModifier.isNo

    fun isReal(): Boolean {
        return !(isBlocked() || key.key == comboTrigger || key.key == "KC_TRNS" || key.isNo)
    }
}


typealias Rows = List<List<Key>>

data class Layer(
    val name: LayerName,
    val rows: Rows,
    val combos: List<Rows>,
    val number: Int,
    val option: LayerOption,
) {
    fun get(pos: KeyPosition): Key = rows[pos.row][pos.column]
}
