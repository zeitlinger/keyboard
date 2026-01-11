/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int alternateLayer = -1;
int layer = _BASE;
int chord_state = 0; // 0 = inactive, 1+ = trie states
int chord_depth = 0; // Track number of letters in current chord

// Chord string decoder lookup table (5-bit codes -> characters)
static const char chord_char_lookup[] = {
    'e', 't', 'a', 'n', 'r', 'o', 'i', 's', 'l', 'h', 'u', 'c', 'g', 'd', 'y', 'p', 'w', 'm', 'b', 'f', 'v', 'k', '\'', 'q', ' ', 'z'
};

// Global buffer containing all 5-bit packed chord strings
static const uint8_t chord_data[] = {
    0x04, 0x12, 0x80, 0x01, 0x04, 0x52, 0xac, 0x0a, 0x05, 0x42, 0x16, 0x15, 0x00, 0x07, 0x12, 0x2c,
    0xa1, 0x0e, 0x00, 0x06, 0x12, 0xcc, 0x42, 0x00, 0x07, 0x12, 0x20, 0x03, 0x28, 0x00, 0x06, 0x12,
    0x84, 0x00, 0x08, 0x07, 0x12, 0x04, 0x08, 0xc0, 0x00, 0x06, 0x12, 0x24, 0x33, 0x1a, 0x05, 0x12,
    0x89, 0x55, 0x01, 0x05, 0x92, 0x00, 0x51, 0x01, 0x08, 0x52, 0x1d, 0x33, 0xc0, 0x39, 0x05, 0xab,
    0x28, 0xd4, 0x00, 0x08, 0x62, 0x05, 0x25, 0x10, 0x72, 0x07, 0x07, 0x10, 0x6a, 0x16, 0x00, 0x08,
    0x04, 0x1c, 0x20, 0xc8, 0x4a, 0x05, 0x0b, 0x99, 0x55, 0x01, 0x06, 0xab, 0xa8, 0x87, 0x00, 0x06,
    0x2b, 0x89, 0xc1, 0x00, 0x08, 0xab, 0x8c, 0x60, 0x86, 0x02, 0x06, 0xab, 0x28, 0x72, 0x00, 0x05,
    0xab, 0x50, 0x40, 0x00, 0x06, 0x62, 0x91, 0x72, 0x0e, 0x06, 0x4b, 0x28, 0x96, 0x02, 0x08, 0xab,
    0x28, 0xd4, 0x86, 0x0d, 0x06, 0xaf, 0x20, 0xb3, 0x1c, 0x06, 0xcd, 0xb4, 0x61, 0x03, 0x05, 0xa1,
    0x34, 0xe1, 0x00, 0x06, 0x0d, 0x2c, 0xd3, 0x00, 0x05, 0xd4, 0x34, 0x50, 0x00, 0x09, 0xcd, 0xcc,
    0x09, 0x08, 0x18, 0x01, 0x06, 0x49, 0xb4, 0x61, 0x03, 0x08, 0x8f, 0x94, 0xa6, 0x56, 0x38, 0x07,
    0x02, 0x11, 0x20, 0x9a, 0x03, 0x04, 0x93, 0x94, 0x08, 0x06, 0x53, 0x44, 0x83, 0x1c, 0x06, 0x53,
    0x84, 0x04, 0x08, 0x06, 0xd3, 0x30, 0x45, 0x00, 0x07, 0xd3, 0x0c, 0x81, 0x90, 0x03, 0x06, 0xd3,
    0x0c, 0x06, 0x08, 0x06, 0xd3, 0x0c, 0x73, 0x12, 0x06, 0xb3, 0x20, 0x54, 0x20, 0x0b, 0x66, 0xcc,
    0x42, 0xa2, 0x08, 0xa6, 0x0c, 0x08, 0xa7, 0xcc, 0x00, 0x05, 0x01, 0x05, 0xb3, 0xa8, 0xd1, 0x00,
    0x05, 0x82, 0x09, 0x33, 0x00, 0x05, 0x12, 0x30, 0x31, 0x00, 0x07, 0x0c, 0x0c, 0x40, 0x04, 0x02,
    0x06, 0xc4, 0xb0, 0x14, 0x0e, 0x06, 0x0c, 0x89, 0xb1, 0x00, 0x05, 0x8c, 0x14, 0xf5, 0x00, 0x05,
    0x8c, 0x00, 0x11, 0x00, 0x06, 0x8c, 0x14, 0x35, 0x1a, 0x07, 0x82, 0x09, 0x33, 0x4e, 0x00, 0x05,
    0x4c, 0x81, 0x73, 0x00, 0x08, 0x57, 0x81, 0x13, 0x4c, 0x19, 0x07, 0x57, 0x99, 0x55, 0x91, 0x03,
    0x06, 0x08, 0x0c, 0x16, 0x12, 0x04, 0xc8, 0x54, 0x00, 0x05, 0x48, 0x28, 0x96, 0x00, 0x05, 0x08,
    0x08, 0x0a, 0x00, 0x07, 0xc9, 0xc4, 0x03, 0xd0, 0x04, 0x06, 0x09, 0x08, 0x14, 0x12, 0x05, 0xc8,
    0xb0, 0x14, 0x00, 0x06, 0x02, 0xc5, 0x72, 0x02, 0x05, 0x02, 0x95, 0xc1, 0x00, 0x06, 0xc8, 0x9c,
    0x00, 0x06, 0x06, 0xc8, 0x84, 0x80, 0x00, 0x06, 0x02, 0x41, 0xe1, 0x0e, 0x04, 0xb1, 0x10, 0x00,
    0x07, 0x11, 0x9c, 0x23, 0x18, 0x00, 0x05, 0xd1, 0xb0, 0x14, 0x00, 0x06, 0xd1, 0x0c, 0x15, 0x00,
    0x06, 0xb1, 0x44, 0x30, 0x02, 0x07, 0xa7, 0x44, 0x50, 0x06, 0x00, 0x05, 0x26, 0x80, 0x78, 0x00,
    0x05, 0x51, 0x1d, 0xb3, 0x00, 0x06, 0xd1, 0x1d, 0x80, 0x26, 0x0a, 0x6a, 0x34, 0x40, 0x4e, 0x10,
    0xa3, 0x01, 0x06, 0x62, 0x38, 0x28, 0x1c, 0x05, 0xc8, 0x8c, 0x7a, 0x00, 0x08, 0x62, 0xb8, 0x90,
    0xcc, 0x60, 0x0a, 0x6a, 0x18, 0x0a, 0xc8, 0x31, 0xc1, 0x01, 0x07, 0x62, 0x94, 0x90, 0x00, 0x01,
    0x06, 0x60, 0x14, 0xc5, 0x12, 0x06, 0x62, 0x1c, 0x08, 0x08, 0x06, 0x66, 0x1c, 0xd3, 0x00, 0x07,
    0x66, 0x9c, 0x00, 0x44, 0x03, 0x07, 0xa3, 0x84, 0x64, 0x06, 0x03, 0x06, 0x43, 0x45, 0x09, 0x08,
    0x07, 0xab, 0xc4, 0x27, 0x86, 0x03, 0x06, 0x62, 0xb8, 0x32, 0x00, 0x06, 0x0f, 0x94, 0x87, 0x00,
    0x07, 0x8f, 0x18, 0x2a, 0x96, 0x03, 0x06, 0x4f, 0x10, 0x30, 0x02, 0x05, 0x0f, 0x89, 0x05, 0x00,
    0x06, 0x0f, 0x01, 0x71, 0x00, 0x06, 0x49, 0xbc, 0x07, 0x06, 0x06, 0x0f, 0x90, 0x53, 0x06, 0x07,
    0x8f, 0x94, 0xa6, 0x56, 0x00, 0x07, 0x8f, 0x14, 0x89, 0x40, 0x04, 0x06, 0x8f, 0x80, 0x10, 0x1c,
    0x08, 0x8f, 0x14, 0x29, 0x24, 0x72, 0x06, 0x4f, 0x49, 0x64, 0x16, 0x06, 0x04, 0x08, 0x84, 0x1c,
    0x07, 0x8f, 0x14, 0x46, 0x44, 0x04, 0x05, 0x85, 0x34, 0x40, 0x00, 0x05, 0x04, 0x88, 0xe6, 0x00,
    0x08, 0x04, 0x44, 0x10, 0x25, 0x20, 0x05, 0x04, 0x3c, 0xe4, 0x00, 0x07, 0x21, 0x01, 0x02, 0xec,
    0x01, 0x06, 0x04, 0x04, 0x45, 0x06, 0x06, 0x04, 0x50, 0x03, 0x20, 0x05, 0xc4, 0xb0, 0x14, 0x00,
    0x05, 0xb0, 0x10, 0xd4, 0x00, 0x07, 0xb1, 0x90, 0x61, 0x06, 0x03, 0x06, 0x82, 0x14, 0x35, 0x1a,
    0x05, 0x0e, 0x08, 0x72, 0x00, 0x08, 0x80, 0x02, 0xe2, 0xca, 0x00, 0x06, 0x27, 0x15, 0x85, 0x1a,
    0x06, 0x07, 0x08, 0xb2, 0x12, 0x06, 0x07, 0xac, 0x32, 0x1a, 0x07, 0xc7, 0x20, 0x30, 0x16, 0x00,
    0x08, 0x07, 0x19, 0x96, 0x02, 0x72, 0x06, 0x07, 0x15, 0x88, 0x1c, 0x06, 0x50, 0x9c, 0x61, 0x03,
    0x09, 0xa7, 0x44, 0x10, 0x92, 0x19, 0x0c, 0x05, 0x27, 0x94, 0xd2, 0x00, 0x07, 0x47, 0xbd, 0x57,
    0x48, 0x00, 0x08, 0x47, 0xb5, 0x06, 0x06, 0x72, 0x07, 0x47, 0xbd, 0x57, 0x0e, 0x00, 0x08, 0x47,
    0x91, 0x47, 0xcc, 0x01, 0x06, 0xc7, 0x9d, 0x00, 0x22, 0x05, 0x21, 0x99, 0x51, 0x01, 0x07, 0xab,
    0x8c, 0x20, 0x56, 0x00, 0x05, 0x41, 0x48, 0x04, 0x00, 0x05, 0x50, 0x84, 0x95, 0x00, 0x06, 0x21,
    0x89, 0x51, 0x0f, 0x07, 0x21, 0x15, 0xc5, 0x52, 0x00, 0x07, 0x21, 0x91, 0xa2, 0x58, 0x02, 0x06,
    0xa3, 0x04, 0xb3, 0x00, 0x05, 0x21, 0x99, 0xc1, 0x00, 0x06, 0x21, 0x15, 0xc5, 0x12, 0x08, 0xa1,
    0x30, 0x10, 0x12, 0x20, 0x06, 0xa1, 0x40, 0x41, 0x1a, 0x06, 0x21, 0x89, 0x60, 0x0f, 0x09, 0x21,
    0x89, 0x51, 0xb1, 0x2b, 0x0a, 0x04, 0x49, 0x50, 0x00, 0x09, 0x82, 0x0a, 0x83, 0x84, 0x44, 0x00,
    0x08, 0x07, 0x10, 0x6a, 0x16, 0x38, 0x0a, 0x80, 0x02, 0xe2, 0x42, 0x32, 0x83, 0x01, 0x05, 0xb0,
    0x28, 0xd4, 0x00, 0x04, 0x50, 0xa0, 0x0a, 0x05, 0x30, 0x99, 0x95, 0x00, 0x06, 0x30, 0x89, 0x60,
    0x0f, 0x05, 0x30, 0x01, 0x02, 0x00, 0x06, 0xd0, 0x8c, 0x56, 0x20, 0x07, 0xd0, 0x84, 0x54, 0x54,
    0x00, 0x05, 0x90, 0x94, 0xc1, 0x00, 0x07, 0x04, 0x50, 0x03, 0xe0, 0x01, 0x08, 0xb0, 0x28, 0xd4,
    0x86, 0x0d, 0x05, 0xb0, 0x10, 0xe2, 0x00, 0x07, 0x04, 0x08, 0x64, 0x32, 0x00
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
                case 1:
                    if (keycode == KC_B) return 2;
                    if (keycode == KC_C) return 15;
                    if (keycode == KC_D) return 30;
                    if (keycode == KC_F) return 39;
                    if (keycode == KC_G) return 51;
                    if (keycode == KC_K) return 62;
                    if (keycode == KC_L) return 65;
                    if (keycode == KC_M) return 78;
                    if (keycode == KC_N) return 88;
                    if (keycode == KC_P) return 103;
                    if (keycode == KC_R) return 116;
                    if (keycode == KC_S) return 132;
                    if (keycode == KC_T) return 147;
                    if (keycode == KC_V) return 162;
                    if (keycode == KC_W) return 167;
                    if (keycode == KC_Z) return 179;
                    break;
                // b
                case 2:
                    if (keycode == KC_SPC) return 3;
                    if (keycode == KC_A) return 5;
                    if (keycode == KC_D) return 7;
                    if (keycode == KC_E) return 6;
                    if (keycode == KC_H) return 11;
                    if (keycode == KC_K) return 4;
                    if (keycode == KC_L) return 8;
                    if (keycode == KC_N) return 12;
                    if (keycode == KC_R) return 13;
                    if (keycode == KC_T) return 9;
                    if (keycode == KC_U) return 14;
                    if (keycode == KC_W) return 10;
                    break;
                // c
                case 15:
                    if (keycode == KC_SPC) return 16;
                    if (keycode == KC_A) return 17;
                    if (keycode == KC_D) return 28;
                    if (keycode == KC_E) return 18;
                    if (keycode == KC_H) return 19;
                    if (keycode == KC_I) return 20;
                    if (keycode == KC_L) return 21;
                    if (keycode == KC_N) return 22;
                    if (keycode == KC_O) return 23;
                    if (keycode == KC_Q) return 24;
                    if (keycode == KC_R) return 26;
                    if (keycode == KC_T) return 27;
                    if (keycode == KC_V) return 25;
                    if (keycode == KC_Y) return 29;
                    break;
                // d
                case 30:
                    if (keycode == KC_SPC) return 31;
                    if (keycode == KC_A) return 32;
                    if (keycode == KC_C) return 33;
                    if (keycode == KC_E) return 34;
                    if (keycode == KC_F) return 35;
                    if (keycode == KC_N) return 36;
                    if (keycode == KC_U) return 37;
                    if (keycode == KC_Y) return 38;
                    break;
                // f
                case 39:
                    if (keycode == KC_SPC) return 40;
                    if (keycode == KC_A) return 41;
                    if (keycode == KC_G) return 43;
                    if (keycode == KC_I) return 45;
                    if (keycode == KC_L) return 47;
                    if (keycode == KC_N) return 44;
                    if (keycode == KC_O) return 48;
                    if (keycode == KC_S) return 46;
                    if (keycode == KC_T) return 42;
                    if (keycode == KC_U) return 50;
                    if (keycode == KC_W) return 49;
                    break;
                // g
                case 51:
                    if (keycode == KC_SPC) return 52;
                    if (keycode == KC_D) return 59;
                    if (keycode == KC_E) return 53;
                    if (keycode == KC_H) return 55;
                    if (keycode == KC_J) return 54;
                    if (keycode == KC_O) return 57;
                    if (keycode == KC_R) return 58;
                    if (keycode == KC_S) return 60;
                    if (keycode == KC_U) return 61;
                    if (keycode == KC_Z) return 56;
                    break;
                // k
                case 62:
                    if (keycode == KC_SPC) return 63;
                    if (keycode == KC_Y) return 64;
                    break;
                // l
                case 65:
                    if (keycode == KC_SPC) return 66;
                    if (keycode == KC_A) return 68;
                    if (keycode == KC_E) return 69;
                    if (keycode == KC_F) return 70;
                    if (keycode == KC_H) return 71;
                    if (keycode == KC_I) return 72;
                    if (keycode == KC_K) return 67;
                    if (keycode == KC_O) return 74;
                    if (keycode == KC_Q) return 75;
                    if (keycode == KC_T) return 76;
                    if (keycode == KC_Y) return 77;
                    if (keycode == KC_Z) return 73;
                    break;
                // m
                case 78:
                    if (keycode == KC_SPC) return 79;
                    if (keycode == KC_A) return 84;
                    if (keycode == KC_E) return 80;
                    if (keycode == KC_H) return 81;
                    if (keycode == KC_I) return 82;
                    if (keycode == KC_S) return 85;
                    if (keycode == KC_U) return 86;
                    if (keycode == KC_Y) return 87;
                    if (keycode == KC_Z) return 83;
                    break;
                // n
                case 88:
                    if (keycode == KC_SPC) return 89;
                    if (keycode == KC_A) return 90;
                    if (keycode == KC_C) return 91;
                    if (keycode == KC_H) return 92;
                    if (keycode == KC_I) return 93;
                    if (keycode == KC_J) return 98;
                    if (keycode == KC_O) return 94;
                    if (keycode == KC_P) return 102;
                    if (keycode == KC_Q) return 97;
                    if (keycode == KC_S) return 96;
                    if (keycode == KC_T) return 99;
                    if (keycode == KC_U) return 95;
                    if (keycode == KC_Y) return 101;
                    if (keycode == KC_Z) return 100;
                    break;
                // p
                case 103:
                    if (keycode == KC_SPC) return 104;
                    if (keycode == KC_A) return 105;
                    if (keycode == KC_E) return 107;
                    if (keycode == KC_L) return 108;
                    if (keycode == KC_N) return 109;
                    if (keycode == KC_O) return 111;
                    if (keycode == KC_R) return 106;
                    if (keycode == KC_S) return 110;
                    if (keycode == KC_T) return 113;
                    if (keycode == KC_U) return 115;
                    if (keycode == KC_Y) return 114;
                    if (keycode == KC_Z) return 112;
                    break;
                // r
                case 116:
                    if (keycode == KC_SPC) return 117;
                    if (keycode == KC_A) return 118;
                    if (keycode == KC_E) return 120;
                    if (keycode == KC_H) return 125;
                    if (keycode == KC_I) return 126;
                    if (keycode == KC_L) return 127;
                    if (keycode == KC_M) return 121;
                    if (keycode == KC_N) return 128;
                    if (keycode == KC_O) return 129;
                    if (keycode == KC_P) return 122;
                    if (keycode == KC_Q) return 131;
                    if (keycode == KC_S) return 123;
                    if (keycode == KC_W) return 119;
                    if (keycode == KC_Y) return 130;
                    if (keycode == KC_Z) return 124;
                    break;
                // s
                case 132:
                    if (keycode == KC_SPC) return 133;
                    if (keycode == KC_C) return 135;
                    if (keycode == KC_D) return 143;
                    if (keycode == KC_E) return 134;
                    if (keycode == KC_I) return 136;
                    if (keycode == KC_L) return 137;
                    if (keycode == KC_M) return 140;
                    if (keycode == KC_N) return 139;
                    if (keycode == KC_O) return 138;
                    if (keycode == KC_P) return 144;
                    if (keycode == KC_R) return 145;
                    if (keycode == KC_T) return 141;
                    if (keycode == KC_U) return 142;
                    if (keycode == KC_Y) return 146;
                    break;
                // t
                case 147:
                    if (keycode == KC_SPC) return 148;
                    if (keycode == KC_A) return 149;
                    if (keycode == KC_B) return 150;
                    if (keycode == KC_C) return 151;
                    if (keycode == KC_E) return 155;
                    if (keycode == KC_G) return 158;
                    if (keycode == KC_H) return 152;
                    if (keycode == KC_N) return 156;
                    if (keycode == KC_O) return 153;
                    if (keycode == KC_S) return 160;
                    if (keycode == KC_U) return 157;
                    if (keycode == KC_W) return 159;
                    if (keycode == KC_Y) return 161;
                    if (keycode == KC_Z) return 154;
                    break;
                // v
                case 162:
                    if (keycode == KC_SPC) return 163;
                    if (keycode == KC_A) return 164;
                    if (keycode == KC_I) return 165;
                    if (keycode == KC_Y) return 166;
                    break;
                // w
                case 167:
                    if (keycode == KC_SPC) return 168;
                    if (keycode == KC_A) return 169;
                    if (keycode == KC_H) return 170;
                    if (keycode == KC_I) return 173;
                    if (keycode == KC_O) return 174;
                    if (keycode == KC_R) return 172;
                    if (keycode == KC_S) return 176;
                    if (keycode == KC_T) return 171;
                    if (keycode == KC_U) return 177;
                    if (keycode == KC_Y) return 178;
                    if (keycode == KC_Z) return 175;
                    break;
                // z
                case 179:
                    if (keycode == KC_SPC) return 180;
                    break;
    default:
        // Invalid transition, stop chord mode
        return 0;
    }
    return 0;
}

void chord_output(int state) {
    switch (state) {
                // b 
        case 3: chord_decode_send(chord_data + 0); break;
                // bk
        case 4: chord_decode_send(chord_data + 4); break;
                // ba
        case 5: chord_decode_send(chord_data + 8); break;
                // be
        case 6: chord_decode_send(chord_data + 13); break;
                // bd
        case 7: chord_decode_send(chord_data + 19); break;
                // bl
        case 8: chord_decode_send(chord_data + 24); break;
                // bt
        case 9: chord_decode_send(chord_data + 30); break;
                // bw
        case 10: chord_decode_send(chord_data + 35); break;
                // bh
        case 11: chord_decode_send(chord_data + 41); break;
                // bn
        case 12: chord_decode_send(chord_data + 46); break;
                // br
        case 13: chord_decode_send(chord_data + 51); break;
                // bu
        case 14: chord_decode_send(chord_data + 56); break;
                // c 
        case 16: chord_decode_send(chord_data + 62); break;
                // ca
        case 17: chord_decode_send(chord_data + 67); break;
                // ce
        case 18: chord_decode_send(chord_data + 73); break;
                // ch
        case 19: chord_decode_send(chord_data + 79); break;
                // ci
        case 20: chord_decode_send(chord_data + 85); break;
                // cl
        case 21: chord_decode_send(chord_data + 90); break;
                // cn
        case 22: chord_decode_send(chord_data + 95); break;
                // co
        case 23: chord_decode_send(chord_data + 100); break;
                // cq
        case 24: chord_decode_send(chord_data + 106); break;
                // cv
        case 25: chord_decode_send(chord_data + 111); break;
                // cr
        case 26: chord_decode_send(chord_data + 116); break;
                // ct
        case 27: chord_decode_send(chord_data + 121); break;
                // cd
        case 28: chord_decode_send(chord_data + 126); break;
                // cy
        case 29: chord_decode_send(chord_data + 132); break;
                // d 
        case 31: chord_decode_send(chord_data + 137); break;
                // da
        case 32: chord_decode_send(chord_data + 142); break;
                // dc
        case 33: chord_decode_send(chord_data + 147); break;
                // de
        case 34: chord_decode_send(chord_data + 152); break;
                // df
        case 35: chord_decode_send(chord_data + 157); break;
                // dn
        case 36: chord_decode_send(chord_data + 164); break;
                // du
        case 37: chord_decode_send(chord_data + 169); break;
                // dy
        case 38: chord_decode_send(chord_data + 175); break;
                // f 
        case 40: chord_decode_send(chord_data + 181); break;
                // fa
        case 41: chord_decode_send(chord_data + 185); break;
                // ft
        case 42: chord_decode_send(chord_data + 190); break;
                // fg
        case 43: chord_decode_send(chord_data + 195); break;
                // fn
        case 44: chord_decode_send(chord_data + 200); break;
                // fi
        case 45: chord_decode_send(chord_data + 206); break;
                // fs
        case 46: chord_decode_send(chord_data + 211); break;
                // fl
        case 47: chord_decode_send(chord_data + 216); break;
                // fo
        case 48: chord_decode_send(chord_data + 221); break;
                // fw
        case 49: chord_decode_send(chord_data + 229); break;
                // fu
        case 50: chord_decode_send(chord_data + 235); break;
                // g 
        case 52: chord_decode_send(chord_data + 240); break;
                // ge
        case 53: chord_decode_send(chord_data + 245); break;
                // gj
        case 54: chord_decode_send(chord_data + 250); break;
                // gh
        case 55: chord_decode_send(chord_data + 256); break;
                // gz
        case 56: chord_decode_send(chord_data + 261); break;
                // go
        case 57: chord_decode_send(chord_data + 266); break;
                // gr
        case 58: chord_decode_send(chord_data + 271); break;
                // gd
        case 59: chord_decode_send(chord_data + 276); break;
                // gs
        case 60: chord_decode_send(chord_data + 281); break;
                // gu
        case 61: chord_decode_send(chord_data + 287); break;
                // k 
        case 63: chord_decode_send(chord_data + 292); break;
                // ky
        case 64: chord_decode_send(chord_data + 298); break;
                // l 
        case 66: chord_decode_send(chord_data + 304); break;
                // lk
        case 67: chord_decode_send(chord_data + 309); break;
                // la
        case 68: chord_decode_send(chord_data + 313); break;
                // le
        case 69: chord_decode_send(chord_data + 318); break;
                // lf
        case 70: chord_decode_send(chord_data + 323); break;
                // lh
        case 71: chord_decode_send(chord_data + 329); break;
                // li
        case 72: chord_decode_send(chord_data + 334); break;
                // lz
        case 73: chord_decode_send(chord_data + 339); break;
                // lo
        case 74: chord_decode_send(chord_data + 344); break;
                // lq
        case 75: chord_decode_send(chord_data + 349); break;
                // lt
        case 76: chord_decode_send(chord_data + 354); break;
                // ly
        case 77: chord_decode_send(chord_data + 359); break;
                // m 
        case 79: chord_decode_send(chord_data + 364); break;
                // me
        case 80: chord_decode_send(chord_data + 368); break;
                // mh
        case 81: chord_decode_send(chord_data + 374); break;
                // mi
        case 82: chord_decode_send(chord_data + 379); break;
                // mz
        case 83: chord_decode_send(chord_data + 384); break;
                // ma
        case 84: chord_decode_send(chord_data + 389); break;
                // ms
        case 85: chord_decode_send(chord_data + 395); break;
                // mu
        case 86: chord_decode_send(chord_data + 400); break;
                // my
        case 87: chord_decode_send(chord_data + 405); break;
                // n 
        case 89: chord_decode_send(chord_data + 410); break;
                // na
        case 90: chord_decode_send(chord_data + 418); break;
                // nc
        case 91: chord_decode_send(chord_data + 423); break;
                // nh
        case 92: chord_decode_send(chord_data + 428); break;
                // ni
        case 93: chord_decode_send(chord_data + 434); break;
                // no
        case 94: chord_decode_send(chord_data + 442); break;
                // nu
        case 95: chord_decode_send(chord_data + 448); break;
                // ns
        case 96: chord_decode_send(chord_data + 453); break;
                // nq
        case 97: chord_decode_send(chord_data + 458); break;
                // nj
        case 98: chord_decode_send(chord_data + 463); break;
                // nt
        case 99: chord_decode_send(chord_data + 469); break;
                // nz
        case 100: chord_decode_send(chord_data + 475); break;
                // ny
        case 101: chord_decode_send(chord_data + 480); break;
                // np
        case 102: chord_decode_send(chord_data + 486); break;
                // p 
        case 104: chord_decode_send(chord_data + 491); break;
                // pa
        case 105: chord_decode_send(chord_data + 496); break;
                // pr
        case 106: chord_decode_send(chord_data + 502); break;
                // pe
        case 107: chord_decode_send(chord_data + 507); break;
                // pl
        case 108: chord_decode_send(chord_data + 512); break;
                // pn
        case 109: chord_decode_send(chord_data + 517); break;
                // ps
        case 110: chord_decode_send(chord_data + 522); break;
                // po
        case 111: chord_decode_send(chord_data + 527); break;
                // pz
        case 112: chord_decode_send(chord_data + 533); break;
                // pt
        case 113: chord_decode_send(chord_data + 539); break;
                // py
        case 114: chord_decode_send(chord_data + 544); break;
                // pu
        case 115: chord_decode_send(chord_data + 550); break;
                // r 
        case 117: chord_decode_send(chord_data + 555); break;
                // ra
        case 118: chord_decode_send(chord_data + 560); break;
                // rw
        case 119: chord_decode_send(chord_data + 566); break;
                // re
        case 120: chord_decode_send(chord_data + 571); break;
                // rm
        case 121: chord_decode_send(chord_data + 576); break;
                // rp
        case 122: chord_decode_send(chord_data + 582); break;
                // rs
        case 123: chord_decode_send(chord_data + 587); break;
                // rz
        case 124: chord_decode_send(chord_data + 593); break;
                // rh
        case 125: chord_decode_send(chord_data + 598); break;
                // ri
        case 126: chord_decode_send(chord_data + 603); break;
                // rl
        case 127: chord_decode_send(chord_data + 608); break;
                // rn
        case 128: chord_decode_send(chord_data + 613); break;
                // ro
        case 129: chord_decode_send(chord_data + 619); break;
                // ry
        case 130: chord_decode_send(chord_data + 624); break;
                // rq
        case 131: chord_decode_send(chord_data + 629); break;
                // s 
        case 133: chord_decode_send(chord_data + 635); break;
                // se
        case 134: chord_decode_send(chord_data + 640); break;
                // sc
        case 135: chord_decode_send(chord_data + 645); break;
                // si
        case 136: chord_decode_send(chord_data + 650); break;
                // sl
        case 137: chord_decode_send(chord_data + 656); break;
                // so
        case 138: chord_decode_send(chord_data + 662); break;
                // sn
        case 139: chord_decode_send(chord_data + 667); break;
                // sm
        case 140: chord_decode_send(chord_data + 672); break;
                // st
        case 141: chord_decode_send(chord_data + 679); break;
                // su
        case 142: chord_decode_send(chord_data + 684); break;
                // sd
        case 143: chord_decode_send(chord_data + 690); break;
                // sp
        case 144: chord_decode_send(chord_data + 696); break;
                // sr
        case 145: chord_decode_send(chord_data + 702); break;
                // sy
        case 146: chord_decode_send(chord_data + 708); break;
                // t 
        case 148: chord_decode_send(chord_data + 713); break;
                // ta
        case 149: chord_decode_send(chord_data + 718); break;
                // tb
        case 150: chord_decode_send(chord_data + 724); break;
                // tc
        case 151: chord_decode_send(chord_data + 729); break;
                // th
        case 152: chord_decode_send(chord_data + 734); break;
                // to
        case 153: chord_decode_send(chord_data + 739); break;
                // tz
        case 154: chord_decode_send(chord_data + 745); break;
                // te
        case 155: chord_decode_send(chord_data + 751); break;
                // tn
        case 156: chord_decode_send(chord_data + 756); break;
                // tu
        case 157: chord_decode_send(chord_data + 761); break;
                // tg
        case 158: chord_decode_send(chord_data + 766); break;
                // tw
        case 159: chord_decode_send(chord_data + 772); break;
                // ts
        case 160: chord_decode_send(chord_data + 777); break;
                // ty
        case 161: chord_decode_send(chord_data + 782); break;
                // v 
        case 163: chord_decode_send(chord_data + 789); break;
                // va
        case 164: chord_decode_send(chord_data + 793); break;
                // vi
        case 165: chord_decode_send(chord_data + 800); break;
                // vy
        case 166: chord_decode_send(chord_data + 806); break;
                // w 
        case 168: chord_decode_send(chord_data + 814); break;
                // wa
        case 169: chord_decode_send(chord_data + 819); break;
                // wh
        case 170: chord_decode_send(chord_data + 823); break;
                // wt
        case 171: chord_decode_send(chord_data + 828); break;
                // wr
        case 172: chord_decode_send(chord_data + 833); break;
                // wi
        case 173: chord_decode_send(chord_data + 838); break;
                // wo
        case 174: chord_decode_send(chord_data + 843); break;
                // wz
        case 175: chord_decode_send(chord_data + 849); break;
                // ws
        case 176: chord_decode_send(chord_data + 854); break;
                // wu
        case 177: chord_decode_send(chord_data + 860); break;
                // wy
        case 178: chord_decode_send(chord_data + 866); break;
                // z 
        case 180: chord_decode_send(chord_data + 871); break;
    default:
        return;
    }
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
                    case KC_V: SEND_STRING("en"); return false;
                    case KC_W: tap_code16(KC_S); return false;
                    case KC_X: tap_code16(KC_C); return false;
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
                    case KC_U: tap_code16(KC_A); return false;
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
                    case S(KC_U): tap_code16(KC_A); return false;
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
