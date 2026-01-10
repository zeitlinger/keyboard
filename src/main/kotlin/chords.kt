data class TrieNode(
    val state: Int,
    val children: MutableMap<String, TrieNode> = mutableMapOf(),
    var output: String? = null,
    val chordSequence: String = "" // Track the chord sequence that led to this state
)

data class ChordInfo(
    val transitions: Map<Int, Map<String, Int>>, // state -> (key -> next_state)
    val outputs: Map<Int, String>, // state -> output string
    val maxState: Int,
    val stateToChord: Map<Int, String> // state -> chord sequence for comments
)

fun buildChordTrie(chordTable: Table?): ChordInfo? {
    if (chordTable.isNullOrEmpty()) {
        return null
    }

    val root = TrieNode(state = 1, chordSequence = "") // State 0 = inactive, State 1 = root
    var nextState = 2

    // Build trie from chord definitions
    for (row in chordTable) {
        val chordSequence = row[0].trim()
        val output = row[1].trim().removeSurrounding("\"")

        if (chordSequence.isBlank() || output.isBlank()) {
            continue
        }

        var currentNode = root
        var builtSequence = ""
        for (char in chordSequence) {
            val key = char.toString().lowercase()
            builtSequence += key
            if (!currentNode.children.containsKey(key)) {
                currentNode.children[key] = TrieNode(state = nextState++, chordSequence = builtSequence)
            }
            currentNode = currentNode.children[key]!!
        }
        currentNode.output = output
    }

    // Convert trie to lookup tables
    val transitions = mutableMapOf<Int, MutableMap<String, Int>>()
    val outputs = mutableMapOf<Int, String>()
    val stateToChord = mutableMapOf<Int, String>()

    fun collectNodes(node: TrieNode) {
        if (node.chordSequence.isNotEmpty()) {
            stateToChord[node.state] = node.chordSequence
        }
        if (node.children.isNotEmpty()) {
            transitions[node.state] = node.children.mapValues { it.value.state }.toMutableMap()
        }
        if (node.output != null) {
            outputs[node.state] = node.output!!
        }
        node.children.values.forEach { collectNodes(it) }
    }

    collectNodes(root)

    return ChordInfo(
        transitions = transitions,
        outputs = outputs,
        maxState = nextState - 1,
        stateToChord = stateToChord
    )
}

fun generateChordTransitions(chordInfo: ChordInfo): String {
    val lines = mutableListOf<String>()

    for ((state, keyMap) in chordInfo.transitions.toSortedMap()) {
        val chordComment = chordInfo.stateToChord[state]?.let { "        // $it" } ?: null
        for ((key, nextState) in keyMap.toSortedMap()) {
            val qmkKey = "KC_${key.uppercase()}"
            if (chordComment != null) {
                lines.add(chordComment)
            }
            lines.add("case $state: if (keycode == $qmkKey) return $nextState; break;")
        }
    }

    return if (lines.isEmpty()) {
        ""
    } else {
        lines.joinToString("\n")
    }
}

fun generateChordOutputs(chordInfo: ChordInfo): String {
    val lines = mutableListOf<String>()

    for ((state, output) in chordInfo.outputs.toSortedMap()) {
        val chordComment = chordInfo.stateToChord[state]?.let { "        // $it" } ?: null
        if (chordComment != null) {
            lines.add(chordComment)
        }
        lines.add("case $state: SEND_STRING(\"$output\"); break;")
    }

    return lines.joinToString("\n")
}

