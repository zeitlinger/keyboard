/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;

static bool magic_capitalize_next = false;
static bool magic_context_key_emitted = true;

// Magic string decoder lookup tables
static const char magic_char_4bit[] = {
    ' ', 'e', 'o', 't', 'n', 'i', 'a', 'l', 'r', 's', 'h', 'u', 'g', 'm'
};

static const char magic_char_extended[] = {
    'p', 'd', 'c', 'b', 'w', '\'', 'y', 'f', 'v', 'k', 'x', 'q', '.', 'G', 'I', 'P', 'Z', 'j', 'z'
};

static const uint8_t magic_string_data[] = {
    0x05, 0x06, 0x4f, 0xe1, 0x00, 0x05, 0x0f, 0xe3, 0xb3, 0x00, 0x03, 0xe5, 0xe1, 0x00, 0x04, 0xe5,
    0x77, 0x00, 0x04, 0xe5, 0x81, 0x00, 0x03, 0xe5, 0x90, 0x04, 0xe5, 0xe8, 0x10, 0x02, 0xec, 0x00,
    0x07, 0xed, 0x81, 0xc2, 0x80, 0x05, 0xee, 0xe5, 0xe8, 0x10, 0x0b, 0xef, 0x82, 0xd1, 0x3a, 0x1b,
    0x90, 0x0b, 0xf0, 0x15, 0x37, 0x54, 0xc1, 0x80, 0x0a, 0x6f, 0xe2, 0xe9, 0xc8, 0x2b, 0x4f, 0xe1,
    0x00, 0x08, 0x6f, 0xe1, 0xe1, 0x81, 0x99, 0x00, 0x0a, 0x67, 0x5f, 0xe1, 0x63, 0x52, 0x40, 0x08,
    0x67, 0x81, 0x6f, 0xe1, 0xe6, 0x00, 0x07, 0x67, 0xe4, 0x6f, 0xe6, 0x90, 0x04, 0x64, 0xe1, 0x00,
    0x08, 0x64, 0xcb, 0x6c, 0x10, 0x08, 0x64, 0x23, 0xa1, 0x80, 0x09, 0x64, 0xe6, 0x3a, 0x54, 0xc0,
    0x09, 0x6f, 0xe0, 0xe0, 0x82, 0xe8, 0x67, 0x00, 0x09, 0x69, 0x5f, 0xe2, 0x67, 0x7f, 0xe6, 0x00,
    0x06, 0x69, 0x4f, 0xe5, 0x30, 0x0a, 0x6f, 0xe8, 0x65, 0x76, 0xe3, 0x71, 0x00, 0x0b, 0xe3, 0x6f,
    0xe2, 0xe9, 0xc8, 0x2b, 0x4f, 0xe1, 0x00, 0x0a, 0xe3, 0x69, 0x5f, 0xe2, 0x67, 0x7f, 0xe6, 0x00,
    0x08, 0xe3, 0x1f, 0xe2, 0x6b, 0x91, 0x00, 0x07, 0xe3, 0x1f, 0xe2, 0x2d, 0x10, 0x07, 0xe3, 0x1f,
    0xe7, 0x28, 0x10, 0x07, 0xe2, 0xa6, 0x4c, 0x10, 0x08, 0xe2, 0x2d, 0xd1, 0x43, 0x00, 0x09, 0xe2,
    0x24, 0xe7, 0x75, 0xe2, 0x30, 0x0a, 0xe2, 0x24, 0xe7, 0xb9, 0x54, 0xc0, 0x07, 0xe1, 0xe1, 0x81,
    0x99, 0x00, 0x07, 0xe1, 0x5f, 0xe1, 0x4f, 0xe5, 0x30, 0x0b, 0xe1, 0x5f, 0xe7, 0xe7, 0x5f, 0xe2,
    0xb7, 0x3f, 0xe6, 0x00, 0x08, 0xe1, 0x59, 0x6f, 0xe3, 0x71, 0x00, 0x05, 0xe1, 0x21, 0x90, 0x08,
    0xe1, 0x21, 0x94, 0xe5, 0x30, 0x06, 0xe1, 0x24, 0xe5, 0x30, 0x07, 0x1f, 0xe2, 0x6b, 0x91, 0x00,
    0x06, 0x1f, 0xe2, 0x2d, 0x10, 0x06, 0x1f, 0xe7, 0x28, 0x10, 0x0a, 0x17, 0x6f, 0xe3, 0x28, 0x63,
    0x10, 0x07, 0x14, 0x18, 0x67, 0x00, 0x08, 0x14, 0x18, 0x63, 0x10, 0x03, 0x14, 0x30, 0x06, 0x12,
    0xe0, 0x71, 0x00, 0x08, 0x1f, 0xe0, 0x68, 0x63, 0x10, 0x07, 0x18, 0x95, 0x24, 0x00, 0x05, 0x1f,
    0xe8, 0x18, 0x00, 0x0b, 0x1f, 0xe8, 0x18, 0xe6, 0x3a, 0x54, 0xc0, 0x08, 0x1f, 0xea, 0x6d, 0xe0,
    0x71, 0x00, 0x07, 0x1f, 0xea, 0xe2, 0x1f, 0xe0, 0x30, 0x0a, 0x1f, 0xea, 0xe2, 0x1f, 0xe0, 0x35,
    0x24, 0x00, 0x08, 0x1f, 0xea, 0xe2, 0x7b, 0xe1, 0x10, 0x05, 0x1f, 0xea, 0x53, 0x00, 0x08, 0x1f,
    0xea, 0xe0, 0x76, 0x54, 0x00, 0x09, 0x1f, 0xea, 0xe0, 0x75, 0xe2, 0x53, 0x00, 0x08, 0xe7, 0x2f,
    0xe2, 0xb9, 0x1f, 0xe1, 0x00, 0x0a, 0xe7, 0x27, 0x72, 0xe4, 0x54, 0xc0, 0x08, 0xc1, 0x41, 0x86,
    0x70, 0x09, 0xc1, 0x41, 0x86, 0x31, 0x00, 0x07, 0xc7, 0x2f, 0xe3, 0x67, 0x00, 0x06, 0xc8, 0x1c,
    0x28, 0x05, 0xa5, 0xe2, 0xa0, 0x06, 0xa2, 0xbc, 0xa0, 0x07, 0xa2, 0xbc, 0xa3, 0x00, 0x07, 0xa8,
    0x2b, 0xca, 0x00, 0x03, 0xaf, 0xe6, 0x00, 0x06, 0x5f, 0xe1, 0x4f, 0xe5, 0x30, 0x0a, 0x5f, 0xe7,
    0xe7, 0x5f, 0xe2, 0xb7, 0x3f, 0xe6, 0x00, 0x09, 0x5c, 0x86, 0x35, 0x24, 0x00, 0x07, 0x5d, 0x57,
    0x68, 0x00, 0x04, 0x5d, 0xe0, 0x70, 0x0a, 0x5d, 0xe0, 0x71, 0xd1, 0x43, 0x00, 0x0f, 0x5d, 0xe0,
    0x71, 0xd1, 0x43, 0x63, 0x52, 0x40, 0x08, 0x5d, 0xe0, 0x82, 0xe8, 0x10, 0x10, 0x54, 0x93, 0x8b,
    0xd1, 0x43, 0x63, 0x52, 0x40, 0x03, 0x52, 0x40, 0x08, 0x59, 0xd6, 0x3f, 0xe2, 0xa0, 0x05, 0xf1,
    0xb9, 0x30, 0x05, 0xe9, 0x41, 0xe4, 0x00, 0x05, 0xe9, 0x42, 0xe4, 0x00, 0x09, 0x76, 0x4c, 0xb6,
    0xc1, 0x00, 0x06, 0x72, 0xe3, 0x67, 0x00, 0x04, 0xd1, 0x43, 0x07, 0xd1, 0x8c, 0x1f, 0xe1, 0x00,
    0x0a, 0xd5, 0xc8, 0x63, 0x52, 0x40, 0x09, 0xd5, 0x9d, 0x63, 0xe2, 0xa0, 0x03, 0xdf, 0xe0, 0x70,
    0x09, 0xdf, 0xe0, 0x71, 0xd1, 0x43, 0x00, 0x09, 0xdb, 0x73, 0x5f, 0xe0, 0x71, 0x00, 0x03, 0x4f,
    0xe5, 0x30, 0x04, 0x4f, 0xe5, 0x30, 0x06, 0x41, 0xe8, 0x18, 0x00, 0x04, 0x41, 0xe4, 0x00, 0x04,
    0x42, 0xe4, 0x00, 0x0e, 0x2f, 0xe3, 0x91, 0x8f, 0xe8, 0x6f, 0xe3, 0x57, 0x53, 0xe6, 0x00, 0x09,
    0x2f, 0xe3, 0x92, 0x71, 0x31, 0x00, 0x07, 0x2f, 0xe2, 0xb9, 0x1f, 0xe1, 0x00, 0x04, 0x21, 0x90,
    0x07, 0x21, 0x94, 0xe5, 0x30, 0x09, 0x27, 0x72, 0xe4, 0x54, 0xc0, 0x07, 0x2d, 0x12, 0x41, 0x00,
    0x09, 0x2d, 0x13, 0xa5, 0x4c, 0x00, 0x07, 0x2d, 0xd1, 0x43, 0x00, 0x05, 0x24, 0xe5, 0x30, 0x05,
    0x24, 0x7f, 0xe6, 0x00, 0x09, 0x28, 0xc6, 0x45, 0xf2, 0x10, 0x08, 0x28, 0xe9, 0xe7, 0x72, 0xe4,
    0x00, 0x0a, 0x23, 0xa1, 0x8f, 0xe4, 0x59, 0x10, 0x07, 0xe0, 0x12, 0xe0, 0x71, 0x00, 0x0c, 0xe0,
    0x18, 0xe7, 0x28, 0xd6, 0x4f, 0xe2, 0x10, 0x09, 0xe0, 0x29, 0x95, 0xe3, 0x71, 0x00, 0x09, 0xe0,
    0x82, 0xe3, 0x6f, 0xe3, 0x7f, 0xe6, 0x00, 0x0b, 0xe0, 0x82, 0xe1, 0xbf, 0xe2, 0x35, 0x24, 0x00,
    0x07, 0xe0, 0xe6, 0x3a, 0x24, 0x00, 0x03, 0xeb, 0xb0, 0x09, 0xeb, 0xb1, 0x93, 0x52, 0x40, 0x08,
    0x81, 0x92, 0x7f, 0xe8, 0x10, 0x08, 0x82, 0xe3, 0x6f, 0xe3, 0x7f, 0xe6, 0x00, 0x0a, 0x82, 0xe1,
    0xbf, 0xe2, 0x35, 0x24, 0x00, 0x09, 0x91, 0xe0, 0x68, 0x63, 0x10, 0x08, 0x95, 0xd5, 0x76, 0x80,
    0x04, 0x95, 0x24, 0x08, 0x92, 0xd1, 0x24, 0x10, 0x0a, 0x92, 0xd1, 0x3a, 0x54, 0xc0, 0x08, 0x9b,
    0xcc, 0x19, 0x30, 0x08, 0x9b, 0xe0, 0xe0, 0x28, 0x30, 0x07, 0x9f, 0xe4, 0x53, 0xe2, 0xa0, 0x0a,
    0x3a, 0x64, 0xe9, 0x0f, 0xe6, 0x2b, 0x00, 0x07, 0x3a, 0x64, 0xe9, 0x90, 0x04, 0x3a, 0x10, 0x06,
    0x3a, 0x54, 0xe9, 0x00, 0x07, 0x3a, 0x2b, 0xca, 0x00, 0x08, 0x3a, 0x2b, 0xca, 0x30, 0x08, 0x3a,
    0x82, 0xbc, 0xa0, 0x04, 0x35, 0x24, 0x08, 0xb7, 0x35, 0xe0, 0x71, 0x00, 0x0b, 0xb4, 0xe1, 0x18,
    0x93, 0x64, 0xe1, 0x00, 0x07, 0xbf, 0xe0, 0xe1, 0x63, 0x10, 0x07, 0xbf, 0xe0, 0xe0, 0x28, 0x30,
    0x0b, 0xe8, 0x67, 0x5f, 0xe1, 0x63, 0x52, 0x40, 0x08, 0xe8, 0x18, 0x95, 0x24, 0x00, 0x07, 0xe4,
    0x69, 0x4f, 0xe5, 0x30, 0x06, 0xe4, 0xa5, 0xe2, 0xa0, 0x04, 0xe4, 0xaf, 0xe6, 0x00, 0x08, 0xe4,
    0x53, 0xa2, 0xb3, 0x00, 0x06, 0xe4, 0x24, 0xe5, 0x30, 0x09, 0xe4, 0x28, 0xe9, 0xe7, 0x72, 0xe4,
    0x00, 0x06, 0xe4, 0x28, 0x91, 0x00, 0x06, 0xe6, 0x3a, 0x24, 0x00
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
    { 32, 49, 0, 'r' },
    { 49, 32, 0, 'r' },
    { 454, 461, 9, 'n' },
    { 461, 454, 9, 't' },
    { 783, 791, 5, 's' },
    { 791, 783, 5, 'u' }
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
    if (magic_context_key_emitted) {
        tap_code16(KC_BSPC);
    }
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

static bool repeat_magic_key(uint16_t keycode) {
    switch (keycode) {
case MAGIC_A: return repeat_last_magic_key(MAGIC_A);
case MAGIC_B: return repeat_last_magic_key(MAGIC_B);
case MAGIC_C: return repeat_last_magic_key(MAGIC_C);
case MAGIC_D: return repeat_last_magic_key(MAGIC_D);
case MAGIC_E: return repeat_last_magic_key(MAGIC_E);
case MAGIC_F: return repeat_last_magic_key(MAGIC_F);
case MAGIC_G: return repeat_last_magic_key(MAGIC_G);
case MAGIC_H: return repeat_last_magic_key(MAGIC_H);
case MAGIC_I: return repeat_last_magic_key(MAGIC_I);
case MAGIC_J: return repeat_last_magic_key(MAGIC_J);
case MAGIC_K: return repeat_last_magic_key(MAGIC_K);
    default:
        return false;
    }
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
    if (magic_context_key_emitted) {
        tap_code16(KC_BSPC);
    }
    magic_decode_send_cap(offset, suffix);
}

static void magic_tap_repeatable(uint16_t keycode) {
    tap_code16(keycode);
    magic_remembered_keycode = keycode;
    magic_repeat_keycode = keycode;
}

static inline void magic_replace_tap_repeatable(uint16_t keycode) {
    if (magic_context_key_emitted) {
        tap_code16(KC_BSPC);
    }
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

static uint32_t magic_context_bit(uint16_t keycode) {
    switch (keycode) {
case KC_A: return UINT32_C(1) << 0;
case KC_B: return UINT32_C(1) << 1;
case KC_C: return UINT32_C(1) << 2;
case KC_COMMA: return UINT32_C(1) << 3;
case KC_D: return UINT32_C(1) << 4;
case KC_E: return UINT32_C(1) << 5;
case KC_ENT: return UINT32_C(1) << 6;
case KC_F: return UINT32_C(1) << 7;
case KC_G: return UINT32_C(1) << 8;
case KC_H: return UINT32_C(1) << 9;
case KC_I: return UINT32_C(1) << 10;
case KC_K: return UINT32_C(1) << 11;
case KC_L: return UINT32_C(1) << 12;
case KC_M: return UINT32_C(1) << 13;
case KC_N: return UINT32_C(1) << 14;
case KC_O: return UINT32_C(1) << 15;
case KC_P: return UINT32_C(1) << 16;
case KC_R: return UINT32_C(1) << 17;
case KC_S: return UINT32_C(1) << 18;
case KC_SPC: return UINT32_C(1) << 19;
case KC_T: return UINT32_C(1) << 20;
case KC_TAB: return UINT32_C(1) << 21;
case KC_U: return UINT32_C(1) << 22;
case KC_V: return UINT32_C(1) << 23;
case KC_W: return UINT32_C(1) << 24;
case KC_X: return UINT32_C(1) << 25;
case KC_Y: return UINT32_C(1) << 26;
    default:
        return 0;
    }
}

static bool has_magic_key_with_context(uint16_t keycode, uint16_t context_keycode) {
    uint32_t context_bit = magic_context_bit(unshift_letter_keycode(context_keycode));
    if (context_bit == 0) {
        return false;
    }
    switch (keycode) {
case MAGIC_A: return (UINT32_C(0x3977996) & context_bit) != 0;
case MAGIC_B: return (UINT32_C(0x3977996) & context_bit) != 0;
case MAGIC_C: return (UINT32_C(0x4488621) & context_bit) != 0;
case MAGIC_D: return (UINT32_C(0x3977996) & context_bit) != 0;
case MAGIC_E: return (UINT32_C(0x3977986) & context_bit) != 0;
case MAGIC_F: return (UINT32_C(0x3177914) & context_bit) != 0;
case MAGIC_G: return (UINT32_C(0x44a8621) & context_bit) != 0;
case MAGIC_H: return (UINT32_C(0x3bf79de) & context_bit) != 0;
case MAGIC_I: return (UINT32_C(0x3bf79de) & context_bit) != 0;
case MAGIC_J: return (UINT32_C(0x3977996) & context_bit) != 0;
case MAGIC_K: return (UINT32_C(0x3977916) & context_bit) != 0;
    default:
        return false;
    }
}

static bool has_reverse_magic_key_with_context(uint16_t keycode, uint16_t context_keycode) {
    uint32_t context_bit = magic_context_bit(unshift_letter_keycode(context_keycode));
    if (context_bit == 0) {
        return false;
    }
    switch (keycode) {
case MAGIC_A: return (UINT32_C(0x3020080) & context_bit) != 0;
case MAGIC_B: return (UINT32_C(0x820884) & context_bit) != 0;
case MAGIC_C: return (UINT32_C(0x480200) & context_bit) != 0;
case MAGIC_D: return (UINT32_C(0x2960984) & context_bit) != 0;
case MAGIC_E: return (UINT32_C(0x3025982) & context_bit) != 0;
case MAGIC_F: return (UINT32_C(0x3105804) & context_bit) != 0;
case MAGIC_G: return (UINT32_C(0x40a0000) & context_bit) != 0;
case MAGIC_H: return (UINT32_C(0x2827802) & context_bit) != 0;
case MAGIC_I: return (UINT32_C(0x824004) & context_bit) != 0;
case MAGIC_J: return (UINT32_C(0x920004) & context_bit) != 0;
case MAGIC_K: return (UINT32_C(0x2830104) & context_bit) != 0;
    default:
        return false;
    }
}

static uint16_t magic_combo_component_bit(uint16_t keycode) {
    switch (keycode) {
case DEAD1: return UINT16_C(1) << 0;
case KC_A: return UINT16_C(1) << 1;
case KC_E: return UINT16_C(1) << 2;
case KC_ESC: return UINT16_C(1) << 3;
case KC_H: return UINT16_C(1) << 4;
case KC_I: return UINT16_C(1) << 5;
case KC_O: return UINT16_C(1) << 6;
case KC_S: return UINT16_C(1) << 7;
case KC_U: return UINT16_C(1) << 8;
case KC_Y: return UINT16_C(1) << 9;
case MAGIC_A: return UINT16_C(1) << 10;
case MAGIC_B: return UINT16_C(1) << 11;
case MO(_LEFT): return UINT16_C(1) << 12;
case MO(_RIGHT): return UINT16_C(1) << 13;
    default:
        return 0;
    }
}

static bool is_magic_combo_component_for(uint16_t keycode, uint16_t component_keycode) {
    uint16_t component_bit = magic_combo_component_bit(component_keycode);
    if (component_bit == 0) {
        return false;
    }
    switch (keycode) {
case MAGIC_A: return (UINT16_C(0x0) & component_bit) != 0;
case MAGIC_B: return (UINT16_C(0x0) & component_bit) != 0;
case MAGIC_C: return (UINT16_C(0x88) & component_bit) != 0;
case MAGIC_D: return (UINT16_C(0x404) & component_bit) != 0;
case MAGIC_E: return (UINT16_C(0x820) & component_bit) != 0;
case MAGIC_F: return (UINT16_C(0x11) & component_bit) != 0;
case MAGIC_G: return (UINT16_C(0x2080) & component_bit) != 0;
case MAGIC_H: return (UINT16_C(0x102) & component_bit) != 0;
case MAGIC_I: return (UINT16_C(0x44) & component_bit) != 0;
case MAGIC_J: return (UINT16_C(0x220) & component_bit) != 0;
case MAGIC_K: return (UINT16_C(0x1010) & component_bit) != 0;
    default:
        return false;
    }
}

static bool process_magic_key_with_context(uint16_t keycode, uint16_t context_keycode,
                                           bool allow_repeat, bool context_emitted) {
    magic_context_key_emitted = context_emitted;
    switch (keycode) {
        case MAGIC_A: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_A)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_A;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_decode_send_suffix_cycle(56, 'd', UINT16_MAX); /* emits "ackground " -> "background " */ break;
                case KC_C: magic_tap_repeatable(KC_N); break;
                case KC_D: magic_tap_repeatable(KC_C); break;
                case KC_F: magic_replace_decode_send_cap_cycle(197, 'g', UINT16_MAX); /* emits "confusing " */ break;
                case KC_G: magic_decode_send_suffix_cycle(514, 'l', UINT16_MAX); /* emits "lobal " -> "global " */ break;
                case KC_K: magic_tap_repeatable(KC_R); break;
                case KC_L: magic_tap_repeatable(KC_M); break;
                case KC_M: magic_tap_repeatable(KC_R); break;
                case KC_N: magic_tap_repeatable(KC_R); break;
                case KC_P: magic_tap_repeatable(KC_Y); break;
                case KC_R: magic_replace_tap_repeatable(KC_DQUO); break;
                case KC_S: magic_decode_send_suffix_cycle(619, 'e', UINT16_MAX); /* emits "omeone " -> "someone " */ break;
                case KC_T: magic_tap_repeatable(KC_N); break;
                case KC_V: magic_decode_send_suffix_cycle(72, 'n', UINT16_MAX); /* emits "alidation " -> "validation " */ break;
                case KC_W: magic_replace_decode_send_cap_cycle(86, 's', UINT16_MAX); /* emits "always " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(329, 'n', UINT16_MAX); /* emits "exception " */ break;
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
                case KC_B: magic_decode_send_suffix_cycle(120, 'y', UINT16_MAX); /* emits "asically " -> "basically " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(14, '\0', UINT16_MAX); /* emits "'ll " */ break;
                case KC_D: magic_tap_repeatable(KC_H); break;
                case KC_F: magic_replace_decode_send_cap_cycle(190, 't', UINT16_MAX); /* emits "conflict " */ break;
                case KC_G: magic_tap_repeatable(KC_F); break;
                case KC_K: magic_replace_decode_send_cap_cycle(713, 'n', UINT16_MAX); /* emits "question " */ break;
                case KC_L: magic_tap_repeatable(KC_H); break;
                case KC_M: magic_tap_repeatable(KC_H); break;
                case KC_N: magic_tap_repeatable(KC_H); break;
                case KC_P: magic_tap_repeatable(KC_M); break;
                case KC_R: magic_replace_tap_repeatable(KC_Q); break;
                case KC_S: magic_tap_repeatable(KC_R); break;
                case KC_T: magic_tap_repeatable(KC_F); break;
                case KC_V: magic_replace_decode_send_cap_cycle(307, 'g', UINT16_MAX); /* emits "everything " */ break;
                case KC_W: magic_decode_send_suffix_cycle(128, 't', UINT16_MAX); /* emits "asn't " -> "wasn't " */ break;
                case KC_X: magic_tap_repeatable(KC_W); break;
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
                case KC_A: magic_decode_send_suffix_cycle(204, 's', UINT16_MAX); /* emits "ddress " -> "address " */ break;
                case KC_E: magic_tap_repeatable(KC_U); break;
                case KC_H: magic_replace_decode_send_cap_cycle(710, 'u', UINT16_MAX); /* emits "qu " */ break;
                case KC_I: magic_decode_send_suffix_cycle(544, 't', 454); /* emits "mplement " -> "implement " */ break;
                case KC_O: magic_tap_repeatable(KC_E); break;
                case KC_SPC: magic_replace_decode_send_cap(29, '\0'); /* emits ". " */ add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state(); break;
                case KC_U: magic_replace_decode_send_cap_cycle(397, '\0', UINT16_MAX); /* emits "gregor" */ break;
                case KC_Y: magic_tap_repeatable(KC_R); break;
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
                case KC_B: magic_decode_send_suffix_cycle(256, 'e', UINT16_MAX); /* emits "ecome " -> "become " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(562, '\0', UINT16_MAX); /* emits "n't " */ break;
                case KC_D: magic_decode_send_suffix_cycle(635, 't', UINT16_MAX); /* emits "on't " -> "don't " */ break;
                case KC_F: magic_replace_decode_send_cap_cycle(670, 'e', UINT16_MAX); /* emits "performance " */ break;
                case KC_G: magic_replace_decode_send_cap_cycle(644, 'e', UINT16_MAX); /* emits "organize " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(799, 'k', UINT16_MAX); /* emits "think " */ break;
                case KC_L: magic_decode_send_suffix_cycle(96, 'e', UINT16_MAX); /* emits "anguage " -> "language " */ break;
                case KC_M: magic_decode_send_suffix_cycle(439, 'n', UINT16_MAX); /* emits "igration " -> "migration " */ break;
                case KC_N: magic_decode_send_suffix_cycle(302, 'r', UINT16_MAX); /* emits "ever " -> "never " */ break;
                case KC_P: magic_decode_send_suffix_cycle(286, 'e', UINT16_MAX); /* emits "eople " -> "people " */ break;
                case KC_R: magic_replace_decode_send_cap_cycle(558, '\0', UINT16_MAX); /* emits "n't" */ break;
                case KC_S: magic_replace_decode_send_cap_cycle(679, 'e', UINT16_MAX); /* emits "possible " */ break;
                case KC_T: magic_replace_decode_send_cap_cycle(494, 't', UINT16_MAX); /* emits "just " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(470, 'e', UINT16_MAX); /* emits "improve " */ break;
                case KC_W: magic_decode_send_suffix_cycle(650, 'w', UINT16_MAX); /* emits "orkflow " -> "workflow " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(322, 't', UINT16_MAX); /* emits "except " */ break;
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
                case KC_B: magic_replace_decode_send_cap_cycle(579, 'y', UINT16_MAX); /* emits "observability " */ break;
                case KC_C: magic_tap_repeatable(KC_D); break;
                case KC_F: magic_replace_decode_send_cap_cycle(228, 'e', UINT16_MAX); /* emits "disable " */ break;
                case KC_G: magic_replace_decode_send_cap_cycle(179, 'e', UINT16_MAX); /* emits "change " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(522, 'd', UINT16_MAX); /* emits "merged " */ break;
                case KC_L: magic_replace_decode_send_cap_cycle(79, 'y', UINT16_MAX); /* emits "already " */ break;
                case KC_M: magic_decode_send_suffix_cycle(822, 'e', UINT16_MAX); /* emits "ultiple " -> "multiple " */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(106, 'g', UINT16_MAX); /* emits "anything " */ break;
                case KC_P: magic_decode_send_suffix_cycle(725, 'y', UINT16_MAX); /* emits "robably " -> "probably " */ break;
                case KC_R: magic_replace_tap_repeatable(KC_QUES); break;
                case KC_S: magic_decode_send_suffix_cycle(842, 't', UINT16_MAX); /* emits "upport " -> "support " */ break;
                case KC_T: magic_decode_send_suffix_cycle(414, 'h', UINT16_MAX); /* emits "hrough " -> "through " */ break;
                case KC_V: magic_decode_send_suffix_cycle(297, 'n', UINT16_MAX); /* emits "ersion " -> "version " */ break;
                case KC_W: magic_replace_decode_send_cap_cycle(657, 'e', UINT16_MAX); /* emits "otherwise " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(357, 't', UINT16_MAX); /* emits "explicit " */ break;
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
                case KC_C: magic_replace_decode_send_cap_cycle(25, '\0', UINT16_MAX); /* emits "'ve " */ break;
                case KC_D: magic_decode_send_suffix_cycle(429, 'y', UINT16_MAX); /* emits "ifficulty " -> "difficulty " */ break;
                case KC_G: magic_decode_send_suffix_cycle(273, 'l', UINT16_MAX); /* emits "eneral " -> "general " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(791, 's', 791); /* emits "thanks " */ break;
                case KC_L: magic_replace_decode_send_cap_cycle(133, 'e', UINT16_MAX); /* emits "available " */ break;
                case KC_M: magic_decode_send_suffix_cycle(488, 'h', UINT16_MAX); /* emits "ismatch " -> "mismatch " */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(350, 'n', UINT16_MAX); /* emits "explain " */ break;
                case KC_P: magic_decode_send_suffix_cycle(902, 'n', UINT16_MAX); /* emits "ython " -> "python " */ break;
                case KC_R: magic_tap_repeatable(KC_X); break;
                case KC_S: magic_decode_send_suffix_cycle(445, 'r', UINT16_MAX); /* emits "imilar " -> "similar " */ break;
                case KC_T: magic_replace_decode_send_cap_cycle(101, 'r', UINT16_MAX); /* emits "another " */ break;
                case KC_W: magic_replace_decode_send_cap_cycle(777, 'h', UINT16_MAX); /* emits "switch " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(345, 't', UINT16_MAX); /* emits "exit " */ break;
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
                case KC_H: magic_tap_repeatable(KC_Y); break;
                case KC_I: magic_decode_send(540); /* emits "mpl" -> "impl" */ break;
                case KC_O: magic_tap_repeatable(KC_H); break;
                case KC_R: magic_replace_tap_repeatable(KC_EXLM); break;
                case KC_SPC: magic_replace_tap_repeatable(KC_Z); break;
                case KC_U: magic_tap_repeatable(KC_H); break;
                case KC_Y: magic_replace_decode_send_cap_cycle(639, 'y', UINT16_MAX); /* emits "only " */ break;
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
                case KC_B: magic_replace_decode_send_cap_cycle(591, 'e', UINT16_MAX); /* emits "obsolete " */ break;
                case KC_C: magic_decode_send_suffix_cycle(630, 't', UINT16_MAX); /* emits "omment " -> "comment " */ break;
                case KC_COMMA: magic_decode_send_cap_cycle(5, '\0', UINT16_MAX); /* emits " but " */ break;
                case KC_D: magic_decode_send_suffix_cycle(423, 't', UINT16_MAX); /* emits "idn't " -> "didn't " */ break;
                case KC_ENT: magic_decode_send_cap_cycle(796, 'e', UINT16_MAX); /* emits "the " */ break;
                case KC_F: magic_decode_send_suffix_cycle(598, 'd', UINT16_MAX); /* emits "ocused " -> "focused " */ break;
                case KC_G: magic_decode_send_suffix_cycle(278, 'e', UINT16_MAX); /* emits "enerate " -> "generate " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(836, 'e', UINT16_MAX); /* emits "update " */ break;
                case KC_L: magic_replace_decode_send_cap_cycle(266, 'e', UINT16_MAX); /* emits "elaborate " */ break;
                case KC_M: magic_replace_decode_send_cap_cycle(476, 'n', UINT16_MAX); /* emits "instrumentation " */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(828, 'd', UINT16_MAX); /* emits "understand " */ break;
                case KC_P: magic_decode_send_suffix_cycle(733, 'n', UINT16_MAX); /* emits "roduction " -> "production " */ break;
                case KC_R: magic_replace_tap_repeatable(KC_QUOTE); break;
                case KC_S: magic_decode_send_suffix_cycle(291, 'e', UINT16_MAX); /* emits "eparate " -> "separate " */ break;
                case KC_SPC: magic_decode_send_cap_cycle(796, 'e', UINT16_MAX); /* emits "the " */ break;
                case KC_T: magic_decode_send_suffix_cycle(405, 'h', UINT16_MAX); /* emits "hough " -> "though " */ break;
                case KC_TAB: magic_decode_send_cap_cycle(796, 'e', UINT16_MAX); /* emits "the " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(112, 'l', UINT16_MAX); /* emits "approval " */ break;
                case KC_W: magic_decode_send_suffix_cycle(419, 'y', UINT16_MAX); /* emits "hy " -> "why " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(338, 'e', UINT16_MAX); /* emits "exclude " */ break;
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
                case KC_B: magic_decode_send_suffix_cycle(250, 'e', UINT16_MAX); /* emits "ecause " -> "because " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(18, '\0', UINT16_MAX); /* emits "'re " */ break;
                case KC_COMMA: magic_decode_send_cap_cycle(0, '\0', UINT16_MAX); /* emits " and " */ break;
                case KC_D: magic_decode_send_suffix_cycle(608, 't', UINT16_MAX); /* emits "oesn't " -> "doesn't " */ break;
                case KC_ENT: magic_decode_send_cap_cycle(92, 'd', UINT16_MAX); /* emits "and " */ break;
                case KC_F: magic_decode_send_suffix_cycle(613, 'g', UINT16_MAX); /* emits "ollowing " -> "following " */ break;
                case KC_G: magic_tap_repeatable(KC_K); break;
                case KC_K: magic_decode_send_suffix_cycle(575, 'w', UINT16_MAX); /* emits "now " -> "know " */ break;
                case KC_L: magic_tap_repeatable(KC_R); break;
                case KC_M: magic_decode_send(283); /* emits "ent" -> "ment" */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(884, 't', UINT16_MAX); /* emits "won't " */ break;
                case KC_P: magic_tap_repeatable(KC_N); break;
                case KC_R: magic_replace_tap_repeatable(KC_COMMA); break;
                case KC_S: magic_decode_send(485); /* emits "ion" -> "sion" */ break;
                case KC_SPC: magic_decode_send_cap_cycle(92, 'd', UINT16_MAX); /* emits "and " */ break;
                case KC_T: magic_decode_send(485); /* emits "ion" -> "tion" */ break;
                case KC_TAB: magic_decode_send_cap_cycle(92, 'd', UINT16_MAX); /* emits "and " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(719, 'e', UINT16_MAX); /* emits "resolve " */ break;
                case KC_W: magic_tap_repeatable(KC_S); break;
                case KC_X: magic_tap_repeatable(KC_R); break;
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
                case KC_K: magic_tap_repeatable(KC_X); break;
                case KC_L: magic_tap_repeatable(KC_C); break;
                case KC_M: magic_tap_repeatable(KC_L); break;
                case KC_N: magic_tap_repeatable(KC_X); break;
                case KC_P: magic_tap_repeatable(KC_D); break;
                case KC_R: magic_replace_tap_repeatable(KC_DOT); break;
                case KC_S: magic_tap_repeatable(KC_D); break;
                case KC_T: magic_replace_decode_send_cap_cycle(878, 't', UINT16_MAX); /* emits "without " */ break;
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
                case KC_B: magic_decode_send_suffix_cycle(261, 'e', UINT16_MAX); /* emits "efore " -> "before " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(22, '\0', UINT16_MAX); /* emits "'s " */ break;
                case KC_D: magic_decode_send_suffix_cycle(605, 's', UINT16_MAX); /* emits "oes " -> "does " */ break;
                case KC_G: magic_replace_decode_send_cap_cycle(766, 't', UINT16_MAX); /* emits "suggest " */ break;
                case KC_K: magic_decode_send_suffix_cycle(571, 'w', UINT16_MAX); /* emits "new " -> "knew " */ break;
                case KC_L: magic_tap_repeatable(KC_B); break;
                case KC_M: magic_tap_repeatable(KC_T); break;
                case KC_N: magic_tap_repeatable(KC_P); break;
                case KC_P: magic_replace_decode_send_cap_cycle(42, 's', UINT16_MAX); /* emits "Prometheus " */ break;
                case KC_R: magic_replace_tap_repeatable(KC_J); break;
                case KC_S: magic_decode_send_suffix_cycle(624, 'g', UINT16_MAX); /* emits "omething " -> "something " */ break;
                case KC_T: magic_decode_send_suffix_cycle(409, 't', UINT16_MAX); /* emits "hought " -> "thought " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(897, 'e', UINT16_MAX); /* emits "worse " */ break;
                case KC_W: magic_decode_send_suffix_cycle(401, 'h', UINT16_MAX); /* emits "hich " -> "which " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(315, 'e', UINT16_MAX); /* emits "example " */ break;
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
            if (!process_magic_key_with_context(keycode, last_keycode, true, true)) {
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
