//�ļ�������
//      ��ʵ��һ����ӦChannelģ��
//���ߣ�Ǯ��
//ʱ�䣺2024/2/18
//�޸ļ�¼��
//      2024/2/18     �½�
#pragma once
#include <functional>
//typedef int(*HandleFunc)(void*);
//using HandleFunc = int(*)(void*);

enum class ENUM_FDEVENT :char
{
	TIMEOUT = 0x01,
	READEVENT = 0x02,
	WRITEEVENT = 0x04
};

class CChannel
{
private:
	using HandleFunc = std::function<int(void*)>;
public:
	CChannel() = delete;
	CChannel(const CChannel&) = delete;
	CChannel(int _Fd, enum ENUM_FDEVENT _Events, HandleFunc _ReadCallBack, HandleFunc _WriteCallBack, HandleFunc _DestroyCallBack, void* _Arg);

	HandleFunc m_pReadCallBack;				//���ص�����
	HandleFunc m_pWriteCallBack;			//д�ص�����
	HandleFunc m_pDestroyCallBack;			//���ٻص�����

	/// <summary>
	/// ʹ��д�¼�
	/// </summary>
	/// <param name="_Status">true--ʹ��; false--ȡ��ʹ��</param>
	void EnableWriteEvent(bool _Status);

	/// <summary>
	/// ��⵱ǰ�ļ���������д״̬
	/// </summary>
	/// <returns>true--��ʹ��; false--δʹ��</returns>
	bool IsEnableWriteEvent();

	inline int GetFd()
	{
		return m_nFd;
	}

	inline enum ENUM_FDEVENT GetEvents()
	{
		return m_eEvents;
	}

	inline const void* GetArg()
	{
		return m_pvArg;
	}

private:
	int m_nFd;								//�ļ�������
	enum ENUM_FDEVENT m_eEvents;			//�¼�
	void* m_pvArg;							//�ص���������
};

