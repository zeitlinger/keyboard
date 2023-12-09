
fun analyze(translator: QmkTranslator) {
    translator.nonThumbs.keys.subtract(translator.layerOptions.keys).forEach {
        throw IllegalStateException("unexpected layer $it")
    }
    translator.thumbs.keys.subtract(translator.layerOptions.keys).forEach {
        throw IllegalStateException("unexpected thumb layer $it")
    }
}


//
//private fun printMissingAndUnexpected(
//    translator: QmkTranslator,
//    layers: List<Layer>,
//    symbols: Symbols
//) {
//    val gotKeys = thumbs.map { translator.toQmk(it.baseKey) } +
//            layers.map { it.baseRows.flatten() + it.combos.flatten().flatten() }.flatten()
//                .filterNot { it == blocked || it == comboTrigger }
//
//    val want =
//        symbols.mapping.values +
//                (CharRange('!', '~')
//                    .map { it.toString() }
//                    .filter { it.lowercase() == it }
//                    .map { translator.toQmk(it) }) +
//                (1..12).map { "KC_F$it" }
//                    .toSet()
//
//    val missing = (want - gotKeys.toSet()).map { translator.toLabel(it) }
//    val unexpected = (gotKeys.toSet() - want.toSet()).map { translator.toLabel(it) }
//    println("expected: ${want.size}")
//    println("missing: $missing")
//    println("unexpected: $unexpected")
//    val dups = gotKeys.filter { k -> gotKeys.filter { k == it }.size > 1 }
//        .map { translator.toLabel(it) }.distinct()
//    println("duplicates: $dups")
//}


