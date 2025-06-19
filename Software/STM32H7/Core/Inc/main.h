/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
#define IR_O2_Pin GPIO_PIN_4
#define IR_O2_GPIO_Port GPIOE
#define IR_O3_Pin GPIO_PIN_6
#define IR_O3_GPIO_Port GPIOE
#define IR_O1_Pin GPIO_PIN_0
#define IR_O1_GPIO_Port GPIOC
#define IR_O4_Pin GPIO_PIN_2
#define IR_O4_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_1
#define LED_GPIO_Port GPIOA
#define Motor_EN_Pin GPIO_PIN_4
#define Motor_EN_GPIO_Port GPIOA
#define Motor_L_A_Pin GPIO_PIN_8
#define Motor_L_A_GPIO_Port GPIOE
#define Motor_L_B_Pin GPIO_PIN_10
#define Motor_L_B_GPIO_Port GPIOE
#define Motor_R_A_Pin GPIO_PIN_9
#define Motor_R_A_GPIO_Port GPIOD
#define Motor_R_B_Pin GPIO_PIN_11
#define Motor_R_B_GPIO_Port GPIOD
#define IIC_SCL_Pin GPIO_PIN_6
#define IIC_SCL_GPIO_Port GPIOB
#define IIC_SDA_Pin GPIO_PIN_7
#define IIC_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
