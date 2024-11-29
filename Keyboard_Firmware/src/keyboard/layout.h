// #include "src/hid.h"
// #include <stdint.h>

// uint16_t qwerty = {
//     {KEY_ESC, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_BACKSPACE},
//     {KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFTBRACE, KEY_RIGHTBRACE},
//     {KEY_LEFTCTRL, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_APOSTROPHE},
//     {KEY_LEFTSHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_DOT, KEY_SLASH, KEY_RIGHTSHIFT},
//     {KEY_NO, KEY_NO, KEY_NO, KEY_ALT, KEY_LCTL, KEY_SPC, LT(1, KEY_ENTER), KEY_SUPER, LT(1, KEY_ALTGR), KEY_NO, KEY_NO,
//                     KEY_NO}
// };

// uint16_t program = {{KEY_ESC, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8,
//                      KEY_9, KEY_0, KEY_BACKSPACE},
//                     {
//                         KEY_TAB,
//                         KEY_Q,
//                         KEY_W,
//                         KEY_LEFTBRACE,
//                         KEY_RIGHTBRACE,
//                         KEY_KPPLUS,
//                         KEY_Y,
//                         KEY_U,
//                         KEY_I,
//                         KEY_O,
//                         KEY_LEFTBRACE,
//                         KEY_RIGHTBRACE,
//                     },
//                     {KEY_TAB, KEY_K, KEY_S, KEY_LBRACKET, KEY_RBRACKET, KEY_EQ,
//                      KEY_LEFT, KEY_DOWN, KEY_UP, KEY_RIGHT, KEY_SCOLON, KEY_SQUOTE},
//                     {KEY_LSHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_UNDERSCORE, KEY_N,
//                      KEY_M, KEY_COMMA, KEY_DOT, KEY_SLASH, KEY_RSHIFT},
//                     {KEY_NO, KEY_NO, KEY_NO, KEY_ALT, KEY_TRNS, KEY_SPC,
//                      LT(1, KEY_ENTER), KEY_SUPER, KEY_SUPER, KEY_NO, KEY_NO,
//                      KEY_NO}};

// this->layers = {qwerty, program};
// this->set_active_layer(0);