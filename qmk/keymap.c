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
#include "generated.c"

extern char last_chord_char; // Track last character from chord for suffix modifications

bool is_window_switcher_active = false;
bool is_tab_switcher_active = false;
bool is_one_shot_mouse_active = false;

bool process_chord_mode(uint16_t keycode, keyrecord_t *record) {
    // Handle CHORD_MODIFIER state (after a chord was output)
    if (chord_state == CHORD_MODIFIER && record->event.pressed) {
        // Check for suffix keys based on keycode
        switch (keycode) {
            case ING:
                tap_code16(KC_BSPC); // Delete space
                // Check if last character is a vowel (a, e, i, o, u)
                if (last_chord_char == 'a' || last_chord_char == 'e' ||
                    last_chord_char == 'i' || last_chord_char == 'o' ||
                    last_chord_char == 'u') {
                    tap_code16(KC_BSPC); // Delete the vowel
                }
                SEND_STRING("ing ");
                // Stay in CHORD_MODIFIER to allow chaining suffixes like "ly"
                return false;
            case N_T:
                tap_code16(KC_BSPC);
                SEND_STRING("n't ");
                // Stay in CHORD_MODIFIER to allow chaining suffixes like "ly"
                return false;
            case MAGIC_A:
                tap_code16(KC_BSPC);
                SEND_STRING("ed ");
                // Stay in CHORD_MODIFIER to allow chaining suffixes like "ly"
                return false;
            case MAGIC_B:
                tap_code16(KC_BSPC);
                SEND_STRING("ly ");
                // Stay in CHORD_MODIFIER to allow chaining suffixes like "ly"
                return false;
            case MAGIC_C:
                tap_code16(KC_BSPC);
                SEND_STRING("s ");
                // Stay in CHORD_MODIFIER to allow chaining suffixes like "ly"
                return false;
            case KC_DOT:
                tap_code16(KC_BSPC);
                SEND_STRING(". ");
                add_oneshot_mods(MOD_BIT(KC_LSFT));
                chord_state = CHORD_INACTIVE;
                return false;
            case KC_COMMA:
                tap_code16(KC_BSPC);
                SEND_STRING(", ");
                chord_state = CHORD_INACTIVE;
                return false;
        }

        // If not a modifier key, exit CHORD_MODIFIER state and process normally
        chord_state = CHORD_INACTIVE;
        return true;
    }

    // Handle chord key press
    if (keycode == _HANDLER_CHORD_KEY) {
        if (record->event.pressed) {
            chord_state = CHORD_ROOT; // Activate chord mode at root of trie (negative state)
            chord_depth = 0; // Reset depth counter
        }
        return false;
    }

    if (chord_state != CHORD_INACTIVE && chord_state != CHORD_MODIFIER) {
        if (record->event.pressed) {
            // Special handling for space at root: enable one-shot shift and stay in chord mode
            if (keycode == KC_SPC && chord_state == CHORD_ROOT && chord_depth == 0) {
                add_oneshot_mods(MOD_BIT(KC_LSFT));
                return false; // Stay in chord mode, don't process space
            }

            // Try to transition to next state with the pressed key
            int next_state = chord_transition(chord_state, keycode);
            if (next_state != CHORD_INACTIVE && next_state != chord_state) { // Valid transition (changed state)
                chord_state = next_state;
                chord_depth++;

                // Emit immediately after 2nd letter
                if (chord_depth == 2) {
                    // If state is non-negative, it's a data offset - output directly
                    if (chord_state >= 0) {
                        chord_decode_send(chord_state);
                        tap_code16(KC_SPC);
                        chord_state = CHORD_MODIFIER; // Enter modifier state
                        chord_depth = 0;
                    }
                }
            } else {
                // Invalid transition, reset chord mode
                chord_state = CHORD_INACTIVE;
                chord_depth = 0;
            }
            return false;
        }
    }

    return true;
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
    if (!process_chord_mode(keycode, record)) {
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
