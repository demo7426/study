//�ļ�������
//      ʵ��һ��SelectDispatcherģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/19
//�޸ļ�¼��
//      2024/2/19     �½�

#pragma once
#include <sys/select.h>
#include "Dispatcher.h"

class CSelectDispatcher : public CDispatcher
{
public:
	CSelectDispatcher() = delete;
	CSelectDispatcher(const CSelectDispatcher&) = delete;
	CSelectDispatcher(CEventLoop* _EventLoop_Info);
	~CSelectDispatcher();
	
	//���
	int Add() override;
	//ɾ��
	int Delete() override;
	//�޸�
	int Modify() override;
	//�¼���� _TimeOut����λΪ����
	int Dispatch(int _TimeOut = 2000) override;

private:
	int m_nMaxClientFd;			//�����Ч�ͻ����ļ�������
	fd_set m_tReadFdSet;
	fd_set m_tWriteFdSet;
};
