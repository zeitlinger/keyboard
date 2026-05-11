/* Copyright 2023 ChuseCubr */
/* https://github.com/ChuseCubr/mini-ryoku */

/* This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 */

#include QMK_KEYBOARD_H

enum unicode_names {
    UMLAUT_A,
    UMLAUT_a,
    UMLAUT_O,
    UMLAUT_o,
    UMLAUT_U,
    UMLAUT_u,
    UMLAUT_s
};

const uint32_t PROGMEM unicode_map[] = {
    [UMLAUT_a]  = 0x00E4, // ä
    [UMLAUT_A]  = 0x00C4, // Ä
    [UMLAUT_o]  = 0x00F6, // ö
    [UMLAUT_O]  = 0x00D6, // Ö
    [UMLAUT_u]  = 0x00FC, // ü
    [UMLAUT_U]  = 0x00DC, // Ü
    [UMLAUT_s]  = 0x00DF, // ß
};

// Defined before layout.h so it's in scope for keymap bindings.
enum keymap_custom_keycodes {
    DEBUG_DUMP = SAFE_RANGE + 100,
};

#include "layout.h"

/* for >34 key users, replace this line with an include statement for the mask file */
/* example mask files are included for the Lily58 and Corne keyboards for reference */
#include "masks/sweep.h"
// #include "masks/lily58.h"
// #include "masks/crkbd.h"

#include "g/keymap_combo.h"
#include "casemodes.h"

// Suffix state machine: set when a word-magic fires. Next magic press is
// interpreted as a suffix chain (ed/ly/s/n't/ing) or exit (./,).
static bool suffix_active = false;
static char last_magic_char = 0;
static uint16_t suffix_cycle_offset = UINT16_MAX;
static bool suffix_cycle_capitalize = false;
static uint8_t suffix_cycle_common_prefix_length = 0;
static inline void set_suffix_state(char c) {
    suffix_active = true;
    last_magic_char = c;
    suffix_cycle_offset = UINT16_MAX;
    suffix_cycle_capitalize = false;
}

static inline void clear_suffix_cycle_state(void) {
    suffix_cycle_offset = UINT16_MAX;
    suffix_cycle_capitalize = false;
    suffix_cycle_common_prefix_length = 0;
}

static inline void clear_suffix_state(void) {
    suffix_active = false;
    last_magic_char = 0;
    clear_suffix_cycle_state();
}

static inline void tap_dot_space(void) {
    tap_code16(KC_DOT);
    tap_code16(KC_SPC);
}

static inline void tap_comma_space(void) {
    tap_code16(KC_COMMA);
    tap_code16(KC_SPC);
}

static inline void tap_n_t(void) {
    tap_code16(KC_N);
    tap_code16(KC_QUOTE);
    tap_code16(KC_T);
}

static inline void tap_ing(void) {
    tap_code16(KC_I);
    tap_code16(KC_N);
    tap_code16(KC_G);
}

#include "generated.c"

bool is_window_switcher_active = false;
bool is_tab_switcher_active = false;
bool is_one_shot_mouse_active = false;

static void send_hex_nibble(uint8_t n) {
    char c = n < 10 ? '0' + n : 'A' + (n - 10);
    char s[2] = {c, 0};
    send_string(s);
}

static void send_hex_byte(uint8_t b) {
    send_hex_nibble(b >> 4);
    send_hex_nibble(b & 0xF);
}

// Emit only fields that differ from a clean idle state, each with a short
// label. Empty output = nothing wrong. Flags bits: 0 suffix, 1 winsw,
// 2 tabsw, 3 osmouse, 4 caps, 5-6 xcase, 7 magcap.
//
// Inner col left upper (DEBUG_DUMP trigger) sits at matrix row 0 col 4
// (bit 0x0010); a row showing only that bit is the trigger itself, not
// a stuck key, so it's skipped.
#define DEBUG_DUMP_TRIGGER_ROW  0
#define DEBUG_DUMP_TRIGGER_MASK 0x0010
static void dump_field_u8(const char *label, uint8_t v) {
    if (!v) return;
    send_string(" "); send_string(label); send_string("="); send_hex_byte(v);
}
static void dump_field_u16(const char *label, uint16_t v) {
    if (!v) return;
    send_string(" "); send_string(label); send_string("=");
    send_hex_byte(v >> 8); send_hex_byte(v & 0xFF);
}
static void dump_state(uint8_t snap_mods, uint8_t snap_osm, uint8_t snap_weak) {
    uint8_t flags = (suffix_active                ? 0x01 : 0)
                  | (is_window_switcher_active    ? 0x02 : 0)
                  | (is_tab_switcher_active       ? 0x04 : 0)
                  | (is_one_shot_mouse_active     ? 0x08 : 0)
                  | (caps_word_enabled()          ? 0x10 : 0)
                  | ((get_xcase_state() & 0x3) << 5)
                  | (magic_capitalize_next        ? 0x80 : 0);
    dump_field_u8 ("m",   snap_mods);
    dump_field_u8 ("osm", snap_osm);
    dump_field_u8 ("w",   snap_weak);
    dump_field_u8 ("lay", (uint8_t)layer);
    dump_field_u8 ("flg", flags);
    dump_field_u16("l",   last_keycode);
    dump_field_u16("p",   prev_keycode);
    dump_field_u16("mt",  last_magic_trigger);
    dump_field_u16("mr",  last_magic_repeat_keycode);
    dump_field_u16("mrm", magic_remembered_keycode);
    dump_field_u16("mrp", magic_repeat_keycode);
    if (suffix_cycle_offset != UINT16_MAX) {
        dump_field_u16("cyc", suffix_cycle_offset);
    }
    dump_field_u8 ("lmc", (uint8_t)last_magic_char);
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row_t row = matrix_get_row(r);
        if (!row) continue;
        if (r == DEBUG_DUMP_TRIGGER_ROW && row == DEBUG_DUMP_TRIGGER_MASK) continue;
        send_string(" r"); send_hex_nibble(r); send_string("=");
        send_hex_byte((row >> 8) & 0xFF); send_hex_byte(row & 0xFF);
    }
}

static void reset_all_state(void) {
    clear_keyboard();
    clear_mods();
    clear_oneshot_mods();
    clear_weak_mods();
    if (is_window_switcher_active) { unregister_code(KC_LALT); is_window_switcher_active = false; }
    if (is_tab_switcher_active)    { unregister_code(KC_LCTL); is_tab_switcher_active    = false; }
    is_one_shot_mouse_active = false;
    clear_suffix_state();
    disable_caps_word();
    disable_xcase();
    magic_capitalize_next      = false;
    magic_context_key_emitted  = true;
    prev_keycode               = KC_NO;
    last_keycode               = KC_NO;
    last_magic_trigger         = KC_NO;
    last_magic_repeat_keycode  = KC_NO;
    magic_remembered_keycode   = KC_NO;
    magic_repeat_keycode       = KC_NO;
    layer_move(_BASE);
}

static bool process_suffix(uint16_t keycode, keyrecord_t *record) {
    if (!suffix_active || !record->event.pressed) return true;
    if (process_magic_suffix(keycode)) {
        return false;
    }
    switch (keycode) {
    case _HANDLER_ING:
        tap_code16(KC_BSPC);
        if (last_magic_char == 'a' || last_magic_char == 'e' ||
            last_magic_char == 'i' || last_magic_char == 'o' ||
            last_magic_char == 'u') {
            tap_code16(KC_BSPC);
        }
        tap_ing(); tap_code16(KC_SPC);
        last_magic_char = 'g';
        clear_suffix_cycle_state();
        return false;
    default:
        clear_suffix_state();
        return true;
    }
}

bool process_xcase_activation(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case _HANDLER_CAPS_WORDS:
            enable_caps_word();
            return false;
        case _HANDLER_SNAKE_CASE:
            enable_xcase_with(KC_UNDS);
            return false;
        case _HANDLER_SCREAMING_SNAKE_CASE:
            enable_xcase_with(KC_UNDS);
            enable_caps_word();
            return false;
        case _HANDLER_CAMEL_CASE:
            enable_xcase_with(OSM(MOD_LSFT));
            return false;
        case _HANDLER_PASCAL_CASE:
            enable_xcase_with(OSM(MOD_LSFT));
            add_oneshot_mods(MOD_BIT(KC_LSFT));
            return false;
        case _HANDLER_SLASH_CASE:
            enable_xcase_with(KC_SLASH);
            return false;
        case _HANDLER_DOT_CASE:
            enable_xcase_with(KC_DOT);
            return false;
        case _HANDLER_KEBAP_CASE:
            enable_xcase_with(KC_MINS);
            return false;
        }
    }
    return true;
}
bool process_switcher(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        bool switch_window = keycode == _HANDLER_NEXT_WINDOW;
        bool switch_tab = keycode == _HANDLER_NEXT_TAB;

        if ((is_tab_switcher_active && !switch_tab) || (is_window_switcher_active && !switch_window)) {
            //can use any key as shift tap key in switcher
            tap_code16(S(KC_TAB));
            return false;
        }

        if (switch_window) {
            if (!is_window_switcher_active) {
                is_window_switcher_active = true;
                register_code(KC_LALT);
            }
            tap_code16(KC_TAB);
            return false;
        }

        if (switch_tab) {
            if (!is_tab_switcher_active) {
                is_tab_switcher_active = true;
                register_code(KC_LCTL);
            }
            tap_code16(KC_TAB);
            return false;
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Emergency dump+reset must bypass every other handler so a wedged
    // state (e.g. switcher swallowing all keys) cannot trap it.
    if (keycode == DEBUG_DUMP) {
        if (record->event.pressed) {
            uint8_t snap_mods = get_mods();
            uint8_t snap_osm  = get_oneshot_mods();
            uint8_t snap_weak = get_weak_mods();
            clear_keyboard();
            clear_mods();
            clear_oneshot_mods();
            clear_weak_mods();
            dump_state(snap_mods, snap_osm, snap_weak);
            reset_all_state();
        }
        return false;
    }

    if (!process_suffix(keycode, record)) {
        return false;
    }

    if (record->event.pressed) {
        if (is_magic_keycode(keycode) && repeat_magic_key(keycode)) {
            return false;
        }
    }

    if (!process_record_generated(keycode, record)) {
        return false;
    }
    if (!process_case_modes(keycode, record)) {
        return false;
    }

    if (!process_switcher(keycode, record)) {
        return false;
    }
    if (!process_xcase_activation(keycode, record)) {
        return false;
    }

    switch (keycode) {
    #ifdef _MOUSE
    case _HANDLER_ONE_SHOT_MOUSE:
        if (record->event.pressed) {
            layer_on(_MOUSE);
            is_one_shot_mouse_active = true;
        }
        break;
    case KC_BTN1:
    case KC_BTN2:
    case KC_BTN3:
        if (record->event.pressed && is_one_shot_mouse_active) {
            layer_off(_MOUSE);
            is_one_shot_mouse_active = false;
            tap_code16(keycode);
            return false;
        }
        break;
    #endif
    case _HANDLER_PRINT_VERSION:
        if (record->event.pressed) {
            SEND_STRING(VERSION_STRING);
        }
        return false;
    #ifdef _HANDLER_DOT_SPC
    case _HANDLER_DOT_SPC:
        if (record->event.pressed) {
            tap_dot_space();
            add_oneshot_mods(MOD_BIT(KC_LSFT));
        }
        return false;
    #endif
    #ifdef _HANDLER_N_T
    case _HANDLER_N_T:
        if (record->event.pressed) {
            tap_n_t();
        }
        return false;
    #endif
    #ifdef _HANDLER_ING
    case _HANDLER_ING:
        if (record->event.pressed) {
            tap_ing();
        }
        return false;
    #endif
    #ifdef _HANDLER_ADPT_QU
    case _HANDLER_ADPT_QU:
        if (record->event.pressed) {
            tap_code16(KC_Q); tap_code16(KC_U);
        }
        return false;
    #endif
    default:
        break;
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    layer = get_highest_layer(state);
    switch (layer) {
    case _BASE:
        is_one_shot_mouse_active = false;
        clear_mods();
        break;
    }
    if (is_window_switcher_active) {
      unregister_code(KC_LALT);
      is_window_switcher_active = false;
    }
    if (is_tab_switcher_active) {
      unregister_code(KC_LCTL);
      is_tab_switcher_active = false;
    }
    return state;
}
