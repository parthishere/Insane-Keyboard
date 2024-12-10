#include <stdint.h>
#include "src/keyboard/layout.h"
#include "src/keyboard/deprecated_mappings.h"
#include "src/keymaps.h"
#include <stdbool.h>
#include <string.h>

#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"

layers_t current_layer = BASE;
static uint8_t keymap_report[8];

typedef enum
{
    TOP_ROW,
    UPPER_LETTER_ROW,
    HOME,
    LOWER_LETTER_ROW,
    SPACEBAR_ROW,
    NO_ROW = -1
} row_t;

typedef enum KeyboardColumn
{
    PINKY_OUTER,   // Leftmost column (EQL, DEL, BSPC, LSFT, GRV)
    PINKY_COLUMN,  // Column for pinky (1, Q, A, Z, QUOT)
    RING_COLUMN,   // Column for ring finger (2, W, S, X, LALT)
    MIDDLE_COLUMN, // Column for middle finger (3, E, D, C, LEFT)
    INDEX_INNER,   // Inner column for index finger (4, R, F, V, RGHT)
    INDEX_OUTER,   // Outer column for index finger (5, T, G, B, SPC)
    THUMB_INNER,   // Inner thumb cluster (LEFT, SYMB, APP, NO, BSPC)
    THUMB_OUTER    // Outer thumb cluster (only present in some rows: LGUI, HOME, END)
} column_t;

/*
Report format
This report must be requested by the software using interrupt transfers once every interval milliseconds, and the interval is defined in the interrupt IN descriptor of the USB keyboard. The USB keyboard report may be up to 8 bytes in size, although not all these bytes are used and it's OK to implement a proper implementation using only the first three or four bytes (and this is how I do it.) Just for completion's sake, however, I will describe the full report mechanism of the keyboard. Notice that the report structure defined below applies to the boot protocol only.

Offset	Size	Description
0	Byte	Modifier keys status.
1	Byte	Reserved field.
2	Byte	Keypress #1.
3	Byte	Keypress #2.
4	Byte	Keypress #3.
5	Byte	Keypress #4.
6	Byte	Keypress #5.
7	Byte	Keypress #6.


Modifier keys status: This byte is a bitfield, where each bit corresponds to a specific modifier key. When a bit is set to 1, the corresponding modifier key is being pressed. Unlike PS/2 keyboards, USB keyboards don't have "scancodes" for modifier keys. The bit structure of this byte is:

Bit	Bit Length	Description
0	1	Left Ctrl. =
1	1	Left Shift.
2	1	Left Alt.
3	1	Left GUI (Windows/Super key.)
4	1	Right Ctrl.
5	1	Right Shift.
6	1	Right Alt.
7	1	Right GUI (Windows/Super key.)

Keypress fields: One keyboard report can indicate up to 6 keypresses. All these values are unsigned 8-bit values (unlike PS/2 scancodes, which are mostly 7-bit) which indicate the key being pressed. A reference on the USB scancode to ASCII character conversion table is in the bottom of the article.

*/
// static uint8_t input_report_data[] = {0, 0, 0, 0, 0, 0, 0, 0};
// static uint8_t actual_key = KEY_A;

// https://configure.zsa.io/ergodox-ez/layouts/default/latest/0

inline static layers_t get_current_layer()
{
    return current_layer;
}

row_t __decode_row(uint8_t *row_value)
{

    switch (*row_value)
    {
    case 0x10:
        *row_value &= ~(0x10);
        return TOP_ROW;
    case 0x08:
        *row_value &= ~(0x08);
        return UPPER_LETTER_ROW;
    case 0x04:
        *row_value &= ~(0x04);
        return HOME;
    case 0x02:
        *row_value &= ~(0x02);
        return LOWER_LETTER_ROW;
    case 0x01:
        *row_value &= ~(0x01);
        return SPACEBAR_ROW;
    default:
        return NO_ROW;
    }
}



layers_t __toggle_current_layer(layers_t toggle)
{
    switch (toggle)
    {
    case SYMB:
        if (current_layer == SYMB)
            current_layer = BASE;
        else if (current_layer == BASE)
            current_layer = SYMB;
        break;
    case MDIA:
        if (current_layer == MDIA)
            current_layer = BASE;
        else if (current_layer == BASE)
            current_layer = MDIA;
        break;
    default:
       break;
    }
    return current_layer;
}


layers_t __is_change_layer(uint8_t row_value, uint8_t col_value)
{
    switch (row_value)
    {
    case UPPER_LETTER_ROW:
#if DEVICE_IS_BLE_MASTER == 1
        if (col_value == THUMB_INNER)
        {
            __toggle_current_layer(SYMB);
            // timerWai tUs_polled(1000);
            break;
        }
#else
        if (col_value == PINKY_COLUMN)
        {
            __toggle_current_layer(MDIA);
            break;
        }
#endif
        break;
    default:
        break;
    }
    return current_layer;
}

bool __is_modifier(uint8_t row_value, uint8_t col_value)
{
    switch (row_value)
    {
    case HOME:
        switch (get_current_layer())
        {
        case BASE:
#if DEVICE_IS_BLE_MASTER == 1
#else
            if (col_value == PINKY_OUTER)
            {
                return true;
            }
#endif
            break;
        default:
            break;
        }
        break;
    case LOWER_LETTER_ROW:
        switch (get_current_layer())
        {
        case BASE:
#if DEVICE_IS_BLE_MASTER == 1
            if (col_value == PINKY_OUTER || col_value == THUMB_INNER)
            {
                return true;
            }
#else
            if (col_value == PINKY_COLUMN || col_value == THUMB_OUTER)
            {
                return true;
            }
#endif
            break;
        default:
            break;
        }
        break;

    case SPACEBAR_ROW:
        switch (get_current_layer())
        {
        case BASE:
#if DEVICE_IS_BLE_MASTER == 1
            if (col_value == RING_COLUMN)
            {
                return true;
            }
#else
#endif
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return false;
}



uint8_t *modifypressedkeys_left(uint8_t *keys)
{

    memset(keymap_report, 0x00, sizeof(keymap_report));

    uint8_t total_keypresses = 0;
    for (int col = PINKY_OUTER; col <= THUMB_OUTER; col++)
    {

        while (keys[col] != 0)
        {
            keys[col] = __decode_row(&keys[col]);

            if (keys[col] != (uint8_t)-1 && total_keypresses < MAX_KEYPRESS_HID_REPORT)
            {
                __is_change_layer(keys[col], col);
                if (__is_modifier(keys[col], col))
                    keymap_report[0] = keymaps[0][get_current_layer()][keys[col]][col];
                else
                    keymap_report[total_keypresses + 2] = keymaps[0][get_current_layer()][keys[col]][col];

                // printf("working %d, %d\n\r",keymap_report[total_keypresses], keymaps[0][0][keys[col]][col]);

                total_keypresses++;
            }
            col++;
        }
    }

    return keymap_report;
}

uint8_t *modifypressedkeys_right(uint8_t *keys)
{

    memset(keymap_report, 0x00, sizeof(keymap_report));

    uint8_t total_keypresses = 0;
    for (int col = PINKY_OUTER; col <= THUMB_OUTER; col++)
    {

        while (keys[col] != 0)
        {
            keys[col] = __decode_row(&keys[col]);

            if (keys[col] != (uint8_t)-1 && total_keypresses < MAX_KEYPRESS_HID_REPORT)
            {
                __is_change_layer(keys[col], col);
                if (__is_modifier(keys[col], col))
                    keymap_report[0] = keymaps[1][get_current_layer()][keys[col]][MATRIX_COLS - col - 1];
                else
                    keymap_report[total_keypresses + 2] = keymaps[1][get_current_layer()][keys[col]][MATRIX_COLS - col - 1];

                total_keypresses++;
            }
            col++;
        }
    }

    return keymap_report;
}

