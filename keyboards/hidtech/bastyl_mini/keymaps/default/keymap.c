/*
 * Copyright 2020 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2020 Anthony MARIN <anthony@hidtech.ca>
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

enum {
    DOT_TD = 0,
    ONE_SHOT_CAPS,
};

enum custom_keycodes {
    EMAIL = SAFE_RANGE,
    CAPSWRD,
};

bool caps_word_on = false;

void caps_word_enable(void) {
    caps_word_on = true;
    if (!(host_keyboard_led_state().caps_lock)) {
        tap_code(KC_CAPS);
    }
}

void caps_word_disable(void) {
    caps_word_on = false;
    if (host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
}

void caps_word_process_user(uint16_t keycode, const keyrecord_t *record) {
    // Update caps word state
    if (caps_word_on) {
        // Get the base keycode of a mod or layer tap key
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                // Earlier return if this has not been considered tapped yet
                if (record->tap.count == 0)
                    return;
                keycode = keycode & 0xFF;
                break;
            default:
                break;
        }

        switch (keycode) {
            // Keycodes to shift
            case KC_A ... KC_Z:
                if (record->event.pressed)
                    caps_word_enable();
            // Keycodes to ignore (don't disable caps word), but not to shift
            case KC_MINS:
            case KC_BSPC:
            case KC_UNDS:
            case CAPSWRD:
                // If mod chording disable the mods
                if (record->event.pressed && (get_mods() != MOD_LSFT) && (get_mods() != 0)) {
                    caps_word_disable();
                }
                break;
            default:
                if (record->event.pressed)
                    caps_word_disable();
                break;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    caps_word_process_user(keycode, record);

    switch (keycode) {
        case EMAIL:
            if (record->event.pressed) {
                SEND_STRING("matas234@gmail.com");
            }
            break;
    }
    return true;
};



void sentence_end(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {

        // Double tapping TD_DOT produces
        // ". <one-shot-shift>" i.e. dot, space and capitalize next letter.
        // This helps to quickly end a sentence and begin another one
        // without having to hit shift.
        case 2:
            /* Check that Shift is inactive */
            if (!(get_mods() & MOD_MASK_SHIFT)) {
                tap_code(KC_SPC);
                /* Internal code of OSM(MOD_LSFT) */
                set_oneshot_mods(MOD_BIT(KC_LSHIFT) | get_oneshot_mods());

            } else {
                // send ">" (KC_DOT + shift → ">")
                tap_code(KC_DOT);
            }
            break;

        // Since `sentence_end` is called on each tap
        // and not at the end of the tapping term,
        // the third tap needs to cancel the effects
        // of the double tap in order to get the expected
        // three dots ellipsis.
        case 3:
            // remove the added space of the double tap case
            tap_code(KC_BSPC);
            // replace the space with a second dot
            tap_code(KC_DOT);
            // tap the third dot
            tap_code(KC_DOT);
            break;

        // send KC_DOT on every normal tap of TD_DOT
        default:
            tap_code(KC_DOT);
    }
};

void one_shot_caps(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            caps_word_enable();
            break;
        default:
            set_oneshot_mods(MOD_LSFT);
    }
};

qk_tap_dance_action_t tap_dance_actions[] = {
      [DOT_TD] = ACTION_TAP_DANCE_FN_ADVANCED(sentence_end, NULL, NULL),
      [ONE_SHOT_CAPS] = ACTION_TAP_DANCE_FN(one_shot_caps),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
    EMAIL,   KC_Q, KC_W, KC_E, KC_R, KC_T,	                                KC_Y, KC_U, KC_I,    KC_O,   KC_P,     LT(5,RGB_TOG),
//-------------------------------------------------//-----------------------------------------------------------//
    _______, LALT_T(KC_A), LCTL_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,      KC_H, LSFT_T(KC_J), LGUI_T(KC_K), LCTL_T(KC_L), KC_SCLN, KC_QUOT,
//-------------------------------------------------//-----------------------------------------------------------//
    _______, KC_Z, KC_X, KC_C, KC_V, KC_B,                                  KC_N, KC_M, KC_COMM, TD(DOT_TD), KC_SLSH,  RGB_VAD,
//-------------------------------------------------//-----------------------------------------------------------//
           LT(4,KC_TAB), LT(1,KC_BSPC), TD(ONE_SHOT_CAPS),                KC_ENT, LT(2,KC_SPC), LT(3,KC_ESC)
  ),

  [1] = LAYOUT(
    _______, _______, _______, _______, _______, _______,		_______, KC_7,   KC_8,   KC_9,   _______,  _______,
//---------------------------------------------------------//-----------------------------------------------------------//
    _______, _______, _______, KC_PPLS, KC_PAST, _______,	    KC_DOT, KC_4,   KC_5,   KC_6,   _______,  _______,
//---------------------------------------------------------//-----------------------------------------------------------//
    _______, _______, _______, KC_MINS, KC_SLSH, _______,       KC_COMM, KC_1,   KC_2,   KC_3,   _______,   _______,
//---------------------------------------------------------//-----------------------------------------------------------//
                               _______, LT(1,KC_BSPC), _______,		    KC_LSFT, KC_0, KC_EQL
  ),

  [2] = LAYOUT(
    _______, _______,  KC_PIPE,   KC_ASTR, KC_AMPR, KC_PLUS,		  KC_MINS, KC_LBRC, KC_CIRC, KC_RBRC, _______,  RESET,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, KC_TILD,  KC_EXLM,  KC_EQL,  KC_AT,   	      KC_UNDS, KC_LPRN, KC_DLR,  KC_RPRN,  _______,  EEP_RST,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, KC_LT,    KC_GT,   KC_GRV,  KC_PERC,        KC_BSLS, KC_LCBR, KC_HASH, KC_RCBR, _______,  _______,
//---------------------------------------------------------//--------------------------------------------------------------//
                               _______, KC_DEL, _______,		    _______, LT(2,KC_SPC), _______
  ),

  [3] = LAYOUT(
    _______, _______,  _______,   _______, _______, _______,		  KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______,  _______,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, _______, KC_CUT, KC_COPY, KC_PSTE,     	    KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,  _______,  _______,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, _______, _______, KC_UNDO, KC_AGIN,        _______, KC_PSCR, LGUI(KC_INS), G(S(KC_INS)),_______,  _______,
//---------------------------------------------------------//--------------------------------------------------------------//
                               _______, LCTL(KC_BSLS), _______,		    _______, _______, LT(3,KC_ESC)
  ),

  [4] = LAYOUT(
    _______, _______,  _______,   _______, _______, _______,		  _______, _______, _______, _______, _______,  _______,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, _______,   _______, _______, _______,     	  _______, KC_VOLD, KC_VOLU, _______,  _______,  _______,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, _______, _______, _______, _______,             _______, KC_MUTE, _______, _______, _______, _______,
//---------------------------------------------------------//--------------------------------------------------------------//
                               LT(4,KC_TAB), _______,_______,		    KC_MPRV, KC_MPLY, KC_MNXT
  ),
  [5] = LAYOUT(
    _______, _______, _______, _______, _______, _______,	        _______, RGB_SPD, RGB_SPI, _______, _______,  TO(5),
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, _______, _______, _______, _______,     	    RGB_SAI, RGB_VAD, RGB_VAI, _______,  _______,  _______,
//---------------------------------------------------------//--------------------------------------------------------------//
    _______, _______, _______, _______, _______, _______,             RGB_SAD, RGB_HUD, RGB_HUI, _______, _______, _______,
//---------------------------------------------------------//--------------------------------------------------------------//
                               _______,_______, _______,		      RGB_RMOD, RGB_TOG, RGB_MOD
  )
};
