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
 * @file    oscillator.c
 * @brief   Oscillator configuration for Low Energy Timer (LETIMER).
 *
 * This file contains the implementation for initializing the oscillator used by LETIMER0.
 * It selects the appropriate oscillator (LFXO or ULFRCO) based on the system's energy mode
 * and configures it for optimal operation in that mode.
 *
 * @author  Parth Thakkar
 * @date    27st Sept 2024
 *
 */

#include "oscillator.h" // Include the header file for oscillator-related functions and definitions.



/**
 * @brief Initializes the oscillator for LETIMER0.
 *
 * This function configures the oscillator that drives the LETIMER0.
 * If the system is not in the lowest energy mode EM3, it selects the LFXO (Low Frequency Crystal Oscillator)
 * and sets its division factor. Otherwise, it selects ULFRCO (Ultra Low Frequency RC Oscillator)
 * as the clock source for LETIMER0.
 *
 * @note The LOWEST_ENERGY_MODE macro is assumed to be defined externally.
 *
 * @param None.
 *
 * @return void.
 */
void init_Oscillator(void)
{
  if(LOWEST_ENERGY_MODE > 3){
       // For EM2 mode

      //For EM1 mode
  }
  else{
      //EM3 Mode and lower
  }
} // init_Oscillator()
