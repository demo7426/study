/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	MsgNode.h
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

#pragma once

#include <iostream>

class CSession;

class CMsg_Node
{
	friend class CSession;

public:
	CMsg_Node(char* _pMsg, int _MsgLen);
	virtual ~CMsg_Node();

protected:
	int m_nCurLen = 0;						//��ǰ����
	int m_nMaxLen = 0;						//��󳤶�
	char* m_pchDataStartAddr = nullptr;		//���ݵ���ʼ��ַ
};

class CRecvMsg_Node : public CMsg_Node
{
	friend class CSession;

public:
	CRecvMsg_Node(unsigned short _TLV_Type, char* _pMsg, int _MsgLen);

private:
	unsigned short m_ushTLV_Type = 0;
};

class CSendMsg_Node : public CMsg_Node
{
	friend class CSession;

public:
	using CMsg_Node::CMsg_Node;
};