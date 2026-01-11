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
    'm', 'p', 'd', 'b', 'v', 'w', 'f', 'k', ' ', '\'', 'j', 'x', 'z', '.', 'G', 'q', '@', 'S', 'Z', 'L', 'O', 'T', 'H', 'B', '/'
};

// Global buffer containing all 4/8-bit variable-length encoded chord strings
static const uint8_t chord_data[] = {
    0x0b, 0xf1, 0xe1, 0x26, 0x49, 0xe8, 0xf7, 0x55, 0x10, 0x08, 0x25, 0x88, 0xe2, 0x6b, 0x00, 0x09,
    0xea, 0x30, 0xe4, 0x33, 0x90, 0x41, 0x0e, 0xf1, 0xe1, 0x26, 0x49, 0xe8, 0x71, 0x32, 0x10, 0x20,
    0x06, 0xee, 0x61, 0xf6, 0xa0, 0xe3, 0x08, 0x52, 0x93, 0x46, 0xec, 0x00, 0x05, 0x37, 0xd4, 0xb0,
    0x05, 0x70, 0xe0, 0x68, 0x00, 0x07, 0x20, 0x38, 0x60, 0xec, 0x00, 0x09, 0x10, 0x80, 0xe0, 0x01,
    0x2d, 0x06, 0x3b, 0x1a, 0x38, 0x08, 0x20, 0x75, 0xa2, 0xb0, 0x0d, 0xf4, 0xe1, 0x04, 0xf5, 0x08,
    0x00, 0xe0, 0x01, 0x2d, 0x09, 0x00, 0xeb, 0xb0, 0xe1, 0x16, 0x54, 0x08, 0x00, 0xeb, 0x67, 0x16,
    0x49, 0x05, 0xc1, 0x10, 0xe1, 0x70, 0x07, 0x00, 0xeb, 0x0b, 0xa1, 0x00, 0x07, 0x00, 0xeb, 0x30,
    0xe0, 0xe1, 0x80, 0x06, 0x00, 0xeb, 0xe1, 0x52, 0x10, 0x12, 0xe2, 0x0b, 0x83, 0x23, 0x16, 0xe4,
    0x00, 0xe8, 0xb5, 0x40, 0xe6, 0x69, 0x07, 0xb5, 0x41, 0x00, 0xeb, 0x10, 0x05, 0xe5, 0x52, 0x2d,
    0x08, 0x64, 0x10, 0x24, 0x38, 0x05, 0xe5, 0xc0, 0x20, 0x07, 0xe5, 0x61, 0xc5, 0xa1, 0x05, 0xe5,
    0x25, 0x49, 0x04, 0xe5, 0x61, 0xc0, 0x05, 0xe5, 0xc6, 0xbc, 0x04, 0xe5, 0x38, 0xe7, 0x05, 0x30,
    0xe5, 0x36, 0x10, 0x08, 0xe5, 0x5a, 0x80, 0xe2, 0x40, 0xe9, 0x10, 0x05, 0xe5, 0x5a, 0x80, 0xe2,
    0x0a, 0x00, 0xe4, 0x02, 0xd1, 0xc6, 0x49, 0x05, 0xe4, 0x38, 0xa0, 0x05, 0x40, 0xe4, 0x02, 0x04,
    0x50, 0xe4, 0x02, 0x06, 0x45, 0x16, 0xb0, 0x08, 0x70, 0x20, 0xe4, 0x6b, 0x07, 0x07, 0xe4, 0x02,
    0x76, 0x54, 0x04, 0xe4, 0x02, 0xd0, 0x09, 0x30, 0xe4, 0x36, 0x83, 0xe3, 0x80, 0x04, 0xe4, 0x56,
    0xe2, 0x07, 0xb5, 0x41, 0x26, 0xe3, 0x04, 0xc3, 0xe4, 0x00, 0x04, 0x1c, 0x0d, 0x06, 0x1c, 0x5a,
    0x9c, 0x05, 0x1c, 0x02, 0x00, 0x07, 0x1c, 0x5a, 0x9c, 0x10, 0x07, 0x1c, 0x25, 0xa9, 0xc0, 0x04,
    0x16, 0xe0, 0x00, 0x04, 0x1c, 0x67, 0x05, 0x1c, 0x07, 0x00, 0x04, 0x1c, 0x31, 0x04, 0x1d, 0xe1,
    0x00, 0x06, 0x10, 0x43, 0x41, 0x05, 0x1c, 0x64, 0xe7, 0x06, 0x7d, 0x71, 0x00, 0xe0, 0x07, 0x7a,
    0xe1, 0xe1, 0x52, 0x10, 0x08, 0x7a, 0x20, 0xe1, 0x26, 0x70, 0x06, 0x78, 0x50, 0xe5, 0x8d, 0x07,
    0x7a, 0xe3, 0xea, 0x0b, 0x10, 0x07, 0x75, 0xe0, 0x05, 0x40, 0x05, 0x7c, 0x32, 0x00, 0x06, 0x70,
    0x32, 0xbc, 0x04, 0x73, 0xe0, 0x00, 0x06, 0x71, 0x26, 0x49, 0x06, 0xe5, 0x37, 0x40, 0xe9, 0x10,
    0x06, 0x7c, 0x5a, 0x80, 0xe2, 0x05, 0xd0, 0x32, 0x70, 0x04, 0x12, 0xa0, 0x06, 0x32, 0x5a, 0x40,
    0xe2, 0x06, 0x20, 0x1a, 0x24, 0x05, 0x26, 0x9c, 0x10, 0x06, 0x20, 0xe4, 0x60, 0xe5, 0x05, 0x20,
    0x30, 0xe2, 0xd0, 0x07, 0xe1, 0x25, 0x92, 0x30, 0xe0, 0x05, 0x02, 0x25, 0x20, 0x05, 0x25, 0xa1,
    0x00, 0x06, 0x20, 0x38, 0x8d, 0x05, 0x10, 0x71, 0x70, 0x05, 0xef, 0xa0, 0x2d, 0x04, 0xe3, 0x85,
    0xe3, 0x07, 0xe6, 0x03, 0x1a, 0x20, 0x06, 0x67, 0x7a, 0x07, 0x08, 0xe2, 0x07, 0xb2, 0x60, 0xe3,
    0x00, 0x07, 0x20, 0xef, 0xa0, 0x71, 0x07, 0x71, 0x32, 0x10, 0x20, 0x06, 0x70, 0xe1, 0x26, 0x49,
    0x08, 0xe1, 0x25, 0xe3, 0x30, 0xe3, 0x8d, 0x06, 0xe1, 0xa0, 0xe3, 0x86, 0xb0, 0x06, 0xe1, 0x32,
    0x04, 0x10, 0x07, 0xe1, 0x25, 0xe2, 0xab, 0x10, 0x07, 0xe1, 0x25, 0xe3, 0x80, 0xe0, 0x05, 0xe1,
    0x56, 0x41, 0x04, 0xc1, 0x10, 0xe1, 0x05, 0xe1, 0x83, 0xb0, 0x07, 0xe1, 0x26, 0xe4, 0x3b, 0xd0,
    0x07, 0xe1, 0x25, 0xe0, 0x67, 0x00, 0x06, 0xe1, 0x80, 0x37, 0x00, 0x06, 0xe1, 0x05, 0xe1, 0x80,
    0x07, 0xb5, 0xe0, 0xe1, 0x34, 0xd0, 0x06, 0x04, 0x5a, 0x9c, 0x04, 0x40, 0x32, 0x07, 0x34, 0x51,
    0xc0, 0x20, 0x07, 0x64, 0x71, 0x03, 0xe2, 0x04, 0x64, 0x15, 0x08, 0x34, 0xd1, 0xc6, 0x49, 0x06,
    0x4a, 0xe0, 0xe3, 0x02, 0x06, 0x34, 0xd0, 0xe5, 0x3d, 0x04, 0x4a, 0x88, 0x06, 0x76, 0x49, 0x80,
    0x0a, 0xa4, 0xe2, 0x02, 0x71, 0x34, 0xe2, 0x06, 0xe0, 0xd7, 0x08, 0xe6, 0x05, 0xe0, 0xa7, 0x6b,
    0x05, 0xe0, 0x30, 0xea, 0x52, 0x06, 0xe0, 0x64, 0xa1, 0x00, 0x05, 0xe0, 0x69, 0xc1, 0x07, 0xe0,
    0x07, 0x73, 0x90, 0x04, 0x75, 0xe0, 0x00, 0x06, 0xe0, 0x01, 0xc5, 0xe2, 0x04, 0x89, 0x10, 0xe0,
    0x04, 0xe0, 0x52, 0x00, 0x04, 0x54, 0x8d, 0x06, 0x38, 0xe0, 0x57, 0x10, 0x05, 0x83, 0x10, 0x20,
    0x05, 0x38, 0x54, 0x90, 0x05, 0x83, 0x29, 0x00, 0x05, 0x86, 0x9c, 0x10, 0x06, 0xc0, 0x38, 0x1c,
    0x05, 0x80, 0x30, 0xe4, 0x00, 0x04, 0x38, 0x75, 0x05, 0xb8, 0x37, 0x70, 0x05, 0x80, 0xe4, 0x08,
    0x04, 0x86, 0xe7, 0x00, 0x07, 0xef, 0xa6, 0xb0, 0xe7, 0x8d, 0x06, 0xb3, 0x88, 0x02, 0x04, 0xe5,
    0x52, 0xe7, 0x04, 0xe7, 0x45, 0xe5, 0x04, 0xea, 0x30, 0xe4, 0x30, 0x04, 0xe7, 0x64, 0xe2, 0x05,
    0xbc, 0x0b, 0xe7, 0x04, 0xe7, 0x00, 0xe1, 0x04, 0xe0, 0x30, 0xe7, 0x00, 0x03, 0xe7, 0x0d, 0x06,
    0xb5, 0x40, 0xe6, 0x69, 0x08, 0xef, 0xa0, 0x71, 0x65, 0x40, 0x0c, 0xee, 0x23, 0xe6, 0x34, 0x30,
    0xe8, 0xf3, 0x30, 0xe3, 0x70, 0x07, 0xee, 0x23, 0xe6, 0x34, 0x30, 0x05, 0x51, 0xc0, 0x20, 0x1d,
    0x92, 0x09, 0x52, 0xed, 0xec, 0x06, 0x18, 0x64, 0x90, 0x20, 0xf0, 0x92, 0x30, 0xe6, 0x34, 0x30,
    0xed, 0xb5, 0xe0, 0x04, 0xe5, 0xc0, 0x40, 0x06, 0x60, 0xe0, 0xe1, 0x52, 0x10, 0x04, 0xea, 0xa7,
    0x10, 0x14, 0x92, 0x09, 0x52, 0xf0, 0xec, 0x06, 0x18, 0x64, 0x90, 0x20, 0xed, 0xe2, 0x00, 0x14,
    0xec, 0x06, 0x18, 0x64, 0x90, 0x20, 0xf0, 0x90, 0xe0, 0x36, 0x80, 0xed, 0xb5, 0xe0, 0x0a, 0xf2,
    0x06, 0x18, 0x64, 0x90, 0x20, 0x06, 0xee, 0x20, 0x95, 0x20, 0x05, 0x00, 0xe4, 0x02, 0xd0, 0x05,
    0x9a, 0x07, 0x70, 0x05, 0x92, 0x03, 0x10, 0x05, 0x92, 0x5a, 0xe1, 0x07, 0x90, 0x40, 0x23, 0x80,
    0x06, 0x96, 0xe4, 0x64, 0x90, 0x06, 0x26, 0x9c, 0x17, 0x05, 0xe3, 0x09, 0x34, 0x06, 0x98, 0x34,
    0xb0, 0x05, 0x39, 0x36, 0x40, 0x05, 0xe6, 0x52, 0x1d, 0x05, 0xe6, 0x5a, 0x40, 0xe2, 0x08, 0x75,
    0xe6, 0x10, 0xe5, 0x32, 0x00, 0x0b, 0x64, 0xe6, 0x52, 0xe0, 0x31, 0x65, 0x40, 0x06, 0xe6, 0x64,
    0x90, 0x20, 0x05, 0xe6, 0x62, 0x71, 0x04, 0x1c, 0x04, 0x04, 0xe6, 0x00, 0x80, 0x05, 0x30, 0xe6,
    0x10, 0x20, 0x05, 0xe6, 0x38, 0x70, 0x05, 0xe6, 0x36, 0x87, 0x04, 0xe6, 0x25, 0xe0, 0x07, 0x38,
    0x20, 0x30, 0xe2, 0xd0, 0x08, 0xe1, 0x25, 0xe2, 0xab, 0x17, 0x05, 0x1c, 0x06, 0x20, 0x05, 0xe3,
    0xa6, 0x80, 0xe2, 0x06, 0xe2, 0xa2, 0x64, 0x90, 0x04, 0x1c, 0x34, 0x04, 0x1c, 0x00, 0xe0, 0x05,
    0x15, 0xe2, 0x3d, 0x04, 0xe2, 0x31, 0x30, 0x06, 0xc3, 0xe2, 0x40, 0xe9, 0x10, 0x06, 0xe2, 0x60,
    0xe2, 0x40, 0xe9, 0x10, 0x06, 0xe1, 0x58, 0x6b, 0xd0, 0x07, 0xba, 0x22, 0x04, 0x10, 0x06, 0x3b,
    0x25, 0x77, 0x08, 0xb5, 0x41, 0x64, 0xa0, 0x07, 0xe1, 0x25, 0xea, 0x0b, 0x10, 0x05, 0xb8, 0x6b,
    0xe7, 0x08, 0x20, 0x70, 0x32, 0xbc, 0x07, 0x70, 0x20, 0xe4, 0x6b, 0x00, 0x08, 0x3b, 0x1a, 0x38,
    0x8d, 0x05, 0xb5, 0x47, 0x10, 0x08, 0xb5, 0xa8, 0xe2, 0x40, 0xe9, 0x10, 0x05, 0xb5, 0xa8, 0xe2,
    0x04, 0xe3, 0x50, 0xe2, 0xd0, 0x08, 0xe3, 0xa7, 0x64, 0x07, 0x70, 0x05, 0xe3, 0x20, 0x30, 0xe7,
    0x06, 0xe3, 0x0b, 0x50, 0xe0, 0x00, 0x07, 0xe3, 0x01, 0xe5, 0x00, 0x40, 0x05, 0xe3, 0x06, 0x49,
    0x06, 0xe3, 0x0c, 0x64, 0xe2, 0x04, 0xe3, 0x00, 0x40, 0x07, 0xe3, 0x55, 0x80, 0x34, 0x0d, 0x50,
    0xe3, 0x70, 0x20, 0xe4, 0x30, 0xe3, 0x68, 0x61, 0xd0, 0x05, 0x30, 0xe3, 0x5a, 0x10, 0x06, 0x0b,
    0x3a, 0x70, 0x06, 0x50, 0x74, 0xe9, 0x10, 0x03, 0x50, 0x70, 0x04, 0x54, 0xe9, 0x10, 0x02, 0x52,
    0x02, 0x0d, 0x03, 0xe9, 0xe4, 0x00, 0x03, 0xa7, 0x10, 0x03, 0x45, 0xe5, 0x03, 0x04, 0x10, 0x02,
    0x8d, 0x03, 0x65, 0x40, 0x03, 0x64, 0x90, 0x02, 0x02, 0x02, 0x04, 0x09, 0x06, 0x18, 0x64, 0x90,
    0x20, 0x04, 0x1c, 0x00, 0xe8, 0x04, 0x34, 0xe2, 0xe8, 0x05, 0xe8, 0xe3, 0xa1, 0xe8, 0x05, 0xe8,
    0x34, 0xe2, 0xe8, 0x02, 0xed, 0xf8
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

int chord_transition(int state, uint16_t keycode) {
    switch (state) {
                // z
                case -224:
                    if (keycode == KC_SPC) return 53; // "realize"
                    if (keycode == KC_COMMA) return 48; // "smile"
                    if (keycode == KC_DOT) return 44; // "async"
                    if (keycode == KC_A) return 38; // "organize"
                    if (keycode == KC_E) return 32; // "GitHub"
                    if (keycode == KC_H) return 22; // "Spring starter"
                    if (keycode == KC_J) return 15; // "javaagent"
                    if (keycode == KC_R) return 9; // "rolldice"
                    if (keycode == KC_U) return 0; // "Spring Boot"
                    break;
                // x
                case -211:
                    if (keycode == KC_SPC) return 134; // "context"
                    if (keycode == KC_COMMA) return 121; // "declarative config"
                    if (keycode == KC_DOT) return 115; // "export"
                    if (keycode == KC_A) return 108; // "example"
                    if (keycode == KC_E) return 102; // "execute"
                    if (keycode == KC_H) return 97; // "https"
                    if (keycode == KC_I) return 91; // "existing"
                    if (keycode == KC_J) return 84; // "exception"
                    if (keycode == KC_O) return 74; // "OpenTelemetry"
                    if (keycode == KC_R) return 69; // "resource"
                    if (keycode == KC_U) return 65; // "actual"
                    if (keycode == KC_Y) return 59; // "telemetry"
                    break;
                // w
                case -199:
                    if (keycode == KC_SPC) return 187; // "would"
                    if (keycode == KC_COMMA) return 179; // "wouldn't"
                    if (keycode == KC_DOT) return 174; // "await"
                    if (keycode == KC_A) return 170; // "walk"
                    if (keycode == KC_H) return 166; // "which"
                    if (keycode == KC_I) return 162; // "with"
                    if (keycode == KC_J) return 158; // "wrong"
                    if (keycode == KC_O) return 153; // "without"
                    if (keycode == KC_R) return 149; // "where"
                    if (keycode == KC_U) return 144; // "internal"
                    if (keycode == KC_Y) return 140; // "worry"
                    break;
                // v
                case -186:
                    if (keycode == KC_SPC) return 246; // "have"
                    if (keycode == KC_COMMA) return 241; // "contrib"
                    if (keycode == KC_DOT) return 237; // "void"
                    if (keycode == KC_A) return 230; // "available"
                    if (keycode == KC_E) return 226; // "very"
                    if (keycode == KC_H) return 221; // "version"
                    if (keycode == KC_I) return 215; // "services"
                    if (keycode == KC_J) return 211; // "notice"
                    if (keycode == KC_O) return 207; // "over"
                    if (keycode == KC_R) return 203; // "never"
                    if (keycode == KC_U) return 199; // "value"
                    if (keycode == KC_Y) return 192; // "everything"
                    break;
                // t
                case -173:
                    if (keycode == KC_SPC) return 293; // "think"
                    if (keycode == KC_COMMA) return 289; // "tenant"
                    if (keycode == KC_DOT) return 285; // "type"
                    if (keycode == KC_A) return 282; // "that"
                    if (keycode == KC_E) return 278; // "these"
                    if (keycode == KC_H) return 275; // "this"
                    if (keycode == KC_I) return 271; // "time"
                    if (keycode == KC_J) return 266; // "through"
                    if (keycode == KC_O) return 261; // "thought"
                    if (keycode == KC_R) return 257; // "there"
                    if (keycode == KC_U) return 253; // "though"
                    if (keycode == KC_Y) return 250; // "they"
                    break;
                // s
                case -160:
                    if (keycode == KC_SPC) return 352; // "should"
                    if (keycode == KC_COMMA) return 346; // "wasn't"
                    if (keycode == KC_DOT) return 342; // "string"
                    if (keycode == KC_A) return 338; // "same"
                    if (keycode == KC_E) return 334; // "search"
                    if (keycode == KC_H) return 330; // "share"
                    if (keycode == KC_I) return 325; // "someone"
                    if (keycode == KC_J) return 319; // "subject"
                    if (keycode == KC_O) return 314; // "slowly"
                    if (keycode == KC_R) return 308; // "surprise"
                    if (keycode == KC_U) return 302; // "support"
                    if (keycode == KC_Y) return 297; // "system"
                    break;
                // r
                case -148:
                    if (keycode == KC_SPC) return 401; // "really"
                    if (keycode == KC_COMMA) return 397; // "route"
                    if (keycode == KC_DOT) return 393; // "error"
                    if (keycode == KC_A) return 387; // "program"
                    if (keycode == KC_E) return 382; // "ready"
                    if (keycode == KC_H) return 377; // "review"
                    if (keycode == KC_I) return 373; // "right"
                    if (keycode == KC_J) return 369; // "return"
                    if (keycode == KC_O) return 364; // "around"
                    if (keycode == KC_U) return 361; // "true"
                    if (keycode == KC_Y) return 357; // "years"
                    break;
                // q
                case -138:
                    if (keycode == KC_SPC) return 443; // "spring"
                    if (keycode == KC_A) return 438; // "starter"
                    if (keycode == KC_E) return 433; // "request"
                    if (keycode == KC_H) return 426; // "describe"
                    if (keycode == KC_I) return 422; // "issues"
                    if (keycode == KC_J) return 417; // "feature"
                    if (keycode == KC_O) return 413; // "blob"
                    if (keycode == KC_U) return 409; // "query"
                    if (keycode == KC_Y) return 405; // "tests"
                    break;
                // p
                case -125:
                    if (keycode == KC_SPC) return 507; // "people"
                    if (keycode == KC_COMMA) return 502; // "please"
                    if (keycode == KC_DOT) return 496; // "promise"
                    if (keycode == KC_A) return 490; // "privacy"
                    if (keycode == KC_E) return 486; // "place"
                    if (keycode == KC_H) return 482; // "http"
                    if (keycode == KC_I) return 478; // "point"
                    if (keycode == KC_J) return 472; // "problem"
                    if (keycode == KC_O) return 466; // "product"
                    if (keycode == KC_R) return 461; // "parent"
                    if (keycode == KC_U) return 455; // "public"
                    if (keycode == KC_Y) return 448; // "probably"
                    break;
                // n
                case -112:
                    if (keycode == KC_SPC) return 560; // "understand"
                    if (keycode == KC_COMMA) return 556; // "single"
                    if (keycode == KC_DOT) return 553; // "null"
                    if (keycode == KC_A) return 548; // "anyway"
                    if (keycode == KC_E) return 543; // "number"
                    if (keycode == KC_H) return 538; // "anything"
                    if (keycode == KC_I) return 535; // "into"
                    if (keycode == KC_J) return 530; // "instead"
                    if (keycode == KC_O) return 525; // "another"
                    if (keycode == KC_R) return 522; // "near"
                    if (keycode == KC_U) return 518; // "enough"
                    if (keycode == KC_Y) return 512; // "company"
                    break;
                // m
                case -101:
                    if (keycode == KC_SPC) return 608; // "more"
                    if (keycode == KC_COMMA) return 604; // "lgtm"
                    if (keycode == KC_DOT) return 599; // "method"
                    if (keycode == KC_A) return 595; // "some"
                    if (keycode == KC_E) return 590; // "message"
                    if (keycode == KC_H) return 586; // "might"
                    if (keycode == KC_I) return 581; // "minute"
                    if (keycode == KC_J) return 576; // "major"
                    if (keycode == KC_U) return 572; // "music"
                    if (keycode == KC_Y) return 567; // "myself"
                    break;
                // k
                case -76:
                    if (keycode == KC_SPC) return 708; // "question"
                    if (keycode == KC_COMMA) return 703; // "config"
                    if (keycode == KC_DOT) return 700; // "key"
                    if (keycode == KC_A) return 695; // "make"
                    if (keycode == KC_E) return 691; // "keep"
                    if (keycode == KC_H) return 687; // "check"
                    if (keycode == KC_I) return 683; // "kind"
                    if (keycode == KC_J) return 678; // "java"
                    if (keycode == KC_O) return 674; // "know"
                    if (keycode == KC_R) return 670; // "work"
                    if (keycode == KC_U) return 666; // "caller"
                    if (keycode == KC_Y) return 660; // "quickly"
                    break;
                // j
                case -68:
                    if (keycode == KC_SPC) return 765; // "just"
                    if (keycode == KC_COMMA) return 725; // "Grafana"
                    if (keycode == KC_DOT) return 714; // "Grafana Labs"
                    if (keycode == KC_A) return 759; // "import"
                    if (keycode == KC_E) return 755; // "when"
                    if (keycode == KC_H) return 735; // "gregor.zeitlinger@grafana.com"
                    if (keycode == KC_O) return 731; // "other"
                    break;
                // l
                case -65:
                    if (keycode == KC_SPC) return 656; // "like"
                    if (keycode == KC_COMMA) return 652; // "level"
                    if (keycode == KC_DOT) return 648; // "class"
                    if (keycode == KC_A) return 645; // "also"
                    if (keycode == KC_D) return 783; // "zeitlinger@gmail.com"
                    if (keycode == KC_E) return 640; // "leave"
                    if (keycode == KC_F) return 769; // "gregor@zeitlinger.de"
                    if (keycode == KC_H) return 636; // "health"
                    if (keycode == KC_I) return 632; // "light"
                    if (keycode == KC_J) return 628; // "large"
                    if (keycode == KC_O) return 624; // "along"
                    if (keycode == KC_R) return 620; // "later"
                    if (keycode == KC_U) return 615; // "almost"
                    if (keycode == KC_Y) return 612; // "only"
                    break;
                // g
                case -52:
                    if (keycode == KC_SPC) return 849; // "again"
                    if (keycode == KC_COMMA) return 805; // "Gregor"
                    if (keycode == KC_DOT) return 798; // "Zeitlinger"
                    if (keycode == KC_A) return 845; // "glance"
                    if (keycode == KC_E) return 841; // "began"
                    if (keycode == KC_H) return 837; // "rights"
                    if (keycode == KC_I) return 832; // "giving"
                    if (keycode == KC_J) return 827; // "general"
                    if (keycode == KC_O) return 823; // "group"
                    if (keycode == KC_R) return 819; // "great"
                    if (keycode == KC_U) return 815; // "guess"
                    if (keycode == KC_Y) return 810; // "every"
                    break;
                // f
                case -39:
                    if (keycode == KC_SPC) return 906; // "from"
                    if (keycode == KC_COMMA) return 902; // "fails"
                    if (keycode == KC_DOT) return 898; // "false"
                    if (keycode == KC_A) return 893; // "after"
                    if (keycode == KC_E) return 889; // "feel"
                    if (keycode == KC_H) return 886; // "then"
                    if (keycode == KC_I) return 882; // "first"
                    if (keycode == KC_J) return 877; // "finger"
                    if (keycode == KC_O) return 869; // "information"
                    if (keycode == KC_R) return 862; // "software"
                    if (keycode == KC_U) return 857; // "found"
                    if (keycode == KC_Y) return 853; // "forty"
                    break;
                // d
                case -27:
                    if (keycode == KC_SPC) return 957; // "didn't"
                    if (keycode == KC_COMMA) return 951; // "hadn't"
                    if (keycode == KC_DOT) return 947; // "data"
                    if (keycode == KC_A) return 943; // "today"
                    if (keycode == KC_E) return 939; // "them"
                    if (keycode == KC_H) return 936; // "than"
                    if (keycode == KC_I) return 931; // "during"
                    if (keycode == KC_J) return 926; // "build"
                    if (keycode == KC_R) return 922; // "their"
                    if (keycode == KC_U) return 916; // "products"
                    if (keycode == KC_Y) return 910; // "already"
                    break;
                // c
                case -14:
                    if (keycode == KC_SPC) return 1020; // "could"
                    if (keycode == KC_COMMA) return 1013; // "couldn't"
                    if (keycode == KC_DOT) return 1009; // "const"
                    if (keycode == KC_A) return 1004; // "actually"
                    if (keycode == KC_E) return 998; // "service"
                    if (keycode == KC_H) return 993; // "research"
                    if (keycode == KC_I) return 989; // "click"
                    if (keycode == KC_J) return 983; // "project"
                    if (keycode == KC_O) return 978; // "continue"
                    if (keycode == KC_R) return 974; // "across"
                    if (keycode == KC_U) return 969; // "current"
                    if (keycode == KC_Y) return 964; // "policy"
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return 1081; // "about"
                    if (keycode == KC_COMMA) return 1070; // "observability"
                    if (keycode == KC_DOT) return 1065; // "boolean"
                    if (keycode == KC_A) return 1061; // "been"
                    if (keycode == KC_H) return 1056; // "behind"
                    if (keycode == KC_I) return 1052; // "being"
                    if (keycode == KC_J) return 1046; // "between"
                    if (keycode == KC_O) return 1040; // "become"
                    if (keycode == KC_R) return 1035; // "break"
                    if (keycode == KC_U) return 1029; // "business"
                    if (keycode == KC_Y) return 1024; // "body"
                    break;
                case -1:
                    if (keycode == KC_B) return -2; // b...
                    if (keycode == KC_C) return -14; // c...
                    if (keycode == KC_D) return -27; // d...
                    if (keycode == KC_F) return -39; // f...
                    if (keycode == KC_G) return -52; // g...
                    if (keycode == KC_J) return -68; // j...
                    if (keycode == KC_K) return -76; // k...
                    if (keycode == KC_L) return -65; // l...
                    if (keycode == KC_M) return -101; // m...
                    if (keycode == KC_N) return -112; // n...
                    if (keycode == KC_P) return -125; // p...
                    if (keycode == KC_Q) return -138; // q...
                    if (keycode == KC_R) return -148; // r...
                    if (keycode == KC_S) return -160; // s...
                    if (keycode == KC_T) return -173; // t...
                    if (keycode == KC_V) return -186; // v...
                    if (keycode == KC_W) return -199; // w...
                    if (keycode == KC_X) return -211; // x...
                    if (keycode == KC_Z) return -224; // z...
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
                    case KC_COMMA: chord_decode_send(1145); return false; // " but "
                    case KC_D: chord_decode_send(1090); return false; // "oesn't"
                    case KC_DOT: tap_code16(KC_SLASH); return false;
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_ENT: chord_decode_send(1137); return false; // "the "
                    case KC_EQUAL: tap_code16(KC_RABK); return false;
                    case KC_EXLM: tap_code16(KC_EQUAL); return false;
                    case KC_F: tap_code16(KC_F); return false;
                    case KC_G: tap_code16(KC_N); return false;
                    case KC_H: tap_code16(KC_Y); return false;
                    case KC_I: tap_code16(KC_QUOTE); return false;
                    case KC_J: chord_decode_send(1110); return false; // "ust"
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_P); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_MINUS: tap_code16(KC_RABK); return false;
                    case KC_N: tap_code16(KC_G); return false;
                    case KC_O: tap_code16(KC_E); return false;
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_R: tap_code16(KC_K); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: chord_decode_send(1137); return false; // "the "
                    case KC_T: chord_decode_send(1121); return false; // "ion"
                    case KC_TAB: chord_decode_send(1137); return false; // "the "
                    case KC_TILD: tap_code16(KC_SLASH); return false;
                    case KC_V: chord_decode_send(1127); return false; // "er"
                    case KC_W: tap_code16(KC_N); return false;
                    case KC_X: tap_code16(KC_P); return false;
                    case KC_Z: chord_decode_send(1131); return false; // "eitlinger"
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): chord_decode_send(1090); return false; // "oesn't"
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_F): tap_code16(KC_F); return false;
                    case S(KC_G): tap_code16(KC_N); return false;
                    case S(KC_H): tap_code16(KC_Y); return false;
                    case S(KC_I): tap_code16(KC_QUOTE); return false;
                    case S(KC_J): chord_decode_send(1110); return false; // "ust"
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_P); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): tap_code16(KC_G); return false;
                    case S(KC_O): tap_code16(KC_E); return false;
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_R): tap_code16(KC_K); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): chord_decode_send(1121); return false; // "ion"
                    case S(KC_V): chord_decode_send(1127); return false; // "er"
                    case S(KC_W): tap_code16(KC_N); return false;
                    case S(KC_X): tap_code16(KC_P); return false;
                    case S(KC_Z): chord_decode_send(1131); return false; // "eitlinger"
                }
                return false;
            case MAGIC_B:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_U); return false;
                    case KC_B: chord_decode_send(1086); return false; // "ecause"
                    case KC_C: tap_code16(KC_P); return false;
                    case KC_COMMA: chord_decode_send(1150); return false; // " and "
                    case KC_D: chord_decode_send(1095); return false; // "oes"
                    case KC_DOT: chord_decode_send(1155); return false; // "./"
                    case KC_ENT: chord_decode_send(1141); return false; // "and "
                    case KC_F: chord_decode_send(1102); return false; // "or"
                    case KC_G: tap_code16(KC_K); return false;
                    case KC_H: chord_decode_send(1104); return false; // "ey"
                    case KC_I: chord_decode_send(1106); return false; // "'ve"
                    case KC_K: chord_decode_send(1113); return false; // "now"
                    case KC_L: tap_code16(KC_M); return false;
                    case KC_M: chord_decode_send(1116); return false; // "ent"
                    case KC_N: tap_code16(KC_K); return false;
                    case KC_P: tap_code16(KC_S); return false;
                    case KC_S: chord_decode_send(1121); return false; // "ion"
                    case KC_SPC: tap_code16(KC_BSPC); SEND_STRING(". "); add_oneshot_mods(MOD_BIT(KC_LSFT)); return false;
                    case KC_T: chord_decode_send(1124); return false; // "ing"
                    case KC_TAB: chord_decode_send(1141); return false; // "and "
                    case KC_U: tap_code16(KC_A); return false;
                    case KC_V: chord_decode_send(1129); return false; // "en"
                    case KC_W: tap_code16(KC_S); return false;
                    case KC_X: tap_code16(KC_C); return false;
                    case S(KC_A): tap_code16(KC_U); return false;
                    case S(KC_B): chord_decode_send(1086); return false; // "ecause"
                    case S(KC_C): tap_code16(KC_P); return false;
                    case S(KC_D): chord_decode_send(1095); return false; // "oes"
                    case S(KC_F): chord_decode_send(1102); return false; // "or"
                    case S(KC_G): tap_code16(KC_K); return false;
                    case S(KC_H): chord_decode_send(1104); return false; // "ey"
                    case S(KC_I): chord_decode_send(1106); return false; // "'ve"
                    case S(KC_K): chord_decode_send(1113); return false; // "now"
                    case S(KC_L): tap_code16(KC_M); return false;
                    case S(KC_M): chord_decode_send(1116); return false; // "ent"
                    case S(KC_N): tap_code16(KC_K); return false;
                    case S(KC_P): tap_code16(KC_S); return false;
                    case S(KC_S): chord_decode_send(1121); return false; // "ion"
                    case S(KC_T): chord_decode_send(1124); return false; // "ing"
                    case S(KC_U): tap_code16(KC_A); return false;
                    case S(KC_V): chord_decode_send(1129); return false; // "en"
                    case S(KC_W): tap_code16(KC_S); return false;
                    case S(KC_X): tap_code16(KC_C); return false;
                }
                return false;
            case MAGIC_C:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_U); return false;
                    case KC_B: tap_code16(KC_L); return false;
                    case KC_C: tap_code16(KC_K); return false;
                    case KC_D: chord_decode_send(1098); return false; // "on't"
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_G: tap_code16(KC_L); return false;
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_V); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_N: chord_decode_send(1119); return false; // "ly"
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: chord_decode_send(1137); return false; // "the "
                    case KC_T: chord_decode_send(1121); return false; // "ion"
                    case S(KC_A): tap_code16(KC_U); return false;
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): chord_decode_send(1098); return false; // "on't"
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_G): tap_code16(KC_L); return false;
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_V); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): chord_decode_send(1119); return false; // "ly"
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): chord_decode_send(1121); return false; // "ion"
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
