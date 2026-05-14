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
#define MAGIC_STRING_A_C_K_G_R_O_U_N_D 75
#define MAGIC_STRING_A_D_D_R_E_S_S 84
#define MAGIC_STRING_A_L_I_D_A_T_E 91
#define MAGIC_STRING_A_L_R_E_A_D_Y 97
#define MAGIC_STRING_A_L_W_A_Y_S 104
#define MAGIC_STRING_A_N_D 0
#define MAGIC_STRING_A_N_D_2 110
#define MAGIC_STRING_A_N_G_U_A_G_E 114
#define MAGIC_STRING_A_N_O_T_H_E_R 119
#define MAGIC_STRING_A_N_Y_T_H_I_N_G 124
#define MAGIC_STRING_A_P_P_R_O_V_A_L 130
#define MAGIC_STRING_A_S_I_C_A_L_L_Y 138
#define MAGIC_STRING_A_S_N_APOSTROPHE_T 146
#define MAGIC_STRING_A_V_A_I_L_A_B_L_E 151
#define MAGIC_STRING_B_A_C_K_G_R_O_U_N_D 159
#define MAGIC_STRING_B_A_S_I_C_A_L_L_Y 169
#define MAGIC_STRING_B_E_C_A_U_S_E 178
#define MAGIC_STRING_B_E_C_O_M_E 185
#define MAGIC_STRING_B_E_F_O_R_E 191
#define MAGIC_STRING_B_U_T 5
#define MAGIC_STRING_C_H_A_N_G_E 197
#define MAGIC_STRING_C_O_M_M_E_N_T 202
#define MAGIC_STRING_C_O_N_F_L_I_C_T 208
#define MAGIC_STRING_C_O_N_F_U_S_I_N_G 215
#define MAGIC_STRING_DOT 29
#define MAGIC_STRING_D_D_R_E_S_S 222
#define MAGIC_STRING_D_I_D_N_APOSTROPHE_T 228
#define MAGIC_STRING_D_I_F_F_I_C_U_L_T_Y 235
#define MAGIC_STRING_D_I_S_A_B_L_E 246
#define MAGIC_STRING_D_O_E_S 253
#define MAGIC_STRING_D_O_E_S_N_APOSTROPHE_T 257
#define MAGIC_STRING_D_O_N_APOSTROPHE_T 263
#define MAGIC_STRING_E_C_A_U_S_E 268
#define MAGIC_STRING_E_C_O_M_E 274
#define MAGIC_STRING_E_F_O_R_E 279
#define MAGIC_STRING_E_L_A_B_O_R_A_T_E 284
#define MAGIC_STRING_E_N_A_B_L_E 291
#define MAGIC_STRING_E_N_E_R_A_T_E 297
#define MAGIC_STRING_E_N_T 302
#define MAGIC_STRING_E_O_P_L_E 305
#define MAGIC_STRING_E_P_A_R_A_T_E 310
#define MAGIC_STRING_E_R_S_I_O_N 316
#define MAGIC_STRING_E_V_E_R 321
#define MAGIC_STRING_E_V_E_R_Y_T_H_I_N_G 326
#define MAGIC_STRING_E_X_A_M_P_L_E 334
#define MAGIC_STRING_E_X_C_E_P_T 341
#define MAGIC_STRING_E_X_C_E_P_T_I_O_N 348
#define MAGIC_STRING_E_X_C_L_U_D_E 357
#define MAGIC_STRING_E_X_I_T 364
#define MAGIC_STRING_E_X_P_L_A_I_N 369
#define MAGIC_STRING_E_X_P_L_I_C_I_T 376
#define MAGIC_STRING_F_O_C_U_S_E_D 384
#define MAGIC_STRING_F_O_L_L_O_W_I_N_G 392
#define MAGIC_STRING_G_E_N_E_R_A_T_E 399
#define MAGIC_STRING_G_O_E_S 405
#define MAGIC_STRING_G_R_A_F_A_N_A 32
#define MAGIC_STRING_G_R_A_F_A_N_A_L_A_B_S 38
#define MAGIC_STRING_G_R_E_G_O_R 48
#define MAGIC_STRING_G_R_E_G_O_R_2 409
#define MAGIC_STRING_G_R_E_G_O_R_DOT_Z_E_I_T_L_I_N_G_E_R_U0040_G_R_A_F_A_N_A_DOT_C_O_M 413
#define MAGIC_STRING_G_R_E_G_O_R_U0040_Z_E_I_T_L_I_N_G_E_R_DOT_D_E 433
#define MAGIC_STRING_H_I_C_H 447
#define MAGIC_STRING_H_O_U_G_H 451
#define MAGIC_STRING_H_O_U_G_H_T 455
#define MAGIC_STRING_H_R_O_U_G_H 460
#define MAGIC_STRING_H_Y 465
#define MAGIC_STRING_I_APOSTROPHE_V_E 53
#define MAGIC_STRING_I_D_N_APOSTROPHE_T 469
#define MAGIC_STRING_I_F_F_I_C_U_L_T_Y 475
#define MAGIC_STRING_I_G_R_A_T_I_O_N 485
#define MAGIC_STRING_I_M_I_L_A_R 491
#define MAGIC_STRING_I_M_P_L 496
#define MAGIC_STRING_I_M_P_L_E_M_E_N_T 500
#define MAGIC_STRING_I_M_P_L_E_M_E_N_T_A_T_I_O_N 507
#define MAGIC_STRING_I_M_P_O_R_T_A_N_T 516
#define MAGIC_STRING_I_M_P_O_S_S_I_B_L_E 523
#define MAGIC_STRING_I_M_P_R_O_V_E 531
#define MAGIC_STRING_I_N_S_T_R_U_M_E_N_T 537
#define MAGIC_STRING_I_N_S_T_R_U_M_E_N_T_A_T_I_O_N 544
#define MAGIC_STRING_I_O_N 553
#define MAGIC_STRING_I_S_A_B_L_E 556
#define MAGIC_STRING_I_S_M_A_T_C_H 562
#define MAGIC_STRING_J_U_S_T 568
#define MAGIC_STRING_K_N_E_W 572
#define MAGIC_STRING_K_N_O_W 577
#define MAGIC_STRING_L_A_N_G_U_A_G_E 582
#define MAGIC_STRING_M_E_N_T 588
#define MAGIC_STRING_M_E_R_G_E_D 591
#define MAGIC_STRING_M_I_G_R_A_T_I_O_N 597
#define MAGIC_STRING_M_I_S_M_A_T_C_H 603
#define MAGIC_STRING_M_P_L 609
#define MAGIC_STRING_M_P_L_E_M_E_N_T 613
#define MAGIC_STRING_M_U_L_T_I_P_L_E 620
#define MAGIC_STRING_N_APOSTROPHE_T 627
#define MAGIC_STRING_N_APOSTROPHE_T_2 631
#define MAGIC_STRING_N_E_V_E_R 635
#define MAGIC_STRING_N_E_W 640
#define MAGIC_STRING_N_O_W 644
#define MAGIC_STRING_O_B_S_E_R_V_A_B_I_L_I_T_Y 648
#define MAGIC_STRING_O_B_S_O_L_E_T_E 660
#define MAGIC_STRING_O_C_U_S_E_D 667
#define MAGIC_STRING_O_E_S 674
#define MAGIC_STRING_O_E_S_N_APOSTROPHE_T 677
#define MAGIC_STRING_O_L_L_O_W_I_N_G 682
#define MAGIC_STRING_O_M_E_O_N_E 688
#define MAGIC_STRING_O_M_E_T_H_I_N_G 693
#define MAGIC_STRING_O_M_M_E_N_T 699
#define MAGIC_STRING_O_N_APOSTROPHE_T 704
#define MAGIC_STRING_O_N_L_Y 708
#define MAGIC_STRING_O_R_K 713
#define MAGIC_STRING_O_T_H_E_R_W_I_S_E 717
#define MAGIC_STRING_P_E_O_P_L_E 724
#define MAGIC_STRING_P_E_R_F_O_R_M_A_N_C_E 730
#define MAGIC_STRING_P_O_S_S_I_B_L_E 739
#define MAGIC_STRING_P_R_O_B_A_B_L_Y 746
#define MAGIC_STRING_P_R_O_D_U_C_T_I_O_N 755
#define MAGIC_STRING_P_R_O_M_E_T_H_E_U_S 58
#define MAGIC_STRING_Q_U 65
#define MAGIC_STRING_Q_U_2 764
#define MAGIC_STRING_Q_U_E_S_T_I_O_N 767
#define MAGIC_STRING_R_E_S_O_L_V_E 773
#define MAGIC_STRING_R_O_B_A_B_L_Y 779
#define MAGIC_STRING_R_O_D_U_C_T_I_O_N 787
#define MAGIC_STRING_S_E_P_A_R_A_T_E 795
#define MAGIC_STRING_S_I_M_I_L_A_R 801
#define MAGIC_STRING_S_I_O_N 806
#define MAGIC_STRING_S_O_M_E_O_N_E 809
#define MAGIC_STRING_S_O_M_E_T_H_I_N_G 814
#define MAGIC_STRING_S_U_G_G_E_S_T 820
#define MAGIC_STRING_S_U_P_P_O_R_T 825
#define MAGIC_STRING_S_W_I_T_C_H 831
#define MAGIC_STRING_T_A_S_K 837
#define MAGIC_STRING_T_H_A_N_K_S 850
#define MAGIC_STRING_T_H_A_N_K_Y_O_U 842
#define MAGIC_STRING_T_H_E 855
#define MAGIC_STRING_T_H_I_N_K 858
#define MAGIC_STRING_T_H_O_U_G_H 863
#define MAGIC_STRING_T_H_O_U_G_H_T 868
#define MAGIC_STRING_T_H_R_O_U_G_H 873
#define MAGIC_STRING_T_I_O_N 878
#define MAGIC_STRING_U_L_T_I_P_L_E 881
#define MAGIC_STRING_U_N_D_E_R_S_T_A_N_D 887
#define MAGIC_STRING_U_P_D_A_T_E 895
#define MAGIC_STRING_U_P_P_O_R_T 901
#define MAGIC_STRING_V_A_L_I_D_A_T_E 907
#define MAGIC_STRING_V_A_L_I_D_A_T_I_O_N 914
#define MAGIC_STRING_V_E_R_S_I_O_N 922
#define MAGIC_STRING_W_A_S_N_APOSTROPHE_T 928
#define MAGIC_STRING_W_H_I_C_H 934
#define MAGIC_STRING_W_H_Y 939
#define MAGIC_STRING_W_I_T_H_O_U_T 944
#define MAGIC_STRING_W_O_N_APOSTROPHE_T 950
#define MAGIC_STRING_W_O_R_K 955
#define MAGIC_STRING_W_O_R_S_E 960
#define MAGIC_STRING_Z_E_I_T_L_I_N_G_E_R 68
#define MAGIC_STRING_Z_E_I_T_L_I_N_G_E_R_U0040_G_M_A_I_L_DOT_C_O_M 965

static const char magic_char_4bit[] = {
    ' ', 'e', 'o', 't', 'n', 'a', 'i', 'r', 'l', 's', 'g', 'm', 'u', 'h'
};

static const char magic_char_extended[] = {
    'c', 'd', 'p', 'b', '\'', 'w', 'y', 'f', 'v', 'k', 'x', '.', '@', 'G', 'z', 'q', 'I', 'L', 'P', 'Q', 'Z', 'j'
};

static const uint8_t magic_string_data[] = {
    0x05, 0x05, 0x4f, 0xe1, 0x00, 0x05, 0x0f, 0xe3, 0xc3, 0x00, 0x03, 0xe4, 0xe1, 0x00, 0x04, 0xe4,
    0x88, 0x00, 0x04, 0xe4, 0x71, 0x00, 0x03, 0xe4, 0x90, 0x04, 0xe4, 0xe8, 0x10, 0x02, 0xeb, 0x00,
    0x07, 0xed, 0x75, 0xe7, 0x54, 0x50, 0x0c, 0xed, 0x75, 0xe7, 0x54, 0x50, 0xf1, 0x5f, 0xe3, 0x90,
    0x07, 0xed, 0x71, 0xa2, 0x70, 0x05, 0xf0, 0xe4, 0xe8, 0x10, 0x0b, 0xf2, 0x72, 0xb1, 0x3d, 0x1c,
    0x90, 0x02, 0xf3, 0xc0, 0x0b, 0xf4, 0x16, 0x38, 0x64, 0xa1, 0x70, 0x0a, 0x5f, 0xe0, 0xe9, 0xa7,
    0x2c, 0x4f, 0xe1, 0x00, 0x08, 0x5f, 0xe1, 0xe1, 0x71, 0x99, 0x00, 0x08, 0x58, 0x6f, 0xe1, 0x53,
    0x10, 0x08, 0x58, 0x71, 0x5f, 0xe1, 0xe6, 0x00, 0x07, 0x58, 0xe5, 0x5f, 0xe6, 0x90, 0x04, 0x54,
    0xe1, 0x00, 0x08, 0x54, 0xac, 0x5a, 0x10, 0x08, 0x54, 0x23, 0xd1, 0x70, 0x09, 0x54, 0xe6, 0x3d,
    0x64, 0xa0, 0x09, 0x5f, 0xe2, 0xe2, 0x72, 0xe8, 0x58, 0x00, 0x09, 0x59, 0x6f, 0xe0, 0x58, 0x8f,
    0xe6, 0x00, 0x06, 0x59, 0x4f, 0xe4, 0x30, 0x0a, 0x5f, 0xe8, 0x56, 0x85, 0xe3, 0x81, 0x00, 0x0b,
    0xe3, 0x5f, 0xe0, 0xe9, 0xa7, 0x2c, 0x4f, 0xe1, 0x00, 0x0a, 0xe3, 0x59, 0x6f, 0xe0, 0x58, 0x8f,
    0xe6, 0x00, 0x08, 0xe3, 0x1f, 0xe0, 0x5c, 0x91, 0x00, 0x07, 0xe3, 0x1f, 0xe0, 0x2b, 0x10, 0x07,
    0xe3, 0x1f, 0xe7, 0x27, 0x10, 0x07, 0xe0, 0xd5, 0x4a, 0x10, 0x08, 0xe0, 0x2b, 0xb1, 0x43, 0x00,
    0x09, 0xe0, 0x24, 0xe7, 0x86, 0xe0, 0x30, 0x0a, 0xe0, 0x24, 0xe7, 0xc9, 0x64, 0xa0, 0x07, 0xe1,
    0xe1, 0x71, 0x99, 0x00, 0x07, 0xe1, 0x6f, 0xe1, 0x4f, 0xe4, 0x30, 0x0b, 0xe1, 0x6f, 0xe7, 0xe7,
    0x6f, 0xe0, 0xc8, 0x3f, 0xe6, 0x00, 0x08, 0xe1, 0x69, 0x5f, 0xe3, 0x81, 0x00, 0x05, 0xe1, 0x21,
    0x90, 0x08, 0xe1, 0x21, 0x94, 0xe4, 0x30, 0x06, 0xe1, 0x24, 0xe4, 0x30, 0x07, 0x1f, 0xe0, 0x5c,
    0x91, 0x00, 0x06, 0x1f, 0xe0, 0x2b, 0x10, 0x06, 0x1f, 0xe7, 0x27, 0x10, 0x0a, 0x18, 0x5f, 0xe3,
    0x27, 0x53, 0x10, 0x07, 0x14, 0x5f, 0xe3, 0x81, 0x00, 0x08, 0x14, 0x17, 0x53, 0x10, 0x03, 0x14,
    0x30, 0x06, 0x12, 0xe2, 0x81, 0x00, 0x08, 0x1f, 0xe2, 0x57, 0x53, 0x10, 0x07, 0x17, 0x96, 0x24,
    0x00, 0x05, 0x1f, 0xe8, 0x17, 0x00, 0x0b, 0x1f, 0xe8, 0x17, 0xe6, 0x3d, 0x64, 0xa0, 0x08, 0x1f,
    0xea, 0x5b, 0xe2, 0x81, 0x00, 0x07, 0x1f, 0xea, 0xe0, 0x1f, 0xe2, 0x30, 0x0a, 0x1f, 0xea, 0xe0,
    0x1f, 0xe2, 0x36, 0x24, 0x00, 0x08, 0x1f, 0xea, 0xe0, 0x8c, 0xe1, 0x10, 0x05, 0x1f, 0xea, 0x63,
    0x00, 0x08, 0x1f, 0xea, 0xe2, 0x85, 0x64, 0x00, 0x09, 0x1f, 0xea, 0xe2, 0x86, 0xe0, 0x63, 0x00,
    0x08, 0xe7, 0x2f, 0xe0, 0xc9, 0x1f, 0xe1, 0x00, 0x0a, 0xe7, 0x28, 0x82, 0xe5, 0x64, 0xa0, 0x09,
    0xa1, 0x41, 0x75, 0x31, 0x00, 0x05, 0xa2, 0x19, 0x00, 0x06, 0xa7, 0x1a, 0x27, 0x1d, 0xa7, 0x1a,
    0x27, 0xeb, 0xee, 0x16, 0x38, 0x64, 0xa1, 0x7f, 0xec, 0xa7, 0x5f, 0xe7, 0x54, 0x5f, 0xeb, 0xe0,
    0x2b, 0x14, 0xa7, 0x1a, 0x27, 0xec, 0xee, 0x16, 0x38, 0x64, 0xa1, 0x7f, 0xeb, 0xe1, 0x10, 0x05,
    0xd6, 0xe0, 0xd0, 0x06, 0xd2, 0xca, 0xd0, 0x07, 0xd2, 0xca, 0xd3, 0x00, 0x07, 0xd7, 0x2c, 0xad,
    0x00, 0x03, 0xdf, 0xe6, 0x00, 0x06, 0x6f, 0xe1, 0x4f, 0xe4, 0x30, 0x0a, 0x6f, 0xe7, 0xe7, 0x6f,
    0xe0, 0xc8, 0x3f, 0xe6, 0x00, 0x09, 0x6a, 0x75, 0x36, 0x24, 0x00, 0x07, 0x6b, 0x68, 0x57, 0x00,
    0x04, 0x6b, 0xe2, 0x80, 0x0a, 0x6b, 0xe2, 0x81, 0xb1, 0x43, 0x00, 0x0f, 0x6b, 0xe2, 0x81, 0xb1,
    0x43, 0x53, 0x62, 0x40, 0x0a, 0x6b, 0xe2, 0x27, 0x35, 0x43, 0x00, 0x0b, 0x6b, 0xe2, 0x29, 0x96,
    0xe3, 0x81, 0x00, 0x08, 0x6b, 0xe2, 0x72, 0xe8, 0x10, 0x0b, 0x64, 0x93, 0x7c, 0xb1, 0x43, 0x00,
    0x10, 0x64, 0x93, 0x7c, 0xb1, 0x43, 0x53, 0x62, 0x40, 0x03, 0x62, 0x40, 0x07, 0x69, 0x5f, 0xe3,
    0x81, 0x00, 0x08, 0x69, 0xb5, 0x3f, 0xe0, 0xd0, 0x05, 0xf5, 0xc9, 0x30, 0x05, 0xe9, 0x41, 0xe5,
    0x00, 0x05, 0xe9, 0x42, 0xe5, 0x00, 0x09, 0x85, 0x4a, 0xc5, 0xa1, 0x00, 0x04, 0xb1, 0x43, 0x07,
    0xb1, 0x7a, 0x1f, 0xe1, 0x00, 0x0a, 0xb6, 0xa7, 0x53, 0x62, 0x40, 0x09, 0xb6, 0x9b, 0x53, 0xe0,
    0xd0, 0x03, 0xbf, 0xe2, 0x80, 0x09, 0xbf, 0xe2, 0x81, 0xb1, 0x43, 0x00, 0x09, 0xbc, 0x83, 0x6f,
    0xe2, 0x81, 0x00, 0x03, 0x4f, 0xe4, 0x30, 0x04, 0x4f, 0xe4, 0x30, 0x06, 0x41, 0xe8, 0x17, 0x00,
    0x04, 0x41, 0xe5, 0x00, 0x04, 0x42, 0xe5, 0x00, 0x0e, 0x2f, 0xe3, 0x91, 0x7f, 0xe8, 0x5f, 0xe3,
    0x68, 0x63, 0xe6, 0x00, 0x09, 0x2f, 0xe3, 0x92, 0x81, 0x31, 0x00, 0x07, 0x2f, 0xe0, 0xc9, 0x1f,
    0xe1, 0x00, 0x04, 0x21, 0x90, 0x07, 0x21, 0x94, 0xe4, 0x30, 0x09, 0x28, 0x82, 0xe5, 0x64, 0xa0,
    0x07, 0x2b, 0x12, 0x41, 0x00, 0x09, 0x2b, 0x13, 0xd6, 0x4a, 0x00, 0x07, 0x2b, 0xb1, 0x43, 0x00,
    0x05, 0x24, 0xe4, 0x30, 0x05, 0x24, 0x8f, 0xe6, 0x00, 0x04, 0x27, 0xe9, 0x00, 0x0a, 0x23, 0xd1,
    0x7f, 0xe5, 0x69, 0x10, 0x07, 0xe2, 0x12, 0xe2, 0x81, 0x00, 0x0c, 0xe2, 0x17, 0xe7, 0x27, 0xb5,
    0x4f, 0xe0, 0x10, 0x09, 0xe2, 0x29, 0x96, 0xe3, 0x81, 0x00, 0x09, 0xe2, 0x72, 0xe3, 0x5f, 0xe3,
    0x8f, 0xe6, 0x00, 0x0b, 0xe2, 0x72, 0xe1, 0xcf, 0xe0, 0x36, 0x24, 0x00, 0x02, 0xef, 0xc0, 0x09,
    0xef, 0xc1, 0x93, 0x62, 0x40, 0x08, 0x71, 0x92, 0x8f, 0xe8, 0x10, 0x08, 0x72, 0xe3, 0x5f, 0xe3,
    0x8f, 0xe6, 0x00, 0x0a, 0x72, 0xe1, 0xcf, 0xe0, 0x36, 0x24, 0x00, 0x09, 0x91, 0xe2, 0x57, 0x53,
    0x10, 0x08, 0x96, 0xb6, 0x85, 0x70, 0x04, 0x96, 0x24, 0x08, 0x92, 0xb1, 0x24, 0x10, 0x0a, 0x92,
    0xb1, 0x3d, 0x64, 0xa0, 0x08, 0x9c, 0xaa, 0x19, 0x30, 0x08, 0x9c, 0xe2, 0xe2, 0x27, 0x30, 0x07,
    0x9f, 0xe5, 0x63, 0xe0, 0xd0, 0x05, 0x35, 0x9f, 0xe9, 0x00, 0x0a, 0x3d, 0x54, 0xe9, 0x0f, 0xe6,
    0x2c, 0x00, 0x07, 0x3d, 0x54, 0xe9, 0x90, 0x04, 0x3d, 0x10, 0x06, 0x3d, 0x64, 0xe9, 0x00, 0x07,
    0x3d, 0x2c, 0xad, 0x00, 0x08, 0x3d, 0x2c, 0xad, 0x30, 0x08, 0x3d, 0x72, 0xca, 0xd0, 0x04, 0x36,
    0x24, 0x08, 0xc8, 0x36, 0xe2, 0x81, 0x00, 0x0b, 0xc4, 0xe1, 0x17, 0x93, 0x54, 0xe1, 0x00, 0x07,
    0xcf, 0xe2, 0xe1, 0x53, 0x10, 0x07, 0xcf, 0xe2, 0xe2, 0x27, 0x30, 0x09, 0xe8, 0x58, 0x6f, 0xe1,
    0x53, 0x10, 0x0b, 0xe8, 0x58, 0x6f, 0xe1, 0x53, 0x62, 0x40, 0x08, 0xe8, 0x17, 0x96, 0x24, 0x00,
    0x07, 0xe5, 0x59, 0x4f, 0xe4, 0x30, 0x06, 0xe5, 0xd6, 0xe0, 0xd0, 0x04, 0xe5, 0xdf, 0xe6, 0x00,
    0x08, 0xe5, 0x63, 0xd2, 0xc3, 0x00, 0x06, 0xe5, 0x24, 0xe4, 0x30, 0x05, 0xe5, 0x27, 0xe9, 0x00,
    0x06, 0xe5, 0x27, 0x91, 0x00, 0x14, 0xee, 0x16, 0x38, 0x64, 0xa1, 0x7f, 0xec, 0xab, 0x56, 0x8f,
    0xeb, 0xe0, 0x2b
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
    { MAGIC_STRING_G_R_E_G_O_R, MAGIC_STRING_Z_E_I_T_L_I_N_G_E_R, 0, 'r' },
    { MAGIC_STRING_Z_E_I_T_L_I_N_G_E_R, MAGIC_STRING_G_R_E_G_O_R, 0, 'r' },
    { MAGIC_STRING_D_I_S_A_B_L_E, MAGIC_STRING_E_N_A_B_L_E, 0, 'e' },
    { MAGIC_STRING_E_N_A_B_L_E, MAGIC_STRING_D_I_S_A_B_L_E, 0, 'e' },
    { MAGIC_STRING_I_M_P_L_E_M_E_N_T, MAGIC_STRING_I_M_P_L_E_M_E_N_T_A_T_I_O_N, 9, 'n' },
    { MAGIC_STRING_I_M_P_L_E_M_E_N_T_A_T_I_O_N, MAGIC_STRING_I_M_P_L_E_M_E_N_T, 9, 't' },
    { MAGIC_STRING_I_M_P_O_S_S_I_B_L_E, MAGIC_STRING_P_O_S_S_I_B_L_E, 0, 'e' },
    { MAGIC_STRING_I_N_S_T_R_U_M_E_N_T, MAGIC_STRING_I_N_S_T_R_U_M_E_N_T_A_T_I_O_N, 10, 'n' },
    { MAGIC_STRING_I_N_S_T_R_U_M_E_N_T_A_T_I_O_N, MAGIC_STRING_I_N_S_T_R_U_M_E_N_T, 10, 't' },
    { MAGIC_STRING_P_O_S_S_I_B_L_E, MAGIC_STRING_I_M_P_O_S_S_I_B_L_E, 0, 'e' },
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
// Key presses first remember the real trigger keycode. If an adaptive fires,
// last_keycode is then overwritten with the emitted logical output so the next
// adaptive sees what was typed, not the physical substitute key.
// Combo components like KC_C from P=KC_C+KC_X are never recorded — only KC_P is.
static uint16_t prev_keycode = KC_NO;
static uint16_t last_keycode = KC_NO;
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
    last_magic_trigger = KC_NO;
    last_magic_repeat_keycode = KC_NO;
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
                    case KC_B: magic_decode_send_suffix_cycle(MAGIC_STRING_A_C_K_G_R_O_U_N_D, 'd', MAGIC_CYCLE_NONE); /* emits "ackground " -> "background " */ break;
                    case KC_C: magic_tap_repeatable(KC_N); break;
                    case KC_D: magic_tap_repeatable(KC_C); break;
                    case KC_F: magic_replace_decode_send_cap_cycle(MAGIC_STRING_C_O_N_F_U_S_I_N_G, 'g', MAGIC_CYCLE_NONE); /* emits "confusing " */ break;
                    case KC_G: magic_tap_repeatable(KC_T); break;
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
                    case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_C_E_P_T_I_O_N, 'n', MAGIC_CYCLE_NONE); /* emits "exception " */ break;
                default:
                    break;
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
                uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
                switch (magic_context_prepared) {
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
                default:
                    break;
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
                uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
                switch (magic_context_prepared) {
                    case KC_A: magic_decode_send_suffix_cycle(MAGIC_STRING_D_D_R_E_S_S, 's', MAGIC_CYCLE_NONE); /* emits "ddress " -> "address " */ break;
                    case KC_E: magic_tap_repeatable(KC_U); break;
                    case KC_I: magic_decode_send_suffix_cycle(MAGIC_STRING_M_P_L_E_M_E_N_T, 't', MAGIC_STRING_I_M_P_L_E_M_E_N_T); /* emits "mplement " -> "implement " */ break;
                    case KC_O: magic_tap_repeatable(KC_E); break;
                    case KC_SPC: magic_replace_decode_send_cap(MAGIC_STRING_DOT, '\0'); /* emits ". " */ add_oneshot_mods(MOD_BIT(KC_LSFT)); clear_suffix_state(); break;
                    case KC_U: magic_replace_decode_send_cap_cycle(MAGIC_STRING_G_R_E_G_O_R_2, '\0', MAGIC_CYCLE_NONE); /* emits "gregor" */ break;
                    case KC_Y: magic_tap_repeatable(KC_R); break;
                default:
                    break;
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
                uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
                switch (magic_context_prepared) {
                    case KC_B: magic_decode_send_suffix_cycle(MAGIC_STRING_E_C_O_M_E, 'e', MAGIC_CYCLE_NONE); /* emits "ecome " -> "become " */ break;
                    case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_N_APOSTROPHE_T_2, '\0', MAGIC_CYCLE_NONE); /* emits "n't " */ break;
                    case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_O_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "on't " -> "don't " */ break;
                    case KC_F: magic_replace_decode_send_cap_cycle(MAGIC_STRING_P_E_R_F_O_R_M_A_N_C_E, 'e', MAGIC_CYCLE_NONE); /* emits "performance " */ break;
                    case KC_G: magic_replace_decode_send_cap_cycle(MAGIC_STRING_S_U_G_G_E_S_T, 't', MAGIC_CYCLE_NONE); /* emits "suggest " */ break;
                    case KC_K: magic_replace_decode_send_cap_cycle(MAGIC_STRING_T_H_I_N_K, 'k', MAGIC_CYCLE_NONE); /* emits "think " */ break;
                    case KC_L: magic_decode_send_suffix_cycle(MAGIC_STRING_A_N_G_U_A_G_E, 'e', MAGIC_CYCLE_NONE); /* emits "anguage " -> "language " */ break;
                    case KC_M: magic_decode_send_suffix_cycle(MAGIC_STRING_I_G_R_A_T_I_O_N, 'n', MAGIC_CYCLE_NONE); /* emits "igration " -> "migration " */ break;
                    case KC_N: magic_decode_send_suffix_cycle(MAGIC_STRING_E_V_E_R, 'r', MAGIC_CYCLE_NONE); /* emits "ever " -> "never " */ break;
                    case KC_P: magic_decode_send_suffix_cycle(MAGIC_STRING_E_O_P_L_E, 'e', MAGIC_CYCLE_NONE); /* emits "eople " -> "people " */ break;
                    case KC_R: magic_replace_decode_send_cap_cycle(MAGIC_STRING_N_APOSTROPHE_T, '\0', MAGIC_CYCLE_NONE); /* emits "n't" */ break;
                    case KC_S: magic_replace_decode_send_cap_cycle(MAGIC_STRING_P_O_S_S_I_B_L_E, 'e', MAGIC_STRING_P_O_S_S_I_B_L_E); /* emits "possible " */ break;
                    case KC_T: magic_replace_decode_send_cap_cycle(MAGIC_STRING_J_U_S_T, 't', MAGIC_CYCLE_NONE); /* emits "just " */ break;
                    case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_I_M_P_R_O_V_E, 'e', MAGIC_CYCLE_NONE); /* emits "improve " */ break;
                    case KC_W: magic_decode_send_suffix_cycle(MAGIC_STRING_O_R_K, 'k', MAGIC_CYCLE_NONE); /* emits "ork " -> "work " */ break;
                    case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_C_E_P_T, 't', MAGIC_CYCLE_NONE); /* emits "except " */ break;
                default:
                    break;
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
                uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
                switch (magic_context_prepared) {
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
                default:
                    break;
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
                uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
                switch (magic_context_prepared) {
                    case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_V_E, '\0', MAGIC_CYCLE_NONE); /* emits "'ve " */ break;
                    case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_I_F_F_I_C_U_L_T_Y, 'y', MAGIC_CYCLE_NONE); /* emits "ifficulty " -> "difficulty " */ break;
                    case KC_K: magic_replace_decode_send_cap_cycle(MAGIC_STRING_T_H_A_N_K_S, 's', MAGIC_STRING_T_H_A_N_K_S); /* emits "thanks " */ break;
                    case KC_L: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_V_A_I_L_A_B_L_E, 'e', MAGIC_CYCLE_NONE); /* emits "available " */ break;
                    case KC_M: magic_decode_send_suffix_cycle(MAGIC_STRING_I_S_M_A_T_C_H, 'h', MAGIC_CYCLE_NONE); /* emits "ismatch " -> "mismatch " */ break;
                    case KC_N: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_P_L_A_I_N, 'n', MAGIC_CYCLE_NONE); /* emits "explain " */ break;
                    case KC_P: magic_replace_decode_send_cap_cycle(MAGIC_STRING_I_M_P_O_R_T_A_N_T, 't', MAGIC_CYCLE_NONE); /* emits "important " */ break;
                    case KC_R: magic_tap_repeatable(KC_X); break;
                    case KC_S: magic_decode_send_suffix_cycle(MAGIC_STRING_I_M_I_L_A_R, 'r', MAGIC_CYCLE_NONE); /* emits "imilar " -> "similar " */ break;
                    case KC_T: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_N_O_T_H_E_R, 'r', MAGIC_CYCLE_NONE); /* emits "another " */ break;
                    case KC_W: magic_replace_decode_send_cap_cycle(MAGIC_STRING_S_W_I_T_C_H, 'h', MAGIC_CYCLE_NONE); /* emits "switch " */ break;
                    case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_C_L_U_D_E, 'e', MAGIC_CYCLE_NONE); /* emits "exclude " */ break;
                default:
                    break;
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
                uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
                switch (magic_context_prepared) {
                    case KC_A: magic_tap_repeatable(KC_E); break;
                    case KC_E: magic_tap_repeatable(KC_H); break;
                    case KC_H: magic_replace_decode_send_cap_cycle(MAGIC_STRING_Q_U_2, '\0', MAGIC_CYCLE_NONE); /* emits "qu" */ break;
                    case KC_I: magic_decode_send(MAGIC_STRING_M_P_L); /* emits "mpl" -> "impl" */ break;
                    case KC_O: magic_tap_repeatable(KC_H); break;
                    case KC_R: magic_replace_tap_repeatable(KC_EXLM); break;
                    case KC_SPC: magic_replace_tap_repeatable(KC_Z); break;
                    case KC_U: magic_tap_repeatable(KC_H); break;
                    case KC_Y: magic_replace_decode_send_cap_cycle(MAGIC_STRING_O_N_L_Y, 'y', MAGIC_CYCLE_NONE); /* emits "only " */ break;
                default:
                    break;
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
                uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
                switch (magic_context_prepared) {
                    case KC_B: magic_replace_decode_send_cap_cycle(MAGIC_STRING_O_B_S_O_L_E_T_E, 'e', MAGIC_CYCLE_NONE); /* emits "obsolete " */ break;
                    case KC_C: magic_decode_send_suffix_cycle(MAGIC_STRING_O_M_M_E_N_T, 't', MAGIC_CYCLE_NONE); /* emits "omment " -> "comment " */ break;
                    case KC_COMMA: magic_decode_send_cap_cycle(MAGIC_STRING_A_N_D, '\0', MAGIC_CYCLE_NONE); /* emits " and " */ break;
                    case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_I_D_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "idn't " -> "didn't " */ break;
                    case KC_ENT: magic_decode_send_cap_cycle(MAGIC_STRING_A_N_D_2, 'd', MAGIC_CYCLE_NONE); /* emits "and " */ break;
                    case KC_F: magic_decode_send_suffix_cycle(MAGIC_STRING_O_C_U_S_E_D, 'd', MAGIC_CYCLE_NONE); /* emits "ocused " -> "focused " */ break;
                    case KC_G: magic_decode_send_suffix_cycle(MAGIC_STRING_E_N_E_R_A_T_E, 'e', MAGIC_CYCLE_NONE); /* emits "enerate " -> "generate " */ break;
                    case KC_K: magic_replace_decode_send_cap_cycle(MAGIC_STRING_U_P_D_A_T_E, 'e', MAGIC_CYCLE_NONE); /* emits "update " */ break;
                    case KC_L: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_L_A_B_O_R_A_T_E, 'e', MAGIC_CYCLE_NONE); /* emits "elaborate " */ break;
                    case KC_M: magic_replace_decode_send_cap_cycle(MAGIC_STRING_I_N_S_T_R_U_M_E_N_T, 't', MAGIC_STRING_I_N_S_T_R_U_M_E_N_T); /* emits "instrument " */ break;
                    case KC_N: magic_replace_decode_send_cap_cycle(MAGIC_STRING_U_N_D_E_R_S_T_A_N_D, 'd', MAGIC_CYCLE_NONE); /* emits "understand " */ break;
                    case KC_P: magic_decode_send_suffix_cycle(MAGIC_STRING_R_O_D_U_C_T_I_O_N, 'n', MAGIC_CYCLE_NONE); /* emits "roduction " -> "production " */ break;
                    case KC_R: magic_replace_tap_repeatable(KC_QUOTE); break;
                    case KC_S: magic_decode_send_suffix_cycle(MAGIC_STRING_E_P_A_R_A_T_E, 'e', MAGIC_CYCLE_NONE); /* emits "eparate " -> "separate " */ break;
                    case KC_SPC: magic_decode_send_cap_cycle(MAGIC_STRING_A_N_D_2, 'd', MAGIC_CYCLE_NONE); /* emits "and " */ break;
                    case KC_T: magic_decode_send_suffix_cycle(MAGIC_STRING_H_O_U_G_H, 'h', MAGIC_CYCLE_NONE); /* emits "hough " -> "though " */ break;
                    case KC_TAB: magic_decode_send_cap_cycle(MAGIC_STRING_A_N_D_2, 'd', MAGIC_CYCLE_NONE); /* emits "and " */ break;
                    case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_A_P_P_R_O_V_A_L, 'l', MAGIC_CYCLE_NONE); /* emits "approval " */ break;
                    case KC_W: magic_decode_send_suffix_cycle(MAGIC_STRING_H_Y, 'y', MAGIC_CYCLE_NONE); /* emits "hy " -> "why " */ break;
                    case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_I_T, 't', MAGIC_CYCLE_NONE); /* emits "exit " */ break;
                default:
                    break;
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
                uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
                switch (magic_context_prepared) {
                    case KC_B: magic_decode_send_suffix_cycle(MAGIC_STRING_E_C_A_U_S_E, 'e', MAGIC_CYCLE_NONE); /* emits "ecause " -> "because " */ break;
                    case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_R_E, '\0', MAGIC_CYCLE_NONE); /* emits "'re " */ break;
                    case KC_COMMA: magic_decode_send_cap_cycle(MAGIC_STRING_B_U_T, '\0', MAGIC_CYCLE_NONE); /* emits " but " */ break;
                    case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_O_E_S_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "oesn't " -> "doesn't " */ break;
                    case KC_ENT: magic_decode_send_cap_cycle(MAGIC_STRING_T_H_E, 'e', MAGIC_CYCLE_NONE); /* emits "the " */ break;
                    case KC_F: magic_decode_send_suffix_cycle(MAGIC_STRING_O_L_L_O_W_I_N_G, 'g', MAGIC_CYCLE_NONE); /* emits "ollowing " -> "following " */ break;
                    case KC_G: magic_tap_repeatable(KC_K); break;
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
                    case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_R_E_S_O_L_V_E, 'e', MAGIC_CYCLE_NONE); /* emits "resolve " */ break;
                    case KC_W: magic_tap_repeatable(KC_S); break;
                    case KC_X: magic_tap_repeatable(KC_R); break;
                default:
                    break;
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
                uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
                switch (magic_context_prepared) {
                    case KC_B: magic_tap_repeatable(KC_D); break;
                    case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_D, '\0', MAGIC_CYCLE_NONE); /* emits "'d " */ break;
                    case KC_D: magic_tap_repeatable(KC_F); break;
                    case KC_F: magic_tap_repeatable(KC_D); break;
                    case KC_G: magic_tap_repeatable(KC_D); break;
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
                default:
                    break;
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
                uint16_t magic_context_prepared = magic_prepare_last_keycode(context_keycode);
                switch (magic_context_prepared) {
                    case KC_B: magic_decode_send_suffix_cycle(MAGIC_STRING_E_F_O_R_E, 'e', MAGIC_CYCLE_NONE); /* emits "efore " -> "before " */ break;
                    case KC_C: magic_replace_decode_send_cap_cycle(MAGIC_STRING_APOSTROPHE_S, '\0', MAGIC_CYCLE_NONE); /* emits "'s " */ break;
                    case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_O_E_S, 's', MAGIC_CYCLE_NONE); /* emits "oes " -> "does " */ break;
                    case KC_G: magic_decode_send_suffix_cycle(MAGIC_STRING_O_E_S, 's', MAGIC_CYCLE_NONE); /* emits "oes " -> "goes " */ break;
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
                default:
                    break;
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
            case KC_T:
                switch (adaptive_prev_keycode) {
                    case KC_G: return tap_adaptive(KC_T, KC_G);
                    case KC_M: return tap_adaptive(KC_T, KC_B);
                }
                break;
            case KC_R:
                switch (adaptive_prev_keycode) {
                    case KC_K: return tap_adaptive(KC_R, KC_N);
                    case KC_L: return tap_adaptive(KC_R, KC_L);
                    case KC_M: tap_code16(KC_P); return tap_adaptive(KC_R, KC_L);
                    case KC_N: return tap_adaptive(KC_R, KC_G);
                    case KC_S: return tap_adaptive(KC_R, KC_S);
                    case KC_X: return tap_adaptive(KC_R, KC_C);
                    case KC_Y: return tap_adaptive(KC_R, KC_I);
                }
                break;
            case KC_B:
                switch (adaptive_prev_keycode) {
                    case KC_L: return tap_adaptive(KC_B, KC_K);
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
            case KC_O:
                switch (adaptive_prev_keycode) {
                    case KC_O: return tap_adaptive(KC_O, KC_E);
                }
                break;
            case KC_S:
                switch (adaptive_prev_keycode) {
                    case KC_P: return tap_adaptive(KC_S, KC_Y);
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
