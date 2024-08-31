#ifndef _THREADPOOL_H
#define _THREADPOOL_H

//�̳߳ؽṹ��
typedef struct _THREADPOOL_INFO THREADPOOL_INFO;

/// <summary>
/// �����̳߳ز���ʼ��
/// </summary>
/// <param name="_MinNum">��С�߳���</param>
/// <param name="_MaxNum">����߳���</param>
/// <param name="_Capacity">��������</param>
/// <returns>NULL--ʧ��;!NULL--�ɹ�</returns>
THREADPOOL_INFO* ThreadPool_Create(int _MinNum, int _MaxNum, int _Capacity);

/// <summary>
/// ����������������
/// </summary>
/// <param name="_pInfo"></param>
/// <param name="Func"></param>
/// <param name="_Arg"></param>
void ThreadPoolAdd(THREADPOOL_INFO* _pInfo, void(*Func)(void*), void* _Arg);

/// <summary>
/// ��ȡ�̳߳�����æ���̸߳���
/// </summary>
/// <param name="_pInfo"></param>
/// <returns></returns>
int GetThreadPool_BusyThreadNum(THREADPOOL_INFO* _pInfo);

/// <summary>
/// ��ȡ�̳߳��л��ŵ��̸߳���
/// </summary>
/// <param name="_pInfo"></param>
/// <returns></returns>
int GetThreadPool_AliveThreadNum(THREADPOOL_INFO* _pInfo);

/// <summary>
/// �����̳߳�
/// </summary>
/// <param name="_pInfo"></param>
/// <returns>-1--�����������0--����ִ��ʧ�ܣ�1--����ִ�гɹ�</returns>
int ThreadPool_Destroy(THREADPOOL_INFO* _pInfo);


#endif _THREADPOOL_H// !_THREADPOOL_H
