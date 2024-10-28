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

/// @brief 其它时钟的修改
/// @param  
static void Bsp_Modify_OtherClock(void);

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
    Bsp_Modify_OtherClock();
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

    // 设置PLL1 = 696MHZ，经过1分频之后输出696MHz
    // CCM_ANALOG->PLL_ARM = (1 << 13) | ((58 << 0) & 0x7f);       //Output = fref*DIV_SEL/2;  696 = 24*DIV_SEL/2=>DIV_SEL=58
    // CCM->CACRR = 0;                                             //设置1分频
    // CCM->CCSR &= ~(1 << 2);                                     //设置pll1_sw_clk = pll_main_clk = 696MHZ
}

static void Bsp_Modify_OtherClock(void)
{
    /*    
    2、各个PLL时钟的配置
        PLL2和PLL3。PLL2固定为528MHz，PLL3固定为480MHz。
        ①、初始化PLL2_PFD0~PFD3。寄存器CCM_ANALOG_PFD_528用于设置4路PFD的时钟。比如PFD0= 528*18/PFD0_FRAC。设置PFD0_FRAC位即可。比如PLL2_PFD0=352M=528*18/PFD0_FRAC，因此FPD0_FRAC=27。

        ②、初始化PLL3_PFD0~PFD3
    */

    //设置PLL2的4路PFD
    unsigned int unReg = 0;

    unReg = CCM_ANALOG->PFD_528;
    unReg &= ~(0x3f3f3f3f);             //清除原来的设置
    unReg |= (32 << 24);                //PLL2_PFD3=297MHz
    unReg |= (24 << 16);                //PLL2_PFD2=396MHz
    unReg |= (16 << 8);                 //PLL2_PFD1=594MHz
    unReg |= (27 << 0);                 //PLL2_PFD0=352MHz
    CCM_ANALOG->PFD_528 = unReg;

    //设置PLL3的4路PFD
    unReg = 0;
    unReg = CCM_ANALOG->PFD_480;
    unReg &= ~(0x3f3f3f3f);             //清除原来的设置
    unReg |= (19 << 24);                //PLL3_PFD3=454.7MHz
    unReg |= (17 << 16);                //PLL3_PFD2=508.2MHz
    unReg |= (16 << 8);                 //PLL3_PFD1=540MHz
    unReg |= (12 << 0);                 //PLL3_PFD0=720MHz
    CCM_ANALOG->PFD_480 = unReg;

    /*
    3、其他外设时钟源配置
        AHB_CLK_ROOT、PERCLK_CLK_ROOT以及IPG_CLK_ROOT。
        因为PERCLK_CLK_ROOT和IPG_CLK_ROOT要用到AHB_CLK_ROOT，所以我们要初始化AHB_CLK_ROOT。
        ①、AHB_CLK_ROOT的初始化。
        AHB_CLK_ROOT=132MHz。
        设置CBCMR寄存器的PRE_PERIPH_CLK_SEL位，设置CBCDR寄存器的PERIPH_CLK_SEL位0。设置CBCDR寄存器的AHB_PODF位为2，也就是3分频，因此396/3=132MHz。

        ②、IPG_CLK_ROOT初始化
        设置CBCDR寄存器IPG_PODF=1，也就是2分频。

        ③、PERCLK_CLK_ROOT初始化
        设置CSCMR1寄存器的PERCLK_CLK_SEL位为0，表示PERCLK的时钟源为IPG。
    */

   //设置 AHB_CLK_ROOT=132MHz 时钟；最小6MHz,最大132MHz
   CCM->CBCMR &= ~(3 << 18);                            //清除设置
   CCM->CBCMR |= (1 << 18);                             //pre_periph_clk=PLL2_PFD2=396MHz
   CCM->CBCDR &= !(1 << 25);                            //periph_clk=pre_periph_clk=396MHz
   while(CCM->CDHIPR & (1 << 5));                       //等待握手完成

   /* 修改 AHB_PODF 位的时候需要先禁止 AHB_CLK_ROOT 的输出，但是
    * 我没有找到关闭 AHB_CLK_ROOT 输出的的寄存器，所以就没法设置。
    * 下面设置 AHB_PODF 的代码仅供学习参考不能直接拿来使用！！
    * 内部 boot rom 将 AHB_PODF 设置为了 3 分频，即使我们不设置 AHB_PODF，
    * AHB_ROOT_CLK 也依旧等于 396/3=132Mhz。
    */

#if 0
    //要先关闭AHB_ROOT_CLK输出，否则时钟设置会出错
    CCM->CBCDR &= ~(7 << 10);                           //CBCDR的AHB_PODF清零
    CCM->CBCDR |= (2 << 10);                            //AHB_PODF 3分频，AHB_CLK_ROOT=132MHZ
    while(CCM->CDHIPR & (1 << 1));                      //等待握手完成    
#endif

    //设置IPG_CLK_ROOT 最小 3MHz, 最大 66MHz
    CCM->CBCDR &= ~(3 << 8);                            //CBCDR 的 IPG_PODF 清零
    CCM->CBCDR |= (1 << 8);                             //IPG_PODF 2分频, IPG_CLK_ROOt=66MHz

    //设置PERCLK_CLK_ROOT 时钟源为IPG
    CCM->CSCMR1 &= ~(1 << 6);                           //PERCLK_CLK_ROOt 时钟源为IPG
    CCM->CSCMR1 &= ~(0x3f << 0);                        //PERCLK_PODF 位清零，即1分频
}