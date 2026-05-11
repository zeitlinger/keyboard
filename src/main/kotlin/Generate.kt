import java.io.File

const val MAIN_LAYER_TEMPLATE_4_COLUMNS =
    "\t[%s] = LAYOUT_split_3x5_2(\n" +
        "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
        "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
        "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
        "                            %s, %s, %s, %s),"

const val MAIN_LAYER_TEMPLATE_5_COLUMNS =
    "\t[%s] = LAYOUT_split_3x5_2(\n" +
        "            %s, %s, %s, %s, %s, %s, %s, %s, %s, %s,\n" +
        "            %s, %s, %s, %s, %s, %s, %s, %s, %s, %s,\n" +
        "            %s, %s, %s, %s, %s, %s, %s, %s, %s, %s,\n" +
        "                            %s, %s, %s, %s),"

fun template(layers: List<Layer>): String =
    layers[0].rows[0].size.let { columns ->
        when (columns) {
            10 -> MAIN_LAYER_TEMPLATE_5_COLUMNS
            8 -> MAIN_LAYER_TEMPLATE_4_COLUMNS
            else -> throw IllegalStateException("unsupported number of columns $columns")
        }
    }

private const val THUMB_COLUMNS = 4
private const val NO_CYCLE_OFFSET = "MAGIC_CYCLE_NONE"
private const val MAGIC_REPLACE_PREFIX = "⌫"

private data class CycleEntry(
    val current: String,
    val next: String,
    val currentOffset: Int,
    val nextOffset: Int,
    val commonPrefixLength: Int,
    val nextLastChar: Char,
)

private data class CycleData(
    val entries: List<CycleEntry>,
    val outputs: Set<String>,
)

fun generateBase(layers: List<Layer>): String {
    val template = template(layers)
    return layers
        .sortedBy { it.number }
        .joinToString("\n") { layer ->
            template.format(
                *listOf(layer.name.const())
                    .plus(
                        layer.rows
                            .mapIndexed { index, row ->
                                if (index == layer.rows.size - 1) {
                                    row.drop(2).take(THUMB_COLUMNS - 2) +
                                        row
                                            .drop(row.size - 2 - (THUMB_COLUMNS / 2))
                                            .take(THUMB_COLUMNS - 2)
                                } else {
                                    row
                                }.map {
                                    val key = it.keyWithModifier
                                    if (key.substitution != null) {
                                        throw IllegalStateException(
                                            "substitutionCombo not supported in base layer: $key",
                                        )
                                    } else {
                                        key.key.padStart(
                                            20,
                                        )
                                    }
                                }
                            }.flatten(),
                    ).toTypedArray(),
            )
        }
}

fun triLayer(
    layer: Layer,
    translator: QmkTranslator,
): String {
    val reachable = layer.option.reachable
    if (reachable.size != 2) {
        throw IllegalStateException("triLayer must have exactly 2 reachable layers: $reachable")
    }
    if (reachable.values.any { it != LayerActivation.Hold }) {
        throw IllegalStateException("triLayer must have hold activation: $reachable")
    }
    return listOf(
        "#define TRI_LAYER_LOWER_LAYER ${translator.layerNumbers.getValue(reachable.keys.first().layerName)}",
        "#define TRI_LAYER_UPPER_LAYER ${translator.layerNumbers.getValue(reachable.keys.last().layerName)}",
        "#define TRI_LAYER_ADJUST_LAYER ${translator.layerNumbers.getValue(layer.name)}",
    ).joinToString("\n")
}

fun run(args: GeneratorArgs) {
    val tables = readTables(args.configFile.file)
    val translator = qmkTranslator(tables)
    validateMagicWords(tables, translator)

    val layers =
        addSendString(
            translator.layerOptions.entries.map { (layerName, _) ->
                val table =
                    translator.keys[layerName]
                        ?: listOf(List(translator.options.rows) { List(translator.options.nonThumbColumns) { "" } })
                readLayer(table, translator, layerName, translator.layerNumbers.getOrDefault(layerName, -1))
            },
            translator,
        )

    val combos = translator.combos + generateAllCombos(layers, translator)

    val cycleData = readCycleData(tables)
    val subsStrings =
        combos
            .filter { it.type == ComboType.Substitution }
            .map { unquoteSubsString(it.result.substitution!!) }
    val encodedMagicStrings =
        encodeStrings(collectMagicOutputs(tables, translator) + cycleData.outputs + subsStrings)
    val encodedCycles = encodeCycleEntries(cycleData, encodedMagicStrings.stringOffsets)

    val magicTable = tables.getOptional("Magic").orEmpty()
    magicRows(magicTable).let {
        it.forEachIndexed { index, row ->
            val pos = KeyPosition(0, index, 0, "magic", 0)
            addMagic(
                translator,
                row,
                pos,
                encodedMagicStrings.stringOffsetConstants,
                encodedCycles,
            )
        }
    }

    tables.getOptional("Adaptives")?.let {
        it.forEachIndexed { index, row ->
            val pos = KeyPosition(0, index, 0, "adaptives", 0)
            val after = translator.toQmk(row[0], pos)
            val key = translator.toQmk(row[1], pos)
            val output = translator.toQmk(row[2], pos)
            val seen = translator.adaptives.map { it.key to it.after }.toSet()
            check(key to after !in seen) {
                "Duplicate adaptive at row ${index + 1}: key=$key after=$after"
            }
            translator.adaptives.add(AdaptiveRule(key, after, output))
        }
    }

    val srcDir = args.generatorDir.file
    val dstDir = args.dstDir
    val generationNote =
        "file is generated from ${GIT_TEMPLATE.format(args.configFile.file.name)}"

    val userKeycodes =
        translator.symbols.customKeycodes.keys
            .toList()
    val visible =
        layers.filter {
            val reachable = translator.layerOptions.getValue(it.name).reachable
            reachable.isEmpty() || reachable.any { it.value != LayerActivation.Hidden }
        }
    replaceTemplate(
        File(srcDir, "config.h"),
        File(dstDir, "config.h"),
        mapOf(
            "triLayer" to (
                layers
                    .singleOrNull { LayerFlag.TriLayer in it.option.flags }
                    ?.let { triLayer(it, translator) } ?: ""
            ),
            "comboCount" to combos.size.toString(),
            "baseLayerNumber" to translator.layerNumbers.getValue(BASE_LAYER_NAME).toString(),
        ),
    )
    replaceTemplate(
        File(srcDir, "layout.h"),
        File(dstDir, "layout.h"),
        mapOf(
            "generationNote" to generationNote,
            "versionString" to args.versionString,
            "layers" to generateBase(visible),
            "layerNumbers" to
                translator.layerNumbers.entries
                    .joinToString("\n") {
                        "#define ${it.key.const()} ${it.value}"
                    },
            "custom0" to userKeycodes[0],
            "customRest" to userKeycodes.drop(1).joinToString(",\n    "),
            "customHandlers" to
                translator.symbols.customKeycodes.entries
                    .joinToString("\n") {
                        "#define _HANDLER_${it.key} ${it.value.key}"
                    },
        ),
    )

    replaceTemplate(
        File(srcDir, "generated.c"),
        File(dstDir, "generated.c"),
        mapOf(
            "generationNote" to generationNote,
            "customKeycodesOnTapPress" to customKeycodes(translator, CustomCommandType.OnTap),
            "customKeycodesOnPress" to customKeycodes(translator, CustomCommandType.OnPress),
            "holdOnOtherKeyPress" to holdOnOtherKeyPress(translator.layerTapHold.toSet()),
            "magicStringDecoder" to (encodedMagicStrings.decoder ?: ""),
            "magicCycleData" to magicCycleData(encodedCycles, encodedMagicStrings.stringOffsetConstants),
            "magic" to translator.magic.map { magicCase(it) }.indented(8),
            "magicSuffixes" to magicSuffixCases(translator, magicTable).prependIndent("    "),
            "magicExclusions" to translator.magic.map { "case ${it.trigger.key}:" }.indented(8),
            "magicRepeats" to magicRepeatCases(translator),
            "adaptives" to adaptiveBlocks(translator.adaptives).indented(12),
        ),
    )

    if (args.printStats) {
        analyze(translator, layers)
    }

    File(dstDir, "combos.c").writeText(
        emitCombosC(combos, generationNote, encodedMagicStrings.stringOffsets),
    )
    File(dstDir, "combos.def").delete()
}

private fun unquoteSubsString(quoted: String): String {
    require(quoted.length >= 2 && quoted.startsWith("\"") && quoted.endsWith("\"")) {
        "SUBS string must be quoted: $quoted"
    }
    return quoted
        .substring(1, quoted.length - 1)
        .replace("\\\"", "\"")
        .replace("\\\\", "\\")
}

private data class MagicWordLocation(
    val precedingChar: String,
    val trigger: String,
)

private data class MagicSpec(
    val forceReplace: Boolean,
    val resolvedDef: String,
)

private fun magicRows(table: Table): Table = table.filterNot(::isMagicSuffixRow)

private fun isMagicSuffixRow(row: List<String>): Boolean =
    row.firstOrNull()?.equals("suffix", ignoreCase = true) == true

private fun magicSuffixCases(
    translator: QmkTranslator,
    magicTable: Table,
): String {
    val suffixRow = magicTable.singleOrNull(::isMagicSuffixRow) ?: return ""
    return suffixRow
        .drop(1)
        .mapIndexedNotNull { index, suffix ->
            if (suffix.isBlank()) {
                null
            } else {
                val magic =
                    translator.magic.getOrNull(index)
                        ?: throw IllegalArgumentException(
                            "suffix cell has no matching magic key at column ${index + 2}",
                        )
                val statements = magicSuffixStatements(suffix.trim())
                val handled = if (isBracketToken(suffix.trim())) "" else "\n    return true;"
                "case ${magic.trigger.key}:\n" +
                    statements.prependIndent("    ") +
                    handled
            }
        }.joinToString("\n")
}

private fun magicSuffixStatements(suffix: String): String {
    if (isBracketToken(suffix)) {
        return suffixBracketCommand(suffix.removeSurrounding("[", "]"))
    }
    if (isWord(suffix)) {
        val literal = extractString(suffix)
        val taps = literal.map(::suffixTapStatement).joinToString(" ")
        return """
            tap_code16(KC_BSPC); $taps
            clear_suffix_state();
            """.trimIndent()
    }
    return when (suffix) {
        "." -> {
            """
            tap_code16(KC_BSPC); tap_dot_space();
            add_oneshot_mods(MOD_BIT(KC_LSFT));
            clear_suffix_state();
            """.trimIndent()
        }

        "," -> {
            """
            tap_code16(KC_BSPC); tap_comma_space();
            clear_suffix_state();
            """.trimIndent()
        }

        "n't" -> {
            """
            tap_code16(KC_BSPC); tap_n_t(); tap_code16(KC_SPC);
            last_magic_char = 't';
            clear_suffix_cycle_state();
            """.trimIndent()
        }

        "ed" -> {
            """
            tap_code16(KC_BSPC);
            if (last_magic_char == 'e') {
                tap_code16(KC_D); tap_code16(KC_SPC);
            } else {
                tap_code16(KC_E); tap_code16(KC_D); tap_code16(KC_SPC);
            }
            last_magic_char = 'd';
            clear_suffix_cycle_state();
            """.trimIndent()
        }

        else -> {
            val taps = suffix.map(::suffixTapStatement).joinToString(" ")
            """
            tap_code16(KC_BSPC); $taps tap_code16(KC_SPC);
            last_magic_char = '${suffix.last()}';
            clear_suffix_cycle_state();
            """.trimIndent()
        }
    }
}

private fun suffixBracketCommand(name: String): String =
    when (name) {
        "next" -> "return process_magic_cycle_next();"
        else -> throw IllegalArgumentException("unknown suffix bracket token '[$name]'")
    }

private fun suffixTapStatement(char: Char): String =
    when (char) {
        ' ' -> "tap_code16(KC_SPC);"
        '\'' -> "tap_code16(KC_QUOTE);"
        '"' -> "tap_code16(KC_DQUO);"
        '!' -> "tap_code16(KC_EXLM);"
        '?' -> "tap_code16(KC_QUES);"
        ',' -> "tap_code16(KC_COMMA);"
        '.' -> "tap_code16(KC_DOT);"
        in 'a'..'z' -> "tap_code16(KC_${char.uppercaseChar()});"
        in 'A'..'Z' -> "tap_code16(S(KC_$char));"
        else -> throw IllegalArgumentException("unsupported suffix character '$char'")
    }

private fun magicCase(magic: MagicInfo): String =
    """
    case ${magic.trigger.key}: {
        if (allow_repeat && repeat_last_magic_key(${magic.trigger.key})) {
            return false;
        }
        magic_remembered_keycode = ${magic.trigger.key};
        magic_repeat_keycode = KC_NO;
        switch (magic_prepare_last_keycode(context_keycode)) {
${magicSwitch(magic.press)}
        }
        magic_capitalize_next = false;
        last_magic_trigger = ${magic.trigger.key};
        last_magic_repeat_keycode = magic_repeat_keycode;
        set_last_keycode(magic_remembered_keycode);
        return false;
    }
    """.trimIndent()

private fun magicRepeatCases(translator: QmkTranslator): String =
    translator.magic
        .joinToString("\n") { magic ->
            "case ${magic.trigger.key}: return repeat_last_magic_key(${magic.trigger.key});"
        }

private fun adaptiveBlocks(rules: List<AdaptiveRule>): List<String> =
    rules.groupBy { it.key }.map { (key, entries) ->
        val cases =
            entries
                .sortedBy { it.after.key }
                .joinToString("\n") { "        case ${it.after}: return tap_adaptive($key, ${it.output});" }
        "case $key:\n    switch (adaptive_prev_keycode) {\n$cases\n    }\n    break;"
    }

private fun magicSwitch(map: MutableMap<QmkKey, MagicCommand>): String =
    map.entries
        .sortedBy { it.key.key }
        .map {
            val remember = it.value.rememberedKeycode?.let { keycode -> " magic_remembered_keycode = $keycode;" } ?: ""
            val repeat = it.value.repeatKeycode?.let { keycode -> " magic_repeat_keycode = $keycode;" } ?: ""
            if (it.value.rememberedKeycode != null && it.value.rememberedKeycode == it.value.repeatKeycode) {
                "case ${it.key}: ${it.value.statements} break;"
            } else {
                "case ${it.key}: ${it.value.statements}$remember$repeat break;"
            }
        }.indented(12)

fun addSendString(
    layers: List<Layer>,
    translator: QmkTranslator,
): List<Layer> =
    layers.map {
        it.copy(
            rows =
                it.rows.map { row ->
                    row.map { key ->
                        val substitution = key.key.substitution
                        if (substitution != null) {
                            val name = "ST_${key.pos.layerName}_${key.pos.row}_${key.pos.column}".uppercase()
                            val command =
                                customCommand(
                                    translator,
                                    QmkKey.of(name),
                                    CustomCommandType.OnPress,
                                    listOf(sendString(substitution)),
                                    key.key,
                                )
                            translator.ignoreMissing.add(key.key)

                            key.copy(key = command, keyWithModifier = command)
                        } else {
                            key
                        }
                    }
                },
        )
    }

private fun emitCombosC(
    combos: List<Combo>,
    generationNote: String,
    stringOffsets: Map<String, Int>,
): String {
    val sorted = combos.sortedBy { it.name }
    val enum =
        "enum combos {\n" +
            sorted.joinToString(",\n") { "    ${it.name}" } +
            "\n};"

    // Letter combos (output is a single basic letter on _BASE) need
    // layer-aware emission so that shifted layers produce shifted output.
    fun isLetterCombo(combo: Combo): Boolean =
        combo.type == ComboType.Combo &&
            combo.name.startsWith("C_BASE_") &&
            isLetter(combo.result)

    val emitCases =
        sorted.filter { it.type == ComboType.Substitution }.map { combo ->
            val raw = unquoteSubsString(combo.result.substitution!!)
            val offset = stringOffsets.getValue(raw)
            "    case ${combo.name}: magic_decode_send($offset); break; // ${combo.result.substitution}"
        } +
            sorted.filter { isLetterCombo(it) }.map { combo ->
            val base = combo.result.key
            "    case ${combo.name}: custom_combo_tap_keycode(layer == _LEFT ? S($base) : $base); break;"
        } +
            sorted
                .filter { it.type != ComboType.Substitution && !isLetterCombo(it) }
                .map { combo ->
                    "    case ${combo.name}: custom_combo_tap_keycode(${combo.result.key}); break;"
                }

    val metadata =
        "typedef struct {\n" +
            "    uint16_t index;\n" +
            "    uint8_t row1;\n" +
            "    uint8_t col1;\n" +
            "    uint8_t row2;\n" +
            "    uint8_t col2;\n" +
            "    uint8_t home_layer;\n" +
            "    bool allow_left;\n" +
            "    uint16_t term;\n" +
            "} positional_combo_t;\n\n" +
            "static const positional_combo_t positional_combos[] = {\n" +
            sorted.joinToString(",\n") { combo ->
                val a = combo.triggers[0].pos
                val b = combo.triggers[1].pos
                val allowLeft =
                    combo.homeLayer == BASE_LAYER_NAME &&
                        combo.type == ComboType.Combo &&
                        isLetter(combo.result)
                "    {${combo.name}, ${a.row}, ${a.column}, ${b.row}, ${b.column}, _${combo.homeLayer.uppercase()}, ${if (allowLeft) "true" else "false"}, ${combo.timeout ?: 0}}"
            } +
            "\n};"

    val emitFunction =
        "static void emit_custom_combo(uint16_t combo_index) {\n" +
            "    switch (combo_index) {\n" +
            emitCases.joinToString("\n") +
            "\n    default: break;\n" +
            "    }\n}"

    val customMatcher =
        """
static bool custom_combo_replaying = false;
static bool custom_combo_pending = false;
static bool custom_combo_pending_passthrough = false;
static keyrecord_t custom_combo_pending_record;
static uint16_t custom_combo_pending_keycode = KC_NO;
static uint16_t custom_combo_pending_timer = 0;
static uint16_t custom_combo_pending_term = 0;

static bool custom_combo_active = false;
static keypos_t custom_combo_active_keys[2];
static bool custom_combo_active_down[2] = {false, false};
static bool custom_combo_swallow_release[2] = {false, false};

static bool custom_combo_keypos_equal(keypos_t a, keypos_t b) {
    return a.row == b.row && a.col == b.col;
}

static bool custom_combo_allows_layer(const positional_combo_t *combo) {
    return layer == combo->home_layer || (combo->allow_left && layer == _LEFT);
}

static bool custom_combo_contains_pos(const positional_combo_t *combo, keypos_t key) {
    return (combo->row1 == key.row && combo->col1 == key.col)
        || (combo->row2 == key.row && combo->col2 == key.col);
}

static uint16_t custom_combo_term_for_key(keypos_t key) {
    uint16_t best = 0;
    for (uint16_t i = 0; i < ARRAY_SIZE(positional_combos); ++i) {
        const positional_combo_t *combo = &positional_combos[i];
        if (custom_combo_allows_layer(combo) && custom_combo_contains_pos(combo, key) && combo->term > best) {
            best = combo->term;
        }
    }
    return best;
}

static bool custom_combo_has_candidate(keypos_t key) {
    return custom_combo_term_for_key(key) > 0;
}

static int16_t custom_combo_find_match(keypos_t a, keypos_t b) {
    for (uint16_t i = 0; i < ARRAY_SIZE(positional_combos); ++i) {
        const positional_combo_t *combo = &positional_combos[i];
        if (!custom_combo_allows_layer(combo)) {
            continue;
        }
        const bool forward = combo->row1 == a.row && combo->col1 == a.col && combo->row2 == b.row && combo->col2 == b.col;
        const bool reverse = combo->row1 == b.row && combo->col1 == b.col && combo->row2 == a.row && combo->col2 == a.col;
        if (forward || reverse) {
            return combo->index;
        }
    }
    return -1;
}

static bool custom_combo_key_must_passthrough(uint16_t keycode) {
    return (QK_MOMENTARY <= keycode && keycode <= QK_MOMENTARY_MAX)
        || (QK_LAYER_TAP <= keycode && keycode <= QK_ONE_SHOT_LAYER_MAX);
}

static void custom_combo_dispatch_record(keyrecord_t record, uint16_t keycode) {
    custom_combo_replaying = true;
    record.keycode = keycode;
#ifndef NO_ACTION_TAPPING
    action_tapping_process(record);
#else
    process_record(&record);
#endif
    custom_combo_replaying = false;
}

static void custom_combo_tap_keycode(uint16_t keycode) {
    keyrecord_t press = {
        .event = {
            .key = (keypos_t){0, 0},
            .pressed = true,
            .time = timer_read()
        },
        .tap = {
            .count = 0,
            .interrupted = false
        }
    };
    keyrecord_t release = press;
    release.event.pressed = false;
    release.event.time = timer_read();
    custom_combo_dispatch_record(press, keycode);
    custom_combo_dispatch_record(release, keycode);
}

static void custom_combo_clear_pending(void) {
    custom_combo_pending = false;
    custom_combo_pending_passthrough = false;
    custom_combo_pending_keycode = KC_NO;
    custom_combo_pending_timer = 0;
    custom_combo_pending_term = 0;
}

static void custom_combo_flush_pending_press(void) {
    if (!custom_combo_pending) {
        return;
    }
    if (!custom_combo_pending_passthrough) {
        custom_combo_dispatch_record(custom_combo_pending_record, custom_combo_pending_keycode);
    }
    custom_combo_clear_pending();
}

bool process_custom_combo(uint16_t keycode, keyrecord_t *record) {
    if (custom_combo_replaying) {
        return true;
    }

    keypos_t key = record->event.key;

    if (custom_combo_active && !record->event.pressed) {
        for (uint8_t i = 0; i < 2; ++i) {
            if (custom_combo_active_down[i] && custom_combo_keypos_equal(custom_combo_active_keys[i], key)) {
                custom_combo_active_down[i] = false;
                const bool swallow = custom_combo_swallow_release[i];
                if (!custom_combo_active_down[0] && !custom_combo_active_down[1]) {
                    custom_combo_active = false;
                }
                return !swallow;
            }
        }
    }

    if (custom_combo_pending && custom_combo_pending_term > 0
        && timer_elapsed(custom_combo_pending_timer) > custom_combo_pending_term) {
        custom_combo_flush_pending_press();
    }

    if (!record->event.pressed) {
        if (custom_combo_pending && custom_combo_keypos_equal(custom_combo_pending_record.event.key, key)) {
            if (!custom_combo_pending_passthrough) {
                custom_combo_dispatch_record(custom_combo_pending_record, custom_combo_pending_keycode);
            }
            custom_combo_clear_pending();
        }
        return true;
    }

    if (custom_combo_pending) {
        int16_t combo_index = custom_combo_find_match(custom_combo_pending_record.event.key, key);
        if (combo_index >= 0) {
            emit_custom_combo((uint16_t)combo_index);
            custom_combo_active = true;
            custom_combo_active_keys[0] = custom_combo_pending_record.event.key;
            custom_combo_active_keys[1] = key;
            custom_combo_active_down[0] = true;
            custom_combo_active_down[1] = true;
            custom_combo_swallow_release[0] = !custom_combo_pending_passthrough;
            custom_combo_swallow_release[1] = true;
            custom_combo_clear_pending();
            return false;
        }

        custom_combo_flush_pending_press();
    }

    if (!custom_combo_has_candidate(key)) {
        return true;
    }

    custom_combo_pending = true;
    custom_combo_pending_passthrough = custom_combo_key_must_passthrough(keycode);
    custom_combo_pending_record = *record;
    custom_combo_pending_keycode = keycode;
    custom_combo_pending_timer = timer_read();
    custom_combo_pending_term = custom_combo_term_for_key(key);
    return custom_combo_pending_passthrough;
}

void custom_combo_task(void) {
    if (custom_combo_pending && !custom_combo_pending_passthrough && custom_combo_pending_term > 0
        && timer_elapsed(custom_combo_pending_timer) > custom_combo_pending_term) {
        custom_combo_flush_pending_press();
    }
}
        """.trimIndent()

    return listOf(
        "// $generationNote",
        "#include QMK_KEYBOARD_H",
        "#include \"action_tapping.h\"",
        "#include \"layout.h\"",
        "#include \"unicode_names.h\"",
        "",
        "// Defined in generated.c.",
        "void magic_decode_send(uint16_t offset);",
        "extern int layer;",
        "",
        enum,
        "",
        metadata,
        "",
        emitFunction,
        "",
        customMatcher,
        "",
    ).joinToString("\n")
}

private fun addMagic(
    translator: QmkTranslator,
    row: List<String>,
    pos: KeyPosition,
    stringOffsetConstants: Map<String, String>,
    cycleData: List<CycleEntry>,
) {
    val precedingChar = row[0]
    val base = translator.toQmk(precedingChar, pos)
    row.drop(1).forEachIndexed { index, def ->
        if (def.isNotBlank()) {
            addMagicEntry(
                translator,
                pos,
                translator.magic[index].press,
                base,
                precedingChar,
                def,
                stringOffsetConstants,
                cycleData,
            )
        }
    }
}

private fun addMagicEntry(
    translator: QmkTranslator,
    pos: KeyPosition,
    map: MutableMap<QmkKey, MagicCommand>,
    base: QmkKey,
    precedingChar: String,
    def: String,
    stringOffsetConstants: Map<String, String>,
    cycleData: List<CycleEntry>,
) {
    map[base] = magicCommand(translator, pos, base, precedingChar, def, stringOffsetConstants, cycleData)
}

private fun magicCommand(
    translator: QmkTranslator,
    pos: KeyPosition,
    base: QmkKey,
    precedingChar: String,
    def: String,
    stringOffsetConstants: Map<String, String>,
    cycleData: List<CycleEntry>,
): MagicCommand {
    val spec = parseMagicSpec(def, translator, pos)
    val resolvedDef = spec.resolvedDef
    return when {
        isBracketToken(resolvedDef) -> {
            val bracketName = resolvedDef.removeSurrounding("[", "]")
            MagicCommand(
                bracketCommand(bracketName, pos, stringOffsetConstants),
                reverseSafe = bracketName == "dotSpc",
            )
        }

        translator.symbols.customKeycodes.contains(resolvedDef) || qmkPrefixes.any { resolvedDef.startsWith(it) } -> {
            magicTapCommand(QmkKey.of(resolvedDef), precedingChar, replaceable = true, forceReplace = spec.forceReplace)
        }

        resolvedDef.length == 1 -> {
            val qmk = translator.toQmk(resolvedDef, pos)
            val isLetterOutput = resolvedDef[0].isLetter()
            magicTapCommand(qmk, precedingChar, replaceable = !isLetterOutput, forceReplace = spec.forceReplace)
        }

        isWord(resolvedDef) || isBareWord(resolvedDef) -> {
            val quoted = isWord(resolvedDef)
            val str = if (quoted) extractString(resolvedDef) else resolvedDef
            val output = if (quoted) str else "$str "
            val prevIsLetter = precedingChar.length == 1 && precedingChar[0].isLetter()
            val outputStartsWithPreceding = prevIsLetter && output.startsWith(precedingChar)
            val shouldReplace = !outputStartsWithPreceding && (spec.forceReplace || prevIsLetter)
            val emitted =
                if (outputStartsWithPreceding) {
                    output.drop(precedingChar.length)
                } else {
                    output
                }
            val suffix = if (quoted) "'\\0'" else "'${str.last()}'"
            val offset = stringOffsetConstants.getValue(emitted)
            val cycleOffset =
                if (quoted) {
                    NO_CYCLE_OFFSET
                } else {
                    cycleLiteral(output, cycleData, stringOffsetConstants)
                }
            val send =
                if (outputStartsWithPreceding) {
                    if (quoted) {
                        annotateMagicSend("magic_decode_send($offset);", emitted, output)
                    } else {
                        annotateMagicSend(
                            "magic_decode_send_suffix_cycle($offset, $suffix, $cycleOffset);",
                            emitted,
                            output,
                        )
                    }
                } else if (shouldReplace) {
                    annotateMagicSend(
                        "magic_replace_decode_send_cap_cycle($offset, $suffix, $cycleOffset);",
                        emitted,
                        output,
                    )
                } else {
                    annotateMagicSend("magic_decode_send_cap_cycle($offset, $suffix, $cycleOffset);", emitted, output)
                }
            MagicCommand(send, reverseSafe = shouldReplace)
        }

        else -> {
            throw IllegalArgumentException("unknown command '$resolvedDef' in $pos")
        }
    }
}

private fun magicTapCommand(
    qmk: QmkKey,
    precedingChar: String,
    replaceable: Boolean,
    forceReplace: Boolean = false,
): MagicCommand {
    val shouldReplace = isMagicReplaceablePreceding(precedingChar) && (forceReplace || replaceable)
    return if (shouldReplace) {
        MagicCommand("magic_replace_tap_repeatable(${qmk.key});", qmk.key, qmk.key, reverseSafe = true)
    } else {
        MagicCommand(repeatableTap(qmk), qmk.key, qmk.key)
    }
}

private fun isBareWord(def: String): Boolean =
    def.length > 1 &&
        !isQuotedString(def) &&
        !def.startsWith("[")

private fun isBracketToken(def: String): Boolean = def.startsWith("[") && def.endsWith("]")

private fun isMagicReplaceablePreceding(precedingChar: String): Boolean =
    precedingChar == "spc" ||
        (precedingChar.length == 1 && precedingChar[0].isLetter())

private fun bracketCommand(
    name: String,
    pos: KeyPosition,
    stringOffsetConstants: Map<String, String>,
): String =
    when (name) {
        "dotSpc" -> {
            val offset = stringOffsetConstants.getValue(". ")
            "${annotateMagicSend("magic_replace_decode_send_cap($offset, '\\0');", ". ")} " +
                "add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state();"
        }

        else -> {
            throw IllegalArgumentException("unknown bracket token '[$name]' in $pos")
        }
    }

private fun isWord(alt: String) = isQuotedString(alt)

private fun extractString(alt: String): String =
    when {
        alt.length >= 2 && alt.startsWith("\"") && alt.endsWith("\"") -> alt.removeSurrounding("\"")
        alt.length >= 2 && alt.startsWith("'") && alt.endsWith("'") -> alt.removeSurrounding("'")
        else -> alt
    }

private fun isQuotedString(value: String): Boolean =
    value.length >= 2 &&
        (
            (value.startsWith("\"") && value.endsWith("\"")) ||
                (value.startsWith("'") && value.endsWith("'"))
        )

private fun sendString(alt: String) = "SEND_STRING($alt)"

private fun repeatableTap(qmk: QmkKey) = "magic_tap_repeatable(${qmk.key});"

private fun cycleLiteral(
    output: String,
    cycleData: List<CycleEntry>,
    stringOffsetConstants: Map<String, String>,
): String =
    cycleData
        .firstOrNull { it.current == output }
        ?.current
        ?.let(stringOffsetConstants::getValue) ?: NO_CYCLE_OFFSET

private fun annotateMagicSend(
    statement: String,
    emitted: String,
    fullOutput: String = emitted,
): String {
    val detail =
        if (emitted == fullOutput) {
            "emits ${cStringLiteral(emitted)}"
        } else {
            "emits ${cStringLiteral(emitted)} -> ${cStringLiteral(fullOutput)}"
        }
    return "$statement /* $detail */"
}

private fun cStringLiteral(value: String): String =
    buildString {
        append('"')
        value.forEach { char ->
            when (char) {
                '\\' -> append("\\\\")
                '"' -> append("\\\"")
                '\n' -> append("\\n")
                '\r' -> append("\\r")
                '\t' -> append("\\t")
                else -> append(char)
            }
        }
        append('"')
    }

private fun resolveMagicDefinition(
    def: String,
    translator: QmkTranslator,
    pos: KeyPosition,
): String =
    if (translator.symbols.mapping.containsKey(def)) {
        translator.symbols.replace(def, pos, translator)
    } else if (def.startsWith("#") && def.length > 1) {
        throw IllegalArgumentException("symbol '$def' not found in Symbols table at $pos")
    } else {
        def
    }

private fun parseMagicSpec(
    def: String,
    translator: QmkTranslator,
    pos: KeyPosition,
): MagicSpec {
    val forceReplace = def.startsWith(MAGIC_REPLACE_PREFIX)
    val rawDef = if (forceReplace) def.removePrefix(MAGIC_REPLACE_PREFIX).trimStart() else def
    return MagicSpec(forceReplace, resolveMagicDefinition(rawDef, translator, pos))
}

private fun collectMagicOutputs(
    tables: Tables,
    translator: QmkTranslator,
): Set<String> {
    val outputs = mutableSetOf<String>()
    magicRows(tables.getOptional("Magic").orEmpty()).forEach { row ->
        val precedingChar = row[0]
        row.drop(1).forEach { def ->
            val spec = parseMagicSpec(def, translator, invalidPos)
            magicEmittedString(precedingChar, spec, translator)?.let(outputs::add)
            magicFullOutputString(precedingChar, spec, translator)?.let(outputs::add)
            bracketOutputString(spec.resolvedDef)?.let(outputs::add)
        }
    }
    return outputs
}

private fun validateMagicWords(
    tables: Tables,
    translator: QmkTranslator,
) {
    val seen = mutableMapOf<String, MagicWordLocation>()
    magicRows(tables.getOptional("Magic").orEmpty()).forEach { row ->
        val precedingChar = row[0]
        if (!(precedingChar.length == 1 && precedingChar[0].isLetter())) {
            return@forEach
        }
        row.drop(1).forEachIndexed { index, def ->
            val resolvedDef = parseMagicSpec(def, translator, invalidPos).resolvedDef
            if (!isBareWord(resolvedDef)) {
                return@forEachIndexed
            }
            val current =
                MagicWordLocation(
                    precedingChar = precedingChar,
                    trigger =
                        translator.magic
                            .getOrNull(index)
                            ?.trigger
                            ?.key ?: "column ${index + 2}",
                )
            val previous = seen.putIfAbsent(resolvedDef, current)
            require(previous == null) {
                val duplicate = checkNotNull(previous)
                "duplicate magic word '$resolvedDef' at ${current.precedingChar}+${current.trigger} " +
                    "(already defined at ${duplicate.precedingChar}+${duplicate.trigger})"
            }
        }
    }
}

private fun magicEmittedString(
    precedingChar: String,
    spec: MagicSpec,
    translator: QmkTranslator,
): String? {
    val def = spec.resolvedDef
    if (translator.symbols.customKeycodes.contains(def) || qmkPrefixes.any { def.startsWith(it) }) {
        return null
    }
    if (!(isWord(def) || isBareWord(def))) {
        return null
    }
    val quoted = isWord(def)
    val str = if (quoted) extractString(def) else def
    val output = if (quoted) str else "$str "
    val prevIsLetter = precedingChar.length == 1 && precedingChar[0].isLetter()
    return if (prevIsLetter && output.startsWith(precedingChar)) {
        output.drop(precedingChar.length)
    } else {
        output
    }
}

private fun magicFullOutputString(
    precedingChar: String,
    spec: MagicSpec,
    translator: QmkTranslator,
): String? {
    val def = spec.resolvedDef
    if (translator.symbols.customKeycodes.contains(def) || qmkPrefixes.any { def.startsWith(it) }) {
        return null
    }
    if (!(isWord(def) || isBareWord(def))) {
        return null
    }
    val quoted = isWord(def)
    val str = if (quoted) extractString(def) else def
    return if (quoted) str else "$str "
}

private fun bracketOutputString(def: String): String? =
    when (def) {
        "[dotSpc]" -> ". "
        else -> null
    }

private fun readCycleData(tables: Tables): CycleData {
    val cycleTable = tables.getOptional("Cycle").orEmpty()
    if (cycleTable.isEmpty()) {
        return CycleData(emptyList(), emptySet())
    }

    val entries = mutableListOf<Pair<String, String>>()
    val outputs = mutableSetOf<String>()
    val seen = mutableMapOf<String, String>()

    cycleTable.forEachIndexed { rowIndex, row ->
        val items =
            row
                .map(::cycleItem)
                .filter { it.isNotBlank() }
        require(items.size >= 2) {
            "Cycle row ${rowIndex + 1} must contain at least two items: $row"
        }
        items.forEach { item ->
            val canonical = canonicalCycleItem(item)
            val previous = seen.putIfAbsent(canonical, item)
            require(previous == null) {
                "duplicate Cycle item '$item' (already defined as '$previous')"
            }
            outputs += cycleOutput(item)
        }
        items.zip(items.drop(1) + items.first()).forEach { (current, next) ->
            entries += cycleOutput(current) to cycleOutput(next)
        }
    }

    return CycleData(
        entries =
            entries.map { (current, next) ->
                CycleEntry(current, next, -1, -1, -1, next.dropLast(1).last())
            },
        outputs = outputs,
    )
}

private fun encodeCycleEntries(
    cycleData: CycleData,
    stringOffsets: Map<String, Int>,
): List<CycleEntry> =
    cycleData.entries
        .map { entry ->
            entry.copy(
                currentOffset = stringOffsets.getValue(entry.current),
                nextOffset = stringOffsets.getValue(entry.next),
                commonPrefixLength = commonPrefixLength(entry.current, entry.next),
            )
        }.sortedBy { it.currentOffset }

private fun magicCycleData(
    entries: List<CycleEntry>,
    stringOffsetConstants: Map<String, String>,
): String {
    val declarations =
        if (entries.isEmpty()) {
            ""
        } else {
            val rows =
                entries.joinToString(",\n") {
                    val lastChar = cCharLiteral(it.nextLastChar)
                    val currentOffset = stringOffsetConstants.getValue(it.current)
                    val nextOffset = stringOffsetConstants.getValue(it.next)
                    "    { $currentOffset, $nextOffset, ${it.commonPrefixLength}, $lastChar }"
                }
            """
typedef struct {
    uint16_t current_offset;
    uint16_t next_offset;
    uint8_t common_prefix_length;
    char next_last_char;
} magic_cycle_entry_t;

static const magic_cycle_entry_t magic_cycle_entries[] = {
$rows
};
            """.trimIndent()
        }

    val lookup =
        if (entries.isEmpty()) {
            """
static bool magic_cycle_lookup(uint16_t current_offset, uint16_t* next_offset, char* next_last_char) {
    (void)current_offset;
    (void)next_offset;
    (void)next_last_char;
    return false;
}
            """.trimIndent()
        } else {
            """

static bool magic_cycle_lookup(uint16_t current_offset, uint16_t* next_offset, char* next_last_char) {
    int low = 0;
    int high = (int)(sizeof(magic_cycle_entries) / sizeof(magic_cycle_entries[0])) - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        uint16_t mid_offset = magic_cycle_entries[mid].current_offset;
        if (mid_offset == current_offset) {
            *next_offset = magic_cycle_entries[mid].next_offset;
            suffix_cycle_common_prefix_length = magic_cycle_entries[mid].common_prefix_length;
            *next_last_char = magic_cycle_entries[mid].next_last_char;
            return true;
        }
        if (mid_offset < current_offset) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}
            """.trimIndent()
        }

    return """
$declarations
$lookup

#define MAGIC_CYCLE_NONE UINT16_MAX

static inline void set_suffix_word_state(char c, uint16_t cycle_offset, bool capitalize) {
    suffix_active = true;
    last_magic_char = c;
    suffix_cycle_offset = cycle_offset;
    suffix_cycle_capitalize = capitalize;
}

static void magic_decode_send_cap_cycle(uint16_t offset, char suffix, uint16_t cycle_offset) {
    bool capitalize = magic_capitalize_next;
    if (capitalize) {
        add_oneshot_mods(MOD_BIT(KC_LSFT));
    }
    magic_decode_send(offset);
    if (suffix != '\0') {
        set_suffix_word_state(suffix, cycle_offset, capitalize);
    }
    magic_capitalize_next = false;
}

static void magic_decode_send_suffix_cycle(uint16_t offset, char suffix, uint16_t cycle_offset) {
    bool capitalize = magic_capitalize_next;
    magic_decode_send(offset);
    set_suffix_word_state(suffix, cycle_offset, capitalize);
    magic_capitalize_next = false;
}

static void magic_replace_decode_send_cap_cycle(uint16_t offset, char suffix, uint16_t cycle_offset) {
    if (magic_context_key_emitted) {
        tap_code16(KC_BSPC);
    }
    magic_decode_send_cap_cycle(offset, suffix, cycle_offset);
}

static bool process_magic_cycle_next(void) {
    uint16_t next_offset = 0;
    char next_last_char = '\0';
    if (suffix_cycle_offset == MAGIC_CYCLE_NONE || !magic_cycle_lookup(suffix_cycle_offset, &next_offset, &next_last_char)) {
        clear_suffix_state();
        return false;
    }
    tap_code16(KC_BSPC);
    uint8_t current_length = magic_string_data[suffix_cycle_offset];
    uint8_t delete_count = current_length - 1 - suffix_cycle_common_prefix_length;
    for (uint8_t i = 0; i < delete_count; i++) {
        tap_code16(KC_BSPC);
    }
    if (suffix_cycle_capitalize && suffix_cycle_common_prefix_length == 0) {
        add_oneshot_mods(MOD_BIT(KC_LSFT));
    }
    magic_decode_send_skip(next_offset, suffix_cycle_common_prefix_length);
    set_suffix_word_state(next_last_char, next_offset, suffix_cycle_capitalize);
    return true;
}
        """.trimIndent()
}

private fun cycleItem(value: String): String =
    if (isQuotedString(value)) {
        extractString(value)
    } else {
        value.trim()
    }

private fun cycleOutput(value: String): String = "${cycleItem(value)} "

private fun canonicalCycleItem(value: String): String = cycleItem(value).lowercase()

private fun cCharLiteral(value: Char): String =
    when (value) {
        '\\' -> "'\\\\'"
        '\'' -> "'\\''"
        '\n' -> "'\\n'"
        '\r' -> "'\\r'"
        '\t' -> "'\\t'"
        else -> "'$value'"
    }

private fun commonPrefixLength(
    left: String,
    right: String,
): Int {
    val max = minOf(left.length, right.length)
    for (index in 0 until max) {
        if (left[index] != right[index]) {
            return index
        }
    }
    return max
}

fun customKeycodes(
    translator: QmkTranslator,
    type: CustomCommandType,
): String =
    translator.symbols.customKeycodes.entries
        .filter { it.value.command?.type == type }
        .map {
            translator.ignoreUnexpected.add(it.key)
            "case _HANDLER_${it.key}: ${it.value.command!!.cStatements.joinToString("; ")}; return false;"
        }.indented(12)

fun holdOnOtherKeyPress(layerTapToggle: Set<QmkKey>): String =
    layerTapToggle
        .map {
            "case $it: return true;"
        }.indented(4)

private fun List<String>.indented(indent: Int): String = this.joinToString("\n").prependIndent(" ".repeat(indent))

fun LayerName.const() = "_${this.uppercase()}"

private fun replaceTemplate(
    src: File,
    dst: File,
    vars: Map<String, String>,
) {
    dst.writeText(
        vars.entries.fold(src.readText()) { acc, entry ->
            acc.replace("\${${entry.key}}", entry.value)
        },
    )
}
