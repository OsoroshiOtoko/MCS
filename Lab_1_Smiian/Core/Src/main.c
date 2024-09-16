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
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define Clockwise 1
#define Counterclockwise 0
#define Number_Of_LEDs 4-1
#define Step 1
#define Delay_Limit_ms 100
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t Direction_Handler = 0;
uint8_t Timer_Interrupt_Flag = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Circular_Flick (uint8_t Direction, uint32_t Delay_ms);
void Red_Tog(); 	//Start on top - going counterclockwise 
void Blue_Tog();
void Green_Tog();
void Orange_Tog();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Red_Tog(){ HAL_GPIO_TogglePin(LED_Red_GPIO_Port, LED_Red_Pin);}
void Blue_Tog(){ HAL_GPIO_TogglePin(LED_Blue_GPIO_Port, LED_Blue_Pin);}
void Green_Tog(){ HAL_GPIO_TogglePin(LED_Green_GPIO_Port, LED_Green_Pin);}
void Orange_Tog(){ HAL_GPIO_TogglePin(LED_Orange_GPIO_Port, LED_Orange_Pin);}
void (*LED_Tog[])(void) = {Red_Tog, Blue_Tog, Green_Tog, Orange_Tog};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim->Instance == TIM14){
		static uint8_t Pointer = 0;
		LED_Tog[Pointer]();
		if (Direction_Handler == 0){
      Pointer = (Pointer >= Number_Of_LEDs) ? 0 : Pointer + Step;
    } else { 
      Pointer = (Pointer == 0) ? Number_Of_LEDs : Pointer - Step;
		}
		LED_Tog[Pointer]();
	}
}

void Circular_Flick (uint8_t Direction, uint32_t Delay_ms){
	HAL_TIM_Base_Stop_IT(&htim14);
	Direction_Handler = Direction;
	if (Delay_ms < Delay_Limit_ms){ Delay_ms = Delay_Limit_ms;}
	TIM14->ARR = Delay_ms;
	HAL_TIM_Base_Start_IT(&htim14);
}
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
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(LED_Red_GPIO_Port, LED_Red_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_Blue_GPIO_Port, LED_Blue_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_Orange_GPIO_Port, LED_Orange_Pin, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	Circular_Flick (Clockwise, 500);
	HAL_Delay(4010); //if delay is round - MC stucks for a minute
	Circular_Flick (Counterclockwise, 250);
	HAL_Delay(2010);
		
	//////////////Comment///////////////////////////
		/* 
		This is only core for such task. In real project several functions needed, such as:
		Circular_Flick_Init();
		Circular_Flick_Start();
		Circular_Flick_Stop();
		Core will remain same - functions will setup LEDs, Pointer and Duration
		If needed - duration of pause between flicks also can be specified
		*/
	//////////////Comment///////////////////////////
		
    /* USER CODE END WHILE */

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
