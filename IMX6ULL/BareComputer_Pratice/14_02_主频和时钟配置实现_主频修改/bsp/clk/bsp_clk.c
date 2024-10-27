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

  2.  日期: 2024.10.26
      作者: 钱锐
      内容:
          1) 新增主频时钟修改接口
      版本:V1.1.0          

*************************************************/

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "bsp_clk.h"


/// @brief 主频时钟修改
/// @param  
static void Bsp_Modify_MainFreqClock(void);

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

    Bsp_Modify_MainFreqClock();
}

static void Bsp_Modify_MainFreqClock(void)
{   
    /*
    1、系统主频的配置
        ①、要设置ARM内核主频为528MHz，设置CACRR寄存器的ARM_PODF位为2分频，然后设置PLL1=1056MHz即可。CACRR的bit3~0为ARM_PODF位，可设置0~7，分别对应1~8分频。应该设置CACRR寄存器的ARM_PODF=1。
        ②、设置PLL1=1056MHz。PLL1=pll1_sw_clk。pll1_sw_clk有两路可以选择，分别为pll1_main_clk，和step_clk，通过CCSR寄存器的pll1_sw_clk_sel位(bit2)来选择。为0的时候选择pll1_main_clk，为1的时候选额step_clk。
        ③、在修改PLL1的时候，也就是设置系统时钟的时候需要给6ULL一个临时的时钟，也就是step_clk。在修改PLL1的时候需要将pll1_sw_clk切换到step_clk上。
        ③、设置step_clk。Step_clk也有两路来源，由CCSR的step_sel位(bit8)来设置，为0的时候设置step_clk为osc=24MHz。为1的时候不重要，不用。
        ④、时钟切换成功以后就可以修改PLL1的值。
        ⑤、通过CCM_ANALOG_PLL_ARM寄存器的DIV_SELECT位(bit6~0)来设置PLL1的频率，公式位：
            Output = fref*DIV_SEL/2  1056=24*DIV_SEL/2=>DIEV_SEL=88。
        设置CCM_ANALOG_PLL_ARM寄存器的DIV_SELECT位=88即可。PLL1=1056MHz
        还要设置CCM_ANALOG_PLL_ARM寄存器的ENABLE位(bit13)为1，也就是使能输出。
        ⑥、在切换回PLL1之前，设置置CACRR寄存器的ARM_PODF=1！！切记。
    */
    
    //原来的主频时钟为396MHz,IMX6ULL支持498MHz、528MHz、696MHz、792MHz
    //初始化当前主频时钟为528MHz

    if (((CCM->CCSR >> 2) & 0x1) == 0)                          //保证当前时钟使用的是pll1_main_clk
    {
        CCM->CCSR &= ~(1 << 8);                                 //设置step_clk = osc_clk = 24MHz
        CCM->CCSR |= (1 << 2);                                  //pll1_sw_clk = step_clk = 24MHz
    }
    
    //设置PLL1 = 1056MHZ，经过2分频之后输出528MHz
    CCM_ANALOG->PLL_ARM = (1 << 13) | ((88 << 0) & 0x7f);       //Output = fref*DIV_SEL/2;  1056 = 24*DIV_SEL/2=>DIV_SEL=88
    CCM->CACRR = 1;                                             //设置2分频
    CCM->CCSR &= ~(1 << 2);                                     //设置pll1_sw_clk = pll_main_clk = 1056MHz
    
    //设置PLL1 = 696MHZ，经过1分频之后输出696MHz
    // CCM_ANALOG->PLL_ARM = (1 << 13) | ((58 << 0) & 0x7f);       //Output = fref*DIV_SEL/2;  696 = 24*DIV_SEL/2=>DIV_SEL=58
    // CCM->CACRR = 0;                                             //设置1分频
    // CCM->CCSR &= ~(1 << 2);                                     //设置pll1_sw_clk = pll_main_clk = 696MHZ
}
