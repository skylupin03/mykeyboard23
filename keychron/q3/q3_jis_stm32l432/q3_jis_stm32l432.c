/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

const ckled2001_led PROGMEM g_ckled2001_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, I_1,    G_1,    H_1},  // ESC
    {0, I_2,    G_2,    H_2},  // F1
    {0, I_3,    G_3,    H_3},  // F2
    {0, I_4,    G_4,    H_4},  // F3
    {0, I_5,    G_5,    H_5},  // F4
    {0, I_6,    G_6,    H_6},  // F5
    {0, I_7,    G_7,    H_7},  // F6
    {0, I_8,    G_8,    H_8},  // F7
    {0, I_9,    G_9,    H_9},  // F8
    {0, I_10,   G_10,   H_10}, // F9
    {0, I_11,   G_11,   H_11}, // F10
    {0, I_12,   G_12,   H_12}, // F11
    {0, I_13,   G_13,   H_13}, // F12
    {0, I_15,   G_15,   H_15}, // Print
    {0, I_16,   G_16,   H_16}, // Cortana
    {1, I_15,   G_15,   H_15}, // Light

    {0, C_1,    A_1,    B_1},  // `~
    {0, C_2,    A_2,    B_2},  // 1!
    {0, C_3,    A_3,    B_3},  // 2@
    {0, C_4,    A_4,    B_4},  // 3#
    {0, C_5,    A_5,    B_5},  // 4$
    {0, C_6,    A_6,    B_6},  // 5%
    {0, C_7,    A_7,    B_7},  // 6^
    {0, C_8,    A_8,    B_8},  // 7&
    {0, C_9,    A_9,    B_9},  // 8*
    {0, C_10,   A_10,   B_10}, // 9()
    {0, C_11,   A_11,   B_11}, // 0)
    {0, C_12,   A_12,   B_12}, // -_
    {0, C_13,   A_13,   B_13}, // =+
    {0, I_13,   G_13,   H_13}, // |
    {0, I_14,   G_14,   H_14}, // Backspace
    {0, C_15,   A_15,   B_15}, // Ins
    {0, C_16,   A_16,   B_16}, // Home
    {1, I_16,   G_16,   H_16}, // Page Up

    {0, F_1,    D_1,    E_1},  // tab
    {0, F_2,    D_2,    E_2},  // Q
    {0, F_3,    D_3,    E_3},  // W
    {0, F_4,    D_4,    E_4},  // E
    {0, F_5,    D_5,    E_5},  // R
    {0, F_6,    D_6,    E_6},  // T
    {0, F_7,    D_7,    E_7},  // Y
    {0, F_8,    D_8,    E_8},  // U
    {0, F_9,    D_9,    E_9},  // I
    {0, F_10,   D_10,   E_10}, // O
    {0, F_11,   D_11,   E_11}, // P
    {0, F_12,   D_12,   E_12}, // [{
    {0, F_14,   D_14,   E_14}, // }}
    {0, F_15,   D_15,   E_15}, // Del
    {0, F_16,   D_16,   E_16}, // End
    {1, I_13,   G_13,   H_13}, // Page Down

    {1, I_1,    G_1,    H_1},  // Cpas
    {1, I_2,    G_2,    H_2},  // A
    {1, I_3,    G_3,    H_3},  // S
    {1, I_4,    G_4,    H_4},  // D
    {1, I_5,    G_5,    H_5},  // F
    {1, I_6,    G_6,    H_6},  // G
    {1, I_7,    G_7,    H_7},  // H
    {1, I_8,    G_8,    H_8},  // J
    {1, I_9,    G_9,    H_9},  // K
    {1, I_10,   G_10,   H_10}, // L
    {1, I_11,   G_11,   H_11}, // ;
    {1, I_12,   G_12,   H_12}, // :
    {1, I_14,   G_14,   H_14}, // #~
    {0, F_13,   D_13,   E_13}, // Enter

    {1, C_1,    A_1,    B_1},  // LShift
    {1, C_3,    A_3,    B_3},  // Z
    {1, C_4,    A_4,    B_4},  // X
    {1, C_5,    A_5,    B_5},  // C
    {1, C_6,    A_6,    B_6},  // V
    {1, C_7,    A_7,    B_7},  // B
    {1, C_8,    A_8,    B_8},  // N
    {1, C_9,    A_9,    B_9},  // M
    {1, C_10,   A_10,   B_10}, // ,<
    {1, C_11,   A_11,   B_11}, // .>
    {1, C_12,   A_12,   B_12}, // /?
    {1, C_13,   A_13,   B_13}, // |
    {1, C_14,   A_14,   B_14}, // RShift
    {1, C_16,   A_16,   B_16}, // Up

    {1, F_1,    D_1,    E_1},  // LCtrl
    {1, F_2,    D_2,    E_2},  // LWin
    {1, F_3,    D_3,    E_3},  // LAlt
    {1, F_4,    D_4,    E_4},  // NUm
    {1, F_7,    D_7,    E_7},  // Space
    {1, F_10,   D_10,   E_10}, // Jap
    {1, F_11,   D_11,   E_11}, // RAlt
    {1, F_12,   D_12,   E_12}, // RWin
    {1, F_13,   D_13,   E_13}, // Fn
    {1, F_14,   D_14,   E_14}, // RCtrl
    {1, F_15,   D_15,   E_15}, // Left
    {1, F_16,   D_16,   E_16}, // Down
    {1, C_15,   A_15,   B_15}, // Right
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 30, 13, 14 },
        { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 31, 32 },
        { 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 63, 47, 48 },
        { 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 49, 62, 15, 33 },
        { 64, __, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 90, 77 },
        { 78, 79, 80, 81, __, __, 82, __, __, 83, 84, 85, 86, 87, 88, 89 },
    },
    {
        // LED Index to Physical Position
        {0,0},           {26,0},  {39,0},  {52,0},  {65,0},  {84,0},  {97,0},   {111,0},  {124,0},  {143,0},  {156,0},  {169,0},  {182,0},            {198,0},  {211,0},  {224,0},
        {0,15}, {13,15}, {26,15}, {39,15}, {52,15}, {65,15}, {78,15}, {91,15},  {104,15}, {117,15}, {130,15}, {143,15}, {156,15}, {169,15}, {182,15}, {198,15}, {211,15}, {224,15},
        {3,28}, {19,28}, {32,28}, {45,28}, {59,28}, {72,28}, {85,28}, {98,28},  {111,28}, {124,28}, {137,28}, {150,28}, {163,28},                     {198,28}, {211,28}, {224,28},
        {5,40}, {23,40}, {36,40}, {49,40}, {62,40}, {75,40}, {88,40}, {101,40}, {114,40}, {127,40}, {140,40}, {153,40}, {166,40}, {183,36},
        {8,52},          {29,52}, {42,52}, {55,52}, {68,52}, {81,52}, {94,52},  {107,52}, {120,52}, {133,52}, {146,52}, {159,52}, {177,52},                     {211,52},
        {2,64}, {16,64}, {31,64}, {45,64},                   {81,64},                     {119,64}, {135,64}, {151,64}, {166,64}, {180,64},           {198,64}, {211,64}, {224,64}
    },
    {
        // RGB LED Index to Flag
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,       1, 1, 1,
        9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,       1,
        1, 1, 1, 1,       4,       1, 1, 1, 1, 1,    1, 1, 1,
    }
};

#endif // GB_MATRIX_ENABLE