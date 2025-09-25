/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Led.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.09.25
描  述: platform总线编程示例值platform驱动模块
备  注:	
修改记录:

  1.  日期: 2025.09.25
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
#include <linux/platform_device.h>

#define LED_COUNT           1                               //字符设备数量
#define LED_NAME            "Led"                           //字符设备名称

static void __iomem *g_pvDataAddr = NULL;                       //GPIO数据，虚拟地址
static void __iomem *g_pvDirmAddr = NULL;                       //GPIO方向，虚拟地址
static void __iomem *g_pvOutEnAddr = NULL;                      //GPIO输出使能，虚拟地址
static void __iomem *g_pvIntDisAddr = NULL;                     //GPIO中断，虚拟地址
static void __iomem *g_pvClkCtrlAddr = NULL;                    //时钟控制，虚拟地址

struct CHAR_DEV{
    dev_t DevID;                                                //设备号
    struct cdev CharDev;                                        //字符设备
    struct class* pCharClass;                                   //类
    struct device* pDevice;                                     //设备
    int Major;                                                  //主设备号
    int Minor;                                                  //次设备号
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

struct CHAR_DEV g_tNewCharDev = { 0 };                      //led设备

static struct file_operations g_tFile_Operations = 
{
    .owner = THIS_MODULE,
    .open = Led_Open,
    .read = Led_Read,
    .write = Led_Write,
    .release = Led_Release,
};

//寄存器获取地址及映射
static int Led_GetRes_And_IORemap(struct platform_device *_pDev)
{
    int i = 0;
    struct resource *ptResources[5];

    if(!_pDev)
    {
        printk(KERN_ALERT, "Led_IORemap input paramet is err.\n");
        return -EPERM;
    }

    for (i = 0; i < sizeof(ptResources) / sizeof(ptResources[0]); i++)
    {
        ptResources[i] = platform_get_resource(_pDev, IORESOURCE_MEM, i);
        if(!ptResources[i])
        {
            printk(KERN_ALERT, "Led_IORemap platform_get_resource is err.\n");
            return -ENXIO;
        }
    }

    //寄存器地址映射
    g_pvDataAddr = ioremap(ptResources[0]->start, resource_size(ptResources[0]));
    g_pvDirmAddr = ioremap(ptResources[1]->start, resource_size(ptResources[1]));
    g_pvOutEnAddr = ioremap(ptResources[2]->start, resource_size(ptResources[2]));
    g_pvIntDisAddr = ioremap(ptResources[3]->start, resource_size(ptResources[3]));
    g_pvClkCtrlAddr = ioremap(ptResources[4]->start, resource_size(ptResources[4]));

    return 0;
}

//寄存器取消映射
static void Led_IOUnmap(void)
{
    iounmap(g_pvDataAddr);
    iounmap(g_pvDirmAddr);
    iounmap(g_pvOutEnAddr);
    iounmap(g_pvIntDisAddr);
    iounmap(g_pvClkCtrlAddr);
}

static int Led_Probe(struct platform_device *_pDev)
{
    int nRtn = 0;
    u32 unReadData = 0;

    nRtn = Led_GetRes_And_IORemap(_pDev);
    if(nRtn)
        return nRtn;

    //使能GPIO时钟
    unReadData = readl(g_pvClkCtrlAddr);
    unReadData |= (0x1U << 22);
    writel(unReadData, g_pvClkCtrlAddr);

    //关闭GPIO中断
    unReadData = readl(g_pvIntDisAddr);
    unReadData |= (0x1U << 7);
    writel(unReadData, g_pvIntDisAddr);

    //设置GPIO为输出功能
    unReadData = readl(g_pvDirmAddr);
    unReadData |= (0x1U << 7);
    writel(unReadData, g_pvDirmAddr);

    //使能GPIO为输出功能
    unReadData = readl(g_pvOutEnAddr);
    unReadData |= (0x1U << 7);
    writel(unReadData, g_pvOutEnAddr);
    
    //默认关闭Led
    unReadData = readl(g_pvDataAddr);
    unReadData &= ~(0x1U << 7);
    writel(unReadData, g_pvDataAddr);

    //注册字符设备驱动
    //指定设备号
    if(g_tNewCharDev.Major)
    {
        g_tNewCharDev.DevID = MKDEV(g_tNewCharDev.Major, 0);
        
        nRtn = register_chrdev_region(g_tNewCharDev.DevID, LED_COUNT, LED_NAME);
        if(nRtn)
            goto out1;
    }
    else        //分配设备号
    {
        nRtn = alloc_chrdev_region(&g_tNewCharDev.DevID, 0, LED_COUNT, LED_NAME);
        if(nRtn)
            goto out1;
        
        g_tNewCharDev.Major = MAJOR(g_tNewCharDev.DevID);
        g_tNewCharDev.Minor = MINOR(g_tNewCharDev.DevID);
    }

    printk(KERN_ALERT "Led_Init major = %d, minor = %d.\n", g_tNewCharDev.Major, g_tNewCharDev.Minor);

    //初始化cdev
    g_tNewCharDev.CharDev.owner = THIS_MODULE;
    cdev_init(&g_tNewCharDev.CharDev, &g_tFile_Operations);

    //添加一个cdev
    nRtn = cdev_add(&g_tNewCharDev.CharDev, g_tNewCharDev.DevID, LED_COUNT);
    if(nRtn)
        goto out2;

    //创建类
    g_tNewCharDev.pCharClass = class_create(THIS_MODULE, LED_NAME);
    if(IS_ERR(g_tNewCharDev.pCharClass))
    {
       nRtn = PTR_ERR(g_tNewCharDev.pCharClass); 
       goto out3;
    }

    //创建设备
    g_tNewCharDev.pDevice = device_create(g_tNewCharDev.pCharClass, NULL, g_tNewCharDev.DevID, NULL, LED_NAME);
    if(IS_ERR(g_tNewCharDev.pDevice))
    {
       nRtn = PTR_ERR(g_tNewCharDev.pDevice); 
       goto out4;
    }

    printk(KERN_ALERT "Led_Init success.\n");

    return nRtn;                //正常退出

out4:
    class_destroy(g_tNewCharDev.pCharClass);

out3:
    cdev_del(&g_tNewCharDev.CharDev);

out2:
    unregister_chrdev_region(g_tNewCharDev.DevID, LED_COUNT);

out1:
    Led_IOUnmap();

    return nRtn;                //异常退出
}

static int Led_Remove(struct platform_device *_pDev)
{
    device_destroy(g_tNewCharDev.pCharClass, g_tNewCharDev.DevID);          //注销设备

    class_destroy(g_tNewCharDev.pCharClass);                                //注销类

    cdev_del(&g_tNewCharDev.CharDev);                                       //删除cdev

    unregister_chrdev_region(g_tNewCharDev.DevID, LED_COUNT);           //注销设备号

    Led_IOUnmap();                                                      //取消地址映射
 
    printk(KERN_ALERT "Led_Exit success.\n");
}

static struct platform_driver g_tPlatformDriver = {
    .driver = {
        .name = "zynq-led",     //驱动名字，用于和设备匹配
    },
    .probe = Led_Probe,
    .remove = Led_Remove,
};

static int __init Led_Init(void)
{
    return platform_driver_register(&g_tPlatformDriver);
}

static void __exit Led_Exit(void)
{
    platform_driver_unregister(&g_tPlatformDriver);
}

int Led_Open(struct inode* _pInode, struct file* _pFp)
{
    _pFp->private_data = &g_tNewCharDev;                                            //设置私有数据
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
    if(_pFp == NULL || _pBuf == NULL || _Len <= 0 || _pOffset == NULL)
    {
        printk(KERN_ALERT "Led_Write input param err.\n");
        return -EFAULT;
    }

    u32 unReadData = 0;
    char chDataBuf[1] = { 0 };

    if (copy_from_user(chDataBuf, _pBuf, 1))                                //将用户数据拷贝到内核空间
    {
        printk(KERN_ALERT "Led_Write copy_from_user err.\n");
        return -EFAULT;
    }

    unReadData = readl(g_pvDataAddr);

    if(chDataBuf[0] == 0)       //关闭Led        
        unReadData &= ~(0x1U << 7);
    else                        //打开Led        
        unReadData |= (0x1U << 7);

    writel(unReadData, g_pvDataAddr);

    return _Len;
}

module_init(Led_Init);
module_exit(Led_Exit);

MODULE_AUTHOR("qianrui");
MODULE_DESCRIPTION("Led platform driver");
MODULE_LICENSE("GPL");