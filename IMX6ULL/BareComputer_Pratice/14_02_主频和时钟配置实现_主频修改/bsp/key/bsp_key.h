/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	bsp_key.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.18
描  述: 实现key按键输入读取功能
备  注:
修改记录:

  1.  日期: 2024.08.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0      

*************************************************/

#ifndef __BSP_KEY_H_
#define __BSP_KEY_H_

enum Bsp_KeyInit
{
    BSP_KEY_NONE = 0,
    BSP_KEY0
};

/// @brief 初始化对应的按键
/// @param  
/// @return 
int Bsp_KeyInit(enum Bsp_KeyInit _Key);

/// @brief 获取当前按键输入状态（软件消抖）
/// @param _Key 按键
/// @param _Status 当前状态;0--按下;1--释放;
/// @return 
int GetKey_CurStatus(enum Bsp_KeyInit _Key, int* _Status);

#endif // !__BSP_KEY_H_



