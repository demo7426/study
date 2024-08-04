/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	02_ModuleHelloworldPara.c
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.07.31
描  述: 内核带参数模块
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

static int g_nInitValue = 0;                    //初始化值
static char* g_pchInitName = NULL;              //初始化名称

module_param(g_nInitValue, int, S_IRUGO);
module_param(g_pchInitName, charp, S_IRUGO);

static int __init Init(void)
{
    printk(KERN_ALERT "g_pchInitName = %d, g_pchInitName = %s", g_nInitValue, g_pchInitName);
    printk(KERN_ALERT "(init) Hello world\n");
    return 0;
}

static void __exit Exit(void)
{
    printk(KERN_ALERT "(exit) Hello world\n");
}


module_init(Init);
module_exit(Exit);
