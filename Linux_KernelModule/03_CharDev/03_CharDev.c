/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	03_CharDev.c
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.07.31
描  述: 编写一个简易的字符设备驱动
备  注:	注册时字符设备驱动后，还需要再 /dev/ 下面创建驱动对应名称的字符设备文件
修改记录:

  1.  日期: 2024.07.31
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

static int g_nUserValue = 100;                              //用户数据
static int g_nCharDev_Major = 0;                            //字符设备主设备号
static const char* g_pCharDevName = "03_CharDev";           //字符设备名称


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

/// @brief 在dev创建字符设备驱动文件 
void Create_CharDev(void);

/// @brief 删除dev目录下的字符设备文件 
void Delete_CharDev(void);

/// @brief 执行shell指令
/// @param _pCmd shell指令s
void DealShellCmd(char* _pCmd);

struct file_operations g_tFile_Operations = 
{
    .read = CharDev_Read,
    .write = CharDev_Write
};

/// @brief 字符设备初始化函数
/// @return <0--执行失败,>0--执行成功
static int __init CharDev_Init(void)
{
    int nRtn = 0;

    nRtn = register_chrdev(g_nCharDev_Major, g_pCharDevName, &g_tFile_Operations);                //向内核注册字符设备
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

    Create_CharDev();
    
    return nRtn;
}

/// @brief 字符设备退出函数
static void __exit CharDev_Exit(void)
{
    unregister_chrdev(g_nCharDev_Major, g_pCharDevName);                                        //注销字符设备
    Delete_CharDev();

    printk(KERN_ALERT "CharDev_Exit success.\n");
    return;
}

ssize_t CharDev_Read(struct file* _pFp, char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    if(_pFp == NULL || _pBuf == NULL || _Len < sizeof g_nUserValue || _pOffset == NULL)
    {
        printk(KERN_ALERT "CharDev_Read input param err.\n");
        return -EFAULT;
    }

    if (raw_copy_to_user(_pBuf, &g_nUserValue, sizeof g_nUserValue))                                //将内核数据拷贝到用户空间
    {
        printk(KERN_ALERT "CharDev_Read copy_to_user err.\n");
        return -EFAULT;
    }
    
    return sizeof(g_nUserValue);
}



ssize_t CharDev_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    if(_pFp == NULL || _pBuf == NULL || _Len > sizeof g_nUserValue || _pOffset == NULL)
    {
        printk(KERN_ALERT "CharDev_Write input param err.\n");
        return -EFAULT;
    }

    if(raw_copy_from_user(&g_nUserValue, _pBuf, sizeof g_nUserValue))                               //将用户数据拷贝到内核空间
    {   
        printk(KERN_ALERT "CharDev_Write copy_from_user err.\n");
        return -EFAULT;
    }

    return sizeof(g_nUserValue);
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

void DealShellCmd(char* _pCmd)
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