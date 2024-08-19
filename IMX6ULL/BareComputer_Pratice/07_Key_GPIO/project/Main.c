/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V1.1.0     新建日期: 2024.05.24
描  述: 入口函数文件
备  注:
修改记录:

  1.  日期: 2024.05.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0
  2.  日期: 2024.08.04
      作者: 钱锐
      内容:
          1) 使用C语言实现LED闪烁；
      版本:V1.1.0      

*************************************************/

#include "bsp_led.h"
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_key.h"

int main(int argc, char* argv[])
{
    unsigned int unCount = 0;
    const unsigned int unFreq = 50;                 //次数
    int nCurLedStatus = 0;                          //当前led灯的状态
    int nCurKey0Status = 0;                         //当前按键状态

    Bsp_InitClock();                                //时钟初始化
    Bsp_LedInit();                                  //led初始化
    Bsp_BeepInit();                                 //蜂鸣器初始化
    Bsp_KeyInit(BSP_KEY0);                          //按键初始化

    while (1)
    {
        ++unCount;

        if (unCount >= unFreq)                      //处理led灯
        {
            Bsp_LedSwitchStatus(nCurLedStatus);
            
            nCurLedStatus = !nCurLedStatus;
            unCount = 0;
        }
        
        if(GetKey_CurStatus(BSP_KEY0, &nCurKey0Status) != 0)
            break;
            
        if (nCurKey0Status == 0)
            Bsp_Beep_SetStatus(1);
        else
            Bsp_Beep_SetStatus(0);

        Bsp_Delay(10);
    }
    
    return 0;
}

