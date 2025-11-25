/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	led_app.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.11.25
描  述: 读取按键输入
备  注:	watchdog 是“独占资源”
		✔ 内核 watchdog 驱动启动了硬件狗（cdns-wdt）
		✔ 系统还启动了用户态 watchdog 服务 /usr/sbin/watchdog
		
		让你的应用“接管”看门狗（停止系统级 watchdog），cmd终端执行 
		killall watchdog
		然后你的程序就能成功 open。

修改记录:

  1.  日期: 2025.11.25
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/watchdog.h>
#include <thread>

#define RTN_FAILURE -2
#define RTN_SUCCESS 0

int main(int argc, char* argv[])
{
	int nRtn = -1;
	int nFd = -1;
	int nCmd = -1;

	if(argc < 2)
	{
		std::cout << "Usage:\n\txxx.elf st timeout\n\txxx.elf ka" <<std::endl;
		return RTN_FAILURE;
	}

	nFd = open("/dev/watchdog0", O_WRONLY);
	if (nFd < 0)
	{
		std::cout << "Open char device fail." << std::endl;
		return RTN_FAILURE;
	}

	if(strcmp(argv[1], "st") == 0)			//设置超时时间
		nCmd = 1;
	else if(strcmp(argv[1], "ka") == 0)		//喂狗
		nCmd = 2;
	else
	{
		nCmd = 0;
		std::cout << "Input cmd is not support." <<std::endl;
	}

	switch (nCmd)
	{
	case 1:
	{
		int nTimeout = atoi(argv[2]);
		
		std::cout << "nTimeout = " << nTimeout <<std::endl;

		ioctl(nFd, WDIOC_SETTIMEOUT, &nTimeout);
		break;
	}
	case 2:
	{
		ioctl(nFd, WDIOC_KEEPALIVE, NULL);
		break;
	}
	default:
		break;
	}

	if(nFd)
	{
		close(nFd);
		nFd = 0;
	}

	return RTN_SUCCESS;
}
