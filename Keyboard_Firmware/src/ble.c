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
 * @file    ble.c
 * @brief   Implements BLE event handling for efr32, focusing on initializing,
 *          managing connections, and processing BLE events for power and data management.
 *
 * @author  Parth Thakkar
 * @date    15th Feb 2024
 */

#include "ble.h"

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"

// System ID length for BLE devices, typically 8 bytes.
#define SYSTEM_ID_LEN 8

// Specific bytes within the System ID to indicate the Bluetooth SIG-defined format for public device addresses.
// These are constants used to fill the middle of the System ID byte array.
#define SYSTEM_ID3 0xFF
#define SYSTEM_ID4 0xFE

// Advertising interval for BLE in units of 0.625ms.
// ADV_INTERVAL of 400 translates to 250ms (400 * 0.625ms = 250ms).
#define ADV_INTERVAL 400

// Connection interval for BLE in units of 1.25ms.
// CON_INTERVAL of 60 translates to 75ms (60 * 1.25ms = 75ms).
#define CON_INTERVAL 60

// Connection latency for BLE.
// Defines the number of connection events the slave can skip.
// CON_LATENCY of 4 means the slave device can skip up to 4 connection intervals.
#define CON_LATENCY 4

// Supervision timeout for BLE in units of 10ms.
// CON_TIMEOUT of 400 translates to 4 seconds (76 * 10ms = 760ms > 750ms).
// #define CON_TIMEOUT ((1 + CON_LATENCY) * CON_INTERVAL * 2) = 750ms
#define CON_TIMEOUT 76

// Maximum length of the connection event in BLE.
// MAX_CE_LEN set to 0xFFFF indicates no specific maximum length,
// allowing for the longest possible connection events.
#define MAX_CE_LEN 4

// Some macros for system buffer
#define SYSTEM_ID_7 7
#define SYSTEM_ID_6 6
#define SYSTEM_ID_5 5
#define SYSTEM_ID_4 4
#define SYSTEM_ID_3 3
#define SYSTEM_ID_2 2
#define SYSTEM_ID_1 1

// Macros for system address
#define FIVE 5
#define FOUR 4
#define THREE 3
#define TWO 2
#define ONE 1

#define SERVER_PASSIVE_SCANNING 0

// Value * 0.625 = 80 * 0.625 => 50ms
#define SERVER_SCANNING_INTERVAL 0x50

// Time = Value x 0.625 ms => time = 25ms
#define SERVER_SCANNING_WINDOW 0x28

#define SW_PORT (gpioPortF)
#define SW0_pin (6)
#define SW1_pin (7)

/*
 *   Bit 0:
 *     - 0: Allow bonding without authentication
 *     - 1: Bonding requires authentication (Man-in-the-Middle
 *       protection)
 *
 *   Bit 1:
 *     - 0: Allow encryption without bonding
 *     - 1: Encryption requires bonding. Note that this setting will also
 *       enable bonding.
 *
 *   Bit 2:
 *     - 0: Allow bonding with legacy pairing
 *     - 1: Secure connections only
 *
 *   Bit 3:
 *     - 0: Bonding request does not need to be confirmed
 *     - 1: Bonding requests need to be confirmed. Received bonding
 *       requests are notified by @ref sl_bt_evt_sm_confirm_bonding
 *
 *   Bit 4:
 *     - 0: Allow all connections
 *     - 1: Allow connections only from bonded devices
 *
 *   Bit 5:
 *     - 0: Prefer just works pairing when both options are possible
 *       based on the settings.
 *     - 1: Prefer authenticated pairing when both options are possible
 *       based on the settings.
 */
#define FLAGS (0b00001111)

// Global structure to store BLE data
ble_data_struct_t ble_data;

// Global variables
sl_status_t sc;                   // Status code for Silicon Labs API functions
uint8_t system_id[SYSTEM_ID_LEN]; // Buffer for the System ID value
uint16_t interval;
uint16_t latency;
uint16_t timeout;

// Declare memory for the queue/buffer, and our write and read pointers.
queue_struct_t my_queue[QUEUE_DEPTH]; // the queue
uint32_t wptr = 0;                    // write pointer
uint32_t rptr = 0;                    // read pointer

// global variable
uint32_t current_length = 0; // stores the current value of queue length

/**
 * @brief Retrieves a pointer to the global BLE data structure.
 *
 * This function is used to access the global BLE data structure from other files or functions,
 * providing a mechanism to share BLE-related data across the application.
 *
 * @return ble_data_struct_t* Pointer to the global BLE data structure.
 */
ble_data_struct_t *getBleDataPtr()
{
    return (&ble_data);
} // getBleDataPtr()

/**
 * @brief Converts a floating-point representation from a Bluetooth (BT) buffer into a 32-bit integer.
 *
 * This static function interprets a specific byte format in a Bluetooth buffer to calculate
 * a temperature value represented as a 32-bit integer. The buffer format is expected to be
 * as follows:
 * - The first byte ([0]) contains flags, where bit[0] distinguishes between Celsius and Fahrenheit.
 * - Bytes [1] to [3] represent the mantissa in 2's complement form.
 * - The fifth byte ([4]) represents the exponent, also in 2's complement form.
 *
 * The formula used for conversion is: value = 10^exponent * mantissa
 *
 * @param buffer_ptr Pointer to the buffer containing the bytes to be converted.
 *                   This buffer is expected to have at least 5 bytes:
 *                   a flags byte, three bytes for the mantissa, and one byte for the exponent.
 *
 * @return The temperature value as a 32-bit integer. The return value accounts for the sign of the mantissa
 *         and applies the mathematical operation as per the decoded exponent and mantissa from the buffer.
 *
 */
static int32_t float_to_int32(const uint8_t *buffer_ptr)
{
    uint8_t signByte = 0;
    int32_t mantissa;
    // input data format is:
    // [0] = flags byte, bit[0] = 0 -> Celsius; =1 -> Fahrenheit
    // [3][2][1] = mantissa (2's complement)
    // [4] = exponent (2's complement)
    // BT buffer_ptr[0] has the flags byte
    int8_t exponent = (int8_t)buffer_ptr[4];
    // sign extend the mantissa value if the mantissa is negative
    if (buffer_ptr[3] & 0x80)
    { // msb of [3] is the sign of the mantissa
        signByte = 0xFF;
    }
    mantissa = (int32_t)(buffer_ptr[1] << 0) |
               (buffer_ptr[2] << 8) |
               (buffer_ptr[3] << 16) |
               (signByte << 24);
    // value = 10^exponent * mantissa, pow() returns a double type
    return (int32_t)(pow(10, exponent) * mantissa);
} // FLOAT_TO_INT32

/**
 * @brief Handles incoming BLE events and dispatches actions based on the event type.
 *
 * This function is a central event handler for BLE events. It switches between different
 * BLE event IDs and executes corresponding actions, such as setting up the device on boot,
 * handling new connections, and managing connection parameters.
 *
 * @param evt Pointer to the BLE event structure.
 */
void handle_ble_event(sl_bt_msg_t *evt)
{

    // Switch statement to handle different types of BLE events
    switch (SL_BT_MSG_ID(evt->header))
    {

    // ******************************************************
    // Events common to both Servers and Clients
    // ******************************************************
    // --------------------------------------------------------
    // --------------------------------------------------------
    // System boot event: Initialize BLE settings on device boot-up
    case sl_bt_evt_system_boot_id:
        // Log the version of the Bluetooth stack
        PRINT_LOG("Bluetooth stack booted: v%d.%d.%d-b%d\n\r",
                  evt->data.evt_system_boot.major,
                  evt->data.evt_system_boot.minor,
                  evt->data.evt_system_boot.patch,
                  evt->data.evt_system_boot.build);

        // Retrieve the device's Bluetooth identity address
        sc = sl_bt_system_get_identity_address(&ble_data.myAddress, &ble_data.myAddressType);
        if (sc != SL_STATUS_OK)
        {
            // Log an error if unable to retrieve the address
            LOG_ERROR("sl_bt_system_get_identity_address() returned != 0 status=0x%04x", (unsigned int)sc);
        }

        // Prepare the System ID based on the Bluetooth address
        // The System ID is derived from the device's Bluetooth address with a standard format
        system_id[0] = ble_data.myAddress.addr[FIVE];
        system_id[SYSTEM_ID_1] = ble_data.myAddress.addr[FOUR];
        system_id[SYSTEM_ID_2] = ble_data.myAddress.addr[THREE];
        system_id[SYSTEM_ID_3] = SYSTEM_ID3; // Middle bytes are fixed according to the Bluetooth SIG's specification
        system_id[SYSTEM_ID_4] = SYSTEM_ID4; // Middle bytes are fixed according to the Bluetooth SIG's specification
        system_id[SYSTEM_ID_5] = ble_data.myAddress.addr[TWO];
        system_id[SYSTEM_ID_6] = ble_data.myAddress.addr[ONE];
        system_id[SYSTEM_ID_7] = ble_data.myAddress.addr[0];

        // Write the System ID to the GATT database
        sc = sl_bt_gatt_server_write_attribute_value(gattdb_system_id,
                                                     0,                 // Attribute value offset
                                                     sizeof(system_id), // Length of the System ID
                                                     system_id);        // System ID value
        if (sc != SL_STATUS_OK)
        {
            // Log an error if unable to retrieve the address
            LOG_ERROR("sl_bt_gatt_server_write_attribute_value() returned != 0 status=0x%04x", (unsigned int)sc);
        }

        // Log the Bluetooth address of the device
        PRINT_LOG("Bluetooth %s address: %02X:%02X:%02X:%02X:%02X:%02X\n\r",
                  ble_data.myAddressType ? "static random" : "public device",
                  ble_data.myAddress.addr[0],
                  ble_data.myAddress.addr[ONE],
                  ble_data.myAddress.addr[TWO],
                  ble_data.myAddress.addr[THREE],
                  ble_data.myAddress.addr[FOUR],
                  ble_data.myAddress.addr[FIVE]);


        // Delete the bondings , and configure the stack for bonding.
        sl_bt_sm_delete_bondings();
        sl_bt_sm_configure(FLAGS, sl_bt_sm_io_capability_noinputnooutput);

#if (DEVICE_IS_BLE_SERVER == 1)

        // Create an advertising set for BLE advertising
        sc = sl_bt_advertiser_create_set(&ble_data.advertisingSetHandle);
        if (sc != SL_STATUS_OK)
        {
            // Log an error if the advertising set cannot be created
            LOG_ERROR("sl_bt_advertiser_create_set() returned != 0 status=0x%04x", (unsigned int)sc);
        }

        // Configure advertising timing parameters
        sc = sl_bt_advertiser_set_timing(
            ble_data.advertisingSetHandle, // The advertising set handle
            ADV_INTERVAL,                  // Minimum advertising interval (in units of 0.625 ms, i.e 400*0.625 = 250)
            ADV_INTERVAL,                  // Maximum advertising interval (in units of 0.625 ms, i.e 400*0.625 = 250)
            0,                             // Advertising duration (0 means continue until stopped)
            0);                            // Maximum number of advertising events (0 means no limit)
        if (sc != SL_STATUS_OK)
        {
            // Log an error if advertising timing cannot be set
            LOG_ERROR("sl_bt_advertiser_set_timing() returned != 0 status=0x%04x", (unsigned int)sc);
        }

        // Start advertising
        sc = sl_bt_advertiser_start(
            ble_data.advertisingSetHandle,           // The advertising set handle
            sl_bt_advertiser_general_discoverable,   // General discoverability mode
            sl_bt_advertiser_connectable_scannable); // Connectable and scannable advertising
        if (sc != SL_STATUS_OK)
        {
            // Log an error if advertising cannot be started
            LOG_ERROR("sl_bt_advertiser_start() returned != 0 status=0x%04x", (unsigned int)sc);
        }

#else
        sc = sl_bt_scanner_set_mode(sl_bt_gap_phy_1m, SERVER_PASSIVE_SCANNING);
        if (sc != SL_STATUS_OK)
        {
            // Log an error if the advertising set cannot be created
            LOG_ERROR("sl_bt_scanner_set_mode() returned != 0 status=0x%04x", (unsigned int)sc);
        }

        sc = sl_bt_scanner_set_timing(sl_bt_gap_phy_1m, SERVER_SCANNING_INTERVAL, SERVER_SCANNING_WINDOW);
        if (sc != SL_STATUS_OK)
        {
            // Log an error if scanner timing set cannot be created
            LOG_ERROR("sl_bt_scanner_set_timing() returned != 0 status=0x%04x", (unsigned int)sc);
        }

        sc = sl_bt_connection_set_default_parameters(CON_INTERVAL, CON_INTERVAL, CON_LATENCY, CON_TIMEOUT, 0, MAX_CE_LEN);
        if (sc != SL_STATUS_OK)
        {
            // Log an error if the connection paramter set cannot be created
            LOG_ERROR("sl_bt_connection_set_default_parameters() returned != 0 status=0x%04x", (unsigned int)sc);
        }

        sc = sl_bt_scanner_start(sl_bt_gap_phy_1m, sl_bt_scanner_discover_observation);
        if (sc != SL_STATUS_OK)
        {
            // Log an error if the connection scanning can not be started
            LOG_ERROR("sl_bt_scanner_start() returned != 0 status=0x%04x", (unsigned int)sc);
        }
        displayPrintf(DISPLAY_ROW_CONNECTION, "Discovering");
        displayPrintf(DISPLAY_ROW_BTADDR2, "");
        displayPrintf(DISPLAY_ROW_TEMPVALUE, "");
#endif
        break;

    /*
    * typedef struct sl_bt_evt_connection_opened_t
    * {
    * bd_addr address;
    * uint8_t address_type;
    * uint8_t master;
    * uint8_t connection;
    * uint8_t bonding;
    * uint8_t advertiser;
    }evt_connection_opened;
    */
    // Connection opened event: Manage the new connection
    case sl_bt_evt_connection_opened_id:
        // Log that a new connection has been opened
        PRINT_LOG("Connection opened\n\r");
        // Save the connection handle and mark the connection as open, and handle other flags
        ble_data.appConnectionHandle = evt->data.evt_connection_opened.connection;
        ble_data.connection_open = true;
        ble_data.indication_in_flight = false;
        ble_data.bonded = false;
        ble_data.bonding = false;

#if (DEVICE_IS_BLE_SERVER == 1)
        // Stop advertising since a connection has been established
        sc = sl_bt_advertiser_stop(ble_data.advertisingSetHandle);
        if (sc != SL_STATUS_OK)
        {
            // Log an error if stopping advertising fails
            LOG_ERROR("sl_bt_advertiser_stop() returned != 0 status=0x%04x", (unsigned int)sc);
        }

        // Request to update the connection parameters
        sc = sl_bt_connection_set_parameters(ble_data.appConnectionHandle,
                                             CON_INTERVAL,
                                             CON_INTERVAL,
                                             CON_LATENCY,
                                             CON_TIMEOUT,
                                             0,
                                             MAX_CE_LEN);
        if (sc != SL_STATUS_OK)
        {
            // Log an error if setting new connection parameters fails
            LOG_ERROR("Failed to set connection parameters. Status: 0x%04x", sc);
        }

#else
        displayPrintf(DISPLAY_ROW_BTADDR2, "%02X:%02X:%02X:%02X:%02X:%X",
                      evt->data.evt_connection_opened.address.addr[0],
                      evt->data.evt_connection_opened.address.addr[ONE],
                      evt->data.evt_connection_opened.address.addr[TWO],
                      evt->data.evt_connection_opened.address.addr[THREE],
                      evt->data.evt_connection_opened.address.addr[FOUR],
                      evt->data.evt_connection_opened.address.addr[FIVE]);
        displayPrintf(DISPLAY_ROW_CONNECTION, "Connected");

#endif
        break;

    // Handle the event when a BLE connection is closed
    case sl_bt_evt_connection_closed_id:
        // Log the closure of the connection
        PRINT_LOG("Connection Closed\n\r");
        sl_bt_sm_delete_bondings();

        // Reset connection-related flags as the connection is now closed, reset flags
        ble_data.appConnectionHandle = 0;            // Reset the connection handle
        ble_data.indication_in_flight = false;       // No longer sending indications
        ble_data.ok_to_send_htm_indications = false; // No longer permitted to send indications
        ble_data.connection_open = false;            // Mark the connection as closed
        ble_data.bonded = false;
        ble_data.ok_to_send_button_indications = false;
        ble_data.bonding = false;

        gpioLed0SetOff();
        gpioLed1SetOff();


#if (DEVICE_IS_BLE_SERVER == 1)
        // Restart advertising to allow new connections
        sc = sl_bt_advertiser_start(
            ble_data.advertisingSetHandle,
            sl_bt_advertiser_general_discoverable,
            sl_bt_advertiser_connectable_scannable);
        if (sc != SL_STATUS_OK)
        {
            // Log an error if restarting advertising fails
            LOG_ERROR("sl_bt_advertiser_start() returned != 0 status=0x%04x", (unsigned int)sc);
        }


#else
        displayPrintf(DISPLAY_ROW_TEMPVALUE, "");
        displayPrintf(DISPLAY_ROW_BTADDR2, "");
        displayPrintf(DISPLAY_ROW_CONNECTION, "Discovering");

        sc = sl_bt_scanner_start(sl_bt_gap_phy_1m, sl_bt_scanner_discover_observation);
        if (sc != SL_STATUS_OK)
        {
            // Log an error if the connection paramter set cannot be created
            LOG_ERROR("sl_bt_connection_set_default_parameters() returned != 0 status=0x%04x", (unsigned int)sc);
        }
#endif
        break;

    /*
     * typedef struct sl_bt_evt_connection_parameters_t
     * {
     *   uint8_t  connection;
     *   uint16_t interval;
     *   uint16_t latency;
     *   uint16_t timeout;
     *   uint8_t  security_mode;
     *   uint16_t txsize;
     * });
     */
    // Handle the event when connection parameters are updated
    case sl_bt_evt_connection_parameters_id:
#if (PRINT_LOG_STATEMENTS == 1)
        // Extract the updated connection parameters from the event
        interval = evt->data.evt_connection_parameters.interval;
        latency = evt->data.evt_connection_parameters.latency;
        timeout = evt->data.evt_connection_parameters.timeout;

        // Convert the connection interval and timeout to milliseconds for readability
        float interval_ms = interval * 1.25; // Connection interval in ms
        float timeout_ms = timeout * 10;     // Supervision timeout in ms

        // Log the updated connection parameters
        PRINT_LOG("Connection parameters updated:");
        PRINT_LOG("Interval: %f ms", interval_ms);                       // Log the connection interval in milliseconds
        PRINT_LOG("Latency: %u (number of connection events)", latency); // Log the connection latency
        PRINT_LOG("Timeout: %f ms\n", timeout_ms);                       // Log the supervision timeout in milliseconds
#endif

        break;

    case sl_bt_evt_system_external_signal_id:
        // Check if the external signal corresponds to button 0 being pressed.
        if ((evt->data.evt_system_external_signal.extsignals - evtBTN0) == 0x00)
        {

            // If the device is in the bonding process but not yet bonded, confirm the passkey to complete bonding.
            if (!ble_data.bonded && ble_data.bonding)
            {
                ble_data.bonding = false;
                ble_data.bonded = true;
                sl_bt_sm_passkey_confirm(ble_data.appConnectionHandle, true); // Confirm the passkey with 'true'.
            }

#if (DEVICE_IS_BLE_SERVER)
            // Toggle the button state between pressed and released.
            // ble_data.buttonState = !ble_data.buttonState;
            ble_data.buttonState = !GPIO_PinInGet(SW_PORT, SW0_pin); //  cause of pull up

            // Write the new button state to the corresponding GATT characteristic.
            sl_bt_gatt_server_write_attribute_value(gattdb_report_map, 0, sizeof(ble_data.buttonState), &ble_data.buttonState);

            // Log the current queue depth for debugging purposes.
            PRINT_LOG("Current Queue Length (EXT event): %d\n\r", get_queue_depth());

            // If the device is already bonded and not currently bonding, handle the button state indication.
            if (ble_data.bonded && !ble_data.bonding && ble_data.ok_to_send_button_indications)
            {
                attemptToSendOrQueueIndication(NULL, true);
            }
#endif
        }

        else if (((evt->data.evt_system_external_signal.extsignals - evtBTN1) == 0x00) && !DEVICE_IS_BLE_SERVER)
        {
            if (!GPIO_PinInGet(SW_PORT, SW0_pin) && !GPIO_PinInGet(SW_PORT, SW1_pin) && !ble_data.indication_in_flight)
            {
                int flag = (ble_data.ok_to_send_button_indications == true) ? 0x00 : 0x02;
                ble_data.ok_to_send_button_indications = (ble_data.ok_to_send_button_indications == true) ? false : true;
                // enable indication

                sc = sl_bt_gatt_set_characteristic_notification(
                    ble_data.appConnectionHandle,
                    ble_data.buttonCharacteristicHandle,
                    flag);
                // Error handling if enabling indications failed
                if (sc != SL_STATUS_OK)
                {

                    // SL_STATUS_IN_PROGRESS ((sl_status_t)0x0005): Operation is in progress and not yet complete (pass or fail).
                    LOG_ERROR("BTN sl_bt_gatt_set_characteristic_notification() returned != 0 status=0x%04x", (unsigned int)sc);
                }
                else{
                    ble_data.indication_in_flight = true;
                }
            }
            else if (GPIO_PinInGet(SW_PORT, SW0_pin) && !GPIO_PinInGet(SW_PORT, SW1_pin) && !ble_data.indication_in_flight)
            {
                if(!ble_data.bonded){
                    sl_bt_sm_increase_security(ble_data.appConnectionHandle);
                }
                else{
                    sc = sl_bt_gatt_read_characteristic_value(ble_data.appConnectionHandle, ble_data.buttonCharacteristicHandle);
                    if (sc != SL_STATUS_OK)
                    {
                        LOG_ERROR("BTN sl_bt_gatt_read_characteristic_value() returned != 0 status=0x%04x", (unsigned int)sc);
                        
                    }
                    else{
                        ble_data.indication_in_flight = true;
                    }
                }
                
            
            }
        }

        break;

    // Soft timer event: Handles periodic tasks, such as updating display or sensor readings
    case sl_bt_evt_system_soft_timer_id:


        break;

    // Indicates a user request to display that the new bonding request is received and for the user to confirm the request
    case sl_bt_evt_sm_confirm_bonding_id:

        // Print log message indicating a bonding confirmation request is received.
        PRINT_LOG("Bonding confirm\r\n");
        // Confirm bonding without user interaction, automatically accepting the bonding request.
        sc = sl_bt_sm_bonding_confirm(ble_data.appConnectionHandle, 1);
        // Check if the bonding confirmation was successfully sent.
        if (sc != SL_STATUS_OK)
        {
            // Log an error if the bonding confirmation failed.
            LOG_ERROR("sl_bt_sm_bonding_confirm() returned != 0 status=0x%04x", (unsigned int)sc);
        }
        break;

    // Event raised when bonding is successful
    case sl_bt_evt_sm_bonded_id:
        // Update the application state to indicate bonding is not in progress but bonded.
        ble_data.bonding = false;
        ble_data.bonded = true;

        // Log a message indicating successful bonding.
        PRINT_LOG("Bonded\r\n\n");
        break;

    // Event raised when bonding failed
    case sl_bt_evt_sm_bonding_failed_id:
        // Update the application state to indicate neither bonding nor bonded.
        ble_data.bonding = false;
        ble_data.bonded = false;
        // Log a message indicating bonding failed.
        PRINT_LOG("Bonding failed\r\n\n");
        PRINT_LOG("--------------------------------------\r\n\n");

        break;

    /*
     * typedef struct sl_bt_evt_sm_confirm_passkey_t
     * {
     * uint8_t  connection; Connection handle
     * uint32_t passkey;     Passkey. Range: 0 to 999999.
     * } evt_sm_confirm_passkey ;
     */
    // Event raised by the security manager when a passkey needs to be confirmed
    case sl_bt_evt_sm_confirm_passkey_id:
        // Update the application state to indicate bonding is in progress but not yet bonded.
        ble_data.bonding = true;
        ble_data.bonded = false;

        // Log a message prompting the user to verify the passkey matches the other device's display.
        PRINT_LOG("Do you see this passkey on the other device: %06lu? (y/n)\r\n\n",
                  evt->data.evt_sm_confirm_passkey.passkey);
        break;

    /* ******************************************************
     * ******************************************************
     * ******************************************************
     * Events common to Server
     * ******************************************************
     * --------------------------------------------------------
     * --------------------------------------------------------
     * --------------------------------------------------------
     */
    // typedef struct sl_bt_evt_gatt_server_characteristic_status_t
    // {
    //      uint8_t connection; *< Connection handle
    //      uint16_t characteristic; *< GATT characteristic handle.
    //      uint8_t status_flags; *< Describes whether Client Characteristic Configuration was change or if a confirmation was received.
    //      uint16_t client_config_flags; *< This field carries the new value of the
    //      Client Characteristic Configuration. I
    // } evt_gatt_server_characteristic_status;
    // GATT server characteristic status event: Handles changes in characteristics, such as enabling notifications
    case sl_bt_evt_gatt_server_characteristic_status_id:

        // Check if the event is an indication confirmation from the client.
        if (evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_confirmation)
        {
            // Reset the flag to indicate no indication is currently in-flight.
            ble_data.indication_in_flight = false;
            // If there are queued indications, attempt to send the next one.

            send_from_queue();
        }

//        // Check if the event is related to the temperature measurement characteristic by comparing the characteristic handle.
//        if (evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_temperature_measurement)
//        {
//            // Check if the status change was due to a change in the Client Characteristic Configuration Descriptor (CCCD).
//            if (evt->data.evt_gatt_server_characteristic_status.status_flags == gatt_server_client_config)
//            {
//                // Check if indications have been enabled for the characteristic by inspecting the client configuration flags.
//                // The gatt_indication flag is set if indications are enabled.
//                if (evt->data.evt_gatt_server_characteristic_status.client_config_flags & gatt_indication)
//                {
//                    PRINT_LOG("Indication for Temprature has been enabled by Client\n");
//                    // Indications have been enabled by the client.
//                    ble_data.ok_to_send_htm_indications = true;
//                    gpioLed0SetOn();
//                }
//                else
//                {
//                    PRINT_LOG("Indication for Temprature has been disabled by Client\n");
//                    // Resetting the queue as we are not sending indication
//                    reset_queue();
//                    // Indications have been disabled by the client.
//                    ble_data.ok_to_send_htm_indications = false;
//                    gpioLed0SetOff();
//                }
//            }
//        }


        break;

    // Indication timeout event: Error handling for failed indications
    case sl_bt_evt_gatt_server_indication_timeout_id:
        // Check if the data is still on the way
        if (ble_data.indication_in_flight == true)
        {
            LOG_ERROR("Error in Indication (TIMEOUT)\n");
        }

        ble_data.indication_in_flight = false;

        break;

    /* ******************************************************
     * ******************************************************
     * Events common to Client
     * ******************************************************
     * --------------------------------------------------------
     * --------------------------------------------------------
     * --------------------------------------------------------
     * --------------------------------------------------------
     */
    /* typedef struct sl_bt_evt_scanner_scan_report_t
     * {
     * uint8_t    packet_type;
     * bd_addr    address;
     * uint8_t    address_type;
     * uint8_t    bonding;
     * uint8_t    primary_phy;
     * uint8_t    secondary_phy;
     * uint8_t    adv_sid;
     * int8_t     tx_power;
     * int8_t     rssi;
     * uint8_t    channel;
     * uint16_t   periodic_interval;
     * uint8array data;
     * } evt_scanner_scan_report;
     */
    // this means there was packet found while discovery process
    case sl_bt_evt_scanner_scan_report_id:
        PRINT_LOG("Found Address :%02X %02X %02X %02X %02X %02X\n\r",
                  evt->data.evt_scanner_scan_report.address.addr[0],
                  evt->data.evt_scanner_scan_report.address.addr[1],
                  evt->data.evt_scanner_scan_report.address.addr[2],
                  evt->data.evt_scanner_scan_report.address.addr[3],
                  evt->data.evt_scanner_scan_report.address.addr[4],
                  evt->data.evt_scanner_scan_report.address.addr[5]);
        // if address matcches and address type also matches
        bd_addr device_addr = SERVER_BT_ADDRESS;
        if (evt->data.evt_scanner_scan_report.packet_type == 0)
        {

            if (memcmp(evt->data.evt_scanner_scan_report.address.addr, device_addr.addr, sizeof(device_addr.addr)) == 0)
            {
                PRINT_LOG(" Found the address wohooo!\n\r");
                sc = sl_bt_scanner_stop();
                if (sc != SL_STATUS_OK)
                {
                    // Log an error if stopping advertising fails
                    LOG_ERROR("sl_bt_scanner_stop() returned != 0 status=0x%04x", (unsigned int)sc);
                }

                sc = sl_bt_connection_open(evt->data.evt_scanner_scan_report.address,
                                           evt->data.evt_scanner_scan_report.address_type,
                                           sl_bt_gap_1m_phy,
                                           NULL);
                if (sc != SL_STATUS_OK)
                {
                    // Log an error if stopping advertising fails
                    LOG_ERROR("sl_bt_connection_open() returned != 0 status=0x%04x", (unsigned int)sc);
                }
            }
        }
        break;

    /*
     * typedef struct sl_bt_evt_gatt_service_s
     * {
     * uint8_t    connection;
     * uint32_t   service;
     * uint8array uuid;
     * }evt_gatt_service;
     */
    // this event means there was gatt service found in server's database
    case sl_bt_evt_gatt_service_id:
    {
        // save service handle and save service uuid
        uint8_t thermometer_service_uuid[2] = THERMOMETER_SERVICE_UUID;
        uint8_t button_service_uuid[16] = BUTTON_SERVICE_UUID;

        PRINT_LOG("Got service with service handle %X , uuid %x %x\n\r",
                  evt->data.evt_gatt_service.service,
                  evt->data.evt_gatt_service.uuid.data[0],
                  evt->data.evt_gatt_service.uuid.data[1]);
        if (memcmp(evt->data.evt_gatt_service.uuid.data, thermometer_service_uuid, sizeof(thermometer_service_uuid)) == 0)
        {
            PRINT_LOG("Found the Temperature service, saving handle\n\r");
            // save service handle
            ble_data.thermometerHandle = evt->data.evt_gatt_service.service;
        }

        else if (memcmp(evt->data.evt_gatt_service.uuid.data, button_service_uuid, sizeof(button_service_uuid)) == 0)
        {
            PRINT_LOG("Found the Button service, saving handle\n\r");
            // save service handle
            ble_data.buttonServiceHandle = evt->data.evt_gatt_service.service;
        }
    }
    break;

    /*
     * typedef struct sl_bt_evt_gatt_characteristic_t
     *    {
     *   uint8_t    connection;
     *   uint16_t   characteristic;
     *   uint8_t    properties;
     *   uint8array uuid;
     *   } evt_gatt_characteristic;
     *
     */
    // GATT server characteristic status event: Handles changes in characteristics, enabling notifications
    case sl_bt_evt_gatt_characteristic_id:
    {
        uint8_t thermometer_characteristic_uuid[2] = THERMOMETER_CHARACTERISTIC_UUID;
        uint8_t button_characteristic_uuid[16] = BUTTON_CHARACTERISTIC_UUID;

        PRINT_LOG("Got characteristic with char handle %X , uuid %x %x\n\r",
                  evt->data.evt_gatt_characteristic.characteristic,
                  evt->data.evt_gatt_characteristic.uuid.data[0],
                  evt->data.evt_gatt_characteristic.uuid.data[1]);

        // Check for the characteristic uuid
        if (memcmp(evt->data.evt_gatt_characteristic.uuid.data, thermometer_characteristic_uuid, sizeof(thermometer_characteristic_uuid)) == 0)
        {
            PRINT_LOG("Found HTM Characteristics that we want, enabling Indication \n\r");
            // we found the service we want

            // save handle
            ble_data.thermometerCharacteristicHandle = evt->data.evt_gatt_characteristic.characteristic;
        }

        else if (memcmp(evt->data.evt_gatt_characteristic.uuid.data, button_characteristic_uuid, sizeof(button_characteristic_uuid)) == 0)
        {
            PRINT_LOG("Found Button Characteristics that we want, enabling Indication \n\r");
            // we found the service we want

            // save handle
            ble_data.buttonCharacteristicHandle = evt->data.evt_gatt_characteristic.characteristic;
        }
    }
    break;

    /*
     * typedef struct sl_bt_evt_gatt_characteristic_value_s
     * {
     *   uint8_t    connection;
     *   uint16_t   characteristic;
     *   uint8_t    att_opcode;
     *   uint16_t   offset;
     *   uint8array value;
     * };
     */
    // This event is generated when a characteristic value was received , an indication, a notification
    case sl_bt_evt_gatt_characteristic_value_id:
        // send confirmation to server about received data
        if (evt->data.evt_gatt_characteristic_value.characteristic == ble_data.thermometerCharacteristicHandle && ble_data.ok_to_send_htm_indications == true)
        {

            sc = sl_bt_gatt_send_characteristic_confirmation(evt->data.evt_gatt_characteristic_value.connection);
            // extract value sent by server from evt_gatt_characteristic_value data structure
            uint8_t *char_value = &(evt->data.evt_gatt_characteristic_value.value.data[0]);
            // convert IEEE-11073 value to int32 for display
            int32_t server_temperature = float_to_int32(char_value);
            // printing value on console
            PRINT_LOG("Temperature Data from Server: %d\n\r", server_temperature);

        }

        // Check if the event is for the button characteristic and if sending button indications is allowed and the device is bonded.
        else if (evt->data.evt_gatt_characteristic_value.characteristic == ble_data.buttonCharacteristicHandle && ble_data.bonded)
        {
            // Attempt to send a confirmation for the characteristic update back to the server.
            sc = sl_bt_gatt_send_characteristic_confirmation(evt->data.evt_gatt_characteristic_value.connection);
            // Extract the button state value sent by the server from the event data structure.
            uint8_t char_value = evt->data.evt_gatt_characteristic_value.value.data[0];
            // Update the local button state based on the received value.
            ble_data.buttonState = char_value;

            // Log the received button state value for debugging purposes.
            PRINT_LOG("Button Data from Server: %d\n\r", char_value);
        }
        break;

    case sl_bt_evt_gatt_procedure_completed_id:
        ble_data.indication_in_flight = false;
        break;
    } // end - switch
} // handle_ble_event()

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
void send_HTM_Indication(uint8_t htm_temperature_buffer[], uint8_t size)
{

    // Send the temperature data over BLE as an indication
    sc = sl_bt_gatt_server_send_indication(
        ble_data.appConnectionHandle,
        gattdb_report_map,
        size,
        htm_temperature_buffer);
    // Check for errors in sending the indication
    if (sc != SL_STATUS_OK)
    {
        LOG_ERROR("Failed to send indication. Status: 0x%04x", sc);
    }
    else
    {
        ble_data.indication_in_flight = true;
    }
}

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
void send_Button_Indication(uint8_t buffer[])
{
    sc = sl_bt_gatt_server_send_indication(
        ble_data.appConnectionHandle,
        gattdb_report_map,
        1,
        buffer);
    if (sc != SL_STATUS_OK)
    {
        // Log an error if sending the indication fails.
        LOG_ERROR("sl_bt_gatt_server_send_indication() in sl_bt_evt_gatt_server_characteristic_status_id returned != 0 status=0x%04x", (unsigned int)sc);
    }
    else
    {
        PRINT_LOG("BTN indication Sent\n\r");
        // Successfully sent the indication, set the in-flight flag.
        ble_data.indication_in_flight = true;
    }
}

/*
 * ---------------------------------------------------------------------
 * Private function used only by this .c file.
 * Compute the next ptr value. Given a valid ptr value, compute the next valid
 * value of the ptr and return it.
 * Isolation of functionality: This defines "how" a pointer advances.
 * ---------------------------------------------------------------------
 */
static uint32_t nextPtr(uint32_t ptr)
{

    // Advance the pointer to desired range of 0 to QUEUE_DEPTH
    // with use of modulo, to make circular buffer
    ptr = (ptr + 1) % QUEUE_DEPTH;

    // Return the next pointer
    return ptr;

} // nextPtr()

/*
 * ---------------------------------------------------------------------
 * Check if the Queue is full or not with respect to current length
 * Queue
 * @params:
 *      int for_write: true or false based on for queue is full for writing or reading
 * @returns:
 *     return true or false based on queue is full or not
 * ---------------------------------------------------------------------
 */
static bool checkFull(int for_write)
{
    // Check for_write variable for length check
    if (for_write)
    {
        // If current_length of queue is equal to queue depth it would be full
        // so we return true if length is equal to queue_depth
        // Used for write constraint check
        return (current_length == QUEUE_DEPTH);
    }
    else
    {
        // If current_length is equal to 0 that means there is no value left tor
        // read in the queue
        // Used for read constraint check
        return (current_length == 0);
    }
}

/*
 * ---------------------------------------------------------------------
 * Printing Whole queue values for debugging purpose
 * printing all the values of queue charHandle, bufLength, Buffer values in formatted way
 * @params:
 *      none
 * @returns:
 *     none
 * ---------------------------------------------------------------------
 */
void printBuffer(void)
{
    // Looping through each element for printing
    for (int i = 0; i < QUEUE_DEPTH; i++)
    {
        LOG_INFO("Queue charHandle: %d, Queue length: %ld , Buffer: ", my_queue[i].charHandle, my_queue[i].bufLength);
        // Looping through each buffer value for printing
        for (int j = 0; j < MAX_BUFFER_LENGTH; j++)
        {
            // Printing buffer elements
            printf("%d ", my_queue[i].buffer[j]);
        }
        printf("\n");
    }
}

/*
 * ---------------------------------------------------------------------
 * Public function.
 * This function resets the queue.
 * @params:
 *      none
 * @returns:
 *     none
 * ---------------------------------------------------------------------
 */
void reset_queue(void)
{
    // reset every element to zero in the queue depth
    for (int index = 0; index < QUEUE_DEPTH; index++)
    {
        // Setting bufLength and charLength to zero
        my_queue[index].bufLength = 0;
        my_queue[index].charHandle = 0;
        memset(my_queue[index].buffer, 0, QUEUE_DEPTH); // Setting array value zero with memset
    }
    // setting pointers to initial (0) position
    rptr = 0;
    wptr = 0;

} // reset_queue()

/* ---------------------------------------------------------------------
 * Public function.
 * This function writes an entry to the queue if the the queue is not full.
 * Input parameter "charHandle" should be written to queue_struct_t element "charHandle".
 * Input parameter "bufLength" should be written to queue_struct_t element "bufLength"
 * The bytes pointed at by input parameter "buffer" should be written to queue_struct_t element "buffer"
 * Returns bool false if successful or true if writing to a full fifo.
 * i.e. false means no error, true means an error occurred.
 * @params:
 *      uint16_t charHandle: charHandle for GattDB
 *      uint32_t bufLength: Bufferlength for buffer which should be greater than or =1 and less than or =5
 *      uint8_t *buffer: buffer to store ,need 5-bytes for HTM and 1-byte for button_state.
 * @returns:
 *     bool:
 * ---------------------------------------------------------------------
 */
bool write_queue(uint16_t charHandle, uint32_t bufLength, uint8_t *buffer)
{

    // check if charHandle, bufLength, buffer is not null and
    if (buffer == NULL || bufLength > MAX_BUFFER_LENGTH || bufLength < MIN_BUFFER_LENGTH)
        return false;

    // check rptr and wptr for full condition and round condition
    if (checkFull(true))
        return true;

    // write the value at current write-ptr
    my_queue[wptr].charHandle = charHandle;
    my_queue[wptr].bufLength = bufLength;
    memcpy(my_queue[wptr].buffer, buffer, bufLength); // copy to queue buffer via memcpy

    // Increment the length of queue
    current_length++;
    // advance the write-ptr
    wptr = nextPtr(wptr);

    // return false at end to show no error
    return false;
} // write_queue()

/* ---------------------------------------------------------------------
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
bool read_queue(uint16_t *charHandle, uint32_t *bufLength, uint8_t *buffer)
{

    // check rptr and wptr for full condition and round condition
    if (checkFull(false))
        return true;

    // copy data to pointer
    *bufLength = my_queue[rptr].bufLength;
    *charHandle = my_queue[rptr].charHandle;
    memcpy(&buffer[0], &my_queue[rptr].buffer[0], *bufLength); // Copy buffer with memcpy

    // Reduce the length of queue as we just read the value
    current_length--;
    // advance the read pointer to next location
    rptr = nextPtr(rptr);

    // if everything went good return false = no error
    return false;

} // read_queue()

/* ---------------------------------------------------------------------
 * Public function.
 * This function returns the wptr, rptr, full and empty values, writing
 * to memory using the pointer values passed in, same rationale as read_queue()
 * The "_" characters are used to disambiguate the global variable names from
 * the input parameter names, such that there is no room for the compiler to make a
 * mistake in interpreting your intentions.
 * ---------------------------------------------------------------------
 */
void get_queue_status(uint32_t *_wptr, uint32_t *_rptr, bool *_full, bool *_empty)
{
    // set the values according to the global variables
    *_wptr = wptr;
    *_rptr = rptr;
    *_full = checkFull(true); // check if queue is full for write ?
    *_empty = !(*_full);

} // get_queue_status()

/* ---------------------------------------------------------------------
 * Public function.
 * Function that computes the number of written entries currently in the queue. If there
 * are 3 entries in the queue, it should return 3. If the queue is empty it should
 * return 0. If the queue is full it should return either QUEUE_DEPTH if
 * USE_ALL_ENTRIES==1 otherwise returns QUEUE_DEPTH-1.
 * ---------------------------------------------------------------------
 */
uint32_t get_queue_depth()
{

    // just return the current length variable
    return (current_length);

} // get_queue_depth()