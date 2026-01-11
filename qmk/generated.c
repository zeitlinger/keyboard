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
    'e', 't', 'r', 'a', 'n', 'o', 'i', 's', 'l', 'u', 'h', 'c', 'g', 'y'
};

// 8-bit codes (0xE0+) for less common characters
static const char chord_char_extended[] = {
    'p', 'd', 'b', 'm', 'v', 'w', 'f', 'k', ' ', '\'', 'j', 'x', 'q', 'G', 'L', 'z', 'O', 'T', '.', '/'
};

// Global buffer containing all 4/8-bit variable-length encoded chord strings
static const uint8_t chord_data[] = {
    0x0c, 0xed, 0x23, 0xe6, 0x34, 0x30, 0xe8, 0xee, 0x30, 0xe2, 0x70, 0x0b, 0x70, 0xe0, 0x26, 0x4c,
    0xe8, 0xe2, 0x55, 0x10, 0x08, 0x25, 0x88, 0xe1, 0x6b, 0x00, 0x09, 0xea, 0x30, 0xe4, 0x33, 0xc0,
    0x41, 0x0e, 0x70, 0xe0, 0x26, 0x4c, 0xe8, 0x71, 0x32, 0x10, 0x20, 0x06, 0xc6, 0x1a, 0x90, 0xe2,
    0x08, 0x52, 0xc3, 0x46, 0xef, 0x00, 0x05, 0x37, 0xd4, 0xb0, 0x05, 0x70, 0xe3, 0x68, 0x00, 0x07,
    0x20, 0x38, 0x60, 0xef, 0x00, 0x09, 0x10, 0x80, 0xe3, 0x01, 0x2d, 0x06, 0x3b, 0x19, 0x38, 0x08,
    0x20, 0x75, 0x92, 0xb0, 0x0d, 0xf0, 0xe0, 0x04, 0xf1, 0x08, 0x00, 0xe3, 0x01, 0x2d, 0x09, 0x00,
    0xeb, 0xb0, 0xe0, 0x16, 0x54, 0x08, 0x00, 0xeb, 0x67, 0x16, 0x4c, 0x05, 0xa1, 0x10, 0xe0, 0x70,
    0x07, 0x00, 0xeb, 0x0b, 0x91, 0x00, 0x07, 0x00, 0xeb, 0x30, 0xe3, 0xe0, 0x80, 0x06, 0x00, 0xeb,
    0xe0, 0x52, 0x10, 0x12, 0xe1, 0x0b, 0x83, 0x23, 0x16, 0xe4, 0x00, 0xe8, 0xb5, 0x40, 0xe6, 0x6c,
    0x07, 0xb5, 0x41, 0x00, 0xeb, 0x10, 0x05, 0xe5, 0x52, 0x2d, 0x08, 0x64, 0x10, 0x24, 0x38, 0x05,
    0xe5, 0xa0, 0x20, 0x07, 0xe5, 0x61, 0xa5, 0x91, 0x05, 0xe5, 0x25, 0x4c, 0x04, 0xe5, 0x61, 0xa0,
    0x05, 0xe5, 0xa6, 0xba, 0x04, 0xe5, 0x38, 0xe7, 0x05, 0x30, 0xe5, 0x36, 0x10, 0x08, 0xe5, 0x59,
    0x80, 0xe1, 0x40, 0xe9, 0x10, 0x05, 0xe5, 0x59, 0x80, 0xe1, 0x0a, 0x00, 0xe4, 0x02, 0xd1, 0xa6,
    0x4c, 0x05, 0xe4, 0x38, 0x90, 0x05, 0x40, 0xe4, 0x02, 0x04, 0x50, 0xe4, 0x02, 0x06, 0x45, 0x16,
    0xb0, 0x08, 0x70, 0x20, 0xe4, 0x6b, 0x07, 0x07, 0xe4, 0x02, 0x76, 0x54, 0x04, 0xe4, 0x02, 0xd0,
    0x09, 0x30, 0xe4, 0x36, 0x83, 0xe2, 0x80, 0x04, 0xe4, 0x56, 0xe1, 0x07, 0xb5, 0x41, 0x26, 0xe2,
    0x04, 0xa3, 0xe4, 0x00, 0x04, 0x1a, 0x0d, 0x06, 0x1a, 0x59, 0xca, 0x05, 0x1a, 0x02, 0x00, 0x07,
    0x1a, 0x59, 0xca, 0x10, 0x07, 0x1a, 0x25, 0x9c, 0xa0, 0x04, 0x16, 0xe3, 0x00, 0x04, 0x1a, 0x67,
    0x05, 0x1a, 0x07, 0x00, 0x04, 0x1a, 0x31, 0x04, 0x1d, 0xe0, 0x00, 0x06, 0x10, 0x43, 0x41, 0x05,
    0x1a, 0x64, 0xe7, 0x06, 0x7d, 0x71, 0x00, 0xe3, 0x07, 0x79, 0xe0, 0xe0, 0x52, 0x10, 0x08, 0x79,
    0x20, 0xe0, 0x26, 0x70, 0x06, 0x78, 0x50, 0xe5, 0x8d, 0x07, 0x79, 0xe2, 0xea, 0x0b, 0x10, 0x07,
    0x75, 0xe3, 0x05, 0x40, 0x05, 0x7a, 0x32, 0x00, 0x06, 0x70, 0x32, 0xba, 0x04, 0x73, 0xe3, 0x00,
    0x06, 0x71, 0x26, 0x4c, 0x06, 0xe5, 0x37, 0x40, 0xe9, 0x10, 0x06, 0x7a, 0x59, 0x80, 0xe1, 0x05,
    0xd0, 0x32, 0x70, 0x04, 0x12, 0x90, 0x06, 0x32, 0x59, 0x40, 0xe1, 0x06, 0x20, 0x19, 0x24, 0x05,
    0x26, 0xca, 0x10, 0x06, 0x20, 0xe4, 0x60, 0xe5, 0x05, 0x20, 0x30, 0xe1, 0xd0, 0x07, 0xe0, 0x25,
    0xc2, 0x30, 0xe3, 0x05, 0x02, 0x25, 0x20, 0x05, 0x25, 0x91, 0x00, 0x06, 0x20, 0x38, 0x8d, 0x05,
    0x10, 0x71, 0x70, 0x05, 0xec, 0x90, 0x2d, 0x04, 0xe2, 0x85, 0xe2, 0x07, 0xe6, 0x03, 0x19, 0x20,
    0x06, 0x67, 0x79, 0x07, 0x08, 0xe1, 0x07, 0xb2, 0x60, 0xe2, 0x00, 0x07, 0x20, 0xec, 0x90, 0x71,
    0x07, 0x71, 0x32, 0x10, 0x20, 0x06, 0x70, 0xe0, 0x26, 0x4c, 0x06, 0x70, 0xe0, 0x26, 0x4c, 0x08,
    0xe0, 0x25, 0xe2, 0x30, 0xe2, 0x8d, 0x06, 0xe0, 0x90, 0xe2, 0x86, 0xb0, 0x06, 0xe0, 0x32, 0x04,
    0x10, 0x07, 0xe0, 0x25, 0xe1, 0x9b, 0x10, 0x07, 0xe0, 0x25, 0xe2, 0x80, 0xe3, 0x05, 0xe0, 0x56,
    0x41, 0x04, 0xa1, 0x10, 0xe0, 0x05, 0xe0, 0x83, 0xb0, 0x07, 0xe0, 0x26, 0xe4, 0x3b, 0xd0, 0x07,
    0xe0, 0x25, 0xe3, 0x67, 0x00, 0x06, 0xe0, 0x80, 0x37, 0x00, 0x06, 0xe0, 0x05, 0xe0, 0x80, 0x07,
    0xb5, 0xe3, 0xe0, 0x34, 0xd0, 0x06, 0x04, 0x59, 0xca, 0x04, 0x40, 0x32, 0x07, 0x34, 0x51, 0xa0,
    0x20, 0x07, 0x64, 0x71, 0x03, 0xe1, 0x04, 0x64, 0x15, 0x08, 0x34, 0xd1, 0xa6, 0x4c, 0x06, 0x49,
    0xe3, 0xe2, 0x02, 0x06, 0x34, 0xd0, 0xe5, 0x3d, 0x04, 0x49, 0x88, 0x06, 0x76, 0x4c, 0x80, 0x0a,
    0x94, 0xe1, 0x02, 0x71, 0x34, 0xe1, 0x06, 0xe3, 0xd7, 0x08, 0xe6, 0x05, 0xe3, 0x97, 0x6b, 0x05,
    0xe3, 0x30, 0xea, 0x52, 0x06, 0xe3, 0x64, 0x91, 0x00, 0x05, 0xe3, 0x6c, 0xa1, 0x07, 0xe3, 0x07,
    0x73, 0xc0, 0x04, 0x75, 0xe3, 0x00, 0x06, 0xe3, 0x01, 0xa5, 0xe1, 0x04, 0x8c, 0x10, 0xe3, 0x04,
    0xe3, 0x52, 0x00, 0x04, 0x54, 0x8d, 0x06, 0x38, 0xe3, 0x57, 0x10, 0x05, 0x83, 0x10, 0x20, 0x05,
    0x38, 0x54, 0xc0, 0x05, 0x83, 0x2c, 0x00, 0x05, 0x86, 0xca, 0x10, 0x06, 0xa0, 0x38, 0x1a, 0x05,
    0x80, 0x30, 0xe4, 0x00, 0x04, 0x38, 0x75, 0x05, 0xb8, 0x37, 0x70, 0x05, 0x80, 0xe4, 0x08, 0x04,
    0x86, 0xe7, 0x00, 0x07, 0xec, 0x96, 0xb0, 0xe7, 0x8d, 0x06, 0xb3, 0x88, 0x02, 0x04, 0xe5, 0x52,
    0xe7, 0x04, 0xe7, 0x45, 0xe5, 0x04, 0xea, 0x30, 0xe4, 0x30, 0x04, 0xe7, 0x64, 0xe1, 0x05, 0xba,
    0x0b, 0xe7, 0x04, 0xe7, 0x00, 0xe0, 0x04, 0xe3, 0x30, 0xe7, 0x00, 0x03, 0xe7, 0x0d, 0x06, 0xb5,
    0x40, 0xe6, 0x6c, 0x08, 0xec, 0x90, 0x71, 0x65, 0x40, 0x05, 0x51, 0xa0, 0x20, 0x04, 0xe5, 0xa0,
    0x40, 0x06, 0x60, 0xe3, 0xe0, 0x52, 0x10, 0x04, 0xea, 0x97, 0x10, 0x05, 0x00, 0xe4, 0x02, 0xd0,
    0x05, 0xc9, 0x07, 0x70, 0x05, 0xc2, 0x03, 0x10, 0x05, 0xc2, 0x59, 0xe0, 0x07, 0xc0, 0x40, 0x23,
    0x80, 0x06, 0xc6, 0xe4, 0x64, 0xc0, 0x06, 0x26, 0xca, 0x17, 0x05, 0xe2, 0x0c, 0x34, 0x06, 0xc8,
    0x34, 0xb0, 0x0c, 0xed, 0x23, 0xe6, 0x34, 0x30, 0xe8, 0xee, 0x30, 0xe2, 0x70, 0x07, 0xed, 0x23,
    0xe6, 0x34, 0x30, 0x05, 0x3c, 0x36, 0x40, 0x05, 0xe6, 0x52, 0x1d, 0x05, 0xe6, 0x59, 0x40, 0xe1,
    0x08, 0x75, 0xe6, 0x10, 0xe5, 0x32, 0x00, 0x0b, 0x64, 0xe6, 0x52, 0xe3, 0x31, 0x65, 0x40, 0x06,
    0xe6, 0x64, 0xc0, 0x20, 0x05, 0xe6, 0x62, 0x71, 0x04, 0x1a, 0x04, 0x04, 0xe6, 0x00, 0x80, 0x05,
    0x30, 0xe6, 0x10, 0x20, 0x05, 0xe6, 0x38, 0x70, 0x05, 0xe6, 0x36, 0x87, 0x04, 0xe6, 0x25, 0xe3,
    0x07, 0x38, 0x20, 0x30, 0xe1, 0xd0, 0x08, 0xe0, 0x25, 0xe1, 0x9b, 0x17, 0x05, 0x1a, 0x06, 0x20,
    0x05, 0xe2, 0x96, 0x80, 0xe1, 0x06, 0xe1, 0x92, 0x64, 0xc0, 0x04, 0x1a, 0x34, 0x04, 0x1a, 0x00,
    0xe3, 0x05, 0x15, 0xe1, 0x3d, 0x04, 0xe1, 0x31, 0x30, 0x06, 0xa3, 0xe1, 0x40, 0xe9, 0x10, 0x06,
    0xe1, 0x60, 0xe1, 0x40, 0xe9, 0x10, 0x06, 0xe0, 0x58, 0x6b, 0xd0, 0x07, 0xb9, 0x22, 0x04, 0x10,
    0x06, 0x3b, 0x25, 0x77, 0x08, 0xb5, 0x41, 0x64, 0x90, 0x07, 0xe0, 0x25, 0xea, 0x0b, 0x10, 0x05,
    0xb8, 0x6b, 0xe7, 0x08, 0x20, 0x70, 0x32, 0xba, 0x07, 0x70, 0x20, 0xe4, 0x6b, 0x00, 0x08, 0x3b,
    0x19, 0x38, 0x8d, 0x05, 0xb5, 0x47, 0x10, 0x08, 0xb5, 0x98, 0xe1, 0x40, 0xe9, 0x10, 0x05, 0xb5,
    0x98, 0xe1, 0x04, 0xe2, 0x50, 0xe1, 0xd0, 0x08, 0xe2, 0x97, 0x64, 0x07, 0x70, 0x05, 0xe2, 0x20,
    0x30, 0xe7, 0x06, 0xe2, 0x0b, 0x50, 0xe3, 0x00, 0x07, 0xe2, 0x01, 0xe5, 0x00, 0x40, 0x05, 0xe2,
    0x06, 0x4c, 0x06, 0xe2, 0x0a, 0x64, 0xe1, 0x04, 0xe2, 0x00, 0x40, 0x07, 0xe2, 0x55, 0x80, 0x34,
    0x0d, 0x50, 0xe2, 0x70, 0x20, 0xe4, 0x30, 0xe2, 0x68, 0x61, 0xd0, 0x05, 0x30, 0xe2, 0x59, 0x10,
    0x06, 0x0b, 0x39, 0x70, 0x06, 0x50, 0x74, 0xe9, 0x10, 0x03, 0x50, 0x70, 0x04, 0x54, 0xe9, 0x10,
    0x02, 0x52, 0x02, 0x0d, 0x03, 0xe9, 0xe4, 0x00, 0x03, 0x97, 0x10, 0x03, 0x45, 0xe5, 0x03, 0x04,
    0x10, 0x02, 0x8d, 0x03, 0x65, 0x40, 0x03, 0x64, 0xc0, 0x02, 0x02, 0x02, 0x04, 0x09, 0x06, 0x18,
    0x64, 0xc0, 0x20, 0x04, 0x1a, 0x00, 0xe8, 0x04, 0x34, 0xe1, 0xe8, 0x05, 0xe8, 0xe2, 0x91, 0xe8,
    0x05, 0xe8, 0x34, 0xe1, 0xe8, 0x02, 0xf2, 0xf3
};

// Decode and send 4/8-bit variable-length encoded chord string from buffer
static void chord_decode_send(const uint8_t* data) {
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
                case -220:
                    if (keycode == KC_SPC) return 63;
                    if (keycode == KC_COMMA) return 58;
                    if (keycode == KC_DOT) return 54;
                    if (keycode == KC_A) return 48;
                    if (keycode == KC_E) return 43;
                    if (keycode == KC_H) return 33;
                    if (keycode == KC_J) return 26;
                    if (keycode == KC_R) return 20;
                    if (keycode == KC_U) return 11;
                    if (keycode == KC_Y) return 0;
                    break;
                // x
                case -207:
                    if (keycode == KC_SPC) return 144;
                    if (keycode == KC_COMMA) return 131;
                    if (keycode == KC_DOT) return 125;
                    if (keycode == KC_A) return 118;
                    if (keycode == KC_E) return 112;
                    if (keycode == KC_H) return 107;
                    if (keycode == KC_I) return 101;
                    if (keycode == KC_J) return 94;
                    if (keycode == KC_O) return 84;
                    if (keycode == KC_R) return 79;
                    if (keycode == KC_U) return 75;
                    if (keycode == KC_Y) return 69;
                    break;
                // w
                case -195:
                    if (keycode == KC_SPC) return 197;
                    if (keycode == KC_COMMA) return 189;
                    if (keycode == KC_DOT) return 184;
                    if (keycode == KC_A) return 180;
                    if (keycode == KC_H) return 176;
                    if (keycode == KC_I) return 172;
                    if (keycode == KC_J) return 168;
                    if (keycode == KC_O) return 163;
                    if (keycode == KC_R) return 159;
                    if (keycode == KC_U) return 154;
                    if (keycode == KC_Y) return 150;
                    break;
                // v
                case -182:
                    if (keycode == KC_SPC) return 256;
                    if (keycode == KC_COMMA) return 251;
                    if (keycode == KC_DOT) return 247;
                    if (keycode == KC_A) return 240;
                    if (keycode == KC_E) return 236;
                    if (keycode == KC_H) return 231;
                    if (keycode == KC_I) return 225;
                    if (keycode == KC_J) return 221;
                    if (keycode == KC_O) return 217;
                    if (keycode == KC_R) return 213;
                    if (keycode == KC_U) return 209;
                    if (keycode == KC_Y) return 202;
                    break;
                // t
                case -169:
                    if (keycode == KC_SPC) return 303;
                    if (keycode == KC_COMMA) return 299;
                    if (keycode == KC_DOT) return 295;
                    if (keycode == KC_A) return 292;
                    if (keycode == KC_E) return 288;
                    if (keycode == KC_H) return 285;
                    if (keycode == KC_I) return 281;
                    if (keycode == KC_J) return 276;
                    if (keycode == KC_O) return 271;
                    if (keycode == KC_R) return 267;
                    if (keycode == KC_U) return 263;
                    if (keycode == KC_Y) return 260;
                    break;
                // s
                case -156:
                    if (keycode == KC_SPC) return 362;
                    if (keycode == KC_COMMA) return 356;
                    if (keycode == KC_DOT) return 352;
                    if (keycode == KC_A) return 348;
                    if (keycode == KC_E) return 344;
                    if (keycode == KC_H) return 340;
                    if (keycode == KC_I) return 335;
                    if (keycode == KC_J) return 329;
                    if (keycode == KC_O) return 324;
                    if (keycode == KC_R) return 318;
                    if (keycode == KC_U) return 312;
                    if (keycode == KC_Y) return 307;
                    break;
                // r
                case -144:
                    if (keycode == KC_SPC) return 411;
                    if (keycode == KC_COMMA) return 407;
                    if (keycode == KC_DOT) return 403;
                    if (keycode == KC_A) return 397;
                    if (keycode == KC_E) return 392;
                    if (keycode == KC_H) return 387;
                    if (keycode == KC_I) return 383;
                    if (keycode == KC_J) return 379;
                    if (keycode == KC_O) return 374;
                    if (keycode == KC_U) return 371;
                    if (keycode == KC_Y) return 367;
                    break;
                // q
                case -133:
                    if (keycode == KC_SPC) return 458;
                    if (keycode == KC_COMMA) return 453;
                    if (keycode == KC_A) return 448;
                    if (keycode == KC_E) return 443;
                    if (keycode == KC_H) return 436;
                    if (keycode == KC_I) return 432;
                    if (keycode == KC_J) return 427;
                    if (keycode == KC_O) return 423;
                    if (keycode == KC_U) return 419;
                    if (keycode == KC_Y) return 415;
                    break;
                // p
                case -120:
                    if (keycode == KC_SPC) return 522;
                    if (keycode == KC_COMMA) return 517;
                    if (keycode == KC_DOT) return 511;
                    if (keycode == KC_A) return 505;
                    if (keycode == KC_E) return 501;
                    if (keycode == KC_H) return 497;
                    if (keycode == KC_I) return 493;
                    if (keycode == KC_J) return 487;
                    if (keycode == KC_O) return 481;
                    if (keycode == KC_R) return 476;
                    if (keycode == KC_U) return 470;
                    if (keycode == KC_Y) return 463;
                    break;
                // n
                case -107:
                    if (keycode == KC_SPC) return 575;
                    if (keycode == KC_COMMA) return 571;
                    if (keycode == KC_DOT) return 568;
                    if (keycode == KC_A) return 563;
                    if (keycode == KC_E) return 558;
                    if (keycode == KC_H) return 553;
                    if (keycode == KC_I) return 550;
                    if (keycode == KC_J) return 545;
                    if (keycode == KC_O) return 540;
                    if (keycode == KC_R) return 537;
                    if (keycode == KC_U) return 533;
                    if (keycode == KC_Y) return 527;
                    break;
                // m
                case -96:
                    if (keycode == KC_SPC) return 623;
                    if (keycode == KC_COMMA) return 619;
                    if (keycode == KC_DOT) return 614;
                    if (keycode == KC_A) return 610;
                    if (keycode == KC_E) return 605;
                    if (keycode == KC_H) return 601;
                    if (keycode == KC_I) return 596;
                    if (keycode == KC_J) return 591;
                    if (keycode == KC_U) return 587;
                    if (keycode == KC_Y) return 582;
                    break;
                // l
                case -83:
                    if (keycode == KC_SPC) return 671;
                    if (keycode == KC_COMMA) return 667;
                    if (keycode == KC_DOT) return 663;
                    if (keycode == KC_A) return 660;
                    if (keycode == KC_E) return 655;
                    if (keycode == KC_H) return 651;
                    if (keycode == KC_I) return 647;
                    if (keycode == KC_J) return 643;
                    if (keycode == KC_O) return 639;
                    if (keycode == KC_R) return 635;
                    if (keycode == KC_U) return 630;
                    if (keycode == KC_Y) return 627;
                    break;
                // k
                case -70:
                    if (keycode == KC_SPC) return 723;
                    if (keycode == KC_COMMA) return 718;
                    if (keycode == KC_DOT) return 715;
                    if (keycode == KC_A) return 710;
                    if (keycode == KC_E) return 706;
                    if (keycode == KC_H) return 702;
                    if (keycode == KC_I) return 698;
                    if (keycode == KC_J) return 693;
                    if (keycode == KC_O) return 689;
                    if (keycode == KC_R) return 685;
                    if (keycode == KC_U) return 681;
                    if (keycode == KC_Y) return 675;
                    break;
                // j
                case -65:
                    if (keycode == KC_SPC) return 743;
                    if (keycode == KC_A) return 737;
                    if (keycode == KC_E) return 733;
                    if (keycode == KC_O) return 729;
                    break;
                // g
                case -52:
                    if (keycode == KC_SPC) return 803;
                    if (keycode == KC_COMMA) return 797;
                    if (keycode == KC_DOT) return 786;
                    if (keycode == KC_A) return 782;
                    if (keycode == KC_E) return 778;
                    if (keycode == KC_H) return 774;
                    if (keycode == KC_I) return 769;
                    if (keycode == KC_J) return 764;
                    if (keycode == KC_O) return 760;
                    if (keycode == KC_R) return 756;
                    if (keycode == KC_U) return 752;
                    if (keycode == KC_Y) return 747;
                    break;
                // f
                case -39:
                    if (keycode == KC_SPC) return 860;
                    if (keycode == KC_COMMA) return 856;
                    if (keycode == KC_DOT) return 852;
                    if (keycode == KC_A) return 847;
                    if (keycode == KC_E) return 843;
                    if (keycode == KC_H) return 840;
                    if (keycode == KC_I) return 836;
                    if (keycode == KC_J) return 831;
                    if (keycode == KC_O) return 823;
                    if (keycode == KC_R) return 816;
                    if (keycode == KC_U) return 811;
                    if (keycode == KC_Y) return 807;
                    break;
                // d
                case -27:
                    if (keycode == KC_SPC) return 911;
                    if (keycode == KC_COMMA) return 905;
                    if (keycode == KC_DOT) return 901;
                    if (keycode == KC_A) return 897;
                    if (keycode == KC_E) return 893;
                    if (keycode == KC_H) return 890;
                    if (keycode == KC_I) return 885;
                    if (keycode == KC_J) return 880;
                    if (keycode == KC_R) return 876;
                    if (keycode == KC_U) return 870;
                    if (keycode == KC_Y) return 864;
                    break;
                // c
                case -14:
                    if (keycode == KC_SPC) return 974;
                    if (keycode == KC_COMMA) return 967;
                    if (keycode == KC_DOT) return 963;
                    if (keycode == KC_A) return 958;
                    if (keycode == KC_E) return 952;
                    if (keycode == KC_H) return 947;
                    if (keycode == KC_I) return 943;
                    if (keycode == KC_J) return 937;
                    if (keycode == KC_O) return 932;
                    if (keycode == KC_R) return 928;
                    if (keycode == KC_U) return 923;
                    if (keycode == KC_Y) return 918;
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return 1035;
                    if (keycode == KC_COMMA) return 1024;
                    if (keycode == KC_DOT) return 1019;
                    if (keycode == KC_A) return 1015;
                    if (keycode == KC_H) return 1010;
                    if (keycode == KC_I) return 1006;
                    if (keycode == KC_J) return 1000;
                    if (keycode == KC_O) return 994;
                    if (keycode == KC_R) return 989;
                    if (keycode == KC_U) return 983;
                    if (keycode == KC_Y) return 978;
                    break;
                case -1:
                    if (keycode == KC_B) return -2;
                    if (keycode == KC_C) return -14;
                    if (keycode == KC_D) return -27;
                    if (keycode == KC_F) return -39;
                    if (keycode == KC_G) return -52;
                    if (keycode == KC_J) return -65;
                    if (keycode == KC_K) return -70;
                    if (keycode == KC_L) return -83;
                    if (keycode == KC_M) return -96;
                    if (keycode == KC_N) return -107;
                    if (keycode == KC_P) return -120;
                    if (keycode == KC_Q) return -133;
                    if (keycode == KC_R) return -144;
                    if (keycode == KC_S) return -156;
                    if (keycode == KC_T) return -169;
                    if (keycode == KC_V) return -182;
                    if (keycode == KC_W) return -195;
                    if (keycode == KC_X) return -207;
                    if (keycode == KC_Z) return -220;
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
    case SUB_3: return 200;
    case SUB_4: return 200;
    case SUB_5: return 200;
    case SUB_6: return 200;
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
                    case KC_COMMA: chord_decode_send(chord_data + 1099); return false;
                    case KC_D: chord_decode_send(chord_data + 1044); return false;
                    case KC_DOT: tap_code16(KC_SLASH); return false;
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_ENT: chord_decode_send(chord_data + 1091); return false;
                    case KC_EQUAL: tap_code16(KC_RABK); return false;
                    case KC_EXLM: tap_code16(KC_EQUAL); return false;
                    case KC_F: tap_code16(KC_F); return false;
                    case KC_G: tap_code16(KC_N); return false;
                    case KC_H: tap_code16(KC_Y); return false;
                    case KC_I: tap_code16(KC_QUOTE); return false;
                    case KC_J: chord_decode_send(chord_data + 1064); return false;
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_P); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_MINUS: tap_code16(KC_RABK); return false;
                    case KC_N: tap_code16(KC_G); return false;
                    case KC_O: tap_code16(KC_E); return false;
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_R: tap_code16(KC_K); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: chord_decode_send(chord_data + 1091); return false;
                    case KC_T: chord_decode_send(chord_data + 1075); return false;
                    case KC_TAB: chord_decode_send(chord_data + 1091); return false;
                    case KC_TILD: tap_code16(KC_SLASH); return false;
                    case KC_V: chord_decode_send(chord_data + 1081); return false;
                    case KC_W: tap_code16(KC_N); return false;
                    case KC_X: tap_code16(KC_P); return false;
                    case KC_Z: chord_decode_send(chord_data + 1085); return false;
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): chord_decode_send(chord_data + 1044); return false;
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_F): tap_code16(KC_F); return false;
                    case S(KC_G): tap_code16(KC_N); return false;
                    case S(KC_H): tap_code16(KC_Y); return false;
                    case S(KC_I): tap_code16(KC_QUOTE); return false;
                    case S(KC_J): chord_decode_send(chord_data + 1064); return false;
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_P); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): tap_code16(KC_G); return false;
                    case S(KC_O): tap_code16(KC_E); return false;
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_R): tap_code16(KC_K); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): chord_decode_send(chord_data + 1075); return false;
                    case S(KC_V): chord_decode_send(chord_data + 1081); return false;
                    case S(KC_W): tap_code16(KC_N); return false;
                    case S(KC_X): tap_code16(KC_P); return false;
                    case S(KC_Z): chord_decode_send(chord_data + 1085); return false;
                }
                return false;
            case MAGIC_B:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_U); return false;
                    case KC_B: chord_decode_send(chord_data + 1040); return false;
                    case KC_C: tap_code16(KC_P); return false;
                    case KC_COMMA: chord_decode_send(chord_data + 1104); return false;
                    case KC_D: chord_decode_send(chord_data + 1049); return false;
                    case KC_DOT: chord_decode_send(chord_data + 1109); return false;
                    case KC_ENT: chord_decode_send(chord_data + 1095); return false;
                    case KC_F: chord_decode_send(chord_data + 1056); return false;
                    case KC_G: tap_code16(KC_K); return false;
                    case KC_H: chord_decode_send(chord_data + 1058); return false;
                    case KC_I: chord_decode_send(chord_data + 1060); return false;
                    case KC_K: chord_decode_send(chord_data + 1067); return false;
                    case KC_L: tap_code16(KC_M); return false;
                    case KC_M: chord_decode_send(chord_data + 1070); return false;
                    case KC_N: tap_code16(KC_K); return false;
                    case KC_P: tap_code16(KC_S); return false;
                    case KC_S: chord_decode_send(chord_data + 1075); return false;
                    case KC_SPC: tap_code16(KC_BSPC); SEND_STRING(". "); add_oneshot_mods(MOD_BIT(KC_LSFT)); return false;
                    case KC_T: chord_decode_send(chord_data + 1078); return false;
                    case KC_TAB: chord_decode_send(chord_data + 1095); return false;
                    case KC_U: tap_code16(KC_A); return false;
                    case KC_V: chord_decode_send(chord_data + 1083); return false;
                    case KC_W: tap_code16(KC_S); return false;
                    case KC_X: tap_code16(KC_C); return false;
                    case S(KC_A): tap_code16(KC_U); return false;
                    case S(KC_B): chord_decode_send(chord_data + 1040); return false;
                    case S(KC_C): tap_code16(KC_P); return false;
                    case S(KC_D): chord_decode_send(chord_data + 1049); return false;
                    case S(KC_F): chord_decode_send(chord_data + 1056); return false;
                    case S(KC_G): tap_code16(KC_K); return false;
                    case S(KC_H): chord_decode_send(chord_data + 1058); return false;
                    case S(KC_I): chord_decode_send(chord_data + 1060); return false;
                    case S(KC_K): chord_decode_send(chord_data + 1067); return false;
                    case S(KC_L): tap_code16(KC_M); return false;
                    case S(KC_M): chord_decode_send(chord_data + 1070); return false;
                    case S(KC_N): tap_code16(KC_K); return false;
                    case S(KC_P): tap_code16(KC_S); return false;
                    case S(KC_S): chord_decode_send(chord_data + 1075); return false;
                    case S(KC_T): chord_decode_send(chord_data + 1078); return false;
                    case S(KC_U): tap_code16(KC_A); return false;
                    case S(KC_V): chord_decode_send(chord_data + 1083); return false;
                    case S(KC_W): tap_code16(KC_S); return false;
                    case S(KC_X): tap_code16(KC_C); return false;
                }
                return false;
            case MAGIC_C:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_U); return false;
                    case KC_B: tap_code16(KC_L); return false;
                    case KC_C: tap_code16(KC_K); return false;
                    case KC_D: chord_decode_send(chord_data + 1052); return false;
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_G: tap_code16(KC_L); return false;
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_V); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_N: chord_decode_send(chord_data + 1073); return false;
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: chord_decode_send(chord_data + 1091); return false;
                    case KC_T: chord_decode_send(chord_data + 1075); return false;
                    case S(KC_A): tap_code16(KC_U); return false;
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): chord_decode_send(chord_data + 1052); return false;
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_G): tap_code16(KC_L); return false;
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_V); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): chord_decode_send(chord_data + 1073); return false;
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): chord_decode_send(chord_data + 1075); return false;
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
