/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	LogicSystem.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.05.06
��  ��: ʵ��һ����̨�߼�ϵͳ
��  ע:
�޸ļ�¼:

  1.  ����: 2025.05.06
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.1.0

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

	if (m_bTheadIsStop)							//��֤�߳���������
	{
		m_cCondVar_Recv.notify_one();			//�����̣߳���ֹ�߳���Ϊ�ź������µ��޷�����
		m_cThread.join();
	}
}

int CLogicSystem::PushBack_RecvMsg_Node(std::shared_ptr<CRecvMsg_Node> _RecvMsg_Node)
{
	std::unique_lock<std::mutex> cUniqueLock(m_cMutex_Recv);

	m_queRecv.push(_RecvMsg_Node);

	if (m_queRecv.size() == 1)					//���û�д���������ݣ��ó�cpu��Դ
		m_cCondVar_Recv.notify_one();

	return 0;
}

void CLogicSystem::Thread_Run(void)
{
	for (;;)
	{
		std::unique_lock<std::mutex> cUniqueLock(m_cMutex_Recv);

		if (m_queRecv.size() == 0)				//���û�д���������ݣ��ó�cpu��Դ
			m_cCondVar_Recv.wait(cUniqueLock);

		//���������ݵ����
		while (m_bTheadIsStop)					//���ֹͣ�̣߳������������ݣ��������������߳�
		{
			if (m_queRecv.size() == 0)			//��������������ݣ��������������߳�
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
