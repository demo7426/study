/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Key.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.09.11
描  述: 使用设备树中的gpio，读取按键输入
备  注:	
修改记录:

  1.  日期: 2025.09.11
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
#include <linux/delay.h>

#define KEY_COUNT           1                                   //字符设备数量
#define KEY_NAME            "key"                               //字符设备名称

struct CHAR_DEV{
    dev_t DevID;                                                //设备号
    struct cdev CharDev;                                        //字符设备
    struct class* pCharClass;                                   //类
    struct device* pDevice;                                     //设备
    int Major;                                                  //主设备号
    int Minor;                                                  //次设备号

    struct device_node *pDevNode;                               //设备节点
    int Key_Gpio;                                               //LED所使用的GPIO编号

    struct mutex Mutex;                                         //互斥锁
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

static int __init Key_Init(void)
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

    printk(KERN_INFO "key-gpio num = %d\n", g_tCharDev.Key_Gpio);

    //向gpio子系统申请使用gpio
    nRtn = gpio_request(g_tCharDev.Key_Gpio, "KEY-GPIO");
    if(nRtn)
    {
        printk(KERN_ERR "Failed to request led-gpio\n");
        return -EINVAL;
    }

    //将led-gpio管脚设置为输入模式
    gpio_direction_input(g_tCharDev.Key_Gpio);

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
 
    mutex_init(&g_tCharDev.Mutex);                  //初始化互斥锁
    
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
    if(_pFp == NULL || _pBuf == NULL || _Len <= 0)
    {
        printk(KERN_ALERT "Key_Read input param err, %p, %p, %d.\n", _pFp, _pBuf, _Len);
        return -EFAULT;
    }

    int nRet = 0;
    int nKeyInputVal = 1;       //按键输入值;0--按键按下;1--按键未按下

    if(mutex_lock_interruptible(&g_tCharDev.Mutex))                         //使用此函数获取互斥锁失败进入休眠以后可以被信号打断。
    {   
        //获取信号失败
        printk(KERN_ALERT "Key_Open is busy.\n");
        return -ERESTARTSYS;
    }

    if(!gpio_get_value(g_tCharDev.Key_Gpio))
    {
        msleep(20);             //按键消抖
        while(!gpio_get_value(g_tCharDev.Key_Gpio))
        {
            nKeyInputVal = 0;
        }
    }
    else
        nKeyInputVal = 1;

    if (copy_to_user(_pBuf, &nKeyInputVal, sizeof(nKeyInputVal)))                                //将内核数据拷贝到用户空间
    {
        printk(KERN_ALERT "Key_Read copy_to_user err.\n");
        return -EFAULT;
    }

    mutex_unlock(&g_tCharDev.Mutex);                                        //解锁

    return sizeof(nKeyInputVal);
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