#pragma once
#include "Channel.h"

typedef struct _CHANNELMAP_INFO
{
	int Capacity;				//������С
	PCHANNEL_INFO* List;		//Mapָ���������ʼ��ַ
}CHANNELMAP_INFO, *PCHANNELMAP_INFO;

/// <summary>
/// ��������ʼ�� PCHANNELMAP_INFO ����
/// </summary>
/// <param name="_Capacity">����</param>
/// <returns>NULL--ʧ�ܣ�!NULL--�ɹ�</returns>
PCHANNELMAP_INFO ChannelMapInit(int _Capacity);

/// <summary>
/// ����ָ�� PCHANNELMAP_INFO ����
/// </summary>
/// <param name="_ChannelMap_Info"></param>
/// <returns>-1--ʧ�ܣ�0--�ɹ�</returns>
int ChannelMapDestroy(PCHANNELMAP_INFO _ChannelMap_Info);

/// <summary>
/// ��������
/// </summary>
/// <param name="_ChannelMap_Info"></param>
/// <param name="_NewCap">�����������С��������ڵ�ǰ������</param>
/// <returns>-1--ʧ�ܣ�0--�ɹ�</returns>
int ExpandChannelMapCapacity(PCHANNELMAP_INFO _ChannelMap_Info, int _NewCap);
