/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;

// Magic string decoder lookup tables
static const char magic_char_4bit[] = {
    ' ', 'e', 'n', 'o', 't', 'a', 'r', 'i', 'g', 'l', 'h', 'u', 's', 'd'
};

static const char magic_char_extended[] = {
    'b', 'm', 'y', 'w', 'c', 'f', '\'', 'v', 'p', 'z', '.', '@', 'k', 'G', '"', '/', 'L', 'I', 'O', 'T', 'P', 'S', 'B', 'x', 'j', 'q'
};

static const uint8_t magic_string_data[] = {
    0x05, 0x05, 0x2d, 0x00, 0x05, 0x0f, 0xe0, 0xb4, 0x00, 0x01, 0xee, 0x02, 0xea, 0xef, 0x08, 0xed,
    0x65, 0xe5, 0x52, 0x50, 0x0d, 0xed, 0x65, 0xe5, 0x52, 0x50, 0xf0, 0x5f, 0xe0, 0xc0, 0x05, 0xf1,
    0xe6, 0xe7, 0x10, 0x0e, 0xf2, 0xe8, 0x12, 0xf3, 0x19, 0x1f, 0xe1, 0x14, 0x6f, 0xe2, 0x00, 0x0b,
    0xf4, 0x63, 0xe1, 0x14, 0xa1, 0xbc, 0x00, 0x0c, 0xf5, 0xe8, 0x67, 0x28, 0x0f, 0xf6, 0x33, 0x40,
    0x06, 0x5f, 0xe0, 0x3b, 0x40, 0x06, 0x5f, 0xe5, 0x41, 0x60, 0x06, 0x58, 0x57, 0x20, 0x07, 0x59,
    0xe1, 0x3c, 0x40, 0x08, 0x59, 0x61, 0x5d, 0xe2, 0x00, 0x07, 0x59, 0xe3, 0x5f, 0xe2, 0xc0, 0x04,
    0x52, 0xd0, 0x08, 0x52, 0x8b, 0x58, 0x10, 0x08, 0x52, 0x34, 0xa1, 0x60, 0x09, 0x52, 0xe2, 0x4a,
    0x72, 0x80, 0x06, 0x5c, 0x2f, 0xe6, 0x40, 0x08, 0xe0, 0x1f, 0xe4, 0x5b, 0xc1, 0x00, 0x07, 0xe0,
    0x1f, 0xe5, 0x36, 0x10, 0x07, 0xe0, 0x1a, 0x72, 0xd0, 0x08, 0xe0, 0x14, 0xe3, 0x11, 0x20, 0x09,
    0xe0, 0xbc, 0x72, 0x1c, 0xc0, 0x13, 0xd1, 0xe4, 0x95, 0x65, 0x47, 0xe7, 0x10, 0xe4, 0x32, 0xe5,
    0x78, 0x00, 0x07, 0xd7, 0xd2, 0xe6, 0x40, 0x05, 0xd3, 0x1c, 0x00, 0x08, 0xd3, 0x1c, 0x2f, 0xe6,
    0x40, 0x06, 0xd3, 0x2f, 0xe6, 0x40, 0x05, 0x15, 0xe7, 0x10, 0x07, 0x1f, 0xe4, 0x5b, 0xc1, 0x00,
    0x06, 0x1f, 0xe5, 0x36, 0x10, 0x06, 0x1a, 0x72, 0xd0, 0x0a, 0x17, 0x49, 0x72, 0x81, 0x60, 0x0a,
    0x19, 0x5f, 0xe0, 0x36, 0x54, 0x10, 0x07, 0x12, 0x3b, 0x8a, 0x00, 0x03, 0x12, 0x40, 0x07, 0x14,
    0xe3, 0x11, 0x20, 0x0b, 0x1f, 0xe7, 0x16, 0xe2, 0x4a, 0x72, 0x80, 0x0a, 0x1f, 0xf7, 0xe4, 0x1f,
    0xe8, 0x47, 0x32, 0x00, 0x06, 0xe5, 0x76, 0xc4, 0x00, 0x06, 0xe5, 0x3b, 0x2d, 0x00, 0x07, 0x89,
    0x3f, 0xe0, 0x59, 0x00, 0x07, 0x86, 0x18, 0x36, 0x00, 0x1e, 0x86, 0x18, 0x36, 0xea, 0xe9, 0x17,
    0x49, 0x72, 0x81, 0x6f, 0xeb, 0x86, 0x5f, 0xe5, 0x52, 0x5f, 0xea, 0xe4, 0x3f, 0xe1, 0x00, 0x15,
    0x86, 0x18, 0x36, 0xeb, 0xe9, 0x17, 0x49, 0x72, 0x81, 0x6f, 0xea, 0xd1, 0x00, 0x09, 0xa5, 0x2f,
    0xec, 0x0f, 0xe2, 0x3b, 0x00, 0x05, 0xa5, 0xe7, 0x10, 0x04, 0xa1, 0x20, 0x05, 0xa1, 0x61, 0x00,
    0x05, 0xa7, 0xe4, 0xa0, 0x06, 0x7d, 0x2f, 0xe6, 0x40, 0x04, 0x79, 0x90, 0x10, 0x72, 0xc4, 0x6b,
    0xe1, 0x12, 0x45, 0x47, 0x32, 0x00, 0x03, 0x73, 0x20, 0x05, 0x76, 0xc4, 0x00, 0x05, 0xf8, 0xbc,
    0x40, 0x05, 0xec, 0x23, 0xe3, 0x00, 0x09, 0x95, 0x28, 0xb5, 0x81, 0x00, 0x06, 0x91, 0x5f, 0xe7,
    0x10, 0x06, 0x93, 0xe0, 0x59, 0x00, 0x04, 0xe1, 0x12, 0x40, 0x06, 0x21, 0xe7, 0x16, 0x00, 0x04,
    0x23, 0xe3, 0x00, 0x07, 0x2b, 0xe1, 0xe0, 0x16, 0x00, 0x0e, 0x3f, 0xe0, 0xc1, 0x6f, 0xe7, 0x5f,
    0xe0, 0x79, 0x74, 0xe2, 0x00, 0x04, 0x31, 0xc0, 0x07, 0x31, 0xc2, 0xe6, 0x40, 0x07, 0x3f, 0xe1,
    0x13, 0x21, 0x00, 0x09, 0x3f, 0xe1, 0x14, 0xa7, 0x28, 0x00, 0x05, 0x32, 0xe6, 0x40, 0x05, 0x32,
    0x9f, 0xe2, 0x00, 0x09, 0x36, 0x85, 0x27, 0xe9, 0x10, 0x05, 0x3b, 0x2d, 0x00, 0x07, 0xe8, 0x13,
    0xe8, 0x91, 0x00, 0x09, 0xe8, 0x63, 0xe0, 0x5f, 0xe0, 0x9f, 0xe2, 0x00, 0x0b, 0xe8, 0x63, 0xdb,
    0xe4, 0x47, 0x32, 0x00, 0x02, 0xf9, 0xb0, 0x08, 0x61, 0x59, 0x7f, 0xe9, 0x10, 0x08, 0x63, 0xe0,
    0x5f, 0xe0, 0x9f, 0xe2, 0x00, 0x0a, 0x63, 0xdb, 0xe4, 0x47, 0x32, 0x00, 0x04, 0xc7, 0x32, 0x08,
    0xc3, 0xe1, 0x13, 0x21, 0x00, 0x0a, 0xc3, 0xe1, 0x14, 0xa7, 0x28, 0x00, 0x0a, 0x4a, 0x52, 0xec,
    0x0f, 0xe2, 0x3b, 0x00, 0x04, 0x4a, 0x10, 0x07, 0x4a, 0x3b, 0x8a, 0x00, 0x08, 0x4a, 0x3b, 0x8a,
    0x40, 0x08, 0x4a, 0x63, 0xb8, 0xa0, 0x04, 0x47, 0x32, 0x06, 0xbf, 0xe1, 0xe0, 0x16, 0x00, 0x0b,
    0xb2, 0xd1, 0x6c, 0x45, 0x2d, 0x00, 0x07, 0xbf, 0xe8, 0xd5, 0x41, 0x00, 0x07, 0xe3, 0x5c, 0x2f,
    0xe6, 0x40, 0x05, 0xe3, 0xa1, 0x20, 0x06, 0xe3, 0xa1, 0x61, 0x00, 0x06, 0xe3, 0xa7, 0xe4, 0xa0,
    0x05, 0xe3, 0x79, 0x90, 0x08, 0xe3, 0x74, 0xa3, 0xb4, 0x00, 0x06, 0xe3, 0x36, 0x6f, 0xe2, 0x00,
    0x0b, 0xe9, 0x17, 0x49, 0x72, 0x81, 0x60, 0x15, 0xe9, 0x17, 0x49, 0x72, 0x81, 0x6f, 0xeb, 0x8f,
    0xe1, 0x57, 0x9f, 0xea, 0xe4, 0x3f, 0xe1, 0x00
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
            case KC_B:
                switch (prev_keycode) {
                    case KC_L: return tap(KC_K);
                    case S(KC_L): return tap(KC_K);
                }
                break;
            case KC_T:
                switch (prev_keycode) {
                    case KC_M: return tap(KC_B);
                    case S(KC_M): return tap(KC_B);
                }
                break;
            case KC_P:
                switch (prev_keycode) {
                    case KC_N: return tap(KC_K);
                    case S(KC_N): return tap(KC_K);
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
                    case KC_B: magic_decode_send(197); set_suffix_state('d'); break;
                    case KC_C: tap_code16(KC_N); remembered_keycode = KC_N; repeat_keycode = KC_N; break;
                    case KC_D: tap_code16(KC_C); remembered_keycode = KC_C; repeat_keycode = KC_C; break;
                    case KC_F: magic_decode_send(441); set_suffix_state('d'); break;
                    case KC_G: magic_decode_send(369); set_suffix_state('l'); break;
                    case KC_K: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case KC_L: tap_code16(KC_M); remembered_keycode = KC_M; repeat_keycode = KC_M; break;
                    case KC_M: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case KC_N: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case KC_P: tap_code16(KC_Y); remembered_keycode = KC_Y; repeat_keycode = KC_Y; break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(83); set_suffix_state('y'); break;
                    case KC_S: magic_decode_send(413); set_suffix_state('e'); break;
                    case KC_T: tap_code16(KC_N); remembered_keycode = KC_N; repeat_keycode = KC_N; break;
                    case KC_V: tap_code16(KC_BSPC); magic_decode_send(599); set_suffix_state('m'); break;
                    case KC_W: magic_decode_send(329); set_suffix_state('l'); break;
                    case KC_Z: magic_decode_send(201); set_suffix_state('r'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(132); set_suffix_state('d'); break;
                    case S(KC_C): tap_code16(KC_N); remembered_keycode = KC_N; repeat_keycode = KC_N; break;
                    case S(KC_D): tap_code16(KC_C); remembered_keycode = KC_C; repeat_keycode = KC_C; break;
                    case S(KC_F): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(249); set_suffix_state('d'); break;
                    case S(KC_G): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(254); set_suffix_state('l'); break;
                    case S(KC_K): tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_L): tap_code16(KC_M); remembered_keycode = KC_M; repeat_keycode = KC_M; break;
                    case S(KC_M): tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_N): tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_P): tap_code16(KC_Y); remembered_keycode = KC_Y; repeat_keycode = KC_Y; break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(83); set_suffix_state('y'); break;
                    case S(KC_S): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(495); set_suffix_state('e'); break;
                    case S(KC_T): tap_code16(KC_N); remembered_keycode = KC_N; repeat_keycode = KC_N; break;
                    case S(KC_V): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(599); set_suffix_state('m'); break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(576); set_suffix_state('l'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(592); set_suffix_state('r'); break;
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
                    case KC_B: magic_decode_send(222); set_suffix_state('n'); break;
                    case KC_C: tap_code16(KC_BSPC); magic_decode_send(550); set_suffix_state('e'); break;
                    case KC_D: tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case KC_F: magic_decode_send(345); set_suffix_state('t'); break;
                    case KC_G: tap_code16(KC_F); remembered_keycode = KC_F; repeat_keycode = KC_F; break;
                    case KC_K: tap_code16(KC_BSPC); magic_decode_send(64); set_suffix_state('t'); break;
                    case KC_L: tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case KC_M: tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case KC_N: tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case KC_P: tap_code16(KC_M); remembered_keycode = KC_M; repeat_keycode = KC_M; break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(227); set_suffix_state('g'); break;
                    case KC_S: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case KC_T: tap_code16(KC_F); remembered_keycode = KC_F; repeat_keycode = KC_F; break;
                    case KC_V: tap_code16(KC_BSPC); magic_decode_send(265); set_suffix_state('m'); break;
                    case KC_W: magic_decode_send(114); set_suffix_state('t'); break;
                    case KC_X: tap_code16(KC_W); remembered_keycode = KC_W; repeat_keycode = KC_W; break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(260); set_suffix_state('r'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(137); set_suffix_state('n'); break;
                    case S(KC_C): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(550); set_suffix_state('e'); break;
                    case S(KC_D): tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case S(KC_F): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(244); set_suffix_state('t'); break;
                    case S(KC_G): tap_code16(KC_F); remembered_keycode = KC_F; repeat_keycode = KC_F; break;
                    case S(KC_K): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(64); set_suffix_state('t'); break;
                    case S(KC_L): tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case S(KC_M): tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case S(KC_N): tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case S(KC_P): tap_code16(KC_M); remembered_keycode = KC_M; repeat_keycode = KC_M; break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(227); set_suffix_state('g'); break;
                    case S(KC_S): tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_T): tap_code16(KC_F); remembered_keycode = KC_F; repeat_keycode = KC_F; break;
                    case S(KC_V): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(265); set_suffix_state('m'); break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(556); set_suffix_state('t'); break;
                    case S(KC_X): tap_code16(KC_W); remembered_keycode = KC_W; repeat_keycode = KC_W; break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(260); set_suffix_state('r'); break;
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
                    case KC_I: tap_code16(KC_BSPC); tap_code16(KC_QUOTE); remembered_keycode = KC_QUOTE; repeat_keycode = KC_QUOTE; break;
                    case KC_O: tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case KC_U: tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case KC_Y: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_A): tap_code16(KC_E); remembered_keycode = KC_E; repeat_keycode = KC_E; break;
                    case S(KC_E): tap_code16(KC_H); remembered_keycode = KC_H; repeat_keycode = KC_H; break;
                    case S(KC_I): tap_code16(KC_BSPC); tap_code16(KC_QUOTE); remembered_keycode = KC_QUOTE; repeat_keycode = KC_QUOTE; break;
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
                    case KC_B: magic_decode_send(186); set_suffix_state('e'); break;
                    case KC_C: tap_code16(KC_P); remembered_keycode = KC_P; repeat_keycode = KC_P; break;
                    case KC_D: magic_decode_send(408); set_suffix_state('t'); break;
                    case KC_DOT: magic_decode_send(11); break;
                    case KC_F: tap_code16(KC_BSPC); magic_decode_send(143); set_suffix_state('s'); break;
                    case KC_G: tap_code16(KC_K); remembered_keycode = KC_K; repeat_keycode = KC_K; break;
                    case KC_K: magic_decode_send(383); set_suffix_state('w'); break;
                    case KC_L: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case KC_M: magic_decode_send(219); break;
                    case KC_N: tap_code16(KC_BSPC); magic_decode_send(468); break;
                    case KC_P: tap_code16(KC_N); remembered_keycode = KC_N; repeat_keycode = KC_N; break;
                    case KC_R: tap_code16(KC_K); remembered_keycode = KC_K; repeat_keycode = KC_K; break;
                    case KC_S: magic_decode_send(342); break;
                    case KC_T: magic_decode_send(342); break;
                    case KC_V: tap_code16(KC_BSPC); magic_decode_send(287); set_suffix_state('e'); break;
                    case KC_W: tap_code16(KC_S); remembered_keycode = KC_S; repeat_keycode = KC_S; break;
                    case KC_X: tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(14); set_suffix_state('a'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(119); set_suffix_state('e'); break;
                    case S(KC_C): tap_code16(KC_P); remembered_keycode = KC_P; repeat_keycode = KC_P; break;
                    case S(KC_D): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(171); set_suffix_state('t'); break;
                    case S(KC_F): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(143); set_suffix_state('s'); break;
                    case S(KC_G): tap_code16(KC_K); remembered_keycode = KC_K; repeat_keycode = KC_K; break;
                    case S(KC_K): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(353); set_suffix_state('w'); break;
                    case S(KC_L): tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_M): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(374); break;
                    case S(KC_N): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(468); break;
                    case S(KC_P): tap_code16(KC_N); remembered_keycode = KC_N; repeat_keycode = KC_N; break;
                    case S(KC_R): tap_code16(KC_K); remembered_keycode = KC_K; repeat_keycode = KC_K; break;
                    case S(KC_S): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(492); break;
                    case S(KC_T): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(534); break;
                    case S(KC_V): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(287); set_suffix_state('e'); break;
                    case S(KC_W): tap_code16(KC_S); remembered_keycode = KC_S; repeat_keycode = KC_S; break;
                    case S(KC_X): tap_code16(KC_R); remembered_keycode = KC_R; repeat_keycode = KC_R; break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(14); set_suffix_state('a'); break;
                    default: magic_decode_send(468); break;
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
                    case KC_K: tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case KC_L: tap_code16(KC_C); remembered_keycode = KC_C; repeat_keycode = KC_C; break;
                    case KC_M: tap_code16(KC_L); remembered_keycode = KC_L; repeat_keycode = KC_L; break;
                    case KC_MINUS: tap_code16(KC_RABK); remembered_keycode = KC_RABK; repeat_keycode = KC_RABK; break;
                    case KC_N: tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case KC_P: tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(78); set_suffix_state('t'); break;
                    case KC_S: tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case KC_TILD: tap_code16(KC_SLASH); remembered_keycode = KC_SLASH; repeat_keycode = KC_SLASH; break;
                    case KC_W: tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case KC_X: tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(20); set_suffix_state('s'); break;
                    case S(KC_B): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_C): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_D): tap_code16(KC_F); remembered_keycode = KC_F; repeat_keycode = KC_F; break;
                    case S(KC_E): tap_code16(KC_U); remembered_keycode = KC_U; repeat_keycode = KC_U; break;
                    case S(KC_F): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_G): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_H): tap_code16(KC_Y); remembered_keycode = KC_Y; repeat_keycode = KC_Y; break;
                    case S(KC_K): tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case S(KC_L): tap_code16(KC_C); remembered_keycode = KC_C; repeat_keycode = KC_C; break;
                    case S(KC_M): tap_code16(KC_L); remembered_keycode = KC_L; repeat_keycode = KC_L; break;
                    case S(KC_N): tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case S(KC_P): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(78); set_suffix_state('t'); break;
                    case S(KC_S): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_W): tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case S(KC_X): tap_code16(KC_D); remembered_keycode = KC_D; repeat_keycode = KC_D; break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(20); set_suffix_state('s'); break;
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
                    case KC_L: tap_code16(KC_B); remembered_keycode = KC_B; repeat_keycode = KC_B; break;
                    case KC_M: tap_code16(KC_T); remembered_keycode = KC_T; repeat_keycode = KC_T; break;
                    case KC_N: tap_code16(KC_P); remembered_keycode = KC_P; repeat_keycode = KC_P; break;
                    case KC_P: tap_code16(KC_BSPC); magic_decode_send(393); set_suffix_state('y'); break;
                    case KC_R: tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case KC_W: tap_code16(KC_BSPC); magic_decode_send(89); set_suffix_state('s'); break;
                    case S(KC_L): tap_code16(KC_B); remembered_keycode = KC_B; repeat_keycode = KC_B; break;
                    case S(KC_M): tap_code16(KC_T); remembered_keycode = KC_T; repeat_keycode = KC_T; break;
                    case S(KC_N): tap_code16(KC_P); remembered_keycode = KC_P; repeat_keycode = KC_P; break;
                    case S(KC_P): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(393); set_suffix_state('y'); break;
                    case S(KC_R): tap_code16(KC_X); remembered_keycode = KC_X; repeat_keycode = KC_X; break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(89); set_suffix_state('s'); break;
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
                    case KC_B: magic_decode_send(192); set_suffix_state('e'); break;
                    case KC_C: tap_code16(KC_BSPC); magic_decode_send(543); set_suffix_state('d'); break;
                    case KC_COMMA: magic_decode_send(0); break;
                    case KC_D: magic_decode_send(324); set_suffix_state('t'); break;
                    case KC_ENT: magic_decode_send(95); set_suffix_state('d'); break;
                    case KC_F: tap_code16(KC_BSPC); magic_decode_send(235); set_suffix_state('n'); break;
                    case KC_G: tap_code16(KC_BSPC); magic_decode_send(435); set_suffix_state('e'); break;
                    case KC_K: tap_code16(KC_BSPC); magic_decode_send(74); set_suffix_state('n'); break;
                    case KC_L: magic_decode_send(98); set_suffix_state('e'); break;
                    case KC_M: tap_code16(KC_BSPC); magic_decode_send(332); set_suffix_state('n'); break;
                    case KC_N: magic_decode_send(537); set_suffix_state('r'); break;
                    case KC_O: tap_code16(KC_E); remembered_keycode = KC_E; repeat_keycode = KC_E; break;
                    case KC_P: magic_decode_send(485); set_suffix_state('n'); break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(524); set_suffix_state('t'); break;
                    case KC_S: magic_decode_send(419); set_suffix_state('g'); break;
                    case KC_SPC: magic_decode_send(95); set_suffix_state('d'); break;
                    case KC_T: magic_decode_send(301); set_suffix_state('u'); break;
                    case KC_TAB: magic_decode_send(95); set_suffix_state('d'); break;
                    case KC_V: tap_code16(KC_BSPC); magic_decode_send(378); set_suffix_state('r'); break;
                    case KC_W: magic_decode_send(316); set_suffix_state('e'); break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(35); set_suffix_state('y'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(126); set_suffix_state('e'); break;
                    case S(KC_C): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(543); set_suffix_state('d'); break;
                    case S(KC_D): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(162); set_suffix_state('t'); break;
                    case S(KC_F): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(235); set_suffix_state('n'); break;
                    case S(KC_G): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(435); set_suffix_state('e'); break;
                    case S(KC_K): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(74); set_suffix_state('n'); break;
                    case S(KC_L): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(358); set_suffix_state('e'); break;
                    case S(KC_M): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(332); set_suffix_state('n'); break;
                    case S(KC_N): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(387); set_suffix_state('r'); break;
                    case S(KC_O): tap_code16(KC_E); remembered_keycode = KC_E; repeat_keycode = KC_E; break;
                    case S(KC_P): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(460); set_suffix_state('n'); break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(524); set_suffix_state('t'); break;
                    case S(KC_S): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(501); set_suffix_state('g'); break;
                    case S(KC_T): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(508); set_suffix_state('u'); break;
                    case S(KC_V): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(378); set_suffix_state('r'); break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(566); set_suffix_state('e'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(35); set_suffix_state('y'); break;
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
                    case KC_B: tap_code16(KC_BSPC); magic_decode_send(529); set_suffix_state('h'); break;
                    case KC_C: tap_code16(KC_BSPC); tap_code16(KC_EXLM); remembered_keycode = KC_EXLM; repeat_keycode = KC_EXLM; break;
                    case KC_COMMA: magic_decode_send(4); break;
                    case KC_D: magic_decode_send(426); set_suffix_state('t'); break;
                    case KC_ENT: magic_decode_send(516); set_suffix_state('e'); break;
                    case KC_F: tap_code16(KC_BSPC); magic_decode_send(108); set_suffix_state('g'); break;
                    case KC_G: tap_code16(KC_BSPC); magic_decode_send(103); set_suffix_state('r'); break;
                    case KC_K: tap_code16(KC_BSPC); magic_decode_send(309); set_suffix_state('e'); break;
                    case KC_L: magic_decode_send(182); set_suffix_state('e'); break;
                    case KC_M: tap_code16(KC_BSPC); magic_decode_send(30); set_suffix_state('e'); break;
                    case KC_N: tap_code16(KC_BSPC); tap_code16(KC_QUOTE); remembered_keycode = KC_QUOTE; repeat_keycode = KC_QUOTE; break;
                    case KC_P: tap_code16(KC_BSPC); magic_decode_send(149); set_suffix_state('g'); break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(445); set_suffix_state('e'); break;
                    case KC_S: tap_code16(KC_BSPC); magic_decode_send(430); set_suffix_state('y'); break;
                    case KC_SPC: magic_decode_send(516); set_suffix_state('e'); break;
                    case KC_T: tap_code16(KC_BSPC); tap_code16(KC_COMMA); remembered_keycode = KC_COMMA; repeat_keycode = KC_COMMA; break;
                    case KC_TAB: magic_decode_send(516); set_suffix_state('e'); break;
                    case KC_W: magic_decode_send(320); set_suffix_state('h'); break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(55); set_suffix_state('t'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(529); set_suffix_state('h'); break;
                    case S(KC_C): tap_code16(KC_BSPC); tap_code16(KC_EXLM); remembered_keycode = KC_EXLM; repeat_keycode = KC_EXLM; break;
                    case S(KC_D): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(177); set_suffix_state('t'); break;
                    case S(KC_F): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(108); set_suffix_state('g'); break;
                    case S(KC_G): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(103); set_suffix_state('r'); break;
                    case S(KC_K): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(309); set_suffix_state('e'); break;
                    case S(KC_L): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(364); set_suffix_state('e'); break;
                    case S(KC_M): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(30); set_suffix_state('e'); break;
                    case S(KC_N): tap_code16(KC_BSPC); tap_code16(KC_QUOTE); remembered_keycode = KC_QUOTE; repeat_keycode = KC_QUOTE; break;
                    case S(KC_P): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(149); set_suffix_state('g'); break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(445); set_suffix_state('e'); break;
                    case S(KC_S): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(430); set_suffix_state('y'); break;
                    case S(KC_T): tap_code16(KC_BSPC); tap_code16(KC_COMMA); remembered_keycode = KC_COMMA; repeat_keycode = KC_COMMA; break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(571); set_suffix_state('h'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(55); set_suffix_state('t'); break;
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
                    case KC_B: tap_code16(KC_BSPC); magic_decode_send(519); set_suffix_state('h'); break;
                    case KC_C: tap_code16(KC_BSPC); tap_code16(KC_QUES); remembered_keycode = KC_QUES; repeat_keycode = KC_QUES; break;
                    case KC_D: magic_decode_send(405); set_suffix_state('s'); break;
                    case KC_F: tap_code16(KC_BSPC); magic_decode_send(214); set_suffix_state('h'); break;
                    case KC_G: tap_code16(KC_BSPC); magic_decode_send(471); set_suffix_state('e'); break;
                    case KC_K: tap_code16(KC_BSPC); magic_decode_send(349); set_suffix_state('t'); break;
                    case KC_L: tap_code16(KC_BSPC); magic_decode_send(69); set_suffix_state('r'); break;
                    case KC_M: tap_code16(KC_BSPC); magic_decode_send(580); set_suffix_state('t'); break;
                    case KC_N: tap_code16(KC_BSPC); tap_code16(KC_DQUO); remembered_keycode = KC_DQUO; repeat_keycode = KC_DQUO; break;
                    case KC_P: magic_decode_send(477); set_suffix_state('y'); break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(207); set_suffix_state('e'); break;
                    case KC_S: tap_code16(KC_BSPC); magic_decode_send(586); set_suffix_state('y'); break;
                    case KC_SPC: tap_code16(KC_BSPC); SEND_STRING(". "); add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state(); break;
                    case KC_T: tap_code16(KC_BSPC); tap_code16(KC_DOT); remembered_keycode = KC_DOT; repeat_keycode = KC_DOT; break;
                    case KC_W: magic_decode_send(313); set_suffix_state('n'); break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(47); set_suffix_state('s'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(519); set_suffix_state('h'); break;
                    case S(KC_C): tap_code16(KC_BSPC); tap_code16(KC_QUES); remembered_keycode = KC_QUES; repeat_keycode = KC_QUES; break;
                    case S(KC_D): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(167); set_suffix_state('s'); break;
                    case S(KC_F): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(214); set_suffix_state('h'); break;
                    case S(KC_G): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(471); set_suffix_state('e'); break;
                    case S(KC_K): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(349); set_suffix_state('t'); break;
                    case S(KC_L): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(69); set_suffix_state('r'); break;
                    case S(KC_M): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(580); set_suffix_state('t'); break;
                    case S(KC_N): tap_code16(KC_BSPC); tap_code16(KC_DQUO); remembered_keycode = KC_DQUO; repeat_keycode = KC_DQUO; break;
                    case S(KC_P): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(451); set_suffix_state('y'); break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(207); set_suffix_state('e'); break;
                    case S(KC_S): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(586); set_suffix_state('y'); break;
                    case S(KC_T): tap_code16(KC_BSPC); tap_code16(KC_DOT); remembered_keycode = KC_DOT; repeat_keycode = KC_DOT; break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(562); set_suffix_state('n'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(47); set_suffix_state('s'); break;
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
