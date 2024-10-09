/*******************************************************************************
 * Copyright (C) 2023 by Parth Thakkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Parth Thakkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    irq.c
 * @brief   Interrupt Service Routines for the LETIMER0.
 *
 * This file provides the implementation of the Interrupt Service Routine (ISR) for LETIMER0.
 * It includes handling for different types of interrupts like Compare Match 1 and Underflow,
 * and actions to be performed in each case, such as LED control.
 *
 * @author  Parth Thakkar
 * @date    15th Feb 2024
 *
 */

#include "irq.h" // Include the header file for interrupt-related functions and definitions.

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"

// Interval for log timing
#define UF_TIME_MS 3000
#define SW0_pin (6)
#define SW1_pin (7)

volatile uint32_t underflow_count = 0;

/**
 * @brief Interrupt Service Routine for LETIMER0.
 *
 * This function is called when LETIMER0 generates an interrupt. It handles two types
 * of interrupts: Compare Match 1 and Underflow. The function checks which interrupt
 * occurred and performs actions accordingly, such as turning an LED on or off.
 * The function operates within a critical section to ensure atomic operations.
 *
 *
 * @param None.
 *
 * @return void.
 */
void LETIMER0_IRQHandler(void)
{
    CORE_DECLARE_IRQ_STATE; // Declare variable to hold the interrupt state.

    CORE_ENTER_CRITICAL(); // Enter a critical section to prevent interruption during flag handling.

    volatile uint32_t flags = LETIMER_IntGetEnabled(LETIMER0); // Retrieve currently enabled interrupt flags.
    LETIMER_IntClear(LETIMER0, flags);                         // Clear the interrupt flags to prevent re-triggering.

    if ((flags & LETIMER_IEN_UF) > 0)
    { // Check if Underflow Interrupt flag is set.
        // Handle Underflow Interrupt.
        schedulerSetEventUF();
        underflow_count++;
    }
    if ((flags & LETIMER_IEN_COMP1) > 0)
    { // Check if Underflow Interrupt flag is set.
        // Handle Underflow Interrupt.

        schedularSetEventCOMP1();
    }
    CORE_EXIT_CRITICAL(); // Exit the critical section, allowing other interrupts to be processed.
} // LETIMER0_IRQHandler

/**
 * @brief Interrupt Service Routine (ISR) for I2C0.
 *
 * This function serves as the ISR for I2C0 interrupts. It handles the I2C communication by calling the
 * I2C_Transfer function to process ongoing data transfers. Upon successful completion of a transfer,
 * it sets an I2C event in the scheduler to notify the system of the completed transfer. If an error occurs
 * during the transfer, it logs the error with the specific error code.
 * only performs actions related to the I2C transfer status.
 *
 */
void I2C0_IRQHandler(void)
{

    // Call the I2C_Transfer function to handle the I2C interrupt and move the state machine forward.
    I2C_TransferReturn_TypeDef transferStatus = I2C_Transfer(I2C0);

    // Check if the I2C transfer is complete.
    if (transferStatus == i2cTransferDone)
    {
        // If the transfer is done, set the corresponding I2C event in the scheduler.
        schedularSetEventI2C();
    }
    else if (transferStatus < 0)
    {
        // If an error occurred (transfer status is negative), log the error with its code.
        LOG_ERROR("Error Occurred: %d\n", transferStatus);
    }

} // LETIMER0_IRQHandler



/**
 * Handles GPIO interrupts for odd-numbered GPIO pins.
 * This interrupt service routine (ISR) is triggered by events on odd-numbered GPIO pins. It reads
 * the interrupt flags to determine which pin(s) caused the interrupt, clears these flags, and then
 * performs actions based on the specific pin(s) involved. In the context of a BLE server device, this
 * ISR specifically checks for events related to the SW1 pin (assumed to be odd-numbered) and triggers
 * appropriate actions (like setting an event in a scheduler) in response to these events.
 */
void GPIO_ODD_IRQHandler(void)
{
    uint32_t flags = GPIO_IntGetEnabled();
    GPIO_IntClear(flags);

    // during reading for client
    if (flags & (1 << SW1_pin))
    {
        // sw1 pressed
        schedularSetEventPB1();
    }

    // GPIO_PinInGet
}



/**
 * Handles GPIO interrupts for even-numbered GPIO pins.
 * Similar to its odd-numbered counterpart, this interrupt service routine (ISR) is called when an
 * event occurs on any even-numbered GPIO pin. It identifies the source(s) of the interrupts by checking
 * the enabled interrupt flags, clears these flags, and then triggers specific responses. For a BLE server
 * device, this function is concerned with actions related to the SW0 pin,
 * such as scheduling specific events in response to button presses or other triggers.
 */
void GPIO_EVEN_IRQHandler(void)
{
    uint32_t flags = GPIO_IntGetEnabled();
    GPIO_IntClear(flags);

    // during pairing and bonding confirmation for server
    if (flags & (1 << SW0_pin))
    {
        // sw0 pressed
        schedularSetEventPB0();
    }

}


/**
 * @brief Calculate the total elapsed time in milliseconds based on LETIMER underflows.
 *
 * This function calculates the total time elapsed in milliseconds by multiplying the number
 * of LETIMER underflows by the predefined duration of one underflow event in milliseconds (UF_TIME_MS).
 * each underflow represents a fixed and known time interval, allowing for the
 * calculation of the total elapsed time since the LETIMER started counting underflows.
 *
 * @return uint32_t The total elapsed time in milliseconds since the LETIMER started.
 */
uint32_t letimerMilliseconds(void)
{
    // Return interval for underflow count and underflow millisecond (3000ms)
    return ((underflow_count * UF_TIME_MS));
}
