/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdint.h"
#include "leds.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum
{
	FORWARD = 0,
	REVERSE = 1
}direction_e_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED_POWER_ARR_LEN 400
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t led_power = 0;
direction_e_t direction = FORWARD;

uint8_t led_power_arr[LED_POWER_ARR_LEN] = {0};
uint8_t led_power_arr_reverse[LED_POWER_ARR_LEN] = {0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void LED_Blink(void);
void LED_Blink_DMA_Init(void);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  leds_PWM_init();  	   //PWM Mode

  //LED_Blink_DMA_Init();  //PWM_DMA Mode
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  LED_Blink();  //PWM Mode
	  HAL_Delay(20);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void LED_Blink(void)
{
	if(direction == FORWARD)
	{
		led_power++;

		if(led_power == LED_POWER_MAX)
		{
			direction = REVERSE;
		}
	}
	else //direction == REVERSE
	{
		led_power--;

		if(led_power == LED_POWER_MIN)
		{
			direction = FORWARD;
		}
	}
	leds_PWM_set(GREEN, led_power);
	leds_PWM_set(ORANGE, led_power);
	leds_PWM_set(RED, LED_POWER_MAX - led_power);
	leds_PWM_set(BLUE, LED_POWER_MAX - led_power);
}

void LED_Blink_DMA_Init(void)
{
	for(uint8_t i = 0; i < LED_POWER_ARR_LEN; i += 2)
	  {
		  led_power_arr[i] = i/2;
		  led_power_arr[i+1] = i/2;
		  led_power_arr[LED_POWER_ARR_LEN-1 - i] = i/2;
		  led_power_arr[LED_POWER_ARR_LEN-1 - i+1] = i/2;

		  led_power_arr_reverse[i] = 100 - i/2;
		  led_power_arr_reverse[i+1] = 100 - i/2;
		  led_power_arr_reverse[LED_POWER_ARR_LEN-1 - i] = 100 - i/2;
		  led_power_arr_reverse[LED_POWER_ARR_LEN-1 - i+1] = 100 - i/2;
	  }
	  led_power_arr[200] = 100;


	  leds_PWM_DMA_init(GREEN, (const uint32_t *)led_power_arr, (uint16_t)LED_POWER_ARR_LEN);
	  leds_PWM_DMA_init(ORANGE, (const uint32_t *)led_power_arr, (uint16_t)LED_POWER_ARR_LEN);
	  leds_PWM_DMA_init(RED, (const uint32_t *)led_power_arr_reverse, (uint16_t)LED_POWER_ARR_LEN);
	  leds_PWM_DMA_init(BLUE, (const uint32_t *)led_power_arr_reverse, (uint16_t)LED_POWER_ARR_LEN);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
