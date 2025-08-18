/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	char_dev_base_app.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.18
描  述: 字符设备驱动测试程序
备  注:	
修改记录:

  1.  日期: 2025.08.18
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

#define RTN_FAILURE -2
#define RTN_SUCCESS 0

constexpr const char* g_pchCharDevName = "/dev/char_dev_base";					//字符驱动文件路径

int main()
{
	int nRtn = -1;
	int nOpenCharDev_Fd = -1;
    char chWriteBuf[] = "write data";
    char chReadBuf[1024] = { 0 };

	nOpenCharDev_Fd = open(g_pchCharDevName, O_RDWR, S_IRUSR | S_IWUSR);
	if (nOpenCharDev_Fd < 0)
	{
		std::cout << "Open char device fail." <<std::endl;
		return RTN_FAILURE;
	}

	for(int i = 0; i < 64; i++)
	{	
		chWriteBuf[strlen(chWriteBuf) - 1] = i % 256;

		if(write(nOpenCharDev_Fd, chWriteBuf, strlen(chWriteBuf)) <= 0)						//写入数据
		{
			std::cout << "Write err." <<std::endl;
			break;
		}

		if(read(nOpenCharDev_Fd, chReadBuf, strlen(chWriteBuf)) <= 0)						//读取当前内核中的数据
		{
			std::cout << "Read err." <<std::endl;
			break;
		}

		if(strcmp(chWriteBuf, chReadBuf))
		{
			std::cout << "Strcmp err." <<std::endl;
			break;
		}
	}

	close(nOpenCharDev_Fd);

	std::cout << "Test char_dev_base_app is success." <<std::endl;

	return RTN_SUCCESS;
}
