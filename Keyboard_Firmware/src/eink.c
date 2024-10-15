/*
E-ink display source file
*/

#include<src/eink.h>
#include <stdint.h>


// Enables debug logging for this file
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h" // Includes the logging header for debug messages


// Modules Inits
void EINK_Module_Init(void)
{
    gpio_Set_Display_DC(0);
    gpio_Set_Display_Reset(1);
}


void EINK_Module_Exit(void)
{
    gpio_Set_Display_DC(0);
    gpio_Set_Display_Reset(0);
}

//Software Reset
static void EINK_Reset(void)
{
    gpio_Set_Display_Reset(1);
    EINK_Delay_ms(200);
    gpio_Set_Display_Reset(0);
    EINK_Delay_ms(2);
    gpio_Set_Display_Reset(1);
    EINK_Delay_ms(200);
}

//Send Command
static void EINK_SendCommand(uint8_t value)
{
    gpio_Set_Display_DC(0);
    //EINK_Digital_Write(EINK_CS, 0);
    EINK_SPI_WriteData(value, 1);
    //EINK_Digital_Write(EINK_CS, 1);
}

//Send Data
static void EINK_SendData(uint8_t value)
{
    gpio_Set_Display_DC(1);
    //EINK_Digital_Write(EINK_CS, 0);
    EINK_SPI_WriteData(value, 1);
   // EINK_Digital_Write(EINK_CS, 1);
}

//Wait until the busy_pin goes LOW
static void EINK_ReadBusy(void)
{
    while(gpio_Read_Busy() == 1) 
    {      //LOW: idle, HIGH: busy
    }
}


//Turn On Display full
static void EINK_TurnOnDisplay(void)
{
    EINK_SendCommand(0x22);
    EINK_SendData(0xc7);
    EINK_SendCommand(0x20);
    //EINK_ReadBusy();
}


//Turn On Display part
static void EINK_TurnOnDisplayPart(void)
{
    EINK_SendCommand(0x22);
    EINK_SendData(0xcF);
    EINK_SendCommand(0x20);
    //EINK_ReadBusy();
}

//set window
static void EINK_SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
    EINK_SendCommand(0x44); // SET_RAM_X_ADDRESS_START_END_POSITION
    EINK_SendData((Xstart>>3) & 0xFF);
    EINK_SendData((Xend>>3) & 0xFF);
	
    EINK_SendCommand(0x45); // SET_RAM_Y_ADDRESS_START_END_POSITION
    EINK_SendData(Ystart & 0xFF);
    EINK_SendData((Ystart >> 8) & 0xFF);
    EINK_SendData(Yend & 0xFF);
    EINK_SendData((Yend >> 8) & 0xFF);
}

//set curser
static void EINK_SetCursor(uint16_t Xstart, uint16_t Ystart)
{
    EINK_SendCommand(0x4E); // SET_RAM_X_ADDRESS_COUNTER
    EINK_SendData(Xstart & 0xFF);

    EINK_SendCommand(0x4F); // SET_RAM_Y_ADDRESS_COUNTER
    EINK_SendData(Ystart & 0xFF);
    EINK_SendData((Ystart >> 8) & 0xFF);
}

// EINK initialization sequence
void EINK_Init(void)
{
    EINK_Reset();

    //EINK_ReadBusy();
    EINK_SendCommand(0x12);  //SWRESET
    //EINK_ReadBusy();

    EINK_SendCommand(0x01); //Driver output control
    EINK_SendData(0xC7);
    EINK_SendData(0x00);
    EINK_SendData(0x00);

    EINK_SendCommand(0x11); //data entry mode
    EINK_SendData(0x01);

    EINK_SetWindows(0, EINK_HEIGHT-1, EINK_WIDTH-1, 0);

    EINK_SendCommand(0x3C); //BorderWavefrom
    EINK_SendData(0x01);

    EINK_SendCommand(0x18); // Temperature Sensor Control
    EINK_SendData(0x80);

    EINK_SendCommand(0x22); // //Load Temperature and waveform setting.
    EINK_SendData(0XB1);
    EINK_SendCommand(0x20);

    EINK_SetCursor(0, EINK_HEIGHT-1);
    //EINK_ReadBusy();
}

//Partial Init
void EINK_Init_Partial(void)
{
    EINK_Reset();
	//EINK_ReadBusy();
	
	EINK_SendCommand(0x37); 
	EINK_SendData(0x00);  
	EINK_SendData(0x00);  
	EINK_SendData(0x00);  
	EINK_SendData(0x00); 
	EINK_SendData(0x00);  	
	EINK_SendData(0x40);  
	EINK_SendData(0x00);  
	EINK_SendData(0x00);   
	EINK_SendData(0x00);  
	EINK_SendData(0x00);

	EINK_SendCommand(0x3C); //BorderWavefrom
	EINK_SendData(0x80);
	
	EINK_SendCommand(0x22); 
	EINK_SendData(0xc0); 
	EINK_SendCommand(0x20); 
	//EINK_ReadBusy();
}

//clear
void EINK_Clear(void)
{
    uint8_t Width, Height;
    Width = (EINK_WIDTH % 8 == 0)? (EINK_WIDTH / 8 ): (EINK_WIDTH / 8 + 1);
    Height = EINK_HEIGHT;

    EINK_SendCommand(0x24);
    for (uint16_t j = 0; j < Height; j++) 
    {
        for (uint16_t i = 0; i < Width; i++) 
        {
            EINK_SendData(0XFF);
        }
    }
    EINK_SendCommand(0x26);
    for (uint16_t j = 0; j < Height; j++) 
    {
        for (uint16_t i = 0; i < Width; i++) 
        {
            EINK_SendData(0XFF);
        }
    }
    EINK_TurnOnDisplay();
}

//dispaly image
void EINK_Display(uint8_t *Image)
{
    uint16_t Width, Height;
    Width = (EINK_WIDTH % 8 == 0)? (EINK_WIDTH / 8 ): (EINK_WIDTH / 8 + 1);
    Height = EINK_HEIGHT;

    uint32_t Addr = 0;
    EINK_SendCommand(0x24);
    for (uint16_t j = 0; j < Height; j++) 
    {
        for (uint16_t i = 0; i < Width; i++) 
        {
            Addr = i + j * Width;
            EINK_SendData(Image[Addr]);
        }
    }
    EINK_TurnOnDisplay();
}

//Sends the image buffer in RAM to e-Paper and displays
void EINK_DisplayPart(uint8_t *Image)
{
    uint16_t Width, Height;
    Width = (EINK_WIDTH % 8 == 0)? (EINK_WIDTH / 8 ): (EINK_WIDTH / 8 + 1);
    Height = EINK_HEIGHT;
	
    uint32_t Addr = 0;
    EINK_SendCommand(0x24);
    for (uint16_t j = 0; j < Height; j++) 
    {
        for (uint16_t i = 0; i < Width; i++) 
        {
            Addr = i + j * Width;
            EINK_SendData(Image[Addr]);
        }
    }
    EINK_TurnOnDisplayPart();
}
void EINK_Sleep(void)
{
    EINK_SendCommand(0x10); //enter deep sleep
    EINK_SendData(0x01);
    EINK_Delay_ms(100);
}


void display_test(void)
{
    EINK_Module_Init();

    LOG_INFO("e-Paper Init and Clear...\r\n");
    EINK_Init();
    EINK_Clear();
    EINK_Delay_ms(500);
    EINK_Module_Exit();
}
