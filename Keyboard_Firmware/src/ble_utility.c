#include "src/ble_utility.h"


#define SERVER_PASSIVE_SCANNING 0

// Value * 0.625 = 80 * 0.625 => 50ms
#define SERVER_SCANNING_INTERVAL 0x50

// Time = Value x 0.625 ms => time = 25ms
#define SERVER_SCANNING_WINDOW 0x28

// Advertising interval for BLE in units of 0.625ms.
// ADV_INTERVAL of 400 translates to 250ms (400 * 0.625ms = 250ms).
#define ADV_INTERVAL 160

static sl_status_t sc;


void advertizement(ble_data_struct_t *ble_data){
        // Create an advertising set for BLE advertising
        sc = sl_bt_advertiser_create_set(&ble_data->advertisingSetHandle);
        app_assert_status(sc);

        sc = sl_bt_legacy_advertiser_generate_data(ble_data->advertisingSetHandle,
                                                   sl_bt_advertiser_general_discoverable);
        app_assert_status(sc);

        // Configure advertising timing parameters
        sc = sl_bt_advertiser_set_timing(
            ble_data->advertisingSetHandle, // The advertising set handle
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
            ble_data->advertisingSetHandle,        // The advertising set handle
            sl_bt_legacy_advertiser_connectable); // Connectable and scannable advertising
        app_assert_status(sc);
}


void scan(){
    sc = sl_bt_connection_set_default_parameters(CON_INTERVAL, CON_INTERVAL, CON_LATENCY, CON_TIMEOUT, 0, MAX_CE_LEN);
    app_assert_status(sc);

    sc = sl_bt_scanner_start(sl_bt_gap_phy_1m, sl_bt_scanner_discover_observation);
    app_assert_status(sc);
}


void external_signal_evtENCODER_SW(){

}

void external_signal_evtIOEXPANDER(){
    
}

void external_signal_evtENCODER_ROTATE(){
    
}
