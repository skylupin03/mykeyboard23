/* Copyright 2021 Maxime Coirault, Don Kjer, Tyler Tidman
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

#include QMK_KEYBOARD_H

// Layer shorthand
enum _layer {
    WIN_BASE = 0,
    WIN_FN,
    MAC_BASE,
    MAC_FN
};

#define KC_WINM KC_WIN_MODE
#define KC_MACM KC_MAC_MODE

#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD

#define KC_SPLT KC_SPOTLIGHT
#define KC_SIRI KC_DICTATION
#define KC_DOND KC_DO_NOT_DISTURB
#define KC_LOCK_ KC_LOCK_SCREEN

//#define KC_TASK KC_TASK_VIEW
//#define KC_FLXP KC_FILE_EXPLORER

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)


// extern static bool win_key_locked;

// static uint8_t mac_keycode[4] = { KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD };

// typedef struct PACKED {
//     uint8_t len;
//     uint8_t keycode[2];
// } key_combination_t;

// key_combination_t key_comb_list[2] = {
//     {2, {KC_LWIN, KC_TAB}},
//     {2, {KC_LWIN, KC_E}}
// };

// Tap dance declarations (These must go above the keymaps)
enum {
  TD_NLCK_CALC = 0,
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

// Tapdance definitions. Tap Dance F Keys.
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_NLCK_CALC] = ACTION_TAP_DANCE_DOUBLE(KC_NUM_LOCK, KC_CALC),
    [TD_2] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MSEL),
    [TD_3] = ACTION_TAP_DANCE_DOUBLE(KC_FLXP, KC_MYCM),
    [TD_4] = ACTION_TAP_DANCE_DOUBLE(KC_MSEL, KC_MAIL),
    [TD_5] = ACTION_TAP_DANCE_FN(dance_test),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BASE: Base Layer (Default Layer)
   * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
   * │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PSc│Slk│Pse│
   * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
   * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│Hom│PgU│ │Num│ / │ * │ - │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
   * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ │Del│End│PgD│ │ 7 │ 8 │ 9 │   │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬┈┈┈┈┤ └───┴───┴───┘ ├───┼───┼───┤ + │
   * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │Entr│               │ 4 │ 5 │ 6 │   │
   * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤     ┌───┐     ├───┼───┼───┼───┤
   * │Shft│ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │     │ ↑ │     │ 1 │ 2 │ 3 │   │
   * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤Ent│
   * │Ctrl│GUI │Alt │                        │ Alt│Func│ App│Ctrl│ │ ← │ ↓ │ → │ │   0   │ . │   │
   * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘

      KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SCRL, KC_PAUS,
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,    TD(TD_NLCK_CALC), KC_PSLS, KC_PAST, KC_PMNS,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
      RALT_T(KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,                                   KC_P4,   KC_P5,   KC_P6,
      OSM(KC_LSFT), KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,               KC_P1,   KC_P2,   KC_P3,   KC_PENT,
      KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,MO(WIN_FN),KC_APP, KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT
  ),
  OSM(MOD_LGUI) --> 이키는 락기능에서 손봐야 함
   */
  [WIN_BASE] = LAYOUT_all( /* Base Layer */
      KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SCRL, KC_PAUS,
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,  TD(TD_NLCK_CALC),KC_PSLS,KC_PAST,KC_PMNS,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
      RALT_T(KC_CAPS),KC_A,KC_S,  KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,                                  KC_P4,   KC_P5,   KC_P6,
      OSM(MOD_LSFT),KC_NUBS,KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,         KC_RSFT,             KC_UP,              KC_P1,   KC_P2,   KC_P3,   KC_PENT,
      OSM(MOD_LCTL), OSM(MOD_LGUI), OSM(MOD_LALT),          KC_SPC,                             KC_RALT,MO(WIN_FN),KC_APP, KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT
  ),
  /* Keymap _FN: Function Layer
   * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
   * │Firm   │Ply│Stp│Prv│Nxt│ │Mut│Vo+│Vo-│   │ │   │   │   │   │ │   │   │   │
   * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
   * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │ │   │   │   │ │   │   │   │   │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
   * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │ │   │   │   │ │   │   │   │   │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬┈┈┈┈┤ └───┴───┴───┘ ├───┼───┼───┤   │
   * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │               │   │   │   │   │
   * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤     ┌───┐     ├───┼───┼───┼───┤
   * │    │   │   │   │   │   │   │   │   │   │   │   │          │     │   │     │   │   │   │   │
   * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤   │
   * │    │Lock│    │                        │    │Func│ Sys│    │ │   │   │   │ │       │   │   │
   * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘
   * 
   *  EE_CLR,  QK_RBT,
   * 
   *      QK_BOOT,          KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_TASK, KC_FLXP, KC_MSEL, KC_BRIU, KC_BRID,    _______, NK_ON, NK_OFF,
      DM_RSTP, DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______, _______, _______, _______,  EE_CLR,    BL_ON,   BL_TOGG, BL_STEP,    KC_CALC, KC_ACL0, KC_ACL1, KC_ACL2,
      _______, _______, KC_WINM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  QK_RBT,    BL_OFF,  BL_BRTG, KC_STER,    KC_BTN4, KC_MS_U,  KC_BTN5, KC_WH_U,
      CL_SWAP, _______, _______, _______, _______, _______, _______, _______, _______, QK_LOCK, _______,  _______, _______, _______,                                 KC_MS_L, KC_BTN3,  KC_MS_R,
        AS_ON, _______, AS_DOWN,   AS_UP, CW_TOGG, OS_ON, OS_OFF, _______, KC_MACM, _______, _______,  AS_RPT,           AS_OFF,              BL_INC,             KC_WH_L, KC_MS_D,  KC_WH_R, KC_WH_D,
      CL_NORM, KC_TGUI, _______,                            _______,                            _______, _______, _______, _______,    KC_SPDD,  BL_DEC, KC_SPDI,    KC_BTN1,           KC_BTN2

   */
  [WIN_FN] = LAYOUT_all( /* Function Layer */
      QK_BOOT,          TD(TD_2),TD(TD_5), KC_MPRV, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,KC_TASK,TD(TD_3),TD(TD_4), KC_BRIU, KC_BRID,    _______,    NK_ON, NK_OFF,
      DM_RSTP, DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______, _______, _______, _______,  EE_CLR,    BL_ON,   BL_TOGG, BL_STEP,    KC_CALC, KC_ACL0, KC_ACL1, KC_ACL2,
      _______, _______, KC_WINM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  QK_RBT,    BL_OFF,  BL_BRTG, KC_STER,    KC_BTN4, KC_MS_U,  KC_BTN5, KC_WH_U,
      CL_SWAP, DT_DOWN, DT_UP, _______, DT_PRNT, _______, _______, _______, _______, QK_LOCK, _______,  _______, _______, _______,                                 KC_MS_L, KC_BTN3,  KC_MS_R,
        AS_ON, _______, AS_DOWN,   AS_UP, CW_TOGG, AS_RPT, _______, _______, KC_MACM, _______,   OS_ON,  OS_OFF,           AS_OFF,              BL_INC,             KC_WH_L, KC_MS_D,  KC_WH_R, KC_WH_D,
      CL_NORM, KC_TGUI, _______,                            _______,                            _______, _______, QK_LEAD, _______,    KC_SPDD,  BL_DEC, KC_SPDI,    KC_BTN1,           KC_BTN2
  ),
/*
  [MAC_BASE] = LAYOUT_all( // Layer 3 
      KC_ESC,           KC_BRID, KC_BRIU, KC_MCTL, KC_SPLT, KC_SIRI, KC_DOND, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,    KC_LPAD, KC_SCRL, KC_LOCK_,
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,    TD(TD_NLCK_CALC), KC_PSLS, KC_PAST, KC_PMNS,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,                                   KC_P4,   KC_P5,   KC_P6,
      KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,               KC_P1,   KC_P2,   KC_P3,   KC_PENT,
      KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI,MO(MAC_FN),KC_RALT,KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT
  ),
  */
  [MAC_BASE] = LAYOUT_all( /* Layer 3 */
      KC_ESC,           KC_BRID, KC_BRIU, KC_MCTL, KC_SPLT, KC_SIRI, KC_DOND, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,    KC_LPAD, KC_SCRL, KC_LOCK_,
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,    TD(TD_NLCK_CALC), KC_PSLS, KC_PAST, KC_PMNS,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,                                   KC_P4,   KC_P5,   KC_P6,
      KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,               KC_P1,   KC_P2,   KC_P3,   KC_PENT,
      KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI,MO(MAC_FN),KC_RALT,KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT
  ),
  [MAC_FN] = LAYOUT_all( /* Layer 4 */
      QK_BOOT,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_F13,   KC_F14,  KC_F15,
      DM_RSTP, DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______, _______, _______, _______, _______,    BL_ON,   BL_TOGG, BL_STEP,    KC_CALC, KC_ACL0, KC_ACL1, KC_ACL2,
      _______, _______, KC_WINM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    BL_OFF,  BL_BRTG, KC_STER,    _______, KC_MS_U, _______, KC_WH_U,
      CL_SWAP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                                  KC_MS_L, _______, KC_MS_R,
        AS_ON, _______, AS_DOWN,   AS_UP, CW_TOGG, OS_ON, OS_OFF, _______, KC_MACM, _______, _______,  AS_RPT,           AS_OFF,                 BL_INC,             _______, KC_MS_D, _______, KC_WH_D,
      CL_NORM, _______, KC_TGUI,                            _______,                            _______, _______, _______, _______,    KC_SPDD,  BL_DEC, KC_SPDI,    KC_BTN1,          KC_BTN2
  )
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
 //   oled_write_P(PSTR("Layer: "), false);

//    switch (get_highest_layer(layer_state)) {           // layer_state -> MAC_BASE일떄 WIN_BASE로 체크되는 문제 
     switch (get_highest_layer(default_layer_state)) {    // default_layer_state -> FN layer는 체크되지 않는 문제 
        case WIN_BASE:                                    // Booting떄 초기화루틴에서는 잘못 가져옴
            oled_write_P(PSTR(" Windows Mode \n"), false);
//            default_layer_set(1UL << 0);
//            set_single_persistent_default_layer(0);
//            layer_off(2);
//            layer_on(0);
            writePinHigh(LED_MR_LOCK_PIN);
            break;
        case WIN_FN:
            oled_write_P(PSTR(" Win-Function \n"), false);
            break;
        case MAC_BASE:
            oled_write_P(PSTR(" Macintosh Mode\n"), true);
//            default_layer_set(1UL << 2);
//            set_single_persistent_default_layer(2);
//            layer_off(0);
//            layer_on(2);
            writePinLow(LED_MR_LOCK_PIN);
            break;
        case MAC_FN:
            oled_write_P(PSTR(" MAC-Function \n"), true);
            break;            
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    oled_write_P(PSTR("---------------\n"), false);
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    
    oled_write_P(PSTR("-"), false);
  
    oled_write_P(IS_LAYER_ON(0) ? PSTR("1 ") : PSTR("0 "), false);
    oled_write_P(IS_LAYER_ON_STATE(layer_state,1) ? PSTR("1 ") : PSTR("0 "), false);
    oled_write_P(IS_LAYER_ON_STATE(layer_state,2) ? PSTR("1 ") : PSTR("0 "), false);
    oled_write_P(IS_LAYER_ON_STATE(layer_state,3) ? PSTR("1 ") : PSTR("0 "), false);

    return false;
}
#else

bool isRecording = false;           // dynamic macro LED
bool isRecordingLedOn = false;
static uint16_t recording_timer;
bool isAutoShiftOn = false;         // AutoShift function LED
bool AutoShiftLED  = false;
static uint16_t AutoShift_timer;

//static bool win_key_locked = false;
//extern static bool win_key_locked;

LEADER_EXTERNS();

void matrix_scan_user(void) {
    
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_D) {
            SEND_STRING("Metable K310 STD");
    //        did_leader_succeed = true;
        }
        SEQ_TWO_KEYS(KC_P, KC_1) {
            SEND_STRING("Durgod Keyboard");
    //        did_leader_succeed = true;
        }
        SEQ_TWO_KEYS(KC_P, KC_2) {
            SEND_STRING("Forida Multi Hub");
    //        did_leader_succeed = true;
        } 
        SEQ_THREE_KEYS(KC_C, KC_C, KC_C) {
            SEND_STRING("Metable is GREAT!!!");
        }
        SEQ_FOUR_KEYS(KC_F, KC_I, KC_R, KC_M) {
            bootloader_jump();
        }
        SEQ_FIVE_KEYS(KC_R, KC_E, KC_S, KC_E, KC_T) {
            SEND_STRING("ReBoot!!");
            soft_reset_keyboard();      // reset_keyboard()
        }
    }

    /*
     switch (get_highest_layer(default_layer_state)) {    // default_layer_state -> FN layer는 체크되지 않는 문제 
        case WIN_BASE:    
        case WIN_FN:                                // Booting떄 초기화루틴에서는 잘못 가져옴
//            default_layer_set(1UL << 0);
//            set_single_persistent_default_layer(0);
//            layer_off(2);
//            layer_on(0);
            writePinHigh(LED_MR_LOCK_PIN);


            break;
        case MAC_BASE:
        case MAC_FN:        
//            default_layer_set(1UL << 2);
//            set_single_persistent_default_layer(2);
//            layer_off(0);
//            layer_on(2);
            writePinLow(LED_MR_LOCK_PIN);

            break;
    }
    */
    if (get_autoshift_state()){
        if(isAutoShiftOn){
            if(timer_elapsed(AutoShift_timer) >500){
                AutoShift_timer = timer_read();
                AutoShiftLED    = !AutoShiftLED;
                writePin(LED_MR_LOCK_PIN, !AutoShiftLED);
            }
        }
        else{
            isAutoShiftOn = true;
            AutoShift_timer = timer_read();
            AutoShiftLED    = true;
            writePin(LED_MR_LOCK_PIN, !AutoShiftLED);
        }
    }
    else{
        isAutoShiftOn = false;
        switch (get_highest_layer(default_layer_state)) {    // default_layer_state -> FN layer는 체크되지 않는 문제 
            case WIN_BASE:    
            case WIN_FN:                                // Booting떄 초기화루틴에서는 잘못 가져옴
                writePinHigh(LED_MR_LOCK_PIN);
                break;
            case MAC_BASE:
            case MAC_FN:        
                writePinLow(LED_MR_LOCK_PIN);
                break;
        }      
    }

    if (isRecording){
        if(timer_elapsed(recording_timer) > 500)
        {
            isRecordingLedOn = !isRecordingLedOn;
            recording_timer  = timer_read();
            writePin(LED_WIN_LOCK_PIN, !isRecordingLedOn); 
        }
    }
    else{
//            writePin(LED_WIN_LOCK_PIN, !win_key_locked);       
    }
}
#endif

void dynamic_macro_record_start_user(void) {
    isRecording = true;
    isRecordingLedOn = true;
                writePin(LED_WIN_LOCK_PIN, !isRecordingLedOn); 

    recording_timer = timer_read();
}
void dynamic_macro_record_end_user(int8_t direction)
{
    isRecording = false;
    isRecordingLedOn = false;
}
//----------------------------------

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
/*
    switch (keycode) {
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
    }
*/
    return true;
}

// void rgb_matrix_indicators_user(void)
// {

// }

bool rgb_matrix_indicators_user(void)
{
    return TRUE;
}

/*  레이어 인식을 잘 못함 
layer_state_t layer_state_set_user(layer_state_t state) {
    if (layer_state_cmp(state, MAC_BASE)||layer_state_cmp(state,MAC_FN)) {
        autoshift_disable();
//        autoshift_enable();        
                        writePinHigh(LED_MR_LOCK_PIN);

    } else { 
        autoshift_enable();  
                                writePinLow(LED_MR_LOCK_PIN);   
    }
    return state;
} */

void ieader_start_user(void){
//    writePinLow(LED_MR_LOCK_PIN); //동작안함
}

void leader_end_user(void){
//    writePinHigh(LED_MR_LOCK_PIN); //동작안함
}