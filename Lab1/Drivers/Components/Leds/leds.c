#include "leds.h"
#include "gpio.h"

void leds_init(void)
{
	leds_set(leds_color_e_t.ALL, leds_state_e_t.OFF);
}

void leds_set(leds_color_e_t color, leds_state_e_t state)
{
	switch (state)
	{
	    case leds_state_e_t.ON:
	        switch (color)
	        {
	            case leds_color_e_t.GREEN: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET); break;
	            case leds_color_e_t.ORANGE: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Orange_Pin, GPIO_PIN_SET); break;
	            case leds_color_e_t.RED: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Red_Pin, GPIO_PIN_SET); break;
	            case leds_color_e_t.BLUE: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Blue_Pin, GPIO_PIN_SET); break;
	            case leds_color_e_t.ALL:
		            HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET);
	                HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Orange_Pin, GPIO_PIN_SET);
	                HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Red_Pin, GPIO_PIN_SET);
	                HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Blue_Pin, GPIO_PIN_SET);
	                break;
	        }
	        break;

	    case leds_state_e_t.OFF:
		    switch (color)
			{
			    case leds_color_e_t.GREEN: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET); break;
			    case leds_color_e_t.ORANGE: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Orange_Pin, GPIO_PIN_RESET); break;
			    case leds_color_e_t.RED: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Red_Pin, GPIO_PIN_RESET); break;
			    case leds_color_e_t.BLUE: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Blue_Pin, GPIO_PIN_RESET); break;
			    case leds_color_e_t.ALL:
				    HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET);
			        HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Orange_Pin, GPIO_PIN_RESET);
			        HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Red_Pin, GPIO_PIN_RESET);
			        HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Blue_Pin, GPIO_PIN_RESET);
			        break;
			 }
			 break;
	}
}
