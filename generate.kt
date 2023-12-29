import java.io.File

const val mainLayerTemplate =
    "\t[%s] = LAYOUT_split_3x5_2(\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "                            %s, %s, %s, %s),"

fun generateBase(layers: List<Layer>): String {
    return layers
        .filter { !it.option.flags.contains(LayerFlag.Hidden) }
        .sortedBy { it.number }
        .joinToString("\n") { layer ->
            mainLayerTemplate.format(*listOf(layer.name.const()).plus(layer.baseRows.map { it.map { it.keyWithModifier } }
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

    analyze(translator, layers)

    val combos = generateAllCombos(layers, translator.options, translator.homeRowThumbCombo)
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
            "customKeycodesOnTapPressed" to customKeycodesOnTapPressed(translator),
            "targetLayerOnHoldPressed" to targetLayerOnHold(translator.modTapKeyTargetLayers, "on", "add"),
            "targetLayerOnHoldReleased" to targetLayerOnHold(translator.modTapKeyTargetLayers, "off", "del"),
            "holdOnOtherKeyPress" to holdOnOtherKeyPress(translator.layerTapHold.toSet()),
            "layerOffKeys" to layerOffKeys(translator),
            "disableComboOnNonBaseLayer" to disableComboOnNonBaseLayer(combos),
        )
    )

    File(dstDir, "qmk/combos.def").writeText((listOf("// $generationNote") + comboLines).joinToString("\n"))
}

private fun layerOffKeys(translator: QmkTranslator): String =
    listOf(
        translator.layerOffKeys
            .joinToString("\n    ") {
                "if (keycode == ${it.key} && layer_state_is(${it.layer})) { return ${it.layer}; } "
            },
        translator.layerOptions.entries.filter { it.value.flags.contains(LayerFlag.OneShot) }
            .joinToString("\n    ") {
                "if (layer_state_is(${it.key.const()})) { return ${it.key.const()}; } "
            }
    ).joinToString("\n    ")

fun customKeycodesOnTapPressed(translator: QmkTranslator): String =
    translator.symbols.customKeycodes.entries
        .filter { it.value.onTapPressed != null }
        .joinToString("\n            ") {
            "case _HANDLER_${it.key}: ${it.value.onTapPressed}; return false;"
        }

fun disableComboOnNonBaseLayer(combos: List<Combo>): String =
    combos.filter { it.name.startsWith("C_OSM") }.joinToString("\n        ") { "case ${it.name}: return false;" }

fun holdOnOtherKeyPress(layerTapToggle: Set<String>): String =
    layerTapToggle.joinToString("\n    ") { "case ${it}: return true;" }

fun LayerName.const() = "_${this.uppercase()}"

private fun replaceTemplate(src: File, dst: File, vars: Map<String, String>) {
    dst.writeText(vars.entries.fold(src.readText()) { acc, entry ->
        acc.replace("\${${entry.key}}", entry.value)
    })
}
