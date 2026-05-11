// file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
#include QMK_KEYBOARD_H
#include "action_tapping.h"
#include "layout.h"
#include "unicode_names.h"

// Defined in generated.c.
void magic_decode_send(uint16_t offset);
extern int layer;

enum combos {
    C_BASE_ING,
    C_BASE_KC_B,
    C_BASE_KC_G,
    C_BASE_KC_K,
    C_BASE_KC_M,
    C_BASE_KC_P,
    C_BASE_KC_V,
    C_BASE_MAGIC_C,
    C_BASE_MAGIC_D,
    C_BASE_MAGIC_E,
    C_BASE_MAGIC_F,
    C_BASE_MAGIC_G,
    C_BASE_MAGIC_H,
    C_BASE_MAGIC_I,
    C_BASE_MAGIC_J,
    C_BASE_MAGIC_K,
    C_FNSYM_KC_AMPR,
    C_FNSYM_KC_ASTR,
    C_FNSYM_KC_BACKSLASH,
    C_FNSYM_KC_CIRC,
    C_FNSYM_KC_DLR,
    C_FNSYM_KC_F11,
    C_FNSYM_KC_HASH,
    C_FNSYM_KC_KP_MINUS,
    C_FNSYM_KC_KP_PLUS,
    C_FNSYM_KC_LABK,
    C_FNSYM_KC_LCBR,
    C_FNSYM_KC_LGUI,
    C_FNSYM_KC_LPRN,
    C_FNSYM_KC_MINUS,
    C_FNSYM_KC_PERC,
    C_FNSYM_KC_PIPE,
    C_FNSYM_KC_RABK,
    C_FNSYM_KC_RCBR,
    C_FNSYM_KC_RPRN,
    C_FNSYM_KC_SLASH,
    C_FNSYM_KC_TILD,
    C_FNSYM_LT_NUM2KC_EQUAL,
    C_FNSYM_MO_NUM,
    C_LEFT_KC_COLN,
    C_NAV_AKC_F12,
    C_NAV_CKC_A,
    C_NAV_CKC_B,
    C_NAV_CKC_C,
    C_NAV_CKC_D,
    C_NAV_CKC_E,
    C_NAV_CKC_F12,
    C_NAV_CKC_K,
    C_NAV_CKC_P,
    C_NAV_CKC_SLASH,
    C_NAV_CKC_V,
    C_NAV_CKC_W,
    C_NAV_CKC_X,
    C_NAV_CKC_Y,
    C_NAV_CKC_Z,
    C_NAV_KC_END,
    C_NAV_KC_HOME,
    C_NAV_KC_PGDN,
    C_NAV_KC_PGUP,
    C_NAV_LCAKC_B,
    C_NAV_RCSKC_C,
    C_NAV_RCSKC_N,
    C_NAV_RCSKC_V,
    C_NAV_RCSKC_Z,
    C_NAV_UMUMLAUT_S,
    C_NAV_UPUMLAUT_AUMLAUT_A,
    C_NAV_UPUMLAUT_OUMLAUT_O,
    C_NAV_UPUMLAUT_UUMLAUT_U,
    C_NUM_AKC_F1,
    C_NUM_CKC_G,
    C_NUM_LCAKC_L,
    C_NUM_LSAKC_B,
    C_NUM_LSAKC_S,
    C_NUM_LSAKC_X,
    C_NUM_RCSKC_V,
    C_RIGHT_KC_AT,
    C_RIGHT_KC_COMMA,
    C_RIGHT_KC_DOT,
    C_RIGHT_KC_EXLM,
    C_RIGHT_KC_GRAVE,
    C_RIGHT_KC_QUES,
    C_RIGHT_KC_QUOTE,
    C_RIGHT_KC_UNDS,
    C_RIGHT_N_T,
    C_RIGHT_RCSKC_F,
    C_RIGHT_RCSKC_R,
    SUB_1,
    SUB_2,
    SUB_3,
    SUB_4,
    SUB_5,
    SUB_6
};

typedef struct {
    uint16_t index;
    uint8_t row1;
    uint8_t col1;
    uint8_t row2;
    uint8_t col2;
    uint8_t home_layer;
    bool allow_left;
    uint16_t term;
} positional_combo_t;

static const positional_combo_t positional_combos[] = {
    {C_BASE_ING, 0, 4, 1, 4, _BASE, false, 50},
    {C_BASE_KC_B, 1, 1, 2, 1, _BASE, true, 50},
    {C_BASE_KC_G, 2, 2, 1, 2, _BASE, true, 50},
    {C_BASE_KC_K, 2, 3, 1, 3, _BASE, true, 50},
    {C_BASE_KC_M, 1, 2, 0, 2, _BASE, true, 50},
    {C_BASE_KC_P, 1, 1, 0, 1, _BASE, true, 50},
    {C_BASE_KC_V, 0, 3, 1, 3, _BASE, true, 50},
    {C_BASE_MAGIC_C, 0, 0, 1, 0, _BASE, false, 50},
    {C_BASE_MAGIC_D, 1, 5, 0, 5, _BASE, false, 50},
    {C_BASE_MAGIC_E, 1, 6, 0, 6, _BASE, false, 50},
    {C_BASE_MAGIC_F, 0, 7, 1, 7, _BASE, false, 50},
    {C_BASE_MAGIC_G, 1, 0, 2, 0, _BASE, false, 50},
    {C_BASE_MAGIC_H, 1, 4, 2, 4, _BASE, false, 50},
    {C_BASE_MAGIC_I, 1, 5, 2, 5, _BASE, false, 50},
    {C_BASE_MAGIC_J, 1, 6, 2, 6, _BASE, false, 50},
    {C_BASE_MAGIC_K, 1, 7, 2, 7, _BASE, false, 50},
    {C_FNSYM_KC_AMPR, 1, 1, 2, 1, _FNSYM, false, 50},
    {C_FNSYM_KC_ASTR, 1, 2, 0, 2, _FNSYM, false, 50},
    {C_FNSYM_KC_BACKSLASH, 0, 7, 1, 7, _FNSYM, false, 50},
    {C_FNSYM_KC_CIRC, 0, 0, 1, 0, _FNSYM, false, 50},
    {C_FNSYM_KC_DLR, 1, 0, 2, 0, _FNSYM, false, 50},
    {C_FNSYM_KC_F11, 1, 2, 2, 2, _FNSYM, false, 50},
    {C_FNSYM_KC_HASH, 1, 6, 2, 6, _FNSYM, false, 50},
    {C_FNSYM_KC_KP_MINUS, 0, 3, 1, 3, _FNSYM, false, 50},
    {C_FNSYM_KC_KP_PLUS, 1, 3, 2, 3, _FNSYM, false, 50},
    {C_FNSYM_KC_LABK, 1, 5, 0, 5, _FNSYM, false, 50},
    {C_FNSYM_KC_LCBR, 2, 5, 3, 5, _FNSYM, false, 50},
    {C_FNSYM_KC_LGUI, 0, 4, 1, 4, _FNSYM, false, 50},
    {C_FNSYM_KC_LPRN, 0, 5, 3, 5, _FNSYM, false, 50},
    {C_FNSYM_KC_MINUS, 2, 4, 3, 5, _FNSYM, false, 50},
    {C_FNSYM_KC_PERC, 1, 7, 2, 7, _FNSYM, false, 50},
    {C_FNSYM_KC_PIPE, 0, 1, 1, 1, _FNSYM, false, 50},
    {C_FNSYM_KC_RABK, 1, 6, 0, 6, _FNSYM, false, 50},
    {C_FNSYM_KC_RCBR, 2, 6, 3, 5, _FNSYM, false, 50},
    {C_FNSYM_KC_RPRN, 0, 6, 3, 5, _FNSYM, false, 50},
    {C_FNSYM_KC_SLASH, 2, 5, 1, 5, _FNSYM, false, 50},
    {C_FNSYM_KC_TILD, 1, 4, 2, 4, _FNSYM, false, 50},
    {C_FNSYM_LT_NUM2KC_EQUAL, 1, 7, 3, 5, _FNSYM, false, 50},
    {C_FNSYM_MO_NUM, 3, 5, 2, 7, _FNSYM, false, 50},
    {C_LEFT_KC_COLN, 2, 0, 1, 0, _LEFT, false, 50},
    {C_NAV_AKC_F12, 1, 5, 1, 6, _NAV, false, 50},
    {C_NAV_CKC_A, 0, 2, 1, 2, _NAV, false, 50},
    {C_NAV_CKC_B, 1, 4, 1, 6, _NAV, false, 50},
    {C_NAV_CKC_C, 1, 0, 3, 2, _NAV, false, 50},
    {C_NAV_CKC_D, 1, 2, 2, 2, _NAV, false, 50},
    {C_NAV_CKC_E, 1, 0, 0, 0, _NAV, false, 50},
    {C_NAV_CKC_F12, 2, 5, 2, 4, _NAV, false, 50},
    {C_NAV_CKC_K, 2, 1, 1, 1, _NAV, false, 50},
    {C_NAV_CKC_P, 2, 6, 2, 4, _NAV, false, 50},
    {C_NAV_CKC_SLASH, 2, 5, 2, 6, _NAV, false, 50},
    {C_NAV_CKC_V, 0, 2, 3, 2, _NAV, false, 50},
    {C_NAV_CKC_W, 2, 1, 3, 2, _NAV, false, 50},
    {C_NAV_CKC_X, 0, 1, 3, 2, _NAV, false, 50},
    {C_NAV_CKC_Y, 1, 3, 2, 3, _NAV, false, 50},
    {C_NAV_CKC_Z, 3, 2, 2, 0, _NAV, false, 50},
    {C_NAV_KC_END, 1, 7, 2, 7, _NAV, false, 50},
    {C_NAV_KC_HOME, 2, 4, 1, 4, _NAV, false, 50},
    {C_NAV_KC_PGDN, 2, 5, 1, 5, _NAV, false, 50},
    {C_NAV_KC_PGUP, 2, 6, 1, 6, _NAV, false, 50},
    {C_NAV_LCAKC_B, 1, 5, 1, 4, _NAV, false, 50},
    {C_NAV_RCSKC_C, 1, 0, 2, 0, _NAV, false, 50},
    {C_NAV_RCSKC_N, 0, 1, 1, 1, _NAV, false, 50},
    {C_NAV_RCSKC_V, 1, 3, 0, 3, _NAV, false, 50},
    {C_NAV_RCSKC_Z, 0, 3, 3, 2, _NAV, false, 50},
    {C_NAV_UMUMLAUT_S, 0, 7, 1, 7, _NAV, false, 50},
    {C_NAV_UPUMLAUT_AUMLAUT_A, 0, 6, 1, 6, _NAV, false, 50},
    {C_NAV_UPUMLAUT_OUMLAUT_O, 1, 5, 0, 5, _NAV, false, 50},
    {C_NAV_UPUMLAUT_UUMLAUT_U, 0, 4, 1, 4, _NAV, false, 50},
    {C_NUM_AKC_F1, 1, 2, 0, 2, _NUM, false, 50},
    {C_NUM_CKC_G, 1, 3, 2, 3, _NUM, false, 50},
    {C_NUM_LCAKC_L, 1, 2, 2, 2, _NUM, false, 50},
    {C_NUM_LSAKC_B, 1, 1, 2, 1, _NUM, false, 50},
    {C_NUM_LSAKC_S, 1, 0, 2, 0, _NUM, false, 50},
    {C_NUM_LSAKC_X, 1, 1, 0, 1, _NUM, false, 50},
    {C_NUM_RCSKC_V, 0, 3, 1, 3, _NUM, false, 50},
    {C_RIGHT_KC_AT, 0, 4, 1, 4, _RIGHT, false, 50},
    {C_RIGHT_KC_COMMA, 1, 5, 2, 5, _RIGHT, false, 50},
    {C_RIGHT_KC_DOT, 1, 6, 2, 6, _RIGHT, false, 50},
    {C_RIGHT_KC_EXLM, 1, 2, 0, 2, _RIGHT, false, 50},
    {C_RIGHT_KC_GRAVE, 0, 7, 1, 7, _RIGHT, false, 50},
    {C_RIGHT_KC_QUES, 0, 6, 1, 6, _RIGHT, false, 50},
    {C_RIGHT_KC_QUOTE, 1, 4, 2, 4, _RIGHT, false, 50},
    {C_RIGHT_KC_UNDS, 2, 7, 1, 7, _RIGHT, false, 50},
    {C_RIGHT_N_T, 0, 5, 1, 5, _RIGHT, false, 50},
    {C_RIGHT_RCSKC_F, 1, 2, 2, 2, _RIGHT, false, 50},
    {C_RIGHT_RCSKC_R, 1, 3, 2, 3, _RIGHT, false, 50},
    {SUB_1, 0, 0, 1, 0, _LEFT, false, 50},
    {SUB_2, 2, 3, 1, 3, _MEDIA, false, 50},
    {SUB_3, 2, 2, 1, 2, _MEDIA, false, 50},
    {SUB_4, 2, 1, 1, 1, _MEDIA, false, 50},
    {SUB_5, 0, 0, 1, 0, _MEDIA, false, 50},
    {SUB_6, 1, 0, 2, 0, _MEDIA, false, 50}
};

static bool custom_combo_replaying = false;
static bool custom_combo_pending = false;
static bool custom_combo_pending_passthrough = false;
static keyrecord_t custom_combo_pending_record;
static uint16_t custom_combo_pending_keycode = KC_NO;
static uint16_t custom_combo_pending_timer = 0;
static uint16_t custom_combo_pending_term = 0;
static void emit_custom_combo(uint16_t combo_index);

static bool custom_combo_active = false;
static keypos_t custom_combo_active_keys[2];
static bool custom_combo_active_down[2] = {false, false};
static bool custom_combo_swallow_release[2] = {false, false};

static bool custom_combo_keypos_equal(keypos_t a, keypos_t b) {
    return a.row == b.row && a.col == b.col;
}

static bool custom_combo_allows_layer(const positional_combo_t *combo) {
    return layer == combo->home_layer || (combo->allow_left && layer == _LEFT);
}

static bool custom_combo_contains_pos(const positional_combo_t *combo, keypos_t key) {
    return (combo->row1 == key.row && combo->col1 == key.col)
        || (combo->row2 == key.row && combo->col2 == key.col);
}

static uint16_t custom_combo_term_for_key(keypos_t key) {
    uint16_t best = 0;
    for (uint16_t i = 0; i < ARRAY_SIZE(positional_combos); ++i) {
        const positional_combo_t *combo = &positional_combos[i];
        if (custom_combo_allows_layer(combo) && custom_combo_contains_pos(combo, key) && combo->term > best) {
            best = combo->term;
        }
    }
    return best;
}

static bool custom_combo_has_candidate(keypos_t key) {
    return custom_combo_term_for_key(key) > 0;
}

static int16_t custom_combo_find_match(keypos_t a, keypos_t b) {
    for (uint16_t i = 0; i < ARRAY_SIZE(positional_combos); ++i) {
        const positional_combo_t *combo = &positional_combos[i];
        if (!custom_combo_allows_layer(combo)) {
            continue;
        }
        const bool forward = combo->row1 == a.row && combo->col1 == a.col && combo->row2 == b.row && combo->col2 == b.col;
        const bool reverse = combo->row1 == b.row && combo->col1 == b.col && combo->row2 == a.row && combo->col2 == a.col;
        if (forward || reverse) {
            return combo->index;
        }
    }
    return -1;
}

static bool custom_combo_key_must_passthrough(uint16_t keycode) {
    return (QK_MOMENTARY <= keycode && keycode <= QK_MOMENTARY_MAX)
        || (QK_LAYER_TAP <= keycode && keycode <= QK_ONE_SHOT_LAYER_MAX);
}

static void custom_combo_dispatch_record(keyrecord_t record, uint16_t keycode) {
    custom_combo_replaying = true;
    record.keycode = keycode;
#ifndef NO_ACTION_TAPPING
    action_tapping_process(record);
#else
    process_record(&record);
#endif
    custom_combo_replaying = false;
}

static void custom_combo_tap_keycode(uint16_t keycode) {
    keyrecord_t press = {
        .event = {
            .key = (keypos_t){0, 0},
            .pressed = true,
            .time = timer_read()
        },
        .tap = {
            .count = 0,
            .interrupted = false
        }
    };
    keyrecord_t release = press;
    release.event.pressed = false;
    release.event.time = timer_read();
    custom_combo_dispatch_record(press, keycode);
    custom_combo_dispatch_record(release, keycode);
}

static void custom_combo_clear_pending(void) {
    custom_combo_pending = false;
    custom_combo_pending_passthrough = false;
    custom_combo_pending_keycode = KC_NO;
    custom_combo_pending_timer = 0;
    custom_combo_pending_term = 0;
}

static void custom_combo_flush_pending_press(void) {
    if (!custom_combo_pending) {
        return;
    }
    if (!custom_combo_pending_passthrough) {
        custom_combo_dispatch_record(custom_combo_pending_record, custom_combo_pending_keycode);
    }
    custom_combo_clear_pending();
}

bool process_custom_combo(uint16_t keycode, keyrecord_t *record) {
    if (custom_combo_replaying) {
        return true;
    }

    keypos_t key = record->event.key;

    if (custom_combo_active && !record->event.pressed) {
        for (uint8_t i = 0; i < 2; ++i) {
            if (custom_combo_active_down[i] && custom_combo_keypos_equal(custom_combo_active_keys[i], key)) {
                custom_combo_active_down[i] = false;
                const bool swallow = custom_combo_swallow_release[i];
                if (!custom_combo_active_down[0] && !custom_combo_active_down[1]) {
                    custom_combo_active = false;
                }
                return !swallow;
            }
        }
    }

    if (custom_combo_pending && custom_combo_pending_term > 0
        && timer_elapsed(custom_combo_pending_timer) > custom_combo_pending_term) {
        custom_combo_flush_pending_press();
    }

    if (!record->event.pressed) {
        if (custom_combo_pending && custom_combo_keypos_equal(custom_combo_pending_record.event.key, key)) {
            if (!custom_combo_pending_passthrough) {
                custom_combo_dispatch_record(custom_combo_pending_record, custom_combo_pending_keycode);
            }
            custom_combo_clear_pending();
        }
        return true;
    }

    if (custom_combo_pending) {
        int16_t combo_index = custom_combo_find_match(custom_combo_pending_record.event.key, key);
        if (combo_index >= 0) {
            emit_custom_combo((uint16_t)combo_index);
            custom_combo_active = true;
            custom_combo_active_keys[0] = custom_combo_pending_record.event.key;
            custom_combo_active_keys[1] = key;
            custom_combo_active_down[0] = true;
            custom_combo_active_down[1] = true;
            custom_combo_swallow_release[0] = !custom_combo_pending_passthrough;
            custom_combo_swallow_release[1] = true;
            custom_combo_clear_pending();
            return false;
        }

        custom_combo_flush_pending_press();
    }

    if (!custom_combo_has_candidate(key)) {
        return true;
    }

    custom_combo_pending = true;
    custom_combo_pending_passthrough = custom_combo_key_must_passthrough(keycode);
    custom_combo_pending_record = *record;
    custom_combo_pending_keycode = keycode;
    custom_combo_pending_timer = timer_read();
    custom_combo_pending_term = custom_combo_term_for_key(key);
    return custom_combo_pending_passthrough;
}

void custom_combo_task(void) {
    if (custom_combo_pending && !custom_combo_pending_passthrough && custom_combo_pending_term > 0
        && timer_elapsed(custom_combo_pending_timer) > custom_combo_pending_term) {
        custom_combo_flush_pending_press();
    }
}

static void emit_custom_combo(uint16_t combo_index) {
    switch (combo_index) {
    case SUB_1: magic_decode_send(764); break; // "qu"
    case SUB_2: magic_decode_send(410); break; // "gregor.zeitlinger@grafana.com"
    case SUB_3: magic_decode_send(968); break; // "zeitlinger@gmail.com"
    case SUB_4: magic_decode_send(430); break; // "gregor@zeitlinger.de"
    case SUB_5: magic_decode_send(32); break; // "Grafana"
    case SUB_6: magic_decode_send(38); break; // "Grafana Labs"
    case C_BASE_KC_B: custom_combo_tap_keycode(layer == _LEFT ? S(KC_B) : KC_B); break;
    case C_BASE_KC_G: custom_combo_tap_keycode(layer == _LEFT ? S(KC_G) : KC_G); break;
    case C_BASE_KC_K: custom_combo_tap_keycode(layer == _LEFT ? S(KC_K) : KC_K); break;
    case C_BASE_KC_M: custom_combo_tap_keycode(layer == _LEFT ? S(KC_M) : KC_M); break;
    case C_BASE_KC_P: custom_combo_tap_keycode(layer == _LEFT ? S(KC_P) : KC_P); break;
    case C_BASE_KC_V: custom_combo_tap_keycode(layer == _LEFT ? S(KC_V) : KC_V); break;
    case C_BASE_ING: custom_combo_tap_keycode(ING); break;
    case C_BASE_MAGIC_C: custom_combo_tap_keycode(MAGIC_C); break;
    case C_BASE_MAGIC_D: custom_combo_tap_keycode(MAGIC_D); break;
    case C_BASE_MAGIC_E: custom_combo_tap_keycode(MAGIC_E); break;
    case C_BASE_MAGIC_F: custom_combo_tap_keycode(MAGIC_F); break;
    case C_BASE_MAGIC_G: custom_combo_tap_keycode(MAGIC_G); break;
    case C_BASE_MAGIC_H: custom_combo_tap_keycode(MAGIC_H); break;
    case C_BASE_MAGIC_I: custom_combo_tap_keycode(MAGIC_I); break;
    case C_BASE_MAGIC_J: custom_combo_tap_keycode(MAGIC_J); break;
    case C_BASE_MAGIC_K: custom_combo_tap_keycode(MAGIC_K); break;
    case C_FNSYM_KC_AMPR: custom_combo_tap_keycode(KC_AMPR); break;
    case C_FNSYM_KC_ASTR: custom_combo_tap_keycode(KC_ASTR); break;
    case C_FNSYM_KC_BACKSLASH: custom_combo_tap_keycode(KC_BACKSLASH); break;
    case C_FNSYM_KC_CIRC: custom_combo_tap_keycode(KC_CIRC); break;
    case C_FNSYM_KC_DLR: custom_combo_tap_keycode(KC_DLR); break;
    case C_FNSYM_KC_F11: custom_combo_tap_keycode(KC_F11); break;
    case C_FNSYM_KC_HASH: custom_combo_tap_keycode(KC_HASH); break;
    case C_FNSYM_KC_KP_MINUS: custom_combo_tap_keycode(KC_KP_MINUS); break;
    case C_FNSYM_KC_KP_PLUS: custom_combo_tap_keycode(KC_KP_PLUS); break;
    case C_FNSYM_KC_LABK: custom_combo_tap_keycode(KC_LABK); break;
    case C_FNSYM_KC_LCBR: custom_combo_tap_keycode(KC_LCBR); break;
    case C_FNSYM_KC_LGUI: custom_combo_tap_keycode(KC_LGUI); break;
    case C_FNSYM_KC_LPRN: custom_combo_tap_keycode(KC_LPRN); break;
    case C_FNSYM_KC_MINUS: custom_combo_tap_keycode(KC_MINUS); break;
    case C_FNSYM_KC_PERC: custom_combo_tap_keycode(KC_PERC); break;
    case C_FNSYM_KC_PIPE: custom_combo_tap_keycode(KC_PIPE); break;
    case C_FNSYM_KC_RABK: custom_combo_tap_keycode(KC_RABK); break;
    case C_FNSYM_KC_RCBR: custom_combo_tap_keycode(KC_RCBR); break;
    case C_FNSYM_KC_RPRN: custom_combo_tap_keycode(KC_RPRN); break;
    case C_FNSYM_KC_SLASH: custom_combo_tap_keycode(KC_SLASH); break;
    case C_FNSYM_KC_TILD: custom_combo_tap_keycode(KC_TILD); break;
    case C_FNSYM_LT_NUM2KC_EQUAL: custom_combo_tap_keycode(LT(_NUM2,KC_EQUAL)); break;
    case C_FNSYM_MO_NUM: custom_combo_tap_keycode(MO(_NUM)); break;
    case C_LEFT_KC_COLN: custom_combo_tap_keycode(KC_COLN); break;
    case C_NAV_AKC_F12: custom_combo_tap_keycode(A(KC_F12)); break;
    case C_NAV_CKC_A: custom_combo_tap_keycode(C(KC_A)); break;
    case C_NAV_CKC_B: custom_combo_tap_keycode(C(KC_B)); break;
    case C_NAV_CKC_C: custom_combo_tap_keycode(C(KC_C)); break;
    case C_NAV_CKC_D: custom_combo_tap_keycode(C(KC_D)); break;
    case C_NAV_CKC_E: custom_combo_tap_keycode(C(KC_E)); break;
    case C_NAV_CKC_F12: custom_combo_tap_keycode(C(KC_F12)); break;
    case C_NAV_CKC_K: custom_combo_tap_keycode(C(KC_K)); break;
    case C_NAV_CKC_P: custom_combo_tap_keycode(C(KC_P)); break;
    case C_NAV_CKC_SLASH: custom_combo_tap_keycode(C(KC_SLASH)); break;
    case C_NAV_CKC_V: custom_combo_tap_keycode(C(KC_V)); break;
    case C_NAV_CKC_W: custom_combo_tap_keycode(C(KC_W)); break;
    case C_NAV_CKC_X: custom_combo_tap_keycode(C(KC_X)); break;
    case C_NAV_CKC_Y: custom_combo_tap_keycode(C(KC_Y)); break;
    case C_NAV_CKC_Z: custom_combo_tap_keycode(C(KC_Z)); break;
    case C_NAV_KC_END: custom_combo_tap_keycode(KC_END); break;
    case C_NAV_KC_HOME: custom_combo_tap_keycode(KC_HOME); break;
    case C_NAV_KC_PGDN: custom_combo_tap_keycode(KC_PGDN); break;
    case C_NAV_KC_PGUP: custom_combo_tap_keycode(KC_PGUP); break;
    case C_NAV_LCAKC_B: custom_combo_tap_keycode(LCA(KC_B)); break;
    case C_NAV_RCSKC_C: custom_combo_tap_keycode(RCS(KC_C)); break;
    case C_NAV_RCSKC_N: custom_combo_tap_keycode(RCS(KC_N)); break;
    case C_NAV_RCSKC_V: custom_combo_tap_keycode(RCS(KC_V)); break;
    case C_NAV_RCSKC_Z: custom_combo_tap_keycode(RCS(KC_Z)); break;
    case C_NAV_UMUMLAUT_S: custom_combo_tap_keycode(UM(UMLAUT_s)); break;
    case C_NAV_UPUMLAUT_AUMLAUT_A: custom_combo_tap_keycode(UP(UMLAUT_a, UMLAUT_A)); break;
    case C_NAV_UPUMLAUT_OUMLAUT_O: custom_combo_tap_keycode(UP(UMLAUT_o, UMLAUT_O)); break;
    case C_NAV_UPUMLAUT_UUMLAUT_U: custom_combo_tap_keycode(UP(UMLAUT_u, UMLAUT_U)); break;
    case C_NUM_AKC_F1: custom_combo_tap_keycode(A(KC_F1)); break;
    case C_NUM_CKC_G: custom_combo_tap_keycode(C(KC_G)); break;
    case C_NUM_LCAKC_L: custom_combo_tap_keycode(LCA(KC_L)); break;
    case C_NUM_LSAKC_B: custom_combo_tap_keycode(LSA(KC_B)); break;
    case C_NUM_LSAKC_S: custom_combo_tap_keycode(LSA(KC_S)); break;
    case C_NUM_LSAKC_X: custom_combo_tap_keycode(LSA(KC_X)); break;
    case C_NUM_RCSKC_V: custom_combo_tap_keycode(RCS(KC_V)); break;
    case C_RIGHT_KC_AT: custom_combo_tap_keycode(KC_AT); break;
    case C_RIGHT_KC_COMMA: custom_combo_tap_keycode(KC_COMMA); break;
    case C_RIGHT_KC_DOT: custom_combo_tap_keycode(KC_DOT); break;
    case C_RIGHT_KC_EXLM: custom_combo_tap_keycode(KC_EXLM); break;
    case C_RIGHT_KC_GRAVE: custom_combo_tap_keycode(KC_GRAVE); break;
    case C_RIGHT_KC_QUES: custom_combo_tap_keycode(KC_QUES); break;
    case C_RIGHT_KC_QUOTE: custom_combo_tap_keycode(KC_QUOTE); break;
    case C_RIGHT_KC_UNDS: custom_combo_tap_keycode(KC_UNDS); break;
    case C_RIGHT_N_T: custom_combo_tap_keycode(N_T); break;
    case C_RIGHT_RCSKC_F: custom_combo_tap_keycode(RCS(KC_F)); break;
    case C_RIGHT_RCSKC_R: custom_combo_tap_keycode(RCS(KC_R)); break;
    default: break;
    }
}
