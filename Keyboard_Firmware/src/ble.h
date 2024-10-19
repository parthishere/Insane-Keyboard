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

// This is the number of entries in the queue. Please leave
// this value set to 16.
#define QUEUE_DEPTH (16)
// Student edit:
//   define this to 1 if your design uses all array entries
//   define this to 0 if your design leaves 1 array entry empty
#define USE_ALL_ENTRIES (1)

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

typedef struct
{

    uint16_t charHandle;               // GATT DB handle from gatt_db.h
    uint32_t bufLength;                // Number of bytes written to field buffer[5]
    uint8_t buffer[MAX_BUFFER_LENGTH]; // The actual data buffer for the indication,
                                       //   need 5-bytes for HTM and 1-byte for button_state.
                                       //   For testing, test lengths 1 through 5,
                                       //   a length of 0 shall be considered an
                                       //   error, as well as lengths > 5
} queue_struct_t;

// Macros for packing single-byte and multi-byte data into a bitstream.
#define UINT8_TO_BITSTREAM(p, n) \
    {                            \
        *(p)++ = (uint8_t)(n);   \
    }
#define UINT32_TO_BITSTREAM(p, n)      \
    {                                  \
        *(p)++ = (uint8_t)(n);         \
        *(p)++ = (uint8_t)((n) >> 8);  \
        *(p)++ = (uint8_t)((n) >> 16); \
        *(p)++ = (uint8_t)((n) >> 24); \
    }
// Macro for converting a 32-bit unsigned integer to a floating-point format.
#define INT32_TO_FLOAT(m, e) ((int32_t)(((uint32_t)m) & 0x00FFFFFFU) | (((uint32_t)e) << 24))




#define THERMOMETER_SERVICE_UUID \
    {                            \
        0x09, 0x18               \
    }
#define THERMOMETER_CHARACTERISTIC_UUID \
    {                                   \
        0x1c, 0x2a                      \
    }


#define BUTTON_SERVICE_UUID { 0x89, 0x62, 0x13, 0x2d, 0x2a, 0x65, 0xec, 0x87, 0x3e, 0x43, 0xc8, 0x38, 0x01, 0x00, 0x00, 0x00, }
#define BUTTON_CHARACTERISTIC_UUID {0x89, 0x62, 0x13, 0x2d, 0x2a, 0x65, 0xec, 0x87, 0x3e, 0x43, 0xc8, 0x38, 0x02, 0x00, 0x00, 0x00, }

// Structure definition for BLE data management.
// This structure includes both common and server-specific BLE attributes.
typedef struct
{
    bd_addr myAddress;     // Device's Bluetooth address, unique identifier for BLE devices.
    uint8_t myAddressType; // Type of Bluetooth address being used (public or random).

    // Server-specific attributes for managing connections and service characteristics.
    uint8_t advertisingSetHandle; // Handle identifying the advertising set used for BLE advertisement.
    uint8_t appConnectionHandle;  // Handle for managing the current active connection with a client.
    uint32_t thermometerHandle; // Service handle for the thermometer service.
    uint16_t thermometerCharacteristicHandle; // Characteristic handle for thermometer measurement.
    uint32_t buttonServiceHandle; // Service handle for the custom button service.
    uint32_t buttonCharacteristicHandle; // Characteristic handle for button state.
    // uint8_t buttonState;                // Current state of button PB0 (pressed or released).
    bool connection_open;               // True if there is an active BLE connection.
    bool bonded;                        // True if the device has successfully bonded with a client.
    bool bonding;                       // True if the device is currently in the process of bonding.
    bool ok_to_send_report_notification; // True if it's permissible to send button notificaiton.
    bool indication_in_flight;          // True if an indication is currently being sent.
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

/**
 * @brief Sends a temperature measurement indication over Bluetooth Low Energy (BLE) using GATT (Generic Attribute Profile).
 *
 * This function writes a temperature value to a local GATT database and then sends an indication to a connected BLE device
 * if there is not already an indication in flight. The temperature value is displayed on a connected display and sent
 * over BLE in IEEE-11073 format. If any operation fails, an error is logged.
 *
 * @param htm_temperature_buffer Array of uint8_t that contains the temperature data in IEEE-11073 format to be written
 *                               to the GATT database and sent as an indication.
 * @param size The size of the `htm_temperature_buffer` array, indicating how many bytes of temperature data are to be sent.
 *             This should match the length of the temperature data in IEEE-11073 format.
 *
 * @return void This function does not return a value. It performs operations of writing to a GATT database and sending BLE
 *              indications. If any operation fails, errors are logged but not returned.
 *
 * @note This function checks if an indication is currently being sent (`indication_in_flight`). If so, it does not attempt
 *       to send another indication. This is to prevent sending multiple indications at the same time.
 * @note The function uses `sl_bt_gatt_server_write_attribute_value` to write the temperature value to the GATT database and
 *       `sl_bt_gatt_server_send_indication` to send the indication over BLE. The success of these operations is checked,
 *       and errors are logged accordingly.
 * @note The macro `LOG_ERROR` is used to log errors. It must be defined elsewhere in your codebase.
 * @note This function assumes that `ble_data.indication_in_flight`, `ble_data.appConnectionHandle`, and `gattdb_temperature_measurement`
 *       are properly defined and available in your application.
 */
void send_HTM_Indication(uint8_t htm_temperature_buffer[], uint8_t size);



/**
 * @brief Sends a button state indication over Bluetooth Low Energy (BLE) using GATT (Generic Attribute Profile).
 *
 * This function sends a single byte representing the state of a button to a connected BLE device
 * as an indication. The button state is sent over BLE using the specified GATT characteristic. If the operation
 * succeeds, a log message is produced, and the indication is marked as in-flight. If the operation fails,
 * an error with the status code is logged.
 *
 * @param buffer Array of uint8_t that contains the single byte of button state data to be sent as an indication.
 *               The button state is represented by this single byte (e.g., 0x00 for released, 0x01 for pressed).
 *
 * @return void This function does not return a value. It logs either the success or failure of sending the
 *              button state indication. On success, it also marks an indication as in-flight to prevent
 *              sending multiple indications simultaneously.
 */
void send_Button_Indication(uint8_t buffer[]);



/*
 * ---------------------------------------------------------------------
 * This function resets the queue.
 * @param
 *      none
 * @return
 *     none
 * ---------------------------------------------------------------------
 */
void reset_queue(void);

/* ---------------------------------------------------------------------
 * This function writes an entry to the queue if the the queue is not full.
 * Input parameter "charHandle" should be written to queue_struct_t element "charHandle".
 * Input parameter "bufLength" should be written to queue_struct_t element "bufLength"
 * The bytes pointed at by input parameter "buffer" should be written to queue_struct_t element "buffer"
 * Returns bool false if successful or true if writing to a full fifo.
 * i.e. false means no error, true means an error occurred.
 * @param :
 *      uint16_t charHandle: charHandle for GattDB
 *      uint32_t bufLength: Bufferlength for buffer which should be greater than or =1 and less than or =5
 *      uint8_t *buffer: buffer to store ,need 5-bytes for HTM and 1-byte for button_state.
 * @return :
 *     bool:
 * ---------------------------------------------------------------------
 */
bool write_queue(uint16_t charHandle, uint32_t bufLength, uint8_t *buffer);

/* ---------------------------------------------------------------------
 * Public function.
 * This function reads an entry from the queue, and returns values to the
 * caller. The values from the queue entry are returned by writing
 * the values to variables declared by the caller, where the caller is passing
 * in pointers to charHandle, bufLength and buffer. The caller's code will look like this:
 *
 *   uint16_t     charHandle;
 *   uint32_t     bufLength;
 *   uint8_t      buffer[5];
 *
 *   status = read_queue (&charHandle, &bufLength, &buffer[0]);
 *
 * *** If the code above doesn't make sense to you, you probably lack the
 * necessary prerequisite knowledge to be successful in this course.
 *
 * Write the values of charHandle, bufLength, and buffer from my_queue[rptr] to
 * the memory addresses pointed at by charHandle, bufLength and buffer, like this :
 *      *charHandle = <something>;
 *      *bufLength  = <something_else>;
 *      *buffer     = <something_else_again>; // perhaps memcpy() would be useful?
 *
 * In this implementation, we do it this way because
 * standard C does not provide a mechanism for a C function to return multiple
 * values, as is common in perl or python.
 * Returns bool false if successful or true if reading from an empty fifo.
 * i.e. false means no error, true means an error occurred.
 * ---------------------------------------------------------------------
 */
bool read_queue(uint16_t *charHandle, uint32_t *bufLength, uint8_t *buffer);

/* ---------------------------------------------------------------------
 * This function returns the wptr, rptr, full and empty values, writing
 * to memory using the pointer values passed in, same rationale as read_queue()
 * The "_" characters are used to disambiguate the global variable names from
 * the input parameter names, such that there is no room for the compiler to make a
 * mistake in interpreting your intentions.
 * ---------------------------------------------------------------------
 */
void get_queue_status(uint32_t *wptr, uint32_t *rptr, bool *full, bool *empty);

/* ---------------------------------------------------------------------
 * Function that computes the number of written entries currently in the queue. If there
 * are 3 entries in the queue, it should return 3. If the queue is empty it should
 * return 0. If the queue is full it should return either QUEUE_DEPTH if
 * USE_ALL_ENTRIES==1 otherwise returns QUEUE_DEPTH-1.
 * ---------------------------------------------------------------------
 */
uint32_t get_queue_depth(void);

#endif // End of include guard __BLE_H__
