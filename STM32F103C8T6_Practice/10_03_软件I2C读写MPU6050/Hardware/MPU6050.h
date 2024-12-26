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

#ifndef __MPU6050_H__
#define __MPU6050_H__

/// @brief MPU6050初始化
/// @param 无
/// @return 无
void MPU6050_Init(void);

/// @brief 读取MPU6050指定地址数据
/// @param _Addr--MPU6050地址
/// @return 读取到的数据
uint8_t MPU6050_ReadReg(uint8_t _Addr);

/// @brief 写入数据到MPU6050指定地址
/// @param _Addr--MPU6050地址
/// @param _Data--写入数据
/// @return 无
void MPU6050_WriteReg(uint8_t _Addr, uint8_t _Data);

/// @brief 获取MPU6050硬件ID
/// @param _无
/// @return 硬件ID
uint8_t MPU6050_GetID(void);

/// @brief 获取MPU6050 3轴加速度、3轴角速度
/// @param __pAccX--x轴加速度;_pAccY--y轴加速度;_pAccZ--z轴加速度;_pGyroX--x轴角速度;_pGyroY--y轴角速度;_pGyroZ--z轴角速度;
/// @return 无
void MPU6050_GetData(int16_t *_pAccX, int16_t *_pAccY, int16_t *_pAccZ,
						int16_t *_pGyroX, int16_t *_pGyroY, int16_t *_pGyroZ);

#endif
