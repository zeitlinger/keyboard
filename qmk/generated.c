/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch(index) {
    case C_BASE_ING: return 200;
    case C_BASE_KC_B: return 200;
    case C_BASE_KC_G: return 200;
    case C_BASE_KC_J: return 200;
    case C_BASE_KC_K: return 200;
    case C_BASE_KC_M: return 200;
    case C_BASE_KC_P: return 200;
    case C_BASE_KC_V: return 200;
    case C_BASE_KC_Z: return 200;
    case C_BASE_MAGIC_C: return 200;
    case C_BASE_MAGIC_D: return 200;
    case C_BASE_MAGIC_E: return 200;
    case C_BASE_MAGIC_F: return 200;
    case C_BASE_MAGIC_G: return 200;
    case C_BASE_MAGIC_H: return 200;
    case C_BASE_MAGIC_I: return 200;
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
    case C_NAV_RCSKC_C: return 200;
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
    case C_RIGHT_KC_DQUO: return 200;
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
    case DS_C_BASE_KC_V: return 200;
    case DS_C_BASE_KC_Z: return 200;
    case SUB_1: return 200;
    case S_C_BASE_KC_B: return 200;
    case S_C_BASE_KC_G: return 200;
    case S_C_BASE_KC_J: return 200;
    case S_C_BASE_KC_K: return 200;
    case S_C_BASE_KC_M: return 200;
    case S_C_BASE_KC_P: return 200;
    case S_C_BASE_KC_V: return 200;
    case S_C_BASE_KC_Z: return 200;
    default:
        return COMBO_TERM;
    }
}

// Two-variable tracking for adaptive keys.
// prev_keycode = the key before the current one (what adaptives check against).
// last_keycode = the most recent key (shifts to prev_keycode on the next keypress).
// Updated only in remember_last_key_user (called with resolved combo keycodes,
// so combo components like KC_C from P=KC_C+KC_X are never recorded — only KC_P is).
static uint16_t prev_keycode = KC_NO;
static uint16_t last_keycode = KC_NO;

bool tap(uint16_t keycode) {
    tap_code16(keycode);
    set_last_keycode(keycode);
    last_keycode = keycode;
    return false;
}

bool process_record_generated(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Adaptive keys: runs after combo resolution in process_record_user,
        // so combo components are suppressed and prev_keycode reflects the
        // resolved combo keycode (e.g. KC_P not KC_C).
        switch (keycode) {
            case KC_E:
                switch (prev_keycode) {
                    case KC_A: return tap(KC_U);
                    case S(KC_A): return tap(KC_U);
                }
                break;
            case KC_D:
                switch (prev_keycode) {
                    case KC_B: return tap(KC_S);
                    case KC_C: return tap(KC_K);
                    case KC_F: return tap(KC_F);
                    case KC_G: return tap(KC_N);
                    case KC_P: return tap(KC_L);
                    case KC_S: return tap(KC_P);
                    case KC_X: return tap(KC_C);
                    case S(KC_B): return tap(KC_S);
                    case S(KC_C): return tap(KC_K);
                    case S(KC_F): return tap(KC_F);
                    case S(KC_G): return tap(KC_N);
                    case S(KC_P): return tap(KC_L);
                    case S(KC_S): return tap(KC_P);
                    case S(KC_X): return tap(KC_C);
                }
                break;
            case KC_N:
                switch (prev_keycode) {
                    case KC_C: return tap(KC_C);
                    case KC_P: return tap(KC_P);
                    case KC_T: return tap(KC_T);
                    case S(KC_C): return tap(KC_C);
                    case S(KC_P): return tap(KC_P);
                    case S(KC_T): return tap(KC_T);
                }
                break;
            case KC_C:
                switch (prev_keycode) {
                    case KC_D: return tap(KC_V);
                    case KC_L: return tap(KC_V);
                    case S(KC_D): return tap(KC_V);
                    case S(KC_L): return tap(KC_V);
                }
                break;
            case KC_F:
                switch (prev_keycode) {
                    case KC_D: return tap(KC_G);
                    case KC_G: return tap(KC_L);
                    case KC_T: return tap(KC_M);
                    case S(KC_D): return tap(KC_G);
                    case S(KC_G): return tap(KC_L);
                    case S(KC_T): return tap(KC_M);
                }
                break;
            case KC_H:
                switch (prev_keycode) {
                    case KC_D: return tap(KC_D);
                    case KC_E: return tap(KC_E);
                    case KC_L: return tap(KC_P);
                    case KC_M: return tap(KC_M);
                    case KC_N: return tap(KC_N);
                    case KC_O: return tap(KC_O);
                    case KC_U: return tap(KC_A);
                    case S(KC_D): return tap(KC_D);
                    case S(KC_E): return tap(KC_E);
                    case S(KC_L): return tap(KC_P);
                    case S(KC_M): return tap(KC_M);
                    case S(KC_N): return tap(KC_N);
                    case S(KC_O): return tap(KC_O);
                    case S(KC_U): return tap(KC_A);
                }
                break;
            case KC_U:
                switch (prev_keycode) {
                    case KC_E: return tap(KC_O);
                    case S(KC_E): return tap(KC_O);
                }
                break;
            case KC_R:
                switch (prev_keycode) {
                    case KC_K: return tap(KC_N);
                    case KC_L: return tap(KC_L);
                    case KC_M: return tap(KC_P);
                    case KC_N: return tap(KC_G);
                    case KC_S: return tap(KC_S);
                    case KC_Y: return tap(KC_I);
                    case S(KC_K): return tap(KC_N);
                    case S(KC_L): return tap(KC_L);
                    case S(KC_M): return tap(KC_P);
                    case S(KC_N): return tap(KC_G);
                    case S(KC_S): return tap(KC_S);
                    case S(KC_Y): return tap(KC_I);
                }
                break;
            case KC_T:
                switch (prev_keycode) {
                    case KC_M: return tap(KC_B);
                    case S(KC_M): return tap(KC_B);
                }
                break;
            case KC_X:
                switch (prev_keycode) {
                    case KC_N: return tap(KC_L);
                    case KC_T: return tap(KC_W);
                    case KC_W: return tap(KC_N);
                    case S(KC_N): return tap(KC_L);
                    case S(KC_T): return tap(KC_W);
                    case S(KC_W): return tap(KC_N);
                }
                break;
            case KC_Y:
                switch (prev_keycode) {
                    case KC_P: return tap(KC_S);
                    case S(KC_P): return tap(KC_S);
                }
                break;
            case KC_W:
                switch (prev_keycode) {
                    case KC_X: return tap(KC_P);
                    case S(KC_X): return tap(KC_P);
                }
                break;
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
                    case KC_A: SEND_STRING("bout "); set_suffix_state('t'); break;
                    case KC_B: SEND_STRING("ehind "); set_suffix_state('d'); break;
                    case KC_C: tap_code16(KC_N); break;
                    case KC_D: tap_code16(KC_C); break;
                    case KC_E: SEND_STRING("xception "); set_suffix_state('n'); break;
                    case KC_F: SEND_STRING("ound "); set_suffix_state('d'); break;
                    case KC_G: SEND_STRING("lobal "); set_suffix_state('l'); break;
                    case KC_I: SEND_STRING("nstrumentation "); set_suffix_state('n'); break;
                    case KC_K: tap_code16(KC_R); break;
                    case KC_L: tap_code16(KC_M); break;
                    case KC_M: tap_code16(KC_R); break;
                    case KC_N: tap_code16(KC_R); break;
                    case KC_P: tap_code16(KC_Y); break;
                    case KC_R: tap_code16(KC_BSPC); SEND_STRING("already "); set_suffix_state('y'); break;
                    case KC_S: SEND_STRING("omeone "); set_suffix_state('e'); break;
                    case KC_T: tap_code16(KC_N); break;
                    case KC_U: tap_code16(KC_BSPC); SEND_STRING("business "); set_suffix_state('s'); break;
                    case KC_V: tap_code16(KC_BSPC); SEND_STRING("zeitlinger@gmail.com "); set_suffix_state('m'); break;
                    case KC_W: SEND_STRING("ill "); set_suffix_state('l'); break;
                    case KC_Z: SEND_STRING("eitlinger "); set_suffix_state('r'); break;
                    case S(KC_A): SEND_STRING("bout "); set_suffix_state('t'); break;
                    case S(KC_B): SEND_STRING("ehind "); set_suffix_state('d'); break;
                    case S(KC_C): tap_code16(KC_N); break;
                    case S(KC_D): tap_code16(KC_C); break;
                    case S(KC_E): SEND_STRING("xception "); set_suffix_state('n'); break;
                    case S(KC_F): SEND_STRING("ound "); set_suffix_state('d'); break;
                    case S(KC_G): SEND_STRING("lobal "); set_suffix_state('l'); break;
                    case S(KC_I): SEND_STRING("nstrumentation "); set_suffix_state('n'); break;
                    case S(KC_K): tap_code16(KC_R); break;
                    case S(KC_L): tap_code16(KC_M); break;
                    case S(KC_M): tap_code16(KC_R); break;
                    case S(KC_N): tap_code16(KC_R); break;
                    case S(KC_P): tap_code16(KC_Y); break;
                    case S(KC_R): tap_code16(KC_BSPC); SEND_STRING("already "); set_suffix_state('y'); break;
                    case S(KC_S): SEND_STRING("omeone "); set_suffix_state('e'); break;
                    case S(KC_T): tap_code16(KC_N); break;
                    case S(KC_U): tap_code16(KC_BSPC); SEND_STRING("business "); set_suffix_state('s'); break;
                    case S(KC_V): tap_code16(KC_BSPC); SEND_STRING("zeitlinger@gmail.com "); set_suffix_state('m'); break;
                    case S(KC_W): SEND_STRING("ill "); set_suffix_state('l'); break;
                    case S(KC_Z): SEND_STRING("eitlinger "); set_suffix_state('r'); break;
                }
                set_last_keycode(MAGIC_A);
                return false;
            case MAGIC_B:
                switch (get_last_keycode()) {
                    case KC_B: SEND_STRING("etween "); set_suffix_state('n'); break;
                    case KC_D: tap_code16(KC_H); break;
                    case KC_E: SEND_STRING("nough "); set_suffix_state('h'); break;
                    case KC_F: SEND_STRING("irst "); set_suffix_state('t'); break;
                    case KC_G: tap_code16(KC_F); break;
                    case KC_L: tap_code16(KC_H); break;
                    case KC_M: tap_code16(KC_H); break;
                    case KC_N: tap_code16(KC_H); break;
                    case KC_P: tap_code16(KC_M); break;
                    case KC_R: tap_code16(KC_BSPC); SEND_STRING("everything "); set_suffix_state('g'); break;
                    case KC_S: tap_code16(KC_R); break;
                    case KC_T: tap_code16(KC_F); break;
                    case KC_V: tap_code16(KC_BSPC); SEND_STRING("gregor.zeitlinger@grafana.com "); set_suffix_state('m'); break;
                    case KC_W: SEND_STRING("asn't "); set_suffix_state('t'); break;
                    case KC_X: tap_code16(KC_W); break;
                    case KC_Z: tap_code16(KC_BSPC); SEND_STRING("gregor "); set_suffix_state('r'); break;
                    case S(KC_B): SEND_STRING("etween "); set_suffix_state('n'); break;
                    case S(KC_D): tap_code16(KC_H); break;
                    case S(KC_E): SEND_STRING("nough "); set_suffix_state('h'); break;
                    case S(KC_F): SEND_STRING("irst "); set_suffix_state('t'); break;
                    case S(KC_G): tap_code16(KC_F); break;
                    case S(KC_L): tap_code16(KC_H); break;
                    case S(KC_M): tap_code16(KC_H); break;
                    case S(KC_N): tap_code16(KC_H); break;
                    case S(KC_P): tap_code16(KC_M); break;
                    case S(KC_R): tap_code16(KC_BSPC); SEND_STRING("everything "); set_suffix_state('g'); break;
                    case S(KC_S): tap_code16(KC_R); break;
                    case S(KC_T): tap_code16(KC_F); break;
                    case S(KC_V): tap_code16(KC_BSPC); SEND_STRING("gregor.zeitlinger@grafana.com "); set_suffix_state('m'); break;
                    case S(KC_W): SEND_STRING("asn't "); set_suffix_state('t'); break;
                    case S(KC_X): tap_code16(KC_W); break;
                    case S(KC_Z): tap_code16(KC_BSPC); SEND_STRING("gregor "); set_suffix_state('r'); break;
                }
                set_last_keycode(MAGIC_B);
                return false;
            case MAGIC_C:
                switch (get_last_keycode()) {
                    case KC_A: tap_code16(KC_E); break;
                    case KC_E: tap_code16(KC_H); break;
                    case KC_O: tap_code16(KC_H); break;
                    case KC_U: tap_code16(KC_H); break;
                    case KC_Y: tap_code16(KC_R); break;
                    case S(KC_A): tap_code16(KC_E); break;
                    case S(KC_E): tap_code16(KC_H); break;
                    case S(KC_O): tap_code16(KC_H); break;
                    case S(KC_U): tap_code16(KC_H); break;
                    case S(KC_Y): tap_code16(KC_R); break;
                }
                set_last_keycode(MAGIC_C);
                return false;
            case MAGIC_D:
                switch (get_last_keycode()) {
                    case KC_A: SEND_STRING("fter "); set_suffix_state('r'); break;
                    case KC_B: SEND_STRING("ecause "); set_suffix_state('e'); break;
                    case KC_C: tap_code16(KC_P); break;
                    case KC_D: SEND_STRING("oesn't "); set_suffix_state('t'); break;
                    case KC_DOT: SEND_STRING("./"); break;
                    case KC_E: SEND_STRING("xit "); set_suffix_state('t'); break;
                    case KC_G: tap_code16(KC_K); break;
                    case KC_H: SEND_STRING("ave "); set_suffix_state('e'); break;
                    case KC_I: tap_code16(KC_BSPC); SEND_STRING("I've "); set_suffix_state('e'); break;
                    case KC_J: SEND_STRING("ust "); set_suffix_state('t'); break;
                    case KC_K: SEND_STRING("now "); set_suffix_state('w'); break;
                    case KC_L: tap_code16(KC_R); break;
                    case KC_M: SEND_STRING("ent "); set_suffix_state('t'); break;
                    case KC_N: tap_code16(KC_BSPC); SEND_STRING("qu"); break;
                    case KC_P: tap_code16(KC_N); break;
                    case KC_R: tap_code16(KC_K); break;
                    case KC_S: SEND_STRING("ion "); set_suffix_state('n'); break;
                    case KC_T: SEND_STRING("ion "); set_suffix_state('n'); break;
                    case KC_V: tap_code16(KC_BSPC); SEND_STRING("gregor@zeitlinger.de "); set_suffix_state('e'); break;
                    case KC_W: tap_code16(KC_S); break;
                    case KC_X: tap_code16(KC_R); break;
                    case KC_Z: tap_code16(KC_BSPC); SEND_STRING("Grafana "); set_suffix_state('a'); break;
                    case S(KC_A): SEND_STRING("fter "); set_suffix_state('r'); break;
                    case S(KC_B): SEND_STRING("ecause "); set_suffix_state('e'); break;
                    case S(KC_C): tap_code16(KC_P); break;
                    case S(KC_D): SEND_STRING("oesn't "); set_suffix_state('t'); break;
                    case S(KC_E): SEND_STRING("xit "); set_suffix_state('t'); break;
                    case S(KC_G): tap_code16(KC_K); break;
                    case S(KC_H): SEND_STRING("ave "); set_suffix_state('e'); break;
                    case S(KC_I): tap_code16(KC_BSPC); SEND_STRING("I've "); set_suffix_state('e'); break;
                    case S(KC_J): SEND_STRING("ust "); set_suffix_state('t'); break;
                    case S(KC_K): SEND_STRING("now "); set_suffix_state('w'); break;
                    case S(KC_L): tap_code16(KC_R); break;
                    case S(KC_M): SEND_STRING("ent "); set_suffix_state('t'); break;
                    case S(KC_N): tap_code16(KC_BSPC); SEND_STRING("qu"); break;
                    case S(KC_P): tap_code16(KC_N); break;
                    case S(KC_R): tap_code16(KC_K); break;
                    case S(KC_S): SEND_STRING("ion "); set_suffix_state('n'); break;
                    case S(KC_T): SEND_STRING("ion "); set_suffix_state('n'); break;
                    case S(KC_V): tap_code16(KC_BSPC); SEND_STRING("gregor@zeitlinger.de "); set_suffix_state('e'); break;
                    case S(KC_W): tap_code16(KC_S); break;
                    case S(KC_X): tap_code16(KC_R); break;
                    case S(KC_Z): tap_code16(KC_BSPC); SEND_STRING("Grafana "); set_suffix_state('a'); break;
                    default: SEND_STRING("qu"); break;
                }
                set_last_keycode(MAGIC_D);
                return false;
            case MAGIC_E:
                switch (get_last_keycode()) {
                    case KC_A: SEND_STRING("nything "); set_suffix_state('g'); break;
                    case KC_B: tap_code16(KC_D); break;
                    case KC_C: tap_code16(KC_D); break;
                    case KC_D: tap_code16(KC_F); break;
                    case KC_DOT: tap_code16(KC_SLASH); break;
                    case KC_E: tap_code16(KC_U); break;
                    case KC_EQUAL: tap_code16(KC_RABK); break;
                    case KC_EXLM: tap_code16(KC_EQUAL); break;
                    case KC_F: tap_code16(KC_D); break;
                    case KC_G: tap_code16(KC_D); break;
                    case KC_H: tap_code16(KC_Y); break;
                    case KC_I: tap_code16(KC_QUOTE); break;
                    case KC_K: tap_code16(KC_X); break;
                    case KC_L: tap_code16(KC_C); break;
                    case KC_M: tap_code16(KC_L); break;
                    case KC_MINUS: tap_code16(KC_RABK); break;
                    case KC_N: tap_code16(KC_X); break;
                    case KC_O: SEND_STRING("bservability "); set_suffix_state('y'); break;
                    case KC_P: tap_code16(KC_D); break;
                    case KC_R: tap_code16(KC_BSPC); SEND_STRING("almost "); set_suffix_state('t'); break;
                    case KC_S: tap_code16(KC_D); break;
                    case KC_T: tap_code16(KC_X); break;
                    case KC_TILD: tap_code16(KC_SLASH); break;
                    case KC_W: tap_code16(KC_X); break;
                    case KC_X: tap_code16(KC_D); break;
                    case KC_Z: tap_code16(KC_BSPC); SEND_STRING("Grafana Labs "); set_suffix_state('s'); break;
                    case S(KC_A): SEND_STRING("nything "); set_suffix_state('g'); break;
                    case S(KC_B): tap_code16(KC_D); break;
                    case S(KC_C): tap_code16(KC_D); break;
                    case S(KC_D): tap_code16(KC_F); break;
                    case S(KC_E): tap_code16(KC_U); break;
                    case S(KC_F): tap_code16(KC_D); break;
                    case S(KC_G): tap_code16(KC_D); break;
                    case S(KC_H): tap_code16(KC_Y); break;
                    case S(KC_I): tap_code16(KC_QUOTE); break;
                    case S(KC_K): tap_code16(KC_X); break;
                    case S(KC_L): tap_code16(KC_C); break;
                    case S(KC_M): tap_code16(KC_L); break;
                    case S(KC_N): tap_code16(KC_X); break;
                    case S(KC_O): SEND_STRING("bservability "); set_suffix_state('y'); break;
                    case S(KC_P): tap_code16(KC_D); break;
                    case S(KC_R): tap_code16(KC_BSPC); SEND_STRING("almost "); set_suffix_state('t'); break;
                    case S(KC_S): tap_code16(KC_D); break;
                    case S(KC_T): tap_code16(KC_X); break;
                    case S(KC_W): tap_code16(KC_X); break;
                    case S(KC_X): tap_code16(KC_D); break;
                    case S(KC_Z): tap_code16(KC_BSPC); SEND_STRING("Grafana Labs "); set_suffix_state('s'); break;
                }
                set_last_keycode(MAGIC_E);
                return false;
            case MAGIC_F:
                switch (get_last_keycode()) {
                    case KC_M: tap_code16(KC_T); break;
                    case KC_N: tap_code16(KC_K); break;
                    case S(KC_M): tap_code16(KC_T); break;
                    case S(KC_N): tap_code16(KC_K); break;
                }
                set_last_keycode(MAGIC_F);
                return false;
            case MAGIC_G:
                switch (get_last_keycode()) {
                    case KC_A: SEND_STRING("gain "); set_suffix_state('n'); break;
                    case KC_B: SEND_STRING("efore "); set_suffix_state('e'); break;
                    case KC_COMMA: SEND_STRING(" and "); break;
                    case KC_D: SEND_STRING("idn't "); set_suffix_state('t'); break;
                    case KC_ENT: SEND_STRING("and "); set_suffix_state('d'); break;
                    case KC_G: tap_code16(KC_BSPC); SEND_STRING("organize "); set_suffix_state('e'); break;
                    case KC_L: SEND_STRING("anguage "); set_suffix_state('e'); break;
                    case KC_O: tap_code16(KC_E); break;
                    case KC_P: SEND_STRING("roduction "); set_suffix_state('n'); break;
                    case KC_R: tap_code16(KC_BSPC); SEND_STRING("thought "); set_suffix_state('t'); break;
                    case KC_S: SEND_STRING("omething "); set_suffix_state('g'); break;
                    case KC_SPC: SEND_STRING("and "); set_suffix_state('d'); break;
                    case KC_T: SEND_STRING("hank you "); set_suffix_state('u'); break;
                    case KC_TAB: SEND_STRING("and "); set_suffix_state('d'); break;
                    case KC_U: SEND_STRING("nderstand "); set_suffix_state('d'); break;
                    case KC_W: SEND_STRING("here "); set_suffix_state('e'); break;
                    case KC_Z: tap_code16(KC_BSPC); SEND_STRING("OpenTelemetry "); set_suffix_state('y'); break;
                    case S(KC_A): SEND_STRING("gain "); set_suffix_state('n'); break;
                    case S(KC_B): SEND_STRING("efore "); set_suffix_state('e'); break;
                    case S(KC_D): SEND_STRING("idn't "); set_suffix_state('t'); break;
                    case S(KC_G): tap_code16(KC_BSPC); SEND_STRING("organize "); set_suffix_state('e'); break;
                    case S(KC_L): SEND_STRING("anguage "); set_suffix_state('e'); break;
                    case S(KC_O): tap_code16(KC_E); break;
                    case S(KC_P): SEND_STRING("roduction "); set_suffix_state('n'); break;
                    case S(KC_R): tap_code16(KC_BSPC); SEND_STRING("thought "); set_suffix_state('t'); break;
                    case S(KC_S): SEND_STRING("omething "); set_suffix_state('g'); break;
                    case S(KC_T): SEND_STRING("hank you "); set_suffix_state('u'); break;
                    case S(KC_U): SEND_STRING("nderstand "); set_suffix_state('d'); break;
                    case S(KC_W): SEND_STRING("here "); set_suffix_state('e'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); SEND_STRING("OpenTelemetry "); set_suffix_state('y'); break;
                }
                set_last_keycode(MAGIC_G);
                return false;
            case MAGIC_H:
                switch (get_last_keycode()) {
                    case KC_B: tap_code16(KC_BSPC); SEND_STRING("through "); set_suffix_state('h'); break;
                    case KC_C: tap_code16(KC_EXLM); break;
                    case KC_COMMA: SEND_STRING(" but "); break;
                    case KC_D: SEND_STRING("on't "); set_suffix_state('t'); break;
                    case KC_ENT: SEND_STRING("the "); set_suffix_state('e'); break;
                    case KC_L: SEND_STRING("eave "); set_suffix_state('e'); break;
                    case KC_N: tap_code16(KC_QUOTE); break;
                    case KC_O: tap_code16(KC_BSPC); SEND_STRING("without "); set_suffix_state('t'); break;
                    case KC_P: tap_code16(KC_BSPC); SEND_STRING("declarative config "); set_suffix_state('g'); break;
                    case KC_R: tap_code16(KC_BSPC); SEND_STRING("people "); set_suffix_state('e'); break;
                    case KC_SPC: SEND_STRING("the "); set_suffix_state('e'); break;
                    case KC_T: tap_code16(KC_COMMA); break;
                    case KC_TAB: SEND_STRING("the "); set_suffix_state('e'); break;
                    case KC_W: SEND_STRING("hich "); set_suffix_state('h'); break;
                    case KC_Z: tap_code16(KC_BSPC); SEND_STRING("Spring Boot "); set_suffix_state('t'); break;
                    case S(KC_B): tap_code16(KC_BSPC); SEND_STRING("through "); set_suffix_state('h'); break;
                    case S(KC_C): tap_code16(KC_EXLM); break;
                    case S(KC_D): SEND_STRING("on't "); set_suffix_state('t'); break;
                    case S(KC_L): SEND_STRING("eave "); set_suffix_state('e'); break;
                    case S(KC_N): tap_code16(KC_QUOTE); break;
                    case S(KC_O): tap_code16(KC_BSPC); SEND_STRING("without "); set_suffix_state('t'); break;
                    case S(KC_P): tap_code16(KC_BSPC); SEND_STRING("declarative config "); set_suffix_state('g'); break;
                    case S(KC_R): tap_code16(KC_BSPC); SEND_STRING("people "); set_suffix_state('e'); break;
                    case S(KC_T): tap_code16(KC_COMMA); break;
                    case S(KC_W): SEND_STRING("hich "); set_suffix_state('h'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); SEND_STRING("Spring Boot "); set_suffix_state('t'); break;
                }
                set_last_keycode(MAGIC_H);
                return false;
            case MAGIC_I:
                switch (get_last_keycode()) {
                    case KC_A: SEND_STRING("nother "); set_suffix_state('r'); break;
                    case KC_B: tap_code16(KC_BSPC); SEND_STRING("though "); set_suffix_state('h'); break;
                    case KC_C: tap_code16(KC_QUES); break;
                    case KC_D: SEND_STRING("oes "); set_suffix_state('s'); break;
                    case KC_G: tap_code16(KC_BSPC); SEND_STRING("realize "); set_suffix_state('e'); break;
                    case KC_N: SEND_STRING("umber "); set_suffix_state('r'); break;
                    case KC_O: SEND_STRING("nly "); set_suffix_state('y'); break;
                    case KC_P: SEND_STRING("robably "); set_suffix_state('y'); break;
                    case KC_R: tap_code16(KC_BSPC); SEND_STRING("elaborate "); set_suffix_state('e'); break;
                    case KC_SPC: tap_code16(KC_BSPC); SEND_STRING(". "); add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state(); break;
                    case KC_T: tap_code16(KC_DOT); break;
                    case KC_U: SEND_STRING("pdate "); set_suffix_state('e'); break;
                    case KC_W: SEND_STRING("hen "); set_suffix_state('n'); break;
                    case KC_Y: tap_code16(KC_BSPC); SEND_STRING("worry "); set_suffix_state('y'); break;
                    case KC_Z: tap_code16(KC_BSPC); SEND_STRING("Prometheus "); set_suffix_state('s'); break;
                    case S(KC_A): SEND_STRING("nother "); set_suffix_state('r'); break;
                    case S(KC_B): tap_code16(KC_BSPC); SEND_STRING("though "); set_suffix_state('h'); break;
                    case S(KC_C): tap_code16(KC_QUES); break;
                    case S(KC_D): SEND_STRING("oes "); set_suffix_state('s'); break;
                    case S(KC_G): tap_code16(KC_BSPC); SEND_STRING("realize "); set_suffix_state('e'); break;
                    case S(KC_N): SEND_STRING("umber "); set_suffix_state('r'); break;
                    case S(KC_O): SEND_STRING("nly "); set_suffix_state('y'); break;
                    case S(KC_P): SEND_STRING("robably "); set_suffix_state('y'); break;
                    case S(KC_R): tap_code16(KC_BSPC); SEND_STRING("elaborate "); set_suffix_state('e'); break;
                    case S(KC_T): tap_code16(KC_DOT); break;
                    case S(KC_U): SEND_STRING("pdate "); set_suffix_state('e'); break;
                    case S(KC_W): SEND_STRING("hen "); set_suffix_state('n'); break;
                    case S(KC_Y): tap_code16(KC_BSPC); SEND_STRING("worry "); set_suffix_state('y'); break;
                    case S(KC_Z): tap_code16(KC_BSPC); SEND_STRING("Prometheus "); set_suffix_state('s'); break;
                }
                set_last_keycode(MAGIC_I);
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
        case MAGIC_D:
        case MAGIC_E:
        case MAGIC_F:
        case MAGIC_G:
        case MAGIC_H:
        case MAGIC_I:
            return false;
    }

    prev_keycode = last_keycode;
    last_keycode = keycode;
    return true;  // Other keys can be repeated.
}
