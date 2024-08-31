//�ļ�������
//      ʵ��һ��EventLoopģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/18
//�޸ļ�¼��
//      2024/2/18     �½�

#pragma once
#include <stdbool.h>
#include <thread>
#include <mutex>
#include <queue>
#include <map>

#include "Dispatcher.h"

enum class ELEMENTTYPE:char
{
	ADD, DELETE, MODIFY
};

typedef struct _CHANNELELEMENT
{
	enum ELEMENTTYPE Type;									//��δ���ǰ�ڵ��е�channel
	CChannel* ChannelInfo;
}CHANNELELEMENT, *PCHANNELELEMENT;

class CDispatcher;
class CEventLoop
{
public:
	CEventLoop();
	CEventLoop(std::string _ThreadName);

	//������Ӧ��ģ��
	int Run();

	//����������ڲ����������
	int AddTask(CChannel* _pChannel_Info, ELEMENTTYPE _Type);

	//����������ļ�fd
	int Activate(int _Fd, ENUM_FDEVENT _Event);  

	inline std::thread::id GetThreadId() const
	{
		return m_thThreadId;
	}

	//����CChannel* �ڴ�
	int DestroyChannelInfo(CChannel* _pChannel_Info);

private:
	bool IsQuit;								//��ǰEventLoop�Ƿ��˳�;true--�˳�;false--δ�˳�

	CDispatcher* m_pcDispatcher;

	//�������
	std::queue<PCHANNELELEMENT> m_queTaskQ;

	// ChannelMap
	std::map<int, CChannel*> pChMap_Info;

	//�߳����
	std::thread::id m_thThreadId;							//�߳�id
	std::string m_strThreadNames;							//�߳�����
	std::mutex m_ThreadMutex;								//�̻߳�����

	int m_nSocketPairs[2];									//�洢����ͨ�ŵ�fd�����ڻ��ѱ�������ͨ��ģ�ͣ�ͨ��socketpair������ʼ��

private:
	int WriteLocalMsg();

	int ReadLocalMsg();

	//������������ڲ�������
	int ProcessTask();

	//������������ڲ��������������
	int ProcessTask_Add(CChannel* _pChannel_Info);

	//������������ڲ�������ɾ������
	int ProcessTask_Delete(CChannel* _pChannel_Info);

	//������������ڲ��������޸�����
	int ProcessTask_Modify(CChannel* _pChannel_Info);


};

