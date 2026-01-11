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
    val stateToChord: Map<Int, String>, // state -> chord sequence for comments
    val trie: TrieNode? = null // Optional trie structure for two-pass processing
)

fun buildChordTrie(chordTable: Table?): ChordInfo? {
    if (chordTable.isNullOrEmpty()) {
        return null
    }

    val root = TrieNode(state = -1, chordSequence = "") // State 0 = inactive, State -1 = root
    var nextState = -2 // Negative states for transitions

    // check for duplicate chord sequences
    val seenChords = mutableSetOf<String>()
    for (row in chordTable) {
        val chordSequence = row[0].trim()
        if (chordSequence in seenChords) {
            throw IllegalArgumentException("Duplicate chord sequence found: '$chordSequence'")
        }
        seenChords.add(chordSequence)
    }

    // Build trie from chord definitions
    for (row in chordTable) {
        var chordSequence = row[0].trim()
        val output = row[1].trim().removeSurrounding("\"")

        chordSequence = when (chordSequence.length) {
            1 -> "$chordSequence " // single character chords get a trailing space
            2 -> chordSequence // two character chords are fine as-is
            else -> throw IllegalArgumentException("Chord sequence must be 1 or 2 characters: '$chordSequence'")
        }
        if (output.isBlank()) {
            throw IllegalArgumentException("Chord output cannot be blank for chord sequence: '$chordSequence'")
        }

        var currentNode = root
        var builtSequence = ""
        for (char in chordSequence) {
            val key = char.toString().lowercase()
            builtSequence += key
            if (!currentNode.children.containsKey(key)) {
                currentNode.children[key] = TrieNode(state = nextState--, chordSequence = builtSequence)
            }
            currentNode = currentNode.children[key]!!
        }
        currentNode.output = output
    }

    // Collect all nodes
    val allNodes = mutableListOf<TrieNode>()
    fun collectAllNodes(node: TrieNode) {
        allNodes.add(node)
        node.children.values.forEach { collectAllNodes(it) }
    }
    collectAllNodes(root)

    // Convert trie to lookup tables - keep temporary negative states for now
    // They will be remapped to byte offsets during encoding
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
        maxState = -nextState - 1, // Count of transition states
        stateToChord = stateToChord,
        trie = root
    )
}

fun generateChordTransitions(chordInfo: ChordInfo): String {
    val lines = mutableListOf<String>()

    for ((state, keyMap) in chordInfo.transitions.toSortedMap()) {
        val chordComment = chordInfo.stateToChord[state]?.let { "        // $it" } ?: ""
        if (chordComment.isNotEmpty()) {
            lines.add(chordComment)
        }
        lines.add("        case $state:")
        for ((key, nextState) in keyMap.toSortedMap()) {
            val qmkKey =
                when (key) {
                    " " -> "KC_SPC"
                    else -> "KC_${key.uppercase()}"
                }
            lines.add("            if (keycode == $qmkKey) return $nextState;")
        }
        lines.add("            break;")
    }

    return if (lines.isEmpty()) {
        ""
    } else {
        lines.joinToString("\n")
    }
}

data class EncodedChordData(
    val outputs: String, // C code for chord outputs
    val decoder: String?, // Optional decoder function
    val statistics: String, // Memory usage statistics
    val remappedChordInfo: ChordInfo? = null // ChordInfo with byte offsets as states
)

fun generateChordOutputs(chordInfo: ChordInfo): EncodedChordData {
    // Analyze all chord output strings
    val allStrings = chordInfo.outputs.values.toList()

    // Calculate raw memory usage
    val rawSize = allStrings.sumOf { it.length + 1 } // +1 for null terminator

    // Try encoding
    val encodingResult = tryEncodeChordStrings(chordInfo.outputs)

    // Determine whether to use encoding
    val useEncoding = encodingResult != null && encodingResult.totalSize < rawSize

    val stats = if (encodingResult != null) {
        val compressionRatio = "%.1f".format((encodingResult.dataSize.toDouble() / rawSize) * 100)
        if (useEncoding) {
            "Chord strings: 5-BIT ENCODED ✓ - data=${encodingResult.dataSize}B ($compressionRatio% of raw) + decoder=${encodingResult.decoderSize}B = ${encodingResult.totalSize}B vs raw ${rawSize}B (SAVED ${rawSize - encodingResult.totalSize}B, ${100 - (encodingResult.totalSize * 100 / rawSize)}%)"
        } else {
            "Chord strings: RAW - raw=${rawSize}B is better than 5-bit encoded ${encodingResult.totalSize}B (data=${encodingResult.dataSize}B @$compressionRatio% + decoder=${encodingResult.decoderSize}B)"
        }
    } else {
        "Chord strings: raw $rawSize bytes (encoding not possible - >32 unique characters)"
    }

    return if (useEncoding && encodingResult != null) {
        // Compute byte offset mapping
        val stateToByteOffset = mutableMapOf<Int, Int>()
        var currentOffset = 0
        for ((state, _) in chordInfo.outputs.toSortedMap()) {
            stateToByteOffset[state] = currentOffset
            currentOffset += encodingResult.encodedData[state]!!.size
        }

        // Remap chord info: transition states keep negative, output states become byte offsets
        val remappedChordInfo = remapChordInfoStates(chordInfo, stateToByteOffset)

        EncodedChordData(
            outputs = generateEncodedOutputs(chordInfo, encodingResult, stateToByteOffset),
            decoder = generateDecoder(encodingResult),
            statistics = stats,
            remappedChordInfo = remappedChordInfo
        )
    } else {
        EncodedChordData(
            outputs = generateRawOutputs(chordInfo),
            decoder = null,
            statistics = stats,
            remappedChordInfo = null // No remapping for raw outputs
        )
    }
}

// Remap states: transition states stay negative, output states become byte offsets
private fun remapChordInfoStates(chordInfo: ChordInfo, stateToByteOffset: Map<Int, Int>): ChordInfo {
    val stateMapping = mutableMapOf<Int, Int>()

    // Map output states to byte offsets
    stateToByteOffset.forEach { (state, offset) ->
        stateMapping[state] = offset
    }

    // Keep negative (transition) states as-is
    chordInfo.transitions.keys.filter { it < 0 }.forEach { state ->
        stateMapping[state] = state
    }

    // Remap transitions
    val remappedTransitions = mutableMapOf<Int, MutableMap<String, Int>>()
    chordInfo.transitions.forEach { (state, keyMap) ->
        val mappedState = stateMapping[state]!!
        remappedTransitions[mappedState] = keyMap.mapValues { (_, nextState) ->
            stateMapping[nextState] ?: nextState
        }.toMutableMap()
    }

    // Remap outputs
    val remappedOutputs = mutableMapOf<Int, String>()
    chordInfo.outputs.forEach { (state, output) ->
        remappedOutputs[stateMapping[state]!!] = output
    }

    // Remap stateToChord
    val remappedStateToChord = mutableMapOf<Int, String>()
    chordInfo.stateToChord.forEach { (state, chord) ->
        remappedStateToChord[stateMapping[state]!!] = chord
    }

    return ChordInfo(
        transitions = remappedTransitions,
        outputs = remappedOutputs,
        maxState = remappedOutputs.keys.maxOrNull() ?: 0,
        stateToChord = remappedStateToChord,
        trie = chordInfo.trie
    )
}

private fun generateRawOutputs(chordInfo: ChordInfo): String {
    val lines = mutableListOf<String>()
    for ((state, output) in chordInfo.outputs.toSortedMap()) {
        val chordComment = chordInfo.stateToChord[state]?.let { "        // $it" }
        if (chordComment != null) {
            lines.add(chordComment)
        }
        lines.add("case $state: SEND_STRING(\"$output\"); break;")
    }
    return lines.joinToString("\n")
}

data class ChordEncoding(
    val encodedData: Map<Int, ByteArray>, // state -> encoded bytes
    val charToCode: Map<Char, Int>, // character -> encoding value
    val codeToChar: Map<Int, Char>, // encoding value -> character
    val dataSize: Int, // Raw data bytes
    val decoderSize: Int, // Decoder overhead
    val totalSize: Int // Total bytes used (data + decoder overhead)
)

private fun tryEncodeChordStrings(outputs: Map<Int, String>): ChordEncoding? {
    // Build character frequency map
    val charFreq = mutableMapOf<Char, Int>()
    outputs.values.forEach { str ->
        str.forEach { char ->
            charFreq[char] = charFreq.getOrDefault(char, 0) + 1
        }
    }

    // Create sorted character list by frequency (most common first)
    val sortedChars = charFreq.entries.sortedByDescending { it.value }.map { it.key }

    // Check if we have too many unique characters (>32 won't fit in 5-bit encoding)
    if (sortedChars.size > 32) {
        return null
    }

    // Assign codes: use values 0-31 for 5-bit encoding
    val charToCode = sortedChars.mapIndexed { index, char -> char to index }.toMap()
    val codeToChar = charToCode.entries.associate { it.value to it.key }

    // Encode strings with 5-bit packing: pack multiple 5-bit values into bytes
    val encodedData = mutableMapOf<Int, ByteArray>()
    var totalDataSize = 0

    outputs.forEach { (state, str) ->
        // Calculate how many bytes needed for 5-bit packed data
        val numBits = str.length * 5
        val numBytes = (numBits + 7) / 8  // Round up to nearest byte

        val encoded = ByteArray(1 + numBytes)  // 1 byte for length + packed data
        encoded[0] = str.length.toByte()

        // Pack 5-bit codes into bytes
        var bitOffset = 0
        str.forEachIndexed { index, char ->
            val code = charToCode[char] ?: 0
            val byteIndex = bitOffset / 8
            val bitInByte = bitOffset % 8

            // Write 5-bit code across byte boundaries if needed
            if (bitInByte <= 3) {
                // Fits in current byte
                encoded[1 + byteIndex] = (encoded[1 + byteIndex].toInt() or (code shl bitInByte)).toByte()
            } else {
                // Spans two bytes
                encoded[1 + byteIndex] = (encoded[1 + byteIndex].toInt() or (code shl bitInByte)).toByte()
                encoded[2 + byteIndex] = ((code shr (8 - bitInByte)) and 0xFF).toByte()
            }

            bitOffset += 5
        }

        encodedData[state] = encoded
        totalDataSize += encoded.size
    }

    // Calculate decoder overhead:
    // - Lookup table: 1 byte per character (sortedChars.size)
    // - Function code: ~150 bytes (bit unpacking is more complex)
    // - Global buffer declaration: ~20 bytes
    val lookupTableSize = sortedChars.size
    val functionCodeSize = 150 // Bit manipulation decoder is larger
    val decoderOverhead = lookupTableSize + functionCodeSize

    val totalSize = totalDataSize + decoderOverhead

    return ChordEncoding(encodedData, charToCode, codeToChar, totalDataSize, decoderOverhead, totalSize)
}

private fun generateEncodedOutputs(chordInfo: ChordInfo, encoding: ChordEncoding, stateToByteOffset: Map<Int, Int>): String {
    // Return empty - we'll use a special marker to indicate direct offset mode
    return "DIRECT_OFFSET_MODE"
}

private fun generateDecoder(encoding: ChordEncoding): String {
    val lookupEntries = encoding.codeToChar.entries.sortedBy { it.key }.map { (code, char) ->
        val escapedChar = when (char) {
            '\'' -> "\\'"
            '\\' -> "\\\\"
            '\n' -> "\\n"
            '\r' -> "\\r"
            '\t' -> "\\t"
            else -> char.toString()
        }
        "'$escapedChar'"
    }

    // Build global buffer with all encoded strings
    val allEncodedBytes = mutableListOf<Byte>()
    encoding.encodedData.entries.sortedBy { it.key }.forEach { (_, bytes) ->
        allEncodedBytes.addAll(bytes.toList())
    }

    // Format as hex bytes, 16 per line
    val hexLines = allEncodedBytes.chunked(16).map { chunk ->
        "    " + chunk.joinToString(", ") { "0x%02x".format(it.toInt() and 0xFF) }
    }

    return """
// Chord string decoder lookup table (5-bit codes -> characters)
static const char chord_char_lookup[] = {
    ${lookupEntries.joinToString(", ")}
};

// Global buffer containing all 5-bit packed chord strings
static const uint8_t chord_data[] = {
${hexLines.joinToString(",\n")}
};

// Decode and send 5-bit packed chord string from buffer
static void chord_decode_send(const uint8_t* data) {
    uint8_t len = data[0];  // First byte is string length
    data++;  // Move to packed data
    
    uint16_t bitOffset = 0;
    for (uint8_t i = 0; i < len; i++) {
        // Extract 5-bit code from packed data
        uint8_t byteIndex = bitOffset / 8;
        uint8_t bitInByte = bitOffset % 8;
        
        uint8_t code;
        if (bitInByte <= 3) {
            // Code fits in current byte
            code = (data[byteIndex] >> bitInByte) & 0x1F;
        } else {
            // Code spans two bytes
            uint8_t lowBits = (data[byteIndex] >> bitInByte);
            uint8_t highBits = (data[byteIndex + 1] << (8 - bitInByte));
            code = (lowBits | highBits) & 0x1F;
        }
        
        if (code < sizeof(chord_char_lookup)) {
            send_char(chord_char_lookup[code]);
        }
        
        bitOffset += 5;
    }
}
""".trimIndent()
}

