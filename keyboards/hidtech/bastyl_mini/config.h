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

#pragma once
#include "config_common.h"
#define VENDOR_ID 0xA8F7
#define PRODUCT_ID 0x1827
#define DEVICE_VER 0x0001
#define MANUFACTURER HID Technologies
#define PRODUCT Bastyl Mini

#define MATRIX_ROWS 10
#define MATRIX_COLS 6
#define DIODE_DIRECTION ROW2COL
#define MATRIX_ROW_PINS { D7, B5, F7, F6, B6 }
#define MATRIX_COL_PINS { B4, E6, C6, B1, B3, B2 }
#define TAPPING_TERM    180
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)
// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD
// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD
#define RGB_DI_PIN D2
#define RGBLED_NUM 42
#define RGBLIGHT_SPLIT 21
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 10
#define RGBLIGHT_VAL_STEP 10
#define RGBLIGHT_LIMIT_VAL 180
#define DEBOUNCE 5
#define SOFT_SERIAL_PIN D0
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
#define MASTER_RIGHT
