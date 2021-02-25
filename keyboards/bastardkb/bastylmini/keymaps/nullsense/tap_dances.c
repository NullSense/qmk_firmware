#include "keymap.h"
#include "one_shot_caps.c"
#include "sentence_end.c"

// Initialize variable holding the binary
// representation of active modifiers.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    caps_word_process_user(keycode, record);

    uint8_t mod_state = get_mods();

    switch (keycode) {
        case EMAIL:
            if (record->event.pressed) {
                SEND_STRING("matas234@gmail.com");
            }
            break;
        case BSP_6: // Del if Shift + Backspace are pressed
            if (record->tap.count > 0) {
                static bool delkey_registered;

                if (record->event.pressed) {
                    if (mod_state & MOD_MASK_SHIFT) {
                        // In case only one shift is held
                        // see https://stackoverflow.com/questions/1596668/logical-xor-operator-in-c
                        // This also means that in case of holding both shifts and pressing KC_BSPC,
                        // Shift+Delete is sent (useful in Firefox) since the shift modifiers aren't deleted.
                        if (!(mod_state & MOD_BIT(KC_LSHIFT)) != !(mod_state & MOD_BIT(KC_RSHIFT))) {
                            del_mods(MOD_MASK_SHIFT);
                        }
                        register_code(KC_DEL);
                        delkey_registered = true;
                        set_mods(mod_state);
                        return false;
                    }
                } else {
                    if (delkey_registered) {
                        unregister_code(KC_DEL);
                        delkey_registered = false;
                        return false;
                    }
                }
                return true;
            }
    }
    return true;
};


#define ACTION_TAP_DANCE_FN_ADVANCED_USER(on_tap, on_finished, on_reset, user_user_data) \
{ .fn = {on_tap, on_finished, on_reset}, .user_data = (void*)user_user_data, }
qk_tap_dance_action_t tap_dance_actions[] = {
    [DOT_TD] = ACTION_TAP_DANCE_FN_ADVANCED_USER(sentence_end, NULL, NULL, KC_DOT),
    [EXLM_TD] = ACTION_TAP_DANCE_FN_ADVANCED_USER(sentence_end, NULL, NULL, KC_EXLM),
    [QUES_TD] = ACTION_TAP_DANCE_FN_ADVANCED_USER(sentence_end, NULL, NULL, KC_SLSH),
    [ONE_SHOT_CAPS] = ACTION_TAP_DANCE_FN(one_shot_caps),
};
