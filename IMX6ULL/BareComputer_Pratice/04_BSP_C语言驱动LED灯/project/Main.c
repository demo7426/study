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

int main(int argc, char* argv[])
{
    Bsp_InitClock();                    //时钟初始化
    Bsp_LedInit();                      //led初始化

    while (1)
    {
        Bsp_LedOn();
        Bsp_Delay(1000);

        Bsp_LedOff();
        Bsp_Delay(1000);
    }
    
    return 0;
}

