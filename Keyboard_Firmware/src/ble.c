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

static bd_addr new_device_id = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

/*
Report format
This report must be requested by the software using interrupt transfers once every interval milliseconds, and the interval is defined in the interrupt IN descriptor of the USB keyboard. The USB keyboard report may be up to 8 bytes in size, although not all these bytes are used and it's OK to implement a proper implementation using only the first three or four bytes (and this is how I do it.) Just for completion's sake, however, I will describe the full report mechanism of the keyboard. Notice that the report structure defined below applies to the boot protocol only.

Offset	Size	Description
0	Byte	Modifier keys status.
1	Byte	Reserved field.
2	Byte	Keypress #1.
3	Byte	Keypress #2.
4	Byte	Keypress #3.
5	Byte	Keypress #4.
6	Byte	Keypress #5.
7	Byte	Keypress #6.


Modifier keys status: This byte is a bitfield, where each bit corresponds to a specific modifier key. When a bit is set to 1, the corresponding modifier key is being pressed. Unlike PS/2 keyboards, USB keyboards don't have "scancodes" for modifier keys. The bit structure of this byte is:

Bit	Bit Length	Description
0	1	Left Ctrl.
1	1	Left Shift.
2	1	Left Alt.
3	1	Left GUI (Windows/Super key.)
4	1	Right Ctrl.
5	1	Right Shift.
6	1	Right Alt.
7	1	Right GUI (Windows/Super key.)

Keypress fields: One keyboard report can indicate up to 6 keypresses. All these values are unsigned 8-bit values (unlike PS/2 scancodes, which are mostly 7-bit) which indicate the key being pressed. A reference on the USB scancode to ASCII character conversion table is in the bottom of the article.

*/
static uint8_t input_report_data[] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t dev_index;

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
ble_data_struct_t ble_data = {0};

#define SERVER_PASSIVE_SCANNING 0

// Value * 0.625 = 80 * 0.625 => 50ms
#define SERVER_SCANNING_INTERVAL 0x50

// Time = Value x 0.625 ms => time = 25ms
#define SERVER_SCANNING_WINDOW 0x28

// Advertising interval for BLE in units of 0.625ms.
// ADV_INTERVAL of 400 translates to 250ms (400 * 0.625ms = 250ms).
#define ADV_INTERVAL 160

// Global variables
static sl_status_t sc; // Status code for Silicon Labs API functions
uint16_t interval;
uint16_t latency;
uint16_t timeout;

static uint8_t service_uuid[2] = __HID_SERVICE_UUID;
static uint8_t report_char[2] = __HID_REPORT_CHARACTERISTIC_UUID;

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

void sl_app_log_stats()
{
    app_log("\r\n--------------- LIST of CONNECTED DEVICES ----------------\r\n");
    app_log("==========================================================\r\n");
    static bool print_header = true;

    // print header
    if (print_header == true)
    {
        app_log("ADDRESS            ROLE          HANDLE        STATE\r\n");
    }
    app_log("==========================================================\r\n");

    for (int i = 0; i < (ble_data.number_of_connection); i++)
    {
        print_bd_addr(ble_data.connections[i].device_address);
        app_log("  %-14s%-14d%-10s\r\n",
                (ble_data.connections[i].conn_role == 0) ? "PERIPHARAL" : "CENTRAL",
                ble_data.connections[i].connectionHandle,
                get_conn_state(ble_data.connections[i].conn_state));
    }
    app_log("\r\n");
}

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
    // Events common to both GATT Servers and GATT Clients
    // ******************************************************
    // --------------------------------------------------------
    // --------------------------------------------------------
    // System boot event: Initialize BLE settings on device boot-up
    case sl_bt_evt_system_boot_id:
        ble_data.number_of_connection = 0;
        // Log the version of the Bluetooth stack
        PRINT_LOG("Bluetooth stack booted ! \n\r");
        get_stack_version(evt);
        get_system_id();
        if (DEVICE_IS_BLE_MASTER == 1)
        {
            LOG_INFO(" MASTERRRR \n\r");
        }
        else
        {

            LOG_INFO(" ....slave.... \n\r");
        }

#if (DEVICE_IS_BLE_MASTER == 1)
        sc = sl_bt_scanner_set_parameters(sl_bt_scanner_scan_mode_passive,
                                          20,
                                          10);
        app_assert_status(sc);

        // Start scanning
        sc = sl_bt_scanner_start(sl_bt_gap_1m_phy,
                                 sl_bt_scanner_discover_generic);
        app_assert_status_f(sc, "Failed to start discovery #1\n");
#else
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
            ble_data.advertisingSetHandle,           // The advertising set handle
            sl_bt_advertiser_connectable_scannable); // Connectable and scannable advertising
        app_assert_status(sc);
#endif

        break;

    /*
    * typedef struct sl_bt_evt_connection_opened_t
    * {
    * bd_addr address;
    * uint8_t address_type;
    * uint8_t master; The role this  device operates in the connection.
    * uint8_t connection;
    * uint8_t bonding;
    * uint8_t advertiser;
    }evt_connection_opened;
    */
    // Connection opened event: Manage the new connection
    case sl_bt_evt_connection_opened_id:
        // Log that a new connection has been opened
        PRINT_LOG("[INFO] Connection opened\n\r");

#if DEVICE_IS_BLE_MASTER == 1
        sc = sl_bt_connection_set_parameters(evt->data.evt_connection_opened.connection,
                                        CON_INTERVAL,
                                        CON_INTERVAL,
                                        CON_LATENCY,
                                        CON_TIMEOUT,
                                        0,
                                        MAX_CE_LEN);
#endif

        // our master device is gatt client for that is CR_CENTRAL
        if (evt->data.evt_connection_opened.master == CR_CENTRAL)
        {
            // }
            // Device role: GATT Data base client
            /* Start discovering the remote GATT database */
            PRINT_LOG("CR_CENTRAL\n\r");
            // Request to update the connection parameters
            
            app_assert_status(sc);

            sc = sl_bt_gatt_discover_primary_services_by_uuid(
                evt->data.evt_connection_opened.connection,
                sizeof(service_uuid),
                service_uuid);
            app_assert_status(sc);

            ble_data.discovering_service = true;

            /* connection process completed. */
            ble_data.connecting = false;

            // if (!ble_data.bonded)
            // {
            sc = sl_bt_sm_increase_security(ble_data.connectionHandle);
            app_assert_status(sc);

#if DEVICE_IS_BLE_MASTER == 1
            display_string("CONN", 2, 10);
            // added from boot
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
                ble_data.advertisingSetHandle,           // The advertising set handle
                sl_bt_advertiser_connectable_scannable); // Connectable and scannable advertising
            app_assert_status(sc);
#endif
            // we dont want to increament the count as we already did in connection open call
        }

        /* else if connection role is PERIPHERAL that is GATT Client ...*/
        else if (evt->data.evt_connection_opened.master == CR_PERIPHERAL)
        {

            PRINT_LOG("CR_PERIPHERAL\n\r");
            // Device role: GATT Data base server
            /* update device list */
            ble_data.connections[ble_data.number_of_connection].device_address =
                evt->data.evt_connection_opened.address;
            ble_data.connections[ble_data.number_of_connection].address_type =
                evt->data.evt_connection_opened.address_type;
            ble_data.connections[ble_data.number_of_connection].connectionHandle =
                evt->data.evt_connection_opened.connection;
            ble_data.connections[ble_data.number_of_connection].conn_role = CR_CENTRAL; // connection
                                                                                        //   role of
                                                                                        //   the
                                                                                        //   remote
                                                                                        //   device

            /* Increment ble_data.number_of_connection. */
            ble_data.number_of_connection++;

#if DEVICE_IS_BLE_MASTER == 1
            char buf[100];
            snprintf(buf, sizeof(buf), "%d", ble_data.number_of_connection);
            display_string(buf, 110, 50);
#endif
            //
        }

        // Update device connection state. common for both master and slave roles
        ble_data.connections[ble_data.number_of_connection - 1].conn_state = CS_CONNECTING;

        // /* Advertising stops when connection is opened. Re-start advertising */
        if (ble_data.number_of_connection == MAX_CONNECTIONS)
        {
            PRINT_LOG("[ERROR] Maximum number of allowed connections reached.\r\n");

#if (DEVICE_IS_BLE_MASTER == 1)
            PRINT_LOG("[INFO] Stop scanning and stop advertising.\r\n");
            sc = sl_bt_scanner_stop();
            app_assert_status(sc);
#endif
            // sc = sl_bt_legacy_advertiser_start(ble_data.advertisingSetHandle,
            //                                    sl_bt_legacy_advertiser_connectable);
            sc = sl_bt_advertiser_stop(ble_data.advertisingSetHandle);
            app_assert_status(sc);
            // sc = sl_bt_legacy_advertiser_start(ble_data.advertisingSetHandle,
            //                                    sl_bt_legacy_advertiser_non_connectable);
            // app_assert_status(sc);
            // Safety check - force connection count to MAX
            ble_data.number_of_connection = MAX_CONNECTIONS;
        }
        else
        {
            PRINT_LOG("[INFO]  Max connection not reached. Re-start advertising in connectable mode.\r\n");
            // // Max connection not reached. Re-start advertising in connectable mode
            // sc = sl_bt_legacy_advertiser_start(ble_data.advertisingSetHandle,
            //                                    sl_bt_legacy_advertiser_connectable);
            // app_assert_status(sc);
        }

        break;

    // Handle the event when a BLE connection is closed
    case sl_bt_evt_connection_closed_id:
        // Log the closure of the connection
        PRINT_LOG("[INFO] Connection Closed\n\r");

        ble_data.closedHandle = evt->data.evt_connection_closed.connection;
        dev_index = get_dev_index(ble_data.closedHandle, ble_data);
        if (dev_index > MAX_CONNECTIONS)
        {
            PRINT_LOG("[ERROR] Invalid device index\n\r");
            // ble_data.number_of_connection = 0;  // Reset to safe state
        }
        app_log("Device ");
        print_bd_addr(ble_data.connections[dev_index].device_address);
        app_log(" left the connection::0x%04X\r\n",
                evt->data.evt_connection_closed.reason);

        uint8_t i;
        for (i = dev_index; i < ble_data.number_of_connection - 1; i++)
        {
            ble_data.connections[i] = ble_data.connections[i + 1];
        }

        if (ble_data.number_of_connection > 0)
        {
            ble_data.number_of_connection--;
            char buf[100];
            snprintf(buf, sizeof(buf), "%d", ble_data.number_of_connection);
#if DEVICE_IS_BLE_MASTER == 1
            display_string("DISCONN", 2, 10);
            display_string(buf, 110, 50);
#else
#endif
        }

        // print list of remaining connections
        sl_app_log_stats();

        app_log("Number of active connections ...: %d\r\n", ble_data.number_of_connection);
        app_log("Available connections ..........: %d\r\n",
                MAX_CONNECTIONS - ble_data.number_of_connection);

        /* If we have one less available connection than the maximum allowed...*/
        if (ble_data.number_of_connection == MAX_CONNECTIONS - 1)
        {

#if (DEVICE_IS_BLE_MASTER == 1)
            sc = sl_bt_scanner_start(sl_bt_gap_1m_phy,
                                     sl_bt_scanner_discover_generic);
            app_assert_status_f(sc, "Failed to start discovery #1\n");
            app_log("Scanning restarted.\r\n");
#else
            // sc = sl_bt_gap_enable_whitelisting(1);
            // sl_bt_sm_add_to_whitelist(server_address, uint8_t address_type)

#endif
            sc = sl_bt_legacy_advertiser_start(
                ble_data.advertisingSetHandle,
                sl_bt_legacy_advertiser_connectable);
            app_assert_status(sc);
            app_log("Advertising restarted in CONNECTABLE mode.\r\n");
        }

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
        dev_index = get_dev_index(evt->data.evt_connection_parameters.connection, ble_data);
        ble_data.connections[dev_index].conn_state = CS_CONNECTED;

        if (memcmp(&new_device_id, &ble_data.connections[dev_index].device_address,
                   sizeof(bd_addr)) != 0)
        {
            memcpy(&new_device_id, &ble_data.connections[dev_index].device_address,
                   sizeof(bd_addr));
            app_log("\r\nNEW CONNECTION ESTABLISHED \r\n");
            app_log("Device ID .................: ");
            print_bd_addr(ble_data.connections[ble_data.number_of_connection - 1].device_address);
            app_log("\r\n");
            app_log("Role ......................: %s\r\n",
                    (ble_data.connections[dev_index].conn_role == CR_PERIPHERAL) ? "peripharal" : "central");
            app_log("Handle ....................: %d\r\n",
                    ble_data.connections[dev_index].connectionHandle);
            app_log("Number of connected devices: %d\r\n", ble_data.number_of_connection);
            app_log("Available connections .....: %d\r\n",
                    MAX_CONNECTIONS - ble_data.number_of_connection);

            /* Print connection summary*/
            // if(ble_data.number_of_connection > MAX_CONNECTIONS) ble_data.number_of_connection = MAX_CONNECTIONS;
            PRINT_LOG("ble_data.connection %d \n\r", ble_data.number_of_connection);
            sl_app_log_stats();
        }

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

        if (((evt->data.evt_system_external_signal.extsignals - evtIOEXPANDER_ROW) == 0x00) && (ble_data.ok_to_send_report_notification))
        {
            uint8_t *data = scan_io_expander();
#if DEVICE_IS_BLE_MASTER == 1
            uint8_t *report_data = modifypressedkeys_left(data);
#else
            uint8_t *report_data = modifypressedkeys_right(data);
#endif
            // start scanning, send signal to main
            memset(input_report_data, 0, sizeof(input_report_data));
            memcpy(input_report_data, report_data, 8);

            // PRINT_LOG("[INFO] Key report %X %X %X %X %X %X %X %X\r\n", input_report_data[0],
            //           input_report_data[1],
            //           input_report_data[2],
            //           input_report_data[3],
            //           input_report_data[4],
            //           input_report_data[5],
            //           input_report_data[6],
            //           input_report_data[7]);

            sc = sl_bt_gatt_server_notify_all(gattdb_report,
                                              sizeof(input_report_data),
                                              input_report_data);
            app_assert_status(sc);

            // PRINT_LOG("[INFO] Key report was sent\r\n");
        }

        if (((evt->data.evt_system_external_signal.extsignals - evtENCODER_SW) == 0x00) || ((evt->data.evt_system_external_signal.extsignals - evtENCODER_ROTATE) == 0x00))
        {

                        // memset(input_report_data, 0, sizeof(input_report_data));
                        // input_report_data[2] =  0xA9;

                        // PRINT_LOG("[INFO] Key report %X %X %X %X %X %X %X %X\r\n", input_report_data[0],
                        //           input_report_data[1],
                        //           input_report_data[2],
                        //           input_report_data[3],
                        //           input_report_data[4],
                        //           input_report_data[5],
                        //           input_report_data[6],
                        //           input_report_data[7]);

                        // sc = sl_bt_gatt_server_notify_all(gattdb_report,
                        //                                   sizeof(input_report_data),
                        //                                   input_report_data);
                        // app_assert_status(sc);
        }

        if (((evt->data.evt_system_external_signal.extsignals - evtIOEXPANDER_ROW) == 0x00))
        {
        }

        if (((evt->data.evt_system_external_signal.extsignals - evtLETIMER0_UF) == 0x00))
        {
#if DEVICE_IS_BLE_MASTER == 1
            read_SI7021();
            // EPD_test();
#endif
        }
        break;

    // Indicates a user request to display that the new bonding request is received and for the user to confirm the request
    case sl_bt_evt_sm_confirm_bonding_id:

        // Print log message indicating a bonding confirmation request is received.
        PRINT_LOG("[INFO] Bonding confirm\r\n");
        // Confirm bonding without user interaction, automatically accepting the bonding request.
        sc = sl_bt_sm_bonding_confirm(ble_data.connectionHandle, 1);
        // Check if the bonding confirmation was successfully sent.
        app_assert_status(sc);
        break;

    // Event raised when bonding is successful
    case sl_bt_evt_sm_bonded_id:
        // Update the application state to indicate bonding is not in progress but bonded.
        // ble_data.connections.bonding = false;
        // ble_data.connections.bonded = true;
        ble_data.bonded = true;
        // Log a message indicating successful bonding.
        PRINT_LOG("[INFO] Bonded\r\n\n");
        break;

    // Event raised when bonding failed
    case sl_bt_evt_sm_bonding_failed_id:
        // Update the application state to indicate neither bonding nor bonded.
        // ble_data.connections.bonding = false;
        // ble_data.connections.bonded = false;
        // Log a message indicating bonding failed.
        PRINT_LOG("[ERROR] Bonding failed\r\n\n");
        PRINT_LOG("--------------------------------------\r\n\n");
        sc = sl_bt_sm_delete_bondings();
        app_assert_status(sc);

        break;

    case sl_bt_evt_gatt_procedure_completed_id:
        /* if service discovery completed */
        if (ble_data.discovering_service)
        {
            ble_data.discovering_service = false;

            /* discover Temperature Measurement characteristic */
            PRINT_LOG("[INFO] discovering service success\r\n");
            sc = sl_bt_gatt_discover_characteristics_by_uuid(
                evt->data.evt_gatt_procedure_completed.connection,
                ble_data.HIDServiceHandle,
                sizeof(report_char),
                report_char);
            app_assert_status(sc);
            ble_data.discovering_characteristic = true;
        }

        /* if characteristic discovery completed */
        else if (ble_data.discovering_characteristic)
        {
            PRINT_LOG("[INFO] Found REPORT Characteristics that we want, enabling Notification \n\r");
            ble_data.discovering_characteristic = false;

            /* enable indications on the HID report characteristic */
            sc = sl_bt_gatt_set_characteristic_notification(
                evt->data.evt_gatt_procedure_completed.connection,
                ble_data.reportMapCharacteristicHandle,
                sl_bt_gatt_notification);
            app_assert_status(sc);
            ble_data.enabling_notification = true;
        }

        else if (ble_data.enabling_notification)
        {
            PRINT_LOG("[INFO] Notification enabled ! \n\r");
            ble_data.enabling_notification = false;
        }
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
                    PRINT_LOG("Notification for Report has been enabled by Client\n");
                    ble_data.ok_to_send_report_notification = 1;
                }
                else
                {
                    PRINT_LOG("Notification for Report has been disabled by Client\n");
                    ble_data.ok_to_send_report_notification = 0;
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

    // -------------------------------
    // This event is generated when an advertisement packet or a scan response
    // is received from a peripheral device
    case sl_bt_evt_scanner_legacy_advertisement_report_id:
        /* Exit event if max connection is reached */

        if (ble_data.number_of_connection == MAX_CONNECTIONS)
        {
            break;
        }

        /* Exit if device is in connection process (processing another scan
         * response),
         * or service, or characterstics discovery */
        if (ble_data.connecting || ble_data.enabling_notification || ble_data.discovering_service || ble_data.discovering_characteristic)
        {
            break;
        }

        // if address matcches and address type also matches
        bd_addr device_addr = SERVER_BT_ADDRESS;

        // PRINT_LOG("memcpy %d ", memcmp(evt->data.evt_scanner_scan_report.address.addr, device_addr.addr, sizeof(device_addr.addr)));
        // PRINT_LOG("Found Address :%02X %02X %02X %02X %02X %02X\n\r",
        //           evt->data.evt_scanner_scan_report.address.addr[0],
        //           evt->data.evt_scanner_scan_report.address.addr[1],
        //           evt->data.evt_scanner_scan_report.address.addr[2],
        //           evt->data.evt_scanner_scan_report.address.addr[3],
        //           evt->data.evt_scanner_scan_report.address.addr[4],
        //           evt->data.evt_scanner_scan_report.address.addr[5]);
        if (memcmp(evt->data.evt_scanner_scan_report.address.addr, device_addr.addr, sizeof(device_addr.addr)) == 0)
        {

            /* Max connection isn't reached, device is not in a connection process,
             * new HTM service is found.
             * Continue ...*/
            if (!hid_service_found(&(evt->data.evt_scanner_legacy_advertisement_report)))
            {
                PRINT_LOG("[ERROR] Device Address matched but no HID service found...\n\r");
                break;
            }

            PRINT_LOG("founded device\r\n");

            /* Exit event if the scan response is triggered by a device already in the
             * connection list. */
            if (found_device(evt->data.evt_scanner_legacy_advertisement_report.address, ble_data))
            {
                PRINT_LOG("[ERROR] Device Address matched but and it is already in the ble_data struct...\n\r");
                break;
            }

            sc = sl_bt_connection_open(evt->data.evt_scanner_scan_report.address,
                                       evt->data.evt_scanner_scan_report.address_type,
                                       sl_bt_gap_1m_phy,
                                       &ble_data.connectionHandle);
            app_assert_status(sc);
            ble_data.connecting = true;
            PRINT_LOG("[INFO] founded device\r\n");

            /* Update device list. If connection doesn't succeed (due to timeout) the
             * device will be removed from the list in connection closed event
             * handler*/
            ble_data.connections[ble_data.number_of_connection].device_address =
                evt->data.evt_scanner_scan_report.address;
            ble_data.connections[ble_data.number_of_connection].address_type =
                evt->data.evt_scanner_scan_report.address_type;
            ble_data.connections[ble_data.number_of_connection].connectionHandle = ble_data.connectionHandle;
            ble_data.connections[ble_data.number_of_connection].conn_role = CR_PERIPHERAL; // connection role
                                                                                           // of the remote
                                                                                           // device
            ble_data.connections[ble_data.number_of_connection].conn_state = CS_CONNECTING;

            /* Increment ble_data.number_of_connection */
            ble_data.number_of_connection++;
            char buf[100];
            snprintf(buf, sizeof(buf), "%d", ble_data.number_of_connection);
            display_string(buf, 110, 50);
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

        PRINT_LOG("Got service with service handle %lX , uuid %x %x\n\r",
                  evt->data.evt_gatt_service.service,
                  evt->data.evt_gatt_service.uuid.data[0],
                  evt->data.evt_gatt_service.uuid.data[1]);

        if (memcmp(evt->data.evt_gatt_service.uuid.data, service_uuid, sizeof(service_uuid)) == 0)
        {
            PRINT_LOG("Found the HID service, saving handle\n\r");
            // save service handle
            ble_data.HIDServiceHandle = evt->data.evt_gatt_service.service;
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
        // if (memcmp(evt->data.evt_gatt_service.uuid.data, report_char, sizeof(report_char)) == 0)
        // {
        PRINT_LOG("Found the Report Char, saving handle\n\r");
        // save service handle
        ble_data.reportMapCharacteristicHandle = evt->data.evt_gatt_characteristic.characteristic;
        // }
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
        // print what we got
        // PRINT_LOG("heahahah 1\n");
        if (evt->data.evt_gatt_characteristic_value.att_opcode == sl_bt_gatt_handle_value_notification)
        {
            // PRINT_LOG("heahahah 2\n");
            if (evt->data.evt_gatt_characteristic_value.characteristic == ble_data.reportMapCharacteristicHandle)
            {
                // PRINT_LOG("heahahah 3\n");

                // extract value sent by server from evt_gatt_characteristic_value data structure
                uint8_t *char_value = evt->data.evt_gatt_characteristic_value.value.data;
                memset(input_report_data, 0, sizeof(input_report_data));
                memcpy(input_report_data, char_value, 8);

                sc = sl_bt_gatt_server_notify_all(gattdb_report,
                                                  sizeof(input_report_data),
                                                  input_report_data);
                app_assert_status(sc);

                // PRINT_LOG("[INFO] got Key report %d %d %d %d %d %d %d %d\r\n", input_report_data[0],
                //           input_report_data[1],
                //           input_report_data[2],
                //           input_report_data[3],
                //           input_report_data[4],
                //           input_report_data[5],
                //           input_report_data[6],
                //           input_report_data[7]);
                // PRINT_LOG("[INFO] Key report was sent\r\n");
            }
        }

        break;

    default:
        break;

    } // end - switch
} // handle_ble_event()

// // after boot

// �    0:Info :handle_ble_event: Bluetooth stack booted !

//     0:Info :get_stack_version: Stack version: v7.1.2-b1685

//     0:Info :get_system_id: Local BT public device address: E8:E0:7E:62:CD:CB

//     0:Info :handle_ble_event:  MASTERRRR

// founded device
//     0:Info :handle_ble_event: [INFO] founded device

//     0:Info :handle_ble_event: [INFO] Connection opened

//     0:Info :handle_ble_event: CR_CENTRAL

//     0:Info :handle_ble_event: [INFO]  Max connection not reached. Re-start advertising in connectable mode.

//     0:Info :handle_ble_event: Connection parameters updated:
//     0:Info :handle_ble_event: Interval:  ms
//     0:Info :handle_ble_event: Latency: 0 (number of connection events)
//     0:Info :handle_ble_event: Timeout:  ms

//     0:Info :handle_ble_event: Connection parameters updated:
//     0:Info :handle_ble_event: Interval:  ms
//     0:Info :handle_ble_event: Latency: 0 (number of connection events)
//     0:Info :handle_ble_event: Timeout:  ms

//     0:Info :handle_ble_event: Got service with service handle 230030 , uuid 12 18

//     0:Info :handle_ble_event: Found the HID service, saving handle

//     0:Info :handle_ble_event: [INFO] discovering service success

//     0:Info :handle_ble_event: Found the Report Char, saving handle

//     0:Info :handle_ble_event: [INFO] Found REPORT Characteristics that we want, enabling Notification

//     0:Info :handle_ble_event: [INFO] Notification enabled !

//     0:Info :handle_ble_event: [INFO] Connection opened

//     0:Info :handle_ble_event: CR_PERIPHERAL

//     0:Info :handle_ble_event: [ERROR] Maximum number of allowed connections reached.

//     0:Info :handle_ble_event: [INFO] Stop scanning but and stop advertising.

// NEW CONNECTION ESTABLISHED
// Device ID .................: 6B:08:DD:4E:2C:EA
// Role ......................: central
// Handle ....................: 1
// Number of connected devices: 2
// Available connections .....: 0
//     0:Info :handle_ble_event: ble_data.connection 2

// --------------- LIST of CONNECTED DEVICES ----------------
// ==========================================================
// ADDRESS            ROLE          HANDLE        STATE
// ==========================================================
// E8:E0:7E:62:DC:FC  PERIPHARAL    2             CONNECTING
// 6B:08:DD:4E:2C:EA  CENTRAL       1             CONNECTED

//     0:Info :handle_ble_event: Connection parameters updated:
//     0:Info :handle_ble_event: Interval:  ms
//     0:Info :handle_ble_event: Latency: 0 (number of connection events)
//     0:Info :handle_ble_event: Timeout:  ms

//     0:Info :handle_ble_event: Something came

//     0:Info :handle_ble_event: Something came

//     0:Info :handle_ble_event: Notification for Report has been enabled by Client

//     0:Info :handle_ble_event: Connection parameters updated:
//     0:Info :handle_ble_event: Interval:  ms
//     0:Info :handle_ble_event: Latency: 0 (number of connection events)
//     0:Info :handle_ble_event: Timeout:  ms

// // after connect and disconnet phone
// 360000:Info :handle_ble_event: [INFO] Connection Closed

// Device 64:F3:63:78:4B:BB left the connection::0x1013

// --------------- LIST of CONNECTED DEVICES ----------------
// ==========================================================
// ADDRESS            ROLE          HANDLE        STATE
// ==========================================================
// E8:E0:7E:62:DC:FC  PERIPHARAL    2             CONNECTING

// Number of active connections ...: 1
// Available connections ..........: 1
// Scanning restarted.
// Advertising restarted in CONNECTABLE mode.
// 420000:Info :read_SI7021: Got the temprature from Si7021 sensor => 28 Celsius

// 420000:Info :handle_ble_event: [INFO] Connection opened

// 420000:Info :handle_ble_event: CR_PERIPHERAL

// 420000:Info :handle_ble_event: [ERROR] Maximum number of allowed connections reached.

// 420000:Info :handle_ble_event: [INFO] Stop scanning but and stop advertising.

// 420000:Info :handle_ble_event: Connection parameters updated:
// 420000:Info :handle_ble_event: Interval:  ms
// 420000:Info :handle_ble_event: Latency: 0 (number of connection events)
// 420000:Info :handle_ble_event: Timeout:  ms

// 420000:Info :handle_ble_event: Something came

// 420000:Info :handle_ble_event: Something came

// 420000:Info :handle_ble_event: Notification for Report has been enabled by Client

// 420000:Info :handle_ble_event: Connection parameters updated:
// 420000:Info :handle_ble_event: Interval:  ms
// 420000:Info :handle_ble_event: Latency: 0 (number of connection events)
// 420000:Info :handle_ble_event: Timeout:  ms
