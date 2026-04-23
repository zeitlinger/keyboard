/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;

static bool magic_capitalize_next = false;

// Magic string decoder lookup tables
static const char magic_char_4bit[] = {
    ' ', 'e', 'n', 'o', 't', 'a', 'r', 'i', 'l', 'h', 'g', 's', 'u', 'd'
};

static const char magic_char_extended[] = {
    'b', '\'', 'm', 'w', 'y', 'c', 'p', 'v', 'f', 'z', '.', 'x', 'k', '@', 'G', '"', 'L', 'I', 'O', 'T', 'P', 'S', 'B', 'j', 'q'
};

static const uint8_t magic_string_data[] = {
    0x01, 0xef, 0x02, 0xe1, 0xd0, 0x03, 0xe1, 0x88, 0x04, 0xe1, 0x88, 0x00, 0x03, 0xe1, 0x61, 0x02,
    0xe1, 0xb0, 0x03, 0xe1, 0xe7, 0x10, 0x02, 0xea, 0x00, 0x08, 0xee, 0x65, 0xe8, 0x52, 0x50, 0x0d,
    0xee, 0x65, 0xe8, 0x52, 0x50, 0xf0, 0x5f, 0xe0, 0xb0, 0x05, 0xf1, 0xe1, 0xe7, 0x10, 0x0e, 0xf2,
    0xe6, 0x12, 0xf3, 0x18, 0x1f, 0xe2, 0x14, 0x6f, 0xe4, 0x00, 0x0b, 0xf4, 0x63, 0xe2, 0x14, 0x91,
    0xcb, 0x00, 0x0c, 0xf5, 0xe6, 0x67, 0x2a, 0x0f, 0xf6, 0x33, 0x40, 0x06, 0x5f, 0xe0, 0x3c, 0x40,
    0x06, 0x5f, 0xe8, 0x41, 0x60, 0x06, 0x5a, 0x57, 0x20, 0x07, 0x58, 0xe2, 0x3b, 0x40, 0x08, 0x58,
    0x61, 0x5d, 0xe4, 0x00, 0x07, 0x58, 0xe3, 0x5f, 0xe4, 0xb0, 0x04, 0x52, 0xd0, 0x08, 0x52, 0xac,
    0x5a, 0x10, 0x08, 0x52, 0x34, 0x91, 0x60, 0x09, 0x52, 0xe4, 0x49, 0x72, 0xa0, 0x06, 0x5b, 0x2f,
    0xe1, 0x40, 0x08, 0xe0, 0x1f, 0xe5, 0x5c, 0xb1, 0x00, 0x07, 0xe0, 0x1f, 0xe8, 0x36, 0x10, 0x07,
    0xe0, 0x19, 0x72, 0xd0, 0x08, 0xe0, 0x14, 0xe3, 0x11, 0x20, 0x09, 0xe0, 0xcb, 0x72, 0x1b, 0xb0,
    0x13, 0xd1, 0xe5, 0x85, 0x65, 0x47, 0xe7, 0x10, 0xe5, 0x32, 0xe8, 0x7a, 0x00, 0x07, 0xd7, 0xd2,
    0xe1, 0x40, 0x05, 0xd3, 0x1b, 0x00, 0x08, 0xd3, 0x1b, 0x2f, 0xe1, 0x40, 0x06, 0xd3, 0x2f, 0xe1,
    0x40, 0x07, 0x15, 0x87, 0xe9, 0x10, 0x05, 0x15, 0xe7, 0x10, 0x07, 0x1f, 0xe5, 0x5c, 0xb1, 0x00,
    0x06, 0x1f, 0xe8, 0x36, 0x10, 0x06, 0x19, 0x72, 0xd0, 0x0a, 0x17, 0x48, 0x72, 0xa1, 0x60, 0x0a,
    0x18, 0x5f, 0xe0, 0x36, 0x54, 0x10, 0x03, 0x12, 0x40, 0x06, 0x13, 0xe6, 0x81, 0x00, 0x07, 0x14,
    0xe3, 0x11, 0x20, 0x0b, 0x1f, 0xe7, 0x16, 0xe4, 0x49, 0x72, 0xa0, 0x0a, 0x1f, 0xeb, 0xe5, 0x1f,
    0xe6, 0x47, 0x32, 0x00, 0x08, 0x1f, 0xeb, 0xe5, 0x8c, 0xd1, 0x00, 0x08, 0x1f, 0xeb, 0xe6, 0x85,
    0x72, 0x00, 0x09, 0x1f, 0xeb, 0xe6, 0x87, 0xe5, 0x74, 0x00, 0x06, 0xe8, 0x76, 0xb4, 0x00, 0x06,
    0xe8, 0x3c, 0x2d, 0x00, 0x07, 0xa8, 0x3f, 0xe0, 0x58, 0x00, 0x07, 0xa6, 0x1a, 0x36, 0x00, 0x1e,
    0xa6, 0x1a, 0x36, 0xea, 0xe9, 0x17, 0x48, 0x72, 0xa1, 0x6f, 0xed, 0xa6, 0x5f, 0xe8, 0x52, 0x5f,
    0xea, 0xe5, 0x3f, 0xe2, 0x00, 0x15, 0xa6, 0x1a, 0x36, 0xed, 0xe9, 0x17, 0x48, 0x72, 0xa1, 0x6f,
    0xea, 0xd1, 0x00, 0x09, 0x95, 0x2f, 0xec, 0x0f, 0xe4, 0x3c, 0x00, 0x05, 0x95, 0xe7, 0x10, 0x04,
    0x91, 0x20, 0x05, 0x91, 0x61, 0x00, 0x05, 0x97, 0xe5, 0x90, 0x06, 0x93, 0xca, 0x90, 0x07, 0x96,
    0x3c, 0xa9, 0x00, 0x06, 0x7d, 0x2f, 0xe1, 0x40, 0x04, 0x78, 0x80, 0x08, 0x7f, 0xe2, 0xe6, 0x63,
    0xe7, 0x10, 0x10, 0x72, 0xb4, 0x6c, 0xe2, 0x12, 0x45, 0x47, 0x32, 0x00, 0x03, 0x73, 0x20, 0x05,
    0x76, 0xb4, 0x00, 0x05, 0xf7, 0xcb, 0x40, 0x05, 0xec, 0x21, 0xe3, 0x00, 0x05, 0xec, 0x23, 0xe3,
    0x00, 0x09, 0x85, 0x2a, 0xc5, 0xa1, 0x00, 0x06, 0x81, 0x5f, 0xe7, 0x10, 0x06, 0x83, 0xe0, 0x58,
    0x00, 0x04, 0xe2, 0x12, 0x40, 0x03, 0x2f, 0xe1, 0x40, 0x06, 0x21, 0xe7, 0x16, 0x00, 0x04, 0x21,
    0xe3, 0x00, 0x04, 0x23, 0xe3, 0x00, 0x07, 0x2c, 0xe2, 0xe0, 0x16, 0x00, 0x0e, 0x3f, 0xe0, 0xb1,
    0x6f, 0xe7, 0x5f, 0xe0, 0x78, 0x74, 0xe4, 0x00, 0x04, 0x31, 0xb0, 0x07, 0x31, 0xb2, 0xe1, 0x40,
    0x07, 0x3f, 0xe2, 0x13, 0x21, 0x00, 0x09, 0x3f, 0xe2, 0x14, 0x97, 0x2a, 0x00, 0x05, 0x32, 0xe1,
    0x40, 0x05, 0x32, 0x8f, 0xe4, 0x00, 0x09, 0x36, 0xa5, 0x27, 0xe9, 0x10, 0x05, 0x36, 0x6f, 0xe4,
    0x00, 0x05, 0x36, 0xb1, 0x00, 0x05, 0x3c, 0x2d, 0x00, 0x07, 0xe6, 0x13, 0xe6, 0x81, 0x00, 0x09,
    0xe6, 0x63, 0xe0, 0x5f, 0xe0, 0x8f, 0xe4, 0x00, 0x0b, 0xe6, 0x63, 0xdc, 0xe5, 0x47, 0x32, 0x00,
    0x02, 0xf8, 0xc0, 0x08, 0x61, 0x58, 0x7f, 0xe9, 0x10, 0x08, 0x63, 0xe0, 0x5f, 0xe0, 0x8f, 0xe4,
    0x00, 0x0a, 0x63, 0xdc, 0xe5, 0x47, 0x32, 0x00, 0x04, 0xb7, 0x32, 0x08, 0xb3, 0xe2, 0x13, 0x21,
    0x00, 0x0a, 0xb3, 0xe2, 0x14, 0x97, 0x2a, 0x00, 0x0a, 0x49, 0x52, 0xec, 0x0f, 0xe4, 0x3c, 0x00,
    0x04, 0x49, 0x10, 0x07, 0x49, 0x3c, 0xa9, 0x00, 0x08, 0x49, 0x3c, 0xa9, 0x40, 0x08, 0x49, 0x63,
    0xca, 0x90, 0x04, 0x47, 0x32, 0x06, 0xcf, 0xe2, 0xe0, 0x16, 0x00, 0x0b, 0xc2, 0xd1, 0x6b, 0x45,
    0x2d, 0x00, 0x07, 0xcf, 0xe6, 0xd5, 0x41, 0x00, 0x08, 0xcb, 0x72, 0x1b, 0xb0, 0x07, 0xe3, 0x5b,
    0x2f, 0xe1, 0x40, 0x05, 0xe3, 0x91, 0x20, 0x06, 0xe3, 0x91, 0x61, 0x00, 0x06, 0xe3, 0x97, 0xe5,
    0x90, 0x05, 0xe3, 0x78, 0x80, 0x08, 0xe3, 0x74, 0x93, 0xc4, 0x00, 0x06, 0xe3, 0x36, 0x6f, 0xe4,
    0x00, 0x06, 0xe3, 0x36, 0xb1, 0x00, 0x0b, 0xe9, 0x17, 0x48, 0x72, 0xa1, 0x60, 0x15, 0xe9, 0x17,
    0x48, 0x72, 0xa1, 0x6f, 0xed, 0xaf, 0xe2, 0x57, 0x8f, 0xea, 0xe5, 0x3f, 0xe2, 0x00
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

static void magic_decode_send_cap_full(uint16_t offset, uint16_t capital_offset, char suffix) {
    if (magic_capitalize_next) {
        tap_code16(KC_BSPC);
        magic_decode_send_cap(capital_offset, suffix);
    } else {
        magic_decode_send_cap(offset, suffix);
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

static void magic_replace_tap_repeatable(uint16_t keycode) {
    tap_code16(KC_BSPC);
    magic_tap_repeatable(keycode);
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
                    case KC_B: magic_decode_send_cap_full(213, 143, 'd'); break;
                    case KC_C: magic_tap_repeatable(KC_N); break;
                    case KC_D: magic_tap_repeatable(KC_C); break;
                    case KC_F: magic_decode_send_cap_full(517, 287, 'd'); break;
                    case KC_G: magic_decode_send_cap_full(428, 292, 'l'); break;
                    case KC_K: magic_tap_repeatable(KC_R); break;
                    case KC_L: magic_tap_repeatable(KC_M); break;
                    case KC_M: magic_tap_repeatable(KC_R); break;
                    case KC_N: magic_tap_repeatable(KC_R); break;
                    case KC_P: magic_tap_repeatable(KC_Y); break;
                    case KC_R: magic_replace_tap_repeatable(KC_QUOTE); break;
                    case KC_S: magic_decode_send_cap_full(480, 571, 'e'); break;
                    case KC_SPC: magic_replace_decode_send_cap(8, '\0'); clear_suffix_state(); break;
                    case KC_T: magic_tap_repeatable(KC_N); break;
                    case KC_V: magic_replace_decode_send_cap(685, 'm'); break;
                    case KC_W: magic_decode_send_cap_full(376, 657, 'l'); break;
                    case KC_X: magic_replace_decode_send_cap(251, 'n'); break;
                    case KC_Z: magic_decode_send_cap_full(217, 678, 'r'); break;
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
                    case KC_B: magic_decode_send_cap_full(238, 148, 'n'); break;
                    case KC_C: magic_replace_decode_send_cap(5, '\0'); break;
                    case KC_D: magic_tap_repeatable(KC_H); break;
                    case KC_F: magic_decode_send_cap_full(399, 282, 't'); break;
                    case KC_G: magic_tap_repeatable(KC_F); break;
                    case KC_L: magic_tap_repeatable(KC_H); break;
                    case KC_M: magic_tap_repeatable(KC_H); break;
                    case KC_N: magic_tap_repeatable(KC_H); break;
                    case KC_P: magic_tap_repeatable(KC_M); break;
                    case KC_R: magic_replace_tap_repeatable(KC_DQUO); break;
                    case KC_S: magic_tap_repeatable(KC_R); break;
                    case KC_T: magic_tap_repeatable(KC_F); break;
                    case KC_V: magic_replace_decode_send_cap(303, 'm'); break;
                    case KC_W: magic_decode_send_cap_full(125, 637, 't'); break;
                    case KC_X: magic_tap_repeatable(KC_W); break;
                    case KC_Z: magic_replace_decode_send_cap(298, 'r'); break;
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
                    case KC_A: magic_tap_repeatable(KC_E); break;
                    case KC_E: magic_tap_repeatable(KC_H); break;
                    case KC_I: magic_replace_tap_repeatable(KC_QUOTE); break;
                    case KC_O: magic_tap_repeatable(KC_H); break;
                    case KC_U: magic_tap_repeatable(KC_H); break;
                    case KC_V: magic_replace_decode_send_cap(160, 'g'); break;
                    case KC_W: magic_decode_send_cap_full(513, 673, 'e'); break;
                    case KC_Y: magic_tap_repeatable(KC_R); break;
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
                    case KC_B: magic_decode_send_cap_full(202, 130, 'e'); break;
                    case KC_C: magic_tap_repeatable(KC_P); break;
                    case KC_D: magic_decode_send_cap_full(475, 182, 't'); break;
                    case KC_G: magic_tap_repeatable(KC_K); break;
                    case KC_K: magic_decode_send_cap_full(450, 412, 'w'); break;
                    case KC_L: magic_tap_repeatable(KC_R); break;
                    case KC_M: magic_decode_send_cap_full(230, 433, '\0'); break;
                    case KC_N: magic_replace_decode_send_cap(544, '\0'); break;
                    case KC_P: magic_tap_repeatable(KC_N); break;
                    case KC_R: magic_replace_tap_repeatable(KC_EXLM); break;
                    case KC_S: magic_decode_send_cap_full(396, 568, '\0'); break;
                    case KC_T: magic_decode_send_cap_full(396, 610, '\0'); break;
                    case KC_V: magic_replace_decode_send_cap(325, 'e'); break;
                    case KC_W: magic_tap_repeatable(KC_S); break;
                    case KC_X: magic_tap_repeatable(KC_R); break;
                    case KC_Z: magic_replace_decode_send_cap(25, 'a'); break;
                    default: magic_decode_send(544); break;
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
                    case KC_B: magic_tap_repeatable(KC_D); break;
                    case KC_C: magic_replace_decode_send_cap(2, '\0'); break;
                    case KC_D: magic_tap_repeatable(KC_F); break;
                    case KC_E: magic_tap_repeatable(KC_U); break;
                    case KC_F: magic_tap_repeatable(KC_D); break;
                    case KC_G: magic_tap_repeatable(KC_D); break;
                    case KC_H: magic_tap_repeatable(KC_Y); break;
                    case KC_K: magic_tap_repeatable(KC_X); break;
                    case KC_L: magic_tap_repeatable(KC_C); break;
                    case KC_M: magic_tap_repeatable(KC_L); break;
                    case KC_N: magic_tap_repeatable(KC_X); break;
                    case KC_P: magic_tap_repeatable(KC_D); break;
                    case KC_R: magic_replace_tap_repeatable(KC_QUES); break;
                    case KC_S: magic_tap_repeatable(KC_D); break;
                    case KC_T: magic_replace_decode_send_cap(661, 't'); break;
                    case KC_V: magic_replace_decode_send_cap(41, 'e'); break;
                    case KC_W: magic_tap_repeatable(KC_X); break;
                    case KC_X: magic_tap_repeatable(KC_D); break;
                    case KC_Z: magic_replace_decode_send_cap(31, 's'); break;
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
                    case KC_B: magic_decode_send_cap_full(632, 154, 's'); break;
                    case KC_D: magic_replace_decode_send_cap(626, 'e'); break;
                    case KC_G: magic_replace_decode_send_cap(85, 'n'); break;
                    case KC_L: magic_tap_repeatable(KC_B); break;
                    case KC_M: magic_tap_repeatable(KC_T); break;
                    case KC_N: magic_tap_repeatable(KC_P); break;
                    case KC_P: magic_replace_decode_send_cap(379, 'e'); break;
                    case KC_R: magic_replace_decode_send_cap(114, 'r'); break;
                    case KC_S: magic_replace_decode_send_cap(403, 't'); break;
                    case KC_T: magic_decode_send_cap_full(339, 584, 'u'); break;
                    case KC_V: magic_replace_decode_send_cap(347, 'e'); break;
                    case KC_W: magic_decode_send_cap_full(508, 667, 'y'); break;
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
                    case KC_B: magic_decode_send_cap_full(208, 137, 'e'); break;
                    case KC_C: magic_replace_decode_send_cap(15, '\0'); break;
                    case KC_D: magic_decode_send_cap_full(371, 173, 't'); break;
                    case KC_ENT: magic_decode_send_cap(106, 'd'); break;
                    case KC_G: magic_replace_decode_send_cap(502, 'e'); break;
                    case KC_K: magic_decode_send_cap_full(446, 407, 'w'); break;
                    case KC_L: magic_decode_send_cap_full(109, 417, 'e'); break;
                    case KC_M: magic_replace_decode_send_cap(386, 'n'); break;
                    case KC_N: magic_decode_send_cap_full(613, 454, 'r'); break;
                    case KC_O: magic_tap_repeatable(KC_E); break;
                    case KC_P: magic_decode_send_cap_full(561, 536, 'n'); break;
                    case KC_R: magic_decode_send_cap_full(193, 547, 'e'); break;
                    case KC_S: magic_decode_send_cap_full(486, 577, 'g'); break;
                    case KC_SPC: magic_decode_send_cap(106, 'd'); break;
                    case KC_T: magic_decode_send_cap_full(362, 595, 'h'); break;
                    case KC_TAB: magic_decode_send_cap(106, 'd'); break;
                    case KC_V: magic_replace_decode_send_cap(441, 'r'); break;
                    case KC_W: magic_decode_send_cap_full(354, 647, 'e'); break;
                    case KC_X: magic_replace_decode_send_cap(260, 'e'); break;
                    case KC_Z: magic_replace_decode_send_cap(46, 'y'); break;
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
                    case KC_B: magic_replace_decode_send_cap(223, 'e'); break;
                    case KC_C: magic_replace_decode_send_cap(12, '\0'); break;
                    case KC_D: magic_decode_send_cap_full(493, 188, 't'); break;
                    case KC_ENT: magic_decode_send_cap(592, 'e'); break;
                    case KC_G: magic_replace_decode_send_cap(119, 'g'); break;
                    case KC_L: magic_decode_send_cap_full(198, 423, 'e'); break;
                    case KC_M: magic_replace_decode_send_cap(89, 't'); break;
                    case KC_N: magic_replace_decode_send_cap(619, 'd'); break;
                    case KC_P: magic_decode_send_cap_full(233, 521, 'e'); break;
                    case KC_R: magic_replace_tap_repeatable(KC_COMMA); break;
                    case KC_S: magic_replace_decode_send_cap(100, 's'); break;
                    case KC_SPC: magic_decode_send_cap(592, 'e'); break;
                    case KC_T: magic_replace_decode_send_cap(243, 'g'); break;
                    case KC_TAB: magic_decode_send_cap(592, 'e'); break;
                    case KC_V: magic_replace_decode_send_cap(18, '\0'); break;
                    case KC_W: magic_decode_send_cap_full(358, 652, 'h'); break;
                    case KC_X: magic_replace_decode_send_cap(267, 'n'); break;
                    case KC_Z: magic_replace_decode_send_cap(66, 't'); break;
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
                    case KC_B: magic_replace_decode_send_cap(75, 't'); break;
                    case KC_C: magic_replace_decode_send_cap(437, '\0'); break;
                    case KC_D: magic_decode_send_cap_full(472, 178, 's'); break;
                    case KC_F: magic_replace_decode_send_cap(80, 'r'); break;
                    case KC_G: magic_replace_decode_send_cap(600, 't'); break;
                    case KC_L: magic_replace_decode_send_cap(94, 'y'); break;
                    case KC_N: magic_replace_decode_send_cap(497, 'y'); break;
                    case KC_P: magic_decode_send_cap_full(553, 527, 'y'); break;
                    case KC_R: magic_replace_tap_repeatable(KC_DOT); break;
                    case KC_SPC: magic_replace_decode_send_cap(22, '\0'); add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state(); break;
                    case KC_T: magic_decode_send_cap_full(366, 605, 'h'); break;
                    case KC_V: magic_replace_decode_send_cap(460, 'y'); break;
                    case KC_W: magic_decode_send_cap_full(351, 643, 'n'); break;
                    case KC_X: magic_replace_decode_send_cap(274, 't'); break;
                    case KC_Z: magic_replace_decode_send_cap(58, 's'); break;
                }
                magic_capitalize_next = false;
                last_magic_trigger = MAGIC_I;
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
            return false;
    }

    prev_keycode = last_keycode;
    last_keycode = keycode;
    last_magic_trigger = KC_NO;
    last_magic_repeat_keycode = KC_NO;
    return true;  // Other keys can be repeated.
}
