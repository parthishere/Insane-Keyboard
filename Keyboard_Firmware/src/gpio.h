/*
   gpio.h

    Created on: Dec 12, 2018
        Author: Dan Walkes

    Updated by Dave Sluiter Sept 7, 2020. moved #defines from .c to .h file.
    Updated by Dave Sluiter Dec 31, 2020. Minor edits with #defines.

    Editor: Feb 26, 2022, Dave Sluiter
    Change: Added comment about use of .h files.

 *
 * Student edit: Add your name and email address here:
 * @student    Awesome Student, Awesome.Student@Colorado.edu
 *

 */

// Students: Remember, a header file (a .h file) generally defines an interface
//           for functions defined within an implementation file (a .c file).
//           The .h file defines what a caller (a user) of a .c file requires.
//           At a minimum, the .h file should define the publicly callable
//           functions, i.e. define the function prototypes. #define and type
//           definitions can be added if the caller requires theses.

#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#include "em_cmu.h"

/*
 * Initializes the GPIO pins with predefined settings for LEDs and sensors.
 * This setup involves setting the drive strength and mode for the LED and sensor pins.
 * No parameters and no return value.
 */
void gpioInit();
/*
 * Turns on LED0 by setting its corresponding GPIO pin high.
 * No parameters and no return value.
 */
void gpioLed0SetOn();
/*
 * Turns off LED0 by clearing its corresponding GPIO pin.
 * No parameters and no return value.
 */
void gpioLed0SetOff();
/*
 * Turns on LED1 by setting its corresponding GPIO pin high.
 * No parameters and no return value.
 */
void gpioLed1SetOn();
/*
 * Turns off LED1 by clearing its corresponding GPIO pin.
 * No parameters and no return value.
 */
void gpioLed1SetOff();

/*
 * Enables the sensor by setting its enable pin high.
 * No parameters and no return value.
 */
void sensor_Enable();
/*
 * Disables the sensor by clearing its enable pin.
 * No parameters and no return value.
 */
void sensor_Disable();

/*
 * Sets the display's external communication pin (EXTCOMIN) according to the parameter.
 *
 * @param on A boolean value indicating the desired state of the EXTCOMIN pin.
 *           If true, the EXTCOMIN pin is set high; if false, it is cleared (set low).
 * No return value.
 */
void gpioSetDisplayExtcomin(bool on);

#endif /* SRC_GPIO_H_ */
