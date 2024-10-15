/*
  gpio.c

   Created on: Dec 12, 2018
       Author: Dan Walkes
   Updated by Dave Sluiter Dec 31, 2020. Minor edits with #defines.

   March 17
   Dave Sluiter: Use this file to define functions that set up or control GPIOs.

   Jan 24, 2023
   Dave Sluiter: Cleaned up gpioInit() to make it less confusing for students regarding
                 drive strength setting.

 *
 * Student edit: Add your name and email address here:
 * @student    Awesome Student, Awesome.Student@Colorado.edu
 *

 */

// *****************************************************************************
// Students:
// We will be creating additional functions that configure and manipulate GPIOs.
// For any new GPIO function you create, place that function in this file.
// *****************************************************************************

#include <stdbool.h>
#include "em_gpio.h"
#include <string.h>

#include "gpio.h"

// Student Edit: Define these, 0's are placeholder values.
//
// See the radio board user guide at https://www.silabs.com/documents/login/user-guides/ug279-brd4104a-user-guide.pdf
// and GPIO documentation at https://siliconlabs.github.io/Gecko_SDK_Doc/efm32g/html/group__GPIO.html
// to determine the correct values for these.
// If these links have gone bad, consult the reference manual and/or the datasheet for the MCU.
// Change to correct port and pins:

#define INTNO0 0 // from 0,1,2,3
#define INTNO1 1 // from 4,5,6,7 // odd
#define INTNO2 2 // from 8,9,10,11
#define INTNO3 3 // from 12,13,14,15

#define LED_port (gpioPortF)
#define LED0_pin (4)
#define LED1_pin (5)

#define SW_PORT (gpioPortF)
#define SW0_pin (6)
#define SW1_pin (7)

#define SENSOR_ENABLE_PORT (gpioPortD)
#define SENSOR_ENABLE (15)
#define DISP_EXTCOMIN_PIN (13)

#define ROTARY_ENCODER_PORT (gpioPortD)
#define ROTARY_ENCODER_A_PIN (10)
#define ROTARY_ENCODER_B_PIN (11)

#define SENSOR_ENABLE_PORT (gpioPortD)
#define SENSOR_ENABLE (15)
#define DISP_EXTCOMIN_PIN (13)




/*
 * Initializes the GPIO pins with predefined settings for LEDs and sensors.
 * This setup involves setting the drive strength and mode for the LED and sensor pins.
 * No parameters and no return value.
 */
void gpioInit()
{
  // Student Edit:

  // Set the port's drive strength. In this MCU implementation, all GPIO cells
  // in a "Port" share the same drive strength setting.
  // GPIO_DriveStrengthSet(LED_port, gpioDriveStrengthStrongAlternateStrong); // Strong, 10mA
  GPIO_DriveStrengthSet(LED_port, gpioDriveStrengthWeakAlternateWeak); // Weak, 1mA

  // GPIO_DriveStrengthSet(LED_port, gpioDriveStrengthWeakAlternateWeak);            // Weak, 1mA
  GPIO_DriveStrengthSet(ROTARY_ENCODER_PORT, gpioDriveStrengthWeakAlternateWeak); // Weak, 1mA
  GPIO_DriveStrengthSet(SENSOR_ENABLE_PORT, gpioDriveStrengthWeakAlternateWeak);

  GPIO_PinModeSet(ROTARY_ENCODER_PORT, ROTARY_ENCODER_A_PIN, gpioModeInput, true);
  GPIO_PinModeSet(ROTARY_ENCODER_PORT, ROTARY_ENCODER_B_PIN, gpioModeInput, true);

  GPIO_ExtIntConfig(ROTARY_ENCODER_PORT, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_B_PIN, 1, 0, true);

  GPIO_DriveStrengthSet(SENSOR_ENABLE_PORT, gpioDriveStrengthWeakAlternateWeak);
  GPIO_PinModeSet(SENSOR_ENABLE_PORT, SENSOR_ENABLE, gpioModePushPull, false);

  NVIC_ClearPendingIRQ(GPIO_ODD_IRQn); // Clear pending interrupts for LETIMER.
  NVIC_EnableIRQ(GPIO_ODD_IRQn);       // Enable NVIC interrupts for LETIMER.
  NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn); // Clear pending interrupts for LETIMER.
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);       // Enable NVIC interrupts for LETIMER.

} // gpioInit()

/*
 * Turns on LED0 by setting its corresponding GPIO pin high.
 * No parameters and no return value.
 */
void gpioLed0SetOn()
{
  GPIO_PinOutSet(LED_port, LED0_pin);
}

/*
 * Turns off LED0 by clearing its corresponding GPIO pin.
 * No parameters and no return value.
 */
void gpioLed0SetOff()
{
  GPIO_PinOutClear(LED_port, LED0_pin);
}

/*
 * Turns on LED1 by setting its corresponding GPIO pin high.
 * No parameters and no return value.
 */
void gpioLed1SetOn()
{
  GPIO_PinOutSet(LED_port, LED1_pin);
}

/*
 * Turns off LED1 by clearing its corresponding GPIO pin.
 * No parameters and no return value.
 */
void gpioLed1SetOff()
{
  GPIO_PinOutClear(LED_port, LED1_pin);
}

/*
 * Enables the sensor by setting its enable pin high.
 * No parameters and no return value.
 */
void sensor_Enable()
{
  GPIO_PinOutSet(SENSOR_ENABLE_PORT, SENSOR_ENABLE);
}

/*
 * Disables the sensor by clearing its enable pin.
 * No parameters and no return value.
 */
void sensor_Disable()
{
  GPIO_PinOutClear(SENSOR_ENABLE_PORT, SENSOR_ENABLE);
}

/*
 * Sets the display's external communication pin (EXTCOMIN) according to the parameter.
 *
 * @param on A boolean value indicating the desired state of the EXTCOMIN pin.
 *           If true, the EXTCOMIN pin is set high; if false, it is cleared (set low).
 * No return value.
 */
void gpioSetDisplayExtcomin(bool on)
{
  if (on)
  {
    GPIO_PinOutSet(SENSOR_ENABLE_PORT, DISP_EXTCOMIN_PIN); // Turn the display COM pin on
  }
  else
  {
    GPIO_PinOutClear(SENSOR_ENABLE_PORT, DISP_EXTCOMIN_PIN); // Turn the display COM pin off
  }
}

