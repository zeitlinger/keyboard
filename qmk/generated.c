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
    'e', 'r', 't', 'a', 'n', 'i', 'o', 's', 'l', 'u', 'c', 'g', 'h', 'p', 'y', 'd', 'b', 'm', 'v', 'w', 'f', 'k', 'j', 'x', '\'', ' ', 'q', 'G', 'z', 'L', 'O', 'T'
};

// Global buffer containing all 5-bit packed chord strings
static const uint8_t chord_data[] = {
    0x05, 0xe3, 0x38, 0xa2, 0x00, 0x0b, 0xa7, 0x85, 0x42, 0x56, 0x86, 0xc6, 0x08, 0x08, 0xc1, 0x20,
    0xf4, 0x8a, 0x02, 0x09, 0x76, 0xc8, 0x31, 0x16, 0x20, 0x02, 0x0e, 0xa7, 0x85, 0x42, 0x56, 0x3e,
    0x62, 0x04, 0x01, 0x02, 0x06, 0xab, 0x08, 0x96, 0x20, 0x08, 0x26, 0xac, 0x41, 0x0a, 0x07, 0x05,
    0x27, 0x16, 0x04, 0x00, 0x07, 0x01, 0x0c, 0x54, 0x38, 0x00, 0x09, 0x02, 0x20, 0x10, 0x81, 0x08,
    0x0e, 0x06, 0x43, 0x89, 0x34, 0x10, 0x08, 0x01, 0x1c, 0x93, 0x82, 0x02, 0x0d, 0xbe, 0x01, 0xf2,
    0x01, 0x02, 0x11, 0x88, 0xe0, 0x00, 0x09, 0xe0, 0x2a, 0xd0, 0x44, 0x31, 0x04, 0x08, 0xe0, 0x96,
    0x23, 0x0a, 0x59, 0x05, 0x4c, 0x88, 0x76, 0x00, 0x07, 0xe0, 0x02, 0x95, 0x04, 0x00, 0x07, 0xe0,
    0x8e, 0xd8, 0x10, 0x00, 0x06, 0xe0, 0x36, 0x13, 0x04, 0x12, 0x0f, 0x28, 0x34, 0xc2, 0x10, 0x45,
    0x82, 0xac, 0x0c, 0xa1, 0x65, 0x01, 0x07, 0xca, 0x10, 0x01, 0xae, 0x00, 0x05, 0xd3, 0x84, 0xe0,
    0x00, 0x08, 0x85, 0x08, 0x10, 0xc8, 0x40, 0x05, 0x93, 0x81, 0x00, 0x00, 0x07, 0xb3, 0x08, 0x66,
    0x92, 0x00, 0x05, 0x33, 0x18, 0xb2, 0x00, 0x06, 0xb3, 0x90, 0x67, 0x26, 0x05, 0x93, 0x15, 0xc5,
    0x00, 0x04, 0x73, 0xa0, 0x0a, 0x05, 0x63, 0x8e, 0x22, 0x00, 0x08, 0xd3, 0x24, 0xf4, 0x08, 0x16,
    0x05, 0xd3, 0x24, 0xf4, 0x00, 0x0a, 0x40, 0x82, 0xe0, 0x04, 0x2b, 0x64, 0x01, 0x05, 0x72, 0xa0,
    0x04, 0x00, 0x05, 0x04, 0x48, 0x10, 0x00, 0x04, 0xa8, 0x54, 0x00, 0x08, 0x07, 0x04, 0x59, 0x14,
    0x38, 0x07, 0x12, 0x84, 0x53, 0x0c, 0x01, 0x09, 0x43, 0x8e, 0x82, 0x06, 0x44, 0x00, 0x07, 0xca,
    0x10, 0x11, 0x0a, 0x04, 0x04, 0x6c, 0x48, 0x00, 0x09, 0x82, 0x0d, 0x52, 0xb3, 0x33, 0x09, 0x06,
    0x82, 0x99, 0xb4, 0x18, 0x05, 0x82, 0x81, 0x00, 0x00, 0x07, 0x82, 0x99, 0xb4, 0x98, 0x00, 0x07,
    0x82, 0x05, 0x93, 0x16, 0x03, 0x06, 0x82, 0x0d, 0x52, 0x0f, 0x06, 0xc4, 0x88, 0xa2, 0x00, 0x07,
    0xca, 0x10, 0x31, 0x94, 0x00, 0x06, 0x02, 0x90, 0x41, 0x04, 0x04, 0xc2, 0x35, 0x00, 0x05, 0x82,
    0x15, 0x52, 0x01, 0x06, 0xc7, 0x1d, 0x01, 0x22, 0x07, 0x27, 0xb5, 0x66, 0x82, 0x00, 0x08, 0x27,
    0x85, 0x16, 0xca, 0x01, 0x06, 0x07, 0x99, 0x89, 0x1c, 0x07, 0x27, 0x41, 0x0b, 0x94, 0x00, 0x07,
    0xa7, 0x20, 0x40, 0x14, 0x00, 0x05, 0x87, 0x8d, 0x00, 0x00, 0x06, 0x07, 0x8c, 0xa0, 0x18, 0x04,
    0x67, 0x44, 0x00, 0x06, 0x47, 0x84, 0x42, 0x16, 0x06, 0x73, 0x1c, 0x82, 0x05, 0x06, 0x87, 0x99,
    0x84, 0x1e, 0x05, 0x0e, 0x8c, 0x70, 0x00, 0x04, 0x22, 0x24, 0x00, 0x06, 0x23, 0x98, 0x44, 0x1e,
    0x06, 0x01, 0x88, 0x14, 0x08, 0x05, 0xa1, 0x2c, 0x26, 0x00, 0x06, 0x01, 0xc8, 0x02, 0x26, 0x05,
    0x01, 0x8c, 0xe7, 0x00, 0x07, 0x2d, 0x98, 0x15, 0x46, 0x04, 0x05, 0x20, 0x04, 0x13, 0x00, 0x05,
    0xc1, 0x24, 0x01, 0x00, 0x06, 0x01, 0x0c, 0x84, 0x1c, 0x05, 0x02, 0x1c, 0x71, 0x00, 0x05, 0x3a,
    0x81, 0xe0, 0x00, 0x04, 0x10, 0x19, 0x08, 0x07, 0x14, 0x0c, 0x91, 0x02, 0x00, 0x06, 0xe5, 0x9c,
    0x04, 0x0e, 0x08, 0x0f, 0x1c, 0x15, 0x0a, 0x04, 0x07, 0x01, 0xe8, 0x04, 0x8e, 0x00, 0x07, 0x47,
    0x8c, 0x20, 0x40, 0x00, 0x06, 0xa7, 0x85, 0x42, 0x16, 0x06, 0xa7, 0x85, 0x42, 0x16, 0x08, 0x2d,
    0x18, 0x38, 0x20, 0x72, 0x06, 0x2d, 0x41, 0x54, 0x14, 0x06, 0x6d, 0x04, 0x40, 0x04, 0x07, 0x2d,
    0x98, 0x97, 0x94, 0x00, 0x07, 0x2d, 0x18, 0x88, 0x40, 0x04, 0x05, 0xcd, 0x14, 0x22, 0x00, 0x04,
    0x4c, 0x88, 0x06, 0x05, 0x0d, 0x0d, 0x05, 0x00, 0x07, 0x2d, 0x14, 0x39, 0x94, 0x03, 0x07, 0x2d,
    0x98, 0x58, 0x0e, 0x00, 0x06, 0x0d, 0x81, 0x71, 0x00, 0x06, 0x0d, 0x98, 0x86, 0x00, 0x07, 0xca,
    0xc4, 0x36, 0x88, 0x03, 0x06, 0x80, 0x98, 0xb4, 0x18, 0x04, 0x04, 0x8c, 0x00, 0x07, 0x83, 0x18,
    0xc1, 0x40, 0x00, 0x07, 0x85, 0x1c, 0x01, 0xc6, 0x03, 0x0a, 0x89, 0x14, 0x09, 0xc2, 0x29, 0xc2,
    0x01, 0x08, 0x83, 0x38, 0xc1, 0x0a, 0x59, 0x06, 0x24, 0x45, 0x08, 0x02, 0x06, 0x83, 0xb8, 0x39,
    0x1c, 0x04, 0x24, 0x21, 0x04, 0x06, 0xa7, 0x90, 0x85, 0x00, 0x0a, 0x89, 0x3c, 0x10, 0x8e, 0x18,
    0xe4, 0x01, 0x06, 0xd1, 0x1d, 0x80, 0x28, 0x05, 0x31, 0x9d, 0xa2, 0x00, 0x05, 0x71, 0x58, 0x13,
    0x00, 0x06, 0xb1, 0x90, 0x24, 0x00, 0x05, 0xb1, 0x2c, 0x26, 0x00, 0x07, 0x11, 0x9c, 0x33, 0x16,
    0x00, 0x07, 0xc7, 0x44, 0x60, 0x08, 0x00, 0x06, 0x11, 0x08, 0x66, 0x1e, 0x04, 0x68, 0x89, 0x08,
    0x04, 0xd1, 0x04, 0x00, 0x06, 0x03, 0xcd, 0xe1, 0x0e, 0x06, 0x03, 0x45, 0x73, 0x04, 0x05, 0x68,
    0x08, 0x10, 0x00, 0x05, 0x03, 0x19, 0xb2, 0x00, 0x05, 0x68, 0x84, 0x05, 0x00, 0x05, 0xa8, 0x2c,
    0x26, 0x00, 0x06, 0x0c, 0x0c, 0x24, 0x18, 0x05, 0x08, 0x0c, 0x09, 0x00, 0x05, 0x68, 0xa4, 0xc5,
    0x00, 0x05, 0x0a, 0x8d, 0x73, 0x00, 0x05, 0x08, 0x48, 0x80, 0x00, 0x06, 0x08, 0x90, 0x25, 0x18,
    0x07, 0x3a, 0x15, 0x55, 0x91, 0x03, 0x06, 0x6a, 0x20, 0x04, 0x02, 0x04, 0xd3, 0x84, 0x0a, 0x04,
    0x95, 0x98, 0x09, 0x04, 0x36, 0x1d, 0x01, 0x04, 0xb5, 0x90, 0x07, 0x05, 0x8a, 0x01, 0x55, 0x01,
    0x04, 0x15, 0x80, 0x06, 0x04, 0x71, 0x54, 0x00, 0x03, 0x15, 0x38, 0x06, 0xca, 0x10, 0x5a, 0x16,
    0x08, 0x3a, 0x81, 0x23, 0x8a, 0x21, 0x06, 0x25, 0x36, 0x13, 0x04, 0x04, 0x76, 0xc8, 0x01, 0x05,
    0x40, 0x82, 0xe0, 0x00, 0x05, 0x2b, 0x81, 0x73, 0x00, 0x05, 0x2b, 0x80, 0x21, 0x00, 0x05, 0x2b,
    0x98, 0xd4, 0x00, 0x07, 0x0b, 0x10, 0x10, 0x06, 0x02, 0x06, 0xab, 0xc8, 0x42, 0x16, 0x06, 0xa1,
    0x2c, 0x26, 0x0e, 0x05, 0x10, 0xac, 0x41, 0x00, 0x06, 0x0b, 0x0d, 0xa2, 0x00, 0x0c, 0x3b, 0x0c,
    0x3a, 0xc8, 0xc8, 0x7d, 0xc0, 0x03, 0x07, 0x3b, 0x0c, 0x3a, 0xc8, 0x00, 0x05, 0x63, 0x8d, 0x42,
    0x00, 0x05, 0xd4, 0x04, 0xe1, 0x00, 0x05, 0xd4, 0x24, 0xf2, 0x00, 0x08, 0xc7, 0x50, 0x31, 0x47,
    0x00, 0x0b, 0x85, 0x50, 0x13, 0xe2, 0x10, 0xc5, 0x10, 0x05, 0xb4, 0x84, 0x23, 0x00, 0x06, 0xb4,
    0x90, 0x05, 0x02, 0x05, 0xb4, 0x50, 0xc1, 0x00, 0x04, 0x14, 0x00, 0x04, 0x06, 0x74, 0xc4, 0x82,
    0x1c, 0x05, 0x74, 0xa0, 0x03, 0x00, 0x05, 0x74, 0x14, 0x74, 0x00, 0x04, 0x34, 0x98, 0x08, 0x07,
    0x03, 0x05, 0x30, 0x9e, 0x03, 0x08, 0x2d, 0x98, 0x97, 0x94, 0x38, 0x05, 0x82, 0x81, 0x12, 0x00,
    0x05, 0x30, 0x15, 0xf4, 0x00, 0x06, 0x2f, 0x85, 0x42, 0x16, 0x05, 0x82, 0x95, 0xf0, 0x00, 0x05,
    0xb2, 0x3c, 0x60, 0x00, 0x05, 0xc2, 0xbc, 0xe1, 0x00, 0x04, 0x6f, 0x88, 0x01, 0x06, 0x6c, 0x3c,
    0x82, 0x05, 0x06, 0xaf, 0x3c, 0x82, 0x05, 0x06, 0xcd, 0xa0, 0xa2, 0x1c, 0x07, 0x2a, 0x85, 0x00,
    0x88, 0x00, 0x06, 0x43, 0x05, 0x73, 0x0e, 0x08, 0xca, 0x10, 0x51, 0x48, 0x02, 0x07, 0x2d, 0x18,
    0x0b, 0x94, 0x00, 0x05, 0x0a, 0x15, 0x55, 0x01, 0x08, 0x01, 0x1c, 0x30, 0x82, 0x62, 0x07, 0x07,
    0x04, 0x59, 0x14, 0x00, 0x08, 0x43, 0x89, 0x34, 0x10, 0x72, 0x05, 0xca, 0x90, 0x23, 0x00, 0x08,
    0xca, 0x24, 0xf4, 0x08, 0x16, 0x05, 0xca, 0x24, 0xf4, 0x00, 0x04, 0xd0, 0x3c, 0x07, 0x08, 0x30,
    0x9d, 0x42, 0xc0, 0x39, 0x05, 0x30, 0x80, 0x51, 0x01, 0x06, 0x10, 0x28, 0x13, 0x01, 0x07, 0x10,
    0x88, 0x09, 0x00, 0x01, 0x05, 0x10, 0x14, 0xb2, 0x00, 0x06, 0x10, 0xb0, 0x42, 0x1e, 0x05, 0x03,
    0x9a, 0x24, 0x00, 0x07, 0xd0, 0x18, 0x04, 0x06, 0x01, 0x0d, 0x06, 0x1e, 0x10, 0xe4, 0x80, 0x05,
    0x15, 0xe1, 0x00, 0x04, 0x10, 0x00, 0x02
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
                case -214:
                    if (keycode == KC_SPC) return 52;
                    if (keycode == KC_COMMA) return 47;
                    if (keycode == KC_A) return 41;
                    if (keycode == KC_E) return 36;
                    if (keycode == KC_H) return 26;
                    if (keycode == KC_J) return 19;
                    if (keycode == KC_R) return 13;
                    if (keycode == KC_U) return 5;
                    if (keycode == KC_Y) return 0;
                    break;
                // x
                case -201:
                    if (keycode == KC_SPC) return 134;
                    if (keycode == KC_COMMA) return 121;
                    if (keycode == KC_DOT) return 116;
                    if (keycode == KC_A) return 110;
                    if (keycode == KC_E) return 104;
                    if (keycode == KC_H) return 99;
                    if (keycode == KC_I) return 93;
                    if (keycode == KC_J) return 86;
                    if (keycode == KC_O) return 76;
                    if (keycode == KC_R) return 70;
                    if (keycode == KC_U) return 65;
                    if (keycode == KC_Y) return 58;
                    break;
                // w
                case -189:
                    if (keycode == KC_SPC) return 192;
                    if (keycode == KC_COMMA) return 186;
                    if (keycode == KC_DOT) return 181;
                    if (keycode == KC_A) return 177;
                    if (keycode == KC_H) return 172;
                    if (keycode == KC_I) return 167;
                    if (keycode == KC_J) return 162;
                    if (keycode == KC_O) return 156;
                    if (keycode == KC_R) return 151;
                    if (keycode == KC_U) return 145;
                    if (keycode == KC_Y) return 140;
                    break;
                // v
                case -179:
                    if (keycode == KC_SPC) return 244;
                    if (keycode == KC_COMMA) return 238;
                    if (keycode == KC_A) return 231;
                    if (keycode == KC_H) return 225;
                    if (keycode == KC_I) return 219;
                    if (keycode == KC_J) return 215;
                    if (keycode == KC_R) return 210;
                    if (keycode == KC_U) return 205;
                    if (keycode == KC_Y) return 197;
                    break;
                // t
                case -167:
                    if (keycode == KC_SPC) return 302;
                    if (keycode == KC_COMMA) return 298;
                    if (keycode == KC_DOT) return 293;
                    if (keycode == KC_A) return 287;
                    if (keycode == KC_E) return 282;
                    if (keycode == KC_H) return 277;
                    if (keycode == KC_J) return 271;
                    if (keycode == KC_O) return 265;
                    if (keycode == KC_R) return 260;
                    if (keycode == KC_U) return 255;
                    if (keycode == KC_Y) return 248;
                    break;
                // s
                case -154:
                    if (keycode == KC_SPC) return 365;
                    if (keycode == KC_COMMA) return 360;
                    if (keycode == KC_DOT) return 355;
                    if (keycode == KC_A) return 351;
                    if (keycode == KC_E) return 346;
                    if (keycode == KC_H) return 341;
                    if (keycode == KC_I) return 335;
                    if (keycode == KC_J) return 329;
                    if (keycode == KC_O) return 324;
                    if (keycode == KC_R) return 318;
                    if (keycode == KC_U) return 312;
                    if (keycode == KC_Y) return 307;
                    break;
                // r
                case -142:
                    if (keycode == KC_SPC) return 420;
                    if (keycode == KC_COMMA) return 415;
                    if (keycode == KC_DOT) return 410;
                    if (keycode == KC_A) return 404;
                    if (keycode == KC_E) return 399;
                    if (keycode == KC_H) return 394;
                    if (keycode == KC_I) return 389;
                    if (keycode == KC_J) return 384;
                    if (keycode == KC_O) return 379;
                    if (keycode == KC_U) return 375;
                    if (keycode == KC_Y) return 370;
                    break;
                // q
                case -131:
                    if (keycode == KC_SPC) return 473;
                    if (keycode == KC_COMMA) return 468;
                    if (keycode == KC_A) return 462;
                    if (keycode == KC_E) return 456;
                    if (keycode == KC_H) return 450;
                    if (keycode == KC_I) return 445;
                    if (keycode == KC_J) return 439;
                    if (keycode == KC_O) return 435;
                    if (keycode == KC_U) return 430;
                    if (keycode == KC_Y) return 425;
                    break;
                // p
                case -118:
                    if (keycode == KC_SPC) return 537;
                    if (keycode == KC_COMMA) return 532;
                    if (keycode == KC_DOT) return 526;
                    if (keycode == KC_A) return 520;
                    if (keycode == KC_E) return 515;
                    if (keycode == KC_H) return 511;
                    if (keycode == KC_I) return 506;
                    if (keycode == KC_J) return 500;
                    if (keycode == KC_O) return 494;
                    if (keycode == KC_R) return 489;
                    if (keycode == KC_U) return 484;
                    if (keycode == KC_Y) return 478;
                    break;
                // n
                case -105:
                    if (keycode == KC_SPC) return 602;
                    if (keycode == KC_COMMA) return 597;
                    if (keycode == KC_DOT) return 593;
                    if (keycode == KC_A) return 588;
                    if (keycode == KC_E) return 583;
                    if (keycode == KC_H) return 577;
                    if (keycode == KC_I) return 569;
                    if (keycode == KC_J) return 563;
                    if (keycode == KC_O) return 557;
                    if (keycode == KC_R) return 553;
                    if (keycode == KC_U) return 548;
                    if (keycode == KC_Y) return 542;
                    break;
                // m
                case -94:
                    if (keycode == KC_SPC) return 656;
                    if (keycode == KC_COMMA) return 652;
                    if (keycode == KC_DOT) return 647;
                    if (keycode == KC_A) return 641;
                    if (keycode == KC_E) return 635;
                    if (keycode == KC_H) return 630;
                    if (keycode == KC_I) return 625;
                    if (keycode == KC_J) return 620;
                    if (keycode == KC_U) return 615;
                    if (keycode == KC_Y) return 610;
                    break;
                // l
                case -81:
                    if (keycode == KC_SPC) return 715;
                    if (keycode == KC_COMMA) return 710;
                    if (keycode == KC_DOT) return 705;
                    if (keycode == KC_A) return 700;
                    if (keycode == KC_E) return 695;
                    if (keycode == KC_H) return 690;
                    if (keycode == KC_I) return 685;
                    if (keycode == KC_J) return 680;
                    if (keycode == KC_O) return 675;
                    if (keycode == KC_R) return 670;
                    if (keycode == KC_U) return 665;
                    if (keycode == KC_Y) return 660;
                    break;
                // k
                case -68:
                    if (keycode == KC_SPC) return 768;
                    if (keycode == KC_COMMA) return 763;
                    if (keycode == KC_DOT) return 760;
                    if (keycode == KC_A) return 756;
                    if (keycode == KC_E) return 752;
                    if (keycode == KC_H) return 747;
                    if (keycode == KC_I) return 743;
                    if (keycode == KC_J) return 739;
                    if (keycode == KC_O) return 735;
                    if (keycode == KC_R) return 731;
                    if (keycode == KC_U) return 726;
                    if (keycode == KC_Y) return 720;
                    break;
                // j
                case -65:
                    if (keycode == KC_SPC) return 779;
                    if (keycode == KC_A) return 774;
                    break;
                // g
                case -52:
                    if (keycode == KC_SPC) return 844;
                    if (keycode == KC_COMMA) return 838;
                    if (keycode == KC_DOT) return 829;
                    if (keycode == KC_A) return 824;
                    if (keycode == KC_E) return 819;
                    if (keycode == KC_H) return 814;
                    if (keycode == KC_I) return 809;
                    if (keycode == KC_J) return 803;
                    if (keycode == KC_O) return 798;
                    if (keycode == KC_R) return 793;
                    if (keycode == KC_U) return 788;
                    if (keycode == KC_Y) return 783;
                    break;
                // f
                case -39:
                    if (keycode == KC_SPC) return 907;
                    if (keycode == KC_COMMA) return 902;
                    if (keycode == KC_DOT) return 897;
                    if (keycode == KC_A) return 892;
                    if (keycode == KC_E) return 888;
                    if (keycode == KC_H) return 883;
                    if (keycode == KC_I) return 878;
                    if (keycode == KC_J) return 873;
                    if (keycode == KC_O) return 865;
                    if (keycode == KC_R) return 859;
                    if (keycode == KC_U) return 854;
                    if (keycode == KC_Y) return 849;
                    break;
                // d
                case -27:
                    if (keycode == KC_SPC) return 962;
                    if (keycode == KC_COMMA) return 957;
                    if (keycode == KC_DOT) return 953;
                    if (keycode == KC_A) return 948;
                    if (keycode == KC_E) return 943;
                    if (keycode == KC_H) return 938;
                    if (keycode == KC_I) return 933;
                    if (keycode == KC_J) return 928;
                    if (keycode == KC_R) return 923;
                    if (keycode == KC_U) return 917;
                    if (keycode == KC_Y) return 911;
                    break;
                // c
                case -14:
                    if (keycode == KC_SPC) return 1029;
                    if (keycode == KC_COMMA) return 1023;
                    if (keycode == KC_DOT) return 1018;
                    if (keycode == KC_A) return 1012;
                    if (keycode == KC_E) return 1006;
                    if (keycode == KC_H) return 1000;
                    if (keycode == KC_I) return 995;
                    if (keycode == KC_J) return 989;
                    if (keycode == KC_O) return 983;
                    if (keycode == KC_R) return 978;
                    if (keycode == KC_U) return 972;
                    if (keycode == KC_Y) return 967;
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return 1091;
                    if (keycode == KC_COMMA) return 1081;
                    if (keycode == KC_DOT) return 1075;
                    if (keycode == KC_A) return 1070;
                    if (keycode == KC_H) return 1065;
                    if (keycode == KC_I) return 1060;
                    if (keycode == KC_J) return 1054;
                    if (keycode == KC_O) return 1049;
                    if (keycode == KC_R) return 1044;
                    if (keycode == KC_U) return 1038;
                    if (keycode == KC_Y) return 1034;
                    break;
                case -1:
                    if (keycode == KC_B) return -2;
                    if (keycode == KC_C) return -14;
                    if (keycode == KC_D) return -27;
                    if (keycode == KC_F) return -39;
                    if (keycode == KC_G) return -52;
                    if (keycode == KC_J) return -65;
                    if (keycode == KC_K) return -68;
                    if (keycode == KC_L) return -81;
                    if (keycode == KC_M) return -94;
                    if (keycode == KC_N) return -105;
                    if (keycode == KC_P) return -118;
                    if (keycode == KC_Q) return -131;
                    if (keycode == KC_R) return -142;
                    if (keycode == KC_S) return -154;
                    if (keycode == KC_T) return -167;
                    if (keycode == KC_V) return -179;
                    if (keycode == KC_W) return -189;
                    if (keycode == KC_X) return -201;
                    if (keycode == KC_Z) return -214;
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
