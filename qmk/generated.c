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
    'e', 't', 'r', 'a', 'n', 'o', 'i', 's', 'l', 'g', 'u', 'c', 'h', 'y'
};

// 8-bit codes (0xE0+) for less common characters
static const char chord_char_extended[] = {
    'd', 'm', 'p', 'b', 'v', 'w', 'f', ' ', 'k', '\'', 'x', 'j', 'z', '.', 'G', 'q', '@', 'S', 'P', 'O', 'T', 'H', 'L', 'B', 'Z', '/'
};

// Global buffer containing all 4/8-bit variable-length encoded chord strings
static const uint8_t chord_data[] = {
    0x0a, 0xf8, 0x06, 0x18, 0x64, 0x90, 0x20, 0x12, 0xe0, 0x0b, 0x83, 0x23, 0x16, 0xe4, 0x0f, 0xe7,
    0xb5, 0x4f, 0xe6, 0x69, 0x0b, 0xf1, 0xe2, 0x26, 0x49, 0xe7, 0xf7, 0x55, 0x10, 0x0c, 0xee, 0x23,
    0xe6, 0x34, 0x3f, 0xe7, 0xf6, 0x3f, 0xe3, 0x70, 0x09, 0xeb, 0x3f, 0xe4, 0x33, 0x90, 0x41, 0x06,
    0x7f, 0xe2, 0x26, 0x49, 0x0e, 0xf1, 0xe2, 0x26, 0x49, 0xe7, 0x71, 0x32, 0x10, 0x20, 0x06, 0xee,
    0x61, 0xf5, 0xaf, 0xe3, 0x08, 0x52, 0x93, 0x46, 0xec, 0x00, 0x05, 0x37, 0xd4, 0xb0, 0x05, 0x7f,
    0xe1, 0x68, 0x00, 0x09, 0x10, 0x80, 0xe1, 0x01, 0x2d, 0x06, 0x3b, 0x1a, 0x38, 0x08, 0x20, 0x75,
    0xa2, 0xb0, 0x09, 0x0f, 0xea, 0xb0, 0xe2, 0x16, 0x54, 0x08, 0x0f, 0xea, 0x67, 0x16, 0x49, 0x05,
    0xc1, 0x1f, 0xe2, 0x70, 0x07, 0x0f, 0xea, 0x0b, 0xa1, 0x00, 0x07, 0x0f, 0xea, 0x3f, 0xe1, 0xe2,
    0x80, 0x06, 0x0f, 0xea, 0xe2, 0x52, 0x10, 0x07, 0xb5, 0x41, 0x0f, 0xea, 0x10, 0x05, 0xe5, 0x52,
    0x2d, 0x08, 0x64, 0x10, 0x24, 0x38, 0x05, 0xe5, 0xc0, 0x20, 0x07, 0xe5, 0x61, 0xc5, 0xa1, 0x05,
    0xe5, 0x25, 0x49, 0x04, 0xe5, 0x68, 0x80, 0x05, 0xe5, 0xc6, 0xbc, 0x04, 0xe5, 0xc0, 0x40, 0x05,
    0x3f, 0xe5, 0x36, 0x10, 0x08, 0xe5, 0x5a, 0x8f, 0xe0, 0x4f, 0xe9, 0x10, 0x0a, 0x0f, 0xe4, 0x02,
    0xd1, 0xc6, 0x49, 0x05, 0xe4, 0x38, 0xa0, 0x05, 0x40, 0xe4, 0x02, 0x04, 0x5f, 0xe4, 0x02, 0x06,
    0x45, 0x16, 0xb0, 0x08, 0x70, 0x2f, 0xe4, 0x6b, 0x07, 0x07, 0xe4, 0x02, 0x76, 0x54, 0x09, 0x3f,
    0xe4, 0x36, 0x83, 0xe3, 0x80, 0x07, 0xb5, 0x41, 0x26, 0xe3, 0x09, 0x1c, 0x34, 0xe8, 0xe7, 0xd5,
    0xa0, 0x06, 0x1c, 0x5a, 0x9c, 0x0d, 0xf3, 0xe2, 0x04, 0xf4, 0x08, 0x0f, 0xe1, 0x01, 0x2d, 0x05,
    0x1c, 0x02, 0x00, 0x07, 0x1c, 0x5a, 0x9c, 0x10, 0x07, 0x1c, 0x25, 0xa9, 0xc0, 0x04, 0x16, 0xe1,
    0x00, 0x05, 0x51, 0xc0, 0x20, 0x05, 0x1c, 0x07, 0x00, 0x05, 0x15, 0xe0, 0x3d, 0x06, 0x10, 0x43,
    0x41, 0x05, 0x1c, 0x64, 0xe8, 0x06, 0x7d, 0x71, 0x0f, 0xe1, 0x09, 0x75, 0xe1, 0x01, 0xc6, 0x49,
    0x07, 0x7a, 0xe2, 0xe2, 0x52, 0x10, 0x08, 0x7a, 0x2f, 0xe2, 0x26, 0x70, 0x06, 0x78, 0x5f, 0xe5,
    0x8d, 0x07, 0x7a, 0xe3, 0xeb, 0x0b, 0x10, 0x07, 0x75, 0xe1, 0x05, 0x40, 0x05, 0x7c, 0x32, 0x00,
    0x06, 0x70, 0x32, 0xbc, 0x06, 0x71, 0x26, 0x49, 0x06, 0xe5, 0x37, 0x4f, 0xe9, 0x10, 0x06, 0x7c,
    0x5a, 0x8f, 0xe0, 0x07, 0x20, 0x38, 0x6f, 0xec, 0x00, 0x05, 0xd0, 0x32, 0x70, 0x07, 0x20, 0xef,
    0xa0, 0x71, 0x06, 0x32, 0x5a, 0x4f, 0xe0, 0x05, 0xef, 0xa0, 0x2d, 0x06, 0x20, 0x1a, 0x24, 0x06,
    0x20, 0xe4, 0x60, 0xe5, 0x06, 0x26, 0x9c, 0x17, 0x07, 0xe2, 0x25, 0x92, 0x3f, 0xe1, 0x05, 0x25,
    0xa1, 0x00, 0x06, 0x20, 0x38, 0x8d, 0x08, 0xe2, 0x25, 0xe3, 0x3f, 0xe3, 0x8d, 0x06, 0xe2, 0xaf,
    0xe3, 0x86, 0xb0, 0x06, 0xe2, 0x32, 0x04, 0x10, 0x0a, 0xf2, 0x25, 0xe1, 0x01, 0xc0, 0xa7, 0x07,
    0xe2, 0x25, 0xe0, 0xab, 0x10, 0x07, 0xe2, 0x25, 0xe3, 0x80, 0xe1, 0x05, 0xe2, 0x56, 0x41, 0x05,
    0xe2, 0x83, 0xb0, 0x07, 0xe2, 0x26, 0xe4, 0x3b, 0xd0, 0x07, 0xe2, 0x25, 0xe1, 0x67, 0x00, 0x06,
    0xe2, 0x80, 0x37, 0x00, 0x06, 0xe2, 0x05, 0xe2, 0x80, 0x07, 0xb5, 0xe1, 0xe2, 0x34, 0xd0, 0x06,
    0x04, 0x5a, 0x9c, 0x07, 0x34, 0x51, 0xc0, 0x20, 0x06, 0x67, 0x7a, 0x07, 0x04, 0x64, 0x15, 0x08,
    0x34, 0xd1, 0xc6, 0x49, 0x06, 0x4a, 0xe1, 0xe3, 0x02, 0x07, 0x64, 0x71, 0x03, 0xe0, 0x06, 0x34,
    0xdf, 0xe5, 0x3d, 0x06, 0x76, 0x49, 0x80, 0x0a, 0xa4, 0xe0, 0x02, 0x71, 0x34, 0xe0, 0x06, 0xe1,
    0xd7, 0x08, 0xe6, 0x05, 0xe1, 0xa7, 0x6b, 0x07, 0xe6, 0x03, 0x1a, 0x20, 0x05, 0xe1, 0x3f, 0xeb,
    0x52, 0x06, 0xe1, 0x64, 0xa1, 0x00, 0x05, 0xe1, 0x69, 0xc1, 0x07, 0xe1, 0x07, 0x73, 0x90, 0x06,
    0xe1, 0x01, 0xc5, 0xe0, 0x04, 0x89, 0x1f, 0xe1, 0x04, 0x54, 0x8d, 0x06, 0x38, 0xe1, 0x57, 0x10,
    0x05, 0x83, 0x10, 0x20, 0x05, 0x38, 0x54, 0x90, 0x14, 0x92, 0x09, 0x52, 0xf0, 0xec, 0x06, 0x18,
    0x64, 0x90, 0x2f, 0xed, 0xe0, 0x00, 0x05, 0x83, 0x29, 0x00, 0x05, 0x86, 0x9c, 0x10, 0x06, 0xc0,
    0x38, 0x1c, 0x05, 0x80, 0x3f, 0xe4, 0x00, 0x04, 0xe5, 0x61, 0xc0, 0x08, 0x83, 0x49, 0xa3, 0x90,
    0x05, 0xb8, 0x37, 0x70, 0x05, 0x80, 0xe4, 0x08, 0x07, 0xef, 0xa6, 0xbf, 0xe8, 0x8d, 0x06, 0xb3,
    0x88, 0x02, 0x04, 0xe5, 0x52, 0xe8, 0x04, 0xe8, 0x45, 0xe5, 0x04, 0xeb, 0x3f, 0xe4, 0x30, 0x04,
    0xe8, 0x64, 0xe0, 0x05, 0xbc, 0x0b, 0xe8, 0x06, 0xb5, 0x4f, 0xe6, 0x69, 0x08, 0xef, 0xa0, 0x71,
    0x65, 0x40, 0x05, 0x0f, 0xe4, 0x02, 0xd0, 0x06, 0x98, 0x5f, 0xe3, 0x38, 0x07, 0x90, 0x40, 0x23,
    0x80, 0x06, 0x96, 0xe4, 0x64, 0x90, 0x06, 0xee, 0x20, 0x95, 0x20, 0x06, 0x98, 0x34, 0xb0, 0x07,
    0xee, 0x23, 0xe6, 0x34, 0x30, 0x05, 0x39, 0x36, 0x40, 0x05, 0xe6, 0x52, 0x1d, 0x05, 0xe6, 0x5a,
    0x4f, 0xe0, 0x08, 0x75, 0xe6, 0x1f, 0xe5, 0x32, 0x00, 0x0b, 0x64, 0xe6, 0x52, 0xe1, 0x31, 0x65,
    0x40, 0x04, 0xc3, 0xe4, 0x00, 0x06, 0xe6, 0x64, 0x90, 0x20, 0x05, 0xe6, 0x62, 0x71, 0x04, 0x1c,
    0x04, 0x1d, 0x92, 0x09, 0x52, 0xed, 0xec, 0x06, 0x18, 0x64, 0x90, 0x2f, 0xf0, 0x92, 0x3f, 0xe6,
    0x34, 0x3f, 0xed, 0xb5, 0xe1, 0x04, 0xe6, 0x00, 0x80, 0x05, 0x3f, 0xe6, 0x10, 0x20, 0x05, 0xe6,
    0x38, 0x70, 0x05, 0xe6, 0x36, 0x87, 0x07, 0x38, 0x20, 0x3f, 0xe0, 0xd0, 0x08, 0xe2, 0x25, 0xe0,
    0xab, 0x17, 0x05, 0x1c, 0x06, 0x20, 0x05, 0xe0, 0x54, 0xe9, 0x10, 0x05, 0xe3, 0xa6, 0x8f, 0xe0,
    0x06, 0xe0, 0xa2, 0x64, 0x90, 0x14, 0xec, 0x06, 0x18, 0x64, 0x90, 0x2f, 0xf0, 0x9f, 0xe1, 0x36,
    0x8f, 0xed, 0xb5, 0xe1, 0x08, 0xe0, 0x07, 0xb2, 0x6f, 0xe3, 0x00, 0x06, 0xc3, 0xe0, 0x4f, 0xe9,
    0x10, 0x06, 0xe0, 0x6f, 0xe0, 0x4f, 0xe9, 0x10, 0x06, 0xe2, 0x58, 0x6b, 0xd0, 0x07, 0xba, 0x22,
    0x04, 0x10, 0x06, 0x3b, 0x25, 0x77, 0x08, 0xb5, 0x41, 0x64, 0xa0, 0x04, 0xe3, 0x00, 0x40, 0x07,
    0xe2, 0x25, 0xeb, 0x0b, 0x10, 0x05, 0xb8, 0x6b, 0xe8, 0x08, 0x20, 0x70, 0x32, 0xbc, 0x07, 0x70,
    0x2f, 0xe4, 0x6b, 0x00, 0x08, 0x3b, 0x1a, 0x38, 0x8d, 0x05, 0xb5, 0x47, 0x10, 0x08, 0xb5, 0xa8,
    0xe0, 0x4f, 0xe9, 0x10, 0x05, 0xb5, 0xa8, 0xe0, 0x04, 0xe3, 0x5f, 0xe0, 0xd0, 0x08, 0xe3, 0xa7,
    0x64, 0x07, 0x70, 0x05, 0xe3, 0x20, 0x3f, 0xe8, 0x06, 0xe3, 0x0b, 0x5f, 0xe1, 0x00, 0x07, 0xe3,
    0x01, 0xe5, 0x00, 0x40, 0x05, 0xe3, 0x06, 0x49, 0x06, 0xe3, 0x0c, 0x64, 0xe0, 0x05, 0xe3, 0x09,
    0x34, 0x07, 0xe3, 0x55, 0x80, 0x34, 0x0d, 0x5f, 0xe3, 0x70, 0x2f, 0xe4, 0x3f, 0xe3, 0x68, 0x61,
    0xd0, 0x05, 0x3f, 0xe3, 0x5a, 0x10, 0x06, 0x0b, 0x3a, 0x70, 0x03, 0x45, 0xe5, 0x03, 0x04, 0x10,
    0x03, 0x65, 0x40, 0x03, 0x50, 0x70, 0x06, 0x50, 0x74, 0xe9, 0x10, 0x02, 0x52, 0x02, 0x0d, 0x03,
    0xe9, 0xe4, 0x00, 0x02, 0x02, 0x02, 0x04, 0x03, 0xa7, 0x10, 0x04, 0x1c, 0x0f, 0xe7, 0x04, 0x34,
    0xe0, 0xe7, 0x05, 0xe7, 0xe3, 0xa1, 0xe7, 0x05, 0xe7, 0x34, 0xe0, 0xe7, 0x02, 0xed, 0xf9
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
                case -191:
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
                case -180:
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
                case -169:
                    if (keycode == KC_COMMA) return 180; // "wouldn't"
                    if (keycode == KC_DOT) return 175; // "await"
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
                case -159:
                    if (keycode == KC_COMMA) return 229; // "contrib"
                    if (keycode == KC_A) return 222; // "available"
                    if (keycode == KC_H) return 217; // "version"
                    if (keycode == KC_I) return 211; // "services"
                    if (keycode == KC_J) return 207; // "notice"
                    if (keycode == KC_O) return 203; // "over"
                    if (keycode == KC_R) return 199; // "never"
                    if (keycode == KC_U) return 195; // "value"
                    if (keycode == KC_Y) return 188; // "everything"
                    break;
                // t
                case -146:
                    if (keycode == KC_SPC) return 289; // "think"
                    if (keycode == KC_COMMA) return 285; // "tenant"
                    if (keycode == KC_A) return 281; // "today"
                    if (keycode == KC_E) return 277; // "these"
                    if (keycode == KC_H) return 273; // "other"
                    if (keycode == KC_I) return 269; // "time"
                    if (keycode == KC_J) return 264; // "through"
                    if (keycode == KC_O) return 259; // "thought"
                    if (keycode == KC_R) return 255; // "there"
                    if (keycode == KC_T) return 245; // "OpenTelemetry"
                    if (keycode == KC_U) return 241; // "though"
                    if (keycode == KC_Y) return 234; // "thank you"
                    break;
                // s
                case -133:
                    if (keycode == KC_SPC) return 350; // "should"
                    if (keycode == KC_COMMA) return 344; // "wasn't"
                    if (keycode == KC_DOT) return 340; // "string"
                    if (keycode == KC_E) return 336; // "search"
                    if (keycode == KC_H) return 332; // "share"
                    if (keycode == KC_I) return 327; // "someone"
                    if (keycode == KC_J) return 321; // "subject"
                    if (keycode == KC_O) return 316; // "slowly"
                    if (keycode == KC_R) return 310; // "surprise"
                    if (keycode == KC_T) return 298; // "something"
                    if (keycode == KC_U) return 304; // "support"
                    if (keycode == KC_Y) return 293; // "system"
                    break;
                // r
                case -121:
                    if (keycode == KC_SPC) return 402; // "really"
                    if (keycode == KC_COMMA) return 398; // "route"
                    if (keycode == KC_A) return 392; // "program"
                    if (keycode == KC_G) return 388; // "rights"
                    if (keycode == KC_H) return 383; // "review"
                    if (keycode == KC_J) return 379; // "return"
                    if (keycode == KC_L) return 375; // "query"
                    if (keycode == KC_O) return 370; // "around"
                    if (keycode == KC_S) return 365; // "request"
                    if (keycode == KC_Y) return 361; // "years"
                    if (keycode == KC_Z) return 355; // "realize"
                    break;
                // p
                case -108:
                    if (keycode == KC_SPC) return 468; // "people"
                    if (keycode == KC_COMMA) return 463; // "please"
                    if (keycode == KC_DOT) return 457; // "promise"
                    if (keycode == KC_A) return 451; // "privacy"
                    if (keycode == KC_E) return 447; // "place"
                    if (keycode == KC_I) return 443; // "point"
                    if (keycode == KC_J) return 437; // "problem"
                    if (keycode == KC_O) return 431; // "product"
                    if (keycode == KC_P) return 424; // "Prometheus"
                    if (keycode == KC_R) return 419; // "parent"
                    if (keycode == KC_U) return 413; // "public"
                    if (keycode == KC_Y) return 406; // "probably"
                    break;
                // n
                case -96:
                    if (keycode == KC_SPC) return 519; // "understand"
                    if (keycode == KC_COMMA) return 515; // "single"
                    if (keycode == KC_A) return 510; // "anyway"
                    if (keycode == KC_D) return 505; // "instead"
                    if (keycode == KC_E) return 500; // "number"
                    if (keycode == KC_H) return 495; // "anything"
                    if (keycode == KC_I) return 492; // "into"
                    if (keycode == KC_J) return 488; // "issues"
                    if (keycode == KC_O) return 483; // "another"
                    if (keycode == KC_U) return 479; // "enough"
                    if (keycode == KC_Y) return 473; // "company"
                    break;
                // m
                case -86:
                    if (keycode == KC_COMMA) return 564; // "lgtm"
                    if (keycode == KC_DOT) return 559; // "method"
                    if (keycode == KC_E) return 554; // "message"
                    if (keycode == KC_H) return 550; // "might"
                    if (keycode == KC_I) return 545; // "minute"
                    if (keycode == KC_J) return 540; // "major"
                    if (keycode == KC_O) return 535; // "feature"
                    if (keycode == KC_U) return 531; // "music"
                    if (keycode == KC_Y) return 526; // "myself"
                    break;
                // l
                case -72:
                    if (keycode == KC_COMMA) return 628; // "level"
                    if (keycode == KC_DOT) return 624; // "class"
                    if (keycode == KC_A) return 619; // "language"
                    if (keycode == KC_D) return 615; // "with"
                    if (keycode == KC_E) return 610; // "leave"
                    if (keycode == KC_H) return 606; // "health"
                    if (keycode == KC_I) return 602; // "light"
                    if (keycode == KC_J) return 598; // "large"
                    if (keycode == KC_L) return 584; // "gregor@zeitlinger.de"
                    if (keycode == KC_O) return 580; // "along"
                    if (keycode == KC_R) return 576; // "later"
                    if (keycode == KC_U) return 571; // "almost"
                    if (keycode == KC_Y) return 568; // "only"
                    break;
                // k
                case -62:
                    if (keycode == KC_SPC) return 668; // "question"
                    if (keycode == KC_COMMA) return 663; // "config"
                    if (keycode == KC_H) return 659; // "check"
                    if (keycode == KC_I) return 655; // "kind"
                    if (keycode == KC_J) return 650; // "java"
                    if (keycode == KC_O) return 646; // "know"
                    if (keycode == KC_R) return 642; // "work"
                    if (keycode == KC_U) return 638; // "caller"
                    if (keycode == KC_Y) return 632; // "quickly"
                    break;
                // g
                case -53:
                    if (keycode == KC_SPC) return 709; // "again"
                    if (keycode == KC_DOT) return 703; // "Grafana"
                    if (keycode == KC_A) return 699; // "glance"
                    if (keycode == KC_G) return 694; // "Gregor"
                    if (keycode == KC_I) return 689; // "giving"
                    if (keycode == KC_J) return 684; // "general"
                    if (keycode == KC_O) return 679; // "global"
                    if (keycode == KC_Y) return 674; // "every"
                    break;
                // f
                case -39:
                    if (keycode == KC_COMMA) return 786; // "fails"
                    if (keycode == KC_DOT) return 782; // "false"
                    if (keycode == KC_A) return 777; // "after"
                    if (keycode == KC_E) return 773; // "feel"
                    if (keycode == KC_F) return 753; // "gregor.zeitlinger@grafana.com"
                    if (keycode == KC_H) return 750; // "then"
                    if (keycode == KC_I) return 746; // "first"
                    if (keycode == KC_J) return 741; // "finger"
                    if (keycode == KC_L) return 737; // "have"
                    if (keycode == KC_O) return 729; // "information"
                    if (keycode == KC_R) return 722; // "software"
                    if (keycode == KC_U) return 717; // "found"
                    if (keycode == KC_Y) return 713; // "forty"
                    break;
                // d
                case -28:
                    if (keycode == KC_SPC) return 849; // "didn't"
                    if (keycode == KC_COMMA) return 843; // "hadn't"
                    if (keycode == KC_A) return 836; // "describe"
                    if (keycode == KC_D) return 821; // "zeitlinger@gmail.com"
                    if (keycode == KC_I) return 816; // "during"
                    if (keycode == KC_J) return 811; // "build"
                    if (keycode == KC_O) return 806; // "don't"
                    if (keycode == KC_R) return 802; // "their"
                    if (keycode == KC_U) return 796; // "products"
                    if (keycode == KC_Y) return 790; // "already"
                    break;
                // c
                case -14:
                    if (keycode == KC_SPC) return 916; // "could"
                    if (keycode == KC_COMMA) return 909; // "couldn't"
                    if (keycode == KC_DOT) return 905; // "const"
                    if (keycode == KC_A) return 900; // "actually"
                    if (keycode == KC_E) return 894; // "service"
                    if (keycode == KC_H) return 889; // "research"
                    if (keycode == KC_I) return 885; // "click"
                    if (keycode == KC_J) return 879; // "project"
                    if (keycode == KC_N) return 875; // "been"
                    if (keycode == KC_O) return 870; // "continue"
                    if (keycode == KC_R) return 866; // "across"
                    if (keycode == KC_U) return 861; // "current"
                    if (keycode == KC_Y) return 856; // "policy"
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return 977; // "about"
                    if (keycode == KC_COMMA) return 966; // "observability"
                    if (keycode == KC_DOT) return 961; // "boolean"
                    if (keycode == KC_E) return 957; // "began"
                    if (keycode == KC_H) return 952; // "behind"
                    if (keycode == KC_I) return 948; // "being"
                    if (keycode == KC_J) return 942; // "between"
                    if (keycode == KC_O) return 936; // "become"
                    if (keycode == KC_R) return 931; // "break"
                    if (keycode == KC_U) return 925; // "business"
                    if (keycode == KC_Y) return 920; // "body"
                    break;
                case -1:
                    if (keycode == KC_B) return -2; // b...
                    if (keycode == KC_C) return -14; // c...
                    if (keycode == KC_D) return -28; // d...
                    if (keycode == KC_F) return -39; // f...
                    if (keycode == KC_G) return -53; // g...
                    if (keycode == KC_K) return -62; // k...
                    if (keycode == KC_L) return -72; // l...
                    if (keycode == KC_M) return -86; // m...
                    if (keycode == KC_N) return -96; // n...
                    if (keycode == KC_P) return -108; // p...
                    if (keycode == KC_R) return -121; // r...
                    if (keycode == KC_S) return -133; // s...
                    if (keycode == KC_T) return -146; // t...
                    if (keycode == KC_V) return -159; // v...
                    if (keycode == KC_W) return -169; // w...
                    if (keycode == KC_X) return -180; // x...
                    if (keycode == KC_Z) return -191; // z...
                    break;
    default:
        // Invalid transition, stop chord mode
        return CHORD_INACTIVE;
    }
    return CHORD_INACTIVE;
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch(index) {
    case C_BASE_ADPT_QU: return 200;
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
    case C_NAV_RCSKC_C: return 200;
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

// Two-variable tracking for adaptive keys.
// prev_keycode = the key before the current one (what adaptives check against).
// last_keycode = the most recent key (shifts to prev_keycode on the next keypress).
// Updated only in remember_last_key_user (called with resolved combo keycodes,
// so combo components like KC_C from P=KC_C+KC_X are never recorded — only KC_P is).
static uint16_t prev_keycode = KC_NO;
static uint16_t last_keycode = KC_NO;

bool tap(uint16_t keycode) {
    tap_code16(keycode);
    set_last_keycode(keycode);
    last_keycode = keycode;
    return false;
}

bool process_record_generated(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Adaptive keys: runs after combo resolution in process_record_user,
        // so combo components are suppressed and prev_keycode reflects the
        // resolved combo keycode (e.g. KC_P not KC_C).
        switch (keycode) {
            case KC_E:
                switch (prev_keycode) {
                    case KC_A: return tap(KC_U);
                    case S(KC_A): return tap(KC_U);
                }
                break;
            case KC_D:
                switch (prev_keycode) {
                    case KC_B: return tap(KC_L);
                    case KC_C: return tap(KC_K);
                    case KC_P: return tap(KC_L);
                    case KC_S: return tap(KC_P);
                    case KC_X: return tap(KC_C);
                    case S(KC_B): return tap(KC_L);
                    case S(KC_C): return tap(KC_K);
                    case S(KC_P): return tap(KC_L);
                    case S(KC_S): return tap(KC_P);
                    case S(KC_X): return tap(KC_C);
                }
                break;
            case KC_H:
                switch (prev_keycode) {
                    case KC_B: return tap(KC_S);
                    case KC_E: return tap(KC_O);
                    case KC_K: return tap(KC_N);
                    case KC_L: return tap(KC_V);
                    case KC_M: return tap(KC_B);
                    case KC_N: return tap(KC_G);
                    case KC_O: return tap(KC_E);
                    case KC_U: return tap(KC_A);
                    case S(KC_B): return tap(KC_S);
                    case S(KC_E): return tap(KC_O);
                    case S(KC_K): return tap(KC_N);
                    case S(KC_L): return tap(KC_V);
                    case S(KC_M): return tap(KC_B);
                    case S(KC_N): return tap(KC_G);
                    case S(KC_O): return tap(KC_E);
                    case S(KC_U): return tap(KC_A);
                }
                break;
            case KC_F:
                switch (prev_keycode) {
                    case KC_G: return tap(KC_L);
                    case S(KC_G): return tap(KC_L);
                }
                break;
            case KC_Y:
                switch (prev_keycode) {
                    case KC_G: return tap(KC_N);
                    case S(KC_G): return tap(KC_N);
                }
                break;
            case KC_C:
                switch (prev_keycode) {
                    case KC_L: return tap(KC_M);
                    case S(KC_L): return tap(KC_M);
                }
                break;
            case KC_R:
                switch (prev_keycode) {
                    case KC_L: return tap(KC_P);
                    case KC_N: return tap(KC_K);
                    case KC_S: return tap(KC_K);
                    case S(KC_L): return tap(KC_P);
                    case S(KC_N): return tap(KC_K);
                    case S(KC_S): return tap(KC_K);
                }
                break;
            case KC_X:
                switch (prev_keycode) {
                    case KC_N: return tap(KC_L);
                    case KC_T: return tap(KC_M);
                    case KC_W: return tap(KC_N);
                    case KC_Y: return tap(KC_I);
                    case S(KC_N): return tap(KC_L);
                    case S(KC_T): return tap(KC_M);
                    case S(KC_W): return tap(KC_N);
                    case S(KC_Y): return tap(KC_I);
                }
                break;
            case KC_N:
                switch (prev_keycode) {
                    case KC_P: return tap(KC_S);
                    case S(KC_P): return tap(KC_S);
                }
                break;
            case KC_T:
                switch (prev_keycode) {
                    case KC_W: return tap(KC_N);
                    case S(KC_W): return tap(KC_N);
                }
                break;
            case KC_W:
                switch (prev_keycode) {
                    case KC_X: return tap(KC_P);
                    case S(KC_X): return tap(KC_P);
                }
                break;
            case ADPT_QU:
                switch (prev_keycode) {
                    case KC_A: return tap(KC_E);
                    case KC_E: return tap(KC_H);
                    case KC_O: return tap(KC_H);
                    case KC_U: return tap(KC_H);
                    case KC_Y: return tap(KC_X);
                    case S(KC_A): return tap(KC_E);
                    case S(KC_E): return tap(KC_H);
                    case S(KC_O): return tap(KC_H);
                    case S(KC_U): return tap(KC_H);
                    case S(KC_Y): return tap(KC_X);
                }
                break;
        }
    }
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
                    case KC_B: tap_code16(KC_D); return false;
                    case KC_C: tap_code16(KC_D); return false;
                    case KC_D: chord_decode_send(995); return false; // "oes"
                    case KC_DOT: tap_code16(KC_SLASH); return false;
                    case KC_EQUAL: tap_code16(KC_RABK); return false;
                    case KC_EXLM: tap_code16(KC_EQUAL); return false;
                    case KC_G: tap_code16(KC_Y); return false;
                    case KC_H: tap_code16(KC_Y); return false;
                    case KC_I: tap_code16(KC_QUOTE); return false;
                    case KC_K: tap_code16(KC_X); return false;
                    case KC_L: tap_code16(KC_C); return false;
                    case KC_M: tap_code16(KC_L); return false;
                    case KC_MINUS: tap_code16(KC_RABK); return false;
                    case KC_N: tap_code16(KC_X); return false;
                    case KC_P: tap_code16(KC_D); return false;
                    case KC_S: tap_code16(KC_D); return false;
                    case KC_T: tap_code16(KC_X); return false;
                    case KC_TILD: tap_code16(KC_SLASH); return false;
                    case KC_V: chord_decode_send(1011); return false; // "er"
                    case KC_W: tap_code16(KC_X); return false;
                    case KC_X: tap_code16(KC_D); return false;
                    case S(KC_B): tap_code16(KC_D); return false;
                    case S(KC_C): tap_code16(KC_D); return false;
                    case S(KC_D): chord_decode_send(995); return false; // "oes"
                    case S(KC_G): tap_code16(KC_Y); return false;
                    case S(KC_H): tap_code16(KC_Y); return false;
                    case S(KC_I): tap_code16(KC_QUOTE); return false;
                    case S(KC_K): tap_code16(KC_X); return false;
                    case S(KC_L): tap_code16(KC_C); return false;
                    case S(KC_M): tap_code16(KC_L); return false;
                    case S(KC_N): tap_code16(KC_X); return false;
                    case S(KC_P): tap_code16(KC_D); return false;
                    case S(KC_S): tap_code16(KC_D); return false;
                    case S(KC_T): tap_code16(KC_X); return false;
                    case S(KC_V): chord_decode_send(1011); return false; // "er"
                    case S(KC_W): tap_code16(KC_X); return false;
                    case S(KC_X): tap_code16(KC_D); return false;
                }
                return false;
            case MAGIC_B:
                switch (get_last_keycode()) {
                    case KC_B: chord_decode_send(982); return false; // "ecause"
                    case KC_C: tap_code16(KC_P); return false;
                    case KC_COMMA: chord_decode_send(1026); return false; // " but "
                    case KC_D: chord_decode_send(998); return false; // "oesn't"
                    case KC_DOT: chord_decode_send(1036); return false; // "./"
                    case KC_ENT: chord_decode_send(1018); return false; // "the "
                    case KC_F: chord_decode_send(1003); return false; // "or"
                    case KC_G: tap_code16(KC_K); return false;
                    case KC_H: chord_decode_send(1005); return false; // "ey"
                    case KC_I: chord_decode_send(1007); return false; // "'ve"
                    case KC_J: chord_decode_send(1015); return false; // "ust"
                    case KC_K: chord_decode_send(986); return false; // "now"
                    case KC_L: tap_code16(KC_R); return false;
                    case KC_M: chord_decode_send(989); return false; // "ent"
                    case KC_N: tap_code16(KC_R); return false;
                    case KC_P: tap_code16(KC_N); return false;
                    case KC_R: tap_code16(KC_K); return false;
                    case KC_S: chord_decode_send(992); return false; // "ion"
                    case KC_SPC: chord_decode_send(1018); return false; // "the "
                    case KC_T: chord_decode_send(992); return false; // "ion"
                    case KC_TAB: chord_decode_send(1018); return false; // "the "
                    case KC_V: chord_decode_send(1013); return false; // "en"
                    case KC_W: tap_code16(KC_S); return false;
                    case KC_X: tap_code16(KC_R); return false;
                    case S(KC_B): chord_decode_send(982); return false; // "ecause"
                    case S(KC_C): tap_code16(KC_P); return false;
                    case S(KC_D): chord_decode_send(998); return false; // "oesn't"
                    case S(KC_F): chord_decode_send(1003); return false; // "or"
                    case S(KC_G): tap_code16(KC_K); return false;
                    case S(KC_H): chord_decode_send(1005); return false; // "ey"
                    case S(KC_I): chord_decode_send(1007); return false; // "'ve"
                    case S(KC_J): chord_decode_send(1015); return false; // "ust"
                    case S(KC_K): chord_decode_send(986); return false; // "now"
                    case S(KC_L): tap_code16(KC_R); return false;
                    case S(KC_M): chord_decode_send(989); return false; // "ent"
                    case S(KC_N): tap_code16(KC_R); return false;
                    case S(KC_P): tap_code16(KC_N); return false;
                    case S(KC_R): tap_code16(KC_K); return false;
                    case S(KC_S): chord_decode_send(992); return false; // "ion"
                    case S(KC_T): chord_decode_send(992); return false; // "ion"
                    case S(KC_V): chord_decode_send(1013); return false; // "en"
                    case S(KC_W): tap_code16(KC_S); return false;
                    case S(KC_X): tap_code16(KC_R); return false;
                }
                return false;
            case MAGIC_C:
                switch (get_last_keycode()) {
                    case KC_B: tap_code16(KC_H); return false;
                    case KC_COMMA: chord_decode_send(1031); return false; // " and "
                    case KC_ENT: chord_decode_send(1022); return false; // "and "
                    case KC_F: tap_code16(KC_F); return false;
                    case KC_G: tap_code16(KC_F); return false;
                    case KC_K: tap_code16(KC_H); return false;
                    case KC_L: tap_code16(KC_H); return false;
                    case KC_M: tap_code16(KC_H); return false;
                    case KC_N: tap_code16(KC_H); return false;
                    case KC_P: tap_code16(KC_M); return false;
                    case KC_S: tap_code16(KC_R); return false;
                    case KC_SPC: tap_code16(KC_BSPC); SEND_STRING(". "); add_oneshot_mods(MOD_BIT(KC_LSFT)); return false;
                    case KC_TAB: chord_decode_send(1022); return false; // "and "
                    case KC_W: tap_code16(KC_T); return false;
                    case KC_X: tap_code16(KC_W); return false;
                    case S(KC_B): tap_code16(KC_H); return false;
                    case S(KC_F): tap_code16(KC_F); return false;
                    case S(KC_G): tap_code16(KC_F); return false;
                    case S(KC_K): tap_code16(KC_H); return false;
                    case S(KC_L): tap_code16(KC_H); return false;
                    case S(KC_M): tap_code16(KC_H); return false;
                    case S(KC_N): tap_code16(KC_H); return false;
                    case S(KC_P): tap_code16(KC_M); return false;
                    case S(KC_S): tap_code16(KC_R); return false;
                    case S(KC_W): tap_code16(KC_T); return false;
                    case S(KC_X): tap_code16(KC_W); return false;
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

    prev_keycode = last_keycode;
    last_keycode = keycode;
    return true;  // Other keys can be repeated.
}
