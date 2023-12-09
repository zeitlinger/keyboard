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

fun targetLayerOnHold(modTapKeyTargetLayers: MutableMap<String, Int>): String {
    return modTapKeyTargetLayers.entries.joinToString("\n    ") { "case ${it.key}: return ${it.value};" }
}

fun run(args: GeneratorArgs) {
    val translator = qmkTranslator(args)

    val layers = translator.layerOptions.entries.map { (layerName, content) ->
        val table = translator.nonThumbs[layerName] ?: listOf(List(translator.options.nonThumbRows) { List(translator.options.nonThumbColumns) { "" } })
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

    val generationNote =
        "file is generated from ${args.config.name} using https://github.com/zeitlinger/keyboard/blob/main/generateKeyboard.kt"

    val gitVersion = readGitVersion(args)
    replaceTemplate(
        args.layoutTemplate, args.layoutFile, mapOf(
            "generationNote" to generationNote,
            "versionString" to gitVersion.url,
            "layers" to generateBase(layers),
            "layerNumbers" to translator.layerNumbers.entries
                .joinToString("\n") { "#define _${it.key.uppercase()} ${it.value}" },
            "custom0" to translator.symbols.userKeycodes[0],
            "customRest" to translator.symbols.userKeycodes.drop(1).joinToString(",\n    ")
        )
    )

    replaceTemplate(
        args.generatedTemplate, args.generatedFile, mapOf(
            "generationNote" to generationNote,
            "timeouts" to timeouts.joinToString("\n    "),
            "targetLayerOnHold" to targetLayerOnHold(translator.modTapKeyTargetLayers),
        )
    )

    args.comboFile.writeText((listOf("// $generationNote") + comboLines).joinToString("\n"))

    if (gitVersion.uncommittedChanges != null) {
        throw IllegalStateException("uncommitted changes: ${gitVersion.uncommittedChanges}")
    }
}

private fun replaceTemplate(src: File, dst: File, vars: Map<String, String>) {
    dst.writeText(vars.entries.fold(src.readText()) { acc, entry ->
        acc.replace("\${${entry.key}}", entry.value)
    })
}
