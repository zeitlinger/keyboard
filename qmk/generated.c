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
#define MAGIC_STRING_A_C_K_G_R_O_U_N_D 62
#define MAGIC_STRING_A_D_D_R_E_S_S 71
#define MAGIC_STRING_A_L_I_D_A_T_E 78
#define MAGIC_STRING_A_L_R_E_A_D_Y 84
#define MAGIC_STRING_A_L_W_A_Y_S 91
#define MAGIC_STRING_A_N_D 0
#define MAGIC_STRING_A_N_D_2 97
#define MAGIC_STRING_A_N_G_U_A_G_E 101
#define MAGIC_STRING_A_N_O_T_H_E_R 106
#define MAGIC_STRING_A_N_Y_T_H_I_N_G 111
#define MAGIC_STRING_A_P_P_R_O_V_A_L 117
#define MAGIC_STRING_A_S_I_C_A_L_L_Y 125
#define MAGIC_STRING_A_S_N_APOSTROPHE_T 133
#define MAGIC_STRING_A_V_A_I_L_A_B_L_E 138
#define MAGIC_STRING_B_A_C_K_G_R_O_U_N_D 146
#define MAGIC_STRING_B_A_S_I_C_A_L_L_Y 156
#define MAGIC_STRING_B_E_C_A_U_S_E 165
#define MAGIC_STRING_B_E_C_O_M_E 172
#define MAGIC_STRING_B_E_F_O_R_E 178
#define MAGIC_STRING_B_U_T 5
#define MAGIC_STRING_C_H_A_N_G_E 184
#define MAGIC_STRING_C_O_M_M_E_N_T 189
#define MAGIC_STRING_C_O_N_F_L_I_C_T 195
#define MAGIC_STRING_C_O_N_F_U_S_I_N_G 202
#define MAGIC_STRING_DOT 29
#define MAGIC_STRING_D_D_R_E_S_S 209
#define MAGIC_STRING_D_I_D_N_APOSTROPHE_T 215
#define MAGIC_STRING_D_I_F_F_I_C_U_L_T_Y 222
#define MAGIC_STRING_D_I_S_A_B_L_E 233
#define MAGIC_STRING_D_O_E_S 240
#define MAGIC_STRING_D_O_E_S_N_APOSTROPHE_T 244
#define MAGIC_STRING_D_O_N_APOSTROPHE_T 250
#define MAGIC_STRING_E_C_A_U_S_E 255
#define MAGIC_STRING_E_C_O_M_E 261
#define MAGIC_STRING_E_F_O_R_E 266
#define MAGIC_STRING_E_L_A_B_O_R_A_T_E 271
#define MAGIC_STRING_E_N_A_B_L_E 278
#define MAGIC_STRING_E_N_E_R_A_T_E 284
#define MAGIC_STRING_E_N_T 289
#define MAGIC_STRING_E_O_P_L_E 292
#define MAGIC_STRING_E_P_A_R_A_T_E 297
#define MAGIC_STRING_E_R_S_I_O_N 303
#define MAGIC_STRING_E_V_E_R 308
#define MAGIC_STRING_E_V_E_R_Y_T_H_I_N_G 313
#define MAGIC_STRING_E_X_A_M_P_L_E 321
#define MAGIC_STRING_E_X_C_E_P_T 328
#define MAGIC_STRING_E_X_C_E_P_T_I_O_N 335
#define MAGIC_STRING_E_X_C_L_U_D_E 344
#define MAGIC_STRING_E_X_I_T 351
#define MAGIC_STRING_E_X_P_L_A_I_N 356
#define MAGIC_STRING_E_X_P_L_I_C_I_T 363
#define MAGIC_STRING_F_O_C_U_S_E_D 371
#define MAGIC_STRING_F_O_L_L_O_W_I_N_G 379
#define MAGIC_STRING_G_E_N_E_R_A_T_E 386
#define MAGIC_STRING_G_O_E_S 392
#define MAGIC_STRING_G_R_E_G_O_R 32
#define MAGIC_STRING_G_R_E_G_O_R_2 396
#define MAGIC_STRING_H_I_C_H 400
#define MAGIC_STRING_H_O_U_G_H 404
#define MAGIC_STRING_H_O_U_G_H_T 408
#define MAGIC_STRING_H_R_O_U_G_H 413
#define MAGIC_STRING_H_Y 418
#define MAGIC_STRING_I_APOSTROPHE_V_E 37
#define MAGIC_STRING_I_D_N_APOSTROPHE_T 422
#define MAGIC_STRING_I_F_F_I_C_U_L_T_Y 428
#define MAGIC_STRING_I_G_R_A_T_I_O_N 438
#define MAGIC_STRING_I_M_I_L_A_R 444
#define MAGIC_STRING_I_M_P_L 449
#define MAGIC_STRING_I_M_P_L_E_M_E_N_T 453
#define MAGIC_STRING_I_M_P_L_E_M_E_N_T_A_T_I_O_N 460
#define MAGIC_STRING_I_M_P_O_R_T_A_N_T 469
#define MAGIC_STRING_I_M_P_O_S_S_I_B_L_E 476
#define MAGIC_STRING_I_M_P_R_O_V_E 484
#define MAGIC_STRING_I_N_S_T_R_U_M_E_N_T 490
#define MAGIC_STRING_I_N_S_T_R_U_M_E_N_T_A_T_I_O_N 497
#define MAGIC_STRING_I_O_N 506
#define MAGIC_STRING_I_S_A_B_L_E 509
#define MAGIC_STRING_I_S_M_A_T_C_H 515
#define MAGIC_STRING_J_U_S_T 521
#define MAGIC_STRING_K_N_E_W 525
#define MAGIC_STRING_K_N_O_W 530
#define MAGIC_STRING_L_A_N_G_U_A_G_E 535
#define MAGIC_STRING_L_G_T_M 42
#define MAGIC_STRING_M_E_N_T 541
#define MAGIC_STRING_M_E_R_G_E_D 544
#define MAGIC_STRING_M_I_G_R_A_T_I_O_N 550
#define MAGIC_STRING_M_I_S_M_A_T_C_H 556
#define MAGIC_STRING_M_P_L 562
#define MAGIC_STRING_M_P_L_E_M_E_N_T 566
#define MAGIC_STRING_M_U_L_T_I_P_L_E 573
#define MAGIC_STRING_N_APOSTROPHE_T 580
#define MAGIC_STRING_N_APOSTROPHE_T_2 584
#define MAGIC_STRING_N_E_V_E_R 588
#define MAGIC_STRING_N_E_W 593
#define MAGIC_STRING_N_O_W 597
#define MAGIC_STRING_O_B_S_E_R_V_A_B_I_L_I_T_Y 601
#define MAGIC_STRING_O_B_S_O_L_E_T_E 613
#define MAGIC_STRING_O_C_U_S_E_D 620
#define MAGIC_STRING_O_E_S 627
#define MAGIC_STRING_O_E_S_N_APOSTROPHE_T 630
#define MAGIC_STRING_O_L_L_O_W_I_N_G 635
#define MAGIC_STRING_O_M_E_O_N_E 641
#define MAGIC_STRING_O_M_E_T_H_I_N_G 646
#define MAGIC_STRING_O_M_M_E_N_T 652
#define MAGIC_STRING_O_N_APOSTROPHE_T 657
#define MAGIC_STRING_O_N_L_Y 661
#define MAGIC_STRING_O_R_K_F_L_O_W 666
#define MAGIC_STRING_O_T_H_E_R_W_I_S_E 673
#define MAGIC_STRING_P_E_O_P_L_E 680
#define MAGIC_STRING_P_E_R_F_O_R_M_A_N_C_E 686
#define MAGIC_STRING_P_O_S_S_I_B_L_E 695
#define MAGIC_STRING_P_R_O_B_A_B_L_Y 702
#define MAGIC_STRING_P_R_O_D_U_C_T_I_O_N 711
#define MAGIC_STRING_P_R_O_M_E_T_H_E_U_S 48
#define MAGIC_STRING_Q_U 720
#define MAGIC_STRING_Q_U_E_S_T_I_O_N 723
#define MAGIC_STRING_R_E_S_O_L_V_E 729
#define MAGIC_STRING_R_O_B_A_B_L_Y 735
#define MAGIC_STRING_R_O_D_U_C_T_I_O_N 743
#define MAGIC_STRING_S_E_P_A_R_A_T_E 751
#define MAGIC_STRING_S_I_M_I_L_A_R 757
#define MAGIC_STRING_S_I_O_N 762
#define MAGIC_STRING_S_O_M_E_O_N_E 765
#define MAGIC_STRING_S_O_M_E_T_H_I_N_G 770
#define MAGIC_STRING_S_U_G_G_E_S_T 776
#define MAGIC_STRING_S_U_P_P_O_R_T 781
#define MAGIC_STRING_S_W_I_T_C_H 787
#define MAGIC_STRING_T_A_S_K 793
#define MAGIC_STRING_T_H_A_N_K_S 806
#define MAGIC_STRING_T_H_A_N_K_Y_O_U 798
#define MAGIC_STRING_T_H_E 811
#define MAGIC_STRING_T_H_I_N_K 814
#define MAGIC_STRING_T_H_O_U_G_H 819
#define MAGIC_STRING_T_H_O_U_G_H_T 824
#define MAGIC_STRING_T_H_R_O_U_G_H 829
#define MAGIC_STRING_T_I_O_N 834
#define MAGIC_STRING_U_L_T_I_P_L_E 837
#define MAGIC_STRING_U_N_D_E_R_S_T_A_N_D 843
#define MAGIC_STRING_U_P_D_A_T_E 851
#define MAGIC_STRING_U_P_P_O_R_T 857
#define MAGIC_STRING_V_A_L_I_D_A_T_E 863
#define MAGIC_STRING_V_A_L_I_D_A_T_I_O_N 870
#define MAGIC_STRING_V_E_R_S_I_O_N 878
#define MAGIC_STRING_W_A_S_N_APOSTROPHE_T 884
#define MAGIC_STRING_W_H_I_C_H 890
#define MAGIC_STRING_W_H_Y 895
#define MAGIC_STRING_W_I_T_H_O_U_T 900
#define MAGIC_STRING_W_O_N_APOSTROPHE_T 906
#define MAGIC_STRING_W_O_R_K_F_L_O_W 911
#define MAGIC_STRING_W_O_R_S_E 919
#define MAGIC_STRING_Z_E_I_T_L_I_N_G_E_R 55

static const char magic_char_4bit[] = {
    ' ', 'e', 'o', 't', 'n', 'i', 'a', 'l', 'r', 's', 'u', 'm', 'h', 'g'
};

static const char magic_char_extended[] = {
    'p', 'd', 'c', 'b', 'w', '\'', 'y', 'f', 'v', 'k', 'x', 'G', 'q', '.', 'I', 'L', 'M', 'P', 'T', 'Z', 'j'
};

static const uint8_t magic_string_data[] = {
    0x05, 0x06, 0x4f, 0xe1, 0x00, 0x05, 0x0f, 0xe3, 0xa3, 0x00, 0x03, 0xe5, 0xe1, 0x00, 0x04, 0xe5,
    0x77, 0x00, 0x04, 0xe5, 0x81, 0x00, 0x03, 0xe5, 0x90, 0x04, 0xe5, 0xe8, 0x10, 0x02, 0xed, 0x00,
    0x07, 0xeb, 0x81, 0xd2, 0x80, 0x05, 0xee, 0xe5, 0xe8, 0x10, 0x05, 0xef, 0xeb, 0xf2, 0xf0, 0x00,
    0x0b, 0xf1, 0x82, 0xb1, 0x3c, 0x1a, 0x90, 0x0b, 0xf3, 0x15, 0x37, 0x54, 0xd1, 0x80, 0x0a, 0x6f,
    0xe2, 0xe9, 0xd8, 0x2a, 0x4f, 0xe1, 0x00, 0x08, 0x6f, 0xe1, 0xe1, 0x81, 0x99, 0x00, 0x08, 0x67,
    0x5f, 0xe1, 0x63, 0x10, 0x08, 0x67, 0x81, 0x6f, 0xe1, 0xe6, 0x00, 0x07, 0x67, 0xe4, 0x6f, 0xe6,
    0x90, 0x04, 0x64, 0xe1, 0x00, 0x08, 0x64, 0xda, 0x6d, 0x10, 0x08, 0x64, 0x23, 0xc1, 0x80, 0x09,
    0x64, 0xe6, 0x3c, 0x54, 0xd0, 0x09, 0x6f, 0xe0, 0xe0, 0x82, 0xe8, 0x67, 0x00, 0x09, 0x69, 0x5f,
    0xe2, 0x67, 0x7f, 0xe6, 0x00, 0x06, 0x69, 0x4f, 0xe5, 0x30, 0x0a, 0x6f, 0xe8, 0x65, 0x76, 0xe3,
    0x71, 0x00, 0x0b, 0xe3, 0x6f, 0xe2, 0xe9, 0xd8, 0x2a, 0x4f, 0xe1, 0x00, 0x0a, 0xe3, 0x69, 0x5f,
    0xe2, 0x67, 0x7f, 0xe6, 0x00, 0x08, 0xe3, 0x1f, 0xe2, 0x6a, 0x91, 0x00, 0x07, 0xe3, 0x1f, 0xe2,
    0x2b, 0x10, 0x07, 0xe3, 0x1f, 0xe7, 0x28, 0x10, 0x07, 0xe2, 0xc6, 0x4d, 0x10, 0x08, 0xe2, 0x2b,
    0xb1, 0x43, 0x00, 0x09, 0xe2, 0x24, 0xe7, 0x75, 0xe2, 0x30, 0x0a, 0xe2, 0x24, 0xe7, 0xa9, 0x54,
    0xd0, 0x07, 0xe1, 0xe1, 0x81, 0x99, 0x00, 0x07, 0xe1, 0x5f, 0xe1, 0x4f, 0xe5, 0x30, 0x0b, 0xe1,
    0x5f, 0xe7, 0xe7, 0x5f, 0xe2, 0xa7, 0x3f, 0xe6, 0x00, 0x08, 0xe1, 0x59, 0x6f, 0xe3, 0x71, 0x00,
    0x05, 0xe1, 0x21, 0x90, 0x08, 0xe1, 0x21, 0x94, 0xe5, 0x30, 0x06, 0xe1, 0x24, 0xe5, 0x30, 0x07,
    0x1f, 0xe2, 0x6a, 0x91, 0x00, 0x06, 0x1f, 0xe2, 0x2b, 0x10, 0x06, 0x1f, 0xe7, 0x28, 0x10, 0x0a,
    0x17, 0x6f, 0xe3, 0x28, 0x63, 0x10, 0x07, 0x14, 0x6f, 0xe3, 0x71, 0x00, 0x08, 0x14, 0x18, 0x63,
    0x10, 0x03, 0x14, 0x30, 0x06, 0x12, 0xe0, 0x71, 0x00, 0x08, 0x1f, 0xe0, 0x68, 0x63, 0x10, 0x07,
    0x18, 0x95, 0x24, 0x00, 0x05, 0x1f, 0xe8, 0x18, 0x00, 0x0b, 0x1f, 0xe8, 0x18, 0xe6, 0x3c, 0x54,
    0xd0, 0x08, 0x1f, 0xea, 0x6b, 0xe0, 0x71, 0x00, 0x07, 0x1f, 0xea, 0xe2, 0x1f, 0xe0, 0x30, 0x0a,
    0x1f, 0xea, 0xe2, 0x1f, 0xe0, 0x35, 0x24, 0x00, 0x08, 0x1f, 0xea, 0xe2, 0x7a, 0xe1, 0x10, 0x05,
    0x1f, 0xea, 0x53, 0x00, 0x08, 0x1f, 0xea, 0xe0, 0x76, 0x54, 0x00, 0x09, 0x1f, 0xea, 0xe0, 0x75,
    0xe2, 0x53, 0x00, 0x08, 0xe7, 0x2f, 0xe2, 0xa9, 0x1f, 0xe1, 0x00, 0x0a, 0xe7, 0x27, 0x72, 0xe4,
    0x54, 0xd0, 0x09, 0xd1, 0x41, 0x86, 0x31, 0x00, 0x05, 0xd2, 0x19, 0x00, 0x06, 0xd8, 0x1d, 0x28,
    0x05, 0xc5, 0xe2, 0xc0, 0x06, 0xc2, 0xad, 0xc0, 0x07, 0xc2, 0xad, 0xc3, 0x00, 0x07, 0xc8, 0x2a,
    0xdc, 0x00, 0x03, 0xcf, 0xe6, 0x00, 0x06, 0x5f, 0xe1, 0x4f, 0xe5, 0x30, 0x0a, 0x5f, 0xe7, 0xe7,
    0x5f, 0xe2, 0xa7, 0x3f, 0xe6, 0x00, 0x09, 0x5d, 0x86, 0x35, 0x24, 0x00, 0x07, 0x5b, 0x57, 0x68,
    0x00, 0x04, 0x5b, 0xe0, 0x70, 0x0a, 0x5b, 0xe0, 0x71, 0xb1, 0x43, 0x00, 0x0f, 0x5b, 0xe0, 0x71,
    0xb1, 0x43, 0x63, 0x52, 0x40, 0x0a, 0x5b, 0xe0, 0x28, 0x36, 0x43, 0x00, 0x0b, 0x5b, 0xe0, 0x29,
    0x95, 0xe3, 0x71, 0x00, 0x08, 0x5b, 0xe0, 0x82, 0xe8, 0x10, 0x0b, 0x54, 0x93, 0x8a, 0xb1, 0x43,
    0x00, 0x10, 0x54, 0x93, 0x8a, 0xb1, 0x43, 0x63, 0x52, 0x40, 0x03, 0x52, 0x40, 0x07, 0x59, 0x6f,
    0xe3, 0x71, 0x00, 0x08, 0x59, 0xb6, 0x3f, 0xe2, 0xc0, 0x05, 0xf4, 0xa9, 0x30, 0x05, 0xe9, 0x41,
    0xe4, 0x00, 0x05, 0xe9, 0x42, 0xe4, 0x00, 0x09, 0x76, 0x4d, 0xa6, 0xd1, 0x00, 0x04, 0xb1, 0x43,
    0x07, 0xb1, 0x8d, 0x1f, 0xe1, 0x00, 0x0a, 0xb5, 0xd8, 0x63, 0x52, 0x40, 0x09, 0xb5, 0x9b, 0x63,
    0xe2, 0xc0, 0x03, 0xbf, 0xe0, 0x70, 0x09, 0xbf, 0xe0, 0x71, 0xb1, 0x43, 0x00, 0x09, 0xba, 0x73,
    0x5f, 0xe0, 0x71, 0x00, 0x03, 0x4f, 0xe5, 0x30, 0x04, 0x4f, 0xe5, 0x30, 0x06, 0x41, 0xe8, 0x18,
    0x00, 0x04, 0x41, 0xe4, 0x00, 0x04, 0x42, 0xe4, 0x00, 0x0e, 0x2f, 0xe3, 0x91, 0x8f, 0xe8, 0x6f,
    0xe3, 0x57, 0x53, 0xe6, 0x00, 0x09, 0x2f, 0xe3, 0x92, 0x71, 0x31, 0x00, 0x07, 0x2f, 0xe2, 0xa9,
    0x1f, 0xe1, 0x00, 0x04, 0x21, 0x90, 0x07, 0x21, 0x94, 0xe5, 0x30, 0x09, 0x27, 0x72, 0xe4, 0x54,
    0xd0, 0x07, 0x2b, 0x12, 0x41, 0x00, 0x09, 0x2b, 0x13, 0xc5, 0x4d, 0x00, 0x07, 0x2b, 0xb1, 0x43,
    0x00, 0x05, 0x24, 0xe5, 0x30, 0x05, 0x24, 0x7f, 0xe6, 0x00, 0x08, 0x28, 0xe9, 0xe7, 0x72, 0xe4,
    0x00, 0x0a, 0x23, 0xc1, 0x8f, 0xe4, 0x59, 0x10, 0x07, 0xe0, 0x12, 0xe0, 0x71, 0x00, 0x0c, 0xe0,
    0x18, 0xe7, 0x28, 0xb6, 0x4f, 0xe2, 0x10, 0x09, 0xe0, 0x29, 0x95, 0xe3, 0x71, 0x00, 0x09, 0xe0,
    0x82, 0xe3, 0x6f, 0xe3, 0x7f, 0xe6, 0x00, 0x0b, 0xe0, 0x82, 0xe1, 0xaf, 0xe2, 0x35, 0x24, 0x00,
    0x02, 0xec, 0xa0, 0x09, 0xec, 0xa1, 0x93, 0x52, 0x40, 0x08, 0x81, 0x92, 0x7f, 0xe8, 0x10, 0x08,
    0x82, 0xe3, 0x6f, 0xe3, 0x7f, 0xe6, 0x00, 0x0a, 0x82, 0xe1, 0xaf, 0xe2, 0x35, 0x24, 0x00, 0x09,
    0x91, 0xe0, 0x68, 0x63, 0x10, 0x08, 0x95, 0xb5, 0x76, 0x80, 0x04, 0x95, 0x24, 0x08, 0x92, 0xb1,
    0x24, 0x10, 0x0a, 0x92, 0xb1, 0x3c, 0x54, 0xd0, 0x08, 0x9a, 0xdd, 0x19, 0x30, 0x08, 0x9a, 0xe0,
    0xe0, 0x28, 0x30, 0x07, 0x9f, 0xe4, 0x53, 0xe2, 0xc0, 0x05, 0x36, 0x9f, 0xe9, 0x00, 0x0a, 0x3c,
    0x64, 0xe9, 0x0f, 0xe6, 0x2a, 0x00, 0x07, 0x3c, 0x64, 0xe9, 0x90, 0x04, 0x3c, 0x10, 0x06, 0x3c,
    0x54, 0xe9, 0x00, 0x07, 0x3c, 0x2a, 0xdc, 0x00, 0x08, 0x3c, 0x2a, 0xdc, 0x30, 0x08, 0x3c, 0x82,
    0xad, 0xc0, 0x04, 0x35, 0x24, 0x08, 0xa7, 0x35, 0xe0, 0x71, 0x00, 0x0b, 0xa4, 0xe1, 0x18, 0x93,
    0x64, 0xe1, 0x00, 0x07, 0xaf, 0xe0, 0xe1, 0x63, 0x10, 0x07, 0xaf, 0xe0, 0xe0, 0x28, 0x30, 0x09,
    0xe8, 0x67, 0x5f, 0xe1, 0x63, 0x10, 0x0b, 0xe8, 0x67, 0x5f, 0xe1, 0x63, 0x52, 0x40, 0x08, 0xe8,
    0x18, 0x95, 0x24, 0x00, 0x07, 0xe4, 0x69, 0x4f, 0xe5, 0x30, 0x06, 0xe4, 0xc5, 0xe2, 0xc0, 0x04,
    0xe4, 0xcf, 0xe6, 0x00, 0x08, 0xe4, 0x53, 0xc2, 0xa3, 0x00, 0x06, 0xe4, 0x24, 0xe5, 0x30, 0x09,
    0xe4, 0x28, 0xe9, 0xe7, 0x72, 0xe4, 0x00, 0x06, 0xe4, 0x28, 0x91, 0x00
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
// Updated from the real trigger keycode, not the emitted adaptive/magic output,
// so context-sensitive logic can see through substitutions.
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
                case KC_U: magic_replace_decode_send_cap_cycle(MAGIC_STRING_G_R_E_G_O_R_2, '\0', MAGIC_CYCLE_NONE); /* emits "gregor" */ break;
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
                case KC_G: magic_decode_send_suffix_cycle(MAGIC_STRING_O_E_S, 's', MAGIC_CYCLE_NONE); /* emits "oes " -> "goes " */ break;
                case KC_K: magic_replace_decode_send_cap_cycle(MAGIC_STRING_T_H_I_N_K, 'k', MAGIC_CYCLE_NONE); /* emits "think " */ break;
                case KC_L: magic_decode_send_suffix_cycle(MAGIC_STRING_A_N_G_U_A_G_E, 'e', MAGIC_CYCLE_NONE); /* emits "anguage " -> "language " */ break;
                case KC_M: magic_decode_send_suffix_cycle(MAGIC_STRING_I_G_R_A_T_I_O_N, 'n', MAGIC_CYCLE_NONE); /* emits "igration " -> "migration " */ break;
                case KC_N: magic_decode_send_suffix_cycle(MAGIC_STRING_E_V_E_R, 'r', MAGIC_CYCLE_NONE); /* emits "ever " -> "never " */ break;
                case KC_P: magic_decode_send_suffix_cycle(MAGIC_STRING_E_O_P_L_E, 'e', MAGIC_CYCLE_NONE); /* emits "eople " -> "people " */ break;
                case KC_R: magic_replace_decode_send_cap_cycle(MAGIC_STRING_N_APOSTROPHE_T, '\0', MAGIC_CYCLE_NONE); /* emits "n't" */ break;
                case KC_S: magic_replace_decode_send_cap_cycle(MAGIC_STRING_P_O_S_S_I_B_L_E, 'e', MAGIC_STRING_P_O_S_S_I_B_L_E); /* emits "possible " */ break;
                case KC_T: magic_replace_decode_send_cap_cycle(MAGIC_STRING_J_U_S_T, 't', MAGIC_CYCLE_NONE); /* emits "just " */ break;
                case KC_V: magic_replace_decode_send_cap_cycle(MAGIC_STRING_I_M_P_R_O_V_E, 'e', MAGIC_CYCLE_NONE); /* emits "improve " */ break;
                case KC_W: magic_decode_send_suffix_cycle(MAGIC_STRING_O_R_K_F_L_O_W, 'w', MAGIC_CYCLE_NONE); /* emits "orkflow " -> "workflow " */ break;
                case KC_X: magic_replace_decode_send_cap_cycle(MAGIC_STRING_E_X_C_E_P_T, 't', MAGIC_CYCLE_NONE); /* emits "except " */ break;
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
                case KC_B: magic_replace_decode_send_cap_cycle(MAGIC_STRING_O_B_S_O_L_E_T_E, 'e', MAGIC_CYCLE_NONE); /* emits "obsolete " */ break;
                case KC_C: magic_decode_send_suffix_cycle(MAGIC_STRING_O_M_M_E_N_T, 't', MAGIC_CYCLE_NONE); /* emits "omment " -> "comment " */ break;
                case KC_COMMA: magic_decode_send_cap_cycle(MAGIC_STRING_A_N_D, '\0', MAGIC_CYCLE_NONE); /* emits " and " */ break;
                case KC_D: magic_decode_send_suffix_cycle(MAGIC_STRING_I_D_N_APOSTROPHE_T, 't', MAGIC_CYCLE_NONE); /* emits "idn't " -> "didn't " */ break;
                case KC_E: magic_replace_decode_send_cap_cycle(MAGIC_STRING_L_G_T_M, 'M', MAGIC_CYCLE_NONE); /* emits "LGTM " */ break;
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
            case KC_S:
                switch (adaptive_prev_keycode) {
                    case KC_P: return tap_adaptive(KC_S, KC_Y);
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
