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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "LEDs.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef enum
{
	FORWARD = 0,
	REVERSE = 1,
}direction_e_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define second 1000
#define LED_GPIO_Port LED_Green_GPIO_Port //same port
//#define NUM_LEDS (sizeof(LEDs) / sizeof(LED_TypeDef)) // Array size
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

static GPIO_PinState pin_state = GPIO_PIN_RESET;
static bool flag_set_button = false;
static leds_color_e_t led_switcher = GREEN;
static direction_e_t direction = FORWARD;
static uint32_t timeout = 0;
static uint16_t leds[ALL] = {GREEN, ORANGE, RED, BLUE};


// Initialization of the array with LEDs
//	   LED_TypeDef LEDs[] = {
//    {LED_Blue_GPIO_Port, LED_Blue_Pin},
//    {LED_Red_GPIO_Port, LED_Red_Pin},
//    {LED_Orange_GPIO_Port, LED_Orange_Pin},
//    {LED_Green_GPIO_Port, LED_Green_Pin}
//    };
//		 
//		uint8_t current_led = 0; // Variable for tracking the current LED
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
		
// Function to turn off all LEDs		
//void TurnOffAllLEDs(void) {
//    for (uint8_t i = 0; i < NUM_LEDS; i++) {
//        HAL_GPIO_WritePin(LEDs[i].Port, LEDs[i].Pin, GPIO_PIN_RESET);
//    }
//}


//// Function for switching to the next LED
//void Next_LED(void) {
//    // Turn off all LEDs
//    TurnOffAllLEDs();
//    
//    // Turn on the next LED
//    HAL_GPIO_WritePin(LEDs[current_led].Port, LEDs[current_led].Pin, GPIO_PIN_SET);
//    
//    // Increase the counter
//    current_led++;

//    // If the counter has reached the end of the array, reset it to 0
//    if (current_led >= NUM_LEDS) {
//        current_led = 0;
//    }
//}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
	
	
int main(void)
{

  /* USER CODE BEGIN 1 */
   //GPIO_PinState pin_state = GPIO_PIN_RESET;

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
  /* USER CODE BEGIN 2 */
  // HAL_GPIO_WritePin(LED_Red_GPIO_Port, LED_Red_Pin, GPIO_PIN_SET);
	
	//for (uint32_t i; i < ALL; i++)
	//HAL_GPIO_WritePin(LED_GPIO_Port, leds[led_switcher], GPIO_PIN_SET);
  leds_set(leds[led_switcher], ON);  
	timeout = 250;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		

		HAL_Delay(timeout);
		if (HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == GPIO_PIN_SET)
		{
			if(flag_set_button == false)
			{
			flag_set_button = true;
		//HAL_GPIO_WritePin(LED_GPIO_Port, leds[led_switcher], GPIO_PIN_RESET);
    leds_set(leds[led_switcher], OFF);				
    if(direction == FORWARD)
		{			
		led_switcher ++;
		if (led_switcher == ALL)
		{
			led_switcher = GREEN;
		}
	}
		else
		{
					
		if (led_switcher == GREEN)
		{
			led_switcher = ALL;
		}
		led_switcher --;
		}
		//HAL_GPIO_WritePin(LED_GPIO_Port, leds[led_switcher], GPIO_PIN_SET); 
		leds_set(leds[led_switcher], ON);
	}
}
		else
		{
			flag_set_button = false;
		}
		
		
		
//		if (HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == GPIO_PIN_SET) {      // If the button is pressed
//				HAL_Delay(50);  
//				if (HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == GPIO_PIN_SET) {  // If the button is still pressed
//					
//						Next_LED();   // Switch to the next LED 
//						
//						while (HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == GPIO_PIN_SET) { // Wait for the button to be released to avoid multiple triggering
//								
//						}
//				}
//		}
		
		
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
if(direction == FORWARD)
{
	direction = REVERSE;
}
		else
		{
			direction = FORWARD;
		}
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