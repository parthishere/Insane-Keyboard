#ifndef __LAYOUT_H__
#define __LAYOUT_H__


#include <stdint.h>
#include "src/keymaps.h"
#include "src/keyboard/deprecated_mappings.h"

enum layers {
    BASE,  // default layer
    SYMB,  // symbols
    MDIA,  // media keys
};

#define LAYERS 3
#define MATRIX_ROWS 5
#define MATRIX_COLS 8
#define MAX_KEYPRESS_HID_REPORT 6



#define LEFT 0
#define RIGHT 1

typedef struct {
    int row;
    int column;
} pressedkeys_t;

static const uint16_t keymaps[2][LAYERS][MATRIX_ROWS][MATRIX_COLS] = 
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|  LGui  |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */


/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE

// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
{
    {       // layer 0 : default
        // left hand
        {
            {KC_EQL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_LEFT, 0x00},
            {KC_DEL, KC_Q, KC_W, KC_E, KC_R, KC_T, SYMB, 0x00},
            {KC_BSPC, KC_A, KC_S, KC_D, KC_F, KC_G, ALT_T(KC_APP), KC_LGUI},
            {MOD_BIT_LSHIFT, CTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B, ALL_T(KC_NO), KC_HOME},
            {KC_GRV, KC_QUOT, MOD_BIT_LSHIFT, KC_LEFT,KC_RGHT, KC_SPC,KC_BSPC,KC_END}
        },
        {
            {KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS},
            {KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, BASE},
            {KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV, RGB_MOD, KC_TRNS},
            {KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS, KC_TRNS},
            {BASE,  KC_EQL, KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAD, RGB_VAI, KC_TRNS}
        },
        {
            {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
            {KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS},
            {KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_TRNS},
            {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
            {KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS}
        }
    },

    {
        // right hand
        {
            {0x00, KC_RGHT, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS},
            {0x00, MDIA, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS},
            {KC_LALT, CTL_T(KC_ESC), KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT},
            {KC_PGUP, MEH_T(KC_NO), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT},
            {KC_PGDN, KC_TAB, KC_ENT, KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, SYMB}
        },
        {
            {KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11},
            {MDIA, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12},
            {RGB_TOG, RGB_M_P, KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS},
            {KC_TRNS, KC_TRNS, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS},
            {KC_TRNS, RGB_HUD, RGB_HUI, KC_TRNS, KC_DOT,  KC_0,    KC_EQL,  KC_TRNS}
        },
        {
            {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
            {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
            {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY},
            {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS},
            {KC_TRNS, KC_TRNS, KC_WBAK, KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,}
        }
    }
    
};


uint8_t* modifypressedkeys_left(uint8_t *keys);
uint8_t* modifypressedkeys_right(uint8_t *keys);

#endif
