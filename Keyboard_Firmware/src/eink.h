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
#define EINK_SPI_ReadData(r_data, size_in_bytes) receiveBytes(&r_data, (uint8_t)size_in_bytes)
#define EINK_SPI_WriteData(t_data, size_in_bytes) transmitBytes(&t_data, (uint8_t)size_in_bytes)

// Modules Inits
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
