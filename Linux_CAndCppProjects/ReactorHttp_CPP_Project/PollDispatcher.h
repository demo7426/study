//�ļ�������
//      ʵ��һ��PollDispatcherģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/18
//�޸ļ�¼��
//      2024/2/18     �½�

#pragma once
#include <poll.h>
#include "Dispatcher.h"

class CPollDispatcher : public CDispatcher
{
public:
	CPollDispatcher() = delete;
	CPollDispatcher(const CPollDispatcher&) = delete;
	CPollDispatcher(CEventLoop* _EventLoop_Info);
	~CPollDispatcher();

	//���
	int Add() override;
	//ɾ��
	int Delete() override;
	//�޸�
	int Modify() override;
	//�¼���� _TimeOut����λΪ����
	int Dispatch(int _TimeOut = 2000) override;

private:
	static const int m_nMaxNum = 512;					//poll���ʱ�����ͻ�����������
	int m_nMaxClientFdIndex;							//�����Ч�ͻ����ļ���������������λ��
	struct pollfd m_tPollfds[m_nMaxNum];
};
