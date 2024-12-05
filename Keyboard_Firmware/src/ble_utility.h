#ifndef __BLE_UTILITY_H__
#define __BLE_UTILITY_H__



#include "sl_bt_api.h" // Silicon Labs Bluetooth API for BLE operations
#include "gatt_db.h"   // GATT database for BLE services and characteristics
#include "app_assert.h"

#if (DEVICE_IS_BLE_MASTER == 1)
#define MAX_CONNECTIONS 2
#else
#define MAX_CONNECTIONS 1
#endif


// For your Bluetooth Client implementations, starting with A7,
// set this #define to the bd_addr of the Gecko that will be your Server.
// These values are from one of my Geckos, to serve as an example for you:
//                   bd_addr  [0]   [1]   [2]   [3]   [4]   [5] <- array indices
#if BLE_PAIR == 1
#define MASTER_BT_ADDRESS {{ 0xCB, 0xCD, 0x62, 0x7E, 0xE0, 0xE8 }}
#define SERVER_BT_ADDRESS {{ 0xFC, 0xDC, 0x62, 0x7E, 0xE0, 0xE8 }}
#elif BLE_PAIR == 2
#define MASTER_BT_ADDRESS {{ 0xCB, 0xCD, 0x62, 0x7E, 0xE0, 0xE8 }}
#define SERVER_BT_ADDRESS {{ 0xFC, 0xDC, 0x62, 0x7E, 0xE0, 0xE8 }}
#elif BLE_PAIR == 3
#define MASTER_BT_ADDRESS {{ 0xCB, 0xCD, 0x62, 0x7E, 0xE0, 0xE8 }}
#define SERVER_BT_ADDRESS {{ 0xFC, 0xDC, 0x62, 0x7E, 0xE0, 0xE8 }}
#else
#define MASTER_BT_ADDRESS {{ 0xCB, 0xCD, 0x62, 0x7E, 0xE0, 0xE8 }}
#define SERVER_BT_ADDRESS {{ 0xFC, 0xDC, 0x62, 0x7E, 0xE0, 0xE8 }}
#endif

#define __HID_SERVICE_UUID {0x12, 0x18};
#define __HID_REPORT_CHARACTERISTIC_UUID {0x4d, 0x2a};

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
  // Connection States (CS)
  CS_CONNECTED,
  CS_CONNECTING,
  CS_CLOSED
} conn_state_t;


typedef enum {
  scanning,
  opening,
  discover_services,
  discover_characteristics,
  enable_indication,
  running
} conn_state;

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
  // bool bonded;
} connections_t;

// Structure definition for BLE data management.
// This structure includes both common and server-specific BLE attributes.
typedef struct
{
  uint8_t advertisingSetHandle;
  uint8_t connectionHandle;
  uint8_t closedHandle;

  uint32_t HIDServiceHandle;              // Service handle for the thermometer service.
  uint32_t reportMapCharacteristicHandle; // Characteristic handle for thermometer measurement.

  connections_t connections[MAX_CONNECTIONS];

  int number_of_connection;

  bool connecting;
  bool enabling_notification;
  bool discovering_service;
  bool discovering_characteristic;

  bool ok_to_send_report_notification;
  bool indication_in_flight;
  bool bonded;
} ble_data_struct_t;

void get_system_id(void);
void get_stack_version(sl_bt_msg_t *evt);
void print_bd_addr(bd_addr bd_address);
uint8_t get_dev_index(uint8_t handle, ble_data_struct_t ble_data);
bool hid_service_found(struct sl_bt_evt_scanner_legacy_advertisement_report_s *pResp);
bool found_device(bd_addr bd_address, ble_data_struct_t ble_data);


void init_advertizement(ble_data_struct_t *ble_data);
void advertizement(ble_data_struct_t *ble_data);
void scan();
void scan_init();
void external_signal_evtIOEXPANDER();

#endif
