#if defined(RGBLIGHT_STARTUP_ANIMATION)
extern rgblight_config_t rgblight_config;

static bool is_enabled;
static bool is_rgblight_startup;
static uint8_t old_hue;
static uint16_t rgblight_startup_loop_timer;

void keyboard_post_init_rgb_light(void) {
    is_enabled = rgblight_is_enabled();

    if (rgblight_is_enabled()) {
        old_hue = rgblight_get_hue();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        is_rgblight_startup = true;
    }
}

void matrix_scan_rgb_light(void) {
    if (is_rgblight_startup && is_keyboard_master()) {
        if (timer_elapsed(rgblight_startup_loop_timer) > 10) {
            static uint8_t counter;
            counter++;
            rgblight_sethsv_noeeprom((counter + old_hue) % 255, 255, 255);
            rgblight_startup_loop_timer = timer_read();

            if (counter == 255) {
                is_rgblight_startup = false;
                if (!is_enabled) {
                    rgblight_disable_noeeprom();
                }
            }
        }
    }
}
#endif
