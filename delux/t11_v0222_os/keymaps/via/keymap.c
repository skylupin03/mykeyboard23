#include QMK_KEYBOARD_H

#ifdef OS_DETECTION_ENABLE
    #include "os_detection.h"   // os_variant_t detected_host_os (void);
// static os_variant_t OS_detect;
#endif

//#include "k20emul2.h"

#ifdef OLED_ENABLE      
    static void render_logo_font(void);
#endif

uint16_t startup_timer;
static bool finished_timer = false;

enum layers {   WIN_BASE,
                WIN_FN,
                MAC_BASE,
                MAC_FN,
                LINUX_BASE,
                LINUX_FN
            };

enum K20_keycodes {
#ifdef VIA_ENABLE
    KC_TGUI = QK_KB_0,   // Toggle between GUI Lock or Unlock
    KC_WIN_MODE,             // WINDOWS Keyboard(layer)로 변경
    KC_MAC_MODE,             // Machintosh Keyboard(layer)로 변경
    KC_LINUX_MODE,             // LINUX 모드(TEST)
    // KC_MISSION_CONTROL,     // MAC_key
    // KC_LAUNCHPAD,           // MAC_key
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
    KC_LINUX_MODE,             // LINUX 모드(TEST)    
    // KC_MISSION_CONTROL,     // MAC_key
    // KC_LAUNCHPAD,           // MAC_key
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
#define KC_LINM KC_LINUX_MODE
#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD
#define KC_SPLT KC_SPOTLIGHT
#define KC_SIRI KC_DICTATION
#define KC_DOND KC_DO_NOT_DISTURB
#define KC_LSCR KC_LOCK_SCREEN

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

void keyboard_post_init_user(void) {
    // Read the user config from EEPROM
    // kvm_pc_sel = 0;
    // kvm_switch(kvm_pc_sel);

    // user_config.raw = eeconfig_read_user();
    // kvm_pc_sel      = user_config.eeprom_kvm_pc_sel;
    // kvm_switch(kvm_pc_sel);
#ifdef OS_DETECTION_ENABLE
//     switch (detected_host_os()) {
//         case OS_UNSURE:
//             oled_write_P(PSTR("OS_UNSURE"), false);
//             break;
//         case OS_LINUX:
//             oled_write_P(PSTR("OS_LINUX"), false);
//             break;
//         case OS_WINDOWS:
//             oled_write_P(PSTR("OS_WINDOWS"), false);
//             break;
//         case OS_MACOS:
//             oled_write_P(PSTR("OS_MACOS"), false);
//             break;
//         case OS_IOS:
//             oled_write_P(PSTR("OS_IOS"), false);
//             break;
//         default:
//             oled_write_P(PSTR("Unknown"), false);
// }
//    OS_detect = detect_host_os();
 #endif
}


void dance_test(tap_dance_state_t *state, void *user_data){
    if(state->count >=5){
        SEND_STRING("Tap Dance Test ok!");
        reset_tap_dance(state);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_NCAL] = ACTION_TAP_DANCE_DOUBLE(KC_NUM_LOCK, KC_CALC),
    [TD_2] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MSEL),
    [TD_3] = ACTION_TAP_DANCE_DOUBLE(KC_FLXP, KC_MYCM),
    [TD_4] = ACTION_TAP_DANCE_DOUBLE(KC_MSEL, KC_MAIL),
    [TD_5] = ACTION_TAP_DANCE_FN(dance_test),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_BASE] = LAYOUT(TD(TD_NCAL), KC_F1,     KC_F2,     KC_F3, 
                        KC_ESC,       KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,     KC_DEL,
                        KC_TAB,       KC_7,      KC_8,      KC_9,      KC_0,    KC_EQL,    KC_ENT, 
                        KC_LSFT,      KC_Z,      KC_X,      KC_C,      KC_V,
                        KC_LCTL,MO(WIN_FN),   KC_LALT,    KC_SPC,                       KC_MUTE),

    [WIN_FN] = LAYOUT(  QK_BOOT,   KC_WINM,   KC_MACM,   KC_LINM, 
                        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
                        _______,   RGB_SPI,   RGB_HUI,   RGB_SAI,   _______,   _______,   _______, 
                        _______,   RGB_SPD,   RGB_HUD,   RGB_SAD,   _______,
                        EE_CLR,    _______,    QK_RBT,   RGB_MOD,                         RGB_TOG ),

    [MAC_BASE] = LAYOUT(TD(TD_NCAL), KC_F1,     KC_F2,     KC_F3, 
                        KC_ESC,       KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,     KC_DEL,
                        KC_TAB,       KC_7,      KC_8,      KC_9,      KC_0,    KC_EQL,    KC_ENT, 
                        KC_LSFT,      KC_Z,      KC_X,      KC_C,      KC_V,
                        KC_LCTL,MO(MAC_FN),   KC_LALT,    KC_SPC,                       KC_MUTE),

    [MAC_FN] = LAYOUT(  QK_BOOT,   KC_WINM,   KC_MACM,   KC_LINM, 
                        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
                        _______,   RGB_SPI,   RGB_HUI,   RGB_SAI,   _______,   _______,   _______, 
                        _______,   RGB_SPD,   RGB_HUD,   RGB_SAD,   _______,
                        EE_CLR,    _______,    QK_RBT,   RGB_MOD,                         RGB_TOG ),

    [LINUX_BASE] = LAYOUT(TD(TD_NCAL), KC_F1,     KC_F2,     KC_F3, 
                        KC_ESC,       KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,     KC_DEL,
                        KC_TAB,       KC_7,      KC_8,      KC_9,      KC_0,    KC_EQL,    KC_ENT, 
                        KC_LSFT,      KC_Z,      KC_X,      KC_C,      KC_V,
                        KC_LCTL,MO(LINUX_FN),   KC_LALT,    KC_SPC,                       KC_MUTE),

    [LINUX_FN] = LAYOUT(QK_BOOT,   KC_WINM,   KC_MACM,   KC_LINM, 
                        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
                        _______,   RGB_SPI,   RGB_HUI,   RGB_SAI,   _______,   _______,   _______, 
                        _______,   RGB_SPD,   RGB_HUD,   RGB_SAD,   _______,
                        EE_CLR,    _______,    QK_RBT,   RGB_MOD,                         RGB_TOG )                     
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

// #define NUM_ENCODERS 2
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [LINUX_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LINUX_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
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

    finished_timer = true;

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
        case KC_LINUX_MODE:
            set_single_persistent_default_layer(4);
            return false;            

        case QK_BOOT:
            if (record->event.pressed) {
                #ifdef OLED_ENABLE                
                    oled_clear();                    //               on_all_leds();
                    render_logo_font();         
                #endif
            }
            return true; 
            
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

// uint16_t startup_timer;
// static bool finished_timer = false;

static const char logo_MS[] = {0x97,0x98,0x00, 0xB7,0xB8,0x00}; 
static const char logo_APPLE[] = {0x95,0x96,0x00, 0xB5,0xB6,0x00};
static const char logo_Linux[] = {0x99,0x9A,0x00, 0xB9,0xBA,0x00}; 

// void init_timer(void){
//    startup_timer = timer_read32();
// };

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    startup_timer = timer_read();
    return rotation;                    //    return OLED_ROTATION_180; // flips the display 180 degrees if offhand 
}

// static void render_logo(void) {
//     static const char PROGMEM raw_logo[] = {
//         240,248,252,252,254,254,222,206,238,238,238,238,238,206,206, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,254,254,252,252,248,248,  0,  0,  0,  0, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,  0,  0,  0,  0,254,254,254,254,254,254,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
//         0,254,254,254,254,254,254,255,255,255,255,255,255,  1,  1,  1,  3,  3,  3,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,  0,  0,  0,  0, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 24,  0,  0,  0,  0,255,255,255,255,255,255, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
//         60,255,255,255,255,255,255, 31, 63, 63,127,127,127,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,127,127,127,127, 31, 31,  0,  0,  0,  0,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112, 96, 96,  0,  0,  0, 
//         0,127,127,127,127,127,127,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,127,127,127,127,127,127,
//     };
//     oled_write_raw_P(raw_logo, sizeof(raw_logo));
// }

// static void render_logo(void) {     // logo 1
//     static const char PROGMEM raw_logo[] = {
//         0,  0,  0,  0,  0,  0,240,248, 24, 24, 24, 24, 24,248,248, 24, 24, 24, 24, 24,240,224,  0,240,240, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0, 24, 24, 24, 24, 24, 24, 24,248,248, 24, 24, 24, 24, 24, 24, 24,  0,240,240, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,248,240,  0,248,248, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,240,240,  0,240,248,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,240, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0,  0,  0,  0,  0,  0,  0,
//         0,  0,  0,  0, 63, 63,  0,  0,  0,  0,  0, 63, 63,  0,  0,  0,  0,  0, 63, 63,  0, 63, 63, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,  0,  0,  0,  0,  0,  0,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0, 63, 63,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3, 63, 63,  0, 63, 63, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 63, 63,  0, 63, 63, 32, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,  0, 31, 63, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,  0,  0,  0,  0,  0,  0,
//     };
//     oled_write_raw_P(raw_logo, sizeof(raw_logo));
// }

static void render_logo_font(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
}
/*
void render_info(void){

    oled_set_cursor(0, 0);
//     oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state|default_layer_state)) {
        case WIN_BASE:
            oled_write_P(logo_MS, false);
            oled_write_P(PSTR(" Layer: WINdows\n"), false);    
            oled_write_P(logo_MS+3, false);      
            oled_write_ln_P(PSTR(" ---------------"), false);       // oled_write_ln_P 함수 테스트
            break;
        case WIN_FN:
            oled_write_P(logo_MS, false);        
            oled_write_P(PSTR(" Layer: WIN-FN\n"), false);
            break;
        case MAC_BASE:
            oled_write_P(logo_APPLE, false);
            oled_write_P(PSTR(" Layer: MACintosh\n"), false);
            oled_write_P(logo_APPLE+3, false);        
            oled_write_P(PSTR(" ---------------\n"), false);         
            break;
        case MAC_FN:
            oled_write_P(logo_APPLE, false);        
            oled_write_P(PSTR(" Layer: MAC-FN\n"), false);
            break;

        case LINUX_BASE:
            oled_write_P(logo_Linux, false);
            oled_write_P(PSTR(" Layer: Linux\n"), false);
            oled_write_P(logo_Linux+3, false);        
            oled_write_P(PSTR(" ---------------\n"), false);         
            break;
        case LINUX_FN:
            oled_write_P(logo_Linux, false);        
            oled_write_P(PSTR(" Layer: Linux-FN\n"), false);
            break;            
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("error?"), false);
    }
//    oled_write_P(PSTR("---------------\n"), false);
        oled_set_cursor(3, 2);   
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM  ") : PSTR("     "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP  ") : PSTR("     "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR  ") : PSTR("     "), false);
}
//---------------------------------------
// static void render_rgbled_status(void) {
//     char string[4];

//     oled_set_cursor(0, 3);   
//     if (rgb_matrix_is_enabled()) {
//         oled_write("RGB", true);    
//         uint16_t m = rgb_matrix_get_mode();
//         string[3] = '\0';
//         string[2] = '0' + m % 10;
//         string[1] = ( m /= 10) % 10 ? '0' + (m) % 10 : (m / 10) % 10 ? '0' : ' ';
//         string[0] =  m / 10 ? '0' + m / 10 : ' ';
//         oled_write_P(PSTR(" -"), false);
//         oled_write(string, false);

//         uint16_t h = rgb_matrix_get_hue()/RGBLIGHT_HUE_STEP;
//         string[3] = '\0';
//         string[2] = '0' + h % 10;
//         string[1] = ( h /= 10) % 10 ? '0' + (h) % 10 : (h / 10) % 10 ? '0' : ' ';
//         string[0] =  h / 10 ? '0' + h / 10 : ' ';
//         oled_write_P(PSTR(","), false);
//         oled_write(string, false);

//         uint16_t s = rgb_matrix_get_sat()/RGBLIGHT_SAT_STEP;
//         string[3] = '\0';
//         string[2] = '0' + s % 10;
//         string[1] = ( s /= 10) % 10 ? '0' + (s) % 10 : (s / 10) % 10 ? '0' : ' ';
//         string[0] =  s / 10 ? '0' + s / 10 : ' ';
//         oled_write_P(PSTR(","), false);
//         oled_write(string, false);

//         uint16_t v = rgb_matrix_get_val()/RGBLIGHT_VAL_STEP;
//         string[3] = '\0';
//         string[2] = '0' + v % 10;
//         string[1] = ( v /= 10) % 10 ? '0' + (v) % 10 : (v / 10) % 10 ? '0' : ' ';
//         string[0] =  v / 10 ? '0' + v / 10 : ' ';
//         oled_write_P(PSTR(","), false);
//         oled_write(string, false);
//         // oled_write_ln_P(PSTR("\n     MOD HUE SAT VAR"), false);    
//     } else {
//         oled_write_P(PSTR("RGB off , WPM = "), false);
//             oled_write(get_u8_str(get_current_wpm(), '0'), false);  //예제 키보드= adpenrose-akemipad
//     }
// }
*/


// 참고키보드 = 0xcb-1377, 0xcb-STATIC, adafruit-macropad
bool oled_task_user(void) {

#ifdef OS_DETECTION_ENABLE
    render_logo_font();  
    oled_set_cursor(0, 3);
    oled_write_P(PSTR(" OS Detected; "), false);
    switch (detected_host_os()) {
            case OS_UNSURE:
                    oled_write_P(PSTR("---?---"), false);
                    break;
            case OS_LINUX:
                    oled_write_P(PSTR("LINUX  "), false);
                    break;
            case OS_WINDOWS:
                    oled_write_P(PSTR("WINDOWS"), false);
                    break;
            case OS_MACOS:
                    oled_write_P(PSTR("MAC OS "), false);
                    break;
            case OS_IOS:
                    oled_write_P(PSTR("IOS    "), false);
                    break;
            default:
                    oled_write_P(PSTR("Unknown"), false);
    }
#endif

 //   static bool finished_timer = false;

//     if (!finished_timer && (timer_elapsed(startup_timer) < 20000)) {
// //        render_logo();
//         render_logo_font();  
//         oled_scroll_left(); // Turns on scrolling      // scroll하면 아래로 안감? oled_scroll_off();을 먼저해야 함
//     } else {
//         if (!finished_timer){
//             oled_scroll_off();
//             oled_clear();
//             finished_timer = true;
//         }
//        render_info();
//        oled_scroll_off();        
//        render_rgbled_status();
//    }
    return false;
}

/* 1upkeyboard-pi40
   switch (rgb_matrix_get_mode()) {
        case 1:
            oled_write_P(PSTR("Solid Color\n                  "), false);
            break;
        case 2:
            oled_write_P(PSTR("Alphas Mods\n                  "), false);
            break;
        case 3:
            oled_write_P(PSTR("Gradient Up Down\n                  "), false);
            break;
        case 4:
            oled_write_P(PSTR("Gradient Left Right\n                  "), false);
            break;
        case 5:
            oled_write_P(PSTR("Breathing\n                  "), false);
            break;
        case 6:
            oled_write_P(PSTR("Band Sat\n                  "), false);
            break;
        case 7:
            oled_write_P(PSTR("Band Val\n                  "), false);
            break;
        case 8:
            oled_write_P(PSTR("Band Pinwheel Sat\n                  "), false);
            break;
        case 9:
            oled_write_P(PSTR("Band Pinwheel Val\n                  "), false);
            break;
        case 10:
            oled_write_P(PSTR("Band Spiral Sat\n                  "), false);
            break;
        case 11:
            oled_write_P(PSTR("Band Spiral Val\n                  "), false);
            break;
        case 12:
            oled_write_P(PSTR("Cycle All\n                  "), false);
            break;
        case 13:
            oled_write_P(PSTR("Cycle Left Right\n                  "), false);
            break;
        case 14:
            oled_write_P(PSTR("Cycle Up Down\n                  "), false);
            break;
        case 15:
            oled_write_P(PSTR("Rainbow\nMoving Chevron    "), false);
            break;
        case 16:
            oled_write_P(PSTR("Cycle Out In\n                  "), false);
            break;
        case 17:
            oled_write_P(PSTR("Cycle Out In Dual\n                  "), false);
            break;
        case 18:
            oled_write_P(PSTR("Cycle Pinwheel\n                  "), false);
            break;
        case 19:
            oled_write_P(PSTR("Cycle Spiral\n                  "), false);
            break;
        case 20:
            oled_write_P(PSTR("Dual Beacon\n                  "), false);
            break;
        case 21:
            oled_write_P(PSTR("Rainbow Beacon\n                  "), false);
            break;
        case 22:
            oled_write_P(PSTR("Rainbow Pinwheels\n                  "), false);
            break;
        case 23:
            oled_write_P(PSTR("Raindrops\n                  "), false);
            break;
        case 24:
            oled_write_P(PSTR("Jellybean Raindrops\n                  "), false);
            break;
        case 25:
            oled_write_P(PSTR("Hue Breathing\n                  "), false);
            break;
        case 26:
            oled_write_P(PSTR("Hue Pendulum\n                  "), false);
            break;
        case 27:
            oled_write_P(PSTR("Hue Wave\n                  "), false);
            break;
        case 28:
            oled_write_P(PSTR("Pixel Rain\n                  "), false);
            break;
        case 29:
            oled_write_P(PSTR("Pixel Flow\n                  "), false);
            break;
        case 30:
            oled_write_P(PSTR("Pixel Fractal\n                  "), false);
            break;
        case 31:
            oled_write_P(PSTR("Typing Heatmap\n                  "), false);
            break;
        case 32:
            oled_write_P(PSTR("Digital Rain\n                  "), false);
            break;
        case 33:
            oled_write_P(PSTR("Solid Reactive\nSimple            "), false);
            break;
        case 34:
            oled_write_P(PSTR("Solid Reactive\n                  "), false);
            break;
        case 35:
            oled_write_P(PSTR("Solid Reactive\nWide              "), false);
            break;
        case 36:
            oled_write_P(PSTR("Solid Reactive\nMultiwide         "), false);
            break;
        case 37:
            oled_write_P(PSTR("Solid Reactive\nCross             "), false);
            break;
        case 38:
            oled_write_P(PSTR("Solid Reactive\nMulticross        "), false);
            break;
        case 39:
            oled_write_P(PSTR("Solid Reactive\nNexus             "), false);
            break;
        case 40:
            oled_write_P(PSTR("Solid Reactive\nMultinexus        "), false);
            break;
        case 41:
            oled_write_P(PSTR("Splash\n                  "), false);
            break;
        case 42:
            oled_write_P(PSTR("Multisplash\n                  "), false);
            break;
        case 43:
            oled_write_P(PSTR("Solid Splash\n                  "), false);
            break;
        case 44:
            oled_write_P(PSTR("Solid Multisplash\n                  "), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined\n                  "), false);
    }
*/
#endif
//----------------------------------
