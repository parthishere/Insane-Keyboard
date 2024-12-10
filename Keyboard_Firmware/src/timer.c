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
 * @file    timer.c
 * @brief   Timer initialization and configuration for low energy modes.
 *
 * This file contains functions to initialize and configure the Low Energy Timer (LETIMER)
 * for different energy modes. It includes setting up timer periods, on-times, and
 * interrupt handling depending on the system's energy mode.
 *
 * @author  Parth Thakkar
 * @date    15th Feb 2024
 *
 */

#include "timer.h" // Include the header file for timer-related functions and definitions.

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "log.h"

// Define constants for clock settings.
#define LFXO_CLOCK (32768) // Low Frequency Crystal Oscillator clock rate in Hz.
#define LFXO_PRESCALER (4) // Prescaler value for LFXO.

#define ULFRCO_CLOCK (1000) // Ultra Low Frequency RC Oscillator clock rate in Hz.



// Calculate maximum counter values for LETIMER with LFXO and ULFRCO settings.
#define LETIMER_LFXO_MAX_VALUE ((LETIMER_PERIOD_MS * (LFXO_CLOCK / LFXO_PRESCALER)) / 1000)

#define LETIMER_ULFRCO_MAX_VALUE ((LETIMER_PERIOD_MS * ULFRCO_CLOCK) / 1000)

// Maximum and minimum delays for LFXO and ULFRCO.
#define MAX_DELAY_FOR_LFXO 3000000   // Maximum delay for LFXO in microseconds.
#define MAX_DELAY_FOR_ULFRCO 3000000 // Maximum delay for ULFRCO in microseconds.

#define MIN_DELAY_FOR_LFXO_US 123    // Minimum delay for LFXO in microseconds.
#define MIN_DELAY_FOR_ULFRCO_US 1000 // Minimum delay for ULFRCO in microseconds.

#define COMP1 1 // Identifier for COMP1 register.

#define ONE_SEC_TO_US 1000000 // Conversion factor from seconds to microseconds.

// Determine the final clock rate based on the lowest energy mode setting.
#if (LOWEST_ENERGY_MODE != 3)
#define FINAL_CLOCK (LFXO_CLOCK / LFXO_PRESCALER)
#else
#define FINAL_CLOCK ULFRCO_CLOCK
#endif

#define PWM_FREQ 833333 //Hz // Time Period is 1.20 us.


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
void init_Timer(void)
{


  LETIMER_Init_TypeDef letimer_init; // Declare a structure for LETIMER initialization.

  letimer_init.enable = false;              // Disable LETIMER upon initialization.
  letimer_init.debugRun = true;             // LETIMER runs even when the debugger is halted.
  letimer_init.comp0Top = true;             // Load COMP0 register into CNT on underflow.
  letimer_init.repMode = letimerRepeatFree; // Set repeat mode to free running.

  // Conditional configuration based on energy mode.
  if (LOWEST_ENERGY_MODE != EM3_MODE)
  {
    // Top value. Counter wraps when top value matches counter value is
    letimer_init.topValue = LETIMER_LFXO_MAX_VALUE;
  }
  else
  {
    //  Top value. Counter wraps when top value matches counter value is
    letimer_init.topValue = LETIMER_ULFRCO_MAX_VALUE;
  }

  // Enable interrupts for Underflow only
  LETIMER_IntClear(LETIMER0, (LETIMER_IEN_UF));

  LETIMER_IntEnable(LETIMER0, (LETIMER_IEN_UF));

  // Final initialization and enabling of LETIMER.
  LETIMER_Init(LETIMER0, &letimer_init); // Initialize LETIMER with specified settings.

  // Enable clock for TIMER0 module
  // CMU_ClockEnable(cmuClock_TIMER0, true);
  // // Configure TIMER0 Compare/Capture for output compare
  // // Use PWM mode, which sets output on overflow and clears on compare events
  // TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;
  // timerCCInit.mode = timerCCModePWM;
  // TIMER_InitCC(TIMER0, 0, &timerCCInit);

  // // Set route to Location 15 and enable
  // // TIM0_CC0 #15 is PC10
  // TIMER0->ROUTELOC0 |=  TIMER_ROUTELOC0_CC0LOC_LOC31;
  // TIMER0->ROUTEPEN |= TIMER_ROUTEPEN_CC0PEN;

  // // Set top value to overflow at the desired PWM_FREQ frequency
  // TIMER_TopSet(TIMER0, CMU_ClockFreqGet(cmuClock_TIMER0) / PWM_FREQ);

  // // Initialize and start timer with no prescaling
  // TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
  // timerInit.dmaClrAct = true;

  // TIMER_Init(TIMER0, &timerInit);


  LETIMER_Enable(LETIMER0, true);      // Enable LETIMER.
  NVIC_ClearPendingIRQ(LETIMER0_IRQn); // Clear pending interrupts for LETIMER.
  NVIC_EnableIRQ(LETIMER0_IRQn);       // Enable NVIC interrupts for LETIMER.

} // init_Timer()




/**
 * Implement a polled precise delay using LETIMER.
 * Calculates and sets a COMP1 value for the required delay, waits for the
 * COMP1 match interrupt, and clears the interrupt flag.
 *
 * @param us_wait The delay duration in microseconds.
 */
void timerWaitUs_polled(uint32_t us_wait)
{
  // Validate the delay range based on the energy mode.
  if (LOWEST_ENERGY_MODE == EM3_MODE)
  {
    // For ULFRCO, check if delay is within allowed range.
    if (us_wait <= MIN_DELAY_FOR_ULFRCO_US)
    {
      LOG_ERROR("Delay is too less, out of range for ULFRCO mode.\n");
      us_wait = MIN_DELAY_FOR_ULFRCO_US;
    }
    else if (us_wait >= MAX_DELAY_FOR_ULFRCO)
    {
      LOG_ERROR("Delay is too Large, out of range for ULFRCO mode.\n");
      us_wait = MAX_DELAY_FOR_ULFRCO;
    }
  }
  else
  {
    // For LFXO, check if delay is within allowed range.
    if (us_wait <= MIN_DELAY_FOR_LFXO_US)
    {
      LOG_ERROR("Delay is too less, out of range for LFXO mode.\n");
      us_wait = MIN_DELAY_FOR_LFXO_US;
    }
    else if (us_wait >= MAX_DELAY_FOR_LFXO)
    {
      LOG_ERROR("Delay is too Large, out of range for LFXO mode.\n");
      us_wait = MAX_DELAY_FOR_LFXO;
    }
  }

  // Calculate the current counter value and the required counts for the delay.
  uint32_t current_count = LETIMER_CounterGet(LETIMER0);
  uint32_t needed_count_for_us = (uint32_t)((float)((float)us_wait / ONE_SEC_TO_US) * FINAL_CLOCK);
  uint32_t comp1_count = (((current_count - needed_count_for_us) + LETIMER_LFXO_MAX_VALUE) % LETIMER_LFXO_MAX_VALUE);

  // Set COMP1 for the calculated delay and wait for the COMP1 match interrupt.
  LETIMER_CompareSet(LETIMER0, COMP1, comp1_count);
  while ((LETIMER_IntGet(LETIMER0) & LETIMER_IEN_COMP1) == 0)
    ;                                            // Wait for COMP1 match.
  LETIMER_IntClear(LETIMER0, LETIMER_IEN_COMP1); // Clear COMP1 match interrupt.
}

/**
 * Implement a Interrupt based precise delay using LETIMER.
 * Calculates and sets a COMP1 value for the required delay
 * sets the COMP1 value and leaves the rest to State machine
 *
 * @param us_wait The delay duration in microseconds.
 */
void timerWaitUs_irq(uint32_t us_wait)
{
  uint32_t current_count;       // Variable to store the current counter value of LETIMER.
  uint32_t needed_count_for_us; // Variable to calculate the number of counts needed for the specified delay.
  uint32_t comp1_count;         // Variable to store the calculated COMP1 value for the timer.

  // Check if the system is in the lowest energy mode specified.
  if (LOWEST_ENERGY_MODE == EM3_MODE)
  {
    // If in ULFRCO (Ultra Low Frequency RC Oscillator) mode, validate the delay is within the permissible range.
    if (us_wait <= MIN_DELAY_FOR_ULFRCO_US)
    {
      // Log an error if the delay is too short for ULFRCO mode and adjust to minimum allowed delay.
      LOG_ERROR("Delay is too less, out of range for ULFRCO mode.\n");
      us_wait = MIN_DELAY_FOR_ULFRCO_US;
    }
    else if (us_wait >= MAX_DELAY_FOR_ULFRCO)
    {
      // Log an error if the delay is too long for ULFRCO mode and adjust to maximum allowed delay.
      LOG_ERROR("Delay is too Large, out of range for ULFRCO mode.\n");
      us_wait = MAX_DELAY_FOR_ULFRCO;
    }

    // Retrieve the current LETIMER counter value.
    current_count = LETIMER_CounterGet(LETIMER0);
    // Calculate the needed count for the specified delay in microseconds.
    needed_count_for_us = (uint32_t)((float)((float)us_wait / ONE_SEC_TO_US) * FINAL_CLOCK);
    // Calculate COMP1 value, adjusting for counter wrap-around.
    comp1_count = (((current_count - needed_count_for_us) + LETIMER_ULFRCO_MAX_VALUE) % LETIMER_ULFRCO_MAX_VALUE);
  }
  else // For other energy modes, typically using LFXO (Low Frequency Crystal Oscillator).
  {
    // Validate the delay is within the permissible range for LFXO mode.
    if (us_wait <= MIN_DELAY_FOR_LFXO_US)
    {
      // Log an error if the delay is too short for LFXO mode and adjust to minimum allowed delay.
      LOG_ERROR("Delay is too less, out of range for LFXO mode.\n");
      us_wait = MIN_DELAY_FOR_LFXO_US;
    }
    else if (us_wait >= MAX_DELAY_FOR_LFXO)
    {
      // Log an error if the delay is too long for LFXO mode and adjust to maximum allowed delay.
      LOG_ERROR("Delay is too Large, out of range for LFXO mode.\n");
      us_wait = MAX_DELAY_FOR_LFXO;
    }

    // Retrieve the current LETIMER counter value.
    current_count = LETIMER_CounterGet(LETIMER0);
    // Calculate the needed count for the specified delay in microseconds.
    needed_count_for_us = (uint32_t)((float)((float)us_wait / ONE_SEC_TO_US) * FINAL_CLOCK);
    // Calculate COMP1 value, adjusting for counter wrap-around in LFXO mode.
    comp1_count = (((current_count - needed_count_for_us) + LETIMER_LFXO_MAX_VALUE) % LETIMER_LFXO_MAX_VALUE);
  }

  // Clear any pending COMP1 interrupts.
  LETIMER_IntClear(LETIMER0, (LETIMER_IEN_COMP1));
  // Enable COMP1 interrupts for LETIMER.
  LETIMER_IntEnable(LETIMER0, (LETIMER_IEN_COMP1));

  // Set the COMP1 register with the calculated comp1_count to trigger an interrupt after the specified delay.
  LETIMER_CompareSet(LETIMER0, COMP1, comp1_count);
}
