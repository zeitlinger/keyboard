/* THIS FILE WAS GENERATED!
 *
 * file is generated from https://github.com/zeitlinger/keyboard/blob/main/README.md
 */

int layer = _BASE;

static bool magic_capitalize_next = false;
static bool magic_context_key_emitted = true;

// Magic string decoder lookup tables
#define MAGIC_STRING_APOSTROPHE_D 10
#define MAGIC_STRING_APOSTROPHE_L_L 14
#define MAGIC_STRING_APOSTROPHE_R_E 18
#define MAGIC_STRING_APOSTROPHE_S 22
#define MAGIC_STRING_APOSTROPHE_V_E 25
#define MAGIC_STRING_A_C_K_G_R_O_U_N_D 51
#define MAGIC_STRING_A_D_D_R_E_S_S 60
#define MAGIC_STRING_A_L_I_D_A_T_E 67
#define MAGIC_STRING_A_L_R_E_A_D_Y 73
#define MAGIC_STRING_A_L_W_A_Y_S 80
#define MAGIC_STRING_A_N_D 0
#define MAGIC_STRING_A_N_D_2 86
#define MAGIC_STRING_A_N_G_U_A_G_E 90
#define MAGIC_STRING_A_N_O_T_H_E_R 95
#define MAGIC_STRING_A_N_Y_T_H_I_N_G 101
#define MAGIC_STRING_A_P_P_R_O_V_A_L 108
#define MAGIC_STRING_A_P_P_R_O_V_E 115
#define MAGIC_STRING_A_S_I_C_A_L_L_Y 121
#define MAGIC_STRING_A_S_N_APOSTROPHE_T 129
#define MAGIC_STRING_A_V_A_I_L_A_B_L_E 134
#define MAGIC_STRING_B_A_C_K_G_R_O_U_N_D 142
#define MAGIC_STRING_B_A_S_I_C_A_L_L_Y 152
#define MAGIC_STRING_B_E_C_A_U_S_E 161
#define MAGIC_STRING_B_E_C_O_M_E 168
#define MAGIC_STRING_B_E_F_O_R_E 174
#define MAGIC_STRING_B_U_T 5
#define MAGIC_STRING_C_H_A_N_G_E 180
#define MAGIC_STRING_C_O_M_M_E_N_T 186
#define MAGIC_STRING_C_O_N_F_L_I_C_T 192
#define MAGIC_STRING_C_O_N_F_U_S_I_N_G 199
#define MAGIC_STRING_DOT 29
#define MAGIC_STRING_D_D_R_E_S_S 206
#define MAGIC_STRING_D_I_D_N_APOSTROPHE_T 212
#define MAGIC_STRING_D_I_F_F_I_C_U_L_T_Y 219
#define MAGIC_STRING_D_I_S_A_B_L_E 230
#define MAGIC_STRING_D_O_E_S 237
#define MAGIC_STRING_D_O_E_S_N_APOSTROPHE_T 241
#define MAGIC_STRING_D_O_N_APOSTROPHE_T 247
#define MAGIC_STRING_E_C_A_U_S_E 252
#define MAGIC_STRING_E_C_O_M_E 258
#define MAGIC_STRING_E_F_O_R_E 263
#define MAGIC_STRING_E_L_A_B_O_R_A_T_E 268
#define MAGIC_STRING_E_L_A_B_O_R_A_T_I_O_N 275
#define MAGIC_STRING_E_N_A_B_L_E 283
#define MAGIC_STRING_E_N_E_R_A_L 289
#define MAGIC_STRING_E_N_E_R_A_T_E 294
#define MAGIC_STRING_E_N_T 299
#define MAGIC_STRING_E_O_P_L_E 302
#define MAGIC_STRING_E_P_A_R_A_T_E 306
#define MAGIC_STRING_E_R_S_I_O_N 311
#define MAGIC_STRING_E_V_E_R 316
#define MAGIC_STRING_E_V_E_R_Y_T_H_I_N_G 321
#define MAGIC_STRING_E_X_A_M_P_L_E 330
#define MAGIC_STRING_E_X_C_E_P_T 336
#define MAGIC_STRING_E_X_C_E_P_T_I_O_N 342
#define MAGIC_STRING_E_X_C_L_U_D_E 350
#define MAGIC_STRING_E_X_I_T 357
#define MAGIC_STRING_E_X_P_L_A_I_N 362
#define MAGIC_STRING_E_X_P_L_A_N_A_T_I_O_N 368
#define MAGIC_STRING_E_X_P_L_I_C_I_T 376
#define MAGIC_STRING_F_O_C_U_S_E_D 384
#define MAGIC_STRING_F_O_L_L_O_W_I_N_G 392
#define MAGIC_STRING_G_E_N_E_R_A_L 399
#define MAGIC_STRING_G_E_N_E_R_A_T_E 404
#define MAGIC_STRING_G_E_N_E_R_A_T_I_O_N 410
#define MAGIC_STRING_G_L_O_B_A_L 417
#define MAGIC_STRING_G_R_A_F_A_N_A 423
#define MAGIC_STRING_G_R_E_G_O_R 429
#define MAGIC_STRING_G_R_E_G_O_R_DOT_Z_E_I_T_L_I_N_G_E_R_U0040_G_R_A_F_A_N_A_DOT_C_O_M 434
#define MAGIC_STRING_G_R_E_G_O_R_U0040_Z_E_I_T_L_I_N_G_E_R_DOT_D_E 454
#define MAGIC_STRING_H_I_C_H 468
#define MAGIC_STRING_H_O_U_G_H 474
#define MAGIC_STRING_H_O_U_G_H_T 480
#define MAGIC_STRING_H_R_O_U_G_H 486
#define MAGIC_STRING_H_Y 492
#define MAGIC_STRING_I_APOSTROPHE_V_E 32
#define MAGIC_STRING_I_D_N_APOSTROPHE_T 496
#define MAGIC_STRING_I_F_F_I_C_U_L_T_Y 502
#define MAGIC_STRING_I_G_R_A_T_E 512
#define MAGIC_STRING_I_M_I_L_A_R 517
#define MAGIC_STRING_I_M_P_L 522
#define MAGIC_STRING_I_M_P_L_E_M_E_N_T 525
#define MAGIC_STRING_I_M_P_L_E_M_E_N_T_A_T_I_O_N 531
#define MAGIC_STRING_I_M_P_O_R_T_A_N_T 540
#define MAGIC_STRING_I_M_P_O_S_S_I_B_L_E 546
#define MAGIC_STRING_I_M_P_R_O_V_E 554
#define MAGIC_STRING_I_N_S_T_R_U_M_E_N_T 560
#define MAGIC_STRING_I_N_S_T_R_U_M_E_N_T_A_T_I_O_N 567
#define MAGIC_STRING_I_O_N 576
#define MAGIC_STRING_I_S_A_B_L_E 579
#define MAGIC_STRING_I_S_M_A_T_C_H 585
#define MAGIC_STRING_J_U_S_T 592
#define MAGIC_STRING_K_N_E_W 596
#define MAGIC_STRING_K_N_O_W 601
#define MAGIC_STRING_L_A_N_G_U_A_G_E 606
#define MAGIC_STRING_L_G_T_M 37
#define MAGIC_STRING_L_O_B_A_L 612
#define MAGIC_STRING_M_E_N_T 617
#define MAGIC_STRING_M_E_R_G_E_D 620
#define MAGIC_STRING_M_I_G_R_A_T_E 626
#define MAGIC_STRING_M_I_G_R_A_T_I_O_N 631
#define MAGIC_STRING_M_I_S_M_A_T_C_H 637
#define MAGIC_STRING_M_P_L 644
#define MAGIC_STRING_M_P_L_E_M_E_N_T 647
#define MAGIC_STRING_M_U_L_T_I_P_L_E 653
#define MAGIC_STRING_N_APOSTROPHE_T 659
#define MAGIC_STRING_N_APOSTROPHE_T_2 663
#define MAGIC_STRING_N_E_V_E_R 667
#define MAGIC_STRING_N_E_W 672
#define MAGIC_STRING_N_O_W 676
#define MAGIC_STRING_O_B_S_E_R_V_A_B_I_L_I_T_Y 680
#define MAGIC_STRING_O_B_S_O_L_E_T_E 692
#define MAGIC_STRING_O_C_U_S_E_D 699
#define MAGIC_STRING_O_E_S 706
#define MAGIC_STRING_O_E_S_N_APOSTROPHE_T 709
#define MAGIC_STRING_O_L_L_O_W_I_N_G 714
#define MAGIC_STRING_O_M_E_O_N_E 720
#define MAGIC_STRING_O_M_E_T_H_I_N_G 725
#define MAGIC_STRING_O_M_M_E_N_T 731
#define MAGIC_STRING_O_N_APOSTROPHE_T 736
#define MAGIC_STRING_O_N_L_Y 740
#define MAGIC_STRING_O_R_G_A_N_I_Z_A_T_I_O_N 745
#define MAGIC_STRING_O_R_G_A_N_I_Z_E 753
#define MAGIC_STRING_O_R_K_F_L_O_W 759
#define MAGIC_STRING_O_T_H_E_R_W_I_S_E 766
#define MAGIC_STRING_P_E_O_P_L_E 773
#define MAGIC_STRING_P_E_R_F_O_R_M_A_N_C_E 778
#define MAGIC_STRING_P_O_S_S_I_B_L_E 787
#define MAGIC_STRING_P_R_O_B_A_B_L_Y 794
#define MAGIC_STRING_P_R_O_D_U_C_T_I_O_N 803
#define MAGIC_STRING_P_R_O_M_E_T_H_E_U_S 43
#define MAGIC_STRING_Q_U 812
#define MAGIC_STRING_Q_U_E_S_T_I_O_N 815
#define MAGIC_STRING_R_E_S_O_L_U_T_I_O_N 821
#define MAGIC_STRING_R_E_S_O_L_V_E 828
#define MAGIC_STRING_R_O_B_A_B_L_Y 834
#define MAGIC_STRING_R_O_D_U_C_T_I_O_N 842
#define MAGIC_STRING_S_E_P_A_R_A_T_E 850
#define MAGIC_STRING_S_E_P_A_R_A_T_I_O_N 856
#define MAGIC_STRING_S_I_M_I_L_A_R 863
#define MAGIC_STRING_S_I_O_N 868
#define MAGIC_STRING_S_O_M_E_O_N_E 871
#define MAGIC_STRING_S_O_M_E_T_H_I_N_G 876
#define MAGIC_STRING_S_U_G_G_E_S_T 883
#define MAGIC_STRING_S_U_P_P_O_R_T 888
#define MAGIC_STRING_S_W_I_T_C_H 893
#define MAGIC_STRING_T_A_S_K 900
#define MAGIC_STRING_T_H_A_N_K_S 914
#define MAGIC_STRING_T_H_A_N_K_Y_O_U 905
#define MAGIC_STRING_T_H_E 920
#define MAGIC_STRING_T_H_I_N_K 924
#define MAGIC_STRING_T_H_O_U_G_H 930
#define MAGIC_STRING_T_H_O_U_G_H_T 937
#define MAGIC_STRING_T_H_R_O_U_G_H 944
#define MAGIC_STRING_T_I_O_N 951
#define MAGIC_STRING_U_L_T_I_P_L_E 954
#define MAGIC_STRING_U_N_D_E_R_S_T_A_N_D 959
#define MAGIC_STRING_U_P_D_A_T_E 967
#define MAGIC_STRING_U_P_P_O_R_T 972
#define MAGIC_STRING_V_A_L_I_D_A_T_E 977
#define MAGIC_STRING_V_A_L_I_D_A_T_I_O_N 984
#define MAGIC_STRING_V_E_R_S_I_O_N 992
#define MAGIC_STRING_W_A_S_N_APOSTROPHE_T 998
#define MAGIC_STRING_W_H_I_C_H 1004
#define MAGIC_STRING_W_H_Y 1011
#define MAGIC_STRING_W_I_T_H_O_U_T 1016
#define MAGIC_STRING_W_O_N_APOSTROPHE_T 1022
#define MAGIC_STRING_W_O_R_K_F_L_O_W 1027
#define MAGIC_STRING_W_O_R_S_E 1035
#define MAGIC_STRING_Z_E_I_T_L_I_N_G_E_R 1040
#define MAGIC_STRING_Z_E_I_T_L_I_N_G_E_R_U0040_G_M_A_I_L_DOT_C_O_M 1047

static const char magic_char_4bit[] = {
    ' ', 'e', 'o', 't', 'n', 'a', 'i', 'r', 'l', 's', 'g', 'm', 'u', 'p'
};

static const char magic_char_extended[] = {
    'h', 'c', 'd', 'b', 'w', '\'', 'f', 'y', 'v', 'k', 'x', 'z', '.', '@', 'q', 'G', 'I', 'L', 'M', 'P', 'T', 'j'
};

static const uint8_t magic_string_data[] = {
    0x05, 0x05, 0x4f, 0xe2, 0x00, 0x05, 0x0f, 0xe3, 0xc3, 0x00, 0x03, 0xe5, 0xe2, 0x00, 0x04, 0xe5,
    0x88, 0x00, 0x04, 0xe5, 0x71, 0x00, 0x03, 0xe5, 0x90, 0x04, 0xe5, 0xe8, 0x10, 0x02, 0xec, 0x00,
    0x05, 0xf0, 0xe5, 0xe8, 0x10, 0x05, 0xf1, 0xef, 0xf4, 0xf2, 0x00, 0x0b, 0xf3, 0x72, 0xb1, 0x3f,
    0xe0, 0x1c, 0x90, 0x0a, 0x5f, 0xe1, 0xe9, 0xa7, 0x2c, 0x4f, 0xe2, 0x00, 0x08, 0x5f, 0xe2, 0xe2,
    0x71, 0x99, 0x00, 0x08, 0x58, 0x6f, 0xe2, 0x53, 0x10, 0x08, 0x58, 0x71, 0x5f, 0xe2, 0xe7, 0x00,
    0x07, 0x58, 0xe4, 0x5f, 0xe7, 0x90, 0x04, 0x54, 0xe2, 0x00, 0x08, 0x54, 0xac, 0x5a, 0x10, 0x08,
    0x54, 0x23, 0xe0, 0x17, 0x00, 0x09, 0x54, 0xe7, 0x3f, 0xe0, 0x64, 0xa0, 0x09, 0x5d, 0xd7, 0x2f,
    0xe8, 0x58, 0x00, 0x08, 0x5d, 0xd7, 0x2f, 0xe8, 0x10, 0x09, 0x59, 0x6f, 0xe1, 0x58, 0x8f, 0xe7,
    0x00, 0x06, 0x59, 0x4f, 0xe5, 0x30, 0x0a, 0x5f, 0xe8, 0x56, 0x85, 0xe3, 0x81, 0x00, 0x0b, 0xe3,
    0x5f, 0xe1, 0xe9, 0xa7, 0x2c, 0x4f, 0xe2, 0x00, 0x0a, 0xe3, 0x59, 0x6f, 0xe1, 0x58, 0x8f, 0xe7,
    0x00, 0x08, 0xe3, 0x1f, 0xe1, 0x5c, 0x91, 0x00, 0x07, 0xe3, 0x1f, 0xe1, 0x2b, 0x10, 0x07, 0xe3,
    0x1f, 0xe6, 0x27, 0x10, 0x07, 0xe1, 0xe0, 0x54, 0xa1, 0x00, 0x08, 0xe1, 0x2b, 0xb1, 0x43, 0x00,
    0x09, 0xe1, 0x24, 0xe6, 0x86, 0xe1, 0x30, 0x0a, 0xe1, 0x24, 0xe6, 0xc9, 0x64, 0xa0, 0x07, 0xe2,
    0xe2, 0x71, 0x99, 0x00, 0x07, 0xe2, 0x6f, 0xe2, 0x4f, 0xe5, 0x30, 0x0b, 0xe2, 0x6f, 0xe6, 0xe6,
    0x6f, 0xe1, 0xc8, 0x3f, 0xe7, 0x00, 0x08, 0xe2, 0x69, 0x5f, 0xe3, 0x81, 0x00, 0x05, 0xe2, 0x21,
    0x90, 0x08, 0xe2, 0x21, 0x94, 0xe5, 0x30, 0x06, 0xe2, 0x24, 0xe5, 0x30, 0x07, 0x1f, 0xe1, 0x5c,
    0x91, 0x00, 0x06, 0x1f, 0xe1, 0x2b, 0x10, 0x06, 0x1f, 0xe6, 0x27, 0x10, 0x0a, 0x18, 0x5f, 0xe3,
    0x27, 0x53, 0x10, 0x0c, 0x18, 0x5f, 0xe3, 0x27, 0x53, 0x62, 0x40, 0x07, 0x14, 0x5f, 0xe3, 0x81,
    0x00, 0x07, 0x14, 0x17, 0x58, 0x00, 0x08, 0x14, 0x17, 0x53, 0x10, 0x03, 0x14, 0x30, 0x06, 0x12,
    0xd8, 0x10, 0x08, 0x1d, 0x57, 0x53, 0x10, 0x07, 0x17, 0x96, 0x24, 0x00, 0x05, 0x1f, 0xe8, 0x17,
    0x00, 0x0b, 0x1f, 0xe8, 0x17, 0xe7, 0x3f, 0xe0, 0x64, 0xa0, 0x08, 0x1f, 0xea, 0x5b, 0xd8, 0x10,
    0x07, 0x1f, 0xea, 0xe1, 0x1d, 0x30, 0x0a, 0x1f, 0xea, 0xe1, 0x1d, 0x36, 0x24, 0x00, 0x08, 0x1f,
    0xea, 0xe1, 0x8c, 0xe2, 0x10, 0x05, 0x1f, 0xea, 0x63, 0x00, 0x08, 0x1f, 0xea, 0xd8, 0x56, 0x40,
    0x0c, 0x1f, 0xea, 0xd8, 0x54, 0x53, 0x62, 0x40, 0x09, 0x1f, 0xea, 0xd8, 0x6f, 0xe1, 0x63, 0x00,
    0x08, 0xe6, 0x2f, 0xe1, 0xc9, 0x1f, 0xe2, 0x00, 0x0a, 0xe6, 0x28, 0x82, 0xe4, 0x64, 0xa0, 0x08,
    0xa1, 0x41, 0x75, 0x80, 0x09, 0xa1, 0x41, 0x75, 0x31, 0x00, 0x0b, 0xa1, 0x41, 0x75, 0x36, 0x24,
    0x00, 0x07, 0xa8, 0x2f, 0xe3, 0x58, 0x00, 0x08, 0xa7, 0x5f, 0xe6, 0x54, 0x50, 0x07, 0xa7, 0x1a,
    0x27, 0x00, 0x1d, 0xa7, 0x1a, 0x27, 0xec, 0xeb, 0x16, 0x38, 0x64, 0xa1, 0x7f, 0xed, 0xa7, 0x5f,
    0xe6, 0x54, 0x5f, 0xec, 0xe1, 0x2b, 0x14, 0xa7, 0x1a, 0x27, 0xed, 0xeb, 0x16, 0x38, 0x64, 0xa1,
    0x7f, 0xec, 0xe2, 0x10, 0x05, 0xe0, 0x6f, 0xe1, 0xe0, 0x00, 0x06, 0xe0, 0x2c, 0xaf, 0xe0, 0x00,
    0x07, 0xe0, 0x2c, 0xaf, 0xe0, 0x30, 0x07, 0xe0, 0x72, 0xca, 0xe0, 0x00, 0x03, 0xe0, 0xe7, 0x00,
    0x06, 0x6f, 0xe2, 0x4f, 0xe5, 0x30, 0x0a, 0x6f, 0xe6, 0xe6, 0x6f, 0xe1, 0xc8, 0x3f, 0xe7, 0x00,
    0x07, 0x6a, 0x75, 0x31, 0x00, 0x07, 0x6b, 0x68, 0x57, 0x00, 0x04, 0x6b, 0xd8, 0x0a, 0x6b, 0xd8,
    0x1b, 0x14, 0x30, 0x0f, 0x6b, 0xd8, 0x1b, 0x14, 0x35, 0x36, 0x24, 0x00, 0x0a, 0x6b, 0xd2, 0x73,
    0x54, 0x30, 0x0b, 0x6b, 0xd2, 0x99, 0x6f, 0xe3, 0x81, 0x00, 0x08, 0x6b, 0xd7, 0x2f, 0xe8, 0x10,
    0x0b, 0x64, 0x93, 0x7c, 0xb1, 0x43, 0x00, 0x10, 0x64, 0x93, 0x7c, 0xb1, 0x43, 0x53, 0x62, 0x40,
    0x03, 0x62, 0x40, 0x07, 0x69, 0x5f, 0xe3, 0x81, 0x00, 0x08, 0x69, 0xb5, 0x3f, 0xe1, 0xe0, 0x00,
    0x05, 0xf5, 0xc9, 0x30, 0x05, 0xe9, 0x41, 0xe4, 0x00, 0x05, 0xe9, 0x42, 0xe4, 0x00, 0x09, 0x85,
    0x4a, 0xc5, 0xa1, 0x00, 0x06, 0x82, 0xe3, 0x58, 0x00, 0x04, 0xb1, 0x43, 0x07, 0xb1, 0x7a, 0x1f,
    0xe2, 0x00, 0x08, 0xb6, 0xa7, 0x53, 0x10, 0x0a, 0xb6, 0xa7, 0x53, 0x62, 0x40, 0x09, 0xb6, 0x9b,
    0x53, 0xe1, 0xe0, 0x00, 0x03, 0xbd, 0x80, 0x09, 0xbd, 0x81, 0xb1, 0x43, 0x00, 0x09, 0xbc, 0x83,
    0x6d, 0x81, 0x00, 0x03, 0x4f, 0xe5, 0x30, 0x04, 0x4f, 0xe5, 0x30, 0x06, 0x41, 0xe8, 0x17, 0x00,
    0x04, 0x41, 0xe4, 0x00, 0x04, 0x42, 0xe4, 0x00, 0x0e, 0x2f, 0xe3, 0x91, 0x7f, 0xe8, 0x5f, 0xe3,
    0x68, 0x63, 0xe7, 0x00, 0x09, 0x2f, 0xe3, 0x92, 0x81, 0x31, 0x00, 0x07, 0x2f, 0xe1, 0xc9, 0x1f,
    0xe2, 0x00, 0x04, 0x21, 0x90, 0x07, 0x21, 0x94, 0xe5, 0x30, 0x09, 0x28, 0x82, 0xe4, 0x64, 0xa0,
    0x07, 0x2b, 0x12, 0x41, 0x00, 0x09, 0x2b, 0x13, 0xe0, 0x64, 0xa0, 0x07, 0x2b, 0xb1, 0x43, 0x00,
    0x05, 0x24, 0xe5, 0x30, 0x05, 0x24, 0x8f, 0xe7, 0x00, 0x0d, 0x27, 0xa5, 0x46, 0xeb, 0x53, 0x62,
    0x40, 0x09, 0x27, 0xa5, 0x46, 0xeb, 0x10, 0x08, 0x27, 0xe9, 0xe6, 0x82, 0xe4, 0x00, 0x0a, 0x23,
    0xe0, 0x17, 0xe4, 0x69, 0x10, 0x07, 0xd1, 0x2d, 0x81, 0x00, 0x0c, 0xd1, 0x7f, 0xe6, 0x27, 0xb5,
    0x4f, 0xe1, 0x10, 0x09, 0xd2, 0x99, 0x6f, 0xe3, 0x81, 0x00, 0x09, 0xd7, 0x2f, 0xe3, 0x5f, 0xe3,
    0x8f, 0xe7, 0x00, 0x0b, 0xd7, 0x2f, 0xe2, 0xcf, 0xe1, 0x36, 0x24, 0x00, 0x02, 0xee, 0xc0, 0x09,
    0xee, 0xc1, 0x93, 0x62, 0x40, 0x0b, 0x71, 0x92, 0x8c, 0x36, 0x24, 0x00, 0x08, 0x71, 0x92, 0x8f,
    0xe8, 0x10, 0x08, 0x72, 0xe3, 0x5f, 0xe3, 0x8f, 0xe7, 0x00, 0x0a, 0x72, 0xe2, 0xcf, 0xe1, 0x36,
    0x24, 0x00, 0x09, 0x91, 0xd5, 0x75, 0x31, 0x00, 0x0b, 0x91, 0xd5, 0x75, 0x36, 0x24, 0x00, 0x08,
    0x96, 0xb6, 0x85, 0x70, 0x04, 0x96, 0x24, 0x08, 0x92, 0xb1, 0x24, 0x10, 0x0a, 0x92, 0xb1, 0x3f,
    0xe0, 0x64, 0xa0, 0x08, 0x9c, 0xaa, 0x19, 0x30, 0x08, 0x9c, 0xdd, 0x27, 0x30, 0x07, 0x9f, 0xe4,
    0x63, 0xe1, 0xe0, 0x00, 0x05, 0x35, 0x9f, 0xe9, 0x00, 0x0a, 0x3f, 0xe0, 0x54, 0xe9, 0x0f, 0xe7,
    0x2c, 0x00, 0x07, 0x3f, 0xe0, 0x54, 0xe9, 0x90, 0x04, 0x3f, 0xe0, 0x10, 0x06, 0x3f, 0xe0, 0x64,
    0xe9, 0x00, 0x07, 0x3f, 0xe0, 0x2c, 0xaf, 0xe0, 0x00, 0x08, 0x3f, 0xe0, 0x2c, 0xaf, 0xe0, 0x30,
    0x08, 0x3f, 0xe0, 0x72, 0xca, 0xe0, 0x00, 0x04, 0x36, 0x24, 0x08, 0xc8, 0x36, 0xd8, 0x10, 0x0b,
    0xc4, 0xe2, 0x17, 0x93, 0x54, 0xe2, 0x00, 0x07, 0xcd, 0xe2, 0x53, 0x10, 0x07, 0xcd, 0xd2, 0x73,
    0x00, 0x09, 0xe8, 0x58, 0x6f, 0xe2, 0x53, 0x10, 0x0b, 0xe8, 0x58, 0x6f, 0xe2, 0x53, 0x62, 0x40,
    0x08, 0xe8, 0x17, 0x96, 0x24, 0x00, 0x07, 0xe4, 0x59, 0x4f, 0xe5, 0x30, 0x06, 0xe4, 0xe0, 0x6f,
    0xe1, 0xe0, 0x00, 0x04, 0xe4, 0xe0, 0xe7, 0x00, 0x08, 0xe4, 0x63, 0xe0, 0x2c, 0x30, 0x06, 0xe4,
    0x24, 0xe5, 0x30, 0x09, 0xe4, 0x27, 0xe9, 0xe6, 0x82, 0xe4, 0x00, 0x06, 0xe4, 0x27, 0x91, 0x00,
    0x0b, 0xeb, 0x16, 0x38, 0x64, 0xa1, 0x70, 0x14, 0xeb, 0x16, 0x38, 0x64, 0xa1, 0x7f, 0xed, 0xab,
    0x56, 0x8f, 0xec, 0xe1, 0x2b
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

static void magic_decode_send(uint16_t offset) {
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
    { MAGIC_STRING_D_I_S_A_B_L_E, MAGIC_STRING_E_N_A_B_L_E, 0, 'e' },
    { MAGIC_STRING_E_L_A_B_O_R_A_T_E, MAGIC_STRING_E_L_A_B_O_R_A_T_I_O_N, 8, 'n' },
    { MAGIC_STRING_E_L_A_B_O_R_A_T_I_O_N, MAGIC_STRING_E_L_A_B_O_R_A_T_E, 8, 'e' },
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
    { MAGIC_STRING_M_I_G_R_A_T_E, MAGIC_STRING_M_I_G_R_A_T_I_O_N, 6, 'n' },
    { MAGIC_STRING_M_I_G_R_A_T_I_O_N, MAGIC_STRING_M_I_G_R_A_T_E, 6, 'e' },
    { MAGIC_STRING_O_R_G_A_N_I_Z_A_T_I_O_N, MAGIC_STRING_O_R_G_A_N_I_Z_E, 7, 'e' },
    { MAGIC_STRING_O_R_G_A_N_I_Z_E, MAGIC_STRING_O_R_G_A_N_I_Z_A_T_I_O_N, 7, 'n' },
    { MAGIC_STRING_P_O_S_S_I_B_L_E, MAGIC_STRING_I_M_P_O_S_S_I_B_L_E, 0, 'e' },
    { MAGIC_STRING_R_E_S_O_L_U_T_I_O_N, MAGIC_STRING_R_E_S_O_L_V_E, 5, 'e' },
    { MAGIC_STRING_R_E_S_O_L_V_E, MAGIC_STRING_R_E_S_O_L_U_T_I_O_N, 5, 'n' },
    { MAGIC_STRING_S_E_P_A_R_A_T_E, MAGIC_STRING_S_E_P_A_R_A_T_I_O_N, 7, 'n' },
    { MAGIC_STRING_S_E_P_A_R_A_T_I_O_N, MAGIC_STRING_S_E_P_A_R_A_T_E, 7, 'e' },
    { MAGIC_STRING_T_H_A_N_K_Y_O_U, MAGIC_STRING_T_H_A_N_K_S, 5, 's' },
    { MAGIC_STRING_T_H_A_N_K_S, MAGIC_STRING_T_H_A_N_K_Y_O_U, 5, 'u' },
    { MAGIC_STRING_V_A_L_I_D_A_T_E, MAGIC_STRING_V_A_L_I_D_A_T_I_O_N, 7, 'n' },
    { MAGIC_STRING_V_A_L_I_D_A_T_I_O_N, MAGIC_STRING_V_A_L_I_D_A_T_E, 7, 'e' }
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
    if (suffix != '\0') {
        set_suffix_word_state(suffix, cycle_offset, capitalize);
    }
    magic_capitalize_next = false;
}

static void magic_decode_send_suffix_cycle(uint16_t offset, char suffix, uint16_t cycle_offset) {
    bool capitalize = magic_capitalize_next;
    magic_decode_send(offset);
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
// Updated from the real trigger keycode, not the emitted adaptive/magic output,
// so context-sensitive logic can see through substitutions.
// Combo components like KC_C from P=KC_C+KC_X are never recorded — only KC_P is.
static uint16_t prev_keycode = KC_NO;
static uint16_t last_keycode = KC_NO;
static uint16_t last_keycode_timer = 0;
static uint16_t last_magic_trigger = KC_NO;
static uint16_t last_magic_repeat_keycode = KC_NO;
static uint16_t magic_remembered_keycode = KC_NO;
static uint16_t magic_repeat_keycode = KC_NO;

static inline uint16_t unshift_letter_keycode(uint16_t keycode) {
    if (keycode >= S(KC_A) && keycode <= S(KC_Z)) {
        return keycode - S(KC_A) + KC_A;
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
    if (last_magic_repeat_keycode >= SAFE_RANGE) {
        last_magic_repeat_keycode = KC_NO;
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
    prev_keycode = last_keycode;
    last_keycode = keycode;
    last_keycode_timer = timer_read();
    last_magic_trigger = KC_NO;
    last_magic_repeat_keycode = KC_NO;
}

bool tap(uint16_t keycode) {
    tap_code16(keycode);
    set_last_keycode(keycode);
    return false;
}

bool tap_adaptive(uint16_t pressed_keycode, uint16_t output_keycode) {
    remember_real_keycode(pressed_keycode);
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
        tap_code16(KC_BSPC); tap_code16(KC_L); tap_code16(KC_Y); tap_code16(KC_SPC);
        last_magic_char = 'y';
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
        tap_code16(KC_BSPC); tap_code16(KC_S); tap_code16(KC_SPC);
        last_magic_char = 's';
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

static uint32_t magic_context_bit(uint16_t keycode) {
    switch (keycode) {
case KC_A: return UINT32_C(1) << 0;
case KC_B: return UINT32_C(1) << 1;
case KC_C: return UINT32_C(1) << 2;
case KC_COMMA: return UINT32_C(1) << 3;
case KC_D: return UINT32_C(1) << 4;
case KC_E: return UINT32_C(1) << 5;
case KC_ENT: return UINT32_C(1) << 6;
case KC_F: return UINT32_C(1) << 7;
case KC_G: return UINT32_C(1) << 8;
case KC_H: return UINT32_C(1) << 9;
case KC_I: return UINT32_C(1) << 10;
case KC_K: return UINT32_C(1) << 11;
case KC_L: return UINT32_C(1) << 12;
case KC_M: return UINT32_C(1) << 13;
case KC_N: return UINT32_C(1) << 14;
case KC_O: return UINT32_C(1) << 15;
case KC_P: return UINT32_C(1) << 16;
case KC_R: return UINT32_C(1) << 17;
case KC_S: return UINT32_C(1) << 18;
case KC_SPC: return UINT32_C(1) << 19;
case KC_T: return UINT32_C(1) << 20;
case KC_TAB: return UINT32_C(1) << 21;
case KC_U: return UINT32_C(1) << 22;
case KC_V: return UINT32_C(1) << 23;
case KC_W: return UINT32_C(1) << 24;
case KC_X: return UINT32_C(1) << 25;
case KC_Y: return UINT32_C(1) << 26;
    default:
        return 0;
    }
}

static bool has_magic_key_with_context(uint16_t keycode, uint16_t context_keycode) {
    uint32_t context_bit = magic_context_bit(unshift_letter_keycode(context_keycode));
    if (context_bit == 0) {
        return false;
    }
    switch (keycode) {
case MAGIC_A: return (UINT32_C(0x1977996) & context_bit) != 0;
case MAGIC_B: return (UINT32_C(0x3977996) & context_bit) != 0;
case MAGIC_C: return (UINT32_C(0x4088421) & context_bit) != 0;
case MAGIC_D: return (UINT32_C(0x3977996) & context_bit) != 0;
case MAGIC_E: return (UINT32_C(0x3977996) & context_bit) != 0;
case MAGIC_F: return (UINT32_C(0x3177914) & context_bit) != 0;
case MAGIC_G: return (UINT32_C(0x44a8621) & context_bit) != 0;
case MAGIC_H: return (UINT32_C(0x3bf7dff) & context_bit) != 0;
case MAGIC_I: return (UINT32_C(0x3bf7ddf) & context_bit) != 0;
case MAGIC_J: return (UINT32_C(0x3977d97) & context_bit) != 0;
case MAGIC_K: return (UINT32_C(0x3977916) & context_bit) != 0;
    default:
        return false;
    }
}

static bool has_reverse_magic_key_with_context(uint16_t keycode, uint16_t context_keycode) {
    uint32_t context_bit = magic_context_bit(unshift_letter_keycode(context_keycode));
    if (context_bit == 0) {
        return false;
    }
    switch (keycode) {
case MAGIC_A: return (UINT32_C(0x1020080) & context_bit) != 0;
case MAGIC_B: return (UINT32_C(0x820884) & context_bit) != 0;
case MAGIC_C: return (UINT32_C(0x80000) & context_bit) != 0;
case MAGIC_D: return (UINT32_C(0x2960984) & context_bit) != 0;
case MAGIC_E: return (UINT32_C(0x3025982) & context_bit) != 0;
case MAGIC_F: return (UINT32_C(0x3115804) & context_bit) != 0;
case MAGIC_G: return (UINT32_C(0x40a0200) & context_bit) != 0;
case MAGIC_H: return (UINT32_C(0x2827c23) & context_bit) != 0;
case MAGIC_I: return (UINT32_C(0x824405) & context_bit) != 0;
case MAGIC_J: return (UINT32_C(0x920405) & context_bit) != 0;
case MAGIC_K: return (UINT32_C(0x2830104) & context_bit) != 0;
    default:
        return false;
    }
}

static uint16_t magic_combo_component_bit(uint16_t keycode) {
    switch (keycode) {
case DEAD1: return UINT16_C(1) << 0;
case KC_A: return UINT16_C(1) << 1;
case KC_E: return UINT16_C(1) << 2;
case KC_ESC: return UINT16_C(1) << 3;
case KC_H: return UINT16_C(1) << 4;
case KC_I: return UINT16_C(1) << 5;
case KC_O: return UINT16_C(1) << 6;
case KC_S: return UINT16_C(1) << 7;
case KC_U: return UINT16_C(1) << 8;
case KC_Y: return UINT16_C(1) << 9;
case MAGIC_A: return UINT16_C(1) << 10;
case MAGIC_B: return UINT16_C(1) << 11;
case MO(_LEFT): return UINT16_C(1) << 12;
case MO(_RIGHT): return UINT16_C(1) << 13;
    default:
        return 0;
    }
}

static bool is_magic_combo_component_for(uint16_t keycode, uint16_t component_keycode) {
    uint16_t component_bit = magic_combo_component_bit(component_keycode);
    if (component_bit == 0) {
        return false;
    }
    switch (keycode) {
case MAGIC_A: return (UINT16_C(0x0) & component_bit) != 0;
case MAGIC_B: return (UINT16_C(0x0) & component_bit) != 0;
case MAGIC_C: return (UINT16_C(0x88) & component_bit) != 0;
case MAGIC_D: return (UINT16_C(0x404) & component_bit) != 0;
case MAGIC_E: return (UINT16_C(0x820) & component_bit) != 0;
case MAGIC_F: return (UINT16_C(0x11) & component_bit) != 0;
case MAGIC_G: return (UINT16_C(0x2080) & component_bit) != 0;
case MAGIC_H: return (UINT16_C(0x102) & component_bit) != 0;
case MAGIC_I: return (UINT16_C(0x44) & component_bit) != 0;
case MAGIC_J: return (UINT16_C(0x220) & component_bit) != 0;
case MAGIC_K: return (UINT16_C(0x1010) & component_bit) != 0;
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
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_decode_send_suffix_cycle(MAGIC_STRING_A_C_K_G_R_O_U_N_D, 'd', MAGIC_CYCLE_NONE); /* emits "ackground " -> "background " */ break;
                case KC_C: magic_tap_repeatable(KC_N); break;
                case KC_D: magic_tap_repeatable(KC_C); break;
                case KC_F: magic_replace_decode_send_cap_cycle(MAGIC_STRING_C_O_N_F_U_S_I_N_G, 'g', MAGIC_CYCLE_NONE); /* emits "confusing " */ break;
                case KC_G: magic_decode_send_suffix_cycle(MAGIC_STRING_L_O_B_A_L, 'l', MAGIC_CYCLE_NONE); /* emits "lobal " -> "global " */ break;
                case KC_K: magic_tap_repeatable(KC_R); break;
                case KC_L: magic_tap_repeatable(KC_M); break;
                case KC_M: magic_tap_repeatable(KC_R); break;
                case KC_N: magic_tap_repeatable(KC_R); break;
                case KC_P: magic_tap_repeatable(KC_Y); break;
                case KC_R: magic_replace_tap_repeatable(KC_DQUO); break;
                case KC_S: magic_decode_send_suffix_cycle(MAGIC_STRING_O_M_E_O_N_E, 'e', MAGIC_CYCLE_NONE); /* emits "omeone " -> "someone " */ break;
                case KC_T: magic_tap_repeatable(KC_N); break;
                case KC_V: magic_decode_send_suffix_cycle(MAGIC_STRING_A_L_I_D_A_T_E, 'e', MAGIC_STRING_V_A_L_I_D_A_T_E); /* emits "alidate " -> "validate " */ break;
                case KC_W: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_L_W_A_Y_S, 's', MAGIC_CYCLE_NONE); /* emits "always " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_A;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_B: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_B)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_B;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_decode_send_suffix_cycle(MAGIC_STRING_A_S_I_C_A_L_L_Y, 'y', MAGIC_CYCLE_NONE); /* emits "asically " -> "basically " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_L_L, '\0', MAGIC_CYCLE_NONE); /* emits "'ll " */ break;
                case KC_D: magic_tap_repeatable(KC_H); break;
                case KC_F: magic_replace_decode_send_cap_cycle(MAGIC_STRING_C_O_N_F_L_I_C_T, 't', MAGIC_CYCLE_NONE); /* emits "conflict " */ break;
                case KC_G: magic_tap_repeatable(KC_F); break;
                case KC_K: magic_replace_decode_send_cap_cycle(MAGIC_STRING_Q_U_E_S_T_I_O_N, 'n', MAGIC_CYCLE_NONE); /* emits "question " */ break;
                case KC_L: magic_tap_repeatable(KC_H); break;
                case KC_M: magic_tap_repeatable(KC_H); break;
                case KC_N: magic_tap_repeatable(KC_H); break;
                case KC_P: magic_tap_repeatable(KC_M); break;
                case KC_R: magic_replace_tap_repeatable(KC_Q); break;
                case KC_S: magic_tap_repeatable(KC_R); break;
                case KC_T: magic_tap_repeatable(KC_F); break;
                case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_V_E_R_Y_T_H_I_N_G, 'g', MAGIC_CYCLE_NONE); /* emits "everything " */ break;
                case KC_W: magic_decode_send_suffix_cycle(MAGIC_STRING_A_S_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "asn't " -> "wasn't " */ break;
                case KC_X: magic_tap_repeatable(KC_W); break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_B;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_C: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_C)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_C;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_A: magic_decode_send_suffix_cycle(MAGIC_STRING_D_D_R_E_S_S, 's', MAGIC_CYCLE_NONE); /* emits "ddress " -> "address " */ break;
                case KC_E: magic_tap_repeatable(KC_U); break;
                case KC_I: magic_decode_send_suffix_cycle(MAGIC_STRING_M_P_L_E_M_E_N_T, 't', MAGIC_STRING_I_M_P_L_E_M_E_N_T); /* emits "mplement " -> "implement " */ break;
                case KC_O: magic_tap_repeatable(KC_E); break;
                case KC_SPC: magic_replace_decode_send_cap(MAGIC_STRING_DOT, '\0'); /* emits ". " */ add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state(); break;
                case KC_Y: magic_tap_repeatable(KC_R); break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_C;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_D: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_D)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_D;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_decode_send_suffix_cycle(MAGIC_STRING_E_C_O_M_E, 'e', MAGIC_CYCLE_NONE); /* emits "ecome " -> "become " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_N_APOSTROPHE_T_2, '\0', MAGIC_CYCLE_NONE); /* emits "n't " */ break;
                case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_O_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "on't " -> "don't " */ break;
                case KC_F: magic_replace_decode_send_cap_cycle(MAGIC_STRING_P_E_R_F_O_R_M_A_N_C_E, 'e', MAGIC_CYCLE_NONE); /* emits "performance " */ break;
                case KC_G: magic_replace_decode_send_cap_cycle(MAGIC_STRING_O_R_G_A_N_I_Z_E, 'e', MAGIC_STRING_O_R_G_A_N_I_Z_E); /* emits "organize " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(MAGIC_STRING_T_H_I_N_K, 'k', MAGIC_CYCLE_NONE); /* emits "think " */ break;
                case KC_L: magic_decode_send_suffix_cycle(MAGIC_STRING_A_N_G_U_A_G_E, 'e', MAGIC_CYCLE_NONE); /* emits "anguage " -> "language " */ break;
                case KC_M: magic_decode_send_suffix_cycle(MAGIC_STRING_I_G_R_A_T_E, 'e', MAGIC_STRING_M_I_G_R_A_T_E); /* emits "igrate " -> "migrate " */ break;
                case KC_N: magic_decode_send_suffix_cycle(MAGIC_STRING_E_V_E_R, 'r', MAGIC_CYCLE_NONE); /* emits "ever " -> "never " */ break;
                case KC_P: magic_decode_send_suffix_cycle(MAGIC_STRING_E_O_P_L_E, 'e', MAGIC_CYCLE_NONE); /* emits "eople " -> "people " */ break;
                case KC_R: magic_replace_decode_send_cap_cycle(MAGIC_STRING_N_APOSTROPHE_T, '\0', MAGIC_CYCLE_NONE); /* emits "n't" */ break;
                case KC_S: magic_replace_decode_send_cap_cycle(MAGIC_STRING_P_O_S_S_I_B_L_E, 'e', MAGIC_STRING_P_O_S_S_I_B_L_E); /* emits "possible " */ break;
                case KC_T: magic_replace_decode_send_cap_cycle(MAGIC_STRING_J_U_S_T, 't', MAGIC_CYCLE_NONE); /* emits "just " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_I_M_P_R_O_V_E, 'e', MAGIC_CYCLE_NONE); /* emits "improve " */ break;
                case KC_W: magic_decode_send_suffix_cycle(MAGIC_STRING_O_R_K_F_L_O_W, 'w', MAGIC_CYCLE_NONE); /* emits "orkflow " -> "workflow " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_C_E_P_T, 't', MAGIC_STRING_E_X_C_E_P_T); /* emits "except " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_D;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_E: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_E)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_E;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_replace_decode_send_cap_cycle(MAGIC_STRING_O_B_S_E_R_V_A_B_I_L_I_T_Y, 'y', MAGIC_CYCLE_NONE); /* emits "observability " */ break;
                case KC_C: magic_tap_repeatable(KC_D); break;
                case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_I_S_A_B_L_E, 'e', MAGIC_STRING_D_I_S_A_B_L_E); /* emits "isable " -> "disable " */ break;
                case KC_F: magic_replace_decode_send_cap_cycle(MAGIC_STRING_M_E_R_G_E_D, 'd', MAGIC_CYCLE_NONE); /* emits "merged " */ break;
                case KC_G: magic_replace_decode_send_cap_cycle(MAGIC_STRING_C_H_A_N_G_E, 'e', MAGIC_CYCLE_NONE); /* emits "change " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(MAGIC_STRING_T_A_S_K, 'k', MAGIC_CYCLE_NONE); /* emits "task " */ break;
                case KC_L: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_L_R_E_A_D_Y, 'y', MAGIC_CYCLE_NONE); /* emits "already " */ break;
                case KC_M: magic_decode_send_suffix_cycle(MAGIC_STRING_U_L_T_I_P_L_E, 'e', MAGIC_CYCLE_NONE); /* emits "ultiple " -> "multiple " */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_N_Y_T_H_I_N_G, 'g', MAGIC_CYCLE_NONE); /* emits "anything " */ break;
                case KC_P: magic_decode_send_suffix_cycle(MAGIC_STRING_R_O_B_A_B_L_Y, 'y', MAGIC_CYCLE_NONE); /* emits "robably " -> "probably " */ break;
                case KC_R: magic_replace_tap_repeatable(KC_QUES); break;
                case KC_S: magic_decode_send_suffix_cycle(MAGIC_STRING_U_P_P_O_R_T, 't', MAGIC_CYCLE_NONE); /* emits "upport " -> "support " */ break;
                case KC_T: magic_decode_send_suffix_cycle(MAGIC_STRING_H_R_O_U_G_H, 'h', MAGIC_CYCLE_NONE); /* emits "hrough " -> "through " */ break;
                case KC_V: magic_decode_send_suffix_cycle(MAGIC_STRING_E_R_S_I_O_N, 'n', MAGIC_CYCLE_NONE); /* emits "ersion " -> "version " */ break;
                case KC_W: magic_replace_decode_send_cap_cycle(MAGIC_STRING_O_T_H_E_R_W_I_S_E, 'e', MAGIC_CYCLE_NONE); /* emits "otherwise " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_P_L_I_C_I_T, 't', MAGIC_CYCLE_NONE); /* emits "explicit " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_E;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_F: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_F)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_F;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_V_E, '\0', MAGIC_CYCLE_NONE); /* emits "'ve " */ break;
                case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_I_F_F_I_C_U_L_T_Y, 'y', MAGIC_CYCLE_NONE); /* emits "ifficulty " -> "difficulty " */ break;
                case KC_G: magic_decode_send_suffix_cycle(MAGIC_STRING_E_N_E_R_A_L, 'l', MAGIC_CYCLE_NONE); /* emits "eneral " -> "general " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(MAGIC_STRING_T_H_A_N_K_S, 's', MAGIC_STRING_T_H_A_N_K_S); /* emits "thanks " */ break;
                case KC_L: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_V_A_I_L_A_B_L_E, 'e', MAGIC_CYCLE_NONE); /* emits "available " */ break;
                case KC_M: magic_decode_send_suffix_cycle(MAGIC_STRING_I_S_M_A_T_C_H, 'h', MAGIC_CYCLE_NONE); /* emits "ismatch " -> "mismatch " */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_P_L_A_I_N, 'n', MAGIC_STRING_E_X_P_L_A_I_N); /* emits "explain " */ break;
                case KC_P: magic_replace_decode_send_cap_cycle(MAGIC_STRING_I_M_P_O_R_T_A_N_T, 't', MAGIC_CYCLE_NONE); /* emits "important " */ break;
                case KC_R: magic_tap_repeatable(KC_X); break;
                case KC_S: magic_decode_send_suffix_cycle(MAGIC_STRING_I_M_I_L_A_R, 'r', MAGIC_CYCLE_NONE); /* emits "imilar " -> "similar " */ break;
                case KC_T: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_N_O_T_H_E_R, 'r', MAGIC_CYCLE_NONE); /* emits "another " */ break;
                case KC_W: magic_replace_decode_send_cap_cycle(MAGIC_STRING_S_W_I_T_C_H, 'h', MAGIC_CYCLE_NONE); /* emits "switch " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_I_T, 't', MAGIC_CYCLE_NONE); /* emits "exit " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_F;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_G: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_G)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_G;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_A: magic_tap_repeatable(KC_E); break;
                case KC_E: magic_tap_repeatable(KC_H); break;
                case KC_H: magic_replace_decode_send_cap_cycle(MAGIC_STRING_Q_U, '\0', MAGIC_CYCLE_NONE); /* emits "qu" */ break;
                case KC_I: magic_decode_send(MAGIC_STRING_M_P_L); /* emits "mpl" -> "impl" */ break;
                case KC_O: magic_tap_repeatable(KC_H); break;
                case KC_R: magic_replace_tap_repeatable(KC_EXLM); break;
                case KC_SPC: magic_replace_tap_repeatable(KC_Z); break;
                case KC_U: magic_tap_repeatable(KC_H); break;
                case KC_Y: magic_replace_decode_send_cap_cycle(MAGIC_STRING_O_N_L_Y, 'y', MAGIC_CYCLE_NONE); /* emits "only " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_G;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_H: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_H)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_H;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_A: magic_replace_decode_send_cap_cycle(MAGIC_STRING_G_R_E_G_O_R, 'r', MAGIC_CYCLE_NONE); /* emits "gregor " */ break;
                case KC_B: magic_replace_decode_send_cap_cycle(MAGIC_STRING_O_B_S_O_L_E_T_E, 'e', MAGIC_CYCLE_NONE); /* emits "obsolete " */ break;
                case KC_C: magic_decode_send_suffix_cycle(MAGIC_STRING_O_M_M_E_N_T, 't', MAGIC_CYCLE_NONE); /* emits "omment " -> "comment " */ break;
                case KC_COMMA: magic_decode_send_cap_cycle(MAGIC_STRING_A_N_D, '\0', MAGIC_CYCLE_NONE); /* emits " and " */ break;
                case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_I_D_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "idn't " -> "didn't " */ break;
                case KC_E: magic_replace_decode_send_cap_cycle(MAGIC_STRING_L_G_T_M, 'M', MAGIC_CYCLE_NONE); /* emits "LGTM " */ break;
                case KC_ENT: magic_decode_send_cap_cycle(MAGIC_STRING_A_N_D_2, 'd', MAGIC_CYCLE_NONE); /* emits "and " */ break;
                case KC_F: magic_decode_send_suffix_cycle(MAGIC_STRING_O_C_U_S_E_D, 'd', MAGIC_CYCLE_NONE); /* emits "ocused " -> "focused " */ break;
                case KC_G: magic_decode_send_suffix_cycle(MAGIC_STRING_E_N_E_R_A_T_E, 'e', MAGIC_STRING_G_E_N_E_R_A_T_E); /* emits "enerate " -> "generate " */ break;
                case KC_I: magic_replace_decode_send_cap_cycle(MAGIC_STRING_Z_E_I_T_L_I_N_G_E_R_U0040_G_M_A_I_L_DOT_C_O_M, '\0', MAGIC_CYCLE_NONE); /* emits "zeitlinger@gmail.com" */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(MAGIC_STRING_U_P_D_A_T_E, 'e', MAGIC_CYCLE_NONE); /* emits "update " */ break;
                case KC_L: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_L_A_B_O_R_A_T_E, 'e', MAGIC_STRING_E_L_A_B_O_R_A_T_E); /* emits "elaborate " */ break;
                case KC_M: magic_replace_decode_send_cap_cycle(MAGIC_STRING_I_N_S_T_R_U_M_E_N_T, 't', MAGIC_STRING_I_N_S_T_R_U_M_E_N_T); /* emits "instrument " */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(MAGIC_STRING_U_N_D_E_R_S_T_A_N_D, 'd', MAGIC_CYCLE_NONE); /* emits "understand " */ break;
                case KC_P: magic_decode_send_suffix_cycle(MAGIC_STRING_R_O_D_U_C_T_I_O_N, 'n', MAGIC_CYCLE_NONE); /* emits "roduction " -> "production " */ break;
                case KC_R: magic_replace_tap_repeatable(KC_QUOTE); break;
                case KC_S: magic_decode_send_suffix_cycle(MAGIC_STRING_E_P_A_R_A_T_E, 'e', MAGIC_STRING_S_E_P_A_R_A_T_E); /* emits "eparate " -> "separate " */ break;
                case KC_SPC: magic_decode_send_cap_cycle(MAGIC_STRING_A_N_D_2, 'd', MAGIC_CYCLE_NONE); /* emits "and " */ break;
                case KC_T: magic_decode_send_suffix_cycle(MAGIC_STRING_H_O_U_G_H, 'h', MAGIC_CYCLE_NONE); /* emits "hough " -> "though " */ break;
                case KC_TAB: magic_decode_send_cap_cycle(MAGIC_STRING_A_N_D_2, 'd', MAGIC_CYCLE_NONE); /* emits "and " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_P_P_R_O_V_A_L, 'l', MAGIC_STRING_A_P_P_R_O_V_A_L); /* emits "approval " */ break;
                case KC_W: magic_decode_send_suffix_cycle(MAGIC_STRING_H_Y, 'y', MAGIC_CYCLE_NONE); /* emits "hy " -> "why " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_C_L_U_D_E, 'e', MAGIC_CYCLE_NONE); /* emits "exclude " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_H;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_I: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_I)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_I;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_A: magic_replace_decode_send_cap_cycle(MAGIC_STRING_Z_E_I_T_L_I_N_G_E_R, 'r', MAGIC_CYCLE_NONE); /* emits "zeitlinger " */ break;
                case KC_B: magic_decode_send_suffix_cycle(MAGIC_STRING_E_C_A_U_S_E, 'e', MAGIC_CYCLE_NONE); /* emits "ecause " -> "because " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_R_E, '\0', MAGIC_CYCLE_NONE); /* emits "'re " */ break;
                case KC_COMMA: magic_decode_send_cap_cycle(MAGIC_STRING_B_U_T, '\0', MAGIC_CYCLE_NONE); /* emits " but " */ break;
                case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_O_E_S_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "oesn't " -> "doesn't " */ break;
                case KC_ENT: magic_decode_send_cap_cycle(MAGIC_STRING_T_H_E, 'e', MAGIC_CYCLE_NONE); /* emits "the " */ break;
                case KC_F: magic_decode_send_suffix_cycle(MAGIC_STRING_O_L_L_O_W_I_N_G, 'g', MAGIC_CYCLE_NONE); /* emits "ollowing " -> "following " */ break;
                case KC_G: magic_tap_repeatable(KC_K); break;
                case KC_I: magic_replace_decode_send_cap_cycle(MAGIC_STRING_G_R_E_G_O_R_DOT_Z_E_I_T_L_I_N_G_E_R_U0040_G_R_A_F_A_N_A_DOT_C_O_M, '\0', MAGIC_CYCLE_NONE); /* emits "gregor.zeitlinger@grafana.com" */ break;
                case KC_K: magic_decode_send_suffix_cycle(MAGIC_STRING_N_O_W, 'w', MAGIC_CYCLE_NONE); /* emits "now " -> "know " */ break;
                case KC_L: magic_tap_repeatable(KC_R); break;
                case KC_M: magic_decode_send(MAGIC_STRING_E_N_T); /* emits "ent" -> "ment" */ break;
                case KC_N: magic_replace_decode_send_cap_cycle(MAGIC_STRING_W_O_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "won't " */ break;
                case KC_P: magic_tap_repeatable(KC_N); break;
                case KC_R: magic_replace_tap_repeatable(KC_COMMA); break;
                case KC_S: magic_decode_send(MAGIC_STRING_I_O_N); /* emits "ion" -> "sion" */ break;
                case KC_SPC: magic_decode_send_cap_cycle(MAGIC_STRING_T_H_E, 'e', MAGIC_CYCLE_NONE); /* emits "the " */ break;
                case KC_T: magic_decode_send(MAGIC_STRING_I_O_N); /* emits "ion" -> "tion" */ break;
                case KC_TAB: magic_decode_send_cap_cycle(MAGIC_STRING_T_H_E, 'e', MAGIC_CYCLE_NONE); /* emits "the " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_R_E_S_O_L_V_E, 'e', MAGIC_STRING_R_E_S_O_L_V_E); /* emits "resolve " */ break;
                case KC_W: magic_tap_repeatable(KC_S); break;
                case KC_X: magic_tap_repeatable(KC_R); break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_I;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_J: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_J)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_J;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_A: magic_replace_decode_send_cap_cycle(MAGIC_STRING_G_R_A_F_A_N_A, 'a', MAGIC_CYCLE_NONE); /* emits "grafana " */ break;
                case KC_B: magic_tap_repeatable(KC_D); break;
                case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_D, '\0', MAGIC_CYCLE_NONE); /* emits "'d " */ break;
                case KC_D: magic_tap_repeatable(KC_F); break;
                case KC_F: magic_tap_repeatable(KC_D); break;
                case KC_G: magic_tap_repeatable(KC_D); break;
                case KC_I: magic_replace_decode_send_cap_cycle(MAGIC_STRING_G_R_E_G_O_R_U0040_Z_E_I_T_L_I_N_G_E_R_DOT_D_E, '\0', MAGIC_CYCLE_NONE); /* emits "gregor@zeitlinger.de" */ break;
                case KC_K: magic_tap_repeatable(KC_X); break;
                case KC_L: magic_tap_repeatable(KC_C); break;
                case KC_M: magic_tap_repeatable(KC_L); break;
                case KC_N: magic_tap_repeatable(KC_X); break;
                case KC_P: magic_tap_repeatable(KC_D); break;
                case KC_R: magic_replace_tap_repeatable(KC_DOT); break;
                case KC_S: magic_tap_repeatable(KC_D); break;
                case KC_T: magic_replace_decode_send_cap_cycle(MAGIC_STRING_W_I_T_H_O_U_T, 't', MAGIC_CYCLE_NONE); /* emits "without " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_I_APOSTROPHE_V_E, 'e', MAGIC_CYCLE_NONE); /* emits "I've " */ break;
                case KC_W: magic_tap_repeatable(KC_X); break;
                case KC_X: magic_tap_repeatable(KC_D); break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_J;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
        case MAGIC_K: {
            if (allow_repeat && repeat_last_magic_key(MAGIC_K)) {
                return false;
            }
            magic_remembered_keycode = MAGIC_K;
            magic_repeat_keycode = KC_NO;
            switch (magic_prepare_last_keycode(context_keycode)) {
                case KC_B: magic_decode_send_suffix_cycle(MAGIC_STRING_E_F_O_R_E, 'e', MAGIC_CYCLE_NONE); /* emits "efore " -> "before " */ break;
                case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_S, '\0', MAGIC_CYCLE_NONE); /* emits "'s " */ break;
                case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_O_E_S, 's', MAGIC_CYCLE_NONE); /* emits "oes " -> "does " */ break;
                case KC_G: magic_replace_decode_send_cap_cycle(MAGIC_STRING_S_U_G_G_E_S_T, 't', MAGIC_CYCLE_NONE); /* emits "suggest " */ break;
                case KC_K: magic_decode_send_suffix_cycle(MAGIC_STRING_N_E_W, 'w', MAGIC_CYCLE_NONE); /* emits "new " -> "knew " */ break;
                case KC_L: magic_tap_repeatable(KC_B); break;
                case KC_M: magic_tap_repeatable(KC_T); break;
                case KC_N: magic_tap_repeatable(KC_P); break;
                case KC_P: magic_replace_decode_send_cap_cycle(MAGIC_STRING_P_R_O_M_E_T_H_E_U_S, 's', MAGIC_CYCLE_NONE); /* emits "Prometheus " */ break;
                case KC_R: magic_replace_tap_repeatable(KC_J); break;
                case KC_S: magic_decode_send_suffix_cycle(MAGIC_STRING_O_M_E_T_H_I_N_G, 'g', MAGIC_CYCLE_NONE); /* emits "omething " -> "something " */ break;
                case KC_T: magic_decode_send_suffix_cycle(MAGIC_STRING_H_O_U_G_H_T, 't', MAGIC_CYCLE_NONE); /* emits "hought " -> "thought " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_W_O_R_S_E, 'e', MAGIC_CYCLE_NONE); /* emits "worse " */ break;
                case KC_W: magic_decode_send_suffix_cycle(MAGIC_STRING_H_I_C_H, 'h', MAGIC_CYCLE_NONE); /* emits "hich " -> "which " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_A_M_P_L_E, 'e', MAGIC_CYCLE_NONE); /* emits "example " */ break;
            }
            magic_capitalize_next = false;
            last_magic_trigger = MAGIC_K;
            last_magic_repeat_keycode = magic_repeat_keycode;
            set_last_keycode(magic_remembered_keycode);
            return false;
        }
    default:
        return true;
    }
}

bool process_record_generated(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Adaptive keys: runs after combo resolution in process_record_user,
        // so combo components are suppressed and prev_keycode reflects the
        // resolved combo keycode (e.g. KC_P not KC_C).
        uint16_t adaptive_prev_keycode = unshift_letter_keycode(prev_keycode);
        switch (keycode) {
            case KC_E:
                switch (adaptive_prev_keycode) {
                    case KC_A: return tap_adaptive(KC_E, KC_U);
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
                    case KC_X: return tap_adaptive(KC_D, KC_C);
                }
                break;
            case KC_N:
                switch (adaptive_prev_keycode) {
                    case KC_C: return tap_adaptive(KC_N, KC_K);
                    case KC_P: return tap_adaptive(KC_N, KC_P);
                    case KC_T: return tap_adaptive(KC_N, KC_T);
                }
                break;
            case KC_C:
                switch (adaptive_prev_keycode) {
                    case KC_D: return tap_adaptive(KC_C, KC_V);
                    case KC_L: return tap_adaptive(KC_C, KC_V);
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
                    case KC_D: return tap_adaptive(KC_H, KC_G);
                    case KC_E: return tap_adaptive(KC_H, KC_E);
                    case KC_L: return tap_adaptive(KC_H, KC_P);
                    case KC_M: return tap_adaptive(KC_H, KC_M);
                    case KC_N: return tap_adaptive(KC_H, KC_N);
                    case KC_O: return tap_adaptive(KC_H, KC_O);
                    case KC_U: return tap_adaptive(KC_H, KC_A);
                }
                break;
            case KC_U:
                switch (adaptive_prev_keycode) {
                    case KC_E: return tap_adaptive(KC_U, KC_O);
                }
                break;
            case KC_R:
                switch (adaptive_prev_keycode) {
                    case KC_K: return tap_adaptive(KC_R, KC_N);
                    case KC_L: return tap_adaptive(KC_R, KC_L);
                    case KC_M: return tap_adaptive(KC_R, KC_P);
                    case KC_N: return tap_adaptive(KC_R, KC_G);
                    case KC_S: return tap_adaptive(KC_R, KC_S);
                    case KC_Y: return tap_adaptive(KC_R, KC_I);
                }
                break;
            case KC_B:
                switch (adaptive_prev_keycode) {
                    case KC_L: return tap_adaptive(KC_B, KC_K);
                }
                break;
            case KC_T:
                switch (adaptive_prev_keycode) {
                    case KC_M: return tap_adaptive(KC_T, KC_B);
                }
                break;
            case KC_P:
                switch (adaptive_prev_keycode) {
                    case KC_N: return tap_adaptive(KC_P, KC_K);
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
                    case KC_P: return tap_adaptive(KC_Y, KC_S);
                }
                break;
            case KC_W:
                switch (adaptive_prev_keycode) {
                    case KC_X: return tap_adaptive(KC_W, KC_P);
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
