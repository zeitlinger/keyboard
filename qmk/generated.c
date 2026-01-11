/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int alternateLayer = -1;
int layer = _BASE;
int chord_state = -1000; // -1000 = inactive, -1 = root, other negative = transition states, non-negative = byte offsets
int chord_depth = 0; // Track number of letters in current chord

// Chord string decoder lookup table (5-bit codes -> characters)
static const char chord_char_lookup[] = {
    'e', 't', 'a', 'n', 'r', 'o', 'i', 's', 'l', 'h', 'u', 'c', 'g', 'd', 'y', 'p', 'w', 'm', 'b', 'f', 'v', 'k', '\'', 'q', ' ', 'z'
};

// Global buffer containing all 5-bit packed chord strings
static const uint8_t chord_data[] = {
    0x07, 0x04, 0x08, 0x64, 0x32, 0x00, 0x05, 0xb0, 0x10, 0xe2, 0x00, 0x08, 0xb0, 0x28, 0xd4, 0x86,
    0x0d, 0x07, 0x04, 0x50, 0x03, 0xe0, 0x01, 0x05, 0x90, 0x94, 0xc1, 0x00, 0x07, 0xd0, 0x84, 0x54,
    0x54, 0x00, 0x06, 0xd0, 0x8c, 0x56, 0x20, 0x05, 0x30, 0x01, 0x02, 0x00, 0x06, 0x30, 0x89, 0x60,
    0x0f, 0x05, 0x30, 0x99, 0x95, 0x00, 0x04, 0x50, 0xa0, 0x0a, 0x05, 0xb0, 0x28, 0xd4, 0x00, 0x0a,
    0x80, 0x02, 0xe2, 0x42, 0x32, 0x83, 0x01, 0x08, 0x07, 0x10, 0x6a, 0x16, 0x38, 0x09, 0x82, 0x0a,
    0x83, 0x84, 0x44, 0x00, 0x04, 0x49, 0x50, 0x00, 0x09, 0x21, 0x89, 0x51, 0xb1, 0x2b, 0x0a, 0x06,
    0x21, 0x89, 0x60, 0x0f, 0x06, 0xa1, 0x40, 0x41, 0x1a, 0x08, 0xa1, 0x30, 0x10, 0x12, 0x20, 0x06,
    0x21, 0x15, 0xc5, 0x12, 0x05, 0x21, 0x99, 0xc1, 0x00, 0x06, 0xa3, 0x04, 0xb3, 0x00, 0x07, 0x21,
    0x91, 0xa2, 0x58, 0x02, 0x07, 0x21, 0x15, 0xc5, 0x52, 0x00, 0x06, 0x21, 0x89, 0x51, 0x0f, 0x05,
    0x50, 0x84, 0x95, 0x00, 0x05, 0x41, 0x48, 0x04, 0x00, 0x07, 0xab, 0x8c, 0x20, 0x56, 0x00, 0x05,
    0x21, 0x99, 0x51, 0x01, 0x06, 0xc7, 0x9d, 0x00, 0x22, 0x08, 0x47, 0x91, 0x47, 0xcc, 0x01, 0x07,
    0x47, 0xbd, 0x57, 0x0e, 0x00, 0x08, 0x47, 0xb5, 0x06, 0x06, 0x72, 0x07, 0x47, 0xbd, 0x57, 0x48,
    0x00, 0x05, 0x27, 0x94, 0xd2, 0x00, 0x09, 0xa7, 0x44, 0x10, 0x92, 0x19, 0x0c, 0x06, 0x50, 0x9c,
    0x61, 0x03, 0x06, 0x07, 0x15, 0x88, 0x1c, 0x08, 0x07, 0x19, 0x96, 0x02, 0x72, 0x07, 0xc7, 0x20,
    0x30, 0x16, 0x00, 0x06, 0x07, 0xac, 0x32, 0x1a, 0x06, 0x07, 0x08, 0xb2, 0x12, 0x06, 0x27, 0x15,
    0x85, 0x1a, 0x08, 0x80, 0x02, 0xe2, 0xca, 0x00, 0x05, 0x0e, 0x08, 0x72, 0x00, 0x06, 0x82, 0x14,
    0x35, 0x1a, 0x07, 0xb1, 0x90, 0x61, 0x06, 0x03, 0x05, 0xb0, 0x10, 0xd4, 0x00, 0x05, 0xc4, 0xb0,
    0x14, 0x00, 0x06, 0x04, 0x50, 0x03, 0x20, 0x06, 0x04, 0x04, 0x45, 0x06, 0x07, 0x21, 0x01, 0x02,
    0xec, 0x01, 0x05, 0x04, 0x3c, 0xe4, 0x00, 0x08, 0x04, 0x44, 0x10, 0x25, 0x20, 0x05, 0x04, 0x88,
    0xe6, 0x00, 0x05, 0x85, 0x34, 0x40, 0x00, 0x07, 0x8f, 0x14, 0x46, 0x44, 0x04, 0x06, 0x04, 0x08,
    0x84, 0x1c, 0x06, 0x4f, 0x49, 0x64, 0x16, 0x08, 0x8f, 0x14, 0x29, 0x24, 0x72, 0x06, 0x8f, 0x80,
    0x10, 0x1c, 0x07, 0x8f, 0x14, 0x89, 0x40, 0x04, 0x07, 0x8f, 0x94, 0xa6, 0x56, 0x00, 0x06, 0x0f,
    0x90, 0x53, 0x06, 0x06, 0x49, 0xbc, 0x07, 0x06, 0x06, 0x0f, 0x01, 0x71, 0x00, 0x05, 0x0f, 0x89,
    0x05, 0x00, 0x06, 0x4f, 0x10, 0x30, 0x02, 0x07, 0x8f, 0x18, 0x2a, 0x96, 0x03, 0x06, 0x0f, 0x94,
    0x87, 0x00, 0x06, 0x62, 0xb8, 0x32, 0x00, 0x07, 0xab, 0xc4, 0x27, 0x86, 0x03, 0x06, 0x43, 0x45,
    0x09, 0x08, 0x07, 0xa3, 0x84, 0x64, 0x06, 0x03, 0x07, 0x66, 0x9c, 0x00, 0x44, 0x03, 0x06, 0x66,
    0x1c, 0xd3, 0x00, 0x06, 0x62, 0x1c, 0x08, 0x08, 0x06, 0x60, 0x14, 0xc5, 0x12, 0x07, 0x62, 0x94,
    0x90, 0x00, 0x01, 0x0a, 0x6a, 0x18, 0x0a, 0xc8, 0x31, 0xc1, 0x01, 0x08, 0x62, 0xb8, 0x90, 0xcc,
    0x60, 0x05, 0xc8, 0x8c, 0x7a, 0x00, 0x06, 0x62, 0x38, 0x28, 0x1c, 0x0a, 0x6a, 0x34, 0x40, 0x4e,
    0x10, 0xa3, 0x01, 0x06, 0xd1, 0x1d, 0x80, 0x26, 0x05, 0x51, 0x1d, 0xb3, 0x00, 0x05, 0x26, 0x80,
    0x78, 0x00, 0x07, 0xa7, 0x44, 0x50, 0x06, 0x00, 0x06, 0xb1, 0x44, 0x30, 0x02, 0x06, 0xd1, 0x0c,
    0x15, 0x00, 0x05, 0xd1, 0xb0, 0x14, 0x00, 0x07, 0x11, 0x9c, 0x23, 0x18, 0x00, 0x04, 0xb1, 0x10,
    0x00, 0x06, 0x02, 0x41, 0xe1, 0x0e, 0x06, 0xc8, 0x84, 0x80, 0x00, 0x06, 0xc8, 0x9c, 0x00, 0x06,
    0x05, 0x02, 0x95, 0xc1, 0x00, 0x06, 0x02, 0xc5, 0x72, 0x02, 0x05, 0xc8, 0xb0, 0x14, 0x00, 0x06,
    0x09, 0x08, 0x14, 0x12, 0x07, 0xc9, 0xc4, 0x03, 0xd0, 0x04, 0x05, 0x08, 0x08, 0x0a, 0x00, 0x05,
    0x48, 0x28, 0x96, 0x00, 0x04, 0xc8, 0x54, 0x00, 0x06, 0x08, 0x0c, 0x16, 0x12, 0x07, 0x57, 0x99,
    0x55, 0x91, 0x03, 0x08, 0x57, 0x81, 0x13, 0x4c, 0x19, 0x05, 0x4c, 0x81, 0x73, 0x00, 0x07, 0x82,
    0x09, 0x33, 0x4e, 0x00, 0x06, 0x8c, 0x14, 0x35, 0x1a, 0x05, 0x8c, 0x00, 0x11, 0x00, 0x05, 0x8c,
    0x14, 0xf5, 0x00, 0x06, 0x0c, 0x89, 0xb1, 0x00, 0x06, 0xc4, 0xb0, 0x14, 0x0e, 0x07, 0x0c, 0x0c,
    0x40, 0x04, 0x02, 0x05, 0x12, 0x30, 0x31, 0x00, 0x05, 0x82, 0x09, 0x33, 0x00, 0x05, 0xb3, 0xa8,
    0xd1, 0x00, 0x08, 0xa7, 0xcc, 0x00, 0x05, 0x01, 0x0b, 0x66, 0xcc, 0x42, 0xa2, 0x08, 0xa6, 0x0c,
    0x06, 0xb3, 0x20, 0x54, 0x20, 0x06, 0xd3, 0x0c, 0x73, 0x12, 0x06, 0xd3, 0x0c, 0x06, 0x08, 0x07,
    0xd3, 0x0c, 0x81, 0x90, 0x03, 0x06, 0xd3, 0x30, 0x45, 0x00, 0x06, 0x53, 0x84, 0x04, 0x08, 0x06,
    0x53, 0x44, 0x83, 0x1c, 0x04, 0x93, 0x94, 0x08, 0x07, 0x02, 0x11, 0x20, 0x9a, 0x03, 0x08, 0x8f,
    0x94, 0xa6, 0x56, 0x38, 0x06, 0x49, 0xb4, 0x61, 0x03, 0x09, 0xcd, 0xcc, 0x09, 0x08, 0x18, 0x01,
    0x05, 0xd4, 0x34, 0x50, 0x00, 0x06, 0x0d, 0x2c, 0xd3, 0x00, 0x05, 0xa1, 0x34, 0xe1, 0x00, 0x06,
    0xcd, 0xb4, 0x61, 0x03, 0x06, 0xaf, 0x20, 0xb3, 0x1c, 0x08, 0xab, 0x28, 0xd4, 0x86, 0x0d, 0x06,
    0x4b, 0x28, 0x96, 0x02, 0x06, 0x62, 0x91, 0x72, 0x0e, 0x05, 0xab, 0x50, 0x40, 0x00, 0x06, 0xab,
    0x28, 0x72, 0x00, 0x08, 0xab, 0x8c, 0x60, 0x86, 0x02, 0x06, 0x2b, 0x89, 0xc1, 0x00, 0x06, 0xab,
    0xa8, 0x87, 0x00, 0x05, 0x0b, 0x99, 0x55, 0x01, 0x08, 0x04, 0x1c, 0x20, 0xc8, 0x4a, 0x07, 0x07,
    0x10, 0x6a, 0x16, 0x00, 0x08, 0x62, 0x05, 0x25, 0x10, 0x72, 0x05, 0xab, 0x28, 0xd4, 0x00, 0x08,
    0x52, 0x1d, 0x33, 0xc0, 0x39, 0x05, 0x92, 0x00, 0x51, 0x01, 0x05, 0x12, 0x89, 0x55, 0x01, 0x06,
    0x12, 0x24, 0x33, 0x1a, 0x07, 0x12, 0x04, 0x08, 0xc0, 0x00, 0x06, 0x12, 0x84, 0x00, 0x08, 0x07,
    0x12, 0x20, 0x03, 0x28, 0x00, 0x06, 0x12, 0xcc, 0x42, 0x00, 0x07, 0x12, 0x2c, 0xa1, 0x0e, 0x00,
    0x05, 0x42, 0x16, 0x15, 0x00, 0x04, 0x52, 0xac, 0x0a, 0x04, 0x12, 0x80, 0x01
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
                case -179:
                    if (keycode == KC_SPC) return 0;
                    break;
                // w
                case -167:
                    if (keycode == KC_SPC) return 58;
                    if (keycode == KC_A) return 54;
                    if (keycode == KC_H) return 49;
                    if (keycode == KC_I) return 34;
                    if (keycode == KC_J) return 23;
                    if (keycode == KC_O) return 28;
                    if (keycode == KC_R) return 39;
                    if (keycode == KC_S) return 17;
                    if (keycode == KC_T) return 44;
                    if (keycode == KC_U) return 11;
                    if (keycode == KC_Y) return 6;
                    break;
                // v
                case -162:
                    if (keycode == KC_SPC) return 84;
                    if (keycode == KC_A) return 77;
                    if (keycode == KC_I) return 71;
                    if (keycode == KC_Y) return 63;
                    break;
                // t
                case -147:
                    if (keycode == KC_SPC) return 159;
                    if (keycode == KC_A) return 153;
                    if (keycode == KC_B) return 148;
                    if (keycode == KC_C) return 143;
                    if (keycode == KC_E) return 121;
                    if (keycode == KC_G) return 105;
                    if (keycode == KC_H) return 138;
                    if (keycode == KC_J) return 126;
                    if (keycode == KC_N) return 116;
                    if (keycode == KC_O) return 132;
                    if (keycode == KC_S) return 95;
                    if (keycode == KC_U) return 111;
                    if (keycode == KC_W) return 100;
                    if (keycode == KC_Y) return 88;
                    break;
                // s
                case -132:
                    if (keycode == KC_SPC) return 237;
                    if (keycode == KC_C) return 227;
                    if (keycode == KC_D) return 181;
                    if (keycode == KC_E) return 232;
                    if (keycode == KC_I) return 221;
                    if (keycode == KC_L) return 215;
                    if (keycode == KC_M) return 198;
                    if (keycode == KC_N) return 205;
                    if (keycode == KC_O) return 210;
                    if (keycode == KC_P) return 175;
                    if (keycode == KC_R) return 169;
                    if (keycode == KC_T) return 193;
                    if (keycode == KC_U) return 187;
                    if (keycode == KC_Y) return 164;
                    break;
                // r
                case -116:
                    if (keycode == KC_SPC) return 317;
                    if (keycode == KC_A) return 311;
                    if (keycode == KC_E) return 301;
                    if (keycode == KC_H) return 274;
                    if (keycode == KC_I) return 269;
                    if (keycode == KC_J) return 279;
                    if (keycode == KC_L) return 264;
                    if (keycode == KC_M) return 295;
                    if (keycode == KC_N) return 258;
                    if (keycode == KC_O) return 253;
                    if (keycode == KC_P) return 290;
                    if (keycode == KC_S) return 284;
                    if (keycode == KC_V) return 242;
                    if (keycode == KC_W) return 306;
                    if (keycode == KC_Y) return 248;
                    break;
                // p
                case -103:
                    if (keycode == KC_SPC) return 381;
                    if (keycode == KC_A) return 375;
                    if (keycode == KC_E) return 365;
                    if (keycode == KC_J) return 338;
                    if (keycode == KC_L) return 360;
                    if (keycode == KC_N) return 355;
                    if (keycode == KC_O) return 344;
                    if (keycode == KC_R) return 370;
                    if (keycode == KC_S) return 350;
                    if (keycode == KC_T) return 333;
                    if (keycode == KC_U) return 322;
                    if (keycode == KC_Y) return 327;
                    break;
                // n
                case -88:
                    if (keycode == KC_SPC) return 459;
                    if (keycode == KC_A) return 454;
                    if (keycode == KC_C) return 449;
                    if (keycode == KC_D) return 414;
                    if (keycode == KC_E) return 397;
                    if (keycode == KC_H) return 443;
                    if (keycode == KC_I) return 435;
                    if (keycode == KC_J) return 408;
                    if (keycode == KC_O) return 429;
                    if (keycode == KC_P) return 386;
                    if (keycode == KC_S) return 419;
                    if (keycode == KC_T) return 402;
                    if (keycode == KC_U) return 424;
                    if (keycode == KC_Y) return 391;
                    break;
                // m
                case -78:
                    if (keycode == KC_SPC) return 509;
                    if (keycode == KC_A) return 482;
                    if (keycode == KC_E) return 503;
                    if (keycode == KC_H) return 498;
                    if (keycode == KC_I) return 493;
                    if (keycode == KC_S) return 477;
                    if (keycode == KC_T) return 488;
                    if (keycode == KC_U) return 472;
                    if (keycode == KC_Y) return 467;
                    break;
                // l
                case -65:
                    if (keycode == KC_SPC) return 568;
                    if (keycode == KC_A) return 559;
                    if (keycode == KC_E) return 554;
                    if (keycode == KC_F) return 548;
                    if (keycode == KC_H) return 543;
                    if (keycode == KC_I) return 538;
                    if (keycode == KC_K) return 564;
                    if (keycode == KC_O) return 528;
                    if (keycode == KC_S) return 523;
                    if (keycode == KC_T) return 518;
                    if (keycode == KC_U) return 533;
                    if (keycode == KC_Y) return 513;
                    break;
                // k
                case -62:
                    if (keycode == KC_SPC) return 579;
                    if (keycode == KC_Y) return 573;
                    break;
                // g
                case -51:
                    if (keycode == KC_SPC) return 632;
                    if (keycode == KC_A) return 611;
                    if (keycode == KC_D) return 596;
                    if (keycode == KC_E) return 627;
                    if (keycode == KC_H) return 616;
                    if (keycode == KC_J) return 621;
                    if (keycode == KC_O) return 606;
                    if (keycode == KC_R) return 601;
                    if (keycode == KC_S) return 590;
                    if (keycode == KC_U) return 585;
                    break;
                // f
                case -39:
                    if (keycode == KC_SPC) return 692;
                    if (keycode == KC_A) return 687;
                    if (keycode == KC_G) return 677;
                    if (keycode == KC_I) return 666;
                    if (keycode == KC_L) return 656;
                    if (keycode == KC_N) return 671;
                    if (keycode == KC_O) return 648;
                    if (keycode == KC_S) return 661;
                    if (keycode == KC_T) return 682;
                    if (keycode == KC_U) return 637;
                    if (keycode == KC_W) return 642;
                    break;
                // d
                case -30:
                    if (keycode == KC_SPC) return 735;
                    if (keycode == KC_A) return 730;
                    if (keycode == KC_C) return 725;
                    if (keycode == KC_E) return 720;
                    if (keycode == KC_F) return 713;
                    if (keycode == KC_N) return 708;
                    if (keycode == KC_U) return 702;
                    if (keycode == KC_Y) return 696;
                    break;
                // c
                case -15:
                    if (keycode == KC_SPC) return 810;
                    if (keycode == KC_A) return 804;
                    if (keycode == KC_D) return 745;
                    if (keycode == KC_E) return 798;
                    if (keycode == KC_H) return 792;
                    if (keycode == KC_I) return 787;
                    if (keycode == KC_L) return 782;
                    if (keycode == KC_N) return 777;
                    if (keycode == KC_O) return 771;
                    if (keycode == KC_R) return 756;
                    if (keycode == KC_S) return 766;
                    if (keycode == KC_T) return 751;
                    if (keycode == KC_V) return 761;
                    if (keycode == KC_Y) return 740;
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return 873;
                    if (keycode == KC_A) return 864;
                    if (keycode == KC_D) return 853;
                    if (keycode == KC_E) return 858;
                    if (keycode == KC_H) return 831;
                    if (keycode == KC_K) return 869;
                    if (keycode == KC_L) return 847;
                    if (keycode == KC_N) return 826;
                    if (keycode == KC_R) return 821;
                    if (keycode == KC_T) return 842;
                    if (keycode == KC_U) return 815;
                    if (keycode == KC_W) return 836;
                    break;
                case -1:
                    if (keycode == KC_B) return -2;
                    if (keycode == KC_C) return -15;
                    if (keycode == KC_D) return -30;
                    if (keycode == KC_F) return -39;
                    if (keycode == KC_G) return -51;
                    if (keycode == KC_K) return -62;
                    if (keycode == KC_L) return -65;
                    if (keycode == KC_M) return -78;
                    if (keycode == KC_N) return -88;
                    if (keycode == KC_P) return -103;
                    if (keycode == KC_R) return -116;
                    if (keycode == KC_S) return -132;
                    if (keycode == KC_T) return -147;
                    if (keycode == KC_V) return -162;
                    if (keycode == KC_W) return -167;
                    if (keycode == KC_Z) return -179;
                    break;
    default:
        // Invalid transition, stop chord mode
        return -1000;
    }
    return -1000;
}

void chord_output(int state) {
    switch (state) {
        // State is byte offset directly
                chord_decode_send(chord_data + state);
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
