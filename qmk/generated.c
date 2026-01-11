/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int alternateLayer = -1;
int layer = _BASE;
# #define CHORD_INACTIVE -10000
int chord_state = CHORD_INACTIVE; // -1 = root, other negative = transition states, non-negative = byte offsets
int chord_depth = 0; // Track number of letters in current chord

// Chord string decoder lookup table (5-bit codes -> characters)
static const char chord_char_lookup[] = {
    'e', 'r', 'a', 't', 'o', 'n', 'i', 's', 'l', 'u', 'h', 'c', 'g', 'y', 'd', 'm', 'p', 'b', 'w', 'v', 'k', 'f', '\'', 'x', 'z', 'j', 'q', ' '
};

// Global buffer containing all 5-bit packed chord strings
static const uint8_t chord_data[] = {
    0x05, 0xe2, 0xb4, 0xb2, 0x00, 0x04, 0x98, 0x14, 0x00, 0x04, 0xc7, 0x60, 0x00, 0x04, 0x18, 0x04,
    0x02, 0x08, 0x24, 0x30, 0x51, 0x0c, 0x06, 0x07, 0x01, 0x08, 0x64, 0x30, 0x00, 0x06, 0xe0, 0x42,
    0x12, 0x06, 0x09, 0xe0, 0x2e, 0x00, 0x87, 0x21, 0x05, 0x08, 0xe0, 0x9a, 0x33, 0x4c, 0x61, 0x07,
    0xe0, 0x82, 0x95, 0x06, 0x00, 0x07, 0xe0, 0x8a, 0x07, 0x11, 0x00, 0x08, 0x92, 0x24, 0xe4, 0x8a,
    0x1d, 0x05, 0x42, 0x0a, 0x33, 0x00, 0x05, 0x92, 0x84, 0xd0, 0x00, 0x05, 0x52, 0x81, 0x00, 0x00,
    0x07, 0xd2, 0x0c, 0x45, 0xd2, 0x00, 0x05, 0x32, 0x90, 0xc2, 0x00, 0x06, 0xd2, 0x14, 0x47, 0x24,
    0x05, 0x52, 0x99, 0xa5, 0x00, 0x04, 0x12, 0x04, 0x00, 0x04, 0x52, 0x20, 0x0a, 0x05, 0x92, 0x24,
    0xe4, 0x00, 0x04, 0x93, 0x18, 0x07, 0x0a, 0x60, 0x82, 0xd0, 0x86, 0x32, 0x85, 0x01, 0x05, 0x53,
    0xa0, 0x04, 0x00, 0x05, 0x05, 0x4c, 0x10, 0x00, 0x04, 0x64, 0x82, 0x00, 0x08, 0x07, 0x84, 0x69,
    0x16, 0x38, 0x04, 0x13, 0x84, 0x06, 0x09, 0x62, 0x0a, 0x83, 0x44, 0x44, 0x00, 0x04, 0x4a, 0x4c,
    0x00, 0x04, 0xa3, 0x41, 0x00, 0x09, 0x43, 0x89, 0x42, 0x77, 0x23, 0x09, 0x06, 0x43, 0x91, 0xc4,
    0x14, 0x05, 0x43, 0x81, 0x00, 0x00, 0x07, 0x43, 0x91, 0xc4, 0xd4, 0x00, 0x07, 0x43, 0x05, 0x92,
    0x98, 0x02, 0x04, 0xc3, 0x3c, 0x00, 0x06, 0x43, 0x89, 0x42, 0x0f, 0x06, 0x85, 0x0c, 0xb3, 0x00,
    0x07, 0x8b, 0x94, 0x21, 0xd6, 0x00, 0x05, 0x43, 0x99, 0x42, 0x01, 0x06, 0x52, 0x9c, 0x62, 0x07,
    0x06, 0x67, 0x04, 0x53, 0x18, 0x06, 0xa7, 0x9d, 0x01, 0x1e, 0x07, 0x27, 0x41, 0x48, 0xc2, 0x00,
    0x08, 0x27, 0x05, 0x18, 0xcc, 0x01, 0x06, 0x07, 0x11, 0x89, 0x1a, 0x07, 0x27, 0xc5, 0x0c, 0xd6,
    0x00, 0x07, 0xc7, 0x20, 0x50, 0x16, 0x00, 0x05, 0x47, 0x89, 0x00, 0x00, 0x06, 0x07, 0x88, 0xb0,
    0x14, 0x04, 0x47, 0x3c, 0x00, 0x06, 0x47, 0x91, 0x84, 0x1c, 0x05, 0x20, 0x04, 0x12, 0x00, 0x05,
    0x0d, 0x88, 0x70, 0x00, 0x04, 0x23, 0x24, 0x00, 0x06, 0x22, 0x90, 0x54, 0x1c, 0x06, 0x01, 0x8c,
    0x14, 0x0a, 0x05, 0xc1, 0x30, 0x35, 0x00, 0x06, 0x01, 0x4c, 0x03, 0x24, 0x05, 0x01, 0x08, 0xd7,
    0x00, 0x07, 0x30, 0x10, 0x16, 0xc4, 0x03, 0x06, 0x01, 0x08, 0x84, 0x1a, 0x07, 0x30, 0x90, 0x67,
    0x0e, 0x00, 0x08, 0x30, 0x90, 0x28, 0x22, 0x6a, 0x06, 0x30, 0x45, 0x64, 0x16, 0x06, 0x50, 0x04,
    0x50, 0x06, 0x07, 0x30, 0x10, 0x97, 0xd6, 0x00, 0x07, 0x30, 0x90, 0x88, 0xc0, 0x03, 0x05, 0x90,
    0x98, 0x32, 0x00, 0x05, 0x10, 0x89, 0x05, 0x00, 0x07, 0x30, 0x98, 0x29, 0x56, 0x03, 0x06, 0x10,
    0x10, 0x88, 0x00, 0x04, 0x25, 0x21, 0x04, 0x07, 0x8b, 0x3c, 0x28, 0x4a, 0x03, 0x06, 0xa0, 0x90,
    0xc4, 0x14, 0x04, 0x05, 0x88, 0x00, 0x07, 0xa2, 0x90, 0xa1, 0x40, 0x00, 0x07, 0xa6, 0x9c, 0x01,
    0x84, 0x03, 0x0a, 0xa9, 0x98, 0x09, 0xc2, 0x31, 0xa3, 0x01, 0x08, 0xa2, 0xb4, 0xa1, 0x4c, 0x61,
    0x06, 0x25, 0xbd, 0x08, 0x02, 0x06, 0xa2, 0x34, 0x29, 0x1a, 0x0a, 0xa9, 0x38, 0x10, 0xce, 0x10,
    0xc5, 0x01, 0x06, 0x0f, 0x0c, 0x45, 0x1c, 0x06, 0xaf, 0x1d, 0x80, 0x2a, 0x05, 0x2f, 0x1d, 0xb3,
    0x00, 0x04, 0x8f, 0x9c, 0x01, 0x05, 0x4f, 0x64, 0x12, 0x00, 0x06, 0xcf, 0x94, 0x34, 0x00, 0x05,
    0xcf, 0x30, 0x35, 0x00, 0x07, 0x0f, 0x9c, 0x23, 0x18, 0x00, 0x07, 0x87, 0x3c, 0x40, 0x0a, 0x00,
    0x04, 0x8f, 0x04, 0x00, 0x05, 0x0b, 0x89, 0x73, 0x00, 0x06, 0x02, 0x49, 0xd1, 0x0e, 0x06, 0x02,
    0x3d, 0x72, 0x06, 0x05, 0x48, 0x0c, 0x10, 0x00, 0x05, 0x02, 0x91, 0xc2, 0x00, 0x05, 0x48, 0x04,
    0x06, 0x00, 0x05, 0xc8, 0x30, 0x35, 0x00, 0x06, 0x0a, 0x08, 0x34, 0x14, 0x05, 0x08, 0x88, 0x09,
    0x00, 0x05, 0x48, 0x24, 0xa6, 0x00, 0x06, 0x08, 0x14, 0x36, 0x14, 0x03, 0x14, 0x34, 0x07, 0x3a,
    0x99, 0x45, 0x51, 0x03, 0x04, 0x92, 0x04, 0x0a, 0x04, 0xb4, 0x10, 0x09, 0x04, 0x39, 0x9d, 0x01,
    0x04, 0xd4, 0x14, 0x07, 0x04, 0x14, 0x00, 0x08, 0x04, 0x4f, 0x50, 0x00, 0x08, 0x3a, 0x81, 0x33,
    0x0c, 0x29, 0x05, 0x60, 0x82, 0xd0, 0x00, 0x05, 0x2c, 0x81, 0x73, 0x00, 0x05, 0x2c, 0x00, 0x31,
    0x00, 0x05, 0x2c, 0x90, 0x04, 0x01, 0x07, 0x0c, 0x14, 0x10, 0x04, 0x02, 0x06, 0xcc, 0x4c, 0x53,
    0x18, 0x06, 0xc1, 0x30, 0x35, 0x0e, 0x05, 0x11, 0x30, 0x51, 0x00, 0x06, 0x0c, 0x89, 0xb2, 0x00,
    0x05, 0x82, 0x09, 0x53, 0x00, 0x05, 0x55, 0xa0, 0x03, 0x00, 0x05, 0x95, 0x84, 0xd1, 0x00, 0x05,
    0x95, 0xa4, 0xe2, 0x00, 0x08, 0x87, 0xd4, 0x21, 0x45, 0x00, 0x0b, 0xa6, 0x54, 0x12, 0x9e, 0x18,
    0x86, 0x14, 0x05, 0xd5, 0x84, 0x33, 0x00, 0x06, 0xd5, 0x14, 0x06, 0x02, 0x05, 0xd5, 0xd4, 0xa1,
    0x00, 0x04, 0x15, 0x00, 0x04, 0x06, 0x55, 0x3c, 0x83, 0x1a, 0x04, 0x35, 0x90, 0x07, 0x06, 0x4a,
    0xb8, 0x62, 0x07, 0x04, 0x4e, 0x0c, 0x01, 0x07, 0x02, 0x05, 0x20, 0x5c, 0x03, 0x08, 0x30, 0x10,
    0x97, 0xd6, 0x38, 0x05, 0x43, 0x01, 0x13, 0x00, 0x07, 0x8e, 0x80, 0x53, 0xec, 0x00, 0x06, 0x2e,
    0x05, 0x53, 0x18, 0x05, 0x43, 0x99, 0xe0, 0x00, 0x05, 0xd3, 0x38, 0x40, 0x00, 0x05, 0x83, 0x38,
    0xd1, 0x00, 0x06, 0xce, 0xb8, 0x62, 0x07, 0x08, 0x8b, 0x24, 0xe4, 0x8a, 0x1d, 0x05, 0x8b, 0x94,
    0x33, 0x00, 0x06, 0x90, 0x20, 0xb3, 0x1a, 0x07, 0x2b, 0x85, 0x00, 0xca, 0x00, 0x06, 0x62, 0x05,
    0x72, 0x0e, 0x08, 0x8b, 0x94, 0x61, 0x4a, 0x02, 0x07, 0x30, 0x90, 0x0c, 0xd6, 0x00, 0x05, 0x0b,
    0x99, 0x45, 0x01, 0x08, 0x01, 0x1c, 0x20, 0xc2, 0x52, 0x07, 0x07, 0x84, 0x69, 0x16, 0x00, 0x08,
    0x62, 0x8d, 0x24, 0x10, 0x6a, 0x05, 0x8b, 0x24, 0xe4, 0x00, 0x0d, 0x24, 0x1e, 0x10, 0xa6, 0x88,
    0x06, 0x99, 0xd1, 0x00, 0x07, 0x91, 0x10, 0x04, 0x44, 0x01, 0x04, 0x91, 0xb8, 0x06, 0x08, 0x31,
    0x1d, 0x53, 0xc0, 0x39, 0x05, 0x31, 0x00, 0x41, 0x01, 0x06, 0x11, 0x2c, 0xf2, 0x00, 0x07, 0x11,
    0x0c, 0x09, 0x40, 0x01, 0x05, 0x11, 0x98, 0xc2, 0x00, 0x06, 0x11, 0x28, 0x53, 0x1c, 0x07, 0x11,
    0x2c, 0x91, 0x0e, 0x00, 0x05, 0x22, 0x92, 0x34, 0x00, 0x04, 0x11, 0x80, 0x02
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
                case -183:
                    if (keycode == KC_SPC) return 23;
                    if (keycode == KC_DOT) return 0;
                    if (keycode == KC_A) return 17;
                    if (keycode == KC_E) return 13;
                    if (keycode == KC_I) return 9;
                    if (keycode == KC_O) return 5;
                    break;
                // x
                case -177:
                    if (keycode == KC_DOT) return 29;
                    if (keycode == KC_A) return 53;
                    if (keycode == KC_E) return 47;
                    if (keycode == KC_I) return 41;
                    if (keycode == KC_J) return 34;
                    break;
                // w
                case -165:
                    if (keycode == KC_SPC) return 109;
                    if (keycode == KC_COMMA) return 59;
                    if (keycode == KC_DOT) return 65;
                    if (keycode == KC_A) return 105;
                    if (keycode == KC_E) return 101;
                    if (keycode == KC_H) return 96;
                    if (keycode == KC_I) return 91;
                    if (keycode == KC_J) return 86;
                    if (keycode == KC_O) return 80;
                    if (keycode == KC_R) return 75;
                    if (keycode == KC_Y) return 70;
                    break;
                // v
                case -155:
                    if (keycode == KC_SPC) return 157;
                    if (keycode == KC_DOT) return 114;
                    if (keycode == KC_A) return 150;
                    if (keycode == KC_E) return 146;
                    if (keycode == KC_I) return 140;
                    if (keycode == KC_O) return 136;
                    if (keycode == KC_R) return 131;
                    if (keycode == KC_U) return 126;
                    if (keycode == KC_Y) return 118;
                    break;
                // t
                case -143:
                    if (keycode == KC_SPC) return 214;
                    if (keycode == KC_DOT) return 161;
                    if (keycode == KC_A) return 208;
                    if (keycode == KC_E) return 203;
                    if (keycode == KC_H) return 198;
                    if (keycode == KC_I) return 194;
                    if (keycode == KC_J) return 188;
                    if (keycode == KC_O) return 182;
                    if (keycode == KC_R) return 177;
                    if (keycode == KC_U) return 172;
                    if (keycode == KC_Y) return 165;
                    break;
                // s
                case -130:
                    if (keycode == KC_SPC) return 277;
                    if (keycode == KC_COMMA) return 219;
                    if (keycode == KC_DOT) return 224;
                    if (keycode == KC_A) return 273;
                    if (keycode == KC_E) return 268;
                    if (keycode == KC_H) return 263;
                    if (keycode == KC_I) return 257;
                    if (keycode == KC_J) return 251;
                    if (keycode == KC_O) return 246;
                    if (keycode == KC_R) return 240;
                    if (keycode == KC_U) return 234;
                    if (keycode == KC_Y) return 229;
                    break;
                // r
                case -119:
                    if (keycode == KC_SPC) return 327;
                    if (keycode == KC_DOT) return 282;
                    if (keycode == KC_A) return 321;
                    if (keycode == KC_E) return 316;
                    if (keycode == KC_H) return 311;
                    if (keycode == KC_I) return 306;
                    if (keycode == KC_J) return 301;
                    if (keycode == KC_O) return 296;
                    if (keycode == KC_U) return 292;
                    if (keycode == KC_Y) return 287;
                    break;
                // p
                case -108:
                    if (keycode == KC_SPC) return 382;
                    if (keycode == KC_DOT) return 332;
                    if (keycode == KC_A) return 376;
                    if (keycode == KC_E) return 371;
                    if (keycode == KC_I) return 366;
                    if (keycode == KC_J) return 360;
                    if (keycode == KC_O) return 354;
                    if (keycode == KC_R) return 349;
                    if (keycode == KC_U) return 344;
                    if (keycode == KC_Y) return 338;
                    break;
                // n
                case -96:
                    if (keycode == KC_SPC) return 442;
                    if (keycode == KC_DOT) return 387;
                    if (keycode == KC_A) return 437;
                    if (keycode == KC_E) return 432;
                    if (keycode == KC_H) return 426;
                    if (keycode == KC_I) return 418;
                    if (keycode == KC_J) return 412;
                    if (keycode == KC_O) return 406;
                    if (keycode == KC_R) return 402;
                    if (keycode == KC_U) return 397;
                    if (keycode == KC_Y) return 391;
                    break;
                // m
                case -85:
                    if (keycode == KC_SPC) return 496;
                    if (keycode == KC_DOT) return 450;
                    if (keycode == KC_A) return 490;
                    if (keycode == KC_E) return 484;
                    if (keycode == KC_H) return 479;
                    if (keycode == KC_I) return 474;
                    if (keycode == KC_J) return 469;
                    if (keycode == KC_O) return 465;
                    if (keycode == KC_U) return 460;
                    if (keycode == KC_Y) return 455;
                    break;
                // l
                case -73:
                    if (keycode == KC_SPC) return 550;
                    if (keycode == KC_DOT) return 500;
                    if (keycode == KC_A) return 545;
                    if (keycode == KC_E) return 540;
                    if (keycode == KC_H) return 535;
                    if (keycode == KC_I) return 530;
                    if (keycode == KC_J) return 525;
                    if (keycode == KC_O) return 520;
                    if (keycode == KC_R) return 515;
                    if (keycode == KC_U) return 510;
                    if (keycode == KC_Y) return 505;
                    break;
                // k
                case -63:
                    if (keycode == KC_SPC) return 588;
                    if (keycode == KC_DOT) return 555;
                    if (keycode == KC_A) return 584;
                    if (keycode == KC_E) return 580;
                    if (keycode == KC_I) return 576;
                    if (keycode == KC_J) return 572;
                    if (keycode == KC_O) return 568;
                    if (keycode == KC_R) return 564;
                    if (keycode == KC_Y) return 558;
                    break;
                // g
                case -52:
                    if (keycode == KC_SPC) return 640;
                    if (keycode == KC_A) return 635;
                    if (keycode == KC_E) return 630;
                    if (keycode == KC_H) return 625;
                    if (keycode == KC_I) return 620;
                    if (keycode == KC_J) return 614;
                    if (keycode == KC_O) return 609;
                    if (keycode == KC_R) return 604;
                    if (keycode == KC_U) return 599;
                    if (keycode == KC_Y) return 594;
                    break;
                // f
                case -40:
                    if (keycode == KC_SPC) return 698;
                    if (keycode == KC_DOT) return 645;
                    if (keycode == KC_A) return 693;
                    if (keycode == KC_E) return 689;
                    if (keycode == KC_H) return 684;
                    if (keycode == KC_I) return 679;
                    if (keycode == KC_J) return 674;
                    if (keycode == KC_O) return 666;
                    if (keycode == KC_R) return 660;
                    if (keycode == KC_U) return 655;
                    if (keycode == KC_Y) return 650;
                    break;
                // d
                case -28:
                    if (keycode == KC_SPC) return 754;
                    if (keycode == KC_COMMA) return 702;
                    if (keycode == KC_DOT) return 707;
                    if (keycode == KC_A) return 749;
                    if (keycode == KC_E) return 744;
                    if (keycode == KC_H) return 739;
                    if (keycode == KC_I) return 734;
                    if (keycode == KC_O) return 728;
                    if (keycode == KC_R) return 723;
                    if (keycode == KC_U) return 717;
                    if (keycode == KC_Y) return 711;
                    break;
                // c
                case -15:
                    if (keycode == KC_SPC) return 821;
                    if (keycode == KC_COMMA) return 759;
                    if (keycode == KC_DOT) return 765;
                    if (keycode == KC_A) return 815;
                    if (keycode == KC_E) return 809;
                    if (keycode == KC_H) return 803;
                    if (keycode == KC_I) return 798;
                    if (keycode == KC_J) return 792;
                    if (keycode == KC_O) return 786;
                    if (keycode == KC_R) return 781;
                    if (keycode == KC_U) return 775;
                    if (keycode == KC_Y) return 770;
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return 889;
                    if (keycode == KC_COMMA) return 826;
                    if (keycode == KC_DOT) return 836;
                    if (keycode == KC_A) return 884;
                    if (keycode == KC_E) return 878;
                    if (keycode == KC_H) return 873;
                    if (keycode == KC_I) return 868;
                    if (keycode == KC_J) return 862;
                    if (keycode == KC_O) return 857;
                    if (keycode == KC_R) return 852;
                    if (keycode == KC_U) return 846;
                    if (keycode == KC_Y) return 842;
                    break;
                case -1:
                    if (keycode == KC_B) return -2;
                    if (keycode == KC_C) return -15;
                    if (keycode == KC_D) return -28;
                    if (keycode == KC_F) return -40;
                    if (keycode == KC_G) return -52;
                    if (keycode == KC_K) return -63;
                    if (keycode == KC_L) return -73;
                    if (keycode == KC_M) return -85;
                    if (keycode == KC_N) return -96;
                    if (keycode == KC_P) return -108;
                    if (keycode == KC_R) return -119;
                    if (keycode == KC_S) return -130;
                    if (keycode == KC_T) return -143;
                    if (keycode == KC_V) return -155;
                    if (keycode == KC_W) return -165;
                    if (keycode == KC_X) return -177;
                    if (keycode == KC_Z) return -183;
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
