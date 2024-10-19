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
 * @file    ble.h
 * @brief
 *
 * @author  Parth Thakkar
 * @date    15th Feb 2024
 */

// Include guard to prevent double inclusion of this header file
#ifndef __BLE_H__
#define __BLE_H__

// Including necessary headers for BLE functionality
#include "em_core.h"   // Core system and energy management functions
#include "sl_bt_api.h" // Silicon Labs Bluetooth API for BLE operations
#include "gatt_db.h"   // GATT database for BLE services and characteristics
#include "ble_device_type.h"
#include "math.h"
#include "app_assert.h"

#define MAX_CONNECTIONS_AND_BONDING 3
// Modern C (circa 2021 does it this way)
// This is referred to as an anonymous struct definition.
//
// This is the structure of 1 queue/buffer/FIFO entry.
// When you write an entry to the queue, you write 3
// values to the queue entry, 1 value for each field (element) of the struct.
// The rationale for declaring 1 queue entry in this
// manner will become clear later in Assignment 8.
//
// *** Please do not change this definition!
// *** The autograder (i.e. the testbench) uses this struct definition!
// *** Changing this struct definiton will cause the autograder to fail.

#define MAX_BUFFER_LENGTH (5)
#define MIN_BUFFER_LENGTH (1)

#define THERMOMETER_SERVICE_UUID \
    {                            \
        0x09, 0x18}
#define THERMOMETER_CHARACTERISTIC_UUID \
    {                                   \
        0x1c, 0x2a}

#define BUTTON_SERVICE_UUID { \
    0x89,                     \
    0x62,                     \
    0x13,                     \
    0x2d,                     \
    0x2a,                     \
    0x65,                     \
    0xec,                     \
    0x87,                     \
    0x3e,                     \
    0x43,                     \
    0xc8,                     \
    0x38,                     \
    0x01,                     \
    0x00,                     \
    0x00,                     \
    0x00,                     \
}
#define BUTTON_CHARACTERISTIC_UUID { \
    0x89,                            \
    0x62,                            \
    0x13,                            \
    0x2d,                            \
    0x2a,                            \
    0x65,                            \
    0xec,                            \
    0x87,                            \
    0x3e,                            \
    0x43,                            \
    0xc8,                            \
    0x38,                            \
    0x02,                            \
    0x00,                            \
    0x00,                            \
    0x00,                            \
}

typedef struct
{
    bd_addr device_address;
    uint8_t address_type;

    uint8_t connectionHandle;

    uint32_t reportMapHandle;               // Service handle for the thermometer service.
    uint32_t reportMapCharacteristicHandle; // Characteristic handle for thermometer measurement.

    bool ok_to_send_report_notification;
    bool connection_open; // True if there is an active BLE connection.
    bool bonded;          // True if the device has successfully bonded with a client.
    bool bonding;         // True if the device is currently in the process of bonding.

} connections_t;

typedef struct{
    uint32_t DataSendServiceHandle;        // Service handle for the custom button service.
    uint32_t DataSendCharacteristicHandle; // Characteristic handle for button state.

    uint32_t timerServiceHandle;        // Service handle for the custom button service.
    uint32_t timerCharacteristicHandle; // Characteristic handle for button state.
                                        // uint8_t buttonState;                // Current state of button PB0 (pressed or released).

    bool ok_to_send_timer_notification;
    bool ok_to_send_data_notification;
}second_unit_t;

// Structure definition for BLE data management.
// This structure includes both common and server-specific BLE attributes.
typedef struct
{
    int current_connetion;

    bd_addr myAddress;     // Device's Bluetooth address, unique identifier for BLE devices.
    uint8_t myAddressType; // Type of Bluetooth address being used (public or random).

    uint8_t advertisingSetHandle;

    connections_t connections;
    second_unit_t second_unit;


    bool indication_in_flight; // True if an indication is currently being sent.
} ble_data_struct_t;

/**
 * @brief Handles incoming BLE events and dispatches actions based on the event type.
 *
 * This function is a central event handler for BLE events. It switches between different
 * BLE event IDs and executes corresponding actions, such as setting up the device on boot,
 * handling new connections, and managing connection parameters.
 *
 * @param evt Pointer to the BLE event structure.
 */
void handle_ble_event(sl_bt_msg_t *evt); // Handles incoming BLE events

/**
 * @brief Retrieves a pointer to the global BLE data structure.
 *
 * This function is used to access the global BLE data structure from other files or functions,
 * providing a mechanism to share BLE-related data across the application.
 *
 * @return ble_data_struct_t* Pointer to the global BLE data structure.
 */
ble_data_struct_t *getBleDataPtr(void); // Returns a pointer to the BLE data structure

#endif // End of include guard __BLE_H__
