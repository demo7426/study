/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	led_app.cpp
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

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <thread>

#define RTN_FAILURE -2
#define RTN_SUCCESS 0

constexpr const char* g_pchCharDevName = "/dev/Gpio_Led";					//字符驱动文件路径

int main()
{
	int nRtn = -1;
	int nOpenCharDev_Fd = -1;
    char chWriteData = 0;

	nOpenCharDev_Fd = open(g_pchCharDevName, O_RDWR, S_IRUSR | S_IWUSR);
	if (nOpenCharDev_Fd < 0)
	{
		std::cout << "Open char device fail." <<std::endl;
		return RTN_FAILURE;
	}

	for(int i = 0; i < 64; i++)
	{	
		chWriteData++;
		chWriteData %= 2;

		chWriteData == 1? std::cout << "LED亮." <<std::endl: std::cout << "LED灭." <<std::endl;

		if(write(nOpenCharDev_Fd, &chWriteData, sizeof(chWriteData)) <= 0)						//写入数据
		{
			std::cout << "Write err." <<std::endl;
			break;
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	close(nOpenCharDev_Fd);

	std::cout << "Test led is success." <<std::endl;

	return RTN_SUCCESS;
}
