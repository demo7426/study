/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Test.c
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.07.31
描  述: 编写一个对字符设备驱动的测试函数
备  注:	
修改记录:

  1.  日期: 2024.07.31
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define RTN_FAILURE -2
#define RTN_SUCCESS 0

constexpr const char* g_pchCharDevName = "/dev/03_CharDev";					//字符驱动文件路径

int Test(void)
{
	int nRtn = -1;
	int nOpenCharDev_Fd = -1;
	int nReadValue = 0;

	nOpenCharDev_Fd = open(g_pchCharDevName, O_RDWR, S_IRUSR | S_IWUSR);
	if (nOpenCharDev_Fd < 0)
	{
		std::cout << "Test open char device fail." <<std::endl;
		return RTN_FAILURE;
	}
	
	if(read(nOpenCharDev_Fd, &nReadValue, sizeof nReadValue) <= 0)						//读取当前内核中的数据
	{
		std::cout << "Test read err." <<std::endl;
		close(nOpenCharDev_Fd);
		return RTN_FAILURE;
	}

	std::cout << "Test first nReadValue = " << nReadValue <<std::endl;

	nReadValue = 999;
	if(write(nOpenCharDev_Fd, &nReadValue, sizeof nReadValue) <= 0)						//写入数据
	{
		std::cout << "Test write err." <<std::endl;
		close(nOpenCharDev_Fd);
		return RTN_FAILURE;
	}

	if(read(nOpenCharDev_Fd, &nReadValue, sizeof nReadValue) <= 0)						//读取当前内核中的数据
	{
		std::cout << "Test read err." <<std::endl;
		close(nOpenCharDev_Fd);
		return RTN_FAILURE;
	}

	std::cout << "Test second read nReadValue = " << nReadValue <<std::endl;

	close(nOpenCharDev_Fd);
	nOpenCharDev_Fd = -1;

	return RTN_SUCCESS;
}

int main(void)
{
	Test();

	return RTN_SUCCESS;
}

