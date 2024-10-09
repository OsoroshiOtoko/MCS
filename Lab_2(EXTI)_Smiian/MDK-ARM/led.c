#include "led.h"
#include "gpio.h"

void led_init(void)
{
    MX_GPIO_Init();
}

void led_set(led_color_e_t color, led_state_e_t state)
{
    GPIO_PinState pin_state = GPIO_PIN_RESET;
    if (state != 0){
       pin_state = GPIO_PIN_SET;
    }
    switch (color)
    {
        case (RED):
        {
            HAL_GPIO_WritePin(LED_Red_GPIO_Port, LED_Red_Pin, pin_state);
            break;
        }
        case (BLUE):
        {
            HAL_GPIO_WritePin(LED_Blue_GPIO_Port, LED_Blue_Pin, pin_state);
            break;
        }
        case (GREEN):
        {
            HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, pin_state);
            break;
        }
        case (ORANGE):
        {
            HAL_GPIO_WritePin(LED_Orange_GPIO_Port, LED_Orange_Pin, pin_state);
            break;
        }
        case (ALL):
        {
            HAL_GPIO_WritePin(LED_Red_GPIO_Port, LED_Orange_Pin, pin_state);
            HAL_GPIO_WritePin(LED_Blue_GPIO_Port, LED_Blue_Pin, pin_state);
            HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, pin_state);
            HAL_GPIO_WritePin(LED_Orange_GPIO_Port, LED_Orange_Pin, pin_state);
            break;
        }
    }
}