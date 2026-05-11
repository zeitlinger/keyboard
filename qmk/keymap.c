/* Copyright 2023 ChuseCubr */
/* https://github.com/ChuseCubr/mini-ryoku */

/* This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 */

#include QMK_KEYBOARD_H

#include "unicode_names.h"

const uint32_t PROGMEM unicode_map[] = {
    [UMLAUT_a]  = 0x00E4, // ä
    [UMLAUT_A]  = 0x00C4, // Ä
    [UMLAUT_o]  = 0x00F6, // ö
    [UMLAUT_O]  = 0x00D6, // Ö
    [UMLAUT_u]  = 0x00FC, // ü
    [UMLAUT_U]  = 0x00DC, // Ü
    [UMLAUT_s]  = 0x00DF, // ß
    [SMILEY]    = 0x1F600 // 😀
};

#include "layout.h"

/* for >34 key users, replace this line with an include statement for the mask file */
/* example mask files are included for the Lily58 and Corne keyboards for reference */
#include "masks/sweep.h"
// #include "masks/lily58.h"
// #include "masks/crkbd.h"

#include "casemodes.h"
#include "combos.c"

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

#ifdef USE_CUSTOM_COMBO_POC
#ifndef CUSTOM_COMBO_TERM
#define CUSTOM_COMBO_TERM 50
#endif

static bool custom_combo_poc_pending = false;
static keypos_t custom_combo_poc_pending_key = {0, 0};
static uint16_t custom_combo_poc_pending_keycode = KC_NO;
static uint16_t custom_combo_poc_pending_timer = 0;

static bool custom_combo_poc_active = false;
static keypos_t custom_combo_poc_active_keys[2];
static bool custom_combo_poc_active_down[2] = {false, false};

static bool custom_combo_poc_same_key(keypos_t a, keypos_t b) {
    return a.row == b.row && a.col == b.col;
}

static bool custom_combo_poc_layer_ok(void) {
    return layer == _BASE || layer == _LEFT;
}

static bool custom_combo_poc_is_trigger(keypos_t key) {
    return (key.row == 1 && key.col == 1) || (key.row == 0 && key.col == 1); // KC_C + KC_X -> KC_P
}

static void custom_combo_poc_clear_pending(void) {
    custom_combo_poc_pending = false;
    custom_combo_poc_pending_keycode = KC_NO;
    custom_combo_poc_pending_timer = 0;
}

static void custom_combo_poc_emit_pending(void) {
    if (custom_combo_poc_pending) {
        tap_code16(custom_combo_poc_pending_keycode);
        custom_combo_poc_clear_pending();
    }
}

static void custom_combo_poc_emit_combo(void) {
    tap_code16(layer == _LEFT ? S(KC_P) : KC_P);
}

static bool process_custom_combo_poc(uint16_t keycode, keyrecord_t *record) {
    keypos_t key = record->event.key;

    if (custom_combo_poc_active && !record->event.pressed) {
        for (uint8_t i = 0; i < 2; ++i) {
            if (custom_combo_poc_active_down[i] && custom_combo_poc_same_key(custom_combo_poc_active_keys[i], key)) {
                custom_combo_poc_active_down[i] = false;
                if (!custom_combo_poc_active_down[0] && !custom_combo_poc_active_down[1]) {
                    custom_combo_poc_active = false;
                }
                return false;
            }
        }
    }

    if (custom_combo_poc_pending) {
        bool expired = timer_elapsed(custom_combo_poc_pending_timer) > CUSTOM_COMBO_TERM;
        bool same_layer = custom_combo_poc_layer_ok();
        bool is_trigger = custom_combo_poc_is_trigger(key);
        if (!same_layer || expired || (record->event.pressed && !is_trigger)) {
            custom_combo_poc_emit_pending();
        }
    }

    if (!custom_combo_poc_layer_ok() || !custom_combo_poc_is_trigger(key)) {
        return true;
    }

    if (!record->event.pressed) {
        if (custom_combo_poc_pending && custom_combo_poc_same_key(custom_combo_poc_pending_key, key)) {
            custom_combo_poc_emit_pending();
            return false;
        }
        return true;
    }

    if (!custom_combo_poc_pending) {
        custom_combo_poc_pending = true;
        custom_combo_poc_pending_key = key;
        custom_combo_poc_pending_keycode = keycode;
        custom_combo_poc_pending_timer = timer_read();
        return false;
    }

    if (custom_combo_poc_same_key(custom_combo_poc_pending_key, key)) {
        return false;
    }

    if (timer_elapsed(custom_combo_poc_pending_timer) > CUSTOM_COMBO_TERM) {
        custom_combo_poc_emit_pending();
        custom_combo_poc_pending = true;
        custom_combo_poc_pending_key = key;
        custom_combo_poc_pending_keycode = keycode;
        custom_combo_poc_pending_timer = timer_read();
        return false;
    }

    custom_combo_poc_emit_combo();
    custom_combo_poc_active = true;
    custom_combo_poc_active_keys[0] = custom_combo_poc_pending_key;
    custom_combo_poc_active_keys[1] = key;
    custom_combo_poc_active_down[0] = true;
    custom_combo_poc_active_down[1] = true;
    custom_combo_poc_clear_pending();
    return false;
}
#endif

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
#ifdef USE_CUSTOM_COMBO_POC
    if (!process_custom_combo_poc(keycode, record)) {
        return false;
    }
#endif

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
