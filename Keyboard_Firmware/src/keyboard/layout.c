#include <stdint.h>
#include "src/keymaps.h"
#include "src/keyboard/deprecated_mappings.h"
#include "layout.h"


int decode_row(uint8_t row_value)
{
    int row_index = 0;

    while (row_value > 1) {
        row_value >>= 1; 
        row_index++; 
    }

    return row_index;
}

uint8_t* modifypressedkeys_left(pressedkeys *keys, int totalkeys)
{
    static uint8_t return_array[8] = {0}; 
    uint8_t layer = current_layer;  
    uint8_t cnt = 0;

    //have to check if CAPS is on 
    for (int i = 0; i < totalkeys; i++)
    {
        keys[i].row = decode_row(keys[i].row);
        // Check for Shift and FN key 
        if ((keys[i].row == 2) && (keys[i].column == 7)) 
        {
            layer = (layer == BASE) ? MDIA : BASE; 
            continue;
        }
        else if ((keys[i].row == 4) && (keys[i].column == 1)) 
        {
            layer = (layer == BASE) ?  SYMB: BASE; 
            continue; 
        }
       
        uint8_t key_value = keymaps[LEFT][layer][keys[i].row][keys[i].column];
        return_array[cnt] = key_value; 
        cnt++;
    }

    return return_array; 
}

uint8_t* modifypressedkeys_right(pressedkeys *keys, int totalkeys)
{
    static uint8_t return_array[8] = {0}; 
    uint8_t layer = current_layer;  
    uint8_t cnt = 0;

    //have to check if CAPS is on 

    for (int i = 0; i < totalkeys; i++)
    {
        keys[i].row = decode_row(keys[i].row);

        // Check for Shift and FN key for the right hand
        if ((keys[i].row == 2) && (keys[i].column == 1)) //R L1
        {
            layer = (layer == BASE) ? MDIA : BASE; 
            continue;
        }
        else if ((keys[i].row == 4) && (keys[i].column == 7)) //Rshift
        {
            layer = (layer == BASE) ? SYMB : BASE; 
            continue; 
        }
       
        uint8_t key_value = keymaps[RIGHT][layer][keys[i].row][keys[i].column];
        return_array[cnt] = key_value; 
        cnt++;
    }

    return return_array; 
}
