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
#include "app.h"
#include "em_core.h"   // Core system and energy management functions
#include "sl_bt_api.h" // Silicon Labs Bluetooth API for BLE operations
#include "gatt_db.h"   // GATT database for BLE services and characteristics
#include "math.h"
#include "app_assert.h"
#include "stdbool.h"

#include "src/ble_utility.h"


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
