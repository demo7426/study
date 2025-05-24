/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	ConnectionMgr.cpp
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
