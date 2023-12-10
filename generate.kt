import java.io.File

const val mainLayerTemplate =
    "\t[%d] = LAYOUT_split_3x5_2(\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "            %s, %s, %s, %s, KC_NO, KC_NO, %s, %s, %s, %s,\n" +
            "                            %s, %s, %s, %s),"

fun generateBase(layers: List<Layer>): String {
    return layers
        .filter { !it.option.flags.contains(LayerFlag.Hidden) }
        .sortedBy { it.number }
        .joinToString("\n") { layer ->
            mainLayerTemplate.format(*listOf(layer.number).plus(layer.baseRows.map { it.map { it.keyWithModifier } }
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
            "custom0" to translator.symbols.userKeycodes[0],
            "customRest" to translator.symbols.userKeycodes.drop(1).joinToString(",\n    ")
        )
    )

    replaceTemplate(
        File(srcDir, "generated.c"),
        File(dstDir, "qmk/generated.c"),
        mapOf(
            "generationNote" to generationNote,
            "timeouts" to timeouts.joinToString("\n    "),
            "targetLayerOnHoldPressed" to targetLayerOnHold(translator.modTapKeyTargetLayers, "on", "add"),
            "targetLayerOnHoldReleased" to targetLayerOnHold(translator.modTapKeyTargetLayers, "off", "del"),
            "holdOnOtherKeyPress" to holdOnOtherKeyPress(translator.layerTapHold),
        )
    )

    File(dstDir, "qmk/combos.def").writeText((listOf("// $generationNote") + comboLines).joinToString("\n"))
}

fun holdOnOtherKeyPress(layerTapToggle: List<String>): String =
    layerTapToggle.joinToString("\n        ") { "case ${it}: return true;" }

fun LayerName.const() = "_${this.uppercase()}"

private fun replaceTemplate(src: File, dst: File, vars: Map<String, String>) {
    dst.writeText(vars.entries.fold(src.readText()) { acc, entry ->
        acc.replace("\${${entry.key}}", entry.value)
    })
}
