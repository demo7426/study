/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	New_Led.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.09.04
描  述: 使用设备树，控制Led灯的亮灭实验
备  注:	
修改记录:

  1.  日期: 2025.09.04
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

#define NEW_LED_COUNT           1                               //字符设备数量
#define NEW_LED_NAME            "Dts_Led"                       //字符设备名称

static void __iomem *g_pvDataAddr = NULL;                       //GPIO数据，虚拟地址
static void __iomem *g_pvDirmAddr = NULL;                       //GPIO方向，虚拟地址
static void __iomem *g_pvOutEnAddr = NULL;                      //GPIO输出使能，虚拟地址
static void __iomem *g_pvIntDisAddr = NULL;                     //GPIO中断，虚拟地址
static void __iomem *g_pvClkCtrlAddr = NULL;                    //时钟控制，虚拟地址

struct NEW_CHAR_DEV{
    dev_t DevID;                                                //设备号
    struct cdev CharDev;                                        //字符设备
    struct class* pCharClass;                                   //类
    struct device* pDevice;                                     //设备
    int Major;                                                  //主设备号
    int Minor;                                                  //次设备号

    struct device_node *pDevNode;                               //设备节点
};

/// @brief 对字符设备文件 open 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int New_Led_Open(struct inode* _pInode, struct file* _pFp);  

/// @brief 对字符设备文件 read 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t New_Led_Read(struct file* _pFp, char __user* _pBuf, size_t _Len, loff_t* _pOffset);                    

/// @brief 对字符设备文件 write 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t New_Led_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset);

/// @brief 对字符设备文件 release 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int New_Led_Release(struct inode* _pInode, struct file* _pFp);  

struct NEW_CHAR_DEV g_tNewCharDev = { 0 };                      //led设备

static struct file_operations g_tFile_Operations = 
{
    .owner = THIS_MODULE,
    .open = New_Led_Open,
    .read = New_Led_Read,
    .write = New_Led_Write,
    .release = New_Led_Release,
};

//寄存器映射
static void New_Led_IORemap(void)
{
    //寄存器地址映射
    g_pvDataAddr = of_iomap(g_tNewCharDev.pDevNode, 0);
    g_pvDirmAddr = of_iomap(g_tNewCharDev.pDevNode, 1);
    g_pvOutEnAddr = of_iomap(g_tNewCharDev.pDevNode, 2);
    g_pvIntDisAddr = of_iomap(g_tNewCharDev.pDevNode, 3);
    g_pvClkCtrlAddr = of_iomap(g_tNewCharDev.pDevNode, 4);
}

//寄存器取消映射
static void New_Led_IOUnmap(void)
{
    iounmap(g_pvDataAddr);
    iounmap(g_pvDirmAddr);
    iounmap(g_pvOutEnAddr);
    iounmap(g_pvIntDisAddr);
    iounmap(g_pvClkCtrlAddr);
}

static int __init New_Led_Init(void)
{
    int nRtn = 0;
    unsigned int unReadData = 0;
    const char* chReadDtsBuf;                               //读取出的dts数据

    //获取设备树LED设备节点
    g_tNewCharDev.pDevNode = of_find_node_by_path("/led");
    if(!g_tNewCharDev.pDevNode)
    {
        printk(KERN_ERR "Led node can not found\n");
        return -EINVAL;
    }

    //校验设备树status字段
    nRtn = of_property_read_string(g_tNewCharDev.pDevNode, "status", &chReadDtsBuf);
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
    nRtn = of_property_read_string(g_tNewCharDev.pDevNode, "compatible", &chReadDtsBuf);
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

    New_Led_IORemap();

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
    
    //根据设备树设置Led的状态
    unReadData = readl(g_pvDataAddr);
    
    //校验设备树compatible字段
    nRtn = of_property_read_string(g_tNewCharDev.pDevNode, "default-state", &chReadDtsBuf);
    if(!nRtn)   //成功获取到该字段
    {
        if(!strcmp(chReadDtsBuf, "on"))
            unReadData |= (0x1U << 7);
        else
            unReadData &= ~(0x1U << 7);
    }
    else        //未获取到该字段，默认关闭Led灯
        unReadData &= ~(0x1U << 7);
    
    writel(unReadData, g_pvDataAddr);

    //注册字符设备驱动
    //指定设备号
    if(g_tNewCharDev.Major)
    {
        g_tNewCharDev.DevID = MKDEV(g_tNewCharDev.Major, 0);
        
        nRtn = register_chrdev_region(g_tNewCharDev.DevID, NEW_LED_COUNT, NEW_LED_NAME);
        if(nRtn)
            goto out1;
    }
    else        //分配设备号
    {
        nRtn = alloc_chrdev_region(&g_tNewCharDev.DevID, 0, NEW_LED_COUNT, NEW_LED_NAME);
        if(nRtn)
            goto out1;
        
        g_tNewCharDev.Major = MAJOR(g_tNewCharDev.DevID);
        g_tNewCharDev.Minor = MINOR(g_tNewCharDev.DevID);
    }

    printk(KERN_ALERT "New_Led_Init major = %d, minor = %d.\n", g_tNewCharDev.Major, g_tNewCharDev.Minor);

    //初始化cdev
    g_tNewCharDev.CharDev.owner = THIS_MODULE;
    cdev_init(&g_tNewCharDev.CharDev, &g_tFile_Operations);

    //添加一个cdev
    nRtn = cdev_add(&g_tNewCharDev.CharDev, g_tNewCharDev.DevID, NEW_LED_COUNT);
    if(nRtn)
        goto out2;

    //创建类
    g_tNewCharDev.pCharClass = class_create(THIS_MODULE, NEW_LED_NAME);
    if(IS_ERR(g_tNewCharDev.pCharClass))
    {
       nRtn = PTR_ERR(g_tNewCharDev.pCharClass); 
       goto out3;
    }

    //创建设备
    g_tNewCharDev.pDevice = device_create(g_tNewCharDev.pCharClass, NULL, g_tNewCharDev.DevID, NULL, NEW_LED_NAME);
    if(IS_ERR(g_tNewCharDev.pDevice))
    {
       nRtn = PTR_ERR(g_tNewCharDev.pDevice); 
       goto out4;
    }

    printk(KERN_ALERT "New_Led_Init success.\n");

    return nRtn;                //正常退出

out4:
    class_destroy(g_tNewCharDev.pCharClass);

out3:
    cdev_del(&g_tNewCharDev.CharDev);

out2:
    unregister_chrdev_region(g_tNewCharDev.DevID, NEW_LED_COUNT);

out1:
    New_Led_IOUnmap();

    return nRtn;                //异常退出
}

static void __exit New_Led_Exit(void)
{
    device_destroy(g_tNewCharDev.pCharClass, g_tNewCharDev.DevID);          //注销设备

    class_destroy(g_tNewCharDev.pCharClass);                                //注销类

    cdev_del(&g_tNewCharDev.CharDev);                                       //删除cdev

    unregister_chrdev_region(g_tNewCharDev.DevID, NEW_LED_COUNT);           //注销设备号

    New_Led_IOUnmap();                                                      //取消地址映射
 
    printk(KERN_ALERT "New_Led_Exit success.\n");
}

int New_Led_Open(struct inode* _pInode, struct file* _pFp)
{
    _pFp->private_data = &g_tNewCharDev;                                            //设置私有数据
    printk(KERN_ALERT "New_Led_Open success.\n");
    return 0;
}

int New_Led_Release(struct inode* _pInode, struct file* _pFp)
{
    printk(KERN_ALERT "New_Led_Release success.\n");
    return 0;
}

ssize_t New_Led_Read(struct file* _pFp, char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    return 0;

    // if(_pFp == NULL || _pBuf == NULL || _Len > sizeof g_chDataBuf || _pOffset == NULL)
    // {
    //     printk(KERN_ALERT "New_Led_Read input param err.\n");
    //     return -EFAULT;
    // }

    // if (copy_to_user(_pBuf, g_chDataBuf, _Len))                                //将内核数据拷贝到用户空间
    // {
    //     printk(KERN_ALERT "New_Led_Read copy_to_user err.\n");
    //     return -EFAULT;
    // }

    // return _Len;
}

/// @brief 对字符设备文件 write 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t New_Led_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    if(_pFp == NULL || _pBuf == NULL || _Len <= 0 || _pOffset == NULL)
    {
        printk(KERN_ALERT "New_Led_Write input param err.\n");
        return -EFAULT;
    }

    unsigned int unReadData = 0;
    char chDataBuf[1] = { 0 };

    if (copy_from_user(chDataBuf, _pBuf, 1))                                //将用户数据拷贝到内核空间
    {
        printk(KERN_ALERT "New_Led_Write copy_from_user err.\n");
        return -EFAULT;
    }

    unReadData = readl(g_pvDataAddr);

    if(chDataBuf[0] == 0)       //关闭New_Led        
        unReadData &= ~(0x1U << 7);
    else                        //打开New_Led        
        unReadData |= (0x1U << 7);

    writel(unReadData, g_pvDataAddr);

    return _Len;
}

module_init(New_Led_Init);
module_exit(New_Led_Exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qianrui");