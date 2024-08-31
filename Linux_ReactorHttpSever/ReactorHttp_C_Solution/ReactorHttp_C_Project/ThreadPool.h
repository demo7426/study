//�ļ�������
//      ʵ��һ���̳߳�ģ�飨�̳߳���������1���̣߳���Ϊ�������һ�����̣߳�
//���ߣ�Ǯ��
//ʱ�䣺2024/1/24
//�޸ļ�¼��
//      2024/1/24     �½�
#pragma once
#include <stdbool.h>

#include "WorkThread.h"

typedef struct _THREADPOOL_INFO
{
	bool IsStart;								//�̳߳��Ƿ�����;true--������,false--δ����
	int SubThreadNum;							//�̳߳��ڲ����߳�����
	int SubThreadIndex;							//���߳�����

	PEVENTLOOP_INFO pMainEventLoop_Info;		//���߳��¼�ѭ��ģ��
	PWORKTHREAD_INFO pWorkThread_Info;			//���̹߳������߳���ʼ��ַ
}THREADPOOL_INFO, *PTHREADPOOL_INFO;

/// <summary>
/// �̳߳س�ʼ��
/// </summary>
/// <param name="_pMainLoop_Info">���߳��¼�ѭ��ģ��</param>
/// <param name="_SubThreadNum">�����������߳�����</param>
/// <returns></returns>
PTHREADPOOL_INFO ThreadPoolInit(PEVENTLOOP_INFO _pMainLoop_Info, int _SubThreadNum);

// �̳߳�����
void ThreadPoolRun(PTHREADPOOL_INFO _pThreadPool_Info);

//��ȡ��Ӧ��ʵ��ָ�룬���������¼�ѭ���ڲ�����������������
PEVENTLOOP_INFO GetEventLoopObj(PTHREADPOOL_INFO _pThreadPool_Info);
