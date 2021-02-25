#pragma once

#include QMK_KEYBOARD_H

enum {
    DOT_TD = 0,
    EXLM_TD,
    QUES_TD,
    ONE_SHOT_CAPS,
};

enum custom_keycodes {
    EMAIL = SAFE_RANGE,
    CAPSWRD,
};

enum layer_names {
    _QWERTY,
    _SYM,
    _NAV,
    _MEDIA,
    _RGB,
    _GAM,
    _NUM,
};

// home row mods
#define ALT_A LALT_T(KC_A)
#define CTL_S LCTL_T(KC_S)
#define GUI_D LGUI_T(KC_D)
#define SFT_F LSFT_T(KC_F)

#define SFT_J LSFT_T(KC_J)
#define GUI_K LGUI_T(KC_K)
#define CTL_L LCTL_T(KC_L)

// layers
#define SPC_1 LT(1,KC_SPC)
#define ESC_2 LT(2,KC_ESC)
#define TAB_3 LT(3,KC_TAB)
#define BSP_6 LT(6,KC_BSPC)

// tap dances
#define OS_CAPS TD(ONE_SHOT_CAPS)
#define DOT TD(DOT_TD)
#define EXLM TD(EXLM_TD)
#define QUES TD(QUES_TD)

// file manager (lf)
#define FILE_MAN LCTL(KC_BSLS)

// clipboard
#define PRT_CLIP LGUI(KC_INS) // print
#define UPL_CLIP G(S(KC_INS)) // upload

// launcher
#define LAUNCHER G(KC_D)

// browser
#define BROWSER G(S(KC_B))

// lock screen
#define LOCK C(A(KC_DELETE))
