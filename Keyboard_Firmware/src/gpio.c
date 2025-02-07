/*
  gpio.c

*/


#include <stdbool.h>
#include "em_gpio.h"
#include <string.h>

#include "gpio.h"


#define INTNO0 0 // from 0,1,2,3
#define INTNO1 1 // from 4,5,6,7 // odd
#define INTNO2 2 // from 8,9,10,11
#define INTNO3 3 // from 12,13,14,15


/*
 * Initializes the GPIO pins with predefined settings for LEDs and sensors.
 * This setup involves setting the drive strength and mode for the LED and sensor pins.
 * No parameters and no return value.
 */
void gpioInit()
{

  // Set the port's drive strength. In this MCU implementation, all GPIO cells
  // in a "Port" share the same drive strength setting.
  GPIO_DriveStrengthSet(gpioPortA, gpioDriveStrengthWeakAlternateWeak); // Weak, 1mA
  GPIO_DriveStrengthSet(gpioPortB, gpioDriveStrengthWeakAlternateWeak);
  GPIO_DriveStrengthSet(gpioPortC, gpioDriveStrengthWeakAlternateWeak);
  GPIO_DriveStrengthSet(gpioPortD, gpioDriveStrengthWeakAlternateWeak);
  GPIO_DriveStrengthSet(gpioPortF, gpioDriveStrengthWeakAlternateWeak);


  // INPUTS 
  GPIO_PinModeSet(ROTARY_ENCODER_A, gpioModeInput, true);
  GPIO_PinModeSet(ROTARY_ENCODER_B, gpioModeInput, true);
  GPIO_PinModeSet(ROTARY_ENCODER_SW, gpioModeInput, true);

  GPIO_PinModeSet(EXPANDER_INT_COL, gpioModeInput, true);
  GPIO_PinModeSet(EXPANDER_INT_ROW, gpioModeInput, false);

  GPIO_PinModeSet(DISPLAY_BUSY, gpioModeInput, true);


  // Setting Interrupts on inputs
  GPIO_ExtIntConfig(ROTARY_ENCODER_port, ROTARY_ENCODER_B_pin, ROTARY_ENCODER_B_pin, 1, 1, true); // on rising edge
  GPIO_ExtIntConfig(ROTARY_ENCODER_port, ROTARY_ENCODER_A_pin, ROTARY_ENCODER_A_pin, 1, 1, true); // on rising edge

  GPIO_ExtIntConfig(ROTARY_ENCODER_port, ROTERY_ENCODER_SW_pin, ROTERY_ENCODER_SW_pin, 1, 1, true); // on falling edge 
  GPIO_ExtIntConfig(EXPANDER_INT_port, EXPANDER_INT_ROW_pin, EXPANDER_INT_ROW_pin, 1, 1, true); // on rising-falling edge
  GPIO_ExtIntConfig(EXPANDER_INT_port, EXPANDER_INT_COL_pin, EXPANDER_INT_COL_pin, 1, 1, true); // on rising-falling edge


  // OUTPUTS
  GPIO_PinModeSet(DISPLAY_RST, gpioModePushPull, false); // output
  GPIO_PinModeSet(DISPLAY_DC, gpioModePushPull, false); // output
  GPIO_PinModeSet(ON_TEMP, gpioModePushPull, false); // output
  GPIO_PinModeSet(ON_DISPLAY, gpioModePushPull, false); // output
  GPIO_PinModeSet(ON_LED, gpioModePushPull, false); // output
  GPIO_PinModeSet(LED_DATA, gpioModePushPull, false); // output
  GPIO_PinModeSet(LED_TEST, gpioModePushPull, false); // output


  NVIC_ClearPendingIRQ(GPIO_ODD_IRQn); // Clear pending interrupts for ODD IRQs.
  NVIC_EnableIRQ(GPIO_ODD_IRQn);       // Enable NVIC interrupts for ODD IRQs.
  NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn); // Clear pending interrupts for Even IRQs.
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);       // Enable NVIC interrupts for EVEN IRQs.

} // gpioInit()




uint32_t gpio_Read_Busy(void){
  return GPIO_PinInGet(DISPLAY_BUSY);
}

/*
 * Sets the display's external communication pin (EXTCOMIN) according to the parameter.
 *
 * @param on A boolean value indicating the desired state of the EXTCOMIN pin.
 *           If true, the EXTCOMIN pin is set high; if false, it is cleared (set low).
 * No return value.
 */
void gpio_Set_Display_Reset(bool on)
{
  if (on)
  {
    GPIO_PinOutSet(DISPLAY_RST); // Turn the display COM pin on
  }
  else
  {
    GPIO_PinOutClear(DISPLAY_RST); // Turn the display COM pin off
  }
}


void gpio_Set_Display_DC(bool on)
{
  if (on)
  {
    GPIO_PinOutSet(DISPLAY_DC); // Turn the display COM pin on
  }
  else
  {
    GPIO_PinOutClear(DISPLAY_DC); // Turn the display COM pin off
  }
}


void led_test(bool on){
 if(on){
     GPIO_PinOutSet(LED_TEST); // Turn the display COM pin on
 }else{
     GPIO_PinOutClear(LED_TEST); // Turn the display COM pin off
 }
}

/*
 * Enables the temp sensor by setting its enable pin high.
 * No parameters and no return value.
 */
void enable_Temperature_Sensor(bool on){
  if(on){
    GPIO_PinOutSet(ON_TEMP);
  }
  else{
    GPIO_PinOutClear(ON_TEMP);
  }
}

/*  
 * Enables the display by setting its enable pin high.
 * No parameters and no return value.
 */
void enable_Display(bool on){
  if(on){
    GPIO_PinOutSet(ON_DISPLAY);
  }
  else{
    GPIO_PinOutClear(ON_DISPLAY);
  }
}


void enable_LEDs(bool on){
  if(on){
    GPIO_PinOutSet(ON_LED);
  }
  else{
    GPIO_PinOutClear(ON_LED);
  }
}

