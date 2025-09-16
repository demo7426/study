/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Key.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.09.16
描  述: 使用设备树中的gpio，通过中断读取按键输入
备  注:	
修改记录:

  1.  日期: 2025.09.16
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

#define KEY_COUNT           1                                   //字符设备数量
#define KEY_NAME            "key"                               //字符设备名称

enum KEY_STATUS{
    KEY_PRESS = 0,                                              //按键按下
    KEY_RELEASE,                                                //按键释放
    KEY_KEEP                                                    //按键保持
};

struct CHAR_DEV{
    dev_t DevID;                                                //设备号
    struct cdev CharDev;                                        //字符设备
    struct class* pCharClass;                                   //类
    struct device* pDevice;                                     //设备
    int Major;                                                  //主设备号
    int Minor;                                                  //次设备号

    struct device_node *pDevNode;                               //设备节点
    int Key_Gpio;                                               //GPIO号
    int Irq_Num;                                                //中断号
    struct timer_list Timer;                                    //定时器

    spinlock_t SpinLock;                                        //自旋锁
    enum KEY_STATUS KeyStatus;                                  //按键当前状态
};

/// @brief 对字符设备文件 open 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int Key_Open(struct inode* _pInode, struct file* _pFp);  

/// @brief 对字符设备文件 read 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t Key_Read(struct file* _pFp, char __user* _pBuf, size_t _Len, loff_t* _pOffset);                    

/// @brief 对字符设备文件 write 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t Key_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset);

/// @brief 对字符设备文件 release 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int Key_Release(struct inode* _pInode, struct file* _pFp);  

struct CHAR_DEV g_tCharDev = { 0 };                      //led设备

static struct file_operations g_tFile_Operations = 
{
    .owner = THIS_MODULE,
    .open = Key_Open,
    .read = Key_Read,
    .write = Key_Write,
    .release = Key_Release,
};

/// @brief 解析设备树
/// @param  
/// @return 0--成功;!0--失败
static int Parse_Dt(void)
{
    int nRtn = 0;
    const char* chReadDtsBuf;                               //读取出的dts数据

    //获取设备树LED设备节点
    g_tCharDev.pDevNode = of_find_node_by_path("/key");
    if(!g_tCharDev.pDevNode)
    {
        printk(KERN_ERR "Key node can not found\n");
        return -EINVAL;
    }

    //校验设备树status字段
    nRtn = of_property_read_string(g_tCharDev.pDevNode, "status", &chReadDtsBuf);
    if(nRtn)
    {
        printk(KERN_ERR "Key node status can not found\n");
        return -EINVAL;
    }

    if(strcmp(chReadDtsBuf, "okay"))
    {
        printk(KERN_ERR "Key node status is mismatch\n");
        return -EINVAL;
    }

    //校验设备树compatible字段
    nRtn = of_property_read_string(g_tCharDev.pDevNode, "compatible", &chReadDtsBuf);
    if(nRtn)
    {
        printk(KERN_ERR "Key node compatible can not found\n");
        return -EINVAL;
    }

    if(strcmp(chReadDtsBuf, "alientek,key"))
    {
        printk(KERN_ERR "Key node compatible is mismatch\n");
        return -EINVAL;
    }

    //获取设备树中的led-gpio字段，得到led所使用的gpio编号
    g_tCharDev.Key_Gpio = of_get_named_gpio(g_tCharDev.pDevNode, "key-gpio", 0);
    if(!gpio_is_valid(g_tCharDev.Key_Gpio))
    {
        printk(KERN_ERR "Failed to get led-gpio\n");
        return -EINVAL;
    }

    //获取GPIO对应的中断号
    g_tCharDev.Irq_Num = irq_of_parse_and_map(g_tCharDev.pDevNode, 0);
    if(!g_tCharDev.Irq_Num)
    {
        printk(KERN_ERR "irq_of_parse_and_map is err.\n");
        return -EINVAL;
    }

    printk(KERN_INFO "key-gpio num = %d\n", g_tCharDev.Key_Gpio);

    return 0;
}

/// @brief 中断回调函数
/// @param _Irq 
/// @param _pDevID 
/// @return 
static irqreturn_t Key_Interrupt(int _Irq, void* _pDevID)
{
    mod_timer(&g_tCharDev.Timer, jiffies + msecs_to_jiffies(15));     //重新启动定时器

    return IRQ_HANDLED;
}

/// @brief 初始化gpio
/// @param  
/// @return 0--成功;!0--失败
static int Gpio_Init(void)
{
    int nRtn = 0;
    unsigned long ulIrqFlags = 0;       //中断触发类型

    //向gpio子系统申请使用gpio
    nRtn = gpio_request(g_tCharDev.Key_Gpio, "KEY-GPIO");
    if(nRtn)
    {
        printk(KERN_ERR "Failed to request led-gpio\n");
        return -EINVAL;
    }

    //将led-gpio管脚设置为输入模式
    gpio_direction_input(g_tCharDev.Key_Gpio);

    //获取设备树中指定的中断触发类型
    ulIrqFlags = irq_get_trigger_type(g_tCharDev.Irq_Num);
    if(ulIrqFlags == IRQF_TRIGGER_NONE)
        ulIrqFlags = IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING;
    
    //申请中断
    nRtn = request_irq(g_tCharDev.Irq_Num, Key_Interrupt, ulIrqFlags, "PS Key0 IRQ", NULL);
    if(nRtn)
    {
        printk(KERN_ERR "request_irq is err.\n");
        gpio_free(g_tCharDev.Key_Gpio);
        return -EINVAL;
    }

    return 0;
}

/// @brief 定时器回调函数
/// @param _pTimer 定时器指针对象
static void Timer_CallBack(struct timer_list* _pTimer)
{
    static int nLastKeyState = 1;                                            //上一次的key状态
    int nCurKeyState = 1;
    unsigned int unFlag;

    spin_lock_irqsave(&g_tCharDev.SpinLock, unFlag);                        //保存中断状态，禁止本地中断，并获取自旋锁。

    nCurKeyState = gpio_get_value(g_tCharDev.Key_Gpio);

    if(nLastKeyState == 1 && nCurKeyState == 0)
    {
        g_tCharDev.KeyStatus = KEY_PRESS;
    }
    else if(nLastKeyState == 0 && nCurKeyState == 1)
    {
        g_tCharDev.KeyStatus = KEY_RELEASE;
    }
    else
        g_tCharDev.KeyStatus = KEY_KEEP;

    nLastKeyState = nCurKeyState;

    spin_unlock_irqrestore(&g_tCharDev.SpinLock, unFlag);                   //将中断状态恢复到以前的状态，并且激活本地中断，释放自旋锁。
}

static int __init Key_Init(void)
{
    int nRtn = 0;
   
    Parse_Dt();

    Gpio_Init();

    //注册字符设备驱动
    //指定设备号
    if(g_tCharDev.Major)
    {
        g_tCharDev.DevID = MKDEV(g_tCharDev.Major, 0);
        
        nRtn = register_chrdev_region(g_tCharDev.DevID, KEY_COUNT, KEY_NAME);
        if(nRtn)
            goto out1;
    }
    else        //分配设备号
    {
        nRtn = alloc_chrdev_region(&g_tCharDev.DevID, 0, KEY_COUNT, KEY_NAME);
        if(nRtn)
            goto out1;
        
        g_tCharDev.Major = MAJOR(g_tCharDev.DevID);
        g_tCharDev.Minor = MINOR(g_tCharDev.DevID);
    }

    printk(KERN_ALERT "Key_Init major = %d, minor = %d.\n", g_tCharDev.Major, g_tCharDev.Minor);

    //初始化cdev
    g_tCharDev.CharDev.owner = THIS_MODULE;
    cdev_init(&g_tCharDev.CharDev, &g_tFile_Operations);

    //添加一个cdev
    nRtn = cdev_add(&g_tCharDev.CharDev, g_tCharDev.DevID, KEY_COUNT);
    if(nRtn)
        goto out2;

    //创建类
    g_tCharDev.pCharClass = class_create(THIS_MODULE, KEY_NAME);
    if(IS_ERR(g_tCharDev.pCharClass))
    {
       nRtn = PTR_ERR(g_tCharDev.pCharClass); 
       goto out3;
    }

    //创建设备
    g_tCharDev.pDevice = device_create(g_tCharDev.pCharClass, NULL, g_tCharDev.DevID, NULL, KEY_NAME);
    if(IS_ERR(g_tCharDev.pDevice))
    {
       nRtn = PTR_ERR(g_tCharDev.pDevice); 
       goto out4;
    }
 
    spin_lock_init(&g_tCharDev.SpinLock);           //对自旋锁进行初始化
    
    timer_setup(&g_tCharDev.Timer, Timer_CallBack, 0);      //初始化定时器，此时并不会启动定时器
    
    printk(KERN_ALERT "Key_Init success.\n");

    return nRtn;                //正常退出

out4:
    class_destroy(g_tCharDev.pCharClass);

out3:
    cdev_del(&g_tCharDev.CharDev);

out2:
    unregister_chrdev_region(g_tCharDev.DevID, KEY_COUNT);

out1:
    gpio_free(g_tCharDev.Key_Gpio);

    return nRtn;                //异常退出
}

static void __exit Key_Exit(void)
{
    device_destroy(g_tCharDev.pCharClass, g_tCharDev.DevID);                //注销设备

    class_destroy(g_tCharDev.pCharClass);                                   //注销类

    cdev_del(&g_tCharDev.CharDev);                                          //删除cdev

    unregister_chrdev_region(g_tCharDev.DevID, KEY_COUNT);                  //注销设备号

    free_irq(g_tCharDev.Irq_Num, NULL);                                     //释放中断

    gpio_free(g_tCharDev.Key_Gpio);
 
    printk(KERN_ALERT "Key_Exit success.\n");
}

int Key_Open(struct inode* _pInode, struct file* _pFp)
{
    _pFp->private_data = &g_tCharDev;                                       //设置私有数据
    printk(KERN_ALERT "Key_Open success.\n");
    return 0;
}

int Key_Release(struct inode* _pInode, struct file* _pFp)
{
    printk(KERN_ALERT "Key_Release success.\n");
    return 0;
}

ssize_t Key_Read(struct file* _pFp, char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    unsigned int unFlag;

    if(_pFp == NULL || _pBuf == NULL || _Len < sizeof(g_tCharDev.KeyStatus))
    {
        printk(KERN_ALERT "Key_Read input param err, %p, %p, %d.\n", _pFp, _pBuf, _Len);
        return -EFAULT;
    }

    spin_lock_irqsave(&g_tCharDev.SpinLock, unFlag);                        //保存中断状态，禁止本地中断，并获取自旋锁。

    if (copy_to_user(_pBuf, &g_tCharDev.KeyStatus, sizeof(g_tCharDev.KeyStatus)))                                //将内核数据拷贝到用户空间
    {
        printk(KERN_ALERT "Key_Read copy_to_user err.\n");
        return -EFAULT;
    }

    g_tCharDev.KeyStatus = KEY_KEEP;

    spin_unlock_irqrestore(&g_tCharDev.SpinLock, unFlag);                   //将中断状态恢复到以前的状态，并且激活本地中断，释放自旋锁。

    return sizeof(g_tCharDev.KeyStatus);
}

/// @brief 对字符设备文件 write 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t Key_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    return 0;
}

module_init(Key_Init);
module_exit(Key_Exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qianrui");