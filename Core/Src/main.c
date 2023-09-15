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
#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd_proc.h"
#include "lcd_init.h"
#include "flash_proc.h"
#include "sys.h"
#include "sbus_proc.h"
#include "motor_proc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "openmv_proc.h"
//#include  "trcRecorder.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

//串口接受缓冲
u8 Uart1Rx[MAX_UART_RX_NUM];
u8 Uart2Rx[MAX_UART_RX_NUM];
u8 Uart3Rx[MAX_UART_RX_NUM];
u8 Uart4Rx[MAX_UART_RX_NUM];
u8 Uart5Rx[MAX_UART_RX_NUM];
u8 Uart6Rx[MAX_UART_RX_NUM];

//串口发送缓冲
u8 RunTimeFlag = 0;
u8 TaskListFlag = 0;
char InfoBuffer[1000];
u8 Uart1Tx[1000];
u8 Uart2Tx[MAX_UART_TX_NUM];
u8 Uart3Tx[MAX_UART_TX_NUM];
u8 Uart4Tx[MAX_UART_TX_NUM];
u8 Uart5Tx[MAX_UART_TX_NUM];
u8 Uart6Tx[MAX_UART_TX_NUM];

u32 TIM12Count;       //freertos 时间调度统计
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM7_Init();
  MX_TIM8_Init();
  MX_TIM9_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  MX_TIM12_Init();
  MX_USART6_UART_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_TIM13_Init();
  /* USER CODE BEGIN 2 */
//	vTraceEnable(TRC_INIT);          /
 //拉高spi片选
  HAL_GPIO_WritePin(SPI1_FLASH_GPIO_Port, SPI1_FLASH_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE,SPI1_TFT_Pin, GPIO_PIN_SET);
	//点亮lcd背屏幕
	HAL_GPIO_WritePin(GPIOE,TFT_BL_Pin, GPIO_PIN_SET);
	
	
	//HAL_Delay(100);
	
//	//LED0=0;
//	LCD_ShowString(30,30,"XCJK",WHITE,BLACK,32,0);
//	LCD_ShowString(30,62,"RTOS",WHITE,BLACK,32,0);
	
	//串口开启中断
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, Uart1Rx, MAX_UART_RX_NUM);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart2, Uart2Rx, MAX_UART_RX_NUM);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3, Uart3Rx, MAX_UART_RX_NUM);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart4, Uart4Rx, MAX_UART_RX_NUM);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart5, Uart5Rx, MAX_UART_RX_NUM);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart6, Uart6Rx, MAX_UART_RX_NUM);
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


/******************************************************************************
      函数说明：串口中断回调
      入口数据：无    
      返回值：  无
******************************************************************************/

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart->Instance == USART1)
	{

		HAL_UART_Transmit_DMA(&huart1, Uart1Rx, Size);
		if(Uart1Rx[0] == 'l' && Uart1Rx[1] == 's') 
					TaskListFlag = 1;
		if(Uart1Rx[0] == 't' && Uart1Rx[1] == 's')
					RunTimeFlag = 1;

		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, Uart1Rx, MAX_UART_RX_NUM);
	}
	else if(huart->Instance == USART2)
	{
		HAL_UART_Transmit_DMA(&huart2, Uart2Rx, Size);
		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, Uart2Rx, MAX_UART_RX_NUM);
	}
	else if(huart->Instance == USART3)
	{
				
		HAL_UART_Transmit_DMA(&huart3, Uart3Rx, Size);
		HAL_UARTEx_ReceiveToIdle_DMA(&huart3, Uart3Rx, MAX_UART_RX_NUM);
	}
	else if(huart->Instance == UART4)
	{
		HAL_UART_Transmit_DMA(&huart4, Uart4Rx, Size);
		HAL_UARTEx_ReceiveToIdle_DMA(&huart4, Uart4Rx, MAX_UART_RX_NUM);
	}
	else if(huart->Instance == UART5)
	{
		HAL_UART_Transmit_DMA(&huart5, Uart5Rx, Size);
		HAL_UARTEx_ReceiveToIdle_DMA(&huart5, Uart5Rx, MAX_UART_RX_NUM);
	}
	else if(huart->Instance == USART6)
	{
		Sbus_Uart6_IDLE_Proc(Size);           //遥控器
		HAL_UARTEx_ReceiveToIdle_DMA(&huart6, Uart6Rx, MAX_UART_RX_NUM);
	}


}

extern u32 TIM7Count;

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
	if(htim->Instance == TIM13)//FREERTOS 时间统计
	{
	 TIM12Count++;
	}
	
  /* USER CODE END Callback 1 */
}

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
