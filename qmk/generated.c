/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;

static bool magic_capitalize_next = false;

// Magic string decoder lookup tables
static const char magic_char_4bit[] = {
    ' ', 'e', 'o', 'n', 't', 'i', 'a', 'r', 'l', 's', 'u', 'g', 'c', 'h'
};

static const char magic_char_extended[] = {
    'p', 'm', 'd', 'f', 'b', 'y', 'w', '\'', 'v', 'k', 'x', 'q', 'z', '.', 'G', 'Z', 'I', 'O', 'T', 'P', 'S', 'B', 'j'
};

static const uint8_t magic_string_data[] = {
    0x02, 0xe7, 0xe2, 0x03, 0xe7, 0x88, 0x03, 0xe7, 0x71, 0x02, 0xe7, 0x90, 0x03, 0xe7, 0xe8, 0x10,
    0x02, 0xed, 0x00, 0x11, 0xee, 0x71, 0xb2, 0x70, 0xef, 0x15, 0x48, 0x53, 0xb1, 0x70, 0x05, 0xf0,
    0xe7, 0xe8, 0x10, 0x0e, 0xf1, 0xe0, 0x13, 0xf2, 0x18, 0x1f, 0xe1, 0x14, 0x7f, 0xe5, 0x00, 0x0b,
    0xf3, 0x72, 0xe1, 0x14, 0xd1, 0xa9, 0x00, 0x0c, 0xf4, 0xe0, 0x75, 0x3b, 0x0f, 0xf5, 0x22, 0x40,
    0x0a, 0x6c, 0xe9, 0xb7, 0x2a, 0x3f, 0xe2, 0x00, 0x09, 0x6f, 0xe2, 0x6f, 0xe0, 0x45, 0xe8, 0x10,
    0x0a, 0x68, 0x5f, 0xe2, 0x64, 0x52, 0x30, 0x08, 0x68, 0x71, 0x6f, 0xe2, 0xe5, 0x00, 0x07, 0x68,
    0xe6, 0x6f, 0xe5, 0x90, 0x04, 0x63, 0xe2, 0x00, 0x08, 0x63, 0xba, 0x6b, 0x10, 0x08, 0x63, 0x24,
    0xd1, 0x70, 0x09, 0x63, 0xe5, 0x4d, 0x53, 0xb0, 0x09, 0x6f, 0xe0, 0xe0, 0x72, 0xe8, 0x68, 0x00,
    0x09, 0x69, 0x5c, 0x68, 0x8f, 0xe5, 0x00, 0x06, 0x69, 0x3f, 0xe7, 0x40, 0x0a, 0x6f, 0xe8, 0x65,
    0x86, 0xe4, 0x81, 0x00, 0x0b, 0xe4, 0x6c, 0xe9, 0xb7, 0x2a, 0x3f, 0xe2, 0x00, 0x0a, 0xe4, 0x69,
    0x5c, 0x68, 0x8f, 0xe5, 0x00, 0x08, 0xe4, 0x1c, 0x6a, 0x91, 0x00, 0x07, 0xe4, 0x1c, 0x2f, 0xe1,
    0x10, 0x07, 0xe4, 0x1f, 0xe3, 0x27, 0x10, 0x07, 0xe4, 0x1d, 0x53, 0xe2, 0x00, 0x08, 0xc2, 0xe1,
    0xe1, 0x13, 0x40, 0x09, 0xc2, 0x3f, 0xe3, 0x85, 0xc4, 0x00, 0x0a, 0xc2, 0x3f, 0xe3, 0xa9, 0x53,
    0xb0, 0x09, 0xc2, 0x39, 0xaf, 0xe1, 0x17, 0x00, 0x0a, 0xc2, 0x34, 0x65, 0x31, 0x70, 0x09, 0xc2,
    0x34, 0x53, 0xa1, 0x00, 0x13, 0xe2, 0x1c, 0x86, 0x76, 0x45, 0xe8, 0x10, 0xc2, 0x3f, 0xe3, 0x5b,
    0x00, 0x08, 0xe2, 0x1f, 0xe3, 0x6a, 0x84, 0x00, 0x07, 0xe2, 0x5f, 0xe2, 0x3f, 0xe7, 0x40, 0x0a,
    0xe2, 0x5f, 0xe3, 0xe3, 0x17, 0x13, 0x40, 0x0b, 0xe2, 0x5f, 0xe3, 0xe3, 0x5c, 0xa8, 0x4f, 0xe5,
    0x00, 0x08, 0xe2, 0x59, 0x6f, 0xe4, 0x81, 0x00, 0x05, 0xe2, 0x21, 0x90, 0x08, 0xe2, 0x21, 0x93,
    0xe7, 0x40, 0x06, 0xe2, 0x23, 0xe7, 0x40, 0x07, 0x1c, 0x6a, 0x91, 0x00, 0x06, 0x1c, 0x2f, 0xe1,
    0x10, 0x07, 0x1f, 0xe3, 0x6a, 0x84, 0x00, 0x06, 0x1f, 0xe3, 0x27, 0x10, 0x06, 0x1d, 0x53, 0xe2,
    0x00, 0x09, 0x15, 0x48, 0x53, 0xb1, 0x70, 0x0a, 0x18, 0x6f, 0xe4, 0x27, 0x64, 0x10, 0x07, 0x13,
    0x17, 0x68, 0x00, 0x08, 0x13, 0x17, 0x64, 0x10, 0x04, 0x13, 0x40, 0x06, 0x12, 0xe0, 0x81, 0x00,
    0x08, 0x1f, 0xe0, 0x67, 0x64, 0x10, 0x07, 0x17, 0x95, 0x23, 0x00, 0x05, 0x1f, 0xe8, 0x17, 0x00,
    0x0b, 0x1f, 0xe8, 0x17, 0xe5, 0x4d, 0x53, 0xb0, 0x08, 0x1f, 0xea, 0x6f, 0xe1, 0xe0, 0x81, 0x00,
    0x07, 0x1f, 0xea, 0xc1, 0xe0, 0x40, 0x0a, 0x1f, 0xea, 0xc1, 0xe0, 0x45, 0x23, 0x00, 0x08, 0x1f,
    0xea, 0xc8, 0xaf, 0xe2, 0x10, 0x08, 0x1f, 0xea, 0xe0, 0x86, 0x53, 0x00, 0x09, 0x1f, 0xea, 0xe0,
    0x85, 0xc5, 0x40, 0x08, 0xe3, 0x2c, 0xa9, 0x1f, 0xe2, 0x00, 0x0a, 0xe3, 0x28, 0x82, 0xe6, 0x53,
    0xb0, 0x0a, 0xe3, 0x71, 0xeb, 0xa1, 0x3c, 0xe5, 0x00, 0x08, 0xb1, 0x31, 0x76, 0x80, 0x09, 0xb1,
    0x31, 0x76, 0x41, 0x00, 0x07, 0xb5, 0x4d, 0xaf, 0xe4, 0x00, 0x07, 0xb8, 0x2f, 0xe4, 0x68, 0x00,
    0x06, 0xb7, 0x1b, 0x27, 0x05, 0xd5, 0xcd, 0x00, 0x06, 0xd2, 0xab, 0xd0, 0x07, 0xd2, 0xab, 0xd4,
    0x00, 0x07, 0xd7, 0x2a, 0xbd, 0x00, 0x06, 0x5f, 0xe2, 0x3f, 0xe7, 0x40, 0x09, 0x5f, 0xe3, 0xe3,
    0x17, 0x13, 0x40, 0x0a, 0x5f, 0xe3, 0xe3, 0x5c, 0xa8, 0x4f, 0xe5, 0x00, 0x09, 0x5b, 0x76, 0x45,
    0x23, 0x00, 0x07, 0x5f, 0xe1, 0x58, 0x67, 0x00, 0x0a, 0x5f, 0xe1, 0xe0, 0x81, 0xe1, 0x13, 0x40,
    0x0f, 0x5f, 0xe1, 0xe0, 0x81, 0xe1, 0x13, 0x46, 0x45, 0x23, 0x00, 0x08, 0x5f, 0xe1, 0xe0, 0x72,
    0xe8, 0x10, 0x10, 0x53, 0x94, 0x7a, 0xe1, 0x13, 0x46, 0x45, 0x23, 0x00, 0x03, 0x52, 0x30, 0x08,
    0x59, 0xe1, 0x64, 0xcd, 0x00, 0x06, 0x54, 0xda, 0xe4, 0x00, 0x05, 0xf6, 0xa9, 0x40, 0x05, 0xe9,
    0x31, 0xe6, 0x00, 0x05, 0xe9, 0x32, 0xe6, 0x00, 0x09, 0x86, 0x3b, 0xa6, 0xb1, 0x00, 0x06, 0x82,
    0xe4, 0x68, 0x00, 0x05, 0xe1, 0x13, 0x40, 0x07, 0xe1, 0x17, 0xb1, 0xe2, 0x00, 0x0a, 0xe1, 0x5b,
    0x76, 0x45, 0x23, 0x00, 0x09, 0xe1, 0x59, 0xe1, 0x64, 0xcd, 0x00, 0x09, 0xe1, 0xe0, 0x81, 0xe1,
    0x13, 0x40, 0x09, 0xe1, 0xa8, 0x45, 0xe0, 0x81, 0x00, 0x03, 0x3f, 0xe7, 0x40, 0x06, 0x31, 0xe8,
    0x17, 0x00, 0x04, 0x31, 0xe6, 0x00, 0x0e, 0x32, 0x45, 0xe3, 0x5c, 0x64, 0x52, 0x39, 0x00, 0x04,
    0x32, 0xe6, 0x00, 0x0e, 0x2f, 0xe4, 0x91, 0x7f, 0xe8, 0x6f, 0xe4, 0x58, 0x54, 0xe5, 0x00, 0x09,
    0x2f, 0xe4, 0x92, 0x81, 0x41, 0x00, 0x07, 0x2c, 0xa9, 0x1f, 0xe2, 0x00, 0x04, 0x21, 0x90, 0x07,
    0x21, 0x93, 0xe7, 0x40, 0x09, 0x28, 0x82, 0xe6, 0x53, 0xb0, 0x07, 0x2f, 0xe1, 0x12, 0x31, 0x00,
    0x09, 0x2f, 0xe1, 0x14, 0xd5, 0x3b, 0x00, 0x07, 0x2f, 0xe1, 0xe1, 0x13, 0x40, 0x05, 0x23, 0xe7,
    0x40, 0x05, 0x23, 0x8f, 0xe5, 0x00, 0x09, 0x23, 0x46, 0x53, 0x17, 0x00, 0x09, 0x27, 0xb6, 0x35,
    0xec, 0x10, 0x08, 0x27, 0xe9, 0xe3, 0x82, 0xe6, 0x00, 0x05, 0x27, 0x91, 0x00, 0x0a, 0x24, 0xd1,
    0x7f, 0xe6, 0x59, 0x10, 0x0d, 0x24, 0x5f, 0xe3, 0x5c, 0x64, 0x52, 0x39, 0x00, 0x07, 0xe0, 0x12,
    0xe0, 0x81, 0x00, 0x0c, 0xe0, 0x17, 0xe3, 0x27, 0xe1, 0x63, 0xc1, 0x00, 0x09, 0xe0, 0x29, 0x95,
    0xe4, 0x81, 0x00, 0x09, 0xe0, 0x72, 0xe4, 0x6f, 0xe4, 0x8f, 0xe5, 0x00, 0x0b, 0xe0, 0x72, 0xe2,
    0xac, 0x45, 0x23, 0x00, 0x07, 0xe0, 0xe5, 0x4d, 0x23, 0x00, 0x02, 0xeb, 0xa0, 0x09, 0xeb, 0xa1,
    0x94, 0x52, 0x30, 0x08, 0x71, 0x68, 0x5f, 0xec, 0x10, 0x09, 0x71, 0xeb, 0xa1, 0x3c, 0xe5, 0x00,
    0x08, 0x71, 0x92, 0x8f, 0xe8, 0x10, 0x08, 0x72, 0xe4, 0x6f, 0xe4, 0x8f, 0xe5, 0x00, 0x0a, 0x72,
    0xe2, 0xac, 0x45, 0x23, 0x00, 0x09, 0x91, 0xe0, 0x67, 0x64, 0x10, 0x08, 0x95, 0xe1, 0x58, 0x67,
    0x00, 0x04, 0x95, 0x23, 0x08, 0x92, 0xe1, 0x12, 0x31, 0x00, 0x0a, 0x92, 0xe1, 0x14, 0xd5, 0x3b,
    0x00, 0x08, 0x9a, 0xbb, 0x19, 0x40, 0x08, 0x9a, 0xe0, 0xe0, 0x27, 0x40, 0x07, 0x9f, 0xe6, 0x54,
    0xcd, 0x00, 0x04, 0x4d, 0x10, 0x06, 0x4d, 0x53, 0xe9, 0x00, 0x07, 0x4d, 0x2a, 0xbd, 0x00, 0x08,
    0x4d, 0x2a, 0xbd, 0x40, 0x08, 0x4d, 0x72, 0xab, 0xd0, 0x04, 0x45, 0x23, 0x08, 0xa8, 0x45, 0xe0,
    0x81, 0x00, 0x0b, 0xa3, 0xe2, 0x17, 0x94, 0x63, 0xe2, 0x00, 0x0a, 0xa3, 0x71, 0x86, 0x41, 0xe2,
    0x00, 0x07, 0xaf, 0xe0, 0xe2, 0x64, 0x10, 0x07, 0xaf, 0xe0, 0xe0, 0x27, 0x40, 0x04, 0xa9, 0x40,
    0x0b, 0xe8, 0x68, 0x5f, 0xe2, 0x64, 0x52, 0x30, 0x08, 0xe8, 0x17, 0x95, 0x23, 0x00, 0x07, 0xe6,
    0x69, 0x3f, 0xe7, 0x40, 0x06, 0xe6, 0xd5, 0xcd, 0x00, 0x08, 0xe6, 0x54, 0xd2, 0xa4, 0x00, 0x09,
    0xe6, 0x27, 0xe9, 0xe3, 0x82, 0xe6, 0x00, 0x06, 0xe6, 0x27, 0x91, 0x00, 0x07, 0xea, 0xe0, 0x86,
    0x53, 0x00, 0x06, 0xe5, 0x4d, 0x23, 0x00, 0x0a, 0xec, 0x15, 0x48, 0x53, 0xb1, 0x70
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
    { 520, 528, 9, 'n' },
    { 528, 520, 9, 't' }
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
                    case KC_B: magic_decode_send_suffix_cycle(64, 'd', UINT16_MAX); /* emits "ackground " -> "background " */ break;
                    case KC_C: magic_tap_repeatable(KC_N); break;
                    case KC_D: magic_tap_repeatable(KC_C); break;
                    case KC_F: magic_replace_decode_send_cap_cycle(202, 'g', UINT16_MAX); /* emits "confusing " */ break;
                    case KC_G: magic_decode_send_suffix_cycle(590, 'l', UINT16_MAX); /* emits "lobal " -> "global " */ break;
                    case KC_K: magic_tap_repeatable(KC_R); break;
                    case KC_L: magic_tap_repeatable(KC_M); break;
                    case KC_M: magic_tap_repeatable(KC_R); break;
                    case KC_N: magic_tap_repeatable(KC_R); break;
                    case KC_P: magic_tap_repeatable(KC_Y); break;
                    case KC_S: magic_decode_send_suffix_cycle(698, 'e', UINT16_MAX); /* emits "omeone " -> "someone " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_DQUO); break;
                    case KC_T: magic_tap_repeatable(KC_N); break;
                    case KC_V: magic_decode_send_suffix_cycle(80, 'n', UINT16_MAX); /* emits "alidation " -> "validation " */ break;
                    case KC_W: magic_replace_decode_send_cap_cycle(94, 's', UINT16_MAX); /* emits "always " */ break;
                    case KC_X: magic_replace_decode_send_cap_cycle(390, 'n', UINT16_MAX); /* emits "exception " */ break;
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
                    case KC_B: magic_decode_send_suffix_cycle(316, 'd', UINT16_MAX); /* emits "ehind " -> "behind " */ break;
                    case KC_C: magic_replace_decode_send_cap_cycle(3, '\0', UINT16_MAX); /* emits "'ll" */ break;
                    case KC_D: magic_tap_repeatable(KC_H); break;
                    case KC_F: magic_replace_decode_send_cap_cycle(195, 't', UINT16_MAX); /* emits "conflict " */ break;
                    case KC_G: magic_tap_repeatable(KC_F); break;
                    case KC_K: magic_replace_decode_send_cap_cycle(813, 'n', UINT16_MAX); /* emits "question " */ break;
                    case KC_L: magic_tap_repeatable(KC_H); break;
                    case KC_M: magic_tap_repeatable(KC_H); break;
                    case KC_N: magic_tap_repeatable(KC_H); break;
                    case KC_P: magic_tap_repeatable(KC_M); break;
                    case KC_S: magic_tap_repeatable(KC_R); break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_EXLM); break;
                    case KC_T: magic_tap_repeatable(KC_F); break;
                    case KC_V: magic_replace_decode_send_cap_cycle(368, 'g', UINT16_MAX); /* emits "everything " */ break;
                    case KC_W: magic_decode_send_suffix_cycle(135, 't', UINT16_MAX); /* emits "asn't " -> "wasn't " */ break;
                    case KC_X: magic_tap_repeatable(KC_W); break;
                    case KC_Z: magic_replace_decode_send_cap_cycle(819, 'e', UINT16_MAX); /* emits "realize " */ break;
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
                    case KC_V: magic_replace_decode_send_cap_cycle(228, 'g', UINT16_MAX); /* emits "declarative config " */ break;
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
                    case KC_B: magic_decode_send_suffix_cycle(300, 'e', UINT16_MAX); /* emits "ecome " -> "become " */ break;
                    case KC_C: magic_replace_decode_send_cap_cycle(633, '\0', UINT16_MAX); /* emits "n't" */ break;
                    case KC_D: magic_decode_send_suffix_cycle(717, 't', UINT16_MAX); /* emits "on't " -> "don't " */ break;
                    case KC_F: magic_replace_decode_send_cap_cycle(771, 'e', UINT16_MAX); /* emits "performance " */ break;
                    case KC_G: magic_replace_decode_send_cap_cycle(732, 'e', UINT16_MAX); /* emits "organize " */ break;
                    case KC_K: magic_replace_decode_send_cap_cycle(901, 'k', UINT16_MAX); /* emits "think " */ break;
                    case KC_L: magic_decode_send_suffix_cycle(104, 'e', UINT16_MAX); /* emits "anguage " -> "language " */ break;
                    case KC_M: magic_decode_send_suffix_cycle(508, 'n', UINT16_MAX); /* emits "igration " -> "migration " */ break;
                    case KC_N: magic_decode_send_suffix_cycle(363, 'r', UINT16_MAX); /* emits "ever " -> "never " */ break;
                    case KC_P: magic_decode_send_suffix_cycle(347, 'e', UINT16_MAX); /* emits "eople " -> "people " */ break;
                    case KC_S: magic_replace_decode_send_cap_cycle(780, 'e', UINT16_MAX); /* emits "possible " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_QUOTE); break;
                    case KC_T: magic_replace_decode_send_cap_cycle(72, 'e', UINT16_MAX); /* emits "adaptive " */ break;
                    case KC_V: magic_replace_decode_send_cap_cycle(12, '\0', UINT16_MAX); /* emits "'ve" */ break;
                    case KC_W: magic_decode_send_suffix_cycle(738, 'w', UINT16_MAX); /* emits "orkflow " -> "workflow " */ break;
                    case KC_X: magic_replace_decode_send_cap_cycle(384, 't', UINT16_MAX); /* emits "except " */ break;
                    case KC_Z: magic_replace_decode_send_cap_cycle(464, '\0', UINT16_MAX); /* emits "gregor" */ break;
                    default: magic_decode_send(810); /* emits "qu" */ break;
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
                    case KC_B: magic_replace_decode_send_cap_cycle(659, 'y', UINT16_MAX); /* emits "observability " */ break;
                    case KC_C: magic_tap_repeatable(KC_D); break;
                    case KC_D: magic_decode_send_suffix_cycle(305, 't', UINT16_MAX); /* emits "efault " -> "default " */ break;
                    case KC_E: magic_replace_decode_send_cap_cycle(109, 'r', UINT16_MAX); /* emits "another " */ break;
                    case KC_F: magic_decode_send_suffix_cycle(825, 'y', UINT16_MAX); /* emits "requency " -> "frequency " */ break;
                    case KC_G: magic_decode_send_suffix_cycle(565, 'b', UINT16_MAX); /* emits "ithub " -> "github " */ break;
                    case KC_K: magic_replace_decode_send_cap_cycle(599, 'd', UINT16_MAX); /* emits "merged " */ break;
                    case KC_L: magic_replace_decode_send_cap_cycle(87, 'y', UINT16_MAX); /* emits "already " */ break;
                    case KC_M: magic_decode_send_suffix_cycle(924, 'e', UINT16_MAX); /* emits "ultiple " -> "multiple " */ break;
                    case KC_N: magic_replace_decode_send_cap_cycle(114, 'g', UINT16_MAX); /* emits "anything " */ break;
                    case KC_P: magic_decode_send_suffix_cycle(838, 'y', UINT16_MAX); /* emits "robably " -> "probably " */ break;
                    case KC_S: magic_decode_send_suffix_cycle(951, 't', UINT16_MAX); /* emits "upport " -> "support " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_QUES); break;
                    case KC_T: magic_decode_send_suffix_cycle(481, 'h', UINT16_MAX); /* emits "hrough " -> "through " */ break;
                    case KC_V: magic_decode_send_suffix_cycle(358, 'n', UINT16_MAX); /* emits "ersion " -> "version " */ break;
                    case KC_W: magic_replace_decode_send_cap_cycle(749, 'e', UINT16_MAX); /* emits "otherwise " */ break;
                    case KC_X: magic_replace_decode_send_cap_cycle(412, 't', UINT16_MAX); /* emits "explicit " */ break;
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
                    case KC_B: magic_replace_decode_send_cap_cycle(273, 'e', UINT16_MAX); /* emits "disable " */ break;
                    case KC_C: magic_decode_send_suffix_cycle(726, 'r', UINT16_MAX); /* emits "ontainer " -> "container " */ break;
                    case KC_D: magic_decode_send_suffix_cycle(492, 't', UINT16_MAX); /* emits "ifferent " -> "different " */ break;
                    case KC_ENT: magic_decode_send_cap_cycle(100, 'd', UINT16_MAX); /* emits "and " */ break;
                    case KC_G: magic_decode_send_suffix_cycle(334, 'l', UINT16_MAX); /* emits "eneral " -> "general " */ break;
                    case KC_L: magic_replace_decode_send_cap_cycle(140, 'e', UINT16_MAX); /* emits "available " */ break;
                    case KC_M: magic_decode_send_suffix_cycle(559, 'h', UINT16_MAX); /* emits "ismatch " -> "mismatch " */ break;
                    case KC_P: magic_decode_send_suffix_cycle(1010, 'n', UINT16_MAX); /* emits "ython " -> "python " */ break;
                    case KC_S: magic_decode_send_suffix_cycle(514, 'r', UINT16_MAX); /* emits "imilar " -> "similar " */ break;
                    case KC_SPC: magic_decode_send_cap_cycle(100, 'd', UINT16_MAX); /* emits "and " */ break;
                    case KC_TAB: magic_decode_send_cap_cycle(100, 'd', UINT16_MAX); /* emits "and " */ break;
                    case KC_W: magic_replace_decode_send_cap_cycle(892, 'h', UINT16_MAX); /* emits "switch " */ break;
                    case KC_Z: magic_replace_decode_send_cap_cycle(19, '\0', UINT16_MAX); /* emits "Gregor Zeitlinger" */ break;
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
                    case KC_B: magic_decode_send_suffix_cycle(128, 'y', UINT16_MAX); /* emits "asically " -> "basically " */ break;
                    case KC_D: magic_decode_send_suffix_cycle(499, 'y', UINT16_MAX); /* emits "ifficulty " -> "difficulty " */ break;
                    case KC_E: magic_tap_repeatable(KC_H); break;
                    case KC_I: magic_decode_send_suffix_cycle(619, 't', 520); /* emits "mplement " -> "implement " */ break;
                    case KC_J: magic_decode_send_suffix_cycle(957, 't', UINT16_MAX); /* emits "ust " -> "just " */ break;
                    case KC_L: magic_replace_decode_send_cap_cycle(938, 'd', UINT16_MAX); /* emits "unrelated " */ break;
                    case KC_N: magic_decode_send_suffix_cycle(756, 's', UINT16_MAX); /* emits "otifications " -> "notifications " */ break;
                    case KC_O: magic_tap_repeatable(KC_H); break;
                    case KC_P: magic_replace_decode_send_cap_cycle(539, 'e', UINT16_MAX); /* emits "improve " */ break;
                    case KC_S: magic_replace_decode_send_cap_cycle(209, 'r', UINT16_MAX); /* emits "consumer " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_Z); break;
                    case KC_T: magic_replace_decode_send_cap_cycle(222, 'e', UINT16_MAX); /* emits "continue " */ break;
                    case KC_U: magic_tap_repeatable(KC_H); break;
                    case KC_Y: magic_replace_decode_send_cap_cycle(721, 'y', UINT16_MAX); /* emits "only " */ break;
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
                    case KC_B: magic_replace_decode_send_cap_cycle(671, 'e', UINT16_MAX); /* emits "obsolete " */ break;
                    case KC_C: magic_decode_send_suffix_cycle(711, 't', UINT16_MAX); /* emits "omment " -> "comment " */ break;
                    case KC_D: magic_decode_send_suffix_cycle(486, 't', UINT16_MAX); /* emits "idn't " -> "didn't " */ break;
                    case KC_F: magic_decode_send_suffix_cycle(678, 'd', UINT16_MAX); /* emits "ocused " -> "focused " */ break;
                    case KC_G: magic_decode_send_suffix_cycle(339, 'e', UINT16_MAX); /* emits "enerate " -> "generate " */ break;
                    case KC_K: magic_replace_decode_send_cap_cycle(945, 'e', UINT16_MAX); /* emits "update " */ break;
                    case KC_L: magic_replace_decode_send_cap_cycle(327, 'e', UINT16_MAX); /* emits "elaborate " */ break;
                    case KC_M: magic_replace_decode_send_cap_cycle(546, 'n', UINT16_MAX); /* emits "instrumentation " */ break;
                    case KC_N: magic_replace_decode_send_cap_cycle(930, 'd', UINT16_MAX); /* emits "understand " */ break;
                    case KC_P: magic_decode_send_suffix_cycle(846, 'n', UINT16_MAX); /* emits "roduction " -> "production " */ break;
                    case KC_S: magic_decode_send_suffix_cycle(352, 'e', UINT16_MAX); /* emits "eparate " -> "separate " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_COMMA); break;
                    case KC_T: magic_decode_send_suffix_cycle(472, 'h', UINT16_MAX); /* emits "hough " -> "though " */ break;
                    case KC_V: magic_replace_decode_send_cap_cycle(120, 'l', UINT16_MAX); /* emits "approval " */ break;
                    case KC_W: magic_decode_send_suffix_cycle(468, 'h', UINT16_MAX); /* emits "hich " -> "which " */ break;
                    case KC_X: magic_replace_decode_send_cap_cycle(398, 'e', UINT16_MAX); /* emits "exclude " */ break;
                    case KC_Y: magic_tap_repeatable(KC_R); break;
                    case KC_Z: magic_replace_decode_send_cap_cycle(35, 'y', UINT16_MAX); /* emits "OpenTelemetry " */ break;
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
                    case KC_B: magic_decode_send_suffix_cycle(295, 'e', UINT16_MAX); /* emits "ecause " -> "because " */ break;
                    case KC_C: magic_replace_decode_send_cap_cycle(6, '\0', UINT16_MAX); /* emits "'re" */ break;
                    case KC_D: magic_decode_send_suffix_cycle(687, 't', UINT16_MAX); /* emits "oesn't " -> "doesn't " */ break;
                    case KC_ENT: magic_decode_send_cap_cycle(898, 'e', UINT16_MAX); /* emits "the " */ break;
                    case KC_F: magic_decode_send_suffix_cycle(692, 'g', UINT16_MAX); /* emits "ollowing " -> "following " */ break;
                    case KC_G: magic_tap_repeatable(KC_K); break;
                    case KC_K: magic_decode_send_suffix_cycle(655, 'w', UINT16_MAX); /* emits "now " -> "know " */ break;
                    case KC_L: magic_tap_repeatable(KC_R); break;
                    case KC_M: magic_decode_send_suffix_cycle(344, 't', UINT16_MAX); /* emits "ent " -> "ment " */ break;
                    case KC_N: magic_replace_decode_send_cap_cycle(810, '\0', UINT16_MAX); /* emits "qu" */ break;
                    case KC_P: magic_tap_repeatable(KC_N); break;
                    case KC_S: magic_decode_send(556); /* emits "ion" -> "sion" */ break;
                    case KC_SPC: magic_decode_send_cap_cycle(898, 'e', UINT16_MAX); /* emits "the " */ break;
                    case KC_T: magic_decode_send(556); /* emits "ion" -> "tion" */ break;
                    case KC_TAB: magic_decode_send_cap_cycle(898, 'e', UINT16_MAX); /* emits "the " */ break;
                    case KC_V: magic_replace_decode_send_cap_cycle(832, 'e', UINT16_MAX); /* emits "resolve " */ break;
                    case KC_W: magic_tap_repeatable(KC_S); break;
                    case KC_X: magic_tap_repeatable(KC_R); break;
                    case KC_Z: magic_replace_decode_send_cap_cycle(55, 't', UINT16_MAX); /* emits "Spring Boot " */ break;
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
                    case KC_C: magic_replace_decode_send_cap_cycle(0, '\0', UINT16_MAX); /* emits "'d" */ break;
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
                    case KC_T: magic_replace_decode_send_cap_cycle(985, 't', UINT16_MAX); /* emits "without " */ break;
                    case KC_V: magic_replace_decode_send_cap_cycle(30, 'e', UINT16_MAX); /* emits "I've " */ break;
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
                    case KC_B: magic_decode_send_suffix_cycle(311, 'e', UINT16_MAX); /* emits "efore " -> "before " */ break;
                    case KC_C: magic_replace_decode_send_cap_cycle(9, '\0', UINT16_MAX); /* emits "'s" */ break;
                    case KC_D: magic_decode_send_suffix_cycle(684, 's', UINT16_MAX); /* emits "oes " -> "does " */ break;
                    case KC_E: magic_decode_send_suffix_cycle(1004, 'n', UINT16_MAX); /* emits "xplain " -> "explain " */ break;
                    case KC_G: magic_replace_decode_send_cap_cycle(881, 't', UINT16_MAX); /* emits "suggest " */ break;
                    case KC_K: magic_decode_send_suffix_cycle(642, 'w', UINT16_MAX); /* emits "new " -> "knew " */ break;
                    case KC_L: magic_tap_repeatable(KC_B); break;
                    case KC_M: magic_tap_repeatable(KC_T); break;
                    case KC_N: magic_tap_repeatable(KC_P); break;
                    case KC_P: magic_replace_decode_send_cap_cycle(47, 's', UINT16_MAX); /* emits "Prometheus " */ break;
                    case KC_S: magic_decode_send_suffix_cycle(704, 'g', UINT16_MAX); /* emits "omething " -> "something " */ break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_J); break;
                    case KC_T: magic_decode_send_suffix_cycle(476, 't', UINT16_MAX); /* emits "hought " -> "thought " */ break;
                    case KC_W: magic_decode_send_suffix_cycle(745, 'e', UINT16_MAX); /* emits "orse " -> "worse " */ break;
                    case KC_X: magic_replace_decode_send_cap_cycle(376, 'e', UINT16_MAX); /* emits "example " */ break;
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
