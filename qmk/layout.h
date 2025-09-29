#include QMK_KEYBOARD_H


/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

#define VERSION_STRING "use target/qmk to build the firmware to get the git version"

#define _BASE 0
#define _NAV2 1
#define _LEFT 2
#define _RIGHT 3
#define _LMODS 4
#define _RMODS 5
#define _NAV 6
#define _FNSYM 7
#define _NUM 8
#define _NUM2 9
#define _ANUM 10
#define _MM 11
#define _CASE 12
#define _WORDS 13

enum custom_keycodes {
	U00E4 = SAFE_RANGE,
	U00F6,
    U00FC,
    U00C4,
    U00D6,
    U00DC,
    U00DF,
    NEXT_TAB,
    NEXT_WINDOW,
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
    ST_WORDS_1_2,
    ST_WORDS_2_0,
    ST_WORDS_2_1,
    ST_WORDS_2_2,
    ST_WORDS_2_3,
    ALT_KC_H,
    ALT_KC_Q,
    ALT_KC_T,
    ALT_KC_V,
    ALT_KC_Z,
    ALT_KC_SPC,
    ALT_KC_TAB,
    ALT_KC_ENT,
    ALT_KC_COMMA
};

#define _HANDLER_U00E4 U00E4
#define _HANDLER_U00F6 U00F6
#define _HANDLER_U00FC U00FC
#define _HANDLER_U00C4 U00C4
#define _HANDLER_U00D6 U00D6
#define _HANDLER_U00DC U00DC
#define _HANDLER_U00DF U00DF
#define _HANDLER_NEXT_TAB NEXT_TAB
#define _HANDLER_NEXT_WINDOW NEXT_WINDOW
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
#define _HANDLER_ST_WORDS_1_2 ST_WORDS_1_2
#define _HANDLER_ST_WORDS_2_0 ST_WORDS_2_0
#define _HANDLER_ST_WORDS_2_1 ST_WORDS_2_1
#define _HANDLER_ST_WORDS_2_2 ST_WORDS_2_2
#define _HANDLER_ST_WORDS_2_3 ST_WORDS_2_3
#define _HANDLER_ALT_KC_H ALT_KC_H
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
                          KC_ESC,                 KC_P,                 KC_M,                DEAD3, KC_NO, KC_NO,                DEAD2,        QK_REPEAT_KEY,    QK_ALT_REPEAT_KEY,                DEAD1,
                            KC_S,                 KC_C,                 KC_N,                 KC_T, KC_NO, KC_NO,                 KC_A,                 KC_E,                 KC_I,                 KC_H,
                      MO(_RIGHT),                 KC_F,                 KC_L,                 KC_D, KC_NO, KC_NO,                 KC_U,                 KC_O,                 KC_Y,            MO(_LEFT),
                                        MO(_NAV),                 KC_R,               KC_SPC,           MO(_FNSYM)),
	[_NAV2] = LAYOUT_split_3x5_2(
                           KC_NO,              C(KC_X),              C(KC_V),            RCS(KC_Z), KC_NO, KC_NO,                KC_NO,               KC_ESC,               KC_INS,                KC_NO,
                         C(KC_C),              KC_LALT,              KC_LCTL,              KC_LSFT, KC_NO, KC_NO,              KC_LEFT,              KC_DOWN,                KC_UP,             KC_RIGHT,
                         C(KC_Z),              C(KC_W),               KC_TAB,              KC_LGUI, KC_NO, KC_NO,               KC_ENT,              KC_BSPC,               KC_DEL,               KC_TAB,
                                       MO(_NUM2),            DF(_BASE),               KC_SPC,           MO(_FNSYM)),
	[_LEFT] = LAYOUT_split_3x5_2(
                       S(KC_ESC),              S(KC_P),              S(KC_M),             S(DEAD3), KC_NO, KC_NO,                DEAD1,                KC_NO,                KC_NO,                KC_NO,
                         S(KC_S),              S(KC_C),              S(KC_N),              S(KC_T), KC_NO, KC_NO,            MO(_CASE),           MO(_WORDS),              MO(_MM),                KC_NO,
                         KC_COLN,              S(KC_F),              S(KC_L),              S(KC_D), KC_NO, KC_NO, LM(_LMODS, MOD_LSFT), LM(_LMODS, MOD_LCTL), LM(_LMODS, MOD_LALT),                KC_NO,
                                    KC_SEMICOLON,              S(KC_R),            MO(_ANUM),             MO(_NUM)),
	[_RIGHT] = LAYOUT_split_3x5_2(
                           KC_NO,                KC_NO,                KC_NO,                KC_NO, KC_NO, KC_NO,                DEAD3,              KC_DQUO,          A(KC_RIGHT),             S(DEAD1),
                           KC_NO,                KC_NO,              C(KC_F),              C(KC_R), KC_NO, KC_NO,              S(KC_A),              S(KC_E),              S(KC_I),              S(KC_H),
                           KC_NO, LM(_RMODS, MOD_LALT), LM(_RMODS, MOD_LCTL),           MO(_WORDS), KC_NO, KC_NO,              S(KC_U),              S(KC_O),              S(KC_Y),              KC_UNDS,
                                        A(KC_F7),              C(KC_N),      KC_LEFT_BRACKET,     KC_RIGHT_BRACKET),
	[_LMODS] = LAYOUT_split_3x5_2(
                          KC_ESC,                 KC_P,                 KC_M,                DEAD3, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                            KC_S,                 KC_C,                 KC_N,                 KC_T, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                        KC_MINUS,                 KC_F,                 KC_L,                 KC_D, KC_NO, KC_NO, LM(_LMODS, MOD_LSFT), LM(_LMODS, MOD_LCTL), LM(_LMODS, MOD_LALT),                KC_NO,
                                           KC_NO,                 KC_R,                KC_NO,                KC_NO),
	[_RMODS] = LAYOUT_split_3x5_2(
                           KC_NO,                KC_NO,                KC_NO,                KC_NO, KC_NO, KC_NO,                DEAD2,        QK_REPEAT_KEY,    QK_ALT_REPEAT_KEY,                DEAD1,
                           KC_NO,                KC_NO,                KC_NO,                KC_NO, KC_NO, KC_NO,                 KC_A,                 KC_E,                 KC_I,                 KC_H,
                           KC_NO, LM(_RMODS, MOD_LALT), LM(_RMODS, MOD_LCTL), LM(_RMODS, MOD_LSFT), KC_NO, KC_NO,                 KC_U,                 KC_O,                 KC_Y,             KC_EQUAL,
                                           KC_NO,                KC_NO,      KC_LEFT_BRACKET,     KC_RIGHT_BRACKET),
	[_NAV] = LAYOUT_split_3x5_2(
                           KC_NO,              C(KC_X),              C(KC_V),            RCS(KC_Z), KC_NO, KC_NO,                KC_NO,               KC_ESC,               KC_INS,                KC_NO,
                         C(KC_C),              KC_LALT,              KC_LCTL,              KC_LSFT, KC_NO, KC_NO,              KC_LEFT,              KC_DOWN,                KC_UP,             KC_RIGHT,
                         C(KC_Z),              C(KC_W),             NEXT_TAB,          NEXT_WINDOW, KC_NO, KC_NO,               KC_ENT,              KC_BSPC,               KC_DEL,               KC_TAB,
                                           KC_NO,                KC_NO,               KC_SPC,                KC_NO),
	[_FNSYM] = LAYOUT_split_3x5_2(
                           DEAD2,               KC_F10,                KC_F9,                DEAD2, KC_NO, KC_NO,                DEAD3,              KC_LPRN,              KC_RPRN,                DEAD1,
                           KC_F4,                KC_F3,                KC_F2,                KC_F1, KC_NO, KC_NO,              KC_LSFT,              KC_LCTL,              KC_LALT,   LT(_NUM2,KC_EQUAL),
                           KC_F8,                KC_F7,                KC_F6,                KC_F5, KC_NO, KC_NO,             KC_MINUS,              KC_LCBR,              KC_RCBR,             MO(_NUM),
                                           KC_NO,               KC_F12,                KC_NO,                KC_NO),
	[_NUM] = LAYOUT_split_3x5_2(
                           DEAD1,             KC_COMMA,               KC_DOT,                DEAD2, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                            KC_4,                 KC_3,                 KC_2,                 KC_1, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                            KC_8,                 KC_7,                 KC_6,                 KC_5, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                                            KC_9,                 KC_0,                KC_NO,                KC_NO),
	[_NUM2] = LAYOUT_split_3x5_2(
                           DEAD1,             KC_COMMA,               KC_DOT,                DEAD2, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                            KC_4,                 KC_3,                 KC_2,                 KC_1, KC_NO, KC_NO,              KC_LSFT,              KC_LCTL,              KC_LALT,                KC_NO,
                            KC_8,                 KC_7,                 KC_6,                 KC_5, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                                            KC_9,                 KC_0,                KC_NO,                KC_NO),
	[_ANUM] = LAYOUT_split_3x5_2(
                           KC_NO,                KC_NO,                KC_NO,                KC_NO, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                         A(KC_4),              A(KC_3),              A(KC_2),              A(KC_1), KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                         A(KC_8),              A(KC_7),              A(KC_6),              A(KC_5), KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                                         A(KC_9),              A(KC_0),                KC_NO,                KC_NO),
	[_MM] = LAYOUT_split_3x5_2(
                           KC_NO,              KC_BRID,              KC_BRIU,                KC_NO, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                         KC_PSCR,              KC_VOLD,              KC_VOLU,              KC_MUTE, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                   PRINT_VERSION,              KC_MPRV,              KC_MNXT,              KC_MPLY, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                                           KC_NO,                KC_NO,                KC_NO,                KC_NO),
	[_CASE] = LAYOUT_split_3x5_2(
                           KC_NO,                KC_NO,           KEBAP_CASE,                KC_NO, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                      SLASH_CASE,           CAPS_WORDS,           SNAKE_CASE,           CAMEL_CASE, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                         KC_CAPS,             DOT_CASE, SCREAMING_SNAKE_CASE,          PASCAL_CASE, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                                           KC_NO,                KC_NO,                KC_NO,                KC_NO),
	[_WORDS] = LAYOUT_split_3x5_2(
                           KC_NO,                KC_NO,                KC_NO,                KC_NO, KC_NO, KC_NO,                KC_NO,                KC_NO,                KC_NO,                KC_NO,
                           KC_NO,                KC_NO,         ST_WORDS_1_2,                KC_NO, KC_NO, KC_NO,                U00E4,                U00F6,                U00FC,                U00DF,
                    ST_WORDS_2_0,         ST_WORDS_2_1,         ST_WORDS_2_2,         ST_WORDS_2_3, KC_NO, KC_NO,                U00C4,                U00D6,                U00DC,                KC_NO,
                                           KC_NO,                KC_NO,                KC_NO,                KC_NO),
};
