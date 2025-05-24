/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	ConnectionMgr.h
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

#pragma once

#include "boost/unordered_map.hpp"

#include "Connection.h"

class CConnectionMgr
{
public:
	static CConnectionMgr& GetInstance();

	void Add_Connection(std::shared_ptr<CConnection> _ConPtr);

	void Remove_Connection(std::string _Uuid);

private:
	CConnectionMgr() = default;
	CConnectionMgr(const CConnectionMgr&) = delete;
	CConnectionMgr& operator=(const CConnectionMgr&) = delete;

	boost::unordered_map<std::string, std::shared_ptr<CConnection>> m_mapCons;
};


