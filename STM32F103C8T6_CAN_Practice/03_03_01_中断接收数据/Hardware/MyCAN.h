/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MyCAN.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.11.28
描  述: CAN协议数据收发模块
备  注: 采用中断接收数据 
修改记录: 

  1.  日期: 2025.11.28
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __MYCAN_H__
#define __MYCAN_H__

#include "stm32f10x.h"                  // Device header

/// @brief CAN总线初始化
/// @param 无
/// @return 无
void MyCAN_Init(void);

/// @brief CAN总线发送数据
/// @param _ID id号
/// @param _pData 数据首地址
/// @param _Length 数据长度;范围:<=8字节
/// @return 无
void MyCAN_Transmit(CanTxMsg* _pCanTxMsg);

/// @brief CAN总线初始化
/// @param 无
/// @return 是否存在待接收的数据;0--不存在;1--存在
uint8_t MyCAN_ReceiveFlag(void);

/// @brief CAN总线发送数据
/// @param _pID id号
/// @param _Data 数据首地址;最少为8个字节大小
/// @param _pLength 数据长度
/// @return 无
void MyCAN_Receive(CanRxMsg* _pCanRxMsg);

#endif

