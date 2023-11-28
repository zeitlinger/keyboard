import org.hjson.JsonValue
import java.io.FileReader

const val qmkNo = "KC_NO"

class QmkTranslator(
    val symbols: Symbols,
    private val layerNames: Map<String, Int>,
    val comboLayerTrigger: MutableMap<String, String> = mutableMapOf(),
    var homeRowCombo: HomeRowCombo? = null,
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

    fun mustTranslateLayer(key: String): Int = layerNames.getValue(key)
}

fun assertQmk(key: String): String {
    return when {
        key.isBlocked() || key == comboTrigger || qmkPrefixes.any { key.startsWith(it) } -> key
        else -> throw IllegalStateException("key not translated $key")
    }
}

val qmkPrefixes = setOf(
    "KC_",
    "LT(",
    "MO(",
    "LCTL(",
    "RCS(",
    "RALT(",
    "RSA(",
    "LALT(",
    "LSFT(",
    "LALT_T(",
    "LCTL_T(",
    "RCTL_T(",
    "RALT_T(",
    "LSFT_T(",
    "RSFT_T(",
)
