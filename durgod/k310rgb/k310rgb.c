/* Copyright 2021 kuenhlee, Don Kjer, Tyler Tidman
 * Copyright 2021 Simon Arlott
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
//#include "quantum.h"

#include "k310rgb.h"
#include <ch.h>
#include <hal.h>

//#include <math.h>
//#include "print.h"

// #ifdef DYNAMIC_MACRO_ENABLE
// static bool is_dynamic_recording = false;

// void dynamic_macro_record_start_user(void) { is_dynamic_recording = true; }

// void dynamic_macro_record_end_user(int8_t direction) {
//     is_dynamic_recording = false;
// }
// #endif




// #ifdef DYNAMIC_MACRO_ENABLE
//     if (is_dynamic_recording) {
//         writePinLow(LED_MR_LOCK_PIN);
//         wait_ms(100);
//        writePinHigh(LED_MR_LOCK_PIN);
//         wait_ms(155);
//     }
// #endif




/* Private Functions */
void off_all_leds(void) {
#ifdef LED_NUM_LOCK_PIN
    writePinHigh(LED_NUM_LOCK_PIN);
#endif
    writePinHigh(LED_CAPS_LOCK_PIN);
    writePinHigh(LED_SCROLL_LOCK_PIN);
    writePinHigh(LED_WIN_LOCK_PIN);
    writePinHigh(LED_MR_LOCK_PIN);
}

void on_all_leds(void) {
#ifdef LED_NUM_LOCK_PIN
    writePinLow(LED_NUM_LOCK_PIN);
#endif
    writePinLow(LED_CAPS_LOCK_PIN);
    writePinLow(LED_SCROLL_LOCK_PIN);
    writePinLow(LED_WIN_LOCK_PIN);
    writePinLow(LED_MR_LOCK_PIN);
}

void off_mr_leds(void) {
    writePinHigh(LED_MR_LOCK_PIN);
}
void on_mr_leds(void) {
    writePinLow(LED_MR_LOCK_PIN);
}

/* WinLock and MR LEDs are non-standard. Need to override led init */
void led_init_ports(void) {
#ifdef LED_NUM_LOCK_PIN
    setPinOutput(LED_NUM_LOCK_PIN);
#endif
    setPinOutput(LED_CAPS_LOCK_PIN);
    setPinOutput(LED_SCROLL_LOCK_PIN);
    setPinOutput(LED_WIN_LOCK_PIN);
    setPinOutput(LED_MR_LOCK_PIN);
    off_all_leds();
}

#ifndef WINLOCK_DISABLED
static bool win_key_locked = false;
//extern static bool win_key_locked;

// static bool all_key_locked = false;

static uint8_t mac_keycode[4] = {KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD};

typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[2];
} key_combination_t;

key_combination_t key_comb_list[2] = {
    {2, {KC_LWIN, KC_TAB}},
    {2, {KC_LWIN, KC_E}}
};

#define HCS(report) host_consumer_send(record->event.pressed ? report : 0); return false
#define HSS(report) host_system_send(record->event.pressed ? report : 0); return false

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

//    if (get_autoshift_state()) writePinLow(LED_MR_LOCK_PIN);
//    else writePinHigh(LED_MR_LOCK_PIN);
//    writePin(LED_MR_LOCK_PIN, !get_autoshift_state());

    switch (keycode) {
        case KC_TGUI:
            if (record->event.pressed) { // Toggle GUI lock on key press
                win_key_locked = !win_key_locked;
                writePin(LED_WIN_LOCK_PIN, !win_key_locked);
            }
            break;
            
        case OSM(MOD_LGUI):
        case KC_LGUI:
            if (win_key_locked) { return false; }
            break;

#ifdef LED_MATRIX_ENABLE
        case KC_STER:
            if (record->event.pressed) {  led_matrix_step_reverse(); }
            break;
        case KC_SPDI:
            if (record->event.pressed) {  led_matrix_increase_speed(); }
            break;
        case KC_SPDD:
            if (record->event.pressed) {  led_matrix_decrease_speed(); }
            break;
#endif
        case KC_MISSION_CONTROL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false; // Skip all further processing of this key
        case KC_LAUNCHPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false; // Skip all further processing of this key

        case KC_SPOTLIGHT:
            HCS(0x221);
        case KC_DICTATION:
            HCS(0xCF);
        case KC_DO_NOT_DISTURB:
            HSS(0x9B);
        case KC_LOCK_SCREEN:
            HCS(0x19E);

        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false; // Skip all further processing of this key

        // case KC_TASK_VIEW:
        // case KC_FILE_EXPLORER:
        //     if (record->event.pressed) {
        //         for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK_VIEW].len; i++) {
        //             register_code(key_comb_list[keycode - KC_TASK_VIEW].keycode[i]);
        //         }
        //     } else {
        //         for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK_VIEW].len; i++) {
        //             unregister_code(key_comb_list[keycode - KC_TASK_VIEW].keycode[i]);
        //         }
        //     }
        //     return false;  // Skip all further processing of this key

        case KC_WIN_MODE:
            writePinHigh(LED_MR_LOCK_PIN);
            set_single_persistent_default_layer(0);
            // default_layer_set(1UL << 0);
            // layer_off(2);
            // layer_on(0);
            return false;

        case KC_MAC_MODE:
            writePinLow(LED_MR_LOCK_PIN);
            set_single_persistent_default_layer(2);
            // default_layer_set(1UL << 2);
            // layer_off(0);
            // layer_on(2);
            return false;

        // case KC_TKEY:                        // 전체키 input off -> 좀 더  손을 봐야 함 위에 나열한 키는 입력이 되며, FN키는 동작되게 해야 할듯함
        //     if (record->event.pressed){
        //         all_key_locked = !all_key_locked;
        //         writePin(LED_MR_LOCK_PIN, !all_key_locked);
        //     }
        //     break;
        // default:
        //     if (all_key_locked) { return false; }

                    case AS_ON:
                        //on_mr_leds();
                        writePinLow(LED_MR_LOCK_PIN);
                        break;
                    case AS_OFF:
                        //off_mr_leds();                    
                        writePinHigh(LED_MR_LOCK_PIN);
                        break;
                        
        case QK_BOOT:
            if (record->event.pressed) {
                // Flash LEDs to indicate bootloader mode is enabled.
                on_all_leds();
            }
            break;           
    }
    return process_record_user(keycode, record);
}
#endif /* WINLOCK_DISABLED */

// #ifndef HW_RESET_PIN_DISABLED
// static void hardware_reset_cb(void *arg) {
//     chSysLockFromISR();
//     bootloader_jump();
//     chSysUnlockFromISR();
// }
// #endif

// void keyboard_pre_init_kb(void) {
//     setPinInputHigh(HARDWARE_RESET_PIN);

// #ifndef HW_RESET_PIN_DISABLED
//     /* Jump to bootloader when the hardware reset button is pressed */
//     palEnablePadEvent(PAL_PORT(HARDWARE_RESET_PIN), PAL_PAD(HARDWARE_RESET_PIN), PAL_EVENT_MODE_FALLING_EDGE);
//     palSetPadCallback(PAL_PORT(HARDWARE_RESET_PIN), PAL_PAD(HARDWARE_RESET_PIN), hardware_reset_cb, NULL);

//     /* The interrupt is edge-triggered so check that it's not already pressed */
//     if (!readPin(HARDWARE_RESET_PIN)) {
//         bootloader_jump();
//     }
// #endif
// }

void keyboard_post_init_kb(void) {
//    tap_code16(KC_2);       // (AS_OFF); // 동작안함
    autoshift_disable();
    oneshot_disable();      // oneshot_enable(), oneshot_toggle()

    //    if (get_autoshift_state()) writePinHigh(LED_MR_LOCK_PIN);  // 동작안함, LED제어는 되는데 아직 autoshift가 동작안하는 듯
    //    else writePinLow(LED_MR_LOCK_PIN);
}
//----------------------------------

#define __ NO_LED
#define ___ NO_LED

//------------------------------------------
#ifdef RGB_MATRIX_ENABLE

//__attribute__ ((weak)) bool rgb_matrix_indicators_user(void)  {
__attribute__ ((weak)) bool rgb_matrix_indicators_kb(void)  {
    led_t host_leds = host_keyboard_led_state();

    if (host_leds.caps_lock) { 
        rgb_matrix_set_color(84, 0x05, 0x0, 0x05);
        rgb_matrix_set_color(0, 0x05, 0x0, 0x05);        
    }
    if (host_leds.scroll_lock) {
        rgb_matrix_set_color(24, 0x00, 0x5, 0x5);
        rgb_matrix_set_color(1, 0x00, 0x5, 0x5);
    }        
    if (host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(59, 0x5, 0x5, 0x00);
        rgb_matrix_set_color(2, 0x5, 0x5, 0x00);
    }

    uint8_t layer = get_highest_layer(layer_state|default_layer_state);
    switch (layer) {
        case 0:
            // rgb_matrix_set_color(pgm_read_byte(&convert_led_location2number[11]),  RGB_RED);         //  RGB_TOG  <- too heavy.
            rgb_matrix_set_color(3,0,0,5);
            break;
        case 1:
            rgb_matrix_set_color(3,0,0,5);      
            rgb_matrix_set_color(4,0,0,10);
            break;
        case 2:
            rgb_matrix_set_color(5,3,0,0);
            break;
        case 3:
            rgb_matrix_set_color(5,3,0,0);          
            rgb_matrix_set_color(6,8,0,0);
            break;              
    }
    return TRUE;
}
//----------------------------------

led_config_t g_led_config = {    // 3731 Driver에서 LED 스트링으로 변경함, 상단 및 하단에 21개의 더미 LED 추가 됨
/*
KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SLCK, KC_PAUS,
 K00,              K01,     K02,     K03,     K04,     K05,     K06,     K07,     K08,     K09,      K0A,    K0B,     K0C,         K0D,     K0E,      K0F,
 021,              023,     024,     025,     026,     027,     028,     029,     030,     031,      032,    033,     034,         036,     037,      038,
  41,               39       38       37       36       35       34       33       32       30        29      28       27           25       24        23   <===좌 우 반전

KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,    N_LOCK, KC_PSLS, KC_PAST, KC_PMNS,
 K10,     K11,     K12,     K13,     K14,     K15,     K16,     K17,     K18,     K19,     K1A,      K1B,    K1C,     K1E,         K2E,    K2F,     K1F,         K6A,   K69,      K68,    K67,
 042,     043,     044,     045,     046,     047,     048,     049,     050,     051,     052,      053,    054,     055,         056,    057,     058,         059,    060,     61,    62,

KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
 K20,     K21,    K22,      K23,     K24,     K25,     K26,     K27,     K28,     K29,     K2A,       K2B,      K2C,    K2D,      K3D,       K3E,     K3F,      K7A,      K79,     K78,     K6B,
 063,    064,     065,      066,     067,     068,     069,     070,     071,     072,     073,       074,      075,    076,      077,        78,     79,       80,       81,      82,     83,
  83,     82,      81,       80,      79,      78,      77,      76,      75,      74,      73,        72,       71,     70,       69,        68,     67,       66,       65,      64,     63,  <===좌 우 반전

                                                                                                             <K42>
KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, <KC_NUHS> KC_ENT,                                   KC_P4,   KC_P5,   KC_P6,
  K30,   K31,     K32,     K33,     K34,     K35,     K36,     K37,     K38,     K39,      K3A,      K3B,     K3C,    K4E,                                      K7E,     K7D,     K7C,
  084,   086,     087,     088,     089,     090,     091,     092,     093,      94,      095,      096,     097,    098,                                      102,     103,     104,

           <K45>                                                                                             <K56>
KC_LSFT,<KC_NUBS> KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,              KC_UP,               KC_P1,   KC_P2,   KC_P3,   KC_PENT,
 K40,       K41,   K42,     K43,     K44,     K45,     K46,     K47,     K48,     K49,      K4A,      K4B,              K4D,                K4F,                 K6E,     K6D,     K6C,      K7B,
 105,       106,   107,     108,     109,     110,     111,     112,     113,     114,      115,      116,              118,                120,                 122,     123,     124,      125
 125,       124,   123,     122,     121,     120,     119,     118,     117,     116,      115,      114,              112,                110,                 108,     107,     106,      105    <===좌 우 반전

                            <k131>                                           <k132> <k133>
KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,MO(WIN_FN),KC_APP, KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,     KC_P0,            KC_PDOT
 K50,      K51,    K52,                                K56,                                 K5A,     K5B,      K5C,     K5D,      K5E,      K5F,     K6F,        K7F,               K77
 126,      127,    128,                                132                                  136,     137,      138,     139,      140,      141,     142,        143,               145

    { K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D,  K0E,  K0F },  \
    { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  XXX,  K1E,  K1F },  \
    { K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D,  K2E,  K2F },  \
    { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,  K3D,  K3E,  K3F },  \
    { K40,  K41,  K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K4A,  K4B,  XXX,  K4D,  K4E,  K4F },  \
    { K50,  K51,  K52,  XXX,  XXX,  XXX,  K56,  XXX,  XXX,  XXX,  K5A,  K5B,  K5C,  K5D,  K5E,  K5F },  \
    { XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  K67,  K68,  K69,  K6A,  K6B,  K6C,  K6D,  K6E,  K6F },  \
    { XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  K77,  K78,  K79,  K7A,  K7B,  K7C,  K7D,  K7E,  K7F }   \

    실제파일에 0을 앞에 붙이면 안됨.. 8진수로 오인함  /  위 LED넘버는 하나씩 뺴야 함
*/
    {       // total 16x8 = 128 - 22 = 106  (config led total = 112) // WS2812용
    { 41, 39, 38,  37,  36,  35,  34,  33,   32,  30,  29,  28,  27,   25, 24,  23 },
    { 42, 43, 44,  45,  46,  47,  48,  49,   50,  51,  52,  53,  54,  ___, 55,  58 },
    { 83, 82, 81,  80,  79,  78,  77,  76,   75,  74,  73,  72,  71,  70,  56,  57 },
    { 84, 86, 87,  88,  89,  90,  91,  92,   93,  94,  95,  96,  97,  69,  68,  67 },
    {125,124,123, 122, 121, 120, 119, 118,  117, 116, 115, 114, ___, 112,  98, 110 },
    {126,127, 128, ___, ___, ___, 132, ___, ___, ___, 136, 137, 138, 139, 140, 141 },
    {___,___, ___, ___, ___, ___, ___,  62,  61,  60,  59,  63, 106, 107, 108, 142 },
    {___,___, ___, ___, ___, ___, ___, 145,  64,  65,  66, 105, 104, 103, 102, 143 }
    },
  /*
 {       // total 16x8 = 128 - 22 = 106  (config led total = 112)       // 3731용
    {  8,  9,  10,  11,  12,  13,  14,  15,  56,  57,  58,  59,  60,  61,  62,  63 },
    {  0,  1,  2,   3,   4,   5,   6,   7,   48,  49,  50,  51,  52,  ___, 54,  97 },
    { 24, 25, 26,  27,  28,  29,  30,  31,   72,  73,  74,  75,  76,  77,  55,  81 },
    { 16, 17, 18,  19,  20,  21,  22,  23,   64,  65,  66,  67,  68,  78,  79,  96 },
    { 40, 41, 42,  43,  44,  45,  46,  47,   88,  89,  90,  91, ___,  71,  69,  87 },
    { 32, 33,  34, ___, ___, ___,  36, ___, ___, ___,  39,  92,  93,  94,  95,  86 },
    {___,___, ___, ___, ___, ___, ___, 101, 100,  99,  98, 102, 106, 105, 104,  85 },
    {___,___, ___, ___, ___, ___, ___,  83, 103, 111, 110,  81, 109, 108, 107,  84 }
    },  

    {       // total 16x8 = 128 - 22 = 106  (config led total = 112) // WS2812용
    { 21, 23, 24,  25,  26,  27,  28,  29,   30,  31,  32,  33,  34,  36,  37,  38 },
    { 42, 43, 44,  45,  46,  47,  48,  49,   50,  51,  52,  53,  54,  ___, 55,  58 },
    { 63, 64, 65,  66,  67,  68,  69,  70,   71,  72,  73,  74,  75,  76,  56,  57 },
    { 84, 86, 87,  88,  89,  90,  91,  92,   93,  94,  95,  96,  97,  77,  78,  79 },
    {105,106,107, 108, 109, 110, 111, 112,  113, 114, 115, 116, ___, 118,  98, 120 },
    {126,127, 128, ___, ___, ___, 132, ___, ___, ___, 136, 137, 138, 139, 140, 141 },
    {___,___, ___, ___, ___, ___, ___,  62,  61,  60,  59,  83, 124, 123, 122, 142 },
    {___,___, ___, ___, ___, ___, ___, 145,  82,  81,  80, 125, 104, 103, 102, 143 }
    },
     */


/*
    {       // total 16x7 = 112  (config led total = 112)
        // LED Index to Physical Position
        {  0,  0}, { 15,  0}, { 30,  0}, { 45,  0}, { 60,  0}, { 75,  0}, { 90,  0}, {105,  0}, {130,  0}, {145,  0}, {160,  0}, {175,  0}, {190,  0}, {205,  0}, {220,  0}, {235,  0},
        {  0,  8}, { 15,  8}, { 30,  8}, { 45,  8}, { 60,  8}, { 75,  8}, { 90,  8}, {105,  8}, {130,  8}, {145,  8}, {160,  8}, {175,  8}, {190,  8}, {205,  8}, {220,  8}, {235,  8},
        {  0, 16}, { 15, 16}, { 30, 16}, { 45, 16}, { 60, 16}, { 75, 16}, { 90, 16}, {105, 16}, {130, 16}, {145, 16}, {160, 16}, {175, 16}, {190, 16}, {205, 16}, {220, 16}, {235, 16},
        {  0, 24}, { 15, 24}, { 30, 24}, { 45, 24}, { 60, 24}, { 75, 24}, { 90, 24}, {105, 24}, {130, 24}, {145, 24}, {160, 24}, {175, 24}, {190, 24}, {205, 24}, {220, 24}, {235, 24},
        {  0, 32}, { 15, 32}, { 30, 32}, { 45, 32}, { 60, 32}, { 75, 32}, { 90, 32}, {105, 32}, {130, 32}, {145, 32}, {160, 32}, {175, 32}, {190, 32}, {205, 32}, {220, 32}, {235, 32},

        {  0, 40}, { 15, 40}, { 30, 40}, { 45, 40}, { 60, 40}, { 75, 40}, { 90, 40}, {105, 40}, {130, 40}, {145, 40}, {160, 40}, {175, 40}, {190, 40}, {205, 40}, {220, 40}, {235, 40},
        {  0, 48}, { 15, 48}, { 30, 48}, { 45, 48}, { 60, 48}, { 75, 48}, { 90, 48}, {105, 48}, {130, 48}, {145, 48}, {160, 48}, {175, 48}, {190, 48}, {205, 48}, {220, 48}, {235, 48}
      //  {  0, 56}, { 15, 56}, { 30, 56}, { 45, 56}, { 60, 56}, { 75, 56}, { 90, 56}, {105, 56}, {130, 56}, {145, 56}, {160, 56}, {175, 56}, {190, 56}, {205, 56}, {220, 56}, {235, 56},
      //  {  0, 64}, { 15, 64}, { 30, 64}, { 45, 64}, { 60, 64}, { 75, 64}, { 90, 64}, {105, 64}, {130, 64}, {145, 64}, {160, 64}, {175, 64}, {190, 64}, {205, 64}, {220, 64}, {235, 64}
    }, {
        // LED Index to Flag
        9, 4, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 4, 1, 8, 1,  //15       // scroll lock
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,  //31
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,  //47
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,  //63     caplock
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,  // 79
        1, 1, 1, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 4,  // 95
        4, 4, 4, 4, 4, 4, 4, 4, 8, 1, 1, 1, 4, 4, 4, 1,  // 111     numlock

     //   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4,  // 127
     //   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }

    {     // for 3731 total 112  (config led total = 112)
          // LED Index to Physical Position (config led total = 112와 수가 같아야 함, 더미로 몇개 추가함)
        {0,0},           {21,0},  {31,0},  {42,0},  {52,0},  {68,0},  {78,0},  {89,0},   {99,0},   {115,0},  {125,0},  {136,0},  {146,0},  {159,0},  {169,0},  {180,0},  {193,0},  {203,0},  {214,0},  {224,0},
        {0,15}, {10,15}, {21,15}, {31,15}, {42,15}, {52,15}, {63,15}, {73,15}, {83,15},  {94,15},  {104,15}, {115,15}, {125,15}, {141,15}, {159,15}, {169,15}, {180,15}, {193,15}, {203,15}, {214,15}, {224,15},
        {3,27}, {16,27}, {26,27}, {36,27}, {47,27}, {57,27}, {68,27}, {78,27}, {89,27},  {99,27},  {109,27}, {120,27}, {130,27}, {143,27}, {159,27}, {169,27}, {180,27}, {193,27}, {203,27}, {214,27},
        {4,40}, {18,40}, {29,40}, {39,40}, {50,40}, {60,40}, {70,40}, {81,40}, {91,40},  {102,40}, {112,40}, {123,40}, {130,40}, {139,40},                               {193,40}, {203,40}, {214,40}, {224,34},
        {7,52}, {10,52}, {23,52}, {34,52}, {44,52}, {55,52}, {65,52}, {76,52}, {86,52},  {96,52},  {107,52}, {117,52}, {130,52}, {137,52},           {169,52},           {193,52}, {203,52}, {214,52},
        {1,64}, {14,64}, {27,64}, {34,64},                   {66,64},                              {105,64}, {118,64}, {131,64}, {145,64}, {159,64}, {169,64}, {180,64}, {198,64},           {214,64}, {224,58},
    },
    {
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 9, 4, 4, 4,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 4, 4, 4,
        9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,          4, 4, 4, 4,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,    4, 4, 4,
        1, 1, 1, 1,       4,          1, 1, 1, 1, 1, 1, 1, 1,    4, 1,
    }

        {     // total 112  (config led total = 112)
          // LED Index to Physical Position (config led total = 112와 수가 같아야 함, 더미로 몇개 추가함)
        {0, 0},{10, 0},{20, 0},{30, 0},{40, 0},{50, 0},{60, 0},{70, 0},{80, 0},{90, 0},{100, 0},{110, 0},{120, 0},{130, 0},{140, 0},{150, 0},{160, 0},{170, 0},{180, 0},{190, 0},{200, 0},
        {0, 9},{10, 9},{20, 9},{30, 9},{40, 9},{50, 9},{60, 9},{70, 9},{80, 9},{90, 9},{100, 9},{110, 9},{120, 9},{130, 9},{140, 9},{150, 9},{160, 9},{170, 9},{180, 9},{190, 9},{200, 9},
        {0,18},{10,18},{20,18},{30,18},{40,18},{50,18},{60,18},{70,18},{80,18},{90,18},{100,18},{110,18},{120,18},{130,18},{140,18},{150,18},{160,18},{170,18},{180,18},{190,18},{200,18},
        {0,27},{10,27},{20,27},{30,27},{40,27},{50,27},{60,27},{70,27},{80,27},{90,27},{100,27},{110,27},{120,27},{130,27},{140,27},{150,27},{160,27},{170,27},{180,27},{190,27},{200,27},
        {0,36},{10,36},{20,36},{30,36},{40,36},{50,36},{60,36},{70,36},{80,36},{90,36},{100,36},{110,36},{120,36},{130,36},{140,36},{150,36},{160,36},{170,36},{180,36},{190,36},{200,36},
        {0,45},{10,45},{20,45},{30,45},{40,45},{50,45},{60,45},{70,45},{80,45},{90,45},{100,45},{110,45},{120,45},{130,45},{140,45},{150,45},{160,45},{170,45},{180,45},{190,45},{200,45},
        {0,54},{10,54},{20,54},{30,54},{40,54},{50,54},{60,54},{70,54},{80,54},{90,54},{100,54},{110,54},{120,54},{130,54},{140,54},{150,54},{160,54},{170,54},{180,54},{190,54},{200,54},
        {0,63},{10,63},{20,63},{30,63},{40,63},{50,63},{60,63},{70,63},{80,63},{90,63},{100,63},{110,63},{120,63},{130,63},{140,63},{150,63},{160,63},{170,63},{180,63},{190,63},{200,63} 
    },
        {  0, 0},{ 10, 0},{ 20, 0},{ 30, 0},{ 40, 0},{ 50, 0},{ 60, 0},{ 70, 0},{ 80, 0},{ 90, 0},{100, 0},{110, 0},{120, 0},{130, 0},{140, 0},{150, 0},{160, 0},{170, 0},{180, 0},{190, 0},{200, 0},
        {  0, 9},{ 10, 9},{ 20, 9},{ 30, 9},{ 40, 9},{ 50, 9},{ 60, 9},{ 70, 9},{ 80, 9},{ 90, 9},{100, 9},{110, 9},{120, 9},{130, 9},{140, 9},{150, 9},{160, 9},{170, 9},{180, 9},{190, 9},{200, 9},
        {  0,18},{ 10,18},{ 20,18},{ 30,18},{ 40,18},{ 50,18},{ 60,18},{ 70,18},{ 80,18},{ 90,18},{100,18},{110,18},{120,18},{130,18},{140,18},{150,18},{160,18},{170,18},{180,18},{190,18},{200,18},
        {  0,27},{ 10,27},{ 20,27},{ 30,27},{ 40,27},{ 50,27},{ 60,27},{ 70,27},{ 80,27},{ 90,27},{100,27},{110,27},{120,27},{130,27},{140,27},{150,27},{160,27},{170,27},{180,27},{190,27},{200,27},
        {  0,36},{ 10,36},{ 20,36},{ 30,36},{ 40,36},{ 50,36},{ 60,36},{ 70,36},{ 80,36},{ 90,36},{100,36},{110,36},{120,36},{130,36},{140,36},{150,36},{160,36},{170,36},{180,36},{190,36},{200,36},
        {  0,45},{ 10,45},{ 20,45},{ 30,45},{ 40,45},{ 50,45},{ 60,45},{ 70,45},{ 80,45},{ 90,45},{100,45},{110,45},{120,45},{130,45},{140,45},{150,45},{160,45},{170,45},{180,45},{190,45},{200,45},
        {  0,54},{ 10,54},{ 20,54},{ 30,54},{ 40,54},{ 50,54},{ 60,54},{ 70,54},{ 80,54},{ 90,54},{100,54},{110,54},{120,54},{130,54},{140,54},{150,54},{160,54},{170,54},{180,54},{190,54},{200,54},
        {  0,63},{ 10,63},{ 20,63},{ 30,63},{ 40,63},{ 50,63},{ 60,63},{ 70,63},{ 80,63},{ 90,63},{100,63},{110,63},{120,63},{130,63},{140,63},{150,63},{160,63},{170,63},{180,63},{190,63},{200,63} 

     */

    {     // total 112  (config led total = 112)
          // LED Index to Physical Position (config led total = 112와 수가 같아야 함, 더미로 몇개 추가함)
        {  0, 0},{ 10, 0},{ 20, 0},{ 30, 0},{ 40, 0},{ 50, 0},{ 60, 0},{ 70, 0},{ 80, 0},{ 90, 0},{100, 0},{110, 0},{120, 0},{130, 0},{140, 0},{150, 0},{160, 0},{170, 0},{180, 0},{190, 0},{200, 0},
        {200, 9},{190, 9},{180, 9},{170, 9},{160, 9},{150, 9},{140, 9},{130, 9},{120, 9},{110, 9},{100, 9},{ 90, 9},{ 80, 9},{ 70, 9},{ 60, 9},{ 50, 9},{ 40, 9},{ 30, 9},{ 20, 9},{ 10, 9},{  0, 9},
        {  0,18},{ 10,18},{ 20,18},{ 30,18},{ 40,18},{ 50,18},{ 60,18},{ 70,18},{ 80,18},{ 90,18},{100,18},{110,18},{120,18},{130,18},{140,18},{150,18},{160,18},{170,18},{180,18},{190,18},{200,18},
        {200,27},{190,27},{180,27},{170,27},{160,27},{150,27},{140,27},{130,27},{120,27},{110,27},{100,27},{ 90,27},{ 80,27},{ 70,27},{ 60,27},{ 50,27},{ 40,27},{ 30,27},{ 20,27},{ 10,27},{  0,27},
        {  0,36},{ 10,36},{ 20,36},{ 30,36},{ 40,36},{ 50,36},{ 60,36},{ 70,36},{ 80,36},{ 90,36},{100,36},{110,36},{120,36},{130,36},{140,36},{150,36},{160,36},{170,36},{180,36},{190,36},{200,36},
        {200,45},{190,45},{180,45},{170,45},{160,45},{150,45},{140,45},{130,45},{120,45},{110,45},{100,45},{ 90,45},{ 80,45},{ 70,45},{ 60,45},{ 50,45},{ 40,45},{ 30,45},{ 20,45},{ 10,45},{  0,45},
        {  0,54},{ 10,54},{ 20,54},{ 30,54},{ 40,54},{ 50,54},{ 60,54},{ 70,54},{ 80,54},{ 90,54},{100,54},{110,54},{120,54},{130,54},{140,54},{150,54},{160,54},{170,54},{180,54},{190,54},{200,54},
        {200,63},{190,63},{180,63},{170,63},{160,63},{150,63},{140,63},{130,63},{120,63},{110,63},{100,63},{ 90,63},{ 80,63},{ 70,63},{ 60,63},{ 50,63},{ 40,63},{ 30,63},{ 20,63},{ 10,63},{  0,63} 
    },
    {
        4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,
        4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,
        4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,
        4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,
        4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,
        4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,
        4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,        
        4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,4, 4                                                
    }

};
   /*
    {
        {0,0},           {21,0},  {31,0},  {42,0},  {52,0},  {68,0},  {78,0},  {89,0},   {99,0},   {115,0},  {125,0},  {136,0},  {146,0},  {159,0},  {169,0},  {180,0},  {193,0},  {203,0},  {214,0},  {224,0},
        {0,15}, {10,15}, {21,15}, {31,15}, {42,15}, {52,15}, {63,15}, {73,15}, {83,15},  {94,15},  {104,15}, {115,15}, {125,15}, {141,15}, {159,15}, {169,15}, {180,15}, {193,15}, {203,15}, {214,15}, {224,15},
        {3,27}, {16,27}, {26,27}, {36,27}, {47,27}, {57,27}, {68,27}, {78,27}, {89,27},  {99,27},  {109,27}, {120,27}, {130,27}, {143,27}, {159,27}, {169,27}, {180,27}, {193,27}, {203,27}, {214,27},
        {4,40}, {18,40}, {29,40}, {39,40}, {50,40}, {60,40}, {70,40}, {81,40}, {91,40},  {102,40}, {112,40}, {123,40},           {139,40},                               {193,40}, {203,40}, {214,40}, {224,34},
        {7,52},          {23,52}, {34,52}, {44,52}, {55,52}, {65,52}, {76,52}, {86,52},  {96,52},  {107,52}, {117,52},           {137,52},           {169,52},           {193,52}, {203,52}, {214,52},
        {1,64}, {14,64}, {27,64},                            {66,64},                              {105,64}, {118,64}, {131,64}, {145,64}, {159,64}, {169,64}, {180,64}, {198,64},           {214,64}, {224,58},
    },
    {
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 9, 4, 4, 4,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 4, 4, 4,
        9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,          4, 4, 4, 4,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,    1,    4, 4, 4,
        1, 1, 1,          4,          1, 1, 1, 1, 1, 1, 1, 1,    4, 1,
    }
*/
#endif

//------------------------------------------

#ifdef LED_MATRIX_ENABLE        // RGB 보다 앞에 있으면 에러남 실행 되는것이 희안, 어딘가에 모르는 곳에 LED_MATRIX_ENABLE이 define되었나?

__attribute__ ((weak)) bool led_matrix_indicators_kb(void) {

    led_t host_leds = host_keyboard_led_state();

    if (host_leds.caps_lock) {led_matrix_set_value(48, 0xff);  }
    if (host_leds.scroll_lock) {led_matrix_set_value(14, 0xff); }
    if (host_keyboard_led_state().num_lock) { led_matrix_set_value(104, 0xff);  }

    return TRUE;
}
//----------------------------------
const is31_led PROGMEM g_is31_leds[LED_MATRIX_LED_COUNT] = {
    {0, C1_1}, {0, C1_2}, {0, C1_3}, {0, C1_4}, {0, C1_5}, {0, C1_6}, {0, C1_7}, {0, C1_8},    {0, C1_9}, {0, C1_10}, {0, C1_11}, {0, C1_12}, {0, C1_13}, {0, C1_14}, {0, C1_15}, {0, C1_16},
    {0, C2_1}, {0, C2_2}, {0, C2_3}, {0, C2_4}, {0, C2_5}, {0, C2_6}, {0, C2_7}, {0, C2_8},    {0, C2_9}, {0, C2_10}, {0, C2_11}, {0, C2_12}, {0, C2_13}, {0, C2_14}, {0, C2_15}, {0, C2_16},
    {0, C3_1}, {0, C3_2}, {0, C3_3}, {0, C3_4}, {0, C3_5}, {0, C3_6}, {0, C3_7}, {0, C3_8},    {0, C3_9}, {0, C3_10}, {0, C3_11}, {0, C3_12}, {0, C3_13}, {0, C3_14}, {0, C3_15}, {0, C3_16},
    {0, C4_1}, {0, C4_2}, {0, C4_3}, {0, C4_4}, {0, C4_5}, {0, C4_6}, {0, C4_7}, {0, C4_8},    {0, C4_9}, {0, C4_10}, {0, C4_11}, {0, C4_12}, {0, C4_13}, {0, C4_14}, {0, C4_15}, {0, C4_16},
    {0, C5_1}, {0, C5_2}, {0, C5_3}, {0, C5_4}, {0, C5_5}, {0, C5_6}, {0, C5_7}, {0, C5_8},    {0, C5_9}, {0, C5_10}, {0, C5_11}, {0, C5_12}, {0, C5_13}, {0, C5_14}, {0, C5_15}, {0, C5_16},

    {0, C6_1}, {0, C6_2}, {0, C6_3}, {0, C6_4}, {0, C6_5}, {0, C6_6}, {0, C6_7}, {0, C6_8},    {0, C6_9}, {0, C6_10}, {0, C6_11}, {0, C6_12}, {0, C6_13}, {0, C6_14}, {0, C6_15}, {0, C6_16},
    {0, C7_1}, {0, C7_2}, {0, C7_3}, {0, C7_4}, {0, C7_5}, {0, C7_6}, {0, C7_7}, {0, C7_8},    {0, C7_9}, {0, C7_10}, {0, C7_11}, {0, C7_12}, {0, C7_13}, {0, C7_14}, {0, C7_15}, {0, C7_16},
    {0, C8_1}, {0, C8_2}, {0, C8_3}, {0, C8_4}, {0, C8_5}, {0, C8_6}, {0, C8_7}, {0, C8_8},    {0, C8_9}, {0, C8_10}, {0, C8_11}, {0, C8_12}, {0, C8_13}, {0, C8_14}, {0, C8_15}, {0, C8_16},
    {0, C9_1}, {0, C9_2}, {0, C9_3}, {0, C9_4}, {0, C9_5}, {0, C9_6}, {0, C9_7}, {0, C9_8},    {0, C9_9}, {0, C9_10}, {0, C9_11}, {0, C9_12}, {0, C9_13}, {0, C9_14}, {0, C9_15}, {0, C9_16}
};

led_config_t g_led_config = {
    {  // Key Matrix to LED Index

        // {  0,  1,  2,  3,  4,  5,  6,  7,    8,  9, 10, 11, 12, 13, 14, 15 },
        // { 16, 17, 18, 19, 20, 21, 22, 23,   24, 25, 26, 27, 28, 29, 30, 31 },
        // { 32, 33, 34, 35, 36, 37, 38, 39,   40, 41, 42, 43, 44, 45, 46, 47 },
        // { 48, 49, 50, 51, 52, 53, 54, 55,   56, 57, 58, 59, 60, 61, 62, 63 },
        // { 64, 65, 66, 67, 68, 69, 70, 71,   72, 73, 74, 75, 76, 77, 78, 79 },
        // { 80, 81, 82, 83, 84, 85, 86, 87,   88, 89, 90, 91, 92, 93, 94, 95 },
        // { 96, 97, 98, 99,100,101,102,103,  104,105,106,107,108,109,110,111 },
        // {112,113,114,115,116,117,118,119,  120,121,122,123,124,125,126,127 },
        // {128,129,130,131,132,133,134,135,  136,137,138,139,140,141,142,143 }

    { 00,  01,  02,  03,  04,  05,  06,  07,     8,   9,  10,  11,  12,  13,  14,  15 },  \
    { 16,  17,  18,  19,  20,  21,  22,  23,    24,  25,  26,  27,  28, ___,  30,  47 },  \
    { 32,  33,  34,  35,  36,  37,  38,  39,    40,  41,  42,  43,  44,  45,  31,  46 },  \
    { 48,  49,  50,  51,  52,  53,  54,  55,    56,  57,  58,  59,  62,  62,  63,  79 },  \
    { 64,  65,  66,  67,  68,  69,  70,  71,    72,  73,  74,  75, ___,  77,  61,  78 },  \
    { 80,  81,  82, ___, ___, ___,  85, ___,   ___, ___,  88,  89,  90,  91,  92,  93 },  \
    {___, ___, ___, ___, ___, ___, ___, 107,   106, 105, 104, 123, 110, 109, 108,  94 },  \
    {___, ___, ___, ___, ___, ___, ___,  127,  122, 121, 120, 111, 126, 125, 124,  95 }
/*
< 사용하지 않는 led >
29,60,76, 83,86,87
96, 97,98,99,100,101,102,103,    112,113,114,115,116,117,118,119,
128,129,130,131,132,133,134,135,   136,137,138,139,140,141,142,143

     [_BASE] = LAYOUT_all( // Base Layer
      KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SLCK, KC_PAUS,
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,    KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,                                   KC_P4,   KC_P5,   KC_P6,
      KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,               KC_P1,   KC_P2,   KC_P3,   KC_PENT,
      KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN), KC_APP,  KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT
  ),

    #define LAYOUT_all( \
      K00,        K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,      K0D,  K0E,  K0F,                          \
      K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1E,      K2E,  K2F,  K1F,      K6A, K69, K68, K67, \
      K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D,      K3D,  K3E,  K3F,      K7A, K79, K78, K6B, \
      K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,  K4E,                            K7E, K7D, K7C,      \
      K40,  K41,  K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K4A,  K4B,        K4D,            K4F,            K6E, K6D, K6C, K7B, \
      K50,  K51,  K52,                    K56,                    K5A,  K5B,  K5C,  K5D,      K5E,  K5F,  K6F,      K7F,      K77       \
) { \
    { K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D,  K0E,  K0F },  \
    { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  XXX,  K1E,  K1F },  \
    { K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D,  K2E,  K2F },  \
    { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,  K3D,  K3E,  K3F },  \
    { K40,  K41,  K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K4A,  K4B,  XXX,  K4D,  K4E,  K4F },  \
    { K50,  K51,  K52,  XXX,  XXX,  XXX,  K56,  XXX,  XXX,  XXX,  K5A,  K5B,  K5C,  K5D,  K5E,  K5F },  \
    { XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  K67,  K68,  K69,  K6A,  K6B,  K6C,  K6D,  K6E,  K6F },  \
    { XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  K77,  K78,  K79,  K7A,  K7B,  K7C,  K7D,  K7E,  K7F }   \
}*/

    }, {
        // LED Index to Physical Position
        {  0,  0}, { 15,  0}, { 30,  0}, { 45,  0}, { 60,  0}, { 75,  0}, { 90,  0}, {105,  0}, {130,  0}, {145,  0}, {160,  0}, {175,  0}, {190,  0}, {205,  0}, {220,  0}, {235,  0},
        {  0,  8}, { 15,  8}, { 30,  8}, { 45,  8}, { 60,  8}, { 75,  8}, { 90,  8}, {105,  8}, {130,  8}, {145,  8}, {160,  8}, {175,  8}, {190,  8}, {205,  8}, {220,  8}, {235,  8},
        {  0, 16}, { 15, 16}, { 30, 16}, { 45, 16}, { 60, 16}, { 75, 16}, { 90, 16}, {105, 16}, {130, 16}, {145, 16}, {160, 16}, {175, 16}, {190, 16}, {205, 16}, {220, 16}, {235, 16},
        {  0, 24}, { 15, 24}, { 30, 24}, { 45, 24}, { 60, 24}, { 75, 24}, { 90, 24}, {105, 24}, {130, 24}, {145, 24}, {160, 24}, {175, 24}, {190, 24}, {205, 24}, {220, 24}, {235, 24},
        {  0, 32}, { 15, 32}, { 30, 32}, { 45, 32}, { 60, 32}, { 75, 32}, { 90, 32}, {105, 32}, {130, 32}, {145, 32}, {160, 32}, {175, 32}, {190, 32}, {205, 32}, {220, 32}, {235, 32},

        {  0, 40}, { 15, 40}, { 30, 40}, { 45, 40}, { 60, 40}, { 75, 40}, { 90, 40}, {105, 40}, {130, 40}, {145, 40}, {160, 40}, {175, 40}, {190, 40}, {205, 40}, {220, 40}, {235, 40},
        {  0, 48}, { 15, 48}, { 30, 48}, { 45, 48}, { 60, 48}, { 75, 48}, { 90, 48}, {105, 48}, {130, 48}, {145, 48}, {160, 48}, {175, 48}, {190, 48}, {205, 48}, {220, 48}, {235, 48},
        {  0, 56}, { 15, 56}, { 30, 56}, { 45, 56}, { 60, 56}, { 75, 56}, { 90, 56}, {105, 56}, {130, 56}, {145, 56}, {160, 56}, {175, 56}, {190, 56}, {205, 56}, {220, 56}, {235, 56},
        {  0, 64}, { 15, 64}, { 30, 64}, { 45, 64}, { 60, 64}, { 75, 64}, { 90, 64}, {105, 64}, {130, 64}, {145, 64}, {160, 64}, {175, 64}, {190, 64}, {205, 64}, {220, 64}, {235, 64}
    }, {
        // LED Index to Flag
        9, 4, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 4, 1, 8, 1,  //15       // scroll lock
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,  //31
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,  //47
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,  //63     caplock
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,  // 79
        1, 1, 1, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 4,  // 95
        4, 4, 4, 4, 4, 4, 4, 4, 8, 1, 1, 1, 4, 4, 4, 1,  // 111     numlock

        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4,  // 127
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};
#endif