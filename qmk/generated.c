/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int alternateLayer = -1;
int layer = _BASE;

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch(index) {
    case C_BASE_ING: return 200;
    case C_BASE_ION: return 200;
    case C_BASE_KC_B: return 200;
    case C_BASE_KC_COMMA: return 200;
    case C_BASE_KC_DOT: return 200;
    case C_BASE_KC_G: return 200;
    case C_BASE_KC_J: return 200;
    case C_BASE_KC_K: return 200;
    case C_BASE_KC_Q: return 200;
    case C_BASE_KC_QUOTE: return 200;
    case C_BASE_KC_V: return 200;
    case C_BASE_KC_W: return 200;
    case C_BASE_KC_X: return 200;
    case C_BASE_KC_Z: return 200;
    case C_BASE_NG: return 200;
    case C_BASE_QU: return 200;
    case C_FNSYM_KC_AMPR: return 500;
    case C_FNSYM_KC_ASTR: return 500;
    case C_FNSYM_KC_BACKSLASH: return 500;
    case C_FNSYM_KC_CIRC: return 500;
    case C_FNSYM_KC_DLR: return 500;
    case C_FNSYM_KC_F11: return 500;
    case C_FNSYM_KC_HASH: return 500;
    case C_FNSYM_KC_LABK: return 500;
    case C_FNSYM_KC_LCBR: return 500;
    case C_FNSYM_KC_LPRN: return 500;
    case C_FNSYM_KC_MINUS: return 500;
    case C_FNSYM_KC_PERC: return 500;
    case C_FNSYM_KC_PIPE: return 500;
    case C_FNSYM_KC_PLUS: return 500;
    case C_FNSYM_KC_RABK: return 500;
    case C_FNSYM_KC_RCBR: return 500;
    case C_FNSYM_KC_RPRN: return 500;
    case C_FNSYM_KC_SLASH: return 500;
    case C_FNSYM_KC_TILD: return 500;
    case C_FNSYM_LT_NUM2KC_EQUAL: return 500;
    case C_FNSYM_MO_NUM: return 500;
    case C_LEFT_QU: return 500;
    case C_LEFT_U00C4: return 500;
    case C_LEFT_U00D6: return 500;
    case C_LEFT_U00DC: return 500;
    case C_LEFT_U00DF: return 500;
    case C_NAV_CKC_A: return 500;
    case C_NAV_CKC_C: return 500;
    case C_NAV_CKC_D: return 500;
    case C_NAV_CKC_E: return 500;
    case C_NAV_CKC_K: return 500;
    case C_NAV_CKC_SLASH: return 500;
    case C_NAV_CKC_V: return 500;
    case C_NAV_CKC_W: return 500;
    case C_NAV_CKC_X: return 500;
    case C_NAV_CKC_Y: return 500;
    case C_NAV_CKC_Z: return 500;
    case C_NAV_KC_END: return 500;
    case C_NAV_KC_HOME: return 500;
    case C_NAV_KC_PGDN: return 500;
    case C_NAV_KC_PGUP: return 500;
    case C_NAV_RCSKC_N: return 500;
    case C_NAV_RCSKC_V: return 500;
    case C_NAV_RCSKC_Z: return 500;
    case C_NUM_LSAKC_B: return 500;
    case C_NUM_LSAKC_L: return 500;
    case C_NUM_LSAKC_X: return 500;
    case C_RIGHT_DOT_SPC: return 500;
    case C_RIGHT_KC_AT: return 500;
    case C_RIGHT_KC_EXLM: return 500;
    case C_RIGHT_KC_GRAVE: return 500;
    case C_RIGHT_KC_QUES: return 500;
    case C_RIGHT_N_T: return 500;
    case C_RIGHT_RCSKC_F: return 500;
    case C_RIGHT_RCSKC_R: return 500;
    case DS_C_BASE_KC_B: return 500;
    case DS_C_BASE_KC_G: return 500;
    case DS_C_BASE_KC_J: return 500;
    case DS_C_BASE_KC_K: return 500;
    case DS_C_BASE_KC_Q: return 500;
    case DS_C_BASE_KC_V: return 500;
    case DS_C_BASE_KC_W: return 500;
    case DS_C_BASE_KC_X: return 500;
    case DS_C_BASE_KC_Z: return 500;
    case S_C_BASE_KC_B: return 500;
    case S_C_BASE_KC_G: return 500;
    case S_C_BASE_KC_J: return 500;
    case S_C_BASE_KC_K: return 500;
    case S_C_BASE_KC_Q: return 500;
    case S_C_BASE_KC_V: return 500;
    case S_C_BASE_KC_W: return 500;
    case S_C_BASE_KC_X: return 500;
    case S_C_BASE_KC_Z: return 500;
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
            case _HANDLER_U00E4: register_unicode(0x00E4); return false;
            case _HANDLER_U00FC: register_unicode(0x00FC); return false;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (get_repeat_key_count() > 0) {
                switch (keycode) {
                case KC_B: SEND_STRING("ecause"); return false;
                case KC_COMMA: SEND_STRING(" and "); return false;
                case KC_D: SEND_STRING("oes"); return false;
                case KC_DOT: SEND_STRING("./"); return false;
                case KC_ENT: SEND_STRING("and "); return false;
                case KC_F: SEND_STRING("or"); return false;
                case KC_G: tap_code16(KC_L); return false;
                case KC_H: tap_code16(KC_Y); return false;
                case KC_J: SEND_STRING("ust"); return false;
                case KC_K: SEND_STRING("now"); return false;
                case KC_L: tap_code16(KC_M); return false;
                case KC_M: SEND_STRING("ent"); return false;
                case KC_N: tap_code16(KC_K); return false;
                case KC_P: tap_code16(KC_S); return false;
                case KC_S: tap_code16(KC_S); return false;
                case KC_SPC: SEND_STRING("and "); return false;
                case KC_T: SEND_STRING("ing"); return false;
                case KC_TAB: SEND_STRING("and "); return false;
                case KC_V: SEND_STRING("en"); return false;
                case KC_W: tap_code16(KC_S); return false;
                case KC_X: tap_code16(KC_C); return false;
                case KC_Y: tap_code16(KC_I); return false;
                case KC_Z: tap_code16(KC_I); return false;
                case S(KC_B): SEND_STRING("ecause"); return false;
                case S(KC_D): SEND_STRING("oes"); return false;
                case S(KC_F): SEND_STRING("or"); return false;
                case S(KC_G): tap_code16(KC_L); return false;
                case S(KC_H): tap_code16(KC_Y); return false;
                case S(KC_J): SEND_STRING("ust"); return false;
                case S(KC_K): SEND_STRING("now"); return false;
                case S(KC_L): tap_code16(KC_M); return false;
                case S(KC_M): SEND_STRING("ent"); return false;
                case S(KC_N): tap_code16(KC_K); return false;
                case S(KC_P): tap_code16(KC_S); return false;
                case S(KC_S): tap_code16(KC_S); return false;
                case S(KC_T): SEND_STRING("ing"); return false;
                case S(KC_V): SEND_STRING("en"); return false;
                case S(KC_W): tap_code16(KC_S); return false;
                case S(KC_X): tap_code16(KC_C); return false;
                case S(KC_Y): tap_code16(KC_I); return false;
                case S(KC_Z): tap_code16(KC_I); return false;
                }
            }
            switch (keycode) {
            case _HANDLER_U00F6: register_unicode(0x00F6); return false;
            case _HANDLER_U00C4: register_unicode(0x00C4); return false;
            case _HANDLER_U00D6: register_unicode(0x00D6); return false;
            case _HANDLER_U00DC: register_unicode(0x00DC); return false;
            case _HANDLER_U00DF: register_unicode(0x00DF); return false;
            case _HANDLER_ST_WORDS_1_2: SEND_STRING("LGTM"); return false;
            case _HANDLER_ST_WORDS_2_0: SEND_STRING("Gregor Zeitlinger"); return false;
            case _HANDLER_ST_WORDS_2_1: SEND_STRING("gregor.zeitlinger@grafana.com"); return false;
            case _HANDLER_ST_WORDS_2_2: SEND_STRING("gregor@zeitlinger.de"); return false;
            case _HANDLER_ST_WORDS_2_3: SEND_STRING("zeitlinger@gmail.com"); return false;
            case _HANDLER_ALT_KC_H: SEND_STRING("ey"); return false;
            case _HANDLER_ALT_KC_Q: SEND_STRING("ua"); return false;
            case _HANDLER_ALT_KC_T: SEND_STRING("ion"); return false;
            case _HANDLER_ALT_KC_V: SEND_STRING("er"); return false;
            case _HANDLER_ALT_KC_Z: SEND_STRING("eitlinger"); return false;
            case _HANDLER_ALT_KC_SPC: SEND_STRING("the "); return false;
            case _HANDLER_ALT_KC_TAB: SEND_STRING("the "); return false;
            case _HANDLER_ALT_KC_ENT: SEND_STRING("the "); return false;
            case _HANDLER_ALT_KC_COMMA: SEND_STRING(" but "); return false;
            default:
                break;
            }
        }
    }
    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LT(_WORDS,U00E4): return true;
    case LT(_MM,U00FC): return true;
    case LT(_NUM2,KC_EQUAL): return true;
    default:
        // Do not select the hold action when another key is pressed.
        return false;
    }
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        case KC_A: return KC_U;
        case KC_B: return KC_L;
        case KC_C: return KC_K;
        case KC_COMMA: return ALT_KC_COMMA;
        case KC_D: return KC_V;
        case KC_DOT: return KC_SLASH;
        case KC_E: return KC_O;
        case KC_ENT: return ALT_KC_ENT;
        case KC_EQUAL: return KC_RABK;
        case KC_EXLM: return KC_EQUAL;
        case KC_F: return KC_F;
        case KC_G: return KC_N;
        case KC_H: return ALT_KC_H;
        case KC_K: return KC_N;
        case KC_L: return KC_P;
        case KC_M: return KC_B;
        case KC_MINUS: return KC_RABK;
        case KC_N: return KC_L;
        case KC_O: return KC_E;
        case KC_P: return KC_L;
        case KC_Q: return ALT_KC_Q;
        case KC_R: return KC_K;
        case KC_S: return KC_P;
        case KC_SPC: return ALT_KC_SPC;
        case KC_T: return ALT_KC_T;
        case KC_TAB: return ALT_KC_TAB;
        case KC_TILD: return KC_SLASH;
        case KC_U: return KC_A;
        case KC_V: return ALT_KC_V;
        case KC_W: return KC_N;
        case KC_X: return KC_P;
        case KC_Z: return ALT_KC_Z;
        case S(KC_A): return KC_U;
        case S(KC_B): return KC_L;
        case S(KC_C): return KC_K;
        case S(KC_D): return KC_V;
        case S(KC_E): return KC_O;
        case S(KC_F): return KC_F;
        case S(KC_G): return KC_N;
        case S(KC_H): return ALT_KC_H;
        case S(KC_K): return KC_N;
        case S(KC_L): return KC_P;
        case S(KC_M): return KC_B;
        case S(KC_N): return KC_L;
        case S(KC_O): return KC_E;
        case S(KC_P): return KC_L;
        case S(KC_Q): return ALT_KC_Q;
        case S(KC_R): return KC_K;
        case S(KC_S): return KC_P;
        case S(KC_T): return ALT_KC_T;
        case S(KC_U): return KC_A;
        case S(KC_V): return ALT_KC_V;
        case S(KC_W): return KC_N;
        case S(KC_X): return KC_P;
        case S(KC_Z): return ALT_KC_Z;
    }

    return KC_TRNS;
}
