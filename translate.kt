import org.hjson.JsonValue
import java.io.FileReader

const val qmkNo = "KC_NO"

class QmkTranslator(
        val symbols: Symbols,
        val layerOption: Map<String, LayerOption>,
        private val nonThumbs: Map<String, List<List<String>>>,
        private val thumbs: Map<String, List<List<String>>>,
        private val layerNumbers: Map<String, Int>,
        val comboLayerTrigger: MutableMap<String, Key>,
        var homeRowThumbCombo: HomeRowCombo?,
        val options: Options,
) {

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
        .let { translatedKey -> map.getOrDefault(translatedKey.replaceFirstChar { it.titlecase() }, translatedKey) }
        .let {
            when {
                getSubstitutionCombo(it) != null || symbols.userKeycodes.contains(it) -> it
                else -> assertQmk(it)
            }
        }

    fun mustTranslateLayer(layerName: String): Int = layerNumbers.getValue(layerName)

    fun getThumbContent(layerName: String): List<List<String>> =
        thumbs[layerName] ?: listOf(List(thumbColumns) { "" })

    fun getKey(pos: KeyPosition): String =
        (if (pos.thumb) getThumbContent(pos.layerName) else nonThumbs.getValue(pos.layerName))[pos.row][pos.column]
}

fun assertQmk(key: String): String {
    return when {
        key == comboTrigger || qmkPrefixes.any { key.startsWith(it) } -> key
        else -> throw IllegalStateException("key not translated $key")
    }
}

val qmkPrefixes = setOf(
    "QK_",
    "KC_",
    "LT(",
    "MO(",
    "C(",
    "RCS(",
    "ALGR(",
    "RSA(",
    "A(",
    "S(",
    "ALT_T(",
    "CTL_T(",
    "SFT_T(",
)
