#ifndef __SPI_H__
#define __SPI_H__

#include "spidrv.h"
#include "sl_spidrv_instances.h"
#include <stdint.h>

void receiveBytes(uint8_t *r_data, int size_in_bytes);

void DEV_SPI_WriteByte(uint8_t value);
void DEV_SPI_Write_nByte(uint8_t *value, int len);

int DEV_Module_Init(void);
void DEV_Module_Exit(void);

#endif // !__SPI_H__
