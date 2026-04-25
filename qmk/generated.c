/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;

static bool magic_capitalize_next = false;

// Magic string decoder lookup tables
static const char magic_char_4bit[] = {
    ' ', 'e', 'n', 'o', 'a', 't', 'r', 'i', 'h', 's', 'l', 'u', 'd', 'b'
};

static const char magic_char_extended[] = {
    'g', '\'', 'w', 'p', 'm', 'y', 'v', 'c', 'f', 'x', 'k', 'z', 'G', '"', '.', 'L', 'I', 'O', 'T', 'P', 'S', 'B', 'j', 'q'
};

static const uint8_t magic_string_data[] = {
    0x01, 0xed, 0x02, 0xe1, 0xc0, 0x03, 0xe1, 0xaa, 0x03, 0xe1, 0x61, 0x02, 0xe1, 0x90, 0x03, 0xe1,
    0xe6, 0x10, 0x02, 0xee, 0x00, 0x08, 0xec, 0x64, 0xe8, 0x42, 0x40, 0x0d, 0xec, 0x64, 0xe8, 0x42,
    0x40, 0xef, 0x4d, 0x90, 0x05, 0xf0, 0xe1, 0xe6, 0x10, 0x0e, 0xf1, 0xe3, 0x12, 0xf2, 0x1a, 0x1f,
    0xe4, 0x15, 0x6f, 0xe5, 0x00, 0x0b, 0xf3, 0x63, 0xe4, 0x15, 0x81, 0xb9, 0x00, 0x0c, 0xf4, 0xe3,
    0x67, 0x2f, 0xe0, 0x0f, 0xf5, 0x33, 0x50, 0x06, 0x4d, 0x3b, 0x50, 0x06, 0x4f, 0xe8, 0x51, 0x60,
    0x06, 0x4f, 0xe0, 0x47, 0x20, 0x07, 0x4a, 0xe4, 0x39, 0x50, 0x08, 0x4a, 0x61, 0x4c, 0xe5, 0x00,
    0x07, 0x4a, 0xe2, 0x4f, 0xe5, 0x90, 0x04, 0x42, 0xc0, 0x08, 0x42, 0xe0, 0xb4, 0xe0, 0x10, 0x08,
    0x42, 0x35, 0x81, 0x60, 0x09, 0x42, 0xe5, 0x58, 0x72, 0xe0, 0x00, 0x06, 0x49, 0x2f, 0xe1, 0x50,
    0x08, 0xd1, 0xe7, 0x4b, 0x91, 0x00, 0x07, 0xd1, 0xe8, 0x36, 0x10, 0x07, 0xd1, 0x87, 0x2c, 0x00,
    0x08, 0xd1, 0x5f, 0xe2, 0x11, 0x20, 0x09, 0xdb, 0x97, 0x21, 0x99, 0x00, 0x13, 0xc1, 0xe7, 0xa4,
    0x64, 0x57, 0xe6, 0x10, 0xe7, 0x32, 0xe8, 0x7f, 0xe0, 0x00, 0x07, 0xc7, 0xc2, 0xe1, 0x50, 0x05,
    0xc3, 0x19, 0x00, 0x08, 0xc3, 0x19, 0x2f, 0xe1, 0x50, 0x06, 0xc3, 0x2f, 0xe1, 0x50, 0x07, 0x14,
    0xa7, 0xeb, 0x10, 0x05, 0x14, 0xe6, 0x10, 0x07, 0x1f, 0xe7, 0x4b, 0x91, 0x00, 0x06, 0x1f, 0xe8,
    0x36, 0x10, 0x06, 0x18, 0x72, 0xc0, 0x0a, 0x1a, 0x4d, 0x36, 0x45, 0x10, 0x03, 0x12, 0x50, 0x06,
    0x13, 0xe3, 0xa1, 0x00, 0x07, 0x15, 0xe2, 0x11, 0x20, 0x0b, 0x1f, 0xe6, 0x16, 0xe5, 0x58, 0x72,
    0xe0, 0x00, 0x0a, 0x1f, 0xe9, 0xe7, 0x1f, 0xe3, 0x57, 0x32, 0x00, 0x08, 0x1f, 0xe9, 0xe7, 0xab,
    0xc1, 0x00, 0x08, 0x1f, 0xe9, 0xe3, 0xa4, 0x72, 0x00, 0x09, 0x1f, 0xe9, 0xe3, 0xa7, 0xe7, 0x75,
    0x00, 0x06, 0xe8, 0x76, 0x95, 0x00, 0x06, 0xe8, 0x3b, 0x2c, 0x00, 0x07, 0xe0, 0xa3, 0xd4, 0xa0,
    0x09, 0x84, 0x2f, 0xea, 0x0f, 0xe5, 0x3b, 0x00, 0x05, 0x84, 0xe6, 0x10, 0x04, 0x81, 0x20, 0x05,
    0x81, 0x61, 0x00, 0x05, 0x87, 0xe7, 0x80, 0x06, 0x83, 0xbf, 0xe0, 0x80, 0x07, 0x86, 0x3b, 0xe0,
    0x80, 0x06, 0x7c, 0x2f, 0xe1, 0x50, 0x04, 0x7a, 0xa0, 0x08, 0x7f, 0xe4, 0xe3, 0x63, 0xe6, 0x10,
    0x10, 0x72, 0x95, 0x6b, 0xe4, 0x12, 0x54, 0x57, 0x32, 0x00, 0x03, 0x73, 0x20, 0x05, 0x76, 0x95,
    0x00, 0x05, 0xf6, 0xb9, 0x50, 0x05, 0xea, 0x21, 0xe2, 0x00, 0x05, 0xea, 0x23, 0xe2, 0x00, 0x09,
    0xa4, 0x2f, 0xe0, 0xb4, 0xe0, 0x10, 0x06, 0xa1, 0x4f, 0xe6, 0x10, 0x06, 0xa3, 0xd4, 0xa0, 0x04,
    0xe4, 0x12, 0x50, 0x07, 0xe4, 0xe3, 0x63, 0xe6, 0x10, 0x03, 0x2f, 0xe1, 0x50, 0x06, 0x21, 0xe6,
    0x16, 0x00, 0x04, 0x21, 0xe2, 0x00, 0x04, 0x23, 0xe2, 0x00, 0x07, 0x2b, 0xe4, 0xd1, 0x60, 0x0e,
    0x3d, 0x91, 0x6f, 0xe6, 0x4d, 0x7a, 0x75, 0xe5, 0x00, 0x04, 0x31, 0x90, 0x07, 0x31, 0x92, 0xe1,
    0x50, 0x07, 0x3f, 0xe4, 0x13, 0x21, 0x00, 0x09, 0x3f, 0xe4, 0x15, 0x87, 0x2f, 0xe0, 0x00, 0x05,
    0x32, 0xe1, 0x50, 0x05, 0x32, 0xaf, 0xe5, 0x00, 0x09, 0x36, 0xe0, 0x42, 0x7f, 0xeb, 0x10, 0x05,
    0x36, 0x6f, 0xe5, 0x00, 0x05, 0x36, 0x91, 0x00, 0x05, 0x3b, 0x2c, 0x00, 0x07, 0xe3, 0x13, 0xe3,
    0xa1, 0x00, 0x09, 0xe3, 0x63, 0xd4, 0xda, 0xe5, 0x00, 0x0b, 0xe3, 0x63, 0xcb, 0xe7, 0x57, 0x32,
    0x00, 0x02, 0xf7, 0xb0, 0x08, 0x61, 0x4a, 0x7f, 0xeb, 0x10, 0x08, 0x63, 0xd4, 0xda, 0xe5, 0x00,
    0x0a, 0x63, 0xcb, 0xe7, 0x57, 0x32, 0x00, 0x04, 0x97, 0x32, 0x08, 0x93, 0xe4, 0x13, 0x21, 0x00,
    0x0a, 0x93, 0xe4, 0x15, 0x87, 0x2f, 0xe0, 0x00, 0x0a, 0x58, 0x42, 0xea, 0x0f, 0xe5, 0x3b, 0x00,
    0x04, 0x58, 0x10, 0x07, 0x58, 0x3b, 0xe0, 0x80, 0x08, 0x58, 0x3b, 0xe0, 0x85, 0x00, 0x08, 0x58,
    0x63, 0xbf, 0xe0, 0x80, 0x04, 0x57, 0x32, 0x06, 0xbf, 0xe4, 0xd1, 0x60, 0x0b, 0xb2, 0xc1, 0x69,
    0x54, 0x2c, 0x00, 0x07, 0xbf, 0xe3, 0xc4, 0x51, 0x00, 0x08, 0xb9, 0x72, 0x19, 0x90, 0x07, 0xe2,
    0x49, 0x2f, 0xe1, 0x50, 0x05, 0xe2, 0x81, 0x20, 0x06, 0xe2, 0x81, 0x61, 0x00, 0x06, 0xe2, 0x87,
    0xe7, 0x80, 0x05, 0xe2, 0x7a, 0xa0, 0x08, 0xe2, 0x75, 0x83, 0xb5, 0x00, 0x06, 0xe2, 0x36, 0x6f,
    0xe5, 0x00, 0x06, 0xe2, 0x36, 0x91, 0x00
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
    case SUB_7: return 200;
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

static void magic_replace_tap_repeatable(uint16_t keycode) {
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
        tap_code16(KC_BSPC);
        if (last_magic_char == 'e') {
            tap_code16(KC_D); tap_code16(KC_SPC);
        } else {
            tap_code16(KC_E); tap_code16(KC_D); tap_code16(KC_SPC);
        }
        last_magic_char = 'd';
        return true;
    case MAGIC_H:
        tap_code16(KC_BSPC); tap_code16(KC_S); tap_code16(KC_SPC);
        last_magic_char = 's';
        return true;
    case MAGIC_I:
        tap_code16(KC_BSPC); tap_comma_space();
        suffix_active = false;
        return true;
    case MAGIC_J:
        tap_code16(KC_BSPC); tap_dot_space();
        add_oneshot_mods(MOD_BIT(KC_LSFT));
        suffix_active = false;
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
                    case KC_B: magic_decode_send_suffix(210, 'd'); break;
                    case KC_C: magic_tap_repeatable(KC_N); break;
                    case KC_D: magic_tap_repeatable(KC_C); break;
                    case KC_F: magic_decode_send_suffix(472, 'd'); break;
                    case KC_G: magic_decode_send_suffix(379, 'l'); break;
                    case KC_K: magic_tap_repeatable(KC_R); break;
                    case KC_L: magic_tap_repeatable(KC_M); break;
                    case KC_M: magic_tap_repeatable(KC_R); break;
                    case KC_N: magic_tap_repeatable(KC_R); break;
                    case KC_P: magic_tap_repeatable(KC_Y); break;
                    case KC_S: magic_decode_send_suffix(433, 'e'); break;
                    case KC_SPC: magic_tap_repeatable(KC_QUOTE); break;
                    case KC_T: magic_tap_repeatable(KC_N); break;
                    case KC_W: magic_decode_send_suffix(326, 'l'); break;
                    case KC_X: magic_replace_decode_send_cap(242, 'n'); break;
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
                    case KC_B: magic_decode_send_suffix(228, 'n'); break;
                    case KC_C: magic_replace_decode_send_cap(5, '\0'); break;
                    case KC_D: magic_tap_repeatable(KC_H); break;
                    case KC_F: magic_decode_send_suffix(349, 't'); break;
                    case KC_G: magic_tap_repeatable(KC_F); break;
                    case KC_L: magic_tap_repeatable(KC_H); break;
                    case KC_M: magic_tap_repeatable(KC_H); break;
                    case KC_N: magic_tap_repeatable(KC_H); break;
                    case KC_P: magic_tap_repeatable(KC_M); break;
                    case KC_S: magic_tap_repeatable(KC_R); break;
                    case KC_SPC: magic_tap_repeatable(KC_DQUO); break;
                    case KC_T: magic_tap_repeatable(KC_F); break;
                    case KC_W: magic_decode_send_suffix(123, 't'); break;
                    case KC_X: magic_tap_repeatable(KC_W); break;
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
                    case KC_SPC: magic_replace_decode_send_cap(18, '\0'); add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state(); break;
                    case KC_V: magic_replace_decode_send_cap(156, 'g'); break;
                    case KC_W: magic_decode_send_suffix(468, 'e'); break;
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
                    case KC_B: magic_decode_send_suffix(199, 'e'); break;
                    case KC_C: magic_replace_decode_send_cap(393, '\0'); break;
                    case KC_D: magic_decode_send_suffix(428, 't'); break;
                    case KC_G: magic_tap_repeatable(KC_K); break;
                    case KC_K: magic_decode_send_suffix(406, 'w'); break;
                    case KC_L: magic_tap_repeatable(KC_R); break;
                    case KC_M: magic_decode_send(220); break;
                    case KC_N: magic_replace_decode_send_cap(497, '\0'); break;
                    case KC_P: magic_tap_repeatable(KC_N); break;
                    case KC_S: magic_decode_send(346); break;
                    case KC_SPC: magic_tap_repeatable(KC_EXLM); break;
                    case KC_T: magic_decode_send(346); break;
                    case KC_W: magic_tap_repeatable(KC_S); break;
                    case KC_X: magic_tap_repeatable(KC_R); break;
                    case KC_Z: magic_replace_decode_send_cap(21, 'a'); break;
                    default: magic_decode_send(497); break;
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
                    case KC_SPC: magic_tap_repeatable(KC_QUES); break;
                    case KC_T: magic_replace_decode_send_cap(614, 't'); break;
                    case KC_V: magic_replace_decode_send_cap(36, 'e'); break;
                    case KC_W: magic_tap_repeatable(KC_X); break;
                    case KC_X: magic_tap_repeatable(KC_D); break;
                    case KC_Z: magic_replace_decode_send_cap(27, 's'); break;
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
                    case KC_B: magic_decode_send_suffix(585, 's'); break;
                    case KC_ENT: magic_decode_send_cap(102, 'd'); break;
                    case KC_G: magic_replace_decode_send_cap(80, 'n'); break;
                    case KC_L: magic_tap_repeatable(KC_B); break;
                    case KC_M: magic_tap_repeatable(KC_T); break;
                    case KC_N: magic_tap_repeatable(KC_P); break;
                    case KC_R: magic_replace_decode_send_cap(111, 'r'); break;
                    case KC_S: magic_replace_decode_send_cap(353, 't'); break;
                    case KC_SPC: magic_decode_send_cap(102, 'd'); break;
                    case KC_T: magic_decode_send_suffix(288, 'u'); break;
                    case KC_TAB: magic_decode_send_cap(102, 'd'); break;
                    case KC_V: magic_replace_decode_send_cap(296, 'e'); break;
                    case KC_W: magic_decode_send_suffix(463, 'y'); break;
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
                    case KC_E: magic_tap_repeatable(KC_H); break;
                    case KC_I: magic_decode_send_suffix(387, 'e'); break;
                    case KC_O: magic_tap_repeatable(KC_H); break;
                    case KC_SPC: magic_tap_repeatable(KC_Z); break;
                    case KC_U: magic_tap_repeatable(KC_H); break;
                    case KC_Y: magic_tap_repeatable(KC_R); break;
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
                    case KC_B: magic_decode_send_suffix(205, 'e'); break;
                    case KC_C: magic_replace_decode_send_cap(11, '\0'); break;
                    case KC_D: magic_decode_send_suffix(321, 't'); break;
                    case KC_G: magic_replace_decode_send_cap(456, 'e'); break;
                    case KC_K: magic_replace_decode_send_cap(579, 'e'); break;
                    case KC_L: magic_decode_send_suffix(105, 'e'); break;
                    case KC_M: magic_replace_decode_send_cap(336, 'n'); break;
                    case KC_N: magic_decode_send_suffix(567, 'r'); break;
                    case KC_P: magic_decode_send_suffix(512, 'n'); break;
                    case KC_R: magic_decode_send_suffix(190, 'e'); break;
                    case KC_S: magic_decode_send_suffix(439, 'g'); break;
                    case KC_SPC: magic_tap_repeatable(KC_COMMA); break;
                    case KC_T: magic_decode_send_suffix(311, 'h'); break;
                    case KC_V: magic_replace_decode_send_cap(397, 'r'); break;
                    case KC_W: magic_decode_send_suffix(303, 'e'); break;
                    case KC_X: magic_replace_decode_send_cap(251, 'e'); break;
                    case KC_Z: magic_replace_decode_send_cap(41, 'y'); break;
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
                    case KC_B: magic_replace_decode_send_cap(214, 'e'); break;
                    case KC_C: magic_replace_decode_send_cap(8, '\0'); break;
                    case KC_D: magic_decode_send_suffix(447, 't'); break;
                    case KC_ENT: magic_decode_send_cap(544, 'e'); break;
                    case KC_G: magic_replace_decode_send_cap(116, 'g'); break;
                    case KC_K: magic_decode_send_suffix(402, 'w'); break;
                    case KC_L: magic_decode_send_suffix(195, 'e'); break;
                    case KC_M: magic_replace_decode_send_cap(85, 't'); break;
                    case KC_N: magic_replace_decode_send_cap(572, 'd'); break;
                    case KC_P: magic_decode_send_suffix(223, 'e'); break;
                    case KC_S: magic_replace_decode_send_cap(96, 's'); break;
                    case KC_SPC: magic_decode_send_cap(544, 'e'); break;
                    case KC_T: magic_replace_decode_send_cap(233, 'g'); break;
                    case KC_TAB: magic_decode_send_cap(544, 'e'); break;
                    case KC_V: magic_replace_decode_send_cap(14, '\0'); break;
                    case KC_W: magic_decode_send_suffix(307, 'h'); break;
                    case KC_X: magic_replace_decode_send_cap(258, 'n'); break;
                    case KC_Z: magic_replace_decode_send_cap(61, 't'); break;
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
                    case KC_B: magic_replace_decode_send_cap(71, 't'); break;
                    case KC_C: magic_tap_repeatable(KC_D); break;
                    case KC_D: magic_decode_send_suffix(425, 's'); break;
                    case KC_F: magic_replace_decode_send_cap(75, 'r'); break;
                    case KC_G: magic_replace_decode_send_cap(552, 't'); break;
                    case KC_L: magic_replace_decode_send_cap(90, 'y'); break;
                    case KC_N: magic_replace_decode_send_cap(451, 'y'); break;
                    case KC_P: magic_decode_send_suffix(506, 'y'); break;
                    case KC_SPC: magic_tap_repeatable(KC_DOT); break;
                    case KC_T: magic_decode_send_suffix(316, 'h'); break;
                    case KC_V: magic_replace_decode_send_cap(415, 'y'); break;
                    case KC_W: magic_decode_send_suffix(300, 'n'); break;
                    case KC_X: magic_replace_decode_send_cap(265, 't'); break;
                    case KC_Z: magic_replace_decode_send_cap(53, 's'); break;
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
                    case KC_SPC: magic_tap_repeatable(KC_J); break;
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
