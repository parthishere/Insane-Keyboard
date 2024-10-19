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
#include "hid.h"

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
#define ADV_INTERVAL 160

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


static uint8_t input_report_data[] = {0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t actual_key = KEY_A;

/*
 *   Bit 0:
 *     - <b>0:</b> Allow bonding without authentication
 *     - <b>1:</b> Bonding requires authentication (Man-in-the-Middle
 *       protection)
 *
 *   Bit 1:
 *     - <b>0:</b> Allow encryption without bonding
 *     - <b>1:</b> Encryption requires bonding. Note that this setting will also
 *       enable bonding.
 *
 *   Bit 2:
 *     - <b>0:</b> Allow bonding with legacy pairing
 *     - <b>1:</b> Secure connections only
 *
 *   Bit 3:
 *     - <b>0:</b> Bonding request does not need to be confirmed
 *     - <b>1:</b> Bonding requests need to be confirmed. Received bonding
 *       requests are notified by @ref sl_bt_evt_sm_confirm_bonding
 *
 *   Bit 4: This option is ignored when the application includes the
 *   bluetooth_feature_external_bonding_database feature.
 *     - <b>0:</b> Allow all connections
 *     - <b>1:</b> Allow connections only from bonded devices
 *
 *   Bit 5:
 *     - <b>0:</b> Prefer just works pairing when both options are possible
 *       based on the settings.
 *     - <b>1:</b> Prefer authenticated pairing when both options are possible
 *       based on the settings.
 *
 *   Bit 6:
 *     - <b>0:</b> Allow secure connections OOB pairing with OOB data from only
 *       one device.
 *     - <b>1:</b> Require secure connections OOB data from both devices.
 *
 *   Bit 7:
 *     - <b>0:</b> Allow debug keys from remote device.
 *     - <b>1:</b> Reject pairing if remote device uses debug keys.
 */
#define FLAGS (0b00000000)

// Global structure to store BLE data
ble_data_struct_t ble_data;

// Global variables
sl_status_t sc;                   // Status code for Silicon Labs API functions
uint8_t system_id[SYSTEM_ID_LEN]; // Buffer for the System ID value
uint16_t interval;
uint16_t latency;
uint16_t timeout;


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
        app_assert_status(sc);

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
        app_assert_status(sc);

        // Log the Bluetooth address of the device
        PRINT_LOG("Bluetooth %s address: %02X:%02X:%02X:%02X:%02X:%02X\n\r",
                  ble_data.myAddressType ? "static random" : "public device",
                  ble_data.myAddress.addr[0],
                  ble_data.myAddress.addr[ONE],
                  ble_data.myAddress.addr[TWO],
                  ble_data.myAddress.addr[THREE],
                  ble_data.myAddress.addr[FOUR],
                  ble_data.myAddress.addr[FIVE]);

        // Create an advertising set for BLE advertising
        sc = sl_bt_advertiser_create_set(&ble_data.advertisingSetHandle);
        app_assert_status(sc);

        sc = sl_bt_legacy_advertiser_generate_data(ble_data.advertisingSetHandle,
                                                   sl_bt_advertiser_general_discoverable);
        app_assert_status(sc);

        // Configure advertising timing parameters
        sc = sl_bt_advertiser_set_timing(
            ble_data.advertisingSetHandle, // The advertising set handle
            ADV_INTERVAL,                  // Minimum advertising interval (in units of 0.625 ms, i.e 400*0.625 = 250)
            ADV_INTERVAL,                  // Maximum advertising interval (in units of 0.625 ms, i.e 400*0.625 = 250)
            0,                             // Advertising duration (0 means continue until stopped)
            0);                            // Maximum number of advertising events (0 means no limit)
        app_assert_status(sc);

        // Bondings

        sc = sl_bt_sm_configure(0, sl_bt_sm_io_capability_noinputnooutput);
        app_assert_status(sc);

        sc = sl_bt_sm_set_bondable_mode(1);
        app_assert_status(sc);

        sc = sl_bt_legacy_advertiser_start(
            ble_data.advertisingSetHandle,        // The advertising set handle
            sl_bt_legacy_advertiser_connectable); // Connectable and scannable advertising
        app_assert_status(sc);

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
        ble_data.connections.connectionHandle = evt->data.evt_connection_opened.connection;
        ble_data.connections.connection_open = true;
        ble_data.connections.bonded = false;
        ble_data.connections.bonding = false;
        
        ble_data.indication_in_flight = false;

        ble_data.current_connetion++;

        // GATT DB server
        // Stop advertising since a connection has been established
        sc = sl_bt_advertiser_stop(ble_data.advertisingSetHandle);
        app_assert_status(sc);

        // Request to update the connection parameters
        sc = sl_bt_connection_set_parameters(ble_data.connections.connectionHandle,
                                             CON_INTERVAL,
                                             CON_INTERVAL,
                                             CON_LATENCY,
                                             CON_TIMEOUT,
                                             0,
                                             MAX_CE_LEN);
        app_assert_status(sc);

        // sc = sl_bt_sm_increase_security(ble_data.connectionHandle);
        // app_assert_status(sc);

        break;

    // Handle the event when a BLE connection is closed
    case sl_bt_evt_connection_closed_id:
        // Log the closure of the connection
        PRINT_LOG("Connection Closed\n\r");

        // Reset connection-related flags as the connection is now closed, reset flags
        ble_data.connections.connectionHandle = 0;      // Reset the connection handle
        ble_data.connections.connection_open = false;      // Mark the connection as closed
        ble_data.connections.bonded = false;
        ble_data.connections.ok_to_send_report_notification = false;
        ble_data.connections.bonding = false;
        ble_data.indication_in_flight = false; // No longer sending indications
        
        ble_data.current_connetion--;
        sc = sl_bt_legacy_advertiser_generate_data(ble_data.advertisingSetHandle,
                                                   sl_bt_advertiser_general_discoverable);
        app_assert_status(sc);

        sc = sl_bt_legacy_advertiser_start(
            ble_data.advertisingSetHandle,        // The advertising set handle
            sl_bt_legacy_advertiser_connectable); // Connectable and scannable advertising
        app_assert_status(sc);

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
        if (((evt->data.evt_system_external_signal.extsignals - evtBTN0) == 0x00) && (ble_data.connections.ok_to_send_report_notification))
        {
            memset(input_report_data, 0, sizeof(input_report_data));

            input_report_data[MODIFIER_INDEX] = 0;
            input_report_data[DATA0_INDEX] = actual_key;

            sc = sl_bt_gatt_server_notify_all(gattdb_report,
                                              sizeof(input_report_data),
                                              input_report_data);

            app_log("Key report was sent\r\n");
        }



        break;

    // Indicates a user request to display that the new bonding request is received and for the user to confirm the request
    case sl_bt_evt_sm_confirm_bonding_id:

        // Print log message indicating a bonding confirmation request is received.
        PRINT_LOG("Bonding confirm\r\n");
        // Confirm bonding without user interaction, automatically accepting the bonding request.
        sc = sl_bt_sm_bonding_confirm(ble_data.connections.connectionHandle, 1);
        // Check if the bonding confirmation was successfully sent.
        app_assert_status(sc);
        break;

    // Event raised when bonding is successful
    case sl_bt_evt_sm_bonded_id:
        // Update the application state to indicate bonding is not in progress but bonded.
        ble_data.connections.bonding = false;
        ble_data.connections.bonded = true;

        // Log a message indicating successful bonding.
        PRINT_LOG("Bonded\r\n\n");
        break;

    // Event raised when bonding failed
    case sl_bt_evt_sm_bonding_failed_id:
        // Update the application state to indicate neither bonding nor bonded.
        ble_data.connections.bonding = false;
        ble_data.connections.bonded = false;
        // Log a message indicating bonding failed.
        PRINT_LOG("Bonding failed\r\n\n");
        PRINT_LOG("--------------------------------------\r\n\n");

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

            // send_from_queue();
        }
        PRINT_LOG("Something came \n");
        if (evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_report)
        {
            // client characteristic configuration changed by remote GATT client
            if (evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_client_config)
            {
                if (evt->data.evt_gatt_server_characteristic_status.client_config_flags == sl_bt_gatt_notification)
                {
                    PRINT_LOG("Indication for Temprature has been enabled by Client\n");
                    ble_data.connections.ok_to_send_report_notification = 1;
                }
                else
                {
                    PRINT_LOG("Indication for Temprature has been disabled by Client\n");
                    ble_data.connections.ok_to_send_report_notification = 0;
                }
            }
        }

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

    case sl_bt_evt_gatt_procedure_completed_id:
        ble_data.indication_in_flight = false;
        break;
    } // end - switch
} // handle_ble_event()
