/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __tm1650_H
#define __tm1650_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "main.h"
#include "gpio.h"
////////////////////////////////////////////////////////////////////////////////
//IIC1定义
////////////////////////////////////////////////////////////////////////////////
#define GPIO_PORT_I2C1	GPIOA			     // GPIO端口 
#define I2C1_SCL_PIN		SCL1_Pin			 // 连接到SCL时钟线的GPIO 
#define I2C1_SDA_PIN		SDA1_Pin			 // 连接到SDA数据线的GPIO 
 
/* 定义读写SCL和SDA的宏 */
#define I2C1_SCL_1()  GPIO_PORT_I2C1->BSRR = I2C1_SCL_PIN											// SCL = 1 
#define I2C1_SCL_0()  GPIO_PORT_I2C1->BSRR = (uint32_t)I2C1_SCL_PIN << 16U  		// SCL = 0 
 
#define I2C1_SDA_1()  GPIO_PORT_I2C1->BSRR = I2C1_SDA_PIN   										// SDA = 1 
#define I2C1_SDA_0()  GPIO_PORT_I2C1->BSRR = (uint32_t)I2C1_SDA_PIN << 16U  		// SDA = 0 
 
#define I2C1_SDA_READ()  (GPIO_PORT_I2C1->IDR & I2C1_SDA_PIN)										// 读SDA口线状态 
#define I2C1_SCL_READ()  (GPIO_PORT_I2C1->IDR & I2C1_SCL_PIN)		// 读SCL口线状态 
////////////////////////////////////////////////////////////////////////////////
//IIC2定义
////////////////////////////////////////////////////////////////////////////////
#define GPIO_PORT_I2C2	GPIOB			     // GPIO端口 
#define I2C2_SCL_PIN		SCL2_Pin			 // 连接到SCL时钟线的GPIO 
#define I2C2_SDA_PIN		SDA2_Pin			 // 连接到SDA数据线的GPIO 
 
/* 定义读写SCL和SDA的宏 */
#define I2C2_SCL_1()  GPIO_PORT_I2C2->BSRR = I2C2_SCL_PIN											// SCL = 1 
#define I2C2_SCL_0()  GPIO_PORT_I2C2->BSRR = (uint32_t)I2C2_SCL_PIN << 16U  		// SCL = 0 
 
#define I2C2_SDA_1()  GPIO_PORT_I2C2->BSRR = I2C2_SDA_PIN   										// SDA = 1 
#define I2C2_SDA_0()  GPIO_PORT_I2C2->BSRR = (uint32_t)I2C2_SDA_PIN << 16U  		// SDA = 0 
 
#define I2C2_SDA_READ()  (GPIO_PORT_I2C2->IDR & I2C2_SDA_PIN)										// 读SDA口线状态 
#define I2C2_SCL_READ()  (GPIO_PORT_I2C2->IDR & I2C2_SCL_PIN)		// 读SCL口线状态 
////////////////////////////////////////////////////////////////////////////////
//数码管控制函数
////////////////////////////////////////////////////////////////////////////////
void i2c1_Start(void);
//停止信号
void i2c1_Stop(void);
//发送一个字节
void i2c1_SendByte(uint8_t _ucByte);
//读取一个字节
uint8_t i2c1_ReadByte(void);
//等待应答信号
uint8_t i2c1_WaitAck(void);
//应答信号
void i2c1_Ack(void);
//检查设备
uint8_t i2c1_CheckDevice(uint8_t _Address);
//发送数据
void  Device1_WriteData(uint8_t DeciveAddr,uint8_t *Data,int size);

void Nixie_light_SET(uint8_t brightness);		
//数码管0-8级亮度设置(必须)
void Nixie_light_Display(uint8_t bit,uint8_t data,uint8_t point);
//数码管显示,位数(1-4),数据(0-F),有无小数点

////////////////////////////////////////////////////////////////////////////////
//指示灯控制函数
////////////////////////////////////////////////////////////////////////////////

void i2c2_Start(void);
//停止信号
void i2c2_Stop(void);
//发送一个字节
void i2c2_SendByte(uint8_t _ucByte);
//读取一个字节
uint8_t i2c2_ReadByte(void);
//等待应答信号
uint8_t i2c2_WaitAck(void);
//应答信号
void i2c2_Ack(void);
//检查设备
uint8_t i2c2_CheckDevice(uint8_t _Address);
//发送数据
void  Device2_WriteData(uint8_t DeciveAddr,uint8_t *Data,int size);

void LEDS_light_SET(uint8_t brightness);		
//指示灯0-8级亮度设置(必须)
void LEDS_Display(uint8_t bit,uint8_t data);
//指示灯显示,编号(0-22),数据(0-1,为1亮)


#endif  

/**
  * @}
  */

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

