/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MPU6050.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.26
描  述: MPU6050 6轴姿态传感器模块
备  注:  
修改记录: 

  1.  日期: 2024.12.26
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "stm32f10x.h"                  // Device header

#include "MPU6050.h"
#include "MyI2C.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDR 0xD0				//原始地址为 1101000

void MPU6050_Init(void)
{
	MyI2C_Init();
	
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);		//配置电源管理器1
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);		//配置电源管理器2
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);		//配置采样率分频；设置当前为10分频
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);			//配置寄存器;取消外部同步,选择最平滑的滤波
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);	//不自测,陀螺仪传感器最大量程
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);	//不自测,加速度传感器最大量程;取消高通滤波
}

uint8_t MPU6050_ReadReg(uint8_t _Addr)
{
	uint8_t uchRecvByte = 0;
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDR | 0x0);
	MyI2C_RecvAck();
	MyI2C_SendByte(_Addr);
	MyI2C_RecvAck();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDR | 0x1);
	MyI2C_RecvAck();
	
	uchRecvByte = MyI2C_RecvByte();
	MyI2C_SendAck(1);
	MyI2C_Stop();	
	
	return uchRecvByte;
}

void MPU6050_WriteReg(uint8_t _Addr, uint8_t _Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDR | 0x0);
	MyI2C_RecvAck();
	MyI2C_SendByte(_Addr);
	MyI2C_RecvAck();
	MyI2C_SendByte(_Data);
	MyI2C_RecvAck();
	MyI2C_Stop();	
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




