/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __24CXX_H
#define __24CXX_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "main.h"
#include "gpio.h"
////////////////////////////////////////////////////////////////////////////////
//IIC1����
////////////////////////////////////////////////////////////////////////////////
#define GPIO_PORT_I2C1	GPIOB			     // GPIO�˿� 
#define I2C1_SCL_PIN		SCL_Pin			 // ���ӵ�SCLʱ���ߵ�GPIO 
#define I2C1_SDA_PIN		SDA_Pin			 // ���ӵ�SDA�����ߵ�GPIO 
 
/* �����дSCL��SDA�ĺ� */
#define I2C1_SCL_1()  GPIO_PORT_I2C1->BSRR = I2C1_SCL_PIN											// SCL = 1 
#define I2C1_SCL_0()  GPIO_PORT_I2C1->BSRR = (uint32_t)I2C1_SCL_PIN << 16U  		// SCL = 0 
 
#define I2C1_SDA_1()  GPIO_PORT_I2C1->BSRR = I2C1_SDA_PIN   										// SDA = 1 
#define I2C1_SDA_0()  GPIO_PORT_I2C1->BSRR = (uint32_t)I2C1_SDA_PIN << 16U  		// SDA = 0 
 
#define I2C1_SDA_READ()  (GPIO_PORT_I2C1->IDR & I2C1_SDA_PIN)										// ��SDA����״̬ 
#define I2C1_SCL_READ()  (GPIO_PORT_I2C1->IDR & I2C1_SCL_PIN)		// ��SCL����״̬ 
////////////////////////////////////////////////////////////////////////////////
//IIC2����
////////////////////////////////////////////////////////////////////////////////
//#define GPIO_PORT_I2C2	GPIOB			     // GPIO�˿� 
//#define I2C2_SCL_PIN		SCL2_Pin			 // ���ӵ�SCLʱ���ߵ�GPIO 
//#define I2C2_SDA_PIN		SDA2_Pin			 // ���ӵ�SDA�����ߵ�GPIO 
// 
///* �����дSCL��SDA�ĺ� */
//#define I2C2_SCL_1()  GPIO_PORT_I2C2->BSRR = I2C2_SCL_PIN											// SCL = 1 
//#define I2C2_SCL_0()  GPIO_PORT_I2C2->BSRR = (uint32_t)I2C2_SCL_PIN << 16U  		// SCL = 0 
// 
//#define I2C2_SDA_1()  GPIO_PORT_I2C2->BSRR = I2C2_SDA_PIN   										// SDA = 1 
//#define I2C2_SDA_0()  GPIO_PORT_I2C2->BSRR = (uint32_t)I2C2_SDA_PIN << 16U  		// SDA = 0 
// 
//#define I2C2_SDA_READ()  (GPIO_PORT_I2C2->IDR & I2C2_SDA_PIN)										// ��SDA����״̬ 
//#define I2C2_SCL_READ()  (GPIO_PORT_I2C2->IDR & I2C2_SCL_PIN)		// ��SCL����״̬ 
////////////////////////////////////////////////////////////////////////////////
//����ܿ��ƺ���
////////////////////////////////////////////////////////////////////////////////
void i2c1_Start(void);
//ֹͣ�ź�
void i2c1_Stop(void);
//����һ���ֽ�
void i2c1_SendByte(uint8_t _ucByte);
//��ȡһ���ֽ�
uint8_t i2c1_ReadByte(void);
//�ȴ�Ӧ���ź�
uint8_t i2c1_WaitAck(void);
//Ӧ���ź�
void i2c1_Ack(void);
//����豸
uint8_t i2c1_CheckDevice(uint8_t _Address);
//��������
void  Device1_WriteData(uint8_t DeciveAddr,uint8_t *Data,int size);

uint8_t AT24CM01_WRITE(uint32_t address, uint8_t *write_data, uint32_t size);

uint8_t AT24CM01_READ(uint32_t address,uint8_t* datacode,uint32_t size);



////////////////////////////////////////////////////////////////////////////////


#endif  

/**
  * @}
  */

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

