/* Copyright 2023 ChuseCubr */
/* https://github.com/ChuseCubr/mini-ryoku */

/* This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>. */

#include QMK_KEYBOARD_H

enum unicode_names {
    UMLAUT_A,
    UMLAUT_a,
    UMLAUT_O,
    UMLAUT_o,
    UMLAUT_U,
    UMLAUT_u,
    UMLAUT_s,
    SMILEY
};

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

#include "g/keymap_combo.h"
#include "casemodes.h"

// Suffix state machine: set when a word-magic fires. Next magic press is
// interpreted as a suffix chain (ed/ly/s/n't/ing) or exit (./,).
static bool suffix_active = false;
static char last_magic_char = 0;

static inline void set_suffix_state(char c) {
    suffix_active = true;
    last_magic_char = c;
}

static inline void clear_suffix_state(void) {
    suffix_active = false;
}

#include "generated.c"

bool is_window_switcher_active = false;
bool is_tab_switcher_active = false;
bool is_one_shot_mouse_active = false;

static bool process_suffix(uint16_t keycode, keyrecord_t *record) {
    if (!suffix_active || !record->event.pressed) return true;
    switch (keycode) {
    case MAGIC_I:
        tap_code16(KC_BSPC); SEND_STRING(". ");
        add_oneshot_mods(MOD_BIT(KC_LSFT));
        suffix_active = false;
        return false;
    case MAGIC_H:
        tap_code16(KC_BSPC); SEND_STRING(", ");
        suffix_active = false;
        return false;
    case MAGIC_D:
        tap_code16(KC_BSPC); SEND_STRING("n't ");
        last_magic_char = 't';
        return false;
    case MAGIC_G:
        tap_code16(KC_BSPC);
        if (last_magic_char == 'e') {
            SEND_STRING("d ");
        } else {
            SEND_STRING("ed ");
        }
        last_magic_char = 'd';
        return false;
    case MAGIC_E:
        tap_code16(KC_BSPC); SEND_STRING("ly ");
        last_magic_char = 'y';
        return false;
    case MAGIC_B:
        tap_code16(KC_BSPC); SEND_STRING("s ");
        last_magic_char = 's';
        return false;
    case _HANDLER_ING:
        tap_code16(KC_BSPC);
        if (last_magic_char == 'a' || last_magic_char == 'e' ||
            last_magic_char == 'i' || last_magic_char == 'o' ||
            last_magic_char == 'u') {
            tap_code16(KC_BSPC);
        }
        SEND_STRING("ing ");
        last_magic_char = 'g';
        return false;
    default:
        suffix_active = false;
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
    if (!process_suffix(keycode, record)) {
        return false;
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
            SEND_STRING(". ");
            add_oneshot_mods(MOD_BIT(KC_LSFT));
        }
        return false;
    #endif
    #ifdef _HANDLER_N_T
    case _HANDLER_N_T:
        if (record->event.pressed) {
            SEND_STRING("n't");
        }
        return false;
    #endif
    #ifdef _HANDLER_ING
    case _HANDLER_ING:
        if (record->event.pressed) {
            SEND_STRING("ing");
        }
        return false;
    #endif
    #ifdef _HANDLER_ADPT_QU
    case _HANDLER_ADPT_QU:
        if (record->event.pressed) {
            SEND_STRING("qu");
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
