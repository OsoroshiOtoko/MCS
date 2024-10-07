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
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum
	{
		
	FLAG_TIMEOUT = 0,
  }flag_e_t;


   
  typedef struct{
    uint16_t power;
    bool up_power;
}LED_PowerState_s_t;

 typedef enum {
    BLUE,
    RED,
    ORANGE,
    GREEN
} LED_Color;

LED_PowerState_s_t LED_PowerState[4] = {
    {100, true},    //blue
    {50, false},    //red
    {75, true},     //orange
    {25, false}     //green
};

//	typedef struct {
//    uint16_t power_blue;
//    uint16_t power_red;
//	uint16_t power_orange;
//	uint16_t power_green;
//    bool up_power_blue;
//    bool up_power_red;
//	bool up_power_orange;
//	bool up_power_green;
//}LED_PowerState_s_t;
	


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED_MASSIVE_POWER_MAX 200
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define FLAG_SET(flag) flags |= (1 << flag)
#define FLAG_RESET(flag) flags &= (~(1 << flag))	
#define FLAG_CHECK(flag) (flags == (1 << flag))
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
  uint32_t flags = 0;
	uint16_t variable_timeout = 0;


	
	uint16_t led_mass_power[LED_MASSIVE_POWER_MAX] = {0};	
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
	
void UpdateLEDs(void) {
//    if (*up_power) {
//        (*power)++;
//        if (*power >= 100) {
//            *up_power = false;
//        }
//    } else {
//        (*power)--;
//        if (*power == 0) {
//            *up_power = true;
//        }
//    }

       for (int i = 0; i < 4; i++) {
        if (LED_PowerState[i].up_power) {
            LED_PowerState[i].power++;
            if (LED_PowerState[i].power >= 100) {
                LED_PowerState[i].power = 100;
                LED_PowerState[i].up_power = false;
            }
        } else {
            LED_PowerState[i].power--;
            if (LED_PowerState[i].power == 0) {
                LED_PowerState[i].up_power = true;
            }
        }
    }



}
void ApplyPWM(void) {
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, LED_PowerState[0].power);  
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, LED_PowerState[1].power);  
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, LED_PowerState[2].power);  
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, LED_PowerState[3].power);  
}
	
	
//	void UpdateLEDs(LED_PowerState_s_t *led_state) {
//    UpdateLEDState(&led_state->power_blue, &led_state->up_power_blue);
//    UpdateLEDState(&led_state->power_red, &led_state->up_power_red);
//    UpdateLEDState(&led_state->power_orange, &led_state->up_power_orange);
//    UpdateLEDState(&led_state->power_green, &led_state->up_power_green);

//    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, led_state->power_blue);
//    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, led_state->power_red);
//    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, led_state->power_orange);
//    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, led_state->power_green);

//}



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_TIM6_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	htim6.Init.Period = 100;
	HAL_TIM_Base_Init(&htim6);
	HAL_TIM_Base_Start_IT(&htim6);

	variable_timeout = 100;

		
//		LED_PowerState_s_t led_state = {0, 0, 0, 0, true, true, true, true};


//led_state.power_blue = 100;
//led_state.up_power_red = false;
		
// led_state.power_red = 0;
// led_state.up_power_red = true;
// led_state.power_blue = 25;
// led_state.up_power_blue = true;
// led_state.power_orange = 50;
// led_state.up_power_orange = false;
//	led_state.power_green = 75;
// led_state.up_power_green = false;
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, LED_PowerState[0].power);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, LED_PowerState[1].power);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, LED_PowerState[2].power);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, LED_PowerState[3].power);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


    //UpdateLEDs(&led_state); 
    UpdateLEDs();
    ApplyPWM(); 
    HAL_Delay(200);    
    
      
        
  
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
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim6)
	{
	//	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);
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
