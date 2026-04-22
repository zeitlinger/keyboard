/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;

// Magic string decoder lookup tables
static const char magic_char_4bit[] = {
    ' ', 'e', 'n', 't', 'o', 'a', 'i', 'r', 'g', 'h', 'u', 'l', 's', 'd'
};

static const char magic_char_extended[] = {
    'b', 'm', 'y', 'c', 'w', 'f', 'p', '\'', 'v', 'z', '.', 'x', '@', 'k', 'G', '"', '/', 'L', 'I', 'O', 'T', 'P', 'S', 'B', 'j', 'q'
};

static const uint8_t magic_string_data[] = {
    0x05, 0x05, 0x2d, 0x00, 0x05, 0x0f, 0xe0, 0xa3, 0x00, 0x01, 0xef, 0x02, 0xea, 0xf0, 0x08, 0xee,
    0x75, 0xe5, 0x52, 0x50, 0x0d, 0xee, 0x75, 0xe5, 0x52, 0x50, 0xf1, 0x5f, 0xe0, 0xc0, 0x05, 0xf2,
    0xe7, 0xe8, 0x10, 0x0e, 0xf3, 0xe6, 0x12, 0xf4, 0x1b, 0x1f, 0xe1, 0x13, 0x7f, 0xe2, 0x00, 0x0b,
    0xf5, 0x74, 0xe1, 0x13, 0x91, 0xac, 0x00, 0x0c, 0xf6, 0xe6, 0x76, 0x28, 0x0f, 0xf7, 0x44, 0x30,
    0x06, 0x5f, 0xe0, 0x4a, 0x30, 0x06, 0x5f, 0xe5, 0x31, 0x70, 0x06, 0x58, 0x56, 0x20, 0x07, 0x5b,
    0xe1, 0x4c, 0x30, 0x08, 0x5b, 0x71, 0x5d, 0xe2, 0x00, 0x04, 0x52, 0xd0, 0x08, 0x52, 0x8a, 0x58,
    0x10, 0x08, 0x52, 0x43, 0x91, 0x70, 0x09, 0x52, 0xe2, 0x39, 0x62, 0x80, 0x06, 0x5c, 0x2f, 0xe7,
    0x30, 0x04, 0x5f, 0xe8, 0x10, 0x08, 0xe0, 0x1f, 0xe3, 0x5a, 0xc1, 0x00, 0x07, 0xe0, 0x1f, 0xe5,
    0x47, 0x10, 0x07, 0xe0, 0x19, 0x62, 0xd0, 0x08, 0xe0, 0x13, 0xe4, 0x11, 0x20, 0x05, 0xe0, 0x4a,
    0x30, 0x0d, 0xe0, 0xc1, 0x7f, 0xe8, 0x5f, 0xe0, 0x6b, 0x63, 0xe2, 0x00, 0x09, 0xe0, 0xac, 0x62,
    0x1c, 0xc0, 0x13, 0xd1, 0xe3, 0xb5, 0x75, 0x36, 0xe8, 0x10, 0xe3, 0x42, 0xe5, 0x68, 0x00, 0x07,
    0xd6, 0xd2, 0xe7, 0x30, 0x05, 0xd4, 0x1c, 0x00, 0x08, 0xd4, 0x1c, 0x2f, 0xe7, 0x30, 0x06, 0xd4,
    0x2f, 0xe7, 0x30, 0x05, 0x15, 0xe8, 0x10, 0x07, 0x1f, 0xe3, 0x5a, 0xc1, 0x00, 0x06, 0x1f, 0xe5,
    0x47, 0x10, 0x06, 0x19, 0x62, 0xd0, 0x0a, 0x16, 0x3b, 0x62, 0x81, 0x70, 0x0a, 0x1b, 0x5f, 0xe0,
    0x47, 0x53, 0x10, 0x07, 0x12, 0x4a, 0x89, 0x00, 0x04, 0x12, 0x30, 0x07, 0x13, 0xe4, 0x11, 0x20,
    0x0b, 0x1f, 0xe8, 0x17, 0xe2, 0x39, 0x62, 0x80, 0x0a, 0x1f, 0xeb, 0xe3, 0x1f, 0xe6, 0x36, 0x42,
    0x00, 0x05, 0x1f, 0xeb, 0x63, 0x00, 0x06, 0xe5, 0x67, 0xc3, 0x00, 0x06, 0xe5, 0x4a, 0x2d, 0x00,
    0x05, 0xe5, 0x31, 0x70, 0x05, 0x85, 0x62, 0x00, 0x07, 0x8b, 0x4f, 0xe0, 0x5b, 0x00, 0x07, 0x87,
    0x18, 0x47, 0x00, 0x1e, 0x87, 0x18, 0x47, 0xea, 0xe9, 0x16, 0x3b, 0x62, 0x81, 0x7f, 0xec, 0x87,
    0x5f, 0xe5, 0x52, 0x5f, 0xea, 0xe3, 0x4f, 0xe1, 0x00, 0x15, 0x87, 0x18, 0x47, 0xec, 0xe9, 0x16,
    0x3b, 0x62, 0x81, 0x7f, 0xea, 0xd1, 0x00, 0x09, 0x95, 0x2f, 0xed, 0x0f, 0xe2, 0x4a, 0x00, 0x05,
    0x95, 0xe8, 0x10, 0x04, 0x91, 0x20, 0x05, 0x91, 0x71, 0x00, 0x05, 0x96, 0xe3, 0x90, 0x06, 0x6d,
    0x2f, 0xe7, 0x30, 0x04, 0x6b, 0xb0, 0x10, 0x62, 0xc3, 0x7a, 0xe1, 0x12, 0x35, 0x36, 0x42, 0x00,
    0x04, 0x64, 0x20, 0x05, 0x67, 0xc3, 0x00, 0x05, 0xf8, 0xac, 0x30, 0x05, 0xed, 0x24, 0xe4, 0x00,
    0x09, 0xb5, 0x28, 0xa5, 0x81, 0x00, 0x06, 0xb1, 0x5f, 0xe8, 0x10, 0x06, 0xb4, 0xe0, 0x5b, 0x00,
    0x05, 0xe1, 0x12, 0x30, 0x0a, 0x2d, 0x17, 0xc3, 0x52, 0xd0, 0x04, 0x2b, 0xe2, 0x00, 0x07, 0x24,
    0x39, 0x17, 0x00, 0x06, 0x24, 0xa8, 0x90, 0x04, 0x24, 0xe4, 0x00, 0x0f, 0x2c, 0x37, 0xaf, 0xe1,
    0x12, 0x35, 0x36, 0x42, 0x00, 0x07, 0x2a, 0xe1, 0xe0, 0x17, 0x00, 0x08, 0x2f, 0xe2, 0x39, 0x62,
    0x80, 0x0e, 0x4f, 0xe0, 0xc1, 0x7f, 0xe8, 0x5f, 0xe0, 0x6b, 0x63, 0xe2, 0x00, 0x04, 0x41, 0xc0,
    0x07, 0x41, 0xc2, 0xe7, 0x30, 0x07, 0x4f, 0xe1, 0x14, 0x21, 0x00, 0x09, 0x4f, 0xe1, 0x13, 0x96,
    0x28, 0x00, 0x05, 0x42, 0xe7, 0x30, 0x05, 0x42, 0xbf, 0xe2, 0x00, 0x09, 0x47, 0x85, 0x26, 0xe9,
    0x10, 0x05, 0x4a, 0x2d, 0x00, 0x06, 0xe6, 0xd5, 0x31, 0x00, 0x07, 0xe6, 0x14, 0xe6, 0xb1, 0x00,
    0x09, 0xe6, 0x74, 0xe0, 0x5f, 0xe0, 0xbf, 0xe2, 0x00, 0x0b, 0xe6, 0x74, 0xda, 0xe3, 0x36, 0x42,
    0x00, 0x02, 0xf9, 0xa0, 0x08, 0x71, 0x5b, 0x6f, 0xe9, 0x10, 0x08, 0x74, 0xe0, 0x5f, 0xe0, 0xbf,
    0xe2, 0x00, 0x0a, 0x74, 0xda, 0xe3, 0x36, 0x42, 0x00, 0x05, 0xc6, 0x42, 0x00, 0x08, 0xc4, 0xe1,
    0x14, 0x21, 0x00, 0x0a, 0xc4, 0xe1, 0x13, 0x96, 0x28, 0x00, 0x0a, 0x39, 0x52, 0xed, 0x0f, 0xe2,
    0x4a, 0x00, 0x04, 0x39, 0x10, 0x07, 0x39, 0x4a, 0x89, 0x00, 0x08, 0x39, 0x4a, 0x89, 0x30, 0x08,
    0x39, 0x74, 0xa8, 0x90, 0x05, 0x36, 0x42, 0x00, 0x06, 0xaf, 0xe1, 0xe0, 0x17, 0x00, 0x0b, 0xa2,
    0xd1, 0x7c, 0x35, 0x2d, 0x00, 0x07, 0xaf, 0xe6, 0xd5, 0x31, 0x00, 0x04, 0xac, 0x30, 0x07, 0xe4,
    0x5c, 0x2f, 0xe7, 0x30, 0x05, 0xe4, 0x91, 0x20, 0x06, 0xe4, 0x91, 0x71, 0x00, 0x06, 0xe4, 0x96,
    0xe3, 0x90, 0x05, 0xe4, 0x6b, 0xb0, 0x08, 0xe4, 0x63, 0x94, 0xa3, 0x00, 0x06, 0xe4, 0x47, 0x7f,
    0xe2, 0x00, 0x09, 0xeb, 0xe3, 0x1f, 0xe6, 0x36, 0x42, 0x00, 0x04, 0xeb, 0x63, 0x00, 0x0b, 0xe9,
    0x16, 0x3b, 0x62, 0x81, 0x70, 0x15, 0xe9, 0x16, 0x3b, 0x62, 0x81, 0x7f, 0xec, 0x8f, 0xe1, 0x56,
    0xbf, 0xea, 0xe3, 0x4f, 0xe1, 0x00
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
            case MAGIC_A:
                switch (get_last_keycode()) {
                    case KC_A: magic_decode_send(141); set_suffix_state('t'); break;
                    case KC_B: magic_decode_send(210); set_suffix_state('d'); break;
                    case KC_C: tap_code16(KC_N); break;
                    case KC_D: tap_code16(KC_C); break;
                    case KC_E: magic_decode_send(658); set_suffix_state('n'); break;
                    case KC_F: magic_decode_send(497); set_suffix_state('d'); break;
                    case KC_G: magic_decode_send(395); set_suffix_state('l'); break;
                    case KC_I: magic_decode_send(427); set_suffix_state('n'); break;
                    case KC_K: tap_code16(KC_R); break;
                    case KC_L: tap_code16(KC_M); break;
                    case KC_M: tap_code16(KC_R); break;
                    case KC_N: tap_code16(KC_R); break;
                    case KC_P: tap_code16(KC_Y); break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(83); set_suffix_state('y'); break;
                    case KC_S: magic_decode_send(469); set_suffix_state('e'); break;
                    case KC_T: tap_code16(KC_N); break;
                    case KC_U: tap_code16(KC_BSPC); magic_decode_send(156); set_suffix_state('s'); break;
                    case KC_V: tap_code16(KC_BSPC); magic_decode_send(677); set_suffix_state('m'); break;
                    case KC_W: magic_decode_send(355); set_suffix_state('l'); break;
                    case KC_Z: magic_decode_send(214); set_suffix_state('r'); break;
                    case S(KC_A): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(64); set_suffix_state('t'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(130); set_suffix_state('d'); break;
                    case S(KC_C): tap_code16(KC_N); break;
                    case S(KC_D): tap_code16(KC_C); break;
                    case S(KC_E): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(248); set_suffix_state('n'); break;
                    case S(KC_F): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(267); set_suffix_state('d'); break;
                    case S(KC_G): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(280); set_suffix_state('l'); break;
                    case S(KC_I): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(358); set_suffix_state('n'); break;
                    case S(KC_K): tap_code16(KC_R); break;
                    case S(KC_L): tap_code16(KC_M); break;
                    case S(KC_M): tap_code16(KC_R); break;
                    case S(KC_N): tap_code16(KC_R); break;
                    case S(KC_P): tap_code16(KC_Y); break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(83); set_suffix_state('y'); break;
                    case S(KC_S): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(557); set_suffix_state('e'); break;
                    case S(KC_T): tap_code16(KC_N); break;
                    case S(KC_U): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(156); set_suffix_state('s'); break;
                    case S(KC_V): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(677); set_suffix_state('m'); break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(642); set_suffix_state('l'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(670); set_suffix_state('r'); break;
                }
                set_last_keycode(MAGIC_A);
                return false;
            case MAGIC_B:
                switch (get_last_keycode()) {
                    case KC_B: magic_decode_send(235); set_suffix_state('n'); break;
                    case KC_D: tap_code16(KC_H); break;
                    case KC_E: magic_decode_send(419); set_suffix_state('h'); break;
                    case KC_F: magic_decode_send(371); set_suffix_state('t'); break;
                    case KC_G: tap_code16(KC_F); break;
                    case KC_L: tap_code16(KC_H); break;
                    case KC_M: tap_code16(KC_H); break;
                    case KC_N: tap_code16(KC_H); break;
                    case KC_P: tap_code16(KC_M); break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(240); set_suffix_state('g'); break;
                    case KC_S: tap_code16(KC_R); break;
                    case KC_T: tap_code16(KC_F); break;
                    case KC_V: tap_code16(KC_BSPC); magic_decode_send(291); set_suffix_state('m'); break;
                    case KC_W: magic_decode_send(108); set_suffix_state('t'); break;
                    case KC_X: tap_code16(KC_W); break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(286); set_suffix_state('r'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(135); set_suffix_state('n'); break;
                    case S(KC_D): tap_code16(KC_H); break;
                    case S(KC_E): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(227); set_suffix_state('h'); break;
                    case S(KC_F): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(262); set_suffix_state('t'); break;
                    case S(KC_G): tap_code16(KC_F); break;
                    case S(KC_L): tap_code16(KC_H); break;
                    case S(KC_M): tap_code16(KC_H); break;
                    case S(KC_N): tap_code16(KC_H); break;
                    case S(KC_P): tap_code16(KC_M); break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(240); set_suffix_state('g'); break;
                    case S(KC_S): tap_code16(KC_R); break;
                    case S(KC_T): tap_code16(KC_F); break;
                    case S(KC_V): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(291); set_suffix_state('m'); break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(622); set_suffix_state('t'); break;
                    case S(KC_X): tap_code16(KC_W); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(286); set_suffix_state('r'); break;
                }
                set_last_keycode(MAGIC_B);
                return false;
            case MAGIC_C:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_E); break;
                    case KC_E: tap_code16(KC_H); break;
                    case KC_O: tap_code16(KC_H); break;
                    case KC_U: tap_code16(KC_H); break;
                    case KC_Y: tap_code16(KC_R); break;
                    case S(KC_A): tap_code16(KC_E); break;
                    case S(KC_E): tap_code16(KC_H); break;
                    case S(KC_O): tap_code16(KC_H); break;
                    case S(KC_U): tap_code16(KC_H); break;
                    case S(KC_Y): tap_code16(KC_R); break;
                }
                set_last_keycode(MAGIC_C);
                return false;
            case MAGIC_D:
                switch (get_last_keycode()) {
                    case KC_A: magic_decode_send(272); set_suffix_state('r'); break;
                    case KC_B: magic_decode_send(199); set_suffix_state('e'); break;
                    case KC_C: tap_code16(KC_P); break;
                    case KC_D: magic_decode_send(464); set_suffix_state('t'); break;
                    case KC_DOT: magic_decode_send(11); break;
                    case KC_E: magic_decode_send(666); set_suffix_state('t'); break;
                    case KC_G: tap_code16(KC_K); break;
                    case KC_H: magic_decode_send(113); set_suffix_state('e'); break;
                    case KC_I: tap_code16(KC_BSPC); magic_decode_send(30); set_suffix_state('e'); break;
                    case KC_J: magic_decode_send(619); set_suffix_state('t'); break;
                    case KC_K: magic_decode_send(423); set_suffix_state('w'); break;
                    case KC_L: tap_code16(KC_R); break;
                    case KC_M: magic_decode_send(232); set_suffix_state('t'); break;
                    case KC_N: tap_code16(KC_BSPC); magic_decode_send(529); break;
                    case KC_P: tap_code16(KC_N); break;
                    case KC_R: tap_code16(KC_K); break;
                    case KC_S: magic_decode_send(368); set_suffix_state('n'); break;
                    case KC_T: magic_decode_send(368); set_suffix_state('n'); break;
                    case KC_V: tap_code16(KC_BSPC); magic_decode_send(313); set_suffix_state('e'); break;
                    case KC_W: tap_code16(KC_S); break;
                    case KC_X: tap_code16(KC_R); break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(14); set_suffix_state('a'); break;
                    case S(KC_A): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(69); set_suffix_state('r'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(117); set_suffix_state('e'); break;
                    case S(KC_C): tap_code16(KC_P); break;
                    case S(KC_D): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(184); set_suffix_state('t'); break;
                    case S(KC_E): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(257); set_suffix_state('t'); break;
                    case S(KC_G): tap_code16(KC_K); break;
                    case S(KC_H): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(335); set_suffix_state('e'); break;
                    case S(KC_I): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(30); set_suffix_state('e'); break;
                    case S(KC_J): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(375); set_suffix_state('t'); break;
                    case S(KC_K): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(379); set_suffix_state('w'); break;
                    case S(KC_L): tap_code16(KC_R); break;
                    case S(KC_M): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(400); set_suffix_state('t'); break;
                    case S(KC_N): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(529); break;
                    case S(KC_P): tap_code16(KC_N); break;
                    case S(KC_R): tap_code16(KC_K); break;
                    case S(KC_S): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(553); set_suffix_state('n'); break;
                    case S(KC_T): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(596); set_suffix_state('n'); break;
                    case S(KC_V): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(313); set_suffix_state('e'); break;
                    case S(KC_W): tap_code16(KC_S); break;
                    case S(KC_X): tap_code16(KC_R); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(14); set_suffix_state('a'); break;
                    default: magic_decode_send(529); break;
                }
                set_last_keycode(MAGIC_D);
                return false;
            case MAGIC_E:
                switch (get_last_keycode()) {
                    case KC_A: magic_decode_send(443); set_suffix_state('g'); break;
                    case KC_B: tap_code16(KC_D); break;
                    case KC_C: tap_code16(KC_D); break;
                    case KC_D: tap_code16(KC_F); break;
                    case KC_DOT: tap_code16(KC_SLASH); break;
                    case KC_E: tap_code16(KC_U); break;
                    case KC_EQUAL: tap_code16(KC_RABK); break;
                    case KC_EXLM: tap_code16(KC_EQUAL); break;
                    case KC_F: tap_code16(KC_D); break;
                    case KC_G: tap_code16(KC_D); break;
                    case KC_H: tap_code16(KC_Y); break;
                    case KC_I: tap_code16(KC_BSPC); tap_code16(KC_QUOTE); break;
                    case KC_K: tap_code16(KC_X); break;
                    case KC_L: tap_code16(KC_C); break;
                    case KC_M: tap_code16(KC_L); break;
                    case KC_MINUS: tap_code16(KC_RABK); break;
                    case KC_N: tap_code16(KC_X); break;
                    case KC_O: magic_decode_send(145); set_suffix_state('y'); break;
                    case KC_P: tap_code16(KC_D); break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(78); set_suffix_state('t'); break;
                    case KC_S: tap_code16(KC_D); break;
                    case KC_TILD: tap_code16(KC_SLASH); break;
                    case KC_W: tap_code16(KC_X); break;
                    case KC_X: tap_code16(KC_D); break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(20); set_suffix_state('s'); break;
                    case S(KC_A): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(102); set_suffix_state('g'); break;
                    case S(KC_B): tap_code16(KC_D); break;
                    case S(KC_C): tap_code16(KC_D); break;
                    case S(KC_D): tap_code16(KC_F); break;
                    case S(KC_E): tap_code16(KC_U); break;
                    case S(KC_F): tap_code16(KC_D); break;
                    case S(KC_G): tap_code16(KC_D); break;
                    case S(KC_H): tap_code16(KC_Y); break;
                    case S(KC_I): tap_code16(KC_BSPC); tap_code16(KC_QUOTE); break;
                    case S(KC_K): tap_code16(KC_X); break;
                    case S(KC_L): tap_code16(KC_C); break;
                    case S(KC_M): tap_code16(KC_L); break;
                    case S(KC_N): tap_code16(KC_X); break;
                    case S(KC_O): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(449); set_suffix_state('y'); break;
                    case S(KC_P): tap_code16(KC_D); break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(78); set_suffix_state('t'); break;
                    case S(KC_S): tap_code16(KC_D); break;
                    case S(KC_W): tap_code16(KC_X); break;
                    case S(KC_X): tap_code16(KC_D); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(20); set_suffix_state('s'); break;
                }
                set_last_keycode(MAGIC_E);
                return false;
            case MAGIC_F:
                switch (get_last_keycode()) {
                    case KC_M: tap_code16(KC_T); break;
                    case KC_N: tap_code16(KC_K); break;
                    case KC_R: tap_code16(KC_X); break;
                    case S(KC_M): tap_code16(KC_T); break;
                    case S(KC_N): tap_code16(KC_K); break;
                    case S(KC_R): tap_code16(KC_X); break;
                }
                set_last_keycode(MAGIC_F);
                return false;
            case MAGIC_G:
                switch (get_last_keycode()) {
                    case KC_A: magic_decode_send(276); set_suffix_state('n'); break;
                    case KC_B: magic_decode_send(205); set_suffix_state('e'); break;
                    case KC_COMMA: magic_decode_send(0); break;
                    case KC_D: magic_decode_send(350); set_suffix_state('t'); break;
                    case KC_ENT: magic_decode_send(89); set_suffix_state('d'); break;
                    case KC_G: tap_code16(KC_BSPC); magic_decode_send(491); set_suffix_state('e'); break;
                    case KC_L: magic_decode_send(92); set_suffix_state('e'); break;
                    case KC_N: magic_decode_send(600); set_suffix_state('r'); break;
                    case KC_O: tap_code16(KC_E); break;
                    case KC_P: magic_decode_send(546); set_suffix_state('n'); break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(586); set_suffix_state('t'); break;
                    case KC_S: magic_decode_send(475); set_suffix_state('g'); break;
                    case KC_SPC: magic_decode_send(89); set_suffix_state('d'); break;
                    case KC_T: magic_decode_send(327); set_suffix_state('u'); break;
                    case KC_TAB: magic_decode_send(89); set_suffix_state('d'); break;
                    case KC_U: magic_decode_send(404); set_suffix_state('d'); break;
                    case KC_W: magic_decode_send(342); set_suffix_state('e'); break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(35); set_suffix_state('y'); break;
                    case S(KC_A): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(74); set_suffix_state('n'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(124); set_suffix_state('e'); break;
                    case S(KC_D): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(175); set_suffix_state('t'); break;
                    case S(KC_G): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(491); set_suffix_state('e'); break;
                    case S(KC_L): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(384); set_suffix_state('e'); break;
                    case S(KC_N): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(437); set_suffix_state('r'); break;
                    case S(KC_O): tap_code16(KC_E); break;
                    case S(KC_P): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(521); set_suffix_state('n'); break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(586); set_suffix_state('t'); break;
                    case S(KC_S): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(563); set_suffix_state('g'); break;
                    case S(KC_T): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(570); set_suffix_state('u'); break;
                    case S(KC_U): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(606); set_suffix_state('d'); break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(632); set_suffix_state('e'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(35); set_suffix_state('y'); break;
                }
                set_last_keycode(MAGIC_G);
                return false;
            case MAGIC_H:
                switch (get_last_keycode()) {
                    case KC_B: tap_code16(KC_BSPC); magic_decode_send(591); set_suffix_state('h'); break;
                    case KC_C: tap_code16(KC_BSPC); tap_code16(KC_EXLM); break;
                    case KC_COMMA: magic_decode_send(4); break;
                    case KC_D: magic_decode_send(482); set_suffix_state('t'); break;
                    case KC_ENT: magic_decode_send(578); set_suffix_state('e'); break;
                    case KC_L: magic_decode_send(195); set_suffix_state('e'); break;
                    case KC_N: tap_code16(KC_BSPC); tap_code16(KC_QUOTE); break;
                    case KC_O: tap_code16(KC_BSPC); magic_decode_send(646); set_suffix_state('t'); break;
                    case KC_P: tap_code16(KC_BSPC); magic_decode_send(162); set_suffix_state('g'); break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(506); set_suffix_state('e'); break;
                    case KC_SPC: magic_decode_send(578); set_suffix_state('e'); break;
                    case KC_T: tap_code16(KC_BSPC); tap_code16(KC_COMMA); break;
                    case KC_TAB: magic_decode_send(578); set_suffix_state('e'); break;
                    case KC_W: magic_decode_send(346); set_suffix_state('h'); break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(55); set_suffix_state('t'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(591); set_suffix_state('h'); break;
                    case S(KC_C): tap_code16(KC_BSPC); tap_code16(KC_EXLM); break;
                    case S(KC_D): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(190); set_suffix_state('t'); break;
                    case S(KC_L): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(390); set_suffix_state('e'); break;
                    case S(KC_N): tap_code16(KC_BSPC); tap_code16(KC_QUOTE); break;
                    case S(KC_O): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(646); set_suffix_state('t'); break;
                    case S(KC_P): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(162); set_suffix_state('g'); break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(506); set_suffix_state('e'); break;
                    case S(KC_T): tap_code16(KC_BSPC); tap_code16(KC_COMMA); break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(637); set_suffix_state('h'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(55); set_suffix_state('t'); break;
                }
                set_last_keycode(MAGIC_H);
                return false;
            case MAGIC_I:
                switch (get_last_keycode()) {
                    case KC_A: magic_decode_send(414); set_suffix_state('r'); break;
                    case KC_B: tap_code16(KC_BSPC); magic_decode_send(581); set_suffix_state('h'); break;
                    case KC_C: tap_code16(KC_BSPC); tap_code16(KC_QUES); break;
                    case KC_D: magic_decode_send(461); set_suffix_state('s'); break;
                    case KC_G: tap_code16(KC_BSPC); magic_decode_send(532); set_suffix_state('e'); break;
                    case KC_N: tap_code16(KC_BSPC); tap_code16(KC_DQUO); break;
                    case KC_O: magic_decode_send(410); set_suffix_state('y'); break;
                    case KC_P: magic_decode_send(538); set_suffix_state('y'); break;
                    case KC_R: tap_code16(KC_BSPC); magic_decode_send(220); set_suffix_state('e'); break;
                    case KC_SPC: tap_code16(KC_BSPC); SEND_STRING(". "); add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state(); break;
                    case KC_T: tap_code16(KC_BSPC); tap_code16(KC_DOT); break;
                    case KC_U: magic_decode_send(501); set_suffix_state('e'); break;
                    case KC_W: magic_decode_send(339); set_suffix_state('n'); break;
                    case KC_Y: tap_code16(KC_BSPC); magic_decode_send(652); set_suffix_state('y'); break;
                    case KC_Z: tap_code16(KC_BSPC); magic_decode_send(47); set_suffix_state('s'); break;
                    case S(KC_A): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(97); set_suffix_state('r'); break;
                    case S(KC_B): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(581); set_suffix_state('h'); break;
                    case S(KC_C): tap_code16(KC_BSPC); tap_code16(KC_QUES); break;
                    case S(KC_D): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(180); set_suffix_state('s'); break;
                    case S(KC_G): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(532); set_suffix_state('e'); break;
                    case S(KC_N): tap_code16(KC_BSPC); tap_code16(KC_DQUO); break;
                    case S(KC_O): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(486); set_suffix_state('y'); break;
                    case S(KC_P): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(512); set_suffix_state('y'); break;
                    case S(KC_R): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(220); set_suffix_state('e'); break;
                    case S(KC_T): tap_code16(KC_BSPC); tap_code16(KC_DOT); break;
                    case S(KC_U): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(613); set_suffix_state('e'); break;
                    case S(KC_W): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(628); set_suffix_state('n'); break;
                    case S(KC_Y): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(652); set_suffix_state('y'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); add_oneshot_mods(MOD_BIT(KC_LSFT)); magic_decode_send(47); set_suffix_state('s'); break;
                }
                set_last_keycode(MAGIC_I);
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
    return true;  // Other keys can be repeated.
}
