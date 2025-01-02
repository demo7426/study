/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Serial.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.22
描  述: 串口模块
备  注:  
修改记录: 

  1.  日期: 2024.12.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <stdio.h>

/// @brief 初始化
/// @param 无
/// @return 无
void Serial_Init(void);

/// @brief 发送一个字节的数据
/// @param _Byte--字节数据
/// @return 无
void Serial_SendByte(unsigned char _Byte);

/// @brief 发送单字节数组
/// @param _pAddr--起始地址
/// @param _Size--数组个数
/// @return 无
void Serial_SendArray(unsigned char* _pAddr, unsigned short _Size);

/// @brief 发送字符串
/// @param _Content--字符串内容
/// @return 无
void Serial_SendString(char* _Content);

/// @brief 发送一个数字
/// @param _Number--数字
/// @param _NumLen--数字有效长度
/// @return 无
void Serial_SendNumber(unsigned int _Number, unsigned char _NumLen);

/// @brief 发送格式化数据
/// @param format--格式化字符串
/// @param ...--待匹配参数
/// @return 无
void Serial_Printf(char* format, ...);

/// @brief 获取串口是否有接收数据标志
/// @param 无
/// @return 0--未接收到数据;1--接收到数据;
unsigned char Serial_GetRxFlag(void);

/// @brief 获取串口接收的数据
/// @param 无
/// @return 接收数据
unsigned char Serial_GetRxData(void);

#endif
