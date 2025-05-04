/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MsgNode.cpp
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
