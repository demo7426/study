//文件描述：
//      实现一个线程池模块（线程池中最少有1个线程，因为必须存在一个主线程）
//作者：钱锐
//时间：2024/2/20
//修改记录：
//      2024/2/20     新建
#pragma once
#include <stdbool.h>
#include <vector>

#include "WorkThread.h"

class CThreadPool
{
public:
	CThreadPool() = delete;
	CThreadPool(CEventLoop* _pMainLoop, int _SubThreadNum);
	~CThreadPool();

	// 线程池启动
	void Run();

	//获取反应堆实例指针，用于向其事件循环内部任务队列添加子任务
	CEventLoop* GetEventLoopObj();

private:
	bool m_bIsStart;								//线程池是否启动;true--已启动,false--未启动
	int m_nSubThreadNum;							//线程池内部子线程数量
	int m_nSubThreadIndex;							//子线程索引

	CEventLoop* m_pcMainEventLoop;					//主线程事件循环模块
	std::vector<CWorkThread*> m_pvecWorkThread;		//子线程工作者线程起始地址		
};

