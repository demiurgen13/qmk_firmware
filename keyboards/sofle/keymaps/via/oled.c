 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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

//Sets up what the OLED screens display.

#ifdef OLED_DRIVER_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void render_dao(void) {
    static const char PROGMEM qmk_dao[] = {
        0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xe0, 0x07, 0xff,
        0xff, 0x80, 0x01, 0xff, 0xfe, 0x00, 0x00, 0xff, 0xfc, 0x0f, 0xe0, 0x3f, 0xf8, 0x3f, 0xf0, 0x3f,
        0xf8, 0x7f, 0xf8, 0x1f, 0xf0, 0xfe, 0x78, 0x0f, 0xf1, 0xfc, 0x78, 0x0f, 0xe1, 0xfc, 0x78, 0x07,
        0xe3, 0xff, 0xf8, 0x07, 0xe3, 0xff, 0xf0, 0x07, 0xc3, 0xff, 0xf0, 0x07, 0xc3, 0xff, 0xc0, 0x07,
        0xc3, 0xfc, 0x00, 0x07, 0xe3, 0xf0, 0x00, 0x07, 0xe3, 0xf0, 0x00, 0x07, 0xe3, 0xe1, 0x80, 0x07,
        0xe1, 0xe3, 0xc0, 0x07, 0xf1, 0xe3, 0xc0, 0x0f, 0xf0, 0xe1, 0x80, 0x0f, 0xf8, 0x70, 0x00, 0x1f,
        0xf8, 0x30, 0x00, 0x3f, 0xfc, 0x08, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0xff, 0xff, 0x80, 0x01, 0xff,
        0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_P(qmk_dao, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("GAME!!!!!!"), false);
            break;
        default:
            oled_write_P(PSTR("Mod\n"), false);
            break;
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Game\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Num"), false);
            break;
        case 3:
            oled_write_P(PSTR("Nav"), false);
            break;
        case 4:
            oled_write_P(PSTR("_FN4"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

void oled_task_user1(void) {
    render_dao();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
}


#endif
