/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int alternateLayer = -1;
int layer = _BASE;
#define CHORD_ROOT -1
#define CHORD_INACTIVE -10000
#define CHORD_MODIFIER -10001
int chord_state = CHORD_INACTIVE; // negative = transition states, non-negative = byte offsets
int chord_depth = 0; // Track number of letters in current chord

// Chord string decoder lookup table (5-bit codes -> characters)
static const char chord_char_lookup[] = {
    'e', 't', 'r', 'a', 'n', 'o', 'i', 's', 'l', 'u', 'h', 'c', 'g', 'p', 'y', 'm', 'b', 'd', 'v', 'w', 'f', 'k', 'j', 'x', '\'', ' ', 'q', 'G', 'z', 'L', 'O', 'T'
};

// Global buffer containing all 5-bit packed chord strings
static const uint8_t chord_data[] = {
    0x0c, 0x5b, 0x0c, 0x3a, 0xc8, 0xc8, 0x7d, 0xc0, 0x03, 0x0b, 0xa7, 0x09, 0x43, 0x58, 0x86, 0xa5,
    0x04, 0x08, 0xa2, 0x20, 0x14, 0xcd, 0x02, 0x04, 0xbc, 0x10, 0x00, 0x09, 0x76, 0xc8, 0x31, 0x18,
    0x20, 0x01, 0x0e, 0xa7, 0x09, 0x43, 0x58, 0x3e, 0x61, 0x88, 0x00, 0x04, 0x06, 0xcc, 0x04, 0x95,
    0x20, 0x08, 0x45, 0xb0, 0x41, 0x0c, 0x07, 0x05, 0xe3, 0x38, 0xb2, 0x00, 0x05, 0xe7, 0x19, 0x04,
    0x00, 0x07, 0x02, 0x0c, 0x64, 0x38, 0x00, 0x09, 0x01, 0x20, 0xf0, 0x40, 0x10, 0x0e, 0x06, 0x63,
    0x85, 0x34, 0x10, 0x08, 0x02, 0x9c, 0x92, 0xc4, 0x02, 0x0d, 0xbe, 0x01, 0xf2, 0x01, 0x02, 0x0f,
    0x04, 0xe1, 0x00, 0x09, 0xe0, 0x2e, 0xd0, 0x82, 0x29, 0x04, 0x08, 0xe0, 0x9a, 0x13, 0x0c, 0x61,
    0x05, 0x2a, 0x84, 0x76, 0x00, 0x07, 0xe0, 0x82, 0x95, 0x02, 0x00, 0x07, 0xe0, 0x8e, 0xd7, 0x10,
    0x00, 0x06, 0xe0, 0xb6, 0x22, 0x02, 0x12, 0x11, 0x2c, 0x34, 0xc4, 0x08, 0x46, 0x82, 0xbc, 0x0a,
    0xa1, 0x86, 0x01, 0x07, 0xab, 0x90, 0x00, 0x6e, 0x00, 0x05, 0xb3, 0x08, 0xe1, 0x00, 0x08, 0x86,
    0x04, 0x20, 0xc8, 0x40, 0x05, 0x53, 0x01, 0x01, 0x00, 0x07, 0xd3, 0x04, 0x55, 0x52, 0x00, 0x05,
    0x53, 0x14, 0xc2, 0x00, 0x04, 0xd3, 0x04, 0x05, 0x05, 0x53, 0x99, 0xa5, 0x00, 0x04, 0x73, 0xa0,
    0x0a, 0x05, 0x63, 0x0e, 0x13, 0x00, 0x08, 0xb3, 0x24, 0x14, 0x09, 0x0e, 0x05, 0xb3, 0x24, 0x14,
    0x01, 0x0a, 0x40, 0x02, 0xe1, 0x82, 0x32, 0x84, 0x01, 0x05, 0x72, 0xa0, 0x04, 0x00, 0x05, 0x04,
    0x48, 0x20, 0x00, 0x04, 0x45, 0x02, 0x01, 0x06, 0xa4, 0x04, 0xb3, 0x00, 0x08, 0x07, 0x08, 0x69,
    0x16, 0x38, 0x07, 0x12, 0x88, 0x63, 0x0a, 0x01, 0x04, 0x12, 0x08, 0x07, 0x09, 0x43, 0x0e, 0x83,
    0x06, 0x44, 0x00, 0x04, 0xb2, 0x98, 0x08, 0x07, 0xab, 0x90, 0x20, 0x0c, 0x04, 0x04, 0x6a, 0x48,
    0x00, 0x04, 0x41, 0x01, 0x07, 0x06, 0x41, 0x95, 0xc4, 0x14, 0x05, 0x41, 0x01, 0x01, 0x00, 0x07,
    0x41, 0x95, 0xc4, 0x54, 0x00, 0x07, 0x41, 0x89, 0x92, 0x98, 0x02, 0x04, 0xc1, 0x3c, 0x00, 0x04,
    0x41, 0x99, 0x03, 0x05, 0x41, 0x81, 0x03, 0x00, 0x04, 0x41, 0x8d, 0x00, 0x04, 0xc1, 0x35, 0x00,
    0x06, 0x01, 0x90, 0x41, 0x02, 0x05, 0x41, 0x19, 0x52, 0x01, 0x06, 0xc7, 0x9d, 0x00, 0x1e, 0x07,
    0x27, 0xb5, 0x56, 0x44, 0x00, 0x08, 0x27, 0x89, 0x26, 0xcc, 0x01, 0x06, 0x07, 0x95, 0x89, 0x1c,
    0x07, 0x27, 0x41, 0x0b, 0x56, 0x00, 0x07, 0xa7, 0x3c, 0x50, 0x08, 0x00, 0x05, 0x47, 0x0d, 0x01,
    0x00, 0x06, 0x07, 0x0c, 0xb1, 0x14, 0x04, 0x67, 0x3c, 0x00, 0x06, 0x27, 0x08, 0x43, 0x18, 0x06,
    0x73, 0x1c, 0x82, 0x03, 0x06, 0x47, 0x95, 0x84, 0x22, 0x05, 0x0e, 0x0c, 0x71, 0x00, 0x04, 0x41,
    0x24, 0x00, 0x06, 0x43, 0x94, 0x44, 0x22, 0x06, 0x02, 0x84, 0x24, 0x08, 0x05, 0xc2, 0x30, 0x15,
    0x00, 0x06, 0x02, 0x48, 0x03, 0x26, 0x05, 0x02, 0x8c, 0xe8, 0x00, 0x07, 0x4d, 0x14, 0x26, 0xc6,
    0x03, 0x05, 0x40, 0x88, 0x22, 0x00, 0x05, 0xa2, 0xa4, 0x00, 0x00, 0x06, 0x02, 0x0c, 0x84, 0x1c,
    0x05, 0x01, 0x9c, 0x70, 0x00, 0x05, 0x3a, 0x01, 0xe1, 0x00, 0x04, 0x10, 0x15, 0x08, 0x07, 0x14,
    0x8c, 0x90, 0x04, 0x00, 0x06, 0xe6, 0x9c, 0x04, 0x0e, 0x08, 0x11, 0x9c, 0x25, 0x0c, 0x04, 0x07,
    0x02, 0xe8, 0x04, 0x4e, 0x00, 0x07, 0x27, 0x0c, 0x11, 0x80, 0x00, 0x06, 0xa7, 0x09, 0x43, 0x18,
    0x06, 0xa7, 0x09, 0x43, 0x18, 0x08, 0x4d, 0x14, 0x38, 0x20, 0x72, 0x06, 0x2d, 0x41, 0x64, 0x16,
    0x06, 0x6d, 0x08, 0x40, 0x02, 0x07, 0x4d, 0x94, 0x98, 0x56, 0x00, 0x07, 0x4d, 0x14, 0x88, 0xc0,
    0x03, 0x05, 0xad, 0x18, 0x12, 0x00, 0x04, 0x2a, 0x84, 0x06, 0x05, 0x0d, 0x8d, 0x05, 0x00, 0x07,
    0x4d, 0x18, 0x39, 0x96, 0x03, 0x07, 0x4d, 0x94, 0x67, 0x0e, 0x00, 0x06, 0x0d, 0x81, 0x71, 0x00,
    0x06, 0x0d, 0x94, 0x86, 0x00, 0x07, 0xab, 0xbc, 0x36, 0x88, 0x03, 0x06, 0x80, 0x94, 0xc4, 0x14,
    0x04, 0x04, 0x0c, 0x01, 0x07, 0x83, 0x94, 0xa0, 0x80, 0x00, 0x07, 0x86, 0x9c, 0x00, 0x46, 0x04,
    0x04, 0x86, 0x84, 0x02, 0x08, 0x83, 0xb8, 0xa0, 0x0c, 0x61, 0x06, 0x24, 0x3d, 0x08, 0x04, 0x06,
    0x83, 0xb8, 0x39, 0x1c, 0x04, 0x24, 0x21, 0x04, 0x06, 0xc7, 0x10, 0x86, 0x00, 0x0a, 0x89, 0x44,
    0x20, 0x4e, 0x18, 0x24, 0x02, 0x06, 0xcf, 0x1d, 0x80, 0x28, 0x05, 0x2f, 0x1d, 0xb3, 0x00, 0x04,
    0xaf, 0x9c, 0x00, 0x05, 0x6f, 0xd8, 0x22, 0x00, 0x06, 0xcf, 0x90, 0x14, 0x00, 0x05, 0xcf, 0x30,
    0x15, 0x00, 0x07, 0x0f, 0x9c, 0x33, 0x18, 0x00, 0x04, 0xa7, 0x3c, 0x00, 0x06, 0x0f, 0x04, 0x55,
    0x22, 0x04, 0x88, 0x85, 0x07, 0x04, 0xaf, 0x08, 0x00, 0x04, 0x85, 0x20, 0x07, 0x06, 0x03, 0xbd,
    0x72, 0x02, 0x05, 0x68, 0x04, 0x20, 0x00, 0x05, 0x03, 0x15, 0xc2, 0x00, 0x05, 0x68, 0x08, 0x06,
    0x00, 0x05, 0xc8, 0x30, 0x15, 0x00, 0x06, 0x0a, 0x0c, 0x14, 0x14, 0x05, 0x08, 0x0c, 0x09, 0x00,
    0x04, 0x03, 0x9d, 0x02, 0x05, 0x0b, 0x8d, 0x73, 0x00, 0x05, 0x08, 0x48, 0x80, 0x00, 0x04, 0xc8,
    0x54, 0x00, 0x07, 0x3a, 0x99, 0x55, 0x91, 0x03, 0x06, 0x6b, 0x20, 0x04, 0x04, 0x04, 0xb3, 0x88,
    0x0a, 0x04, 0x95, 0x94, 0x09, 0x04, 0x76, 0xc8, 0x01, 0x04, 0xd5, 0x90, 0x08, 0x05, 0x4b, 0x81,
    0x55, 0x01, 0x04, 0x15, 0x80, 0x06, 0x04, 0x6f, 0x54, 0x00, 0x03, 0x15, 0x38, 0x06, 0xab, 0x10,
    0x6a, 0x18, 0x08, 0x3a, 0x81, 0x13, 0x4c, 0x21, 0x05, 0x25, 0x28, 0x20, 0x00, 0x04, 0x53, 0x01,
    0x02, 0x06, 0xe6, 0xb5, 0x22, 0x02, 0x04, 0x36, 0x9d, 0x00, 0x05, 0x40, 0x02, 0xe1, 0x00, 0x05,
    0x2c, 0x81, 0x73, 0x00, 0x05, 0x4c, 0x80, 0x11, 0x00, 0x05, 0x4c, 0x94, 0xd4, 0x00, 0x07, 0x0c,
    0x10, 0x20, 0x06, 0x02, 0x06, 0xcc, 0x48, 0x43, 0x18, 0x06, 0xc2, 0x30, 0x15, 0x0e, 0x05, 0x10,
    0xb0, 0x41, 0x00, 0x06, 0x0c, 0x0d, 0xb2, 0x00, 0x0c, 0x5b, 0x0c, 0x3a, 0xc8, 0xc8, 0x7d, 0xc0,
    0x03, 0x07, 0x5b, 0x0c, 0x3a, 0xc8, 0x00, 0x05, 0x83, 0x0d, 0x43, 0x00, 0x05, 0xb4, 0x88, 0xe0,
    0x00, 0x05, 0xb4, 0x24, 0x12, 0x01, 0x08, 0xa7, 0xd0, 0x30, 0x87, 0x00, 0x0b, 0x86, 0xd0, 0x22,
    0xde, 0x08, 0xa6, 0x10, 0x06, 0xd4, 0x10, 0x06, 0x04, 0x05, 0xd4, 0x88, 0x13, 0x00, 0x04, 0x41,
    0x01, 0x02, 0x04, 0x14, 0x00, 0x04, 0x05, 0x83, 0x06, 0x20, 0x00, 0x05, 0x74, 0xa0, 0x03, 0x00,
    0x05, 0x74, 0x18, 0x74, 0x00, 0x04, 0x54, 0x94, 0x07, 0x07, 0x03, 0x09, 0x30, 0xa2, 0x03, 0x08,
    0x4d, 0x94, 0x98, 0x56, 0x38, 0x05, 0x41, 0x01, 0x23, 0x00, 0x05, 0x30, 0x19, 0x14, 0x01, 0x06,
    0x31, 0x09, 0x43, 0x18, 0x04, 0x41, 0x0d, 0x02, 0x04, 0x41, 0x81, 0x07, 0x05, 0xa1, 0xc4, 0xe1,
    0x00, 0x04, 0x71, 0x84, 0x01, 0x06, 0x6a, 0x44, 0x82, 0x03, 0x06, 0xd1, 0x44, 0x82, 0x03, 0x06,
    0xad, 0x20, 0xb3, 0x1c, 0x07, 0x2b, 0x09, 0x01, 0x48, 0x00, 0x06, 0x63, 0x89, 0x72, 0x0e, 0x08,
    0xab, 0x90, 0x60, 0x48, 0x02, 0x07, 0x4d, 0x14, 0x0b, 0x56, 0x00, 0x05, 0x0b, 0x99, 0x55, 0x01,
    0x08, 0x02, 0x1c, 0x30, 0xc4, 0x52, 0x07, 0x07, 0x08, 0x69, 0x16, 0x00, 0x08, 0x63, 0x85, 0x34,
    0x10, 0x72, 0x05, 0xab, 0x90, 0x13, 0x00, 0x08, 0xab, 0x24, 0x14, 0x09, 0x0e, 0x05, 0xab, 0x24,
    0x14, 0x01, 0x04, 0xb0, 0x44, 0x07, 0x08, 0x30, 0x1d, 0x43, 0xc0, 0x39, 0x05, 0x50, 0x80, 0x51,
    0x01, 0x06, 0x10, 0xac, 0xf2, 0x00, 0x07, 0x10, 0x84, 0x09, 0x00, 0x01, 0x05, 0x10, 0x18, 0xc2,
    0x00, 0x06, 0x10, 0x28, 0x43, 0x22, 0x04, 0x10, 0x00, 0x02, 0x07, 0xb0, 0x14, 0x04, 0x06, 0x01,
    0x0d, 0x05, 0x1e, 0x20, 0xe4, 0x80, 0x06, 0x99, 0xe0, 0x00, 0x05, 0x03, 0x96, 0x14, 0x00
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

int chord_transition(int state, uint16_t keycode) {
    switch (state) {
                // z
                case -221:
                    if (keycode == KC_SPC) return 65;
                    if (keycode == KC_COMMA) return 60;
                    if (keycode == KC_DOT) return 55;
                    if (keycode == KC_A) return 49;
                    if (keycode == KC_E) return 44;
                    if (keycode == KC_H) return 34;
                    if (keycode == KC_J) return 27;
                    if (keycode == KC_O) return 23;
                    if (keycode == KC_R) return 17;
                    if (keycode == KC_U) return 9;
                    if (keycode == KC_Y) return 0;
                    break;
                // x
                case -208:
                    if (keycode == KC_SPC) return 147;
                    if (keycode == KC_COMMA) return 134;
                    if (keycode == KC_DOT) return 129;
                    if (keycode == KC_A) return 123;
                    if (keycode == KC_E) return 117;
                    if (keycode == KC_H) return 112;
                    if (keycode == KC_I) return 106;
                    if (keycode == KC_J) return 99;
                    if (keycode == KC_O) return 89;
                    if (keycode == KC_R) return 83;
                    if (keycode == KC_U) return 78;
                    if (keycode == KC_Y) return 71;
                    break;
                // w
                case -196:
                    if (keycode == KC_SPC) return 204;
                    if (keycode == KC_COMMA) return 198;
                    if (keycode == KC_DOT) return 193;
                    if (keycode == KC_A) return 189;
                    if (keycode == KC_H) return 184;
                    if (keycode == KC_I) return 180;
                    if (keycode == KC_J) return 175;
                    if (keycode == KC_O) return 169;
                    if (keycode == KC_R) return 164;
                    if (keycode == KC_U) return 158;
                    if (keycode == KC_Y) return 153;
                    break;
                // v
                case -183:
                    if (keycode == KC_SPC) return 269;
                    if (keycode == KC_COMMA) return 263;
                    if (keycode == KC_DOT) return 259;
                    if (keycode == KC_A) return 252;
                    if (keycode == KC_E) return 248;
                    if (keycode == KC_H) return 242;
                    if (keycode == KC_I) return 236;
                    if (keycode == KC_J) return 231;
                    if (keycode == KC_O) return 227;
                    if (keycode == KC_R) return 222;
                    if (keycode == KC_U) return 217;
                    if (keycode == KC_Y) return 209;
                    break;
                // t
                case -170:
                    if (keycode == KC_SPC) return 325;
                    if (keycode == KC_COMMA) return 320;
                    if (keycode == KC_DOT) return 316;
                    if (keycode == KC_A) return 312;
                    if (keycode == KC_E) return 307;
                    if (keycode == KC_H) return 303;
                    if (keycode == KC_I) return 299;
                    if (keycode == KC_J) return 293;
                    if (keycode == KC_O) return 287;
                    if (keycode == KC_R) return 282;
                    if (keycode == KC_U) return 277;
                    if (keycode == KC_Y) return 273;
                    break;
                // s
                case -157:
                    if (keycode == KC_SPC) return 388;
                    if (keycode == KC_COMMA) return 383;
                    if (keycode == KC_DOT) return 378;
                    if (keycode == KC_A) return 374;
                    if (keycode == KC_E) return 369;
                    if (keycode == KC_H) return 364;
                    if (keycode == KC_I) return 358;
                    if (keycode == KC_J) return 352;
                    if (keycode == KC_O) return 347;
                    if (keycode == KC_R) return 341;
                    if (keycode == KC_U) return 335;
                    if (keycode == KC_Y) return 330;
                    break;
                // r
                case -145:
                    if (keycode == KC_SPC) return 443;
                    if (keycode == KC_COMMA) return 438;
                    if (keycode == KC_DOT) return 433;
                    if (keycode == KC_A) return 427;
                    if (keycode == KC_E) return 422;
                    if (keycode == KC_H) return 417;
                    if (keycode == KC_I) return 412;
                    if (keycode == KC_J) return 407;
                    if (keycode == KC_O) return 402;
                    if (keycode == KC_U) return 398;
                    if (keycode == KC_Y) return 393;
                    break;
                // q
                case -134:
                    if (keycode == KC_SPC) return 496;
                    if (keycode == KC_COMMA) return 491;
                    if (keycode == KC_A) return 485;
                    if (keycode == KC_E) return 479;
                    if (keycode == KC_H) return 473;
                    if (keycode == KC_I) return 468;
                    if (keycode == KC_J) return 462;
                    if (keycode == KC_O) return 458;
                    if (keycode == KC_U) return 453;
                    if (keycode == KC_Y) return 448;
                    break;
                // p
                case -121:
                    if (keycode == KC_SPC) return 560;
                    if (keycode == KC_COMMA) return 555;
                    if (keycode == KC_DOT) return 549;
                    if (keycode == KC_A) return 543;
                    if (keycode == KC_E) return 538;
                    if (keycode == KC_H) return 534;
                    if (keycode == KC_I) return 529;
                    if (keycode == KC_J) return 523;
                    if (keycode == KC_O) return 517;
                    if (keycode == KC_R) return 512;
                    if (keycode == KC_U) return 507;
                    if (keycode == KC_Y) return 501;
                    break;
                // n
                case -108:
                    if (keycode == KC_SPC) return 621;
                    if (keycode == KC_COMMA) return 616;
                    if (keycode == KC_DOT) return 612;
                    if (keycode == KC_A) return 607;
                    if (keycode == KC_E) return 602;
                    if (keycode == KC_H) return 596;
                    if (keycode == KC_I) return 592;
                    if (keycode == KC_J) return 586;
                    if (keycode == KC_O) return 580;
                    if (keycode == KC_R) return 576;
                    if (keycode == KC_U) return 571;
                    if (keycode == KC_Y) return 565;
                    break;
                // m
                case -96:
                    if (keycode == KC_SPC) return 677;
                    if (keycode == KC_COMMA) return 673;
                    if (keycode == KC_DOT) return 668;
                    if (keycode == KC_A) return 664;
                    if (keycode == KC_E) return 658;
                    if (keycode == KC_H) return 653;
                    if (keycode == KC_I) return 648;
                    if (keycode == KC_J) return 643;
                    if (keycode == KC_O) return 639;
                    if (keycode == KC_U) return 634;
                    if (keycode == KC_Y) return 629;
                    break;
                // l
                case -83:
                    if (keycode == KC_SPC) return 734;
                    if (keycode == KC_COMMA) return 729;
                    if (keycode == KC_DOT) return 724;
                    if (keycode == KC_A) return 720;
                    if (keycode == KC_E) return 715;
                    if (keycode == KC_H) return 710;
                    if (keycode == KC_I) return 705;
                    if (keycode == KC_J) return 700;
                    if (keycode == KC_O) return 695;
                    if (keycode == KC_R) return 690;
                    if (keycode == KC_U) return 685;
                    if (keycode == KC_Y) return 681;
                    break;
                // k
                case -70:
                    if (keycode == KC_SPC) return 786;
                    if (keycode == KC_COMMA) return 781;
                    if (keycode == KC_DOT) return 778;
                    if (keycode == KC_A) return 774;
                    if (keycode == KC_E) return 770;
                    if (keycode == KC_H) return 765;
                    if (keycode == KC_I) return 761;
                    if (keycode == KC_J) return 757;
                    if (keycode == KC_O) return 753;
                    if (keycode == KC_R) return 749;
                    if (keycode == KC_U) return 744;
                    if (keycode == KC_Y) return 738;
                    break;
                // j
                case -65:
                    if (keycode == KC_SPC) return 806;
                    if (keycode == KC_A) return 801;
                    if (keycode == KC_E) return 797;
                    if (keycode == KC_O) return 792;
                    break;
                // g
                case -52:
                    if (keycode == KC_SPC) return 871;
                    if (keycode == KC_COMMA) return 865;
                    if (keycode == KC_DOT) return 856;
                    if (keycode == KC_A) return 851;
                    if (keycode == KC_E) return 846;
                    if (keycode == KC_H) return 841;
                    if (keycode == KC_I) return 836;
                    if (keycode == KC_J) return 830;
                    if (keycode == KC_O) return 825;
                    if (keycode == KC_R) return 820;
                    if (keycode == KC_U) return 815;
                    if (keycode == KC_Y) return 810;
                    break;
                // f
                case -39:
                    if (keycode == KC_SPC) return 933;
                    if (keycode == KC_COMMA) return 928;
                    if (keycode == KC_DOT) return 923;
                    if (keycode == KC_A) return 918;
                    if (keycode == KC_E) return 914;
                    if (keycode == KC_H) return 910;
                    if (keycode == KC_I) return 905;
                    if (keycode == KC_J) return 900;
                    if (keycode == KC_O) return 892;
                    if (keycode == KC_R) return 886;
                    if (keycode == KC_U) return 881;
                    if (keycode == KC_Y) return 876;
                    break;
                // d
                case -27:
                    if (keycode == KC_SPC) return 986;
                    if (keycode == KC_COMMA) return 981;
                    if (keycode == KC_DOT) return 977;
                    if (keycode == KC_A) return 972;
                    if (keycode == KC_E) return 968;
                    if (keycode == KC_H) return 964;
                    if (keycode == KC_I) return 959;
                    if (keycode == KC_J) return 954;
                    if (keycode == KC_R) return 949;
                    if (keycode == KC_U) return 943;
                    if (keycode == KC_Y) return 937;
                    break;
                // c
                case -14:
                    if (keycode == KC_SPC) return 1053;
                    if (keycode == KC_COMMA) return 1047;
                    if (keycode == KC_DOT) return 1042;
                    if (keycode == KC_A) return 1036;
                    if (keycode == KC_E) return 1030;
                    if (keycode == KC_H) return 1024;
                    if (keycode == KC_I) return 1019;
                    if (keycode == KC_J) return 1013;
                    if (keycode == KC_O) return 1007;
                    if (keycode == KC_R) return 1002;
                    if (keycode == KC_U) return 996;
                    if (keycode == KC_Y) return 991;
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return 1114;
                    if (keycode == KC_COMMA) return 1104;
                    if (keycode == KC_DOT) return 1098;
                    if (keycode == KC_A) return 1094;
                    if (keycode == KC_H) return 1089;
                    if (keycode == KC_I) return 1084;
                    if (keycode == KC_J) return 1078;
                    if (keycode == KC_O) return 1073;
                    if (keycode == KC_R) return 1068;
                    if (keycode == KC_U) return 1062;
                    if (keycode == KC_Y) return 1058;
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
                    if (keycode == KC_N) return -108;
                    if (keycode == KC_P) return -121;
                    if (keycode == KC_Q) return -134;
                    if (keycode == KC_R) return -145;
                    if (keycode == KC_S) return -157;
                    if (keycode == KC_T) return -170;
                    if (keycode == KC_V) return -183;
                    if (keycode == KC_W) return -196;
                    if (keycode == KC_X) return -208;
                    if (keycode == KC_Z) return -221;
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
    if (alternateLayer >= 0 && record->event.pressed) {
        int al = alternateLayer;
        alternateLayer = -1;
        if (layer == _BASE) {
            switch (al) {
            
            }
        }
    } else if (layer == _BASE && record->event.pressed) {
        switch (keycode) {
        
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
                    case KC_B: tap_code16(KC_L); return false;
                    case KC_C: tap_code16(KC_K); return false;
                    case KC_COMMA: SEND_STRING(" but "); return false;
                    case KC_D: SEND_STRING("oesn't"); return false;
                    case KC_DOT: tap_code16(KC_SLASH); return false;
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_ENT: SEND_STRING("the "); return false;
                    case KC_EQUAL: tap_code16(KC_RABK); return false;
                    case KC_EXLM: tap_code16(KC_EQUAL); return false;
                    case KC_F: tap_code16(KC_F); return false;
                    case KC_G: tap_code16(KC_N); return false;
                    case KC_H: tap_code16(KC_Y); return false;
                    case KC_I: tap_code16(KC_QUOTE); return false;
                    case KC_J: SEND_STRING("ust"); return false;
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_P); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_MINUS: tap_code16(KC_RABK); return false;
                    case KC_N: tap_code16(KC_G); return false;
                    case KC_O: tap_code16(KC_E); return false;
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_R: tap_code16(KC_K); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: SEND_STRING("the "); return false;
                    case KC_T: SEND_STRING("ion"); return false;
                    case KC_TAB: SEND_STRING("the "); return false;
                    case KC_TILD: tap_code16(KC_SLASH); return false;
                    case KC_V: SEND_STRING("er"); return false;
                    case KC_W: tap_code16(KC_N); return false;
                    case KC_X: tap_code16(KC_P); return false;
                    case KC_Z: SEND_STRING("eitlinger"); return false;
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): SEND_STRING("oesn't"); return false;
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_F): tap_code16(KC_F); return false;
                    case S(KC_G): tap_code16(KC_N); return false;
                    case S(KC_H): tap_code16(KC_Y); return false;
                    case S(KC_I): tap_code16(KC_QUOTE); return false;
                    case S(KC_J): SEND_STRING("ust"); return false;
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_P); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): tap_code16(KC_G); return false;
                    case S(KC_O): tap_code16(KC_E); return false;
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_R): tap_code16(KC_K); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): SEND_STRING("ion"); return false;
                    case S(KC_V): SEND_STRING("er"); return false;
                    case S(KC_W): tap_code16(KC_N); return false;
                    case S(KC_X): tap_code16(KC_P); return false;
                    case S(KC_Z): SEND_STRING("eitlinger"); return false;
                }
                return false;
            case MAGIC_B:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_U); return false;
                    case KC_B: SEND_STRING("ecause"); return false;
                    case KC_C: tap_code16(KC_P); return false;
                    case KC_COMMA: SEND_STRING(" and "); return false;
                    case KC_D: SEND_STRING("oes"); return false;
                    case KC_DOT: SEND_STRING("./"); return false;
                    case KC_ENT: SEND_STRING("and "); return false;
                    case KC_F: SEND_STRING("or"); return false;
                    case KC_G: tap_code16(KC_K); return false;
                    case KC_H: SEND_STRING("ey"); return false;
                    case KC_I: SEND_STRING("'ve"); return false;
                    case KC_K: SEND_STRING("now"); return false;
                    case KC_L: tap_code16(KC_M); return false;
                    case KC_M: SEND_STRING("ent"); return false;
                    case KC_N: tap_code16(KC_K); return false;
                    case KC_P: tap_code16(KC_S); return false;
                    case KC_S: SEND_STRING("ion"); return false;
                    case KC_SPC: tap_code16(KC_BSPC); SEND_STRING(". "); add_oneshot_mods(MOD_BIT(KC_LSFT)); return false;
                    case KC_T: SEND_STRING("ing"); return false;
                    case KC_TAB: SEND_STRING("and "); return false;
                    case KC_U: tap_code16(KC_A); return false;
                    case KC_V: SEND_STRING("en"); return false;
                    case KC_W: tap_code16(KC_S); return false;
                    case KC_X: tap_code16(KC_C); return false;
                    case S(KC_A): tap_code16(KC_U); return false;
                    case S(KC_B): SEND_STRING("ecause"); return false;
                    case S(KC_C): tap_code16(KC_P); return false;
                    case S(KC_D): SEND_STRING("oes"); return false;
                    case S(KC_F): SEND_STRING("or"); return false;
                    case S(KC_G): tap_code16(KC_K); return false;
                    case S(KC_H): SEND_STRING("ey"); return false;
                    case S(KC_I): SEND_STRING("'ve"); return false;
                    case S(KC_K): SEND_STRING("now"); return false;
                    case S(KC_L): tap_code16(KC_M); return false;
                    case S(KC_M): SEND_STRING("ent"); return false;
                    case S(KC_N): tap_code16(KC_K); return false;
                    case S(KC_P): tap_code16(KC_S); return false;
                    case S(KC_S): SEND_STRING("ion"); return false;
                    case S(KC_T): SEND_STRING("ing"); return false;
                    case S(KC_U): tap_code16(KC_A); return false;
                    case S(KC_V): SEND_STRING("en"); return false;
                    case S(KC_W): tap_code16(KC_S); return false;
                    case S(KC_X): tap_code16(KC_C); return false;
                }
                return false;
            case MAGIC_C:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_U); return false;
                    case KC_B: tap_code16(KC_L); return false;
                    case KC_C: tap_code16(KC_K); return false;
                    case KC_D: SEND_STRING("on't"); return false;
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_G: tap_code16(KC_L); return false;
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_V); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_N: SEND_STRING("ly"); return false;
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: SEND_STRING("the "); return false;
                    case KC_T: SEND_STRING("ion"); return false;
                    case S(KC_A): tap_code16(KC_U); return false;
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): SEND_STRING("on't"); return false;
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_G): tap_code16(KC_L); return false;
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_V); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): SEND_STRING("ly"); return false;
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): SEND_STRING("ion"); return false;
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
