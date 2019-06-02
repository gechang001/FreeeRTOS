/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define LED0_Pin GPIO_PIN_13
#define LED0_GPIO_Port GPIOC
#define VS1838_Pin GPIO_PIN_0
#define VS1838_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOA
#define KEYA_Pin GPIO_PIN_0
#define KEYA_GPIO_Port GPIOB
#define KEYB_Pin GPIO_PIN_1
#define KEYB_GPIO_Port GPIOB
#define CH_PD_Pin GPIO_PIN_3
#define CH_PD_GPIO_Port GPIOB
#define ESP8266_REST_Pin GPIO_PIN_4
#define ESP8266_REST_GPIO_Port GPIOB
#define DHT11_Pin GPIO_PIN_5
#define DHT11_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_6
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_7
#define SDA_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

#define LED0_ON 								HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_RESET)
#define LED0_OFF 								HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET)
#define LED0_TOGGLE     				HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin)       

#define LED1_ON 								HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET)
#define LED1_OFF 								HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET)
#define LED1_TOGGLE     				HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin)  

#define KEYA_READ 							HAL_GPIO_ReadPin(KEYA_GPIO_Port,KEYA_Pin)

#define KEYB_READ 							HAL_GPIO_ReadPin(KEYB_GPIO_Port,KEYB_Pin)

#define VS1838_READ 						HAL_GPIO_ReadPin(VS1838_GPIO_Port,VS1838_Pin)

#define DHT11_HIGH 							HAL_GPIO_WritePin(DHT11_GPIO_Port,DHT11_Pin,GPIO_PIN_SET)
#define DHT11_LOW 							HAL_GPIO_WritePin(DHT11_GPIO_Port,DHT11_Pin,GPIO_PIN_RESET)
#define DHT11_TOGGLE   				 	HAL_GPIO_TogglePin(DHT11_GPIO_Port,DHT11_Pin) 
#define DHT11_READ 							HAL_GPIO_ReadPin(DHT11_GPIO_Port,DHT11_Pin)

#define ESP8266_REST_HIGH 			HAL_GPIO_WritePin(ESP8266_REST_GPIO_Port,ESP8266_REST_Pin,GPIO_PIN_SET)
#define ESP8266_REST_LOW 				HAL_GPIO_WritePin(ESP8266_REST_GPIO_Port,ESP8266_REST_Pin,GPIO_PIN_RESET)
#define CH_PD_HIGH 							HAL_GPIO_WritePin(CH_PD_GPIO_Port,CH_PD_Pin,GPIO_PIN_SET)
#define CH_PD_LOW 							HAL_GPIO_WritePin(CH_PD_GPIO_Port,CH_PD_Pin,GPIO_PIN_RESET)

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
