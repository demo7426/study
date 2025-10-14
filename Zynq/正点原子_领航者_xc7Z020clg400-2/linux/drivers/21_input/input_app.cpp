/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	led_app.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.10.14
描  述: 读取按键输入
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

#define RTN_FAILURE -2
#define RTN_SUCCESS 0

int main(int argc, char* argv[])
{
	int nRtn = -1;
	int nOpenCharDev_Fd = -1;
	struct input_event tInputEv;

	if(argc < 2)
	{
		std::cout << "Usage:\n\txxx.elf /dev/input/eventX" <<std::endl;
		return RTN_FAILURE;
	}

	nOpenCharDev_Fd = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);
	if (nOpenCharDev_Fd < 0)
	{
		std::cout << "Open char device fail." <<std::endl;
		return RTN_FAILURE;
	}

	for(;;)
	{	
		nRtn = read(nOpenCharDev_Fd, &tInputEv, sizeof(tInputEv));
		if(nRtn)
		{
			switch (tInputEv.type)
			{
			case EV_KEY:				//按键事件
				if(KEY_0 == tInputEv.code)
				{
					if(tInputEv.value == 1)
						std::cout << "PS Key0 Pressed\n";
					else if(tInputEv.value == 0)
						std::cout << "PS Key0 Release\n";	
					else
						std::cout << "PS Key0 Long-term Pressing\n";
				}
				break;
			case EV_REL:
				break;
			case EV_ABS:
				break;
			case EV_MSC:
				break;
			default:
				break;
			}
		}
		else
		{
			std::cout << "Error: file read failed." <<std::endl;
			break;
		}
	}

	close(nOpenCharDev_Fd);
	return RTN_SUCCESS;
}
