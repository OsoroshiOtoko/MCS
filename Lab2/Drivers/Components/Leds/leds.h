#ifndef LEDS_H
#define LEDS_H

#include "stdint.h"

#define LED_POWER_MAX (uint8_t)100
#define LED_POWER_MIN (uint8_t)0

typedef enum
{
	GREEN,
	ORANGE,
	RED,
	BLUE,
	ALL
}leds_color_e_t;


void leds_PWM_init(void);
void leds_PWM_set(leds_color_e_t color, uint8_t power);

void leds_PWM_DMA_init(leds_color_e_t color, const uint32_t *power_arr, uint16_t size);


#endif // LEDS_H
