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
 * @file    irq.h
 * @brief   Header file for LETIMER IRQ
 *
 *
 * @author  Parth Thakkar
 * @date    15th Feb 2024
 *
 */

#ifndef __IRQ_H__
#define __IRQ_H__

#include "gpio.h"
#include "em_letimer.h"
#include "em_core.h"
#include "scheduler.h"
#include "em_i2c.h"
#include "em_core.h"

/**
 * @brief Interrupt Service Routine for LETIMER0.
 *
 * This function is called when LETIMER0 generates an interrupt. It handles two types
 * of interrupts: Compare Match 1 and Underflow. The function checks which interrupt
 * occurred and performs scheduling of events accordingly
 *
 * The function operates within a critical section to ensure atomic operations.
 *
 *
 * @param None.
 *
 * @return void.
 */
void LETIMER0_IRQHandler(void);

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
void I2C0_IRQHandler(void);

/**
 * Handles GPIO interrupts for odd-numbered GPIO pins.
 * This interrupt service routine (ISR) is triggered by events on odd-numbered GPIO pins. It reads
 * the interrupt flags to determine which pin(s) caused the interrupt, clears these flags, and then
 * performs actions based on the specific pin(s) involved. In the context of a BLE server device, this
 * ISR specifically checks for events related to the SW1 pin and triggers
 * appropriate actions setting an event in a scheduler
 */
void GPIO_ODD_IRQHandler(void);


/**
 * Handles GPIO interrupts for even-numbered GPIO pins.
 * Similar to its odd-numbered counterpart, this interrupt service routine (ISR) is called when an
 * event occurs on any even-numbered GPIO pin. It identifies the source(s) of the interrupts by checking
 * the enabled interrupt flags, clears these flags, and then triggers specific responses. For a BLE server
 * device, this function is concerned with actions related to the SW0 pin,
 * such as scheduling specific events in response to button presses or other triggers.
 */
void GPIO_EVEN_IRQHandler(void);

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
uint32_t letimerMilliseconds(void);

#endif // !__IRQ_H__
