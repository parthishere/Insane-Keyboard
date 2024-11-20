#include "spi.h"

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"



void receiveBytes(uint8_t *r_data, int size_in_bytes)
{
    SPIDRV_MReceiveB(sl_spidrv_usart_displayy_handle, r_data, size_in_bytes);
}

void DEV_SPI_WriteByte(uint8_t value)
{
    SPIDRV_MTransmitB(sl_spidrv_usart_displayy_handle, &value, 1);
}

void DEV_SPI_Write_nByte(uint8_t *value, int len)
{
    SPIDRV_MTransmitB(sl_spidrv_usart_displayy_handle, value, len);
}


int DEV_Module_Init(void)
{
    gpio_Set_Display_DC(0);
    gpio_Set_Display_Reset(1);
    return 0;
}

void DEV_Module_Exit(void)
{
    gpio_Set_Display_DC(0);
    gpio_Set_Display_Reset(0);
}
