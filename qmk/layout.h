#include QMK_KEYBOARD_H


/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/uncommitted changes/README.md using https://github.com/zeitlinger/keyboard/blob/uncommitted changes/generateKeyboard.kt
 */

#define VERSION_STRING "https://github.com/zeitlinger/keyboard/blob/uncommitted changes/README.md"

#define _BASE 0
#define _LEFT 1
#define _RIGHT 2
#define _LMODS 3
#define _RMODS 4
#define _NAV 5
#define _NAV2 6
#define _FN 7
#define _NUM 8
#define _MEDIA 9

enum custom_keycodes {
	NEXT_TAB = SAFE_RANGE,
	NEXT_WINDOW,
    DOT_SPC,
    N_T,
    PRINT_VERSION,
    CAPS_WORDS,
    SNAKE_CASE,
    SCREAMING_SNAKE_CASE,
    CAMEL_CASE,
    PASCAL_CASE,
    SLASH_CASE,
    DOT_CASE,
    KEBAP_CASE,
    DEAD1,
    DEAD2,
    DEAD3,
    _LMODS_S,
    _LMODS_C,
    _LMODS_A,
    _RMODS_A,
    _RMODS_C,
    _RMODS_S,
    _TAP_C_CKC_C,
    _TAP_C_CKC_K,
    _TAP_C_KC_LCBR,
    _TAP_C_KC_RCBR,
    ALT_KC_D,
    ALT_KC_H,
    ALT_KC_J,
    ALT_KC_Q,
    ALT_KC_T,
    ALT_KC_V,
    ALT_KC_Z,
    ALT_KC_SPC,
    ALT_KC_TAB,
    ALT_KC_ENT,
    ALT_KC_COMMA
};

#define _HANDLER_NEXT_TAB NEXT_TAB
#define _HANDLER_NEXT_WINDOW NEXT_WINDOW
#define _HANDLER_DOT_SPC DOT_SPC
#define _HANDLER_N_T N_T
#define _HANDLER_PRINT_VERSION PRINT_VERSION
#define _HANDLER_CAPS_WORDS CAPS_WORDS
#define _HANDLER_SNAKE_CASE SNAKE_CASE
#define _HANDLER_SCREAMING_SNAKE_CASE SCREAMING_SNAKE_CASE
#define _HANDLER_CAMEL_CASE CAMEL_CASE
#define _HANDLER_PASCAL_CASE PASCAL_CASE
#define _HANDLER_SLASH_CASE SLASH_CASE
#define _HANDLER_DOT_CASE DOT_CASE
#define _HANDLER_KEBAP_CASE KEBAP_CASE
#define _HANDLER_DEAD1 DEAD1
#define _HANDLER_DEAD2 DEAD2
#define _HANDLER_DEAD3 DEAD3
#define _HANDLER__LMODS_S _LMODS_S
#define _HANDLER__LMODS_C _LMODS_C
#define _HANDLER__LMODS_A _LMODS_A
#define _HANDLER__RMODS_A _RMODS_A
#define _HANDLER__RMODS_C _RMODS_C
#define _HANDLER__RMODS_S _RMODS_S
#define _HANDLER__TAP_C_CKC_C LT(_NAV2,_TAP_C_CKC_C)
#define _HANDLER__TAP_C_CKC_K _TAP_C_CKC_K
#define _HANDLER__TAP_C_KC_LCBR CTL_T(_TAP_C_KC_LCBR)
#define _HANDLER__TAP_C_KC_RCBR ALT_T(_TAP_C_KC_RCBR)
#define _HANDLER_ALT_KC_D ALT_KC_D
#define _HANDLER_ALT_KC_H ALT_KC_H
#define _HANDLER_ALT_KC_J ALT_KC_J
#define _HANDLER_ALT_KC_Q ALT_KC_Q
#define _HANDLER_ALT_KC_T ALT_KC_T
#define _HANDLER_ALT_KC_V ALT_KC_V
#define _HANDLER_ALT_KC_Z ALT_KC_Z
#define _HANDLER_ALT_KC_SPC ALT_KC_SPC
#define _HANDLER_ALT_KC_TAB ALT_KC_TAB
#define _HANDLER_ALT_KC_ENT ALT_KC_ENT
#define _HANDLER_ALT_KC_COMMA ALT_KC_COMMA

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT_split_3x5_2(
                          KC_ESC,                 KC_P,                 KC_M,    QK_ALT_REPEAT_KEY, KC_NO, KC_NO,                DEAD2,        QK_REPEAT_KEY,    QK_ALT_REPEAT_KEY,                KC_NO,
                            KC_S,                 KC_C,                 KC_N,                 KC_T, KC_NO, KC_NO,                 KC_A,                 KC_E,                 KC_I,                 KC_H,
                      MO(_RIGHT),                 KC_F,                 KC_L,                 KC_D, KC_NO, KC_NO,                 KC_U,                 KC_O,                 KC_Y,            MO(_LEFT),
                                        TT(_NAV),                 KC_R,               KC_SPC,              MO(_FN)),
	[_LEFT] = LAYOUT_split_3x5_2(
                       S(KC_ESC),              S(KC_P),              S(KC_M), S(QK_ALT_REPEAT_KEY), KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                         S(KC_S),              S(KC_C),              S(KC_N),              S(KC_T), KC_NO, KC_NO,                 KC_5,                 KC_6,           MO(_MEDIA),                KC_NO,
                         KC_COLN,              S(KC_F),              S(KC_L),              S(KC_D), KC_NO, KC_NO, LM(_LMODS, MOD_LSFT), LM(_LMODS, MOD_LCTL), LM(_LMODS, MOD_LALT),                KC_NO,
                                            KC_4,              S(KC_R),                 KC_7,                 KC_8),
	[_RIGHT] = LAYOUT_split_3x5_2(
                           KC_NO,                KC_NO,                KC_NO,                KC_NO, KC_NO, KC_NO,                DEAD3,              KC_DQUO,          A(KC_RIGHT),                KC_NO,
                           KC_NO,             TO(_NUM),                 KC_9,                 KC_0, KC_NO, KC_NO,              S(KC_A),              S(KC_E),              S(KC_I),              S(KC_H),
                           KC_NO, LM(_RMODS, MOD_LALT), LM(_RMODS, MOD_LCTL), LM(_RMODS, MOD_LSFT), KC_NO, KC_NO,              S(KC_U),              S(KC_O),              S(KC_Y),              KC_QUES,
                                            KC_1,                 KC_2,               KC_SPC,                 KC_3),
	[_LMODS] = LAYOUT_split_3x5_2(
                          KC_ESC,                 KC_P,                 KC_M,    QK_ALT_REPEAT_KEY, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                            KC_S,                 KC_C,                 KC_N,                 KC_T, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                           KC_NO,                 KC_F,                 KC_L,                 KC_D, KC_NO, KC_NO, LM(_LMODS, MOD_LSFT), LM(_LMODS, MOD_LCTL), LM(_LMODS, MOD_LALT),                KC_NO,
                                        TT(_NAV),                 KC_R,                KC_NO,                KC_NO),
	[_RMODS] = LAYOUT_split_3x5_2(
                           KC_NO,                KC_NO,                KC_NO,                KC_NO, KC_NO, KC_NO,                DEAD2,        QK_REPEAT_KEY,    QK_ALT_REPEAT_KEY,                KC_NO,
                           KC_NO,                KC_NO,                KC_NO,                KC_NO, KC_NO, KC_NO,                 KC_A,                 KC_E,                 KC_I,                 KC_H,
                           KC_NO, LM(_RMODS, MOD_LALT), LM(_RMODS, MOD_LCTL), LM(_RMODS, MOD_LSFT), KC_NO, KC_NO,                 KC_U,                 KC_O,                 KC_Y,                KC_NO,
                                           KC_NO,                KC_NO,               KC_SPC,                KC_NO),
	[_NAV] = LAYOUT_split_3x5_2(
                          KC_SPC,              C(KC_X),              C(KC_V),            RCS(KC_Z), KC_NO, KC_NO,              KC_MUTE,               KC_ESC,               KC_INS,                KC_NO,
            LT(_NAV2,_TAP_C_CKC_C),              KC_LALT,              KC_LCTL,              KC_LSFT, KC_NO, KC_NO,              KC_LEFT,              KC_DOWN,                KC_UP,             KC_RIGHT,
                         C(KC_Z),              C(KC_W),             NEXT_TAB,          NEXT_WINDOW, KC_NO, KC_NO,               KC_ENT,              KC_BSPC,               KC_DEL,               KC_SPC,
                                       TO(_BASE),                KC_NO,               KC_TAB,            S(KC_TAB)),
	[_NAV2] = LAYOUT_split_3x5_2(
                           KC_NO,                KC_NO,                KC_NO,                KC_NO, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                           KC_NO,              KC_LALT,              KC_LCTL,              KC_LSFT, KC_NO, KC_NO,              KC_HOME,              KC_PGDN,              KC_PGUP,               KC_END,
                           KC_NO,                KC_NO,                KC_NO,                KC_NO, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                                           KC_NO,                KC_NO,                KC_NO,                KC_NO),
	[_FN] = LAYOUT_split_3x5_2(
                           KC_NO,               KC_F10,                KC_F9,              KC_LGUI, KC_NO, KC_NO,                KC_NO,              KC_LPRN,              KC_RPRN,                KC_NO,
                           KC_F4,         ALT_T(KC_F3),         CTL_T(KC_F2),         SFT_T(KC_F1), KC_NO, KC_NO,      SFT_T(KC_MINUS), CTL_T(_TAP_C_KC_LCBR), ALT_T(_TAP_C_KC_RCBR), LT(_NUM,KC_SEMICOLON),
                           KC_F8,                KC_F7,                KC_F6,                KC_F5, KC_NO, KC_NO,              KC_UNDS,             KC_EQUAL,              KC_PLUS,             KC_SLASH,
                                          KC_F11,               KC_F12,                KC_NO,                KC_NO),
	[_NUM] = LAYOUT_split_3x5_2(
                           KC_NO,               KC_DOT,                 KC_9,                KC_NO, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                            KC_4,                 KC_3,                 KC_2,                 KC_1, KC_NO, KC_NO,              KC_LSFT,      CTL_T(KC_COMMA),        ALT_T(KC_DOT),                KC_NO,
                            KC_8,                 KC_7,                 KC_6,                 KC_5, KC_NO, KC_NO,                KC_NO,              KC_BSPC,               KC_DEL,                KC_NO,
                                       TO(_BASE),                 KC_0,               KC_TAB,            S(KC_TAB)),
	[_MEDIA] = LAYOUT_split_3x5_2(
                           KC_NO,              KC_BRID,              KC_BRIU,                KC_NO, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                         KC_PSCR,              KC_VOLD,              KC_VOLU,              KC_MUTE, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                   PRINT_VERSION,              KC_MPRV,              KC_MNXT,              KC_MPLY, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                                           KC_NO,                KC_NO,                KC_NO,                KC_NO),
};
