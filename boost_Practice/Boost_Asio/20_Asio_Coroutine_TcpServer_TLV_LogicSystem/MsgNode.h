/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MsgNode.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.05.04
描  述: 消息节点
备  注:
修改记录:

  1.  日期: 2025.05.04
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

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
	int m_nCurLen = 0;						//当前长度
	int m_nMaxLen = 0;						//最大长度
	char* m_pchDataStartAddr = nullptr;		//数据的起始地址

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