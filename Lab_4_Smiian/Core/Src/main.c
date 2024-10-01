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


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tim.h"
#include "gpio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum
{
    LEDS_PWM_CALLB = 0
}flags_e_t;

typedef enum
{
    RED = 0,
    BLUE,
    GREEN,
    ORANGE,
    LEDS_ALL
}leds_color_e_t;

typedef enum
{
    REVERSE = 0,
    FORWARD
}directions_e_t;

typedef struct
{
    directions_e_t led_dir;
    uint8_t        led_ptr;
    uint32_t       led_ch;
}leds_config_s_t;

leds_config_s_t leds_config[LEDS_ALL] = {0};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LEDS_PWM_TIM htim4
#define MAX_VALUE 255
#define LEDS_WAVE_LENGTH 256
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define __FLAG_SET(flag_bit)   main_flags |= (1 << flag_bit)
#define __FLAG_RESET(flag_bit) main_flags &= (~ (1 << flag_bit))
#define __FLAG_CHECK(flag_bit) main_flags &= (1 << flag_bit)
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t main_flags = 0;
const uint8_t LEDS_WAVE[LEDS_WAVE_LENGTH] = 
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
void LEDS_PWM_Start (uint8_t RED_Start_Point, uint8_t BLUE_Start_Point, uint8_t GREEN_Start_Point, uint8_t ORANGE_Start_Point);
void LEDS_PWM_Step ();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Leds_PWM_Start (uint8_t RED_Start_Point, uint8_t BLUE_Start_Point, uint8_t GREEN_Start_Point, uint8_t ORANGE_Start_Point)
{
    uint8_t start_points [LEDS_ALL] = {RED_Start_Point, BLUE_Start_Point, GREEN_Start_Point, ORANGE_Start_Point};  
    for(leds_color_e_t color = RED; color < LEDS_ALL; color++)
    {
        leds_config[color].led_dir = FORWARD;
        if (start_points [color] > MAX_VALUE)
        {
            leds_config[color].led_ptr = MAX_VALUE;
        }
        else
        {
            leds_config[color].led_ptr = start_points[color];
        }
    } 
    leds_config[RED].led_ch    = TIM_CHANNEL_1;
    leds_config[BLUE].led_ch   = TIM_CHANNEL_2;
    leds_config[GREEN].led_ch  = TIM_CHANNEL_3;
    leds_config[ORANGE].led_ch = TIM_CHANNEL_4;
    __HAL_TIM_ENABLE_IT (&LEDS_PWM_TIM, TIM_IT_UPDATE);
    HAL_TIM_PWM_Start (&LEDS_PWM_TIM, leds_config[RED].led_ch);
    HAL_TIM_PWM_Start (&LEDS_PWM_TIM, leds_config[BLUE].led_ch);
    HAL_TIM_PWM_Start (&LEDS_PWM_TIM, leds_config[GREEN].led_ch);
    HAL_TIM_PWM_Start (&LEDS_PWM_TIM, leds_config[ORANGE].led_ch);
}

void Leds_PWM_Step ()
{
    for (leds_color_e_t color = RED; color < LEDS_ALL; color++)
    {
        switch (leds_config[color].led_dir)
        {
            case FORWARD: 
            {
                if (leds_config[color].led_ptr == (LEDS_WAVE_LENGTH - 1))
                {
                    leds_config[color].led_dir = REVERSE;
                }
                else
                {
                    leds_config[color].led_ptr++;
                }
                break;
            }
            case REVERSE: 
            {
                if (leds_config[color].led_ptr == 0)
                {
                    leds_config[color].led_ptr = (LEDS_WAVE_LENGTH - 1);
                }
                else
                {
                    leds_config[color].led_ptr--;
                }
                break;
            }
            default:
            {
                break;
            }
        }
    __HAL_TIM_SET_COMPARE(&LEDS_PWM_TIM, leds_config[color].led_ch, LEDS_WAVE[leds_config[color].led_ptr]);
    }
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

      if (__FLAG_CHECK(LEDS_PWM_CALLB))
      {
          Leds_PWM_Step();
          __FLAG_RESET(LEDS_PWM_CALLB);
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
        __FLAG_SET(LEDS_PWM_CALLB);
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
