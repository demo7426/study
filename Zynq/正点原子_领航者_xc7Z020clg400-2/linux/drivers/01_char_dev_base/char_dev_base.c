/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	char_dev_base.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.18
描  述: 字符设备驱动模板
备  注:	
修改记录:

  1.  日期: 2025.08.18
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

static char g_chDataBuf[64 * 1024] = { 0 };                     //读写数据缓冲
static int g_nCharDev_Major = 0;                                //字符设备主设备号
static const char* g_pCharDevName = "char_dev_base";            //字符设备名称

/// @brief 对字符设备文件 open 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int CharDev_Open(struct inode* _pInode, struct file* _pFp);  

/// @brief 对字符设备文件 read 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t CharDev_Read(struct file* _pFp, char __user* _pBuf, size_t _Len, loff_t* _pOffset);                    

/// @brief 对字符设备文件 write 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t CharDev_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset);

/// @brief 对字符设备文件 release 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int CharDev_Release(struct inode* _pInode, struct file* _pFp);  

/// @brief 在dev创建字符设备驱动文件 
void Create_CharDev(void);

/// @brief 删除dev目录下的字符设备文件 
void Delete_CharDev(void);

/// @brief 执行shell指令
/// @param _pCmd shell指令s
static void DealShellCmd(char* _pCmd);

static struct file_operations g_tFile_Operations = 
{
    .owner = THIS_MODULE,
    .open = CharDev_Open,
    .read = CharDev_Read,
    .write = CharDev_Write,
    .release = CharDev_Release,
};

static int __init CharDev_Init(void)
{
    int nRtn = 0;

    nRtn = register_chrdev(g_nCharDev_Major, g_pCharDevName, &g_tFile_Operations);
        if (nRtn < 0)
    {
        printk(KERN_ALERT "CharDev_Init register_chrdev err.\n");
    }
    else
    {
        printk(KERN_ALERT "CharDev_Init register_chrdev success.\n");
        g_nCharDev_Major = nRtn;
        printk(KERN_ALERT "CharDev_Init major = %d.\n", g_nCharDev_Major);
    }

    Create_CharDev();                                                               //创建字符设备

    printk(KERN_ALERT "CharDev_Init success.\n");

    return nRtn;
}

static void __exit CharDev_Exit(void)
{
    unregister_chrdev(g_nCharDev_Major, g_pCharDevName);                            //注销字符设备
    Delete_CharDev();
    
    printk(KERN_ALERT "CharDev_Exit success.\n");
}

int CharDev_Open(struct inode* _pInode, struct file* _pFp)
{
    printk(KERN_ALERT "CharDev_Open success.\n");
    return 0;
}

int CharDev_Release(struct inode* _pInode, struct file* _pFp)
{
    printk(KERN_ALERT "CharDev_Release success.\n");
    return 0;
}

ssize_t CharDev_Read(struct file* _pFp, char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    if(_pFp == NULL || _pBuf == NULL || _Len > sizeof g_chDataBuf || _pOffset == NULL)
    {
        printk(KERN_ALERT "CharDev_Read input param err.\n");
        return -EFAULT;
    }

    
    if (copy_to_user(_pBuf, g_chDataBuf, _Len))                                //将内核数据拷贝到用户空间
    {
        printk(KERN_ALERT "CharDev_Read copy_to_user err.\n");
        return -EFAULT;
    }

    return _Len;
}

/// @brief 对字符设备文件 write 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t CharDev_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    if(_pFp == NULL || _pBuf == NULL || _Len > sizeof g_chDataBuf || _pOffset == NULL)
    {
        printk(KERN_ALERT "CharDev_Write input param err.\n");
        return -EFAULT;
    }

    if (copy_from_user(g_chDataBuf, _pBuf, _Len))                                //将用户数据拷贝到内核空间
    {
        printk(KERN_ALERT "CharDev_Write copy_from_user err.\n");
        return -EFAULT;
    }

    return _Len;
}

void Create_CharDev(void)
{
    char chCmd[257] = { 0 };                //命令

    sprintf(chCmd, "sudo mknod -m 666 /dev/%s c %d 0", g_pCharDevName, g_nCharDev_Major);

    DealShellCmd(chCmd);
}

void Delete_CharDev(void)
{
    char chCmd[257] = { 0 };                //命令

    sprintf(chCmd, "sudo rm -rf /dev/%s", g_pCharDevName);

    DealShellCmd(chCmd);
}

static void DealShellCmd(char* _pCmd)
{
    char cmdPath[] = "/bin/bash";    
    
    char* cmdArgv[] = {cmdPath, "-c", _pCmd, NULL};   
    
    char* cmdEnvp[] = {"HOME=/", "PATH=/sbin:/bin:/usr/bin", NULL};    

    call_usermodehelper(cmdPath, cmdArgv, cmdEnvp, UMH_WAIT_PROC); 
}

module_init(CharDev_Init);
module_exit(CharDev_Exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qianrui");