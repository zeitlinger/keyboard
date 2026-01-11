import org.hjson.JsonValue
import java.io.FileReader

const val qmkNo = "KC_NO"

data class QmkKey(
    val key: String,
    val substitution: String?,
) {
    override fun toString(): String {
        return key
    }

    val isNo = key == qmkNo

    companion object {
        fun substitution(kay: String, substitutionCombo: String): QmkKey {
            return QmkKey(kay, substitutionCombo)
        }

        fun of(key: String): QmkKey {
            return QmkKey(key, null)
        }
    }
}

data class OneShotOnUpLayer(
    val down: LayerName,
    val up: LayerName,
    val activation: Key,
)

data class MagicInfo(
    val trigger: QmkKey,
    val press: MutableMap<QmkKey, String>,
) {
    constructor(trigger: String) : this(
        QmkKey.of(trigger),
        mutableMapOf(),
    )
}

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
    val magic: List<MagicInfo>,
    val oneShotOnUpLayer: MutableList<OneShotOnUpLayer>,
    val originalKeys: MutableMap<KeyPosition, QmkKey>,
) {

    private val map: Map<String, String>
    val nonSimpleKeys = mutableMapOf<String, String>()

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
                if (file.value == "aliases" && it.name.contains("(")) {
                    nonSimpleKeys[key] = it.name
                }
                key.takeUnless { it.contains("KP_") || it.contains("NONUS_") }?.let { o.get("label").asString() to it }
            }
        }.toMap()
    }

    fun toQmk(key: String, pos: KeyPosition): QmkKey {
        return key
            .let { symbols.replace(it, pos, this) }
            .let { translatedKey ->
                toQmkIgnoringPosition(translatedKey)
            }
            .let {
                val substitutionCombo = if (it.startsWith("\"") && it.endsWith("\"")) it else null
                when {
                    substitutionCombo != null -> QmkKey.substitution(it, substitutionCombo)
                    symbols.customKeycodes.contains(it) -> QmkKey.of(it)
                    else -> assertQmk(it, pos)
                }
            }
    }

    fun toQmkIgnoringPosition(translatedKey: String): String = map.getOrDefault(
        translatedKey.replaceFirstChar { it.titlecase() },
        translatedKey
    )

    fun reachLayer(layerName: LayerName, pos: KeyPosition, activation: LayerActivation): LayerRef {
        val option = layerOptions[layerName] ?: throw IllegalArgumentException("unknown layer $layerName in $pos")
        val number = layerNumbers[layerName]
        if (number != null && !activation.isToggle()) {
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
        if (pos.layerName == "Num" && !key.first().isDigit()) {
            // non-num keys are only in additional to other layers
            return
        }
        gotKeys[key] = gotKeys.getOrDefault(key, mutableListOf()).apply { add(pos.layerName) }
    }
}

fun assertQmk(key: String, pos: KeyPosition): QmkKey {
    return when {
        key == comboTrigger || qmkPrefixes.any { key.startsWith(it) } -> QmkKey.of(key)
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
