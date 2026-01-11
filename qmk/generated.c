/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int alternateLayer = -1;
int layer = _BASE;
#define CHORD_INACTIVE -10000
int chord_state = CHORD_INACTIVE; // -1 = root, other negative = transition states, non-negative = byte offsets
int chord_depth = 0; // Track number of letters in current chord



int chord_transition(int state, uint16_t keycode) {
    switch (state) {
                // z
                case -223:
                    if (keycode == KC_SPC) return -224;
                    if (keycode == KC_COMMA) return -235;
                    if (keycode == KC_DOT) return -229;
                    if (keycode == KC_A) return -225;
                    if (keycode == KC_E) return -226;
                    if (keycode == KC_H) return -230;
                    if (keycode == KC_I) return -227;
                    if (keycode == KC_J) return -233;
                    if (keycode == KC_O) return -228;
                    if (keycode == KC_R) return -234;
                    if (keycode == KC_U) return -231;
                    if (keycode == KC_Y) return -232;
                    break;
                // x
                case -210:
                    if (keycode == KC_SPC) return -211;
                    if (keycode == KC_COMMA) return -222;
                    if (keycode == KC_DOT) return -216;
                    if (keycode == KC_A) return -212;
                    if (keycode == KC_E) return -213;
                    if (keycode == KC_H) return -217;
                    if (keycode == KC_I) return -214;
                    if (keycode == KC_J) return -215;
                    if (keycode == KC_O) return -219;
                    if (keycode == KC_R) return -221;
                    if (keycode == KC_U) return -218;
                    if (keycode == KC_Y) return -220;
                    break;
                // w
                case -197:
                    if (keycode == KC_SPC) return -198;
                    if (keycode == KC_COMMA) return -208;
                    if (keycode == KC_DOT) return -207;
                    if (keycode == KC_A) return -199;
                    if (keycode == KC_E) return -200;
                    if (keycode == KC_H) return -201;
                    if (keycode == KC_I) return -202;
                    if (keycode == KC_J) return -203;
                    if (keycode == KC_O) return -204;
                    if (keycode == KC_R) return -205;
                    if (keycode == KC_U) return -209;
                    if (keycode == KC_Y) return -206;
                    break;
                // v
                case -184:
                    if (keycode == KC_SPC) return -185;
                    if (keycode == KC_COMMA) return -196;
                    if (keycode == KC_DOT) return -193;
                    if (keycode == KC_A) return -186;
                    if (keycode == KC_E) return -187;
                    if (keycode == KC_H) return -194;
                    if (keycode == KC_I) return -188;
                    if (keycode == KC_J) return -195;
                    if (keycode == KC_O) return -189;
                    if (keycode == KC_R) return -190;
                    if (keycode == KC_U) return -191;
                    if (keycode == KC_Y) return -192;
                    break;
                // t
                case -171:
                    if (keycode == KC_SPC) return -172;
                    if (keycode == KC_COMMA) return -183;
                    if (keycode == KC_DOT) return -182;
                    if (keycode == KC_A) return -173;
                    if (keycode == KC_E) return -174;
                    if (keycode == KC_H) return -175;
                    if (keycode == KC_I) return -176;
                    if (keycode == KC_J) return -177;
                    if (keycode == KC_O) return -178;
                    if (keycode == KC_R) return -179;
                    if (keycode == KC_U) return -180;
                    if (keycode == KC_Y) return -181;
                    break;
                // s
                case -158:
                    if (keycode == KC_SPC) return -159;
                    if (keycode == KC_COMMA) return -170;
                    if (keycode == KC_DOT) return -169;
                    if (keycode == KC_A) return -160;
                    if (keycode == KC_E) return -161;
                    if (keycode == KC_H) return -162;
                    if (keycode == KC_I) return -163;
                    if (keycode == KC_J) return -164;
                    if (keycode == KC_O) return -165;
                    if (keycode == KC_R) return -166;
                    if (keycode == KC_U) return -167;
                    if (keycode == KC_Y) return -168;
                    break;
                // r
                case -146:
                    if (keycode == KC_SPC) return -147;
                    if (keycode == KC_COMMA) return -157;
                    if (keycode == KC_DOT) return -156;
                    if (keycode == KC_A) return -148;
                    if (keycode == KC_E) return -149;
                    if (keycode == KC_H) return -150;
                    if (keycode == KC_I) return -151;
                    if (keycode == KC_J) return -152;
                    if (keycode == KC_O) return -153;
                    if (keycode == KC_U) return -154;
                    if (keycode == KC_Y) return -155;
                    break;
                // q
                case -134:
                    if (keycode == KC_SPC) return -135;
                    if (keycode == KC_COMMA) return -139;
                    if (keycode == KC_A) return -140;
                    if (keycode == KC_E) return -141;
                    if (keycode == KC_H) return -142;
                    if (keycode == KC_I) return -137;
                    if (keycode == KC_J) return -143;
                    if (keycode == KC_O) return -138;
                    if (keycode == KC_R) return -144;
                    if (keycode == KC_U) return -136;
                    if (keycode == KC_Y) return -145;
                    break;
                // p
                case -121:
                    if (keycode == KC_SPC) return -122;
                    if (keycode == KC_COMMA) return -133;
                    if (keycode == KC_DOT) return -131;
                    if (keycode == KC_A) return -123;
                    if (keycode == KC_E) return -124;
                    if (keycode == KC_H) return -132;
                    if (keycode == KC_I) return -125;
                    if (keycode == KC_J) return -126;
                    if (keycode == KC_O) return -127;
                    if (keycode == KC_R) return -128;
                    if (keycode == KC_U) return -129;
                    if (keycode == KC_Y) return -130;
                    break;
                // n
                case -108:
                    if (keycode == KC_SPC) return -109;
                    if (keycode == KC_COMMA) return -120;
                    if (keycode == KC_DOT) return -119;
                    if (keycode == KC_A) return -110;
                    if (keycode == KC_E) return -111;
                    if (keycode == KC_H) return -112;
                    if (keycode == KC_I) return -113;
                    if (keycode == KC_J) return -114;
                    if (keycode == KC_O) return -115;
                    if (keycode == KC_R) return -116;
                    if (keycode == KC_U) return -117;
                    if (keycode == KC_Y) return -118;
                    break;
                // m
                case -96:
                    if (keycode == KC_SPC) return -97;
                    if (keycode == KC_COMMA) return -107;
                    if (keycode == KC_DOT) return -106;
                    if (keycode == KC_A) return -98;
                    if (keycode == KC_E) return -99;
                    if (keycode == KC_H) return -100;
                    if (keycode == KC_I) return -101;
                    if (keycode == KC_J) return -102;
                    if (keycode == KC_O) return -103;
                    if (keycode == KC_U) return -104;
                    if (keycode == KC_Y) return -105;
                    break;
                // l
                case -83:
                    if (keycode == KC_SPC) return -84;
                    if (keycode == KC_COMMA) return -95;
                    if (keycode == KC_DOT) return -94;
                    if (keycode == KC_A) return -85;
                    if (keycode == KC_E) return -86;
                    if (keycode == KC_H) return -87;
                    if (keycode == KC_I) return -88;
                    if (keycode == KC_J) return -89;
                    if (keycode == KC_O) return -90;
                    if (keycode == KC_R) return -91;
                    if (keycode == KC_U) return -92;
                    if (keycode == KC_Y) return -93;
                    break;
                // k
                case -70:
                    if (keycode == KC_SPC) return -71;
                    if (keycode == KC_COMMA) return -80;
                    if (keycode == KC_DOT) return -79;
                    if (keycode == KC_A) return -72;
                    if (keycode == KC_E) return -73;
                    if (keycode == KC_H) return -81;
                    if (keycode == KC_I) return -74;
                    if (keycode == KC_J) return -75;
                    if (keycode == KC_O) return -76;
                    if (keycode == KC_R) return -77;
                    if (keycode == KC_U) return -82;
                    if (keycode == KC_Y) return -78;
                    break;
                // j
                case -67:
                    if (keycode == KC_SPC) return -68;
                    if (keycode == KC_A) return -69;
                    break;
                // g
                case -54:
                    if (keycode == KC_SPC) return -55;
                    if (keycode == KC_COMMA) return -66;
                    if (keycode == KC_DOT) return -65;
                    if (keycode == KC_A) return -56;
                    if (keycode == KC_E) return -57;
                    if (keycode == KC_H) return -58;
                    if (keycode == KC_I) return -59;
                    if (keycode == KC_J) return -60;
                    if (keycode == KC_O) return -61;
                    if (keycode == KC_R) return -62;
                    if (keycode == KC_U) return -63;
                    if (keycode == KC_Y) return -64;
                    break;
                // f
                case -41:
                    if (keycode == KC_SPC) return -42;
                    if (keycode == KC_COMMA) return -53;
                    if (keycode == KC_DOT) return -52;
                    if (keycode == KC_A) return -43;
                    if (keycode == KC_E) return -44;
                    if (keycode == KC_H) return -45;
                    if (keycode == KC_I) return -46;
                    if (keycode == KC_J) return -47;
                    if (keycode == KC_O) return -48;
                    if (keycode == KC_R) return -49;
                    if (keycode == KC_U) return -50;
                    if (keycode == KC_Y) return -51;
                    break;
                // d
                case -28:
                    if (keycode == KC_SPC) return -29;
                    if (keycode == KC_COMMA) return -39;
                    if (keycode == KC_DOT) return -38;
                    if (keycode == KC_A) return -30;
                    if (keycode == KC_E) return -31;
                    if (keycode == KC_H) return -32;
                    if (keycode == KC_I) return -33;
                    if (keycode == KC_J) return -40;
                    if (keycode == KC_O) return -34;
                    if (keycode == KC_R) return -35;
                    if (keycode == KC_U) return -36;
                    if (keycode == KC_Y) return -37;
                    break;
                // c
                case -15:
                    if (keycode == KC_SPC) return -16;
                    if (keycode == KC_COMMA) return -27;
                    if (keycode == KC_DOT) return -26;
                    if (keycode == KC_A) return -17;
                    if (keycode == KC_E) return -18;
                    if (keycode == KC_H) return -19;
                    if (keycode == KC_I) return -20;
                    if (keycode == KC_J) return -21;
                    if (keycode == KC_O) return -22;
                    if (keycode == KC_R) return -23;
                    if (keycode == KC_U) return -24;
                    if (keycode == KC_Y) return -25;
                    break;
                // b
                case -2:
                    if (keycode == KC_SPC) return -3;
                    if (keycode == KC_COMMA) return -14;
                    if (keycode == KC_DOT) return -13;
                    if (keycode == KC_A) return -4;
                    if (keycode == KC_E) return -5;
                    if (keycode == KC_H) return -6;
                    if (keycode == KC_I) return -7;
                    if (keycode == KC_J) return -8;
                    if (keycode == KC_O) return -9;
                    if (keycode == KC_R) return -10;
                    if (keycode == KC_U) return -11;
                    if (keycode == KC_Y) return -12;
                    break;
                case -1:
                    if (keycode == KC_B) return -2;
                    if (keycode == KC_C) return -15;
                    if (keycode == KC_D) return -28;
                    if (keycode == KC_F) return -41;
                    if (keycode == KC_G) return -54;
                    if (keycode == KC_J) return -67;
                    if (keycode == KC_K) return -70;
                    if (keycode == KC_L) return -83;
                    if (keycode == KC_M) return -96;
                    if (keycode == KC_N) return -108;
                    if (keycode == KC_P) return -121;
                    if (keycode == KC_Q) return -134;
                    if (keycode == KC_R) return -146;
                    if (keycode == KC_S) return -158;
                    if (keycode == KC_T) return -171;
                    if (keycode == KC_V) return -184;
                    if (keycode == KC_W) return -197;
                    if (keycode == KC_X) return -210;
                    if (keycode == KC_Z) return -223;
                    break;
    default:
        // Invalid transition, stop chord mode
        return CHORD_INACTIVE;
    }
    return CHORD_INACTIVE;
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch(index) {
    case C_BASE_CHORD_KEY: return 200;
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
                    case KC_A: tap_code16(KC_U); return false;
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
                    case KC_U: tap_code16(KC_A); return false;
                    case KC_V: SEND_STRING("en"); return false;
                    case KC_W: tap_code16(KC_S); return false;
                    case KC_X: tap_code16(KC_C); return false;
                    case S(KC_A): tap_code16(KC_U); return false;
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
                    case S(KC_U): tap_code16(KC_A); return false;
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
