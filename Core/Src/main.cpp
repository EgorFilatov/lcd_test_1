/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PIN_EN    (1 << 2)
#define BACKLIGHT (1 << 3)

#define LCD_DELAY_MS 5
#define LCD_ADDR (0x27 << 1)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_i2c1_tx;

TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t addr = 0;
uint8_t i2c_state = 0;
uint8_t step = 0;
uint8_t cursor_position = 1;
uint8_t str[] = "ѕроверка передачи UART\r\n\0";


uint8_t flag = 0;

uint8_t chislo[6] = {1,2,3,4,5,6};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM6_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void i2c_addr_scan() {
	for (uint16_t i = 0; i < 128; i++) {
		if ((HAL_I2C_IsDeviceReady(&hi2c1, i << 1, 1, HAL_MAX_DELAY))
				== HAL_OK) {
			addr = i;
			i = 129;
		}
	}
}

void lcd_send_bite(uint8_t data, uint8_t rs) {
	uint8_t up = data & 0xF0;
	uint8_t lo = (data << 4) & 0xF0;

	uint8_t data_arr[4];

	data_arr[0] = up | rs | BACKLIGHT | PIN_EN;
	data_arr[1] = 0;
	data_arr[2] = lo | rs | BACKLIGHT | PIN_EN;
	data_arr[3] = 0;

	i2c_state = 1;
	HAL_I2C_Master_Transmit_DMA(&hi2c1, LCD_ADDR, data_arr, 4);
	while (i2c_state == 1) {
	}
}


void lcd_send_string(char *str) {
	while (*str) {
		lcd_send_bite((uint8_t)(*str), 1);
		str++;
	}
}

uint8_t debounce_count[4] = { 0, 0, 0, 0 }; // –азмер массива- количество кнопок
uint8_t button_status[4] = { 0, 0, 0, 0 }; // –азмер массива- количество кнопок
uint8_t timer_status = 0;

void button_click(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t button_num) {
	if ((GPIOx->IDR & (1 << pin)) && button_status[button_num] == 0) {
		button_status[button_num] = 1;
		++timer_status;
		HAL_TIM_Base_Start_IT(&htim6); // ¬ключение таймера 6
	}

	if ((GPIOA->IDR & (1 << pin)) == 0 && button_status[button_num] == 2) {
		button_status[button_num] = 0;
	}
}

void button_interrupt(uint8_t button_num) {
	if (debounce_count[button_num] < 5) {
		++debounce_count[button_num];
	}

	if (debounce_count[button_num] == 5 && (GPIOA->IDR & (1 << button_num))) {

		if (timer_status == 1) {
			timer_status = 0;
			HAL_TIM_Base_Stop_IT(&htim6);
		} else {
			--timer_status;
		}
		if (button_num == 0) {
			--cursor_position;
		}
		if (button_num == 1) {
			++cursor_position;
		}

		debounce_count[button_num] = 0;
		button_status[button_num] = 2;
	} else {
		button_status[button_num] = 0;
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
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	/* Ќастройка диспле€ */
	HAL_Delay(50);

	lcd_send_bite(0b00110000, 0);   // 8ми битный интерфейс
	HAL_Delay(40);

	lcd_send_bite(0b00000010, 0);   // установка курсора в начале строки
	HAL_Delay(40);

	lcd_send_bite(0b00001100, 0);   // нормальный режим работы, выкл курсор
	HAL_Delay(40);

	lcd_send_bite(0b00000001, 0);   // очистка диспле€
	HAL_Delay(2);




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
		button_click(GPIOA, 0, 0);
		button_click(GPIOA, 1, 1);

		if (cursor_position == 7) {
			cursor_position = 1;
		}
		if (cursor_position == 0) {
			cursor_position = 6;
		}

		if (step == 0) {
			step = 1;

			lcd_send_bite(0x88, 0); // переход на 1 строку
			lcd_send_string("Menu");

			lcd_send_bite(0xC2, 0); // переход на 2 строку
			lcd_send_string("Line 1      Line 4");

			lcd_send_bite(0x96, 0); // переход на 3 строку
			lcd_send_string("Line 2      Line 5");

			lcd_send_bite(0xD6, 0); // переход на 4 строку
			lcd_send_string("Line 3      Line 6");
		}

		if (cursor_position == 1) {
			lcd_send_bite(0xE0, 0); // переход на 4 строку
			lcd_send_string(" ");
			lcd_send_bite(0x94, 0); // переход на 3 строку
			lcd_send_string(" ");

			lcd_send_bite(0xC0, 0); // переход на 2 строку
			lcd_send_string(">");
		}

		if (cursor_position == 2) {
			lcd_send_bite(0xC0, 0); // переход на 2 строку
			lcd_send_string(" ");
			lcd_send_bite(0xD4, 0);
			lcd_send_string(" ");

			lcd_send_bite(0x94, 0); // переход на 3 строку
			lcd_send_string(">");
		}

		if (cursor_position == 3) {
			lcd_send_bite(0x94, 0);
			lcd_send_string(" ");
			lcd_send_bite(0xCC, 0);
			lcd_send_string(" ");

			lcd_send_bite(0xD4, 0);
			lcd_send_string(">");
		}

		if (cursor_position == 4) {
			lcd_send_bite(0xD4, 0);
			lcd_send_string(" ");
			lcd_send_bite(0xA0, 0);
			lcd_send_string(" ");

			lcd_send_bite(0xCC, 0);
			lcd_send_string(">");
		}

		if (cursor_position == 5) {
			lcd_send_bite(0xCC, 0);
			lcd_send_string(" ");
			lcd_send_bite(0xE0, 0);
			lcd_send_string(" ");

			lcd_send_bite(0xA0, 0);
			lcd_send_string(">");
		}

		if (cursor_position == 6) {
			lcd_send_bite(0xA0, 0);
			lcd_send_string(" ");
			lcd_send_bite(0xC0, 0); // переход на 2 строку
			lcd_send_string(" ");

			lcd_send_bite(0xE0, 0);
			lcd_send_string(">");
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 5000;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 2;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LD4_Pin|LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	i2c_state = 0;
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) {

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {

	++flag;

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	button_interrupt(0);
	button_interrupt(1);
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
