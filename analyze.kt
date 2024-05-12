fun analyze(translator: QmkTranslator, layers: List<Layer>) {
    val layerNames = translator.layerOptions.keys
    translator.nonThumbs.keys.subtract(layerNames).forEach {
        throw IllegalStateException("unexpected layer $it")
    }
    translator.thumbs.keys.subtract(layerNames).forEach {
        throw IllegalStateException("unexpected thumb layer $it")
    }
    translator.layerOptions.entries.forEach { (layer, option) ->
        if (LayerActivation.Toggle in option.reachable && LayerFlag.Toggle !in option.flags) {
            throw IllegalStateException("can't exit from layer $layer")
        }
    }
    val unreachable = translator.layerOptions.entries
        .filter { it.value.reachable.isEmpty() }.map { it.key } - listOf(layers.first().name).toSet()
    if (unreachable.isNotEmpty()) {
        throw IllegalStateException("can't reach layers $unreachable")
    }

    printMissingAndUnexpected(translator, layers)
}

val invalidPos = KeyPosition(0, 0, "none", false, 0)

val ignoreDuplicates = setOf(
    "esc",
    "spc",
    "shift",
    "\uD83D\uDDB1\uFE0F1", //mouse button 1
    "\uD83D\uDDB1\uFE0F2", //mouse button 2
    "\uD83D\uDDB1\uFE0F3", //mouse button 3
    "\uD83D\uDC8E", //diamond
)

private fun printMissingAndUnexpected(translator: QmkTranslator, layers: List<Layer>) {
    val gotKeys = layers.map { it.baseRows.flatten() + it.combos.flatten().flatten() }
        .flatten()
        .map { it.key }


    val want =
        translator.symbols.mapping.values +
                (CharRange('!', '~')
                    .map { it.toString() }
                    .filter { it.lowercase() == it }
                    .map { translator.toQmk(it, invalidPos) }) +
                (1..12).map { "KC_F$it" }
                    .toSet()

    val missing =
        want - gotKeys.toSet() - translator.symbols.ignoreMissing.map { translator.toQmk(it, invalidPos) }.toSet()
    val unexpected = (gotKeys.toSet() - want.toSet())
        .filter {
            when {
                it in translator.symbols.ignoreUnexpected -> false
                it.startsWith("\"") -> false
                it.contains("(") -> false
                it.startsWith("DT_") -> false
                it.startsWith("KC_ACL") -> false
                it == qmkNo -> false
                it == layerBlocked -> false
                it == comboTrigger -> false
                else -> true
            }
        }


    val duplicates = translator.symbols.gotKeys
        .filter { it.value > 1 }
        .keys - ignoreDuplicates

    println("expected: ${want.size}")
    println("missing: ${missing.sorted().distinct().joinToString(", ")}")
    println("unexpected: $unexpected")
    println("duplicates: $duplicates")
}


