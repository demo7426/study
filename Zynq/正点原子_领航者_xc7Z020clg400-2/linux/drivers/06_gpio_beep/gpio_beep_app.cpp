/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	led_app.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.09.07
描  述: 控制蜂鸣器
备  注:	
修改记录:

  1.  日期: 2025.09.07
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

constexpr const char* g_pchCharDevName = "/dev/Gpio_Beep";					//字符驱动文件路径

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("Please input param: ./xxx.elf status\n");
		return 0;
	}

	int nRtn = -1;
	int nOpenCharDev_Fd = -1;
    char chWriteData = atoi(argv[1]);

	nOpenCharDev_Fd = open(g_pchCharDevName, O_RDWR, S_IRUSR | S_IWUSR);
	if (nOpenCharDev_Fd < 0)
	{
		std::cout << "Open char device fail." <<std::endl;
		return RTN_FAILURE;
	}

	if(write(nOpenCharDev_Fd, &chWriteData, sizeof(chWriteData)) <= 0)						//写入数据
	{
		std::cout << "Write err." <<std::endl;
	}
	else
		std::cout << "Test beep is success." <<std::endl;

	close(nOpenCharDev_Fd);

	return RTN_SUCCESS;
}
