#include QMK_KEYBOARD_H
//#include "k20emul2.h"

enum layers {   WIN_BASE,
                WIN_FN,
                MAC_BASE,
                MAC_FN  
            };

enum K20_keycodes {
#ifdef VIA_ENABLE
    KC_TGUI = USER00,   // Toggle between GUI Lock or Unlock
    KC_WIN_MODE,             // WINDOWS Keyboard(layer)로 변경
    KC_MAC_MODE,             // Machintosh Keyboard(layer)로 변경
    KC_MISSION_CONTROL,     // MAC_key
    KC_LAUNCHPAD,           // MAC_key
KC_SPOTLIGHT,           // MAC_key
KC_DICTATION,           // MAC_key
KC_DO_NOT_DISTURB,      // MAC_key
KC_LOCK_SCREEN,         // MAC_key
    KC_LOPTN,               // MAC_key - left option   (win위치)
    KC_ROPTN,               // MAC_key - right option
    KC_LCMMD,               // MAC_key - left command  (ALT위치)
    KC_RCMMD,               // MAC_key - right command
    KC_TASK_VIEW,           // for win (gui + tap)
    KC_FILE_EXPLORER,       // for win (gui + e)
    KC_STER,                // LED effect step reverse
    KC_SPDI,                // LED effect speed up
    KC_SPDD,                // LED effect speed down
    KC_TKEY,                // all key input off
    NEW_SAFE_RANGE = SAFE_RANGE
#else
    KC_TGUI = SAFE_RANGE,   // Toggle between GUI Lock or Unlock
    KC_WIN_MODE,             // WINDOWS Keyboard로 변경
    KC_MAC_MODE,             // Machintosh Keyboard로 변경
    KC_MISSION_CONTROL,     // MAC_key
    KC_LAUNCHPAD,           // MAC_key
KC_SPOTLIGHT,           // MAC_key
KC_DICTATION,           // MAC_key
KC_DO_NOT_DISTURB,      // MAC_key
KC_LOCK_SCREEN,         // MAC_key
    KC_LOPTN,               // MAC_key 불필요한듯
    KC_ROPTN,               // MAC_key 불필요한듯
    KC_LCMMD,               // MAC_key 불필요한듯
    KC_RCMMD,               // MAC_key 불필요한듯
    KC_TASK_VIEW,           // for win (gui + tap)
    KC_FILE_EXPLORER,       // for win (gui + e)
    KC_STER,                // LED effect step reverse
    KC_SPDI,                // LED effect speed up
    KC_SPDD,                // LED effect speed down
    KC_TKEY,                // all key input off
    NEW_SAFE_RANGE
#endif
};

#define KC_WINM KC_WIN_MODE      // DIP switch
#define KC_MACM KC_MAC_MODE

#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD
#define KC_SPLT KC_SPOTLIGHT
#define KC_SIRI KC_DICTATION
#define KC_DOND KC_DO_NOT_DISTURB
#define KC_LSCR KC_LOCK_SCREEN

#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD
//#define KC_TASK KC_TASK_VIEW
//#define KC_FLXP KC_FILE_EXPLORER
#define KC_TASK LGUI(KC_TAB)       // Task view (modifier combination)
#define KC_FLXP LGUI(KC_E)         // File Explorer

typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[2];
} key_combination_t;

key_combination_t key_comb_list[2] = {
    {2, {KC_LWIN, KC_TAB}},
    {2, {KC_LWIN, KC_E}}
};

// Tap dance declarations 
enum {
    TD_NCAL = 0,
    TD_2,
    TD_3,
    TD_4,
    TD_5
};

void dance_test(qk_tap_dance_state_t *state, void *user_data){
    if(state->count >=5){
        SEND_STRING("Tap Dance Test ok!");
        reset_tap_dance(state);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_NCAL] = ACTION_TAP_DANCE_DOUBLE(KC_NUM_LOCK, KC_CALC),
    [TD_2] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MSEL),
    [TD_3] = ACTION_TAP_DANCE_DOUBLE(KC_FLXP, KC_MYCM),
    [TD_4] = ACTION_TAP_DANCE_DOUBLE(KC_MSEL, KC_MAIL),
    [TD_5] = ACTION_TAP_DANCE_FN(dance_test),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* ┌───┬───┬───┬───┐
     * │Esc│Tab│MO1│Bsp│
     * ├───┼───┼───┼───┤
     * │Num│ / │ * │ - │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┤ + │
     * │ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │   │
     * ├───┴───┼───┤Ent│
     * │ 0     │ . │   │
     * └───────┴───┴───┘ */
    [WIN_BASE] = LAYOUT(KC_ESC,       KC_TAB,   KC_BSPC, KC_VOLD,MO(1),KC_VOLU,
                        TD(TD_NCAL), KC_PSLS,   KC_PAST,       KC_PMNS,
                        KC_P7,         KC_P8,     KC_P9,       KC_PPLS,
                        KC_P4,         KC_P5,     KC_P6,
                        KC_P1,         KC_P2,     KC_P3,       KC_PENT,
                        KC_P0,                   KC_PDOT ),
    /* ┌───┐───┬───┬───┐
     * │Rst│Tab│MO1│Bsp│
     * └───┘───┼───┼───┤
     * │Num│ / │ * │ - │
     * ┌───┬───┬───┐───┤
     * │Hom│ ↑ │PgU│   │
     * ├───┼───┼───┤ + │
     * │ ← │   │ → │   │
     * ├───┼───┼───┤───┤
     * │End│ ↓ │PgD│   │
     * ├───┴───┼───┤Ent│
     * │Insert │Del│   │
     * └───────┴───┘───┘*/
    [WIN_FN] = LAYOUT(  KC_CALC, KC_WINM,  KC_MACM,  RGB_VAD,_______,RGB_VAI,
                        _______, _______, _______,    EE_CLR,
                        _______, _______, _______,    QK_RBT,
                        RGB_SPI, RGB_HUI,  RGB_SAI,
                        RGB_SPD, RGB_HUD,  RGB_SAD,  QK_BOOT,
                        RGB_MOD,           RGB_TOG),

    [MAC_BASE] = LAYOUT(KC_ESC,   KC_TAB, KC_BSPC, KC_VOLD, MO(3), KC_VOLU,
                        TD(TD_NCAL), KC_ACL0, KC_ACL1, KC_ACL2,
                        KC_BTN4, KC_MS_U,  KC_BTN5, KC_WH_U,
                        KC_MS_L, KC_BTN3,  KC_MS_R,
                        KC_WH_L, KC_MS_D,  KC_WH_R, KC_WH_D,
                        KC_BTN1,           KC_BTN2),

    [MAC_FN] = LAYOUT(  KC_CALC, KC_WINM,  KC_MACM,  RGB_VAD,_______,RGB_VAI,
                        _______, _______, _______,    EE_CLR,
                        _______, _______, _______,    QK_RBT,
                        RGB_SPI, RGB_HUI,  RGB_SAI,
                        RGB_SPD, RGB_HUD,  RGB_SAD,  QK_BOOT,
                        RGB_MOD,           RGB_TOG)
};

//-----------------------------------------------------------------
//#if defined(VIA_ENABLE) && defined(ENCODER_ENABLE)
#ifndef ENCODER_MAP_ENABLE

#define ENCODERS 1
static uint8_t  encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS]    = {{3, 5}};     // key matrix K53
static keypos_t encoder_ccw[ENCODERS]   = {{1, 5}};     // key matrix K51

void encoder_action_unregister(void) {
    for (int index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t){
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = (timer_read() | 1)
            };
            encoder_state[index]     = 0;
            action_exec(encoder_event);
        }
    }
}

void encoder_action_register(uint8_t index, bool clockwise){
    keyevent_t encoder_event = (keyevent_t){
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = (timer_read() | 1)
    };
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

bool encoder_update_user(uint8_t index, bool clockwise) {

    encoder_action_register(index, clockwise);
    return false;
}

void matrix_scan_user(void) {
    
    encoder_action_unregister();
}
//---------------------------
#else /////defined(VIA_ENABLE) && defined(ENCODER_ENABLE)  or #ifndef ENCODER_MAP_ENABLE
//#ifdef ENCODER_MAP_ENABLE

// #define NUM_ENCODERS 1
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }  
};
//#endif

// bool encoder_update_user(uint8_t index, bool clockwise) {

//     if (index == 0) {
//         if (IS_LAYER_ON(WIN_FN)) {
//             if (clockwise) {
//                 tap_code_delay(KC_P8, 10);
//             } else {
//                 tap_code_delay(KC_P2, 10);
//             }
//         }
//         else {
//             if (clockwise) {
//                 tap_code_delay(KC_VOLU, 10);
//             } else {
//                 tap_code_delay(KC_VOLD, 10);
//             }
//         }
//     }
//     return false;
// }

void matrix_scan_user(void) {

}

#endif///// end of defined(VIA_ENABLE) && defined(ENCODER_ENABLE)
//-----------------------------------------------------------------
#define HCS(report) host_consumer_send(record->event.pressed ? report : 0); return false
#define HSS(report) host_system_send(record->event.pressed ? report : 0); return false

static bool win_key_locked = false;

static uint8_t mac_keycode[4] = { KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_TGUI:
            if (record->event.pressed) {
                // Toggle GUI lock on key press
                win_key_locked = !win_key_locked;
              //  writePin(LED_JAMES1_PIN, !win_key_locked);
            }
            return false;   // break;
        case KC_LGUI:
            if (win_key_locked) { return false; }
            return false;   // break;

        case KC_STER:
//            if (record->event.pressed) {  backlight_step(); }
            return false;   // break;
        case KC_SPDI:
//            if (record->event.pressed) {  backlight_toggle(); }
            return false;   // break;
        case KC_SPDD:
//            if (record->event.pressed) {  breathing_toggle(); }
            return false;   // break;

        case KC_MISSION_CONTROL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LAUNCHPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false;  // Skip all further processing of this key

/*        case KC_TASK:
        case KC_FLXP:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    register_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            } else {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    unregister_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            }
            return false;  // Skip all further processing of this key
            */
        case KC_WIN_MODE:
            set_single_persistent_default_layer(0);
            return false;
        case KC_MAC_MODE:
            set_single_persistent_default_layer(2);
            // default_layer_set(1UL << 2);
            //    layer_off(0);
            //    layer_off(1);            
            return false;

        default:
            return true;   // Process all other keycodes normally
    }
}

//---------------------
/* #ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_user(uint8_t index, bool active) {
        if (index == 0){
            default_layer_set(1UL << (active ? 2 : 0));
        }
    return true;
#endif // DIP_SWITCH_ENABLE */

//---------------------

#ifdef OLED_ENABLE

bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case WIN_BASE:
            oled_write_P(PSTR("WINdows\n"), false);
            break;
        case WIN_FN:
            oled_write_P(PSTR("WIN-FN\n"), false);
            break;
        case MAC_BASE:
            oled_write_P(PSTR("MACintosh\n"), false);
            break;
        case MAC_FN:
            oled_write_P(PSTR("MAC-FN\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("error?"), false);
    }

    oled_write_P(PSTR("---------------\n"), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM  ") : PSTR("     "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP  ") : PSTR("     "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR  ") : PSTR("     "), false);

    return false;
}

// oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//     return OLED_ROTATION_0;
// }

// static void render_logo(void) {

//     static const char PROGMEM qmk_logo[] = {
//         0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
//         0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
//         0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
//     };
//     oled_write_P(qmk_logo, false);
// }
// // OLED
// bool oled_task_user(void) {

//     togglePin(LED_JAMES1_PIN);

//     render_logo();
//     //oled_scroll_right(); 이부분은 주석끄면 로고가 스크롤됩니다 안꺼도 config.h에서 준 시간 이후 스크롤됩니다
//      return false;
// }

#endif
//----------------------------------
