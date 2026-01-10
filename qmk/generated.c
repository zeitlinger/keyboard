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
                    if (keycode == KC_B) return 2;
                    if (keycode == KC_C) return 13;
                    if (keycode == KC_D) return 28;
                    if (keycode == KC_F) return 39;
                    if (keycode == KC_G) return 52;
                    if (keycode == KC_K) return 62;
                    if (keycode == KC_L) return 64;
                    if (keycode == KC_M) return 75;
                    if (keycode == KC_N) return 85;
                    if (keycode == KC_P) return 100;
                    if (keycode == KC_R) return 112;
                    if (keycode == KC_S) return 129;
                    if (keycode == KC_T) return 149;
                    if (keycode == KC_V) return 166;
                    if (keycode == KC_W) return 169;
                    if (keycode == KC_Z) return 183;
                    break;
                // b
                case 2:
                    if (keycode == KC_A) return 3;
                    if (keycode == KC_E) return 4;
                    if (keycode == KC_H) return 9;
                    if (keycode == KC_L) return 10;
                    if (keycode == KC_R) return 11;
                    if (keycode == KC_U) return 12;
                    break;
                // be
                case 4:
                    if (keycode == KC_F) return 5;
                    if (keycode == KC_L) return 6;
                    if (keycode == KC_T) return 7;
                    if (keycode == KC_W) return 8;
                    break;
                // c
                case 13:
                    if (keycode == KC_A) return 14;
                    if (keycode == KC_E) return 15;
                    if (keycode == KC_H) return 16;
                    if (keycode == KC_I) return 17;
                    if (keycode == KC_L) return 18;
                    if (keycode == KC_N) return 19;
                    if (keycode == KC_O) return 20;
                    if (keycode == KC_R) return 24;
                    if (keycode == KC_T) return 25;
                    if (keycode == KC_U) return 26;
                    if (keycode == KC_Y) return 27;
                    break;
                // co
                case 20:
                    if (keycode == KC_N) return 21;
                    if (keycode == KC_U) return 22;
                    if (keycode == KC_V) return 23;
                    break;
                // d
                case 28:
                    if (keycode == KC_A) return 29;
                    if (keycode == KC_C) return 30;
                    if (keycode == KC_E) return 31;
                    if (keycode == KC_F) return 32;
                    if (keycode == KC_N) return 33;
                    if (keycode == KC_O) return 35;
                    if (keycode == KC_U) return 37;
                    if (keycode == KC_Y) return 38;
                    break;
                // dn
                case 33:
                    if (keycode == KC_T) return 34;
                    break;
                // do
                case 35:
                    if (keycode == KC_E) return 36;
                    break;
                // f
                case 39:
                    if (keycode == KC_A) return 40;
                    if (keycode == KC_I) return 43;
                    if (keycode == KC_L) return 48;
                    if (keycode == KC_O) return 49;
                    if (keycode == KC_T) return 50;
                    if (keycode == KC_U) return 51;
                    break;
                // fa
                case 40:
                    if (keycode == KC_M) return 41;
                    if (keycode == KC_T) return 42;
                    break;
                // fi
                case 43:
                    if (keycode == KC_G) return 44;
                    if (keycode == KC_N) return 45;
                    break;
                // fin
                case 45:
                    if (keycode == KC_G) return 46;
                    if (keycode == KC_I) return 47;
                    break;
                // g
                case 52:
                    if (keycode == KC_A) return 53;
                    if (keycode == KC_E) return 54;
                    if (keycode == KC_H) return 55;
                    if (keycode == KC_L) return 56;
                    if (keycode == KC_O) return 57;
                    if (keycode == KC_R) return 58;
                    if (keycode == KC_S) return 60;
                    if (keycode == KC_U) return 61;
                    break;
                // gr
                case 58:
                    if (keycode == KC_O) return 59;
                    break;
                // k
                case 62:
                    if (keycode == KC_Y) return 63;
                    break;
                // l
                case 64:
                    if (keycode == KC_A) return 65;
                    if (keycode == KC_E) return 66;
                    if (keycode == KC_F) return 67;
                    if (keycode == KC_H) return 68;
                    if (keycode == KC_I) return 69;
                    if (keycode == KC_M) return 70;
                    if (keycode == KC_O) return 71;
                    if (keycode == KC_S) return 72;
                    if (keycode == KC_T) return 73;
                    if (keycode == KC_Y) return 74;
                    break;
                // m
                case 75:
                    if (keycode == KC_E) return 76;
                    if (keycode == KC_H) return 77;
                    if (keycode == KC_I) return 78;
                    if (keycode == KC_M) return 80;
                    if (keycode == KC_O) return 81;
                    if (keycode == KC_S) return 82;
                    if (keycode == KC_U) return 83;
                    if (keycode == KC_Y) return 84;
                    break;
                // mi
                case 78:
                    if (keycode == KC_N) return 79;
                    break;
                // n
                case 85:
                    if (keycode == KC_A) return 86;
                    if (keycode == KC_C) return 87;
                    if (keycode == KC_H) return 88;
                    if (keycode == KC_I) return 89;
                    if (keycode == KC_O) return 90;
                    if (keycode == KC_S) return 93;
                    if (keycode == KC_T) return 96;
                    if (keycode == KC_U) return 97;
                    if (keycode == KC_Y) return 98;
                    break;
                // no
                case 90:
                    if (keycode == KC_T) return 91;
                    if (keycode == KC_U) return 92;
                    break;
                // ns
                case 93:
                    if (keycode == KC_I) return 94;
                    if (keycode == KC_T) return 95;
                    break;
                // ny
                case 98:
                    if (keycode == KC_O) return 99;
                    break;
                // p
                case 100:
                    if (keycode == KC_A) return 101;
                    if (keycode == KC_E) return 103;
                    if (keycode == KC_O) return 107;
                    if (keycode == KC_R) return 108;
                    if (keycode == KC_U) return 111;
                    break;
                // pa
                case 101:
                    if (keycode == KC_R) return 102;
                    break;
                // pe
                case 103:
                    if (keycode == KC_A) return 104;
                    if (keycode == KC_N) return 105;
                    if (keycode == KC_R) return 106;
                    break;
                // pr
                case 108:
                    if (keycode == KC_E) return 109;
                    if (keycode == KC_O) return 110;
                    break;
                // r
                case 112:
                    if (keycode == KC_A) return 113;
                    if (keycode == KC_D) return 114;
                    if (keycode == KC_E) return 115;
                    if (keycode == KC_I) return 122;
                    if (keycode == KC_L) return 123;
                    if (keycode == KC_N) return 124;
                    if (keycode == KC_O) return 125;
                    if (keycode == KC_S) return 126;
                    if (keycode == KC_Y) return 127;
                    break;
                // re
                case 115:
                    if (keycode == KC_A) return 116;
                    if (keycode == KC_M) return 117;
                    if (keycode == KC_P) return 118;
                    if (keycode == KC_S) return 119;
                    if (keycode == KC_T) return 120;
                    if (keycode == KC_V) return 121;
                    break;
                // ry
                case 127:
                    if (keycode == KC_O) return 128;
                    break;
                // s
                case 129:
                    if (keycode == KC_E) return 130;
                    if (keycode == KC_I) return 132;
                    if (keycode == KC_L) return 134;
                    if (keycode == KC_M) return 137;
                    if (keycode == KC_N) return 139;
                    if (keycode == KC_O) return 140;
                    if (keycode == KC_T) return 142;
                    if (keycode == KC_U) return 144;
                    if (keycode == KC_Y) return 148;
                    break;
                // se
                case 130:
                    if (keycode == KC_C) return 131;
                    break;
                // si
                case 132:
                    if (keycode == KC_L) return 133;
                    break;
                // sl
                case 134:
                    if (keycode == KC_I) return 135;
                    if (keycode == KC_O) return 136;
                    break;
                // sm
                case 137:
                    if (keycode == KC_I) return 138;
                    break;
                // so
                case 140:
                    if (keycode == KC_M) return 141;
                    break;
                // st
                case 142:
                    if (keycode == KC_O) return 143;
                    break;
                // su
                case 144:
                    if (keycode == KC_D) return 145;
                    if (keycode == KC_P) return 146;
                    if (keycode == KC_R) return 147;
                    break;
                // t
                case 149:
                    if (keycode == KC_A) return 150;
                    if (keycode == KC_C) return 152;
                    if (keycode == KC_H) return 153;
                    if (keycode == KC_I) return 158;
                    if (keycode == KC_N) return 160;
                    if (keycode == KC_O) return 161;
                    if (keycode == KC_S) return 164;
                    if (keycode == KC_Y) return 165;
                    break;
                // ta
                case 150:
                    if (keycode == KC_B) return 151;
                    break;
                // th
                case 153:
                    if (keycode == KC_A) return 154;
                    if (keycode == KC_O) return 155;
                    if (keycode == KC_R) return 157;
                    break;
                // tho
                case 155:
                    if (keycode == KC_U) return 156;
                    break;
                // ti
                case 158:
                    if (keycode == KC_C) return 159;
                    break;
                // to
                case 161:
                    if (keycode == KC_G) return 162;
                    if (keycode == KC_W) return 163;
                    break;
                // v
                case 166:
                    if (keycode == KC_I) return 167;
                    if (keycode == KC_Y) return 168;
                    break;
                // w
                case 169:
                    if (keycode == KC_A) return 170;
                    if (keycode == KC_H) return 172;
                    if (keycode == KC_I) return 176;
                    if (keycode == KC_R) return 179;
                    if (keycode == KC_S) return 180;
                    if (keycode == KC_U) return 181;
                    if (keycode == KC_Y) return 182;
                    break;
                // wa
                case 170:
                    if (keycode == KC_L) return 171;
                    break;
                // wh
                case 172:
                    if (keycode == KC_A) return 173;
                    if (keycode == KC_E) return 174;
                    break;
                // whe
                case 174:
                    if (keycode == KC_R) return 175;
                    break;
                // wi
                case 176:
                    if (keycode == KC_N) return 177;
                    if (keycode == KC_T) return 178;
                    break;
    default:
        return state; // Invalid transition, ignore and stay in current state
    }
    return 0;
}

void chord_output(int state) {
    switch (state) {
                // b
        case 2: SEND_STRING("back"); break;
                // ba
        case 3: SEND_STRING("about"); break;
                // be
        case 4: SEND_STRING("because"); break;
                // bef
        case 5: SEND_STRING("before"); break;
                // bel
        case 6: SEND_STRING("believe"); break;
                // bet
        case 7: SEND_STRING("better"); break;
                // bew
        case 8: SEND_STRING("between"); break;
                // bh
        case 9: SEND_STRING("behind"); break;
                // bl
        case 10: SEND_STRING("black"); break;
                // br
        case 11: SEND_STRING("break"); break;
                // bu
        case 12: SEND_STRING("business"); break;
                // c
        case 13: SEND_STRING("could"); break;
                // ca
        case 14: SEND_STRING("actually"); break;
                // ce
        case 15: SEND_STRING("service"); break;
                // ch
        case 16: SEND_STRING("research"); break;
                // ci
        case 17: SEND_STRING("click"); break;
                // cl
        case 18: SEND_STRING("couple"); break;
                // cn
        case 19: SEND_STRING("change"); break;
                // con
        case 21: SEND_STRING("continue"); break;
                // cou
        case 22: SEND_STRING("course"); break;
                // cov
        case 23: SEND_STRING("cover"); break;
                // cr
        case 24: SEND_STRING("across"); break;
                // ct
        case 25: SEND_STRING("caught"); break;
                // cu
        case 26: SEND_STRING("couldn't"); break;
                // cy
        case 27: SEND_STRING("policy"); break;
                // d
        case 28: SEND_STRING("didn't"); break;
                // da
        case 29: SEND_STRING("today"); break;
                // dc
        case 30: SEND_STRING("decide"); break;
                // de
        case 31: SEND_STRING("video"); break;
                // df
        case 32: SEND_STRING("different"); break;
                // dnt
        case 34: SEND_STRING("hadn't"); break;
                // do
        case 35: SEND_STRING("don't"); break;
                // doe
        case 36: SEND_STRING("doesn't"); break;
                // du
        case 37: SEND_STRING("products"); break;
                // dy
        case 38: SEND_STRING("already"); break;
                // f
        case 39: SEND_STRING("from"); break;
                // fam
        case 41: SEND_STRING("family"); break;
                // fat
        case 42: SEND_STRING("father"); break;
                // fig
        case 44: SEND_STRING("figure"); break;
                // fin
        case 45: SEND_STRING("finally"); break;
                // fing
        case 46: SEND_STRING("finger"); break;
                // fini
        case 47: SEND_STRING("finish"); break;
                // fl
        case 48: SEND_STRING("follow"); break;
                // fo
        case 49: SEND_STRING("information"); break;
                // ft
        case 50: SEND_STRING("software"); break;
                // fu
        case 51: SEND_STRING("found"); break;
                // g
        case 52: SEND_STRING("again"); break;
                // ga
        case 53: SEND_STRING("began"); break;
                // ge
        case 54: SEND_STRING("general"); break;
                // gh
        case 55: SEND_STRING("rights"); break;
                // gl
        case 56: SEND_STRING("glance"); break;
                // go
        case 57: SEND_STRING("group"); break;
                // gr
        case 58: SEND_STRING("great"); break;
                // gro
        case 59: SEND_STRING("ground"); break;
                // gs
        case 60: SEND_STRING("against"); break;
                // gu
        case 61: SEND_STRING("guess"); break;
                // k
        case 62: SEND_STRING("question"); break;
                // ky
        case 63: SEND_STRING("quickly"); break;
                // l
        case 64: SEND_STRING("like"); break;
                // la
        case 65: SEND_STRING("laugh"); break;
                // le
        case 66: SEND_STRING("leave"); break;
                // lf
        case 67: SEND_STRING("himself"); break;
                // lh
        case 68: SEND_STRING("health"); break;
                // li
        case 69: SEND_STRING("light"); break;
                // lm
        case 70: SEND_STRING("almost"); break;
                // lo
        case 71: SEND_STRING("along"); break;
                // ls
        case 72: SEND_STRING("listen"); break;
                // lt
        case 73: SEND_STRING("little"); break;
                // ly
        case 74: SEND_STRING("always"); break;
                // m
        case 75: SEND_STRING("more"); break;
                // me
        case 76: SEND_STRING("message"); break;
                // mh
        case 77: SEND_STRING("might"); break;
                // min
        case 79: SEND_STRING("minute"); break;
                // mm
        case 80: SEND_STRING("moment"); break;
                // mo
        case 81: SEND_STRING("someone"); break;
                // ms
        case 82: SEND_STRING("items"); break;
                // mu
        case 83: SEND_STRING("music"); break;
                // my
        case 84: SEND_STRING("myself"); break;
                // n
        case 85: SEND_STRING("understand"); break;
                // na
        case 86: SEND_STRING("anyway"); break;
                // nc
        case 87: SEND_STRING("links"); break;
                // nh
        case 88: SEND_STRING("anything"); break;
                // ni
        case 89: SEND_STRING("university"); break;
                // not
        case 91: SEND_STRING("another"); break;
                // nou
        case 92: SEND_STRING("enough"); break;
                // ns
        case 93: SEND_STRING("answer"); break;
                // nsi
        case 94: SEND_STRING("inside"); break;
                // nst
        case 95: SEND_STRING("instead"); break;
                // nt
        case 96: SEND_STRING("nothing"); break;
                // nu
        case 97: SEND_STRING("number"); break;
                // ny
        case 98: SEND_STRING("company"); break;
                // nyo
        case 99: SEND_STRING("anyone"); break;
                // p
        case 100: SEND_STRING("people"); break;
                // pa
        case 101: SEND_STRING("privacy"); break;
                // par
        case 102: SEND_STRING("parent"); break;
                // pe
        case 103: SEND_STRING("place"); break;
                // pea
        case 104: SEND_STRING("please"); break;
                // pen
        case 105: SEND_STRING("happen"); break;
                // per
        case 106: SEND_STRING("person"); break;
                // po
        case 107: SEND_STRING("product"); break;
                // pr
        case 108: SEND_STRING("problem"); break;
                // pre
        case 109: SEND_STRING("pretty"); break;
                // pro
        case 110: SEND_STRING("probably"); break;
                // pu
        case 111: SEND_STRING("public"); break;
                // r
        case 112: SEND_STRING("really"); break;
                // ra
        case 113: SEND_STRING("program"); break;
                // rd
        case 114: SEND_STRING("order"); break;
                // rea
        case 116: SEND_STRING("ready"); break;
                // rem
        case 117: SEND_STRING("remember"); break;
                // rep
        case 118: SEND_STRING("reply"); break;
                // res
        case 119: SEND_STRING("there's"); break;
                // ret
        case 120: SEND_STRING("return"); break;
                // rev
        case 121: SEND_STRING("review"); break;
                // ri
        case 122: SEND_STRING("right"); break;
                // rl
        case 123: SEND_STRING("world"); break;
                // rn
        case 124: SEND_STRING("morning"); break;
                // ro
        case 125: SEND_STRING("around"); break;
                // rs
        case 126: SEND_STRING("years"); break;
                // ryo
        case 128: SEND_STRING("everyone"); break;
                // s
        case 129: SEND_STRING("should"); break;
                // se
        case 130: SEND_STRING("search"); break;
                // sec
        case 131: SEND_STRING("second"); break;
                // sil
        case 133: SEND_STRING("silence"); break;
                // sli
        case 135: SEND_STRING("slightly"); break;
                // slo
        case 136: SEND_STRING("slowly"); break;
                // smi
        case 138: SEND_STRING("smile"); break;
                // sn
        case 139: SEND_STRING("wasn't"); break;
                // som
        case 141: SEND_STRING("something"); break;
                // sto
        case 143: SEND_STRING("stood"); break;
                // su
        case 144: SEND_STRING("support"); break;
                // sud
        case 145: SEND_STRING("suddenly"); break;
                // sup
        case 146: SEND_STRING("suppose"); break;
                // sur
        case 147: SEND_STRING("surprise"); break;
                // sy
        case 148: SEND_STRING("system"); break;
                // t
        case 149: SEND_STRING("think"); break;
                // ta
        case 150: SEND_STRING("contact"); break;
                // tab
        case 151: SEND_STRING("table"); break;
                // tc
        case 152: SEND_STRING("watch"); break;
                // tha
        case 154: SEND_STRING("thanks"); break;
                // thou
        case 156: SEND_STRING("thought"); break;
                // thr
        case 157: SEND_STRING("through"); break;
                // tic
        case 159: SEND_STRING("notice"); break;
                // tn
        case 160: SEND_STRING("thing"); break;
                // to
        case 161: SEND_STRING("though"); break;
                // tog
        case 162: SEND_STRING("together"); break;
                // tow
        case 163: SEND_STRING("toward"); break;
                // ts
        case 164: SEND_STRING("that's"); break;
                // ty
        case 165: SEND_STRING("thank you"); break;
                // v
        case 166: SEND_STRING("available"); break;
                // vi
        case 167: SEND_STRING("services"); break;
                // vy
        case 168: SEND_STRING("everything"); break;
                // w
        case 169: SEND_STRING("would"); break;
                // wal
        case 171: SEND_STRING("walk"); break;
                // wh
        case 172: SEND_STRING("which"); break;
                // wha
        case 173: SEND_STRING("what's"); break;
                // wher
        case 175: SEND_STRING("where"); break;
                // win
        case 177: SEND_STRING("window"); break;
                // wit
        case 178: SEND_STRING("without"); break;
                // wr
        case 179: SEND_STRING("wrong"); break;
                // ws
        case 180: SEND_STRING("reviews"); break;
                // wu
        case 181: SEND_STRING("wouldn't"); break;
                // wy
        case 182: SEND_STRING("worry"); break;
                // z
        case 183: SEND_STRING("realize"); break;
    default:
        return;
    }
    tap_code16(KC_SPC);
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
