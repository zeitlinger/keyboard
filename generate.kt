import java.io.File

const val mainLayerTemplate4Columns =
    "\t[%s] = LAYOUT_split_3x5_2(\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "                            %s, %s, %s, %s),"

const val mainLayerTemplate5Columns =
    "\t[%s] = LAYOUT_split_3x5_2(\n" +
            "            %s, %s, %s, %s, %s, %s, %s, %s, %s, %s,\n" +
            "            %s, %s, %s, %s, %s, %s, %s, %s, %s, %s,\n" +
            "            %s, %s, %s, %s, %s, %s, %s, %s, %s, %s,\n" +
            "                            %s, %s, %s, %s),"

fun template(layers: List<Layer>): String =
    layers[0].rows[0].size.let { columns ->
        when (columns) {
            10 -> mainLayerTemplate5Columns
            8 -> mainLayerTemplate4Columns
            else -> throw IllegalStateException("unsupported number of columns $columns")
        }
    }

private const val thumbColumns = 4

fun generateBase(layers: List<Layer>): String {
    val template = template(layers)
    return layers
        .sortedBy { it.number }
        .joinToString("\n") { layer ->
            template.format(*listOf(layer.name.const()).plus(layer.rows.mapIndexed { index, row ->
                if (index == layer.rows.size - 1) {
                    val drop = (row.size - thumbColumns) / 2
                    row.drop(drop).take(thumbColumns)
                } else {
                    row
                }.map {
                    it.keyWithModifier.key.padStart(
                        20
                    )
                }
            }
                .flatten()).toTypedArray())
        }
}

fun run(args: GeneratorArgs) {
    val tables = readTables(args.configFile.file)
    val translator = qmkTranslator(tables)

    val layers = translator.layerOptions.entries.map { (layerName, _) ->
        val table = translator.keys[layerName]
            ?: listOf(List(translator.options.rows) { List(translator.options.nonThumbColumns) { "" } })
        readLayer(table, translator, layerName, translator.layerNumbers.getOrDefault(layerName, -1))
    }

    val combos = translator.combos + generateAllCombos(layers, translator)
    val comboLines = combos.map { combo ->
        combo.type.template.format(
            combo.name.padEnd(35),
            combo.result.let { it.substitutionCombo ?: it.key }.padEnd(35),
            combo.triggers.joinToString(", ") { it.keyWithModifier.key }
        )
    }.sorted()

    val timeouts = combos.filter { it.timeout != null }.map {
        "case ${it.name}: return ${it.timeout};"
    }.sorted()

    tables.getOptional("Repeat")?.let {
        it.forEachIndexed { index, row ->
            val pos = KeyPosition(0, index, 0, "alt repeat", 0)
            addRepeat(translator, row, pos)
        }
    }

    val srcDir = args.generatorDir.file
    val dstDir = args.dstDir
    val gitVersion = readGitVersion(args.configFile, args.configFile.file.name)
    val generatorDir = args.generatorDir
    val generationNote =
        "file is generated from $gitVersion using ${
            readGitVersion(generatorDir, "generateKeyboard.kt")
        }"

    val userKeycodes = translator.symbols.customKeycodes.keys.toList()
    replaceTemplate(
        File(srcDir, "layout.h"),
        File(dstDir, "qmk/layout.h"),
        mapOf(
            "generationNote" to generationNote,
            "versionString" to gitVersion,
            "layers" to generateBase(layers),
            "layerNumbers" to translator.layerNumbers.entries
                .joinToString("\n") {
                    "#define ${it.key.const()} ${it.value}"
                },
            "custom0" to userKeycodes[0],
            "customRest" to userKeycodes.drop(1).joinToString(",\n    "),
            "customHandlers" to translator.symbols.customKeycodes.entries
                .joinToString("\n") {
                    "#define _HANDLER_${it.key} ${it.value.key}"
                },
        )
    )

    replaceTemplate(
        File(srcDir, "generated.c"),
        File(dstDir, "qmk/generated.c"),
        mapOf(
            "generationNote" to generationNote,
            "timeouts" to timeouts.joinToString("\n    "),
            "customKeycodesOnTapPress" to customKeycodes(translator, CustomCommandType.OnTap),
            "customKeycodesOnPress" to customKeycodes(translator, CustomCommandType.OnPress),
            "holdOnOtherKeyPress" to holdOnOtherKeyPress(translator.layerTapHold.toSet()),
            "altRepeat" to translator.symbols.altRepeat.entries.sortedBy { it.key.key }.joinToString("\n        ") {
                "case ${it.key}: return ${it.value};"
            },
            "repeat" to translator.symbols.repeat.entries.sortedBy { it.key.key }.joinToString("\n                ") {
                "case ${it.key}: ${it.value};"
            }
        )
    )

    analyze(translator, layers)

    File(dstDir, "qmk/combos.def").writeText((listOf("// $generationNote") + comboLines).joinToString("\n"))
}

private fun addRepeat(translator: QmkTranslator, row: List<String>, pos: KeyPosition) {
    val base = translator.toQmk(row[0], pos)
    val alt = row[1]
    if (alt.isNotBlank()) {
        val command = when {
            alt.length == 1 -> translator.toQmk(alt, pos).key
            isWord(alt) -> customCommand(
                translator,
                QmkKey("${"ALT"}_${base}"),
                CustomCommandType.OnPress,
                listOf(sendString(alt))
            ).key

            else -> throw IllegalArgumentException("unknown command '${alt}' in $pos")
        }
        addRepeat(translator.symbols.altRepeat, base, command)
    }
    val repeat = row[2]
    if (repeat.isNotBlank()) {
        val command = when {
            repeat.length == 1 -> tap(translator.toQmk(repeat, pos)) + "; return false"
            isWord(repeat) -> sendString(repeat) + "; return false"

            else -> throw IllegalArgumentException("unknown command '${repeat}' in $pos")
        }
        addRepeat(translator.symbols.repeat, base, command)
    }
}

private fun addRepeat(
    map: MutableMap<QmkKey, String>,
    base: QmkKey,
    command: String,
) {
    map[base] = command
    if (isLetter(base)) {
        map[shifted(base)] = command
    }
}

private fun isWord(alt: String) = alt.startsWith("\"") && alt.endsWith("\"")

private fun sendString(alt: String) = "SEND_STRING(${alt})"

fun customKeycodes(translator: QmkTranslator, type: CustomCommandType): String =
    translator.symbols.customKeycodes.entries
        .filter { it.value.command?.type == type }
        .joinToString("\n            ") {
            translator.symbols.ignoreUnexpected.add(it.key)
            "case _HANDLER_${it.key}: ${it.value.command!!.cStatements.joinToString("; ")}; return false;"
        }

fun holdOnOtherKeyPress(layerTapToggle: Set<QmkKey>): String =
    layerTapToggle.joinToString("\n    ") { "case ${it}: return true;" }

fun LayerName.const() = "_${this.uppercase()}"

private fun replaceTemplate(src: File, dst: File, vars: Map<String, String>) {
    dst.writeText(vars.entries.fold(src.readText()) { acc, entry ->
        acc.replace("\${${entry.key}}", entry.value)
    })
}
