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
typedef enum
{
    LEDS_PWM_CH_RED = TIM_CHANNEL_1,
    LEDS_PWM_CH_BLUE = TIM_CHANNEL_2,
    LEDS_PWM_CH_GREEN = TIM_CHANNEL_3,
    LEDS_PWM_CH_ORANGE = TIM_CHANNEL_4 
}LEDS_PWM_TIM_CH_e_t;

typedef enum
{
    LEDS = 0,
    DIR_RED,
    DIR_BLUE,
    DIR_GREEN,
    DIR_ORANGE
}FLAGS_e_t;

typedef enum
{
    REVERSE = 0,
    FORWARD
}DIRECTIONS_e_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LEDS_PWM_TIM htim4
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define __FLAG_SET(flag_bit) main_flags|=(1<<flag_bit)
#define __FLAG_RESET(flag_bit) main_flags&=(~(1<<flag_bit))
#define __FLAG_CHECK(flag_bit) main_flags&=(1<<flag_bit)
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t main_flags = 0;
uint8_t RED_pointer = 0;
uint8_t BLUE_pointer = 0;
uint8_t GREEN_pointer = 0;
uint8_t ORANGE_pointer = 0;
uint16_t LEDS_WAVE_LENGTH = 255;
uint8_t LEDS_wave[256] = 
{
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    2,    2,    2,    2,    2,    2,    2,    2,    3,    3,    3,    3,    3,
    3,    3,    4,    4,    4,    4,    4,    5,    5,    5,    5,    5,    6,    6,    6,    6,
    6,    7,    7,    7,    7,    8,    8,    8,    8,    9,    9,    9,   10,   10,   10,   11,
   11,   11,   12,   12,   12,   13,   13,   13,   14,   14,   14,   15,   15,   16,   16,   16,
   17,   17,   18,   18,   19,   19,   20,   20,   21,   21,   22,   22,   23,   23,   24,   24,
   25,   25,   26,   26,   27,   28,   28,   29,   29,   30,   31,   31,   32,   33,   33,   34,
   35,   35,   36,   37,   37,   38,   39,   40,   40,   41,   42,   43,   44,   44,   45,   46,
   47,   48,   49,   49,   50,   51,   52,   53,   54,   55,   56,   57,   58,   59,   60,   61,
   62,   63,   64,   65,   66,   67,   68,   69,   70,   71,   72,   73,   75,   76,   77,   78,
   79,   80,   82,   83,   84,   85,   87,   88,   89,   90,   92,   93,   94,   96,   97,   99,
  100,  101,  103,  104,  106,  107,  108,  110,  111,  113,  114,  116,  118,  119,  121,  122,
  124,  125,  127,  129,  130,  132,  134,  135,  137,  139,  141,  142,  144,  146,  148,  149,
  151,  153,  155,  157,  159,  161,  162,  164,  166,  168,  170,  172,  174,  176,  178,  180,
  182,  185,  187,  189,  191,  193,  195,  197,  200,  202,  204,  206,  208,  211,  213,  215,
  218,  220,  222,  225,  227,  230,  232,  234,  237,  239,  242,  244,  247,  249,  252,  255,
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void LEDS_PWM_Start (uint16_t RED_Start_Point, uint16_t BLUE_Start_Point, uint16_t GREEN_Start_Point, uint16_t ORANGE_Start_Point);
void LEDS_PWM_Step ();
void LEDS_PWM_Ind_Step (uint16_t LED_pointer, LEDS_PWM_TIM_CH_e_t TIM_CH, FLAGS_e_t DIR_LED);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Leds_PWM_Start (uint16_t RED_Start_Point, uint16_t BLUE_Start_Point, uint16_t GREEN_Start_Point, uint16_t ORANGE_Start_Point)
{
    if ((RED_Start_Point > LEDS_WAVE_LENGTH) || (RED_Start_Point < 0))
    {
        RED_Start_Point = 0;
    }
    if ((BLUE_Start_Point > LEDS_WAVE_LENGTH) || (BLUE_Start_Point < 0))
    {
        BLUE_Start_Point = 0;
    } 
    if ((GREEN_Start_Point > LEDS_WAVE_LENGTH) || (GREEN_Start_Point < 0))
    {
        GREEN_Start_Point = 0;
    } 
    if ((ORANGE_Start_Point > LEDS_WAVE_LENGTH) || (ORANGE_Start_Point < 0))
    {
        ORANGE_Start_Point = 0;
    }     
    RED_pointer = RED_Start_Point;
    BLUE_pointer = BLUE_Start_Point;
    GREEN_pointer = GREEN_Start_Point;
    ORANGE_pointer = ORANGE_Start_Point;
    __FLAG_SET(DIR_RED);
    __FLAG_SET(DIR_BLUE);
    __FLAG_SET(DIR_GREEN);
    __FLAG_SET(DIR_ORANGE);
    HAL_TIM_PWM_Start_IT (&LEDS_PWM_TIM, LEDS_PWM_CH_RED);
    HAL_TIM_PWM_Start_IT (&LEDS_PWM_TIM, LEDS_PWM_CH_BLUE);
    HAL_TIM_PWM_Start_IT (&LEDS_PWM_TIM, LEDS_PWM_CH_GREEN);
    HAL_TIM_PWM_Start_IT (&LEDS_PWM_TIM, LEDS_PWM_CH_ORANGE);
}

void Leds_PWM_Step ()
{
    LEDS_PWM_Ind_Step(RED_pointer, LEDS_PWM_CH_RED, DIR_RED);
    LEDS_PWM_Ind_Step(BLUE_pointer, LEDS_PWM_CH_BLUE, DIR_BLUE);
    LEDS_PWM_Ind_Step(GREEN_pointer, LEDS_PWM_CH_GREEN, DIR_GREEN);
    LEDS_PWM_Ind_Step(ORANGE_pointer, LEDS_PWM_CH_ORANGE, DIR_ORANGE);
}

void LEDS_PWM_Ind_Step (uint16_t LED_pointer, LEDS_PWM_TIM_CH_e_t TIM_CH, FLAGS_e_t DIR_LED)
{
    switch (__FLAG_CHECK(DIR_LED))
    {
        case FORWARD: 
        {
            if (LED_pointer == LEDS_WAVE_LENGTH)
            {
                __FLAG_RESET(DIR_LED);
            }
            else
            {
               LED_pointer++; 
            }
            return;
        }
        case REVERSE: 
        {
            if (LED_pointer == 0)
            {
                __FLAG_SET(DIR_LED);
            }
            else
            {
               LED_pointer--; 
            }
            return;
        }
        default:
        {
            return;
        }
    }
    __HAL_TIM_SET_COMPARE(&LEDS_PWM_TIM, TIM_CH, LEDS_wave[LED_pointer]);
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
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  Leds_PWM_Start((LEDS_WAVE_LENGTH/2), 0, (LEDS_WAVE_LENGTH/2), 0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

      if (__FLAG_CHECK(LEDS))
      {
          Leds_PWM_Step();
          __FLAG_RESET(LEDS);
      }
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
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &LEDS_PWM_TIM)
    {
        __FLAG_SET(LEDS);
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
