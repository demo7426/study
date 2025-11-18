/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	pwm.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.11.17
描  述: pwm驱动程序
备  注:	
修改记录:

  1.  日期: 2025.11.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of_device.h>
#include <linux/device.h>
#include <linux/pwm.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/io.h>

#define PWM_AXI_CTRL_REG_OFFSET         0       //pwm控制寄存器偏移值
#define PWM_AXI_STATUS_REG_OFFSET       4       //pwm状态寄存器偏移值
#define PWM_AXI_PERIOD_REG_OFFSET       8       //pwm周期寄存器偏移值
#define PWM_AXI_DUTY_REG_OFFSET         64      //pwm占空比寄存器偏移值

struct DGLNT_PWM_DEV
{
    struct device* ptDev;       //device对象指针
    struct pwm_chip tChip;      //内置 pwm_chip 成员
    struct clk* ptPwmClk;       //axi_pwm IP 输入时钟
    void __iomem *pBaseAddr;    //axi_pwm IP 寄存器基地址
    unsigned int PeriodMinNs;   //pwm 输出最小周期
};

#define S_TO_NS 1000000000U     //秒换算成纳秒的量级单位

static inline void Dglnt_Pwm_Writel(struct DGLNT_PWM_DEV* _pDglntPwmDev, u32 _Reg, u32 _Val)
{
    writel(_Val, _pDglntPwmDev->pBaseAddr + _Reg);
}

static inline struct DGLNT_PWM_DEV* To_DGLNT_PWM_DEV(struct pwm_chip *chip)
{
    return container_of(chip, struct DGLNT_PWM_DEV, tChip);
}

int Pwm_Config(struct pwm_chip *chip, struct pwm_device *pwm,
            int duty_ns, int period_ns)
{
    int nDuty, nPeriod;
    struct DGLNT_PWM_DEV* ptDglntPwmDev = To_DGLNT_PWM_DEV(chip);

    if(ptDglntPwmDev->PeriodMinNs > period_ns)
        period_ns = ptDglntPwmDev->PeriodMinNs;

    nPeriod = period_ns / ptDglntPwmDev->PeriodMinNs;
    nDuty = duty_ns / ptDglntPwmDev->PeriodMinNs;

    printk(KERN_INFO "Pwm_Config nPeriod = %d, nDuty = %d\n", nPeriod, nDuty);

    Dglnt_Pwm_Writel(ptDglntPwmDev, PWM_AXI_PERIOD_REG_OFFSET, nPeriod);
    Dglnt_Pwm_Writel(ptDglntPwmDev, PWM_AXI_DUTY_REG_OFFSET + (4 * pwm->hwpwm), nDuty);

    return 0;
}

int Pwm_Enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
    struct DGLNT_PWM_DEV* ptDglntPwmDev = To_DGLNT_PWM_DEV(chip);
    
    Dglnt_Pwm_Writel(ptDglntPwmDev, PWM_AXI_CTRL_REG_OFFSET, 1);
    return 0;
}

void Pwm_Disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
    struct DGLNT_PWM_DEV* ptDglntPwmDev = To_DGLNT_PWM_DEV(chip);
    
    Dglnt_Pwm_Writel(ptDglntPwmDev, PWM_AXI_CTRL_REG_OFFSET, 0);
}

/// @brief pwm操作函数集
struct pwm_ops g_tPwm_Ops = { 
    .owner = THIS_MODULE,
    .config = Pwm_Config,
    .enable = Pwm_Enable,
    .disable = Pwm_Disable
 };

int PWM_Probe(struct platform_device *_pDev)
{
    int nRtn = 0; 
    struct DGLNT_PWM_DEV* ptDglntPwmDev = NULL;
    struct resource * ptResource = NULL;
    unsigned long ulClkRate = 0;

    //实例化一个 struct DGLNT_PWM_DEV 对象
    ptDglntPwmDev = devm_kzalloc(&_pDev->dev, sizeof(struct DGLNT_PWM_DEV), GFP_KERNEL);
    if(!ptDglntPwmDev)
    {
        dev_err(&_pDev->dev, "PWM_Probe devm_kzalloc is err\n");
        return -ENOMEM;
    }

    //获取平台资源，得到寄存器基地址
    ptResource = platform_get_resource(_pDev, IORESOURCE_MEM, 0);
    ptDglntPwmDev->pBaseAddr = devm_ioremap_resource(&_pDev->dev, ptResource);
    if(IS_ERR(ptDglntPwmDev->pBaseAddr))
    {
        dev_err(&_pDev->dev, "PWM_Probe devm_ioremap_resource is err\n");
        return -ENOMEM;
    }

    //获取时钟、得到时钟大小
    ptDglntPwmDev->ptPwmClk = devm_clk_get(&_pDev->dev, "pwm");
    if(IS_ERR(ptDglntPwmDev->ptPwmClk))
    {
        dev_err(&_pDev->dev, "PWM_Probe devm_clk_get is err\n");
        return PTR_ERR(ptDglntPwmDev->ptPwmClk);
    }

    ulClkRate = clk_get_rate(ptDglntPwmDev->ptPwmClk);

    //计算pwm的最小周期
    ptDglntPwmDev->PeriodMinNs = S_TO_NS / ulClkRate;
    printk(KERN_INFO "PWM_Probe pwm_clk = %d, period_min_ns = %d\n", ulClkRate, ptDglntPwmDev->PeriodMinNs);

    //注册pwm设备
    ptDglntPwmDev->tChip.dev = &_pDev->dev;
    ptDglntPwmDev->tChip.ops = &g_tPwm_Ops;
    ptDglntPwmDev->tChip.base = -1;
    nRtn = of_property_read_u32(_pDev->dev.of_node, "npwm", &ptDglntPwmDev->tChip.npwm);
    if(nRtn)
    {
        dev_err(&_pDev->dev, "PWM_Probe of_property_read_u32 is err\n");
        return nRtn;
    }

    nRtn = pwmchip_add(&ptDglntPwmDev->tChip);
    if(nRtn < 0)
    {
        dev_err(&_pDev->dev, "PWM_Probe pwmchip_add is err, nRtn = %d, npwm = %d\n", nRtn, ptDglntPwmDev->tChip.npwm);
        return nRtn;
    }

    platform_set_drvdata(_pDev, ptDglntPwmDev);

    return nRtn;
}

int PWM_Remove(struct platform_device *_pDev)
{
    struct DGLNT_PWM_DEV* ptDglntPwmDev = platform_get_drvdata(_pDev);
    unsigned int i = 0;

    //禁止pwm输出
    for (i = 0; i < ptDglntPwmDev->tChip.npwm; i++)
    {
        Dglnt_Pwm_Writel(ptDglntPwmDev, PWM_AXI_CTRL_REG_OFFSET, 0);
    }

    //卸载pwm设备
    return pwmchip_remove(&ptDglntPwmDev->tChip);
}

//匹配列表
static const struct of_device_id g_tPWMOfMatch[] = {
    {.compatible = "digilent,axi-pwm"},
    {},
};

MODULE_DEVICE_TABLE(of, g_tPWMOfMatch);

//platform驱动结构体
static struct platform_driver g_tPlatform_Driver = {
    .driver = {
        .name = "dglnt-pwm",                    
        .of_match_table = g_tPWMOfMatch,        //设备树匹配表，用于和设备树中定义的设备匹配
    },
    
    .probe = PWM_Probe,                         //probe函数
    .remove = PWM_Remove,                       //remove函数
};

module_platform_driver(g_tPlatform_Driver);

MODULE_AUTHOR("qianrui");
MODULE_DESCRIPTION("Led platform driver");
MODULE_LICENSE("GPL");