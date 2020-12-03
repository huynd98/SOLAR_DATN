/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define FB_VBAT_Pin GPIO_PIN_1
#define FB_VBAT_GPIO_Port GPIOB
#define ALERT_CHARGE_Pin GPIO_PIN_12
#define ALERT_CHARGE_GPIO_Port GPIOB
#define ALERT_CHARGE_EXTI_IRQn EXTI15_10_IRQn
#define ALERT_DISCHARGE_Pin GPIO_PIN_13
#define ALERT_DISCHARGE_GPIO_Port GPIOB
#define ALERT_DISCHARGE_EXTI_IRQn EXTI15_10_IRQn
#define CTRL_WAVE_SOLAR_Pin GPIO_PIN_8
#define CTRL_WAVE_SOLAR_GPIO_Port GPIOA
#define CRTL_5V_LOAD_Pin GPIO_PIN_11
#define CRTL_5V_LOAD_GPIO_Port GPIOA
#define CTRL_12V_LOAD_Pin GPIO_PIN_12
#define CTRL_12V_LOAD_GPIO_Port GPIOA
#define Level10_Pin GPIO_PIN_3
#define Level10_GPIO_Port GPIOB
#define Level89_Pin GPIO_PIN_4
#define Level89_GPIO_Port GPIOB
#define Level7_Pin GPIO_PIN_5
#define Level7_GPIO_Port GPIOB
#define Level65_Pin GPIO_PIN_6
#define Level65_GPIO_Port GPIOB
#define Level4_Pin GPIO_PIN_7
#define Level4_GPIO_Port GPIOB
#define Level32_Pin GPIO_PIN_8
#define Level32_GPIO_Port GPIOB
#define Level1_Pin GPIO_PIN_9
#define Level1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
