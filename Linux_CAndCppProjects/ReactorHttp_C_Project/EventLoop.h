//�ļ�������
//      ʵ��һ��EventLoopģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/16
//�޸ļ�¼��
//      2024/1/16     �½��������ӿ�
//      2024/1/22     ʵ�ֽӿ�

#pragma once
#include <stdbool.h>
#include <pthread.h>

#include "ChanneMap.h"
#include "Dispatcher.h"

enum ELEMENTTYPE
{
	ADD, DELETE, MODIFY
};

typedef struct _CHANNELELEMENT
{
	enum ELEMENTTYPE Type;									//��δ���ǰ�ڵ��е�channel
	PCHANNEL_INFO ChannelInfo;
	struct _CHANNELELEMENT* pNext;
}CHANNELELEMENT, *PCHANNELELEMENT;

struct _DISPATCHR_INFO;
typedef struct _EVENTLOOP_INFO
{
	bool IsQuit;								//��ǰEventLoop�Ƿ��˳�;true--�˳�;false--δ�˳�

	struct _DISPATCHR_INFO* pDispatcher_Info;
	void* pDispatcherData;

	//�������
	PCHANNELELEMENT pTaskQHead;
	PCHANNELELEMENT pTaskQTail;

	// ChannelMap
	PCHANNELMAP_INFO pChMap_Info;

	//�߳����
	pthread_t ThreadId;							//�߳�id
	char ThreadNames[33];						//�߳�����
	pthread_mutex_t ThreadMutex;				//�̻߳�����

	int SocketPair[2];								//�洢����ͨ�ŵ�fd�����ڻ��ѱ�������ͨ��ģ�ͣ�ͨ��socketpair������ʼ��
}EVENTLOOP_INFO, *PEVENTLOOP_INFO;

//��ʼ��
PEVENTLOOP_INFO EventLoopInit();

//��ʼ����ָ���߳�����
PEVENTLOOP_INFO EventLoopInitEx(const char* _ThreadName);

//������Ӧ��ģ��
int EventLoopRun(PEVENTLOOP_INFO _pEventLoop_Info);

//����������ڲ����������
int EventLoopAddTask(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info, enum ELEMENTTYPE _Type);

//����struct _CHANNEL_INFO* �ڴ�
int EventLoopDestroyChannelInfo(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info);

/////////////////////////////////////////�ڲ��ӿ�/////////////////////////////////////////

//����������ļ�fd
int EventActivate(PEVENTLOOP_INFO _pEventLoop_Info, int _Fd, enum ENUM_FDEVENT _Event);

//������������ڲ�������
int EventLoopProcessTask(PEVENTLOOP_INFO _pEventLoop_Info);

//������������ڲ��������������
int EventLoopProcessTask_Add(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info);

//������������ڲ�������ɾ������
int EventLoopProcessTask_Delete(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info);

//������������ڲ��������޸�����
int EventLoopProcessTask_Modify(PEVENTLOOP_INFO _pEventLoop_Info, struct _CHANNEL_INFO* _pChannel_Info);


/////////////////////////////////////////�ڲ��ӿ�/////////////////////////////////////////