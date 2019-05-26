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

void vTask1(void *pvParameters)
{
	for(;;)
	{
		printf("GC002\r\n");
		osDelay(2000);
	}
}
   
