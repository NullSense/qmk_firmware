#include "keymap.h"

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

void one_shot_caps(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            caps_word_enable();
            break;
        default:
            set_oneshot_mods(MOD_LSFT);
    }
};
