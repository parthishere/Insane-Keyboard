/*
   gpio.h
 */


#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#include "em_cmu.h"




#define EXPANDER_INT_port (gpioPortA)
#define EXPANDER_INT_0_pin 4
#define EXPANDER_INT_0 EXPANDER_INT_port, EXPANDER_INT_0_pin


#define EXPANDER_INT_1_pin 5
#define EXPANDER_INT_1 EXPANDER_INT_port, EXPANDER_INT_1_pin



//GPIO eink
#define RST_GPIO_Port gpioPortA
#define RST_Pin 2
#define DISPLAY_RST    RST_GPIO_Port, RST_Pin

#define DC_GPIO_Port gpioPortA
#define DC_Pin 3
#define DISPLAY_DC     DC_GPIO_Port, DC_Pin   

#define BUSY_GPIO_Port gpioPortD
#define BUSY_Pin 12
#define DISPLAY_BUSY   BUSY_GPIO_Port, BUSY_Pin



#define ROTARY_ENCODER_port (gpioPortD)
#define ROTARY_ENCODER_A_pin (10)
#define ROTARY_ENCODER_A ROTARY_ENCODER_port, ROTARY_ENCODER_A_pin

#define ROTARY_ENCODER_B_pin (11)
#define ROTARY_ENCODER_B ROTARY_ENCODER_port, ROTARY_ENCODER_B_pin

#define ROTERY_ENCODER_SW_pin (14)
#define ROTARY_ENCODER_SW ROTARY_ENCODER_port, ROTERY_ENCODER_SW_pin



#define ON_TEMP_port (gpioPortD)
#define ON_TEMP_pin (12)
#define ON_TEMP ON_TEMP_port, ON_TEMP_pin

#define ON_DISPLAY_port (gpioPortD)
#define ON_DISPLAY_pin (13)
#define ON_DISPLAY ON_DISPLAY_port, ON_DISPLAY_pin



void gpioInit();


uint32_t gpio_Read_Busy(void);

/*
 * Sets the display's external communication pin (EXTCOMIN) according to the parameter.
 *
 * @param on A boolean value indicating the desired state of the EXTCOMIN pin.
 *           If true, the EXTCOMIN pin is set high; if false, it is cleared (set low).
 * No return value.
 */
void gpio_Set_Display_Reset(bool on);


void gpio_Set_Display_DC(bool on);


/*
 * Enables the temp sensor by setting its enable pin high.
 * No parameters and no return value.
 */
void enable_Temperature_Sensor(bool on);

/*
 * Enables the display by setting its enable pin high.
 * No parameters and no return value.
 */
void enable_Display(bool on);



#endif /* SRC_GPIO_H_ */
