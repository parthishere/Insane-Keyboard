#ifndef __SPI_H__
#define __SPI_H__

#include "spidrv.h"
#include "sl_spidrv_instances.h"
#include <stdint.h>

void transmitBytes(uint8_t *t_data, int size_in_bytes);
void receiveBytes(uint8_t *r_data, int size_in_bytes);

#endif // !__SPI_H__
