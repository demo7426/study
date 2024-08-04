/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	01_Helloworld.c
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.07.31
描  述: 编写一个简易的内核模块
备  注:	
修改记录:

  1.  日期: 2024.07.31
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qianrui");

/// @brief 模块初始化函数
/// @param  
/// @return 
static int __init Init(void)
{
    printk(KERN_ALERT "(init) Hello world.\n");
    return 0;
}

static void __exit Exit(void)
{
    printk(KERN_ALERT "(exit) Hello world.\n");
}



module_init(Init);              //模块初始化入口函数
module_exit(Exit);              //模块退出时清除函数

