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
    layers[0].baseRows[0].size.let { columns ->
        when (columns) {
            10 -> mainLayerTemplate5Columns
            8 -> mainLayerTemplate4Columns
            else -> throw IllegalStateException("unsupported number of columns $columns")
        }
    }

fun generateBase(layers: List<Layer>): String {
    val template = template(layers)
    return layers
        .sortedBy { it.number }
        .joinToString("\n") { layer ->
            template.format(*listOf(layer.name.const()).plus(layer.baseRows.map {
                it.map {
                    it.keyWithModifier.padStart(
                        20
                    )
                }
            }
                .flatten()).toTypedArray())
        }
}

fun run(args: GeneratorArgs) {
    val translator = qmkTranslator(args)

    val layers = translator.layerOptions.entries.map { (layerName, _) ->
        val table = translator.nonThumbs[layerName]
            ?: listOf(List(translator.options.nonThumbRows) { List(translator.options.nonThumbColumns) { "" } })
        readLayer(table, translator, layerName, translator.layerNumbers.getOrDefault(layerName, -1))
    }

    val combos = translator.combos + generateAllCombos(layers, translator)
    val comboLines = combos.map { combo ->
        combo.type.template.format(
            combo.name.padEnd(35),
            combo.result.padEnd(35),
            combo.triggers.joinToString(", ") { it.keyWithModifier }
        )
    }.sorted()

    val timeouts = combos.filter { it.timeout != null }.map {
        "case ${it.name}: return ${it.timeout};"
    }.sorted()

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
            "customKeycodesOnPress" to
                    customKeycodes(translator, CustomCommandType.OnPress) +
                    "\n            " +
                    targetLayerOnHold(
                        translator.modTapKeyTargetLayers,
                        "on",
                        "add"
                    ),
            "customKeycodesOnRelease" to targetLayerOnHold(translator.modTapKeyTargetLayers, "off", "del"),
            "holdOnOtherKeyPress" to holdOnOtherKeyPress(translator.layerTapHold.toSet()),
            "altRepeat" to translator.symbols.altRepeat.entries.sortedBy { it.key }.joinToString("\n        ") {
                "case ${it.key}: return ${it.value};"
            }
        )
    )

    analyze(translator, layers)

    File(dstDir, "qmk/combos.def").writeText((listOf("// $generationNote") + comboLines).joinToString("\n"))
}

fun customKeycodes(translator: QmkTranslator, type: CustomCommandType): String =
    translator.symbols.customKeycodes.entries
        .filter { it.value.command?.type == type }
        .joinToString("\n            ") {
            translator.symbols.ignoreUnexpected.add(it.key)
            "case _HANDLER_${it.key}: ${it.value.command!!.cStatements.joinToString("; ")}; return false;"
        }

fun holdOnOtherKeyPress(layerTapToggle: Set<String>): String =
    layerTapToggle.joinToString("\n    ") { "case ${it}: return true;" }

fun LayerName.const() = "_${this.uppercase()}"

private fun replaceTemplate(src: File, dst: File, vars: Map<String, String>) {
    dst.writeText(vars.entries.fold(src.readText()) { acc, entry ->
        acc.replace("\${${entry.key}}", entry.value)
    })
}
