#include "spi.h"

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"




void transmitBytes(uint8_t *t_data, int size_in_bytes)
{
    SPIDRV_MTransmitB(sl_spidrv_usart_displayy_handle, t_data, size_in_bytes);
}

void receiveBytes(uint8_t *r_data, int size_in_bytes)
{
    SPIDRV_MReceiveB(sl_spidrv_usart_displayy_handle, r_data, size_in_bytes);
}
