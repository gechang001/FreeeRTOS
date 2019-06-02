/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __tm1650_H
#define __tm1650_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "main.h"
#include "gpio.h"
////////////////////////////////////////////////////////////////////////////////
//IIC1����
////////////////////////////////////////////////////////////////////////////////
#define GPIO_PORT_I2C1	GPIOA			     // GPIO�˿� 
#define I2C1_SCL_PIN		SCL1_Pin			 // ���ӵ�SCLʱ���ߵ�GPIO 
#define I2C1_SDA_PIN		SDA1_Pin			 // ���ӵ�SDA�����ߵ�GPIO 
 
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
#define GPIO_PORT_I2C2	GPIOB			     // GPIO�˿� 
#define I2C2_SCL_PIN		SCL2_Pin			 // ���ӵ�SCLʱ���ߵ�GPIO 
#define I2C2_SDA_PIN		SDA2_Pin			 // ���ӵ�SDA�����ߵ�GPIO 
 
/* �����дSCL��SDA�ĺ� */
#define I2C2_SCL_1()  GPIO_PORT_I2C2->BSRR = I2C2_SCL_PIN											// SCL = 1 
#define I2C2_SCL_0()  GPIO_PORT_I2C2->BSRR = (uint32_t)I2C2_SCL_PIN << 16U  		// SCL = 0 
 
#define I2C2_SDA_1()  GPIO_PORT_I2C2->BSRR = I2C2_SDA_PIN   										// SDA = 1 
#define I2C2_SDA_0()  GPIO_PORT_I2C2->BSRR = (uint32_t)I2C2_SDA_PIN << 16U  		// SDA = 0 
 
#define I2C2_SDA_READ()  (GPIO_PORT_I2C2->IDR & I2C2_SDA_PIN)										// ��SDA����״̬ 
#define I2C2_SCL_READ()  (GPIO_PORT_I2C2->IDR & I2C2_SCL_PIN)		// ��SCL����״̬ 
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

void Nixie_light_SET(uint8_t brightness);		
//�����0-8����������(����)
void Nixie_light_Display(uint8_t bit,uint8_t data,uint8_t point);
//�������ʾ,λ��(1-4),����(0-F),����С����

////////////////////////////////////////////////////////////////////////////////
//ָʾ�ƿ��ƺ���
////////////////////////////////////////////////////////////////////////////////

void i2c2_Start(void);
//ֹͣ�ź�
void i2c2_Stop(void);
//����һ���ֽ�
void i2c2_SendByte(uint8_t _ucByte);
//��ȡһ���ֽ�
uint8_t i2c2_ReadByte(void);
//�ȴ�Ӧ���ź�
uint8_t i2c2_WaitAck(void);
//Ӧ���ź�
void i2c2_Ack(void);
//����豸
uint8_t i2c2_CheckDevice(uint8_t _Address);
//��������
void  Device2_WriteData(uint8_t DeciveAddr,uint8_t *Data,int size);

void LEDS_light_SET(uint8_t brightness);		
//ָʾ��0-8����������(����)
void LEDS_Display(uint8_t bit,uint8_t data);
//ָʾ����ʾ,���(0-22),����(0-1,Ϊ1��)


#endif  

/**
  * @}
  */

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

