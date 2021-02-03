#include "keymap.h"

void sentence_end(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t tap_keycode = ((int16_t)((size_t)user_data));

    switch (state->count) {
        // Double tapping TD_KEYCODE produces
        // ". <one-shot-shift>" i.e. TD_KEYCODE, space and capitalize next letter.
        case 2:
            if (tap_keycode == KC_SLSH) {
                if ((get_mods() & MOD_MASK_SHIFT)) {
                    tap_code(KC_SPC);
                    /* Internal code of OSM(MOD_LSFT) */
                    add_oneshot_mods(MOD_BIT(KC_LSHIFT));

                } else {
                    // send ">" (KC_DOT + shift → ">")
                    tap_code16(tap_keycode);
                }
            } else {
                /* Checkjthat Shift is inactive */
                if (!(get_mods() & MOD_MASK_SHIFT)) {
                    tap_code(KC_SPC);
                    /* Internal code of OSM(MOD_LSFT) */
                    add_oneshot_mods(MOD_BIT(KC_LSHIFT));

                } else {
                    // send ">" (KC_DOT + shift → ">")
                    tap_code16(tap_keycode);
                }
            }

            // Since `sentence_end` is called on each tap
            // and not at the end of the tapping term,
            // the third tap needs to cancel the effects
            // of the double tap in order to get the expected
            // three TD_KEYCODE ellipsis.
            break;
        case 3:
            // remove the added space of the double tap case
            tap_code(KC_BSPC);
            // replace the space with a second dot
            tap_code16(tap_keycode);
            // tap the third dot
            tap_code16(tap_keycode);
            break;

            // send KC_DOT on every normal tap of TD_DOT
        default:
            tap_code16(tap_keycode);
    }
};

void sentence_end_tap(qk_tap_dance_state_t *state, void *user_data) {
    tap_code16((int16_t)((size_t)user_data));
}
