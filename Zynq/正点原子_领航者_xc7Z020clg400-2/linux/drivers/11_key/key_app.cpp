/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	led_app.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.09.11
描  述: 使用设备树中的gpio，读取按键输入
备  注:	
修改记录:

  1.  日期: 2025.09.11
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

#include <thread>

#define RTN_FAILURE -2
#define RTN_SUCCESS 0

constexpr const char* g_pchCharDevName = "/dev/key";					//字符驱动文件路径

int main()
{
	int nRtn = -1;
	int nOpenCharDev_Fd = -1;
	int nReadData = 0;

	nOpenCharDev_Fd = open(g_pchCharDevName, O_RDWR, S_IRUSR | S_IWUSR);
	if (nOpenCharDev_Fd < 0)
	{
		std::cout << "Open char device fail." <<std::endl;
		return RTN_FAILURE;
	}

	for(;;)
	{
		if(read(nOpenCharDev_Fd, &nReadData, sizeof(nReadData)) <= 0)	
		{
			std::cout << "Read err." <<std::endl;
			break;
		}

		if(nReadData == 0)
		{
			std::cout << "Key is pressed." <<std::endl;
		}
	}

	close(nOpenCharDev_Fd);

	std::cout << "Test key is success." <<std::endl;

	return RTN_SUCCESS;
}
