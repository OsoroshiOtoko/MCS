
#include "LEDs.h"
#include "gpio.h"

void LEDs_init(void)
{
	
	 GPIO_InitTypeDef GPIO_InitStruct = {0};
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED_Green_Pin|LED_Orange_Pin|LED_Red_Pin|LED_Blue_Pin, GPIO_PIN_RESET);
	
	  /*Configure GPIO pins : PDPin PDPin PDPin PDPin */
   GPIO_InitStruct.Pin = LED_Green_Pin|LED_Orange_Pin|LED_Red_Pin|LED_Blue_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_PULLDOWN;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
void leds_set(leds_color_e_t color, leds_state_e_t state)
{
	GPIO_PinState pin_state = GPIO_PIN_RESET;
	
	switch (color)
	{
		case GREEN:
		{
			HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, pin_state);
			break;
		}
		case ORANGE:
		{
			HAL_GPIO_WritePin(LED_Orange_GPIO_Port, LED_Orange_Pin, pin_state);
			break;
		}
		case RED:
		{
			HAL_GPIO_WritePin(LED_Red_GPIO_Port, LED_Red_Pin, pin_state);
			break;
		}
		case BLUE:
		{
			HAL_GPIO_WritePin(LED_Blue_GPIO_Port, LED_Blue_Pin, pin_state);
			break;
		}
				case ALL:
		{
			HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, pin_state);
			HAL_GPIO_WritePin(LED_Orange_GPIO_Port, LED_Orange_Pin, pin_state);
			HAL_GPIO_WritePin(LED_Red_GPIO_Port, LED_Red_Pin, pin_state);
			HAL_GPIO_WritePin(LED_Blue_GPIO_Port, LED_Blue_Pin, pin_state);
			break;
		}
	}
}
