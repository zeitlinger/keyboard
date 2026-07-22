/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;

static bool magic_capitalize_next = false;
static bool magic_context_key_emitted = true;
static uint16_t magic_remembered_keycode = KC_NO;

// Magic string decoder lookup tables
#define MAGIC_STRING_APOSTROPHE_D 10
#define MAGIC_STRING_APOSTROPHE_L_L 14
#define MAGIC_STRING_APOSTROPHE_R_E 18
#define MAGIC_STRING_APOSTROPHE_S 22
#define MAGIC_STRING_APOSTROPHE_V_E 25
#define MAGIC_STRING_A_D_D_R_E_S_S 45
#define MAGIC_STRING_A_E 52
#define MAGIC_STRING_A_L_I_D_A_T_E 54
#define MAGIC_STRING_A_L_R_E_A_D_Y 60
#define MAGIC_STRING_A_L_W_A_Y_S 67
#define MAGIC_STRING_A_N_D 0
#define MAGIC_STRING_A_N_D_2 73
#define MAGIC_STRING_A_N_G_U_A_G_E 77
#define MAGIC_STRING_A_N_Y_T_H_I_N_G 82
#define MAGIC_STRING_A_P_P_L_Y 88
#define MAGIC_STRING_A_P_P_R_O_V_A_L 93
#define MAGIC_STRING_A_P_P_R_O_V_E 100
#define MAGIC_STRING_A_S_N_APOSTROPHE_T 106
#define MAGIC_STRING_B_E_C_A_M_E 111
#define MAGIC_STRING_B_E_C_A_U_S_E 118
#define MAGIC_STRING_B_E_C_O_M_E 125
#define MAGIC_STRING_B_U_T 5
#define MAGIC_STRING_C_H_A_N_G_E 132
#define MAGIC_STRING_C_O_N_F_U_S_I_N_G 137
#define MAGIC_STRING_DOT 29
#define MAGIC_STRING_D_I_D_N_APOSTROPHE_T 144
#define MAGIC_STRING_D_I_F_F_I_C_U_L_T_Y 151
#define MAGIC_STRING_D_I_S_A_B_L_E 162
#define MAGIC_STRING_D_O_E_S 169
#define MAGIC_STRING_D_O_E_S_N_APOSTROPHE_T 173
#define MAGIC_STRING_D_O_N_APOSTROPHE_T 179
#define MAGIC_STRING_E_C_A_U_S_E 184
#define MAGIC_STRING_E_C_O_M_E 190
#define MAGIC_STRING_E_H 196
#define MAGIC_STRING_E_N_A_B_L_E 198
#define MAGIC_STRING_E_N_E_R_A_T_E 204
#define MAGIC_STRING_E_N_T 209
#define MAGIC_STRING_E_P_A_R_A_T_E 212
#define MAGIC_STRING_E_R_S_I_O_N 217
#define MAGIC_STRING_E_U 222
#define MAGIC_STRING_E_V_E_R_Y_T_H_I_N_G 224
#define MAGIC_STRING_E_X_A_M_P_L_E 232
#define MAGIC_STRING_E_X_C_E_P_T 239
#define MAGIC_STRING_E_X_C_E_P_T_I_O_N 245
#define MAGIC_STRING_E_X_C_L_U_D_E 253
#define MAGIC_STRING_E_X_I_T 260
#define MAGIC_STRING_E_X_P_L_A_I_N 265
#define MAGIC_STRING_E_X_P_L_A_N_A_T_I_O_N 271
#define MAGIC_STRING_E_X_P_L_I_C_I_T 279
#define MAGIC_STRING_F_O_C_U_S_E_D 287
#define MAGIC_STRING_F_O_L_L_O_W_I_N_G 295
#define MAGIC_STRING_G_E_N_E_R_A_T_E 302
#define MAGIC_STRING_G_E_N_E_R_A_T_I_O_N 308
#define MAGIC_STRING_G_O_E_S 315
#define MAGIC_STRING_G_R_E_G_O_R_DOT_Z_E_I_T_L_I_N_G_E_R_U0040_G_R_A_F_A_N_A_DOT_C_O_M 319
#define MAGIC_STRING_G_R_E_G_O_R_U0040_Z_E_I_T_L_I_N_G_E_R_DOT_D_E 340
#define MAGIC_STRING_H_O_U_G_H 354
#define MAGIC_STRING_H_O_U_G_H_T 358
#define MAGIC_STRING_H_R_O_U_G_H 363
#define MAGIC_STRING_H_Y 368
#define MAGIC_STRING_H_Y_2 371
#define MAGIC_STRING_I_APOSTROPHE_M 32
#define MAGIC_STRING_I_D_N_APOSTROPHE_T 375
#define MAGIC_STRING_I_F_F_I_C_U_L_T_Y 381
#define MAGIC_STRING_I_M_I_L_A_R 391
#define MAGIC_STRING_I_M_P_L_E_M_E_N_T 397
#define MAGIC_STRING_I_M_P_L_E_M_E_N_T_A_T_I_O_N 405
#define MAGIC_STRING_I_M_P_O_R_T_A_N_T 416
#define MAGIC_STRING_I_M_P_O_S_S_I_B_L_E 423
#define MAGIC_STRING_I_M_P_R_O_V_E 432
#define MAGIC_STRING_I_N_S_T_R_U_M_E_N_T 439
#define MAGIC_STRING_I_N_S_T_R_U_M_E_N_T_A_T_I_O_N 446
#define MAGIC_STRING_I_O_N 456
#define MAGIC_STRING_J_U_S_T 459
#define MAGIC_STRING_K_N_E_W 463
#define MAGIC_STRING_K_N_O_W 468
#define MAGIC_STRING_K_N_O_W_L_E_D_G_E 473
#define MAGIC_STRING_L_A_N_G_U_A_G_E 481
#define MAGIC_STRING_L_G_T_M 37
#define MAGIC_STRING_M_E_N_T 487
#define MAGIC_STRING_M_E_R_G_E 491
#define MAGIC_STRING_M_I_G_R_A_T_E 496
#define MAGIC_STRING_M_I_G_R_A_T_I_O_N 502
#define MAGIC_STRING_M_U_L_T_I_P_L_E 509
#define MAGIC_STRING_N_APOSTROPHE_T 515
#define MAGIC_STRING_N_O_W 519
#define MAGIC_STRING_O_B_S_E_R_V_A_B_I_L_I_T_Y 523
#define MAGIC_STRING_O_C_U_S_E_D 535
#define MAGIC_STRING_O_E 542
#define MAGIC_STRING_O_E_S 544
#define MAGIC_STRING_O_E_S_N_APOSTROPHE_T 547
#define MAGIC_STRING_O_H 552
#define MAGIC_STRING_O_L_L_O_W_I_N_G 554
#define MAGIC_STRING_O_M_E_O_N_E 560
#define MAGIC_STRING_O_M_E_T_H_I_N_G 566
#define MAGIC_STRING_O_N_APOSTROPHE_T 573
#define MAGIC_STRING_O_N_L_Y 577
#define MAGIC_STRING_O_T_H_E_R_W_I_S_E 582
#define MAGIC_STRING_P_E_R_F_O_R_M_A_N_C_E 589
#define MAGIC_STRING_P_L 598
#define MAGIC_STRING_P_O_S_S_I_B_L_E 600
#define MAGIC_STRING_P_P_L 607
#define MAGIC_STRING_P_R_O_B_A_B_L_Y 610
#define MAGIC_STRING_Q_U 42
#define MAGIC_STRING_Q_U_2 619
#define MAGIC_STRING_Q_U_E_S_T_I_O_N 622
#define MAGIC_STRING_R_E_S_O_L_U_T_I_O_N 628
#define MAGIC_STRING_R_E_S_O_L_V_E 635
#define MAGIC_STRING_S_E_P_A_R_A_T_E 641
#define MAGIC_STRING_S_E_P_A_R_A_T_I_O_N 647
#define MAGIC_STRING_S_I_M_I_L_A_R 654
#define MAGIC_STRING_S_I_O_N 660
#define MAGIC_STRING_S_O_M_E_O_N_E 663
#define MAGIC_STRING_S_O_M_E_T_H_I_N_G 669
#define MAGIC_STRING_S_U_G_G_E_S_T 676
#define MAGIC_STRING_S_U_P_P_O_R_T 681
#define MAGIC_STRING_S_W_I_T_C_H 686
#define MAGIC_STRING_T_H_A_N_K_S 700
#define MAGIC_STRING_T_H_A_N_K_Y_O_U 692
#define MAGIC_STRING_T_H_E 705
#define MAGIC_STRING_T_H_I_N_K 708
#define MAGIC_STRING_T_H_O_U_G_H 713
#define MAGIC_STRING_T_H_O_U_G_H_T 718
#define MAGIC_STRING_T_H_R_O_U_G_H 723
#define MAGIC_STRING_T_I_O_N 728
#define MAGIC_STRING_U_H 731
#define MAGIC_STRING_U_L_T_I_P_L_E 733
#define MAGIC_STRING_U_N_D_E_R_S_T_A_N_D 738
#define MAGIC_STRING_U_P_D_A_T_E 746
#define MAGIC_STRING_U_P_P_O_R_T 751
#define MAGIC_STRING_V_A_L_I_D_A_T_E 756
#define MAGIC_STRING_V_A_L_I_D_A_T_I_O_N 763
#define MAGIC_STRING_V_E_R_S_I_O_N 771
#define MAGIC_STRING_W_A_S_N_APOSTROPHE_T 777
#define MAGIC_STRING_W_H_Y 783
#define MAGIC_STRING_W_L 788
#define MAGIC_STRING_W_O_N_APOSTROPHE_T 791
#define MAGIC_STRING_W_O_R_S_E 796
#define MAGIC_STRING_W_O_R_S_T 801
#define MAGIC_STRING_Y_R 806
#define MAGIC_STRING_Z_E_I_T_L_I_N_G_E_R_U0040_G_M_A_I_L_DOT_C_O_M 809

static const char magic_char_4bit[] = {
    ' ', 'e', 't', 'n', 'o', 'i', 'a', 'l', 'r', 's', 'g', 'u', 'p', 'h'
};

static const char magic_char_extended[] = {
    'm', 'd', 'c', '\'', 'w', 'y', 'b', 'v', 'f', 'x', 'k', '.', '@', 'z', 'q', 'G', 'I', 'L', 'M', 'Q', 'T', 'j'
};

static const uint8_t magic_string_data[] = {
    0x05, 0x06, 0x3f, 0xe1, 0x00, 0x05, 0x0f, 0xe6, 0xb2, 0x00, 0x03, 0xe3, 0xe1, 0x00, 0x04, 0xe3,
    0x77, 0x00, 0x04, 0xe3, 0x81, 0x00, 0x03, 0xe3, 0x90, 0x04, 0xe3, 0xe7, 0x10, 0x02, 0xeb, 0x00,
    0x04, 0xf0, 0xe3, 0xe0, 0x00, 0x04, 0xf1, 0xef, 0xf4, 0xf2, 0x02, 0xf3, 0xb0, 0x08, 0x6f, 0xe1,
    0xe1, 0x81, 0x99, 0x00, 0x02, 0x61, 0x08, 0x67, 0x5f, 0xe1, 0x62, 0x10, 0x08, 0x67, 0x81, 0x6f,
    0xe1, 0xe5, 0x00, 0x07, 0x67, 0xe4, 0x6f, 0xe5, 0x90, 0x04, 0x63, 0xe1, 0x00, 0x08, 0x63, 0xab,
    0x6a, 0x10, 0x09, 0x63, 0xe5, 0x2d, 0x53, 0xa0, 0x06, 0x6c, 0xc7, 0xe5, 0x00, 0x09, 0x6c, 0xc8,
    0x4f, 0xe7, 0x67, 0x00, 0x08, 0x6c, 0xc8, 0x4f, 0xe7, 0x10, 0x06, 0x69, 0x3f, 0xe3, 0x20, 0x07,
    0xe6, 0x1f, 0xe2, 0x6f, 0xe0, 0x10, 0x08, 0xe6, 0x1f, 0xe2, 0x6b, 0x91, 0x00, 0x07, 0xe6, 0x1f,
    0xe2, 0x4f, 0xe0, 0x10, 0x07, 0xe2, 0xd6, 0x3a, 0x10, 0x0a, 0xe2, 0x43, 0xe8, 0xb9, 0x53, 0xa0,
    0x07, 0xe1, 0x5f, 0xe1, 0x3f, 0xe3, 0x20, 0x0b, 0xe1, 0x5f, 0xe8, 0xe8, 0x5f, 0xe2, 0xb7, 0x2f,
    0xe5, 0x00, 0x08, 0xe1, 0x59, 0x6f, 0xe6, 0x71, 0x00, 0x05, 0xe1, 0x41, 0x90, 0x08, 0xe1, 0x41,
    0x93, 0xe3, 0x20, 0x06, 0xe1, 0x43, 0xe3, 0x20, 0x07, 0x1f, 0xe2, 0x6b, 0x91, 0x00, 0x06, 0x1f,
    0xe2, 0x4f, 0xe0, 0x10, 0x02, 0x1d, 0x07, 0x13, 0x6f, 0xe6, 0x71, 0x00, 0x08, 0x13, 0x18, 0x62,
    0x10, 0x03, 0x13, 0x20, 0x08, 0x1c, 0x68, 0x62, 0x10, 0x07, 0x18, 0x95, 0x43, 0x00, 0x02, 0x1b,
    0x0b, 0x1f, 0xe7, 0x18, 0xe5, 0x2d, 0x53, 0xa0, 0x08, 0x1f, 0xe9, 0x6f, 0xe0, 0xc7, 0x10, 0x07,
    0x1f, 0xe9, 0xe2, 0x1c, 0x20, 0x0a, 0x1f, 0xe9, 0xe2, 0x1c, 0x25, 0x43, 0x00, 0x08, 0x1f, 0xe9,
    0xe2, 0x7b, 0xe1, 0x10, 0x05, 0x1f, 0xe9, 0x52, 0x00, 0x08, 0x1f, 0xe9, 0xc7, 0x65, 0x30, 0x0c,
    0x1f, 0xe9, 0xc7, 0x63, 0x62, 0x54, 0x30, 0x09, 0x1f, 0xe9, 0xc7, 0x5f, 0xe2, 0x52, 0x00, 0x08,
    0xe8, 0x4f, 0xe2, 0xb9, 0x1f, 0xe1, 0x00, 0x0a, 0xe8, 0x47, 0x74, 0xe4, 0x53, 0xa0, 0x09, 0xa1,
    0x31, 0x86, 0x21, 0x00, 0x0b, 0xa1, 0x31, 0x86, 0x25, 0x43, 0x00, 0x05, 0xa4, 0x19, 0x00, 0x1d,
    0xa8, 0x1a, 0x48, 0xeb, 0xed, 0x15, 0x27, 0x53, 0xa1, 0x8f, 0xec, 0xa8, 0x6f, 0xe8, 0x63, 0x6f,
    0xeb, 0xe2, 0x4f, 0xe0, 0x14, 0xa8, 0x1a, 0x48, 0xec, 0xed, 0x15, 0x27, 0x53, 0xa1, 0x8f, 0xeb,
    0xe1, 0x10, 0x06, 0xd4, 0xba, 0xd0, 0x07, 0xd4, 0xba, 0xd2, 0x00, 0x07, 0xd8, 0x4b, 0xad, 0x00,
    0x02, 0xdf, 0xe5, 0x03, 0xdf, 0xe5, 0x00, 0x06, 0x5f, 0xe1, 0x3f, 0xe3, 0x20, 0x0a, 0x5f, 0xe8,
    0xe8, 0x5f, 0xe2, 0xb7, 0x2f, 0xe5, 0x00, 0x07, 0x5f, 0xe0, 0x57, 0x68, 0x00, 0x0a, 0x5f, 0xe0,
    0xc7, 0x1f, 0xe0, 0x13, 0x20, 0x0f, 0x5f, 0xe0, 0xc7, 0x1f, 0xe0, 0x13, 0x26, 0x25, 0x43, 0x00,
    0x0a, 0x5f, 0xe0, 0xc4, 0x82, 0x63, 0x20, 0x0b, 0x5f, 0xe0, 0xc4, 0x99, 0x5f, 0xe6, 0x71, 0x00,
    0x08, 0x5f, 0xe0, 0xc8, 0x4f, 0xe7, 0x10, 0x0b, 0x53, 0x92, 0x8b, 0xe0, 0x13, 0x20, 0x10, 0x53,
    0x92, 0x8b, 0xe0, 0x13, 0x26, 0x25, 0x43, 0x00, 0x03, 0x54, 0x30, 0x05, 0xf5, 0xb9, 0x20, 0x05,
    0xea, 0x31, 0xe4, 0x00, 0x05, 0xea, 0x34, 0xe4, 0x00, 0x0a, 0xea, 0x34, 0xe4, 0x71, 0xe1, 0xa1,
    0x00, 0x09, 0x76, 0x3a, 0xb6, 0xa1, 0x00, 0x04, 0xe0, 0x13, 0x20, 0x06, 0xe0, 0x18, 0xa1, 0x00,
    0x08, 0xe0, 0x5a, 0x86, 0x21, 0x00, 0x0a, 0xe0, 0x5a, 0x86, 0x25, 0x43, 0x00, 0x09, 0xe0, 0xb7,
    0x25, 0xc7, 0x10, 0x04, 0x3f, 0xe3, 0x20, 0x04, 0x34, 0xe4, 0x00, 0x0e, 0x4f, 0xe6, 0x91, 0x8f,
    0xe7, 0x6f, 0xe6, 0x57, 0x52, 0xe5, 0x00, 0x07, 0x4f, 0xe2, 0xb9, 0x1f, 0xe1, 0x00, 0x02, 0x41,
    0x04, 0x41, 0x90, 0x07, 0x41, 0x93, 0xe3, 0x20, 0x02, 0x4d, 0x09, 0x47, 0x74, 0xe4, 0x53, 0xa0,
    0x07, 0x4f, 0xe0, 0x14, 0x31, 0x00, 0x09, 0x4f, 0xe0, 0x12, 0xd5, 0x3a, 0x00, 0x05, 0x43, 0xe3,
    0x20, 0x05, 0x43, 0x7f, 0xe5, 0x00, 0x0a, 0x42, 0xd1, 0x8f, 0xe4, 0x59, 0x10, 0x0c, 0xc1, 0x8f,
    0xe8, 0x48, 0xe0, 0x63, 0xe2, 0x10, 0x02, 0xc7, 0x09, 0xc4, 0x99, 0x5f, 0xe6, 0x71, 0x00, 0x03,
    0xcc, 0x70, 0x09, 0xc8, 0x4f, 0xe6, 0x6f, 0xe6, 0x7f, 0xe5, 0x00, 0x02, 0xee, 0xb0, 0x09, 0xee,
    0xb1, 0x92, 0x54, 0x30, 0x0b, 0x81, 0x94, 0x7b, 0x25, 0x43, 0x00, 0x08, 0x81, 0x94, 0x7f, 0xe7,
    0x10, 0x09, 0x91, 0xc6, 0x86, 0x21, 0x00, 0x0b, 0x91, 0xc6, 0x86, 0x25, 0x43, 0x00, 0x08, 0x95,
    0xe0, 0x57, 0x68, 0x00, 0x04, 0x95, 0x43, 0x08, 0x94, 0xe0, 0x14, 0x31, 0x00, 0x0a, 0x94, 0xe0,
    0x12, 0xd5, 0x3a, 0x00, 0x08, 0x9b, 0xaa, 0x19, 0x20, 0x08, 0x9b, 0xcc, 0x48, 0x20, 0x07, 0x9f,
    0xe4, 0x52, 0xe2, 0xd0, 0x0a, 0x2d, 0x63, 0xea, 0x0f, 0xe5, 0x4b, 0x00, 0x07, 0x2d, 0x63, 0xea,
    0x90, 0x04, 0x2d, 0x10, 0x06, 0x2d, 0x53, 0xea, 0x00, 0x07, 0x2d, 0x4b, 0xad, 0x00, 0x08, 0x2d,
    0x4b, 0xad, 0x20, 0x08, 0x2d, 0x84, 0xba, 0xd0, 0x04, 0x25, 0x43, 0x02, 0xbd, 0x08, 0xb7, 0x25,
    0xc7, 0x10, 0x0b, 0xb3, 0xe1, 0x18, 0x92, 0x63, 0xe1, 0x00, 0x07, 0xbc, 0xe1, 0x62, 0x10, 0x07,
    0xbc, 0xc4, 0x82, 0x00, 0x09, 0xe7, 0x67, 0x5f, 0xe1, 0x62, 0x10, 0x0b, 0xe7, 0x67, 0x5f, 0xe1,
    0x62, 0x54, 0x30, 0x08, 0xe7, 0x18, 0x95, 0x43, 0x00, 0x07, 0xe4, 0x69, 0x3f, 0xe3, 0x20, 0x04,
    0xe4, 0xdf, 0xe5, 0x00, 0x02, 0xe4, 0x70, 0x06, 0xe4, 0x43, 0xe3, 0x20, 0x06, 0xe4, 0x48, 0x91,
    0x00, 0x06, 0xe4, 0x48, 0x92, 0x00, 0x02, 0xe5, 0x80, 0x14, 0xed, 0x15, 0x27, 0x53, 0xa1, 0x8f,
    0xec, 0xaf, 0xe0, 0x65, 0x7f, 0xeb, 0xe2, 0x4f, 0xe0
};

static void magic_decode_send_skip(uint16_t offset, uint8_t skip_chars) {
    const uint8_t* data = magic_string_data + offset;
    uint8_t len = data[0];
    data++;

    uint8_t byteIndex = 0;
    bool highNibble = true;
    uint8_t charCount = 0;

    while (charCount < len) {
        uint8_t code;
        char c = '\0';

        if (highNibble) {
            code = (data[byteIndex] >> 4) & 0x0F;
            if (code >= 14) {
                code = data[byteIndex];
                byteIndex++;
                highNibble = true;
                if (code >= 0xE0 && code < 0xE0 + sizeof(magic_char_extended)) {
                    c = magic_char_extended[code - 0xE0];
                    if (skip_chars > 0) {
                        skip_chars--;
                    } else {
                        send_char(c);
                    }
                    charCount++;
                }
            } else {
                highNibble = false;
                if (code < sizeof(magic_char_4bit)) {
                    c = magic_char_4bit[code];
                    if (skip_chars > 0) {
                        skip_chars--;
                    } else {
                        send_char(c);
                    }
                    charCount++;
                }
            }
        } else {
            code = data[byteIndex] & 0x0F;
            byteIndex++;
            highNibble = true;
            if (code == 0x0F) {
                continue;
            }
            if (code < sizeof(magic_char_4bit)) {
                c = magic_char_4bit[code];
                if (skip_chars > 0) {
                    skip_chars--;
                } else {
                    send_char(c);
                }
                charCount++;
            }
        }
    }
}

void magic_decode_send(uint16_t offset) {
    magic_decode_send_skip(offset, 0);
}

static void magic_decode_send_cap(uint16_t offset, char suffix) {
    if (magic_capitalize_next) {
        add_oneshot_mods(MOD_BIT(KC_LSFT));
    }
    magic_decode_send(offset);
    if (suffix != '\0') {
        set_suffix_state(suffix);
    }
    magic_capitalize_next = false;
}

typedef struct {
    uint16_t current_offset;
    uint16_t next_offset;
    uint8_t common_prefix_length;
    char next_last_char;
} magic_cycle_entry_t;

static const magic_cycle_entry_t magic_cycle_entries[] = {
    { MAGIC_STRING_A_P_P_R_O_V_A_L, MAGIC_STRING_A_P_P_R_O_V_E, 6, 'e' },
    { MAGIC_STRING_A_P_P_R_O_V_E, MAGIC_STRING_A_P_P_R_O_V_A_L, 6, 'l' },
    { MAGIC_STRING_B_E_C_A_M_E, MAGIC_STRING_B_E_C_O_M_E, 3, 'e' },
    { MAGIC_STRING_B_E_C_O_M_E, MAGIC_STRING_B_E_C_A_M_E, 3, 'e' },
    { MAGIC_STRING_D_I_S_A_B_L_E, MAGIC_STRING_E_N_A_B_L_E, 0, 'e' },
    { MAGIC_STRING_E_N_A_B_L_E, MAGIC_STRING_D_I_S_A_B_L_E, 0, 'e' },
    { MAGIC_STRING_E_X_C_E_P_T, MAGIC_STRING_E_X_C_E_P_T_I_O_N, 6, 'n' },
    { MAGIC_STRING_E_X_C_E_P_T_I_O_N, MAGIC_STRING_E_X_C_E_P_T, 6, 't' },
    { MAGIC_STRING_E_X_P_L_A_I_N, MAGIC_STRING_E_X_P_L_A_N_A_T_I_O_N, 5, 'n' },
    { MAGIC_STRING_E_X_P_L_A_N_A_T_I_O_N, MAGIC_STRING_E_X_P_L_A_I_N, 5, 'n' },
    { MAGIC_STRING_G_E_N_E_R_A_T_E, MAGIC_STRING_G_E_N_E_R_A_T_I_O_N, 7, 'n' },
    { MAGIC_STRING_G_E_N_E_R_A_T_I_O_N, MAGIC_STRING_G_E_N_E_R_A_T_E, 7, 'e' },
    { MAGIC_STRING_I_M_P_L_E_M_E_N_T, MAGIC_STRING_I_M_P_L_E_M_E_N_T_A_T_I_O_N, 9, 'n' },
    { MAGIC_STRING_I_M_P_L_E_M_E_N_T_A_T_I_O_N, MAGIC_STRING_I_M_P_L_E_M_E_N_T, 9, 't' },
    { MAGIC_STRING_I_M_P_O_S_S_I_B_L_E, MAGIC_STRING_P_O_S_S_I_B_L_E, 0, 'e' },
    { MAGIC_STRING_I_N_S_T_R_U_M_E_N_T, MAGIC_STRING_I_N_S_T_R_U_M_E_N_T_A_T_I_O_N, 10, 'n' },
    { MAGIC_STRING_I_N_S_T_R_U_M_E_N_T_A_T_I_O_N, MAGIC_STRING_I_N_S_T_R_U_M_E_N_T, 10, 't' },
    { MAGIC_STRING_K_N_O_W, MAGIC_STRING_K_N_O_W_L_E_D_G_E, 4, 'e' },
    { MAGIC_STRING_K_N_O_W_L_E_D_G_E, MAGIC_STRING_K_N_O_W, 4, 'w' },
    { MAGIC_STRING_M_I_G_R_A_T_E, MAGIC_STRING_M_I_G_R_A_T_I_O_N, 6, 'n' },
    { MAGIC_STRING_M_I_G_R_A_T_I_O_N, MAGIC_STRING_M_I_G_R_A_T_E, 6, 'e' },
    { MAGIC_STRING_P_O_S_S_I_B_L_E, MAGIC_STRING_I_M_P_O_S_S_I_B_L_E, 0, 'e' },
    { MAGIC_STRING_R_E_S_O_L_U_T_I_O_N, MAGIC_STRING_R_E_S_O_L_V_E, 5, 'e' },
    { MAGIC_STRING_R_E_S_O_L_V_E, MAGIC_STRING_R_E_S_O_L_U_T_I_O_N, 5, 'n' },
    { MAGIC_STRING_S_E_P_A_R_A_T_E, MAGIC_STRING_S_E_P_A_R_A_T_I_O_N, 7, 'n' },
    { MAGIC_STRING_S_E_P_A_R_A_T_I_O_N, MAGIC_STRING_S_E_P_A_R_A_T_E, 7, 'e' },
    { MAGIC_STRING_T_H_A_N_K_Y_O_U, MAGIC_STRING_T_H_A_N_K_S, 5, 's' },
    { MAGIC_STRING_T_H_A_N_K_S, MAGIC_STRING_T_H_A_N_K_Y_O_U, 5, 'u' },
    { MAGIC_STRING_V_A_L_I_D_A_T_E, MAGIC_STRING_V_A_L_I_D_A_T_I_O_N, 7, 'n' },
    { MAGIC_STRING_V_A_L_I_D_A_T_I_O_N, MAGIC_STRING_V_A_L_I_D_A_T_E, 7, 'e' },
    { MAGIC_STRING_W_O_R_S_E, MAGIC_STRING_W_O_R_S_T, 4, 't' },
    { MAGIC_STRING_W_O_R_S_T, MAGIC_STRING_W_O_R_S_E, 4, 'e' }
};

static bool magic_cycle_lookup(uint16_t current_offset, uint16_t* next_offset, char* next_last_char) {
    int low = 0;
    int high = (int)(sizeof(magic_cycle_entries) / sizeof(magic_cycle_entries[0])) - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        uint16_t mid_offset = magic_cycle_entries[mid].current_offset;
        if (mid_offset == current_offset) {
            *next_offset = magic_cycle_entries[mid].next_offset;
            suffix_cycle_common_prefix_length = magic_cycle_entries[mid].common_prefix_length;
            *next_last_char = magic_cycle_entries[mid].next_last_char;
            return true;
        }
        if (mid_offset < current_offset) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}

#define MAGIC_CYCLE_NONE UINT16_MAX

static inline void set_suffix_word_state(char c, uint16_t cycle_offset, bool capitalize) {
    suffix_active = true;
    last_magic_char = c;
    suffix_cycle_offset = cycle_offset;
    suffix_cycle_capitalize = capitalize;
}

static void magic_decode_send_cap_cycle(uint16_t offset, char suffix, uint16_t cycle_offset) {
    bool capitalize = magic_capitalize_next;
    if (capitalize) {
        add_oneshot_mods(MOD_BIT(KC_LSFT));
    }
    magic_decode_send(offset);
    magic_remembered_keycode = KC_SPC;
    if (suffix != '\0') {
        set_suffix_word_state(suffix, cycle_offset, capitalize);
    }
    magic_capitalize_next = false;
}

static void magic_decode_send_suffix_cycle(uint16_t offset, char suffix, uint16_t cycle_offset) {
    bool capitalize = magic_capitalize_next;
    magic_decode_send(offset);
    magic_remembered_keycode = KC_SPC;
    set_suffix_word_state(suffix, cycle_offset, capitalize);
    magic_capitalize_next = false;
}

static void magic_replace_decode_send_cap_cycle(uint16_t offset, char suffix, uint16_t cycle_offset) {
    if (magic_context_key_emitted) {
        tap_code16(KC_BSPC);
    }
    magic_decode_send_cap_cycle(offset, suffix, cycle_offset);
}

static bool process_magic_cycle_next(void) {
    uint16_t next_offset = 0;
    char next_last_char = '\0';
    if (suffix_cycle_offset == MAGIC_CYCLE_NONE || !magic_cycle_lookup(suffix_cycle_offset, &next_offset, &next_last_char)) {
        clear_suffix_state();
        return false;
    }
    tap_code16(KC_BSPC);
    uint8_t current_length = magic_string_data[suffix_cycle_offset];
    uint8_t delete_count = current_length - 1 - suffix_cycle_common_prefix_length;
    for (uint8_t i = 0; i < delete_count; i++) {
        tap_code16(KC_BSPC);
    }
    if (suffix_cycle_capitalize && suffix_cycle_common_prefix_length == 0) {
        add_oneshot_mods(MOD_BIT(KC_LSFT));
    }
    magic_decode_send_skip(next_offset, suffix_cycle_common_prefix_length);
    set_suffix_word_state(next_last_char, next_offset, suffix_cycle_capitalize);
    return true;
}

// Two-variable tracking for real logical keys.
// prev_keycode = the prior resolved key press (what adaptives and magics check against).
// last_keycode = the most recent resolved key press (shifts to prev_keycode on the next keypress).
// Key presses first remember the real trigger keycode. If an adaptive fires,
// last_keycode is then overwritten with the emitted logical output so the next
// adaptive sees what was typed, not the physical substitute key.
// Combo components like KC_C from P=KC_C+KC_X are never recorded — only KC_P is.
static uint16_t prev_keycode = KC_NO;
static uint16_t last_keycode = KC_NO;
static uint16_t last_magic_trigger = KC_NO;
static uint16_t last_magic_repeat_keycode = KC_NO;
static uint16_t magic_repeat_keycode = KC_NO;

static inline uint16_t unshift_letter_keycode(uint16_t keycode) {
    if (keycode >= S(KC_A) && keycode <= S(KC_Z)) {
        return keycode - S(KC_A) + KC_A;
    }
    return keycode;
}

static inline uint16_t maybe_shift_letter_keycode(uint16_t keycode) {
    if (keycode >= KC_A && keycode <= KC_Z && ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)) {
        return S(keycode);
    }
    return keycode;
}

static uint16_t magic_prepare_last_keycode(uint16_t keycode) {
    uint16_t unshifted = unshift_letter_keycode(keycode);
    magic_capitalize_next = unshifted != keycode;
    return unshifted;
}

static bool repeat_last_magic_key(uint16_t trigger) {
    if (last_magic_trigger != trigger || last_magic_repeat_keycode == KC_NO) {
        return false;
    }
    tap_code16(last_magic_repeat_keycode);
    set_last_keycode(last_magic_repeat_keycode);
    return true;
}

static bool repeat_magic_key(uint16_t keycode) {
    switch (keycode) {
case MAGIC_A: return repeat_last_magic_key(MAGIC_A);
case MAGIC_B: return repeat_last_magic_key(MAGIC_B);
case MAGIC_C: return repeat_last_magic_key(MAGIC_C);
case MAGIC_D: return repeat_last_magic_key(MAGIC_D);
case MAGIC_E: return repeat_last_magic_key(MAGIC_E);
case MAGIC_F: return repeat_last_magic_key(MAGIC_F);
case MAGIC_G: return repeat_last_magic_key(MAGIC_G);
case MAGIC_H: return repeat_last_magic_key(MAGIC_H);
case MAGIC_I: return repeat_last_magic_key(MAGIC_I);
case MAGIC_J: return repeat_last_magic_key(MAGIC_J);
case MAGIC_K: return repeat_last_magic_key(MAGIC_K);
    default:
        return false;
    }
}

static void remember_real_keycode(uint16_t keycode) {
    keycode = maybe_shift_letter_keycode(keycode);
    prev_keycode = last_keycode;
    last_keycode = keycode;
    last_magic_trigger = KC_NO;
    last_magic_repeat_keycode = KC_NO;
}

// Multi-key substitutions (such as the eh combo) do not have one logical
// keycode that can safely be used as adaptive context for the next key.
static void clear_last_keycode(void) {
    last_keycode = KC_NO;
    last_magic_trigger = KC_NO;
    last_magic_repeat_keycode = KC_NO;
    set_last_keycode(KC_NO);
}

bool tap(uint16_t keycode) {
    tap_code16(keycode);
    set_last_keycode(keycode);
    return false;
}

bool tap_adaptive(uint16_t pressed_keycode, uint16_t output_keycode) {
    last_keycode = output_keycode;
    tap_code16(output_keycode);
    set_last_keycode(output_keycode);
    return false;
}

static inline void magic_replace_decode_send_cap(uint16_t offset, char suffix) {
    if (magic_context_key_emitted) {
        tap_code16(KC_BSPC);
    }
    magic_decode_send_cap(offset, suffix);
}

static void magic_tap_repeatable(uint16_t keycode) {
    tap_code16(keycode);
    magic_remembered_keycode = keycode;
    magic_repeat_keycode = keycode;
}

static inline void magic_replace_tap_repeatable(uint16_t keycode) {
    if (magic_context_key_emitted) {
        tap_code16(KC_BSPC);
    }
    magic_tap_repeatable(keycode);
}

static bool process_magic_suffix(uint16_t keycode) {
    switch (keycode) {
    case MAGIC_A:
        tap_code16(KC_BSPC);
        if (last_magic_char == 'e') {
            tap_code16(KC_D); tap_code16(KC_SPC);
        } else {
            tap_code16(KC_E); tap_code16(KC_D); tap_code16(KC_SPC);
        }
        last_magic_char = 'd';
        clear_suffix_cycle_state();
        return true;
    case MAGIC_B:
        tap_code16(KC_BSPC); tap_code16(KC_S); tap_code16(KC_SPC);
        last_magic_char = 's';
        clear_suffix_cycle_state();
        return true;
    case MAGIC_D:
        tap_code16(KC_BSPC); tap_n_t(); tap_code16(KC_SPC);
        last_magic_char = 't';
        clear_suffix_cycle_state();
        return true;
    case MAGIC_E:
        tap_code16(KC_BSPC); tap_code16(KC_QUES); tap_code16(KC_SPC);
        last_magic_char = '?';
        clear_suffix_cycle_state();
        return true;
    case MAGIC_G:
        tap_code16(KC_BSPC); tap_code16(KC_COMMA); tap_code16(KC_SPC);
        clear_suffix_state();
        return true;
    case MAGIC_H:
        return process_magic_cycle_next();
    case MAGIC_I:
        tap_code16(KC_BSPC); tap_code16(KC_SPC); tap_code16(KC_T); tap_code16(KC_H); tap_code16(KC_E); tap_code16(KC_SPC);
        clear_suffix_state();
        return true;
    case MAGIC_J:
        tap_code16(KC_BSPC); tap_code16(KC_DOT); tap_code16(KC_SPC);
        clear_suffix_state();
        return true;
    case MAGIC_K:
        tap_code16(KC_BSPC); tap_code16(KC_L); tap_code16(KC_Y); tap_code16(KC_SPC);
        last_magic_char = 'y';
        clear_suffix_cycle_state();
        return true;
    default:
        return false;
    }
}

static bool is_magic_keycode(uint16_t keycode) {
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
        case MAGIC_J:
        case MAGIC_K:
            return true;
    default:
        return false;
    }
}

static bool process_magic_key_with_context(uint16_t keycode, uint16_t context_keycode,
                                           bool allow_repeat, bool context_emitted) {
    magic_context_key_emitted = context_emitted;
    switch (keycode) {
        case MAGIC_A: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_A)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_A;
            magic_repeat_keycode = KC_NO;
            uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
            switch (magic_context_prepared) {
                case KC_B: magic_replace_decode_send_cap_cycle(MAGIC_STRING_D_I_S_A_B_L_E, 'e', MAGIC_STRING_D_I_S_A_B_L_E); /* emits "disable " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_L_L, '\0', MAGIC_CYCLE_NONE); /* emits "'ll " */ break;
                case KC_D: magic_tap_repeatable(KC_F); break;
                case KC_F: magic_replace_decode_send_cap_cycle(MAGIC_STRING_C_O_N_F_U_S_I_N_G, 'g', MAGIC_CYCLE_NONE); /* emits "confusing " */ break;
                case KC_G: magic_tap_repeatable(KC_F); break;
                case KC_K: magic_tap_repeatable(KC_Y); break;
                case KC_L: magic_tap_repeatable(KC_R); break;
                case KC_M: magic_tap_repeatable(KC_R); break;
                case KC_N: magic_tap_repeatable(KC_R); break;
                case KC_P: magic_tap_repeatable(KC_Y); break;
                case KC_R: magic_replace_decode_send_cap_cycle(MAGIC_STRING_M_I_G_R_A_T_E, 'e', MAGIC_STRING_M_I_G_R_A_T_E); /* emits "migrate " */ break;
                case KC_S: magic_tap_repeatable(KC_R); break;
                case KC_T: magic_tap_repeatable(KC_F); break;
                case KC_V: magic_decode_send_suffix_cycle(MAGIC_STRING_A_L_I_D_A_T_E, 'e', MAGIC_STRING_V_A_L_I_D_A_T_E); /* emits "alidate " -> "validate " */ break;
                case KC_W: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_L_W_A_Y_S, 's', MAGIC_CYCLE_NONE); /* emits "always " */ break;
                case KC_X: magic_tap_repeatable(KC_R); break;
            default:
                            if (context_keycode != KC_NO && !is_magic_keycode(context_keycode)) {
                                tap_code16(context_keycode);
                                magic_remembered_keycode = context_keycode;
                                magic_repeat_keycode = context_keycode;
                                break;
                            }
                            break;
            }
            break;
        }
        case MAGIC_B: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_B)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_B;
            magic_repeat_keycode = KC_NO;
            uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
            switch (magic_context_prepared) {
                case KC_B: magic_tap_repeatable(KC_H); break;
                case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_S, '\0', MAGIC_CYCLE_NONE); /* emits "'s " */ break;
                case KC_D: magic_tap_repeatable(KC_H); break;
                case KC_F: magic_tap_repeatable(KC_H); break;
                case KC_G: magic_tap_repeatable(KC_T); break;
                case KC_K: magic_tap_repeatable(KC_H); break;
                case KC_L: magic_tap_repeatable(KC_H); break;
                case KC_M: magic_tap_repeatable(KC_H); break;
                case KC_N: magic_tap_repeatable(KC_H); break;
                case KC_P: magic_decode_send(MAGIC_STRING_P_L); /* emits "pl" -> "ppl" */ magic_remembered_keycode = KC_L; break;
                case KC_R: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_D_D_R_E_S_S, 's', MAGIC_CYCLE_NONE); /* emits "address " */ break;
                case KC_S: magic_decode_send_suffix_cycle(MAGIC_STRING_O_M_E_O_N_E, 'e', MAGIC_CYCLE_NONE); /* emits "omeone " -> "someone " */ break;
                case KC_T: magic_decode_send_suffix_cycle(MAGIC_STRING_H_O_U_G_H, 'h', MAGIC_CYCLE_NONE); /* emits "hough " -> "though " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_V_E_R_Y_T_H_I_N_G, 'g', MAGIC_CYCLE_NONE); /* emits "everything " */ break;
                case KC_W: magic_decode_send_suffix_cycle(MAGIC_STRING_A_S_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "asn't " -> "wasn't " */ break;
                case KC_X: magic_tap_repeatable(KC_H); break;
            default:
                            break;
            }
            break;
        }
        case MAGIC_C: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_C)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_C;
            magic_repeat_keycode = KC_NO;
            uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
            switch (magic_context_prepared) {
                case KC_SPC: magic_replace_decode_send_cap(MAGIC_STRING_DOT, '\0'); /* emits ". " */ add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state(); magic_remembered_keycode = KC_SPC; break;
            default:
                            break;
            }
            break;
        }
        case MAGIC_D: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_D)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_D;
            magic_repeat_keycode = KC_NO;
            uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
            switch (magic_context_prepared) {
                case KC_B: magic_replace_decode_send_cap_cycle(MAGIC_STRING_P_O_S_S_I_B_L_E, 'e', MAGIC_STRING_P_O_S_S_I_B_L_E); /* emits "possible " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_N_APOSTROPHE_T, '\0', MAGIC_CYCLE_NONE); /* emits "n't " */ break;
                case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_O_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "on't " -> "don't " */ break;
                case KC_F: magic_replace_decode_send_cap_cycle(MAGIC_STRING_P_E_R_F_O_R_M_A_N_C_E, 'e', MAGIC_CYCLE_NONE); /* emits "performance " */ break;
                case KC_G: magic_replace_decode_send_cap_cycle(MAGIC_STRING_S_U_G_G_E_S_T, 't', MAGIC_CYCLE_NONE); /* emits "suggest " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(MAGIC_STRING_T_H_I_N_K, 'k', MAGIC_CYCLE_NONE); /* emits "think " */ break;
                case KC_L: magic_decode_send_suffix_cycle(MAGIC_STRING_A_N_G_U_A_G_E, 'e', MAGIC_CYCLE_NONE); /* emits "anguage " -> "language " */ break;
                case KC_M: magic_replace_decode_send_cap_cycle(MAGIC_STRING_I_M_P_L_E_M_E_N_T, 't', MAGIC_STRING_I_M_P_L_E_M_E_N_T); /* emits "implement " */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(MAGIC_STRING_O_N_L_Y, 'y', MAGIC_CYCLE_NONE); /* emits "only " */ break;
                case KC_P: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_P_P_L_Y, 'y', MAGIC_CYCLE_NONE); /* emits "apply " */ break;
                case KC_R: magic_replace_decode_send_cap_cycle(MAGIC_STRING_M_E_R_G_E, 'e', MAGIC_CYCLE_NONE); /* emits "merge " */ break;
                case KC_S: magic_decode_send_suffix_cycle(MAGIC_STRING_O_M_E_T_H_I_N_G, 'g', MAGIC_CYCLE_NONE); /* emits "omething " -> "something " */ break;
                case KC_T: magic_replace_decode_send_cap_cycle(MAGIC_STRING_J_U_S_T, 't', MAGIC_CYCLE_NONE); /* emits "just " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_I_M_P_R_O_V_E, 'e', MAGIC_CYCLE_NONE); /* emits "improve " */ break;
                case KC_W: magic_replace_decode_send_cap_cycle(MAGIC_STRING_K_N_E_W, 'w', MAGIC_CYCLE_NONE); /* emits "knew " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_C_E_P_T, 't', MAGIC_STRING_E_X_C_E_P_T); /* emits "except " */ break;
            default:
                            break;
            }
            break;
        }
        case MAGIC_E: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_E)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_E;
            magic_repeat_keycode = KC_NO;
            uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
            switch (magic_context_prepared) {
                case KC_B: magic_replace_decode_send_cap_cycle(MAGIC_STRING_O_B_S_E_R_V_A_B_I_L_I_T_Y, 'y', MAGIC_CYCLE_NONE); /* emits "observability " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_V_E, '\0', MAGIC_CYCLE_NONE); /* emits "'ve " */ break;
                case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_O_E_S, 's', MAGIC_CYCLE_NONE); /* emits "oes " -> "does " */ break;
                case KC_G: magic_replace_decode_send_cap_cycle(MAGIC_STRING_C_H_A_N_G_E, 'e', MAGIC_CYCLE_NONE); /* emits "change " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(MAGIC_STRING_Q_U_E_S_T_I_O_N, 'n', MAGIC_CYCLE_NONE); /* emits "question " */ break;
                case KC_L: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_L_R_E_A_D_Y, 'y', MAGIC_CYCLE_NONE); /* emits "already " */ break;
                case KC_M: magic_decode_send_suffix_cycle(MAGIC_STRING_U_L_T_I_P_L_E, 'e', MAGIC_CYCLE_NONE); /* emits "ultiple " -> "multiple " */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_N_Y_T_H_I_N_G, 'g', MAGIC_CYCLE_NONE); /* emits "anything " */ break;
                case KC_P: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_A_M_P_L_E, 'e', MAGIC_CYCLE_NONE); /* emits "example " */ break;
                case KC_R: magic_replace_decode_send_cap_cycle(MAGIC_STRING_P_R_O_B_A_B_L_Y, 'y', MAGIC_CYCLE_NONE); /* emits "probably " */ break;
                case KC_S: magic_decode_send_suffix_cycle(MAGIC_STRING_U_P_P_O_R_T, 't', MAGIC_CYCLE_NONE); /* emits "upport " -> "support " */ break;
                case KC_T: magic_decode_send_suffix_cycle(MAGIC_STRING_H_R_O_U_G_H, 'h', MAGIC_CYCLE_NONE); /* emits "hrough " -> "through " */ break;
                case KC_V: magic_decode_send_suffix_cycle(MAGIC_STRING_E_R_S_I_O_N, 'n', MAGIC_CYCLE_NONE); /* emits "ersion " -> "version " */ break;
                case KC_W: magic_replace_decode_send_cap_cycle(MAGIC_STRING_O_T_H_E_R_W_I_S_E, 'e', MAGIC_CYCLE_NONE); /* emits "otherwise " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_P_L_A_I_N, 'n', MAGIC_STRING_E_X_P_L_A_I_N); /* emits "explain " */ break;
            default:
                            break;
            }
            break;
        }
        case MAGIC_F: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_F)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_F;
            magic_repeat_keycode = KC_NO;
            uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
            switch (magic_context_prepared) {
                case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_D, '\0', MAGIC_CYCLE_NONE); /* emits "'d " */ break;
                case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_I_F_F_I_C_U_L_T_Y, 'y', MAGIC_CYCLE_NONE); /* emits "ifficulty " -> "difficulty " */ break;
                case KC_G: magic_decode_send_suffix_cycle(MAGIC_STRING_E_N_E_R_A_T_E, 'e', MAGIC_STRING_G_E_N_E_R_A_T_E); /* emits "enerate " -> "generate " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(MAGIC_STRING_T_H_A_N_K_S, 's', MAGIC_STRING_T_H_A_N_K_S); /* emits "thanks " */ break;
                case KC_L: magic_tap_repeatable(KC_B); break;
                case KC_M: magic_tap_repeatable(KC_V); break;
                case KC_N: magic_tap_repeatable(KC_P); break;
                case KC_P: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_P_L_I_C_I_T, 't', MAGIC_CYCLE_NONE); /* emits "explicit " */ break;
                case KC_R: magic_replace_decode_send_cap_cycle(MAGIC_STRING_I_M_P_O_R_T_A_N_T, 't', MAGIC_CYCLE_NONE); /* emits "important " */ break;
                case KC_S: magic_decode_send_suffix_cycle(MAGIC_STRING_I_M_I_L_A_R, 'r', MAGIC_CYCLE_NONE); /* emits "imilar " -> "similar " */ break;
                case KC_T: magic_tap_repeatable(KC_Z); break;
                case KC_W: magic_replace_decode_send_cap_cycle(MAGIC_STRING_S_W_I_T_C_H, 'h', MAGIC_CYCLE_NONE); /* emits "switch " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_C_L_U_D_E, 'e', MAGIC_CYCLE_NONE); /* emits "exclude " */ break;
            default:
                            break;
            }
            break;
        }
        case MAGIC_G: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_G)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_G;
            magic_repeat_keycode = KC_NO;
            uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
            switch (magic_context_prepared) {
        
            default:
                            break;
            }
            break;
        }
        case MAGIC_H: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_H)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_H;
            magic_repeat_keycode = KC_NO;
            uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
            switch (magic_context_prepared) {
                case KC_B: magic_decode_send_suffix_cycle(MAGIC_STRING_E_C_O_M_E, 'e', MAGIC_STRING_B_E_C_O_M_E); /* emits "ecome " -> "become " */ break;
                case KC_C: magic_tap_repeatable(KC_N); break;
                case KC_COMMA: magic_decode_send_cap_cycle(MAGIC_STRING_A_N_D, '\0', MAGIC_CYCLE_NONE); /* emits " and " */ break;
                case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_I_D_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "idn't " -> "didn't " */ break;
                case KC_ENT: magic_decode_send_cap_cycle(MAGIC_STRING_A_N_D_2, 'd', MAGIC_CYCLE_NONE); /* emits "and " */ break;
                case KC_F: magic_decode_send_suffix_cycle(MAGIC_STRING_O_C_U_S_E_D, 'd', MAGIC_CYCLE_NONE); /* emits "ocused " -> "focused " */ break;
                case KC_G: magic_decode_send_suffix_cycle(MAGIC_STRING_O_E_S, 's', MAGIC_CYCLE_NONE); /* emits "oes " -> "goes " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(MAGIC_STRING_U_P_D_A_T_E, 'e', MAGIC_CYCLE_NONE); /* emits "update " */ break;
                case KC_L: magic_tap_repeatable(KC_N); break;
                case KC_M: magic_replace_decode_send_cap_cycle(MAGIC_STRING_I_N_S_T_R_U_M_E_N_T, 't', MAGIC_STRING_I_N_S_T_R_U_M_E_N_T); /* emits "instrument " */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(MAGIC_STRING_U_N_D_E_R_S_T_A_N_D, 'd', MAGIC_CYCLE_NONE); /* emits "understand " */ break;
                case KC_P: magic_tap_repeatable(KC_N); break;
                case KC_R: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_P_P_R_O_V_A_L, 'l', MAGIC_STRING_A_P_P_R_O_V_A_L); /* emits "approval " */ break;
                case KC_S: magic_decode_send_suffix_cycle(MAGIC_STRING_E_P_A_R_A_T_E, 'e', MAGIC_STRING_S_E_P_A_R_A_T_E); /* emits "eparate " -> "separate " */ break;
                case KC_SPC: magic_decode_send_cap_cycle(MAGIC_STRING_A_N_D_2, 'd', MAGIC_CYCLE_NONE); /* emits "and " */ break;
                case KC_T: magic_tap_repeatable(KC_N); break;
                case KC_TAB: magic_decode_send_cap_cycle(MAGIC_STRING_A_N_D_2, 'd', MAGIC_CYCLE_NONE); /* emits "and " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_W_O_R_S_E, 'e', MAGIC_STRING_W_O_R_S_E); /* emits "worse " */ break;
                case KC_W: magic_decode_send_suffix_cycle(MAGIC_STRING_H_Y_2, 'y', MAGIC_CYCLE_NONE); /* emits "hy " -> "why " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_I_T, 't', MAGIC_CYCLE_NONE); /* emits "exit " */ break;
            default:
                            break;
            }
            break;
        }
        case MAGIC_I: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_I)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_I;
            magic_repeat_keycode = KC_NO;
            uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
            switch (magic_context_prepared) {
                case KC_B: magic_decode_send_suffix_cycle(MAGIC_STRING_E_C_A_U_S_E, 'e', MAGIC_CYCLE_NONE); /* emits "ecause " -> "because " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_R_E, '\0', MAGIC_CYCLE_NONE); /* emits "'re " */ break;
                case KC_COMMA: magic_decode_send_cap_cycle(MAGIC_STRING_B_U_T, '\0', MAGIC_CYCLE_NONE); /* emits " but " */ break;
                case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_O_E_S_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "oesn't " -> "doesn't " */ break;
                case KC_ENT: magic_decode_send_cap_cycle(MAGIC_STRING_T_H_E, 'e', MAGIC_CYCLE_NONE); /* emits "the " */ break;
                case KC_F: magic_decode_send_suffix_cycle(MAGIC_STRING_O_L_L_O_W_I_N_G, 'g', MAGIC_CYCLE_NONE); /* emits "ollowing " -> "following " */ break;
                case KC_G: magic_tap_repeatable(KC_K); break;
                case KC_K: magic_decode_send_suffix_cycle(MAGIC_STRING_N_O_W, 'w', MAGIC_STRING_K_N_O_W); /* emits "now " -> "know " */ break;
                case KC_L: magic_tap_repeatable(KC_M); break;
                case KC_M: magic_decode_send(MAGIC_STRING_E_N_T); /* emits "ent" -> "ment" */ magic_remembered_keycode = KC_T; break;
                case KC_N: magic_replace_decode_send_cap_cycle(MAGIC_STRING_W_O_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "won't " */ break;
                case KC_P: magic_tap_repeatable(KC_M); break;
                case KC_S: magic_decode_send(MAGIC_STRING_I_O_N); /* emits "ion" -> "sion" */ magic_remembered_keycode = KC_N; break;
                case KC_SPC: magic_decode_send_cap_cycle(MAGIC_STRING_T_H_E, 'e', MAGIC_CYCLE_NONE); /* emits "the " */ break;
                case KC_T: magic_decode_send(MAGIC_STRING_I_O_N); /* emits "ion" -> "tion" */ magic_remembered_keycode = KC_N; break;
                case KC_TAB: magic_decode_send_cap_cycle(MAGIC_STRING_T_H_E, 'e', MAGIC_CYCLE_NONE); /* emits "the " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_R_E_S_O_L_V_E, 'e', MAGIC_STRING_R_E_S_O_L_V_E); /* emits "resolve " */ break;
                case KC_W: magic_tap_repeatable(KC_S); break;
                case KC_X: magic_tap_repeatable(KC_W); break;
            default:
                            break;
            }
            break;
        }
        case MAGIC_J: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_J)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_J;
            magic_repeat_keycode = KC_NO;
            uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
            switch (magic_context_prepared) {
                case KC_B: magic_tap_repeatable(KC_D); break;
                case KC_C: magic_tap_repeatable(KC_D); break;
                case KC_D: magic_tap_repeatable(KC_C); break;
                case KC_F: magic_tap_repeatable(KC_D); break;
                case KC_G: magic_tap_repeatable(KC_D); break;
                case KC_K: magic_tap_repeatable(KC_X); break;
                case KC_L: magic_tap_repeatable(KC_C); break;
                case KC_M: magic_tap_repeatable(KC_L); break;
                case KC_N: magic_tap_repeatable(KC_X); break;
                case KC_P: magic_tap_repeatable(KC_D); break;
                case KC_R: magic_tap_repeatable(KC_X); break;
                case KC_S: magic_tap_repeatable(KC_D); break;
                case KC_T: magic_decode_send_suffix_cycle(MAGIC_STRING_H_O_U_G_H_T, 't', MAGIC_CYCLE_NONE); /* emits "hought " -> "thought " */ break;
                case KC_W: magic_tap_repeatable(KC_X); break;
            default:
                            break;
            }
            break;
        }
        case MAGIC_K: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_K)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_K;
            magic_repeat_keycode = KC_NO;
            uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
            switch (magic_context_prepared) {
        
            default:
                            break;
            }
            break;
        }
    default:
        return true;
    }
    magic_capitalize_next = false;
    last_magic_trigger = keycode;
    last_magic_repeat_keycode = magic_repeat_keycode;
    prev_keycode = last_keycode;
    last_keycode = magic_remembered_keycode;
    set_last_keycode(magic_remembered_keycode);
    return false;
}

bool process_record_generated(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Adaptive keys: runs after combo resolution in process_record_user,
        // so combo components are suppressed and prev_keycode reflects the
        // resolved combo keycode (e.g. KC_P not KC_C).
        uint16_t adaptive_prev_keycode = unshift_letter_keycode(prev_keycode);
        switch (keycode) {
            case KC_B:
                switch (adaptive_prev_keycode) {
                    case KC_L: return tap_adaptive(KC_B, KC_W);
                }
                break;
            case KC_C:
                switch (adaptive_prev_keycode) {
                    case KC_D: return tap_adaptive(KC_C, KC_V);
                }
                break;
            case KC_D:
                switch (adaptive_prev_keycode) {
                    case KC_B: return tap_adaptive(KC_D, KC_S);
                    case KC_C: return tap_adaptive(KC_D, KC_C);
                    case KC_F: return tap_adaptive(KC_D, KC_F);
                    case KC_G: return tap_adaptive(KC_D, KC_N);
                    case KC_P: return tap_adaptive(KC_D, KC_L);
                    case KC_S: return tap_adaptive(KC_D, KC_P);
                }
                break;
            case KC_E:
                switch (adaptive_prev_keycode) {
                    case KC_A: return tap_adaptive(KC_E, KC_U);
                }
                break;
            case KC_F:
                switch (adaptive_prev_keycode) {
                    case KC_D: return tap_adaptive(KC_F, KC_D);
                    case KC_G: return tap_adaptive(KC_F, KC_L);
                    case KC_T: return tap_adaptive(KC_F, KC_W);
                }
                break;
            case KC_H:
                switch (adaptive_prev_keycode) {
                    case KC_B: return tap_adaptive(KC_H, KC_B);
                    case KC_D: return tap_adaptive(KC_H, KC_G);
                    case KC_E: return tap_adaptive(KC_H, KC_E);
                    case KC_F: return tap_adaptive(KC_H, KC_S);
                    case KC_K: return tap_adaptive(KC_H, KC_N);
                    case KC_L: return tap_adaptive(KC_H, KC_P);
                    case KC_M: return tap_adaptive(KC_H, KC_M);
                    case KC_N: return tap_adaptive(KC_H, KC_N);
                    case KC_O: return tap_adaptive(KC_H, KC_O);
                    case KC_U: return tap_adaptive(KC_H, KC_A);
                    case KC_X: tap_code16(KC_P); return tap_adaptive(KC_H, KC_L);
                }
                break;
            case KC_N:
                switch (adaptive_prev_keycode) {
                    case KC_C: return tap_adaptive(KC_N, KC_K);
                    case KC_P: return tap_adaptive(KC_N, KC_P);
                    case KC_T: return tap_adaptive(KC_N, KC_T);
                }
                break;
            case KC_P:
                switch (adaptive_prev_keycode) {
                    case KC_N: return tap_adaptive(KC_P, KC_K);
                }
                break;
            case KC_R:
                switch (adaptive_prev_keycode) {
                    case KC_L: return tap_adaptive(KC_R, KC_L);
                    case KC_M: tap_code16(KC_P); return tap_adaptive(KC_R, KC_L);
                    case KC_N: return tap_adaptive(KC_R, KC_G);
                    case KC_S: return tap_adaptive(KC_R, KC_S);
                    case KC_X: return tap_adaptive(KC_R, KC_C);
                    case KC_Y: return tap_adaptive(KC_R, KC_I);
                }
                break;
            case KC_T:
                switch (adaptive_prev_keycode) {
                    case KC_G: return tap_adaptive(KC_T, KC_G);
                    case KC_M: return tap_adaptive(KC_T, KC_B);
                }
                break;
            case KC_U:
                switch (adaptive_prev_keycode) {
                    case KC_E: return tap_adaptive(KC_U, KC_O);
                }
                break;
            case KC_V:
                switch (adaptive_prev_keycode) {
                    case KC_M: return tap_adaptive(KC_V, KC_T);
                }
                break;
            case KC_W:
                switch (adaptive_prev_keycode) {
                    case KC_X: return tap_adaptive(KC_W, KC_P);
                }
                break;
            case KC_X:
                switch (adaptive_prev_keycode) {
                    case KC_N: return tap_adaptive(KC_X, KC_L);
                    case KC_R: return tap_adaptive(KC_X, KC_R);
                    case KC_W: return tap_adaptive(KC_X, KC_N);
                }
                break;
            case KC_Y:
                switch (adaptive_prev_keycode) {
                    case KC_K: return tap_adaptive(KC_Y, KC_T);
                    case KC_P: return tap_adaptive(KC_Y, KC_S);
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
            if (!process_magic_key_with_context(keycode, last_keycode, true, true)) {
                return false;
            }
            switch (keycode) {
            
                default:
                    break;
            }
        }
    }
    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    
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
        case MAGIC_J:
        case MAGIC_K:
            return false;
    }

    remember_real_keycode(keycode);
    return true;  // Other keys can be repeated.
}
