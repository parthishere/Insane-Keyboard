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

uint8_t __HID_SERVICE_UUID[2] = {0x12, 0x18};
uint8_t __HID_REPORT_CHARACTERISTIC_UUID[2] = {0x4b, 0x2a};

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"

// System ID length for BLE devices, typically 8 bytes.
#define SYSTEM_ID_LEN 8

// Specific bytes within the System ID to indicate the Bluetooth SIG-defined format for public device addresses.
// These are constants used to fill the middle of the System ID byte array.
#define SYSTEM_ID3 0xFF
#define SYSTEM_ID4 0xFE

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

static uint8_t input_report_data[] = {0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t actual_key = KEY_A;

uint8_t dev_index;
static bool scanning = false;

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
static sl_status_t sc;            // Status code for Silicon Labs API functions
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
    // Events common to both GATT Servers and GATT Clients
    // ******************************************************
    // --------------------------------------------------------
    // --------------------------------------------------------
    // System boot event: Initialize BLE settings on device boot-up
    case sl_bt_evt_system_boot_id:

        // Log the version of the Bluetooth stack
        PRINT_LOG("[INFO] Bluetooth stack booted: v%d.%d.%d-b%d\n\r",
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
        PRINT_LOG("[INFO] Bluetooth %s address: %02X:%02X:%02X:%02X:%02X:%02X\n\r",
                  ble_data.myAddressType ? "static random" : "public device",
                  ble_data.myAddress.addr[0],
                  ble_data.myAddress.addr[ONE],
                  ble_data.myAddress.addr[TWO],
                  ble_data.myAddress.addr[THREE],
                  ble_data.myAddress.addr[FOUR],
                  ble_data.myAddress.addr[FIVE]);

#if (DEVICE_IS_BLE_MASTER == 1)
        scan_init();
        scan();
#endif
        init_advertizement(&ble_data);
        advertizement(&ble_data);
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
        // our master device is gatt client for that is CR_CENTRAL
        if (evt->data.evt_connection_opened.master == CR_CENTRAL)
        {
            // Device role: GATT Data base client
            /* Start discovering the remote GATT database */
            PRINT_LOG("CR_CENTRAL\n\r");
            sc = sl_bt_gatt_discover_primary_services_by_uuid(
                evt->data.evt_connection_opened.connection,
                sizeof(__HID_SERVICE_UUID),
                __HID_SERVICE_UUID);
            app_assert_status(sc);

            ble_data.discovering_service = true;

            /* connection process completed. */
            ble_data.connecting = false;

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

            sc = sl_bt_sm_increase_security(ble_data.connectionHandle);
            app_assert_status(sc);
        }

        // Update device connection state. common for both master and slave roles
        ble_data.connections[ble_data.number_of_connection - 1].conn_state = CONNECTED;

#if (DEVICE_IS_BLE_MASTER == 1)
        // /* Advertising stops when connection is opened. Re-start advertising */
        if (ble_data.number_of_connection == MAX_CONNECTIONS)
        {
            PRINT_LOG("[ERROR] Maximum number of allowed connections reached.\r\n");
            PRINT_LOG("[INFO] Stop scanning but continue advertising in non-connectable mode.\r\n");

            sc = sl_bt_scanner_stop();
            app_assert_status(sc);
        }

      

#endif

        break;

    // Handle the event when a BLE connection is closed
    case sl_bt_evt_connection_closed_id:
        // Log the closure of the connection
        PRINT_LOG("[INFO] Connection Closed\n\r");

        // Reset connection-related flags as the connection is now closed, reset flags
        ble_data.connections[ble_data.number_of_connection].connectionHandle = 0; // Reset the connection handle
        ble_data.indication_in_flight = false;                                    // No longer sending indications

        ble_data.number_of_connection--;

        uint8_t i;
        for (i = dev_index; i < ble_data.number_of_connection - 1; i++)
        {
            ble_data.connections[i] = ble_data.connections[i + 1];
        }

        if (ble_data.number_of_connection > 0)
        {
            ble_data.number_of_connection--;
        }

#if (DEVICE_IS_BLE_MASTER == 1)
        // scan();
#endif
        sc = sl_bt_legacy_advertiser_generate_data(advertising_set_handle,
                                                 sl_bt_advertiser_general_discoverable);
        app_assert_status(sc);

        advertizement(&ble_data);

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
        if (((evt->data.evt_system_external_signal.extsignals - evtENCODER_SW) == 0x00) && (ble_data.ok_to_send_report_notification))
        {
            // start scanning, send signal to main
            memset(input_report_data, 0, sizeof(input_report_data));

            input_report_data[MODIFIER_INDEX] = 0;
            input_report_data[DATA0_INDEX] = actual_key;

            sc = sl_bt_gatt_server_notify_all(gattdb_report,
                                              sizeof(input_report_data),
                                              input_report_data);
            app_assert_status(sc);
            PRINT_LOG("[INFO] Key report was sent\r\n");
        }

        if (((evt->data.evt_system_external_signal.extsignals - evtIOEXPANDER_COL) == 0x00) || ((evt->data.evt_system_external_signal.extsignals - evtENCODER_ROTATE) == 0x00))
        {
            //            LOG_INFO("Temp sensor\r\n");
        }

        if (((evt->data.evt_system_external_signal.extsignals - evtIOEXPANDER_ROW) == 0x00))
        {
            //            LOG_INFO("Temp sensor\r\n");
        }

        if (((evt->data.evt_system_external_signal.extsignals - evtLETIMER0_UF) == 0x00))
        {
            read_SI7021();
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
                sizeof(__HID_REPORT_CHARACTERISTIC_UUID),
                __HID_REPORT_CHARACTERISTIC_UUID);
            app_assert_status(sc);
            ble_data.discovering_characteristic = true;
        }

        /* if characteristic discovery completed */
        else if (ble_data.discovering_characteristic)
        {
            ble_data.discovering_characteristic = false;

            /* enable indications on the HID report characteristic */
            sc = sl_bt_gatt_set_characteristic_notification(
                evt->data.evt_gatt_procedure_completed.connection,
                ble_data.reportMapCharacteristicHandle,
                sl_bt_gatt_indication);
            app_assert_status(sc);
            ble_data.enabling_notification = true;
        }

        else if (ble_data.enabling_notification)
        {
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
        if (evt->data.evt_scanner_scan_report.packet_type == 0)
        {

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

                /* Exit event if the scan response is triggered by a device already in the
                 * connection list. */
                if (found_device(evt->data.evt_scanner_legacy_advertisement_report.address))
                {
                    PRINT_LOG("[ERROR] Device Address matched but and it is already in the ble_data struct...\n\r");
                    break;
                }

                sc = sl_bt_scanner_stop();
                app_assert_status(sc);

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
                ble_data.connections[ble_data.number_of_connection].conn_state = CONNECTING;

                /* Increment ble_data.number_of_connection */
                ble_data.number_of_connection++;
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

        PRINT_LOG("Got service with service handle %lX , uuid %x %x\n\r",
                  evt->data.evt_gatt_service.service,
                  evt->data.evt_gatt_service.uuid.data[0],
                  evt->data.evt_gatt_service.uuid.data[1]);
        if (memcmp(evt->data.evt_gatt_service.uuid.data, __HID_SERVICE_UUID, sizeof(__HID_SERVICE_UUID)) == 0)
        {
            PRINT_LOG("Found the Temperature service, saving handle\n\r");
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

        PRINT_LOG("Got characteristic with char handle %X , uuid %x %x\n\r",
                  evt->data.evt_gatt_characteristic.characteristic,
                  evt->data.evt_gatt_characteristic.uuid.data[0],
                  evt->data.evt_gatt_characteristic.uuid.data[1]);

        // Check for the characteristic uuid
        if (memcmp(evt->data.evt_gatt_characteristic.uuid.data, __HID_REPORT_CHARACTERISTIC_UUID, sizeof(__HID_REPORT_CHARACTERISTIC_UUID)) == 0)
        {
            PRINT_LOG("[INFO] Found REPORT Characteristics that we want, enabling Indication \n\r");
            // we found the service we want

            // save handle
            ble_data.reportMapCharacteristicHandle = evt->data.evt_gatt_characteristic.characteristic;
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
        // print what we got
        if (evt->data.evt_gatt_characteristic_value.characteristic == ble_data.reportMapCharacteristicHandle)
        {

            // extract value sent by server from evt_gatt_characteristic_value data structure
            uint8_t *char_value = &(evt->data.evt_gatt_characteristic_value.value.data[0]);
            PRINT_LOG("Temperature Data from Server: %s\n\r", char_value);
        }

        break;

    default:
        break;

    } // end - switch
} // handle_ble_event()

/* returns true if the remote device address is found in the list of connected
 *   device list */
bool found_device(bd_addr bd_address)
{
    int i;

    for (i = 0; i < ble_data.number_of_connection; i++)
    {
        if (memcmp(&ble_data.connections[i].device_address, &bd_address, sizeof(bd_addr)) == 0)
        {
            return true; // Found
        }
    }

    return false; // Not found
}

bool hid_service_found(struct sl_bt_evt_scanner_legacy_advertisement_report_s *pResp)
{
    // decoding advertising
    int i = 0, j;
    int adv_len;
    int adv_type;

    while (i < pResp->data.len - 1)
    {
        adv_len = pResp->data.data[i];
        adv_type = pResp->data.data[i + 1];

        /* type 0x02 = Incomplete List of 16-bit Service Class UUIDs
         * type 0x03 = Complete List of 16-bit Service Class UUIDs */
        if ((adv_type == 0x02) || (adv_type == 0x03))
        {
            // Look through all the UUIDs looking for HTM service
            j = i + 2; // j holds the index of the first data
            do
            {
                if (!memcmp(__HID_SERVICE_UUID, &(pResp->data.data[j]), sizeof(__HID_SERVICE_UUID)))
                {
                    return true;
                }
                j = j + 2;
            } while (j < i + adv_len);
        }
        i = i + adv_len + 1;
    }
    return false;
}

uint8_t get_dev_index(uint8_t handle)
{
    uint8_t index;

    for (index = 0; index < ble_data.number_of_connection; index++)
    {
        if (ble_data.connections[index].connectionHandle == handle)
        {
            return index;
        }
    }
    return 0xFF;
}

void app_log_stats()
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

    int i;
    for (i = 0; i < ble_data.number_of_connection; i++)
    {
        // Log the Bluetooth address of the device
        //        PRINT_LOG("[INFO] Bluetooth %s address: %02X:%02X:%02X:%02X:%02X:%02X\n\r",
        //                  ble_data.connections[i].device_type ? "static random" : "public device",
        //                  ble_data.connections[i].device_address.addr[0],
        //                  ble_data.connections[i].device_address.addr[ONE],
        //                  ble_data.connections[i].device_address.addr[TWO],
        //                  ble_data.connections[i].device_address.addr[THREE],
        //                  ble_data.connections[i].device_address.addr[FOUR],
        //                  ble_dataconnections[i].device_address.addr[FIVE]);
        //        print_bd_addr(ble_data.);
        app_log("  %-14s%-14d%-10s\r\n",
                (ble_data.connections[i].conn_role == 0) ? "PERIPH" : "CENTRAL",
                ble_data.connections[i].connectionHandle,
                get_conn_state(ble_data.connections[i].conn_state));
    }
    app_log("\r\n");
}

void start_scanning()
{
    scanning = true;
}

void stop_scanning()
{
    scanning = false;
}

bool get_scanning()
{
    return scanning;
}
