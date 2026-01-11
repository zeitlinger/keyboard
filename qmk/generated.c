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
    0x25, 0x49, 0x04, 0xe5, 0x68, 0x80, 0x05, 0xe5, 0xc6, 0xbc, 0x04, 0xe5, 0x38, 0xe7, 0x05, 0x30,
    0xe5, 0x36, 0x10, 0x08, 0xe5, 0x5a, 0x80, 0xe2, 0x40, 0xe9, 0x10, 0x05, 0xe5, 0x5a, 0x80, 0xe2,
    0x0a, 0x00, 0xe4, 0x02, 0xd1, 0xc6, 0x49, 0x05, 0xe4, 0x38, 0xa0, 0x05, 0x40, 0xe4, 0x02, 0x04,
    0x50, 0xe4, 0x02, 0x06, 0x45, 0x16, 0xb0, 0x08, 0x70, 0x20, 0xe4, 0x6b, 0x07, 0x07, 0xe4, 0x02,
    0x76, 0x54, 0x04, 0xe4, 0x02, 0xd0, 0x09, 0x30, 0xe4, 0x36, 0x83, 0xe3, 0x80, 0x04, 0xe4, 0x56,
    0xe2, 0x07, 0xb5, 0x41, 0x26, 0xe3, 0x04, 0x00, 0xe4, 0x04, 0x04, 0x1c, 0x0d, 0x06, 0x1c, 0x5a,
    0x9c, 0x05, 0x1c, 0x02, 0x00, 0x07, 0x1c, 0x5a, 0x9c, 0x10, 0x07, 0x1c, 0x25, 0xa9, 0xc0, 0x04,
    0x16, 0xe0, 0x00, 0x05, 0x1c, 0x07, 0x00, 0x05, 0x15, 0xe2, 0x3d, 0x04, 0x1d, 0xe1, 0x00, 0x06,
    0x10, 0x43, 0x41, 0x05, 0x1c, 0x64, 0xe7, 0x06, 0x7d, 0x71, 0x00, 0xe0, 0x07, 0x7a, 0xe1, 0xe1,
    0x52, 0x10, 0x08, 0x7a, 0x20, 0xe1, 0x26, 0x70, 0x06, 0x78, 0x50, 0xe5, 0x8d, 0x07, 0x7a, 0xe3,
    0xea, 0x0b, 0x10, 0x07, 0x75, 0xe0, 0x05, 0x40, 0x05, 0x7c, 0x32, 0x00, 0x06, 0x70, 0x32, 0xbc,
    0x04, 0x73, 0xe0, 0x00, 0x06, 0x71, 0x26, 0x49, 0x06, 0xe5, 0x37, 0x40, 0xe9, 0x10, 0x06, 0x7c,
    0x5a, 0x80, 0xe2, 0x05, 0xd0, 0x32, 0x70, 0x04, 0x12, 0xa0, 0x06, 0x32, 0x5a, 0x40, 0xe2, 0x06,
    0x20, 0x1a, 0x24, 0x05, 0x26, 0x9c, 0x10, 0x06, 0x20, 0xe4, 0x60, 0xe5, 0x05, 0x20, 0x30, 0xe2,
    0xd0, 0x07, 0xe1, 0x25, 0x92, 0x30, 0xe0, 0x05, 0x02, 0x25, 0x20, 0x05, 0x25, 0xa1, 0x00, 0x06,
    0x20, 0x38, 0x8d, 0x05, 0x10, 0x71, 0x70, 0x05, 0xef, 0xa0, 0x2d, 0x04, 0xe3, 0x85, 0xe3, 0x07,
    0xe6, 0x03, 0x1a, 0x20, 0x06, 0x67, 0x7a, 0x07, 0x08, 0xe2, 0x07, 0xb2, 0x60, 0xe3, 0x00, 0x07,
    0x20, 0xef, 0xa0, 0x71, 0x07, 0x71, 0x32, 0x10, 0x20, 0x06, 0x70, 0xe1, 0x26, 0x49, 0x08, 0xe1,
    0x25, 0xe3, 0x30, 0xe3, 0x8d, 0x06, 0xe1, 0xa0, 0xe3, 0x86, 0xb0, 0x06, 0xe1, 0x32, 0x04, 0x10,
    0x07, 0xe1, 0x25, 0xe2, 0xab, 0x10, 0x07, 0xe1, 0x25, 0xe3, 0x80, 0xe0, 0x05, 0xe1, 0x56, 0x41,
    0x04, 0xc1, 0x10, 0xe1, 0x05, 0xe1, 0x83, 0xb0, 0x07, 0xe1, 0x26, 0xe4, 0x3b, 0xd0, 0x07, 0xe1,
    0x25, 0xe0, 0x67, 0x00, 0x06, 0xe1, 0x80, 0x37, 0x00, 0x06, 0xe1, 0x05, 0xe1, 0x80, 0x07, 0xb5,
    0xe0, 0xe1, 0x34, 0xd0, 0x06, 0x04, 0x5a, 0x9c, 0x04, 0x1c, 0x31, 0x04, 0x40, 0x32, 0x07, 0x34,
    0x51, 0xc0, 0x20, 0x07, 0x64, 0x71, 0x03, 0xe2, 0x04, 0x64, 0x15, 0x08, 0x34, 0xd1, 0xc6, 0x49,
    0x06, 0x4a, 0xe0, 0xe3, 0x02, 0x06, 0x34, 0xd0, 0xe5, 0x3d, 0x04, 0x4a, 0x88, 0x06, 0x76, 0x49,
    0x80, 0x0a, 0xa4, 0xe2, 0x02, 0x71, 0x34, 0xe2, 0x06, 0xe0, 0xd7, 0x08, 0xe6, 0x05, 0xe0, 0xa7,
    0x6b, 0x05, 0xe0, 0x30, 0xea, 0x52, 0x06, 0xe0, 0x64, 0xa1, 0x00, 0x05, 0xe0, 0x69, 0xc1, 0x07,
    0xe0, 0x07, 0x73, 0x90, 0x04, 0x75, 0xe0, 0x00, 0x06, 0xe0, 0x01, 0xc5, 0xe2, 0x04, 0x89, 0x10,
    0xe0, 0x04, 0xe0, 0x52, 0x00, 0x04, 0x54, 0x8d, 0x06, 0x38, 0xe0, 0x57, 0x10, 0x05, 0x83, 0x10,
    0x20, 0x05, 0x38, 0x54, 0x90, 0x05, 0x83, 0x29, 0x00, 0x05, 0x86, 0x9c, 0x10, 0x06, 0xc0, 0x38,
    0x1c, 0x03, 0xe6, 0x52, 0x05, 0x80, 0x30, 0xe4, 0x00, 0x04, 0xe5, 0x61, 0xc0, 0x04, 0x38, 0x75,
    0x05, 0xb8, 0x37, 0x70, 0x05, 0x80, 0xe4, 0x08, 0x04, 0x86, 0xe7, 0x00, 0x07, 0xef, 0xa6, 0xb0,
    0xe7, 0x8d, 0x06, 0xb3, 0x88, 0x02, 0x04, 0xe5, 0x52, 0xe7, 0x04, 0xe7, 0x45, 0xe5, 0x04, 0xea,
    0x30, 0xe4, 0x30, 0x04, 0xe7, 0x64, 0xe2, 0x05, 0xbc, 0x0b, 0xe7, 0x04, 0xe7, 0x00, 0xe1, 0x04,
    0xe0, 0x30, 0xe7, 0x00, 0x03, 0xe7, 0x0d, 0x06, 0xb5, 0x40, 0xe6, 0x69, 0x08, 0xef, 0xa0, 0x71,
    0x65, 0x40, 0x0c, 0xee, 0x23, 0xe6, 0x34, 0x30, 0xe8, 0xf3, 0x30, 0xe3, 0x70, 0x07, 0xee, 0x23,
    0xe6, 0x34, 0x30, 0x05, 0x51, 0xc0, 0x20, 0x1d, 0x92, 0x09, 0x52, 0xed, 0xec, 0x06, 0x18, 0x64,
    0x90, 0x20, 0xf0, 0x92, 0x30, 0xe6, 0x34, 0x30, 0xed, 0xb5, 0xe0, 0x04, 0xe5, 0xc0, 0x40, 0x06,
    0x60, 0xe0, 0xe1, 0x52, 0x10, 0x04, 0xea, 0xa7, 0x10, 0x14, 0x92, 0x09, 0x52, 0xf0, 0xec, 0x06,
    0x18, 0x64, 0x90, 0x20, 0xed, 0xe2, 0x00, 0x14, 0xec, 0x06, 0x18, 0x64, 0x90, 0x20, 0xf0, 0x90,
    0xe0, 0x36, 0x80, 0xed, 0xb5, 0xe0, 0x0a, 0xf2, 0x06, 0x18, 0x64, 0x90, 0x20, 0x06, 0xee, 0x20,
    0x95, 0x20, 0x05, 0x00, 0xe4, 0x02, 0xd0, 0x05, 0x9a, 0x07, 0x70, 0x05, 0x92, 0x03, 0x10, 0x05,
    0x92, 0x5a, 0xe1, 0x07, 0x90, 0x40, 0x23, 0x80, 0x06, 0x96, 0xe4, 0x64, 0x90, 0x06, 0x26, 0x9c,
    0x17, 0x05, 0xe3, 0x09, 0x34, 0x06, 0x98, 0x34, 0xb0, 0x05, 0x39, 0x36, 0x40, 0x05, 0xe6, 0x52,
    0x1d, 0x05, 0xe6, 0x5a, 0x40, 0xe2, 0x08, 0x75, 0xe6, 0x10, 0xe5, 0x32, 0x00, 0x0b, 0x64, 0xe6,
    0x52, 0xe0, 0x31, 0x65, 0x40, 0x04, 0xc3, 0xe4, 0x00, 0x06, 0xe6, 0x64, 0x90, 0x20, 0x05, 0xe6,
    0x62, 0x71, 0x04, 0x1c, 0x04, 0x04, 0xe6, 0x00, 0x80, 0x05, 0x30, 0xe6, 0x10, 0x20, 0x05, 0xe6,
    0x38, 0x70, 0x05, 0xe6, 0x36, 0x87, 0x04, 0xe6, 0x25, 0xe0, 0x07, 0x38, 0x20, 0x30, 0xe2, 0xd0,
    0x08, 0xe1, 0x25, 0xe2, 0xab, 0x17, 0x05, 0x1c, 0x06, 0x20, 0x05, 0xe3, 0xa6, 0x80, 0xe2, 0x06,
    0xe2, 0xa2, 0x64, 0x90, 0x04, 0x1c, 0x34, 0x04, 0x1c, 0x00, 0xe0, 0x04, 0xe2, 0x31, 0x30, 0x06,
    0xc3, 0xe2, 0x40, 0xe9, 0x10, 0x06, 0xe2, 0x60, 0xe2, 0x40, 0xe9, 0x10, 0x06, 0xe1, 0x58, 0x6b,
    0xd0, 0x07, 0xba, 0x22, 0x04, 0x10, 0x04, 0x1c, 0x67, 0x06, 0x3b, 0x25, 0x77, 0x08, 0xb5, 0x41,
    0x64, 0xa0, 0x04, 0xe3, 0x00, 0x40, 0x07, 0xe1, 0x25, 0xea, 0x0b, 0x10, 0x05, 0xb8, 0x6b, 0xe7,
    0x08, 0x20, 0x70, 0x32, 0xbc, 0x07, 0x70, 0x20, 0xe4, 0x6b, 0x00, 0x08, 0x3b, 0x1a, 0x38, 0x8d,
    0x05, 0xb5, 0x47, 0x10, 0x08, 0xb5, 0xa8, 0xe2, 0x40, 0xe9, 0x10, 0x05, 0xb5, 0xa8, 0xe2, 0x04,
    0xe3, 0x50, 0xe2, 0xd0, 0x08, 0xe3, 0xa7, 0x64, 0x07, 0x70, 0x05, 0xe3, 0x20, 0x30, 0xe7, 0x06,
    0xe3, 0x0b, 0x50, 0xe0, 0x00, 0x07, 0xe3, 0x01, 0xe5, 0x00, 0x40, 0x05, 0xe3, 0x06, 0x49, 0x06,
    0xe3, 0x0c, 0x64, 0xe2, 0x07, 0xe3, 0x55, 0x80, 0x34, 0x0d, 0x50, 0xe3, 0x70, 0x20, 0xe4, 0x30,
    0xe3, 0x68, 0x61, 0xd0, 0x05, 0x30, 0xe3, 0x5a, 0x10, 0x06, 0x0b, 0x3a, 0x70, 0x06, 0x50, 0x74,
    0xe9, 0x10, 0x03, 0x50, 0x70, 0x04, 0x54, 0xe9, 0x10, 0x02, 0x52, 0x02, 0x0d, 0x03, 0xe9, 0xe4,
    0x00, 0x03, 0xa7, 0x10, 0x03, 0x45, 0xe5, 0x03, 0x04, 0x10, 0x02, 0x8d, 0x03, 0x65, 0x40, 0x03,
    0x64, 0x90, 0x02, 0x02, 0x02, 0x04, 0x09, 0x06, 0x18, 0x64, 0x90, 0x20, 0x04, 0x1c, 0x00, 0xe8,
    0x04, 0x34, 0xe2, 0xe8, 0x05, 0xe8, 0xe3, 0xa1, 0xe8, 0x05, 0xe8, 0x34, 0xe2, 0xe8, 0x02, 0xed,
    0xf8
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
                case -227:
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
                case -214:
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
                case -202:
                    if (keycode == KC_SPC) return 187; // "would"
                    if (keycode == KC_COMMA) return 179; // "wouldn't"
                    if (keycode == KC_DOT) return 174; // "await"
                    if (keycode == KC_A) return 170; // "walk"
                    if (keycode == KC_H) return 166; // "which"
                    if (keycode == KC_I) return 162; // "will"
                    if (keycode == KC_J) return 158; // "wrong"
                    if (keycode == KC_O) return 153; // "without"
                    if (keycode == KC_R) return 149; // "where"
                    if (keycode == KC_U) return 144; // "internal"
                    if (keycode == KC_Y) return 140; // "worry"
                    break;
                // v
                case -189:
                    if (keycode == KC_SPC) return 246; // "even"
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
                case -177:
                    if (keycode == KC_SPC) return 291; // "think"
                    if (keycode == KC_COMMA) return 287; // "tenant"
                    if (keycode == KC_DOT) return 283; // "type"
                    if (keycode == KC_A) return 279; // "today"
                    if (keycode == KC_E) return 275; // "these"
                    if (keycode == KC_I) return 271; // "time"
                    if (keycode == KC_J) return 266; // "through"
                    if (keycode == KC_O) return 261; // "thought"
                    if (keycode == KC_R) return 257; // "there"
                    if (keycode == KC_U) return 253; // "though"
                    if (keycode == KC_Y) return 250; // "they"
                    break;
                // s
                case -164:
                    if (keycode == KC_SPC) return 350; // "should"
                    if (keycode == KC_COMMA) return 344; // "wasn't"
                    if (keycode == KC_DOT) return 340; // "string"
                    if (keycode == KC_A) return 336; // "same"
                    if (keycode == KC_E) return 332; // "search"
                    if (keycode == KC_H) return 328; // "share"
                    if (keycode == KC_I) return 323; // "someone"
                    if (keycode == KC_J) return 317; // "subject"
                    if (keycode == KC_O) return 312; // "slowly"
                    if (keycode == KC_R) return 306; // "surprise"
                    if (keycode == KC_U) return 300; // "support"
                    if (keycode == KC_Y) return 295; // "system"
                    break;
                // r
                case -152:
                    if (keycode == KC_SPC) return 399; // "really"
                    if (keycode == KC_COMMA) return 395; // "route"
                    if (keycode == KC_DOT) return 391; // "error"
                    if (keycode == KC_A) return 385; // "program"
                    if (keycode == KC_E) return 380; // "ready"
                    if (keycode == KC_H) return 375; // "review"
                    if (keycode == KC_I) return 371; // "right"
                    if (keycode == KC_J) return 367; // "return"
                    if (keycode == KC_O) return 362; // "around"
                    if (keycode == KC_U) return 359; // "true"
                    if (keycode == KC_Y) return 355; // "years"
                    break;
                // q
                case -142:
                    if (keycode == KC_SPC) return 441; // "spring"
                    if (keycode == KC_A) return 436; // "starter"
                    if (keycode == KC_E) return 431; // "request"
                    if (keycode == KC_H) return 424; // "describe"
                    if (keycode == KC_I) return 420; // "issues"
                    if (keycode == KC_J) return 415; // "feature"
                    if (keycode == KC_O) return 411; // "blob"
                    if (keycode == KC_U) return 407; // "query"
                    if (keycode == KC_Y) return 403; // "tests"
                    break;
                // p
                case -129:
                    if (keycode == KC_SPC) return 505; // "people"
                    if (keycode == KC_COMMA) return 500; // "please"
                    if (keycode == KC_DOT) return 494; // "promise"
                    if (keycode == KC_A) return 488; // "privacy"
                    if (keycode == KC_E) return 484; // "place"
                    if (keycode == KC_H) return 480; // "http"
                    if (keycode == KC_I) return 476; // "point"
                    if (keycode == KC_J) return 470; // "problem"
                    if (keycode == KC_O) return 464; // "product"
                    if (keycode == KC_R) return 459; // "parent"
                    if (keycode == KC_U) return 453; // "public"
                    if (keycode == KC_Y) return 446; // "probably"
                    break;
                // n
                case -115:
                    if (keycode == KC_SPC) return 561; // "understand"
                    if (keycode == KC_COMMA) return 557; // "single"
                    if (keycode == KC_DOT) return 554; // "null"
                    if (keycode == KC_A) return 549; // "anyway"
                    if (keycode == KC_E) return 544; // "number"
                    if (keycode == KC_H) return 539; // "anything"
                    if (keycode == KC_I) return 536; // "into"
                    if (keycode == KC_J) return 531; // "instead"
                    if (keycode == KC_O) return 526; // "another"
                    if (keycode == KC_R) return 523; // "near"
                    if (keycode == KC_T) return 520; // "that"
                    if (keycode == KC_U) return 516; // "enough"
                    if (keycode == KC_Y) return 510; // "company"
                    break;
                // m
                case -104:
                    if (keycode == KC_SPC) return 609; // "more"
                    if (keycode == KC_COMMA) return 605; // "lgtm"
                    if (keycode == KC_DOT) return 600; // "method"
                    if (keycode == KC_A) return 596; // "some"
                    if (keycode == KC_E) return 591; // "message"
                    if (keycode == KC_H) return 587; // "might"
                    if (keycode == KC_I) return 582; // "minute"
                    if (keycode == KC_J) return 577; // "major"
                    if (keycode == KC_U) return 573; // "music"
                    if (keycode == KC_Y) return 568; // "myself"
                    break;
                // l
                case -89:
                    if (keycode == KC_SPC) return 664; // "like"
                    if (keycode == KC_COMMA) return 660; // "level"
                    if (keycode == KC_DOT) return 656; // "class"
                    if (keycode == KC_A) return 653; // "also"
                    if (keycode == KC_D) return 649; // "with"
                    if (keycode == KC_E) return 644; // "leave"
                    if (keycode == KC_F) return 641; // "for"
                    if (keycode == KC_H) return 637; // "health"
                    if (keycode == KC_I) return 633; // "light"
                    if (keycode == KC_J) return 629; // "large"
                    if (keycode == KC_O) return 625; // "along"
                    if (keycode == KC_R) return 621; // "later"
                    if (keycode == KC_U) return 616; // "almost"
                    if (keycode == KC_Y) return 613; // "only"
                    break;
                // k
                case -76:
                    if (keycode == KC_SPC) return 716; // "question"
                    if (keycode == KC_COMMA) return 711; // "config"
                    if (keycode == KC_DOT) return 708; // "key"
                    if (keycode == KC_A) return 703; // "make"
                    if (keycode == KC_E) return 699; // "keep"
                    if (keycode == KC_H) return 695; // "check"
                    if (keycode == KC_I) return 691; // "kind"
                    if (keycode == KC_J) return 686; // "java"
                    if (keycode == KC_O) return 682; // "know"
                    if (keycode == KC_R) return 678; // "work"
                    if (keycode == KC_U) return 674; // "caller"
                    if (keycode == KC_Y) return 668; // "quickly"
                    break;
                // j
                case -68:
                    if (keycode == KC_SPC) return 773; // "just"
                    if (keycode == KC_COMMA) return 733; // "Grafana"
                    if (keycode == KC_DOT) return 722; // "Grafana Labs"
                    if (keycode == KC_A) return 767; // "import"
                    if (keycode == KC_E) return 763; // "when"
                    if (keycode == KC_H) return 743; // "gregor.zeitlinger@grafana.com"
                    if (keycode == KC_O) return 739; // "other"
                    break;
                // g
                case -53:
                    if (keycode == KC_SPC) return 857; // "again"
                    if (keycode == KC_COMMA) return 813; // "Gregor"
                    if (keycode == KC_DOT) return 806; // "Zeitlinger"
                    if (keycode == KC_A) return 853; // "glance"
                    if (keycode == KC_E) return 849; // "began"
                    if (keycode == KC_H) return 845; // "rights"
                    if (keycode == KC_I) return 840; // "giving"
                    if (keycode == KC_J) return 835; // "general"
                    if (keycode == KC_O) return 831; // "group"
                    if (keycode == KC_R) return 827; // "great"
                    if (keycode == KC_U) return 823; // "guess"
                    if (keycode == KC_X) return 791; // "zeitlinger@gmail.com"
                    if (keycode == KC_Y) return 818; // "every"
                    if (keycode == KC_Z) return 777; // "gregor@zeitlinger.de"
                    break;
                // f
                case -39:
                    if (keycode == KC_SPC) return 918; // "from"
                    if (keycode == KC_COMMA) return 914; // "fails"
                    if (keycode == KC_DOT) return 910; // "false"
                    if (keycode == KC_A) return 905; // "after"
                    if (keycode == KC_E) return 901; // "feel"
                    if (keycode == KC_H) return 898; // "then"
                    if (keycode == KC_I) return 894; // "first"
                    if (keycode == KC_J) return 889; // "finger"
                    if (keycode == KC_L) return 885; // "have"
                    if (keycode == KC_O) return 877; // "information"
                    if (keycode == KC_R) return 870; // "software"
                    if (keycode == KC_U) return 865; // "found"
                    if (keycode == KC_Y) return 861; // "forty"
                    break;
                // d
                case -28:
                    if (keycode == KC_SPC) return 965; // "didn't"
                    if (keycode == KC_COMMA) return 959; // "hadn't"
                    if (keycode == KC_DOT) return 955; // "data"
                    if (keycode == KC_E) return 951; // "them"
                    if (keycode == KC_H) return 948; // "than"
                    if (keycode == KC_I) return 943; // "during"
                    if (keycode == KC_J) return 938; // "build"
                    if (keycode == KC_R) return 934; // "their"
                    if (keycode == KC_U) return 928; // "products"
                    if (keycode == KC_Y) return 922; // "already"
                    break;
                // c
                case -13:
                    if (keycode == KC_SPC) return 1035; // "could"
                    if (keycode == KC_COMMA) return 1028; // "couldn't"
                    if (keycode == KC_DOT) return 1024; // "const"
                    if (keycode == KC_A) return 1019; // "actually"
                    if (keycode == KC_E) return 1013; // "service"
                    if (keycode == KC_H) return 1008; // "research"
                    if (keycode == KC_I) return 1004; // "click"
                    if (keycode == KC_J) return 998; // "project"
                    if (keycode == KC_N) return 994; // "been"
                    if (keycode == KC_O) return 989; // "continue"
                    if (keycode == KC_R) return 985; // "across"
                    if (keycode == KC_S) return 982; // "this"
                    if (keycode == KC_U) return 977; // "current"
                    if (keycode == KC_Y) return 972; // "policy"
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return 1092; // "about"
                    if (keycode == KC_COMMA) return 1081; // "observability"
                    if (keycode == KC_DOT) return 1076; // "boolean"
                    if (keycode == KC_H) return 1071; // "behind"
                    if (keycode == KC_I) return 1067; // "being"
                    if (keycode == KC_J) return 1061; // "between"
                    if (keycode == KC_O) return 1055; // "become"
                    if (keycode == KC_R) return 1050; // "break"
                    if (keycode == KC_U) return 1044; // "business"
                    if (keycode == KC_Y) return 1039; // "body"
                    break;
                case -1:
                    if (keycode == KC_B) return -2; // b...
                    if (keycode == KC_C) return -13; // c...
                    if (keycode == KC_D) return -28; // d...
                    if (keycode == KC_F) return -39; // f...
                    if (keycode == KC_G) return -53; // g...
                    if (keycode == KC_J) return -68; // j...
                    if (keycode == KC_K) return -76; // k...
                    if (keycode == KC_L) return -89; // l...
                    if (keycode == KC_M) return -104; // m...
                    if (keycode == KC_N) return -115; // n...
                    if (keycode == KC_P) return -129; // p...
                    if (keycode == KC_Q) return -142; // q...
                    if (keycode == KC_R) return -152; // r...
                    if (keycode == KC_S) return -164; // s...
                    if (keycode == KC_T) return -177; // t...
                    if (keycode == KC_V) return -189; // v...
                    if (keycode == KC_W) return -202; // w...
                    if (keycode == KC_X) return -214; // x...
                    if (keycode == KC_Z) return -227; // z...
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
                    case KC_COMMA: chord_decode_send(1156); return false; // " but "
                    case KC_D: chord_decode_send(1101); return false; // "oesn't"
                    case KC_DOT: tap_code16(KC_SLASH); return false;
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_ENT: chord_decode_send(1148); return false; // "the "
                    case KC_EQUAL: tap_code16(KC_RABK); return false;
                    case KC_EXLM: tap_code16(KC_EQUAL); return false;
                    case KC_F: tap_code16(KC_F); return false;
                    case KC_G: tap_code16(KC_N); return false;
                    case KC_H: tap_code16(KC_Y); return false;
                    case KC_I: tap_code16(KC_QUOTE); return false;
                    case KC_J: chord_decode_send(1121); return false; // "ust"
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_P); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_MINUS: tap_code16(KC_RABK); return false;
                    case KC_N: tap_code16(KC_G); return false;
                    case KC_O: tap_code16(KC_E); return false;
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_R: tap_code16(KC_K); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: chord_decode_send(1148); return false; // "the "
                    case KC_T: chord_decode_send(1132); return false; // "ion"
                    case KC_TAB: chord_decode_send(1148); return false; // "the "
                    case KC_TILD: tap_code16(KC_SLASH); return false;
                    case KC_V: chord_decode_send(1138); return false; // "er"
                    case KC_W: tap_code16(KC_N); return false;
                    case KC_X: tap_code16(KC_P); return false;
                    case KC_Z: chord_decode_send(1142); return false; // "eitlinger"
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): chord_decode_send(1101); return false; // "oesn't"
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_F): tap_code16(KC_F); return false;
                    case S(KC_G): tap_code16(KC_N); return false;
                    case S(KC_H): tap_code16(KC_Y); return false;
                    case S(KC_I): tap_code16(KC_QUOTE); return false;
                    case S(KC_J): chord_decode_send(1121); return false; // "ust"
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_P); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): tap_code16(KC_G); return false;
                    case S(KC_O): tap_code16(KC_E); return false;
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_R): tap_code16(KC_K); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): chord_decode_send(1132); return false; // "ion"
                    case S(KC_V): chord_decode_send(1138); return false; // "er"
                    case S(KC_W): tap_code16(KC_N); return false;
                    case S(KC_X): tap_code16(KC_P); return false;
                    case S(KC_Z): chord_decode_send(1142); return false; // "eitlinger"
                }
                return false;
            case MAGIC_B:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_U); return false;
                    case KC_B: chord_decode_send(1097); return false; // "ecause"
                    case KC_C: tap_code16(KC_P); return false;
                    case KC_COMMA: chord_decode_send(1161); return false; // " and "
                    case KC_D: chord_decode_send(1106); return false; // "oes"
                    case KC_DOT: chord_decode_send(1166); return false; // "./"
                    case KC_ENT: chord_decode_send(1152); return false; // "and "
                    case KC_F: chord_decode_send(1113); return false; // "or"
                    case KC_G: tap_code16(KC_K); return false;
                    case KC_H: chord_decode_send(1115); return false; // "ey"
                    case KC_I: chord_decode_send(1117); return false; // "'ve"
                    case KC_K: chord_decode_send(1124); return false; // "now"
                    case KC_L: tap_code16(KC_M); return false;
                    case KC_M: chord_decode_send(1127); return false; // "ent"
                    case KC_N: tap_code16(KC_K); return false;
                    case KC_P: tap_code16(KC_S); return false;
                    case KC_S: chord_decode_send(1132); return false; // "ion"
                    case KC_SPC: tap_code16(KC_BSPC); SEND_STRING(". "); add_oneshot_mods(MOD_BIT(KC_LSFT)); return false;
                    case KC_T: chord_decode_send(1135); return false; // "ing"
                    case KC_TAB: chord_decode_send(1152); return false; // "and "
                    case KC_U: tap_code16(KC_A); return false;
                    case KC_V: chord_decode_send(1140); return false; // "en"
                    case KC_W: tap_code16(KC_S); return false;
                    case KC_X: tap_code16(KC_C); return false;
                    case S(KC_A): tap_code16(KC_U); return false;
                    case S(KC_B): chord_decode_send(1097); return false; // "ecause"
                    case S(KC_C): tap_code16(KC_P); return false;
                    case S(KC_D): chord_decode_send(1106); return false; // "oes"
                    case S(KC_F): chord_decode_send(1113); return false; // "or"
                    case S(KC_G): tap_code16(KC_K); return false;
                    case S(KC_H): chord_decode_send(1115); return false; // "ey"
                    case S(KC_I): chord_decode_send(1117); return false; // "'ve"
                    case S(KC_K): chord_decode_send(1124); return false; // "now"
                    case S(KC_L): tap_code16(KC_M); return false;
                    case S(KC_M): chord_decode_send(1127); return false; // "ent"
                    case S(KC_N): tap_code16(KC_K); return false;
                    case S(KC_P): tap_code16(KC_S); return false;
                    case S(KC_S): chord_decode_send(1132); return false; // "ion"
                    case S(KC_T): chord_decode_send(1135); return false; // "ing"
                    case S(KC_U): tap_code16(KC_A); return false;
                    case S(KC_V): chord_decode_send(1140); return false; // "en"
                    case S(KC_W): tap_code16(KC_S); return false;
                    case S(KC_X): tap_code16(KC_C); return false;
                }
                return false;
            case MAGIC_C:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_U); return false;
                    case KC_B: tap_code16(KC_L); return false;
                    case KC_C: tap_code16(KC_K); return false;
                    case KC_D: chord_decode_send(1109); return false; // "on't"
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_G: tap_code16(KC_L); return false;
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_V); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_N: chord_decode_send(1130); return false; // "ly"
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: chord_decode_send(1148); return false; // "the "
                    case KC_T: chord_decode_send(1132); return false; // "ion"
                    case S(KC_A): tap_code16(KC_U); return false;
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): chord_decode_send(1109); return false; // "on't"
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_G): tap_code16(KC_L); return false;
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_V); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): chord_decode_send(1130); return false; // "ly"
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): chord_decode_send(1132); return false; // "ion"
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
