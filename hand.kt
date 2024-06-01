
data class Hand(
    val name: String
) {
    fun skip(options: Options) = if (isRight) columns(options) / 2 else 0

    fun applies(rows: Rows, options: Options): Boolean {
        val cols = columns(options)
        if (cols != rows[0].size) {
            return false
        }

        val half = cols / 2
        val halves = listOf(0, half).map { drop ->
            rows.map { it.drop(drop).take(half) }.flatten()
        }

        val isFull = halves
            .any { row ->
                val comboTriggers = row.filter { it.key.key == comboTrigger }.size
                val used = row.filter { !it.isBlocked() }.size
                used > 0 && comboTriggers == 0
            }
        return this.isFull == isFull
    }

    private fun columns(options: Options): Int {
        return options.nonThumbColumns
    }

    private val isRight = this.name.startsWith("right")
    val isThumb = this.name.contains("thumb")
    private val isFull = this.name.contains("both")
    fun comboColumns(options: Options) = if (isFull) this.columns(options) else this.columns(options) / 2
}

val hands = listOf(
    Hand("left"),
    Hand("right"),
    Hand("both"),
    Hand("left thumb"),
    Hand("right thumb"),
    Hand("both thumbs"),
)
