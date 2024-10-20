import org.hjson.JsonValue
import java.io.FileReader

const val qmkNo = "KC_NO"

data class QmkKey(
    val key: String,
    val substitutionCombo: String? = null,
) {
    override fun toString(): String {
        return key
    }

    val isNo = key == qmkNo
}

data class OneShotOnUpLayer (
    val down: LayerName,
    val up: LayerName,
    val activation: Key,
)

class QmkTranslator(
    val symbols: Symbols,
    val layerOptions: Map<LayerName, LayerOption>,
    val keys: Map<LayerName, MultiTable>,
    val layerNumbers: Map<LayerName, Int>,
    val options: Options,
    val layerTapHold: MutableList<QmkKey>,
    val combos: MutableList<Combo>,
    val ignoreMissing: MutableList<QmkKey>, // because there's a good way to reach this using shift
    val ignoreUnexpected: MutableList<String>,
    val gotKeys: MutableMap<String, MutableList<String>>,
    val noHoldKeys: List<QmkKey>,
    val repeat: MutableMap<QmkKey, String>,
    val altRepeat: MutableMap<QmkKey, String>,
    val oneShotOnUpLayer: MutableList<OneShotOnUpLayer>,
    val originalKeys: MutableMap<KeyPosition, QmkKey>,
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

    fun toQmk(key: String, pos: KeyPosition): QmkKey {
        return key
            .let { symbols.replace(it, pos, this) }
            .let { translatedKey ->
                map.getOrDefault(
                    translatedKey.replaceFirstChar { it.titlecase() },
                    translatedKey
                )
            }
            .let {
                val substitutionCombo = if (it.startsWith("\"") && it.endsWith("\"")) it else null
                when {
                    substitutionCombo != null -> QmkKey(it, substitutionCombo)
                    symbols.customKeycodes.contains(it) -> QmkKey(it)
                    else -> assertQmk(it, pos)
                }
            }
    }

    fun reachLayer(layerName: LayerName, pos: KeyPosition, activation: LayerActivation): LayerRef {
        val option = layerOptions[layerName] ?: throw IllegalArgumentException("unknown layer $layerName in $pos")
        val number = layerNumbers[layerName]
        if (number != null && activation != LayerActivation.Toggle) {
            assertTargetOrder(layerName, pos)
        }
        if (pos.layerName != layerName) {
            option.reachable[pos] = activation
        }

        return LayerRef(layerName, number, option)
    }

    fun assertTargetOrder(targetLayerName: LayerName, pos: KeyPosition) {
        if (layerNumbers.getValue(targetLayerName) < layerNumbers.getValue(pos.layerName))
            throw IllegalStateException("layer $targetLayerName is lower than $pos")
    }

    fun getKey(pos: KeyPosition): String =
        (keys[pos.layerName])?.get(pos.tableIndex)?.get(pos.row)?.get(pos.column) ?: ""

    fun gotKey(key: String, pos: KeyPosition) {
        gotKeys[key] = gotKeys.getOrDefault(key, mutableListOf()).apply { add(pos.layerName) }
    }
}

fun assertQmk(key: String, pos: KeyPosition): QmkKey {
    return when {
        key == comboTrigger || qmkPrefixes.any { key.startsWith(it) } -> QmkKey(key)
        else -> throw IllegalStateException("key not translated '$key' in $pos")
    }
}

val qmkPrefixes = setOf(
    "QK_",
    "DT_",
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
    "OSM(",
    "LSFT_T(",
    "RSFT_T(",
    "UP(",
    "UM(",
    "OS_TOGG",
)
