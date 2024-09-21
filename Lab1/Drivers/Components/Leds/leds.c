#include "leds.h"
#include "gpio.h"

void leds_init(void)
{
	leds_set(ALL, OFF);
}

void leds_set(leds_color_e_t color, leds_state_e_t state)
{
	switch (state)
	{
	    case ON:
	        switch (color)
	        {
	            case GREEN: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET); break;
	            case ORANGE: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Orange_Pin, GPIO_PIN_SET); break;
	            case RED: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Red_Pin, GPIO_PIN_SET); break;
	            case BLUE: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Blue_Pin, GPIO_PIN_SET); break;
	            case ALL:
		            HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET);
	                HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Orange_Pin, GPIO_PIN_SET);
	                HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Red_Pin, GPIO_PIN_SET);
	                HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Blue_Pin, GPIO_PIN_SET);
	                break;
	        }
	        break;

	    case OFF:
		    switch (color)
			{
			    case GREEN: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET); break;
			    case ORANGE: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Orange_Pin, GPIO_PIN_RESET); break;
			    case RED: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Red_Pin, GPIO_PIN_RESET); break;
			    case BLUE: HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Blue_Pin, GPIO_PIN_RESET); break;
			    case ALL:
				    HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET);
			        HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Orange_Pin, GPIO_PIN_RESET);
			        HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Red_Pin, GPIO_PIN_RESET);
			        HAL_GPIO_WritePin(LED_OnBoard_GPIO_Port, LED_Blue_Pin, GPIO_PIN_RESET);
			        break;
			 }
			 break;
	}
}
