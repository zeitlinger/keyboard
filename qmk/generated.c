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

// Chord string decoder lookup table (5-bit codes -> characters)
static const char chord_char_lookup[] = {
    'e', 't', 'r', 'a', 'n', 'o', 'i', 's', 'l', 'u', 'h', 'c', 'g', 'p', 'y', 'm', 'b', 'd', 'v', 'w', 'f', 'k', 'j', 'x', '\'', ' ', 'q', 'G', 'L', 'z', 'O', 'T'
};

// Global buffer containing all 5-bit packed chord strings
static const uint8_t chord_data[] = {
    0x0c, 0x5b, 0x0c, 0x3a, 0xc8, 0xc8, 0x7c, 0xc0, 0x03, 0x0b, 0xa7, 0x09, 0x43, 0x58, 0x86, 0xa5,
    0x04, 0x08, 0xa2, 0x20, 0x14, 0xcd, 0x02, 0x09, 0x76, 0xc8, 0x31, 0x18, 0x20, 0x01, 0x0e, 0xa7,
    0x09, 0x43, 0x58, 0x3e, 0x61, 0x88, 0x00, 0x04, 0x06, 0xcc, 0x04, 0x95, 0x20, 0x08, 0x45, 0xb0,
    0x41, 0x4c, 0x07, 0x05, 0xe3, 0x38, 0xb2, 0x00, 0x05, 0xe7, 0x19, 0x04, 0x00, 0x07, 0x02, 0x0c,
    0x64, 0x3a, 0x00, 0x09, 0x01, 0x20, 0xf0, 0x40, 0x10, 0x0e, 0x06, 0x63, 0x85, 0x34, 0x10, 0x08,
    0x02, 0x9c, 0x92, 0xc4, 0x02, 0x0d, 0xbe, 0x01, 0xf2, 0x01, 0x02, 0x0f, 0x04, 0xe1, 0x00, 0x09,
    0xe0, 0x2e, 0xd0, 0x82, 0x29, 0x04, 0x08, 0xe0, 0x9a, 0x13, 0x0c, 0x61, 0x05, 0x2a, 0x84, 0x76,
    0x00, 0x07, 0xe0, 0x82, 0x95, 0x02, 0x00, 0x07, 0xe0, 0x8e, 0xd7, 0x10, 0x00, 0x06, 0xe0, 0xb6,
    0x22, 0x02, 0x12, 0x11, 0x2c, 0x34, 0xc4, 0x08, 0x46, 0x82, 0xbc, 0x0a, 0xa1, 0x86, 0x01, 0x07,
    0xab, 0x90, 0x00, 0x6e, 0x00, 0x05, 0xb3, 0x08, 0xe1, 0x00, 0x08, 0x86, 0x04, 0x20, 0xc8, 0x40,
    0x05, 0x53, 0x01, 0x01, 0x00, 0x07, 0xd3, 0x04, 0x55, 0x52, 0x00, 0x05, 0x53, 0x14, 0xc2, 0x00,
    0x04, 0xd3, 0x04, 0x05, 0x05, 0x53, 0x99, 0xa5, 0x00, 0x04, 0x73, 0xa0, 0x0a, 0x05, 0x63, 0x0e,
    0x13, 0x00, 0x08, 0xb3, 0x24, 0x14, 0x09, 0x0e, 0x05, 0xb3, 0x24, 0x14, 0x01, 0x0a, 0x40, 0x02,
    0xe1, 0x82, 0x32, 0x84, 0x01, 0x05, 0x72, 0xa0, 0x04, 0x00, 0x05, 0x04, 0x48, 0x20, 0x00, 0x04,
    0x45, 0x02, 0x01, 0x06, 0xa4, 0x04, 0xb3, 0x00, 0x08, 0x07, 0x08, 0x69, 0x16, 0x38, 0x07, 0x12,
    0x88, 0x63, 0x0a, 0x01, 0x04, 0x12, 0x08, 0x07, 0x09, 0x43, 0x0e, 0x83, 0x06, 0x44, 0x00, 0x04,
    0xb2, 0x98, 0x08, 0x07, 0xab, 0x90, 0x20, 0x0c, 0x04, 0x04, 0x6a, 0x48, 0x00, 0x04, 0x41, 0x01,
    0x07, 0x06, 0x41, 0x95, 0xc4, 0x14, 0x05, 0x41, 0x01, 0x01, 0x00, 0x07, 0x41, 0x95, 0xc4, 0x54,
    0x00, 0x07, 0x41, 0x89, 0x92, 0x98, 0x02, 0x04, 0xc1, 0x3c, 0x00, 0x04, 0x41, 0x99, 0x03, 0x05,
    0x41, 0x81, 0x03, 0x00, 0x04, 0x41, 0x8d, 0x00, 0x04, 0xc1, 0x35, 0x00, 0x06, 0x01, 0x90, 0x41,
    0x02, 0x05, 0x41, 0x19, 0x52, 0x01, 0x06, 0xc7, 0x9d, 0x00, 0x1e, 0x07, 0x27, 0xb5, 0x56, 0x44,
    0x00, 0x08, 0x27, 0x89, 0x26, 0xcc, 0x01, 0x06, 0x07, 0x95, 0x89, 0x1c, 0x07, 0x27, 0x41, 0x0b,
    0x56, 0x00, 0x07, 0xa7, 0x3c, 0x50, 0x08, 0x00, 0x05, 0x47, 0x0d, 0x01, 0x00, 0x06, 0x07, 0x0c,
    0xb1, 0x14, 0x04, 0x67, 0x3c, 0x00, 0x06, 0x27, 0x08, 0x43, 0x18, 0x06, 0x73, 0x1c, 0x82, 0x03,
    0x06, 0x47, 0x95, 0x84, 0x22, 0x05, 0x0e, 0x0c, 0x71, 0x00, 0x04, 0x41, 0x24, 0x00, 0x06, 0x43,
    0x94, 0x44, 0x22, 0x06, 0x02, 0x84, 0x24, 0x08, 0x05, 0xc2, 0x30, 0x15, 0x00, 0x06, 0x02, 0x48,
    0x03, 0x26, 0x05, 0x02, 0x8c, 0xe8, 0x00, 0x07, 0x4d, 0x14, 0x26, 0xc6, 0x03, 0x05, 0x40, 0x88,
    0x22, 0x00, 0x05, 0xa2, 0xa4, 0x00, 0x00, 0x06, 0x02, 0x0c, 0x84, 0x1c, 0x05, 0x01, 0x9c, 0x70,
    0x00, 0x05, 0x3a, 0x01, 0xe1, 0x00, 0x04, 0x10, 0x15, 0x08, 0x07, 0x14, 0x8c, 0x90, 0x04, 0x00,
    0x06, 0xe6, 0x9c, 0x04, 0x0e, 0x08, 0x11, 0x9c, 0x25, 0x0c, 0x04, 0x07, 0x02, 0xe8, 0x04, 0x4e,
    0x00, 0x07, 0x27, 0x0c, 0x11, 0x80, 0x00, 0x06, 0xa7, 0x09, 0x43, 0x18, 0x06, 0xa7, 0x09, 0x43,
    0x18, 0x08, 0x4d, 0x14, 0x38, 0x20, 0x72, 0x06, 0x2d, 0x41, 0x64, 0x16, 0x06, 0x6d, 0x08, 0x40,
    0x02, 0x07, 0x4d, 0x94, 0x98, 0x56, 0x00, 0x07, 0x4d, 0x14, 0x88, 0xc0, 0x03, 0x05, 0xad, 0x18,
    0x12, 0x00, 0x04, 0x2a, 0x84, 0x06, 0x05, 0x0d, 0x8d, 0x05, 0x00, 0x07, 0x4d, 0x18, 0x39, 0x96,
    0x03, 0x07, 0x4d, 0x94, 0x67, 0x0e, 0x00, 0x06, 0x0d, 0x81, 0x71, 0x00, 0x06, 0x0d, 0x94, 0x86,
    0x00, 0x07, 0xab, 0xbc, 0x36, 0x88, 0x03, 0x06, 0x80, 0x94, 0xc4, 0x14, 0x04, 0x04, 0x0c, 0x01,
    0x07, 0x83, 0x94, 0xa0, 0x80, 0x00, 0x07, 0x86, 0x9c, 0x00, 0x46, 0x04, 0x04, 0x86, 0x84, 0x02,
    0x08, 0x83, 0xb8, 0xa0, 0x0c, 0x61, 0x06, 0x24, 0x3d, 0x08, 0x04, 0x06, 0x83, 0xb8, 0x39, 0x1c,
    0x04, 0x24, 0x21, 0x04, 0x06, 0xc7, 0x10, 0x86, 0x00, 0x0a, 0x89, 0x44, 0x20, 0x4e, 0x18, 0x24,
    0x02, 0x06, 0xcf, 0x1d, 0x80, 0x28, 0x05, 0x2f, 0x1d, 0xb3, 0x00, 0x05, 0x6f, 0xd8, 0x22, 0x00,
    0x06, 0xcf, 0x90, 0x14, 0x00, 0x05, 0xcf, 0x30, 0x15, 0x00, 0x07, 0x0f, 0x9c, 0x33, 0x18, 0x00,
    0x04, 0xa7, 0x3c, 0x00, 0x06, 0x0f, 0x04, 0x55, 0x22, 0x04, 0x88, 0x85, 0x07, 0x04, 0xaf, 0x08,
    0x00, 0x04, 0x85, 0x20, 0x07, 0x06, 0x03, 0xbd, 0x72, 0x02, 0x05, 0x68, 0x04, 0x20, 0x00, 0x05,
    0x03, 0x15, 0xc2, 0x00, 0x05, 0x68, 0x08, 0x06, 0x00, 0x05, 0xc8, 0x30, 0x15, 0x00, 0x06, 0x0a,
    0x0c, 0x14, 0x14, 0x05, 0x08, 0x0c, 0x09, 0x00, 0x04, 0x03, 0x9d, 0x02, 0x05, 0x0b, 0x8d, 0x73,
    0x00, 0x05, 0x08, 0x48, 0x80, 0x00, 0x04, 0xc8, 0x54, 0x00, 0x07, 0x3a, 0x99, 0x55, 0x91, 0x03,
    0x06, 0x6b, 0x20, 0x04, 0x04, 0x04, 0xb3, 0x88, 0x0a, 0x04, 0x95, 0x94, 0x09, 0x04, 0x76, 0xc8,
    0x01, 0x04, 0xd5, 0x90, 0x08, 0x05, 0x4b, 0x81, 0x55, 0x01, 0x04, 0x15, 0x80, 0x06, 0x04, 0x6f,
    0x54, 0x00, 0x03, 0x15, 0x38, 0x06, 0xab, 0x10, 0x6a, 0x18, 0x08, 0x3a, 0x81, 0x13, 0x4c, 0x21,
    0x05, 0x25, 0x28, 0x20, 0x00, 0x04, 0x53, 0x01, 0x02, 0x06, 0xe6, 0xb5, 0x22, 0x02, 0x04, 0x36,
    0x9d, 0x00, 0x05, 0x40, 0x02, 0xe1, 0x00, 0x05, 0x2c, 0x81, 0x73, 0x00, 0x05, 0x4c, 0x80, 0x11,
    0x00, 0x05, 0x4c, 0x94, 0xd4, 0x00, 0x07, 0x0c, 0x10, 0x20, 0x06, 0x02, 0x06, 0xcc, 0x48, 0x43,
    0x18, 0x06, 0xc2, 0x30, 0x15, 0x0e, 0x05, 0x10, 0xb0, 0x41, 0x00, 0x06, 0x0c, 0x0d, 0xb2, 0x00,
    0x0c, 0x5b, 0x0c, 0x3a, 0xc8, 0xc8, 0x7c, 0xc0, 0x03, 0x07, 0x5b, 0x0c, 0x3a, 0xc8, 0x00, 0x05,
    0x83, 0x0d, 0x43, 0x00, 0x05, 0xb4, 0x88, 0xe0, 0x00, 0x05, 0xb4, 0x24, 0x12, 0x01, 0x08, 0xa7,
    0xd0, 0x30, 0x87, 0x00, 0x0b, 0x86, 0xd0, 0x22, 0xde, 0x08, 0xa6, 0x10, 0x06, 0xd4, 0x10, 0x06,
    0x04, 0x05, 0xd4, 0x88, 0x13, 0x00, 0x04, 0x41, 0x01, 0x02, 0x04, 0x14, 0x00, 0x04, 0x05, 0x83,
    0x06, 0x20, 0x00, 0x05, 0x74, 0xa0, 0x03, 0x00, 0x05, 0x74, 0x18, 0x74, 0x00, 0x04, 0x54, 0x94,
    0x07, 0x07, 0x03, 0x09, 0x30, 0xa2, 0x03, 0x08, 0x4d, 0x94, 0x98, 0x56, 0x38, 0x05, 0x41, 0x01,
    0x23, 0x00, 0x05, 0x30, 0x19, 0x14, 0x01, 0x06, 0x31, 0x09, 0x43, 0x18, 0x04, 0x41, 0x0d, 0x02,
    0x04, 0x41, 0x81, 0x07, 0x05, 0xa1, 0xc4, 0xe1, 0x00, 0x04, 0x71, 0x84, 0x01, 0x06, 0x6a, 0x44,
    0x82, 0x03, 0x06, 0xd1, 0x44, 0x82, 0x03, 0x06, 0xad, 0x20, 0xb3, 0x1c, 0x07, 0x2b, 0x09, 0x01,
    0x48, 0x00, 0x06, 0x63, 0x89, 0x72, 0x0e, 0x08, 0xab, 0x90, 0x60, 0x48, 0x02, 0x07, 0x4d, 0x14,
    0x0b, 0x56, 0x00, 0x05, 0x0b, 0x99, 0x55, 0x01, 0x08, 0x02, 0x1c, 0x30, 0xc4, 0x52, 0x07, 0x07,
    0x08, 0x69, 0x16, 0x00, 0x08, 0x63, 0x85, 0x34, 0x10, 0x72, 0x05, 0xab, 0x90, 0x13, 0x00, 0x08,
    0xab, 0x24, 0x14, 0x09, 0x0e, 0x05, 0xab, 0x24, 0x14, 0x01, 0x04, 0xb0, 0x44, 0x07, 0x08, 0x30,
    0x1d, 0x43, 0xc0, 0x39, 0x05, 0x50, 0x80, 0x51, 0x01, 0x06, 0x10, 0xac, 0xf2, 0x00, 0x07, 0x10,
    0x84, 0x09, 0x00, 0x01, 0x05, 0x10, 0x18, 0xc2, 0x00, 0x06, 0x10, 0x28, 0x43, 0x22, 0x04, 0x10,
    0x00, 0x02, 0x07, 0xb0, 0x14, 0x04, 0x06, 0x01, 0x0d, 0x05, 0x1e, 0x20, 0xe4, 0x80, 0x06, 0x99,
    0xe0, 0x00, 0x05, 0x03, 0x96, 0x14, 0x00
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
                case -220:
                    if (keycode == KC_SPC) return 61;
                    if (keycode == KC_COMMA) return 56;
                    if (keycode == KC_DOT) return 51;
                    if (keycode == KC_A) return 45;
                    if (keycode == KC_E) return 40;
                    if (keycode == KC_H) return 30;
                    if (keycode == KC_J) return 23;
                    if (keycode == KC_R) return 17;
                    if (keycode == KC_U) return 9;
                    if (keycode == KC_Y) return 0;
                    break;
                // x
                case -207:
                    if (keycode == KC_SPC) return 143;
                    if (keycode == KC_COMMA) return 130;
                    if (keycode == KC_DOT) return 125;
                    if (keycode == KC_A) return 119;
                    if (keycode == KC_E) return 113;
                    if (keycode == KC_H) return 108;
                    if (keycode == KC_I) return 102;
                    if (keycode == KC_J) return 95;
                    if (keycode == KC_O) return 85;
                    if (keycode == KC_R) return 79;
                    if (keycode == KC_U) return 74;
                    if (keycode == KC_Y) return 67;
                    break;
                // w
                case -195:
                    if (keycode == KC_SPC) return 200;
                    if (keycode == KC_COMMA) return 194;
                    if (keycode == KC_DOT) return 189;
                    if (keycode == KC_A) return 185;
                    if (keycode == KC_H) return 180;
                    if (keycode == KC_I) return 176;
                    if (keycode == KC_J) return 171;
                    if (keycode == KC_O) return 165;
                    if (keycode == KC_R) return 160;
                    if (keycode == KC_U) return 154;
                    if (keycode == KC_Y) return 149;
                    break;
                // v
                case -182:
                    if (keycode == KC_SPC) return 265;
                    if (keycode == KC_COMMA) return 259;
                    if (keycode == KC_DOT) return 255;
                    if (keycode == KC_A) return 248;
                    if (keycode == KC_E) return 244;
                    if (keycode == KC_H) return 238;
                    if (keycode == KC_I) return 232;
                    if (keycode == KC_J) return 227;
                    if (keycode == KC_O) return 223;
                    if (keycode == KC_R) return 218;
                    if (keycode == KC_U) return 213;
                    if (keycode == KC_Y) return 205;
                    break;
                // t
                case -169:
                    if (keycode == KC_SPC) return 321;
                    if (keycode == KC_COMMA) return 316;
                    if (keycode == KC_DOT) return 312;
                    if (keycode == KC_A) return 308;
                    if (keycode == KC_E) return 303;
                    if (keycode == KC_H) return 299;
                    if (keycode == KC_I) return 295;
                    if (keycode == KC_J) return 289;
                    if (keycode == KC_O) return 283;
                    if (keycode == KC_R) return 278;
                    if (keycode == KC_U) return 273;
                    if (keycode == KC_Y) return 269;
                    break;
                // s
                case -156:
                    if (keycode == KC_SPC) return 384;
                    if (keycode == KC_COMMA) return 379;
                    if (keycode == KC_DOT) return 374;
                    if (keycode == KC_A) return 370;
                    if (keycode == KC_E) return 365;
                    if (keycode == KC_H) return 360;
                    if (keycode == KC_I) return 354;
                    if (keycode == KC_J) return 348;
                    if (keycode == KC_O) return 343;
                    if (keycode == KC_R) return 337;
                    if (keycode == KC_U) return 331;
                    if (keycode == KC_Y) return 326;
                    break;
                // r
                case -144:
                    if (keycode == KC_SPC) return 439;
                    if (keycode == KC_COMMA) return 434;
                    if (keycode == KC_DOT) return 429;
                    if (keycode == KC_A) return 423;
                    if (keycode == KC_E) return 418;
                    if (keycode == KC_H) return 413;
                    if (keycode == KC_I) return 408;
                    if (keycode == KC_J) return 403;
                    if (keycode == KC_O) return 398;
                    if (keycode == KC_U) return 394;
                    if (keycode == KC_Y) return 389;
                    break;
                // q
                case -133:
                    if (keycode == KC_SPC) return 492;
                    if (keycode == KC_COMMA) return 487;
                    if (keycode == KC_A) return 481;
                    if (keycode == KC_E) return 475;
                    if (keycode == KC_H) return 469;
                    if (keycode == KC_I) return 464;
                    if (keycode == KC_J) return 458;
                    if (keycode == KC_O) return 454;
                    if (keycode == KC_U) return 449;
                    if (keycode == KC_Y) return 444;
                    break;
                // p
                case -120:
                    if (keycode == KC_SPC) return 556;
                    if (keycode == KC_COMMA) return 551;
                    if (keycode == KC_DOT) return 545;
                    if (keycode == KC_A) return 539;
                    if (keycode == KC_E) return 534;
                    if (keycode == KC_H) return 530;
                    if (keycode == KC_I) return 525;
                    if (keycode == KC_J) return 519;
                    if (keycode == KC_O) return 513;
                    if (keycode == KC_R) return 508;
                    if (keycode == KC_U) return 503;
                    if (keycode == KC_Y) return 497;
                    break;
                // n
                case -107:
                    if (keycode == KC_SPC) return 617;
                    if (keycode == KC_COMMA) return 612;
                    if (keycode == KC_DOT) return 608;
                    if (keycode == KC_A) return 603;
                    if (keycode == KC_E) return 598;
                    if (keycode == KC_H) return 592;
                    if (keycode == KC_I) return 588;
                    if (keycode == KC_J) return 582;
                    if (keycode == KC_O) return 576;
                    if (keycode == KC_R) return 572;
                    if (keycode == KC_U) return 567;
                    if (keycode == KC_Y) return 561;
                    break;
                // m
                case -96:
                    if (keycode == KC_SPC) return 669;
                    if (keycode == KC_COMMA) return 665;
                    if (keycode == KC_DOT) return 660;
                    if (keycode == KC_A) return 656;
                    if (keycode == KC_E) return 650;
                    if (keycode == KC_H) return 645;
                    if (keycode == KC_I) return 640;
                    if (keycode == KC_J) return 635;
                    if (keycode == KC_U) return 630;
                    if (keycode == KC_Y) return 625;
                    break;
                // l
                case -83:
                    if (keycode == KC_SPC) return 726;
                    if (keycode == KC_COMMA) return 721;
                    if (keycode == KC_DOT) return 716;
                    if (keycode == KC_A) return 712;
                    if (keycode == KC_E) return 707;
                    if (keycode == KC_H) return 702;
                    if (keycode == KC_I) return 697;
                    if (keycode == KC_J) return 692;
                    if (keycode == KC_O) return 687;
                    if (keycode == KC_R) return 682;
                    if (keycode == KC_U) return 677;
                    if (keycode == KC_Y) return 673;
                    break;
                // k
                case -70:
                    if (keycode == KC_SPC) return 778;
                    if (keycode == KC_COMMA) return 773;
                    if (keycode == KC_DOT) return 770;
                    if (keycode == KC_A) return 766;
                    if (keycode == KC_E) return 762;
                    if (keycode == KC_H) return 757;
                    if (keycode == KC_I) return 753;
                    if (keycode == KC_J) return 749;
                    if (keycode == KC_O) return 745;
                    if (keycode == KC_R) return 741;
                    if (keycode == KC_U) return 736;
                    if (keycode == KC_Y) return 730;
                    break;
                // j
                case -65:
                    if (keycode == KC_SPC) return 798;
                    if (keycode == KC_A) return 793;
                    if (keycode == KC_E) return 789;
                    if (keycode == KC_O) return 784;
                    break;
                // g
                case -52:
                    if (keycode == KC_SPC) return 863;
                    if (keycode == KC_COMMA) return 857;
                    if (keycode == KC_DOT) return 848;
                    if (keycode == KC_A) return 843;
                    if (keycode == KC_E) return 838;
                    if (keycode == KC_H) return 833;
                    if (keycode == KC_I) return 828;
                    if (keycode == KC_J) return 822;
                    if (keycode == KC_O) return 817;
                    if (keycode == KC_R) return 812;
                    if (keycode == KC_U) return 807;
                    if (keycode == KC_Y) return 802;
                    break;
                // f
                case -39:
                    if (keycode == KC_SPC) return 925;
                    if (keycode == KC_COMMA) return 920;
                    if (keycode == KC_DOT) return 915;
                    if (keycode == KC_A) return 910;
                    if (keycode == KC_E) return 906;
                    if (keycode == KC_H) return 902;
                    if (keycode == KC_I) return 897;
                    if (keycode == KC_J) return 892;
                    if (keycode == KC_O) return 884;
                    if (keycode == KC_R) return 878;
                    if (keycode == KC_U) return 873;
                    if (keycode == KC_Y) return 868;
                    break;
                // d
                case -27:
                    if (keycode == KC_SPC) return 978;
                    if (keycode == KC_COMMA) return 973;
                    if (keycode == KC_DOT) return 969;
                    if (keycode == KC_A) return 964;
                    if (keycode == KC_E) return 960;
                    if (keycode == KC_H) return 956;
                    if (keycode == KC_I) return 951;
                    if (keycode == KC_J) return 946;
                    if (keycode == KC_R) return 941;
                    if (keycode == KC_U) return 935;
                    if (keycode == KC_Y) return 929;
                    break;
                // c
                case -14:
                    if (keycode == KC_SPC) return 1045;
                    if (keycode == KC_COMMA) return 1039;
                    if (keycode == KC_DOT) return 1034;
                    if (keycode == KC_A) return 1028;
                    if (keycode == KC_E) return 1022;
                    if (keycode == KC_H) return 1016;
                    if (keycode == KC_I) return 1011;
                    if (keycode == KC_J) return 1005;
                    if (keycode == KC_O) return 999;
                    if (keycode == KC_R) return 994;
                    if (keycode == KC_U) return 988;
                    if (keycode == KC_Y) return 983;
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return 1106;
                    if (keycode == KC_COMMA) return 1096;
                    if (keycode == KC_DOT) return 1090;
                    if (keycode == KC_A) return 1086;
                    if (keycode == KC_H) return 1081;
                    if (keycode == KC_I) return 1076;
                    if (keycode == KC_J) return 1070;
                    if (keycode == KC_O) return 1065;
                    if (keycode == KC_R) return 1060;
                    if (keycode == KC_U) return 1054;
                    if (keycode == KC_Y) return 1050;
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
