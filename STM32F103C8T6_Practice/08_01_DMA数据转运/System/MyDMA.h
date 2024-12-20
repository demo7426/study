/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MyDMA.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.20
描  述: DMA数据转运模块
备  注: stm32f103c8t6只有一个DMA（7个通道）
修改记录: 

  1.  日期: 2024.12.20
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __MYDMA_H__
#define __MYDMA_H__

/// @brief 初始化
/// @param _SrcAddr--源地址
/// @param _DesAddr--目的地址
/// @param _Count--待转运数据数量
/// @return 无
void MyDMA_Init(unsigned int _SrcAddr, unsigned int _DesAddr, unsigned int _Count);

/// @brief 转运数据
/// @param 无
/// @return 无
void MyDMA_Transfer(void);

#endif
