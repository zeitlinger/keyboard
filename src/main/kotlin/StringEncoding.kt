data class EncodedStringData(
    val decoder: String?,
    val stringOffsets: Map<String, Int>,
)

data class StringEncoding(
    val encodedData: Map<Int, ByteArray>,
    val charToCode: Map<Char, Int>,
    val codeToChar: Map<Int, Char>,
)

fun encodeStrings(strings: Collection<String>): EncodedStringData {
    val unique = strings.distinct().sorted()
    if (unique.isEmpty()) {
        return EncodedStringData(null, emptyMap())
    }

    val outputs = unique.mapIndexed { index, value -> index to value }.toMap()
    val encoding = tryEncodeStrings(outputs)

    val offsets = mutableMapOf<String, Int>()
    var currentOffset = 0
    for ((state, value) in outputs.toSortedMap()) {
        offsets[value] = currentOffset
        currentOffset += encoding.encodedData.getValue(state).size
    }

    return EncodedStringData(
        decoder = generateStringDecoder(encoding),
        stringOffsets = offsets,
    )
}

private fun tryEncodeStrings(outputs: Map<Int, String>): StringEncoding {
    val charFreq = mutableMapOf<Char, Int>()
    outputs.values.forEach { str ->
        str.forEach { char ->
            charFreq[char] = charFreq.getOrDefault(char, 0) + 1
        }
    }

    val sortedChars = charFreq.entries.sortedByDescending { it.value }.map { it.key }
    val maxChars = 14 + 32
    if (sortedChars.size > maxChars) {
        throw IllegalArgumentException(
            "Magic string encoding supports max $maxChars characters, got ${sortedChars.size} unique characters",
        )
    }

    val charToCode = mutableMapOf<Char, Int>()
    sortedChars.forEachIndexed { index, char ->
        val code = if (index < 14) index else 0xE0 + (index - 14)
        charToCode[char] = code
    }
    val codeToChar = charToCode.entries.associate { it.value to it.key }

    val encodedData = mutableMapOf<Int, ByteArray>()
    outputs.forEach { (state, str) ->
        val dataBytes = mutableListOf<Byte>()
        var currentByte = 0
        var isHighNibble = true

        str.forEach { char ->
            val code = charToCode.getValue(char)
            if (code < 14) {
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
                if (!isHighNibble) {
                    currentByte = currentByte or 0x0F
                    dataBytes.add(currentByte.toByte())
                    isHighNibble = true
                    currentByte = 0
                }
                dataBytes.add(code.toByte())
            }
        }

        if (!isHighNibble) {
            dataBytes.add(currentByte.toByte())
        }

        val encoded = ByteArray(1 + dataBytes.size)
        encoded[0] = str.length.toByte()
        dataBytes.forEachIndexed { index, byte ->
            encoded[1 + index] = byte
        }
        encodedData[state] = encoded
    }

    return StringEncoding(encodedData, charToCode, codeToChar)
}

private fun generateStringDecoder(encoding: StringEncoding): String {
    val fourBitChars = mutableListOf<Char>()
    val eightBitChars = mutableListOf<Pair<Int, Char>>()

    encoding.codeToChar.entries.sortedBy { it.key }.forEach { (code, char) ->
        if (code < 14) {
            while (fourBitChars.size < code) {
                fourBitChars.add('\u0000')
            }
            fourBitChars.add(char)
        } else {
            eightBitChars.add(code to char)
        }
    }

    val fourBitLookup =
        fourBitChars.map { char ->
            val escapedChar =
                when (char) {
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

    val eightBitLookup =
        if (eightBitChars.isNotEmpty()) {
            "static const char magic_char_extended[] = {\n" +
                "    " +
                eightBitChars
                    .map { (_, char) ->
                        val escapedChar =
                            when (char) {
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

    val allEncodedBytes = mutableListOf<Byte>()
    encoding.encodedData.entries.sortedBy { it.key }.forEach { (_, bytes) ->
        allEncodedBytes.addAll(bytes.toList())
    }
    val hexLines =
        allEncodedBytes.chunked(16).map { chunk ->
            "    " + chunk.joinToString(", ") { "0x%02x".format(it.toInt() and 0xFF) }
        }

    return """
// Magic string decoder lookup tables
static const char magic_char_4bit[] = {
    ${fourBitLookup.joinToString(", ")}
};

${eightBitLookup}static const uint8_t magic_string_data[] = {
${hexLines.joinToString(",\n")}
};

static void magic_decode_send(uint16_t offset) {
    const uint8_t* data = magic_string_data + offset;
    uint8_t len = data[0];
    data++;

    uint8_t byteIndex = 0;
    bool highNibble = true;
    uint8_t charCount = 0;

    while (charCount < len) {
        uint8_t code;
        char c = '\0';

        if (highNibble) {
            code = (data[byteIndex] >> 4) & 0x0F;
            if (code >= 14) {
                code = data[byteIndex];
                byteIndex++;
                highNibble = true;
                if (code >= 0xE0 && code < 0xE0 + sizeof(magic_char_extended)) {
                    c = magic_char_extended[code - 0xE0];
                    send_char(c);
                    charCount++;
                }
            } else {
                highNibble = false;
                if (code < sizeof(magic_char_4bit)) {
                    c = magic_char_4bit[code];
                    send_char(c);
                    charCount++;
                }
            }
        } else {
            code = data[byteIndex] & 0x0F;
            byteIndex++;
            highNibble = true;
            if (code == 0x0F) {
                continue;
            }
            if (code < sizeof(magic_char_4bit)) {
                c = magic_char_4bit[code];
                send_char(c);
                charCount++;
            }
        }
    }
}

static void magic_decode_send_cap(uint16_t offset, char suffix) {
    if (magic_capitalize_next) {
        add_oneshot_mods(MOD_BIT(KC_LSFT));
    }
    magic_decode_send(offset);
    if (suffix != '\0') {
        set_suffix_state(suffix);
    }
    magic_capitalize_next = false;
}

        """.trimIndent()
}
