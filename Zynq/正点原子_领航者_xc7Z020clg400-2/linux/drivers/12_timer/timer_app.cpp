/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	timer_app.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.09.12
描  述: 使用设备树中的gpio，定时器或手动控制Led灯的亮灭实验
备  注:	
修改记录:

  1.  日期: 2025.09.12
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
#include <sys/ioctl.h>

#include <thread>

#define RTN_FAILURE -2
#define RTN_SUCCESS 0

#define CMD_LED_CLOSE       (_IO(0xEF, 0x1))                    			//关闭LED
#define CMD_LED_OPEN        (_IO(0xEF, 0x2))                    			//开启LED
#define CMD_LED_PERIOD      (_IO(0xEF, 0x3))                    			//设置定时器LED反转时间

constexpr const char* g_pchCharDevName = "/dev/Gpio_Led";					//字符驱动文件路径


int main()
{
	int nRtn = -1;
	int nOpenCharDev_Fd = -1;
	unsigned int unCmd = 0;													//指令编码
	long unsigned int unTimerPeriod = 0;									//定时器时间间隔		

	nOpenCharDev_Fd = open(g_pchCharDevName, O_RDWR, S_IRUSR | S_IWUSR);
	if (nOpenCharDev_Fd < 0)
	{
		std::cout << "Open char device fail." <<std::endl;
		return RTN_FAILURE;
	}

	for(;;)
	{
		std::cout << "Input cmd:\n	0--关闭LED;1--打开LED;2--设置LED的定时器时间，并启动" <<std::endl;
		if(scanf("%d", &unCmd) == 0)
		{
			while(getchar() != '\n');
			std::cout << "Input cmd:\n	0--关闭LED;1--打开LED;2--设置LED的定时器时间，并启动" <<std::endl;
			continue;
		}

		switch(unCmd)
		{
		case 0:
			unCmd = CMD_LED_CLOSE;
			break;
		case 1:
			unCmd = CMD_LED_OPEN;
			break;
		case 2:
			unCmd = CMD_LED_PERIOD;
			
			//获取定时器时间间隔信息
			std::cout << "Input timer_period: unit millisecond" <<std::endl;		
			scanf("%d", &unTimerPeriod);
			break;
		default:
			break;
		}

		ioctl(nOpenCharDev_Fd, unCmd, unTimerPeriod);
	}

	close(nOpenCharDev_Fd);

	std::cout << "Test led is success." <<std::endl;

	return RTN_SUCCESS;
}
