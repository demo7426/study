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
	unsigned int CurCount;                  //��Чsocket����
	SOCKET sockets[MAX_SOCKET_NUM];         //����socket��ID
	OVERLAPPED tOverlapped[MAX_SOCKET_NUM];
}SOCKET_INFO, * PSOCKET_INFO;

SOCKET_INFO g_tSocket_Info;

//���ջ�����
char g_strRecv[MAX_RECV_COUNT];

int PostAccept();
int PostRecv(const unsigned int _Index);
int PostSend(const unsigned int _Index);

/// <summary>
/// ͨ�ŷ���˻���ģ��
/// </summary>
/// <returns></returns>
int Test01()
{
	int nRtn = -1;                  //����ֵ
	WORD word = MAKEWORD(2, 2);     //MAKEWORD(2, 1);
	WSADATA tWSAData;               //������������
	SOCKET socketClient = 0;        //�ͻ���socket
	SOCKET socketServer = 0;        //������socket

	nRtn = WSAStartup(word, &tWSAData);

	if (nRtn != 0)
	{
		puts("WSAStartup fail.\n");
		return -1;
	}

	//�����ʹ�õ�2.1�汾,��λ�洢���汾; if (HIBYTE(tWSAData.wVersion) != 1 || LOBYTE(tWSAData.wVersion) != 2)
	if (HIBYTE(tWSAData.wVersion) != 2 || LOBYTE(tWSAData.wVersion) != 2)//�ж��򿪰汾�Ƿ����
	{
		//�汾���ԣ����������
		WSACleanup();
		return -1;
	}

	socketServer = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	if (INVALID_SOCKET == socketServer)
	{
		printf("δ�ɹ�����Socket�Ĵ����룺%d��\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	struct sockaddr_in si_Server;
	si_Server.sin_family = AF_INET;
	//inet_pton(AF_INET, "127.0.0.1", si_Server.sin_addr.S_un.S_addr);
	si_Server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//�ػ�IP��ַ
	si_Server.sin_port = htons(12345);//������ָ�netstat -aon|findstr "12345"ָ���ѯ�˿ں��Ƿ�ʹ��;netstat -aon�鿴���б�ʹ�õĶ˿�

	if (bind(socketServer, (const struct sockaddr*)&si_Server, sizeof(si_Server)) == SOCKET_ERROR)
	{
		printf("δ�ɹ�bind�Ĵ����룺%d��\n", WSAGetLastError());
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}

	//SOMAXCONN ����ϵͳ�Զ����ù������ӵ�����
	if (SOCKET_ERROR == listen(socketServer, SOMAXCONN))
	{
		printf("δ�ɹ�listen�Ĵ����룺%d��\n", WSAGetLastError());
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}

	g_tSocket_Info.sockets[g_tSocket_Info.CurCount] = socketServer;
	g_tSocket_Info.tOverlapped[g_tSocket_Info.CurCount].hEvent = WSACreateEvent();
	if (g_tSocket_Info.tOverlapped[g_tSocket_Info.CurCount].hEvent == WSA_INVALID_EVENT)
	{
		printf("δ�ɹ�WSACreateEvent�Ĵ����룺%d��\n", WSAGetLastError());
		return 0;
	}

	g_tSocket_Info.CurCount++;

	PostAccept();

	while (1)
	{
		DWORD dwState = 0;
		DWORD dwFlag = 0;
		DWORD dwRtn = WSAWaitForMultipleEvents(1, &(g_tSocket_Info.tOverlapped[0].hEvent), FALSE, WSA_INFINITE, TRUE);

		//����ִ��ʧ�ܡ���ʱ���������ִ�н���
		if (dwRtn == WSA_WAIT_FAILED || dwRtn == WSA_WAIT_TIMEOUT || dwRtn == WSA_WAIT_IO_COMPLETION)
		{
			continue;
		}
		
		//�ź��ÿ�
		WSAResetEvent(g_tSocket_Info.tOverlapped[0].hEvent);

		PostSend(g_tSocket_Info.CurCount);
		PostRecv(g_tSocket_Info.CurCount);
		//���������socket
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
	DWORD ulRecvLength = 0;//���յ������ݳ���
	g_tSocket_Info.tOverlapped[g_tSocket_Info.CurCount].hEvent = WSACreateEvent();

	if (g_tSocket_Info.tOverlapped[g_tSocket_Info.CurCount].hEvent == WSA_INVALID_EVENT)
	{
		printf("δ�ɹ�WSACreateEvent�Ĵ����룺%d��\n", WSAGetLastError());
		return 0;
	}

	g_tSocket_Info.sockets[g_tSocket_Info.CurCount] = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	if (INVALID_SOCKET == g_tSocket_Info.sockets[g_tSocket_Info.CurCount])
	{
		printf("δ�ɹ�����Socket�Ĵ����룺%d��\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	if (AcceptEx(g_tSocket_Info.sockets[0], g_tSocket_Info.sockets[g_tSocket_Info.CurCount], chBuf, 0,
		sizeof(struct sockaddr_in) + 16, sizeof(struct sockaddr_in) + 16, &ulRecvLength, g_tSocket_Info.tOverlapped))
	{
		//�������
		PostRecv(g_tSocket_Info.CurCount);

		g_tSocket_Info.CurCount++;
		PostAccept();
	}
	else//�����ӳ���ɻ��������
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
	//��������λ��������д�����Ƽ���һ��
	int nIndex = lpOverlapped - &(g_tSocket_Info.tOverlapped[0]);//��һ��

	//nIndex = ((char*)lpOverlapped - (char*)&(g_tSocket_Info.tOverlapped[0])) / sizeof(OVERLAPPED);//�ڶ���
	//������
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
		puts("һ���ͻ���ǿ�ƶϿ�����\n");

		closesocket(g_tSocket_Info.sockets[nIndex]);
		WSACloseEvent(g_tSocket_Info.tOverlapped[nIndex].hEvent);

		g_tSocket_Info.sockets[nIndex] = g_tSocket_Info.sockets[g_tSocket_Info.CurCount - 1];
		g_tSocket_Info.tOverlapped[nIndex] = g_tSocket_Info.tOverlapped[g_tSocket_Info.CurCount - 1];
		g_tSocket_Info.CurCount--;
	}
	else if (cbTransferred == 0)
	{
		puts("һ���ͻ��������Ͽ�����\n");

		closesocket(g_tSocket_Info.sockets[nIndex]);
		WSACloseEvent(g_tSocket_Info.tOverlapped[nIndex].hEvent);

		g_tSocket_Info.sockets[nIndex] = g_tSocket_Info.sockets[g_tSocket_Info.CurCount - 1];
		g_tSocket_Info.tOverlapped[nIndex] = g_tSocket_Info.tOverlapped[g_tSocket_Info.CurCount - 1];
		g_tSocket_Info.CurCount--;
	}
	else
	{
		//����ͻ���socket,���ͻ���ճɹ�
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
	DWORD ulRecvLength = 0;//���յ������ݳ���
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
	else//�����ӳ���ɻ��������
	{
		int nWSALastError = WSAGetLastError();
		switch (nWSALastError)
		{
		case ERROR_IO_PENDING:
		{
			//�ӳ�

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
	puts("SendCallFunc����������");
}

int PostSend(const unsigned int _Index)
{
	DWORD ulSendLength = 0;//���յ������ݳ���
	WSABUF tWSABuf;
	DWORD dwFlag = 0;
	tWSABuf.buf = "�ɹ����ӷ�����";
	tWSABuf.len = sizeof(g_strRecv) - 1;

	if (WSASend(g_tSocket_Info.sockets[_Index], &tWSABuf, 1, &ulSendLength, dwFlag, &(g_tSocket_Info.tOverlapped[_Index]), SendCallFunc) == 0)
	{
	}
	else//�����ӳ���ɻ��������
	{
		int nWSALastError = WSAGetLastError();
		switch (nWSALastError)
		{
		case ERROR_IO_PENDING:
		{
			//�ӳ�

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