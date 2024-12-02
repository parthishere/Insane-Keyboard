#include "src/ble_utility.h"

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"



static sl_status_t sc;

static uint8_t service_uuid[2] = __HID_SERVICE_UUID;

static const char string_central[] = "CENTRAL";
static const char string_peripheral[] = "PERIPHERAL";



const char * get_conn_state(uint8_t state)
{
  switch (state) {
    case CS_CONNECTED:
      return "CONNECTED";
    case CS_CONNECTING:
      return "CONNECTING";
    case CS_CLOSED:
      return "CLOSED";
    default:
      return "UNKNOWN";
  }
}

/* returns true if the remote device address is found in the list of connected
 *   device list */
bool found_device(bd_addr bd_address, ble_data_struct_t ble_data)
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
                if (!memcmp(service_uuid, &(pResp->data.data[j]), sizeof(service_uuid)))
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

uint8_t get_dev_index(uint8_t handle, ble_data_struct_t ble_data)
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

/* print bd_addr */
void print_bd_addr(bd_addr bd_address)
{
  int i;

  for (i = 5; i >= 0; i--) {
    app_log("%02X", bd_address.addr[i]);

    if (i > 0) {
      app_log(":");
    }
  }
}

void sl_app_log_stats(ble_data_struct_t ble_data)
{
  app_log("\r\n--------------- LIST of CONNECTED DEVICES ----------------\r\n");
  app_log("==========================================================\r\n");
  static bool print_header = true;

  // print header
  if (print_header == true) {
    app_log("ADDRESS            ROLE          HANDLE        STATE\r\n");
  }
  app_log("==========================================================\r\n");

  int i;
  for (i = 0; i < ble_data.number_of_connection; i++) {
    print_bd_addr(ble_data.connections[i].device_address);
  }
  app_log("\r\n");
}


void get_stack_version(sl_bt_msg_t *evt)
{
  app_log("Stack version: v%d.%d.%d-b%d\r\n",
          evt->data.evt_system_boot.major,
          evt->data.evt_system_boot.minor,
          evt->data.evt_system_boot.patch,
          evt->data.evt_system_boot.build);
}


void get_system_id(void)
{
  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;
  uint8_t system_id[8];

  // Extract unique ID from BT Address.
  sc = sl_bt_system_get_identity_address(&address, &address_type);
  app_assert_status(sc);

  // Pad and reverse unique ID to get System ID.
  system_id[0] = address.addr[5];
  system_id[1] = address.addr[4];
  system_id[2] = address.addr[3];
  system_id[3] = 0xFF;
  system_id[4] = 0xFE;
  system_id[5] = address.addr[2];
  system_id[6] = address.addr[1];
  system_id[7] = address.addr[0];

  sc = sl_bt_gatt_server_write_attribute_value(gattdb_system_id,
                                               0,
                                               sizeof(system_id),
                                               system_id);
  app_assert_status(sc);

  app_log("Local BT %s address: %02X:%02X:%02X:%02X:%02X:%02X\r\n",
          address_type ? "static random" : "public device",
          address.addr[5],
          address.addr[4],
          address.addr[3],
          address.addr[2],
          address.addr[1],
          address.addr[0]);
}


void init_advertizement(ble_data_struct_t *ble_data)
{
    
}

void advertizement(ble_data_struct_t *ble_data)
{

    
}


void scan_init(){
    sc = sl_bt_connection_set_default_parameters(CON_INTERVAL, CON_INTERVAL, CON_LATENCY, CON_TIMEOUT, 0, MAX_CE_LEN);
    app_assert_status(sc);

    sc = sl_bt_scanner_set_parameters(sl_bt_scanner_scan_mode_passive,
                                    20,
                                    10);
    app_assert_status(sc);
}

void scan()
{
    sc = sl_bt_scanner_start(sl_bt_gap_phy_1m, sl_bt_scanner_discover_observation);
    app_assert_status(sc);
}

void external_signal_evtENCODER_SW()
{
}

void external_signal_evtIOEXPANDER()
{
}

void external_signal_evtENCODER_ROTATE()
{
}


