#include "keymap.h"

void sentence_end(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t tap_keycode = ((int16_t)((size_t)user_data));

    switch (state->count) {
        // Double tapping KEYCODE produces
        // ". <one-shot-shift>" i.e. KEYCODE, space and capitalize next letter.
        case 2:
            // shifted keys (e.g. slash, double quote)
            if (tap_keycode == KC_SLSH) {
                if ((get_mods() & MOD_MASK_SHIFT)) {
                    tap_code(KC_SPC);
                    /* Internal code of OSM(MOD_LSFT) */
                    add_oneshot_mods(MOD_BIT(KC_LSHIFT));
                } else {
                    tap_code16(tap_keycode);
                }
            } else {
                /* Checkjthat Shift is inactive */
                if (!(get_mods() & MOD_MASK_SHIFT)) {
                    tap_code(KC_SPC);
                    /* Internal code of OSM(MOD_LSFT) */
                    add_oneshot_mods(MOD_BIT(KC_LSHIFT));
                } else {
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
            // replace the space with the KEYCODE
            tap_code16(tap_keycode);
            // tap the third KEYCODE
            tap_code16(tap_keycode);
            break;
        default: // send KEYCODE on every normal tap
            tap_code16(tap_keycode);
    }
};

void double_tap_space(qk_tap_dance_state_t *state, void *user_data) {
    /*
     * Double tapping:
     * - COLON
     * - QUOTE
     * - COMMA
     *
     * Leads to the 2nd tapped character being replaced by a SPACE
     */
    uint16_t tap_keycode = ((int16_t)((size_t)user_data));

    switch (state->count) {
        case 2:
            // shifted keys
                if ((get_mods() & MOD_MASK_SHIFT)) {
                    if (tap_keycode == KC_QUOT || tap_keycode == KC_SCLN) {
                        tap_code(KC_SPC);
                    }
                } else {
                    if (tap_keycode == KC_COMM || tap_keycode == KC_QUOT || tap_keycode == KC_SCLN) {
                        tap_code(KC_SPC);
                    }
                }
            break;
        case 3:
            // remove the added space of the double tap case
            tap_code(KC_BSPC);
            // replace the space with the KEYCODE
            tap_code16(tap_keycode);
            // tap the third KEYCODE
            tap_code16(tap_keycode);
            break;
        default: // send KEYCODE on every normal tap
            tap_code16(tap_keycode);
    }
};
