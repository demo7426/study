/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_26_使用 condition_variable 实现生产者和消费者模型-2.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.07.06
描  述: 生产者、消费者模型测试
备  注:
修改记录:

  1.  日期: 2024.07.06
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/

#include <iostream>
#include <thread>

#include "TaskQueue.h"

int Test01(void) throw()
{
	constexpr unsigned int unMaxTaskQueueCap = 200;							//任务队列最大容量
	constexpr unsigned int unProductNum = 5;								//生产者数量
	constexpr unsigned int unConsumeNum = unProductNum;						//消费者数量

	CTaskQueue cTaskQueue(unMaxTaskQueueCap);
	std::thread cThProduct[unProductNum];
	std::thread cThConsume[unConsumeNum];

	void* pvConsumeAddr[unConsumeNum] = { nullptr };

	for (size_t i = 0; i < unProductNum; i++)
	{
		cThProduct[i] = std::thread(&CTaskQueue::Push_Back, &cTaskQueue, reinterpret_cast<void*>(0x10000 + i));
		cThConsume[i] = std::thread(&CTaskQueue::Pop_Front, &cTaskQueue, pvConsumeAddr + i);
	}

	for (size_t i = 0; i < unProductNum; i++)
	{
		cThProduct[i].join();
		cThConsume[i].join();
	}

	return 0;
}

int main()
{
	Test01();

	return EXIT_SUCCESS;
}

