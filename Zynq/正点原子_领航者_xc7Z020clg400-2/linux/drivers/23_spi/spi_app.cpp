/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	iic_app.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.11.05
描  述: spi测试程序
备  注:	
修改记录:

  1.  日期: 2025.11.05
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

#define DEVICE_NAME "/dev/myspi"           //设备名称

typedef struct _PCF8563_TIME
{
    int Sec;                            //秒
    int Min;                            //分
    int Hour;                           //小时
    int Day;                            //日
    int WDay;                           //星期
    int Month;                          //月
    int Year;                           //年
}PCF8563_TIME, *PPCF8563_TIME;

int main(int argc, char* argv[])
{
	int nRtn = -1;
	int nFd = -1;
	PCF8563_TIME tPCF8563_Time = { 0 };

	nFd = open(DEVICE_NAME, O_RDWR, S_IRUSR | S_IWUSR);
	if (nFd < 0)
	{
		std::cout << "Open char device fail." <<std::endl;
		return RTN_FAILURE;
	}

	close(nFd);
	nFd = 0;

	return RTN_SUCCESS;
}
