/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	iic_app.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.10.14
描  述: iic读写pcf8563时钟芯片
备  注:	
修改记录:

  1.  日期: 2025.10.14
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

#define DEVICE_NAME "/dev/pcf8563"           //设备名称

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

	if(argc < 2)
	{
		std::cout << "Usage:\n\txxx.elf read/write" <<std::endl;
		return RTN_FAILURE;
	}

	nFd = open(DEVICE_NAME, O_RDWR, S_IRUSR | S_IWUSR);
	if (nFd < 0)
	{
		std::cout << "Open char device fail." <<std::endl;
		return RTN_FAILURE;
	}

	if(strcmp(argv[1], "read") == 0)		//读取当前时间
	{
		std::vector<std::string> vecWDay = { "星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期日" };
	
		nRtn = read(nFd, &tPCF8563_Time, sizeof(tPCF8563_Time));
		if(nRtn < 0)
		{
			std::cout << "Read is err." << std::endl;
			return RTN_FAILURE;
		}

		printf("%d-%d-%d %d:%d:%d %s\n", 
			tPCF8563_Time.Year, 
			tPCF8563_Time.Month, 
			tPCF8563_Time.Day, 
			tPCF8563_Time.Hour, 
			tPCF8563_Time.Min, 
			tPCF8563_Time.Sec,
			vecWDay[tPCF8563_Time.WDay - 1].c_str()
			);
	}
	else if(strcmp(argv[1], "write") == 0)	//写入时间
	{
		printf("年:");
		scanf("%d", &tPCF8563_Time.Year);
		printf("月:");
		scanf("%d", &tPCF8563_Time.Month);
		printf("日:");
		scanf("%d", &tPCF8563_Time.Day);
		printf("星期:");
		scanf("%d", &tPCF8563_Time.WDay);
		printf("时:");
		scanf("%d", &tPCF8563_Time.Hour);
		printf("分:");
		scanf("%d", &tPCF8563_Time.Min);
		printf("秒:");
		scanf("%d", &tPCF8563_Time.Sec);

		nRtn = write(nFd, &tPCF8563_Time, sizeof(tPCF8563_Time));
		if(nRtn < 0)
		{
			std::cout << "write is err." << std::endl;
			return RTN_FAILURE;
		}
	}
	else		//不支持的操作
		std::cout << "Input parameter is err." << std::endl;

	close(nFd);
	nFd = 0;

	return RTN_SUCCESS;
}
