/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	led.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.22
描  述: 控制LED灯的亮灭实验
备  注:	
修改记录:

  1.  日期: 2025.08.22
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

//GPIO相关寄存器地址定义
#define ZYNQ_GPIO_REG_BASE      0xE000A000                      //GPIO，寄存器基地址
#define DATA_OFFSET             0x00000040                      //GPIO数据，寄存器偏移值
#define DIRM_OFFSET             0x00000204                      //GPIO方向，寄存器偏移值
#define OUTEN_OFFSET            0x00000208                      //GPIO输出使能，寄存器偏移值
#define INTDIS_OFFSET           0x00000214                      //GPIO中断，寄存器偏移值
#define APER_CLK_CTRL           0xF800012C                      //时钟控制，寄存器基地址

static int g_nLed_Major = 0;                                    //字符设备主设备号
static const char* g_pLedName = "led";                          //字符设备名称

static void __iomem *g_pvDataAddr = NULL;                       //GPIO数据，虚拟地址
static void __iomem *g_pvDirmAddr = NULL;                       //GPIO方向，虚拟地址
static void __iomem *g_pvOutEnAddr = NULL;                      //GPIO输出使能，虚拟地址
static void __iomem *g_pvIntDisAddr = NULL;                     //GPIO中断，虚拟地址
static void __iomem *g_pvClkCtrlAddr = NULL;                    //时钟控制，虚拟地址

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

/// @brief 在dev创建字符设备驱动文件 
void Create_Led(void);

/// @brief 删除dev目录下的字符设备文件 
void Delete_Led(void);

/// @brief 执行shell指令
/// @param _pCmd shell指令s
static void DealShellCmd(char* _pCmd);

static struct file_operations g_tFile_Operations = 
{
    .owner = THIS_MODULE,
    .open = Led_Open,
    .read = Led_Read,
    .write = Led_Write,
    .release = Led_Release,
};

static int __init Led_Init(void)
{
    int nRtn = 0;
    u32 unReadData = 0;

    //寄存器地址映射
    g_pvDataAddr = ioremap(ZYNQ_GPIO_REG_BASE + DATA_OFFSET, 4);
    g_pvDirmAddr = ioremap(ZYNQ_GPIO_REG_BASE + DIRM_OFFSET, 4);
    g_pvOutEnAddr = ioremap(ZYNQ_GPIO_REG_BASE + OUTEN_OFFSET, 4);
    g_pvIntDisAddr = ioremap(ZYNQ_GPIO_REG_BASE + INTDIS_OFFSET, 4);
    g_pvClkCtrlAddr = ioremap(APER_CLK_CTRL, 4);

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
    
    //默认关闭LED
    unReadData = readl(g_pvDataAddr);
    unReadData &= ~(0x1U << 7);
    writel(unReadData, g_pvDataAddr);

    nRtn = register_chrdev(g_nLed_Major, g_pLedName, &g_tFile_Operations);
        if (nRtn < 0)
    {
        printk(KERN_ALERT "Led_Init register_chrdev err.\n");
    }
    else
    {
        printk(KERN_ALERT "Led_Init register_chrdev success.\n");
        g_nLed_Major = nRtn;
        printk(KERN_ALERT "Led_Init major = %d.\n", g_nLed_Major);
    }

    Create_Led();                                                               //创建字符设备

    printk(KERN_ALERT "Led_Init success.\n");

    return nRtn;
}

static void __exit Led_Exit(void)
{
    iounmap(g_pvDataAddr);
    iounmap(g_pvDirmAddr);
    iounmap(g_pvOutEnAddr);
    iounmap(g_pvIntDisAddr);
    iounmap(g_pvClkCtrlAddr);

    unregister_chrdev(g_nLed_Major, g_pLedName);                            //注销字符设备
    Delete_Led();
    
    printk(KERN_ALERT "Led_Exit success.\n");
}

int Led_Open(struct inode* _pInode, struct file* _pFp)
{
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

    // if(_pFp == NULL || _pBuf == NULL || _Len > sizeof g_chDataBuf || _pOffset == NULL)
    // {
    //     printk(KERN_ALERT "Led_Read input param err.\n");
    //     return -EFAULT;
    // }

    // if (copy_to_user(_pBuf, g_chDataBuf, _Len))                                //将内核数据拷贝到用户空间
    // {
    //     printk(KERN_ALERT "Led_Read copy_to_user err.\n");
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

    if(chDataBuf[0] == 0)       //关闭LED        
        unReadData &= ~(0x1U << 7);
    else                        //打开LED        
        unReadData |= (0x1U << 7);

    writel(unReadData, g_pvDataAddr);

    return _Len;
}

void Create_Led(void)
{
    char chCmd[257] = { 0 };                //命令

    sprintf(chCmd, "sudo mknod -m 666 /dev/%s c %d 0", g_pLedName, g_nLed_Major);

    DealShellCmd(chCmd);
}

void Delete_Led(void)
{
    char chCmd[257] = { 0 };                //命令

    sprintf(chCmd, "sudo rm -rf /dev/%s", g_pLedName);

    DealShellCmd(chCmd);
}

static void DealShellCmd(char* _pCmd)
{
    char cmdPath[] = "/bin/bash";    
    
    char* cmdArgv[] = {cmdPath, "-c", _pCmd, NULL};   
    
    char* cmdEnvp[] = {"HOME=/", "PATH=/sbin:/bin:/usr/bin", NULL};    

    call_usermodehelper(cmdPath, cmdArgv, cmdEnvp, UMH_WAIT_PROC); 
}

module_init(Led_Init);
module_exit(Led_Exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qianrui");