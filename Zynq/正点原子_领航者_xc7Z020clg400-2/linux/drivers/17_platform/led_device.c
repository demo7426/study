/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	led_device.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.09.25
描  述: platform总线编程示例值platform设备模块
备  注:	
修改记录:

  1.  日期: 2025.09.25
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <linux/module.h>
#include <linux/platform_device.h>

//GPIO相关寄存器地址定义
#define DATA_REG                0xE000A040                      //GPIO数据，寄存器地址
#define DIRM_REG                0xE000A204                      //GPIO方向，寄存器地址
#define OUTEN_REG               0xE000A208                      //GPIO输出使能，寄存器地址
#define INTDIS_REG              0xE000A214                      //GPIO中断，寄存器地址
#define APER_CLK_CTRL           0xF800012C                      //时钟控制，寄存器基地址

static void Led_Release(struct device* _pDev);

/// @brief platform设备资源信息
static struct resource g_tResources[] = {
    [0] = {
        .start = DATA_REG,
        .end = DATA_REG + 3,
        .flags = IORESOURCE_MEM,
    },
    [1] = {
        .start = DIRM_REG,
        .end = DIRM_REG + 3,
        .flags = IORESOURCE_MEM,
    },
    [2] = {
        .start = OUTEN_REG,
        .end = OUTEN_REG + 3,
        .flags = IORESOURCE_MEM,
    },
    [3] = {
        .start = INTDIS_REG,
        .end = INTDIS_REG + 3,
        .flags = IORESOURCE_MEM,
    },
    [4] = {
        .start = APER_CLK_CTRL,
        .end = APER_CLK_CTRL + 3,
        .flags = IORESOURCE_MEM,
    },
};

static struct platform_device g_tPlatformDevice = {
    .name = "zynq-led",
    .id = -1,
    .dev = {
        .release = &Led_Release,
    },
    .num_resources = ARRAY_SIZE(g_tResources),
    .resource = g_tResources,
};

static void Led_Release(struct device* _pDev)
{
    printk(KERN_INFO "Led platform device release\n");
}

static int __init Led_Device_Init(void)
{
    return platform_device_register(&g_tPlatformDevice);
}

static void __exit Led_Device_Exit(void)
{
    platform_device_unregister(&g_tPlatformDevice);
}

module_init(Led_Device_Init);
module_exit(Led_Device_Exit);

MODULE_AUTHOR("qianrui");
MODULE_DESCRIPTION("Led platform device");
MODULE_LICENSE("GPL");

