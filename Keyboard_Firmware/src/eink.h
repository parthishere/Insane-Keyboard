/*
Header file for E-ink Display 
*/

#ifndef _EINK_H_
#define _EINK_H_

//includes 
#include <stdio.h>
#include<stdint.h>
#include"spi.h"
#include"gpio.h"
#include"timer.h"


//Port and Pins
#define RST_Pin rst_x
#define RST_GPIO_Port rst_p
#define DC_Pin dc_x
#define DC_GPIO_Port dc_port
#define BUSY_Pin busy_x
#define BUSY_GPIO_Port busy_port
#define SPI_CS_Pin cs_x
#define SPI_CS_GPIO_Port cs_port
#define PWR_Pin pwr_x
#define PWR_GPIO_Port pwr_port
#define DIN_Pin din_x
#define DIN_GPIO_Port din_port
#define SCK_Pin sck_x
#define SCK_GPIO_Port sck_port

//GPIO eink
#define EINK_RST    RST_GPIO_Port, RST_Pin
#define EINK_DC     DC_GPIO_Port, DC_Pin   
#define EINK_PWR    PWR_GPIO_Port, PWR_Pin
#define EINK_CS     SPI_CS_GPIO_Port, SPI_CS_Pin
#define EINK_BUSY   BUSY_GPIO_Port, BUSY_Pin
#define EINK_MOSI   DIN_GPIO_Port, DIN_Pin
#define EINK_SCLK   SCK_GPIO_Port, SCK_Pin
   

// Display resolution
#define EINK_WIDTH       200
#define EINK_HEIGHT      200

typedef enum
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET
} GPIO_PinState;


// /**
//  * GPIO read and write (0/1)
// **/
// #define EINK_Digital_Write(pin, _value) GPIO_WritePin(pin, _value == 0? GPIO_PIN_RESET:GPIO_PIN_SET)
// #define EINK_Digital_Read(pin) GPIO_ReadPin(pin)


/**
 * delay x ms
**/
#define EINK_Delay_ms(xms) timerWaitUs_polled(xms);

/*
SPI data read and write
*/
#define EINK_SPI_ReadData(r_data, size_in_bytes) receiveBytes(r_data, size_in_bytes)
#define EINK_SPI_WriteData(t_data, size_in_bytes) transmitBytes(t_data, size_in_bytes)

Modules Inits
void EINK_Module_Init(void);
void EINK_Module_Exit(void);

void EINK_Init(void);
void EINK_Init_Partial(void);
void EINK_Clear(void);
void EINK_Display(uint8_t *Image);
void EINK_DisplayPart(uint8_t *Image);
void EINK_Sleep(void);
void display_test(void);

#endif