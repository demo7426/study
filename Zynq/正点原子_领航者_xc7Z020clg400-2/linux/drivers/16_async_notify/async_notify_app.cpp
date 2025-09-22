/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	no_block_io_app.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.09.17
描  述: 使用设备树中的gpio，通过中断读取按键输入，非阻塞io访问按键当前输入值
备  注:	
修改记录:

  1.  日期: 2025.09.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <signal.h>

#include <thread>

#define RTN_FAILURE -2
#define RTN_SUCCESS 0

constexpr const char* g_pchCharDevName = "/dev/key";					//字符驱动文件路径
int g_nOpenCharDev_Fd = -1;

static void SigIO_Signal_CallBack(int _SigNum)
{
	int nReadData = 0;

	if(read(g_nOpenCharDev_Fd, &nReadData, sizeof(nReadData)) <= 0)	
	{
		std::cout << "Read err." <<std::endl;
		return;
	}

	if(nReadData == 0)
		std::cout << "Key is pressed." <<std::endl;
	else if(nReadData == 1)
		std::cout << "Key is release." <<std::endl;
}

int main()
{
	int nFlags = 0;

	g_nOpenCharDev_Fd = open(g_pchCharDevName, O_RDWR | O_NONBLOCK);
	if (g_nOpenCharDev_Fd < 0)
	{
		std::cout << "Open char device fail." <<std::endl;
		return RTN_FAILURE;
	}

	signal(SIGIO, SigIO_Signal_CallBack);

	fcntl(g_nOpenCharDev_Fd, F_SETOWN, getpid());			//将当前进程的进程号告诉给内核
	nFlags = fcntl(g_nOpenCharDev_Fd, F_GETFD);				//获取当前的进程状态
	fcntl(g_nOpenCharDev_Fd, F_SETFL, nFlags | FASYNC);		//设置进程启动异步通知功能

	for(;;)
	{
		sleep(2);
	}

	close(g_nOpenCharDev_Fd);

	std::cout << "Test key is success." <<std::endl;

	return RTN_SUCCESS;
}
