/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	iic_app.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.11.25
描  述: 实现对外设beep蜂鸣器的控制
备  注:	
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
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <thread>
#include <vector>

#define RTN_FAILURE -2
#define RTN_SUCCESS 0

#define DEVICE_NAME "/dev/zynq-beep"           //设备名称

int main(int argc, char* argv[])
{
	int nRtn = -1;
	int nFd = -1;

	if(argc < 2)
	{
		std::cout << "Usage:\n\txxx.elf 0/1" <<std::endl;
		return RTN_FAILURE;
	}

	nFd = open(DEVICE_NAME, O_RDWR, S_IRUSR | S_IWUSR);
	if (nFd < 0)
	{
		std::cout << "Open char device fail." <<std::endl;
		return RTN_FAILURE;
	}

	int8_t nData = atoi(argv[1]);
	nRtn = write(nFd, &nData, sizeof(nData));
	if(nRtn < 0)
	{
		std::cout << "write is err." << std::endl;
	}

	close(nFd);
	nFd = 0;

	return RTN_SUCCESS;
}
