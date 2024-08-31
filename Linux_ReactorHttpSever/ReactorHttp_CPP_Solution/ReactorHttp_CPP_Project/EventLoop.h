//文件描述：
//      实现一个EventLoop模块
//作者：钱锐
//时间：2024/2/18
//修改记录：
//      2024/2/18     新建

#pragma once
#include <stdbool.h>
#include <thread>
#include <mutex>
#include <queue>
#include <map>

#include "Dispatcher.h"

enum class ELEMENTTYPE:char
{
	ADD, DELETE, MODIFY
};

typedef struct _CHANNELELEMENT
{
	enum ELEMENTTYPE Type;									//如何处理当前节点中的channel
	CChannel* ChannelInfo;
}CHANNELELEMENT, *PCHANNELELEMENT;

class CDispatcher;
class CEventLoop
{
public:
	CEventLoop();
	CEventLoop(std::string _ThreadName);

	//启动反应堆模型
	int Run();

	//向任务队列内部添加子任务
	int AddTask(CChannel* _pChannel_Info, ELEMENTTYPE _Type);

	//处理被激活的文件fd
	int Activate(int _Fd, ENUM_FDEVENT _Event);  

	inline std::thread::id GetThreadId() const
	{
		return m_thThreadId;
	}

	//销毁CChannel* 内存
	int DestroyChannelInfo(CChannel* _pChannel_Info);

private:
	bool IsQuit;								//当前EventLoop是否退出;true--退出;false--未退出

	CDispatcher* m_pcDispatcher;

	//任务队列
	std::queue<PCHANNELELEMENT> m_queTaskQ;

	// ChannelMap
	std::map<int, CChannel*> pChMap_Info;

	//线程相关
	std::thread::id m_thThreadId;							//线程id
	std::string m_strThreadNames;							//线程名称
	std::mutex m_ThreadMutex;								//线程互斥量

	int m_nSocketPairs[2];									//存储本地通信的fd，用于唤醒被阻塞的通信模型，通过socketpair函数初始化

private:
	int WriteLocalMsg();

	int ReadLocalMsg();

	//处理任务队列内部的任务
	int ProcessTask();

	//处理任务队列内部的任务，添加任务
	int ProcessTask_Add(CChannel* _pChannel_Info);

	//处理任务队列内部的任务，删除任务
	int ProcessTask_Delete(CChannel* _pChannel_Info);

	//处理任务队列内部的任务，修改任务
	int ProcessTask_Modify(CChannel* _pChannel_Info);


};

