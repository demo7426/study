//�ļ�������
//      ʵ��һ��EpollDispatcherģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/18
//�޸ļ�¼��
//      2024/2/18     �½�

#pragma once
#include <sys/epoll.h>
#include "Dispatcher.h"

class CEpollDispatcher: public CDispatcher
{
public:
	CEpollDispatcher() = delete;
	CEpollDispatcher(const CEpollDispatcher&) = delete;
	CEpollDispatcher(CEventLoop* _EventLoop_Info);
	~CEpollDispatcher();

	//���
	int Add() override;
	//ɾ��
	int Delete() override;
	//�޸�
	int Modify() override;
	//�¼���� _TimeOut����λΪ����
	int Dispatch(int _TimeOut = 2000) override;

private:
	const int m_nMaxNum = 512;				//epoll���ʱ����󷵻�ʱ������
	int m_nEpFd;							//Epoll���ڵ�
	struct epoll_event* m_pcEvents;			//epoll���ʱ����������

private:
	int EpollCtl(int _Op);
};

