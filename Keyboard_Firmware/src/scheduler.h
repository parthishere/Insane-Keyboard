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
 * @file    schedular.h
 * @brief   Header file for function implementation of Schedular and event indication
 *
 * @author  Parth Thakkar
 * @date    15th Feb 2024
 */

#ifndef __SCHEDULAR_H__
#define __SCHEDULAR_H__

#include "em_core.h" // Include for core EM library functionalities, likely for critical section support
#include "i2c.h"
#include "ble.h"

#define NUMBER_OF_EVENTS 8 // Defines the total number of events managed by the scheduler

/* Enumerated type for events */
typedef enum
{
  evtLETIMER0_UF = 0x01,    // Event for LETIMER0 underflow, indicating a timer has elapsed its period.
  evtLETIMER0_COMP1,        // Event for LETIMER0 compare match 1, used for timing or periodic operations.
  evtI2CTransferComplete,   // Indicates completion of an I2C transfer operation.
  evtIOEXPANDER_COL,
  evtIOEXPANDER_ROW,
  evtENCODER_SW,                  // Represents an event triggered by pressing button 0.
  evtENCODER_ROTATE,                  // Represents an event triggered by pressing button 1.
  evtNOEVT                  // Indicates no event is pending, used for idle or default state handling.
} event_t;



void schedulerSetEventUF();
/**
 * @brief Sets the LETIMER0 underflow event in the scheduler.
 *
 * This function marks the LETIMER0 underflow event as pending in the scheduler's event structure.
 * It uses critical sections to ensure that the operation is atomic and safe from concurrent access issues.
 */
void schedulerSetEventIOEXPANDER_COL();

void schedulerSetEventIOEXPANDER_ROW();
void schedulerSetEventENCODER_SW();
void schedulerSetEventENCODER_ROTATE();

/**
 * @brief Sets the LETIMER0 COMP1 event in the scheduler.
 *
 * Marks the LETIMER0 compare match 1 event as pending, using critical sections to protect the operation.
 */
void schedularSetEventCOMP1();


/**
 * @brief Sets the I2C communication event in the scheduler.
 *
 * Similar to schedulerSetEventUF, this function marks the I2C event as pending.
 * It ensures atomic access to the event structure using critical sections.
 */
void schedularSetEventI2C();


/**
 * Sends an external event signal corresponding to button 0 (PB0) to the state machine.
 * This function is designed to be called within an interrupt service routine or another part
 * of the application where button 0's press event needs to be communicated to the system's
 * state machine for handling. It enters a critical section to ensure the atomicity of the
 * operation, preventing any concurrent access or interruption that could potentially lead to
 * race conditions or incorrect system behavior.
 */
void schedularSetEventPB0();

/**
 * Sends an external event signal corresponding to button 1 (PB1) to the state machine.
 * Similar to `schedularSetEventPB0`, this function communicates a button 1 press event to
 * the system's state machine. It securely manages the operation within a critical section
 * to ensure that the signal sending is atomic, preventing disruptions that could affect the
 * system's response to the event. This mechanism is crucial in real-time and interrupt-driven
 * systems to maintain correct operation and state transitions.
 */
void schedularSetEventPB1();


#endif // !__SCHEDULAR_H__
