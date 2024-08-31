#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
#include<string.h>
#include<Mswsock.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")

#define MAX_SOCKET_NUM 1024
#define MAX_RECV_COUNT  1025

typedef struct _SOCKET_INFO
{
	unsigned int CurCount;                  //有效socket数量
	SOCKET sockets[MAX_SOCKET_NUM];         //保存socket的ID
	OVERLAPPED tOverlapped[MAX_SOCKET_NUM];
}SOCKET_INFO, * PSOCKET_INFO;

SOCKET_INFO g_tSocket_Info;

//接收缓冲区
char g_strRecv[MAX_RECV_COUNT];

int PostAccept();
int PostRecv(const unsigned int _Index);
int PostSend(const unsigned int _Index);

/// <summary>
/// 通信服务端基础模型
/// </summary>
/// <returns></returns>
int Test01()
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

	socketServer = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

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

	g_tSocket_Info.sockets[g_tSocket_Info.CurCount] = socketServer;
	g_tSocket_Info.tOverlapped[g_tSocket_Info.CurCount].hEvent = WSACreateEvent();
	if (g_tSocket_Info.tOverlapped[g_tSocket_Info.CurCount].hEvent == WSA_INVALID_EVENT)
	{
		printf("未成功WSACreateEvent的错误码：%d。\n", WSAGetLastError());
		return 0;
	}

	g_tSocket_Info.CurCount++;

	PostAccept();

	while (1)
	{
		DWORD dwState = 0;
		DWORD dwFlag = 0;
		DWORD dwRtn = WSAWaitForMultipleEvents(1, &(g_tSocket_Info.tOverlapped[0].hEvent), FALSE, WSA_INFINITE, TRUE);

		//函数执行失败、超时或完成例程执行结束
		if (dwRtn == WSA_WAIT_FAILED || dwRtn == WSA_WAIT_TIMEOUT || dwRtn == WSA_WAIT_IO_COMPLETION)
		{
			continue;
		}
		
		//信号置空
		WSAResetEvent(g_tSocket_Info.tOverlapped[0].hEvent);

		PostSend(g_tSocket_Info.CurCount);
		PostRecv(g_tSocket_Info.CurCount);
		//处理服务器socket
		g_tSocket_Info.CurCount++;
		PostAccept();
	}

	for (size_t i = 0; i < g_tSocket_Info.CurCount; i++)
	{
		closesocket(g_tSocket_Info.sockets[i]);
		WSACloseEvent(g_tSocket_Info.tOverlapped[i].hEvent);
	}
	WSACleanup();
	return nRtn;
}

int PostAccept()
{
	char chBuf[1024] = { 0 };
	DWORD ulRecvLength = 0;//接收到的数据长度
	g_tSocket_Info.tOverlapped[g_tSocket_Info.CurCount].hEvent = WSACreateEvent();

	if (g_tSocket_Info.tOverlapped[g_tSocket_Info.CurCount].hEvent == WSA_INVALID_EVENT)
	{
		printf("未成功WSACreateEvent的错误码：%d。\n", WSAGetLastError());
		return 0;
	}

	g_tSocket_Info.sockets[g_tSocket_Info.CurCount] = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	if (INVALID_SOCKET == g_tSocket_Info.sockets[g_tSocket_Info.CurCount])
	{
		printf("未成功创建Socket的错误码：%d。\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	if (AcceptEx(g_tSocket_Info.sockets[0], g_tSocket_Info.sockets[g_tSocket_Info.CurCount], chBuf, 0,
		sizeof(struct sockaddr_in) + 16, sizeof(struct sockaddr_in) + 16, &ulRecvLength, g_tSocket_Info.tOverlapped))
	{
		//立即完成
		PostRecv(g_tSocket_Info.CurCount);

		g_tSocket_Info.CurCount++;
		PostAccept();
	}
	else//处理延迟完成或出错的情况
	{
		int nWSALastError = WSAGetLastError();
		switch (nWSALastError)
		{
		case ERROR_IO_PENDING:
		{
		}
		break;
		default:
			//closesocket(g_tSocket_Info.sockets[g_tSocket_Info.CurCount]);
			break;
		}
	}

	return 1;
}

void CALLBACK RecvCallFunc(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	//计算索引位置有三种写法，推荐第一种
	int nIndex = lpOverlapped - &(g_tSocket_Info.tOverlapped[0]);//第一种

	//nIndex = ((char*)lpOverlapped - (char*)&(g_tSocket_Info.tOverlapped[0])) / sizeof(OVERLAPPED);//第二种
	//第三种
	/*for (size_t i = 0; i < g_tSocket_Info.CurCount; i++)
	{
		if (g_tSocket_Info.tOverlapped[i].hEvent == lpOverlapped->hEvent)
		{
			nIndex = i;
			break;
		}
	}*/

	if (dwError == WSAECONNRESET)
	{
		puts("一个客户端强制断开连接\n");

		closesocket(g_tSocket_Info.sockets[nIndex]);
		WSACloseEvent(g_tSocket_Info.tOverlapped[nIndex].hEvent);

		g_tSocket_Info.sockets[nIndex] = g_tSocket_Info.sockets[g_tSocket_Info.CurCount - 1];
		g_tSocket_Info.tOverlapped[nIndex] = g_tSocket_Info.tOverlapped[g_tSocket_Info.CurCount - 1];
		g_tSocket_Info.CurCount--;
	}
	else if (cbTransferred == 0)
	{
		puts("一个客户端正常断开连接\n");

		closesocket(g_tSocket_Info.sockets[nIndex]);
		WSACloseEvent(g_tSocket_Info.tOverlapped[nIndex].hEvent);

		g_tSocket_Info.sockets[nIndex] = g_tSocket_Info.sockets[g_tSocket_Info.CurCount - 1];
		g_tSocket_Info.tOverlapped[nIndex] = g_tSocket_Info.tOverlapped[g_tSocket_Info.CurCount - 1];
		g_tSocket_Info.CurCount--;
	}
	else
	{
		//处理客户端socket,发送或接收成功
		if (g_strRecv[0] != '\0')
		{
			puts(g_strRecv);
			memset(g_strRecv, 0, sizeof(g_strRecv));

			PostRecv(nIndex);
		}
	}
}

int PostRecv(const unsigned int _Index)
{
	DWORD ulRecvLength = 0;//接收到的数据长度
	WSABUF tWSABuf;
	DWORD dwFlag = 0;
	tWSABuf.buf = g_strRecv;
	tWSABuf.len = sizeof(g_strRecv) - 1;

	if (WSARecv(g_tSocket_Info.sockets[_Index], &tWSABuf, 1, &ulRecvLength, &dwFlag, &(g_tSocket_Info.tOverlapped[_Index]), RecvCallFunc) == 0)
	{
		if (tWSABuf.buf[0] != '\0')
			printf("%s\n", tWSABuf.buf);

		PostRecv(_Index);
	}
	else//处理延迟完成或出错的情况
	{
		int nWSALastError = WSAGetLastError();
		switch (nWSALastError)
		{
		case ERROR_IO_PENDING:
		{
			//延迟

		}
		break;
		default:
			break;
		}
	}

	return 1;
}

void CALLBACK SendCallFunc(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	puts("SendCallFunc函数被调用");
}

int PostSend(const unsigned int _Index)
{
	DWORD ulSendLength = 0;//接收到的数据长度
	WSABUF tWSABuf;
	DWORD dwFlag = 0;
	tWSABuf.buf = "成功连接服务器";
	tWSABuf.len = sizeof(g_strRecv) - 1;

	if (WSASend(g_tSocket_Info.sockets[_Index], &tWSABuf, 1, &ulSendLength, dwFlag, &(g_tSocket_Info.tOverlapped[_Index]), SendCallFunc) == 0)
	{
	}
	else//处理延迟完成或出错的情况
	{
		int nWSALastError = WSAGetLastError();
		switch (nWSALastError)
		{
		case ERROR_IO_PENDING:
		{
			//延迟

		}
		break;
		default:
			break;
		}
	}

	return 1;
}

BOOL WINAPI SetConsoleCallFunc(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		for (size_t i = 0; i < g_tSocket_Info.CurCount; i++)
		{
			closesocket(g_tSocket_Info.sockets[i]);
			WSACloseEvent(g_tSocket_Info.tOverlapped[i].hEvent);
		}
		WSACleanup();
	default:
		break;
	}
}
int main()
{
	SetConsoleCtrlHandler(SetConsoleCallFunc, TRUE);

	Test01();
	system("pause");
	return 0;
}