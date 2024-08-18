/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	bsp_clk.c
作  者:	钱锐      版本: V1.1.0     新建日期: 2024.08.11
描  述: bsp时钟文件
备  注:
修改记录:

  1.  日期: 2024.08.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "bsp_clk.h"

/// @brief 初始化外设时钟
void Bsp_InitClock(void)
{
    CCM->CCGR0 = 0xffffffff;
    CCM->CCGR1 = 0xffffffff;
    CCM->CCGR2 = 0xffffffff;
    CCM->CCGR3 = 0xffffffff;
    CCM->CCGR4 = 0xffffffff;
    CCM->CCGR5 = 0xffffffff;
    CCM->CCGR6 = 0xffffffff;
}

