/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MPU6050.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.28
描  述: MPU6050 6轴姿态传感器模块
备  注: 使用硬件I2C进行通信
修改记录: 

  1.  日期: 2024.12.28
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "MPU6050.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDR 0xD0				//原始地址为 1101000

//事件超时等待函数
static void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
	uint16_t usCounter = 6000;
	
	while(I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
	{
		usCounter--;
		if(usCounter <= 0)
			break;
	}
}

void MPU6050_Init(void)
{
//	MyI2C_Init();
	
	GPIO_InitTypeDef tGPIO_InitTypeDef;
	I2C_InitTypeDef tI2C_InitTypeDef;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	tGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_OD;								//设置为复用开漏输出
	tGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	tGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &tGPIO_InitTypeDef);										//初始化GPIO
	
	tI2C_InitTypeDef.I2C_Mode = I2C_Mode_I2C;
	tI2C_InitTypeDef.I2C_ClockSpeed = 50000;									//当时钟频率小于100KHz时，占空比默认为1:1，此时I2C_DutyCycle用户设置无效
	tI2C_InitTypeDef.I2C_DutyCycle = I2C_DutyCycle_2;							//设置占空比
	tI2C_InitTypeDef.I2C_Ack = I2C_Ack_Enable;									//使能是否自动应答
	tI2C_InitTypeDef.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	//I2C自身地址长度
	tI2C_InitTypeDef.I2C_OwnAddress1 = 0x00;									//I2C自身地址	
	I2C_Init(I2C2, &tI2C_InitTypeDef);
	
	I2C_Cmd(I2C2, ENABLE);
	
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);									//配置电源管理器1
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);									//配置电源管理器2
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);									//配置采样率分频；设置当前为10分频
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);										//配置寄存器;取消外部同步,选择最平滑的滤波
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);								//不自测,陀螺仪传感器最大量程
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);								//不自测,加速度传感器最大量程;取消高通滤波
}

uint8_t MPU6050_ReadReg(uint8_t _Addr)
{
	uint8_t uchRecvByte = 0;
	
//	MyI2C_Start();
//	MyI2C_SendByte(MPU6050_ADDR | 0x0);
//	MyI2C_RecvAck();
//	MyI2C_SendByte(_Addr);
//	MyI2C_RecvAck();
//	
//	MyI2C_Start();
//	MyI2C_SendByte(MPU6050_ADDR | 0x1);
//	MyI2C_RecvAck();
//	
//	uchRecvByte = MyI2C_RecvByte();
//	MyI2C_SendAck(1);
//	MyI2C_Stop();	
	
	I2C_GenerateSTART(I2C2, ENABLE);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
		
	I2C_Send7bitAddress(I2C2, MPU6050_ADDR, I2C_Direction_Transmitter);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	
	I2C_SendData(I2C2, _Addr);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
	
	I2C_GenerateSTART(I2C2, ENABLE);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
	
	I2C_Send7bitAddress(I2C2, MPU6050_ADDR, I2C_Direction_Receiver);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);
	
	I2C_AcknowledgeConfig(I2C2, DISABLE);
	I2C_GenerateSTOP(I2C2, ENABLE);
	
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);
	uchRecvByte = I2C_ReceiveData(I2C2);
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);
	
	return uchRecvByte;
}

void MPU6050_WriteReg(uint8_t _Addr, uint8_t _Data)
{
//	MyI2C_Start();
//	MyI2C_SendByte(MPU6050_ADDR | 0x0);
//	MyI2C_RecvAck();
//	MyI2C_SendByte(_Addr);
//	MyI2C_RecvAck();
//	MyI2C_SendByte(_Data);
//	MyI2C_RecvAck();
//	MyI2C_Stop();	
	
	I2C_GenerateSTART(I2C2, ENABLE);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
	
	I2C_Send7bitAddress(I2C2, MPU6050_ADDR, I2C_Direction_Transmitter);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	
	I2C_SendData(I2C2, _Addr);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
	
	I2C_SendData(I2C2, _Data);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	
	I2C_GenerateSTOP(I2C2, ENABLE);
}

uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

void MPU6050_GetData(int16_t *_pAccX, int16_t *_pAccY, int16_t *_pAccZ,
						int16_t *_pGyroX, int16_t *_pGyroY, int16_t *_pGyroZ)
{
	uint8_t uchDataH, uchDataL;
	
	uchDataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	uchDataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*_pAccX = uchDataH << 8 | uchDataL;
	
	uchDataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	uchDataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*_pAccY = uchDataH << 8 | uchDataL;
	
	uchDataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	uchDataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*_pAccZ = uchDataH << 8 | uchDataL;
	
	uchDataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	uchDataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*_pGyroX = uchDataH << 8 | uchDataL;
	
	uchDataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	uchDataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*_pGyroY = uchDataH << 8 | uchDataL;
	
	uchDataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	uchDataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*_pGyroZ = uchDataH << 8 | uchDataL;
}




