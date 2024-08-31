//�ļ�������
//      ��ʵ��һ�����ȳ���ģ�� ���а���select��pool��epoll����ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/18
//�޸ļ�¼��
//      2024/2/18     �½�

#pragma once
#include <string>
#include "Channel.h"
#include "EventLoop.h"

class CEventLoop;
class CDispatcher
{
public:
	CDispatcher() = delete;
	CDispatcher(const CDispatcher&) = delete;
	CDispatcher(CEventLoop* _EventLoop_Info);
	virtual ~CDispatcher();

	//���
	virtual int Add() = 0;
	//ɾ��
	virtual int Delete() = 0;
	//�޸�
	virtual int Modify() = 0;
	//�¼���� _TimeOut����λΪ����
	virtual int Dispatch(int _TimeOut = 2000) = 0;

	inline void SetChannel(CChannel* _pChannnel)
	{
		m_pcChannel = _pChannnel;
	}

protected:
	CChannel* m_pcChannel;
	CEventLoop* m_pcEventLoop_Info;

	std::string m_strName = std::string();
};