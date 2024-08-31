#include"windowsSocket_ServerProject_EventSelect.h"

/// <summary>
/// socket���¼�ID��Ϣ�ṹ��
/// </summary>
typedef struct _FD_EVENTSELECT_INFO
{
	unsigned short Count;
	SOCKET Sockets[WSA_MAXIMUM_WAIT_EVENTS];
	WSAEVENT EnventID[WSA_MAXIMUM_WAIT_EVENTS];
}FD_EVENTSELECT_INFO, * PFD_EVENTSELECT_INFO;

int Test_EventSelect()
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

	socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

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

	WSAEVENT hInstance_EnventID = WSACreateEvent();//�����¼����
	if (WSA_INVALID_EVENT == hInstance_EnventID)
	{
		printf("δ�ɹ�WSACreateEvent�Ĵ����룺%d��\n", WSAGetLastError());
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}

	if (SOCKET_ERROR == WSAEventSelect(socketServer, hInstance_EnventID, FD_ACCEPT))//socketͶ�ݸ��ں�
	{
		printf("δ�ɹ�WSAEventSelect�Ĵ����룺%d��\n", WSAGetLastError());
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
		DWORD ulRtn = WSAWaitForMultipleEvents(tFD_EventSelect_Info.Count, tFD_EventSelect_Info.EnventID, FALSE, WSA_INFINITE, FALSE);//��ѯ�ɲ�����socket
		if (ulRtn == WSA_WAIT_FAILED)//����ִ��ʧ��
		{
			printf("δ�ɹ�WSAWaitForMultipleEvents�Ĵ����룺%d��\n", WSAGetLastError());
			WSACloseEvent(hInstance_EnventID);
			closesocket(socketServer);
			WSACleanup();
			return -1;
		}
		else if (ulRtn >= WSA_WAIT_EVENT_0 && ulRtn <= (WSA_WAIT_EVENT_0 + WSA_MAXIMUM_WAIT_EVENTS - 1))//���ӵ������¼�������
		{
			unsigned int unIndex = ulRtn - WSA_WAIT_EVENT_0;
			WSANETWORKEVENTS NetworkEvents;

			if (SOCKET_ERROR == WSAEnumNetworkEvents(tFD_EventSelect_Info.Sockets[unIndex],
				tFD_EventSelect_Info.EnventID[unIndex], &NetworkEvents))
			{
				printf("δ�ɹ�WSAEnumNetworkEvents�Ĵ����룺%d��\n", WSAGetLastError());
				WSACloseEvent(hInstance_EnventID);
				closesocket(socketServer);
				WSACleanup();
				return -1;
			}
			else
			{
				//����ֻ����if��������switch�ж�����Ϊ����ж���¼�ͬʱ�������ᵼ���޷������ж�
				if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
				{
					if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] == 0)
					{
						struct sockaddr_in si_Client;
						int nLength = sizeof(si_Client);
						SOCKET socketClient = accept(tFD_EventSelect_Info.Sockets[unIndex], (struct sockaddr*)&si_Client, &nLength);
						if (INVALID_SOCKET == socketClient)
							continue;

						printf("һ���ͻ������ӳɹ�����ַΪ = %ul, �˿ں�Ϊ = %d\n", si_Client.sin_addr.S_un.S_addr, si_Client.sin_port);
						WSAEVENT wsaEventClient = WSACreateEvent();
						if (SOCKET_ERROR == WSAEventSelect(socketClient, wsaEventClient, FD_READ | FD_WRITE | FD_CLOSE))//socketͶ�ݸ��ں�
						{
							printf("δ�ɹ�WSAEventSelect�Ĵ����룺%d��\n", WSAGetLastError());
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
							printf("δ�ɹ�send�Ĵ����룺%d��\n", WSAGetLastError());
						}
						printf("��˿ں�Ϊ��%llu������һ����Ϣ\n", tFD_EventSelect_Info.Sockets[unIndex]);
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
							//���ݴ����𣬽�����Ӧ�Ĵ���
							printf("δ�ɹ�recv�Ĵ����룺%d��\n", WSAGetLastError());
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

					printf("һ���˿�Ϊ��%llu�Ŀͻ����˳��ˡ�\n", tFD_EventSelect_Info.Sockets[unIndex]);
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

	socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

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

	WSAEVENT hInstance_EnventID = WSACreateEvent();//�����¼����
	if (WSA_INVALID_EVENT == hInstance_EnventID)
	{
		printf("δ�ɹ�WSACreateEvent�Ĵ����룺%d��\n", WSAGetLastError());
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}

	if (SOCKET_ERROR == WSAEventSelect(socketServer, hInstance_EnventID, FD_ACCEPT))//socketͶ�ݸ��ں�
	{
		printf("δ�ɹ�WSAEventSelect�Ĵ����룺%d��\n", WSAGetLastError());
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
		DWORD ulStartIndex = WSAWaitForMultipleEvents(tFD_EventSelect_Info.Count, tFD_EventSelect_Info.EnventID, FALSE, WSA_INFINITE, FALSE);//��ѯ�ɲ�����socket
		if (ulStartIndex == WSA_WAIT_FAILED)//����ִ��ʧ��
		{
			printf("δ�ɹ�WSAWaitForMultipleEvents�Ĵ����룺%d��\n", WSAGetLastError());
			WSACloseEvent(hInstance_EnventID);
			closesocket(socketServer);
			WSACleanup();
			return -1;
		}

		for (size_t i = ulStartIndex; i < tFD_EventSelect_Info.Count; i++)
		{
			DWORD ulRtn = WSAWaitForMultipleEvents(1, &(tFD_EventSelect_Info.EnventID[i]), FALSE, 0, FALSE) + i;//��ѯ��ǰsocket��ִ��״̬
			if (ulRtn == WSA_WAIT_FAILED)//����ִ��ʧ��
			{
				printf("δ�ɹ�WSAWaitForMultipleEvents�Ĵ����룺%d��\n", WSAGetLastError());
				WSACloseEvent(hInstance_EnventID);
				closesocket(socketServer);
				WSACleanup();
				return -1;
			}
			else if (ulRtn >= WSA_WAIT_EVENT_0 && ulRtn <= (WSA_WAIT_EVENT_0 + WSA_MAXIMUM_WAIT_EVENTS - 1))//���ӵ������¼�������
			{
				unsigned int unIndex = ulRtn - WSA_WAIT_EVENT_0;
				WSANETWORKEVENTS NetworkEvents;

				if (SOCKET_ERROR == WSAEnumNetworkEvents(tFD_EventSelect_Info.Sockets[unIndex],
					tFD_EventSelect_Info.EnventID[unIndex], &NetworkEvents))
				{
					printf("δ�ɹ�WSAEnumNetworkEvents�Ĵ����룺%d��\n", WSAGetLastError());
					WSACloseEvent(hInstance_EnventID);
					closesocket(socketServer);
					WSACleanup();
					return -1;
				}
				else
				{
					//����ֻ����if��������switch�ж�����Ϊ����ж���¼�ͬʱ�������ᵼ���޷������ж�
					if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
					{
						if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] == 0)
						{
							struct sockaddr_in si_Client;
							int nLength = sizeof(si_Client);
							SOCKET socketClient = accept(tFD_EventSelect_Info.Sockets[unIndex], (struct sockaddr*)&si_Client, &nLength);
							if (INVALID_SOCKET == socketClient)
								continue;

							printf("һ���ͻ������ӳɹ�����ַΪ = %ul, �˿ں�Ϊ = %d\n", si_Client.sin_addr.S_un.S_addr, si_Client.sin_port);
							WSAEVENT wsaEventClient = WSACreateEvent();
							if (SOCKET_ERROR == WSAEventSelect(socketClient, wsaEventClient, FD_READ | FD_WRITE | FD_CLOSE))//socketͶ�ݸ��ں�
							{
								printf("δ�ɹ�WSAEventSelect�Ĵ����룺%d��\n", WSAGetLastError());
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
								printf("δ�ɹ�send�Ĵ����룺%d��\n", WSAGetLastError());
							}
							printf("��˿ں�Ϊ��%llu������һ����Ϣ\n", tFD_EventSelect_Info.Sockets[unIndex]);
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
								//���ݴ����𣬽�����Ӧ�Ĵ���
								printf("δ�ɹ�recv�Ĵ����룺%d��\n", WSAGetLastError());
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

						printf("һ���˿�Ϊ��%llu�Ŀͻ����˳��ˡ�\n", tFD_EventSelect_Info.Sockets[unIndex]);
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
