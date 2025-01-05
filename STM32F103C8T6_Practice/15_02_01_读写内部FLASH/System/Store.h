/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Store.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.06
描  述: 内部Flash数据存储模块
备  注:  
修改记录: 

  1.  日期: 2025.01.06
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __STORE_H__
#define __STORE_H__

extern uint16_t g_usStoreData[512];

/// @brief 初始化
/// @param 无
/// @return 无
void Store_Init(void);

/// @brief 保存当前的数据
/// @param 无
/// @return 无
void Store_Save(void);

/// @brief 清除当前的数据
/// @param 无
/// @return 无
void Store_Clear(void);

#endif
