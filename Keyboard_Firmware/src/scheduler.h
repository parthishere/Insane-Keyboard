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

#define NUMBER_OF_EVENTS 4 // Defines the total number of events managed by the scheduler

/* Enumerated type for events */
typedef enum
{
  evtLETIMER0_UF = 0x01,    // Event for LETIMER0 underflow, indicating a timer has elapsed its period.
  evtLETIMER0_COMP1,        // Event for LETIMER0 compare match 1, used for timing or periodic operations.
  evtI2CTransferComplete,   // Indicates completion of an I2C transfer operation.
  evtBTN0,                  // Represents an event triggered by pressing button 0.
  evtBTN1,                  // Represents an event triggered by pressing button 1.
  evtNOEVT                  // Indicates no event is pending, used for idle or default state handling.
} event_t;

/* Enumerated type for states */
typedef enum
{
  stateIdle_Timer_Wait,       // Initial state, involves waiting for a timer event or sensor enabling.
  stateI2C_State1_WriteInit,  // State for initiating a write transfer over I2C.
  stateI2C_State2_Check,      // State for checking the result of an I2C transfer operation.
  stateI2C_State3_Measurment, // State for measuring readings, typically after successful I2C communication.
  stateI2C_State4_Report,     // Final state for reporting or printing the measurements obtained.
} state_t;


typedef enum
{
  stateInitialState,                      // Initial state before discovery process starts.
  stateDiscoveringHTMService,             // State during discovery of the Health Thermometer Service.
  stateDiscoveringButtonService,          // State during discovery of a custom Button Service.
  stateDiscoveringHTMCharacteristic,      // State during discovery of characteristics under HTM Service.
  stateDiscoveringButtonCharacteristic,   // State during discovery of characteristics under Button Service.
  stateEnablingHTMIndication,             // State for enabling indications for HTM characteristic.
  stateEnablingBTNIndication,             // State for enabling indications for Button characteristic.
  stateEndState,                          // Final state indicating the end of the discovery process.
} discovery_state_t;


/* Structure to hold the state of each event */
typedef struct
{
  uint32_t LETIMER0_UF;    // Flag for LETIMER0 underflow event, set when the event occurs.
  uint32_t LETIMER0_COMP1; // Flag for LETIMER0 compare match 1 event, set when the event occurs.
  uint32_t I2C_TRANSFER_COMPLETE; // Flag indicating an I2C transfer has completed.
} event_struct_t;


/**
 * @brief Sets the LETIMER0 underflow event in the scheduler.
 *
 * This function marks the LETIMER0 underflow event as pending in the scheduler's event structure.
 * It uses critical sections to ensure that the operation is atomic and safe from concurrent access issues.
 */
void schedulerSetEventUF();


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

/**
 * @brief Retrieves the next pending event from the scheduler.
 *
 * This function checks the scheduler's event structure for any pending events,
 * prioritizing them in the order of LETIMER0 underflow, LETIMER0 COMP1, and then I2C.
 * It ensures atomic access to the event structure and clears the event flag before returning.
 *
 * @return event_t The next event to be processed, or evtNOEVT if no events are pending.
 */
event_t getNextEvent();

/**
 * @brief Manages state transitions for the SI7021 sensor based on events.
 *
 * This function implements a state machine for handling various events related
 * to the SI7021 temperature and humidity sensor operation.
 * The state machine transitions through different states such as idle, initiating I2C write, checking I2C transfer completion,
 * performing measurement, and reporting the measurement results.
 * The transitions occur in response to specific events like LETIMER0 underflow,
 * LETIMER0 COMP1 compare, and I2C transfer completion. It utilizes low energy timers for efficient power management and operates
 * within different energy modes to conserve energy. The function orchestrates the sequence of powering on the sensor, initiating
 * and checking I2C operations, and processing the sensor data, all while managing the system's power state.
 *
 * @param event sl_bt_msg_t The current event of Bluetooth triggering the state machine transition. extract external signal from the bluetooth event and use that external event to run the state machine
 */
void state_machine_si7021(sl_bt_msg_t *bt_event);

/**
 * @brief Manages the discovery process state machine for BLE services and characteristics.
 *
 * This function progresses through a series of states to discover BLE services and
 * characteristics, and to enable indications for discovered characteristics. The state
 * machine starts in the initial state and moves through discovering services,
 * discovering characteristics, enabling indications, and ends when the process is complete.
 * The transition between states is triggered by BLE events indicating the completion of each
 * discovery step or a change in connection status.
 *
 * @param bt_event Pointer to the BLE event structure received from the BLE stack.
 *                 This structure contains the event information that determines state transitions.
 */
void discovery_State_Machine(sl_bt_msg_t *bt_event);

#endif // !__SCHEDULAR_H__
