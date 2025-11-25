/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	miscbeep.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.11.25
描  述: linux misc总线框架，实现对外设beep蜂鸣器的控制
备  注:	
修改记录:

  1.  日期: 2025.11.25
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/cdev.h>
#include <linux/bcd.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>

/// @brief 蜂鸣器设备信息
typedef struct _MY_MISC_DEV
{
    struct miscdevice MsicDev;          //misc设备
    int Gpio;                           //gpio编号
}MY_MISC_DEV, *PMY_MISC_DEV;

MY_MISC_DEV g_tMyMiscDev = { 0 };       //蜂鸣器设备信息

/// @brief 对字符设备文件 open 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int MISC_Open(struct inode* _pInode, struct file* _pFp);  

/// @brief 对字符设备文件 write 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t MISC_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset);

/// @brief 对字符设备文件 release 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int MISC_Release(struct inode* _pInode, struct file* _pFp);  

static struct file_operations g_tFile_Operations = 
{
    .owner = THIS_MODULE,
    .open = MISC_Open,
    .write = MISC_Write,
    .release = MISC_Release,
};

int MISC_Open(struct inode* _pInode, struct file* _pFp)
{
    _pFp->private_data = &g_tMyMiscDev;                                            //设置私有数据
    printk(KERN_ALERT "MISC_Open success.\n");

    return 0;
}

ssize_t MISC_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    int nRet = 0;
    char chRxBuF[8] = { 0 };

    if(_Len > 1)
    {
        printk(KERN_ALERT, "MISC_Write input parameter is err.\n");
        return -EINVAL;
    }

    nRet = copy_from_user(chRxBuF, _pBuf, _Len);
    if(nRet < 0)
    {
        printk(KERN_ALERT, "MISC_Write copy_from_user is err.\n");
        return -EFAULT;
    }

    gpio_set_value(g_tMyMiscDev.Gpio, chRxBuF[0]);

    return 0;
}

int MISC_Release(struct inode* _pInode, struct file* _pFp)
{
    return 0;
}

static int MISC_Init(struct platform_device *_pDev)
{
    int nRet = 0;
    struct device* pDev = &_pDev->dev;

    //从设备树中获取gpio
    g_tMyMiscDev.Gpio = of_get_named_gpio(pDev->of_node, "beep-gpio", 0);
    if(!gpio_is_valid(g_tMyMiscDev.Gpio))
    {
        dev_err(pDev, "MISC_Init of_get_named_gpio is err.\n");
        return -EINVAL;
    }

    //申请使用gpio
    nRet = devm_gpio_request(pDev, g_tMyMiscDev.Gpio, "beep gpio");
    if(nRet)
    {
        dev_err(pDev, "MISC_Init devm_gpio_request is err.\n");
        return nRet;
    }

    //将gpio设置为输出模式并将其输出为低电平
    gpio_direction_output(g_tMyMiscDev.Gpio, 0);

    return 0;
}

int MISC_Probe(struct platform_device *_pDev)
{
    int nRet = 0;

    dev_info(&_pDev->dev, "MISC_Probe is success.\n");
    
    nRet = MISC_Init(_pDev);
    if(nRet)
        return nRet;

    g_tMyMiscDev.MsicDev.name = "zynq-beep";                //设备名
    g_tMyMiscDev.MsicDev.minor = MISC_DYNAMIC_MINOR;        //动态分配次设备号
    g_tMyMiscDev.MsicDev.fops = &g_tFile_Operations;

    //向linux系统misc驱动框架核心层注册一个beep设备
    return misc_register(&g_tMyMiscDev.MsicDev);                
}

int MISC_Remove(struct platform_device *_pDev)
{
    misc_deregister(&g_tMyMiscDev.MsicDev);

    printk(KERN_ALERT "MISC_Remove success.\n");

    return 0;
}

static const struct of_device_id g_tMISC_Of_Match[] = {
    { .compatible = "alientek,beep" },
    {}
};

static struct platform_driver g_tMISC_Driver = {
    .driver = {
        .name = "zynq-beep",        // 驱动名字，用于和设备匹配
        .of_match_table = g_tMISC_Of_Match,
    },
    .probe = MISC_Probe,
    .remove = MISC_Remove
};

module_platform_driver(g_tMISC_Driver);

MODULE_AUTHOR("qianrui");
MODULE_DESCRIPTION("Misc driver");
MODULE_LICENSE("GPL");


