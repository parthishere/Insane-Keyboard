// copied from : qmk firmware

#pragma once
#include "src/keymaps.h"
// clang-format off



/** \brief 5-bit packed modifiers
 *
 * Mod bits:    43210
 *   bit 0      ||||+- Control
 *   bit 1      |||+-- Shift
 *   bit 2      ||+--- Alt
 *   bit 3      |+---- Gui
 *   bit 4      +----- LR flag(Left:0, Right:1)
 */
enum mods_5bit {
    MOD_LCTL = 0x01,
    MOD_LSFT = 0x02,
    MOD_LALT = 0x04,
    MOD_LGUI = 0x08,
    MOD_RCTL = 0x11,
    MOD_RSFT = 0x12,
    MOD_RALT = 0x14,
    MOD_RGUI = 0x18,
};
#define MOD_HYPR (MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI)
#define MOD_MEH (MOD_LCTL | MOD_LSFT | MOD_LALT)

/** \brief 8-bit packed modifiers
 */
enum mods_8bit {
    MOD_BIT_LCTRL  = 0b00000001,
    MOD_BIT_LSHIFT = 0b00000010,
    MOD_BIT_LALT   = 0b00000100,
    MOD_BIT_LGUI   = 0b00001000,
    MOD_BIT_RCTRL  = 0b00010000,
    MOD_BIT_RSHIFT = 0b00100000,
    MOD_BIT_RALT   = 0b01000000,
    MOD_BIT_RGUI   = 0b10000000,
};
#define MOD_MASK_CTRL (MOD_BIT_LCTRL | MOD_BIT_RCTRL)
#define MOD_MASK_SHIFT (MOD_BIT_LSHIFT | MOD_BIT_RSHIFT)
#define MOD_MASK_ALT (MOD_BIT_LALT | MOD_BIT_RALT)
#define MOD_MASK_GUI (MOD_BIT_LGUI | MOD_BIT_RGUI)
#define MOD_MASK_CS (MOD_MASK_CTRL | MOD_MASK_SHIFT)
#define MOD_MASK_CA (MOD_MASK_CTRL | MOD_MASK_ALT)
#define MOD_MASK_CG (MOD_MASK_CTRL | MOD_MASK_GUI)
#define MOD_MASK_SA (MOD_MASK_SHIFT | MOD_MASK_ALT)
#define MOD_MASK_SG (MOD_MASK_SHIFT | MOD_MASK_GUI)
#define MOD_MASK_AG (MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_CSA (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_ALT)
#define MOD_MASK_CSG (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_GUI)
#define MOD_MASK_CAG (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_SAG (MOD_MASK_SHIFT | MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_CSAG (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_ALT | MOD_MASK_GUI)

// TODO: sub-ranges?
// clang-format off
#define QK_LCTL                0x0100
#define QK_LSFT                0x0200
#define QK_LALT                0x0400
#define QK_LGUI                0x0800
#define QK_RMODS_MIN           0x1000
#define QK_RCTL                0x1100
#define QK_RSFT                0x1200
#define QK_RALT                0x1400
#define QK_RGUI                0x1800

#define SAFE_RANGE             QK_USER
// clang-format on

// Generic decoding for the whole QK_MODS range
#define QK_MODS_GET_MODS(kc) (((kc) >> 8) & 0x1F)
#define QK_MODS_GET_BASIC_KEYCODE(kc) ((kc)&0xFF)

// Keycode modifiers & aliases
#define LCTL(kc) (QK_LCTL | (kc))
#define LSFT(kc) (QK_LSFT | (kc))
#define LALT(kc) (QK_LALT | (kc))
#define LGUI(kc) (QK_LGUI | (kc))
#define LOPT(kc) LALT(kc)
#define LCMD(kc) LGUI(kc)
#define LWIN(kc) LGUI(kc)
#define RCTL(kc) (QK_RCTL | (kc))
#define RSFT(kc) (QK_RSFT | (kc))
#define RALT(kc) (QK_RALT | (kc))
#define RGUI(kc) (QK_RGUI | (kc))
#define ALGR(kc) RALT(kc)
#define ROPT(kc) RALT(kc)
#define RCMD(kc) RGUI(kc)
#define RWIN(kc) RGUI(kc)

#define HYPR(kc) (QK_LCTL | QK_LSFT | QK_LALT | QK_LGUI | (kc))
#define MEH(kc) (QK_LCTL | QK_LSFT | QK_LALT | (kc))
#define LCAG(kc) (QK_LCTL | QK_LALT | QK_LGUI | (kc))
#define LSG(kc) (QK_LSFT | QK_LGUI | (kc))
#define SGUI(kc) LSG(kc)
#define SCMD(kc) LSG(kc)
#define SWIN(kc) LSG(kc)
#define LAG(kc) (QK_LALT | QK_LGUI | (kc))
#define RSG(kc) (QK_RSFT | QK_RGUI | (kc))
#define RAG(kc) (QK_RALT | QK_RGUI | (kc))
#define LCA(kc) (QK_LCTL | QK_LALT | (kc))
#define LSA(kc) (QK_LSFT | QK_LALT | (kc))
#define RSA(kc) (QK_RSFT | QK_RALT | (kc))
#define RCS(kc) (QK_RCTL | QK_RSFT | (kc))
#define SAGR(kc) RSA(kc)

// Modified keycode aliases
#define C(kc) LCTL(kc)
#define S(kc) LSFT(kc)
#define A(kc) LALT(kc)
#define G(kc) LGUI(kc)

// GOTO layer - 32 layer max
#define TO(layer) (QK_TO | ((layer)&0x1F))
#define QK_TO_GET_LAYER(kc) ((kc)&0x1F)

// Momentary switch layer - 32 layer max
#define MO(layer) (QK_MOMENTARY | ((layer)&0x1F))
#define QK_MOMENTARY_GET_LAYER(kc) ((kc)&0x1F)

// Set default layer - 32 layer max
#define DF(layer) (QK_DEF_LAYER | ((layer)&0x1F))
#define QK_DEF_LAYER_GET_LAYER(kc) ((kc)&0x1F)

// Toggle to layer - 32 layer max
#define TG(layer) (QK_TOGGLE_LAYER | ((layer)&0x1F))
#define QK_TOGGLE_LAYER_GET_LAYER(kc) ((kc)&0x1F)

// One-shot layer - 32 layer max
#define OSL(layer) (QK_ONE_SHOT_LAYER | ((layer)&0x1F))
#define QK_ONE_SHOT_LAYER_GET_LAYER(kc) ((kc)&0x1F)

// L-ayer M-od: Momentary switch layer with modifiers active - 16 layer max
#define LM(layer, mod) (QK_LAYER_MOD | (((layer)&0xF) << 5) | ((mod)&0x1F))
#define QK_LAYER_MOD_GET_LAYER(kc) (((kc) >> 5) & 0xF)
#define QK_LAYER_MOD_GET_MODS(kc) ((kc)&0x1F)

// One-shot mod
#define OSM(mod) (QK_ONE_SHOT_MOD | ((mod)&0x1F))
#define QK_ONE_SHOT_MOD_GET_MODS(kc) ((kc)&0x1F)

// Layer tap-toggle - 32 layer max
#define TT(layer) (QK_LAYER_TAP_TOGGLE | ((layer)&0x1F))
#define QK_LAYER_TAP_TOGGLE_GET_LAYER(kc) ((kc)&0x1F)

// L-ayer, T-ap - 256 keycode max, 16 layer max
#define LT(layer, kc) (QK_LAYER_TAP | (((layer)&0xF) << 8) | ((kc)&0xFF))
#define QK_LAYER_TAP_GET_LAYER(kc) (((kc) >> 8) & 0xF)
#define QK_LAYER_TAP_GET_TAP_KEYCODE(kc) ((kc)&0xFF)

// M-od, T-ap - 256 keycode max
#define MT(mod, kc) (QK_MOD_TAP | (((mod)&0x1F) << 8) | ((kc)&0xFF))
#define QK_MOD_TAP_GET_MODS(kc) (((kc) >> 8) & 0x1F)
#define QK_MOD_TAP_GET_TAP_KEYCODE(kc) ((kc)&0xFF)

#define LCTL_T(kc) MT(MOD_LCTL, kc)
#define RCTL_T(kc) MT(MOD_RCTL, kc)
#define CTL_T(kc) LCTL_T(kc)

#define LSFT_T(kc) MT(MOD_LSFT, kc)
#define RSFT_T(kc) MT(MOD_RSFT, kc)
#define SFT_T(kc) LSFT_T(kc)

#define LALT_T(kc) MT(MOD_LALT, kc)
#define RALT_T(kc) MT(MOD_RALT, kc)
#define LOPT_T(kc) LALT_T(kc)
#define ROPT_T(kc) RALT_T(kc)
#define ALGR_T(kc) RALT_T(kc)
#define ALT_T(kc) LALT_T(kc)
#define OPT_T(kc) LOPT_T(kc)

#define LGUI_T(kc) MT(MOD_LGUI, kc)
#define RGUI_T(kc) MT(MOD_RGUI, kc)
#define LCMD_T(kc) LGUI_T(kc)
#define LWIN_T(kc) LGUI_T(kc)
#define RCMD_T(kc) RGUI_T(kc)
#define RWIN_T(kc) RGUI_T(kc)
#define GUI_T(kc) LGUI_T(kc)
#define CMD_T(kc) LCMD_T(kc)
#define WIN_T(kc) LWIN_T(kc)

#define C_S_T(kc) MT(MOD_LCTL | MOD_LSFT, kc)                        // Left Control + Shift e.g. for gnome-terminal
#define MEH_T(kc) MT(MOD_LCTL | MOD_LSFT | MOD_LALT, kc)             // Meh is a less hyper version of the Hyper key -- doesn't include GUI, so just Left Control + Shift + Alt
#define LCAG_T(kc) MT(MOD_LCTL | MOD_LALT | MOD_LGUI, kc)            // Left Control + Alt + GUI
#define RCAG_T(kc) MT(MOD_RCTL | MOD_RALT | MOD_RGUI, kc)            // Right Control + Alt + GUI
#define HYPR_T(kc) MT(MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI, kc) // see http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/
#define LSG_T(kc) MT(MOD_LSFT | MOD_LGUI, kc)                        // Left Shift + GUI
#define SGUI_T(kc) LSG_T(kc)
#define SCMD_T(kc) LSG_T(kc)
#define SWIN_T(kc) LSG_T(kc)
#define LAG_T(kc) MT(MOD_LALT | MOD_LGUI, kc) // Left Alt + GUI
#define RSG_T(kc) MT(MOD_RSFT | MOD_RGUI, kc) // Right Shift + GUI
#define RAG_T(kc) MT(MOD_RALT | MOD_RGUI, kc) // Right Alt + GUI
#define LCA_T(kc) MT(MOD_LCTL | MOD_LALT, kc) // Left Control + Alt
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc) // Left Shift + Alt
#define RSA_T(kc) MT(MOD_RSFT | MOD_RALT, kc) // Right Shift + Alt
#define RCS_T(kc) MT(MOD_RCTL | MOD_RSFT, kc) // Right Control + Shift
#define SAGR_T(kc) RSA_T(kc)

#define ALL_T(kc) HYPR_T(kc)

// Dedicated keycode versions for Hyper and Meh, if you want to use them as standalone keys rather than mod-tap
#define KC_HYPR HYPR(KC_NO)
#define KC_MEH MEH(KC_NO)

// Unicode aliases
// UNICODE_ENABLE - Allows Unicode input up to 0x7FFF
#define UC(c) (QK_UNICODE | (c))
#define QK_UNICODE_GET_CODE_POINT(kc) ((kc)&0x7FFF)

// UNICODEMAP_ENABLE - Allows Unicode input up to 0x10FFFF, requires unicode_map
#define UM(i) (QK_UNICODEMAP | ((i)&0x3FFF))
#define QK_UNICODEMAP_GET_INDEX(kc) ((kc)&0x3FFF)

#define UP(i, j) (QK_UNICODEMAP_PAIR | ((i)&0x7F) | (((j)&0x7F) << 7)) // 127 max i and j
#define QK_UNICODEMAP_PAIR_GET_UNSHIFTED_INDEX(kc) ((kc)&0x7F)
#define QK_UNICODEMAP_PAIR_GET_SHIFTED_INDEX(kc) (((kc) >> 7) & 0x7F)

// Swap Hands
#define SH_T(kc) (QK_SWAP_HANDS | ((kc)&0xFF))
#define QK_SWAP_HANDS_GET_TAP_KEYCODE(kc) ((kc)&0xFF)

// Tap dance
#define TD(i) (QK_TAP_DANCE | ((i)&0xFF))
#define QK_TAP_DANCE_GET_INDEX(kc) ((kc)&0xFF)

// MIDI aliases
#define MIDI_TONE_MIN QK_MIDI_NOTE_C_0
#define MIDI_TONE_MAX QK_MIDI_NOTE_B_5
#define MIDI_OCTAVE_MIN QK_MIDI_OCTAVE_N2
#define MIDI_OCTAVE_MAX QK_MIDI_OCTAVE_7
#define MIDI_TRANSPOSE_MIN QK_MIDI_TRANSPOSE_N6
#define MIDI_TRANSPOSE_MAX QK_MIDI_TRANSPOSE_6
#define MIDI_VELOCITY_MIN QK_MIDI_VELOCITY_0
#define MIDI_VELOCITY_MAX QK_MIDI_VELOCITY_10
#define MIDI_CHANNEL_MIN QK_MIDI_CHANNEL_1
#define MIDI_CHANNEL_MAX QK_MIDI_CHANNEL_16


// Aliases
#define KC_TILD S(KC_GRAVE) // ~
#define KC_EXLM S(KC_1)    // !
#define KC_AT   S(KC_2)    // @
#define KC_HASH S(KC_3)    // #
#define KC_DLR  S(KC_4)    // $
#define KC_PERC S(KC_5)    // %
#define KC_CIRC S(KC_6)    // ^
#define KC_AMPR S(KC_7)    // &
#define KC_ASTR S(KC_8)    // *
#define KC_LPRN S(KC_9)    // (
#define KC_RPRN S(KC_0)    // )
#define KC_UNDS S(KC_MINUS) // _
#define KC_PLUS S(KC_EQUAL) // +
#define KC_LCBR S(KC_LEFT_BRACKET) // {
#define KC_RCBR S(KC_RIGHT_BRACKET) // }
#define KC_PIPE S(KC_BACKSLASH) // |
#define KC_COLN S(KC_SEMICOLON) // :
#define KC_DQUO S(KC_QUOTE) // "
#define KC_LABK S(KC_COMMA) // <
#define KC_RABK S(KC_DOT)  // >
#define KC_QUES S(KC_SLASH) // ?

#define KC_TILDE KC_TILD
#define KC_EXCLAIM KC_EXLM
#define KC_DOLLAR KC_DLR
#define KC_PERCENT KC_PERC
#define KC_CIRCUMFLEX KC_CIRC
#define KC_AMPERSAND KC_AMPR
#define KC_ASTERISK KC_ASTR
#define KC_LEFT_PAREN KC_LPRN
#define KC_RIGHT_PAREN KC_RPRN
#define KC_UNDERSCORE KC_UNDS
#define KC_LEFT_CURLY_BRACE KC_LCBR
#define KC_RIGHT_CURLY_BRACE KC_RCBR
#define KC_COLON KC_COLN
#define KC_DOUBLE_QUOTE KC_DQUO
#define KC_DQT KC_DQUO
#define KC_LEFT_ANGLE_BRACKET KC_LABK
#define KC_LT KC_LABK
#define KC_RIGHT_ANGLE_BRACKET KC_RABK
#define KC_GT KC_RABK
#define KC_QUESTION KC_QUES



// Deprecated Quantum keycodes
#define RGB_TOG QK_UNDERGLOW_TOGGLE
#define RGB_MOD QK_UNDERGLOW_MODE_NEXT
#define RGB_MODE_FORWARD QK_UNDERGLOW_MODE_NEXT
#define RGB_RMOD QK_UNDERGLOW_MODE_PREVIOUS
#define RGB_MODE_REVERSE QK_UNDERGLOW_MODE_PREVIOUS
#define RGB_HUI QK_UNDERGLOW_HUE_UP
#define RGB_HUD QK_UNDERGLOW_HUE_DOWN
#define RGB_SAI QK_UNDERGLOW_SATURATION_UP
#define RGB_SAD QK_UNDERGLOW_SATURATION_DOWN
#define RGB_VAI QK_UNDERGLOW_VALUE_UP
#define RGB_VAD QK_UNDERGLOW_VALUE_DOWN
#define RGB_SPI QK_UNDERGLOW_SPEED_UP
#define RGB_SPD QK_UNDERGLOW_SPEED_DOWN

#define KC_MS_UP QK_MOUSE_CURSOR_UP
#define KC_MS_U QK_MOUSE_CURSOR_UP
#define KC_MS_DOWN QK_MOUSE_CURSOR_DOWN
#define KC_MS_D QK_MOUSE_CURSOR_DOWN
#define KC_MS_LEFT QK_MOUSE_CURSOR_LEFT
#define KC_MS_L QK_MOUSE_CURSOR_LEFT
#define KC_MS_RIGHT QK_MOUSE_CURSOR_RIGHT
#define KC_MS_R QK_MOUSE_CURSOR_RIGHT
#define KC_MS_BTN1 QK_MOUSE_BUTTON_1
#define KC_BTN1 QK_MOUSE_BUTTON_1
#define KC_MS_BTN2 QK_MOUSE_BUTTON_2
#define KC_BTN2 QK_MOUSE_BUTTON_2
#define KC_MS_BTN3 QK_MOUSE_BUTTON_3
#define KC_BTN3 QK_MOUSE_BUTTON_3
#define KC_MS_BTN4 QK_MOUSE_BUTTON_4
#define KC_BTN4 QK_MOUSE_BUTTON_4
#define KC_MS_BTN5 QK_MOUSE_BUTTON_5
#define KC_BTN5 QK_MOUSE_BUTTON_5
#define KC_MS_BTN6 QK_MOUSE_BUTTON_6
#define KC_BTN6 QK_MOUSE_BUTTON_6
#define KC_MS_BTN7 QK_MOUSE_BUTTON_7
#define KC_BTN7 QK_MOUSE_BUTTON_7
#define KC_MS_BTN8 QK_MOUSE_BUTTON_8
#define KC_BTN8 QK_MOUSE_BUTTON_8
#define KC_MS_WH_UP QK_MOUSE_WHEEL_UP
#define KC_WH_U QK_MOUSE_WHEEL_UP
#define KC_MS_WH_DOWN QK_MOUSE_WHEEL_DOWN
#define KC_WH_D QK_MOUSE_WHEEL_DOWN
#define KC_MS_WH_LEFT QK_MOUSE_WHEEL_LEFT
#define KC_WH_L QK_MOUSE_WHEEL_LEFT
#define KC_MS_WH_RIGHT QK_MOUSE_WHEEL_RIGHT
#define KC_WH_R QK_MOUSE_WHEEL_RIGHT
#define KC_MS_ACCEL0 QK_MOUSE_ACCELERATION_0
#define KC_ACL0 QK_MOUSE_ACCELERATION_0
#define KC_MS_ACCEL1 QK_MOUSE_ACCELERATION_1
#define KC_ACL1 QK_MOUSE_ACCELERATION_1
#define KC_MS_ACCEL2 QK_MOUSE_ACCELERATION_2
#define KC_ACL2 QK_MOUSE_ACCELERATION_2
