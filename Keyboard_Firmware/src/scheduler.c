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
 * @file    schedular.c
 * @brief   Implementation of a simple event-driven scheduler for embedded systems.
 *          This scheduler manages events related to LETIMER0 underflow, LETIMER0 COMP1,
 *          and I2C communication. It provides functions to set these events and retrieve
 *          the next event to be processed, ensuring thread-safe operations.
 *
 *          Sends event signal to bluetooth event callback function
 *
 * @author  Parth Thakkar
 * @date    15th Feb 2024
 */

#include "scheduler.h" // Include the scheduler's header file

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"

#define NOT_SET 0 // Define a constant for unset events

// Timing delays for sensor communication
#define INITIAL_DELAY 80000  // Initial delay in microseconds before reading temperature
#define TRANSFER_DELAY 10800 // Delay in microseconds after initiating the temperature read command



/**
 * @brief Sets the LETIMER0 underflow event in the scheduler.
 *
 * This function marks the LETIMER0 underflow event as pending in the scheduler's event structure.
 * It uses critical sections to ensure that the operation is atomic and safe from concurrent access issues.
 * Sends Signal to Bluetooth stack call back function with external signal
 */
inline void schedulerSetEventUF()
{
  CORE_DECLARE_IRQ_STATE;
  // enter critical section
  CORE_ENTER_CRITICAL(); // Enter a critical section to prevent interruption during flag handling.

  // Send external Event Signal to state machine
  sl_bt_external_signal(evtLETIMER0_UF);

  // exit critical section
  CORE_EXIT_CRITICAL(); // Exit the critical section, allowing other interrupts to be processed.
} // schedulerSetEventXXX()



/**
 * @brief Sets the LETIMER0 COMP1 event in the scheduler.
 *
 * Marks the LETIMER0 compare match 1 event as pending, using critical sections to protect the operation.
 * Sends Signal to Bluetooth stack call back function with external signal
 */
inline void schedularSetEventCOMP1()
{
  CORE_DECLARE_IRQ_STATE;
  // enter critical section
  CORE_ENTER_CRITICAL(); // Enter a critical section to prevent interruption during flag handling.

  // Send external Event Signal to state machine
  sl_bt_external_signal(evtLETIMER0_COMP1);

  // exit critical section
  CORE_EXIT_CRITICAL(); // Exit the critical section, allowing other interrupts to be processed.
}



inline void schedulerSetEventIOEXPANDER_COL(){
  CORE_DECLARE_IRQ_STATE;
  // enter critical section
  CORE_ENTER_CRITICAL(); // Enter a critical section to prevent interruption during flag handling.

  // Send external Event Signal to state machine
  sl_bt_external_signal(evtIOEXPANDER_COL);

  // exit critical section
  CORE_EXIT_CRITICAL(); // Exit the critical section, allowing other interrupts to be processed.
}

inline void schedulerSetEventIOEXPANDER_ROW(){
  CORE_DECLARE_IRQ_STATE;
  // enter critical section
  CORE_ENTER_CRITICAL(); // Enter a critical section to prevent interruption during flag handling.

  // Send external Event Signal to state machine
  sl_bt_external_signal(evtIOEXPANDER_ROW);

  // exit critical section
  CORE_EXIT_CRITICAL(); // Exit the critical section, allowing other interrupts to be processed.
}

inline void schedulerSetEventENCODER_SW(){
  CORE_DECLARE_IRQ_STATE;
  // enter critical section
  CORE_ENTER_CRITICAL(); // Enter a critical section to prevent interruption during flag handling.

  // Send external Event Signal to state machine
  sl_bt_external_signal(evtENCODER_SW);

  // exit critical section
  CORE_EXIT_CRITICAL(); // Exit the critical section, allowing other interrupts to be processed.
}

inline void schedulerSetEventENCODER_ROTATE(){
  CORE_DECLARE_IRQ_STATE;
  // enter critical section
  CORE_ENTER_CRITICAL(); // Enter a critical section to prevent interruption during flag handling.

  // Send external Event Signal to state machine
  sl_bt_external_signal(evtENCODER_ROTATE);

  // exit critical section
  CORE_EXIT_CRITICAL(); // Exit the critical section, allowing other interrupts to be processed.
}

