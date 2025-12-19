/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int alternateLayer = -1;
int layer = _BASE;

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch(index) {
    case C_BASE_ALTREP_A: return 200;
    case C_BASE_ALTREP_B: return 200;
    case C_BASE_KC_B: return 200;
    case C_BASE_KC_COMMA: return 200;
    case C_BASE_KC_DOT: return 200;
    case C_BASE_KC_G: return 200;
    case C_BASE_KC_J: return 200;
    case C_BASE_KC_K: return 200;
    case C_BASE_KC_M: return 200;
    case C_BASE_KC_P: return 200;
    case C_BASE_KC_Q: return 200;
    case C_BASE_KC_V: return 200;
    case C_BASE_KC_Z: return 200;
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
    case C_NAV_RCSKC_E: return 200;
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
    case C_RIGHT_KC_EXLM: return 200;
    case C_RIGHT_KC_GRAVE: return 200;
    case C_RIGHT_KC_QUES: return 200;
    case C_RIGHT_N_T: return 200;
    case C_RIGHT_RCSKC_F: return 200;
    case C_RIGHT_RCSKC_R: return 200;
    case DS_C_BASE_KC_B: return 200;
    case DS_C_BASE_KC_G: return 200;
    case DS_C_BASE_KC_J: return 200;
    case DS_C_BASE_KC_K: return 200;
    case DS_C_BASE_KC_M: return 200;
    case DS_C_BASE_KC_P: return 200;
    case DS_C_BASE_KC_Q: return 200;
    case DS_C_BASE_KC_V: return 200;
    case DS_C_BASE_KC_Z: return 200;
    case SUB_1: return 200;
    case SUB_2: return 200;
    case SUB_3: return 200;
    case SUB_4: return 200;
    case SUB_5: return 200;
    case SUB_6: return 200;
    case SUB_7: return 200;
    case SUB_8: return 200;
    case S_C_BASE_KC_B: return 200;
    case S_C_BASE_KC_G: return 200;
    case S_C_BASE_KC_J: return 200;
    case S_C_BASE_KC_K: return 200;
    case S_C_BASE_KC_M: return 200;
    case S_C_BASE_KC_P: return 200;
    case S_C_BASE_KC_Q: return 200;
    case S_C_BASE_KC_V: return 200;
    case S_C_BASE_KC_Z: return 200;
    default:
        return COMBO_TERM;
    }
}

bool tap(uint16_t keycode) {
    tap_code16(keycode);
    set_last_keycode(keycode);
    return false;
}

bool process_record_generated(uint16_t keycode, keyrecord_t *record) {
    if (alternateLayer >= 0 && record->event.pressed) {
        int al = alternateLayer;
        alternateLayer = -1;
        if (layer == _BASE) {
            switch (al) {
            
            }
        }
    } else if (layer == _BASE && record->event.pressed) {
        switch (keycode) {
        
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
            case ALTREP_A:
                if (get_repeat_key_count() > 1) {
                    switch (get_last_keycode()) {
                        case KC_D: ALT_KC_D
                        case KC_G: KC_O
                        case S(KC_D): ALT_KC_D
                        case S(KC_G): KC_O
                    }
                } else {
                    switch (get_last_keycode()) {
                        case KC_B: ALT_KC_B
                        case KC_C: KC_P
                        case KC_COMMA: ALT_KC_COMMA
                        case KC_D: ALT_KC_D
                        case KC_DOT: ALT_KC_DOT
                        case KC_ENT: ALT_KC_ENT
                        case KC_F: ALT_KC_F
                        case KC_G: KC_L
                        case KC_H: KC_Y
                        case KC_J: ALT_KC_J
                        case KC_K: ALT_KC_K
                        case KC_L: KC_M
                        case KC_M: ALT_KC_M
                        case KC_N: KC_K
                        case KC_P: KC_S
                        case KC_S: KC_S
                        case KC_SPC: ALT_KC_SPC
                        case KC_T: ALT_KC_T
                        case KC_TAB: ALT_KC_TAB
                        case KC_V: ALT_KC_V
                        case KC_W: KC_S
                        case KC_X: KC_C
                        case KC_Y: KC_I
                        case KC_Z: KC_I
                        case S(KC_B): ALT_KC_B
                        case S(KC_C): KC_P
                        case S(KC_D): ALT_KC_D
                        case S(KC_F): ALT_KC_F
                        case S(KC_G): KC_L
                        case S(KC_H): KC_Y
                        case S(KC_J): ALT_KC_J
                        case S(KC_K): ALT_KC_K
                        case S(KC_L): KC_M
                        case S(KC_M): ALT_KC_M
                        case S(KC_N): KC_K
                        case S(KC_P): KC_S
                        case S(KC_S): KC_S
                        case S(KC_T): ALT_KC_T
                        case S(KC_V): ALT_KC_V
                        case S(KC_W): KC_S
                        case S(KC_X): KC_C
                        case S(KC_Y): KC_I
                        case S(KC_Z): KC_I
                    }
                }    
                return false;
            case ALTREP_B:
                if (get_repeat_key_count() > 1) {
                    switch (get_last_keycode()) {
                        case KC_B: KC_I
                        case KC_P: KC_I
                        case S(KC_B): KC_I
                        case S(KC_P): KC_I
                    }
                } else {
                    switch (get_last_keycode()) {
                        case KC_A: KC_U
                        case KC_B: KC_L
                        case KC_C: KC_K
                        case KC_COMMA: ALT_KC_COMMA
                        case KC_D: KC_V
                        case KC_DOT: KC_SLASH
                        case KC_E: KC_O
                        case KC_ENT: ALT_KC_ENT
                        case KC_EQUAL: KC_RABK
                        case KC_EXLM: KC_EQUAL
                        case KC_F: KC_F
                        case KC_G: KC_N
                        case KC_H: ALT_KC_H
                        case KC_K: KC_N
                        case KC_L: KC_P
                        case KC_M: KC_B
                        case KC_MINUS: KC_RABK
                        case KC_N: KC_G
                        case KC_O: KC_E
                        case KC_P: KC_L
                        case KC_Q: ALT_KC_Q
                        case KC_R: KC_K
                        case KC_S: KC_P
                        case KC_SPC: ALT_KC_SPC
                        case KC_T: ALT_KC_T
                        case KC_TAB: ALT_KC_TAB
                        case KC_TILD: KC_SLASH
                        case KC_U: KC_A
                        case KC_V: ALT_KC_V
                        case KC_W: KC_N
                        case KC_X: KC_P
                        case KC_Z: ALT_KC_Z
                        case S(KC_A): KC_U
                        case S(KC_B): KC_L
                        case S(KC_C): KC_K
                        case S(KC_D): KC_V
                        case S(KC_E): KC_O
                        case S(KC_F): KC_F
                        case S(KC_G): KC_N
                        case S(KC_H): ALT_KC_H
                        case S(KC_K): KC_N
                        case S(KC_L): KC_P
                        case S(KC_M): KC_B
                        case S(KC_N): KC_G
                        case S(KC_O): KC_E
                        case S(KC_P): KC_L
                        case S(KC_Q): ALT_KC_Q
                        case S(KC_R): KC_K
                        case S(KC_S): KC_P
                        case S(KC_T): ALT_KC_T
                        case S(KC_U): KC_A
                        case S(KC_V): ALT_KC_V
                        case S(KC_W): KC_N
                        case S(KC_X): KC_P
                        case S(KC_Z): ALT_KC_Z
                    }
                }    
                return false;
            case ALTREP_C:
                if (get_repeat_key_count() > 1) {
                    switch (get_last_keycode()) {
            
                    }
                } else {
                    switch (get_last_keycode()) {
            
                    }
                }    
                return false;
            case _HANDLER_ALT_KC_B: SEND_STRING("ecause"); return false;
            case _HANDLER_ALT_KC_D: SEND_STRING("n't"); return false;
            case _HANDLER_ALT_KC_F: SEND_STRING("or"); return false;
            case _HANDLER_ALT_KC_H: SEND_STRING("ey"); return false;
            case _HANDLER_ALT_KC_J: SEND_STRING("ust"); return false;
            case _HANDLER_ALT_KC_K: SEND_STRING("now"); return false;
            case _HANDLER_ALT_KC_M: SEND_STRING("ent"); return false;
            case _HANDLER_ALT_KC_Q: SEND_STRING("ua"); return false;
            case _HANDLER_ALT_KC_T: SEND_STRING("ion"); return false;
            case _HANDLER_ALT_KC_V: SEND_STRING("er"); return false;
            case _HANDLER_ALT_KC_Z: SEND_STRING("eitlinger"); return false;
            case _HANDLER_ALT_KC_SPC: SEND_STRING("the "); return false;
            case _HANDLER_ALT_KC_TAB: SEND_STRING("the "); return false;
            case _HANDLER_ALT_KC_ENT: SEND_STRING("the "); return false;
            case _HANDLER_ALT_KC_COMMA: SEND_STRING(" but "); return false;
            case _HANDLER_ALT_KC_DOT: SEND_STRING("./"); return false;
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

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
${repeatB}
    }

    return KC_TRNS;
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    switch (keycode) {
        case ALTREP1:
        case ALTREP2:
        case ALTREP3:
            return false;
    }

    return true;  // Other keys can be repeated.
}
