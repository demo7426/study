/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Session.h
��  ��:	Ǯ��      �汾: V0.1.1     �½�����: 2025.04.21
��  ��: ��������˻Ự�ӿ�
��  ע:
�޸ļ�¼:

  1.  ����: 2025.04.21
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.1.0

  1.  ����: 2025.04.23
	  ����: Ǯ��
	  ����:
		  1) �����첽��������CMsgNode+���Ͷ��У���֤�첽�������ݺ�����ǰ��һ���ԣ�
	  �汾:V0.1.1

*************************************************/

#pragma once

#include <boost/asio.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <memory>
#include <iostream>
#include <queue>
#include <mutex>

class CServer;

class CMsgNode
{
	friend class CSession;

public:
	CMsgNode(char* _pMsg, int _MsgLen)
	{
		if (_pMsg == nullptr || _MsgLen == 0)
			return;

		m_pchDataStartAddr = new char[_MsgLen];

		memcpy(m_pchDataStartAddr, _pMsg, _MsgLen);

		m_nMaxLen = _MsgLen;
	}

	~CMsgNode()
	{
		if (m_pchDataStartAddr)
		{
			delete[] m_pchDataStartAddr;
			m_pchDataStartAddr = nullptr;
		}
	}

private:
	int m_nCurLen = 0;						//��ǰ����
	int m_nMaxLen = 0;						//��󳤶�
	char* m_pchDataStartAddr = nullptr;		//���ݵ���ʼ��ַ
};

class CSession : public std::enable_shared_from_this<CSession>
{
public:
	CSession(boost::asio::io_context& _IO_Context, CServer* _pServer);
	
	~CSession()
	{
		std::cout << "~CSession" << std::endl;
	}

	void Start(void);

	inline boost::asio::ip::tcp::socket& R_Socket(void)
	{
		return m_cSocket;
	}

	inline std::string& Get_Uuid(void)
	{
		return m_strUuid;
	}

private:
	/// <summary>
	/// �����ݻص�
	/// </summary>
	/// <param name="_ErrCode"></param>
	/// <param name="_Byte_Transferred"></param>
	void Handle_Read_CallBack(const boost::system::error_code& _ErrCode, size_t _Byte_Transferred, std::shared_ptr<CSession> _pSelf_Session);

	/// <summary>
	/// д���ݻص�
	/// </summary>
	/// <param name="_ErrCode"></param>
	void Handle_Write_CallBack(const boost::system::error_code& _ErrCode, std::shared_ptr<CSession> _pSelf_Session);

	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="_pMsg"></param>
	/// <param name="_MsgLen"></param>
	void Send(char* _pMsg, int _MsgLen);

private:
	boost::asio::ip::tcp::socket m_cSocket;
	
	constexpr static unsigned char m_uchTLVLen_OccupyBytes = 2;			//TLV��ʽ��������ռ�õ����ֽ���
	constexpr static size_t m_unMaxRecvLen = 65537;						//�������ݻ�����󳤶�;����ΪTLV������ռ�õ����ֽ���Ϊ2��������󳤶�Ϊ65537��

	char m_chRecvBuf[m_unMaxRecvLen] = { 0 };							//�������ݻ���
	size_t m_uchRecvValidLen = 0;										//��ǰ�������ݵ���Ч����

	std::string m_strUuid;

	CServer* m_pcServer = nullptr;

	std::queue<std::shared_ptr<CMsgNode>> m_queSend;					//���ݷ��ͻ������
	std::queue<std::shared_ptr<CMsgNode>> m_queRecv;					//���ݽ��ջ������
	std::mutex m_SendLock;												//���ݷ��ͻ�����л�����
};

