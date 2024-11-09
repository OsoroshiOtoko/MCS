#include "leds.h"

#include "main.h"
#include "dma.h"
#include "tim.h"


void leds_PWM_init(void)
{
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_ALL, 0);

	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_ALL);
}

void leds_PWM_DMA_init(leds_color_e_t color, const uint32_t *power_arr, uint16_t size)
{
	switch (color)
	{
		case GREEN:
		{
			HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_1, power_arr, size);
		    break;
		}
		case ORANGE:
		{
		    HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_2, power_arr, size);
		    break;
		}
		case RED:
		{
		    HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_3, power_arr, size);
		    break;
		}
		case BLUE:
		{
		    HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_4, power_arr, size);
		    break;
		}
		case ALL:
		{
		    HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_ALL, power_arr, size);
		    break;
		}
	}
}

void leds_PWM_set(leds_color_e_t color, uint8_t power)
{
	switch (color)
	{
		case GREEN:
		{
	    	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, power);
	    	break;
		}
	    case ORANGE:
	    {
	    	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, power);
	    	break;
	    }
	    case RED:
	    {
	    	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, power);
	    	break;
	    }
	    case BLUE:
	    {
	    	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, power);
	    	break;
	    }
	    case ALL:
	    {
	    	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_ALL, power);
	    	break;
	    }
	}
}
