/*******************************************************************************
 * Copyright (C) 2024 by Parth Thakkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Parth Thakkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    oscillator.h
 * @brief   Header file for oscillator initialization function
 *
 *
 * @author  Parth Thakkar
 * @date    27st Sept 2024
 *
 */

#ifndef __OSCILLATOR_H__
#define __OSCILLATOR_H__
#include "app.h"
#include "sl_status.h" // for sl_status_print()
#include "em_cmu.h"

/**
 * @brief Initializes the oscillator for LETIMER0.
 *
 * This function configures the oscillator that drives the LETIMER0.
 * If the system is not in the lowest energy mode EM3, it selects the LFXO (Low Frequency Crystal Oscillator)
 * and sets its division factor. Otherwise, it selects ULFRCO (Ultra Low Frequency RC Oscillator)
 * as the clock source for LETIMER0.
 *
 * @note The LOWEST_ENERGY_MODE macro is defined externally.
 *
 * @param None.
 *
 * @return void.
 */
void init_Oscillator(void);

#endif // !__OSCILLATOR_H__
