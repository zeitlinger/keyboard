/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;

static bool magic_capitalize_next = false;

// Magic string decoder lookup tables
static const char magic_char_4bit[] = {
    ' ', 'e', 'o', 't', 'n', 'i', 'a', 'l', 'r', 's', 'u', 'g', 'h', 'p'
};

static const char magic_char_extended[] = {
    'm', 'c', 'd', 'b', 'y', '\'', 'w', 'f', 'v', 'k', 'x', 'q', 'z', '.', 'G', 'I', 'O', 'T', 'P', 'S', 'B', 'Z', 'j'
};

static const uint8_t magic_string_data[] = {
    0x05, 0x06, 0x4f, 0xe2, 0x00, 0x05, 0x0f, 0xe3, 0xa3, 0x00, 0x03, 0xe5, 0xe2, 0x00, 0x04, 0xe5,
    0x77, 0x00, 0x04, 0xe5, 0x81, 0x00, 0x03, 0xe5, 0x90, 0x04, 0xe5, 0xe8, 0x10, 0x02, 0xed, 0x00,
    0x07, 0xee, 0x81, 0xb2, 0x80, 0x05, 0xef, 0xe5, 0xe8, 0x10, 0x0e, 0xf0, 0xd1, 0x4f, 0xf1, 0x17,
    0x1f, 0xe0, 0x13, 0x8f, 0xe4, 0x00, 0x0b, 0xf2, 0x82, 0xe0, 0x13, 0xc1, 0xa9, 0x00, 0x0c, 0xf3,
    0xd8, 0x54, 0xb0, 0xf4, 0x22, 0x30, 0x0b, 0xf5, 0x15, 0x37, 0x54, 0xb1, 0x80, 0x0a, 0x6f, 0xe1,
    0xe9, 0xb8, 0x2a, 0x4f, 0xe2, 0x00, 0x0a, 0x67, 0x5f, 0xe2, 0x63, 0x52, 0x40, 0x08, 0x67, 0x81,
    0x6f, 0xe2, 0xe4, 0x00, 0x07, 0x67, 0xe6, 0x6f, 0xe4, 0x90, 0x04, 0x64, 0xe2, 0x00, 0x08, 0x64,
    0xba, 0x6b, 0x10, 0x08, 0x64, 0x23, 0xc1, 0x80, 0x09, 0x64, 0xe4, 0x3c, 0x54, 0xb0, 0x09, 0x6d,
    0xd8, 0x2f, 0xe8, 0x67, 0x00, 0x09, 0x69, 0x5f, 0xe1, 0x67, 0x7f, 0xe4, 0x00, 0x06, 0x69, 0x4f,
    0xe5, 0x30, 0x0a, 0x6f, 0xe8, 0x65, 0x76, 0xe3, 0x71, 0x00, 0x0b, 0xe3, 0x6f, 0xe1, 0xe9, 0xb8,
    0x2a, 0x4f, 0xe2, 0x00, 0x0a, 0xe3, 0x69, 0x5f, 0xe1, 0x67, 0x7f, 0xe4, 0x00, 0x08, 0xe3, 0x1f,
    0xe1, 0x6a, 0x91, 0x00, 0x07, 0xe3, 0x1f, 0xe1, 0x2f, 0xe0, 0x10, 0x07, 0xe3, 0x1f, 0xe7, 0x28,
    0x10, 0x08, 0xe1, 0x2f, 0xe0, 0xe0, 0x14, 0x30, 0x09, 0xe1, 0x24, 0xe7, 0x75, 0xe1, 0x30, 0x0a,
    0xe1, 0x24, 0xe7, 0xa9, 0x54, 0xb0, 0x12, 0xe2, 0x1f, 0xe1, 0x76, 0x86, 0x35, 0xe8, 0x10, 0xe1,
    0x24, 0xe7, 0x5b, 0x07, 0xe2, 0x5f, 0xe2, 0x4f, 0xe5, 0x30, 0x0b, 0xe2, 0x5f, 0xe7, 0xe7, 0x5f,
    0xe1, 0xa7, 0x3f, 0xe4, 0x00, 0x08, 0xe2, 0x59, 0x6f, 0xe3, 0x71, 0x00, 0x05, 0xe2, 0x21, 0x90,
    0x08, 0xe2, 0x21, 0x94, 0xe5, 0x30, 0x06, 0xe2, 0x24, 0xe5, 0x30, 0x07, 0x1f, 0xe1, 0x6a, 0x91,
    0x00, 0x06, 0x1f, 0xe1, 0x2f, 0xe0, 0x10, 0x06, 0x1f, 0xe7, 0x28, 0x10, 0x0a, 0x17, 0x6f, 0xe3,
    0x28, 0x63, 0x10, 0x07, 0x14, 0x18, 0x67, 0x00, 0x08, 0x14, 0x18, 0x63, 0x10, 0x04, 0x14, 0x30,
    0x06, 0x12, 0xd7, 0x10, 0x08, 0x1d, 0x68, 0x63, 0x10, 0x07, 0x18, 0x95, 0x24, 0x00, 0x05, 0x1f,
    0xe8, 0x18, 0x00, 0x0b, 0x1f, 0xe8, 0x18, 0xe4, 0x3c, 0x54, 0xb0, 0x08, 0x1f, 0xea, 0x6f, 0xe0,
    0xd7, 0x10, 0x07, 0x1f, 0xea, 0xe1, 0x1d, 0x30, 0x0a, 0x1f, 0xea, 0xe1, 0x1d, 0x35, 0x24, 0x00,
    0x08, 0x1f, 0xea, 0xe1, 0x7a, 0xe2, 0x10, 0x08, 0x1f, 0xea, 0xd7, 0x65, 0x40, 0x09, 0x1f, 0xea,
    0xd7, 0x5f, 0xe1, 0x53, 0x00, 0x08, 0xe7, 0x2f, 0xe1, 0xa9, 0x1f, 0xe2, 0x00, 0x0a, 0xe7, 0x27,
    0x72, 0xe6, 0x54, 0xb0, 0x0a, 0xe7, 0x81, 0xeb, 0xa1, 0x4f, 0xe1, 0xe4, 0x00, 0x08, 0xb1, 0x41,
    0x86, 0x70, 0x09, 0xb1, 0x41, 0x86, 0x31, 0x00, 0x07, 0xb5, 0x3c, 0xaf, 0xe3, 0x00, 0x07, 0xb7,
    0x2f, 0xe3, 0x67, 0x00, 0x06, 0xb8, 0x1b, 0x28, 0x05, 0xc5, 0xe1, 0xc0, 0x06, 0xc2, 0xab, 0xc0,
    0x07, 0xc2, 0xab, 0xc3, 0x00, 0x07, 0xc8, 0x2a, 0xbc, 0x00, 0x06, 0x5f, 0xe2, 0x4f, 0xe5, 0x30,
    0x0a, 0x5f, 0xe7, 0xe7, 0x5f, 0xe1, 0xa7, 0x3f, 0xe4, 0x00, 0x09, 0x5b, 0x86, 0x35, 0x24, 0x00,
    0x07, 0x5f, 0xe0, 0x57, 0x68, 0x00, 0x0a, 0x5f, 0xe0, 0xd7, 0x1f, 0xe0, 0x14, 0x30, 0x0f, 0x5f,
    0xe0, 0xd7, 0x1f, 0xe0, 0x14, 0x36, 0x35, 0x24, 0x00, 0x08, 0x5f, 0xe0, 0xd8, 0x2f, 0xe8, 0x10,
    0x10, 0x54, 0x93, 0x8a, 0xe0, 0x14, 0x36, 0x35, 0x24, 0x00, 0x03, 0x52, 0x40, 0x08, 0x59, 0xe0,
    0x63, 0xe1, 0xc0, 0x06, 0x53, 0xca, 0xe3, 0x00, 0x05, 0xf6, 0xa9, 0x30, 0x05, 0xe9, 0x41, 0xe6,
    0x00, 0x05, 0xe9, 0x42, 0xe6, 0x00, 0x09, 0x76, 0x4b, 0xa6, 0xb1, 0x00, 0x06, 0x72, 0xe3, 0x67,
    0x00, 0x05, 0xe0, 0x14, 0x30, 0x07, 0xe0, 0x18, 0xb1, 0xe2, 0x00, 0x0a, 0xe0, 0x5b, 0x86, 0x35,
    0x24, 0x00, 0x09, 0xe0, 0x59, 0xe0, 0x63, 0xe1, 0xc0, 0x03, 0xe0, 0xd7, 0x09, 0xe0, 0xd7, 0x1f,
    0xe0, 0x14, 0x30, 0x09, 0xe0, 0xa7, 0x35, 0xd7, 0x10, 0x03, 0x4f, 0xe5, 0x30, 0x04, 0x4f, 0xe5,
    0x30, 0x06, 0x41, 0xe8, 0x18, 0x00, 0x04, 0x41, 0xe6, 0x00, 0x04, 0x42, 0xe6, 0x00, 0x0e, 0x2f,
    0xe3, 0x91, 0x8f, 0xe8, 0x6f, 0xe3, 0x57, 0x53, 0xe4, 0x00, 0x09, 0x2f, 0xe3, 0x92, 0x71, 0x31,
    0x00, 0x07, 0x2f, 0xe1, 0xa9, 0x1f, 0xe2, 0x00, 0x04, 0x21, 0x90, 0x07, 0x21, 0x94, 0xe5, 0x30,
    0x09, 0x27, 0x72, 0xe6, 0x54, 0xb0, 0x07, 0x2f, 0xe0, 0x12, 0x41, 0x00, 0x09, 0x2f, 0xe0, 0x13,
    0xc5, 0x4b, 0x00, 0x07, 0x2f, 0xe0, 0xe0, 0x14, 0x30, 0x05, 0x24, 0xe5, 0x30, 0x05, 0x24, 0x7f,
    0xe4, 0x00, 0x09, 0x28, 0xb6, 0x45, 0xec, 0x10, 0x08, 0x28, 0xe9, 0xe7, 0x72, 0xe6, 0x00, 0x05,
    0x28, 0x91, 0x00, 0x0a, 0x23, 0xc1, 0x8f, 0xe6, 0x59, 0x10, 0x07, 0xd1, 0x2d, 0x71, 0x00, 0x0c,
    0xd1, 0x8f, 0xe7, 0x28, 0xe0, 0x64, 0xe1, 0x10, 0x09, 0xd2, 0x99, 0x5f, 0xe3, 0x71, 0x00, 0x09,
    0xd8, 0x2f, 0xe3, 0x6f, 0xe3, 0x7f, 0xe4, 0x00, 0x0b, 0xd8, 0x2f, 0xe2, 0xaf, 0xe1, 0x35, 0x24,
    0x00, 0x07, 0xdf, 0xe4, 0x3c, 0x24, 0x00, 0x01, 0xeb, 0x02, 0xeb, 0xa0, 0x09, 0xeb, 0xa1, 0x93,
    0x52, 0x40, 0x08, 0x81, 0x67, 0x5f, 0xec, 0x10, 0x09, 0x81, 0xeb, 0xa1, 0x4f, 0xe1, 0xe4, 0x00,
    0x08, 0x81, 0x92, 0x7f, 0xe8, 0x10, 0x08, 0x82, 0xe3, 0x6f, 0xe3, 0x7f, 0xe4, 0x00, 0x0a, 0x82,
    0xe2, 0xaf, 0xe1, 0x35, 0x24, 0x00, 0x09, 0x91, 0xd6, 0x86, 0x31, 0x00, 0x08, 0x95, 0xe0, 0x57,
    0x68, 0x00, 0x04, 0x95, 0x24, 0x08, 0x92, 0xe0, 0x12, 0x41, 0x00, 0x0a, 0x92, 0xe0, 0x13, 0xc5,
    0x4b, 0x00, 0x08, 0x9a, 0xbb, 0x19, 0x30, 0x08, 0x9a, 0xdd, 0x28, 0x30, 0x07, 0x9f, 0xe6, 0x53,
    0xe1, 0xc0, 0x04, 0x3c, 0x10, 0x06, 0x3c, 0x54, 0xe9, 0x00, 0x07, 0x3c, 0x2a, 0xbc, 0x00, 0x08,
    0x3c, 0x2a, 0xbc, 0x30, 0x08, 0x3c, 0x82, 0xab, 0xc0, 0x04, 0x35, 0x24, 0x08, 0xa7, 0x35, 0xd7,
    0x10, 0x0b, 0xa4, 0xe2, 0x18, 0x93, 0x64, 0xe2, 0x00, 0x07, 0xad, 0xe2, 0x63, 0x10, 0x07, 0xad,
    0xd2, 0x83, 0x00, 0x04, 0xa9, 0x30, 0x0b, 0xe8, 0x67, 0x5f, 0xe2, 0x63, 0x52, 0x40, 0x08, 0xe8,
    0x18, 0x95, 0x24, 0x00, 0x07, 0xe6, 0x69, 0x4f, 0xe5, 0x30, 0x06, 0xe6, 0xc5, 0xe1, 0xc0, 0x08,
    0xe6, 0x53, 0xc2, 0xa3, 0x00, 0x09, 0xe6, 0x28, 0xe9, 0xe7, 0x72, 0xe6, 0x00, 0x06, 0xe6, 0x28,
    0x91, 0x00, 0x07, 0xea, 0xd7, 0x65, 0x40, 0x06, 0xe4, 0x3c, 0x24, 0x00, 0x01, 0xec
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
    { 32, 70, 0, 'r' },
    { 70, 32, 0, 'r' },
    { 470, 478, 9, 'n' },
    { 478, 470, 9, 't' }
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
    case C_LEFT_KC_EXLM: return 200;
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
    case C_RIGHT_KC_COMMA: return 200;
    case C_RIGHT_KC_DOT: return 200;
    case C_RIGHT_KC_GRAVE: return 200;
    case C_RIGHT_KC_J: return 200;
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
static uint16_t last_keycode_timer = 0;
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
    last_keycode_timer = timer_read();
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

static bool is_magic_keycode(uint16_t keycode) {
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
            return true;
    default:
        return false;
    }
}

static bool is_magic_preceding_keycode(uint16_t keycode) {
    switch (keycode) {
case KC_A:
case KC_B:
case KC_C:
case KC_COMMA:
case KC_D:
case KC_E:
case KC_ENT:
case KC_F:
case KC_G:
case KC_H:
case KC_I:
case KC_J:
case KC_K:
case KC_L:
case KC_M:
case KC_N:
case KC_O:
case KC_P:
case KC_R:
case KC_S:
case KC_SPC:
case KC_T:
case KC_TAB:
case KC_U:
case KC_V:
case KC_W:
case KC_X:
case KC_Y:
case KC_Z:
            return true;
    default:
        return false;
    }
}

static bool process_magic_key_with_context(uint16_t keycode, uint16_t context_keycode, bool allow_repeat) {
    switch (keycode) {
        case MAGIC_A: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_A)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_A;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_decode_send_suffix_cycle(77, 'd', UINT16_MAX); /* emits "ackground " -> "background " */ break;
                case KC_C: magic_tap_repeatable(KC_N); break;
                case KC_D: magic_tap_repeatable(KC_C); break;
                case KC_F: magic_replace_decode_send_cap_cycle(207, 'g', UINT16_MAX); /* emits "confusing " */ break;
                case KC_G: magic_decode_send_suffix_cycle(540, 'l', UINT16_MAX); /* emits "lobal " -> "global " */ break;
                case KC_K: magic_tap_repeatable(KC_R); break;
                case KC_L: magic_tap_repeatable(KC_M); break;
                case KC_M: magic_tap_repeatable(KC_R); break;
                case KC_N: magic_tap_repeatable(KC_R); break;
                case KC_P: magic_tap_repeatable(KC_Y); break;
                case KC_R: magic_replace_tap_repeatable(KC_DQUO); break;
                case KC_S: magic_decode_send_suffix_cycle(646, 'e', UINT16_MAX); /* emits "omeone " -> "someone " */ break;
                case KC_T: magic_tap_repeatable(KC_N); break;
                case KC_V: magic_decode_send_suffix_cycle(86, 'n', UINT16_MAX); /* emits "alidation " -> "validation " */ break;
                case KC_W: magic_replace_decode_send_cap_cycle(100, 's', UINT16_MAX); /* emits "always " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(344, 'n', UINT16_MAX); /* emits "exception " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_A;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_B: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_B)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_B;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_decode_send_suffix_cycle(133, 'y', UINT16_MAX); /* emits "asically " -> "basically " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(14, '\0', UINT16_MAX); /* emits "'ll " */ break;
                case KC_D: magic_tap_repeatable(KC_H); break;
                case KC_F: magic_replace_decode_send_cap_cycle(200, 't', UINT16_MAX); /* emits "conflict " */ break;
                case KC_G: magic_tap_repeatable(KC_F); break;
                case KC_K: magic_replace_decode_send_cap_cycle(748, 'n', UINT16_MAX); /* emits "question " */ break;
                case KC_L: magic_tap_repeatable(KC_H); break;
                case KC_M: magic_tap_repeatable(KC_H); break;
                case KC_N: magic_tap_repeatable(KC_H); break;
                case KC_P: magic_tap_repeatable(KC_M); break;
                case KC_R: magic_replace_decode_send_cap_cycle(743, '\0', UINT16_MAX); /* emits "q" */ break;
                case KC_S: magic_tap_repeatable(KC_R); break;
                case KC_T: magic_tap_repeatable(KC_F); break;
                case KC_V: magic_replace_decode_send_cap_cycle(323, 'g', UINT16_MAX); /* emits "everything " */ break;
                case KC_W: magic_decode_send_suffix_cycle(141, 't', UINT16_MAX); /* emits "asn't " -> "wasn't " */ break;
                case KC_X: magic_tap_repeatable(KC_W); break;
                case KC_Z: magic_replace_decode_send_cap_cycle(754, 'e', UINT16_MAX); /* emits "realize " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_B;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_C: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_C)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_C;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_E: magic_tap_repeatable(KC_U); break;
                case KC_I: magic_decode_send_suffix_cycle(572, 't', 470); /* emits "mplement " -> "implement " */ break;
                case KC_O: magic_tap_repeatable(KC_E); break;
                case KC_SPC: magic_replace_decode_send_cap(29, '\0'); /* emits ". " */ add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state(); break;
                case KC_V: magic_replace_decode_send_cap_cycle(489, 'e', UINT16_MAX); /* emits "improve " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_C;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_D: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_D)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_D;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_decode_send_suffix_cycle(273, 'e', UINT16_MAX); /* emits "ecome " -> "become " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(589, '\0', UINT16_MAX); /* emits "n't " */ break;
                case KC_D: magic_decode_send_suffix_cycle(665, 't', UINT16_MAX); /* emits "on't " -> "don't " */ break;
                case KC_F: magic_replace_decode_send_cap_cycle(703, 'e', UINT16_MAX); /* emits "performance " */ break;
                case KC_G: magic_replace_decode_send_cap_cycle(674, 'e', UINT16_MAX); /* emits "organize " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(837, 'k', UINT16_MAX); /* emits "think " */ break;
                case KC_L: magic_decode_send_suffix_cycle(110, 'e', UINT16_MAX); /* emits "anguage " -> "language " */ break;
                case KC_M: magic_decode_send_suffix_cycle(458, 'n', UINT16_MAX); /* emits "igration " -> "migration " */ break;
                case KC_N: magic_decode_send_suffix_cycle(318, 'r', UINT16_MAX); /* emits "ever " -> "never " */ break;
                case KC_P: magic_decode_send_suffix_cycle(304, 'e', UINT16_MAX); /* emits "eople " -> "people " */ break;
                case KC_R: magic_replace_decode_send_cap_cycle(585, '\0', UINT16_MAX); /* emits "n't" */ break;
                case KC_S: magic_replace_decode_send_cap_cycle(712, 'e', UINT16_MAX); /* emits "possible " */ break;
                case KC_W: magic_decode_send_suffix_cycle(680, 'w', UINT16_MAX); /* emits "orkflow " -> "workflow " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(338, 't', UINT16_MAX); /* emits "except " */ break;
                case KC_Z: magic_replace_decode_send_cap_cycle(420, '\0', UINT16_MAX); /* emits "gregor" */ break;
                default: magic_decode_send(745); /* emits "qu" */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_D;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_E: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_E)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_E;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_replace_decode_send_cap_cycle(606, 'y', UINT16_MAX); /* emits "observability " */ break;
                case KC_C: magic_tap_repeatable(KC_D); break;
                case KC_E: magic_replace_decode_send_cap_cycle(115, 'r', UINT16_MAX); /* emits "another " */ break;
                case KC_F: magic_decode_send_suffix_cycle(760, 'y', UINT16_MAX); /* emits "requency " -> "frequency " */ break;
                case KC_G: magic_decode_send_suffix_cycle(515, 'b', UINT16_MAX); /* emits "ithub " -> "github " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(549, 'd', UINT16_MAX); /* emits "merged " */ break;
                case KC_L: magic_replace_decode_send_cap_cycle(93, 'y', UINT16_MAX); /* emits "already " */ break;
                case KC_M: magic_decode_send_suffix_cycle(860, 'e', UINT16_MAX); /* emits "ultiple " -> "multiple " */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(120, 'g', UINT16_MAX); /* emits "anything " */ break;
                case KC_P: magic_decode_send_suffix_cycle(774, 'y', UINT16_MAX); /* emits "robably " -> "probably " */ break;
                case KC_R: magic_replace_tap_repeatable(KC_QUES); break;
                case KC_S: magic_decode_send_suffix_cycle(878, 't', UINT16_MAX); /* emits "upport " -> "support " */ break;
                case KC_T: magic_decode_send_suffix_cycle(437, 'h', UINT16_MAX); /* emits "hrough " -> "through " */ break;
                case KC_V: magic_decode_send_suffix_cycle(313, 'n', UINT16_MAX); /* emits "ersion " -> "version " */ break;
                case KC_W: magic_replace_decode_send_cap_cycle(691, 'e', UINT16_MAX); /* emits "otherwise " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(365, 't', UINT16_MAX); /* emits "explicit " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_E;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_F: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_F)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_F;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_replace_decode_send_cap_cycle(245, 'e', UINT16_MAX); /* emits "disable " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(25, '\0', UINT16_MAX); /* emits "'ve " */ break;
                case KC_D: magic_decode_send_suffix_cycle(448, 'y', UINT16_MAX); /* emits "ifficulty " -> "difficulty " */ break;
                case KC_G: magic_decode_send_suffix_cycle(291, 'l', UINT16_MAX); /* emits "eneral " -> "general " */ break;
                case KC_L: magic_replace_decode_send_cap_cycle(146, 'e', UINT16_MAX); /* emits "available " */ break;
                case KC_M: magic_decode_send_suffix_cycle(509, 'h', UINT16_MAX); /* emits "ismatch " -> "mismatch " */ break;
                case KC_P: magic_decode_send_suffix_cycle(935, 'n', UINT16_MAX); /* emits "ython " -> "python " */ break;
                case KC_R: magic_tap_repeatable(KC_X); break;
                case KC_S: magic_decode_send_suffix_cycle(464, 'r', UINT16_MAX); /* emits "imilar " -> "similar " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(214, '\0', UINT16_MAX); /* emits "declarative config" */ break;
                case KC_W: magic_replace_decode_send_cap_cycle(828, 'h', UINT16_MAX); /* emits "switch " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_F;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_G: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_G)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_G;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_A: magic_tap_repeatable(KC_E); break;
                case KC_E: magic_tap_repeatable(KC_H); break;
                case KC_H: magic_replace_decode_send_cap_cycle(745, '\0', UINT16_MAX); /* emits "qu" */ break;
                case KC_I: magic_replace_decode_send_cap_cycle(569, '\0', UINT16_MAX); /* emits "mpl" */ break;
                case KC_J: magic_decode_send_suffix_cycle(883, 't', UINT16_MAX); /* emits "ust " -> "just " */ break;
                case KC_O: magic_tap_repeatable(KC_H); break;
                case KC_R: magic_replace_tap_repeatable(KC_EXLM); break;
                case KC_SPC: magic_decode_send_cap_cycle(940, '\0', UINT16_MAX); /* emits "z" */ break;
                case KC_U: magic_tap_repeatable(KC_H); break;
                case KC_Y: magic_replace_decode_send_cap_cycle(669, 'y', UINT16_MAX); /* emits "only " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_G;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_H: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_H)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_H;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_replace_decode_send_cap_cycle(618, 'e', UINT16_MAX); /* emits "obsolete " */ break;
                case KC_C: magic_decode_send_suffix_cycle(659, 't', UINT16_MAX); /* emits "omment " -> "comment " */ break;
                case KC_COMMA: magic_decode_send_cap_cycle(0, '\0', UINT16_MAX); /* emits " and " */ break;
                case KC_D: magic_decode_send_suffix_cycle(442, 't', UINT16_MAX); /* emits "idn't " -> "didn't " */ break;
                case KC_ENT: magic_decode_send_cap_cycle(106, 'd', UINT16_MAX); /* emits "and " */ break;
                case KC_F: magic_decode_send_suffix_cycle(625, 'd', UINT16_MAX); /* emits "ocused " -> "focused " */ break;
                case KC_G: magic_decode_send_suffix_cycle(296, 'e', UINT16_MAX); /* emits "enerate " -> "generate " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(873, 'e', UINT16_MAX); /* emits "update " */ break;
                case KC_L: magic_replace_decode_send_cap_cycle(284, 'e', UINT16_MAX); /* emits "elaborate " */ break;
                case KC_M: magic_replace_decode_send_cap_cycle(496, 'n', UINT16_MAX); /* emits "instrumentation " */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(865, 'd', UINT16_MAX); /* emits "understand " */ break;
                case KC_P: magic_decode_send_suffix_cycle(782, 'n', UINT16_MAX); /* emits "roduction " -> "production " */ break;
                case KC_R: magic_replace_tap_repeatable(KC_QUOTE); break;
                case KC_S: magic_decode_send_suffix_cycle(308, 'e', UINT16_MAX); /* emits "eparate " -> "separate " */ break;
                case KC_SPC: magic_decode_send_cap_cycle(106, 'd', UINT16_MAX); /* emits "and " */ break;
                case KC_T: magic_decode_send_suffix_cycle(428, 'h', UINT16_MAX); /* emits "hough " -> "though " */ break;
                case KC_TAB: magic_decode_send_cap_cycle(106, 'd', UINT16_MAX); /* emits "and " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(126, 'l', UINT16_MAX); /* emits "approval " */ break;
                case KC_W: magic_decode_send_suffix_cycle(424, 'h', UINT16_MAX); /* emits "hich " -> "which " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(352, 'e', UINT16_MAX); /* emits "exclude " */ break;
                case KC_Y: magic_tap_repeatable(KC_R); break;
                case KC_Z: magic_replace_decode_send_cap_cycle(42, 'y', UINT16_MAX); /* emits "OpenTelemetry " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_H;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_I: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_I)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_I;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_decode_send_suffix_cycle(267, 'e', UINT16_MAX); /* emits "ecause " -> "because " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(18, '\0', UINT16_MAX); /* emits "'re " */ break;
                case KC_COMMA: magic_decode_send_cap_cycle(5, '\0', UINT16_MAX); /* emits " but " */ break;
                case KC_D: magic_decode_send_suffix_cycle(635, 't', UINT16_MAX); /* emits "oesn't " -> "doesn't " */ break;
                case KC_ENT: magic_decode_send_cap_cycle(834, 'e', UINT16_MAX); /* emits "the " */ break;
                case KC_F: magic_decode_send_suffix_cycle(640, 'g', UINT16_MAX); /* emits "ollowing " -> "following " */ break;
                case KC_G: magic_tap_repeatable(KC_K); break;
                case KC_K: magic_decode_send_suffix_cycle(602, 'w', UINT16_MAX); /* emits "now " -> "know " */ break;
                case KC_L: magic_tap_repeatable(KC_R); break;
                case KC_M: magic_decode_send_suffix_cycle(301, 't', UINT16_MAX); /* emits "ent " -> "ment " */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(745, '\0', UINT16_MAX); /* emits "qu" */ break;
                case KC_P: magic_tap_repeatable(KC_N); break;
                case KC_R: magic_replace_tap_repeatable(KC_COMMA); break;
                case KC_S: magic_decode_send(506); /* emits "ion" -> "sion" */ break;
                case KC_SPC: magic_decode_send_cap_cycle(834, 'e', UINT16_MAX); /* emits "the " */ break;
                case KC_T: magic_decode_send(506); /* emits "ion" -> "tion" */ break;
                case KC_TAB: magic_decode_send_cap_cycle(834, 'e', UINT16_MAX); /* emits "the " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(768, 'e', UINT16_MAX); /* emits "resolve " */ break;
                case KC_W: magic_tap_repeatable(KC_S); break;
                case KC_X: magic_tap_repeatable(KC_R); break;
                case KC_Z: magic_replace_decode_send_cap_cycle(62, 't', UINT16_MAX); /* emits "Spring Boot " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_I;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_J: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_J)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_J;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_tap_repeatable(KC_D); break;
                case KC_C: magic_replace_decode_send_cap_cycle(10, '\0', UINT16_MAX); /* emits "'d " */ break;
                case KC_D: magic_tap_repeatable(KC_F); break;
                case KC_F: magic_tap_repeatable(KC_D); break;
                case KC_G: magic_tap_repeatable(KC_D); break;
                case KC_H: magic_tap_repeatable(KC_Y); break;
                case KC_K: magic_tap_repeatable(KC_X); break;
                case KC_L: magic_tap_repeatable(KC_C); break;
                case KC_M: magic_tap_repeatable(KC_L); break;
                case KC_N: magic_tap_repeatable(KC_X); break;
                case KC_P: magic_tap_repeatable(KC_D); break;
                case KC_R: magic_replace_tap_repeatable(KC_DOT); break;
                case KC_S: magic_tap_repeatable(KC_D); break;
                case KC_T: magic_replace_decode_send_cap_cycle(911, 't', UINT16_MAX); /* emits "without " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(37, 'e', UINT16_MAX); /* emits "I've " */ break;
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
            if (allow_repeat && repeat_last_magic_key(MAGIC_K)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_K;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_decode_send_suffix_cycle(279, 'e', UINT16_MAX); /* emits "efore " -> "before " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(22, '\0', UINT16_MAX); /* emits "'s " */ break;
                case KC_D: magic_decode_send_suffix_cycle(632, 's', UINT16_MAX); /* emits "oes " -> "does " */ break;
                case KC_E: magic_decode_send_suffix_cycle(930, 'n', UINT16_MAX); /* emits "xplain " -> "explain " */ break;
                case KC_G: magic_replace_decode_send_cap_cycle(818, 't', UINT16_MAX); /* emits "suggest " */ break;
                case KC_K: magic_decode_send_suffix_cycle(598, 'w', UINT16_MAX); /* emits "new " -> "knew " */ break;
                case KC_L: magic_tap_repeatable(KC_B); break;
                case KC_M: magic_tap_repeatable(KC_T); break;
                case KC_N: magic_tap_repeatable(KC_P); break;
                case KC_P: magic_replace_decode_send_cap_cycle(54, 's', UINT16_MAX); /* emits "Prometheus " */ break;
                case KC_R: magic_tap_repeatable(KC_J); break;
                case KC_S: magic_decode_send_suffix_cycle(652, 'g', UINT16_MAX); /* emits "omething " -> "something " */ break;
                case KC_T: magic_decode_send_suffix_cycle(432, 't', UINT16_MAX); /* emits "hought " -> "thought " */ break;
                case KC_W: magic_decode_send_suffix_cycle(687, 'e', UINT16_MAX); /* emits "orse " -> "worse " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(331, 'e', UINT16_MAX); /* emits "example " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_K;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
    default:
        return true;
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
            if (!process_magic_key_with_context(keycode, last_keycode, true)) {
                return false;
            }
            switch (keycode) {
            
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
