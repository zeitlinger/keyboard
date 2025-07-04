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
                    row.drop(2).take(thumbColumns - 2) + row.drop(row.size - 2 - (thumbColumns / 2))
                        .take(thumbColumns - 2)
                } else {
                    row
                }.map {
                    val key = it.keyWithModifier
                    if (key.substitution != null) {
                        throw IllegalStateException("substitutionCombo not supported in base layer: $key")
                    } else {
                        key.key.padStart(
                            20
                        )
                    }
                }
            }
                .flatten()).toTypedArray())
        }
}

fun triLayer(layer: Layer, translator: QmkTranslator): String {
    val reachable = layer.option.reachable
    if (reachable.size != 2) {
        throw IllegalStateException("triLayer must have exactly 2 reachable layers: $reachable")
    }
    if (reachable.values.any { it != LayerActivation.Hold}) {
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

    val layers = addSendString(translator.layerOptions.entries.map { (layerName, _) ->
        val table = translator.keys[layerName]
            ?: listOf(List(translator.options.rows) { List(translator.options.nonThumbColumns) { "" } })
        readLayer(table, translator, layerName, translator.layerNumbers.getOrDefault(layerName, -1))
    }, translator)

    val combos = translator.combos + generateAllCombos(layers, translator)
    val comboLines = getComboLines(combos)

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
    val generationNote =
        "file is generated from ${gitTemplate.format(args.configFile.file.name)}"

    val userKeycodes = translator.symbols.customKeycodes.keys.toList()
    val visible =
        layers.filter {
            val reachable = translator.layerOptions.getValue(it.name).reachable
            reachable.isEmpty() || reachable.any { it.value != LayerActivation.Hidden }
        }
    replaceTemplate(
        File(srcDir, "config.h"),
        File(dstDir, "config.h"),
        mapOf(
            "triLayer" to (layers.singleOrNull { LayerFlag.TriLayer in it.option.flags }
                ?.let { triLayer(it, translator) } ?: ""),
        )
    )
    replaceTemplate(
        File(srcDir, "layout.h"),
        File(dstDir, "layout.h"),
        mapOf(
            "generationNote" to generationNote,
            "versionString" to args.versionString,
            "layers" to generateBase(visible),
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
        File(dstDir, "generated.c"),
        mapOf(
            "generationNote" to generationNote,
            "timeouts" to timeouts.indented(4),
            "customKeycodesOnTapPress" to customKeycodes(translator, CustomCommandType.OnTap),
            "customKeycodesOnPress" to customKeycodes(translator, CustomCommandType.OnPress),
            "holdOnOtherKeyPress" to holdOnOtherKeyPress(translator.layerTapHold.toSet()),
            "altRepeat" to translator.altRepeat.entries.sortedBy { it.key.key }.map {
                "case ${it.key}: return ${it.value};"
            }.indented(8),
            "repeat" to repeatBlock(translator.repeat),
            "repeat2" to repeatBlock(translator.repeat2),
            "oneShotOnUpLayerPressed" to translator.oneShotOnUpLayer.sortedBy { it.up.const() }
                .map {
                    "case ${it.activation.key.key}: alternateLayer = ${it.up.const()}; break;"
                }.indented(8),
            "oneShotOnUpLayerKey" to translator.oneShotOnUpLayer.sortedBy { it.up.const() }
                .map {
                    "case ${it.up.const()}:\n${oneShotOnUpLayerKey(it, layers)}"
                }.indented(12),
        )
    )

    if (args.printStats) {
        analyze(translator, layers)
    }

    File(dstDir, "combos.def").writeText((listOf("// $generationNote") + comboLines).joinToString("\n"))
}

private fun repeatBlock(map: MutableMap<QmkKey, String>): String {
    return map.entries.sortedBy { it.key.key }.map {
        "case ${it.key}: ${it.value};"
    }.indented(16)
}

fun addSendString(layers: List<Layer>, translator: QmkTranslator): List<Layer> {
    return layers.map {
        it.copy(rows = it.rows.map { row ->
            row.map { key ->
                val substitution = key.key.substitution
                if (substitution != null) {
                    val name = "ST_${key.pos.layerName}_${key.pos.row}_${key.pos.column}".uppercase()
                    val command = customCommand(
                        translator,
                        QmkKey.of(name),
                        CustomCommandType.OnPress,
                        listOf(sendString(substitution)),
                        key.key
                    )
                    translator.ignoreMissing.add(key.key)

                    key.copy(key = command, keyWithModifier = command)
                } else {
                    key
                }
            }
        })
    }
}

private fun getComboLines(combos: List<Combo>) = combos.map { combo ->
    combo.type.template.format(
        combo.name.padEnd(35),
        combo.result.let { it.substitution ?: it.key }.padEnd(35),
        combo.triggers.joinToString(", ") { it.keyWithModifier.key }
    )
}.sorted()

private fun addRepeat(translator: QmkTranslator, row: List<String>, pos: KeyPosition) {
    val base = translator.toQmk(row[0], pos)
    val alt = row[1]
    if (alt.isNotBlank()) {
        val command = when {
            alt.length == 1 -> translator.toQmk(alt, pos).key
            isWord(alt) -> customCommand(
                translator,
                QmkKey.of("${"ALT"}_${base}"),
                CustomCommandType.OnPress,
                listOf(sendString(alt)),
                base
            ).key

            else -> throw IllegalArgumentException("unknown command '${alt}' in $pos")
        }
        addRepeat(translator.altRepeat, base, command)
    }
    addRepeatCommand(row[2], translator, pos, translator.repeat, base)
    addRepeatCommand(row[3], translator, pos, translator.repeat2, base)
}

private fun addRepeatCommand(
    repeat: String,
    translator: QmkTranslator,
    pos: KeyPosition,
    map: MutableMap<QmkKey, String>,
    base: QmkKey
) {
    if (repeat.isNotBlank()) {
        val command = when {
            repeat.length == 1 -> tap(translator.toQmk(repeat, pos)) + "; return false"
            isWord(repeat) -> sendString(repeat) + "; return false"

            else -> throw IllegalArgumentException("unknown command '${repeat}' in $pos")
        }
        addRepeat(map, base, command)
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
        .map {
            translator.ignoreUnexpected.add(it.key)
            "case _HANDLER_${it.key}: ${it.value.command!!.cStatements.joinToString("; ")}; return false;"
        }.indented(12)

fun holdOnOtherKeyPress(layerTapToggle: Set<QmkKey>): String =
    layerTapToggle.map { "case ${it}: return true;" }.indented(4)

fun oneShotOnUpLayerKey(oneShotOnUpLayer: OneShotOnUpLayer, layers: List<Layer>): String {
    val up = layers.single { it.name == oneShotOnUpLayer.up }
    val base = layers.first()
    val list = base.rows.flatMapIndexed { rowIndex, row ->
        row.flatMapIndexed { columnIndex, key ->
            val upKey = up.rows[rowIndex][columnIndex]
            if (upKey.isReal()) {
                listOf("    case ${key.keyWithModifier.key}: return tap(${upKey.keyWithModifier.key});")
            } else {
                emptyList()
            }
        }
    }
    return listOf("switch (keycode) {\n${list.joinToString("\n")}", "}", "break;").indented(4)
}

private fun List<String>.indented(indent: Int): String =
    this.joinToString("\n").prependIndent(" ".repeat(indent))

fun LayerName.const() = "_${this.uppercase()}"

private fun replaceTemplate(src: File, dst: File, vars: Map<String, String>) {
    dst.writeText(vars.entries.fold(src.readText()) { acc, entry ->
        acc.replace("\${${entry.key}}", entry.value)
    })
}
