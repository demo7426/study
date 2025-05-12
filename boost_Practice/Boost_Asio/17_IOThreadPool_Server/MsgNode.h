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
	CMsg_Node(std::shared_ptr<CSession> _pSession, char* _pMsg, int _MsgLen);
	virtual ~CMsg_Node();

	inline std::shared_ptr<CSession> GetSession()
	{
		return m_pSession;
	}

	inline char* GetDataStartAddr()
	{
		return m_pchDataStartAddr;
	}

	inline int GetMaxLen()
	{
		return m_nMaxLen;
	}

protected:
	int m_nCurLen = 0;						//��ǰ����
	int m_nMaxLen = 0;						//��󳤶�
	char* m_pchDataStartAddr = nullptr;		//���ݵ���ʼ��ַ

	std::shared_ptr<CSession> m_pSession;
};

class CRecvMsg_Node : public CMsg_Node
{
	friend class CSession;

public:
	CRecvMsg_Node(std::shared_ptr<CSession> _pSession, unsigned short _TLV_Type, char* _pMsg, int _MsgLen);

	inline unsigned short GetTLV_Type()
	{
		return m_ushTLV_Type;
	}

private:
	unsigned short m_ushTLV_Type = 0;
};

class CSendMsg_Node : public CMsg_Node
{
	friend class CSession;

public:
	using CMsg_Node::CMsg_Node;
};