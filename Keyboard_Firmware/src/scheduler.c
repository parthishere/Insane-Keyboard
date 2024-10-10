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

// Structure to hold current event states,  we wont use it in this assignment
static event_struct_t current_events_data = {
    .LETIMER0_UF = 0,          // LETIMER0 underflow event flag
    .LETIMER0_COMP1 = 0,       // LETIMER0 compare match 1 event flag
    .I2C_TRANSFER_COMPLETE = 0 // I2C communication event flag
};

// global variable for current state
static state_t current_state = stateIdle_Timer_Wait;

static discovery_state_t current_discovery_state = stateInitialState;

/**
 * @brief Sets the LETIMER0 underflow event in the scheduler.
 *
 * This function marks the LETIMER0 underflow event as pending in the scheduler's event structure.
 * It uses critical sections to ensure that the operation is atomic and safe from concurrent access issues.
 * Sends Signal to Bluetooth stack call back function with external signal
 */
void schedulerSetEventUF()
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
 * @brief Sets the I2C communication event in the scheduler.
 *
 * Similar to schedulerSetEventUF, this function marks the I2C event as pending.
 * It ensures atomic access to the event structure using critical sections.
 * Sends Signal to Bluetooth stack call back function with external signal
 */
void schedularSetEventI2C()
{
  CORE_DECLARE_IRQ_STATE;
  // enter critical section
  CORE_ENTER_CRITICAL(); // Enter a critical section to prevent interruption during flag handling.

  // Send external Event Signal to state machine
  sl_bt_external_signal(evtI2CTransferComplete);

  // exit critical section
  CORE_EXIT_CRITICAL(); // Exit the critical section, allowing other interrupts to be processed.
}

/**
 * @brief Sets the LETIMER0 COMP1 event in the scheduler.
 *
 * Marks the LETIMER0 compare match 1 event as pending, using critical sections to protect the operation.
 * Sends Signal to Bluetooth stack call back function with external signal
 */
void schedularSetEventCOMP1()
{
  CORE_DECLARE_IRQ_STATE;
  // enter critical section
  CORE_ENTER_CRITICAL(); // Enter a critical section to prevent interruption during flag handling.

  // Send external Event Signal to state machine
  sl_bt_external_signal(evtLETIMER0_COMP1);

  // exit critical section
  CORE_EXIT_CRITICAL(); // Exit the critical section, allowing other interrupts to be processed.
}

/**
 * Sends an external event signal corresponding to button 0 (PB0) to the state machine.
 * This function is designed to be called within an interrupt service routine or another part
 * of the application where button 0's press event needs to be communicated to the system's
 * state machine for handling. It enters a critical section to ensure the atomicity of the
 * operation, preventing any concurrent access or interruption that could potentially lead to
 * race conditions or incorrect system behavior.
 */
void schedularSetEventPB0()
{
  CORE_DECLARE_IRQ_STATE;
  // enter critical section
  CORE_ENTER_CRITICAL(); // Enter a critical section to prevent interruption during flag handling.

  // Send external Event Signal to state machine
  sl_bt_external_signal(evtBTN0);

  // exit critical section
  CORE_EXIT_CRITICAL(); // Exit the critical section, allowing other interrupts to be processed.
}

/**
 * Sends an external event signal corresponding to button 1 (PB1) to the state machine.
 * Similar to `schedularSetEventPB0`, this function communicates a button 1 press event to
 * the system's state machine. It securely manages the operation within a critical section
 * to ensure that the signal sending is atomic, preventing disruptions that could affect the
 * system's response to the event. This mechanism is crucial in real-time and interrupt-driven
 * systems to maintain correct operation and state transitions.
 */
void schedularSetEventPB1()
{
  CORE_DECLARE_IRQ_STATE;
  // enter critical section
  CORE_ENTER_CRITICAL(); // Enter a critical section to prevent interruption during flag handling.

  // Send external Event Signal to state machine
  sl_bt_external_signal(evtBTN1);

  // exit critical section
  CORE_EXIT_CRITICAL(); // Exit the critical section, allowing other interrupts to be processed.
}

/**
 * @brief Retrieves the next pending event from the scheduler.
 *
 * This function checks the scheduler's event structure for any pending events,
 * prioritizing them in the order of LETIMER0 underflow, LETIMER0 COMP1, and then I2C.
 * It ensures atomic access to the event structure and clears the event flag before returning.
 *
 * @return event_t The next event to be processed, or evtNOEVT if no events are pending.
 */
event_t getNextEvent()
{
  CORE_DECLARE_IRQ_STATE; // Prepare to save current interrupt status.
  uint32_t theEvent;      // Variable to hold the event that will be returned.
  CORE_ENTER_CRITICAL();  // Protect the event checking and clearing process.

  // Priority: LETIMER0 underflow < LETIMER0 COMP1 < I2C
  if (current_events_data.LETIMER0_UF)
  {
    current_events_data.LETIMER0_UF = false; // Clear the underflow event.
    theEvent = evtLETIMER0_UF;               // Set to return the underflow event.
  }
  if (current_events_data.LETIMER0_COMP1)
  {
    current_events_data.LETIMER0_COMP1 = false; // Clear the COMP1 event.
    theEvent = evtLETIMER0_COMP1;               // Set to return the COMP1 event.
  }
  if (current_events_data.I2C_TRANSFER_COMPLETE)
  {
    current_events_data.I2C_TRANSFER_COMPLETE = false; // Clear the I2C event.
    theEvent = evtI2CTransferComplete;                 // Set to return the I2C event.
  }

  CORE_EXIT_CRITICAL(); // Restore interrupts, ending critical section.

  return (theEvent); // Return the determined event.
} // getNextEvent()

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
void state_machine_si7021(sl_bt_msg_t *bt_event)
{
  ble_data_struct_t *ble_data_ptr = getBleDataPtr();

  // Check if the current Bluetooth event is an external signal event, and also verify that a connection is open
  // and it is appropriate to send Health Thermometer (HTM) indications based on client configuration.
  if (SL_BT_MSG_ID(bt_event->header) == sl_bt_evt_system_external_signal_id && ble_data_ptr->connection_open && ble_data_ptr->ok_to_send_htm_indications)
  {
    // Extract the external signals from the event data. External signals are user-defined signals
    uint32_t ext_signals = bt_event->data.evt_system_external_signal.extsignals;
    // Switch statement to handle the logic based on the current state of the state machine.
    switch (current_state)
    {
    // State for idling and waiting for a timer event.
    case (stateIdle_Timer_Wait):
      // Check if the event is a LETIMER0 underflow event.
      if ((ext_signals - evtLETIMER0_UF) == 0x00)
      {
        // Power on the SI7021 sensor, call timerWaitMs_irq to wait for a specific time, then go to sleep.
        read_SI7021_timer_wait();
        // Transition to the next state to initiate I2C write.
        current_state = stateI2C_State1_WriteInit;
      }
      break;

    // State for initiating I2C write to SI7021.
    case (stateI2C_State1_WriteInit):
      // Check if the event is a LETIMER0 COMP1 compare event.
      if ((ext_signals - evtLETIMER0_COMP1) == 0x00)
      {
        // Disable LETIMER COMP1 interrupt, start I2C write operation, add energy requirement to stay in EM1 mode.
        LETIMER_IntDisable(LETIMER0, LETIMER_IEN_COMP1);
        read_SI7021_write_initiate();
        sl_power_manager_add_em_requirement(EM1_MODE);

        // Transition to the next state to check the completion of I2C transfer.
        current_state = stateI2C_State2_Check;
      }
      break;

    // State for checking the I2C transfer completion.
    case (stateI2C_State2_Check):
      // Check if the event is an I2C transfer completion.
      if ((ext_signals - evtI2CTransferComplete) == 0x00)
      {
        // Remove energy requirement for EM1 mode, disable I2C interrupt, and setup timer for next operation.
        sl_power_manager_remove_em_requirement(EM1_MODE);
        NVIC_DisableIRQ(I2C0_IRQn);
        timerWaitUs_irq(TRANSFER_DELAY);

        // Transition to the next state to perform measurement.
        current_state = stateI2C_State3_Measurment;
      }
      break;

    // State for performing the measurement with SI7021.
    case (stateI2C_State3_Measurment):
      // Check if the event is a LETIMER0 COMP1 compare event.
      if ((ext_signals - evtLETIMER0_COMP1) == 0x00)
      {
        // Disable LETIMER COMP1 interrupt, perform measurement, add energy requirement to stay in EM1 mode.
        LETIMER_IntDisable(LETIMER0, LETIMER_IEN_COMP1);
        read_SI7021_MEASUREMENT();
        sl_power_manager_add_em_requirement(EM1_MODE);

        // Transition to the next state to report the measurement results.
        current_state = stateI2C_State4_Report;
      }
      break;

    // State for reporting the measurement results.
    case (stateI2C_State4_Report):
      // Check if the event is an I2C transfer completion.
      if ((ext_signals - evtI2CTransferComplete) == 0x00)
      {
        // Remove energy requirement for EM1 mode, disable I2C interrupt, and process the measurement results.
        sl_power_manager_remove_em_requirement(EM1_MODE);
        NVIC_DisableIRQ(I2C0_IRQn);
        read_SI7021();

        // Transition back to the initial state to wait for the next timer event.
        current_state = stateIdle_Timer_Wait;
      }
      break;

    // Default case to handle any unspecified states.
    default:
      break;
    }
  }
}

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
void discovery_State_Machine(sl_bt_msg_t *bt_event)
{
  // Retrieve pointer to the global BLE data structure
  ble_data_struct_t *ble_data_ptr = getBleDataPtr();

  // Status code variable for storing the result of Silicon Labs API function calls
  sl_status_t sc;

  // Switch statement to handle different states of the discovery process
  switch (current_discovery_state)
  {
  // Initial state: Awaiting a connection to be opened
  case stateInitialState:
    // Check if the received event is a connection opened event
    if (SL_BT_MSG_ID(bt_event->header) == sl_bt_evt_connection_opened_id)
    {
      // Transition to the service discovery state
      current_discovery_state = stateDiscoveringHTMService;
      PRINT_LOG("Finding Services : from state machine\n\r");

      uint8_t thermometer_service_uuid[2] = THERMOMETER_SERVICE_UUID;

      // Initiate discovery of primary services based on uuid on the connected device
      sc = sl_bt_gatt_discover_primary_services_by_uuid(ble_data_ptr->appConnectionHandle,
                                                        sizeof(thermometer_service_uuid),
                                                        thermometer_service_uuid);

      // Error handling if the discovery could not be started
      if (sc != SL_STATUS_OK)
      {
        LOG_ERROR("htm sl_bt_gatt_discover_primary_services_by_uuid() returned != 0 status=0x%04x", (unsigned int)sc);
      }
    }
    break;

  // State for discovering services
  case stateDiscoveringHTMService:
    // Check if the discovery process is completed
    if (SL_BT_MSG_ID(bt_event->header) == sl_bt_evt_gatt_procedure_completed_id)
    {
      // Transition to the characteristic discovery state
      current_discovery_state = stateDiscoveringButtonService;
      PRINT_LOG("Finding HTM service : from state machine\n\r");

      // Define the UUID for the button service to discover
      uint8_t button_service_uuid[16] = BUTTON_SERVICE_UUID;

      // Initiate discovery of service by UUID
      sc = sl_bt_gatt_discover_primary_services_by_uuid(ble_data_ptr->appConnectionHandle,
                                                        sizeof(button_service_uuid),
                                                        button_service_uuid);

      // Error handling if the characteristic discovery could not be started
      if (sc != SL_STATUS_OK)
      {
        LOG_ERROR("button sl_bt_gatt_discover_primary_services_by_uuid() returned != 0 status=0x%04x", (unsigned int)sc);
      }
    }
    break;

  // State for discovering services
  case stateDiscoveringButtonService:
    // Check if the discovery process is completed
    if (SL_BT_MSG_ID(bt_event->header) == sl_bt_evt_gatt_procedure_completed_id)
    {
      // Transition to the characteristic discovery state
      current_discovery_state = stateDiscoveringHTMCharacteristic;
      PRINT_LOG("Finding HTM characteristic : from state machine\n\r");

      // Define the UUID for the thermometer characteristic to discover
      uint8_t thermometer_characteristic_uuid[2] = THERMOMETER_CHARACTERISTIC_UUID;

      // Initiate discovery of characteristics by UUID
      sc = sl_bt_gatt_discover_characteristics_by_uuid(
          bt_event->data.evt_gatt_procedure_completed.connection,
          ble_data_ptr->thermometerHandle,
          sizeof(thermometer_characteristic_uuid),
          (const uint8_t *)thermometer_characteristic_uuid);

      // Error handling if the characteristic discovery could not be started
      if (sc != SL_STATUS_OK)
      {
        LOG_ERROR("HTM sl_bt_gatt_discover_characteristics_by_uuid() returned != 0 status=0x%04x", (unsigned int)sc);
      }
    }
    break;

  // State for discovering characteristics
  case stateDiscoveringHTMCharacteristic:
    // Check if the characteristic discovery process is completed
    if (SL_BT_MSG_ID(bt_event->header) == sl_bt_evt_gatt_procedure_completed_id)
    {
      // Transition to the indication enabling state
      current_discovery_state = stateDiscoveringButtonCharacteristic;
      PRINT_LOG("Finding Button characteristic : from state machine\n\r");

      // Define the UUID for the thermometer characteristic to discover
      uint8_t button_characteristic_uuid[16] = BUTTON_CHARACTERISTIC_UUID;

      // Initiate discovery of characteristics by UUID
      sc = sl_bt_gatt_discover_characteristics_by_uuid(
          bt_event->data.evt_gatt_procedure_completed.connection,
          ble_data_ptr->buttonServiceHandle,
          sizeof(button_characteristic_uuid),
          (const uint8_t *)button_characteristic_uuid);

      // Error handling if enabling indications failed
      if (sc != SL_STATUS_OK)
      {
        // SL_STATUS_IN_PROGRESS ((sl_status_t)0x0005): Operation is in progress and not yet complete (pass or fail).
        LOG_ERROR("button sl_bt_gatt_discover_characteristics_by_uuid() returned != 0 status=0x%04x", (unsigned int)sc);
      }
    }
    break;

  // State for discovering characteristics
  case stateDiscoveringButtonCharacteristic:
    // Check if the characteristic discovery process is completed
    if (SL_BT_MSG_ID(bt_event->header) == sl_bt_evt_gatt_procedure_completed_id)
    {
      /// Transition to the final state of the discovery process
      
      current_discovery_state = stateEnablingHTMIndication;
      

      sc = sl_bt_gatt_set_characteristic_notification(
          bt_event->data.evt_gatt_procedure_completed.connection,
          ble_data_ptr->thermometerCharacteristicHandle,
          sl_bt_gatt_indication);

      // Error handling if enabling indications failed
      if (sc != SL_STATUS_OK)
      {
        // SL_STATUS_IN_PROGRESS ((sl_status_t)0x0005): Operation is in progress and not yet complete (pass or fail).
        LOG_ERROR("HTM sl_bt_gatt_set_characteristic_notification() returned != 0 status=0x%04x", (unsigned int)sc);
      }
    }
    break;

  // State for enabling indications
  case stateEnablingHTMIndication:
    // Check if the indication enabling process is completed
    if (SL_BT_MSG_ID(bt_event->header) == sl_bt_evt_gatt_procedure_completed_id)
    {

      // Transition to the final state of the discovery process
      PRINT_LOG("HTM Indication Enabled : from state machine\n\r");
      current_discovery_state = stateEnablingBTNIndication;
      ble_data_ptr->ok_to_send_htm_indications = true;
      
      sc = sl_bt_gatt_set_characteristic_notification(
          bt_event->data.evt_gatt_procedure_completed.connection,
          ble_data_ptr->buttonCharacteristicHandle,
          sl_bt_gatt_indication);

      // Error handling if enabling indications failed
      if (sc != SL_STATUS_OK)
      {
        // SL_STATUS_IN_PROGRESS ((sl_status_t)0x0005): Operation is in progress and not yet complete (pass or fail).
        LOG_ERROR("BTN sl_bt_gatt_set_characteristic_notification() returned != 0 status=0x%04x", (unsigned int)sc);
      }

      
    }
    break;

  // State for enabling indications
  case stateEnablingBTNIndication:
    // Check if the indication enabling process is completed
    if (SL_BT_MSG_ID(bt_event->header) == sl_bt_evt_gatt_procedure_completed_id)
    {
      PRINT_LOG("BTN Indication Enabled : from state machine\n\r");
      ble_data_ptr->ok_to_send_button_indications = true;
      current_discovery_state = stateEndState;
    }

    break;

  // Final state: Awaiting connection closure to reset to the initial state
  case stateEndState:
    // Check if the connection has been closed
    if (SL_BT_MSG_ID(bt_event->header) == sl_bt_evt_connection_closed_id)
    {
      PRINT_LOG("End State : from state machine\n\r");
      // Reset to the initial state to be ready for a new discovery process
      current_discovery_state = stateInitialState;
    }
    break;
  }
}
