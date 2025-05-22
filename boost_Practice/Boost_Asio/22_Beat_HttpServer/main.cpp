/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.05.20
描  述: 使用beast库编写一个http服务器
备  注:
修改记录:

  1.  日期: 2025.05.20
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>

#include <chrono>
#include <iostream>

/// <summary>
/// 获取请求的总次数
/// </summary>
/// <returns></returns>
static std::size_t Request_Counter() 
{
	static std::size_t unCounter = 0;
	return ++unCounter;
}

/// <summary>
/// 获取当前的时间戳
/// </summary>
/// <param name=""></param>
/// <returns></returns>
static std::time_t Now(void)
{
	return std::time(0);
}

class CHttp_Connection : public std::enable_shared_from_this<CHttp_Connection>
{
public:
	CHttp_Connection(boost::asio::ip::tcp::socket _Socket) : m_cSocket(std::move(_Socket)){};
	~CHttp_Connection() {};

	/// <summary>
	/// 启动服务
	/// </summary>
	/// <param name=""></param>
	void Start(void)
	{
		Read_Request();
		Check_Deadline();
	}

	boost::asio::ip::tcp::socket m_cSocket;														//socket
private:
	boost::beast::flat_buffer m_Buffer{ 8192 };													//缓冲区
	boost::beast::http::request<boost::beast::http::dynamic_body> m_cRequest;					//http请求
	boost::beast::http::response<boost::beast::http::dynamic_body> m_cResponse;					//http响应

	boost::beast::net::steady_timer m_cDeadline{ m_cSocket.get_executor(), std::chrono::seconds(60) };
	
	void Read_Request()							//读取http请求
	{
		auto self = shared_from_this();
		boost::beast::http::async_read(m_cSocket, m_Buffer, m_cRequest,
			[self](boost::system::error_code ec, std::size_t _BytesTransferred) {
			if (!ec)
				self->Process_Http_Request();
			});
	}

	void Check_Deadline()						//检测对端是否超时
	{
		auto self = shared_from_this();
		m_cDeadline.async_wait([self](boost::system::error_code ec) {
			if (!ec)
				self->m_cSocket.close(ec);		//关闭连接
			});
	}
		
	/// <summary>
	/// 处理Http请求
	/// </summary>
	void Process_Http_Request()				
	{
		m_cResponse.version(m_cRequest.version());
		m_cResponse.keep_alive(false);

		switch (m_cRequest.method())
		{
		case boost::beast::http::verb::get:
			m_cResponse.result(boost::beast::http::status::ok);
			m_cResponse.set(boost::beast::http::field::server, "Beast");

			Create_Get_Response();
			break;
		case boost::beast::http::verb::post:			
			m_cResponse.result(boost::beast::http::status::ok);
			m_cResponse.set(boost::beast::http::field::server, "Beast");

			Create_Post_Response();
			break;
		default:
			m_cResponse.result(boost::beast::http::status::ok);
			m_cResponse.set(boost::beast::http::field::content_type, "text/plain");
			
			boost::beast::ostream(m_cResponse.body()) << "Invalid request-method '"
				<< std::string(m_cRequest.method_string()) << "'";
			break;
		}

		Write_Response();
	}

	/// <summary>
	/// 创建get的响应数据
	/// </summary>
	void Create_Get_Response()
	{
		if (m_cRequest.target() == "/count")
		{
			m_cResponse.set(boost::beast::http::field::content_type, "text/html");

			boost::beast::ostream(m_cResponse.body()) << "<html>\n"
				<< "<head><title>Request count</title></head>\n"
				<< "<body>\n"
				<< "<h1>Request count</h1>\n"
				<< "<p> There have been "
				<< ::Request_Counter()
				<< " requests so far.</p>\n"
				<< "</body>\n"
				<< "</html>\n";
		}
		else if (m_cRequest.target() == "/time")
		{
			m_cResponse.set(boost::beast::http::field::content_type, "text/html");

			boost::beast::ostream(m_cResponse.body()) << "<html>\n"
				<< "<head><title>Request count</title></head>\n"
				<< "<body>\n"
				<< "<h1>Request count</h1>\n"
				<< "<p> There have been "
				<< ::Now()
				<< " requests so far.</p>\n"
				<< "</body>\n"
				<< "</html>\n";
		}
		else
		{
			m_cResponse.result(boost::beast::http::status::not_found);
			m_cResponse.set(boost::beast::http::field::content_type, "text/plain");

			boost::beast::ostream(m_cResponse.body()) << "File not found\r\n";
		}
	}

	/// <summary>
	/// 创建post的响应数据
	/// </summary>
	void Create_Post_Response()
	{
		if (m_cRequest.target() == "/email")
		{
			auto& body = this->m_cRequest.body();
			auto strBody = boost::beast::buffers_to_string(body.data());

			this->m_cResponse.set(boost::beast::http::field::content_type, "text/json");
			boost::beast::ostream(m_cResponse.body()) << "{ \"name\": \"beast server\" }";
		}
		else
		{
			m_cResponse.result(boost::beast::http::status::not_found);
			m_cResponse.set(boost::beast::http::field::content_type, "text/plain");

			boost::beast::ostream(m_cResponse.body()) << "File not found\r\n";
		}
	}

	/// <summary>
	/// 发送Http的响应数据
	/// </summary>
	void Write_Response()
	{
		auto self = shared_from_this();
		m_cResponse.content_length(m_cResponse.body().size());

		boost::beast::http::async_write(m_cSocket, m_cResponse, [self](boost::system::error_code ec, std::size_t) {
			self->m_cSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
			self->m_cDeadline.cancel();
			});
	}
};

void Http_Server(boost::asio::ip::tcp::acceptor& acceptor) 
{
	auto socket = std::make_shared<boost::asio::ip::tcp::socket>(acceptor.get_executor());

	acceptor.async_accept(*socket, [&, socket](boost::system::error_code ec) {
		if (!ec) {
			std::make_shared<CHttp_Connection>(std::move(*socket))->Start();
		}

		Http_Server(acceptor);
		});
}

int main()
{
	auto const cAddress = boost::beast::net::ip::make_address("127.0.0.1");
	unsigned short ushPortNo = 32888;
	boost::asio::io_context cIO_Context;

	boost::asio::ip::tcp::acceptor cAcceptor{ cIO_Context, { cAddress, ushPortNo } };

	Http_Server(cAcceptor);

	cIO_Context.run();

	return EXIT_SUCCESS;
}

