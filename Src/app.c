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
	HAL_UART_Receive_DMA(&huart1, UsartType1.usartDMA_rxBuf, RECEIVELEN);  						//����1DMA����
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE); 																			//����1�����ж�
	HAL_UART_Receive_DMA(&huart3, UsartType3.usartDMA_rxBuf, RECEIVELEN);  						//����3DMA����
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE); 	
}

void vTaskInit()
{
	
	xTaskCreate( vTask1,                  /*ָ����������ָ��*/
						 "vTask1",               /*������ı�����,ֻ���ڵ������õ�*/
						 128,                       /*ջ���,ռ���ڴ��С����ֵx4*/
						 NULL,                      /*û���������*/
						 1,                         /*�������ȼ�,0��С*/
						 NULL);        /*�����õ�������*/
	xTaskCreate( vTask2,                  /*ָ����������ָ��*/
						 "vTask1",               /*������ı�����,ֻ���ڵ������õ�*/
						 128,                       /*ջ���,ռ���ڴ��С����ֵx4*/
						 NULL,                      /*û���������*/
						 1,                         /*�������ȼ�,0��С*/
						 NULL);        /*�����õ�������*/
	
	vTaskDelete(NULL);				//ɾ���Լ�
	
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
		printf("����24CM10\r\n");
		AT24CM01_WRITE(10,(uint8_t*)"0123456789",10);
		osDelay(2000);
		uint8_t test[10]="9876543210";
//		AT24CM01_READ(10,test,10);
		printf("%s\r\n",test);
		osDelay(5000);
	}
}   

