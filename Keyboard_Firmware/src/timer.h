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
 * @file    timer.h
 * @brief   Header file for letimer initialization function
 *
 *
 * @author  Parth Thakkar
 * @date    15th Feb 2024
 *
 */

#ifndef __TIMERS_H__
#define __TIMERS_H__

#include <stdbool.h> // include for uint32

#include "app.h"
#include "sl_status.h" // for sl_status_print()
#include "em_cmu.h"
#include "em_letimer.h"
#include "gpio.h"
#include <stdint.h>
#include "em_core.h"

/**
 * @brief Initializes the Low Energy Timer (LETIMER).
 *
 * This function configures the LETIMER for operation based on predefined settings.
 * It sets up the timer with specified on-time and period, configures interrupts, and
 * initializes the LETIMER peripheral. The timer is configured differently based on
 * the defined lowest energy mode (LOWEST_ENERGY_MODE).
 *
 *
 * @param None.
 *
 * @return void.
 */
void init_Timer(void);

/**
 * Implement a polled precise delay using LETIMER.
 * Calculates and sets a COMP1 value for the required delay, waits for the
 * COMP1 match interrupt, and clears the interrupt flag.
 *
 * @param us_wait The delay duration in microseconds.
 */
void timerWaitUs_polled(uint32_t us);

/**
 * Implement a Interrupt based precise delay using LETIMER.
 * Calculates and sets a COMP1 value for the required delay
 * sets the COMP1 value and leaves the rest to State machine
 *
 * @param us_wait The delay duration in microseconds.
 */
void timerWaitUs_irq(uint32_t us);

#endif
