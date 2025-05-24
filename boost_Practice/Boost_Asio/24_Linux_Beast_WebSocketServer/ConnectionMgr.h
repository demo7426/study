/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	ConnectionMgr.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.05.22
��  ��: ����Connection����ֹֻ��ָ���䱻�ͷ�
��  ע:
�޸ļ�¼:

  1.  ����: 2025.05.22
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.1.0

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


