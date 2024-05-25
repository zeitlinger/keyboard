import org.hjson.JsonValue
import java.io.FileReader

const val qmkNo = "KC_NO"

class QmkTranslator(
    val symbols: Symbols,
    val layerOptions: Map<LayerName, LayerOption>,
    val nonThumbs: Map<LayerName, MultiTable>,
    val thumbs: Map<LayerName, MultiTable>,
    val layerNumbers: Map<LayerName, Int>,
    val options: Options,
    val layerTapHold: MutableList<String>,
    val combos: MutableList<Combo>,
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

    fun toQmk(key: String, pos: KeyPosition): String = key
        .let { symbols.replace(it, pos, this) }
        .let { translatedKey -> map.getOrDefault(translatedKey.replaceFirstChar { it.titlecase() }, translatedKey) }
        .let {
            when {
                getSubstitutionCombo(it) != null || symbols.customKeycodes.contains(it) -> it
                else -> assertQmk(it, pos)
            }
        }

    fun reachLayer(layerName: LayerName, pos: KeyPosition, activation: LayerActivation): LayerRef {
        val option = layerOptions[layerName] ?: throw IllegalArgumentException("unknown layer $layerName in $pos")
        val number = layerNumbers[layerName]
        if (number != null) {
            assertTargetOrder(layerName, pos)
        }
        if (pos.layerName != layerName) {
            option.reachable += activation
        }

        return LayerRef(layerName, number, option)
    }

    fun assertTargetOrder(targetLayerName: LayerName, pos: KeyPosition) {
        if (layerNumbers.getValue(targetLayerName) < layerNumbers.getValue(pos.layerName))
            throw IllegalStateException("layer $targetLayerName is lower than $pos")
    }

    fun getThumbContent(layerName: LayerName): MultiTable =
        thumbs[layerName] ?: listOf(listOf(List(options.thumbColumns) { "" })) // empty thumb layer

    fun getKey(pos: KeyPosition): String =
        (if (pos.thumb) getThumbContent(pos.layerName) else nonThumbs[pos.layerName])?.get(pos.tableIndex)?.get(pos.row)
            ?.get(pos.column) ?: ""

    fun gotKey(key: String) {
        symbols.gotKeys[key] = symbols.gotKeys.getOrDefault(key, 0) + 1
    }
}

fun assertQmk(key: String, pos: KeyPosition): String {
    return when {
        key == comboTrigger || qmkPrefixes.any { key.startsWith(it) } -> key
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
