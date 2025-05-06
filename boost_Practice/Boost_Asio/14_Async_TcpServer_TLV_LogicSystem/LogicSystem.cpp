/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	LogicSystem.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.05.06
描  述: 实现一个后台逻辑系统
备  注:
修改记录:

  1.  日期: 2025.05.06
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#include "LogicSystem.h"
#include "Session.h"

CLogicSystem::CLogicSystem()
{
	Register_CallbackFunc();

	m_cThread = std::thread(&CLogicSystem::Thread_Run, this);
}

CLogicSystem::~CLogicSystem()
{	
	std::cout << __FUNCTION__ << std::endl;
	
	m_bTheadIsStop = true;

	if (m_bTheadIsStop)							//保证线程正常结束
	{
		m_cCondVar_Recv.notify_one();			//唤醒线程，防止线程因为信号量导致的无法醒来
		m_cThread.join();
	}
}

int CLogicSystem::PushBack_RecvMsg_Node(std::shared_ptr<CRecvMsg_Node> _RecvMsg_Node)
{
	std::unique_lock<std::mutex> cUniqueLock(m_cMutex_Recv);

	m_queRecv.push(_RecvMsg_Node);

	if (m_queRecv.size() == 1)					//如果没有待处理的数据，让出cpu资源
		m_cCondVar_Recv.notify_one();

	return 0;
}

void CLogicSystem::Thread_Run(void)
{
	for (;;)
	{
		std::unique_lock<std::mutex> cUniqueLock(m_cMutex_Recv);

		if (m_queRecv.size() == 0)				//如果没有待处理的数据，让出cpu资源
			m_cCondVar_Recv.wait(cUniqueLock);

		//处理有数据的情况
		while (m_bTheadIsStop)					//如果停止线程，则处理所有数据，并且正常结束线程
		{
			if (m_queRecv.size() == 0)			//处理完毕所有数据，并且正常结束线程
				return;

			std::shared_ptr<CRecvMsg_Node> pRecvMsg_Node = m_queRecv.front();

			m_queRecv.pop();

			auto it = m_mapCallbackFunc.find((CLogicSystem::TLV_TYPE)pRecvMsg_Node->GetTLV_Type());
			if (it == m_mapCallbackFunc.end())
				continue;

			it->second(pRecvMsg_Node);
		}

		if (!m_bTheadIsStop)
		{
			std::shared_ptr<CRecvMsg_Node> pRecvMsg_Node = m_queRecv.front();

			m_queRecv.pop();

			auto it = m_mapCallbackFunc.find((CLogicSystem::TLV_TYPE)pRecvMsg_Node->GetTLV_Type());
			if (it == m_mapCallbackFunc.end())
				continue;

			it->second(pRecvMsg_Node);
		}
	}

}

void CLogicSystem::Register_CallbackFunc(void)
{
	auto bindFunc = std::bind(&CLogicSystem::HelloWorld, this, std::placeholders::_1);
	
	m_mapCallbackFunc[CLogicSystem::TLV_TYPE::HELLOWORLD] = bindFunc;
}

void CLogicSystem::HelloWorld(std::shared_ptr<CRecvMsg_Node> _RecvMsg_Node)
{
	//std::cout << __FUNCTION__ << std::endl;

	std::shared_ptr<CSession> pcSharedPtr_Session = _RecvMsg_Node->GetSession();

	pcSharedPtr_Session->Send(_RecvMsg_Node->GetDataStartAddr(), _RecvMsg_Node->GetMaxLen());
}
