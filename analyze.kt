fun analyze(translator: QmkTranslator, layers: List<Layer>) {
    translator.nonThumbs.keys.subtract(translator.layerOptions.keys).forEach {
        throw IllegalStateException("unexpected layer $it")
    }
    translator.thumbs.keys.subtract(translator.layerOptions.keys).forEach {
        throw IllegalStateException("unexpected thumb layer $it")
    }
    printMissingAndUnexpected(translator, layers)
}

val invalidPos = KeyPosition(0, 0, "none", false, 0)

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

    val missing = (want - gotKeys.toSet())
    val unexpected = (gotKeys.toSet() - want.toSet())
        .filter {
               when {
                   it.startsWith("\"") -> false
                   it.contains("(")  -> false
                   it.startsWith("DT_") -> false
                   it.startsWith("KC_ACL") -> false
                   it == qmkNo -> false
                   it == layerBlocked -> false
                   it == comboTrigger -> false
                   else -> true
               }
           }

    println("expected: ${want.size}")
    println("missing: $missing")
    println("unexpected: $unexpected")
    val dups = gotKeys.filter { k -> gotKeys.filter { k == it }.size > 1 }.distinct()
    println("duplicates: $dups")
}


