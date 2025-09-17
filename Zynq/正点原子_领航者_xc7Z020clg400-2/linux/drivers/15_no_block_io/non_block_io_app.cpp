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

#include <thread>

#define RTN_FAILURE -2
#define RTN_SUCCESS 0

constexpr const char* g_pchCharDevName = "/dev/key";					//字符驱动文件路径

int main()
{
	int nRtn = -1;
	int nOpenCharDev_Fd = -1;
	int nReadData = 0;
	fd_set tReadFds;

	nOpenCharDev_Fd = open(g_pchCharDevName, O_RDWR | O_NONBLOCK, S_IRUSR | S_IWUSR);
	if (nOpenCharDev_Fd < 0)
	{
		std::cout << "Open char device fail." <<std::endl;
		return RTN_FAILURE;
	}

	FD_ZERO(&tReadFds);
	FD_SET(nOpenCharDev_Fd, &tReadFds);

	for(;;)
	{
		fd_set tTmpFds = tReadFds;

		nRtn = select(nOpenCharDev_Fd + 1, &tTmpFds, NULL, NULL, NULL);

		switch(nRtn)
		{
		case 0:			//超时
			break;
		case -2:		//错误
			break;
		default:
			if(FD_ISSET(nOpenCharDev_Fd, &tTmpFds))
			{
				if(read(nOpenCharDev_Fd, &nReadData, sizeof(nReadData)) <= 0)	
				{
					std::cout << "Read err." <<std::endl;
					break;
				}

				if(nReadData == 0)
					std::cout << "Key is pressed." <<std::endl;
				else if(nReadData == 1)
					std::cout << "Key is release." <<std::endl;
			}
			break;
		}
	}

	close(nOpenCharDev_Fd);

	std::cout << "Test key is success." <<std::endl;

	return RTN_SUCCESS;
}
