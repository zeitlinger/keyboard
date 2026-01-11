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
    'e', 'r', 't', 'a', 'n', 'o', 'i', 's', 'l', 'u', 'c', 'g', 'h', 'y', 'p', 'd', 'm', 'b', 'v', 'w', 'f', 'k', 'j', '\'', 'x', ' ', 'z', 'q', 'G', 'L', 'O', 'T'
};

// Global buffer containing all 5-bit packed chord strings
static const uint8_t chord_data[] = {
    0x05, 0x07, 0x1a, 0x04, 0x00, 0x08, 0xa1, 0x20, 0xf4, 0x8c, 0x02, 0x09, 0x76, 0xc8, 0x31, 0x16,
    0x20, 0x02, 0x06, 0xcb, 0x08, 0x96, 0x22, 0x0b, 0xc7, 0x05, 0x43, 0x56, 0x8e, 0xa5, 0x08, 0x0e,
    0xc7, 0x05, 0x43, 0x56, 0x3e, 0x62, 0x04, 0x01, 0x02, 0x05, 0xe3, 0x34, 0xa2, 0x00, 0x04, 0xba,
    0x10, 0x00, 0x04, 0xc7, 0x68, 0x00, 0x04, 0x1a, 0x84, 0x02, 0x08, 0x25, 0xac, 0x41, 0x8c, 0x06,
    0x07, 0x01, 0x0c, 0x64, 0x34, 0x00, 0x12, 0x0f, 0x28, 0x34, 0xc2, 0x10, 0x46, 0x82, 0xac, 0x0a,
    0xa1, 0x66, 0x01, 0x08, 0x01, 0x9c, 0x92, 0x82, 0x02, 0x09, 0x02, 0x20, 0x00, 0x81, 0x08, 0x0d,
    0x0d, 0xde, 0x01, 0xf2, 0x01, 0x02, 0x10, 0x88, 0xd0, 0x00, 0x06, 0x43, 0x89, 0x34, 0x10, 0x05,
    0x4c, 0x08, 0x77, 0x00, 0x06, 0x00, 0xbb, 0x12, 0x04, 0x09, 0x00, 0x2b, 0xe0, 0x84, 0x29, 0x04,
    0x08, 0x00, 0x9b, 0x23, 0x0c, 0x59, 0x07, 0x00, 0x03, 0x95, 0x04, 0x00, 0x07, 0x00, 0x0f, 0xe8,
    0x10, 0x00, 0x07, 0xaa, 0x10, 0x01, 0xb0, 0x00, 0x08, 0x86, 0x08, 0x10, 0xc8, 0x40, 0x08, 0xb3,
    0x24, 0xf4, 0xc8, 0x15, 0x05, 0x63, 0x0e, 0x23, 0x00, 0x05, 0xb3, 0x84, 0xd0, 0x00, 0x05, 0x93,
    0x81, 0x00, 0x00, 0x07, 0xd3, 0x08, 0x56, 0x92, 0x00, 0x05, 0x33, 0x14, 0xb2, 0x00, 0x06, 0xd3,
    0x90, 0x57, 0x26, 0x05, 0x93, 0x19, 0xc5, 0x00, 0x04, 0x13, 0x04, 0x00, 0x04, 0x73, 0xa0, 0x0a,
    0x05, 0xb3, 0x24, 0xf4, 0x00, 0x07, 0xaa, 0x10, 0x11, 0x4c, 0x04, 0x04, 0xc8, 0x54, 0x00, 0x07,
    0x12, 0x84, 0x63, 0x0a, 0x01, 0x04, 0xb2, 0x98, 0x07, 0x0a, 0x40, 0x82, 0xd0, 0x04, 0x33, 0x64,
    0x01, 0x05, 0x72, 0xa0, 0x04, 0x00, 0x05, 0x04, 0x48, 0x10, 0x00, 0x04, 0x45, 0x82, 0x00, 0x08,
    0x07, 0x04, 0x69, 0x14, 0x38, 0x04, 0x12, 0x84, 0x06, 0x09, 0x43, 0x0e, 0x83, 0x46, 0x44, 0x00,
    0x04, 0x6c, 0x48, 0x00, 0x06, 0x02, 0x90, 0x41, 0x04, 0x04, 0xa2, 0x39, 0x00, 0x09, 0x82, 0x0d,
    0x52, 0x73, 0x2b, 0x09, 0x06, 0x82, 0x95, 0xb4, 0x18, 0x05, 0x82, 0x81, 0x00, 0x00, 0x07, 0x82,
    0x95, 0xb4, 0x98, 0x00, 0x07, 0x82, 0x85, 0x92, 0x16, 0x03, 0x04, 0xc2, 0x40, 0x00, 0x06, 0x82,
    0x0d, 0x52, 0x0f, 0x06, 0xa4, 0x08, 0xa3, 0x00, 0x07, 0xaa, 0x10, 0x31, 0x94, 0x00, 0x05, 0x82,
    0x19, 0x52, 0x01, 0x06, 0x73, 0x1c, 0x72, 0x05, 0x06, 0x47, 0x04, 0x43, 0x16, 0x06, 0xa7, 0x1d,
    0x01, 0x20, 0x07, 0x27, 0x39, 0x57, 0x82, 0x00, 0x08, 0x27, 0x05, 0x17, 0xcc, 0x01, 0x06, 0x07,
    0x95, 0x89, 0x1a, 0x07, 0x27, 0x45, 0x0b, 0x94, 0x00, 0x07, 0xc7, 0x20, 0x40, 0x14, 0x00, 0x05,
    0x87, 0x8d, 0x00, 0x00, 0x06, 0x07, 0x8c, 0xa0, 0x18, 0x04, 0x67, 0x40, 0x00, 0x06, 0x87, 0x95,
    0x84, 0x1e, 0x05, 0xa1, 0x24, 0x01, 0x00, 0x05, 0x20, 0x84, 0x12, 0x00, 0x05, 0x0d, 0x8c, 0x70,
    0x00, 0x04, 0x22, 0x24, 0x00, 0x06, 0x23, 0x94, 0x44, 0x1e, 0x06, 0x01, 0x88, 0x14, 0x08, 0x05,
    0xc1, 0x2c, 0x26, 0x00, 0x06, 0x01, 0x48, 0x03, 0x26, 0x05, 0x01, 0x8c, 0xd7, 0x00, 0x07, 0x2e,
    0x94, 0x15, 0x06, 0x04, 0x06, 0x01, 0x0c, 0x84, 0x1a, 0x05, 0x02, 0x1c, 0x71, 0x00, 0x07, 0x14,
    0x0c, 0x91, 0x02, 0x00, 0x08, 0x0f, 0x1c, 0x15, 0x4c, 0x04, 0x07, 0x01, 0xec, 0x04, 0x8e, 0x00,
    0x07, 0x47, 0x8c, 0x20, 0x40, 0x00, 0x06, 0xc7, 0x05, 0x43, 0x16, 0x04, 0x11, 0x95, 0x08, 0x06,
    0xe6, 0x9c, 0x04, 0x0e, 0x05, 0x3b, 0x81, 0xd0, 0x00, 0x06, 0xc7, 0x05, 0x43, 0x16, 0x06, 0x0e,
    0x81, 0x71, 0x00, 0x04, 0x4c, 0x08, 0x07, 0x07, 0x2e, 0x14, 0x68, 0x0e, 0x00, 0x08, 0x2e, 0x94,
    0x38, 0x22, 0x6a, 0x06, 0x2e, 0x45, 0x64, 0x14, 0x06, 0x6e, 0x04, 0x40, 0x04, 0x07, 0x2e, 0x94,
    0x97, 0x94, 0x00, 0x07, 0x2e, 0x94, 0x88, 0x00, 0x04, 0x05, 0xae, 0x18, 0x22, 0x00, 0x05, 0x0e,
    0x0d, 0x05, 0x00, 0x07, 0x2e, 0x18, 0x39, 0x54, 0x03, 0x06, 0x0e, 0x14, 0x87, 0x00, 0x06, 0xc7,
    0x90, 0x85, 0x00, 0x04, 0x24, 0x21, 0x04, 0x07, 0xaa, 0x40, 0x37, 0x48, 0x03, 0x06, 0x80, 0x94,
    0xb4, 0x18, 0x04, 0x04, 0x8c, 0x00, 0x07, 0x83, 0x14, 0xc1, 0x40, 0x00, 0x07, 0x86, 0x1c, 0x01,
    0xc6, 0x03, 0x0a, 0x89, 0x18, 0x09, 0xc2, 0x31, 0xa2, 0x01, 0x08, 0x83, 0x34, 0xc1, 0x0c, 0x59,
    0x06, 0x24, 0xc1, 0x08, 0x02, 0x06, 0x83, 0xb4, 0x39, 0x1a, 0x0a, 0x89, 0x3c, 0x10, 0x8e, 0x18,
    0xe4, 0x01, 0x04, 0x68, 0x09, 0x08, 0x06, 0x10, 0x08, 0x56, 0x1e, 0x06, 0xb0, 0x1d, 0x80, 0x28,
    0x05, 0x30, 0x1d, 0xa3, 0x00, 0x04, 0xb0, 0x1c, 0x01, 0x05, 0x70, 0xd8, 0x12, 0x00, 0x06, 0xd0,
    0x90, 0x24, 0x00, 0x05, 0xd0, 0x2c, 0x26, 0x00, 0x07, 0x10, 0x9c, 0x33, 0x16, 0x00, 0x07, 0xa7,
    0x40, 0x50, 0x08, 0x00, 0x04, 0xb0, 0x04, 0x00, 0x05, 0x08, 0x48, 0x80, 0x00, 0x05, 0x0a, 0x8d,
    0x73, 0x00, 0x06, 0x03, 0xcd, 0xd1, 0x0e, 0x06, 0x03, 0xc1, 0x72, 0x04, 0x05, 0x68, 0x08, 0x10,
    0x00, 0x05, 0x03, 0x15, 0xb2, 0x00, 0x05, 0x68, 0x84, 0x05, 0x00, 0x05, 0xc8, 0x2c, 0x26, 0x00,
    0x06, 0x0c, 0x0c, 0x24, 0x18, 0x05, 0x08, 0x0c, 0x09, 0x00, 0x05, 0x68, 0xa4, 0xc5, 0x00, 0x06,
    0x08, 0x90, 0x25, 0x18, 0x06, 0x6a, 0x20, 0x04, 0x02, 0x05, 0x8a, 0x01, 0x55, 0x01, 0x06, 0xaa,
    0x10, 0x6a, 0x16, 0x03, 0x15, 0x34, 0x07, 0x3b, 0x19, 0x55, 0x51, 0x03, 0x04, 0xb3, 0x84, 0x0a,
    0x04, 0x95, 0x94, 0x09, 0x04, 0x36, 0x1d, 0x01, 0x04, 0xd5, 0x90, 0x07, 0x04, 0x15, 0x00, 0x07,
    0x04, 0x70, 0x54, 0x00, 0x08, 0x3b, 0x81, 0x23, 0x4c, 0x21, 0x06, 0x06, 0xba, 0x12, 0x04, 0x04,
    0x76, 0xc8, 0x01, 0x07, 0x3c, 0x0c, 0x3a, 0xc8, 0x00, 0x0c, 0x3c, 0x0c, 0x3a, 0xc8, 0xc8, 0x7d,
    0xc4, 0x03, 0x05, 0x40, 0x82, 0xd0, 0x00, 0x05, 0x2b, 0x81, 0x73, 0x00, 0x05, 0x2b, 0x80, 0x21,
    0x00, 0x05, 0x2b, 0x94, 0xe4, 0x00, 0x07, 0x0b, 0x10, 0x10, 0x06, 0x02, 0x06, 0xcb, 0x48, 0x43,
    0x16, 0x06, 0xc1, 0x2c, 0x26, 0x0e, 0x05, 0x11, 0xac, 0x41, 0x00, 0x06, 0x0b, 0x0d, 0xa2, 0x00,
    0x05, 0x63, 0x0d, 0x43, 0x00, 0x05, 0x74, 0x18, 0x74, 0x00, 0x05, 0x74, 0xa0, 0x03, 0x00, 0x05,
    0xb4, 0x04, 0xd1, 0x00, 0x05, 0xb4, 0x24, 0xf2, 0x00, 0x08, 0xa7, 0x50, 0x31, 0x47, 0x00, 0x0b,
    0x86, 0xd0, 0x12, 0xe0, 0x10, 0xa6, 0x10, 0x05, 0xd4, 0x84, 0x23, 0x00, 0x06, 0xd4, 0x90, 0x05,
    0x02, 0x05, 0xd4, 0x50, 0xc1, 0x00, 0x04, 0x14, 0x00, 0x04, 0x06, 0x74, 0x40, 0x83, 0x1a, 0x04,
    0x34, 0x14, 0x08, 0x05, 0x31, 0x19, 0xf4, 0x00, 0x06, 0x6c, 0x3c, 0x72, 0x05, 0x04, 0x6f, 0x88,
    0x01, 0x07, 0x03, 0x05, 0x30, 0x5e, 0x03, 0x08, 0x2e, 0x94, 0x97, 0x94, 0x38, 0x05, 0x82, 0x01,
    0x13, 0x00, 0x07, 0xaf, 0x80, 0x43, 0xae, 0x00, 0x06, 0x2f, 0x05, 0x43, 0x16, 0x05, 0x82, 0x99,
    0xf0, 0x00, 0x05, 0xd2, 0x3c, 0x50, 0x00, 0x05, 0xa2, 0xbc, 0xd1, 0x00, 0x06, 0xcf, 0x3c, 0x72,
    0x05, 0x08, 0xaa, 0x24, 0xf4, 0xc8, 0x15, 0x05, 0xaa, 0x90, 0x23, 0x00, 0x06, 0xae, 0x20, 0xa3,
    0x1a, 0x07, 0x2a, 0x85, 0x00, 0x88, 0x00, 0x06, 0x43, 0x85, 0x72, 0x0e, 0x08, 0xaa, 0x10, 0x61,
    0x48, 0x02, 0x07, 0x2e, 0x14, 0x0b, 0x94, 0x00, 0x05, 0x0a, 0x19, 0x55, 0x01, 0x08, 0x01, 0x1c,
    0x30, 0x82, 0x62, 0x07, 0x07, 0x04, 0x69, 0x14, 0x00, 0x08, 0x43, 0x89, 0x34, 0x10, 0x6a, 0x05,
    0xaa, 0x24, 0xf4, 0x00, 0x0d, 0x25, 0x1e, 0x10, 0xe4, 0x88, 0x06, 0x19, 0xd1, 0x00, 0x07, 0xb1,
    0x14, 0x04, 0x06, 0x01, 0x04, 0xb1, 0xbc, 0x06, 0x08, 0x31, 0x1d, 0x43, 0xc0, 0x39, 0x05, 0x31,
    0x80, 0x51, 0x01, 0x06, 0x11, 0xa8, 0x02, 0x01, 0x07, 0x11, 0x88, 0x09, 0x00, 0x01, 0x05, 0x11,
    0x18, 0xb2, 0x00, 0x06, 0x11, 0x30, 0x43, 0x1e, 0x07, 0x11, 0xa8, 0x91, 0x0e, 0x00, 0x05, 0x23,
    0x96, 0x24, 0x00, 0x04, 0x11, 0x00, 0x02
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
                case -222:
                    if (keycode == KC_SPC) return 64;
                    if (keycode == KC_COMMA) return 0;
                    if (keycode == KC_DOT) return 41;
                    if (keycode == KC_A) return 58;
                    if (keycode == KC_E) return 54;
                    if (keycode == KC_H) return 31;
                    if (keycode == KC_I) return 50;
                    if (keycode == KC_J) return 11;
                    if (keycode == KC_O) return 46;
                    if (keycode == KC_R) return 5;
                    if (keycode == KC_U) return 23;
                    if (keycode == KC_Y) return 18;
                    break;
                // x
                case -209:
                    if (keycode == KC_SPC) return 146;
                    if (keycode == KC_COMMA) return 70;
                    if (keycode == KC_DOT) return 116;
                    if (keycode == KC_A) return 140;
                    if (keycode == KC_E) return 134;
                    if (keycode == KC_H) return 111;
                    if (keycode == KC_I) return 128;
                    if (keycode == KC_J) return 121;
                    if (keycode == KC_O) return 96;
                    if (keycode == KC_R) return 83;
                    if (keycode == KC_U) return 106;
                    if (keycode == KC_Y) return 89;
                    break;
                // w
                case -196:
                    if (keycode == KC_SPC) return 208;
                    if (keycode == KC_COMMA) return 158;
                    if (keycode == KC_DOT) return 164;
                    if (keycode == KC_A) return 204;
                    if (keycode == KC_E) return 200;
                    if (keycode == KC_H) return 195;
                    if (keycode == KC_I) return 190;
                    if (keycode == KC_J) return 185;
                    if (keycode == KC_O) return 179;
                    if (keycode == KC_R) return 174;
                    if (keycode == KC_U) return 152;
                    if (keycode == KC_Y) return 169;
                    break;
                // v
                case -183:
                    if (keycode == KC_SPC) return 272;
                    if (keycode == KC_COMMA) return 213;
                    if (keycode == KC_DOT) return 229;
                    if (keycode == KC_A) return 265;
                    if (keycode == KC_E) return 261;
                    if (keycode == KC_H) return 223;
                    if (keycode == KC_I) return 255;
                    if (keycode == KC_J) return 219;
                    if (keycode == KC_O) return 251;
                    if (keycode == KC_R) return 246;
                    if (keycode == KC_U) return 241;
                    if (keycode == KC_Y) return 233;
                    break;
                // t
                case -170:
                    if (keycode == KC_SPC) return 334;
                    if (keycode == KC_COMMA) return 276;
                    if (keycode == KC_DOT) return 281;
                    if (keycode == KC_A) return 328;
                    if (keycode == KC_E) return 323;
                    if (keycode == KC_H) return 318;
                    if (keycode == KC_I) return 314;
                    if (keycode == KC_J) return 308;
                    if (keycode == KC_O) return 302;
                    if (keycode == KC_R) return 297;
                    if (keycode == KC_U) return 292;
                    if (keycode == KC_Y) return 285;
                    break;
                // s
                case -157:
                    if (keycode == KC_SPC) return 397;
                    if (keycode == KC_COMMA) return 339;
                    if (keycode == KC_DOT) return 344;
                    if (keycode == KC_A) return 393;
                    if (keycode == KC_E) return 388;
                    if (keycode == KC_H) return 383;
                    if (keycode == KC_I) return 377;
                    if (keycode == KC_J) return 371;
                    if (keycode == KC_O) return 366;
                    if (keycode == KC_R) return 360;
                    if (keycode == KC_U) return 354;
                    if (keycode == KC_Y) return 349;
                    break;
                // r
                case -145:
                    if (keycode == KC_SPC) return 452;
                    if (keycode == KC_COMMA) return 402;
                    if (keycode == KC_DOT) return 407;
                    if (keycode == KC_A) return 446;
                    if (keycode == KC_E) return 441;
                    if (keycode == KC_H) return 436;
                    if (keycode == KC_I) return 431;
                    if (keycode == KC_J) return 426;
                    if (keycode == KC_O) return 421;
                    if (keycode == KC_U) return 417;
                    if (keycode == KC_Y) return 412;
                    break;
                // q
                case -134:
                    if (keycode == KC_SPC) return 505;
                    if (keycode == KC_COMMA) return 486;
                    if (keycode == KC_A) return 480;
                    if (keycode == KC_E) return 474;
                    if (keycode == KC_H) return 468;
                    if (keycode == KC_I) return 495;
                    if (keycode == KC_J) return 462;
                    if (keycode == KC_O) return 491;
                    if (keycode == KC_U) return 500;
                    if (keycode == KC_Y) return 457;
                    break;
                // p
                case -121:
                    if (keycode == KC_SPC) return 569;
                    if (keycode == KC_COMMA) return 510;
                    if (keycode == KC_DOT) return 519;
                    if (keycode == KC_A) return 563;
                    if (keycode == KC_E) return 558;
                    if (keycode == KC_H) return 515;
                    if (keycode == KC_I) return 553;
                    if (keycode == KC_J) return 547;
                    if (keycode == KC_O) return 541;
                    if (keycode == KC_R) return 536;
                    if (keycode == KC_U) return 531;
                    if (keycode == KC_Y) return 525;
                    break;
                // n
                case -108:
                    if (keycode == KC_SPC) return 634;
                    if (keycode == KC_COMMA) return 574;
                    if (keycode == KC_DOT) return 579;
                    if (keycode == KC_A) return 629;
                    if (keycode == KC_E) return 624;
                    if (keycode == KC_H) return 618;
                    if (keycode == KC_I) return 610;
                    if (keycode == KC_J) return 604;
                    if (keycode == KC_O) return 598;
                    if (keycode == KC_R) return 594;
                    if (keycode == KC_U) return 589;
                    if (keycode == KC_Y) return 583;
                    break;
                // m
                case -96:
                    if (keycode == KC_SPC) return 692;
                    if (keycode == KC_COMMA) return 642;
                    if (keycode == KC_DOT) return 646;
                    if (keycode == KC_A) return 686;
                    if (keycode == KC_E) return 680;
                    if (keycode == KC_H) return 675;
                    if (keycode == KC_I) return 670;
                    if (keycode == KC_J) return 665;
                    if (keycode == KC_O) return 661;
                    if (keycode == KC_U) return 656;
                    if (keycode == KC_Y) return 651;
                    break;
                // l
                case -83:
                    if (keycode == KC_SPC) return 751;
                    if (keycode == KC_COMMA) return 696;
                    if (keycode == KC_DOT) return 701;
                    if (keycode == KC_A) return 746;
                    if (keycode == KC_E) return 741;
                    if (keycode == KC_H) return 736;
                    if (keycode == KC_I) return 731;
                    if (keycode == KC_J) return 726;
                    if (keycode == KC_O) return 721;
                    if (keycode == KC_R) return 716;
                    if (keycode == KC_U) return 711;
                    if (keycode == KC_Y) return 706;
                    break;
                // k
                case -70:
                    if (keycode == KC_SPC) return 804;
                    if (keycode == KC_COMMA) return 766;
                    if (keycode == KC_DOT) return 771;
                    if (keycode == KC_A) return 800;
                    if (keycode == KC_E) return 796;
                    if (keycode == KC_H) return 761;
                    if (keycode == KC_I) return 792;
                    if (keycode == KC_J) return 788;
                    if (keycode == KC_O) return 784;
                    if (keycode == KC_R) return 780;
                    if (keycode == KC_U) return 756;
                    if (keycode == KC_Y) return 774;
                    break;
                // j
                case -67:
                    if (keycode == KC_SPC) return 815;
                    if (keycode == KC_A) return 810;
                    break;
                // g
                case -54:
                    if (keycode == KC_SPC) return 880;
                    if (keycode == KC_COMMA) return 819;
                    if (keycode == KC_DOT) return 825;
                    if (keycode == KC_A) return 875;
                    if (keycode == KC_E) return 870;
                    if (keycode == KC_H) return 865;
                    if (keycode == KC_I) return 860;
                    if (keycode == KC_J) return 854;
                    if (keycode == KC_O) return 849;
                    if (keycode == KC_R) return 844;
                    if (keycode == KC_U) return 839;
                    if (keycode == KC_Y) return 834;
                    break;
                // f
                case -41:
                    if (keycode == KC_SPC) return 943;
                    if (keycode == KC_COMMA) return 885;
                    if (keycode == KC_DOT) return 890;
                    if (keycode == KC_A) return 938;
                    if (keycode == KC_E) return 934;
                    if (keycode == KC_H) return 929;
                    if (keycode == KC_I) return 924;
                    if (keycode == KC_J) return 919;
                    if (keycode == KC_O) return 911;
                    if (keycode == KC_R) return 905;
                    if (keycode == KC_U) return 900;
                    if (keycode == KC_Y) return 895;
                    break;
                // d
                case -28:
                    if (keycode == KC_SPC) return 1004;
                    if (keycode == KC_COMMA) return 952;
                    if (keycode == KC_DOT) return 957;
                    if (keycode == KC_A) return 999;
                    if (keycode == KC_E) return 994;
                    if (keycode == KC_H) return 989;
                    if (keycode == KC_I) return 984;
                    if (keycode == KC_J) return 947;
                    if (keycode == KC_O) return 978;
                    if (keycode == KC_R) return 973;
                    if (keycode == KC_U) return 967;
                    if (keycode == KC_Y) return 961;
                    break;
                // c
                case -15:
                    if (keycode == KC_SPC) return 1071;
                    if (keycode == KC_COMMA) return 1009;
                    if (keycode == KC_DOT) return 1015;
                    if (keycode == KC_A) return 1065;
                    if (keycode == KC_E) return 1059;
                    if (keycode == KC_H) return 1053;
                    if (keycode == KC_I) return 1048;
                    if (keycode == KC_J) return 1042;
                    if (keycode == KC_O) return 1036;
                    if (keycode == KC_R) return 1031;
                    if (keycode == KC_U) return 1025;
                    if (keycode == KC_Y) return 1020;
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return 1139;
                    if (keycode == KC_COMMA) return 1076;
                    if (keycode == KC_DOT) return 1086;
                    if (keycode == KC_A) return 1134;
                    if (keycode == KC_E) return 1128;
                    if (keycode == KC_H) return 1123;
                    if (keycode == KC_I) return 1118;
                    if (keycode == KC_J) return 1112;
                    if (keycode == KC_O) return 1107;
                    if (keycode == KC_R) return 1102;
                    if (keycode == KC_U) return 1096;
                    if (keycode == KC_Y) return 1092;
                    break;
                case -1:
                    if (keycode == KC_B) return -2;
                    if (keycode == KC_C) return -15;
                    if (keycode == KC_D) return -28;
                    if (keycode == KC_F) return -41;
                    if (keycode == KC_G) return -54;
                    if (keycode == KC_J) return -67;
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
                    if (keycode == KC_X) return -209;
                    if (keycode == KC_Z) return -222;
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
    case SUB_7: return 200;
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
