//�ļ�������
//      ʵ��һ���������߳�ģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/1/24
//�޸ļ�¼��
//      2024/1/24     �½�
#include <stdio.h>

#include "WorkThread.h"

int WorkThreadInit(PWORKTHREAD_INFO pWorkThread_Info, int _SerialNum)
{
	pWorkThread_Info->ThreadId = 0;
	sprintf(pWorkThread_Info->ThreadName, "Subthread-%d", _SerialNum);
	pWorkThread_Info->pEventLoop_Info = NULL;

	pthread_mutex_init(&pWorkThread_Info->Mutex, NULL);
	pthread_cond_init(&pWorkThread_Info->Cond, NULL);
	return 0;
}

void* SubThreadRunning(void* _Arg)
{
	PWORKTHREAD_INFO ptWorkThread_Info = (PWORKTHREAD_INFO)_Arg;

	pthread_mutex_lock(&ptWorkThread_Info->Mutex);
	ptWorkThread_Info->pEventLoop_Info = EventLoopInitEx(ptWorkThread_Info->ThreadName);
	pthread_mutex_unlock(&ptWorkThread_Info->Mutex);
	pthread_cond_signal(&ptWorkThread_Info->Cond);
	
	EventLoopRun(ptWorkThread_Info->pEventLoop_Info);

	return NULL;
}

void WorkThreadRun(PWORKTHREAD_INFO pWorkThread_Info)
{
	pthread_create(&pWorkThread_Info->ThreadId, NULL, SubThreadRunning, pWorkThread_Info);

	//��֤���̳߳�ʼ��EventLoop�ɹ�����ֹ���������ָ�뵼�³������
	pthread_mutex_lock(&pWorkThread_Info->Mutex);
	while (pWorkThread_Info->pEventLoop_Info == NULL)
	{
		pthread_cond_wait(&pWorkThread_Info->Cond, &pWorkThread_Info->Mutex);
	}
	pthread_mutex_unlock(&pWorkThread_Info->Mutex);
}
