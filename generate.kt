
fun generateBase(layers: List<Layer>, options: Map<String, Option>): String {
    val fallback = layers.associateBy { it.name }.mapValues { it.value.baseRows }

    return layers.mapIndexed { layerNumber, layer ->
        val qmk = layer.baseRowsWithMods
            .mapIndexed { rowIndex, row ->
                row.mapIndexed { columnIndex, key ->
                    val left = columnIndex < row.size / 2
                    getFallback(key, layer.name, fallback, options, rowIndex, columnIndex, left)
                }
            }.flatten()

        mainLayerTemplate.format(*listOf(layerNumber).plus<Any>(qmk).toTypedArray())
    }.joinToString("\n")
}

private fun getFallback(
    key: String,
    layer: String,
    fallback: Map<String, Rows>,
    options: Map<String, Option>,
    rowIndex: Int,
    columnIndex: Int,
    left: Boolean
): String {
    val option = options.getValue(layer)
    if (!key.isBlocked()) {
        return key
    }
    val fallbackLayer = if (left) option.leftFallbackLayer else option.rightFallbackLayer
    return when {
        fallbackLayer == null || layer == baseLayerName -> qmkNo
        else -> getFallback(
            fallback.getValue(fallbackLayer)[rowIndex][columnIndex],
            fallbackLayer,
            fallback,
            options,
            rowIndex,
            columnIndex,
            left
        )
    }
}
