// vim:colorcolumn=4,13,22,31,40,49,58,67,76,85,94,103,112,121
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

enum layers {
  _BSE,
  _LWR,
  _RSE,
  _ADJ
};

#define      CTL_ESC  CTL_T(KC_ESC)
#define      GUI_ESC  GUI_T(KC_ESC)
#define      CTL_TAB  CTL_T(KC_TAB)
#define      OSM_SFT  OSM(MOD_LSFT)
#define      RSE_ESC  LT(_RSE, KC_ESC)
#define      RSE_TAB  LT(_RSE, KC_TAB)
#define      LWR_ESC  LT(_LWR, KC_ESC)
#define      LWR_DEL  LT(_LWR, KC_DEL)

#define      C_LEFT   C(KC_LEFT)
#define      C_RGHT   C(KC_RGHT)
#define      C_BSPC   C(KC_BSPC)

#define      RAISE    MO(_RSE)
#define      LOWER    MO(_LWR)
#define      ADJUST   MO(_ADJ)

/* #define      UNDO     C(KC_Z) */
/* #define      CUT      C(KC_X) */
/* #define      COPY     C(KC_C) */
/* #define      PASTE    C(KC_V) */
#define      REDO     C(S(KC_Z))

  /* Keyboard layout
   ,-----------------------------------------------------.        ,-----------------------------------------------------.
   |        |        |        |        |        |        |        |        |        |        |        |        |        |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   |        |        |        |        |        |        |        |        |        |        |        |        |        |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   |        |        |        |        |        |        |        |        |        |        |        |        |        |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   |        |        |        |        |        |        |        |        |        |        |        |        |        |
   '--------------------------+--------+--------+--------|        |--------+--------+--------+--------------------------'
                              |        |        |        |        |        |        |        |
                              '--------+--------+--------|        |--------+--------+--------'
                                       |        |        |        |        |        |
                                       '--------+--------'        '--------+--------'                                   */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* BASE: Qwerty
   ,-----------------------------------------------------.        ,-----------------------------------------------------.
   |   `    |   1    |   2    |   3    |   4    |   5    |        |   6    |   7    |   8    |   9    |   0    |   -    |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   |  Tab   |   q    |   w    |   e    |   r    |   t    |        |   y    |   u    |   i    |   o    |   p    |   =    |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   |Ctl-Esc |   a    |   s    |   d    |   f    |   g    |        |   h    |   j    |   k    |   l    |   ;    |   '    |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   | Shift  |   z    |   x    |   c    |   v    |   b    |        |   n    |   m    |   ,    |   .    |   /    |    \   |
   '--------------------------+--------+--------+--------|        |--------+--------+--------+--------------------------'
                              |Gui-Esc | Space  |RSE-Tab |        |LWR-Del | Enter  |  Bspc  |
                              '--------+--------+--------|        |--------+--------+--------'
                                       |OSM_Sft |  Ctl   |        |  Alt   |  Alt   |
                                       '--------+--------'        '--------+--------'                                   */
  [_BSE] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
    CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                               GUI_ESC, KC_SPC,  RSE_TAB,          LWR_DEL, KC_ENT,  KC_BSPC,
                                        OSM_SFT, KC_LCTL,          KC_RALT, KC_RALT
  ),

  /* LOWER: Symbols + Numpad
   ,-----------------------------------------------------.        ,-----------------------------------------------------.
   |   ~    |   !    |   @    |   #    |   $    |   %    |        |   ^    |   &    |   *    |   (    |   )    |        |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   |        |   !    |   @    |   {    |   }    |   t    |        |   -    |   7    |   8    |   9    |   0    |        |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   |        |   #    |   $    |   (    |   )    |   g    |        |   _    |   4    |   5    |   6    |   =    |        |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   |        |   %    |   ^    |   [    |   ]    |   b    |        |   +    |   1    |   2    |   3    |   *    |        |
   '--------------------------+--------+--------+--------|        |--------+--------+--------+--------------------------'
                              |        |        |  ADJ   |        |        |        |        |
                              '--------+--------+--------|        |--------+--------+--------'
                                       |        |        |        |        |        |
                                       '--------+--------'        '--------+--------'                                   */
  [_LWR] = LAYOUT(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_GRV, 	       KC_MINS, KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_TILD,          KC_UNDS, KC_4,    KC_5,    KC_6,    KC_EQL,  _______,
    _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_AMPR,          KC_PLUS, KC_1,    KC_2,    KC_3,    KC_ASTR, _______,
                               _______, _______, ADJUST,           _______, _______, _______,
                                        _______, _______,          _______, _______
  ),

  /* RAISE: Navigation and system
   ,-----------------------------------------------------.        ,-----------------------------------------------------.
   |        |   F1   |   F2   |   F3   |   F4   |   F5   |        |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   |        | PrtScr |  Vol-  |  Mute  |  Vol+  |  Bri+  |        | Ctl ←  |  XXXX  |  XXXX  | Ctl →  |Ctl Bsp |  F12   |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   |        |  XXXX  |  Prev  |  Play  |  Next  |  Bri-  |        |   ←    |   ↓    |   ↑    |   →    |  XXXX  |  XXXX  |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   |        |  Undo  |  Cut   |  Copy  | Paste  |  Redo  |        |  Home  |  PgDn  |  PgUp  |  End   |  Ins   |  Del   |
   '--------------------------+--------+--------+--------|        |--------+--------+--------+--------------------------'
                              |        |        |        |        |        |        |        |
                              '--------+--------+--------|        |--------+--------+--------'
                                       |        |        |        |        |        |
                                       '--------+--------'        '--------+--------'                                   */
  [_RSE] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, KC_PSCR, KC_VOLD, KC_MUTE, KC_VOLU, KC_BRIU,          C_LEFT,  XXXXXXX, XXXXXXX, C_RGHT,  C_BSPC,  KC_F12,
    _______, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
    _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE,REDO,             KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,  KC_DEL,
                               _______, _______, _______,          _______, _______, _______,
                                        _______, _______,          _______, _______
  ),

  /* ADJUST: Keyboard Settings
   ,-----------------------------------------------------.        ,-----------------------------------------------------.
   |        |        |        |        |        |        |        |        |        |        |        |        |        |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   |        |        |        |        |        |        |        |        |        |        |        |        |        |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   | RESET  |        |        |        |        |        |        |        |        |        |        |        |        |
   |--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------|
   |        |        |        |        |        |        |        |        |        |        |        |        |        |
   '--------------------------+--------+--------+--------|        |--------+--------+--------+--------------------------'
                              |        |        |        |        |        |        |        |
                              '--------+--------+--------|        |--------+--------+--------'
                                       |        |        |        |        |        |
                                       '--------+--------'        '--------+--------'                                   */
  [_ADJ] = LAYOUT(
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
    RESET,   _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,          _______, _______, _______,
                                        _______, _______,          _______, _______
  ),
};
