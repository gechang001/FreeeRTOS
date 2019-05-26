/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */    
#include "app.h"
#include "GPIO.h"
#include "string.h"
#include "dma.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId ALL_initHandle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartInitTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
//void vTask1(void const * argument);
/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of ALL_init */
  osThreadDef(ALL_init, StartInitTask, osPriorityNormal, 0, 128);
  ALL_initHandle = osThreadCreate(osThread(ALL_init), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartInitTask function */
void StartInitTask(void const * argument)
{

  /* USER CODE BEGIN StartInitTask */
  /* Infinite loop */
	HAL_UART_Receive_DMA(&huart1, UsartType1.usartDMA_rxBuf, RECEIVELEN);  						//串口1DMA开启
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE); 																			//串口1空闲中断
	HAL_UART_Receive_DMA(&huart3, UsartType3.usartDMA_rxBuf, RECEIVELEN);  						//串口3DMA开启
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE); 	
	
	    xTaskCreate( vTask1,                  /*指向任务函数的指针*/
                 "vTask1",               /*任务的文本名字,只会在调试中用到*/
                 128,                       /*栈深度,占用内存大小等于值x4*/
                 NULL,                      /*没有任务参数*/
                 1,                         /*任务优先级,0最小*/
                 NULL);        /*不会用到任务句柄*/
	
  for(;;)
  {
		HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
		printf("GC001\r\n");
    osDelay(1000);
  }
  /* USER CODE END StartInitTask */
}

/* USER CODE BEGIN Application */
  
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
