/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	ConnectionMgr.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.05.22
描  述: 管理Connection，防止只能指针其被释放
备  注:
修改记录:

  1.  日期: 2025.05.22
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#include "ConnectionMgr.h"

CConnectionMgr& CConnectionMgr::GetInstance()
{
	static CConnectionMgr cConnectionMgr;
	return cConnectionMgr;
}

void CConnectionMgr::Add_Connection(std::shared_ptr<CConnection> _ConPtr)
{
	m_mapCons[_ConPtr->GetUuid()] = _ConPtr;
}

void CConnectionMgr::Remove_Connection(std::string _Uuid)
{
	m_mapCons.erase(_Uuid);
}
