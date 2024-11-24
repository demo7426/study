/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	I2C.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.24
描  述: I2C模块
备  注:  
修改记录: 

  1.  日期: 2024.11.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __I2C_H__
#define __I2C_H__

/// @brief 启动I2C
/// @param 无
/// @return 无
void I2C_Start(void);

/// @brief 停止I2C
/// @param 无
/// @return 无
void I2C_Stop(void);

/// @brief I2C发送一个字节的数据
/// @param 字节数据
/// @return 无
void I2C_SendByte(unsigned char _Data);

/// @brief I2C接收一个字节的数据
/// @param 无
/// @return 接收到的字节数据
unsigned char I2C_RecvByte(void);

/// @brief I2C发送一个确认码
/// @param 确认码
/// @return 无
void I2C_SendAck(unsigned char _Ack);

/// @brief I2C接收一个确认码
/// @param 接收到的码
/// @return 无
unsigned char I2C_RecvAck(void);

#endif