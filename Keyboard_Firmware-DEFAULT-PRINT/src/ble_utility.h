#ifndef __BLE_UTILITY_H__
#define __BLE_UTILITY_H__



#include "sl_bt_api.h" // Silicon Labs Bluetooth API for BLE operations
#include "gatt_db.h"   // GATT database for BLE services and characteristics
#include "app_assert.h"

#if (DEVICE_IS_BLE_MASTER == 1)
#define MAX_CONNECTIONS 3
#else
#define MAX_CONNECTIONS 1
#endif



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


typedef enum
{
  SCANNING,
  OPENING,
  CONNECTING,
  CONNECTED,
  DISCOVER_SERVICE,
  DISCOVER_CHAR,
  ENABLING_INDICATION,
  RUNNING,
  CLOSED
} conn_state_t;

typedef enum
{
  // Connection Roles (CR)
  CR_PERIPHERAL, // GATT database server
  CR_CENTRAL // GATT database client
} conn_role_t;

typedef struct
{
  bd_addr device_address;
  uint8_t address_type;
  conn_role_t conn_role;
  conn_state_t conn_state;
  uint8_t connectionHandle;


} connections_t;

// Structure definition for BLE data management.
// This structure includes both common and server-specific BLE attributes.
typedef struct
{
  bd_addr myAddress;     // Device's Bluetooth address, unique identifier for BLE devices.
  uint8_t myAddressType; // Type of Bluetooth address being used (public or random).

  uint8_t advertisingSetHandle;
  uint8_t connectionHandle;

  uint32_t HIDServiceHandle;              // Service handle for the thermometer service.
  uint32_t reportMapCharacteristicHandle; // Characteristic handle for thermometer measurement.

  connections_t connections[MAX_CONNECTIONS];

  int number_of_connection;

  bool connecting;
  bool enabling_notification;
  bool discovering_service;
  bool discovering_characteristic;
  bool indication_in_flight; // True if an indication is currently being sent.
  bool ok_to_send_report_notification;
} ble_data_struct_t;

void advertizement(ble_data_struct_t *ble_data);
void scan();

#endif
