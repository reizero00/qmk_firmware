/* Copyright 2018 Jack Humbert
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

#define BASE 0
#define FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[BASE] = LAYOUT(
		LCTL(KC_COMMA), LCTL(KC_SLASH), LCTL(KC_DOT),
		KC_4, KC_5, KC_6,
		KC_1, KC_2, KC_3,
		KC_MPLY, KC_MPRV, KC_MNXT
	),
  
	[FN] = LAYOUT(
		KC_TRNS, KC_HOME, KC_PGUP,
		KC_TRNS, KC_END, KC_PGDN,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_ENT
	)
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            default:
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                clockwise ? tap_code16(KC_TAB) : tap_code16(S(KC_TAB));
                alt_tab_timer = timer_read();
                break;
        }
    }
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 600) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
#endif