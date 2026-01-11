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

fun generateChordTransitions(translator: QmkTranslator, chordInfo: ChordInfo): String {
    val lines = mutableListOf<String>()

    for ((state, keyMap) in chordInfo.transitions.toSortedMap()) {
        val chordComment = chordInfo.stateToChord[state]?.let { "        // $it" } ?: ""
        if (chordComment.isNotEmpty()) {
            lines.add(chordComment)
        }
        lines.add("        case $state:")
        for ((key, nextState) in keyMap.toSortedMap()) {
            val qmkKey = translator.toQmkIgnoringPosition(key)

            // Add comment showing what this transition leads to
            val comment = if (nextState >= 0) {
                // nextState is a byte offset - look up the output string
                chordInfo.outputs[nextState]?.let { output -> " // \"$output\"" } ?: ""
            } else {
                // nextState is another transition state - show the chord prefix
                chordInfo.stateToChord[nextState]?.let { chord -> " // $chord..." } ?: ""
            }

            lines.add("            if (keycode == $qmkKey) return $nextState;$comment")
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
    val decoder: String?, // Optional decoder function
    val remappedChordInfo: ChordInfo? = null, // ChordInfo with byte offsets as states
    val magicStringOffsets: Map<String, Int> = emptyMap() // magic string -> byte offset
)

fun generateChordOutputs(chordInfo: ChordInfo, magicStrings: List<String> = emptyList()): EncodedChordData {
    // Combine chord outputs and magic strings for unified encoding
    val allOutputs = chordInfo.outputs.toMutableMap()
    val magicStringToTempState = mutableMapOf<String, Int>()
    var tempState = chordInfo.outputs.keys.maxOrNull()?.let { it + 1 } ?: 0

    // Assign temporary states to magic strings for encoding
    magicStrings.forEach { str ->
        if (str !in magicStringToTempState.keys) {
            magicStringToTempState[str] = tempState++
            allOutputs[magicStringToTempState[str]!!] = str
        }
    }

    // Try encoding all strings together
    val encodingResult = tryEncodeChordStrings(allOutputs)

    // Compute byte offset mapping for chord outputs
    val stateToByteOffset = mutableMapOf<Int, Int>()
    var currentOffset = 0
    for ((state, _) in allOutputs.toSortedMap()) {
        stateToByteOffset[state] = currentOffset
        currentOffset += encodingResult.encodedData[state]!!.size
    }

    // Build magic string offsets map
    val magicStringOffsets = mutableMapOf<String, Int>()
    magicStringToTempState.forEach { (str, state) ->
        magicStringOffsets[str] = stateToByteOffset[state]!!
    }

    // Remap chord info: transition states keep negative, output states become byte offsets
    val remappedChordInfo = remapChordInfoStates(chordInfo, stateToByteOffset)

    return EncodedChordData(
        decoder = generateDecoder(encodingResult),
        remappedChordInfo = remappedChordInfo,
        magicStringOffsets = magicStringOffsets
    )
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

data class ChordEncoding(
    val encodedData: Map<Int, ByteArray>, // state -> encoded bytes
    val charToCode: Map<Char, Int>, // character -> encoding value
    val codeToChar: Map<Int, Char>, // encoding value -> character
    val dataSize: Int, // Raw data bytes
    val decoderSize: Int, // Decoder overhead
    val totalSize: Int // Total bytes used (data + decoder overhead)
)

private fun tryEncodeChordStrings(outputs: Map<Int, String>): ChordEncoding {
    // Build character frequency map
    val charFreq = mutableMapOf<Char, Int>()
    outputs.values.forEach { str ->
        str.forEach { char ->
            charFreq[char] = charFreq.getOrDefault(char, 0) + 1
        }
    }

    // Create sorted character list by frequency (most common first)
    val sortedChars = charFreq.entries.sortedByDescending { it.value }.map { it.key }

    // 4/8-bit encoding scheme:
    // - First 14 characters (codes 0-13) use 4 bits
    // - Remaining characters use 8 bits with 0xE or 0xF prefix (1110xxxx or 1111xxxx patterns)
    // - This allows up to 14 + 32 = 46 unique characters
    val maxChars = 14 + 32
    if (sortedChars.size > maxChars) {
        throw IllegalArgumentException("Chord encoding supports max $maxChars characters, got ${sortedChars.size} unique characters")
    }

    // Assign codes:
    // - 0-13 (0000-1101): 4-bit codes for most common characters
    // - 0xE0-0xEF, 0xF0-0xFF: 8-bit codes for less common characters
    val charToCode = mutableMapOf<Char, Int>()
    sortedChars.forEachIndexed { index, char ->
        val code = if (index < 14) {
            index  // 0-13: use 4 bits directly
        } else {
            // 14+: use 8-bit codes starting at 0xE0
            0xE0 + (index - 14)
        }
        charToCode[char] = code
    }
    val codeToChar = charToCode.entries.associate { it.value to it.key }

    // Encode strings with 4/8-bit variable-length encoding
    val encodedData = mutableMapOf<Int, ByteArray>()
    var totalDataSize = 0

    outputs.forEach { (state, str) ->
        // Calculate how many nibbles/bytes needed
        val dataBytes = mutableListOf<Byte>()
        var currentByte = 0
        var isHighNibble = true  // Start with high nibble

        str.forEach { char ->
            val code = charToCode[char] ?: 0

            if (code < 14) {
                // 4-bit code - pack into nibbles
                if (isHighNibble) {
                    currentByte = code shl 4
                    isHighNibble = false
                } else {
                    currentByte = currentByte or code
                    dataBytes.add(currentByte.toByte())
                    isHighNibble = true
                    currentByte = 0
                }
            } else {
                // 8-bit code - need to flush current byte first if we have a high nibble
                if (!isHighNibble) {
                    dataBytes.add(currentByte.toByte())
                    isHighNibble = true
                    currentByte = 0
                }
                // Add the full 8-bit code
                dataBytes.add(code.toByte())
            }
        }

        // Flush remaining nibble if any
        if (!isHighNibble) {
            dataBytes.add(currentByte.toByte())
        }

        // Create final encoded array: 1 byte for length + data bytes
        val encoded = ByteArray(1 + dataBytes.size)
        encoded[0] = str.length.toByte()
        dataBytes.forEachIndexed { index, byte ->
            encoded[1 + index] = byte
        }

        encodedData[state] = encoded
        totalDataSize += encoded.size
    }

    // Calculate decoder overhead:
    // - Lookup table for 8-bit codes: up to 32 characters
    // - Function code: ~120 bytes (simpler byte-aligned logic)
    // - Global buffer declaration: ~20 bytes
    val extendedCharsCount = if (sortedChars.size > 14) sortedChars.size - 14 else 0
    val lookupTableSize = extendedCharsCount
    val functionCodeSize = 120
    val decoderOverhead = lookupTableSize + functionCodeSize

    val totalSize = totalDataSize + decoderOverhead

    return ChordEncoding(encodedData, charToCode, codeToChar, totalDataSize, decoderOverhead, totalSize)
}

private fun generateDecoder(encoding: ChordEncoding): String {
    // Separate the 4-bit codes (0-13) and 8-bit codes (0xE0+)
    val fourBitChars = mutableListOf<Char>()
    val eightBitChars = mutableListOf<Pair<Int, Char>>()

    encoding.codeToChar.entries.sortedBy { it.key }.forEach { (code, char) ->
        if (code < 14) {
            // Ensure we have the right index
            while (fourBitChars.size < code) {
                fourBitChars.add('\u0000')
            }
            fourBitChars.add(char)
        } else {
            eightBitChars.add(code to char)
        }
    }

    // Build 4-bit lookup table
    val fourBitLookup = fourBitChars.map { char ->
        val escapedChar = when (char) {
            '\u0000' -> "\\0"
            '\'' -> "\\'"
            '\\' -> "\\\\"
            '\n' -> "\\n"
            '\r' -> "\\r"
            '\t' -> "\\t"
            else -> char.toString()
        }
        "'$escapedChar'"
    }

    // Build 8-bit lookup entries (only for extended codes)
    val eightBitLookup = if (eightBitChars.isNotEmpty()) {
        "static const char chord_char_extended[] = {\n" +
        "    " + eightBitChars.map { (_, char) ->
            val escapedChar = when (char) {
                '\'' -> "\\'"
                '\\' -> "\\\\"
                '\n' -> "\\n"
                '\r' -> "\\r"
                '\t' -> "\\t"
                else -> char.toString()
            }
            "'$escapedChar'"
        }.joinToString(", ") + "\n" +
        "};\n\n"
    } else {
        ""
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
// Chord string decoder lookup tables
// 4-bit codes (0-13) for most common characters
static const char chord_char_4bit[] = {
    ${fourBitLookup.joinToString(", ")}
};

// 8-bit codes (0xE0+) for less common characters
$eightBitLookup// Global buffer containing all 4/8-bit variable-length encoded chord strings
static const uint8_t chord_data[] = {
${hexLines.joinToString(",\n")}
};

// Decode and send 4/8-bit variable-length encoded chord string from buffer
static void chord_decode_send(uint16_t offset) {
    const uint8_t* data = chord_data + offset;
    uint8_t len = data[0];  // First byte is string length
    data++;  // Move to encoded data
    
    uint8_t byteIndex = 0;
    bool highNibble = true;  // Start with high nibble
    
    for (uint8_t i = 0; i < len; i++) {
        uint8_t code;
        
        if (highNibble) {
            // Read high nibble
            code = (data[byteIndex] >> 4) & 0x0F;
            
            // Check if this is a 4-bit or 8-bit code
            if (code >= 14) {
                // This is the start of an 8-bit code - read the full byte
                code = data[byteIndex];
                byteIndex++;
                highNibble = true;  // Next read starts at high nibble
                
                // Decode 8-bit extended character
                if (code >= 0xE0 && code < 0xE0 + sizeof(chord_char_extended)) {
                    send_char(chord_char_extended[code - 0xE0]);
                }
            } else {
                // This is a 4-bit code
                highNibble = false;  // Next read is low nibble
                
                // Decode 4-bit character
                if (code < sizeof(chord_char_4bit)) {
                    send_char(chord_char_4bit[code]);
                }
            }
        } else {
            // Read low nibble
            code = data[byteIndex] & 0x0F;
            byteIndex++;
            highNibble = true;  // Next read starts at high nibble
            
            // Decode 4-bit character
            if (code < sizeof(chord_char_4bit)) {
                send_char(chord_char_4bit[code]);
            }
        }
    }
}
""".trimIndent()
}

