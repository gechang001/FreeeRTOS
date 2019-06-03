/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */    
extern void StartInitTask(void const * argument);

#include "app.h"
#include "GPIO.h"
#include "string.h"
#include "dma.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
#include "24cxx.h"
/* USER CODE END Includes */

void FirstInit()
{
	HAL_UART_Receive_DMA(&huart1, UsartType1.usartDMA_rxBuf, RECEIVELEN);  						//串口1DMA开启
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE); 																			//串口1空闲中断
	HAL_UART_Receive_DMA(&huart3, UsartType3.usartDMA_rxBuf, RECEIVELEN);  						//串口3DMA开启
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE); 	
}

void vTaskInit()
{
	
	xTaskCreate( vTask1,                  /*指向任务函数的指针*/
						 "vTask1",               /*任务的文本名字,只会在调试中用到*/
						 128,                       /*栈深度,占用内存大小等于值x4*/
						 NULL,                      /*没有任务参数*/
						 1,                         /*任务优先级,0最小*/
						 NULL);        /*不会用到任务句柄*/
	xTaskCreate( vTask2,                  /*指向任务函数的指针*/
						 "vTask1",               /*任务的文本名字,只会在调试中用到*/
						 128,                       /*栈深度,占用内存大小等于值x4*/
						 NULL,                      /*没有任务参数*/
						 1,                         /*任务优先级,0最小*/
						 NULL);        /*不会用到任务句柄*/
	
	vTaskDelete(NULL);				//删除自己
	
}

void vTask1(void *pvParameters)
{
	for(;;)
	{
		printf("GC001\r\n");
		osDelay(1000);
	}
}

void vTask2(void *pvParameters)
{
	for(;;)
	{
		printf("测试24CM10\r\n");
		AT24CM01_WRITE(10,(uint8_t*)"0123456789",10);
		osDelay(2000);
		uint8_t test[10]="9876543210";
//		AT24CM01_READ(10,test,10);
		printf("%s\r\n",test);
		osDelay(5000);
	}
}   

