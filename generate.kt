
fun generateBase(layers: List<Layer>, options: Map<String, Option>): String {
    val fallback = layers.associateBy { it.name }.mapValues { it.value.baseRows.flatten() }

    return layers.mapIndexed { layerNumber, layer ->
        val def = layer.baseRows.flatten()
        val qmk = def
            .mapIndexed { keyIndex, key ->
                getFallback(key, layer.name, fallback, options, keyIndex)
            }

        mainLayerTemplate.format(*listOf(layerNumber).plus<Any>(qmk).toTypedArray())
    }.joinToString("\n")
}

private fun getFallback(
    key: String,
    layer: String,
    fallback: Map<String, List<String>>,
    options: Map<String, Option>,
    keyIndex: Int
): String {
    val option = options.getValue(layer)
    return when {
        key.isBlocked() && layer == baseLayerName -> qmkNo
        key.isBlocked() -> getFallback(
            fallback.getValue(option.fallbackLayer)[keyIndex],
            option.fallbackLayer,
            fallback,
            options,
            keyIndex
        )

        else -> key
    }
}
