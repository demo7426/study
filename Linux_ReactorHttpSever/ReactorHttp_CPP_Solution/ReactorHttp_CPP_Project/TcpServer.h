//文件描述：
//      实现一个监听模块，属于TcpServer模块
//作者：钱锐
//时间：2024/1/26
//修改记录：
//      2024/1/26     新建

#pragma once
#include "ThreadPool.h"

class CTcpServer
{
public:
	CTcpServer() = delete;

	/// <summary>
	/// 初始化
	/// </summary>
	/// <param name="_ListenPort">监听端口</param>
	/// <param name="_SubThreadNum">线程池子线程数量</param>
	CTcpServer(unsigned short _ListenPort, int _SubThreadNum);
	~CTcpServer();

	/// <summary>
	/// 启动TcpServer
	/// </summary>
	/// <param name="pTcpServer_Info"></param>
	/// <returns></returns>
	int Run();

private:
	/// <summary>
	/// 初始化
	/// </summary>
	/// <param name="_ListenPort">监听端口</param>
	/// <returns></returns>
	int LinsterInit();

	static int AcceptReadCallBack(void* _Arg);
private:
	int m_nSubThreadNum;							//线程池内部子线程的数量
	int m_nListenFd;
	unsigned short m_usListenPort;
	CEventLoop* m_pcMainEventLoop;					//主线程事件循环模块
	CThreadPool* m_pcThreadPool;					//线程池模块信息
};


