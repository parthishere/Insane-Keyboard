#ifndef __WS2812_H__
#define __WS2812_H__

#include <stdint.h>
#include "em_ldma.h"

void initLdma(uint16_t *buffer, int buffer_size);


#endif