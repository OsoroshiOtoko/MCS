#ifndef LEDS_H
#define LEDS_H

typedef enum
{
	OFF = 0,
	ON = 1
}leds_state_e_t;

typedef enum
{
	GREEN,
	ORANGE,
	RED,
	BLUE,
	ALL
}leds_color_e_t;

void leds_init(void);
void leds_set(leds_color_e_t color, leds_state_e_t state);

#endif // LEDS_H
