#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


#include<stdlib.h>
#include<stdio.h>
#include<WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define RTN_SUCCESS 1
#define RTN_FAILURE 0

SOCKADDR g_tSOCKADDR_Client;
SOCKET g_socketClient = 0;

DWORD WINAPI UDPRecvMsg(LPVOID lpThreadParameter)
{
	SOCKET socketClient = (SOCKET)lpThreadParameter;

	SOCKADDR_IN tSOCKADDR_IN;
	tSOCKADDR_IN.sin_family = AF_INET;
	tSOCKADDR_IN.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	tSOCKADDR_IN.sin_port = htons(13000);

	char chRecvBuf[513] = { 0 };
	int nSOCKADDR_ClientLength = sizeof(SOCKADDR_IN);
	int nRecvLength = 0;

	while (TRUE)
	{
		Sleep(1);
		nRecvLength = recvfrom(socketClient, chRecvBuf, sizeof(chRecvBuf) - 1, 0, (struct sockaddr*)&tSOCKADDR_IN, &nSOCKADDR_ClientLength);
		if (nRecvLength == SOCKET_ERROR)
		{
			printf("未成功recvfrom的错误码：%d。\n", WSAGetLastError());
		}
		else if (nRecvLength > 0)
		{
			printf("%s", chRecvBuf);
		}

		memset(chRecvBuf, 0, sizeof(chRecvBuf));
	}

	//关闭网络库
	WSACleanup();

	return RTN_SUCCESS;
}

DWORD WINAPI UDPSendMsg(LPVOID lpThreadParameter)
{
	SOCKET socketClient = (SOCKET)lpThreadParameter;

	SOCKADDR_IN tSOCKADDR_IN;
	tSOCKADDR_IN.sin_family = AF_INET;
	tSOCKADDR_IN.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	tSOCKADDR_IN.sin_port = htons(13000);


	char chRecvBuf[513] = { 0 };
	int nRecvLength = 0;

	while (TRUE)
	{
		scanf("%s", chRecvBuf);
		nRecvLength = sendto(socketClient, chRecvBuf, sizeof(chRecvBuf) - 1, 0, (struct sockaddr*)&tSOCKADDR_IN, sizeof(SOCKADDR_IN));
		if (nRecvLength == SOCKET_ERROR)
		{
			printf("未成功send的错误码：%d。\n", WSAGetLastError());
		}

		memset(chRecvBuf, 0, sizeof(chRecvBuf));
	}

	closesocket(socketClient);
	//关闭网络库
	WSACleanup();

	return RTN_SUCCESS;
}

BOOL WINAPI ConsoleCtl_CallFunc(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		closesocket(g_socketClient);
		//关闭网络库
		WSACleanup();
	default:
		break;
	}

}

int Test01(void)
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

	g_socketClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (g_socketClient == INVALID_SOCKET)
	{
		printf("未成功创建服务器socket的错误码：%d。\n", WSAGetLastError());
		//关闭网络库
		WSACleanup();
		return RTN_FAILURE;
	}

	//pThreadId[0] = CreateThread(NULL, 0, UDPRecvMsg, socketClient, 0, NULL);
	pThreadId[1] = CreateThread(NULL, 0, UDPSendMsg, g_socketClient, 0, NULL);

	if (pThreadId[0] == NULL && pThreadId[1] == NULL)
	{
		puts("服务端创建线程创建失败。");
		closesocket(g_socketClient);
		//关闭网络库
		WSACleanup();
		return RTN_FAILURE;
	}

	return RTN_SUCCESS;
}

int main(void)
{
	SetConsoleCtrlHandler(ConsoleCtl_CallFunc, TRUE);
	Test01();
	
	while (1)
	{
	}
	return 0;
}

