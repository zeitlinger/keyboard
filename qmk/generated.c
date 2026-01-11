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
    'e', 't', 'r', 'a', 'n', 'o', 'i', 'l', 's', 'g', 'u', 'h', 'c', 'y'
};

// 8-bit codes (0xE0+) for less common characters
static const char chord_char_extended[] = {
    'm', 'p', 'd', 'b', 'v', 'w', 'f', 'k', ' ', '\'', 'x', '.', 'z', 'j', 'G', 'q', '@', 'S', 'O', 'T', 'Z', 'H', 'L', 'B', '/'
};

// Global buffer containing all 4/8-bit variable-length encoded chord strings
static const uint8_t chord_data[] = {
    0x0b, 0xf1, 0xe1, 0x26, 0x49, 0xe8, 0xf7, 0x55, 0x10, 0x0c, 0xee, 0x23, 0xe6, 0x34, 0x30, 0xe8,
    0xf6, 0x30, 0xe3, 0x80, 0x09, 0xed, 0x30, 0xe4, 0x33, 0x90, 0x41, 0x06, 0x80, 0xe1, 0x26, 0x49,
    0x0e, 0xf1, 0xe1, 0x26, 0x49, 0xe8, 0x81, 0x32, 0x10, 0x20, 0x06, 0xee, 0x61, 0xf5, 0xa0, 0xe3,
    0x08, 0x52, 0x93, 0x46, 0xec, 0x00, 0x05, 0x38, 0xd4, 0xc0, 0x05, 0x80, 0xe0, 0x67, 0x00, 0x0a,
    0xf4, 0x06, 0x17, 0x64, 0x90, 0x20, 0x09, 0x10, 0x70, 0xe0, 0x01, 0x2d, 0x06, 0x3c, 0x1a, 0x37,
    0x08, 0x20, 0x85, 0xa2, 0xc0, 0x0d, 0xf2, 0xe1, 0x04, 0xf3, 0x07, 0x00, 0xe0, 0x01, 0x2d, 0x09,
    0x00, 0xea, 0xc0, 0xe1, 0x16, 0x54, 0x08, 0x00, 0xea, 0x68, 0x16, 0x49, 0x05, 0xb1, 0x10, 0xe1,
    0x80, 0x07, 0x00, 0xea, 0x0c, 0xa1, 0x00, 0x07, 0x00, 0xea, 0x30, 0xe0, 0xe1, 0x70, 0x06, 0x00,
    0xea, 0xe1, 0x52, 0x10, 0x12, 0xe2, 0x0c, 0x73, 0x23, 0x16, 0xe4, 0x00, 0xe8, 0xc5, 0x40, 0xe6,
    0x69, 0x07, 0xc5, 0x41, 0x00, 0xea, 0x10, 0x05, 0xe5, 0x52, 0x2d, 0x08, 0x64, 0x10, 0x24, 0x37,
    0x05, 0xe5, 0xb0, 0x20, 0x07, 0xe5, 0x61, 0xb5, 0xa1, 0x05, 0xe5, 0x25, 0x49, 0x04, 0xe5, 0x67,
    0x70, 0x05, 0xe5, 0xb6, 0xcb, 0x04, 0xe5, 0xb0, 0x40, 0x04, 0xe5, 0x37, 0xe7, 0x05, 0x30, 0xe5,
    0x36, 0x10, 0x08, 0xe5, 0x5a, 0x70, 0xe2, 0x40, 0xe9, 0x10, 0x05, 0xe5, 0x5a, 0x70, 0xe2, 0x0a,
    0x00, 0xe4, 0x02, 0xd1, 0xb6, 0x49, 0x05, 0xe4, 0x37, 0xa0, 0x05, 0x40, 0xe4, 0x02, 0x04, 0x50,
    0xe4, 0x02, 0x06, 0x45, 0x16, 0xc0, 0x08, 0x80, 0x20, 0xe4, 0x6c, 0x08, 0x07, 0xe4, 0x02, 0x86,
    0x54, 0x04, 0xe4, 0x02, 0xd0, 0x09, 0x30, 0xe4, 0x36, 0x73, 0xe3, 0x70, 0x04, 0xe4, 0x56, 0xe2,
    0x07, 0xc5, 0x41, 0x26, 0xe3, 0x04, 0x00, 0xe4, 0x04, 0x09, 0x1b, 0x34, 0xe7, 0xe8, 0xd5, 0xa0,
    0x06, 0x1b, 0x5a, 0x9b, 0x14, 0x92, 0x09, 0x52, 0xf0, 0xec, 0x06, 0x17, 0x64, 0x90, 0x20, 0xeb,
    0xe2, 0x00, 0x05, 0x1b, 0x02, 0x00, 0x07, 0x1b, 0x5a, 0x9b, 0x10, 0x07, 0x1b, 0x25, 0xa9, 0xb0,
    0x04, 0x16, 0xe0, 0x00, 0x05, 0x51, 0xb0, 0x20, 0x05, 0x1b, 0x08, 0x00, 0x05, 0x15, 0xe2, 0x3d,
    0x04, 0x1d, 0xe1, 0x00, 0x06, 0x10, 0x43, 0x41, 0x05, 0x1b, 0x64, 0xe7, 0x06, 0x8d, 0x81, 0x00,
    0xe0, 0x07, 0x8a, 0xe1, 0xe1, 0x52, 0x10, 0x08, 0x8a, 0x20, 0xe1, 0x26, 0x80, 0x06, 0x87, 0x50,
    0xe5, 0x7d, 0x07, 0x8a, 0xe3, 0xed, 0x0c, 0x10, 0x07, 0x85, 0xe0, 0x05, 0x40, 0x05, 0x8b, 0x32,
    0x00, 0x06, 0x80, 0x32, 0xcb, 0x04, 0x1b, 0x68, 0x04, 0x83, 0xe0, 0x00, 0x06, 0x81, 0x26, 0x49,
    0x06, 0xe5, 0x38, 0x40, 0xe9, 0x10, 0x06, 0x8b, 0x5a, 0x70, 0xe2, 0x07, 0x20, 0x37, 0x60, 0xec,
    0x00, 0x05, 0xd0, 0x32, 0x80, 0x04, 0x12, 0xa0, 0x04, 0x1b, 0x0d, 0x07, 0x20, 0xef, 0xa0, 0x81,
    0x06, 0x32, 0x5a, 0x40, 0xe2, 0x05, 0xef, 0xa0, 0x2d, 0x06, 0x20, 0x1a, 0x24, 0x05, 0x26, 0x9b,
    0x10, 0x06, 0x20, 0xe4, 0x60, 0xe5, 0x06, 0x26, 0x9b, 0x18, 0x05, 0x20, 0x30, 0xe2, 0xd0, 0x07,
    0xe1, 0x25, 0x92, 0x30, 0xe0, 0x05, 0x02, 0x25, 0x20, 0x05, 0x25, 0xa1, 0x00, 0x06, 0x20, 0x37,
    0x7d, 0x08, 0xe1, 0x25, 0xe3, 0x30, 0xe3, 0x7d, 0x06, 0xe1, 0xa0, 0xe3, 0x76, 0xc0, 0x06, 0xe1,
    0x32, 0x04, 0x10, 0x07, 0xe1, 0x25, 0xe2, 0xac, 0x10, 0x07, 0xe1, 0x25, 0xe3, 0x70, 0xe0, 0x05,
    0xe1, 0x56, 0x41, 0x04, 0xb1, 0x10, 0xe1, 0x05, 0xe1, 0x73, 0xc0, 0x07, 0xe1, 0x26, 0xe4, 0x3c,
    0xd0, 0x07, 0xe1, 0x25, 0xe0, 0x68, 0x00, 0x06, 0xe1, 0x70, 0x38, 0x00, 0x06, 0xe1, 0x05, 0xe1,
    0x70, 0x07, 0xc5, 0xe0, 0xe1, 0x34, 0xd0, 0x06, 0x04, 0x5a, 0x9b, 0x04, 0x1b, 0x31, 0x04, 0x40,
    0x32, 0x07, 0x34, 0x51, 0xb0, 0x20, 0x14, 0xec, 0x06, 0x17, 0x64, 0x90, 0x20, 0xf0, 0x90, 0xe0,
    0x36, 0x70, 0xeb, 0xc5, 0xe0, 0x06, 0x68, 0x8a, 0x08, 0x04, 0x64, 0x15, 0x08, 0x34, 0xd1, 0xb6,
    0x49, 0x06, 0x4a, 0xe0, 0xe3, 0x02, 0x07, 0x64, 0x81, 0x03, 0xe2, 0x06, 0x34, 0xd0, 0xe5, 0x3d,
    0x04, 0x4a, 0x77, 0x06, 0x86, 0x49, 0x70, 0x0a, 0xa4, 0xe2, 0x02, 0x81, 0x34, 0xe2, 0x06, 0xe0,
    0xd8, 0x07, 0xe6, 0x05, 0xe0, 0xa8, 0x6c, 0x07, 0xe6, 0x03, 0x1a, 0x20, 0x05, 0xe0, 0x30, 0xed,
    0x52, 0x06, 0xe0, 0x64, 0xa1, 0x00, 0x05, 0xe0, 0x69, 0xb1, 0x07, 0xe0, 0x08, 0x83, 0x90, 0x04,
    0x85, 0xe0, 0x00, 0x06, 0xe0, 0x01, 0xb5, 0xe2, 0x04, 0x79, 0x10, 0xe0, 0x04, 0xe0, 0x52, 0x00,
    0x04, 0x54, 0x7d, 0x06, 0x37, 0xe0, 0x58, 0x10, 0x05, 0x73, 0x10, 0x20, 0x05, 0x37, 0x54, 0x90,
    0x05, 0x73, 0x29, 0x00, 0x05, 0x76, 0x9b, 0x10, 0x06, 0xb0, 0x37, 0x1b, 0x05, 0x70, 0x30, 0xe4,
    0x00, 0x04, 0xe5, 0x61, 0xb0, 0x04, 0x37, 0x85, 0x05, 0xc7, 0x38, 0x80, 0x05, 0x70, 0xe4, 0x07,
    0x04, 0x76, 0xe7, 0x00, 0x07, 0xef, 0xa6, 0xc0, 0xe7, 0x7d, 0x06, 0xc3, 0x77, 0x02, 0x04, 0xe5,
    0x52, 0xe7, 0x04, 0xe7, 0x45, 0xe5, 0x04, 0xed, 0x30, 0xe4, 0x30, 0x04, 0xe7, 0x64, 0xe2, 0x05,
    0xcb, 0x0c, 0xe7, 0x04, 0xe7, 0x00, 0xe1, 0x04, 0xe0, 0x30, 0xe7, 0x00, 0x03, 0xe7, 0x0d, 0x06,
    0xc5, 0x40, 0xe6, 0x69, 0x08, 0xef, 0xa0, 0x81, 0x65, 0x40, 0x05, 0x00, 0xe4, 0x02, 0xd0, 0x05,
    0x9a, 0x08, 0x80, 0x05, 0x92, 0x03, 0x10, 0x05, 0x92, 0x5a, 0xe1, 0x07, 0x90, 0x40, 0x23, 0x70,
    0x06, 0x96, 0xe4, 0x64, 0x90, 0x05, 0xe3, 0x09, 0x34, 0x06, 0x97, 0x34, 0xc0, 0x07, 0xee, 0x23,
    0xe6, 0x34, 0x30, 0x06, 0xee, 0x20, 0x95, 0x20, 0x05, 0x39, 0x36, 0x40, 0x05, 0xe6, 0x52, 0x1d,
    0x05, 0xe6, 0x5a, 0x40, 0xe2, 0x08, 0x85, 0xe6, 0x10, 0xe5, 0x32, 0x00, 0x0b, 0x64, 0xe6, 0x52,
    0xe0, 0x31, 0x65, 0x40, 0x04, 0xb3, 0xe4, 0x00, 0x06, 0xe6, 0x64, 0x90, 0x20, 0x05, 0xe6, 0x62,
    0x81, 0x04, 0x1b, 0x04, 0x04, 0xe6, 0x00, 0x70, 0x05, 0x30, 0xe6, 0x10, 0x20, 0x05, 0xe6, 0x37,
    0x80, 0x05, 0xe6, 0x36, 0x78, 0x04, 0xe6, 0x25, 0xe0, 0x07, 0x37, 0x20, 0x30, 0xe2, 0xd0, 0x08,
    0xe1, 0x25, 0xe2, 0xac, 0x18, 0x05, 0x1b, 0x06, 0x20, 0x06, 0x60, 0xe0, 0xe1, 0x52, 0x10, 0x05,
    0xe3, 0xa6, 0x70, 0xe2, 0x06, 0xe2, 0xa2, 0x64, 0x90, 0x04, 0x1b, 0x34, 0x04, 0x1b, 0x00, 0xe0,
    0x08, 0xe2, 0x08, 0xc2, 0x60, 0xe3, 0x00, 0x04, 0xe2, 0x31, 0x30, 0x06, 0xb3, 0xe2, 0x40, 0xe9,
    0x10, 0x06, 0xe2, 0x60, 0xe2, 0x40, 0xe9, 0x10, 0x06, 0xe1, 0x57, 0x6c, 0xd0, 0x07, 0xca, 0x22,
    0x04, 0x10, 0x06, 0x3c, 0x25, 0x88, 0x08, 0xc5, 0x41, 0x64, 0xa0, 0x04, 0xe3, 0x00, 0x40, 0x07,
    0xe1, 0x25, 0xed, 0x0c, 0x10, 0x05, 0xc7, 0x6c, 0xe7, 0x08, 0x20, 0x80, 0x32, 0xcb, 0x07, 0x80,
    0x20, 0xe4, 0x6c, 0x00, 0x1d, 0x92, 0x09, 0x52, 0xeb, 0xec, 0x06, 0x17, 0x64, 0x90, 0x20, 0xf0,
    0x92, 0x30, 0xe6, 0x34, 0x30, 0xeb, 0xc5, 0xe0, 0x08, 0x3c, 0x1a, 0x37, 0x7d, 0x05, 0xc5, 0x48,
    0x10, 0x08, 0xc5, 0xa7, 0xe2, 0x40, 0xe9, 0x10, 0x05, 0xc5, 0xa7, 0xe2, 0x04, 0xe3, 0x50, 0xe2,
    0xd0, 0x08, 0xe3, 0xa8, 0x64, 0x08, 0x80, 0x05, 0xe3, 0x20, 0x30, 0xe7, 0x06, 0xe3, 0x0c, 0x50,
    0xe0, 0x00, 0x07, 0xe3, 0x01, 0xe5, 0x00, 0x40, 0x05, 0xe3, 0x06, 0x49, 0x06, 0xe3, 0x0b, 0x64,
    0xe2, 0x07, 0xe3, 0x55, 0x70, 0x34, 0x0d, 0x50, 0xe3, 0x80, 0x20, 0xe4, 0x30, 0xe3, 0x67, 0x61,
    0xd0, 0x05, 0x30, 0xe3, 0x5a, 0x10, 0x06, 0x0c, 0x3a, 0x80, 0x06, 0x50, 0x84, 0xe9, 0x10, 0x03,
    0x50, 0x80, 0x04, 0x54, 0xe9, 0x10, 0x02, 0x52, 0x02, 0x0d, 0x03, 0xe9, 0xe4, 0x00, 0x03, 0xa8,
    0x10, 0x03, 0x45, 0xe5, 0x03, 0x04, 0x10, 0x02, 0x7d, 0x03, 0x65, 0x40, 0x03, 0x64, 0x90, 0x02,
    0x02, 0x02, 0x04, 0x09, 0x06, 0x17, 0x64, 0x90, 0x20, 0x04, 0x1b, 0x00, 0xe8, 0x04, 0x34, 0xe2,
    0xe8, 0x05, 0xe8, 0xe3, 0xa1, 0xe8, 0x05, 0xe8, 0x34, 0xe2, 0xe8, 0x02, 0xeb, 0xf8
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
                case -219:
                    if (keycode == KC_SPC) return 63; // "Zeitlinger"
                    if (keycode == KC_COMMA) return 58; // "smile"
                    if (keycode == KC_DOT) return 54; // "async"
                    if (keycode == KC_A) return 48; // "organize"
                    if (keycode == KC_E) return 42; // "GitHub"
                    if (keycode == KC_H) return 32; // "Spring starter"
                    if (keycode == KC_I) return 27; // "spring"
                    if (keycode == KC_J) return 20; // "javaagent"
                    if (keycode == KC_O) return 9; // "Grafana Labs"
                    if (keycode == KC_U) return 0; // "Spring Boot"
                    break;
                // x
                case -206:
                    if (keycode == KC_SPC) return 145; // "context"
                    if (keycode == KC_COMMA) return 132; // "declarative config"
                    if (keycode == KC_DOT) return 126; // "export"
                    if (keycode == KC_A) return 119; // "example"
                    if (keycode == KC_E) return 113; // "execute"
                    if (keycode == KC_H) return 108; // "https"
                    if (keycode == KC_I) return 102; // "existing"
                    if (keycode == KC_J) return 95; // "exception"
                    if (keycode == KC_O) return 85; // "OpenTelemetry"
                    if (keycode == KC_R) return 80; // "resource"
                    if (keycode == KC_U) return 76; // "actual"
                    if (keycode == KC_Y) return 70; // "telemetry"
                    break;
                // w
                case -193:
                    if (keycode == KC_SPC) return 202; // "would"
                    if (keycode == KC_COMMA) return 194; // "wouldn't"
                    if (keycode == KC_DOT) return 189; // "await"
                    if (keycode == KC_A) return 185; // "walk"
                    if (keycode == KC_E) return 181; // "when"
                    if (keycode == KC_H) return 177; // "which"
                    if (keycode == KC_I) return 173; // "will"
                    if (keycode == KC_J) return 169; // "wrong"
                    if (keycode == KC_O) return 164; // "without"
                    if (keycode == KC_R) return 160; // "where"
                    if (keycode == KC_U) return 155; // "internal"
                    if (keycode == KC_Y) return 151; // "worry"
                    break;
                // v
                case -180:
                    if (keycode == KC_SPC) return 261; // "even"
                    if (keycode == KC_COMMA) return 256; // "contrib"
                    if (keycode == KC_DOT) return 252; // "void"
                    if (keycode == KC_A) return 245; // "available"
                    if (keycode == KC_E) return 241; // "very"
                    if (keycode == KC_H) return 236; // "version"
                    if (keycode == KC_I) return 230; // "services"
                    if (keycode == KC_J) return 226; // "notice"
                    if (keycode == KC_O) return 222; // "over"
                    if (keycode == KC_R) return 218; // "never"
                    if (keycode == KC_U) return 214; // "value"
                    if (keycode == KC_Y) return 207; // "everything"
                    break;
                // t
                case -166:
                    if (keycode == KC_SPC) return 328; // "think"
                    if (keycode == KC_COMMA) return 324; // "tenant"
                    if (keycode == KC_DOT) return 320; // "type"
                    if (keycode == KC_A) return 316; // "today"
                    if (keycode == KC_E) return 312; // "these"
                    if (keycode == KC_H) return 308; // "other"
                    if (keycode == KC_I) return 304; // "time"
                    if (keycode == KC_J) return 299; // "through"
                    if (keycode == KC_O) return 294; // "thought"
                    if (keycode == KC_R) return 290; // "there"
                    if (keycode == KC_T) return 276; // "gregor@zeitlinger.de"
                    if (keycode == KC_U) return 272; // "though"
                    if (keycode == KC_Y) return 265; // "thank you"
                    break;
                // s
                case -152:
                    if (keycode == KC_SPC) return 390; // "should"
                    if (keycode == KC_COMMA) return 384; // "wasn't"
                    if (keycode == KC_DOT) return 380; // "string"
                    if (keycode == KC_A) return 376; // "same"
                    if (keycode == KC_C) return 373; // "this"
                    if (keycode == KC_E) return 369; // "search"
                    if (keycode == KC_H) return 365; // "share"
                    if (keycode == KC_I) return 360; // "someone"
                    if (keycode == KC_J) return 354; // "subject"
                    if (keycode == KC_O) return 349; // "slowly"
                    if (keycode == KC_R) return 343; // "surprise"
                    if (keycode == KC_U) return 337; // "support"
                    if (keycode == KC_Y) return 332; // "system"
                    break;
                // r
                case -135:
                    if (keycode == KC_SPC) return 461; // "really"
                    if (keycode == KC_COMMA) return 457; // "route"
                    if (keycode == KC_DOT) return 453; // "error"
                    if (keycode == KC_A) return 447; // "program"
                    if (keycode == KC_E) return 442; // "ready"
                    if (keycode == KC_G) return 438; // "rights"
                    if (keycode == KC_H) return 433; // "review"
                    if (keycode == KC_I) return 429; // "right"
                    if (keycode == KC_J) return 425; // "return"
                    if (keycode == KC_L) return 421; // "query"
                    if (keycode == KC_O) return 416; // "around"
                    if (keycode == KC_S) return 411; // "request"
                    if (keycode == KC_T) return 408; // "they"
                    if (keycode == KC_U) return 405; // "true"
                    if (keycode == KC_Y) return 401; // "years"
                    if (keycode == KC_Z) return 395; // "realize"
                    break;
                // p
                case -122:
                    if (keycode == KC_SPC) return 524; // "people"
                    if (keycode == KC_COMMA) return 519; // "please"
                    if (keycode == KC_DOT) return 513; // "promise"
                    if (keycode == KC_A) return 507; // "privacy"
                    if (keycode == KC_E) return 503; // "place"
                    if (keycode == KC_H) return 499; // "http"
                    if (keycode == KC_I) return 495; // "point"
                    if (keycode == KC_J) return 489; // "problem"
                    if (keycode == KC_O) return 483; // "product"
                    if (keycode == KC_R) return 478; // "parent"
                    if (keycode == KC_U) return 472; // "public"
                    if (keycode == KC_Y) return 465; // "probably"
                    break;
                // n
                case -106:
                    if (keycode == KC_SPC) return 599; // "understand"
                    if (keycode == KC_COMMA) return 595; // "single"
                    if (keycode == KC_DOT) return 592; // "null"
                    if (keycode == KC_A) return 587; // "anyway"
                    if (keycode == KC_D) return 582; // "instead"
                    if (keycode == KC_E) return 577; // "number"
                    if (keycode == KC_H) return 572; // "anything"
                    if (keycode == KC_I) return 569; // "into"
                    if (keycode == KC_J) return 565; // "issues"
                    if (keycode == KC_N) return 550; // "zeitlinger@gmail.com"
                    if (keycode == KC_O) return 545; // "another"
                    if (keycode == KC_R) return 542; // "near"
                    if (keycode == KC_T) return 539; // "that"
                    if (keycode == KC_U) return 535; // "enough"
                    if (keycode == KC_Y) return 529; // "company"
                    break;
                // m
                case -94:
                    if (keycode == KC_SPC) return 652; // "more"
                    if (keycode == KC_COMMA) return 648; // "lgtm"
                    if (keycode == KC_DOT) return 643; // "method"
                    if (keycode == KC_A) return 639; // "some"
                    if (keycode == KC_E) return 634; // "message"
                    if (keycode == KC_H) return 630; // "might"
                    if (keycode == KC_I) return 625; // "minute"
                    if (keycode == KC_J) return 620; // "major"
                    if (keycode == KC_O) return 615; // "feature"
                    if (keycode == KC_U) return 611; // "music"
                    if (keycode == KC_Y) return 606; // "myself"
                    break;
                // l
                case -80:
                    if (keycode == KC_SPC) return 704; // "like"
                    if (keycode == KC_COMMA) return 700; // "level"
                    if (keycode == KC_DOT) return 696; // "class"
                    if (keycode == KC_A) return 693; // "also"
                    if (keycode == KC_D) return 689; // "with"
                    if (keycode == KC_E) return 684; // "leave"
                    if (keycode == KC_H) return 680; // "health"
                    if (keycode == KC_I) return 676; // "light"
                    if (keycode == KC_J) return 672; // "large"
                    if (keycode == KC_O) return 668; // "along"
                    if (keycode == KC_R) return 664; // "later"
                    if (keycode == KC_U) return 659; // "almost"
                    if (keycode == KC_Y) return 656; // "only"
                    break;
                // k
                case -67:
                    if (keycode == KC_SPC) return 756; // "question"
                    if (keycode == KC_COMMA) return 751; // "config"
                    if (keycode == KC_DOT) return 748; // "key"
                    if (keycode == KC_A) return 743; // "make"
                    if (keycode == KC_E) return 739; // "keep"
                    if (keycode == KC_H) return 735; // "check"
                    if (keycode == KC_I) return 731; // "kind"
                    if (keycode == KC_J) return 726; // "java"
                    if (keycode == KC_O) return 722; // "know"
                    if (keycode == KC_R) return 718; // "work"
                    if (keycode == KC_U) return 714; // "caller"
                    if (keycode == KC_Y) return 708; // "quickly"
                    break;
                // g
                case -55:
                    if (keycode == KC_SPC) return 808; // "again"
                    if (keycode == KC_COMMA) return 803; // "Gregor"
                    if (keycode == KC_DOT) return 797; // "Grafana"
                    if (keycode == KC_A) return 793; // "glance"
                    if (keycode == KC_E) return 789; // "began"
                    if (keycode == KC_I) return 784; // "giving"
                    if (keycode == KC_J) return 779; // "general"
                    if (keycode == KC_O) return 775; // "group"
                    if (keycode == KC_R) return 771; // "great"
                    if (keycode == KC_U) return 767; // "guess"
                    if (keycode == KC_Y) return 762; // "every"
                    break;
                // f
                case -41:
                    if (keycode == KC_SPC) return 869; // "from"
                    if (keycode == KC_COMMA) return 865; // "fails"
                    if (keycode == KC_DOT) return 861; // "false"
                    if (keycode == KC_A) return 856; // "after"
                    if (keycode == KC_E) return 852; // "feel"
                    if (keycode == KC_H) return 849; // "then"
                    if (keycode == KC_I) return 845; // "first"
                    if (keycode == KC_J) return 840; // "finger"
                    if (keycode == KC_L) return 836; // "have"
                    if (keycode == KC_O) return 828; // "information"
                    if (keycode == KC_R) return 821; // "software"
                    if (keycode == KC_U) return 816; // "found"
                    if (keycode == KC_Y) return 812; // "forty"
                    break;
                // d
                case -28:
                    if (keycode == KC_SPC) return 929; // "didn't"
                    if (keycode == KC_COMMA) return 923; // "hadn't"
                    if (keycode == KC_DOT) return 919; // "data"
                    if (keycode == KC_A) return 912; // "describe"
                    if (keycode == KC_E) return 908; // "them"
                    if (keycode == KC_H) return 905; // "than"
                    if (keycode == KC_I) return 900; // "during"
                    if (keycode == KC_J) return 895; // "build"
                    if (keycode == KC_O) return 889; // "import"
                    if (keycode == KC_R) return 885; // "their"
                    if (keycode == KC_U) return 879; // "products"
                    if (keycode == KC_Y) return 873; // "already"
                    break;
                // c
                case -13:
                    if (keycode == KC_SPC) return 1016; // "could"
                    if (keycode == KC_COMMA) return 1009; // "couldn't"
                    if (keycode == KC_DOT) return 1005; // "const"
                    if (keycode == KC_A) return 1000; // "actually"
                    if (keycode == KC_C) return 980; // "gregor.zeitlinger@grafana.com"
                    if (keycode == KC_E) return 974; // "service"
                    if (keycode == KC_H) return 969; // "research"
                    if (keycode == KC_I) return 965; // "click"
                    if (keycode == KC_J) return 959; // "project"
                    if (keycode == KC_N) return 955; // "been"
                    if (keycode == KC_O) return 950; // "continue"
                    if (keycode == KC_R) return 946; // "across"
                    if (keycode == KC_U) return 941; // "current"
                    if (keycode == KC_Y) return 936; // "policy"
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return 1073; // "about"
                    if (keycode == KC_COMMA) return 1062; // "observability"
                    if (keycode == KC_DOT) return 1057; // "boolean"
                    if (keycode == KC_H) return 1052; // "behind"
                    if (keycode == KC_I) return 1048; // "being"
                    if (keycode == KC_J) return 1042; // "between"
                    if (keycode == KC_O) return 1036; // "become"
                    if (keycode == KC_R) return 1031; // "break"
                    if (keycode == KC_U) return 1025; // "business"
                    if (keycode == KC_Y) return 1020; // "body"
                    break;
                case -1:
                    if (keycode == KC_B) return -2; // b...
                    if (keycode == KC_C) return -13; // c...
                    if (keycode == KC_D) return -28; // d...
                    if (keycode == KC_F) return -41; // f...
                    if (keycode == KC_G) return -55; // g...
                    if (keycode == KC_K) return -67; // k...
                    if (keycode == KC_L) return -80; // l...
                    if (keycode == KC_M) return -94; // m...
                    if (keycode == KC_N) return -106; // n...
                    if (keycode == KC_P) return -122; // p...
                    if (keycode == KC_R) return -135; // r...
                    if (keycode == KC_S) return -152; // s...
                    if (keycode == KC_T) return -166; // t...
                    if (keycode == KC_V) return -180; // v...
                    if (keycode == KC_W) return -193; // w...
                    if (keycode == KC_X) return -206; // x...
                    if (keycode == KC_Z) return -219; // z...
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
                    case KC_COMMA: chord_decode_send(1137); return false; // " but "
                    case KC_D: chord_decode_send(1082); return false; // "oesn't"
                    case KC_DOT: tap_code16(KC_SLASH); return false;
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_ENT: chord_decode_send(1129); return false; // "the "
                    case KC_EQUAL: tap_code16(KC_RABK); return false;
                    case KC_EXLM: tap_code16(KC_EQUAL); return false;
                    case KC_F: tap_code16(KC_F); return false;
                    case KC_G: tap_code16(KC_N); return false;
                    case KC_H: tap_code16(KC_Y); return false;
                    case KC_I: tap_code16(KC_QUOTE); return false;
                    case KC_J: chord_decode_send(1102); return false; // "ust"
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_P); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_MINUS: tap_code16(KC_RABK); return false;
                    case KC_N: tap_code16(KC_G); return false;
                    case KC_O: tap_code16(KC_E); return false;
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_R: tap_code16(KC_K); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: chord_decode_send(1129); return false; // "the "
                    case KC_T: chord_decode_send(1113); return false; // "ion"
                    case KC_TAB: chord_decode_send(1129); return false; // "the "
                    case KC_TILD: tap_code16(KC_SLASH); return false;
                    case KC_V: chord_decode_send(1119); return false; // "er"
                    case KC_W: tap_code16(KC_N); return false;
                    case KC_X: tap_code16(KC_P); return false;
                    case KC_Z: chord_decode_send(1123); return false; // "eitlinger"
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): chord_decode_send(1082); return false; // "oesn't"
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_F): tap_code16(KC_F); return false;
                    case S(KC_G): tap_code16(KC_N); return false;
                    case S(KC_H): tap_code16(KC_Y); return false;
                    case S(KC_I): tap_code16(KC_QUOTE); return false;
                    case S(KC_J): chord_decode_send(1102); return false; // "ust"
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_P); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): tap_code16(KC_G); return false;
                    case S(KC_O): tap_code16(KC_E); return false;
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_R): tap_code16(KC_K); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): chord_decode_send(1113); return false; // "ion"
                    case S(KC_V): chord_decode_send(1119); return false; // "er"
                    case S(KC_W): tap_code16(KC_N); return false;
                    case S(KC_X): tap_code16(KC_P); return false;
                    case S(KC_Z): chord_decode_send(1123); return false; // "eitlinger"
                }
                return false;
            case MAGIC_B:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_U); return false;
                    case KC_B: chord_decode_send(1078); return false; // "ecause"
                    case KC_C: tap_code16(KC_P); return false;
                    case KC_COMMA: chord_decode_send(1142); return false; // " and "
                    case KC_D: chord_decode_send(1087); return false; // "oes"
                    case KC_DOT: chord_decode_send(1147); return false; // "./"
                    case KC_ENT: chord_decode_send(1133); return false; // "and "
                    case KC_F: chord_decode_send(1094); return false; // "or"
                    case KC_G: tap_code16(KC_K); return false;
                    case KC_H: chord_decode_send(1096); return false; // "ey"
                    case KC_I: chord_decode_send(1098); return false; // "'ve"
                    case KC_K: chord_decode_send(1105); return false; // "now"
                    case KC_L: tap_code16(KC_M); return false;
                    case KC_M: chord_decode_send(1108); return false; // "ent"
                    case KC_N: tap_code16(KC_K); return false;
                    case KC_P: tap_code16(KC_S); return false;
                    case KC_S: chord_decode_send(1113); return false; // "ion"
                    case KC_SPC: tap_code16(KC_BSPC); SEND_STRING(". "); add_oneshot_mods(MOD_BIT(KC_LSFT)); return false;
                    case KC_T: chord_decode_send(1116); return false; // "ing"
                    case KC_TAB: chord_decode_send(1133); return false; // "and "
                    case KC_U: tap_code16(KC_A); return false;
                    case KC_V: chord_decode_send(1121); return false; // "en"
                    case KC_W: tap_code16(KC_S); return false;
                    case KC_X: tap_code16(KC_C); return false;
                    case S(KC_A): tap_code16(KC_U); return false;
                    case S(KC_B): chord_decode_send(1078); return false; // "ecause"
                    case S(KC_C): tap_code16(KC_P); return false;
                    case S(KC_D): chord_decode_send(1087); return false; // "oes"
                    case S(KC_F): chord_decode_send(1094); return false; // "or"
                    case S(KC_G): tap_code16(KC_K); return false;
                    case S(KC_H): chord_decode_send(1096); return false; // "ey"
                    case S(KC_I): chord_decode_send(1098); return false; // "'ve"
                    case S(KC_K): chord_decode_send(1105); return false; // "now"
                    case S(KC_L): tap_code16(KC_M); return false;
                    case S(KC_M): chord_decode_send(1108); return false; // "ent"
                    case S(KC_N): tap_code16(KC_K); return false;
                    case S(KC_P): tap_code16(KC_S); return false;
                    case S(KC_S): chord_decode_send(1113); return false; // "ion"
                    case S(KC_T): chord_decode_send(1116); return false; // "ing"
                    case S(KC_U): tap_code16(KC_A); return false;
                    case S(KC_V): chord_decode_send(1121); return false; // "en"
                    case S(KC_W): tap_code16(KC_S); return false;
                    case S(KC_X): tap_code16(KC_C); return false;
                }
                return false;
            case MAGIC_C:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_U); return false;
                    case KC_B: tap_code16(KC_L); return false;
                    case KC_C: tap_code16(KC_K); return false;
                    case KC_D: chord_decode_send(1090); return false; // "on't"
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_G: tap_code16(KC_L); return false;
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_V); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_N: chord_decode_send(1111); return false; // "ly"
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: chord_decode_send(1129); return false; // "the "
                    case KC_T: chord_decode_send(1113); return false; // "ion"
                    case S(KC_A): tap_code16(KC_U); return false;
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): chord_decode_send(1090); return false; // "on't"
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_G): tap_code16(KC_L); return false;
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_V); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): chord_decode_send(1111); return false; // "ly"
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): chord_decode_send(1113); return false; // "ion"
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
