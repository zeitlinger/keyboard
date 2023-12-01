
data class Hand(
    val name: String,
    val columns: Int,
    val baseLayerRowSkip: Int,
    val skip: Int,
    val translateComboIndex: (Int) -> Int
) {
    fun applies(rows: Rows): Boolean {
        if (this.columns != rows[0].size) {
            return false
        }

        val half = this.columns / 2
        val halves = listOf(0, half).map { drop ->
            rows.map { it.drop(drop).take(half) }.flatten()
        }

        val isFull = halves
            .any { row ->
                val comboTriggers = row.filter { it.key == comboTrigger }.size
                val used = row.filter { !it.isBlocked() }.size
                used > 0 && comboTriggers == 0
            }
        return this.isFull == isFull
    }

    val isRight = this.name.startsWith("right")
    val isThumb = this.name.contains("thumb")
    val isFull = this.name.contains("both")
    val comboColumns = if (isFull) this.columns else this.columns / 2
}

val hands = listOf(
    Hand("left", 8, 0, 0) { i -> i + 4 },
    Hand("right", 8, 0, 4) { i -> 7 - i },
    Hand("both", 8, 0, 0) { i -> i },
    Hand("left thumb", 4, 3, 0) { i -> i + 1 },
    Hand("right thumb", 4, 3, 2) { i -> 4 - i },
    Hand("both thumbs", 4, 3, 0) { i -> i },
)
