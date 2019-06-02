/* Includes ------------------------------------------------------------------*/
#include "tm1650.h"

const uint8_t Nixie_light_Data[20] = {	
	0x3f, 0x06, 0x5b, 0x4f,
	0x66, 0x6d, 0x7d, 0x07,
	0x7f, 0x6f, 0x77, 0x7c,
	0x39, 0x5e, 0x79, 0x71,
	0x40, 0x09, 0x00, 0x63};		//0-F数据表 - H 空
 
uint8_t LEDS_light_Data[23] = {	
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00};		//LED开关表,0关,不为0亮(1)

static void i2c_Delay(void)
{
	uint8_t i;
	for (i = 0; i < 40; i++);
}
////////////////////////////////////////////////////////////////
//开始信号
void i2c1_Start(void)
{
	// 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 
	I2C1_SDA_1();
	I2C1_SCL_1();
	i2c_Delay();
	I2C1_SDA_0();
	i2c_Delay();
	I2C1_SCL_0();
	i2c_Delay();
}
 
//停止信号
void i2c1_Stop(void)
{
	// 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 
	I2C1_SDA_0();
	I2C1_SCL_1();
	i2c_Delay();
	I2C1_SDA_1();
	i2c_Delay();
}
//发送一个字节
void i2c1_SendByte(uint8_t _ucByte)
{
	uint8_t i;
	
	// 先发送字节的高位bit7 
	for (i = 0; i < 8; i++)
	{
		if (_ucByte & 0x80)
		{
			I2C1_SDA_1();
		}
		else
		{
			I2C1_SDA_0();
		}
		i2c_Delay();
		I2C1_SCL_1();
		i2c_Delay();
		I2C1_SCL_0();
		if (i == 7)
		{
			 I2C1_SDA_1(); 	// 释放总线
		}
		_ucByte <<= 1;		// 左移一个bit 
		i2c_Delay();
	}
}
//读取一个字节
uint8_t i2c1_ReadByte(void)
{
	uint8_t i;
	uint8_t value;
	
	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		I2C1_SCL_1();
		i2c_Delay();
		if (I2C1_SDA_READ())
		{
			value++;
		}
		I2C1_SCL_0();
		i2c_Delay();
	}
	return value;
}
 
//等待应答信号
uint8_t i2c1_WaitAck(void)
{
	uint8_t re;
 
	I2C1_SDA_1();	/* CPU释放SDA总线 */
//	i2c_Delay();
	I2C1_SCL_1();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	i2c_Delay();
 
	if (I2C1_SDA_READ())	/* CPU读取SDA口线状态 */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
 
	I2C1_SCL_0();
	i2c_Delay();
	return re;
}
//应答信号
void i2c1_Ack(void)
{
	I2C1_SDA_0();	/* CPU驱动SDA = 0 */
	i2c_Delay();
	I2C1_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	I2C1_SCL_0();
	i2c_Delay();
	I2C1_SDA_1();	/* CPU释放SDA总线 */
}
 
 
uint8_t i2c1_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;
 
	if (I2C1_SDA_READ() && I2C1_SCL_READ())
	{
		i2c1_Start();		/* 发送启动信号 */
 
		/* 发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传 */
		i2c1_SendByte(_Address | 0);
		ucAck = i2c1_WaitAck();	/* 检测设备的ACK应答 */
 
		i2c1_Stop();			/* 发送停止信号 */
 
		return ucAck;
	}
	return 1;	/* I2C总线异常 */
}
 
 
void  Device1_WriteData(uint8_t DeciveAddr,uint8_t *Data,int size)
{
    int count=size;
		uint8_t *pData=Data;
		//起始信号
    i2c1_Start();    
    //发送器件地址                         
    i2c1_SendByte(DeciveAddr);       
    //等待应答
    i2c1_WaitAck();                          
    while(count--)
		{
			//发送数据
			i2c1_SendByte(*pData++);                     
			//等待应答
			i2c1_WaitAck();   
		}			 
                       
    //结束信号
    i2c1_Stop();     
}

void Nixie_light_SET(uint8_t brightness)		//0-8级亮度
{
		i2c1_Start();
		i2c1_SendByte(0x48);
		i2c1_WaitAck();
		if		 (brightness == 0)
			i2c1_SendByte(0x00);
		else if(brightness == 1)
			i2c1_SendByte(0x11);
		else if(brightness == 2)
			i2c1_SendByte(0x21);
		else if(brightness == 3)
			i2c1_SendByte(0x31);
		else if(brightness == 4)
			i2c1_SendByte(0x41);
		else if(brightness == 5)
			i2c1_SendByte(0x51);
		else if(brightness == 6)
			i2c1_SendByte(0x61);
		else if(brightness == 7)
			i2c1_SendByte(0x71);
		else if(brightness == 8)
			i2c1_SendByte(0x01);
		i2c1_WaitAck();
		i2c1_Stop();	
}

void Nixie_light_Display(uint8_t bit,uint8_t data,uint8_t point)
{
		i2c1_Start();
		if		 (bit == 1)
			i2c1_SendByte(0x68);
		else if(bit == 2)
			i2c1_SendByte(0x6A);
		else if(bit == 3)
			i2c1_SendByte(0x6C);
		else if(bit == 4)
			i2c1_SendByte(0x6E);
		i2c1_WaitAck();
		if(point)
			i2c1_SendByte(Nixie_light_Data[data]+0x80);
		else 
			i2c1_SendByte(Nixie_light_Data[data]);
		i2c1_WaitAck();
		i2c1_Stop();
		
}

////////////////////////////////////////////////////////////////
//开始信号
void i2c2_Start(void)
{
	// 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 
	I2C2_SDA_1();
	I2C2_SCL_1();
	i2c_Delay();
	I2C2_SDA_0();
	i2c_Delay();
	I2C2_SCL_0();
	i2c_Delay();
}
 
//停止信号
void i2c2_Stop(void)
{
	// 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 
	I2C2_SDA_0();
	I2C2_SCL_1();
	i2c_Delay();
	I2C2_SDA_1();
	i2c_Delay();
}
//发送一个字节
void i2c2_SendByte(uint8_t _ucByte)
{
	uint8_t i;
	
	// 先发送字节的高位bit7 
	for (i = 0; i < 8; i++)
	{
		if (_ucByte & 0x80)
		{
			I2C2_SDA_1();
		}
		else
		{
			I2C2_SDA_0();
		}
		i2c_Delay();
		I2C2_SCL_1();
		i2c_Delay();
		I2C2_SCL_0();
		if (i == 7)
		{
			 I2C2_SDA_1(); 	// 释放总线
		}
		_ucByte <<= 1;		// 左移一个bit 
		i2c_Delay();
	}
}
//读取一个字节
uint8_t i2c2_ReadByte(void)
{
	uint8_t i;
	uint8_t value;
	
	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		I2C2_SCL_1();
		i2c_Delay();
		if (I2C2_SDA_READ())
		{
			value++;
		}
		I2C2_SCL_0();
		i2c_Delay();
	}
	return value;
}
 
//等待应答信号
uint8_t i2c2_WaitAck(void)
{
	uint8_t re;
 
	I2C2_SDA_1();	/* CPU释放SDA总线 */
//	i2c_Delay();
	I2C2_SCL_1();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	i2c_Delay();
 
	if (I2C2_SDA_READ())	/* CPU读取SDA口线状态 */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
 
	I2C2_SCL_0();
	i2c_Delay();
	return re;
}
//应答信号
void i2c2_Ack(void)
{
	I2C2_SDA_0();	/* CPU驱动SDA = 0 */
	i2c_Delay();
	I2C2_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	I2C2_SCL_0();
	i2c_Delay();
	I2C2_SDA_1();	/* CPU释放SDA总线 */
}
 
 
uint8_t i2c2_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;
 
	if (I2C2_SDA_READ() && I2C2_SCL_READ())
	{
		i2c2_Start();		/* 发送启动信号 */
 
		/* 发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传 */
		i2c2_SendByte(_Address | 0);
		ucAck = i2c2_WaitAck();	/* 检测设备的ACK应答 */
 
		i2c2_Stop();			/* 发送停止信号 */
 
		return ucAck;
	}
	return 1;	/* I2C总线异常 */
}
 
 
void  Device2_WriteData(uint8_t DeciveAddr,uint8_t *Data,int size)
{
    int count=size;
		uint8_t *pData=Data;
		//起始信号
    i2c2_Start();    
    //发送器件地址                         
    i2c2_SendByte(DeciveAddr);       
    //等待应答
    i2c2_WaitAck();                          
    while(count--)
		{
			//发送数据
			i2c2_SendByte(*pData++);                     
			//等待应答
			i2c2_WaitAck();   
		}			 
                       
    //结束信号
    i2c2_Stop();     
}

void LEDS_light_SET(uint8_t brightness)		//0-8级亮度
{
		i2c2_Start();
		i2c2_SendByte(0x48);
		i2c2_WaitAck();
		if		 (brightness == 0)
			i2c2_SendByte(0x00);
		else if(brightness == 1)
			i2c2_SendByte(0x11);
		else if(brightness == 2)
			i2c1_SendByte(0x21);
		else if(brightness == 3)
			i2c2_SendByte(0x31);
		else if(brightness == 4)
			i2c2_SendByte(0x41);
		else if(brightness == 5)
			i2c2_SendByte(0x51);
		else if(brightness == 6)
			i2c2_SendByte(0x61);
		else if(brightness == 7)
			i2c2_SendByte(0x71);
		else if(brightness == 8)
			i2c2_SendByte(0x01);
		i2c2_WaitAck();
		i2c2_Stop();	
}

void LEDS_Display(uint8_t bit,uint8_t data)
{
		if(data != 0)
			LEDS_light_Data[bit] = 0x01;
		else
			LEDS_light_Data[bit] = 0x00;
		
		data=0;
		for(uint8_t i=0;i<8;i++)
		{
			data += (LEDS_light_Data[i]<<(i-0));
		}
		
		i2c2_Start();
		i2c2_SendByte(0x68);
		i2c2_WaitAck();
		i2c2_SendByte(data);
		i2c2_WaitAck();
		i2c2_Stop();
		
		data=0;
		for(uint8_t i=8;i<16;i++)
		{
			data += (LEDS_light_Data[i]<<(i-8));
		}
		
		i2c2_Start();
		i2c2_SendByte(0x6A);
		i2c2_WaitAck();
		i2c2_SendByte(data);
		i2c2_WaitAck();
		i2c2_Stop();
		
		data=0;
		for(uint8_t i=16;i<23;i++)
		{
			data += (LEDS_light_Data[i]<<(i-16));
		}
		
		i2c2_Start();
		i2c2_SendByte(0x6C);
		i2c2_WaitAck();
		i2c2_SendByte(data);
		i2c2_WaitAck();
		i2c2_Stop();
		
}





/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
