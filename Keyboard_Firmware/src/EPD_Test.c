/*****************************************************************************
* | File      	:		EPD_1in54_V2_test.c
* | Author      :   Waveshare team
* | Function    :   1.54inch e-paper test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2019-06-11
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "src/EPD_Test.h"
#include "src/e-ink/EPD_1in54_V2.h"

#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"

uint8_t *BlackImage;

void display_string(char *str, uint16_t Xstart, uint16_t Ystart)
{
    // Paint_ClearWindows(Xstart, Ystart, Xstart + Font20.Width * 7, Ystart + Font20.Height, WHITE);
    DEV_Module_Init();
    Paint_ClearWindows(Xstart, Ystart, Xstart + Font20.Width * 7, Ystart + Font20.Height, WHITE);
    Paint_DrawString_EN(Xstart, Ystart, str, &Font20, WHITE, BLACK);
    EPD_1IN54_V2_DisplayPart(BlackImage);
    DEV_Module_Exit();
}

int EPD_test(void)
{
    // LOG_INFO("EPD_1in54_V2_test Demo\r\n");
    DEV_Module_Init();

    // LOG_INFO("e-Paper Init and Clear...\r\n");
    EPD_1IN54_V2_Init();
    // Create a new image cache

    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    uint16_t Imagesize = ((EPD_1IN54_V2_WIDTH % 8 == 0) ? (EPD_1IN54_V2_WIDTH / 8) : (EPD_1IN54_V2_WIDTH / 8 + 1)) * EPD_1IN54_V2_HEIGHT;
    if ((BlackImage = (uint8_t *)malloc(Imagesize)) == NULL)
    {
        // LOG_INFO("Failed to apply for black memory...\r\n");
        return -1;
    }
    // LOG_INFO("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, ROTATE_180, WHITE);

    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);

    EPD_1IN54_V2_DisplayPartBaseImage(BlackImage);

    // enter partial mode
    EPD_1IN54_V2_Init_Partial();
    // LOG_INFO("Partial refresh\r\n");
    Paint_SelectImage(BlackImage);

    // DEV_Module_Exit();
    display_string("SKO BUFFS!", 2, 150); 
    display_string("T(C):", 2, 100);
    display_string("Devices:", 2, 50);
    display_string("0", 110, 50);
    return 0;
}
