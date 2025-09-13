/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	timer.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.09.12
描  述: 使用设备树中的gpio，定时器或手动控制Led灯的亮灭实验
备  注:	
修改记录:

  1.  日期: 2025.09.12
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

#define LED_COUNT           1                                   //字符设备数量
#define LED_NAME            "Gpio_Led"                          //字符设备名称

#define CMD_LED_CLOSE       (_IO(0xEF, 0x1))                    //关闭LED
#define CMD_LED_OPEN        (_IO(0xEF, 0x2))                    //开启LED
#define CMD_LED_PERIOD      (_IO(0xEF, 0x3))                    //设置定时器LED反转时间

struct CHAR_DEV{
    dev_t DevID;                                                //设备号
    struct cdev CharDev;                                        //字符设备
    struct class* pCharClass;                                   //类
    struct device* pDevice;                                     //设备
    int Major;                                                  //主设备号
    int Minor;                                                  //次设备号

    struct device_node *pDevNode;                               //设备节点
    int Led_Gpio;                                               //LED所使用的GPIO编号

    struct mutex Mutex;                                         //互斥锁

    struct timer_list Timer;                                    //定时器
    unsigned int TimerPeriod;                                   //定时器时间间隔
};

/// @brief 对字符设备文件 open 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int Led_Open(struct inode* _pInode, struct file* _pFp);  

/// @brief 对字符设备文件 read 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t Led_Read(struct file* _pFp, char __user* _pBuf, size_t _Len, loff_t* _pOffset);                    

/// @brief 对字符设备文件 write 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t Led_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset);

/// @brief 对字符设备文件 release 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int Led_Release(struct inode* _pInode, struct file* _pFp);  

/// @brief 对字符设备文件 unlocked_ioctl 回调函数
/// @param _pFp 文件描述符
/// @param _Cmd 指令编码
/// @param _Arg 用户态传入的参数
/// @return <0--执行失败，=0--执行成功
long int Led_Unlocked_IOCtl(struct file* _pFp, unsigned int _Cmd, long unsigned int _Arg);

struct CHAR_DEV g_tCharDev = { 0 };                      //led设备

static struct file_operations g_tFile_Operations = 
{
    .owner = THIS_MODULE,
    .open = Led_Open,
    .read = Led_Read,
    .write = Led_Write,
    .release = Led_Release,
    .unlocked_ioctl = Led_Unlocked_IOCtl,
};

/// @brief 定时器回调函数
/// @param _pTimer 定时器指针对象
static void Timer_CallBack(struct timer_list* _pTimer)
{
    static int nCurLedState = 0;                                            //当前LED状态

    if(mutex_lock_interruptible(&g_tCharDev.Mutex))                         //使用此函数获取互斥锁失败进入休眠以后可以被信号打断。
    {   
        //获取信号失败
        printk(KERN_ALERT "Timer_CallBack mutex_lock_interruptible is err.\n");
        return;
    }

    nCurLedState = !nCurLedState;
    gpio_set_value(g_tCharDev.Led_Gpio, nCurLedState);

    mod_timer(&g_tCharDev.Timer, jiffies + msecs_to_jiffies(g_tCharDev.TimerPeriod));     //重新启动定时器


    mutex_unlock(&g_tCharDev.Mutex);                                        //解锁
}

static int __init Led_Init(void)
{
    int nRtn = 0;
    const char* chReadDtsBuf;                               //读取出的dts数据

    //获取设备树LED设备节点
    g_tCharDev.pDevNode = of_find_node_by_path("/led");
    if(!g_tCharDev.pDevNode)
    {
        printk(KERN_ERR "Led node can not found\n");
        return -EINVAL;
    }

    //校验设备树status字段
    nRtn = of_property_read_string(g_tCharDev.pDevNode, "status", &chReadDtsBuf);
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
    nRtn = of_property_read_string(g_tCharDev.pDevNode, "compatible", &chReadDtsBuf);
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
    g_tCharDev.Led_Gpio = of_get_named_gpio(g_tCharDev.pDevNode, "led-gpio", 0);
    if(!gpio_is_valid(g_tCharDev.Led_Gpio))
    {
        printk(KERN_ERR "Failed to get led-gpio\n");
        return -EINVAL;
    }

    printk(KERN_INFO "led-gpio num = %d\n", g_tCharDev.Led_Gpio);

    //向gpio子系统申请使用gpio
    nRtn = gpio_request(g_tCharDev.Led_Gpio, "LED-GPIO");
    if(nRtn)
    {
        printk(KERN_ERR "Failed to request led-gpio\n");
        return -EINVAL;
    }

    //将led-gpio管脚设置为输出模式，并初始化为低电平
    gpio_direction_output(g_tCharDev.Led_Gpio, 0);

    timer_setup(&g_tCharDev.Timer, Timer_CallBack, 0);      //初始化定时器，此时并不会启动定时器

    //校验设备树compatible字段
    nRtn = of_property_read_string(g_tCharDev.pDevNode, "default-state", &chReadDtsBuf);
    if(!nRtn)   //成功获取到该字段
    {
        if(!strcmp(chReadDtsBuf, "on"))
            gpio_set_value(g_tCharDev.Led_Gpio, 1);
        else
            gpio_set_value(g_tCharDev.Led_Gpio, 0);
    }
    else        //未获取到该字段，默认关闭Led灯
        gpio_set_value(g_tCharDev.Led_Gpio, 0);

    //注册字符设备驱动
    //指定设备号
    if(g_tCharDev.Major)
    {
        g_tCharDev.DevID = MKDEV(g_tCharDev.Major, 0);
        
        nRtn = register_chrdev_region(g_tCharDev.DevID, LED_COUNT, LED_NAME);
        if(nRtn)
            goto out1;
    }
    else        //分配设备号
    {
        nRtn = alloc_chrdev_region(&g_tCharDev.DevID, 0, LED_COUNT, LED_NAME);
        if(nRtn)
            goto out1;
        
        g_tCharDev.Major = MAJOR(g_tCharDev.DevID);
        g_tCharDev.Minor = MINOR(g_tCharDev.DevID);
    }

    printk(KERN_ALERT "Led_Init major = %d, minor = %d.\n", g_tCharDev.Major, g_tCharDev.Minor);

    //初始化cdev
    g_tCharDev.CharDev.owner = THIS_MODULE;
    cdev_init(&g_tCharDev.CharDev, &g_tFile_Operations);

    //添加一个cdev
    nRtn = cdev_add(&g_tCharDev.CharDev, g_tCharDev.DevID, LED_COUNT);
    if(nRtn)
        goto out2;

    //创建类
    g_tCharDev.pCharClass = class_create(THIS_MODULE, LED_NAME);
    if(IS_ERR(g_tCharDev.pCharClass))
    {
       nRtn = PTR_ERR(g_tCharDev.pCharClass); 
       goto out3;
    }

    //创建设备
    g_tCharDev.pDevice = device_create(g_tCharDev.pCharClass, NULL, g_tCharDev.DevID, NULL, LED_NAME);
    if(IS_ERR(g_tCharDev.pDevice))
    {
       nRtn = PTR_ERR(g_tCharDev.pDevice); 
       goto out4;
    }
 
    mutex_init(&g_tCharDev.Mutex);                  //初始化互斥锁
    
    printk(KERN_ALERT "Led_Init success.\n");

    return nRtn;                //正常退出

out4:
    class_destroy(g_tCharDev.pCharClass);

out3:
    cdev_del(&g_tCharDev.CharDev);

out2:
    unregister_chrdev_region(g_tCharDev.DevID, LED_COUNT);

out1:
    gpio_free(g_tCharDev.Led_Gpio);

    return nRtn;                //异常退出
}

static void __exit Led_Exit(void)
{
    device_destroy(g_tCharDev.pCharClass, g_tCharDev.DevID);                //注销设备

    class_destroy(g_tCharDev.pCharClass);                                   //注销类

    cdev_del(&g_tCharDev.CharDev);                                          //删除cdev

    unregister_chrdev_region(g_tCharDev.DevID, LED_COUNT);                  //注销设备号

    gpio_free(g_tCharDev.Led_Gpio);
 
    printk(KERN_ALERT "Led_Exit success.\n");
}

int Led_Open(struct inode* _pInode, struct file* _pFp)
{
    _pFp->private_data = &g_tCharDev;                                       //设置私有数据
    printk(KERN_ALERT "Led_Open success.\n");
    return 0;
}

int Led_Release(struct inode* _pInode, struct file* _pFp)
{
    printk(KERN_ALERT "Led_Release success.\n");
    return 0;
}

ssize_t Led_Read(struct file* _pFp, char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    return 0;
}

/// @brief 对字符设备文件 write 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t Led_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    return 0;
}

long int Led_Unlocked_IOCtl(struct file* _pFp, unsigned int _Cmd, long unsigned int _Arg)
{
    if(mutex_lock_interruptible(&g_tCharDev.Mutex))                         //使用此函数获取互斥锁失败进入休眠以后可以被信号打断。
    {   
        //获取信号失败
        printk(KERN_ALERT "Led_Open is busy.\n");
        return -ERESTARTSYS;
    }

    switch(_Cmd)
    {
    case CMD_LED_CLOSE:
        del_timer_sync(&g_tCharDev.Timer);
        gpio_set_value(g_tCharDev.Led_Gpio, 0);
        break;
    case CMD_LED_OPEN:
        del_timer_sync(&g_tCharDev.Timer);
        gpio_set_value(g_tCharDev.Led_Gpio, 1);
        break;
    case CMD_LED_PERIOD:
        g_tCharDev.TimerPeriod = _Arg;
        mod_timer(&g_tCharDev.Timer, jiffies + msecs_to_jiffies(g_tCharDev.TimerPeriod));     //启动定时器
        break;
    default:
        break;
    }

    mutex_unlock(&g_tCharDev.Mutex);                                        //解锁
    
    return 0;
}

module_init(Led_Init);
module_exit(Led_Exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qianrui");