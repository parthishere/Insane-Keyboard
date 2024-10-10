#include "spi.h"

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"




void transmitBytes(uint8_t *t_data, int size_in_bytes)
{
//    selectRFID();
//    SPIDRV_MTransmitB(sl_spidrv_RFID_handle, t_data, size_in_bytes);
//    deselectRFID();
}

void receiveBytes(uint8_t *r_data, int size_in_bytes)
{
//    selectRFID();
//    SPIDRV_MReceiveB(sl_spidrv_RFID_handle, r_data, size_in_bytes);
//    deselectRFID();
}
