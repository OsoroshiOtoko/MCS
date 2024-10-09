#ifndef LED_H
#define LED_H

typedef enum
{
    OFF = 0,
    ON  = 1
}led_state_e_t;

typedef enum
{
    RED,
    BLUE,
    GREEN,
    ORANGE,
    ALL
}led_color_e_t;

/*typedef struct
{
    led_color_e_t color;
    led_state_e_t state;
}led_s_t;*/

void led_init(void);
void led_set(led_color_e_t color, led_state_e_t state);

#endif //LED_H