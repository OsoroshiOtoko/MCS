#ifndef LEDs_H

#define LEDs_H

typedef enum
{
OFF = 0,
ON = 1
}leds_state_e_t;

typedef enum
{
  GREEN = 0,
  ORANGE,
	RED,
	BLUE,
	ALL
}leds_color_e_t;

void LEDs_init(void);
void leds_set(leds_color_e_t color, leds_state_e_t state);

#endif //LEDs_H