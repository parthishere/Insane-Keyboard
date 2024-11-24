#ifndef __WS2812_H__
#define __WS2812_H__

#include <stdint.h>
#include "em_ldma.h"
#include "math.h"

void initLdma(uint16_t *buffer, int buffer_size);
uint8_t rainbow_effect_right();
uint8_t rainbow_effect_left();
void Set_Brightness (int brightness);
void WS2812_Send(void);
void Set_LED (int LEDnum, int Red, int Green, int Blue);

#endif