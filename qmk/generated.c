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
    'e', 'r', 'a', 't', 'o', 'n', 'i', 's', 'l', 'u', 'h', 'c', 'g', 'y', 'd', 'm', 'b', 'w', 'p', 'v', 'k', 'f', '\'', 'j', 'z', 'q', ' '
};

// Global buffer containing all 5-bit packed chord strings
static const uint8_t chord_data[] = {
    0x04, 0x18, 0x04, 0x02, 0x08, 0x24, 0x30, 0x51, 0x0c, 0x06, 0x07, 0x01, 0x08, 0x64, 0x30, 0x00,
    0x08, 0x91, 0x24, 0xe4, 0x8a, 0x1d, 0x05, 0x91, 0x84, 0xd0, 0x00, 0x05, 0x51, 0x81, 0x00, 0x00,
    0x07, 0xd1, 0x0c, 0x45, 0xd2, 0x00, 0x05, 0x31, 0x90, 0xc2, 0x00, 0x06, 0xd1, 0x14, 0x47, 0x22,
    0x05, 0x51, 0x99, 0xa5, 0x00, 0x04, 0x11, 0x04, 0x00, 0x04, 0x51, 0x20, 0x0a, 0x05, 0x91, 0x24,
    0xe4, 0x00, 0x0a, 0x60, 0x82, 0xd0, 0x86, 0x32, 0x85, 0x01, 0x05, 0x53, 0xa0, 0x04, 0x00, 0x05,
    0x05, 0x4c, 0x10, 0x00, 0x04, 0x64, 0x82, 0x00, 0x08, 0x07, 0x84, 0x69, 0x16, 0x38, 0x04, 0x13,
    0x84, 0x06, 0x09, 0x62, 0x0a, 0x83, 0x04, 0x44, 0x00, 0x04, 0x4a, 0x4c, 0x00, 0x09, 0x43, 0x89,
    0x42, 0x75, 0x23, 0x09, 0x06, 0x43, 0x91, 0xc4, 0x14, 0x05, 0x43, 0x81, 0x00, 0x00, 0x07, 0x43,
    0x91, 0xc4, 0xd4, 0x00, 0x07, 0x43, 0x05, 0x92, 0x98, 0x02, 0x04, 0xc3, 0x3c, 0x00, 0x06, 0x43,
    0x89, 0x42, 0x0f, 0x06, 0x85, 0x0c, 0xb3, 0x00, 0x07, 0x8b, 0x94, 0x21, 0xd6, 0x00, 0x05, 0x43,
    0x99, 0x42, 0x01, 0x06, 0x51, 0x9c, 0x62, 0x07, 0x06, 0xa7, 0x9d, 0x01, 0x1e, 0x07, 0x27, 0x49,
    0x49, 0xc2, 0x00, 0x08, 0x27, 0x05, 0x19, 0xcc, 0x01, 0x06, 0x07, 0x91, 0x88, 0x1a, 0x07, 0x27,
    0xc1, 0x0b, 0xd6, 0x00, 0x07, 0xc7, 0x20, 0x50, 0x16, 0x00, 0x05, 0x47, 0x89, 0x00, 0x00, 0x06,
    0x07, 0x88, 0xb0, 0x14, 0x04, 0x47, 0x3c, 0x00, 0x06, 0x47, 0x91, 0x84, 0x1c, 0x05, 0x0d, 0x88,
    0x70, 0x00, 0x04, 0x23, 0x24, 0x00, 0x06, 0x22, 0x90, 0x54, 0x1c, 0x06, 0x01, 0x8c, 0x14, 0x0a,
    0x05, 0xc1, 0x30, 0x35, 0x00, 0x06, 0x01, 0x4c, 0x03, 0x22, 0x05, 0x01, 0x08, 0xd7, 0x00, 0x07,
    0x32, 0x10, 0x16, 0xc4, 0x03, 0x06, 0x01, 0x08, 0x84, 0x1a, 0x08, 0x32, 0x10, 0x28, 0x20, 0x6a,
    0x06, 0x32, 0x41, 0x64, 0x16, 0x06, 0x52, 0x04, 0x50, 0x06, 0x07, 0x32, 0x10, 0x97, 0xd6, 0x00,
    0x07, 0x32, 0x10, 0x88, 0xc0, 0x03, 0x05, 0x92, 0x98, 0x32, 0x00, 0x05, 0x12, 0x89, 0x05, 0x00,
    0x07, 0x32, 0x98, 0x29, 0x56, 0x03, 0x06, 0x12, 0x10, 0x89, 0x00, 0x07, 0x8b, 0x3c, 0x29, 0x4a,
    0x03, 0x06, 0xa0, 0x90, 0xc4, 0x14, 0x04, 0x05, 0x88, 0x00, 0x07, 0xa2, 0x90, 0xa1, 0x40, 0x00,
    0x07, 0xa6, 0x9c, 0x01, 0x84, 0x03, 0x0a, 0xa9, 0x98, 0x09, 0xc2, 0x31, 0xa3, 0x01, 0x08, 0xa2,
    0xb4, 0xa1, 0x4c, 0x61, 0x06, 0x25, 0x3d, 0x08, 0x02, 0x06, 0xa2, 0xb4, 0x28, 0x1a, 0x0a, 0xa9,
    0x38, 0x10, 0xce, 0x10, 0xc5, 0x01, 0x06, 0xaf, 0x1d, 0x80, 0x2a, 0x05, 0x2f, 0x1d, 0xb3, 0x00,
    0x04, 0x8f, 0x9c, 0x01, 0x05, 0x4f, 0x5c, 0x12, 0x00, 0x06, 0xcf, 0x94, 0x34, 0x00, 0x05, 0xcf,
    0x30, 0x35, 0x00, 0x07, 0x0f, 0x9c, 0x23, 0x18, 0x00, 0x07, 0x87, 0x3c, 0x40, 0x0a, 0x00, 0x04,
    0x8f, 0x04, 0x00, 0x06, 0x02, 0x45, 0xd1, 0x0e, 0x06, 0x02, 0x3d, 0x72, 0x06, 0x05, 0x48, 0x0c,
    0x10, 0x00, 0x05, 0x02, 0x91, 0xc2, 0x00, 0x05, 0x48, 0x04, 0x06, 0x00, 0x05, 0xc8, 0x30, 0x35,
    0x00, 0x06, 0x0a, 0x08, 0x34, 0x14, 0x05, 0x08, 0x88, 0x09, 0x00, 0x05, 0x48, 0x24, 0xa6, 0x00,
    0x06, 0x08, 0x14, 0x36, 0x14, 0x07, 0x39, 0x99, 0x45, 0x51, 0x03, 0x04, 0x91, 0x04, 0x0a, 0x04,
    0xb4, 0x90, 0x08, 0x04, 0x37, 0x9d, 0x01, 0x04, 0xd4, 0x14, 0x07, 0x04, 0x14, 0x00, 0x09, 0x04,
    0x4f, 0x50, 0x00, 0x08, 0x39, 0x81, 0x33, 0x0c, 0x29, 0x05, 0x60, 0x82, 0xd0, 0x00, 0x05, 0x2c,
    0x81, 0x73, 0x00, 0x05, 0x2c, 0x00, 0x31, 0x00, 0x05, 0x2c, 0x90, 0x24, 0x01, 0x07, 0x0c, 0x14,
    0x10, 0x04, 0x02, 0x06, 0xcc, 0x4c, 0x53, 0x18, 0x06, 0xc1, 0x30, 0x35, 0x0e, 0x05, 0x10, 0x30,
    0x51, 0x00, 0x06, 0x0c, 0x89, 0xb2, 0x00, 0x05, 0x82, 0x09, 0x53, 0x00, 0x05, 0x95, 0x84, 0xd1,
    0x00, 0x05, 0x95, 0xa4, 0xe2, 0x00, 0x08, 0x87, 0xd4, 0x11, 0x45, 0x00, 0x0b, 0xa6, 0x54, 0x12,
    0x9e, 0x18, 0x86, 0x14, 0x05, 0xd5, 0x84, 0x33, 0x00, 0x06, 0xd5, 0x14, 0x06, 0x02, 0x05, 0xd5,
    0xd4, 0xa1, 0x00, 0x04, 0x15, 0x00, 0x04, 0x06, 0x55, 0x3c, 0x83, 0x1a, 0x04, 0x35, 0x90, 0x07,
    0x06, 0x4a, 0xb8, 0x62, 0x07, 0x07, 0x02, 0x05, 0x20, 0x5c, 0x03, 0x08, 0x32, 0x10, 0x97, 0xd6,
    0x38, 0x05, 0x43, 0x01, 0x13, 0x00, 0x07, 0x8e, 0x80, 0x53, 0xec, 0x00, 0x06, 0x2e, 0x05, 0x53,
    0x18, 0x05, 0x43, 0x99, 0xe0, 0x00, 0x05, 0xd3, 0x38, 0x40, 0x00, 0x05, 0x83, 0x38, 0xd1, 0x00,
    0x06, 0xce, 0xb8, 0x62, 0x07, 0x08, 0x8b, 0x24, 0xe4, 0x8a, 0x1d, 0x06, 0x92, 0x20, 0xb3, 0x1a,
    0x07, 0x2b, 0x85, 0x00, 0xca, 0x00, 0x06, 0x62, 0x05, 0x72, 0x0e, 0x08, 0x8b, 0x94, 0x61, 0x4a,
    0x02, 0x07, 0x32, 0x90, 0x0b, 0xd6, 0x00, 0x05, 0x0b, 0x99, 0x45, 0x01, 0x08, 0x01, 0x1c, 0x20,
    0xc2, 0x52, 0x07, 0x07, 0x84, 0x69, 0x16, 0x00, 0x08, 0x62, 0x8d, 0x24, 0x10, 0x6a, 0x05, 0x8b,
    0x24, 0xe4, 0x00, 0x0d, 0x04, 0x1e, 0x10, 0xa6, 0x80, 0x06, 0x99, 0xd1, 0x00, 0x04, 0x90, 0xb8,
    0x06, 0x08, 0x30, 0x1d, 0x53, 0xc0, 0x39, 0x05, 0x30, 0x00, 0x41, 0x01, 0x06, 0x10, 0x2c, 0xf2,
    0x00, 0x07, 0x10, 0x8c, 0x08, 0x40, 0x01, 0x05, 0x10, 0x98, 0xc2, 0x00, 0x06, 0x10, 0x28, 0x53,
    0x1c, 0x07, 0x10, 0x2c, 0x91, 0x0e, 0x00, 0x05, 0x02, 0x92, 0x34, 0x00, 0x04, 0x10, 0x80, 0x02
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
                case -163:
                    if (keycode == KC_SPC) return 10;
                    if (keycode == KC_A) return 4;
                    if (keycode == KC_E) return 0;
                    break;
                // w
                case -152:
                    if (keycode == KC_SPC) return 61;
                    if (keycode == KC_COMMA) return 16;
                    if (keycode == KC_A) return 57;
                    if (keycode == KC_E) return 53;
                    if (keycode == KC_H) return 48;
                    if (keycode == KC_I) return 43;
                    if (keycode == KC_J) return 38;
                    if (keycode == KC_O) return 32;
                    if (keycode == KC_R) return 27;
                    if (keycode == KC_Y) return 22;
                    break;
                // v
                case -143:
                    if (keycode == KC_SPC) return 105;
                    if (keycode == KC_A) return 98;
                    if (keycode == KC_E) return 94;
                    if (keycode == KC_I) return 88;
                    if (keycode == KC_O) return 84;
                    if (keycode == KC_R) return 79;
                    if (keycode == KC_U) return 74;
                    if (keycode == KC_Y) return 66;
                    break;
                // t
                case -132:
                    if (keycode == KC_SPC) return 158;
                    if (keycode == KC_A) return 152;
                    if (keycode == KC_E) return 147;
                    if (keycode == KC_H) return 142;
                    if (keycode == KC_I) return 138;
                    if (keycode == KC_J) return 132;
                    if (keycode == KC_O) return 126;
                    if (keycode == KC_R) return 121;
                    if (keycode == KC_U) return 116;
                    if (keycode == KC_Y) return 109;
                    break;
                // s
                case -120:
                    if (keycode == KC_SPC) return 216;
                    if (keycode == KC_COMMA) return 163;
                    if (keycode == KC_A) return 212;
                    if (keycode == KC_E) return 207;
                    if (keycode == KC_H) return 202;
                    if (keycode == KC_I) return 196;
                    if (keycode == KC_J) return 190;
                    if (keycode == KC_O) return 185;
                    if (keycode == KC_R) return 179;
                    if (keycode == KC_U) return 173;
                    if (keycode == KC_Y) return 168;
                    break;
                // r
                case -110:
                    if (keycode == KC_SPC) return 261;
                    if (keycode == KC_A) return 255;
                    if (keycode == KC_E) return 250;
                    if (keycode == KC_H) return 245;
                    if (keycode == KC_I) return 240;
                    if (keycode == KC_J) return 235;
                    if (keycode == KC_O) return 230;
                    if (keycode == KC_U) return 226;
                    if (keycode == KC_Y) return 221;
                    break;
                // p
                case -100:
                    if (keycode == KC_SPC) return 310;
                    if (keycode == KC_A) return 304;
                    if (keycode == KC_E) return 299;
                    if (keycode == KC_I) return 294;
                    if (keycode == KC_J) return 288;
                    if (keycode == KC_O) return 282;
                    if (keycode == KC_R) return 277;
                    if (keycode == KC_U) return 272;
                    if (keycode == KC_Y) return 266;
                    break;
                // n
                case -89:
                    if (keycode == KC_SPC) return 366;
                    if (keycode == KC_A) return 361;
                    if (keycode == KC_E) return 356;
                    if (keycode == KC_H) return 350;
                    if (keycode == KC_I) return 342;
                    if (keycode == KC_J) return 336;
                    if (keycode == KC_O) return 330;
                    if (keycode == KC_R) return 326;
                    if (keycode == KC_U) return 321;
                    if (keycode == KC_Y) return 315;
                    break;
                // m
                case -79:
                    if (keycode == KC_SPC) return 415;
                    if (keycode == KC_A) return 409;
                    if (keycode == KC_E) return 403;
                    if (keycode == KC_H) return 398;
                    if (keycode == KC_I) return 393;
                    if (keycode == KC_J) return 388;
                    if (keycode == KC_O) return 384;
                    if (keycode == KC_U) return 379;
                    if (keycode == KC_Y) return 374;
                    break;
                // l
                case -68:
                    if (keycode == KC_SPC) return 464;
                    if (keycode == KC_A) return 459;
                    if (keycode == KC_E) return 454;
                    if (keycode == KC_H) return 449;
                    if (keycode == KC_I) return 444;
                    if (keycode == KC_J) return 439;
                    if (keycode == KC_O) return 434;
                    if (keycode == KC_R) return 429;
                    if (keycode == KC_U) return 424;
                    if (keycode == KC_Y) return 419;
                    break;
                // k
                case -59:
                    if (keycode == KC_SPC) return 499;
                    if (keycode == KC_A) return 495;
                    if (keycode == KC_E) return 491;
                    if (keycode == KC_I) return 487;
                    if (keycode == KC_J) return 483;
                    if (keycode == KC_O) return 479;
                    if (keycode == KC_R) return 475;
                    if (keycode == KC_Y) return 469;
                    break;
                // g
                case -48:
                    if (keycode == KC_SPC) return 551;
                    if (keycode == KC_A) return 546;
                    if (keycode == KC_E) return 541;
                    if (keycode == KC_H) return 536;
                    if (keycode == KC_I) return 531;
                    if (keycode == KC_J) return 525;
                    if (keycode == KC_O) return 520;
                    if (keycode == KC_R) return 515;
                    if (keycode == KC_U) return 510;
                    if (keycode == KC_Y) return 505;
                    break;
                // f
                case -37:
                    if (keycode == KC_SPC) return 604;
                    if (keycode == KC_A) return 599;
                    if (keycode == KC_E) return 595;
                    if (keycode == KC_H) return 590;
                    if (keycode == KC_I) return 585;
                    if (keycode == KC_J) return 580;
                    if (keycode == KC_O) return 572;
                    if (keycode == KC_R) return 566;
                    if (keycode == KC_U) return 561;
                    if (keycode == KC_Y) return 556;
                    break;
                // d
                case -26:
                    if (keycode == KC_SPC) return 656;
                    if (keycode == KC_COMMA) return 608;
                    if (keycode == KC_A) return 651;
                    if (keycode == KC_E) return 646;
                    if (keycode == KC_H) return 641;
                    if (keycode == KC_I) return 636;
                    if (keycode == KC_O) return 630;
                    if (keycode == KC_R) return 625;
                    if (keycode == KC_U) return 619;
                    if (keycode == KC_Y) return 613;
                    break;
                // c
                case -14:
                    if (keycode == KC_SPC) return 718;
                    if (keycode == KC_COMMA) return 661;
                    if (keycode == KC_A) return 712;
                    if (keycode == KC_E) return 706;
                    if (keycode == KC_H) return 700;
                    if (keycode == KC_I) return 695;
                    if (keycode == KC_J) return 689;
                    if (keycode == KC_O) return 683;
                    if (keycode == KC_R) return 678;
                    if (keycode == KC_U) return 672;
                    if (keycode == KC_Y) return 667;
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return 780;
                    if (keycode == KC_COMMA) return 723;
                    if (keycode == KC_A) return 775;
                    if (keycode == KC_E) return 769;
                    if (keycode == KC_H) return 764;
                    if (keycode == KC_I) return 759;
                    if (keycode == KC_J) return 753;
                    if (keycode == KC_O) return 748;
                    if (keycode == KC_R) return 743;
                    if (keycode == KC_U) return 737;
                    if (keycode == KC_Y) return 733;
                    break;
                case -1:
                    if (keycode == KC_B) return -2;
                    if (keycode == KC_C) return -14;
                    if (keycode == KC_D) return -26;
                    if (keycode == KC_F) return -37;
                    if (keycode == KC_G) return -48;
                    if (keycode == KC_K) return -59;
                    if (keycode == KC_L) return -68;
                    if (keycode == KC_M) return -79;
                    if (keycode == KC_N) return -89;
                    if (keycode == KC_P) return -100;
                    if (keycode == KC_R) return -110;
                    if (keycode == KC_S) return -120;
                    if (keycode == KC_T) return -132;
                    if (keycode == KC_V) return -143;
                    if (keycode == KC_W) return -152;
                    if (keycode == KC_Z) return -163;
                    break;
    default:
        // Invalid transition, stop chord mode
        return -1000;
    }
    return -1000;
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
