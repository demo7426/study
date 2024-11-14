/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	UART.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.14
描  述: 串口模块
备  注:  
修改记录: 

  1.  日期: 2024.11.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __UART_H__
#define __UART_H__

/// @brief 串口初始化
/// @param 无
/// @return 无
void UART_Init(void);

/// @brief 串口发送数据
/// @param 待发送数据
/// @return 无
void UART_SendByte(char _Value);

#endif