/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	MsgNode.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.05.04
��  ��: ��Ϣ�ڵ�
��  ע:
�޸ļ�¼:

  1.  ����: 2025.05.04
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.1.0

*************************************************/

#include "MsgNode.h"

CMsg_Node::CMsg_Node(char* _pMsg, int _MsgLen)
{
	if (_pMsg == nullptr || _MsgLen == 0)
		return;

	m_pchDataStartAddr = new char[_MsgLen + 1];

	memcpy(m_pchDataStartAddr, _pMsg, _MsgLen);
	m_pchDataStartAddr[_MsgLen] = '\0';

	m_nMaxLen = _MsgLen;
}

CMsg_Node::~CMsg_Node()
{
	if (m_pchDataStartAddr)
	{
		delete[] m_pchDataStartAddr;
		m_pchDataStartAddr = nullptr;
	}
}

CRecvMsg_Node::CRecvMsg_Node(unsigned short _TLV_Type, char* _pMsg, int _MsgLen) : CMsg_Node(_pMsg, _MsgLen)
{
	m_ushTLV_Type = _TLV_Type;
}
