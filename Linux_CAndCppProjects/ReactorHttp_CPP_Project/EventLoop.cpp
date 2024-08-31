#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>          /* See NOTES */
#include <arpa/inet.h>
#include <unistd.h>


#include "SelectDispatcher.h"
#include "PollDispatcher.h"
#include "EpollDispatcher.h"
#include "EventLoop.h"

using namespace std;

int CEventLoop::WriteLocalMsg()
{
	write(this->m_nSocketPairs[0], "1", strlen("1"));
	return 0;
}

int CEventLoop::ReadLocalMsg()
{
	char chReadBuf[256] = { 0 };

	read(this->m_nSocketPairs[1], chReadBuf, sizeof chReadBuf);
	return 0;
}

int CEventLoop::ProcessTask()
{
	while (!this->m_queTaskQ.empty())
	{
		this->m_ThreadMutex.lock();
		PCHANNELELEMENT ptChEle = this->m_queTaskQ.front();
		this->m_queTaskQ.pop();

		this->m_ThreadMutex.unlock();

		if (ptChEle->Type == ELEMENTTYPE::ADD)
		{
			//���
			ProcessTask_Add(ptChEle->ChannelInfo);
		}
		else if (ptChEle->Type == ELEMENTTYPE::DELETE)
		{
			//ɾ��
			ProcessTask_Delete(ptChEle->ChannelInfo);

			//TODO:��δ�ͷ��ڴ���Դ
			//EventLoopDestroyChannelInfo(_pEventLoop_Info, ptChEle->ChannelInfo);
		}
		else if (ptChEle->Type == ELEMENTTYPE::MODIFY)
		{
			//�޸�
			ProcessTask_Modify(ptChEle->ChannelInfo);
		}

		delete ptChEle;
	}

	return 0;
}

int CEventLoop::ProcessTask_Add(CChannel* _pChannel_Info)
{
	int nFd = _pChannel_Info->GetFd();

	//ˢ��ChannnelMap������ļ�������
	if (this->pChMap_Info.find(nFd) == this->pChMap_Info.end())
	{
		this->pChMap_Info.insert(make_pair(nFd, _pChannel_Info));

		this->m_pcDispatcher->SetChannel(_pChannel_Info);
		this->m_pcDispatcher->Add();
	}

	return 0;
}

int CEventLoop::ProcessTask_Delete(CChannel* _pChannel_Info)
{
	int nFd = _pChannel_Info->GetFd();
	this->pChMap_Info.erase(nFd);

	this->m_pcDispatcher->SetChannel(_pChannel_Info);
	return this->m_pcDispatcher->Delete();
}

int CEventLoop::ProcessTask_Modify(CChannel* _pChannel_Info)
{
	int nFd = _pChannel_Info->GetFd();

	this->m_pcDispatcher->SetChannel(_pChannel_Info);
	return this->m_pcDispatcher->Modify();
}

int CEventLoop::DestroyChannelInfo(CChannel* _pChannel_Info)
{
	//���ٹ��� PCHANNEL_INFO ����Դ 
	this->pChMap_Info.erase(_pChannel_Info->GetFd());

	close(_pChannel_Info->GetFd());
	delete _pChannel_Info;

	return 0;
}

CEventLoop::CEventLoop() : CEventLoop(std::string())		//ί�й��캯��
{
}

CEventLoop::CEventLoop(string _ThreadName)
{
	this->IsQuit = false;
	this->pChMap_Info.clear();
	this->m_pcDispatcher = new CEpollDispatcher(this);
	this->m_thThreadId = std::this_thread::get_id();

	this->m_strThreadNames = _ThreadName == std::string() ? "MainThread" : _ThreadName;

	socketpair(AF_UNIX, SOCK_STREAM, 0, this->m_nSocketPairs);
	
	auto obj = bind(&CEventLoop::ReadLocalMsg, this);
	CChannel* ptChannel = new CChannel(this->m_nSocketPairs[1], ENUM_FDEVENT::READEVENT, obj, nullptr, nullptr, this);
	this->AddTask(ptChannel, ELEMENTTYPE::ADD);
}

int CEventLoop::Run()
{
	if (this->m_thThreadId != this_thread::get_id())
	{
		return -1;
	}

	while (!this->IsQuit)
	{
		this->m_pcDispatcher->Dispatch(2000);		//��ʱʱ������Ϊ2000ms
		ProcessTask();
	}

	return 0;
}

int CEventLoop::AddTask(CChannel* _pChannel_Info, ELEMENTTYPE _Type)
{
	//����������ܵ�����̵߳ķ���
	this->m_ThreadMutex.lock();

	//�����½ڵ�
	PCHANNELELEMENT ptChEle = new CHANNELELEMENT;
	if (ptChEle == nullptr)
	{
		perror("malloc failed.");
		return -1;
	}
	ptChEle->Type = _Type;
	ptChEle->ChannelInfo = _pChannel_Info;

	this->m_queTaskQ.push(ptChEle);
	this->m_ThreadMutex.unlock();

	//����ϸ��
	/*
	* ϸ�ڣ�
	*   1.��������ڵ����ӣ������ǵ�ǰ�߳�Ҳ���������߳�
	*       1).�޸�fd���¼�����ǰ���̷߳��𣬵�ǰ���̴߳���
	*       2).����µ�fd���������ڵ�Ĳ��������̷߳���
	*   2.���������̴߳���������У���Ҫ�е�ǰ���̴߳���
	*/
	if (this->m_thThreadId == this_thread::get_id())
	{
		//��ǰ���̴߳���
		ProcessTask();
	}
	else
	{
		//���߳� -- �������̴߳�������������������
		//1.���߳��ڹ���  2.���̱߳������ˣ�select��poll��epoll
		WriteLocalMsg();
	}


	return 0;
}

int CEventLoop::Activate(int _Fd, ENUM_FDEVENT _Event)
{
	if (_Fd < 0)
	{
		return -1;
	}

	//ȡ��
	CChannel* ptChanenel_Info = this->pChMap_Info[_Fd];
	assert(ptChanenel_Info->GetFd() == _Fd);

	if ((int)_Event & (int)ENUM_FDEVENT::READEVENT && ptChanenel_Info->m_pReadCallBack != nullptr)
	{
		ptChanenel_Info->m_pReadCallBack(const_cast<void*>(ptChanenel_Info->GetArg()));
	}

	if ((int)_Event & (int)ENUM_FDEVENT::WRITEEVENT && ptChanenel_Info->m_pWriteCallBack != nullptr)
	{
		ptChanenel_Info->m_pWriteCallBack(const_cast<void*>(ptChanenel_Info->GetArg()));
	}

	return 0;
}
