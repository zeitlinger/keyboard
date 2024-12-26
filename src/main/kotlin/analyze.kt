fun analyze(translator: QmkTranslator, layers: List<Layer>) {
    val layerNames = translator.layerOptions.keys
    translator.keys.keys.subtract(layerNames).forEach {
        throw IllegalStateException("unexpected layer $it")
    }
    translator.layerOptions.entries.forEach { (layer, option) ->
        if (option.toggleOn && !option.toggleOff) {
            throw IllegalStateException("toggleOn without toggleOff in layer $layer")
        }
    }
    val unreachable = translator.layerOptions.entries
        .filter { it.value.reachable.isEmpty() }.map { it.key } - listOf(layers.first().name).toSet()
    if (unreachable.isNotEmpty()) {
        throw IllegalStateException("can't reach layers $unreachable")
    }

    printMissingAndUnexpected(translator, layers)
}

val invalidPos = KeyPosition(0, 0, 0, "none", 0)

val ignoreDuplicates = setOf(
    "esc",
    "spc",
    "shift",
    "@",
    "!",
    "CapW",
    "altRep",
    "\uD83D\uDC8E", //diamond
)

private fun printMissingAndUnexpected(translator: QmkTranslator, layers: List<Layer>) {
    val gotKeys = layers.map { it.rows.flatten() + it.combos.flatten().flatten() }
        .flatten()
        .map { it.key.key }


    val want =
        translator.symbols.mapping.values +
                (CharRange('!', '~')
                    .map { it }
                    .map { translator.toQmk(it.toString(), invalidPos).key }) +
                (1..12).map { "KC_F$it" }
                    .toSet()

    val missing =
        want - gotKeys.toSet() - translator.ignoreMissing.map { it.key }.toSet()
    val unexpected = (gotKeys.toSet() - want.toSet())
        .filter {
            when {
                it in translator.ignoreUnexpected -> false
                it.startsWith("\"") -> false
                it.contains("(") -> false
                it.startsWith("DT_") -> false
                it.startsWith("KC_ACL") -> false
                it == qmkNo -> false
                it == layerBlocked -> false
                it == comboTrigger -> false
                it.matches("KC_F\\d{2}".toRegex()) -> false
                else -> true
            }
        }

    for (entry in translator.gotKeys) {
        entry.value.remove("Num")
    }

    val duplicates = translator.gotKeys
        .filterNot { it.key.startsWith("dead") }
        .filter { it.value.size > 1 }
        .keys
        .sorted() - ignoreDuplicates

    println("expected: ${want.size}")
    println("missing: ${missing.sorted().distinct().joinToString(", ")}")
    println("unexpected: $unexpected")
    println("duplicates: $duplicates")
}


