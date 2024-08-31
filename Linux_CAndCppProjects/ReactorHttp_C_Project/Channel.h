//Channelģ��

#pragma once
#include <stdbool.h>

typedef int(*HandleFunc)(void*);

enum ENUM_FDEVENT
{
	TIMEOUT = 0x01,
	READEVENT = 0x02,
	WRITEEVENT = 0x04
};

typedef struct _CHANNEL_INFO
{
	int Fd;								//�ļ�������
	enum ENUM_FDEVENT Events;			//�¼�

	HandleFunc ReadCallBack;			//���ص�����
	HandleFunc WriteCallBack;			//д�ص�����
	HandleFunc DestroyCallBack;			//���ٻص�����

	void* Arg;							//�ص���������
}CHANNEL_INFO, *PCHANNEL_INFO;


//Channnel��ʼ������
PCHANNEL_INFO ChannelInit(int _Fd, enum ENUM_FDEVENT _Events, HandleFunc _ReadCallBack, HandleFunc _WriteCallBack, HandleFunc _DestroyCallBack, void* _Arg);

/// <summary>
/// ʹ��д�¼�
/// </summary>
/// <param name="_ChannelInfo"></param>
/// <param name="_Status">true--ʹ��; false--ȡ��ʹ��</param>
void EnableWriteEvent(PCHANNEL_INFO _ChannelInfo, bool _Status);

/// <summary>
/// ��⵱ǰ�ļ���������д״̬
/// </summary>
/// <param name="_ChannelInfo"></param>
/// <returns>true--��ʹ��; false--δʹ��</returns>
bool IsEnableWriteEvent(PCHANNEL_INFO _ChannelInfo);
