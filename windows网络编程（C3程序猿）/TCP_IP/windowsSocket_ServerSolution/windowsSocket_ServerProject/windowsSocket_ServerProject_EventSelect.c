#include"windowsSocket_ServerProject_EventSelect.h"

/// <summary>
/// socket、事件ID信息结构体
/// </summary>
typedef struct _FD_EVENTSELECT_INFO
{
	unsigned short Count;
	SOCKET Sockets[WSA_MAXIMUM_WAIT_EVENTS];
	WSAEVENT EnventID[WSA_MAXIMUM_WAIT_EVENTS];
}FD_EVENTSELECT_INFO, * PFD_EVENTSELECT_INFO;

int Test_EventSelect()
{
	int nRtn = -1;                  //返回值
	WORD word = MAKEWORD(2, 2);     //MAKEWORD(2, 1);
	WSADATA tWSAData;               //函数传出参数
	SOCKET socketClient = 0;        //客户端socket
	SOCKET socketServer = 0;        //服务器socket

	nRtn = WSAStartup(word, &tWSAData);

	if (nRtn != 0)
	{
		puts("WSAStartup fail.\n");
		return -1;
	}

	//如果是使用的2.1版本,高位存储副版本; if (HIBYTE(tWSAData.wVersion) != 1 || LOBYTE(tWSAData.wVersion) != 2)
	if (HIBYTE(tWSAData.wVersion) != 2 || LOBYTE(tWSAData.wVersion) != 2)//判定打开版本是否错误
	{
		//版本不对，清理网络库
		WSACleanup();
		return -1;
	}

	socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == socketServer)
	{
		printf("未成功创建Socket的错误码：%d。\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	struct sockaddr_in si_Server;
	si_Server.sin_family = AF_INET;
	//inet_pton(AF_INET, "127.0.0.1", si_Server.sin_addr.S_un.S_addr);
	si_Server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//回环IP地址
	si_Server.sin_port = htons(12345);//命令行指令：netstat -aon|findstr "12345"指令查询端口号是否被使用;netstat -aon查看所有被使用的端口

	if (bind(socketServer, (const struct sockaddr*)&si_Server, sizeof(si_Server)) == SOCKET_ERROR)
	{
		printf("未成功bind的错误码：%d。\n", WSAGetLastError());
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}

	//SOMAXCONN 操作系统自动设置挂起连接的数量
	if (SOCKET_ERROR == listen(socketServer, SOMAXCONN))
	{
		printf("未成功listen的错误码：%d。\n", WSAGetLastError());
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}

	WSAEVENT hInstance_EnventID = WSACreateEvent();//创建事件句柄
	if (WSA_INVALID_EVENT == hInstance_EnventID)
	{
		printf("未成功WSACreateEvent的错误码：%d。\n", WSAGetLastError());
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}

	if (SOCKET_ERROR == WSAEventSelect(socketServer, hInstance_EnventID, FD_ACCEPT))//socket投递给内核
	{
		printf("未成功WSAEventSelect的错误码：%d。\n", WSAGetLastError());
		WSACloseEvent(hInstance_EnventID);
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}

	FD_EVENTSELECT_INFO tFD_EventSelect_Info = { 0, { 0 }, { 0 } };

	tFD_EventSelect_Info.Sockets[tFD_EventSelect_Info.Count] = socketServer;
	tFD_EventSelect_Info.EnventID[tFD_EventSelect_Info.Count] = hInstance_EnventID;
	tFD_EventSelect_Info.Count++;

	while (1)
	{
		DWORD ulRtn = WSAWaitForMultipleEvents(tFD_EventSelect_Info.Count, tFD_EventSelect_Info.EnventID, FALSE, WSA_INFINITE, FALSE);//查询可操作的socket
		if (ulRtn == WSA_WAIT_FAILED)//函数执行失败
		{
			printf("未成功WSAWaitForMultipleEvents的错误码：%d。\n", WSAGetLastError());
			WSACloseEvent(hInstance_EnventID);
			closesocket(socketServer);
			WSACleanup();
			return -1;
		}
		else if (ulRtn >= WSA_WAIT_EVENT_0 && ulRtn <= (WSA_WAIT_EVENT_0 + WSA_MAXIMUM_WAIT_EVENTS - 1))//监视到了有事件被触发
		{
			unsigned int unIndex = ulRtn - WSA_WAIT_EVENT_0;
			WSANETWORKEVENTS NetworkEvents;

			if (SOCKET_ERROR == WSAEnumNetworkEvents(tFD_EventSelect_Info.Sockets[unIndex],
				tFD_EventSelect_Info.EnventID[unIndex], &NetworkEvents))
			{
				printf("未成功WSAEnumNetworkEvents的错误码：%d。\n", WSAGetLastError());
				WSACloseEvent(hInstance_EnventID);
				closesocket(socketServer);
				WSACleanup();
				return -1;
			}
			else
			{
				//这里只能用if，不能用switch判定，因为如果有多个事件同时触发，会导致无法进行判定
				if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
				{
					if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] == 0)
					{
						struct sockaddr_in si_Client;
						int nLength = sizeof(si_Client);
						SOCKET socketClient = accept(tFD_EventSelect_Info.Sockets[unIndex], (struct sockaddr*)&si_Client, &nLength);
						if (INVALID_SOCKET == socketClient)
							continue;

						printf("一个客户端连接成功，地址为 = %ul, 端口号为 = %d\n", si_Client.sin_addr.S_un.S_addr, si_Client.sin_port);
						WSAEVENT wsaEventClient = WSACreateEvent();
						if (SOCKET_ERROR == WSAEventSelect(socketClient, wsaEventClient, FD_READ | FD_WRITE | FD_CLOSE))//socket投递给内核
						{
							printf("未成功WSAEventSelect的错误码：%d。\n", WSAGetLastError());
							WSACloseEvent(wsaEventClient);
							closesocket(socketClient);
							continue;
						}

						tFD_EventSelect_Info.Sockets[tFD_EventSelect_Info.Count] = socketClient;
						tFD_EventSelect_Info.EnventID[tFD_EventSelect_Info.Count] = wsaEventClient;
						tFD_EventSelect_Info.Count++;
					}
					else
						printf("FD_ACCEPT:iErrorCode = %d\n", NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
				}

				if (NetworkEvents.lNetworkEvents & FD_WRITE)
				{
					if (NetworkEvents.iErrorCode[FD_WRITE_BIT] == 0)
					{
						if (send(tFD_EventSelect_Info.Sockets[unIndex], "Connect success.", sizeof("Connect success."), 0) == SOCKET_ERROR)
						{
							printf("未成功send的错误码：%d。\n", WSAGetLastError());
						}
						printf("向端口号为：%llu发送了一条消息\n", tFD_EventSelect_Info.Sockets[unIndex]);
					}
					else
						printf("FD_WRITE:iErrorCode = %d\n", NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
				}

				if (NetworkEvents.lNetworkEvents & FD_READ)
				{
					if (NetworkEvents.iErrorCode[FD_READ_BIT] == 0)
					{
						char chBuf[1025] = { 0 };
						if (recv(tFD_EventSelect_Info.Sockets[unIndex], chBuf, sizeof(chBuf) - 1, 0) == SOCKET_ERROR)
						{
							//根据错误吗，进行相应的处理
							printf("未成功recv的错误码：%d。\n", WSAGetLastError());
						}
						else if(chBuf[0] != '\0')
							puts(chBuf);
							
						
					}
					else
						printf("FD_READ:iErrorCode = %d\n", NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
				}

				if (NetworkEvents.lNetworkEvents & FD_CLOSE)
				{
					WSACloseEvent(tFD_EventSelect_Info.EnventID[unIndex]);
					closesocket(tFD_EventSelect_Info.Sockets[unIndex]);

					tFD_EventSelect_Info.EnventID[unIndex] = tFD_EventSelect_Info.EnventID[tFD_EventSelect_Info.Count - 1];
					tFD_EventSelect_Info.Sockets[unIndex] = tFD_EventSelect_Info.Sockets[tFD_EventSelect_Info.Count - 1];
					tFD_EventSelect_Info.Count--;

					printf("一个端口为：%llu的客户端退出了。\n", tFD_EventSelect_Info.Sockets[unIndex]);
				}
			}
		}

	}

	WSACloseEvent(hInstance_EnventID);
	closesocket(socketServer);
	WSACleanup();
	return nRtn;
}

int Test_EventSelect_OptimizedCode()
{
	int nRtn = -1;                  //返回值
	WORD word = MAKEWORD(2, 2);     //MAKEWORD(2, 1);
	WSADATA tWSAData;               //函数传出参数
	SOCKET socketClient = 0;        //客户端socket
	SOCKET socketServer = 0;        //服务器socket

	nRtn = WSAStartup(word, &tWSAData);

	if (nRtn != 0)
	{
		puts("WSAStartup fail.\n");
		return -1;
	}

	//如果是使用的2.1版本,高位存储副版本; if (HIBYTE(tWSAData.wVersion) != 1 || LOBYTE(tWSAData.wVersion) != 2)
	if (HIBYTE(tWSAData.wVersion) != 2 || LOBYTE(tWSAData.wVersion) != 2)//判定打开版本是否错误
	{
		//版本不对，清理网络库
		WSACleanup();
		return -1;
	}

	socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == socketServer)
	{
		printf("未成功创建Socket的错误码：%d。\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	struct sockaddr_in si_Server;
	si_Server.sin_family = AF_INET;
	//inet_pton(AF_INET, "127.0.0.1", si_Server.sin_addr.S_un.S_addr);
	si_Server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//回环IP地址
	si_Server.sin_port = htons(12345);//命令行指令：netstat -aon|findstr "12345"指令查询端口号是否被使用;netstat -aon查看所有被使用的端口

	if (bind(socketServer, (const struct sockaddr*)&si_Server, sizeof(si_Server)) == SOCKET_ERROR)
	{
		printf("未成功bind的错误码：%d。\n", WSAGetLastError());
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}

	//SOMAXCONN 操作系统自动设置挂起连接的数量
	if (SOCKET_ERROR == listen(socketServer, SOMAXCONN))
	{
		printf("未成功listen的错误码：%d。\n", WSAGetLastError());
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}

	WSAEVENT hInstance_EnventID = WSACreateEvent();//创建事件句柄
	if (WSA_INVALID_EVENT == hInstance_EnventID)
	{
		printf("未成功WSACreateEvent的错误码：%d。\n", WSAGetLastError());
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}

	if (SOCKET_ERROR == WSAEventSelect(socketServer, hInstance_EnventID, FD_ACCEPT))//socket投递给内核
	{
		printf("未成功WSAEventSelect的错误码：%d。\n", WSAGetLastError());
		WSACloseEvent(hInstance_EnventID);
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}

	FD_EVENTSELECT_INFO tFD_EventSelect_Info = { 0, { 0 }, { 0 } };

	tFD_EventSelect_Info.Sockets[tFD_EventSelect_Info.Count] = socketServer;
	tFD_EventSelect_Info.EnventID[tFD_EventSelect_Info.Count] = hInstance_EnventID;
	tFD_EventSelect_Info.Count++;

	while (1)
	{
		DWORD ulStartIndex = WSAWaitForMultipleEvents(tFD_EventSelect_Info.Count, tFD_EventSelect_Info.EnventID, FALSE, WSA_INFINITE, FALSE);//查询可操作的socket
		if (ulStartIndex == WSA_WAIT_FAILED)//函数执行失败
		{
			printf("未成功WSAWaitForMultipleEvents的错误码：%d。\n", WSAGetLastError());
			WSACloseEvent(hInstance_EnventID);
			closesocket(socketServer);
			WSACleanup();
			return -1;
		}

		for (size_t i = ulStartIndex; i < tFD_EventSelect_Info.Count; i++)
		{
			DWORD ulRtn = WSAWaitForMultipleEvents(1, &(tFD_EventSelect_Info.EnventID[i]), FALSE, 0, FALSE) + i;//查询当前socket可执行状态
			if (ulRtn == WSA_WAIT_FAILED)//函数执行失败
			{
				printf("未成功WSAWaitForMultipleEvents的错误码：%d。\n", WSAGetLastError());
				WSACloseEvent(hInstance_EnventID);
				closesocket(socketServer);
				WSACleanup();
				return -1;
			}
			else if (ulRtn >= WSA_WAIT_EVENT_0 && ulRtn <= (WSA_WAIT_EVENT_0 + WSA_MAXIMUM_WAIT_EVENTS - 1))//监视到了有事件被触发
			{
				unsigned int unIndex = ulRtn - WSA_WAIT_EVENT_0;
				WSANETWORKEVENTS NetworkEvents;

				if (SOCKET_ERROR == WSAEnumNetworkEvents(tFD_EventSelect_Info.Sockets[unIndex],
					tFD_EventSelect_Info.EnventID[unIndex], &NetworkEvents))
				{
					printf("未成功WSAEnumNetworkEvents的错误码：%d。\n", WSAGetLastError());
					WSACloseEvent(hInstance_EnventID);
					closesocket(socketServer);
					WSACleanup();
					return -1;
				}
				else
				{
					//这里只能用if，不能用switch判定，因为如果有多个事件同时触发，会导致无法进行判定
					if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
					{
						if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] == 0)
						{
							struct sockaddr_in si_Client;
							int nLength = sizeof(si_Client);
							SOCKET socketClient = accept(tFD_EventSelect_Info.Sockets[unIndex], (struct sockaddr*)&si_Client, &nLength);
							if (INVALID_SOCKET == socketClient)
								continue;

							printf("一个客户端连接成功，地址为 = %ul, 端口号为 = %d\n", si_Client.sin_addr.S_un.S_addr, si_Client.sin_port);
							WSAEVENT wsaEventClient = WSACreateEvent();
							if (SOCKET_ERROR == WSAEventSelect(socketClient, wsaEventClient, FD_READ | FD_WRITE | FD_CLOSE))//socket投递给内核
							{
								printf("未成功WSAEventSelect的错误码：%d。\n", WSAGetLastError());
								WSACloseEvent(wsaEventClient);
								closesocket(socketClient);
								continue;
							}

							tFD_EventSelect_Info.Sockets[tFD_EventSelect_Info.Count] = socketClient;
							tFD_EventSelect_Info.EnventID[tFD_EventSelect_Info.Count] = wsaEventClient;
							tFD_EventSelect_Info.Count++;
						}
						else
							printf("FD_ACCEPT:iErrorCode = %d\n", NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
					}

					if (NetworkEvents.lNetworkEvents & FD_WRITE)
					{
						if (NetworkEvents.iErrorCode[FD_WRITE_BIT] == 0)
						{
							if (send(tFD_EventSelect_Info.Sockets[unIndex], "Connect success.", sizeof("Connect success."), 0) == SOCKET_ERROR)
							{
								printf("未成功send的错误码：%d。\n", WSAGetLastError());
							}
							printf("向端口号为：%llu发送了一条消息\n", tFD_EventSelect_Info.Sockets[unIndex]);
						}
						else
							printf("FD_WRITE:iErrorCode = %d\n", NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
					}

					if (NetworkEvents.lNetworkEvents & FD_READ)
					{
						if (NetworkEvents.iErrorCode[FD_READ_BIT] == 0)
						{
							char chBuf[1025] = { 0 };
							if (recv(tFD_EventSelect_Info.Sockets[unIndex], chBuf, sizeof(chBuf) - 1, 0) == SOCKET_ERROR)
							{
								//根据错误吗，进行相应的处理
								printf("未成功recv的错误码：%d。\n", WSAGetLastError());
							}
							else if (chBuf[0] != '\0')
								puts(chBuf);


						}
						else
							printf("FD_READ:iErrorCode = %d\n", NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
					}

					if (NetworkEvents.lNetworkEvents & FD_CLOSE)
					{
						WSACloseEvent(tFD_EventSelect_Info.EnventID[unIndex]);
						closesocket(tFD_EventSelect_Info.Sockets[unIndex]);

						tFD_EventSelect_Info.EnventID[unIndex] = tFD_EventSelect_Info.EnventID[tFD_EventSelect_Info.Count - 1];
						tFD_EventSelect_Info.Sockets[unIndex] = tFD_EventSelect_Info.Sockets[tFD_EventSelect_Info.Count - 1];
						tFD_EventSelect_Info.Count--;

						printf("一个端口为：%llu的客户端退出了。\n", tFD_EventSelect_Info.Sockets[unIndex]);
					}
				}
			}
			else if (ulRtn == WSA_WAIT_TIMEOUT)
			continue;

		}
	}

	WSACloseEvent(hInstance_EnventID);
	closesocket(socketServer);
	WSACleanup();
	return nRtn;
}
