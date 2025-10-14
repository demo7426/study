/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Key.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.10.13
描  述: linux input子系统，使用设备树中的gpio，通过中断读取按键输入
备  注:	
修改记录:

  1.  日期: 2025.10.13
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/ide.h>
#include <linux/cdev.h>
#include <linux/of_address.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/gfp.h>
#include <linux/input-event-codes.h>
#include <linux/interrupt.h>

#define PS_KEY0_CODE        KEY_0

enum KEY_STATUS{
    KEY_PRESS = 0,                                              //按键按下
    KEY_RELEASE,                                                //按键释放
    KEY_KEEP                                                    //按键保持
};

typedef struct _KEY_DEV{
    struct input_dev* ptInputDev;                               //按键对应的 input_dev 事件
    struct timer_list tTimer;                                   //定时器
    int Key_Gpio;                                               //GPIO号
    int Irq_Num;                                                //中断号
}KEY_DEV, *PKEY_DEV;

/// @brief 中断回调函数
/// @param _Irq 
/// @param _pDevID 
/// @return 
static irqreturn_t Key_Interrupt(int _Irq, void* _pArg)
{
    PKEY_DEV ptKeyDev = (PKEY_DEV)_pArg;

    if(ptKeyDev->Irq_Num != _Irq)
        return IRQ_NONE;

    disable_irq_nosync(_Irq);                                           //禁止按键中断
    mod_timer(&ptKeyDev->tTimer, jiffies + msecs_to_jiffies(15));       //重新启动定时器

    return IRQ_HANDLED;
}

/// @brief 定时器回调函数
/// @param _pTimer 定时器指针对象
static void Timer_CallBack(struct timer_list* _pTimer)
{
    int nCurKeyState = 1;
    PKEY_DEV ptKeyDev = container_of(_pTimer, KEY_DEV, tTimer);

    //读取按键值并上报按键事件
    nCurKeyState = gpio_get_value(ptKeyDev->Key_Gpio);
    input_report_key(ptKeyDev->ptInputDev, PS_KEY0_CODE, !nCurKeyState);    //上报按键事件
    input_sync(ptKeyDev->ptInputDev);                                       //同步事件

    //使能按键中断
    enable_irq(ptKeyDev->Irq_Num);
}

static int Key_Init(struct platform_device *_ptPlatformDev)
{
    int nRtn = 0;
    PKEY_DEV ptKeyDev = platform_get_drvdata(_ptPlatformDev);
    struct device* ptDev = &_ptPlatformDev->dev;
    unsigned long ulIrqFlags = 0;       //中断触发类型

    //获取设备树中的led-gpio字段，得到led所使用的gpio编号
    ptKeyDev->Key_Gpio = of_get_named_gpio(ptDev->of_node, "key-gpio", 0);
    if(!gpio_is_valid(ptKeyDev->Key_Gpio))
    {
        printk(KERN_ERR "Failed to get led-gpio\n");
        return -EINVAL;
    }

    //向gpio子系统申请使用gpio
    nRtn = devm_gpio_request(ptDev, ptKeyDev->Key_Gpio, "KEY-GPIO");
    if(nRtn)
    {
        printk(KERN_ERR "Failed to request led-gpio\n");
        return -EINVAL;
    }

    //将led-gpio管脚设置为输入模式
    gpio_direction_input(ptKeyDev->Key_Gpio);

    //获取gpio对应的中断号
    ptKeyDev->Irq_Num = gpio_to_irq(ptKeyDev->Key_Gpio);
    if(!ptKeyDev->Irq_Num)
    {
        printk(KERN_ERR "Failed to gpio_to_irq\n");
        return -EINVAL;
    }

    //获取设备树中指定的中断触发类型
    ulIrqFlags = irq_get_trigger_type(ptKeyDev->Irq_Num);
    if(ulIrqFlags == IRQF_TRIGGER_NONE)
        ulIrqFlags = IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING;
    
    //申请中断
    nRtn = request_irq(ptKeyDev->Irq_Num, Key_Interrupt, ulIrqFlags, "PS Key0 IRQ", ptKeyDev);
    if(nRtn)
    {
        printk(KERN_ERR "request_irq is err.\n");
        return -EINVAL;
    }

    return nRtn;
}

static int Key_Probe(struct platform_device *_ptPlatformDev)
{
    int nRtn = 0;
    PKEY_DEV ptKeyDev = NULL;
    struct input_dev* ptInputDev = NULL; 

    ptKeyDev = devm_kzalloc(&_ptPlatformDev->dev, sizeof(KEY_DEV), GFP_KERNEL);
    if(!ptKeyDev)
        return -ENOMEM;

    platform_set_drvdata(_ptPlatformDev, ptKeyDev);

    //初始化按键
    nRtn = Key_Init(_ptPlatformDev);
    if(nRtn)
        return nRtn;

    //初始化定时器
    timer_setup(&ptKeyDev->tTimer, Timer_CallBack, 0);

    //input_dev初始化
    ptInputDev = devm_input_allocate_device(&_ptPlatformDev->dev);
    if(!ptInputDev)
        return -ENOMEM;

    ptKeyDev->ptInputDev = ptInputDev;
    ptInputDev->name = "mykey";

    __set_bit(EV_KEY, ptInputDev->evbit);                   //可产生按键事件
    __set_bit(EV_REP, ptInputDev->evbit);                   //可产生重复事件
    __set_bit(PS_KEY0_CODE, ptInputDev->keybit);            //可产生KEY_0事件

    //注册按键输入设备
    return input_register_device(ptInputDev);
}

static int Key_Remove(struct platform_device *_ptPlatformDev)
{
    PKEY_DEV ptKeyDev = platform_get_drvdata(_ptPlatformDev);

    del_timer_sync(&ptKeyDev->tTimer);

    input_unregister_device(ptKeyDev->ptInputDev);
 
    printk(KERN_ALERT "Key_Exit success.\n");

    return 0;
}

//匹配列表
static const struct of_device_id g_tKeyOfMatchs[] = {
    {.compatible = "alientek,key"},
    {}
};

//按键platform_driver驱动结构体对象
static struct platform_driver g_tKeyDriver = {
    .driver = {
        .name = "zynq-key",
        .of_match_table = g_tKeyOfMatchs,
    },
    .probe = Key_Probe,
    .remove = Key_Remove,
};  

module_platform_driver(g_tKeyDriver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qianrui");
MODULE_DESCRIPTION("Key driver based on input subsystem");
