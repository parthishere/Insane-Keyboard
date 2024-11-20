/*****************************************************************************
* | File      	:   EPD_1in54_V2.c
* | Author      :   Waveshare team
* | Function    :   1.54inch e-paper V2
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
#include "EPD_1in54_V2.h"
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"


// waveform full refresh
unsigned char WF_Full_1IN54[159] =
{											
0x80,	0x48,	0x40,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x40,	0x48,	0x80,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x80,	0x48,	0x40,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x40,	0x48,	0x80,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0xA,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x8,	0x1,	0x0,	0x8,	0x1,	0x0,	0x2,					
0xA,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x22,	0x22,	0x22,	0x22,	0x22,	0x22,	0x0,	0x0,	0x0,			
0x22,	0x17,	0x41,	0x0,	0x32,	0x20
};

// waveform partial refresh(fast)
unsigned char WF_PARTIAL_1IN54_0[159] =
{
0x0,0x40,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x40,0x40,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0xF,0x0,0x0,0x0,0x0,0x0,0x0,
0x1,0x1,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x22,0x22,0x22,0x22,0x22,0x22,0x0,0x0,0x0,
0x02,0x17,0x41,0xB0,0x32,0x28,
};

/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
static void EPD_1IN54_V2_Reset(void)
{
    gpio_Set_Display_Reset(1);
    timerWaitUs_polled(1000*200);
    gpio_Set_Display_Reset(0);
    timerWaitUs_polled(1000*2);
    gpio_Set_Display_Reset(1);
    timerWaitUs_polled(1000*200);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
static void EPD_1IN54_V2_SendCommand(uint8_t Reg)
{
    gpio_Set_Display_DC(0);
    DEV_SPI_WriteByte(Reg);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void EPD_1IN54_V2_SendData(uint8_t Data)
{
    gpio_Set_Display_DC(1);
    DEV_SPI_WriteByte(Data);
}

/******************************************************************************
function :	Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
static void EPD_1IN54_V2_ReadBusy(void)
{
    LOG_INFO("e-Paper busy\r\n");
    while(gpio_Read_Busy() == 1) {      //LOW: idle, HIGH: busy
        timerWaitUs_polled(1000*10);
    }
    LOG_INFO("e-Paper busy release\r\n");
}

/******************************************************************************
function :	Turn On Display full
parameter:
******************************************************************************/
static void EPD_1IN54_V2_TurnOnDisplay(void)
{
    EPD_1IN54_V2_SendCommand(0x22);
    EPD_1IN54_V2_SendData(0xc7);
    EPD_1IN54_V2_SendCommand(0x20);
    EPD_1IN54_V2_ReadBusy();
}

/******************************************************************************
function :	Turn On Display part
parameter:
******************************************************************************/
static void EPD_1IN54_V2_TurnOnDisplayPart(void)
{
    EPD_1IN54_V2_SendCommand(0x22);
    EPD_1IN54_V2_SendData(0xcF);
    EPD_1IN54_V2_SendCommand(0x20);
    EPD_1IN54_V2_ReadBusy();
}

static void EPD_1IN54_V2_Lut(uint8_t *lut)
{
	EPD_1IN54_V2_SendCommand(0x32);
	for(uint8_t i=0; i<153; i++)
		EPD_1IN54_V2_SendData(lut[i]);
	EPD_1IN54_V2_ReadBusy();
}

static void EPD_1IN54_V2_SetLut(uint8_t *lut)
{
	EPD_1IN54_V2_Lut(lut);
	
    EPD_1IN54_V2_SendCommand(0x3f);
    EPD_1IN54_V2_SendData(lut[153]);
	
    EPD_1IN54_V2_SendCommand(0x03);
    EPD_1IN54_V2_SendData(lut[154]);
	
    EPD_1IN54_V2_SendCommand(0x04);
    EPD_1IN54_V2_SendData(lut[155]);
	EPD_1IN54_V2_SendData(lut[156]);
	EPD_1IN54_V2_SendData(lut[157]);
	
	EPD_1IN54_V2_SendCommand(0x2c);
    EPD_1IN54_V2_SendData(lut[158]);
}

static void EPD_1IN54_V2_SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
    EPD_1IN54_V2_SendCommand(0x44); // SET_RAM_X_ADDRESS_START_END_POSITION
    EPD_1IN54_V2_SendData((Xstart>>3) & 0xFF);
    EPD_1IN54_V2_SendData((Xend>>3) & 0xFF);
	
    EPD_1IN54_V2_SendCommand(0x45); // SET_RAM_Y_ADDRESS_START_END_POSITION
    EPD_1IN54_V2_SendData(Ystart & 0xFF);
    EPD_1IN54_V2_SendData((Ystart >> 8) & 0xFF);
    EPD_1IN54_V2_SendData(Yend & 0xFF);
    EPD_1IN54_V2_SendData((Yend >> 8) & 0xFF);
}

static void EPD_1IN54_V2_SetCursor(uint16_t Xstart, uint16_t Ystart)
{
    EPD_1IN54_V2_SendCommand(0x4E); // SET_RAM_X_ADDRESS_COUNTER
    EPD_1IN54_V2_SendData(Xstart & 0xFF);

    EPD_1IN54_V2_SendCommand(0x4F); // SET_RAM_Y_ADDRESS_COUNTER
    EPD_1IN54_V2_SendData(Ystart & 0xFF);
    EPD_1IN54_V2_SendData((Ystart >> 8) & 0xFF);
}

/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
void EPD_1IN54_V2_Init(void)
{
    EPD_1IN54_V2_Reset();

    EPD_1IN54_V2_ReadBusy();
    EPD_1IN54_V2_SendCommand(0x12);  //SWRESET
    EPD_1IN54_V2_ReadBusy();

    EPD_1IN54_V2_SendCommand(0x01); //Driver output control
    EPD_1IN54_V2_SendData(0xC7);
    EPD_1IN54_V2_SendData(0x00);
    EPD_1IN54_V2_SendData(0x01);

    EPD_1IN54_V2_SendCommand(0x11); //data entry mode
    EPD_1IN54_V2_SendData(0x01);

    EPD_1IN54_V2_SetWindows(0, EPD_1IN54_V2_HEIGHT-1, EPD_1IN54_V2_WIDTH-1, 0);

    EPD_1IN54_V2_SendCommand(0x3C); //BorderWavefrom
    EPD_1IN54_V2_SendData(0x01);

    EPD_1IN54_V2_SendCommand(0x18);
    EPD_1IN54_V2_SendData(0x80);

    EPD_1IN54_V2_SendCommand(0x22); // //Load Temperature and waveform setting.
    EPD_1IN54_V2_SendData(0XB1);
    EPD_1IN54_V2_SendCommand(0x20);

    EPD_1IN54_V2_SetCursor(0, EPD_1IN54_V2_HEIGHT-1);
    EPD_1IN54_V2_ReadBusy();

    EPD_1IN54_V2_SetLut(WF_Full_1IN54);
}

/******************************************************************************
function :	Initialize the e-Paper register (Partial display)
parameter:
******************************************************************************/
void EPD_1IN54_V2_Init_Partial(void)
{
	EPD_1IN54_V2_Reset();
	EPD_1IN54_V2_ReadBusy();
	
	EPD_1IN54_V2_SetLut(WF_PARTIAL_1IN54_0);
	EPD_1IN54_V2_SendCommand(0x37); 
	EPD_1IN54_V2_SendData(0x00);  
	EPD_1IN54_V2_SendData(0x00);  
	EPD_1IN54_V2_SendData(0x00);  
	EPD_1IN54_V2_SendData(0x00); 
	EPD_1IN54_V2_SendData(0x00);  	
	EPD_1IN54_V2_SendData(0x40);  
	EPD_1IN54_V2_SendData(0x00);  
	EPD_1IN54_V2_SendData(0x00);   
	EPD_1IN54_V2_SendData(0x00);  
	EPD_1IN54_V2_SendData(0x00);

	EPD_1IN54_V2_SendCommand(0x3C); //BorderWavefrom
	EPD_1IN54_V2_SendData(0x80);
	
	EPD_1IN54_V2_SendCommand(0x22); 
	EPD_1IN54_V2_SendData(0xc0); 
	EPD_1IN54_V2_SendCommand(0x20); 
	EPD_1IN54_V2_ReadBusy();
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EPD_1IN54_V2_Clear(void)
{
    uint16_t Width, Height;
    Width = (EPD_1IN54_V2_WIDTH % 8 == 0)? (EPD_1IN54_V2_WIDTH / 8 ): (EPD_1IN54_V2_WIDTH / 8 + 1);
    Height = EPD_1IN54_V2_HEIGHT;

    EPD_1IN54_V2_SendCommand(0x24);
    for (uint16_t j = 0; j < Height; j++) {
        for (uint16_t i = 0; i < Width; i++) {
            EPD_1IN54_V2_SendData(0XFF);
        }
    }
    EPD_1IN54_V2_SendCommand(0x26);
    for (uint16_t j = 0; j < Height; j++) {
        for (uint16_t i = 0; i < Width; i++) {
            EPD_1IN54_V2_SendData(0XFF);
        }
    }
    EPD_1IN54_V2_TurnOnDisplay();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_1IN54_V2_Display(uint8_t *Image)
{
    uint16_t Width, Height;
    Width = (EPD_1IN54_V2_WIDTH % 8 == 0)? (EPD_1IN54_V2_WIDTH / 8 ): (EPD_1IN54_V2_WIDTH / 8 + 1);
    Height = EPD_1IN54_V2_HEIGHT;

    int Addr = 0;
    EPD_1IN54_V2_SendCommand(0x24);
    for (uint16_t j = 0; j < Height; j++) {
        for (uint16_t i = 0; i < Width; i++) {
            Addr = i + j * Width;
            EPD_1IN54_V2_SendData(Image[Addr]);
        }
    }
    EPD_1IN54_V2_TurnOnDisplay();
}

/******************************************************************************
function :	 The image of the previous frame must be uploaded, otherwise the
		         first few seconds will display an exception.
parameter:
******************************************************************************/
void EPD_1IN54_V2_DisplayPartBaseImage(uint8_t *Image)
{
    uint16_t Width, Height;
    Width = (EPD_1IN54_V2_WIDTH % 8 == 0)? (EPD_1IN54_V2_WIDTH / 8 ): (EPD_1IN54_V2_WIDTH / 8 + 1);
    Height = EPD_1IN54_V2_HEIGHT;

    int Addr = 0;
    EPD_1IN54_V2_SendCommand(0x24);
    for (uint16_t j = 0; j < Height; j++) {
        for (uint16_t i = 0; i < Width; i++) {
            Addr = i + j * Width;
            EPD_1IN54_V2_SendData(Image[Addr]);
        }
    }
    EPD_1IN54_V2_SendCommand(0x26);
    for (uint16_t j = 0; j < Height; j++) {
        for (uint16_t i = 0; i < Width; i++) {
            Addr = i + j * Width;
            EPD_1IN54_V2_SendData(Image[Addr]);
        }
    }
    EPD_1IN54_V2_TurnOnDisplayPart();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_1IN54_V2_DisplayPart(uint8_t *Image)
{
    uint16_t Width, Height;
    Width = (EPD_1IN54_V2_WIDTH % 8 == 0)? (EPD_1IN54_V2_WIDTH / 8 ): (EPD_1IN54_V2_WIDTH / 8 + 1);
    Height = EPD_1IN54_V2_HEIGHT;
	
    int Addr = 0;
    EPD_1IN54_V2_SendCommand(0x24);
    for (uint16_t j = 0; j < Height; j++) {
        for (uint16_t i = 0; i < Width; i++) {
            Addr = i + j * Width;
            EPD_1IN54_V2_SendData(Image[Addr]);
        }
    }
    EPD_1IN54_V2_TurnOnDisplayPart();
}
/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void EPD_1IN54_V2_Sleep(void)
{
    EPD_1IN54_V2_SendCommand(0x10); //enter deep sleep
    EPD_1IN54_V2_SendData(0x01);
    timerWaitUs_polled(1000*100);
}
