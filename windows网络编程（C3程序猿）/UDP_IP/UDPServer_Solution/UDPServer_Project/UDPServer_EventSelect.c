#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>
#include<WinSock2.h>
#include"UDPServer_EventSelect.h"

#pragma comment(lib, "ws2_32.lib")

#define RTN_SUCCESS 1
#define RTN_FAILURE 0

static SOCKET g_socketServer = 0;
static SOCKADDR g_tSOCKADDR_Client;
static HANDLE g_handServer;

static DWORD WINAPI UDPRecvMsg(LPVOID lpThreadParameter)
{
	SOCKET socketServer = (SOCKET)lpThreadParameter;

	char chRecvBuf[513] = { 0 };
	int nSOCKADDR_ClientLength = sizeof(SOCKADDR);
	int nRecvLength = 0;
	int nSelectRtn = 0;
	fd_set fd;
	const struct timeval tTimeval = { 3 , 0 };

	puts("Start recv thread.");

	FD_ZERO(&fd);

	while (TRUE)
	{
		FD_SET(socketServer, &fd);//成功select后，fd中的数量会被置零，需要重新添加信息
		nSelectRtn = select(0, &fd, NULL, NULL, &tTimeval);

		if (nSelectRtn == 0)
		{
			puts("Start recv thread select timeout.");
			continue;
		}
		else if (nSelectRtn == SOCKET_ERROR)
			printf("未成功select的错误码：%d。\n", WSAGetLastError());
		else if (nSelectRtn > 0)
		{
			nRecvLength = recvfrom(socketServer, chRecvBuf, sizeof(chRecvBuf) - 1, 0, (struct sockaddr*)&g_tSOCKADDR_Client, &nSOCKADDR_ClientLength);
			if (nRecvLength == SOCKET_ERROR)
			{
				printf("未成功recvfrom的错误码：%d。\n", WSAGetLastError());
			}
			else if (nRecvLength > 0)
			{
				printf("%s\n", chRecvBuf);
			}

			memset(chRecvBuf, 0, sizeof(chRecvBuf));
		}
	}
	closesocket(socketServer);
	//关闭网络库
	WSACleanup();

	return RTN_SUCCESS;
}

static DWORD WINAPI UDPSendMsg(LPVOID lpThreadParameter)
{
	SOCKET socketServer = (SOCKET)lpThreadParameter;

	char chRecvBuf[512] = "客户端成功发送一条数据到服务器";
	int nRecvLength = 0;

	while (TRUE)
	{
		nRecvLength = sendto(socketServer, chRecvBuf, sizeof(chRecvBuf), 0, &g_tSOCKADDR_Client, sizeof(SOCKADDR));
		if (nRecvLength == SOCKET_ERROR)
		{
			printf("未成功send的错误码：%d。\n", WSAGetLastError());
		}

		memset(chRecvBuf, 0, sizeof(chRecvBuf));
	}

	//关闭网络库
	//WSACleanup();

	return RTN_SUCCESS;
}

static BOOL WINAPI ConsoleCtl_CallFunc(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		WSACloseEvent(g_handServer);
		closesocket(g_socketServer);
		//关闭网络库
		WSACleanup();
	default:
		break;
	}

}

static int Test01(void)
{
	int nRtn = -1;                  //返回值
	WORD word = MAKEWORD(2, 2);     //MAKEWORD(2, 1);
	WSADATA tWSAData;               //函数传出参数

	HANDLE pThreadId[2] = { 0 };

	nRtn = WSAStartup(word, &tWSAData);
	if (nRtn != 0)
	{
		printf("未成功WSAStartup的错误码：%d。\n", WSAGetLastError());
		return RTN_FAILURE;
	}

	//如果是使用的2.1版本,高位存储副版本; if (HIBYTE(tWSAData.wVersion) != 1 || LOBYTE(tWSAData.wVersion) != 2)
	if (HIBYTE(tWSAData.wVersion) != 2 || LOBYTE(tWSAData.wVersion) != 2)//判定打开版本是否错误
	{
		//版本不对，清理网络库
		printf("未成功校验WinSock2版本的错误码：%d。\n", WSAGetLastError());
		WSACleanup();
		return RTN_FAILURE;
	}

	g_socketServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (g_socketServer == INVALID_SOCKET)
	{
		printf("未成功创建服务器socket的错误码：%d。\n", WSAGetLastError());
		//关闭网络库
		WSACleanup();
		return RTN_FAILURE;
	}

	SOCKADDR_IN tSOCKADDR_IN;
	tSOCKADDR_IN.sin_family = AF_INET;
	tSOCKADDR_IN.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	tSOCKADDR_IN.sin_port = htons(13000);

	if (bind(g_socketServer, (struct sockaddr*)&tSOCKADDR_IN, sizeof(tSOCKADDR_IN)) == SOCKET_ERROR)
	{
		printf("未成功bind的错误码：%d。\n", WSAGetLastError());
		closesocket(g_socketServer);
		//关闭网络库
		WSACleanup();
		return RTN_FAILURE;
	}

	g_handServer = WSACreateEvent();
	if (WSA_INVALID_EVENT == g_handServer)
	{
		printf("未成功WSACreateEvent的错误码：%d。\n", WSAGetLastError());
		closesocket(g_socketServer);
		//关闭网络库
		WSACleanup();
		return RTN_FAILURE;
	}

	if (WSAEventSelect(g_socketServer, g_handServer, FD_READ | FD_READ) == SOCKET_ERROR)
	{
		printf("未成功WSAEventSelect的错误码：%d。\n", WSAGetLastError());
		WSACloseEvent(g_handServer);
		closesocket(g_socketServer);
		//关闭网络库
		WSACleanup();
		return RTN_FAILURE;
	}

	pThreadId[0] = CreateThread(NULL, 0, UDPRecvMsg, g_socketServer, 0, NULL);
	//pThreadId[1] = CreateThread(NULL, 0, UDPSendMsg, socketServer, 0, NULL);

	if (pThreadId[0] == NULL && pThreadId[1] == NULL)
	{
		puts("服务端创建线程创建失败。");
		WSACloseEvent(g_handServer);
		closesocket(g_socketServer);
		//关闭网络库
		WSACleanup();
		return RTN_FAILURE;
	}

	return RTN_SUCCESS;
}

int UDPServer_EventSelectFunc()
{
	SetConsoleCtrlHandler(ConsoleCtl_CallFunc, TRUE);
	Test01();

	while (TRUE);
	return RTN_SUCCESS;
}
