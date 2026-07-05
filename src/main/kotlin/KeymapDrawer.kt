import java.io.File

// Emits a keymap-drawer YAML (https://github.com/caksoylar/keymap-drawer) describing the layout,
// so `keymap draw` can render per-layer SVGs. Grid labels come from the README cells (already
// human-readable); combo badges come from the generated combo list.

private const val MAGIC_GLYPH = "✦"

// Emoji / multi-codepoint cells that don't render in the SVG font, mapped to plain glyphs.
private val GLYPHS =
    mapOf(
        "⬅️⬅️" to "home",
        "➡️➡️" to "end",
        "⬆️⬆️" to "pgup",
        "⬇️⬇️" to "pgdn",
        "⬅️" to "←",
        "➡️" to "→",
        "⬆️" to "↑",
        "⬇️" to "↓",
        "↩️️" to "⏎",
        "↩️" to "⏎",
        "pipe" to "|",
    )

// Auto-mod mechanics layers: they render as confusing near-empty deltas of the base layer (their
// modifiers come from the LayerOptions table, not from cells), so they're left out of the diagram.
// The README tables document them. Left/Right are kept: they're the shifted-letter layers and read
// cleanly when blank cells inherit the capitalized base letter.
private val SKIP_LAYERS = setOf("LMods", "RMods", "ANum", "CNum", "Case", "Vim")

private val UNICODE_NAMES =
    mapOf(
        "UMLAUT_A" to "ä",
        "UMLAUT_O" to "ö",
        "UMLAUT_U" to "ü",
        "UMLAUT_S" to "ß",
    )

// Always double-quote: keymap labels are short and full of YAML-hostile characters
// (=, <, >, -, ~, ?, #, :, brackets, quotes), so quoting unconditionally is safest.
private fun yamlScalar(s: String): String = "\"" + s.replace("\\", "\\\\").replace("\"", "\\\"") + "\""

// type is a keymap-drawer key class: null (normal), "held" (modifier / hold key, highlighted), or
// "actlayer" (the key you hold to reach this layer, colored distinctly via the config).
private data class DrawLabel(
    val text: String,
    val type: String? = null,
)

// Map a raw README cell to a display label.
// Blank for combo triggers (drawn as badges), blocked (🛑) and dead keys; ✦ for magic keys;
// the bare name for hold/layer prefixes (*Nav, $Num, @Sym, #Foo, >Base).
private fun cellLabel(raw: String): DrawLabel {
    val s = raw.trim()
    GLYPHS[s]?.let { return DrawLabel(it) }
    val blank = s.isEmpty() || s == COMBO_TRIGGER || s == LAYER_BLOCKED || s.startsWith("dead")
    return when {
        blank -> DrawLabel("")
        s.startsWith("magic_") -> DrawLabel(MAGIC_GLYPH)
        s.length > 1 && s[0] in setOf('*', '$', '@', '#', '>') -> DrawLabel(s.substring(1), "held")
        else -> DrawLabel(s)
    }
}

private fun fingerIdx(
    col: Int,
    columns: Int,
): Int = if (col >= columns / 2) columns - col - 1 else col

private fun modLabel(m: Modifier): String = if (m == Modifier.Meta) "Gui" else m.name

// Every key held to reach this layer, following chained activations: a key that activates this
// layer may itself live on another layer (e.g. Media is reached from within the Left layer), so we
// recurse into that host layer's activation keys too.
private fun activationPositions(
    layer: Layer,
    byName: Map<String, Layer>,
    seen: MutableSet<String> = mutableSetOf(),
): List<KeyPosition> {
    if (!seen.add(layer.name)) return emptyList()
    val result = mutableListOf<KeyPosition>()
    for ((pos, act) in layer.option.reachable) {
        if (act == LayerActivation.Hidden) continue
        result += pos
        val host = pos.layerName
        if (host != BASE_LAYER_NAME && host != layer.name) {
            byName[host]?.let { result += activationPositions(it, byName, seen) }
        }
    }
    return result
}

// The home-row (or other) modifier this layer puts at (row, col), per the LayerOptions table.
private fun layerModifier(
    layer: Layer,
    row: Int,
    col: Int,
    translator: QmkTranslator,
): Modifier? {
    val cols = translator.options.nonThumbColumns
    val modMap = if (col < cols / 2) layer.option.leftModifier else layer.option.rightModifier
    if (modMap.keys.none { it.row == row }) return null
    return translator.options.homeRowPositions?.get(fingerIdx(col, cols))
}

// keymap-drawer position index for the physical ferris/sweep (LAYOUT_split_3x5_2): 5 columns per
// hand, row-major (0..4 left, 5..9 right) for rows 0..2, then thumbs 30..33. Our grid drops the
// inner columns, so left cols 0..3 -> 0..3 and right cols 4..7 -> 6..9 (physical inner columns 4
// and 5 stay blank); thumb row (row 3) cols 2..5 -> 30..33.
private fun kdIndex(
    row: Int,
    col: Int,
): Int? =
    when {
        row in 0..2 && col in 0..3 -> row * 10 + col
        row in 0..2 && col in 4..7 -> row * 10 + col + 2
        row == 3 && col in 2..5 -> 30 + (col - 2)
        else -> null
    }

private fun kdIndex(pos: KeyPosition): Int? = kdIndex(pos.row, pos.column)

// A "vertical" combo joins two stacked keys in the same column on adjacent main rows; it reads
// cleanly as a badge between the keys. Horizontal/diagonal/"direct" combos look confusing, so we
// skip those (they're documented in the README).
private fun isVerticalCombo(combo: Combo): Boolean {
    if (combo.triggers.size != 2) return false
    val a = combo.triggers[0].pos
    val b = combo.triggers[1].pos
    return a.column == b.column && a.row in 0..2 && b.row in 0..2 && kotlin.math.abs(a.row - b.row) == 1
}

private fun comboLabel(combo: Combo): String {
    val authored = combo.authored.trim()
    GLYPHS[authored]?.let { return it }
    if (authored.startsWith("magic_")) return MAGIC_GLYPH
    return authored.trim('"')
}

fun writeKeymapDrawerYaml(
    dst: File,
    visibleLayers: List<Layer>,
    combos: List<Combo>,
    translator: QmkTranslator,
) {
    val sb = StringBuilder()
    sb.appendLine("# Generated for keymap-drawer (https://github.com/caksoylar/keymap-drawer).")
    sb.appendLine("# Render with: keymap draw <this file>")
    sb.appendLine("layout:")
    sb.appendLine("  qmk_keyboard: ferris/sweep")
    sb.appendLine("layers:")
    val byName = visibleLayers.associateBy { it.name }
    val cols = translator.options.nonThumbColumns
    for (layer in visibleLayers.filterNot { it.name in SKIP_LAYERS }) {
        val rawTable = translator.keys[layer.name]?.firstOrNull()
        sb.appendLine("  ${yamlScalar(layer.name)}:")

        fun cellAt(
            r: Int,
            c: Int,
        ): String = rawTable?.getOrNull(r)?.getOrNull(c) ?: ""

        // Letters from the fallback layer (per LayerOptions Fallback Left/Right) are inherited on
        // their side and capitalized when this layer is a shifted-letter layer (Left/Right).
        val shifted = LayerFlag.Shifted in layer.option.flags

        fun labelAt(
            r: Int,
            c: Int,
        ): DrawLabel {
            val own = cellLabel(cellAt(r, c))
            if (own.text.isNotEmpty()) return own
            val pos = KeyPosition(0, r, c, layer.name, cols)
            val fb = fallbackLayer(pos, layer.option)?.let { translator.keys[it]?.firstOrNull() } ?: return own
            val raw =
                fb
                    .getOrNull(r)
                    ?.getOrNull(c)
                    ?.trim()
                    .orEmpty()
            if (raw.length == 1 && raw[0].isLetter() && raw[0].isLowerCase()) {
                return DrawLabel(if (shifted) raw.uppercase() else raw)
            }
            return own
        }
        // 34 physical slots; inner columns (indices 4,5 of each row) stay blank.
        val slots = arrayOfNulls<DrawLabel>(34)
        for (r in 0..2) {
            for (c in 0..3) slots[r * 10 + c] = labelAt(r, c)
            for (c in 4..7) slots[r * 10 + c + 2] = labelAt(r, c)
        }
        for (c in 2..5) slots[30 + (c - 2)] = labelAt(3, c)
        // Overlay the modifiers this layer places on its rows (from the LayerOptions table) — those
        // show up as 🛑/blank cells otherwise.
        for (r in 0..2) {
            for (c in 0..7) {
                layerModifier(layer, r, c, translator)?.let { mod ->
                    kdIndex(r, c)?.let { idx -> slots[idx] = DrawLabel(modLabel(mod), "held") }
                }
            }
        }
        // Overlay every key held to reach this layer — including chained activations (e.g. Media is
        // reached from within the Left layer, which itself needs a held key) — highlighted in the
        // base layer's held color but left blank (no label), so the whole hold-combination is visible.
        for (pos in activationPositions(layer, byName)) {
            kdIndex(pos)?.let { idx -> slots[idx] = DrawLabel("", "held") }
        }
        for (slot in slots) {
            val label = slot ?: DrawLabel("")
            if (label.type != null) {
                sb.appendLine("    - {t: ${yamlScalar(label.text)}, type: ${label.type}}")
            } else {
                sb.appendLine("    - ${yamlScalar(label.text)}")
            }
        }
    }

    // Draw clean vertical (stacked) combos on every shown layer except Media. Skips the confusing
    // horizontal/diagonal/"direct" combos; the README documents those.
    val ownDrawn =
        combos
            .filter { it.homeLayer !in SKIP_LAYERS && it.homeLayer != "Media" && isVerticalCombo(it) }
            .mapNotNull { combo ->
                if (combo.triggers.size != 2) return@mapNotNull null
                val idx = combo.triggers.mapNotNull { kdIndex(it.pos) }
                if (idx.size != 2) return@mapNotNull null
                Triple(idx.sorted(), comboLabel(combo), combo.homeLayer)
            }
    // Inherit combos from a layer's fallback side (e.g. Base letter-combos on Left's left hand),
    // uppercased when the host layer is Shifted. Both triggers must be on the same side as the
    // matching fallback column in LayerOptions.
    val inherited =
        visibleLayers
            .filterNot { it.name in SKIP_LAYERS }
            .flatMap { host ->
                val hostShifted = LayerFlag.Shifted in host.option.flags
                combos
                    .filter { it.homeLayer != host.name && isVerticalCombo(it) && it.triggers.size == 2 }
                    .mapNotNull { combo ->
                        val triggerPos = combo.triggers[0].pos.copy(layerName = host.name, columns = cols)
                        if (combo.triggers[1].pos.column != triggerPos.column) return@mapNotNull null
                        if (fallbackLayer(triggerPos, host.option) != combo.homeLayer) return@mapNotNull null
                        val raw = combo.authored.trim().trim('"')
                        if (raw.length != 1 || !raw[0].isLetter() || !raw[0].isLowerCase()) return@mapNotNull null
                        val idx = combo.triggers.mapNotNull { kdIndex(it.pos) }
                        if (idx.size != 2) return@mapNotNull null
                        Triple(idx.sorted(), if (hostShifted) raw.uppercase() else raw, host.name)
                    }
            }
    val drawn = ownDrawn + inherited
    if (drawn.isNotEmpty()) {
        sb.appendLine("combos:")
        for ((idx, label, homeLayer) in drawn) {
            sb.appendLine(
                "  - {p: [${idx[0]}, ${idx[1]}], k: ${yamlScalar(label)}, layers: [${yamlScalar(homeLayer)}]}",
            )
        }
    }
    val content = sb.toString()
    if (dst.exists() && dst.readText() == content) {
        System.err.println("unchanged ${dst.path}")
        return
    }
    dst.writeText(content)
    System.err.println("wrote ${dst.path}")
}
