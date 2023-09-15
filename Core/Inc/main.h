/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;
typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI1_TFT_Pin GPIO_PIN_2
#define SPI1_TFT_GPIO_Port GPIOE
#define TFT_BL_Pin GPIO_PIN_3
#define TFT_BL_GPIO_Port GPIOE
#define KEY_D_Pin GPIO_PIN_4
#define KEY_D_GPIO_Port GPIOE
#define PPM_Pin GPIO_PIN_5
#define PPM_GPIO_Port GPIOE
#define KEY_C_Pin GPIO_PIN_6
#define KEY_C_GPIO_Port GPIOE
#define RGB_R_Pin GPIO_PIN_13
#define RGB_R_GPIO_Port GPIOC
#define RGB_G_Pin GPIO_PIN_14
#define RGB_G_GPIO_Port GPIOC
#define RGB_B_Pin GPIO_PIN_15
#define RGB_B_GPIO_Port GPIOC
#define KEY_U_Pin GPIO_PIN_0
#define KEY_U_GPIO_Port GPIOC
#define KEY_L_Pin GPIO_PIN_1
#define KEY_L_GPIO_Port GPIOC
#define IO1_Pin GPIO_PIN_0
#define IO1_GPIO_Port GPIOA
#define IO2_Pin GPIO_PIN_1
#define IO2_GPIO_Port GPIOA
#define IO3_Pin GPIO_PIN_2
#define IO3_GPIO_Port GPIOA
#define IO4_Pin GPIO_PIN_3
#define IO4_GPIO_Port GPIOA
#define SPI1_FLASH_Pin GPIO_PIN_4
#define SPI1_FLASH_GPIO_Port GPIOA
#define ADC1_Pin GPIO_PIN_4
#define ADC1_GPIO_Port GPIOC
#define ADC2_Pin GPIO_PIN_5
#define ADC2_GPIO_Port GPIOC
#define BAT_ADC_Pin GPIO_PIN_0
#define BAT_ADC_GPIO_Port GPIOB
#define KEY_R_Pin GPIO_PIN_7
#define KEY_R_GPIO_Port GPIOE
#define SPL2_Mcu_CS_Pin GPIO_PIN_12
#define SPL2_Mcu_CS_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_14
#define BUZZER_GPIO_Port GPIOB
#define MOTORA_IN1_Pin GPIO_PIN_10
#define MOTORA_IN1_GPIO_Port GPIOD
#define MOTORA_IN2_Pin GPIO_PIN_11
#define MOTORA_IN2_GPIO_Port GPIOD
#define MOTORB_IN1_Pin GPIO_PIN_12
#define MOTORB_IN1_GPIO_Port GPIOD
#define MOTORB_IN2_Pin GPIO_PIN_13
#define MOTORB_IN2_GPIO_Port GPIOD
#define MOTORA_PWM_Pin GPIO_PIN_14
#define MOTORA_PWM_GPIO_Port GPIOD
#define MOTORB_PWM_Pin GPIO_PIN_15
#define MOTORB_PWM_GPIO_Port GPIOD
#define TFT_RES_Pin GPIO_PIN_0
#define TFT_RES_GPIO_Port GPIOE
#define TFT_DC_Pin GPIO_PIN_1
#define TFT_DC_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
