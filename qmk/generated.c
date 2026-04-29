/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;

static bool magic_capitalize_next = false;

// Magic string decoder lookup tables
static const char magic_char_4bit[] = {
    ' ', 'e', 'o', 'n', 't', 'i', 'a', 'r', 'l', 's', 'u', 'g', 'h', 'c'
};

static const char magic_char_extended[] = {
    'p', 'm', 'd', 'b', 'y', 'w', '\'', 'f', 'v', 'k', 'x', 'q', 'z', '#', '.', 'G', 'I', 'O', 'T', 'P', 'S', 'B', 'Z', 'j'
};

static const uint8_t magic_string_data[] = {
    0x04, 0xed, 0xbf, 0xec, 0x00, 0x02, 0xe6, 0xe2, 0x03, 0xe6, 0x88, 0x03, 0xe6, 0x71, 0x02, 0xe6,
    0x90, 0x03, 0xe6, 0xe8, 0x10, 0x02, 0xee, 0x00, 0x07, 0xef, 0x71, 0xb2, 0x70, 0x05, 0xf0, 0xe6,
    0xe8, 0x10, 0x0e, 0xf1, 0xe0, 0x13, 0xf2, 0x18, 0x1f, 0xe1, 0x14, 0x7f, 0xe4, 0x00, 0x0b, 0xf3,
    0x72, 0xe1, 0x14, 0xc1, 0xa9, 0x00, 0x0c, 0xf4, 0xe0, 0x75, 0x3b, 0x0f, 0xf5, 0x22, 0x40, 0x0b,
    0xf6, 0x15, 0x48, 0x53, 0xb1, 0x70, 0x0a, 0x6d, 0xe9, 0xb7, 0x2a, 0x3f, 0xe2, 0x00, 0x0a, 0x68,
    0x5f, 0xe2, 0x64, 0x52, 0x30, 0x08, 0x68, 0x71, 0x6f, 0xe2, 0xe4, 0x00, 0x07, 0x68, 0xe5, 0x6f,
    0xe4, 0x90, 0x04, 0x63, 0xe2, 0x00, 0x08, 0x63, 0xba, 0x6b, 0x10, 0x08, 0x63, 0x24, 0xc1, 0x70,
    0x09, 0x63, 0xe4, 0x4c, 0x53, 0xb0, 0x09, 0x6f, 0xe0, 0xe0, 0x72, 0xe8, 0x68, 0x00, 0x09, 0x69,
    0x5d, 0x68, 0x8f, 0xe4, 0x00, 0x06, 0x69, 0x3f, 0xe6, 0x40, 0x0a, 0x6f, 0xe8, 0x65, 0x86, 0xe3,
    0x81, 0x00, 0x0b, 0xe3, 0x6d, 0xe9, 0xb7, 0x2a, 0x3f, 0xe2, 0x00, 0x0a, 0xe3, 0x69, 0x5d, 0x68,
    0x8f, 0xe4, 0x00, 0x08, 0xe3, 0x1d, 0x6a, 0x91, 0x00, 0x07, 0xe3, 0x1d, 0x2f, 0xe1, 0x10, 0x07,
    0xe3, 0x1f, 0xe7, 0x27, 0x10, 0x08, 0xd2, 0xe1, 0xe1, 0x13, 0x40, 0x09, 0xd2, 0x3f, 0xe7, 0x85,
    0xd4, 0x00, 0x0a, 0xd2, 0x3f, 0xe7, 0xa9, 0x53, 0xb0, 0x0a, 0xd2, 0x34, 0x65, 0x31, 0x70, 0x12,
    0xe2, 0x1d, 0x86, 0x76, 0x45, 0xe8, 0x10, 0xd2, 0x3f, 0xe7, 0x5b, 0x07, 0xe2, 0x5f, 0xe2, 0x3f,
    0xe6, 0x40, 0x0b, 0xe2, 0x5f, 0xe7, 0xe7, 0x5d, 0xa8, 0x4f, 0xe4, 0x00, 0x08, 0xe2, 0x59, 0x6f,
    0xe3, 0x81, 0x00, 0x05, 0xe2, 0x21, 0x90, 0x08, 0xe2, 0x21, 0x93, 0xe6, 0x40, 0x06, 0xe2, 0x23,
    0xe6, 0x40, 0x07, 0x1d, 0x6a, 0x91, 0x00, 0x06, 0x1d, 0x2f, 0xe1, 0x10, 0x06, 0x1f, 0xe7, 0x27,
    0x10, 0x0a, 0x18, 0x6f, 0xe3, 0x27, 0x64, 0x10, 0x07, 0x13, 0x17, 0x68, 0x00, 0x08, 0x13, 0x17,
    0x64, 0x10, 0x04, 0x13, 0x40, 0x06, 0x12, 0xe0, 0x81, 0x00, 0x08, 0x1f, 0xe0, 0x67, 0x64, 0x10,
    0x07, 0x17, 0x95, 0x23, 0x00, 0x05, 0x1f, 0xe8, 0x17, 0x00, 0x0b, 0x1f, 0xe8, 0x17, 0xe4, 0x4c,
    0x53, 0xb0, 0x08, 0x1f, 0xea, 0x6f, 0xe1, 0xe0, 0x81, 0x00, 0x07, 0x1f, 0xea, 0xd1, 0xe0, 0x40,
    0x0a, 0x1f, 0xea, 0xd1, 0xe0, 0x45, 0x23, 0x00, 0x08, 0x1f, 0xea, 0xd8, 0xaf, 0xe2, 0x10, 0x08,
    0x1f, 0xea, 0xe0, 0x86, 0x53, 0x00, 0x09, 0x1f, 0xea, 0xe0, 0x85, 0xd5, 0x40, 0x08, 0xe7, 0x2d,
    0xa9, 0x1f, 0xe2, 0x00, 0x0a, 0xe7, 0x28, 0x82, 0xe5, 0x53, 0xb0, 0x0a, 0xe7, 0x71, 0xeb, 0xa1,
    0x3d, 0xe4, 0x00, 0x08, 0xb1, 0x31, 0x76, 0x80, 0x09, 0xb1, 0x31, 0x76, 0x41, 0x00, 0x07, 0xb5,
    0x4c, 0xaf, 0xe3, 0x00, 0x07, 0xb8, 0x2f, 0xe3, 0x68, 0x00, 0x06, 0xb7, 0x1b, 0x27, 0x05, 0xc5,
    0xdc, 0x00, 0x06, 0xc2, 0xab, 0xc0, 0x07, 0xc2, 0xab, 0xc4, 0x00, 0x07, 0xc7, 0x2a, 0xbc, 0x00,
    0x06, 0x5f, 0xe2, 0x3f, 0xe6, 0x40, 0x0a, 0x5f, 0xe7, 0xe7, 0x5d, 0xa8, 0x4f, 0xe4, 0x00, 0x09,
    0x5b, 0x76, 0x45, 0x23, 0x00, 0x07, 0x5f, 0xe1, 0x58, 0x67, 0x00, 0x0a, 0x5f, 0xe1, 0xe0, 0x81,
    0xe1, 0x13, 0x40, 0x0f, 0x5f, 0xe1, 0xe0, 0x81, 0xe1, 0x13, 0x46, 0x45, 0x23, 0x00, 0x08, 0x5f,
    0xe1, 0xe0, 0x72, 0xe8, 0x10, 0x10, 0x53, 0x94, 0x7a, 0xe1, 0x13, 0x46, 0x45, 0x23, 0x00, 0x03,
    0x52, 0x30, 0x08, 0x59, 0xe1, 0x64, 0xdc, 0x00, 0x06, 0x54, 0xca, 0xe3, 0x00, 0x05, 0xf7, 0xa9,
    0x40, 0x05, 0xe9, 0x31, 0xe5, 0x00, 0x05, 0xe9, 0x32, 0xe5, 0x00, 0x09, 0x86, 0x3b, 0xa6, 0xb1,
    0x00, 0x06, 0x82, 0xe3, 0x68, 0x00, 0x05, 0xe1, 0x13, 0x40, 0x07, 0xe1, 0x17, 0xb1, 0xe2, 0x00,
    0x0a, 0xe1, 0x5b, 0x76, 0x45, 0x23, 0x00, 0x09, 0xe1, 0x59, 0xe1, 0x64, 0xdc, 0x00, 0x03, 0xe1,
    0xe0, 0x80, 0x09, 0xe1, 0xe0, 0x81, 0xe1, 0x13, 0x40, 0x09, 0xe1, 0xa8, 0x45, 0xe0, 0x81, 0x00,
    0x03, 0x3f, 0xe6, 0x40, 0x06, 0x31, 0xe8, 0x17, 0x00, 0x04, 0x31, 0xe5, 0x00, 0x04, 0x32, 0xe5,
    0x00, 0x0e, 0x2f, 0xe3, 0x91, 0x7f, 0xe8, 0x6f, 0xe3, 0x58, 0x54, 0xe4, 0x00, 0x09, 0x2f, 0xe3,
    0x92, 0x81, 0x41, 0x00, 0x07, 0x2d, 0xa9, 0x1f, 0xe2, 0x00, 0x04, 0x21, 0x90, 0x07, 0x21, 0x93,
    0xe6, 0x40, 0x09, 0x28, 0x82, 0xe5, 0x53, 0xb0, 0x07, 0x2f, 0xe1, 0x12, 0x31, 0x00, 0x09, 0x2f,
    0xe1, 0x14, 0xc5, 0x3b, 0x00, 0x07, 0x2f, 0xe1, 0xe1, 0x13, 0x40, 0x05, 0x23, 0xe6, 0x40, 0x05,
    0x23, 0x8f, 0xe4, 0x00, 0x09, 0x23, 0x46, 0x53, 0x17, 0x00, 0x09, 0x27, 0xb6, 0x35, 0xec, 0x10,
    0x08, 0x27, 0xe9, 0xe7, 0x82, 0xe5, 0x00, 0x05, 0x27, 0x91, 0x00, 0x0a, 0x24, 0xc1, 0x7f, 0xe5,
    0x59, 0x10, 0x07, 0xe0, 0x12, 0xe0, 0x81, 0x00, 0x0c, 0xe0, 0x17, 0xe7, 0x27, 0xe1, 0x63, 0xd1,
    0x00, 0x09, 0xe0, 0x29, 0x95, 0xe3, 0x81, 0x00, 0x09, 0xe0, 0x72, 0xe3, 0x6f, 0xe3, 0x8f, 0xe4,
    0x00, 0x0b, 0xe0, 0x72, 0xe2, 0xad, 0x45, 0x23, 0x00, 0x07, 0xe0, 0xe4, 0x4c, 0x23, 0x00, 0x02,
    0xeb, 0xa0, 0x09, 0xeb, 0xa1, 0x94, 0x52, 0x30, 0x08, 0x71, 0x68, 0x5f, 0xec, 0x10, 0x09, 0x71,
    0xeb, 0xa1, 0x3d, 0xe4, 0x00, 0x08, 0x71, 0x92, 0x8f, 0xe8, 0x10, 0x08, 0x72, 0xe3, 0x6f, 0xe3,
    0x8f, 0xe4, 0x00, 0x0a, 0x72, 0xe2, 0xad, 0x45, 0x23, 0x00, 0x09, 0x91, 0xe0, 0x67, 0x64, 0x10,
    0x08, 0x95, 0xe1, 0x58, 0x67, 0x00, 0x04, 0x95, 0x23, 0x08, 0x92, 0xe1, 0x12, 0x31, 0x00, 0x0a,
    0x92, 0xe1, 0x14, 0xc5, 0x3b, 0x00, 0x08, 0x9a, 0xbb, 0x19, 0x40, 0x08, 0x9a, 0xe0, 0xe0, 0x27,
    0x40, 0x07, 0x9f, 0xe5, 0x54, 0xdc, 0x00, 0x04, 0x4c, 0x10, 0x06, 0x4c, 0x53, 0xe9, 0x00, 0x07,
    0x4c, 0x2a, 0xbc, 0x00, 0x08, 0x4c, 0x2a, 0xbc, 0x40, 0x08, 0x4c, 0x72, 0xab, 0xc0, 0x04, 0x45,
    0x23, 0x08, 0xa8, 0x45, 0xe0, 0x81, 0x00, 0x0b, 0xa3, 0xe2, 0x17, 0x94, 0x63, 0xe2, 0x00, 0x07,
    0xaf, 0xe0, 0xe2, 0x64, 0x10, 0x07, 0xaf, 0xe0, 0xe0, 0x27, 0x40, 0x04, 0xa9, 0x40, 0x0b, 0xe8,
    0x68, 0x5f, 0xe2, 0x64, 0x52, 0x30, 0x08, 0xe8, 0x17, 0x95, 0x23, 0x00, 0x07, 0xe5, 0x69, 0x3f,
    0xe6, 0x40, 0x06, 0xe5, 0xc5, 0xdc, 0x00, 0x08, 0xe5, 0x54, 0xc2, 0xa4, 0x00, 0x09, 0xe5, 0x27,
    0xe9, 0xe7, 0x82, 0xe5, 0x00, 0x06, 0xe5, 0x27, 0x91, 0x00, 0x07, 0xea, 0xe0, 0x86, 0x53, 0x00,
    0x06, 0xe4, 0x4c, 0x23, 0x00
};

static void magic_decode_send_skip(uint16_t offset, uint8_t skip_chars) {
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
                    if (skip_chars > 0) {
                        skip_chars--;
                    } else {
                        send_char(c);
                    }
                    charCount++;
                }
            } else {
                highNibble = false;
                if (code < sizeof(magic_char_4bit)) {
                    c = magic_char_4bit[code];
                    if (skip_chars > 0) {
                        skip_chars--;
                    } else {
                        send_char(c);
                    }
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
                if (skip_chars > 0) {
                    skip_chars--;
                } else {
                    send_char(c);
                }
                charCount++;
            }
        }
    }
}

static void magic_decode_send(uint16_t offset) {
    magic_decode_send_skip(offset, 0);
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

typedef struct {
    uint16_t current_offset;
    uint16_t next_offset;
    uint8_t common_prefix_length;
    char next_last_char;
} magic_cycle_entry_t;

static const magic_cycle_entry_t magic_cycle_entries[] = {
    { 24, 63, 0, 'r' },
    { 63, 24, 0, 'r' },
    { 459, 467, 9, 'n' },
    { 467, 459, 9, 't' }
};

static bool magic_cycle_lookup(uint16_t current_offset, uint16_t* next_offset, char* next_last_char) {
    int low = 0;
    int high = (int)(sizeof(magic_cycle_entries) / sizeof(magic_cycle_entries[0])) - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        uint16_t mid_offset = magic_cycle_entries[mid].current_offset;
        if (mid_offset == current_offset) {
            *next_offset = magic_cycle_entries[mid].next_offset;
            suffix_cycle_common_prefix_length = magic_cycle_entries[mid].common_prefix_length;
            *next_last_char = magic_cycle_entries[mid].next_last_char;
            return true;
        }
        if (mid_offset < current_offset) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}

static inline void set_suffix_word_state(char c, uint16_t cycle_offset, bool capitalize) {
    suffix_active = true;
    last_magic_char = c;
    suffix_cycle_offset = cycle_offset;
    suffix_cycle_capitalize = capitalize;
}

static void magic_decode_send_cap_cycle(uint16_t offset, char suffix, uint16_t cycle_offset) {
    bool capitalize = magic_capitalize_next;
    if (capitalize) {
        add_oneshot_mods(MOD_BIT(KC_LSFT));
    }
    magic_decode_send(offset);
    if (suffix != '\0') {
        set_suffix_word_state(suffix, cycle_offset, capitalize);
    }
    magic_capitalize_next = false;
}

static void magic_decode_send_suffix_cycle(uint16_t offset, char suffix, uint16_t cycle_offset) {
    bool capitalize = magic_capitalize_next;
    magic_decode_send(offset);
    set_suffix_word_state(suffix, cycle_offset, capitalize);
    magic_capitalize_next = false;
}

static void magic_replace_decode_send_cap_cycle(uint16_t offset, char suffix, uint16_t cycle_offset) {
    tap_code16(KC_BSPC);
    magic_decode_send_cap_cycle(offset, suffix, cycle_offset);
}

static bool process_magic_cycle_next(void) {
    uint16_t next_offset = 0;
    char next_last_char = '\0';
    if (suffix_cycle_offset == UINT16_MAX || !magic_cycle_lookup(suffix_cycle_offset, &next_offset, &next_last_char)) {
        clear_suffix_state();
        return false;
    }
    tap_code16(KC_BSPC);
    uint8_t current_length = magic_string_data[suffix_cycle_offset];
    uint8_t delete_count = current_length - 1 - suffix_cycle_common_prefix_length;
    for (uint8_t i = 0; i < delete_count; i++) {
        tap_code16(KC_BSPC);
    }
    if (suffix_cycle_capitalize && suffix_cycle_common_prefix_length == 0) {
        add_oneshot_mods(MOD_BIT(KC_LSFT));
    }
    magic_decode_send_skip(next_offset, suffix_cycle_common_prefix_length);
    set_suffix_word_state(next_last_char, next_offset, suffix_cycle_capitalize);
    return true;
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
    case C_FNSYM_KC_BACKSLASH: return 200;
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
    case C_LEFT_KC_AT: return 200;
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
    case C_RIGHT_KC_COMMA: return 200;
    case C_RIGHT_KC_DOT: return 200;
    case C_RIGHT_KC_GRAVE: return 200;
    case C_RIGHT_KC_J: return 200;
    case C_RIGHT_KC_Q: return 200;
    case C_RIGHT_KC_QUES: return 200;
    case C_RIGHT_KC_QUOTE: return 200;
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

// Two-variable tracking for real logical keys.
// prev_keycode = the prior resolved key press (what adaptives and magics check against).
// last_keycode = the most recent resolved key press (shifts to prev_keycode on the next keypress).
// Updated from the real trigger keycode, not the emitted adaptive/magic output,
// so context-sensitive logic can see through substitutions.
// Combo components like KC_C from P=KC_C+KC_X are never recorded — only KC_P is.
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

static void remember_real_keycode(uint16_t keycode) {
    prev_keycode = last_keycode;
    last_keycode = keycode;
    last_magic_trigger = KC_NO;
    last_magic_repeat_keycode = KC_NO;
}

bool tap(uint16_t keycode) {
    tap_code16(keycode);
    set_last_keycode(keycode);
    return false;
}

bool tap_adaptive(uint16_t pressed_keycode, uint16_t output_keycode) {
    remember_real_keycode(pressed_keycode);
    tap_code16(output_keycode);
    set_last_keycode(output_keycode);
    return false;
}

static inline void magic_replace_decode_send_cap(uint16_t offset, char suffix) {
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
    case MAGIC_A:
        tap_code16(KC_BSPC);
        if (last_magic_char == 'e') {
            tap_code16(KC_D); tap_code16(KC_SPC);
        } else {
            tap_code16(KC_E); tap_code16(KC_D); tap_code16(KC_SPC);
        }
        last_magic_char = 'd';
        clear_suffix_cycle_state();
        return true;
    case MAGIC_B:
        tap_code16(KC_BSPC); tap_code16(KC_L); tap_code16(KC_Y); tap_code16(KC_SPC);
        last_magic_char = 'y';
        clear_suffix_cycle_state();
        return true;
    case MAGIC_D:
        tap_code16(KC_BSPC); tap_n_t(); tap_code16(KC_SPC);
        last_magic_char = 't';
        clear_suffix_cycle_state();
        return true;
    case MAGIC_E:
        tap_code16(KC_BSPC); tap_code16(KC_QUES); tap_code16(KC_SPC);
        last_magic_char = '?';
        clear_suffix_cycle_state();
        return true;
    case MAGIC_G:
        tap_code16(KC_BSPC); tap_code16(KC_COMMA); tap_code16(KC_SPC);
        clear_suffix_state();
        return true;
    case MAGIC_H:
        return process_magic_cycle_next();
    case MAGIC_I:
        tap_code16(KC_BSPC); tap_code16(KC_SPC); tap_code16(KC_T); tap_code16(KC_H); tap_code16(KC_E); tap_code16(KC_SPC);
        clear_suffix_state();
        return true;
    case MAGIC_J:
        tap_code16(KC_BSPC); tap_code16(KC_DOT); tap_code16(KC_SPC);
        clear_suffix_state();
        return true;
    case MAGIC_K:
        tap_code16(KC_BSPC); tap_code16(KC_S); tap_code16(KC_SPC);
        last_magic_char = 's';
        clear_suffix_cycle_state();
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
                    case KC_A: return tap_adaptive(KC_E, KC_U);
                }
                break;
            case KC_D:
                switch (adaptive_prev_keycode) {
                    case KC_B: return tap_adaptive(KC_D, KC_S);
                    case KC_C: return tap_adaptive(KC_D, KC_C);
                    case KC_F: return tap_adaptive(KC_D, KC_F);
                    case KC_G: return tap_adaptive(KC_D, KC_N);
                    case KC_P: return tap_adaptive(KC_D, KC_L);
                    case KC_S: return tap_adaptive(KC_D, KC_P);
                    case KC_X: return tap_adaptive(KC_D, KC_C);
                }
                break;
            case KC_N:
                switch (adaptive_prev_keycode) {
                    case KC_C: return tap_adaptive(KC_N, KC_K);
                    case KC_P: return tap_adaptive(KC_N, KC_P);
                    case KC_T: return tap_adaptive(KC_N, KC_T);
                }
                break;
            case KC_C:
                switch (adaptive_prev_keycode) {
                    case KC_D: return tap_adaptive(KC_C, KC_V);
                    case KC_L: return tap_adaptive(KC_C, KC_V);
                }
                break;
            case KC_F:
                switch (adaptive_prev_keycode) {
                    case KC_D: return tap_adaptive(KC_F, KC_D);
                    case KC_G: return tap_adaptive(KC_F, KC_L);
                    case KC_T: return tap_adaptive(KC_F, KC_W);
                }
                break;
            case KC_H:
                switch (adaptive_prev_keycode) {
                    case KC_D: return tap_adaptive(KC_H, KC_G);
                    case KC_E: return tap_adaptive(KC_H, KC_E);
                    case KC_L: return tap_adaptive(KC_H, KC_P);
                    case KC_M: return tap_adaptive(KC_H, KC_M);
                    case KC_N: return tap_adaptive(KC_H, KC_N);
                    case KC_O: return tap_adaptive(KC_H, KC_O);
                    case KC_U: return tap_adaptive(KC_H, KC_A);
                }
                break;
            case KC_U:
                switch (adaptive_prev_keycode) {
                    case KC_E: return tap_adaptive(KC_U, KC_O);
                }
                break;
            case KC_R:
                switch (adaptive_prev_keycode) {
                    case KC_K: return tap_adaptive(KC_R, KC_N);
                    case KC_L: return tap_adaptive(KC_R, KC_L);
                    case KC_M: return tap_adaptive(KC_R, KC_P);
                    case KC_N: return tap_adaptive(KC_R, KC_G);
                    case KC_S: return tap_adaptive(KC_R, KC_S);
                    case KC_Y: return tap_adaptive(KC_R, KC_I);
                }
                break;
            case KC_B:
                switch (adaptive_prev_keycode) {
                    case KC_L: return tap_adaptive(KC_B, KC_K);
                }
                break;
            case KC_T:
                switch (adaptive_prev_keycode) {
                    case KC_M: return tap_adaptive(KC_T, KC_B);
                }
                break;
            case KC_P:
                switch (adaptive_prev_keycode) {
                    case KC_N: return tap_adaptive(KC_P, KC_K);
                }
                break;
            case KC_X:
                switch (adaptive_prev_keycode) {
                    case KC_N: return tap_adaptive(KC_X, KC_L);
                    case KC_R: return tap_adaptive(KC_X, KC_R);
                    case KC_W: return tap_adaptive(KC_X, KC_N);
                }
                break;
            case KC_Y:
                switch (adaptive_prev_keycode) {
                    case KC_P: return tap_adaptive(KC_Y, KC_S);
                }
                break;
            case KC_W:
                switch (adaptive_prev_keycode) {
                    case KC_X: return tap_adaptive(KC_W, KC_P);
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
                switch (magic_prepare_last_keycode(last_keycode)) {
                    case KC_B: magic_decode_send_suffix_cycle(70, 'd', UINT16_MAX); /* emits "ackground " -> "background " */ break;
                    case KC_C: magic_tap_repeatable(KC_N); break;
                    case KC_D: magic_tap_repeatable(KC_C); break;
                    case KC_F: magic_replace_decode_send_cap_cycle(194, 'g', UINT16_MAX); /* emits "confusing " */ break;
                    case KC_G: magic_decode_send_suffix_cycle(529, 'l', UINT16_MAX); /* emits "lobal " -> "global " */ break;
                    case KC_K: magic_tap_repeatable(KC_R); break;
                    case KC_L: magic_tap_repeatable(KC_M); break;
                    case KC_M: magic_tap_repeatable(KC_R); break;
                    case KC_N: magic_tap_repeatable(KC_R); break;
                    case KC_P: magic_tap_repeatable(KC_Y); break;
                    case KC_S: magic_decode_send_suffix_cycle(632, 'e', UINT16_MAX); /* emits "omeone " -> "someone " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_DQUO); break;
                    case KC_T: magic_tap_repeatable(KC_N); break;
                    case KC_V: magic_decode_send_suffix_cycle(78, 'n', UINT16_MAX); /* emits "alidation " -> "validation " */ break;
                    case KC_W: magic_replace_decode_send_cap_cycle(92, 's', UINT16_MAX); /* emits "always " */ break;
                    case KC_X: magic_replace_decode_send_cap_cycle(336, 'n', UINT16_MAX); /* emits "exception " */ break;
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
                switch (magic_prepare_last_keycode(last_keycode)) {
                    case KC_B: magic_decode_send_suffix_cycle(126, 'y', UINT16_MAX); /* emits "asically " -> "basically " */ break;
                    case KC_C: magic_replace_decode_send_cap_cycle(8, '\0', UINT16_MAX); /* emits "'ll" */ break;
                    case KC_D: magic_tap_repeatable(KC_H); break;
                    case KC_F: magic_replace_decode_send_cap_cycle(187, 't', UINT16_MAX); /* emits "conflict " */ break;
                    case KC_G: magic_tap_repeatable(KC_F); break;
                    case KC_K: magic_replace_decode_send_cap_cycle(738, 'n', UINT16_MAX); /* emits "question " */ break;
                    case KC_L: magic_tap_repeatable(KC_H); break;
                    case KC_M: magic_tap_repeatable(KC_H); break;
                    case KC_N: magic_tap_repeatable(KC_H); break;
                    case KC_P: magic_tap_repeatable(KC_M); break;
                    case KC_S: magic_tap_repeatable(KC_R); break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_EXLM); break;
                    case KC_T: magic_tap_repeatable(KC_F); break;
                    case KC_V: magic_replace_decode_send_cap_cycle(314, 'g', UINT16_MAX); /* emits "everything " */ break;
                    case KC_W: magic_decode_send_suffix_cycle(133, 't', UINT16_MAX); /* emits "asn't " -> "wasn't " */ break;
                    case KC_X: magic_tap_repeatable(KC_W); break;
                    case KC_Z: magic_replace_decode_send_cap_cycle(744, 'e', UINT16_MAX); /* emits "realize " */ break;
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
                switch (magic_prepare_last_keycode(last_keycode)) {
                    case KC_E: magic_tap_repeatable(KC_U); break;
                    case KC_I: magic_decode_send_suffix_cycle(562, 't', 459); /* emits "mplement " -> "implement " */ break;
                    case KC_O: magic_tap_repeatable(KC_E); break;
                    case KC_SPC: magic_replace_decode_send_cap(21, '\0'); /* emits ". " */ add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state(); break;
                    case KC_V: magic_replace_decode_send_cap_cycle(478, 'e', UINT16_MAX); /* emits "improve " */ break;
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
                switch (magic_prepare_last_keycode(last_keycode)) {
                    case KC_B: magic_decode_send_suffix_cycle(263, 'e', UINT16_MAX); /* emits "ecome " -> "become " */ break;
                    case KC_C: magic_replace_decode_send_cap_cycle(576, '\0', UINT16_MAX); /* emits "n't" */ break;
                    case KC_D: magic_decode_send_suffix_cycle(651, 't', UINT16_MAX); /* emits "on't " -> "don't " */ break;
                    case KC_F: magic_replace_decode_send_cap_cycle(696, 'e', UINT16_MAX); /* emits "performance " */ break;
                    case KC_G: magic_replace_decode_send_cap_cycle(666, 'e', UINT16_MAX); /* emits "organize " */ break;
                    case KC_K: magic_replace_decode_send_cap_cycle(826, 'k', UINT16_MAX); /* emits "think " */ break;
                    case KC_L: magic_decode_send_suffix_cycle(102, 'e', UINT16_MAX); /* emits "anguage " -> "language " */ break;
                    case KC_M: magic_decode_send_suffix_cycle(447, 'n', UINT16_MAX); /* emits "igration " -> "migration " */ break;
                    case KC_N: magic_decode_send_suffix_cycle(309, 'r', UINT16_MAX); /* emits "ever " -> "never " */ break;
                    case KC_P: magic_decode_send_suffix_cycle(293, 'e', UINT16_MAX); /* emits "eople " -> "people " */ break;
                    case KC_S: magic_replace_decode_send_cap_cycle(705, 'e', UINT16_MAX); /* emits "possible " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_QUOTE); break;
                    case KC_V: magic_replace_decode_send_cap_cycle(17, '\0', UINT16_MAX); /* emits "'ve" */ break;
                    case KC_W: magic_decode_send_suffix_cycle(672, 'w', UINT16_MAX); /* emits "orkflow " -> "workflow " */ break;
                    case KC_X: magic_replace_decode_send_cap_cycle(330, 't', UINT16_MAX); /* emits "except " */ break;
                    case KC_Z: magic_replace_decode_send_cap_cycle(410, '\0', UINT16_MAX); /* emits "gregor" */ break;
                    default: magic_decode_send(735); /* emits "qu" */ break;
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
                switch (magic_prepare_last_keycode(last_keycode)) {
                    case KC_B: magic_replace_decode_send_cap_cycle(593, 'y', UINT16_MAX); /* emits "observability " */ break;
                    case KC_C: magic_tap_repeatable(KC_D); break;
                    case KC_E: magic_replace_decode_send_cap_cycle(107, 'r', UINT16_MAX); /* emits "another " */ break;
                    case KC_F: magic_decode_send_suffix_cycle(750, 'y', UINT16_MAX); /* emits "requency " -> "frequency " */ break;
                    case KC_G: magic_decode_send_suffix_cycle(504, 'b', UINT16_MAX); /* emits "ithub " -> "github " */ break;
                    case KC_K: magic_replace_decode_send_cap_cycle(538, 'd', UINT16_MAX); /* emits "merged " */ break;
                    case KC_L: magic_replace_decode_send_cap_cycle(85, 'y', UINT16_MAX); /* emits "already " */ break;
                    case KC_M: magic_decode_send_suffix_cycle(849, 'e', UINT16_MAX); /* emits "ultiple " -> "multiple " */ break;
                    case KC_N: magic_replace_decode_send_cap_cycle(112, 'g', UINT16_MAX); /* emits "anything " */ break;
                    case KC_P: magic_decode_send_suffix_cycle(763, 'y', UINT16_MAX); /* emits "robably " -> "probably " */ break;
                    case KC_S: magic_decode_send_suffix_cycle(869, 't', UINT16_MAX); /* emits "upport " -> "support " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_QUES); break;
                    case KC_T: magic_decode_send_suffix_cycle(427, 'h', UINT16_MAX); /* emits "hrough " -> "through " */ break;
                    case KC_V: magic_decode_send_suffix_cycle(304, 'n', UINT16_MAX); /* emits "ersion " -> "version " */ break;
                    case KC_W: magic_replace_decode_send_cap_cycle(683, 'e', UINT16_MAX); /* emits "otherwise " */ break;
                    case KC_X: magic_replace_decode_send_cap_cycle(358, 't', UINT16_MAX); /* emits "explicit " */ break;
                    case KC_Z: magic_replace_decode_send_cap_cycle(0, 'z', UINT16_MAX); /* emits "#gz " */ break;
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
                switch (magic_prepare_last_keycode(last_keycode)) {
                    case KC_B: magic_replace_decode_send_cap_cycle(236, 'e', UINT16_MAX); /* emits "disable " */ break;
                    case KC_C: magic_decode_send_suffix_cycle(660, 'r', UINT16_MAX); /* emits "ontainer " -> "container " */ break;
                    case KC_D: magic_decode_send_suffix_cycle(438, 'y', UINT16_MAX); /* emits "ifficulty " -> "difficulty " */ break;
                    case KC_ENT: magic_decode_send_cap_cycle(98, 'd', UINT16_MAX); /* emits "and " */ break;
                    case KC_G: magic_decode_send_suffix_cycle(280, 'l', UINT16_MAX); /* emits "eneral " -> "general " */ break;
                    case KC_L: magic_replace_decode_send_cap_cycle(138, 'e', UINT16_MAX); /* emits "available " */ break;
                    case KC_M: magic_decode_send_suffix_cycle(498, 'h', UINT16_MAX); /* emits "ismatch " -> "mismatch " */ break;
                    case KC_P: magic_decode_send_suffix_cycle(928, 'n', UINT16_MAX); /* emits "ython " -> "python " */ break;
                    case KC_S: magic_decode_send_suffix_cycle(453, 'r', UINT16_MAX); /* emits "imilar " -> "similar " */ break;
                    case KC_SPC: magic_decode_send_cap_cycle(98, 'd', UINT16_MAX); /* emits "and " */ break;
                    case KC_TAB: magic_decode_send_cap_cycle(98, 'd', UINT16_MAX); /* emits "and " */ break;
                    case KC_V: magic_replace_decode_send_cap_cycle(207, '\0', UINT16_MAX); /* emits "declarative config" */ break;
                    case KC_W: magic_replace_decode_send_cap_cycle(817, 'h', UINT16_MAX); /* emits "switch " */ break;
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
                switch (magic_prepare_last_keycode(last_keycode)) {
                    case KC_A: magic_tap_repeatable(KC_E); break;
                    case KC_E: magic_tap_repeatable(KC_H); break;
                    case KC_I: magic_replace_decode_send_cap_cycle(558, '\0', UINT16_MAX); /* emits "mpl" */ break;
                    case KC_J: magic_decode_send_suffix_cycle(875, 't', UINT16_MAX); /* emits "ust " -> "just " */ break;
                    case KC_O: magic_tap_repeatable(KC_H); break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_Z); break;
                    case KC_U: magic_tap_repeatable(KC_H); break;
                    case KC_Y: magic_replace_decode_send_cap_cycle(655, 'y', UINT16_MAX); /* emits "only " */ break;
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
                switch (magic_prepare_last_keycode(last_keycode)) {
                    case KC_B: magic_replace_decode_send_cap_cycle(605, 'e', UINT16_MAX); /* emits "obsolete " */ break;
                    case KC_C: magic_decode_send_suffix_cycle(645, 't', UINT16_MAX); /* emits "omment " -> "comment " */ break;
                    case KC_D: magic_decode_send_suffix_cycle(432, 't', UINT16_MAX); /* emits "idn't " -> "didn't " */ break;
                    case KC_F: magic_decode_send_suffix_cycle(612, 'd', UINT16_MAX); /* emits "ocused " -> "focused " */ break;
                    case KC_G: magic_decode_send_suffix_cycle(285, 'e', UINT16_MAX); /* emits "enerate " -> "generate " */ break;
                    case KC_K: magic_replace_decode_send_cap_cycle(863, 'e', UINT16_MAX); /* emits "update " */ break;
                    case KC_L: magic_replace_decode_send_cap_cycle(273, 'e', UINT16_MAX); /* emits "elaborate " */ break;
                    case KC_M: magic_replace_decode_send_cap_cycle(485, 'n', UINT16_MAX); /* emits "instrumentation " */ break;
                    case KC_N: magic_replace_decode_send_cap_cycle(855, 'd', UINT16_MAX); /* emits "understand " */ break;
                    case KC_P: magic_decode_send_suffix_cycle(771, 'n', UINT16_MAX); /* emits "roduction " -> "production " */ break;
                    case KC_S: magic_decode_send_suffix_cycle(298, 'e', UINT16_MAX); /* emits "eparate " -> "separate " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_COMMA); break;
                    case KC_T: magic_decode_send_suffix_cycle(418, 'h', UINT16_MAX); /* emits "hough " -> "though " */ break;
                    case KC_V: magic_replace_decode_send_cap_cycle(118, 'l', UINT16_MAX); /* emits "approval " */ break;
                    case KC_W: magic_decode_send_suffix_cycle(414, 'h', UINT16_MAX); /* emits "hich " -> "which " */ break;
                    case KC_X: magic_replace_decode_send_cap_cycle(344, 'e', UINT16_MAX); /* emits "exclude " */ break;
                    case KC_Y: magic_tap_repeatable(KC_R); break;
                    case KC_Z: magic_replace_decode_send_cap_cycle(34, 'y', UINT16_MAX); /* emits "OpenTelemetry " */ break;
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
                switch (magic_prepare_last_keycode(last_keycode)) {
                    case KC_B: magic_decode_send_suffix_cycle(258, 'e', UINT16_MAX); /* emits "ecause " -> "because " */ break;
                    case KC_C: magic_replace_decode_send_cap_cycle(11, '\0', UINT16_MAX); /* emits "'re" */ break;
                    case KC_D: magic_decode_send_suffix_cycle(621, 't', UINT16_MAX); /* emits "oesn't " -> "doesn't " */ break;
                    case KC_ENT: magic_decode_send_cap_cycle(823, 'e', UINT16_MAX); /* emits "the " */ break;
                    case KC_F: magic_decode_send_suffix_cycle(626, 'g', UINT16_MAX); /* emits "ollowing " -> "following " */ break;
                    case KC_G: magic_tap_repeatable(KC_K); break;
                    case KC_K: magic_decode_send_suffix_cycle(589, 'w', UINT16_MAX); /* emits "now " -> "know " */ break;
                    case KC_L: magic_tap_repeatable(KC_R); break;
                    case KC_M: magic_decode_send_suffix_cycle(290, 't', UINT16_MAX); /* emits "ent " -> "ment " */ break;
                    case KC_N: magic_replace_decode_send_cap_cycle(735, '\0', UINT16_MAX); /* emits "qu" */ break;
                    case KC_P: magic_tap_repeatable(KC_N); break;
                    case KC_S: magic_decode_send(495); /* emits "ion" -> "sion" */ break;
                    case KC_SPC: magic_decode_send_cap_cycle(823, 'e', UINT16_MAX); /* emits "the " */ break;
                    case KC_T: magic_decode_send(495); /* emits "ion" -> "tion" */ break;
                    case KC_TAB: magic_decode_send_cap_cycle(823, 'e', UINT16_MAX); /* emits "the " */ break;
                    case KC_V: magic_replace_decode_send_cap_cycle(757, 'e', UINT16_MAX); /* emits "resolve " */ break;
                    case KC_W: magic_tap_repeatable(KC_S); break;
                    case KC_X: magic_tap_repeatable(KC_R); break;
                    case KC_Z: magic_replace_decode_send_cap_cycle(54, 't', UINT16_MAX); /* emits "Spring Boot " */ break;
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
                switch (magic_prepare_last_keycode(last_keycode)) {
                    case KC_B: magic_tap_repeatable(KC_D); break;
                    case KC_C: magic_replace_decode_send_cap_cycle(5, '\0', UINT16_MAX); /* emits "'d" */ break;
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
                    case KC_T: magic_replace_decode_send_cap_cycle(903, 't', UINT16_MAX); /* emits "without " */ break;
                    case KC_V: magic_replace_decode_send_cap_cycle(29, 'e', UINT16_MAX); /* emits "I've " */ break;
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
                switch (magic_prepare_last_keycode(last_keycode)) {
                    case KC_B: magic_decode_send_suffix_cycle(268, 'e', UINT16_MAX); /* emits "efore " -> "before " */ break;
                    case KC_C: magic_replace_decode_send_cap_cycle(14, '\0', UINT16_MAX); /* emits "'s" */ break;
                    case KC_D: magic_decode_send_suffix_cycle(618, 's', UINT16_MAX); /* emits "oes " -> "does " */ break;
                    case KC_E: magic_decode_send_suffix_cycle(922, 'n', UINT16_MAX); /* emits "xplain " -> "explain " */ break;
                    case KC_G: magic_replace_decode_send_cap_cycle(806, 't', UINT16_MAX); /* emits "suggest " */ break;
                    case KC_K: magic_decode_send_suffix_cycle(585, 'w', UINT16_MAX); /* emits "new " -> "knew " */ break;
                    case KC_L: magic_tap_repeatable(KC_B); break;
                    case KC_M: magic_tap_repeatable(KC_T); break;
                    case KC_N: magic_tap_repeatable(KC_P); break;
                    case KC_P: magic_replace_decode_send_cap_cycle(46, 's', UINT16_MAX); /* emits "Prometheus " */ break;
                    case KC_S: magic_decode_send_suffix_cycle(638, 'g', UINT16_MAX); /* emits "omething " -> "something " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_J); break;
                    case KC_T: magic_decode_send_suffix_cycle(422, 't', UINT16_MAX); /* emits "hought " -> "thought " */ break;
                    case KC_W: magic_decode_send_suffix_cycle(679, 'e', UINT16_MAX); /* emits "orse " -> "worse " */ break;
                    case KC_X: magic_replace_decode_send_cap_cycle(322, 'e', UINT16_MAX); /* emits "example " */ break;
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

    remember_real_keycode(keycode);
    return true;  // Other keys can be repeated.
}
