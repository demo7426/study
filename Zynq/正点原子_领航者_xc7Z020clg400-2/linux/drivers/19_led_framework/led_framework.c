/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Led.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.09.28
描  述: Linux设备驱动框架入门之LED，控制Led灯的亮灭实验
备  注:	
修改记录:

  1.  日期: 2025.09.28
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
#include <linux/platform_device.h>
#include <linux/leds.h>

#define LED_NAME            "myled"                             //字符设备名称

struct LED_DATA{
    struct led_classdev tClassDev;                              //led设备
    int Led_Gpio;                                               //LED所使用的GPIO编号
};

static inline struct LED_DATA* Led_ClassDev_To_LED_DATA(struct led_classdev* pClassDev)
{
    return container_of(pClassDev, struct LED_DATA, tClassDev);
}

/// @brief led的初始化
/// @param of_node 
/// @return 
static int Led_Init(struct platform_device *_pDev)
{
    int nRtn = 0;
    const char* chReadDtsBuf;                               //读取出的dts数据
    struct LED_DATA* ptLedData = platform_get_drvdata(_pDev);

    //校验设备树status字段
    nRtn = of_property_read_string(_pDev->dev.of_node, "status", &chReadDtsBuf);
    if(nRtn)
    {
        printk(KERN_ERR "Led node status can not found\n");
        return -EINVAL;
    }

    if(strcmp(chReadDtsBuf, "okay"))
    {
        printk(KERN_ERR "Led node status is mismatch\n");
        return -EINVAL;
    }

    //校验设备树compatible字段
    nRtn = of_property_read_string(_pDev->dev.of_node, "compatible", &chReadDtsBuf);
    if(nRtn)
    {
        printk(KERN_ERR "Led node compatible can not found\n");
        return -EINVAL;
    }

    if(strcmp(chReadDtsBuf, "alientek,led"))
    {
        printk(KERN_ERR "Led node compatible is mismatch\n");
        return -EINVAL;
    }

    //获取设备树中的led-gpio字段，得到led所使用的gpio编号
    ptLedData->Led_Gpio = of_get_named_gpio(_pDev->dev.of_node, "led-gpio", 0);
    if(!gpio_is_valid(ptLedData->Led_Gpio))
    {
        printk(KERN_ERR "Failed to get led-gpio\n");
        return -EINVAL;
    }

    printk(KERN_INFO "led-gpio num = %d\n", ptLedData->Led_Gpio);

    //向gpio子系统申请使用gpio
    nRtn = gpio_request(ptLedData->Led_Gpio, "LED-GPIO");
    if(nRtn)
    {
        printk(KERN_ERR "Failed to request led-gpio\n");
        return -EINVAL;
    }

    //将led-gpio管脚设置为输出模式，并初始化为低电平
    gpio_direction_output(ptLedData->Led_Gpio, 0);

    //校验设备树compatible字段
    nRtn = of_property_read_string(_pDev->dev.of_node, "default-state", &chReadDtsBuf);
    if(!nRtn)   //成功获取到该字段
    {
        if(!strcmp(chReadDtsBuf, "on"))
            gpio_set_value(ptLedData->Led_Gpio, 1);
        else
            gpio_set_value(ptLedData->Led_Gpio, 0);
    }
    else        //未获取到该字段，默认关闭Led灯
        gpio_set_value(ptLedData->Led_Gpio, 0);

    return nRtn;   
}

void Led_Brightness_Set(struct led_classdev *led_cdev, enum led_brightness brightness)
{
    struct LED_DATA* ptLedData = Led_ClassDev_To_LED_DATA(led_cdev);
    
    if(brightness == LED_OFF)
        gpio_set_value(ptLedData->Led_Gpio, 0);
    else 
        gpio_set_value(ptLedData->Led_Gpio, 1);

}

int Led_Brightness_Set_Blocking(struct led_classdev *led_cdev, enum led_brightness brightness)
{
    Led_Brightness_Set(led_cdev, brightness);
    return 0;
}


static int Led_Probe(struct platform_device *_pDev)
{
    int nRtn = 0;
    struct LED_DATA* ptLedData = NULL;
    struct led_classdev* ptLed_ClassDev = NULL;

    if(!_pDev)
    {
        printk(KERN_ERR "Led_Probe input param is err.\n");
        return -EINVAL;
    }

    dev_info(&_pDev->dev, "Led device and driver matched successfully\n");

    //将申请的内存挂载在_pDev->dev下面，在卸载驱动的时候，内存会被自动释放
    ptLedData = devm_kzalloc(&_pDev->dev, sizeof(struct LED_DATA), GFP_KERNEL);
    if(!ptLedData)
    {
        dev_info(&_pDev->dev, "Led_Probe's devm_kzalloc is err\n");
        return -ENOMEM;
    }

    platform_set_drvdata(_pDev, ptLedData);

    //初始化led
    nRtn = Led_Init(_pDev);
    if(nRtn)
        return nRtn;     

    //初始化 led_classdev 变量
    ptLed_ClassDev = &ptLedData->tClassDev;
    ptLed_ClassDev->name = LED_NAME;                                        //设置设备名字
    ptLed_ClassDev->brightness = LED_OFF;                                   //设置LED初始亮度
    ptLed_ClassDev->max_brightness = LED_FULL;                              //设置LED最大亮度
    ptLed_ClassDev->brightness_set = Led_Brightness_Set;                    //绑定LED亮度设置函数（不可休眠）
    ptLed_ClassDev->brightness_set_blocking = Led_Brightness_Set_Blocking;  //绑定LED亮度设置函数（可以休眠）

    //注册led设备
    return led_classdev_register(&_pDev->dev, ptLed_ClassDev);
}

static int Led_Remove(struct platform_device *_pDev)
{
    struct LED_DATA* ptLedData = platform_get_drvdata(_pDev);

    gpio_free(ptLedData->Led_Gpio);

    led_classdev_unregister(&ptLedData->tClassDev);

    dev_info(&_pDev->dev, "Led driver has been removed!\n");
    return 0;
}

//匹配列表
static const struct of_device_id g_tLedOfMatch[] = {
    {.compatible = "alientek,led"},
    {},
};

//platform驱动结构体
static struct platform_driver g_tPlatform_Driver = {
    .driver = {
        .name = "zynq-led",                     //platform总线下的驱动名字
        .of_match_table = g_tLedOfMatch,        //设备树匹配表，用于和设备树中定义的设备匹配
    },
    
    .probe = Led_Probe,                         //probe函数
    .remove = Led_Remove,                       //remove函数
};

module_platform_driver(g_tPlatform_Driver);     //驱动注册、卸载

MODULE_AUTHOR("qianrui");
MODULE_DESCRIPTION("Led driver based on led driver framework");
MODULE_LICENSE("GPL");