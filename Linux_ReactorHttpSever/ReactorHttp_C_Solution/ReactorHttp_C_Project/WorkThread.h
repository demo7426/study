//�ļ�������
//      ʵ��һ���������߳�ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/24
//�޸ļ�¼��
//      2024/1/24     �½�
#pragma once 
#include "EventLoop.h"

typedef struct _WORKTHREAD_INFO
{
	PEVENTLOOP_INFO pEventLoop_Info;

	pthread_t ThreadId;					//�߳�id
	char ThreadName[32];				//�߳�����
	pthread_mutex_t Mutex;				
	pthread_cond_t Cond;
}WORKTHREAD_INFO, *PWORKTHREAD_INFO;


//��ʼ��
int WorkThreadInit(PWORKTHREAD_INFO pWorkThread_Info, int _Index);

//����
void WorkThreadRun(PWORKTHREAD_INFO pWorkThread_Info);