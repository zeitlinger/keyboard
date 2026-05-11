// file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
#include QMK_KEYBOARD_H
#include "layout.h"

const uint16_t PROGMEM C_BASE_ING_combo[] = {DEAD2, KC_A, COMBO_END};
const uint16_t PROGMEM C_BASE_KC_B_combo[] = {KC_C, KC_F, COMBO_END};
const uint16_t PROGMEM C_BASE_KC_G_combo[] = {KC_L, KC_N, COMBO_END};
const uint16_t PROGMEM C_BASE_KC_K_combo[] = {KC_D, KC_T, COMBO_END};
const uint16_t PROGMEM C_BASE_KC_M_combo[] = {KC_N, KC_W, COMBO_END};
const uint16_t PROGMEM C_BASE_KC_P_combo[] = {KC_C, KC_X, COMBO_END};
const uint16_t PROGMEM C_BASE_KC_V_combo[] = {DEAD3, KC_T, COMBO_END};
const uint16_t PROGMEM C_BASE_MAGIC_C_combo[] = {KC_ESC, KC_S, COMBO_END};
const uint16_t PROGMEM C_BASE_MAGIC_D_combo[] = {KC_E, MAGIC_A, COMBO_END};
const uint16_t PROGMEM C_BASE_MAGIC_E_combo[] = {KC_I, MAGIC_B, COMBO_END};
const uint16_t PROGMEM C_BASE_MAGIC_F_combo[] = {DEAD1, KC_H, COMBO_END};
const uint16_t PROGMEM C_BASE_MAGIC_G_combo[] = {KC_S, MO(_RIGHT), COMBO_END};
const uint16_t PROGMEM C_BASE_MAGIC_H_combo[] = {KC_A, KC_U, COMBO_END};
const uint16_t PROGMEM C_BASE_MAGIC_I_combo[] = {KC_E, KC_O, COMBO_END};
const uint16_t PROGMEM C_BASE_MAGIC_J_combo[] = {KC_I, KC_Y, COMBO_END};
const uint16_t PROGMEM C_BASE_MAGIC_K_combo[] = {KC_H, MO(_LEFT), COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_AMPR_combo[] = {KC_F3, KC_F7, COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_ASTR_combo[] = {KC_F2, KC_F9, COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_BACKSLASH_combo[] = {DEAD1, LT(_NUM2,KC_EQUAL), COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_CIRC_combo[] = {DEAD2, KC_F4, COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_DLR_combo[] = {KC_F4, KC_F8, COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_F11_combo[] = {KC_F2, KC_F6, COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_HASH_combo[] = {KC_LALT, KC_RCBR, COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_KP_MINUS_combo[] = {DEAD2, KC_F1, COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_KP_PLUS_combo[] = {KC_F1, KC_F5, COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_LABK_combo[] = {KC_LCTL, KC_LPRN, COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_LCBR_combo[] = {KC_O, MO(_FNSYM), COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_LGUI_combo[] = {DEAD3, KC_LSFT, COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_LPRN_combo[] = {MAGIC_A, MO(_FNSYM), COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_MINUS_combo[] = {KC_U, MO(_FNSYM), COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_PERC_combo[] = {LT(_NUM2,KC_EQUAL), MO(_NUM), COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_PIPE_combo[] = {KC_F10, KC_F3, COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_RABK_combo[] = {KC_LALT, KC_RPRN, COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_RCBR_combo[] = {KC_Y, MO(_FNSYM), COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_RPRN_combo[] = {MAGIC_B, MO(_FNSYM), COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_SLASH_combo[] = {KC_LCBR, KC_LCTL, COMBO_END};
const uint16_t PROGMEM C_FNSYM_KC_TILD_combo[] = {KC_LSFT, KC_MINUS, COMBO_END};
const uint16_t PROGMEM C_FNSYM_LT_NUM2KC_EQUAL_combo[] = {KC_H, MO(_FNSYM), COMBO_END};
const uint16_t PROGMEM C_FNSYM_MO_NUM_combo[] = {MO(_FNSYM), MO(_LEFT), COMBO_END};
const uint16_t PROGMEM C_LEFT_KC_COLN_combo[] = {KC_Z, S(KC_S), COMBO_END};
const uint16_t PROGMEM C_NAV_AKC_F12_combo[] = {KC_DOWN, KC_UP, COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_A_combo[] = {C(KC_V), KC_LCTL, COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_B_combo[] = {KC_LEFT, KC_UP, COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_C_combo[] = {KC_S, MO(_NAV), COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_D_combo[] = {KC_LCTL, NEXT_TAB, COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_E_combo[] = {C(KC_C), DEAD3, COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_F12_combo[] = {KC_BSPC, KC_ENT, COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_K_combo[] = {C(KC_W), KC_LALT, COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_P_combo[] = {KC_DEL, KC_ENT, COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_SLASH_combo[] = {KC_BSPC, KC_DEL, COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_V_combo[] = {KC_W, MO(_NAV), COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_W_combo[] = {KC_F, MO(_NAV), COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_X_combo[] = {KC_X, MO(_NAV), COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_Y_combo[] = {KC_LSFT, NEXT_WINDOW, COMBO_END};
const uint16_t PROGMEM C_NAV_CKC_Z_combo[] = {MO(_NAV), MO(_RIGHT), COMBO_END};
const uint16_t PROGMEM C_NAV_KC_END_combo[] = {KC_RIGHT, KC_TAB, COMBO_END};
const uint16_t PROGMEM C_NAV_KC_HOME_combo[] = {KC_ENT, KC_LEFT, COMBO_END};
const uint16_t PROGMEM C_NAV_KC_PGDN_combo[] = {KC_BSPC, KC_DOWN, COMBO_END};
const uint16_t PROGMEM C_NAV_KC_PGUP_combo[] = {KC_DEL, KC_UP, COMBO_END};
const uint16_t PROGMEM C_NAV_LCAKC_B_combo[] = {KC_DOWN, KC_LEFT, COMBO_END};
const uint16_t PROGMEM C_NAV_RCSKC_C_combo[] = {C(KC_C), C(KC_Z), COMBO_END};
const uint16_t PROGMEM C_NAV_RCSKC_N_combo[] = {C(KC_X), KC_LALT, COMBO_END};
const uint16_t PROGMEM C_NAV_RCSKC_V_combo[] = {KC_LSFT, RCS(KC_Z), COMBO_END};
const uint16_t PROGMEM C_NAV_RCSKC_Z_combo[] = {DEAD3, MO(_NAV), COMBO_END};
const uint16_t PROGMEM C_NAV_UMUMLAUT_S_combo[] = {DEAD2, KC_RIGHT, COMBO_END};
const uint16_t PROGMEM C_NAV_UPUMLAUT_AUMLAUT_A_combo[] = {KC_INS, KC_UP, COMBO_END};
const uint16_t PROGMEM C_NAV_UPUMLAUT_OUMLAUT_O_combo[] = {KC_DOWN, KC_ESC, COMBO_END};
const uint16_t PROGMEM C_NAV_UPUMLAUT_UUMLAUT_U_combo[] = {DEAD1, KC_LEFT, COMBO_END};
const uint16_t PROGMEM C_NUM_AKC_F1_combo[] = {KC_2, KC_9, COMBO_END};
const uint16_t PROGMEM C_NUM_CKC_G_combo[] = {KC_1, KC_5, COMBO_END};
const uint16_t PROGMEM C_NUM_LCAKC_L_combo[] = {KC_2, KC_6, COMBO_END};
const uint16_t PROGMEM C_NUM_LSAKC_B_combo[] = {KC_3, KC_7, COMBO_END};
const uint16_t PROGMEM C_NUM_LSAKC_S_combo[] = {KC_4, KC_8, COMBO_END};
const uint16_t PROGMEM C_NUM_LSAKC_X_combo[] = {KC_3, KC_COMMA, COMBO_END};
const uint16_t PROGMEM C_NUM_RCSKC_V_combo[] = {DEAD2, KC_1, COMBO_END};
const uint16_t PROGMEM C_RIGHT_KC_AT_combo[] = {DEAD3, S(KC_A), COMBO_END};
const uint16_t PROGMEM C_RIGHT_KC_COMMA_combo[] = {S(KC_E), S(KC_O), COMBO_END};
const uint16_t PROGMEM C_RIGHT_KC_DOT_combo[] = {S(KC_I), S(KC_Y), COMBO_END};
const uint16_t PROGMEM C_RIGHT_KC_EXLM_combo[] = {C(KC_F), DEAD1, COMBO_END};
const uint16_t PROGMEM C_RIGHT_KC_GRAVE_combo[] = {S(DEAD1), S(KC_H), COMBO_END};
const uint16_t PROGMEM C_RIGHT_KC_QUES_combo[] = {KC_Q, S(KC_I), COMBO_END};
const uint16_t PROGMEM C_RIGHT_KC_QUOTE_combo[] = {S(KC_A), S(KC_U), COMBO_END};
const uint16_t PROGMEM C_RIGHT_KC_UNDS_combo[] = {KC_J, S(KC_H), COMBO_END};
const uint16_t PROGMEM C_RIGHT_N_T_combo[] = {KC_DQUO, S(KC_E), COMBO_END};
const uint16_t PROGMEM C_RIGHT_RCSKC_F_combo[] = {C(KC_F), LM(_RMODS, MOD_LCTL), COMBO_END};
const uint16_t PROGMEM C_RIGHT_RCSKC_R_combo[] = {C(KC_R), LM(_RMODS, MOD_LSFT), COMBO_END};
const uint16_t PROGMEM DS_C_BASE_KC_B_combo[] = {KC_C, KC_F, MO(_LEFT), COMBO_END};
const uint16_t PROGMEM DS_C_BASE_KC_G_combo[] = {KC_L, KC_N, MO(_LEFT), COMBO_END};
const uint16_t PROGMEM DS_C_BASE_KC_K_combo[] = {KC_D, KC_T, MO(_LEFT), COMBO_END};
const uint16_t PROGMEM DS_C_BASE_KC_M_combo[] = {KC_N, KC_W, MO(_LEFT), COMBO_END};
const uint16_t PROGMEM DS_C_BASE_KC_P_combo[] = {KC_C, KC_X, MO(_LEFT), COMBO_END};
const uint16_t PROGMEM DS_C_BASE_KC_V_combo[] = {DEAD3, KC_T, MO(_LEFT), COMBO_END};
const uint16_t PROGMEM SUB_1_combo[] = {S(KC_ESC), S(KC_S), COMBO_END};
const uint16_t PROGMEM SUB_2_combo[] = {KC_MPLY, KC_MUTE, COMBO_END};
const uint16_t PROGMEM SUB_3_combo[] = {KC_MNXT, KC_VOLU, COMBO_END};
const uint16_t PROGMEM SUB_4_combo[] = {KC_MPRV, KC_VOLD, COMBO_END};
const uint16_t PROGMEM SUB_5_combo[] = {DEAD2, KC_PSCR, COMBO_END};
const uint16_t PROGMEM SUB_6_combo[] = {KC_PSCR, PRINT_VERSION, COMBO_END};
const uint16_t PROGMEM S_C_BASE_KC_B_combo[] = {S(KC_C), S(KC_F), COMBO_END};
const uint16_t PROGMEM S_C_BASE_KC_G_combo[] = {S(KC_L), S(KC_N), COMBO_END};
const uint16_t PROGMEM S_C_BASE_KC_K_combo[] = {S(KC_D), S(KC_T), COMBO_END};
const uint16_t PROGMEM S_C_BASE_KC_M_combo[] = {S(KC_N), S(KC_W), COMBO_END};
const uint16_t PROGMEM S_C_BASE_KC_P_combo[] = {S(KC_C), S(KC_X), COMBO_END};
const uint16_t PROGMEM S_C_BASE_KC_V_combo[] = {S(DEAD3), S(KC_T), COMBO_END};

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
    DS_C_BASE_KC_B,
    DS_C_BASE_KC_G,
    DS_C_BASE_KC_K,
    DS_C_BASE_KC_M,
    DS_C_BASE_KC_P,
    DS_C_BASE_KC_V,
    SUB_1,
    SUB_2,
    SUB_3,
    SUB_4,
    SUB_5,
    SUB_6,
    S_C_BASE_KC_B,
    S_C_BASE_KC_G,
    S_C_BASE_KC_K,
    S_C_BASE_KC_M,
    S_C_BASE_KC_P,
    S_C_BASE_KC_V
};

combo_t key_combos[] = {
    [C_BASE_ING] = COMBO(C_BASE_ING_combo, ING),
    [C_BASE_KC_B] = COMBO(C_BASE_KC_B_combo, KC_B),
    [C_BASE_KC_G] = COMBO(C_BASE_KC_G_combo, KC_G),
    [C_BASE_KC_K] = COMBO(C_BASE_KC_K_combo, KC_K),
    [C_BASE_KC_M] = COMBO(C_BASE_KC_M_combo, KC_M),
    [C_BASE_KC_P] = COMBO(C_BASE_KC_P_combo, KC_P),
    [C_BASE_KC_V] = COMBO(C_BASE_KC_V_combo, KC_V),
    [C_BASE_MAGIC_C] = COMBO(C_BASE_MAGIC_C_combo, MAGIC_C),
    [C_BASE_MAGIC_D] = COMBO(C_BASE_MAGIC_D_combo, MAGIC_D),
    [C_BASE_MAGIC_E] = COMBO(C_BASE_MAGIC_E_combo, MAGIC_E),
    [C_BASE_MAGIC_F] = COMBO(C_BASE_MAGIC_F_combo, MAGIC_F),
    [C_BASE_MAGIC_G] = COMBO(C_BASE_MAGIC_G_combo, MAGIC_G),
    [C_BASE_MAGIC_H] = COMBO(C_BASE_MAGIC_H_combo, MAGIC_H),
    [C_BASE_MAGIC_I] = COMBO(C_BASE_MAGIC_I_combo, MAGIC_I),
    [C_BASE_MAGIC_J] = COMBO(C_BASE_MAGIC_J_combo, MAGIC_J),
    [C_BASE_MAGIC_K] = COMBO(C_BASE_MAGIC_K_combo, MAGIC_K),
    [C_FNSYM_KC_AMPR] = COMBO(C_FNSYM_KC_AMPR_combo, KC_AMPR),
    [C_FNSYM_KC_ASTR] = COMBO(C_FNSYM_KC_ASTR_combo, KC_ASTR),
    [C_FNSYM_KC_BACKSLASH] = COMBO(C_FNSYM_KC_BACKSLASH_combo, KC_BACKSLASH),
    [C_FNSYM_KC_CIRC] = COMBO(C_FNSYM_KC_CIRC_combo, KC_CIRC),
    [C_FNSYM_KC_DLR] = COMBO(C_FNSYM_KC_DLR_combo, KC_DLR),
    [C_FNSYM_KC_F11] = COMBO(C_FNSYM_KC_F11_combo, KC_F11),
    [C_FNSYM_KC_HASH] = COMBO(C_FNSYM_KC_HASH_combo, KC_HASH),
    [C_FNSYM_KC_KP_MINUS] = COMBO(C_FNSYM_KC_KP_MINUS_combo, KC_KP_MINUS),
    [C_FNSYM_KC_KP_PLUS] = COMBO(C_FNSYM_KC_KP_PLUS_combo, KC_KP_PLUS),
    [C_FNSYM_KC_LABK] = COMBO(C_FNSYM_KC_LABK_combo, KC_LABK),
    [C_FNSYM_KC_LCBR] = COMBO(C_FNSYM_KC_LCBR_combo, KC_LCBR),
    [C_FNSYM_KC_LGUI] = COMBO(C_FNSYM_KC_LGUI_combo, KC_LGUI),
    [C_FNSYM_KC_LPRN] = COMBO(C_FNSYM_KC_LPRN_combo, KC_LPRN),
    [C_FNSYM_KC_MINUS] = COMBO(C_FNSYM_KC_MINUS_combo, KC_MINUS),
    [C_FNSYM_KC_PERC] = COMBO(C_FNSYM_KC_PERC_combo, KC_PERC),
    [C_FNSYM_KC_PIPE] = COMBO(C_FNSYM_KC_PIPE_combo, KC_PIPE),
    [C_FNSYM_KC_RABK] = COMBO(C_FNSYM_KC_RABK_combo, KC_RABK),
    [C_FNSYM_KC_RCBR] = COMBO(C_FNSYM_KC_RCBR_combo, KC_RCBR),
    [C_FNSYM_KC_RPRN] = COMBO(C_FNSYM_KC_RPRN_combo, KC_RPRN),
    [C_FNSYM_KC_SLASH] = COMBO(C_FNSYM_KC_SLASH_combo, KC_SLASH),
    [C_FNSYM_KC_TILD] = COMBO(C_FNSYM_KC_TILD_combo, KC_TILD),
    [C_FNSYM_LT_NUM2KC_EQUAL] = COMBO(C_FNSYM_LT_NUM2KC_EQUAL_combo, LT(_NUM2,KC_EQUAL)),
    [C_FNSYM_MO_NUM] = COMBO(C_FNSYM_MO_NUM_combo, MO(_NUM)),
    [C_LEFT_KC_COLN] = COMBO(C_LEFT_KC_COLN_combo, KC_COLN),
    [C_NAV_AKC_F12] = COMBO(C_NAV_AKC_F12_combo, A(KC_F12)),
    [C_NAV_CKC_A] = COMBO(C_NAV_CKC_A_combo, C(KC_A)),
    [C_NAV_CKC_B] = COMBO(C_NAV_CKC_B_combo, C(KC_B)),
    [C_NAV_CKC_C] = COMBO(C_NAV_CKC_C_combo, C(KC_C)),
    [C_NAV_CKC_D] = COMBO(C_NAV_CKC_D_combo, C(KC_D)),
    [C_NAV_CKC_E] = COMBO(C_NAV_CKC_E_combo, C(KC_E)),
    [C_NAV_CKC_F12] = COMBO(C_NAV_CKC_F12_combo, C(KC_F12)),
    [C_NAV_CKC_K] = COMBO(C_NAV_CKC_K_combo, C(KC_K)),
    [C_NAV_CKC_P] = COMBO(C_NAV_CKC_P_combo, C(KC_P)),
    [C_NAV_CKC_SLASH] = COMBO(C_NAV_CKC_SLASH_combo, C(KC_SLASH)),
    [C_NAV_CKC_V] = COMBO(C_NAV_CKC_V_combo, C(KC_V)),
    [C_NAV_CKC_W] = COMBO(C_NAV_CKC_W_combo, C(KC_W)),
    [C_NAV_CKC_X] = COMBO(C_NAV_CKC_X_combo, C(KC_X)),
    [C_NAV_CKC_Y] = COMBO(C_NAV_CKC_Y_combo, C(KC_Y)),
    [C_NAV_CKC_Z] = COMBO(C_NAV_CKC_Z_combo, C(KC_Z)),
    [C_NAV_KC_END] = COMBO(C_NAV_KC_END_combo, KC_END),
    [C_NAV_KC_HOME] = COMBO(C_NAV_KC_HOME_combo, KC_HOME),
    [C_NAV_KC_PGDN] = COMBO(C_NAV_KC_PGDN_combo, KC_PGDN),
    [C_NAV_KC_PGUP] = COMBO(C_NAV_KC_PGUP_combo, KC_PGUP),
    [C_NAV_LCAKC_B] = COMBO(C_NAV_LCAKC_B_combo, LCA(KC_B)),
    [C_NAV_RCSKC_C] = COMBO(C_NAV_RCSKC_C_combo, RCS(KC_C)),
    [C_NAV_RCSKC_N] = COMBO(C_NAV_RCSKC_N_combo, RCS(KC_N)),
    [C_NAV_RCSKC_V] = COMBO(C_NAV_RCSKC_V_combo, RCS(KC_V)),
    [C_NAV_RCSKC_Z] = COMBO(C_NAV_RCSKC_Z_combo, RCS(KC_Z)),
    [C_NAV_UMUMLAUT_S] = COMBO(C_NAV_UMUMLAUT_S_combo, UM(UMLAUT_s)),
    [C_NAV_UPUMLAUT_AUMLAUT_A] = COMBO(C_NAV_UPUMLAUT_AUMLAUT_A_combo, UP(UMLAUT_a, UMLAUT_A)),
    [C_NAV_UPUMLAUT_OUMLAUT_O] = COMBO(C_NAV_UPUMLAUT_OUMLAUT_O_combo, UP(UMLAUT_o, UMLAUT_O)),
    [C_NAV_UPUMLAUT_UUMLAUT_U] = COMBO(C_NAV_UPUMLAUT_UUMLAUT_U_combo, UP(UMLAUT_u, UMLAUT_U)),
    [C_NUM_AKC_F1] = COMBO(C_NUM_AKC_F1_combo, A(KC_F1)),
    [C_NUM_CKC_G] = COMBO(C_NUM_CKC_G_combo, C(KC_G)),
    [C_NUM_LCAKC_L] = COMBO(C_NUM_LCAKC_L_combo, LCA(KC_L)),
    [C_NUM_LSAKC_B] = COMBO(C_NUM_LSAKC_B_combo, LSA(KC_B)),
    [C_NUM_LSAKC_S] = COMBO(C_NUM_LSAKC_S_combo, LSA(KC_S)),
    [C_NUM_LSAKC_X] = COMBO(C_NUM_LSAKC_X_combo, LSA(KC_X)),
    [C_NUM_RCSKC_V] = COMBO(C_NUM_RCSKC_V_combo, RCS(KC_V)),
    [C_RIGHT_KC_AT] = COMBO(C_RIGHT_KC_AT_combo, KC_AT),
    [C_RIGHT_KC_COMMA] = COMBO(C_RIGHT_KC_COMMA_combo, KC_COMMA),
    [C_RIGHT_KC_DOT] = COMBO(C_RIGHT_KC_DOT_combo, KC_DOT),
    [C_RIGHT_KC_EXLM] = COMBO(C_RIGHT_KC_EXLM_combo, KC_EXLM),
    [C_RIGHT_KC_GRAVE] = COMBO(C_RIGHT_KC_GRAVE_combo, KC_GRAVE),
    [C_RIGHT_KC_QUES] = COMBO(C_RIGHT_KC_QUES_combo, KC_QUES),
    [C_RIGHT_KC_QUOTE] = COMBO(C_RIGHT_KC_QUOTE_combo, KC_QUOTE),
    [C_RIGHT_KC_UNDS] = COMBO(C_RIGHT_KC_UNDS_combo, KC_UNDS),
    [C_RIGHT_N_T] = COMBO(C_RIGHT_N_T_combo, N_T),
    [C_RIGHT_RCSKC_F] = COMBO(C_RIGHT_RCSKC_F_combo, RCS(KC_F)),
    [C_RIGHT_RCSKC_R] = COMBO(C_RIGHT_RCSKC_R_combo, RCS(KC_R)),
    [DS_C_BASE_KC_B] = COMBO(DS_C_BASE_KC_B_combo, S(KC_B)),
    [DS_C_BASE_KC_G] = COMBO(DS_C_BASE_KC_G_combo, S(KC_G)),
    [DS_C_BASE_KC_K] = COMBO(DS_C_BASE_KC_K_combo, S(KC_K)),
    [DS_C_BASE_KC_M] = COMBO(DS_C_BASE_KC_M_combo, S(KC_M)),
    [DS_C_BASE_KC_P] = COMBO(DS_C_BASE_KC_P_combo, S(KC_P)),
    [DS_C_BASE_KC_V] = COMBO(DS_C_BASE_KC_V_combo, S(KC_V)),
    [SUB_1] = COMBO_ACTION(SUB_1_combo),
    [SUB_2] = COMBO_ACTION(SUB_2_combo),
    [SUB_3] = COMBO_ACTION(SUB_3_combo),
    [SUB_4] = COMBO_ACTION(SUB_4_combo),
    [SUB_5] = COMBO_ACTION(SUB_5_combo),
    [SUB_6] = COMBO_ACTION(SUB_6_combo),
    [S_C_BASE_KC_B] = COMBO(S_C_BASE_KC_B_combo, S(KC_B)),
    [S_C_BASE_KC_G] = COMBO(S_C_BASE_KC_G_combo, S(KC_G)),
    [S_C_BASE_KC_K] = COMBO(S_C_BASE_KC_K_combo, S(KC_K)),
    [S_C_BASE_KC_M] = COMBO(S_C_BASE_KC_M_combo, S(KC_M)),
    [S_C_BASE_KC_P] = COMBO(S_C_BASE_KC_P_combo, S(KC_P)),
    [S_C_BASE_KC_V] = COMBO(S_C_BASE_KC_V_combo, S(KC_V))
};

uint16_t COMBO_LEN = ARRAY_SIZE(key_combos);

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) return;
    switch (combo_index) {
    case SUB_1: SEND_STRING("qu"); break;
    case SUB_2: SEND_STRING("gregor.zeitlinger@grafana.com"); break;
    case SUB_3: SEND_STRING("zeitlinger@gmail.com"); break;
    case SUB_4: SEND_STRING("gregor@zeitlinger.de"); break;
    case SUB_5: SEND_STRING("Grafana"); break;
    case SUB_6: SEND_STRING("Grafana Labs"); break;
    default: break;
    }
}
