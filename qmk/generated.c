/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;

// Magic string decoder lookup tables
static const char magic_char_4bit[] = {
    'b', 'o', 'u', 't', ' ', 'a', 'f', 'e', 'r', 'n', 'y', 'h', 'i', 'g'
};

static const char magic_char_extended[] = {
    'd', 'w', 'c', 's', '\'', 'x', 'p', 'l', 'z', 'v', 'm', 'I', 'j', 'k', 'q', '"', '@', '.', 'G', 'L', 'O', 'T', 'S', 'B', 'P', '/'
};

static const uint8_t magic_string_data[] = {
    0x05, 0x01, 0x23, 0x40, 0x06, 0x50, 0x12, 0x34, 0x05, 0x63, 0x78, 0x40, 0x06, 0x56, 0x37, 0x84,
    0x08, 0x9a, 0x3b, 0xc9, 0xd4, 0x09, 0x59, 0xa3, 0xbc, 0x9d, 0x40, 0x05, 0xd5, 0xc9, 0x40, 0x06,
    0x5d, 0x5c, 0x94, 0x07, 0x91, 0x3b, 0x78, 0x40, 0x08, 0x59, 0x13, 0xb7, 0x84, 0x06, 0x7b, 0xc9,
    0xe0, 0x40, 0x07, 0x07, 0xbc, 0x9f, 0xe0, 0x40, 0x07, 0x73, 0xe1, 0x77, 0x94, 0x08, 0x07, 0x3f,
    0xe1, 0x77, 0x94, 0x07, 0x7f, 0xe2, 0x52, 0xe3, 0x74, 0x08, 0x07, 0xe2, 0x52, 0xe3, 0x74, 0x06,
    0x76, 0x18, 0x74, 0x07, 0x07, 0x61, 0x87, 0x40, 0x08, 0x3b, 0x81, 0x2d, 0xb4, 0x07, 0x3b, 0x12,
    0xdb, 0x40, 0x07, 0x17, 0xe3, 0x9f, 0xe4, 0x34, 0x08, 0xe0, 0x17, 0xe3, 0x9f, 0xe4, 0x34, 0x06,
    0xcf, 0xe0, 0x9f, 0xe4, 0x34, 0x07, 0xe0, 0xcf, 0xe0, 0x9f, 0xe4, 0x34, 0x05, 0x19, 0xe4, 0x34,
    0x06, 0xe0, 0x19, 0xe4, 0x34, 0x04, 0x17, 0xe3, 0x40, 0x05, 0xe0, 0x17, 0xe3, 0x40, 0x09, 0xe5,
    0xe2, 0x7f, 0xe6, 0x3c, 0x19, 0x40, 0x0a, 0x7f, 0xe5, 0xe2, 0x7f, 0xe6, 0x3c, 0x19, 0x40, 0x06,
    0x91, 0x2d, 0xb4, 0x07, 0x79, 0x12, 0xdb, 0x40, 0x04, 0xe5, 0xc3, 0x40, 0x05, 0x7f, 0xe5, 0xc3,
    0x40, 0x05, 0x12, 0x9f, 0xe0, 0x40, 0x06, 0x61, 0x29, 0xe0, 0x40, 0x05, 0xc8, 0xe3, 0x34, 0x06,
    0x6c, 0x8f, 0xe3, 0x34, 0x06, 0xe7, 0x10, 0x5f, 0xe7, 0x40, 0x07, 0xdf, 0xe7, 0x10, 0x5f, 0xe7,
    0x40, 0x09, 0x18, 0xd5, 0x9c, 0xe8, 0x74, 0x08, 0x87, 0x5f, 0xe7, 0xcf, 0xe8, 0x74, 0x04, 0x5f,
    0xe9, 0x74, 0x05, 0xb5, 0xe9, 0x74, 0x0f, 0x9f, 0xe3, 0x38, 0x2f, 0xea, 0x79, 0x35, 0x3c, 0x19,
    0x40, 0x10, 0xc9, 0xe3, 0x38, 0x2f, 0xea, 0x79, 0x35, 0x3c, 0x19, 0x40, 0x05, 0xeb, 0xe4, 0xe9,
    0x74, 0x04, 0x2f, 0xe3, 0x34, 0x05, 0xec, 0x2f, 0xe3, 0x34, 0x04, 0x91, 0xe1, 0x40, 0x05, 0xed,
    0x91, 0xe1, 0x40, 0x08, 0x59, 0xd2, 0x5d, 0x74, 0x09, 0xe7, 0x59, 0xd2, 0x5d, 0x74, 0x05, 0x75,
    0xe9, 0x74, 0x06, 0xe7, 0x75, 0xe9, 0x74, 0x03, 0x79, 0x30, 0x04, 0xea, 0x79, 0x30, 0x02, 0xee,
    0x20, 0x06, 0x2f, 0xea, 0x07, 0x84, 0x07, 0x92, 0xea, 0x07, 0x84, 0x01, 0xef, 0x0d, 0x0f, 0xe3,
    0x78, 0xe9, 0x50, 0xcf, 0xe7, 0xc3, 0xa4, 0x0e, 0x10, 0xe3, 0x78, 0xe9, 0x50, 0xcf, 0xe7, 0xc3,
    0xa4, 0x08, 0xe1, 0xc3, 0xb1, 0x23, 0x40, 0x04, 0x9f, 0xe7, 0xa4, 0x05, 0x19, 0xe7, 0xa4, 0x0a,
    0x81, 0xe0, 0x2f, 0xe2, 0x3c, 0x19, 0x40, 0x0b, 0xe6, 0x81, 0xe0, 0x2f, 0xe2, 0x3c, 0x19, 0x40,
    0x13, 0xe0, 0x7f, 0xe2, 0xe7, 0x58, 0x53, 0xcf, 0xe9, 0x74, 0xe2, 0x19, 0x6c, 0xd4, 0x08, 0x81,
    0x05, 0x0f, 0xe7, 0xa4, 0x09, 0xe6, 0x81, 0x05, 0x0f, 0xe7, 0xa4, 0x08, 0x5f, 0xe7, 0x87, 0x5f,
    0xe0, 0xa4, 0x0b, 0x7f, 0xe9, 0x78, 0xa3, 0xbc, 0x9d, 0x40, 0x07, 0x5f, 0xe7, 0xea, 0x1f, 0xe3,
    0x34, 0x08, 0x3b, 0x12, 0xdb, 0x34, 0x07, 0xe6, 0x71, 0xe6, 0xe7, 0x74, 0x0a, 0x7f, 0xe7, 0x50,
    0x18, 0x53, 0x74, 0x07, 0x1f, 0xea, 0x71, 0x97, 0x40, 0x08, 0xe3, 0x1f, 0xea, 0x71, 0x97, 0x40,
    0x03, 0xc1, 0x90, 0x04, 0xe3, 0xc1, 0x90, 0x09, 0x1f, 0xea, 0x73, 0xbc, 0x9d, 0x40, 0x0a, 0xe3,
    0x1f, 0xea, 0x73, 0xbc, 0x9d, 0x40, 0x04, 0x3c, 0x19, 0x09, 0xb5, 0x9f, 0xed, 0x4a, 0x12, 0x40,
    0x0a, 0x3b, 0x59, 0xed, 0x4a, 0x12, 0x40, 0x09, 0x02, 0xe3, 0xc9, 0x7f, 0xe3, 0xe3, 0x40, 0x0a,
    0x9f, 0xe0, 0x78, 0xe3, 0x35, 0x9f, 0xe0, 0x40, 0x0b, 0x29, 0xe0, 0x78, 0xe3, 0x35, 0x9f, 0xe0,
    0x40, 0x06, 0xe6, 0xe0, 0x53, 0x74, 0x07, 0x2f, 0xe6, 0xe0, 0x53, 0x74, 0x15, 0xe8, 0x7c, 0x3f,
    0xe7, 0xc9, 0xd7, 0x8f, 0xf0, 0xdf, 0xea, 0x5c, 0xe7, 0xf1, 0xe2, 0x1f, 0xea, 0x40, 0x1e, 0xd8,
    0x7d, 0x18, 0xf1, 0xe8, 0x7c, 0x3f, 0xe7, 0xc9, 0xd7, 0x8f, 0xf0, 0xd8, 0x56, 0x59, 0x5f, 0xf1,
    0xe2, 0x1f, 0xea, 0x40, 0x15, 0xd8, 0x7d, 0x18, 0xf0, 0xe8, 0x7c, 0x3f, 0xe7, 0xc9, 0xd7, 0x8f,
    0xf1, 0xe0, 0x74, 0x06, 0x97, 0xe9, 0x78, 0x40, 0x04, 0xcf, 0xe7, 0xe7, 0x40, 0x05, 0xe1, 0xcf,
    0xe7, 0xe7, 0x40, 0x06, 0x5f, 0xe3, 0x9f, 0xe4, 0x34, 0x07, 0xe1, 0x5f, 0xe3, 0x9f, 0xe4, 0x34,
    0x07, 0x5f, 0xe7, 0xe1, 0x5a, 0xe3, 0x40, 0x05, 0xb7, 0x87, 0x40, 0x06, 0xe1, 0xb7, 0x87, 0x40,
    0x05, 0xbc, 0xe2, 0xb4, 0x06, 0xe1, 0xbc, 0xe2, 0xb4, 0x04, 0xb7, 0x94, 0x05, 0xe1, 0xb7, 0x94,
    0x06, 0xe1, 0x18, 0x8a, 0x40, 0x0a, 0x7c, 0x3f, 0xe7, 0xc9, 0xd7, 0x84, 0x0b, 0xe8, 0x7c, 0x3f,
    0xe7, 0xc9, 0xd7, 0x84, 0x07, 0xd8, 0x7d, 0x18, 0x40, 0x08, 0xf2, 0x85, 0x65, 0x95, 0x40, 0x0d,
    0xf2, 0x85, 0x65, 0x95, 0x4f, 0xf3, 0x50, 0xe3, 0x40, 0x0e, 0xf4, 0xe6, 0x79, 0xf5, 0x7f, 0xe7,
    0x7f, 0xea, 0x73, 0x8a, 0x40, 0x0c, 0xf6, 0xe6, 0x8c, 0x9d, 0x4f, 0xf7, 0x11, 0x34, 0x0b, 0xf8,
    0x81, 0xea, 0x73, 0xb7, 0x2f, 0xe3, 0x40, 0x04, 0x59, 0xe0, 0x40, 0x04, 0x3b, 0x74, 0x05, 0x45,
    0x9f, 0xe0, 0x40, 0x05, 0x40, 0x23, 0x40, 0x02, 0xf1, 0xf9
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

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch(index) {
    case C_BASE_ING: return 200;
    case C_BASE_KC_B: return 200;
    case C_BASE_KC_G: return 200;
    case C_BASE_KC_J: return 200;
    case C_BASE_KC_K: return 200;
    case C_BASE_KC_M: return 200;
    case C_BASE_KC_P: return 200;
    case C_BASE_KC_V: return 200;
    case C_BASE_KC_Z: return 200;
    case C_BASE_MAGIC_C: return 200;
    case C_BASE_MAGIC_D: return 200;
    case C_BASE_MAGIC_E: return 200;
    case C_BASE_MAGIC_F: return 200;
    case C_BASE_MAGIC_G: return 200;
    case C_BASE_MAGIC_H: return 200;
    case C_BASE_MAGIC_I: return 200;
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
    case DS_C_BASE_KC_V: return 200;
    case DS_C_BASE_KC_Z: return 200;
    case SUB_1: return 200;
    case S_C_BASE_KC_B: return 200;
    case S_C_BASE_KC_G: return 200;
    case S_C_BASE_KC_J: return 200;
    case S_C_BASE_KC_K: return 200;
    case S_C_BASE_KC_M: return 200;
    case S_C_BASE_KC_P: return 200;
    case S_C_BASE_KC_V: return 200;
    case S_C_BASE_KC_Z: return 200;
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

bool process_record_generated(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Adaptive keys: runs after combo resolution in process_record_user,
        // so combo components are suppressed and prev_keycode reflects the
        // resolved combo keycode (e.g. KC_P not KC_C).
        switch (keycode) {
            case KC_E:
                switch (prev_keycode) {
                    case KC_A: return tap(KC_U);
                    case S(KC_A): return tap(KC_U);
                }
                break;
            case KC_D:
                switch (prev_keycode) {
                    case KC_B: return tap(KC_S);
                    case KC_C: return tap(KC_C);
                    case KC_F: return tap(KC_F);
                    case KC_G: return tap(KC_N);
                    case KC_P: return tap(KC_L);
                    case KC_S: return tap(KC_P);
                    case KC_X: return tap(KC_C);
                    case S(KC_B): return tap(KC_S);
                    case S(KC_C): return tap(KC_C);
                    case S(KC_F): return tap(KC_F);
                    case S(KC_G): return tap(KC_N);
                    case S(KC_P): return tap(KC_L);
                    case S(KC_S): return tap(KC_P);
                    case S(KC_X): return tap(KC_C);
                }
                break;
            case KC_N:
                switch (prev_keycode) {
                    case KC_C: return tap(KC_K);
                    case KC_P: return tap(KC_P);
                    case KC_T: return tap(KC_T);
                    case S(KC_C): return tap(KC_K);
                    case S(KC_P): return tap(KC_P);
                    case S(KC_T): return tap(KC_T);
                }
                break;
            case KC_C:
                switch (prev_keycode) {
                    case KC_D: return tap(KC_V);
                    case KC_L: return tap(KC_V);
                    case S(KC_D): return tap(KC_V);
                    case S(KC_L): return tap(KC_V);
                }
                break;
            case KC_F:
                switch (prev_keycode) {
                    case KC_D: return tap(KC_D);
                    case KC_G: return tap(KC_L);
                    case KC_T: return tap(KC_W);
                    case S(KC_D): return tap(KC_D);
                    case S(KC_G): return tap(KC_L);
                    case S(KC_T): return tap(KC_W);
                }
                break;
            case KC_H:
                switch (prev_keycode) {
                    case KC_D: return tap(KC_G);
                    case KC_E: return tap(KC_E);
                    case KC_L: return tap(KC_P);
                    case KC_M: return tap(KC_M);
                    case KC_N: return tap(KC_N);
                    case KC_O: return tap(KC_O);
                    case KC_U: return tap(KC_A);
                    case S(KC_D): return tap(KC_G);
                    case S(KC_E): return tap(KC_E);
                    case S(KC_L): return tap(KC_P);
                    case S(KC_M): return tap(KC_M);
                    case S(KC_N): return tap(KC_N);
                    case S(KC_O): return tap(KC_O);
                    case S(KC_U): return tap(KC_A);
                }
                break;
            case KC_U:
                switch (prev_keycode) {
                    case KC_E: return tap(KC_O);
                    case S(KC_E): return tap(KC_O);
                }
                break;
            case KC_R:
                switch (prev_keycode) {
                    case KC_K: return tap(KC_N);
                    case KC_L: return tap(KC_L);
                    case KC_M: return tap(KC_P);
                    case KC_N: return tap(KC_G);
                    case KC_S: return tap(KC_S);
                    case KC_Y: return tap(KC_I);
                    case S(KC_K): return tap(KC_N);
                    case S(KC_L): return tap(KC_L);
                    case S(KC_M): return tap(KC_P);
                    case S(KC_N): return tap(KC_G);
                    case S(KC_S): return tap(KC_S);
                    case S(KC_Y): return tap(KC_I);
                }
                break;
            case KC_T:
                switch (prev_keycode) {
                    case KC_M: return tap(KC_B);
                    case S(KC_M): return tap(KC_B);
                }
                break;
            case KC_X:
                switch (prev_keycode) {
                    case KC_N: return tap(KC_L);
                    case KC_R: return tap(KC_R);
                    case KC_W: return tap(KC_N);
                    case S(KC_N): return tap(KC_L);
                    case S(KC_R): return tap(KC_R);
                    case S(KC_W): return tap(KC_N);
                }
                break;
            case KC_Y:
                switch (prev_keycode) {
                    case KC_P: return tap(KC_S);
                    case S(KC_P): return tap(KC_S);
                }
                break;
            case KC_W:
                switch (prev_keycode) {
                    case KC_X: return tap(KC_P);
                    case S(KC_X): return tap(KC_P);
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
                uint16_t remembered_keycode = MAGIC_A;
                uint16_t repeat_keycode = KC_NO;
                switch (get_last_keycode()) {
                    case KC_A: magic_decode_send(0); set_suffix_state('t'); break;
                    case KC_B: magic_decode_send(45); set_suffix_state('d'); break;
                    case KC_C: tap_code16(KC_N); remembered_keycode = KC_N; repeat_keycode = KC_N; break;
                    case KC_D: tap_code16(KC_C); remembered_keycode = KC_C; repeat_keycode = KC_C; break;
                    case KC_E: magic_decode_send(142); set_suffix_state('n'); break;
                    case KC_F: magic_decode_send(177); set_suffix_state('d'); break;
                    case KC_G: magic_decode_send(196); set_suffix_state('l'); break;
                    case KC_I: magic_decode_send(230); set_suffix_state('n'); break;
                    case KC_K: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case KC_L: tap_code16(KC_M); remembered_keycode = KC_M; repeat_keycode = KC_M; break;
                    case KC_M: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case KC_N: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case KC_P: tap_code16(KC_Y); remembered_keycode = KC_Y; repeat_keycode = KC_Y; break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(395); set_suffix_state('y'); break;
                    case KC_S: magic_decode_send(435); set_suffix_state('e'); break;
                    case KC_T: tap_code16(KC_N); remembered_keycode = KC_N; repeat_keycode = KC_N; break;
                    case KC_U: tap_code16(KC_BSPC); magic_decode_send(487); set_suffix_state('s'); break;
                    case KC_V: tap_code16(KC_BSPC); magic_decode_send(524); set_suffix_state('m'); break;
                    case KC_W: magic_decode_send(584); set_suffix_state('l'); break;
                    case KC_Z: magic_decode_send(645); set_suffix_state('r'); break;
                    case S(KC_A): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(4); set_suffix_state('t'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(50); set_suffix_state('d'); break;
                    case S(KC_C): tap_code16(KC_N); remembered_keycode = KC_N; repeat_keycode = KC_N; break;
                    case S(KC_D): tap_code16(KC_C); remembered_keycode = KC_C; repeat_keycode = KC_C; break;
                    case S(KC_E): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(150); set_suffix_state('n'); break;
                    case S(KC_F): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(182); set_suffix_state('d'); break;
                    case S(KC_G): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(202); set_suffix_state('l'); break;
                    case S(KC_I): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(241); set_suffix_state('n'); break;
                    case S(KC_K): tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_L): tap_code16(KC_M); remembered_keycode = KC_M; repeat_keycode = KC_M; break;
                    case S(KC_M): tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_N): tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_P): tap_code16(KC_Y); remembered_keycode = KC_Y; repeat_keycode = KC_Y; break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(395); set_suffix_state('y'); break;
                    case S(KC_S): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(441); set_suffix_state('e'); break;
                    case S(KC_T): tap_code16(KC_N); remembered_keycode = KC_N; repeat_keycode = KC_N; break;
                    case S(KC_U): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(487); set_suffix_state('s'); break;
                    case S(KC_V): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(524); set_suffix_state('m'); break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(589); set_suffix_state('l'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(652); set_suffix_state('r'); break;
                }
                last_magic_trigger = MAGIC_A;
                last_magic_repeat_keycode = repeat_keycode;
                set_last_keycode(remembered_keycode);
                return false;
            }
            case MAGIC_B: {
                if (repeat_last_magic_key(MAGIC_B)) {
                    return false;
                }
                uint16_t remembered_keycode = MAGIC_B;
                uint16_t repeat_keycode = KC_NO;
                switch (get_last_keycode()) {
                    case KC_B: magic_decode_send(56); set_suffix_state('n'); break;
                    case KC_D: tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case KC_E: magic_decode_send(159); set_suffix_state('h'); break;
                    case KC_F: magic_decode_send(187); set_suffix_state('t'); break;
                    case KC_G: tap_code16(KC_F); remembered_keycode = KC_F; repeat_keycode = KC_F; break;
                    case KC_L: tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case KC_M: tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case KC_N: tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case KC_P: tap_code16(KC_M); remembered_keycode = KC_M; repeat_keycode = KC_M; break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(402); set_suffix_state('g'); break;
                    case KC_S: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case KC_T: tap_code16(KC_F); remembered_keycode = KC_F; repeat_keycode = KC_F; break;
                    case KC_V: tap_code16(KC_BSPC); magic_decode_send(542); set_suffix_state('m'); break;
                    case KC_W: magic_decode_send(595); set_suffix_state('t'); break;
                    case KC_X: tap_code16(KC_W); remembered_keycode = KC_W; repeat_keycode = KC_W; break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(660); set_suffix_state('r'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(61); set_suffix_state('n'); break;
                    case S(KC_D): tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case S(KC_E): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(163); set_suffix_state('h'); break;
                    case S(KC_F): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(191); set_suffix_state('t'); break;
                    case S(KC_G): tap_code16(KC_F); remembered_keycode = KC_F; repeat_keycode = KC_F; break;
                    case S(KC_L): tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case S(KC_M): tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case S(KC_N): tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case S(KC_P): tap_code16(KC_M); remembered_keycode = KC_M; repeat_keycode = KC_M; break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(402); set_suffix_state('g'); break;
                    case S(KC_S): tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_T): tap_code16(KC_F); remembered_keycode = KC_F; repeat_keycode = KC_F; break;
                    case S(KC_V): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(542); set_suffix_state('m'); break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(601); set_suffix_state('t'); break;
                    case S(KC_X): tap_code16(KC_W); remembered_keycode = KC_W; repeat_keycode = KC_W; break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(660); set_suffix_state('r'); break;
                }
                last_magic_trigger = MAGIC_B;
                last_magic_repeat_keycode = repeat_keycode;
                set_last_keycode(remembered_keycode);
                return false;
            }
            case MAGIC_C: {
                if (repeat_last_magic_key(MAGIC_C)) {
                    return false;
                }
                uint16_t remembered_keycode = MAGIC_C;
                uint16_t repeat_keycode = KC_NO;
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_E); remembered_keycode = KC_E; repeat_keycode = KC_E; break;
                    case KC_E: tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case KC_O: tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case KC_U: tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case KC_Y: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_A): tap_code16(KC_E); remembered_keycode = KC_E; repeat_keycode = KC_E; break;
                    case S(KC_E): tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case S(KC_O): tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case S(KC_U): tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case S(KC_Y): tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                }
                last_magic_trigger = MAGIC_C;
                last_magic_repeat_keycode = repeat_keycode;
                set_last_keycode(remembered_keycode);
                return false;
            }
            case MAGIC_D: {
                if (repeat_last_magic_key(MAGIC_D)) {
                    return false;
                }
                uint16_t remembered_keycode = MAGIC_D;
                uint16_t repeat_keycode = KC_NO;
                switch (get_last_keycode()) {
                    case KC_A: magic_decode_send(8); set_suffix_state('r'); break;
                    case KC_B: magic_decode_send(67); set_suffix_state('e'); break;
                    case KC_C: tap_code16(KC_P); remembered_keycode = KC_P; repeat_keycode = KC_P; break;
                    case KC_D: magic_decode_send(98); set_suffix_state('t'); break;
                    case KC_DOT: magic_decode_send(727); break;
                    case KC_E: magic_decode_send(168); set_suffix_state('t'); break;
                    case KC_G: tap_code16(KC_K); remembered_keycode = KC_K; repeat_keycode = KC_K; break;
                    case KC_H: magic_decode_send(222); set_suffix_state('e'); break;
                    case KC_I: tap_code16(KC_BSPC); magic_decode_send(252); set_suffix_state('e'); break;
                    case KC_J: magic_decode_send(257); set_suffix_state('t'); break;
                    case KC_K: magic_decode_send(266); set_suffix_state('w'); break;
                    case KC_L: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case KC_M: magic_decode_send(295); break;
                    case KC_N: tap_code16(KC_BSPC); magic_decode_send(302); break;
                    case KC_P: tap_code16(KC_N); remembered_keycode = KC_N; repeat_keycode = KC_N; break;
                    case KC_R: tap_code16(KC_K); remembered_keycode = KC_K; repeat_keycode = KC_K; break;
                    case KC_S: magic_decode_send(448); break;
                    case KC_T: magic_decode_send(448); break;
                    case KC_V: tap_code16(KC_BSPC); magic_decode_send(564); set_suffix_state('e'); break;
                    case KC_W: tap_code16(KC_S); remembered_keycode = KC_S; repeat_keycode = KC_S; break;
                    case KC_X: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(665); set_suffix_state('a'); break;
                    case S(KC_A): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(12); set_suffix_state('r'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(73); set_suffix_state('e'); break;
                    case S(KC_C): tap_code16(KC_P); remembered_keycode = KC_P; repeat_keycode = KC_P; break;
                    case S(KC_D): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(104); set_suffix_state('t'); break;
                    case S(KC_E): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(172); set_suffix_state('t'); break;
                    case S(KC_G): tap_code16(KC_K); remembered_keycode = KC_K; repeat_keycode = KC_K; break;
                    case S(KC_H): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(226); set_suffix_state('e'); break;
                    case S(KC_I): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(252); set_suffix_state('e'); break;
                    case S(KC_J): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(261); set_suffix_state('t'); break;
                    case S(KC_K): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(270); set_suffix_state('w'); break;
                    case S(KC_L): tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_M): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(298); break;
                    case S(KC_N): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(302); break;
                    case S(KC_P): tap_code16(KC_N); remembered_keycode = KC_N; repeat_keycode = KC_N; break;
                    case S(KC_R): tap_code16(KC_K); remembered_keycode = KC_K; repeat_keycode = KC_K; break;
                    case S(KC_S): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(451); break;
                    case S(KC_T): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(470); break;
                    case S(KC_V): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(564); set_suffix_state('e'); break;
                    case S(KC_W): tap_code16(KC_S); remembered_keycode = KC_S; repeat_keycode = KC_S; break;
                    case S(KC_X): tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(665); set_suffix_state('a'); break;
                    default: magic_decode_send(302); break;
                }
                last_magic_trigger = MAGIC_D;
                last_magic_repeat_keycode = repeat_keycode;
                set_last_keycode(remembered_keycode);
                return false;
            }
            case MAGIC_E: {
                if (repeat_last_magic_key(MAGIC_E)) {
                    return false;
                }
                uint16_t remembered_keycode = MAGIC_E;
                uint16_t repeat_keycode = KC_NO;
                switch (get_last_keycode()) {
                    case KC_A: magic_decode_send(16); set_suffix_state('g'); break;
                    case KC_B: tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case KC_C: tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case KC_D: tap_code16(KC_F); remembered_keycode = KC_F; repeat_keycode = KC_F; break;
                    case KC_DOT: tap_code16(KC_SLASH); remembered_keycode = KC_SLASH; repeat_keycode = KC_SLASH; break;
                    case KC_E: tap_code16(KC_U); remembered_keycode = KC_U; repeat_keycode = KC_U; break;
                    case KC_EQUAL: tap_code16(KC_RABK); remembered_keycode = KC_RABK; repeat_keycode = KC_RABK; break;
                    case KC_EXLM: tap_code16(KC_EQUAL); remembered_keycode = KC_EQUAL; repeat_keycode = KC_EQUAL; break;
                    case KC_F: tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case KC_G: tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case KC_H: tap_code16(KC_Y); remembered_keycode = KC_Y; repeat_keycode = KC_Y; break;
                    case KC_I: tap_code16(KC_BSPC); tap_code16(KC_QUOTE); remembered_keycode = KC_QUOTE; repeat_keycode = KC_QUOTE; break;
                    case KC_K: tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case KC_L: tap_code16(KC_C); remembered_keycode = KC_C; repeat_keycode = KC_C; break;
                    case KC_M: tap_code16(KC_L); remembered_keycode = KC_L; repeat_keycode = KC_L; break;
                    case KC_MINUS: tap_code16(KC_RABK); remembered_keycode = KC_RABK; repeat_keycode = KC_RABK; break;
                    case KC_N: tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case KC_O: magic_decode_send(317); set_suffix_state('y'); break;
                    case KC_P: tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(410); set_suffix_state('t'); break;
                    case KC_S: tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case KC_TILD: tap_code16(KC_SLASH); remembered_keycode = KC_SLASH; repeat_keycode = KC_SLASH; break;
                    case KC_W: tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case KC_X: tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(671); set_suffix_state('s'); break;
                    case S(KC_A): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(21); set_suffix_state('g'); break;
                    case S(KC_B): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_C): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_D): tap_code16(KC_F); remembered_keycode = KC_F; repeat_keycode = KC_F; break;
                    case S(KC_E): tap_code16(KC_U); remembered_keycode = KC_U; repeat_keycode = KC_U; break;
                    case S(KC_F): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_G): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_H): tap_code16(KC_Y); remembered_keycode = KC_Y; repeat_keycode = KC_Y; break;
                    case S(KC_I): tap_code16(KC_BSPC); tap_code16(KC_QUOTE); remembered_keycode = KC_QUOTE; repeat_keycode = KC_QUOTE; break;
                    case S(KC_K): tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case S(KC_L): tap_code16(KC_C); remembered_keycode = KC_C; repeat_keycode = KC_C; break;
                    case S(KC_M): tap_code16(KC_L); remembered_keycode = KC_L; repeat_keycode = KC_L; break;
                    case S(KC_N): tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case S(KC_O): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(327); set_suffix_state('y'); break;
                    case S(KC_P): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(410); set_suffix_state('t'); break;
                    case S(KC_S): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_W): tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case S(KC_X): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(671); set_suffix_state('s'); break;
                }
                last_magic_trigger = MAGIC_E;
                last_magic_repeat_keycode = repeat_keycode;
                set_last_keycode(remembered_keycode);
                return false;
            }
            case MAGIC_F: {
                if (repeat_last_magic_key(MAGIC_F)) {
                    return false;
                }
                uint16_t remembered_keycode = MAGIC_F;
                uint16_t repeat_keycode = KC_NO;
                switch (get_last_keycode()) {
                    case KC_M: tap_code16(KC_T); remembered_keycode = KC_T; repeat_keycode = KC_T; break;
                    case KC_N: tap_code16(KC_K); remembered_keycode = KC_K; repeat_keycode = KC_K; break;
                    case KC_R: tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case KC_W: tap_code16(KC_BSPC); magic_decode_send(608); set_suffix_state('s'); break;
                    case S(KC_M): tap_code16(KC_T); remembered_keycode = KC_T; repeat_keycode = KC_T; break;
                    case S(KC_N): tap_code16(KC_K); remembered_keycode = KC_K; repeat_keycode = KC_K; break;
                    case S(KC_R): tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(608); set_suffix_state('s'); break;
                }
                last_magic_trigger = MAGIC_F;
                last_magic_repeat_keycode = repeat_keycode;
                set_last_keycode(remembered_keycode);
                return false;
            }
            case MAGIC_G: {
                if (repeat_last_magic_key(MAGIC_G)) {
                    return false;
                }
                uint16_t remembered_keycode = MAGIC_G;
                uint16_t repeat_keycode = KC_NO;
                switch (get_last_keycode()) {
                    case KC_A: magic_decode_send(27); set_suffix_state('n'); break;
                    case KC_B: magic_decode_send(79); set_suffix_state('e'); break;
                    case KC_COMMA: magic_decode_send(718); break;
                    case KC_D: magic_decode_send(111); set_suffix_state('t'); break;
                    case KC_ENT: magic_decode_send(711); set_suffix_state('d'); break;
                    case KC_G: tap_code16(KC_BSPC); magic_decode_send(209); set_suffix_state('e'); break;
                    case KC_L: magic_decode_send(275); set_suffix_state('e'); break;
                    case KC_N: magic_decode_send(305); set_suffix_state('r'); break;
                    case KC_O: tap_code16(KC_E); remembered_keycode = KC_E; repeat_keycode = KC_E; break;
                    case KC_P: magic_decode_send(351); set_suffix_state('n'); break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(417); set_suffix_state('t'); break;
                    case KC_S: magic_decode_send(455); set_suffix_state('g'); break;
                    case KC_SPC: magic_decode_send(711); set_suffix_state('d'); break;
                    case KC_T: magic_decode_send(473); set_suffix_state('u'); break;
                    case KC_TAB: magic_decode_send(711); set_suffix_state('d'); break;
                    case KC_U: magic_decode_send(495); set_suffix_state('d'); break;
                    case KC_V: tap_code16(KC_BSPC); magic_decode_send(579); set_suffix_state('r'); break;
                    case KC_W: magic_decode_send(615); set_suffix_state('e'); break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(681); set_suffix_state('y'); break;
                    case S(KC_A): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(31); set_suffix_state('n'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(83); set_suffix_state('e'); break;
                    case S(KC_D): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(117); set_suffix_state('t'); break;
                    case S(KC_G): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(209); set_suffix_state('e'); break;
                    case S(KC_L): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(280); set_suffix_state('e'); break;
                    case S(KC_N): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(310); set_suffix_state('r'); break;
                    case S(KC_O): tap_code16(KC_E); remembered_keycode = KC_E; repeat_keycode = KC_E; break;
                    case S(KC_P): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(359); set_suffix_state('n'); break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(417); set_suffix_state('t'); break;
                    case S(KC_S): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(462); set_suffix_state('g'); break;
                    case S(KC_T): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(480); set_suffix_state('u'); break;
                    case S(KC_U): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(504); set_suffix_state('d'); break;
                    case S(KC_V): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(579); set_suffix_state('r'); break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(619); set_suffix_state('e'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(681); set_suffix_state('y'); break;
                }
                last_magic_trigger = MAGIC_G;
                last_magic_repeat_keycode = repeat_keycode;
                set_last_keycode(remembered_keycode);
                return false;
            }
            case MAGIC_H: {
                if (repeat_last_magic_key(MAGIC_H)) {
                    return false;
                }
                uint16_t remembered_keycode = MAGIC_H;
                uint16_t repeat_keycode = KC_NO;
                switch (get_last_keycode()) {
                    case KC_B: tap_code16(KC_BSPC); magic_decode_send(88); set_suffix_state('h'); break;
                    case KC_C: tap_code16(KC_BSPC); tap_code16(KC_EXLM); remembered_keycode = KC_EXLM; repeat_keycode = KC_EXLM; break;
                    case KC_COMMA: magic_decode_send(723); break;
                    case KC_D: magic_decode_send(124); set_suffix_state('t'); break;
                    case KC_ENT: magic_decode_send(715); set_suffix_state('e'); break;
                    case KC_L: magic_decode_send(286); set_suffix_state('e'); break;
                    case KC_N: tap_code16(KC_BSPC); tap_code16(KC_QUOTE); remembered_keycode = KC_QUOTE; repeat_keycode = KC_QUOTE; break;
                    case KC_O: tap_code16(KC_BSPC); magic_decode_send(337); set_suffix_state('t'); break;
                    case KC_P: tap_code16(KC_BSPC); magic_decode_send(368); set_suffix_state('g'); break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(422); set_suffix_state('e'); break;
                    case KC_SPC: magic_decode_send(715); set_suffix_state('e'); break;
                    case KC_T: tap_code16(KC_BSPC); tap_code16(KC_COMMA); remembered_keycode = KC_COMMA; repeat_keycode = KC_COMMA; break;
                    case KC_TAB: magic_decode_send(715); set_suffix_state('e'); break;
                    case KC_W: magic_decode_send(624); set_suffix_state('h'); break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(693); set_suffix_state('t'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(88); set_suffix_state('h'); break;
                    case S(KC_C): tap_code16(KC_BSPC); tap_code16(KC_EXLM); remembered_keycode = KC_EXLM; repeat_keycode = KC_EXLM; break;
                    case S(KC_D): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(128); set_suffix_state('t'); break;
                    case S(KC_L): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(290); set_suffix_state('e'); break;
                    case S(KC_N): tap_code16(KC_BSPC); tap_code16(KC_QUOTE); remembered_keycode = KC_QUOTE; repeat_keycode = KC_QUOTE; break;
                    case S(KC_O): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(337); set_suffix_state('t'); break;
                    case S(KC_P): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(368); set_suffix_state('g'); break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(422); set_suffix_state('e'); break;
                    case S(KC_T): tap_code16(KC_BSPC); tap_code16(KC_COMMA); remembered_keycode = KC_COMMA; repeat_keycode = KC_COMMA; break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(628); set_suffix_state('h'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(693); set_suffix_state('t'); break;
                }
                last_magic_trigger = MAGIC_H;
                last_magic_repeat_keycode = repeat_keycode;
                set_last_keycode(remembered_keycode);
                return false;
            }
            case MAGIC_I: {
                if (repeat_last_magic_key(MAGIC_I)) {
                    return false;
                }
                uint16_t remembered_keycode = MAGIC_I;
                uint16_t repeat_keycode = KC_NO;
                switch (get_last_keycode()) {
                    case KC_A: magic_decode_send(35); set_suffix_state('r'); break;
                    case KC_B: tap_code16(KC_BSPC); magic_decode_send(93); set_suffix_state('h'); break;
                    case KC_C: tap_code16(KC_BSPC); tap_code16(KC_QUES); remembered_keycode = KC_QUES; repeat_keycode = KC_QUES; break;
                    case KC_D: magic_decode_send(133); set_suffix_state('s'); break;
                    case KC_G: tap_code16(KC_BSPC); magic_decode_send(215); set_suffix_state('e'); break;
                    case KC_N: tap_code16(KC_BSPC); tap_code16(KC_DQUO); remembered_keycode = KC_DQUO; repeat_keycode = KC_DQUO; break;
                    case KC_O: magic_decode_send(343); set_suffix_state('y'); break;
                    case KC_P: magic_decode_send(382); set_suffix_state('y'); break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(428); set_suffix_state('e'); break;
                    case KC_SPC: tap_code16(KC_BSPC); SEND_STRING(". "); add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state(); break;
                    case KC_T: tap_code16(KC_BSPC); tap_code16(KC_DOT); remembered_keycode = KC_DOT; repeat_keycode = KC_DOT; break;
                    case KC_U: magic_decode_send(513); set_suffix_state('e'); break;
                    case KC_W: magic_decode_send(633); set_suffix_state('n'); break;
                    case KC_Y: tap_code16(KC_BSPC); magic_decode_send(640); set_suffix_state('y'); break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(702); set_suffix_state('s'); break;
                    case S(KC_A): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(40); set_suffix_state('r'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(93); set_suffix_state('h'); break;
                    case S(KC_C): tap_code16(KC_BSPC); tap_code16(KC_QUES); remembered_keycode = KC_QUES; repeat_keycode = KC_QUES; break;
                    case S(KC_D): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(137); set_suffix_state('s'); break;
                    case S(KC_G): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(215); set_suffix_state('e'); break;
                    case S(KC_N): tap_code16(KC_BSPC); tap_code16(KC_DQUO); remembered_keycode = KC_DQUO; repeat_keycode = KC_DQUO; break;
                    case S(KC_O): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(347); set_suffix_state('y'); break;
                    case S(KC_P): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(388); set_suffix_state('y'); break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(428); set_suffix_state('e'); break;
                    case S(KC_T): tap_code16(KC_BSPC); tap_code16(KC_DOT); remembered_keycode = KC_DOT; repeat_keycode = KC_DOT; break;
                    case S(KC_U): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(518); set_suffix_state('e'); break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(636); set_suffix_state('n'); break;
                    case S(KC_Y): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(640); set_suffix_state('y'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(702); set_suffix_state('s'); break;
                }
                last_magic_trigger = MAGIC_I;
                last_magic_repeat_keycode = repeat_keycode;
                set_last_keycode(remembered_keycode);
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
            return false;
    }

    prev_keycode = last_keycode;
    last_keycode = keycode;
    last_magic_trigger = KC_NO;
    last_magic_repeat_keycode = KC_NO;
    return true;  // Other keys can be repeated.
}
