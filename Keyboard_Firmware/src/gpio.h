/*
   gpio.h
 */


#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#include "em_cmu.h"



#define EXPANDER_RESET_port (gpioPortB)
#define EXPANDER_RESET_pin (12)
#define EXPANDER_RESET EXPANDER_RESET_port, EXPANDER_RESET_pin

#define EXPANDER_RESET_INT0_pin
#define EXPANDER_RESET_INT0 EXPANDER_RESET_port, EXPANDER_RESET_INT0

#define EXPANDER_RESET_INT1_pin
#define EXPANDER_RESET_INT1 EXPANDER_RESET_port, EXPANDER_RESET_INT1_pin

//GPIO eink
#define RST_GPIO_Port gpioPortC
#define RST_Pin 6
#define EINK_RST    RST_GPIO_Port, RST_Pin

#define DC_GPIO_Port gpioPortD
#define DC_Pin 15
#define EINK_DC     DC_GPIO_Port, DC_Pin   

#define BUSY_GPIO_Port gpioPortA
#define BUSY_Pin 5
#define EINK_BUSY   BUSY_GPIO_Port, BUSY_Pin


#define ROTARY_ENCODER_port (gpioPortD)
#define ROTARY_ENCODER_A_pin (10)
#define ROTARY_ENCODER_A ROTARY_ENCODER_port, ROTARY_ENCODER_A_pin

#define ROTARY_ENCODER_B_pin (11)
#define ROTARY_ENCODER_B ROTARY_ENCODER_port, ROTARY_ENCODER_B_pin

#define ROTERY_ENCODER_SW_pin (7)
#define ROTARY_ENCODER_SW ROTARY_ENCODER_port, ROTERY_ENCODER_SW_pin

#define TEMP_ENABLE_port (gpioPortD)
#define TEMP_ENABLE_pin (15)
#define TEMP_ENABLE TEMP_ENABLE_port, TEMP_ENABLE_pin

#define DISPLAY_ENABLE_port (gpioPortD)
#define DISPLAY_ENABLE_pin (15)
#define DISPLAY_ENABLE DISPLAY_ENABLE_port, DISPLAY_ENABLE_pin



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
uint32_t enable_Temperature_Sensor(bool on);

/*
 * Enables the display by setting its enable pin high.
 * No parameters and no return value.
 */
uint32_t enable_Display(bool on);



#endif /* SRC_GPIO_H_ */
