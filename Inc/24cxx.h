/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __24CXX_H
#define __24CXX_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "main.h"
#include "gpio.h"
////////////////////////////////////////////////////////////////////////////////
//IIC1定义
////////////////////////////////////////////////////////////////////////////////
#define GPIO_PORT_I2C1	GPIOB			     // GPIO端口 
#define I2C1_SCL_PIN		SCL_Pin			 // 连接到SCL时钟线的GPIO 
#define I2C1_SDA_PIN		SDA_Pin			 // 连接到SDA数据线的GPIO 
 
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
//#define GPIO_PORT_I2C2	GPIOB			     // GPIO端口 
//#define I2C2_SCL_PIN		SCL2_Pin			 // 连接到SCL时钟线的GPIO 
//#define I2C2_SDA_PIN		SDA2_Pin			 // 连接到SDA数据线的GPIO 
// 
///* 定义读写SCL和SDA的宏 */
//#define I2C2_SCL_1()  GPIO_PORT_I2C2->BSRR = I2C2_SCL_PIN											// SCL = 1 
//#define I2C2_SCL_0()  GPIO_PORT_I2C2->BSRR = (uint32_t)I2C2_SCL_PIN << 16U  		// SCL = 0 
// 
//#define I2C2_SDA_1()  GPIO_PORT_I2C2->BSRR = I2C2_SDA_PIN   										// SDA = 1 
//#define I2C2_SDA_0()  GPIO_PORT_I2C2->BSRR = (uint32_t)I2C2_SDA_PIN << 16U  		// SDA = 0 
// 
//#define I2C2_SDA_READ()  (GPIO_PORT_I2C2->IDR & I2C2_SDA_PIN)										// 读SDA口线状态 
//#define I2C2_SCL_READ()  (GPIO_PORT_I2C2->IDR & I2C2_SCL_PIN)		// 读SCL口线状态 
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

