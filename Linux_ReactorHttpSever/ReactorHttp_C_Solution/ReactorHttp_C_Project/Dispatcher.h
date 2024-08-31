//���ȳ���ģ�� ���а���select��pool��epoll����ģ��
#pragma once
#include "Channel.h"
#include "EventLoop.h"

struct EVENTLOOP_INFO;
typedef struct _DISPATCHR_INFO
{
	//��ʼ��
	void* (*Init)();
	//���
	int (*Add)(PCHANNEL_INFO _Channel_Info, struct EVENTLOOP_INFO* _EventLoop_Info);
	//ɾ��
	int (*Delete)(PCHANNEL_INFO _Channel_Info, struct EVENTLOOP_INFO* _EventLoop_Info);
	//�޸�
	int (*Modify)(PCHANNEL_INFO _Channel_Info, struct EVENTLOOP_INFO* _EventLoop_Info);
	//�¼���� _TimeOut����λΪ����
	int (*Dispatch)(struct EVENTLOOP_INFO* _EventLoop_Info, int _TimeOut);
	//�������(�ر�fd���ͷ��ڴ�)
	int (*Clear)(struct EVENTLOOP_INFO* _EventLoop_Info);
}DISPATCHR_INFO, *PDISPATCHR_INFO;

extern struct _DISPATCHR_INFO g_tEpollDis_Info;
extern struct _DISPATCHR_INFO g_tPollDis_Info;
extern struct _DISPATCHR_INFO g_tSelectDis_Info;