#include QMK_KEYBOARD_H

#define BASE 0
#define FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT(
		KC_PSCR, KC_SCRL, KC_PAUS, KC_MUTE,
		KC_INS, KC_HOME, KC_PGUP, LT(1,KC_NUM), KC_PSLS, KC_PAST, KC_PMNS, 
		KC_DEL, KC_END, KC_PGDN, KC_P7, KC_P8, KC_P9, KC_PPLS, 
		KC_P4, KC_P5, KC_P6, 
		KC_UP, KC_P1, KC_P2, KC_P3, 
		KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT, KC_PENT),
		
	[FN] = LAYOUT(
		EE_CLR, KC_SCRL, KC_PAUS, KC_BSPC, 
		KC_INS, KC_HOME, KC_PGUP, KC_TRNS, RGB_MOD, RGB_VAD, RGB_VAD, 
		KC_DEL, KC_END, KC_PGDN, KC_P7, KC_P8, RGB_SAI, RGB_VAI,
		KC_P4, KC_P5, RGB_SPD, 
		KC_UP, KC_P1, KC_P2, KC_P3, 
		KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT, KC_PENT),

};

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        /* Top-right encoder (scanning) */
        case 0:
            tap_code(clockwise ? KC_VOLD : KC_VOLU);
            break;
    }

    return false;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  debug_mouse=true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

bool oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_P(PSTR("[MigitePad]"), false);
  switch (get_highest_layer(layer_state)) {
    case BASE:
      oled_write_ln_P(PSTR(""), false);
      break;
    case FN:
      oled_write_ln_P(PSTR("FN"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undef"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P( led_state.num_lock == 1 ? PSTR("NLCK ") : PSTR("     "), false);
  oled_write_P( led_state.caps_lock == 1 ? PSTR("CAPS ") : PSTR("       "), false);
  oled_write_P( led_state.scroll_lock == 1 ? PSTR("SCRLK") : PSTR("       "), false);
  
  return false;
}
#endif