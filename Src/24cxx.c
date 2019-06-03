/* Includes ------------------------------------------------------------------*/

#include "24cxx.h"

#define SIZE_24CXX   131072
/*оƬ�ͺ�:24CM01  ��С:1024Kb  128KB  131072B*/
#define READP0_ID			0xA1
#define WRITEP0_ID		0xA0
#define READP1_ID			0xA3
#define WRITEP1_ID		0xA2
/*24CM01��Ϊ����64K�ֽڵ�ҳ*/
uint32_t ADDR_24Cxx	=	0;


static void i2c_Delay(void)
{
	uint8_t i;
	for (i = 0; i < 40; i++);
}
////////////////////////////////////////////////////////////////
//��ʼ�ź�
void i2c1_Start(void)
{
	// ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� 
	I2C1_SDA_1();
	I2C1_SCL_1();
	i2c_Delay();
	I2C1_SDA_0();
	i2c_Delay();
	I2C1_SCL_0();
	i2c_Delay();
}
 
//ֹͣ�ź�
void i2c1_Stop(void)
{
	// ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� 
	I2C1_SDA_0();
	I2C1_SCL_1();
	i2c_Delay();
	I2C1_SDA_1();
	i2c_Delay();
}
//����һ���ֽ�
void i2c1_SendByte(uint8_t _ucByte)
{
	uint8_t i;
	
	// �ȷ����ֽڵĸ�λbit7 
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
			 I2C1_SDA_1(); 	// �ͷ�����
		}
		_ucByte <<= 1;		// ����һ��bit 
		i2c_Delay();
	}
}
//��ȡһ���ֽ�
uint8_t i2c1_ReadByte(void)
{
	uint8_t i;
	uint8_t value;
	
	/* ������1��bitΪ���ݵ�bit7 */
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
 
//�ȴ�Ӧ���ź�
uint8_t i2c1_WaitAck(void)
{
	uint8_t re;
 
	I2C1_SDA_1();	/* CPU�ͷ�SDA���� */
//	i2c_Delay();
	I2C1_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	i2c_Delay();
 
	if (I2C1_SDA_READ())	/* CPU��ȡSDA����״̬ */
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
//Ӧ���ź�
void i2c1_Ack(void)
{
	I2C1_SDA_0();	/* CPU����SDA = 0 */
	i2c_Delay();
	I2C1_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	I2C1_SCL_0();
	i2c_Delay();
	I2C1_SDA_1();	/* CPU�ͷ�SDA���� */
}
 
 
uint8_t i2c1_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;
 
	if (I2C1_SDA_READ() && I2C1_SCL_READ())
	{
		i2c1_Start();		/* ���������ź� */
 
		/* �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ� */
		i2c1_SendByte(_Address | 0);
		ucAck = i2c1_WaitAck();	/* ����豸��ACKӦ�� */
 
		i2c1_Stop();			/* ����ֹͣ�ź� */
 
		return ucAck;
	}
	return 1;	/* I2C�����쳣 */
}
 
 
void  Device1_WriteData(uint8_t DeciveAddr,uint8_t *Data,int size)
{
    int count=size;
		uint8_t *pData=Data;
		//��ʼ�ź�
    i2c1_Start();    
    //����������ַ                         
    i2c1_SendByte(DeciveAddr);       
    //�ȴ�Ӧ��
    i2c1_WaitAck();                          
    while(count--)
		{
			//��������
			i2c1_SendByte(*pData++);                     
			//�ȴ�Ӧ��
			i2c1_WaitAck();   
		}			 
                       
    //�����ź�
    i2c1_Stop();     
}


uint8_t AT24CM01_WRITE(uint32_t address, uint8_t *write_data, uint32_t size)
{
	if(address+size > SIZE_24CXX)
	{
		return 0;
	}
	if(address+size<=0xffff)
	{
    i2c1_Start();								//��ʼ�ź�
		i2c1_SendByte(WRITEP0_ID); 	//����������ַ  
		i2c1_WaitAck(); 						//�ȴ�Ӧ��
		i2c1_SendByte((uint8_t)(address >> 8)); 	//����ǰ��λ��ַ  
		i2c1_WaitAck(); 													//�ȴ�Ӧ��
		i2c1_SendByte((uint8_t)(address >> 0)); 	//���ͺ��λ��ַ  
		i2c1_WaitAck(); 													//�ȴ�Ӧ��
		for(uint32_t i=0;i<size;i++)
		{
			i2c1_SendByte(*(write_data+i)); 	//��������  
			i2c1_WaitAck(); 									//�ȴ�Ӧ��
		}
		i2c1_Stop(); 								//�����ź�
	}
	else if(address<=0xffff && address+size>0xffff)
	{
    i2c1_Start();								//��ʼ�ź�
		i2c1_SendByte(WRITEP0_ID); 	//����������ַ  
		i2c1_WaitAck(); 						//�ȴ�Ӧ��
		i2c1_SendByte((uint8_t)(address >> 8)); 	//����ǰ��λ��ַ  
		i2c1_WaitAck(); 													//�ȴ�Ӧ��
		i2c1_SendByte((uint8_t)(address >> 0)); 	//���ͺ��λ��ַ  
		i2c1_WaitAck(); 													//�ȴ�Ӧ��
		for(uint32_t i=0;i<=0xffff-address;i++)
		{
			i2c1_SendByte(*(write_data+i)); 	//��������  
			i2c1_WaitAck(); 									//�ȴ�Ӧ��
		}
		i2c1_Stop(); 								//�����ź�
		/////////////////////////////////////////////////
		i2c_Delay();i2c_Delay();i2c_Delay();i2c_Delay();
		/////////////////////////////////////////////////
		i2c1_Start();								//��ʼ�ź�
		i2c1_SendByte(WRITEP1_ID); 	//����������ַ  
		i2c1_WaitAck(); 						//�ȴ�Ӧ��
		i2c1_SendByte(0x00); 				//����ǰ��λ��ַ  
		i2c1_WaitAck(); 						//�ȴ�Ӧ��
		i2c1_SendByte(0x00); 				//���ͺ��λ��ַ  
		i2c1_WaitAck(); 						//�ȴ�Ӧ��
		for(uint32_t i=0;i<=address+size-0xffff;i++)
		{
			i2c1_SendByte(*(write_data-0xffff+address+i)); 	//��������  
			i2c1_WaitAck(); 									//�ȴ�Ӧ��
		}
		i2c1_Stop(); 								//�����ź�
	}
	else if(address>0xffff)
	{
    i2c1_Start();								//��ʼ�ź�
		i2c1_SendByte(WRITEP1_ID); 	//����������ַ  
		i2c1_WaitAck(); 						//�ȴ�Ӧ��
		i2c1_SendByte((uint8_t)(address >> 24)); 	//����ǰ��λ��ַ  
		i2c1_WaitAck(); 													//�ȴ�Ӧ��
		i2c1_SendByte((uint8_t)(address >> 16)); 	//���ͺ��λ��ַ  
		i2c1_WaitAck(); 													//�ȴ�Ӧ��
		for(uint32_t i=0;i<size;i++)
		{
			i2c1_SendByte(*(write_data+i)); 	//��������  
			i2c1_WaitAck(); 									//�ȴ�Ӧ��
		}
		i2c1_Stop(); 								//�����ź�		
	}
	return 0;
}	

uint8_t AT24CM01_READ(uint32_t address,uint8_t* datacode,uint32_t size)
{
	i2c1_Start();								//��ʼ�ź�
	i2c1_SendByte(READP0_ID); 	//����������ַ  
	i2c1_WaitAck(); 						//�ȴ�Ӧ��
	i2c1_SendByte((uint8_t)(address >> 8)); 	//����ǰ��λ��ַ  
	i2c1_WaitAck(); 													//�ȴ�Ӧ��
	i2c1_SendByte((uint8_t)(address >> 0)); 	//���ͺ��λ��ַ  
	i2c1_WaitAck(); 													//�ȴ�Ӧ��
	
	i2c1_Start();								//��ʼ�ź�
	i2c1_SendByte(READP0_ID); 	//����������ַ  
	i2c1_WaitAck(); 						//�ȴ�Ӧ��
	for(uint32_t i=0;i<size-1;i++)
	{
		*(datacode+i)=i2c1_ReadByte();
		i2c1_Ack();
	}
	*(datacode+size-1)=i2c1_ReadByte();
	i2c1_Stop(); 								//�����ź�	
	return 0;
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
