/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;
#define CHORD_ROOT -1
#define CHORD_INACTIVE -10000
#define CHORD_MODIFIER -10001
int chord_state = CHORD_INACTIVE; // negative = transition states, non-negative = byte offsets
int chord_depth = 0; // Track number of letters in current chord

// Chord string decoder lookup tables
// 4-bit codes (0-13) for most common characters
static const char chord_char_4bit[] = {
    'e', 'r', 't', 'a', 'n', 'o', 'i', 's', 'l', 'u', 'g', 'c', 'h', 'y'
};

// 8-bit codes (0xE0+) for less common characters
static const char chord_char_extended[] = {
    'm', 'p', 'd', 'b', 'v', 'w', 'f', 'k', ' ', '\'', 'x', 'j', 'z', '.', 'G', 'q', '@', 'S', 'P', 'O', 'T', 'H', 'L', 'B', 'Z', '/'
};

// Global buffer containing all 4/8-bit variable-length encoded chord strings
static const uint8_t chord_data[] = {
    0x0a, 0xf8, 0x06, 0x28, 0x64, 0xa0, 0x10, 0x12, 0xe2, 0x0b, 0x83, 0x13, 0x26, 0xe4, 0x0f, 0xe8,
    0xb5, 0x4f, 0xe6, 0x6a, 0x0b, 0xf1, 0xe1, 0x16, 0x4a, 0xe8, 0xf7, 0x55, 0x20, 0x0c, 0xee, 0x13,
    0xe6, 0x34, 0x3f, 0xe8, 0xf6, 0x3f, 0xe3, 0x70, 0x09, 0xeb, 0x3f, 0xe4, 0x33, 0xa0, 0x42, 0x06,
    0x7f, 0xe1, 0x16, 0x4a, 0x0e, 0xf1, 0xe1, 0x16, 0x4a, 0xe8, 0x72, 0x31, 0x20, 0x10, 0x06, 0xee,
    0x62, 0xf5, 0x9f, 0xe3, 0x08, 0x51, 0xa3, 0x46, 0xec, 0x00, 0x05, 0x37, 0xd4, 0xb0, 0x05, 0x7f,
    0xe0, 0x68, 0x00, 0x09, 0x20, 0x80, 0xe0, 0x02, 0x1d, 0x06, 0x3b, 0x29, 0x38, 0x08, 0x10, 0x75,
    0x91, 0xb0, 0x09, 0x0f, 0xea, 0xb0, 0xe1, 0x26, 0x54, 0x08, 0x0f, 0xea, 0x67, 0x26, 0x4a, 0x05,
    0xc2, 0x2f, 0xe1, 0x70, 0x07, 0x0f, 0xea, 0x0b, 0x92, 0x00, 0x07, 0x0f, 0xea, 0x3f, 0xe0, 0xe1,
    0x80, 0x06, 0x0f, 0xea, 0xe1, 0x51, 0x20, 0x07, 0xb5, 0x42, 0x0f, 0xea, 0x20, 0x05, 0xe5, 0x51,
    0x1d, 0x08, 0x64, 0x20, 0x14, 0x38, 0x05, 0xe5, 0xc0, 0x10, 0x07, 0xe5, 0x62, 0xc5, 0x92, 0x05,
    0xe5, 0x15, 0x4a, 0x04, 0xe5, 0x68, 0x80, 0x05, 0xe5, 0xc6, 0xbc, 0x04, 0xe5, 0xc0, 0x40, 0x04,
    0xe5, 0x38, 0xe7, 0x05, 0x3f, 0xe5, 0x36, 0x20, 0x08, 0xe5, 0x59, 0x8f, 0xe2, 0x4f, 0xe9, 0x20,
    0x05, 0xe5, 0x59, 0x8f, 0xe2, 0x0a, 0x0f, 0xe4, 0x01, 0xd2, 0xc6, 0x4a, 0x05, 0xe4, 0x38, 0x90,
    0x05, 0x40, 0xe4, 0x01, 0x04, 0x5f, 0xe4, 0x01, 0x06, 0x45, 0x26, 0xb0, 0x08, 0x70, 0x1f, 0xe4,
    0x6b, 0x07, 0x07, 0xe4, 0x01, 0x76, 0x54, 0x04, 0xe4, 0x01, 0xd0, 0x09, 0x3f, 0xe4, 0x36, 0x83,
    0xe3, 0x80, 0x04, 0xe4, 0x56, 0xe2, 0x07, 0xb5, 0x42, 0x16, 0xe3, 0x04, 0x0f, 0xe4, 0x04, 0x09,
    0x2c, 0x34, 0xe7, 0xe8, 0xd5, 0x90, 0x06, 0x2c, 0x59, 0xac, 0x0d, 0xf3, 0xe1, 0x04, 0xf4, 0x08,
    0x0f, 0xe0, 0x02, 0x1d, 0x05, 0x2c, 0x01, 0x00, 0x07, 0x2c, 0x59, 0xac, 0x20, 0x07, 0x2c, 0x15,
    0x9a, 0xc0, 0x04, 0x26, 0xe0, 0x00, 0x05, 0x52, 0xc0, 0x10, 0x05, 0x2c, 0x07, 0x00, 0x05, 0x25,
    0xe2, 0x3d, 0x04, 0x2d, 0xe1, 0x00, 0x06, 0x20, 0x43, 0x42, 0x05, 0x2c, 0x64, 0xe7, 0x06, 0x7d,
    0x72, 0x0f, 0xe0, 0x07, 0x79, 0xe1, 0xe1, 0x51, 0x20, 0x08, 0x79, 0x1f, 0xe1, 0x16, 0x70, 0x06,
    0x78, 0x5f, 0xe5, 0x8d, 0x07, 0x79, 0xe3, 0xeb, 0x0b, 0x20, 0x07, 0x75, 0xe0, 0x05, 0x40, 0x05,
    0x7c, 0x31, 0x00, 0x06, 0x70, 0x31, 0xbc, 0x04, 0x2c, 0x67, 0x04, 0x73, 0xe0, 0x00, 0x06, 0x72,
    0x16, 0x4a, 0x06, 0xe5, 0x37, 0x4f, 0xe9, 0x20, 0x06, 0x7c, 0x59, 0x8f, 0xe2, 0x07, 0x10, 0x38,
    0x6f, 0xec, 0x00, 0x05, 0xd0, 0x31, 0x70, 0x04, 0x21, 0x90, 0x04, 0x2c, 0x0d, 0x07, 0x10, 0xef,
    0x90, 0x72, 0x06, 0x31, 0x59, 0x4f, 0xe2, 0x05, 0xef, 0x90, 0x1d, 0x06, 0x10, 0x29, 0x14, 0x05,
    0x16, 0xac, 0x20, 0x06, 0x10, 0xe4, 0x60, 0xe5, 0x06, 0x16, 0xac, 0x27, 0x05, 0x10, 0x3f, 0xe2,
    0xd0, 0x07, 0xe1, 0x15, 0xa1, 0x3f, 0xe0, 0x05, 0x01, 0x15, 0x10, 0x05, 0x15, 0x92, 0x00, 0x06,
    0x10, 0x38, 0x8d, 0x08, 0xe1, 0x15, 0xe3, 0x3f, 0xe3, 0x8d, 0x06, 0xe1, 0x9f, 0xe3, 0x86, 0xb0,
    0x06, 0xe1, 0x31, 0x04, 0x20, 0x0a, 0xf2, 0x15, 0xe0, 0x02, 0xc0, 0x97, 0x07, 0xe1, 0x15, 0xe2,
    0x9b, 0x20, 0x07, 0xe1, 0x15, 0xe3, 0x80, 0xe0, 0x05, 0xe1, 0x56, 0x42, 0x05, 0xe1, 0x83, 0xb0,
    0x07, 0xe1, 0x16, 0xe4, 0x3b, 0xd0, 0x07, 0xe1, 0x15, 0xe0, 0x67, 0x00, 0x06, 0xe1, 0x80, 0x37,
    0x00, 0x06, 0xe1, 0x05, 0xe1, 0x80, 0x07, 0xb5, 0xe0, 0xe1, 0x34, 0xd0, 0x06, 0x04, 0x59, 0xac,
    0x07, 0x34, 0x52, 0xc0, 0x10, 0x06, 0x67, 0x79, 0x07, 0x04, 0x64, 0x25, 0x08, 0x34, 0xd2, 0xc6,
    0x4a, 0x06, 0x49, 0xe0, 0xe3, 0x01, 0x07, 0x64, 0x72, 0x03, 0xe2, 0x06, 0x34, 0xdf, 0xe5, 0x3d,
    0x06, 0x76, 0x4a, 0x80, 0x0a, 0x94, 0xe2, 0x01, 0x72, 0x34, 0xe2, 0x06, 0xe0, 0xd7, 0x08, 0xe6,
    0x05, 0xe0, 0x97, 0x6b, 0x07, 0xe6, 0x03, 0x29, 0x10, 0x05, 0xe0, 0x3f, 0xeb, 0x51, 0x06, 0xe0,
    0x64, 0x92, 0x00, 0x05, 0xe0, 0x6a, 0xc2, 0x07, 0xe0, 0x07, 0x73, 0xa0, 0x04, 0x75, 0xe0, 0x00,
    0x06, 0xe0, 0x02, 0xc5, 0xe2, 0x04, 0x8a, 0x2f, 0xe0, 0x04, 0xe0, 0x51, 0x00, 0x04, 0x54, 0x8d,
    0x06, 0x38, 0xe0, 0x57, 0x20, 0x05, 0x83, 0x20, 0x10, 0x05, 0x38, 0x54, 0xa0, 0x14, 0xa1, 0x0a,
    0x51, 0xf0, 0xec, 0x06, 0x28, 0x64, 0xa0, 0x1f, 0xed, 0xe2, 0x00, 0x05, 0x83, 0x1a, 0x00, 0x05,
    0x86, 0xac, 0x20, 0x06, 0xc0, 0x38, 0x2c, 0x05, 0x80, 0x3f, 0xe4, 0x00, 0x04, 0xe5, 0x62, 0xc0,
    0x04, 0x38, 0x75, 0x05, 0xb8, 0x37, 0x70, 0x05, 0x80, 0xe4, 0x08, 0x04, 0x86, 0xe7, 0x00, 0x07,
    0xef, 0x96, 0xbf, 0xe7, 0x8d, 0x06, 0xb3, 0x88, 0x01, 0x04, 0xe5, 0x51, 0xe7, 0x04, 0xe7, 0x45,
    0xe5, 0x04, 0xeb, 0x3f, 0xe4, 0x30, 0x04, 0xe7, 0x64, 0xe2, 0x05, 0xbc, 0x0b, 0xe7, 0x04, 0xe7,
    0x00, 0xe1, 0x04, 0xe0, 0x3f, 0xe7, 0x00, 0x03, 0xe7, 0x0d, 0x06, 0xb5, 0x4f, 0xe6, 0x6a, 0x08,
    0xef, 0x90, 0x72, 0x65, 0x40, 0x05, 0x0f, 0xe4, 0x01, 0xd0, 0x05, 0xa9, 0x07, 0x70, 0x05, 0xa1,
    0x03, 0x20, 0x05, 0xa1, 0x59, 0xe1, 0x07, 0xa0, 0x40, 0x13, 0x80, 0x06, 0xa6, 0xe4, 0x64, 0xa0,
    0x06, 0xee, 0x10, 0xa5, 0x10, 0x06, 0xa8, 0x34, 0xb0, 0x07, 0xee, 0x13, 0xe6, 0x34, 0x30, 0x05,
    0x3a, 0x36, 0x40, 0x05, 0xe6, 0x51, 0x2d, 0x05, 0xe6, 0x59, 0x4f, 0xe2, 0x08, 0x75, 0xe6, 0x2f,
    0xe5, 0x31, 0x00, 0x0b, 0x64, 0xe6, 0x51, 0xe0, 0x32, 0x65, 0x40, 0x04, 0xc3, 0xe4, 0x00, 0x06,
    0xe6, 0x64, 0xa0, 0x10, 0x05, 0xe6, 0x61, 0x72, 0x04, 0x2c, 0x04, 0x1d, 0xa1, 0x0a, 0x51, 0xed,
    0xec, 0x06, 0x28, 0x64, 0xa0, 0x1f, 0xf0, 0xa1, 0x3f, 0xe6, 0x34, 0x3f, 0xed, 0xb5, 0xe0, 0x04,
    0xe6, 0x00, 0x80, 0x05, 0x3f, 0xe6, 0x20, 0x10, 0x05, 0xe6, 0x38, 0x70, 0x05, 0xe6, 0x36, 0x87,
    0x04, 0xe6, 0x15, 0xe0, 0x07, 0x38, 0x10, 0x3f, 0xe2, 0xd0, 0x08, 0xe1, 0x15, 0xe2, 0x9b, 0x27,
    0x05, 0x2c, 0x06, 0x10, 0x06, 0x6f, 0xe0, 0xe1, 0x51, 0x20, 0x05, 0xe3, 0x96, 0x8f, 0xe2, 0x06,
    0xe2, 0x91, 0x64, 0xa0, 0x04, 0x2c, 0x34, 0x04, 0x2c, 0x0f, 0xe0, 0x14, 0xec, 0x06, 0x28, 0x64,
    0xa0, 0x1f, 0xf0, 0xaf, 0xe0, 0x36, 0x8f, 0xed, 0xb5, 0xe0, 0x08, 0xe2, 0x07, 0xb1, 0x6f, 0xe3,
    0x00, 0x04, 0xe2, 0x32, 0x30, 0x06, 0xc3, 0xe2, 0x4f, 0xe9, 0x20, 0x06, 0xe2, 0x6f, 0xe2, 0x4f,
    0xe9, 0x20, 0x06, 0xe1, 0x58, 0x6b, 0xd0, 0x07, 0xb9, 0x11, 0x04, 0x20, 0x06, 0x3b, 0x15, 0x77,
    0x08, 0xb5, 0x42, 0x64, 0x90, 0x04, 0xe3, 0x00, 0x40, 0x07, 0xe1, 0x15, 0xeb, 0x0b, 0x20, 0x05,
    0xb8, 0x6b, 0xe7, 0x08, 0x10, 0x70, 0x31, 0xbc, 0x07, 0x70, 0x1f, 0xe4, 0x6b, 0x00, 0x08, 0x3b,
    0x29, 0x38, 0x8d, 0x05, 0xb5, 0x47, 0x20, 0x08, 0xb5, 0x98, 0xe2, 0x4f, 0xe9, 0x20, 0x05, 0xb5,
    0x98, 0xe2, 0x04, 0xe3, 0x5f, 0xe2, 0xd0, 0x08, 0xe3, 0x97, 0x64, 0x07, 0x70, 0x05, 0xe3, 0x10,
    0x3f, 0xe7, 0x06, 0xe3, 0x0b, 0x5f, 0xe0, 0x00, 0x07, 0xe3, 0x02, 0xe5, 0x00, 0x40, 0x05, 0xe3,
    0x06, 0x4a, 0x06, 0xe3, 0x0c, 0x64, 0xe2, 0x05, 0xe3, 0x0a, 0x34, 0x07, 0xe3, 0x55, 0x80, 0x34,
    0x0d, 0x5f, 0xe3, 0x70, 0x1f, 0xe4, 0x3f, 0xe3, 0x68, 0x62, 0xd0, 0x05, 0x3f, 0xe3, 0x59, 0x20,
    0x06, 0x0b, 0x39, 0x70, 0x06, 0x50, 0x74, 0xe9, 0x20, 0x03, 0x50, 0x70, 0x04, 0x54, 0xe9, 0x20,
    0x02, 0x51, 0x02, 0x0d, 0x03, 0xe9, 0xe4, 0x00, 0x03, 0x97, 0x20, 0x03, 0x45, 0xe5, 0x03, 0x04,
    0x20, 0x02, 0x8d, 0x03, 0x65, 0x40, 0x03, 0x64, 0xa0, 0x02, 0x01, 0x02, 0x04, 0x04, 0x2c, 0x0f,
    0xe8, 0x04, 0x34, 0xe2, 0xe8, 0x05, 0xe8, 0xe3, 0x92, 0xe8, 0x05, 0xe8, 0x34, 0xe2, 0xe8, 0x02,
    0xed, 0xf9
};

char last_chord_char = '\0'; // Track last character sent in chord for suffix modifications

// Decode and send 4/8-bit variable-length encoded chord string from buffer
static void chord_decode_send(uint16_t offset) {
    const uint8_t* data = chord_data + offset;
    uint8_t len = data[0];  // First byte is string length
    data++;  // Move to encoded data

    uint8_t byteIndex = 0;
    bool highNibble = true;  // Start with high nibble
    uint8_t charCount = 0;  // Count of characters actually sent

    last_chord_char = '\0'; // Reset at start

    while (charCount < len) {
        uint8_t code;
        char c = '\0';

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
                    c = chord_char_extended[code - 0xE0];
                    send_char(c);
                    last_chord_char = c;
                    charCount++;
                }
            } else {
                // This is a 4-bit code
                highNibble = false;  // Next read is low nibble

                // Decode 4-bit character
                if (code < sizeof(chord_char_4bit)) {
                    c = chord_char_4bit[code];
                    send_char(c);
                    last_chord_char = c;
                    charCount++;
                }
            }
        } else {
            // Read low nibble
            code = data[byteIndex] & 0x0F;
            byteIndex++;
            highNibble = true;  // Next read starts at high nibble

            // Check if this is a filler nibble (0xF means skip)
            if (code == 0x0F) {
                // Skip this nibble, it's just padding
                continue;
            }

            // Decode 4-bit character
            if (code < sizeof(chord_char_4bit)) {
                c = chord_char_4bit[code];
                send_char(c);
                last_chord_char = c;
                charCount++;
            }
        }
    }
}

int chord_transition(int state, uint16_t keycode) {
    switch (state) {
                // z
                case -215:
                    if (keycode == KC_COMMA) return 78; // "smile"
                    if (keycode == KC_DOT) return 74; // "async"
                    if (keycode == KC_A) return 68; // "organize"
                    if (keycode == KC_E) return 62; // "GitHub"
                    if (keycode == KC_H) return 52; // "Spring starter"
                    if (keycode == KC_I) return 47; // "spring"
                    if (keycode == KC_J) return 40; // "javaagent"
                    if (keycode == KC_O) return 29; // "Grafana Labs"
                    if (keycode == KC_U) return 20; // "Spring Boot"
                    if (keycode == KC_Y) return 7; // "declarative config"
                    if (keycode == KC_Z) return 0; // "Zeitlinger"
                    break;
                // x
                case -204:
                    if (keycode == KC_SPC) return 135; // "context"
                    if (keycode == KC_DOT) return 129; // "export"
                    if (keycode == KC_A) return 122; // "example"
                    if (keycode == KC_E) return 116; // "execute"
                    if (keycode == KC_H) return 111; // "https"
                    if (keycode == KC_I) return 105; // "existing"
                    if (keycode == KC_J) return 98; // "exception"
                    if (keycode == KC_R) return 93; // "resource"
                    if (keycode == KC_U) return 89; // "actual"
                    if (keycode == KC_Y) return 83; // "telemetry"
                    break;
                // w
                case -191:
                    if (keycode == KC_SPC) return 192; // "would"
                    if (keycode == KC_COMMA) return 184; // "wouldn't"
                    if (keycode == KC_DOT) return 179; // "await"
                    if (keycode == KC_A) return 175; // "walk"
                    if (keycode == KC_E) return 171; // "when"
                    if (keycode == KC_H) return 167; // "which"
                    if (keycode == KC_I) return 163; // "will"
                    if (keycode == KC_J) return 159; // "wrong"
                    if (keycode == KC_O) return 154; // "without"
                    if (keycode == KC_R) return 150; // "where"
                    if (keycode == KC_U) return 145; // "internal"
                    if (keycode == KC_Y) return 141; // "worry"
                    break;
                // v
                case -178:
                    if (keycode == KC_SPC) return 251; // "even"
                    if (keycode == KC_COMMA) return 246; // "contrib"
                    if (keycode == KC_DOT) return 242; // "void"
                    if (keycode == KC_A) return 235; // "available"
                    if (keycode == KC_E) return 231; // "very"
                    if (keycode == KC_H) return 226; // "version"
                    if (keycode == KC_I) return 220; // "services"
                    if (keycode == KC_J) return 216; // "notice"
                    if (keycode == KC_O) return 212; // "over"
                    if (keycode == KC_R) return 208; // "never"
                    if (keycode == KC_U) return 204; // "value"
                    if (keycode == KC_Y) return 197; // "everything"
                    break;
                // t
                case -164:
                    if (keycode == KC_SPC) return 314; // "think"
                    if (keycode == KC_COMMA) return 310; // "tenant"
                    if (keycode == KC_DOT) return 306; // "type"
                    if (keycode == KC_A) return 302; // "today"
                    if (keycode == KC_E) return 298; // "these"
                    if (keycode == KC_H) return 294; // "other"
                    if (keycode == KC_I) return 290; // "time"
                    if (keycode == KC_J) return 285; // "through"
                    if (keycode == KC_O) return 280; // "thought"
                    if (keycode == KC_R) return 276; // "there"
                    if (keycode == KC_T) return 266; // "OpenTelemetry"
                    if (keycode == KC_U) return 262; // "though"
                    if (keycode == KC_Y) return 255; // "thank you"
                    break;
                // s
                case -150:
                    if (keycode == KC_SPC) return 376; // "should"
                    if (keycode == KC_COMMA) return 370; // "wasn't"
                    if (keycode == KC_DOT) return 366; // "string"
                    if (keycode == KC_A) return 362; // "same"
                    if (keycode == KC_C) return 359; // "this"
                    if (keycode == KC_E) return 355; // "search"
                    if (keycode == KC_H) return 351; // "share"
                    if (keycode == KC_I) return 346; // "someone"
                    if (keycode == KC_J) return 340; // "subject"
                    if (keycode == KC_O) return 335; // "slowly"
                    if (keycode == KC_R) return 329; // "surprise"
                    if (keycode == KC_U) return 323; // "support"
                    if (keycode == KC_Y) return 318; // "system"
                    break;
                // r
                case -133:
                    if (keycode == KC_SPC) return 447; // "really"
                    if (keycode == KC_COMMA) return 443; // "route"
                    if (keycode == KC_DOT) return 439; // "error"
                    if (keycode == KC_A) return 433; // "program"
                    if (keycode == KC_E) return 428; // "ready"
                    if (keycode == KC_G) return 424; // "rights"
                    if (keycode == KC_H) return 419; // "review"
                    if (keycode == KC_I) return 415; // "right"
                    if (keycode == KC_J) return 411; // "return"
                    if (keycode == KC_L) return 407; // "query"
                    if (keycode == KC_O) return 402; // "around"
                    if (keycode == KC_S) return 397; // "request"
                    if (keycode == KC_T) return 394; // "they"
                    if (keycode == KC_U) return 391; // "true"
                    if (keycode == KC_Y) return 387; // "years"
                    if (keycode == KC_Z) return 381; // "realize"
                    break;
                // p
                case -120:
                    if (keycode == KC_SPC) return 513; // "people"
                    if (keycode == KC_COMMA) return 508; // "please"
                    if (keycode == KC_DOT) return 502; // "promise"
                    if (keycode == KC_A) return 496; // "privacy"
                    if (keycode == KC_E) return 492; // "place"
                    if (keycode == KC_I) return 488; // "point"
                    if (keycode == KC_J) return 482; // "problem"
                    if (keycode == KC_O) return 476; // "product"
                    if (keycode == KC_P) return 469; // "Prometheus"
                    if (keycode == KC_R) return 464; // "parent"
                    if (keycode == KC_U) return 458; // "public"
                    if (keycode == KC_Y) return 451; // "probably"
                    break;
                // n
                case -108:
                    if (keycode == KC_SPC) return 564; // "understand"
                    if (keycode == KC_COMMA) return 560; // "single"
                    if (keycode == KC_A) return 555; // "anyway"
                    if (keycode == KC_D) return 550; // "instead"
                    if (keycode == KC_E) return 545; // "number"
                    if (keycode == KC_H) return 540; // "anything"
                    if (keycode == KC_I) return 537; // "into"
                    if (keycode == KC_J) return 533; // "issues"
                    if (keycode == KC_O) return 528; // "another"
                    if (keycode == KC_U) return 524; // "enough"
                    if (keycode == KC_Y) return 518; // "company"
                    break;
                // m
                case -96:
                    if (keycode == KC_SPC) return 617; // "more"
                    if (keycode == KC_COMMA) return 613; // "lgtm"
                    if (keycode == KC_DOT) return 608; // "method"
                    if (keycode == KC_A) return 604; // "some"
                    if (keycode == KC_E) return 599; // "message"
                    if (keycode == KC_H) return 595; // "might"
                    if (keycode == KC_I) return 590; // "minute"
                    if (keycode == KC_J) return 585; // "major"
                    if (keycode == KC_O) return 580; // "feature"
                    if (keycode == KC_U) return 576; // "music"
                    if (keycode == KC_Y) return 571; // "myself"
                    break;
                // l
                case -81:
                    if (keycode == KC_SPC) return 683; // "like"
                    if (keycode == KC_COMMA) return 679; // "level"
                    if (keycode == KC_DOT) return 675; // "class"
                    if (keycode == KC_A) return 672; // "also"
                    if (keycode == KC_D) return 668; // "with"
                    if (keycode == KC_E) return 663; // "leave"
                    if (keycode == KC_H) return 659; // "health"
                    if (keycode == KC_I) return 655; // "light"
                    if (keycode == KC_J) return 651; // "large"
                    if (keycode == KC_L) return 637; // "gregor@zeitlinger.de"
                    if (keycode == KC_O) return 633; // "along"
                    if (keycode == KC_R) return 629; // "later"
                    if (keycode == KC_U) return 624; // "almost"
                    if (keycode == KC_Y) return 621; // "only"
                    break;
                // k
                case -68:
                    if (keycode == KC_SPC) return 735; // "question"
                    if (keycode == KC_COMMA) return 730; // "config"
                    if (keycode == KC_DOT) return 727; // "key"
                    if (keycode == KC_A) return 722; // "make"
                    if (keycode == KC_E) return 718; // "keep"
                    if (keycode == KC_H) return 714; // "check"
                    if (keycode == KC_I) return 710; // "kind"
                    if (keycode == KC_J) return 705; // "java"
                    if (keycode == KC_O) return 701; // "know"
                    if (keycode == KC_R) return 697; // "work"
                    if (keycode == KC_U) return 693; // "caller"
                    if (keycode == KC_Y) return 687; // "quickly"
                    break;
                // g
                case -57:
                    if (keycode == KC_SPC) return 783; // "again"
                    if (keycode == KC_DOT) return 777; // "Grafana"
                    if (keycode == KC_A) return 773; // "glance"
                    if (keycode == KC_G) return 768; // "Gregor"
                    if (keycode == KC_I) return 763; // "giving"
                    if (keycode == KC_J) return 758; // "general"
                    if (keycode == KC_O) return 754; // "group"
                    if (keycode == KC_R) return 750; // "great"
                    if (keycode == KC_U) return 746; // "guess"
                    if (keycode == KC_Y) return 741; // "every"
                    break;
                // f
                case -42:
                    if (keycode == KC_SPC) return 864; // "from"
                    if (keycode == KC_COMMA) return 860; // "fails"
                    if (keycode == KC_DOT) return 856; // "false"
                    if (keycode == KC_A) return 851; // "after"
                    if (keycode == KC_E) return 847; // "feel"
                    if (keycode == KC_F) return 827; // "gregor.zeitlinger@grafana.com"
                    if (keycode == KC_H) return 824; // "then"
                    if (keycode == KC_I) return 820; // "first"
                    if (keycode == KC_J) return 815; // "finger"
                    if (keycode == KC_L) return 811; // "have"
                    if (keycode == KC_O) return 803; // "information"
                    if (keycode == KC_R) return 796; // "software"
                    if (keycode == KC_U) return 791; // "found"
                    if (keycode == KC_Y) return 787; // "forty"
                    break;
                // d
                case -28:
                    if (keycode == KC_SPC) return 939; // "didn't"
                    if (keycode == KC_COMMA) return 933; // "hadn't"
                    if (keycode == KC_DOT) return 929; // "data"
                    if (keycode == KC_A) return 922; // "describe"
                    if (keycode == KC_D) return 907; // "zeitlinger@gmail.com"
                    if (keycode == KC_E) return 903; // "them"
                    if (keycode == KC_H) return 900; // "than"
                    if (keycode == KC_I) return 895; // "during"
                    if (keycode == KC_J) return 890; // "build"
                    if (keycode == KC_O) return 884; // "import"
                    if (keycode == KC_R) return 880; // "their"
                    if (keycode == KC_U) return 874; // "products"
                    if (keycode == KC_Y) return 868; // "already"
                    break;
                // c
                case -14:
                    if (keycode == KC_SPC) return 1006; // "could"
                    if (keycode == KC_COMMA) return 999; // "couldn't"
                    if (keycode == KC_DOT) return 995; // "const"
                    if (keycode == KC_A) return 990; // "actually"
                    if (keycode == KC_E) return 984; // "service"
                    if (keycode == KC_H) return 979; // "research"
                    if (keycode == KC_I) return 975; // "click"
                    if (keycode == KC_J) return 969; // "project"
                    if (keycode == KC_N) return 965; // "been"
                    if (keycode == KC_O) return 960; // "continue"
                    if (keycode == KC_R) return 956; // "across"
                    if (keycode == KC_U) return 951; // "current"
                    if (keycode == KC_Y) return 946; // "policy"
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return 1067; // "about"
                    if (keycode == KC_COMMA) return 1056; // "observability"
                    if (keycode == KC_DOT) return 1051; // "boolean"
                    if (keycode == KC_E) return 1047; // "began"
                    if (keycode == KC_H) return 1042; // "behind"
                    if (keycode == KC_I) return 1038; // "being"
                    if (keycode == KC_J) return 1032; // "between"
                    if (keycode == KC_O) return 1026; // "become"
                    if (keycode == KC_R) return 1021; // "break"
                    if (keycode == KC_U) return 1015; // "business"
                    if (keycode == KC_Y) return 1010; // "body"
                    break;
                case -1:
                    if (keycode == KC_B) return -2; // b...
                    if (keycode == KC_C) return -14; // c...
                    if (keycode == KC_D) return -28; // d...
                    if (keycode == KC_F) return -42; // f...
                    if (keycode == KC_G) return -57; // g...
                    if (keycode == KC_K) return -68; // k...
                    if (keycode == KC_L) return -81; // l...
                    if (keycode == KC_M) return -96; // m...
                    if (keycode == KC_N) return -108; // n...
                    if (keycode == KC_P) return -120; // p...
                    if (keycode == KC_R) return -133; // r...
                    if (keycode == KC_S) return -150; // s...
                    if (keycode == KC_T) return -164; // t...
                    if (keycode == KC_V) return -178; // v...
                    if (keycode == KC_W) return -191; // w...
                    if (keycode == KC_X) return -204; // x...
                    if (keycode == KC_Z) return -215; // z...
                    break;
    default:
        // Invalid transition, stop chord mode
        return CHORD_INACTIVE;
    }
    return CHORD_INACTIVE;
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch(index) {
    case C_BASE_CHORD_KEY: return 200;
    case C_BASE_ING: return 200;
    case C_BASE_KC_B: return 200;
    case C_BASE_KC_COMMA: return 200;
    case C_BASE_KC_DOT: return 200;
    case C_BASE_KC_G: return 200;
    case C_BASE_KC_J: return 200;
    case C_BASE_KC_K: return 200;
    case C_BASE_KC_M: return 200;
    case C_BASE_KC_P: return 200;
    case C_BASE_KC_Q: return 200;
    case C_BASE_KC_V: return 200;
    case C_BASE_KC_Z: return 200;
    case C_BASE_MAGIC_A: return 200;
    case C_BASE_MAGIC_B: return 200;
    case C_FNSYM_KC_AMPR: return 200;
    case C_FNSYM_KC_ASTR: return 200;
    case C_FNSYM_KC_CIRC: return 200;
    case C_FNSYM_KC_DLR: return 200;
    case C_FNSYM_KC_F11: return 200;
    case C_FNSYM_KC_HASH: return 200;
    case C_FNSYM_KC_KP_MINUS: return 200;
    case C_FNSYM_KC_KP_PLUS: return 200;
    case C_FNSYM_KC_LABK: return 200;
    case C_FNSYM_KC_LCBR: return 200;
    case C_FNSYM_KC_LGUI: return 200;
    case C_FNSYM_KC_LPRN: return 200;
    case C_FNSYM_KC_MINUS: return 200;
    case C_FNSYM_KC_PERC: return 200;
    case C_FNSYM_KC_PIPE: return 200;
    case C_FNSYM_KC_RABK: return 200;
    case C_FNSYM_KC_RCBR: return 200;
    case C_FNSYM_KC_RPRN: return 200;
    case C_FNSYM_KC_SLASH: return 200;
    case C_FNSYM_KC_TILD: return 200;
    case C_FNSYM_LT_NUM2KC_EQUAL: return 200;
    case C_FNSYM_MO_NUM: return 200;
    case C_FNSYM_UMSMILEY: return 200;
    case C_NAV_AKC_F12: return 200;
    case C_NAV_CKC_A: return 200;
    case C_NAV_CKC_B: return 200;
    case C_NAV_CKC_C: return 200;
    case C_NAV_CKC_D: return 200;
    case C_NAV_CKC_E: return 200;
    case C_NAV_CKC_F12: return 200;
    case C_NAV_CKC_K: return 200;
    case C_NAV_CKC_P: return 200;
    case C_NAV_CKC_SLASH: return 200;
    case C_NAV_CKC_V: return 200;
    case C_NAV_CKC_W: return 200;
    case C_NAV_CKC_X: return 200;
    case C_NAV_CKC_Y: return 200;
    case C_NAV_CKC_Z: return 200;
    case C_NAV_KC_END: return 200;
    case C_NAV_KC_HOME: return 200;
    case C_NAV_KC_PGDN: return 200;
    case C_NAV_KC_PGUP: return 200;
    case C_NAV_LCAKC_B: return 200;
    case C_NAV_RCSKC_E: return 200;
    case C_NAV_RCSKC_N: return 200;
    case C_NAV_RCSKC_V: return 200;
    case C_NAV_RCSKC_Z: return 200;
    case C_NAV_UMUMLAUT_S: return 200;
    case C_NAV_UPUMLAUT_AUMLAUT_A: return 200;
    case C_NAV_UPUMLAUT_OUMLAUT_O: return 200;
    case C_NAV_UPUMLAUT_UUMLAUT_U: return 200;
    case C_NUM_AKC_F1: return 200;
    case C_NUM_CKC_G: return 200;
    case C_NUM_LCAKC_L: return 200;
    case C_NUM_LSAKC_B: return 200;
    case C_NUM_LSAKC_S: return 200;
    case C_NUM_LSAKC_X: return 200;
    case C_NUM_RCSKC_V: return 200;
    case C_RIGHT_KC_AT: return 200;
    case C_RIGHT_KC_BACKSLASH: return 200;
    case C_RIGHT_KC_EXLM: return 200;
    case C_RIGHT_KC_GRAVE: return 200;
    case C_RIGHT_KC_QUES: return 200;
    case C_RIGHT_N_T: return 200;
    case C_RIGHT_RCSKC_F: return 200;
    case C_RIGHT_RCSKC_R: return 200;
    case DS_C_BASE_KC_B: return 200;
    case DS_C_BASE_KC_G: return 200;
    case DS_C_BASE_KC_J: return 200;
    case DS_C_BASE_KC_K: return 200;
    case DS_C_BASE_KC_M: return 200;
    case DS_C_BASE_KC_P: return 200;
    case DS_C_BASE_KC_Q: return 200;
    case DS_C_BASE_KC_V: return 200;
    case DS_C_BASE_KC_Z: return 200;
    case SUB_1: return 200;
    case SUB_2: return 200;
    case S_C_BASE_KC_B: return 200;
    case S_C_BASE_KC_G: return 200;
    case S_C_BASE_KC_J: return 200;
    case S_C_BASE_KC_K: return 200;
    case S_C_BASE_KC_M: return 200;
    case S_C_BASE_KC_P: return 200;
    case S_C_BASE_KC_Q: return 200;
    case S_C_BASE_KC_V: return 200;
    case S_C_BASE_KC_Z: return 200;
    default:
        return COMBO_TERM;
    }
}

bool tap(uint16_t keycode) {
    tap_code16(keycode);
    set_last_keycode(keycode);
    return false;
}

bool process_record_generated(uint16_t keycode, keyrecord_t *record) {
    if (record->tap.count) {
        if (record->event.pressed) {
            switch (keycode) {
            
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            switch (keycode) {
            case MAGIC_A:
                switch (get_last_keycode()) {
                    case KC_B: tap_code16(KC_L); return false;
                    case KC_C: tap_code16(KC_K); return false;
                    case KC_COMMA: chord_decode_send(1125); return false; // " but "
                    case KC_D: chord_decode_send(1076); return false; // "oesn't"
                    case KC_DOT: tap_code16(KC_SLASH); return false;
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_ENT: chord_decode_send(1117); return false; // "the "
                    case KC_EQUAL: tap_code16(KC_RABK); return false;
                    case KC_EXLM: tap_code16(KC_EQUAL); return false;
                    case KC_F: tap_code16(KC_F); return false;
                    case KC_G: tap_code16(KC_N); return false;
                    case KC_H: tap_code16(KC_Y); return false;
                    case KC_I: tap_code16(KC_QUOTE); return false;
                    case KC_J: chord_decode_send(1096); return false; // "ust"
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_P); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_MINUS: tap_code16(KC_RABK); return false;
                    case KC_N: tap_code16(KC_G); return false;
                    case KC_O: tap_code16(KC_E); return false;
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_R: tap_code16(KC_K); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: chord_decode_send(1117); return false; // "the "
                    case KC_T: chord_decode_send(1107); return false; // "ion"
                    case KC_TAB: chord_decode_send(1117); return false; // "the "
                    case KC_TILD: tap_code16(KC_SLASH); return false;
                    case KC_V: chord_decode_send(1113); return false; // "er"
                    case KC_W: tap_code16(KC_N); return false;
                    case KC_X: tap_code16(KC_P); return false;
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): chord_decode_send(1076); return false; // "oesn't"
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_F): tap_code16(KC_F); return false;
                    case S(KC_G): tap_code16(KC_N); return false;
                    case S(KC_H): tap_code16(KC_Y); return false;
                    case S(KC_I): tap_code16(KC_QUOTE); return false;
                    case S(KC_J): chord_decode_send(1096); return false; // "ust"
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_P); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): tap_code16(KC_G); return false;
                    case S(KC_O): tap_code16(KC_E); return false;
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_R): tap_code16(KC_K); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): chord_decode_send(1107); return false; // "ion"
                    case S(KC_V): chord_decode_send(1113); return false; // "er"
                    case S(KC_W): tap_code16(KC_N); return false;
                    case S(KC_X): tap_code16(KC_P); return false;
                }
                return false;
            case MAGIC_B:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_U); return false;
                    case KC_B: chord_decode_send(1072); return false; // "ecause"
                    case KC_C: tap_code16(KC_P); return false;
                    case KC_COMMA: chord_decode_send(1130); return false; // " and "
                    case KC_D: chord_decode_send(1081); return false; // "oes"
                    case KC_DOT: chord_decode_send(1135); return false; // "./"
                    case KC_ENT: chord_decode_send(1121); return false; // "and "
                    case KC_F: chord_decode_send(1088); return false; // "or"
                    case KC_G: tap_code16(KC_K); return false;
                    case KC_H: chord_decode_send(1090); return false; // "ey"
                    case KC_I: chord_decode_send(1092); return false; // "'ve"
                    case KC_K: chord_decode_send(1099); return false; // "now"
                    case KC_L: tap_code16(KC_M); return false;
                    case KC_M: chord_decode_send(1102); return false; // "ent"
                    case KC_N: tap_code16(KC_K); return false;
                    case KC_P: tap_code16(KC_S); return false;
                    case KC_S: chord_decode_send(1107); return false; // "ion"
                    case KC_SPC: tap_code16(KC_BSPC); SEND_STRING(". "); add_oneshot_mods(MOD_BIT(KC_LSFT)); return false;
                    case KC_T: chord_decode_send(1110); return false; // "ing"
                    case KC_TAB: chord_decode_send(1121); return false; // "and "
                    case KC_U: tap_code16(KC_A); return false;
                    case KC_V: chord_decode_send(1115); return false; // "en"
                    case KC_W: tap_code16(KC_S); return false;
                    case KC_X: tap_code16(KC_C); return false;
                    case S(KC_A): tap_code16(KC_U); return false;
                    case S(KC_B): chord_decode_send(1072); return false; // "ecause"
                    case S(KC_C): tap_code16(KC_P); return false;
                    case S(KC_D): chord_decode_send(1081); return false; // "oes"
                    case S(KC_F): chord_decode_send(1088); return false; // "or"
                    case S(KC_G): tap_code16(KC_K); return false;
                    case S(KC_H): chord_decode_send(1090); return false; // "ey"
                    case S(KC_I): chord_decode_send(1092); return false; // "'ve"
                    case S(KC_K): chord_decode_send(1099); return false; // "now"
                    case S(KC_L): tap_code16(KC_M); return false;
                    case S(KC_M): chord_decode_send(1102); return false; // "ent"
                    case S(KC_N): tap_code16(KC_K); return false;
                    case S(KC_P): tap_code16(KC_S); return false;
                    case S(KC_S): chord_decode_send(1107); return false; // "ion"
                    case S(KC_T): chord_decode_send(1110); return false; // "ing"
                    case S(KC_U): tap_code16(KC_A); return false;
                    case S(KC_V): chord_decode_send(1115); return false; // "en"
                    case S(KC_W): tap_code16(KC_S); return false;
                    case S(KC_X): tap_code16(KC_C); return false;
                }
                return false;
            case MAGIC_C:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_U); return false;
                    case KC_B: tap_code16(KC_L); return false;
                    case KC_C: tap_code16(KC_K); return false;
                    case KC_D: chord_decode_send(1084); return false; // "on't"
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_G: tap_code16(KC_L); return false;
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_V); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_N: chord_decode_send(1105); return false; // "ly"
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: chord_decode_send(1117); return false; // "the "
                    case KC_T: chord_decode_send(1107); return false; // "ion"
                    case S(KC_A): tap_code16(KC_U); return false;
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): chord_decode_send(1084); return false; // "on't"
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_G): tap_code16(KC_L); return false;
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_V); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): chord_decode_send(1105); return false; // "ly"
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): chord_decode_send(1107); return false; // "ion"
                }
                return false;
            
            default:
                break;
            }
        }
    }
    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LT(_NUM2,KC_EQUAL): return true;
    default:
        // Do not select the hold action when another key is pressed.
        return false;
    }
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    switch (keycode) {
        case MAGIC_A:
        case MAGIC_B:
        case MAGIC_C:
            return false;
    }

    return true;  // Other keys can be repeated.
}
