/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;

static bool magic_capitalize_next = false;

// Magic string decoder lookup tables
static const char magic_char_4bit[] = {
    ' ', 'e', 'o', 'n', 'i', 't', 'a', 'r', 'l', 's', 'u', 'g', 'h', 'c'
};

static const char magic_char_extended[] = {
    'd', 'p', 'm', 'f', 'b', 'y', 'w', '\'', 'v', 'k', 'x', 'q', 'z', '.', 'G', 'Z', 'I', 'O', 'T', 'P', 'S', 'B', 'j'
};

static const uint8_t magic_string_data[] = {
    0x02, 0xe7, 0xe0, 0x03, 0xe7, 0x88, 0x03, 0xe7, 0x71, 0x02, 0xe7, 0x90, 0x03, 0xe7, 0xe8, 0x10,
    0x02, 0xed, 0x00, 0x11, 0xee, 0x71, 0xb2, 0x70, 0xef, 0x14, 0x58, 0x43, 0xb1, 0x70, 0x05, 0xf0,
    0xe7, 0xe8, 0x10, 0x0e, 0xf1, 0xe1, 0x13, 0xf2, 0x18, 0x1f, 0xe2, 0x15, 0x7f, 0xe5, 0x00, 0x0b,
    0xf3, 0x72, 0xe2, 0x15, 0xc1, 0xa9, 0x00, 0x0c, 0xf4, 0xe1, 0x74, 0x3b, 0x0f, 0xf5, 0x22, 0x50,
    0x0a, 0x6d, 0xe9, 0xb7, 0x2a, 0x3f, 0xe0, 0x00, 0x09, 0x6f, 0xe0, 0x6f, 0xe1, 0x54, 0xe8, 0x10,
    0x0a, 0x68, 0x4f, 0xe0, 0x65, 0x42, 0x30, 0x08, 0x68, 0x71, 0x6f, 0xe0, 0xe5, 0x00, 0x07, 0x68,
    0xe6, 0x6f, 0xe5, 0x90, 0x04, 0x63, 0xe0, 0x00, 0x08, 0x63, 0xba, 0x6b, 0x10, 0x08, 0x63, 0x25,
    0xc1, 0x70, 0x09, 0x63, 0xe5, 0x5c, 0x43, 0xb0, 0x09, 0x6f, 0xe1, 0xe1, 0x72, 0xe8, 0x68, 0x00,
    0x08, 0x69, 0x18, 0x43, 0x10, 0x09, 0x69, 0x4d, 0x68, 0x8f, 0xe5, 0x00, 0x06, 0x69, 0x3f, 0xe7,
    0x50, 0x0a, 0x6f, 0xe8, 0x64, 0x86, 0xe4, 0x81, 0x00, 0x0b, 0xe4, 0x6d, 0xe9, 0xb7, 0x2a, 0x3f,
    0xe0, 0x00, 0x09, 0xe4, 0x69, 0x18, 0x43, 0x10, 0x0a, 0xe4, 0x69, 0x4d, 0x68, 0x8f, 0xe5, 0x00,
    0x08, 0xe4, 0x1d, 0x6a, 0x91, 0x00, 0x07, 0xe4, 0x1f, 0xe3, 0x27, 0x10, 0x07, 0xe4, 0x1c, 0x43,
    0xe0, 0x00, 0x08, 0xd2, 0xe2, 0xe2, 0x13, 0x50, 0x09, 0xd2, 0x3f, 0xe3, 0x84, 0xd5, 0x00, 0x0a,
    0xd2, 0x3f, 0xe3, 0xa9, 0x43, 0xb0, 0x09, 0xd2, 0x39, 0xaf, 0xe2, 0x17, 0x00, 0x0a, 0xd2, 0x35,
    0x64, 0x31, 0x70, 0x09, 0xd2, 0x35, 0x43, 0xa1, 0x00, 0x13, 0xe0, 0x1d, 0x86, 0x76, 0x54, 0xe8,
    0x10, 0xd2, 0x3f, 0xe3, 0x4b, 0x00, 0x08, 0xe0, 0x1f, 0xe3, 0x6a, 0x85, 0x00, 0x07, 0xe0, 0x4f,
    0xe0, 0x3f, 0xe7, 0x50, 0x0a, 0xe0, 0x4f, 0xe3, 0xe3, 0x17, 0x13, 0x50, 0x0b, 0xe0, 0x4f, 0xe3,
    0xe3, 0x4d, 0xa8, 0x5f, 0xe5, 0x00, 0x08, 0xe0, 0x49, 0x6f, 0xe4, 0x81, 0x00, 0x05, 0xe0, 0x21,
    0x90, 0x08, 0xe0, 0x21, 0x93, 0xe7, 0x50, 0x06, 0xe0, 0x23, 0xe7, 0x50, 0x07, 0x1d, 0x6a, 0x91,
    0x00, 0x07, 0x1f, 0xe3, 0x6a, 0x85, 0x00, 0x06, 0x1f, 0xe3, 0x27, 0x10, 0x06, 0x1c, 0x43, 0xe0,
    0x00, 0x09, 0x14, 0x58, 0x43, 0xb1, 0x70, 0x0a, 0x18, 0x6f, 0xe4, 0x27, 0x65, 0x10, 0x07, 0x13,
    0x17, 0x68, 0x00, 0x08, 0x13, 0x17, 0x65, 0x10, 0x04, 0x13, 0x50, 0x06, 0x12, 0xe1, 0x81, 0x00,
    0x08, 0x1f, 0xe1, 0x67, 0x65, 0x10, 0x07, 0x17, 0x94, 0x23, 0x00, 0x05, 0x1f, 0xe8, 0x17, 0x00,
    0x0b, 0x1f, 0xe8, 0x17, 0xe5, 0x5c, 0x43, 0xb0, 0x08, 0x1f, 0xea, 0x6f, 0xe2, 0xe1, 0x81, 0x00,
    0x07, 0x1f, 0xea, 0xd1, 0xe1, 0x50, 0x0a, 0x1f, 0xea, 0xd1, 0xe1, 0x54, 0x23, 0x00, 0x08, 0x1f,
    0xea, 0xd8, 0xaf, 0xe0, 0x10, 0x08, 0x1f, 0xea, 0xe1, 0x86, 0x43, 0x00, 0x09, 0x1f, 0xea, 0xe1,
    0x84, 0xd4, 0x50, 0x08, 0xe3, 0x2d, 0xa9, 0x1f, 0xe0, 0x00, 0x0a, 0xe3, 0x28, 0x82, 0xe6, 0x43,
    0xb0, 0x0a, 0xe3, 0x71, 0xeb, 0xa1, 0x3d, 0xe5, 0x00, 0x08, 0xb1, 0x31, 0x76, 0x80, 0x09, 0xb1,
    0x31, 0x76, 0x51, 0x00, 0x07, 0xb4, 0x5c, 0xaf, 0xe4, 0x00, 0x07, 0xb8, 0x2f, 0xe4, 0x68, 0x00,
    0x06, 0xb7, 0x1b, 0x27, 0x05, 0xc4, 0xdc, 0x00, 0x05, 0xc4, 0x3f, 0xe9, 0x00, 0x06, 0xc2, 0xab,
    0xc0, 0x07, 0xc2, 0xab, 0xc5, 0x00, 0x07, 0xc7, 0x2a, 0xbc, 0x00, 0x06, 0x4f, 0xe0, 0x3f, 0xe7,
    0x50, 0x09, 0x4f, 0xe3, 0xe3, 0x17, 0x13, 0x50, 0x0a, 0x4f, 0xe3, 0xe3, 0x4d, 0xa8, 0x5f, 0xe5,
    0x00, 0x09, 0x4b, 0x76, 0x54, 0x23, 0x00, 0x07, 0x4f, 0xe2, 0x48, 0x67, 0x00, 0x08, 0x4f, 0xe2,
    0xe1, 0x72, 0xe8, 0x10, 0x10, 0x43, 0x95, 0x7a, 0xe2, 0x13, 0x56, 0x54, 0x23, 0x00, 0x03, 0x42,
    0x30, 0x08, 0x49, 0xe2, 0x65, 0xdc, 0x00, 0x06, 0x45, 0xca, 0xe4, 0x00, 0x05, 0xf6, 0xa9, 0x50,
    0x05, 0xe9, 0x31, 0xe6, 0x00, 0x05, 0xe9, 0x32, 0xe6, 0x00, 0x09, 0x86, 0x3b, 0xa6, 0xb1, 0x00,
    0x06, 0x82, 0xe4, 0x68, 0x00, 0x05, 0xe2, 0x13, 0x50, 0x07, 0xe2, 0x17, 0xb1, 0xe0, 0x00, 0x0a,
    0xe2, 0x4b, 0x76, 0x54, 0x23, 0x00, 0x09, 0xe2, 0x49, 0xe2, 0x65, 0xdc, 0x00, 0x09, 0xe2, 0xa8,
    0x54, 0xe1, 0x81, 0x00, 0x03, 0x3f, 0xe7, 0x50, 0x06, 0x31, 0xe8, 0x17, 0x00, 0x04, 0x31, 0xe6,
    0x00, 0x0e, 0x32, 0x54, 0xe3, 0x4d, 0x65, 0x42, 0x39, 0x00, 0x04, 0x32, 0xe6, 0x00, 0x0e, 0x2f,
    0xe4, 0x91, 0x7f, 0xe8, 0x6f, 0xe4, 0x48, 0x45, 0xe5, 0x00, 0x09, 0x2f, 0xe4, 0x92, 0x81, 0x51,
    0x00, 0x07, 0x2d, 0xa9, 0x1f, 0xe0, 0x00, 0x04, 0x21, 0x90, 0x07, 0x21, 0x93, 0xe7, 0x50, 0x09,
    0x28, 0x82, 0xe6, 0x43, 0xb0, 0x07, 0x2f, 0xe2, 0x12, 0x31, 0x00, 0x09, 0x2f, 0xe2, 0x15, 0xc4,
    0x3b, 0x00, 0x07, 0x2f, 0xe2, 0xe2, 0x13, 0x50, 0x05, 0x23, 0xe7, 0x50, 0x05, 0x23, 0x8f, 0xe5,
    0x00, 0x09, 0x23, 0x56, 0x43, 0x17, 0x00, 0x09, 0x27, 0xb6, 0x34, 0xec, 0x10, 0x08, 0x27, 0xe9,
    0xe3, 0x82, 0xe6, 0x00, 0x05, 0x27, 0x91, 0x00, 0x0a, 0x25, 0xc1, 0x7f, 0xe6, 0x49, 0x10, 0x0d,
    0x25, 0x4f, 0xe3, 0x4d, 0x65, 0x42, 0x39, 0x00, 0x07, 0xe1, 0x12, 0xe1, 0x81, 0x00, 0x0c, 0xe1,
    0x17, 0xe3, 0x27, 0xe2, 0x63, 0xd1, 0x00, 0x09, 0xe1, 0x29, 0x94, 0xe4, 0x81, 0x00, 0x09, 0xe1,
    0x72, 0xe4, 0x6f, 0xe4, 0x8f, 0xe5, 0x00, 0x0b, 0xe1, 0x72, 0xe0, 0xad, 0x54, 0x23, 0x00, 0x07,
    0xe1, 0xe5, 0x5c, 0x23, 0x00, 0x02, 0xeb, 0xa0, 0x08, 0x71, 0x68, 0x4f, 0xec, 0x10, 0x09, 0x71,
    0x32, 0xe8, 0x65, 0x10, 0x09, 0x71, 0xeb, 0xa1, 0x3d, 0xe5, 0x00, 0x08, 0x71, 0x92, 0x8f, 0xe8,
    0x10, 0x08, 0x72, 0xe4, 0x6f, 0xe4, 0x8f, 0xe5, 0x00, 0x0a, 0x72, 0xe0, 0xad, 0x54, 0x23, 0x00,
    0x09, 0x91, 0xe1, 0x67, 0x65, 0x10, 0x08, 0x94, 0xe2, 0x48, 0x67, 0x00, 0x04, 0x94, 0x23, 0x08,
    0x92, 0xe2, 0x12, 0x31, 0x00, 0x0a, 0x92, 0xe2, 0x15, 0xc4, 0x3b, 0x00, 0x08, 0x9a, 0xbb, 0x19,
    0x50, 0x08, 0x9a, 0xe1, 0xe1, 0x27, 0x50, 0x07, 0x9f, 0xe6, 0x45, 0xdc, 0x00, 0x04, 0x5c, 0x10,
    0x06, 0x5c, 0x43, 0xe9, 0x00, 0x07, 0x5c, 0x2a, 0xbc, 0x00, 0x08, 0x5c, 0x2a, 0xbc, 0x50, 0x08,
    0x5c, 0x72, 0xab, 0xc0, 0x04, 0x54, 0x23, 0x08, 0xa8, 0x54, 0xe1, 0x81, 0x00, 0x0b, 0xa3, 0xe0,
    0x17, 0x95, 0x63, 0xe0, 0x00, 0x0a, 0xa3, 0x71, 0x86, 0x51, 0xe0, 0x00, 0x07, 0xaf, 0xe1, 0xe0,
    0x65, 0x10, 0x07, 0xaf, 0xe1, 0xe1, 0x27, 0x50, 0x04, 0xa9, 0x50, 0x0b, 0xe8, 0x68, 0x4f, 0xe0,
    0x65, 0x42, 0x30, 0x08, 0xe8, 0x17, 0x94, 0x23, 0x00, 0x07, 0xe6, 0x69, 0x3f, 0xe7, 0x50, 0x06,
    0xe6, 0xc4, 0xdc, 0x00, 0x08, 0xe6, 0x45, 0xc2, 0xa5, 0x00, 0x09, 0xe6, 0x27, 0xe9, 0xe3, 0x82,
    0xe6, 0x00, 0x06, 0xe6, 0x27, 0x91, 0x00, 0x07, 0xea, 0xe1, 0x86, 0x43, 0x00, 0x06, 0xe5, 0x5c,
    0x23, 0x00, 0x0a, 0xec, 0x14, 0x58, 0x43, 0xb1, 0x70
};

static void magic_decode_send(uint16_t offset) {
    const uint8_t* data = magic_string_data + offset;
    uint8_t len = data[0];
    data++;

    uint8_t byteIndex = 0;
    bool highNibble = true;
    uint8_t charCount = 0;

    while (charCount < len) {
        uint8_t code;
        char c = '\0';

        if (highNibble) {
            code = (data[byteIndex] >> 4) & 0x0F;
            if (code >= 14) {
                code = data[byteIndex];
                byteIndex++;
                highNibble = true;
                if (code >= 0xE0 && code < 0xE0 + sizeof(magic_char_extended)) {
                    c = magic_char_extended[code - 0xE0];
                    send_char(c);
                    charCount++;
                }
            } else {
                highNibble = false;
                if (code < sizeof(magic_char_4bit)) {
                    c = magic_char_4bit[code];
                    send_char(c);
                    charCount++;
                }
            }
        } else {
            code = data[byteIndex] & 0x0F;
            byteIndex++;
            highNibble = true;
            if (code == 0x0F) {
                continue;
            }
            if (code < sizeof(magic_char_4bit)) {
                c = magic_char_4bit[code];
                send_char(c);
                charCount++;
            }
        }
    }
}

static void magic_decode_send_cap(uint16_t offset, char suffix) {
    if (magic_capitalize_next) {
        add_oneshot_mods(MOD_BIT(KC_LSFT));
    }
    magic_decode_send(offset);
    if (suffix != '\0') {
        set_suffix_state(suffix);
    }
    magic_capitalize_next = false;
}

static void magic_decode_send_suffix(uint16_t offset, char suffix) {
    magic_decode_send(offset);
    set_suffix_state(suffix);
}


uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch(index) {
    case C_BASE_ING: return 200;
    case C_BASE_KC_B: return 200;
    case C_BASE_KC_G: return 200;
    case C_BASE_KC_K: return 200;
    case C_BASE_KC_M: return 200;
    case C_BASE_KC_P: return 200;
    case C_BASE_KC_V: return 200;
    case C_BASE_MAGIC_C: return 200;
    case C_BASE_MAGIC_D: return 200;
    case C_BASE_MAGIC_E: return 200;
    case C_BASE_MAGIC_F: return 200;
    case C_BASE_MAGIC_G: return 200;
    case C_BASE_MAGIC_H: return 200;
    case C_BASE_MAGIC_I: return 200;
    case C_BASE_MAGIC_J: return 200;
    case C_BASE_MAGIC_K: return 200;
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
    case C_LEFT_KC_Z: return 200;
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
    case C_NAV_RCSKC_C: return 200;
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
    case C_RIGHT_KC_DQUO: return 200;
    case C_RIGHT_KC_EXLM: return 200;
    case C_RIGHT_KC_GRAVE: return 200;
    case C_RIGHT_KC_J: return 200;
    case C_RIGHT_KC_QUES: return 200;
    case C_RIGHT_N_T: return 200;
    case C_RIGHT_RCSKC_F: return 200;
    case C_RIGHT_RCSKC_R: return 200;
    case DS_C_BASE_KC_B: return 200;
    case DS_C_BASE_KC_G: return 200;
    case DS_C_BASE_KC_K: return 200;
    case DS_C_BASE_KC_M: return 200;
    case DS_C_BASE_KC_P: return 200;
    case DS_C_BASE_KC_V: return 200;
    case SUB_1: return 200;
    case SUB_2: return 200;
    case SUB_3: return 200;
    case SUB_4: return 200;
    case SUB_5: return 200;
    case SUB_6: return 200;
    case S_C_BASE_KC_B: return 200;
    case S_C_BASE_KC_G: return 200;
    case S_C_BASE_KC_K: return 200;
    case S_C_BASE_KC_M: return 200;
    case S_C_BASE_KC_P: return 200;
    case S_C_BASE_KC_V: return 200;
    default:
        return COMBO_TERM;
    }
}

// Two-variable tracking for adaptive keys.
// prev_keycode = the key before the current one (what adaptives check against).
// last_keycode = the most recent key (shifts to prev_keycode on the next keypress).
// Updated only in remember_last_key_user (called with resolved combo keycodes,
// so combo components like KC_C from P=KC_C+KC_X are never recorded — only KC_P is).
static uint16_t prev_keycode = KC_NO;
static uint16_t last_keycode = KC_NO;
static uint16_t last_magic_trigger = KC_NO;
static uint16_t last_magic_repeat_keycode = KC_NO;
static uint16_t magic_remembered_keycode = KC_NO;
static uint16_t magic_repeat_keycode = KC_NO;

static inline uint16_t unshift_letter_keycode(uint16_t keycode) {
    if (keycode >= S(KC_A) && keycode <= S(KC_Z)) {
        return keycode - S(KC_A) + KC_A;
    }
    return keycode;
}

static uint16_t magic_prepare_last_keycode(uint16_t keycode) {
    uint16_t unshifted = unshift_letter_keycode(keycode);
    magic_capitalize_next = unshifted != keycode;
    return unshifted;
}

static bool repeat_last_magic_key(uint16_t trigger) {
    if (last_magic_trigger != trigger || last_magic_repeat_keycode == KC_NO) {
        return false;
    }
    tap_code16(last_magic_repeat_keycode);
    set_last_keycode(last_magic_repeat_keycode);
    return true;
}

bool tap(uint16_t keycode) {
    tap_code16(keycode);
    set_last_keycode(keycode);
    last_keycode = keycode;
    return false;
}

static void magic_replace_decode_send_cap(uint16_t offset, char suffix) {
    tap_code16(KC_BSPC);
    magic_decode_send_cap(offset, suffix);
}

static void magic_tap_repeatable(uint16_t keycode) {
    tap_code16(keycode);
    magic_remembered_keycode = keycode;
    magic_repeat_keycode = keycode;
}

static inline void magic_replace_tap_repeatable(uint16_t keycode) {
    tap_code16(KC_BSPC);
    magic_tap_repeatable(keycode);
}

static bool process_magic_suffix(uint16_t keycode) {
    switch (keycode) {
    case MAGIC_B:
        tap_code16(KC_BSPC); tap_code16(KC_L); tap_code16(KC_Y); tap_code16(KC_SPC);
        last_magic_char = 'y';
        return true;
    case MAGIC_D:
        tap_code16(KC_BSPC); tap_n_t(); tap_code16(KC_SPC);
        last_magic_char = 't';
        return true;
    case MAGIC_E:
        tap_code16(KC_BSPC); tap_code16(KC_QUES); tap_code16(KC_SPC);
        last_magic_char = '?';
        return true;
    case MAGIC_G:
        tap_code16(KC_BSPC); tap_code16(KC_COMMA); tap_code16(KC_SPC);
        suffix_active = false;
        return true;
    case MAGIC_H:
        tap_code16(KC_BSPC);
        if (last_magic_char == 'e') {
            tap_code16(KC_D); tap_code16(KC_SPC);
        } else {
            tap_code16(KC_E); tap_code16(KC_D); tap_code16(KC_SPC);
        }
        last_magic_char = 'd';
        return true;
    case MAGIC_I:
        tap_code16(KC_BSPC); tap_code16(KC_SPC); tap_code16(KC_T); tap_code16(KC_H); tap_code16(KC_E); tap_code16(KC_SPC);
        suffix_active = false;
        return true;
    case MAGIC_J:
        tap_code16(KC_BSPC); tap_code16(KC_DOT); tap_code16(KC_SPC);
        suffix_active = false;
        return true;
    case MAGIC_K:
        tap_code16(KC_BSPC); tap_code16(KC_S); tap_code16(KC_SPC);
        last_magic_char = 's';
        return true;
    default:
        return false;
    }
}

bool process_record_generated(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Adaptive keys: runs after combo resolution in process_record_user,
        // so combo components are suppressed and prev_keycode reflects the
        // resolved combo keycode (e.g. KC_P not KC_C).
        uint16_t adaptive_prev_keycode = unshift_letter_keycode(prev_keycode);
        switch (keycode) {
            case KC_E:
                switch (adaptive_prev_keycode) {
                    case KC_A: return tap(KC_U);
                }
                break;
            case KC_D:
                switch (adaptive_prev_keycode) {
                    case KC_B: return tap(KC_S);
                    case KC_C: return tap(KC_C);
                    case KC_F: return tap(KC_F);
                    case KC_G: return tap(KC_N);
                    case KC_P: return tap(KC_L);
                    case KC_S: return tap(KC_P);
                    case KC_X: return tap(KC_C);
                }
                break;
            case KC_N:
                switch (adaptive_prev_keycode) {
                    case KC_C: return tap(KC_K);
                    case KC_P: return tap(KC_P);
                    case KC_T: return tap(KC_T);
                }
                break;
            case KC_C:
                switch (adaptive_prev_keycode) {
                    case KC_D: return tap(KC_V);
                    case KC_L: return tap(KC_V);
                }
                break;
            case KC_F:
                switch (adaptive_prev_keycode) {
                    case KC_D: return tap(KC_D);
                    case KC_G: return tap(KC_L);
                    case KC_T: return tap(KC_W);
                }
                break;
            case KC_H:
                switch (adaptive_prev_keycode) {
                    case KC_D: return tap(KC_G);
                    case KC_E: return tap(KC_E);
                    case KC_L: return tap(KC_P);
                    case KC_M: return tap(KC_M);
                    case KC_N: return tap(KC_N);
                    case KC_O: return tap(KC_O);
                    case KC_U: return tap(KC_A);
                }
                break;
            case KC_U:
                switch (adaptive_prev_keycode) {
                    case KC_E: return tap(KC_O);
                }
                break;
            case KC_R:
                switch (adaptive_prev_keycode) {
                    case KC_K: return tap(KC_N);
                    case KC_L: return tap(KC_L);
                    case KC_M: return tap(KC_P);
                    case KC_N: return tap(KC_G);
                    case KC_S: return tap(KC_S);
                    case KC_Y: return tap(KC_I);
                }
                break;
            case KC_B:
                switch (adaptive_prev_keycode) {
                    case KC_L: return tap(KC_K);
                }
                break;
            case KC_T:
                switch (adaptive_prev_keycode) {
                    case KC_M: return tap(KC_B);
                }
                break;
            case KC_P:
                switch (adaptive_prev_keycode) {
                    case KC_N: return tap(KC_K);
                }
                break;
            case KC_X:
                switch (adaptive_prev_keycode) {
                    case KC_N: return tap(KC_L);
                    case KC_R: return tap(KC_R);
                    case KC_W: return tap(KC_N);
                }
                break;
            case KC_Y:
                switch (adaptive_prev_keycode) {
                    case KC_P: return tap(KC_S);
                }
                break;
            case KC_W:
                switch (adaptive_prev_keycode) {
                    case KC_X: return tap(KC_P);
                }
                break;
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
            case MAGIC_A: {
                if (repeat_last_magic_key(MAGIC_A)) {
                    return false;
                }
                magic_remembered_keycode = MAGIC_A;
                magic_repeat_keycode = KC_NO;
                switch (magic_prepare_last_keycode(get_last_keycode())) {
                    case KC_B: magic_decode_send_suffix(64, 'd'); /* emits "ackground " -> "background " */ break;
                    case KC_C: magic_tap_repeatable(KC_N); break;
                    case KC_D: magic_tap_repeatable(KC_C); break;
                    case KC_F: magic_replace_decode_send_cap(207, 'g'); /* emits "confusing " */ break;
                    case KC_G: magic_decode_send_suffix(576, 'l'); /* emits "lobal " -> "global " */ break;
                    case KC_K: magic_tap_repeatable(KC_R); break;
                    case KC_L: magic_tap_repeatable(KC_M); break;
                    case KC_M: magic_tap_repeatable(KC_R); break;
                    case KC_N: magic_tap_repeatable(KC_R); break;
                    case KC_P: magic_tap_repeatable(KC_Y); break;
                    case KC_S: magic_decode_send_suffix(677, 'e'); /* emits "omeone " -> "someone " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_DQUO); break;
                    case KC_T: magic_tap_repeatable(KC_N); break;
                    case KC_V: magic_decode_send_suffix(80, 'n'); /* emits "alidation " -> "validation " */ break;
                    case KC_W: magic_replace_decode_send_cap(94, 's'); /* emits "always " */ break;
                    case KC_X: magic_replace_decode_send_cap(390, 'n'); /* emits "exception " */ break;
                }
                magic_capitalize_next = false;
                last_magic_trigger = MAGIC_A;
                last_magic_repeat_keycode = magic_repeat_keycode;
                set_last_keycode(magic_remembered_keycode);
                return false;
            }
            case MAGIC_B: {
                if (repeat_last_magic_key(MAGIC_B)) {
                    return false;
                }
                magic_remembered_keycode = MAGIC_B;
                magic_repeat_keycode = KC_NO;
                switch (magic_prepare_last_keycode(get_last_keycode())) {
                    case KC_B: magic_decode_send_suffix(316, 'd'); /* emits "ehind " -> "behind " */ break;
                    case KC_C: magic_replace_decode_send_cap(3, '\0'); /* emits "'ll" */ break;
                    case KC_D: magic_tap_repeatable(KC_H); break;
                    case KC_F: magic_replace_decode_send_cap(200, 't'); /* emits "conflict " */ break;
                    case KC_G: magic_tap_repeatable(KC_F); break;
                    case KC_L: magic_tap_repeatable(KC_H); break;
                    case KC_M: magic_tap_repeatable(KC_H); break;
                    case KC_N: magic_tap_repeatable(KC_H); break;
                    case KC_P: magic_tap_repeatable(KC_M); break;
                    case KC_S: magic_tap_repeatable(KC_R); break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_EXLM); break;
                    case KC_T: magic_tap_repeatable(KC_F); break;
                    case KC_V: magic_replace_decode_send_cap(368, 'g'); /* emits "everything " */ break;
                    case KC_W: magic_decode_send_suffix(140, 't'); /* emits "asn't " -> "wasn't " */ break;
                    case KC_X: magic_tap_repeatable(KC_W); break;
                    case KC_Z: magic_replace_decode_send_cap(792, 'e'); /* emits "realize " */ break;
                }
                magic_capitalize_next = false;
                last_magic_trigger = MAGIC_B;
                last_magic_repeat_keycode = magic_repeat_keycode;
                set_last_keycode(magic_remembered_keycode);
                return false;
            }
            case MAGIC_C: {
                if (repeat_last_magic_key(MAGIC_C)) {
                    return false;
                }
                magic_remembered_keycode = MAGIC_C;
                magic_repeat_keycode = KC_NO;
                switch (magic_prepare_last_keycode(get_last_keycode())) {
                    case KC_E: magic_tap_repeatable(KC_U); break;
                    case KC_O: magic_tap_repeatable(KC_E); break;
                    case KC_SPC: magic_replace_decode_send_cap(16, '\0'); /* emits ". " */ add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state(); break;
                    case KC_V: magic_replace_decode_send_cap(233, 'g'); /* emits "declarative config " */ break;
                }
                magic_capitalize_next = false;
                last_magic_trigger = MAGIC_C;
                last_magic_repeat_keycode = magic_repeat_keycode;
                set_last_keycode(magic_remembered_keycode);
                return false;
            }
            case MAGIC_D: {
                if (repeat_last_magic_key(MAGIC_D)) {
                    return false;
                }
                magic_remembered_keycode = MAGIC_D;
                magic_repeat_keycode = KC_NO;
                switch (magic_prepare_last_keycode(get_last_keycode())) {
                    case KC_B: magic_decode_send_suffix(128, 'e'); /* emits "aseline " -> "baseline " */ break;
                    case KC_C: magic_replace_decode_send_cap(612, '\0'); /* emits "n't" */ break;
                    case KC_D: magic_decode_send_suffix(696, 't'); /* emits "on't " -> "don't " */ break;
                    case KC_F: magic_replace_decode_send_cap(750, 'e'); /* emits "performance " */ break;
                    case KC_G: magic_replace_decode_send_cap(711, 'e'); /* emits "organize " */ break;
                    case KC_L: magic_decode_send_suffix(104, 'e'); /* emits "anguage " -> "language " */ break;
                    case KC_M: magic_decode_send_suffix(513, 'n'); /* emits "igration " -> "migration " */ break;
                    case KC_N: magic_decode_send_suffix(363, 'r'); /* emits "ever " -> "never " */ break;
                    case KC_P: magic_decode_send_suffix(347, 'e'); /* emits "eople " -> "people " */ break;
                    case KC_S: magic_replace_decode_send_cap(759, 'e'); /* emits "possible " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_QUOTE); break;
                    case KC_T: magic_replace_decode_send_cap(72, 'e'); /* emits "adaptive " */ break;
                    case KC_V: magic_replace_decode_send_cap(12, '\0'); /* emits "'ve" */ break;
                    case KC_W: magic_decode_send_suffix(717, 'w'); /* emits "orkflow " -> "workflow " */ break;
                    case KC_X: magic_replace_decode_send_cap(384, 't'); /* emits "except " */ break;
                    case KC_Z: magic_replace_decode_send_cap(464, '\0'); /* emits "gregor" */ break;
                    default: magic_decode_send(789); /* emits "qu" */ break;
                }
                magic_capitalize_next = false;
                last_magic_trigger = MAGIC_D;
                last_magic_repeat_keycode = magic_repeat_keycode;
                set_last_keycode(magic_remembered_keycode);
                return false;
            }
            case MAGIC_E: {
                if (repeat_last_magic_key(MAGIC_E)) {
                    return false;
                }
                magic_remembered_keycode = MAGIC_E;
                magic_repeat_keycode = KC_NO;
                switch (magic_prepare_last_keycode(get_last_keycode())) {
                    case KC_B: magic_replace_decode_send_cap(638, 'y'); /* emits "observability " */ break;
                    case KC_C: magic_tap_repeatable(KC_D); break;
                    case KC_D: magic_decode_send_suffix(305, 't'); /* emits "efault " -> "default " */ break;
                    case KC_E: magic_replace_decode_send_cap(109, 'r'); /* emits "another " */ break;
                    case KC_F: magic_decode_send_suffix(804, 'y'); /* emits "requency " -> "frequency " */ break;
                    case KC_G: magic_decode_send_suffix(551, 'b'); /* emits "ithub " -> "github " */ break;
                    case KC_K: magic_replace_decode_send_cap(585, 'd'); /* emits "merged " */ break;
                    case KC_L: magic_replace_decode_send_cap(87, 'y'); /* emits "already " */ break;
                    case KC_M: magic_decode_send_suffix(903, 'e'); /* emits "ultiple " -> "multiple " */ break;
                    case KC_N: magic_replace_decode_send_cap(114, 'g'); /* emits "anything " */ break;
                    case KC_P: magic_decode_send_suffix(817, 'y'); /* emits "robably " -> "probably " */ break;
                    case KC_S: magic_decode_send_suffix(930, 't'); /* emits "upport " -> "support " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_QUES); break;
                    case KC_T: magic_decode_send_suffix(486, 'h'); /* emits "hrough " -> "through " */ break;
                    case KC_V: magic_decode_send_suffix(358, 'n'); /* emits "ersion " -> "version " */ break;
                    case KC_W: magic_replace_decode_send_cap(728, 'e'); /* emits "otherwise " */ break;
                    case KC_X: magic_replace_decode_send_cap(412, 't'); /* emits "explicit " */ break;
                    case KC_Z: magic_decode_send(321); /* emits "eitlinger" -> "zeitlinger" */ break;
                }
                magic_capitalize_next = false;
                last_magic_trigger = MAGIC_E;
                last_magic_repeat_keycode = magic_repeat_keycode;
                set_last_keycode(magic_remembered_keycode);
                return false;
            }
            case MAGIC_F: {
                if (repeat_last_magic_key(MAGIC_F)) {
                    return false;
                }
                magic_remembered_keycode = MAGIC_F;
                magic_repeat_keycode = KC_NO;
                switch (magic_prepare_last_keycode(get_last_keycode())) {
                    case KC_B: magic_replace_decode_send_cap(278, 'e'); /* emits "disable " */ break;
                    case KC_C: magic_decode_send_suffix(705, 'r'); /* emits "ontainer " -> "container " */ break;
                    case KC_D: magic_decode_send_suffix(497, 't'); /* emits "ifferent " -> "different " */ break;
                    case KC_ENT: magic_decode_send_cap(100, 'd'); /* emits "and " */ break;
                    case KC_G: magic_decode_send_suffix(334, 'l'); /* emits "eneral " -> "general " */ break;
                    case KC_L: magic_replace_decode_send_cap(145, 'e'); /* emits "available " */ break;
                    case KC_M: magic_decode_send_suffix(545, 'h'); /* emits "ismatch " -> "mismatch " */ break;
                    case KC_N: magic_replace_decode_send_cap(798, 'e'); /* emits "renovate " */ break;
                    case KC_P: magic_decode_send_suffix(989, 'n'); /* emits "ython " -> "python " */ break;
                    case KC_S: magic_decode_send_suffix(519, 'r'); /* emits "imilar " -> "similar " */ break;
                    case KC_SPC: magic_decode_send_cap(100, 'd'); /* emits "and " */ break;
                    case KC_T: magic_decode_send_suffix(472, 'k'); /* emits "hink " -> "think " */ break;
                    case KC_TAB: magic_decode_send_cap(100, 'd'); /* emits "and " */ break;
                    case KC_W: magic_replace_decode_send_cap(871, 'h'); /* emits "switch " */ break;
                    case KC_Z: magic_replace_decode_send_cap(19, '\0'); /* emits "Gregor Zeitlinger" */ break;
                }
                magic_capitalize_next = false;
                last_magic_trigger = MAGIC_F;
                last_magic_repeat_keycode = magic_repeat_keycode;
                set_last_keycode(magic_remembered_keycode);
                return false;
            }
            case MAGIC_G: {
                if (repeat_last_magic_key(MAGIC_G)) {
                    return false;
                }
                magic_remembered_keycode = MAGIC_G;
                magic_repeat_keycode = KC_NO;
                switch (magic_prepare_last_keycode(get_last_keycode())) {
                    case KC_A: magic_tap_repeatable(KC_E); break;
                    case KC_B: magic_decode_send_suffix(133, 'y'); /* emits "asically " -> "basically " */ break;
                    case KC_D: magic_decode_send_suffix(504, 'y'); /* emits "ifficulty " -> "difficulty " */ break;
                    case KC_E: magic_tap_repeatable(KC_H); break;
                    case KC_J: magic_decode_send_suffix(936, 't'); /* emits "ust " -> "just " */ break;
                    case KC_L: magic_replace_decode_send_cap(917, 'd'); /* emits "unrelated " */ break;
                    case KC_N: magic_decode_send_suffix(735, 's'); /* emits "otifications " -> "notifications " */ break;
                    case KC_O: magic_tap_repeatable(KC_H); break;
                    case KC_P: magic_replace_decode_send_cap(525, 'e'); /* emits "improve " */ break;
                    case KC_S: magic_replace_decode_send_cap(214, 'r'); /* emits "consumer " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_Z); break;
                    case KC_T: magic_replace_decode_send_cap(227, 'e'); /* emits "continue " */ break;
                    case KC_U: magic_tap_repeatable(KC_H); break;
                    case KC_Y: magic_replace_decode_send_cap(700, 'y'); /* emits "only " */ break;
                }
                magic_capitalize_next = false;
                last_magic_trigger = MAGIC_G;
                last_magic_repeat_keycode = magic_repeat_keycode;
                set_last_keycode(magic_remembered_keycode);
                return false;
            }
            case MAGIC_H: {
                if (repeat_last_magic_key(MAGIC_H)) {
                    return false;
                }
                magic_remembered_keycode = MAGIC_H;
                magic_repeat_keycode = KC_NO;
                switch (magic_prepare_last_keycode(get_last_keycode())) {
                    case KC_B: magic_replace_decode_send_cap(650, 'e'); /* emits "obsolete " */ break;
                    case KC_C: magic_decode_send_suffix(690, 't'); /* emits "omment " -> "comment " */ break;
                    case KC_D: magic_decode_send_suffix(491, 't'); /* emits "idn't " -> "didn't " */ break;
                    case KC_F: magic_decode_send_suffix(657, 'd'); /* emits "ocused " -> "focused " */ break;
                    case KC_G: magic_decode_send_suffix(339, 'e'); /* emits "enerate " -> "generate " */ break;
                    case KC_K: magic_replace_decode_send_cap(924, 'e'); /* emits "update " */ break;
                    case KC_L: magic_replace_decode_send_cap(327, 'e'); /* emits "elaborate " */ break;
                    case KC_M: magic_replace_decode_send_cap(532, 'n'); /* emits "instrumentation " */ break;
                    case KC_N: magic_replace_decode_send_cap(909, 'd'); /* emits "understand " */ break;
                    case KC_P: magic_decode_send_suffix(825, 'n'); /* emits "roduction " -> "production " */ break;
                    case KC_S: magic_decode_send_suffix(352, 'e'); /* emits "eparate " -> "separate " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_COMMA); break;
                    case KC_T: magic_decode_send_suffix(477, 'h'); /* emits "hough " -> "though " */ break;
                    case KC_V: magic_replace_decode_send_cap(120, 'l'); /* emits "approval " */ break;
                    case KC_W: magic_decode_send_suffix(468, 'h'); /* emits "hich " -> "which " */ break;
                    case KC_X: magic_replace_decode_send_cap(398, 'e'); /* emits "exclude " */ break;
                    case KC_Y: magic_tap_repeatable(KC_R); break;
                    case KC_Z: magic_replace_decode_send_cap(35, 'y'); /* emits "OpenTelemetry " */ break;
                }
                magic_capitalize_next = false;
                last_magic_trigger = MAGIC_H;
                last_magic_repeat_keycode = magic_repeat_keycode;
                set_last_keycode(magic_remembered_keycode);
                return false;
            }
            case MAGIC_I: {
                if (repeat_last_magic_key(MAGIC_I)) {
                    return false;
                }
                magic_remembered_keycode = MAGIC_I;
                magic_repeat_keycode = KC_NO;
                switch (magic_prepare_last_keycode(get_last_keycode())) {
                    case KC_B: magic_decode_send_suffix(300, 'e'); /* emits "ecause " -> "because " */ break;
                    case KC_C: magic_replace_decode_send_cap(6, '\0'); /* emits "'re" */ break;
                    case KC_D: magic_decode_send_suffix(666, 't'); /* emits "oesn't " -> "doesn't " */ break;
                    case KC_ENT: magic_decode_send_cap(877, 'e'); /* emits "the " */ break;
                    case KC_F: magic_decode_send_suffix(671, 'g'); /* emits "ollowing " -> "following " */ break;
                    case KC_G: magic_tap_repeatable(KC_K); break;
                    case KC_K: magic_decode_send_suffix(634, 'w'); /* emits "now " -> "know " */ break;
                    case KC_L: magic_tap_repeatable(KC_R); break;
                    case KC_M: magic_decode_send_suffix(344, 't'); /* emits "ent " -> "ment " */ break;
                    case KC_N: magic_replace_decode_send_cap(789, '\0'); /* emits "qu" */ break;
                    case KC_P: magic_tap_repeatable(KC_N); break;
                    case KC_S: magic_decode_send(542); /* emits "ion" -> "sion" */ break;
                    case KC_SPC: magic_decode_send_cap(877, 'e'); /* emits "the " */ break;
                    case KC_T: magic_decode_send(542); /* emits "ion" -> "tion" */ break;
                    case KC_TAB: magic_decode_send_cap(877, 'e'); /* emits "the " */ break;
                    case KC_V: magic_replace_decode_send_cap(811, 'e'); /* emits "resolve " */ break;
                    case KC_W: magic_tap_repeatable(KC_S); break;
                    case KC_X: magic_tap_repeatable(KC_R); break;
                    case KC_Z: magic_replace_decode_send_cap(55, 't'); /* emits "Spring Boot " */ break;
                }
                magic_capitalize_next = false;
                last_magic_trigger = MAGIC_I;
                last_magic_repeat_keycode = magic_repeat_keycode;
                set_last_keycode(magic_remembered_keycode);
                return false;
            }
            case MAGIC_J: {
                if (repeat_last_magic_key(MAGIC_J)) {
                    return false;
                }
                magic_remembered_keycode = MAGIC_J;
                magic_repeat_keycode = KC_NO;
                switch (magic_prepare_last_keycode(get_last_keycode())) {
                    case KC_B: magic_tap_repeatable(KC_D); break;
                    case KC_C: magic_replace_decode_send_cap(0, '\0'); /* emits "'d" */ break;
                    case KC_D: magic_tap_repeatable(KC_F); break;
                    case KC_F: magic_tap_repeatable(KC_D); break;
                    case KC_G: magic_tap_repeatable(KC_D); break;
                    case KC_H: magic_tap_repeatable(KC_Y); break;
                    case KC_K: magic_tap_repeatable(KC_X); break;
                    case KC_L: magic_tap_repeatable(KC_C); break;
                    case KC_M: magic_tap_repeatable(KC_L); break;
                    case KC_N: magic_tap_repeatable(KC_X); break;
                    case KC_P: magic_tap_repeatable(KC_D); break;
                    case KC_R: magic_tap_repeatable(KC_X); break;
                    case KC_S: magic_tap_repeatable(KC_D); break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_DOT); break;
                    case KC_T: magic_replace_decode_send_cap(964, 't'); /* emits "without " */ break;
                    case KC_V: magic_replace_decode_send_cap(30, 'e'); /* emits "I've " */ break;
                    case KC_W: magic_tap_repeatable(KC_X); break;
                    case KC_X: magic_tap_repeatable(KC_D); break;
                }
                magic_capitalize_next = false;
                last_magic_trigger = MAGIC_J;
                last_magic_repeat_keycode = magic_repeat_keycode;
                set_last_keycode(magic_remembered_keycode);
                return false;
            }
            case MAGIC_K: {
                if (repeat_last_magic_key(MAGIC_K)) {
                    return false;
                }
                magic_remembered_keycode = MAGIC_K;
                magic_repeat_keycode = KC_NO;
                switch (magic_prepare_last_keycode(get_last_keycode())) {
                    case KC_B: magic_decode_send_suffix(311, 'e'); /* emits "efore " -> "before " */ break;
                    case KC_C: magic_replace_decode_send_cap(9, '\0'); /* emits "'s" */ break;
                    case KC_D: magic_decode_send_suffix(663, 's'); /* emits "oes " -> "does " */ break;
                    case KC_E: magic_decode_send_suffix(983, 'n'); /* emits "xplain " -> "explain " */ break;
                    case KC_G: magic_replace_decode_send_cap(860, 't'); /* emits "suggest " */ break;
                    case KC_K: magic_decode_send_suffix(621, 'w'); /* emits "new " -> "knew " */ break;
                    case KC_L: magic_tap_repeatable(KC_B); break;
                    case KC_M: magic_tap_repeatable(KC_T); break;
                    case KC_N: magic_tap_repeatable(KC_P); break;
                    case KC_P: magic_replace_decode_send_cap(47, 's'); /* emits "Prometheus " */ break;
                    case KC_S: magic_decode_send_suffix(683, 'g'); /* emits "omething " -> "something " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_J); break;
                    case KC_T: magic_decode_send_suffix(481, 't'); /* emits "hought " -> "thought " */ break;
                    case KC_W: magic_decode_send_suffix(724, 'e'); /* emits "orse " -> "worse " */ break;
                    case KC_X: magic_replace_decode_send_cap(376, 'e'); /* emits "example " */ break;
                }
                magic_capitalize_next = false;
                last_magic_trigger = MAGIC_K;
                last_magic_repeat_keycode = magic_repeat_keycode;
                set_last_keycode(magic_remembered_keycode);
                return false;
            }
            
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
        case MAGIC_D:
        case MAGIC_E:
        case MAGIC_F:
        case MAGIC_G:
        case MAGIC_H:
        case MAGIC_I:
        case MAGIC_J:
        case MAGIC_K:
            return false;
    }

    prev_keycode = last_keycode;
    last_keycode = keycode;
    last_magic_trigger = KC_NO;
    last_magic_repeat_keycode = KC_NO;
    return true;  // Other keys can be repeated.
}
