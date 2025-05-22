/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Connection.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.05.22
��  ��: ����WebSocket����
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.05.22
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.1.0

*************************************************/

#pragma once

#include <queue>
#include <mutex>
#include <memory>

#include "boost/beast.hpp"
#include "boost/asio.hpp"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"

class CConnection : public std::enable_shared_from_this<CConnection>
{
public:
	CConnection(boost::asio::io_context& _IO_Context);
	
	std::string GetUuid();

	boost::asio::ip::tcp::socket& GetSocket();

	void AsyncAccept();

private:
	std::unique_ptr<boost::beast::websocket::stream<boost::beast::tcp_stream>> m_pWebSocket;
	std::string m_strUuid = "";

	boost::asio::io_context& m_cIO_Context;

	boost::beast::flat_buffer m_cRecvFlatBuf;		//���ջ���

	std::queue<std::string> m_queSend;				//���Ͷ���
	std::mutex m_mutSend;							//���Ͷ��л�����

	std::size_t m_unRecvCounter = 0;				//���յ����ݵĴ���

	void Start();

	void AsyncSend(std::string _Msg);
};
