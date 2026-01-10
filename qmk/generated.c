/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int alternateLayer = -1;
int layer = _BASE;
int chord_state = 0; // 0 = inactive, 1+ = trie states

int chord_transition(int state, uint16_t keycode) {
    switch (state) {
                case 1:
                    if (keycode == KC_A) return 2;
                    if (keycode == KC_B) return 4;
                    if (keycode == KC_C) return 8;
                    if (keycode == KC_D) return 10;
                    if (keycode == KC_F) return 14;
                    if (keycode == KC_K) return 17;
                    if (keycode == KC_L) return 19;
                    if (keycode == KC_M) return 22;
                    if (keycode == KC_N) return 25;
                    if (keycode == KC_R) return 27;
                    if (keycode == KC_S) return 32;
                    if (keycode == KC_T) return 37;
                    if (keycode == KC_V) return 46;
                    if (keycode == KC_W) return 49;
                    break;
                // a
                case 2:
                    if (keycode == KC_G) return 3;
                    break;
                // b
                case 4:
                    if (keycode == KC_A) return 5;
                    if (keycode == KC_E) return 6;
                    break;
                // be
                case 6:
                    if (keycode == KC_F) return 7;
                    break;
                // c
                case 8:
                    if (keycode == KC_O) return 9;
                    break;
                // d
                case 10:
                    if (keycode == KC_I) return 11;
                    if (keycode == KC_O) return 12;
                    break;
                // do
                case 12:
                    if (keycode == KC_W) return 13;
                    break;
                // f
                case 14:
                    if (keycode == KC_A) return 15;
                    if (keycode == KC_R) return 16;
                    break;
                // k
                case 17:
                    if (keycode == KC_O) return 18;
                    break;
                // l
                case 19:
                    if (keycode == KC_I) return 20;
                    if (keycode == KC_O) return 21;
                    break;
                // m
                case 22:
                    if (keycode == KC_A) return 23;
                    if (keycode == KC_O) return 24;
                    break;
                // n
                case 25:
                    if (keycode == KC_O) return 26;
                    break;
                // r
                case 27:
                    if (keycode == KC_E) return 28;
                    if (keycode == KC_I) return 29;
                    if (keycode == KC_O) return 30;
                    break;
                // ro
                case 30:
                    if (keycode == KC_O) return 31;
                    break;
                // s
                case 32:
                    if (keycode == KC_M) return 33;
                    if (keycode == KC_O) return 35;
                    break;
                // sm
                case 33:
                    if (keycode == KC_I) return 34;
                    break;
                // so
                case 35:
                    if (keycode == KC_M) return 36;
                    break;
                // t
                case 37:
                    if (keycode == KC_E) return 38;
                    if (keycode == KC_H) return 40;
                    if (keycode == KC_I) return 44;
                    if (keycode == KC_U) return 45;
                    break;
                // te
                case 38:
                    if (keycode == KC_M) return 39;
                    break;
                // th
                case 40:
                    if (keycode == KC_E) return 41;
                    if (keycode == KC_I) return 43;
                    break;
                // the
                case 41:
                    if (keycode == KC_I) return 42;
                    break;
                // v
                case 46:
                    if (keycode == KC_E) return 47;
                    if (keycode == KC_R) return 48;
                    break;
                // w
                case 49:
                    if (keycode == KC_A) return 50;
                    if (keycode == KC_E) return 53;
                    if (keycode == KC_H) return 55;
                    if (keycode == KC_O) return 57;
                    break;
                // wa
                case 50:
                    if (keycode == KC_L) return 51;
                    if (keycode == KC_N) return 52;
                    break;
                // we
                case 53:
                    if (keycode == KC_L) return 54;
                    break;
                // wh
                case 55:
                    if (keycode == KC_E) return 56;
                    break;
    default:
        return state; // Invalid transition, ignore and stay in current state
    }
    return 0;
}

void chord_output(int state) {
    switch (state) {
                // ag
        case 3: SEND_STRING("again "); break;
                // ba
        case 5: SEND_STRING("back "); break;
                // be
        case 6: SEND_STRING("been "); break;
                // bef
        case 7: SEND_STRING("before "); break;
                // co
        case 9: SEND_STRING("could "); break;
                // di
        case 11: SEND_STRING("didn't "); break;
                // do
        case 12: SEND_STRING("don't "); break;
                // dow
        case 13: SEND_STRING("down "); break;
                // fa
        case 15: SEND_STRING("face "); break;
                // fr
        case 16: SEND_STRING("from "); break;
                // ko
        case 18: SEND_STRING("know "); break;
                // li
        case 20: SEND_STRING("like "); break;
                // lo
        case 21: SEND_STRING("look "); break;
                // ma
        case 23: SEND_STRING("make "); break;
                // mo
        case 24: SEND_STRING("more "); break;
                // no
        case 26: SEND_STRING("now "); break;
                // re
        case 28: SEND_STRING("really "); break;
                // ri
        case 29: SEND_STRING("right "); break;
                // ro
        case 30: SEND_STRING("around "); break;
                // roo
        case 31: SEND_STRING("room "); break;
                // smi
        case 34: SEND_STRING("smile "); break;
                // so
        case 35: SEND_STRING("some "); break;
                // som
        case 36: SEND_STRING("something "); break;
                // te
        case 38: SEND_STRING("other "); break;
                // tem
        case 39: SEND_STRING("them "); break;
                // th
        case 40: SEND_STRING("they "); break;
                // thei
        case 42: SEND_STRING("their "); break;
                // thi
        case 43: SEND_STRING("think "); break;
                // ti
        case 44: SEND_STRING("time "); break;
                // tu
        case 45: SEND_STRING("turn "); break;
                // ve
        case 47: SEND_STRING("even "); break;
                // vr
        case 48: SEND_STRING("over "); break;
                // wa
        case 50: SEND_STRING("what "); break;
                // wal
        case 51: SEND_STRING("walk "); break;
                // wan
        case 52: SEND_STRING("want "); break;
                // we
        case 53: SEND_STRING("were "); break;
                // wel
        case 54: SEND_STRING("well "); break;
                // whe
        case 56: SEND_STRING("when "); break;
                // wo
        case 57: SEND_STRING("would "); break;
    default:
        break;
    }
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch(index) {
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
    case C_BASE_MAGIC_A: return 200;
    case C_BASE_MAGIC_B: return 200;
    case C_BASE_MAGIC_C: return 200;
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
            case MAGIC_A:
                switch (get_last_keycode()) {
                    case KC_B: tap_code16(KC_L); return false;
                    case KC_C: tap_code16(KC_K); return false;
                    case KC_COMMA: SEND_STRING(" but "); return false;
                    case KC_D: SEND_STRING("oesn't"); return false;
                    case KC_DOT: tap_code16(KC_SLASH); return false;
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_ENT: SEND_STRING("the "); return false;
                    case KC_EQUAL: tap_code16(KC_RABK); return false;
                    case KC_EXLM: tap_code16(KC_EQUAL); return false;
                    case KC_F: tap_code16(KC_F); return false;
                    case KC_G: tap_code16(KC_N); return false;
                    case KC_H: tap_code16(KC_Y); return false;
                    case KC_I: tap_code16(KC_QUOTE); return false;
                    case KC_J: SEND_STRING("ust"); return false;
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_P); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_MINUS: tap_code16(KC_RABK); return false;
                    case KC_N: tap_code16(KC_G); return false;
                    case KC_O: tap_code16(KC_E); return false;
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_R: tap_code16(KC_K); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: SEND_STRING("the "); return false;
                    case KC_T: SEND_STRING("ion"); return false;
                    case KC_TAB: SEND_STRING("the "); return false;
                    case KC_TILD: tap_code16(KC_SLASH); return false;
                    case KC_V: SEND_STRING("er"); return false;
                    case KC_W: tap_code16(KC_N); return false;
                    case KC_X: tap_code16(KC_P); return false;
                    case KC_Z: SEND_STRING("eitlinger"); return false;
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): SEND_STRING("oesn't"); return false;
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_F): tap_code16(KC_F); return false;
                    case S(KC_G): tap_code16(KC_N); return false;
                    case S(KC_H): tap_code16(KC_Y); return false;
                    case S(KC_I): tap_code16(KC_QUOTE); return false;
                    case S(KC_J): SEND_STRING("ust"); return false;
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_P); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): tap_code16(KC_G); return false;
                    case S(KC_O): tap_code16(KC_E); return false;
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_R): tap_code16(KC_K); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): SEND_STRING("ion"); return false;
                    case S(KC_V): SEND_STRING("er"); return false;
                    case S(KC_W): tap_code16(KC_N); return false;
                    case S(KC_X): tap_code16(KC_P); return false;
                    case S(KC_Z): SEND_STRING("eitlinger"); return false;
                }
                return false;
            case MAGIC_B:
                switch (get_last_keycode()) {
                    case KC_B: SEND_STRING("ecause"); return false;
                    case KC_C: tap_code16(KC_P); return false;
                    case KC_COMMA: SEND_STRING(" and "); return false;
                    case KC_D: SEND_STRING("oes"); return false;
                    case KC_DOT: SEND_STRING("./"); return false;
                    case KC_ENT: SEND_STRING("and "); return false;
                    case KC_F: SEND_STRING("or"); return false;
                    case KC_G: tap_code16(KC_K); return false;
                    case KC_H: SEND_STRING("ey"); return false;
                    case KC_I: SEND_STRING("'ve"); return false;
                    case KC_K: SEND_STRING("now"); return false;
                    case KC_L: tap_code16(KC_M); return false;
                    case KC_M: SEND_STRING("ent"); return false;
                    case KC_N: tap_code16(KC_K); return false;
                    case KC_P: tap_code16(KC_S); return false;
                    case KC_S: SEND_STRING("ion"); return false;
                    case KC_SPC: tap_code16(KC_BSPC); SEND_STRING(". "); add_oneshot_mods(MOD_BIT(KC_LSFT)); return false;
                    case KC_T: SEND_STRING("ing"); return false;
                    case KC_TAB: SEND_STRING("and "); return false;
                    case KC_V: SEND_STRING("en"); return false;
                    case KC_W: tap_code16(KC_S); return false;
                    case KC_X: tap_code16(KC_C); return false;
                    case S(KC_B): SEND_STRING("ecause"); return false;
                    case S(KC_C): tap_code16(KC_P); return false;
                    case S(KC_D): SEND_STRING("oes"); return false;
                    case S(KC_F): SEND_STRING("or"); return false;
                    case S(KC_G): tap_code16(KC_K); return false;
                    case S(KC_H): SEND_STRING("ey"); return false;
                    case S(KC_I): SEND_STRING("'ve"); return false;
                    case S(KC_K): SEND_STRING("now"); return false;
                    case S(KC_L): tap_code16(KC_M); return false;
                    case S(KC_M): SEND_STRING("ent"); return false;
                    case S(KC_N): tap_code16(KC_K); return false;
                    case S(KC_P): tap_code16(KC_S); return false;
                    case S(KC_S): SEND_STRING("ion"); return false;
                    case S(KC_T): SEND_STRING("ing"); return false;
                    case S(KC_V): SEND_STRING("en"); return false;
                    case S(KC_W): tap_code16(KC_S); return false;
                    case S(KC_X): tap_code16(KC_C); return false;
                }
                return false;
            case MAGIC_C:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_U); return false;
                    case KC_B: tap_code16(KC_L); return false;
                    case KC_C: tap_code16(KC_K); return false;
                    case KC_D: SEND_STRING("on't"); return false;
                    case KC_E: tap_code16(KC_O); return false;
                    case KC_G: tap_code16(KC_L); return false;
                    case KC_K: tap_code16(KC_N); return false;
                    case KC_L: tap_code16(KC_V); return false;
                    case KC_M: tap_code16(KC_B); return false;
                    case KC_N: SEND_STRING("ly"); return false;
                    case KC_P: tap_code16(KC_L); return false;
                    case KC_S: tap_code16(KC_P); return false;
                    case KC_SPC: SEND_STRING("the "); return false;
                    case KC_T: SEND_STRING("ion"); return false;
                    case KC_U: tap_code16(KC_A); return false;
                    case S(KC_A): tap_code16(KC_U); return false;
                    case S(KC_B): tap_code16(KC_L); return false;
                    case S(KC_C): tap_code16(KC_K); return false;
                    case S(KC_D): SEND_STRING("on't"); return false;
                    case S(KC_E): tap_code16(KC_O); return false;
                    case S(KC_G): tap_code16(KC_L); return false;
                    case S(KC_K): tap_code16(KC_N); return false;
                    case S(KC_L): tap_code16(KC_V); return false;
                    case S(KC_M): tap_code16(KC_B); return false;
                    case S(KC_N): SEND_STRING("ly"); return false;
                    case S(KC_P): tap_code16(KC_L); return false;
                    case S(KC_S): tap_code16(KC_P); return false;
                    case S(KC_T): SEND_STRING("ion"); return false;
                    case S(KC_U): tap_code16(KC_A); return false;
                }
                return false;
            
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

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    switch (keycode) {
        case MAGIC_A:
        case MAGIC_B:
        case MAGIC_C:
            return false;
    }

    return true;  // Other keys can be repeated.
}
