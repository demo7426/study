/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	LogicSystem.h
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

#pragma once

#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <map>

#include "Singleton.h"
#include "MsgNode.h"

class CLogicSystem : public CSingleton<CLogicSystem>
{
	friend class CSingleton<CLogicSystem>;
private:
	CLogicSystem();

	typedef std::function<void(std::shared_ptr<CRecvMsg_Node>)> CallbackFunc;	//�ص���������

	enum TLV_TYPE			//TLV��ʽ֧�ֵ�����ID
	{	
		HELLOWORLD = 1001		
	};

public:
	~CLogicSystem();

	/// <summary>
	/// ��ӽ������ݽڵ�
	/// </summary>
	/// <param name="_RecvMsg_Node"></param>
	/// <returns></returns>
	int PushBack_RecvMsg_Node(std::shared_ptr<CRecvMsg_Node> _RecvMsg_Node);

private:

	/// <summary>
	/// �̴߳�����
	/// </summary>
	/// <param name=""></param>
	void Thread_Run(void);

	/// <summary>
	/// ע��ص�����
	/// </summary>
	/// <param name=""></param>
	void Register_CallbackFunc(void);

	/// <summary>
	/// Hello world�ص�����
	/// </summary>
	/// <param name="_RecvMsg_Node">�������ݽڵ�</param>
	void HelloWorld(std::shared_ptr<CRecvMsg_Node> _RecvMsg_Node);

private:
	std::mutex m_cMutex_Recv;												//���յĻ�����
	std::condition_variable m_cCondVar_Recv;								//���յ���������
	
	bool m_bTheadIsStop = false;											//�Ƿ�ֹͣ�߳�;false--��ֹͣ;true--ֹͣ
	std::thread m_cThread;													//����������ݵ��߳�

	std::queue<std::shared_ptr<CRecvMsg_Node>> m_queRecv;					//���ݽ��ջ������

	std::map<CLogicSystem::TLV_TYPE, CallbackFunc> m_mapCallbackFunc;		//�ص�����map��
};



