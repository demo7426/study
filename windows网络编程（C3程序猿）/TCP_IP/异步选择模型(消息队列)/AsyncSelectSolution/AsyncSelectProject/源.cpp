#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

//#include<Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include<WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define UM_ASYNCSELECTMSG WM_USER + 1
#define MAX_SOCKET_NUM 256

//Socket��Ϣ
typedef struct _SOCKET_INFO
{
	unsigned int CurrentIndex = 0;							//��ǰ��������
	SOCKET socketClients[MAX_SOCKET_NUM] = { 0 };			//�ͻ���socket
	SOCKET socketServer = 0;								//������socket
}SOCKET_INFO, * PSOCKET_INFO;

LRESULT  CALLBACK WinBackFunc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam);
int Init();

SOCKET_INFO g_tSocket_Info;

int WINAPI WinMain(HINSTANCE hInstance,	//��ǰ���ڵľ��
	HINSTANCE hPrevInstance,			//��һ�δ������ڵľ�����ò����ѱ����ã�
	LPSTR lpCmdLine,					//���������������
	int nShowCmd						//��ʾ��ʽ��0--��С����1--������ʾ��Ĭ��1������ʾ��
)
{
	WNDCLASSEX tWndClassEx;
	tWndClassEx.cbClsExtra = 0;//������Ķ���ռ�
	tWndClassEx.cbSize = sizeof(WNDCLASSEX);
	tWndClassEx.cbWndExtra = 0;//���ڵĶ���ռ�
	tWndClassEx.hbrBackground = NULL;//Ĭ�ϱ���
	tWndClassEx.hCursor = NULL;//���
	tWndClassEx.hIcon = NULL;//���Ͻ�ͼ��
	tWndClassEx.hIconSm = NULL;//������Сͼ��
	tWndClassEx.hInstance = hInstance;//��ǰʵ�����
	tWndClassEx.lpfnWndProc = WinBackFunc;
	tWndClassEx.lpszClassName = TEXT("MyWindow");
	tWndClassEx.lpszMenuName = NULL;
	tWndClassEx.style = CS_HREDRAW | CS_VREDRAW;

	//ע��ṹ��
	RegisterClassEx(&tWndClassEx);

	//��������
	HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, tWndClassEx.lpszClassName,
		TEXT("�ҵĴ���"), WS_OVERLAPPEDWINDOW, 200, 200, 600, 400,
		NULL, NULL, tWndClassEx.hInstance, NULL);

	if (hWnd == NULL)
		return -1;

	//��ʾ����
	ShowWindow(hWnd, nShowCmd);

	//���´���
	UpdateWindow(hWnd);

	//Ͷ�ݵ�������Ϣ����
	if (WSAAsyncSelect(g_tSocket_Info.socketServer, hWnd, UM_ASYNCSELECTMSG, FD_ACCEPT) == SOCKET_ERROR)
	{
		printf("δ�ɹ�WSAAsyncSelect�Ĵ����룺%d��\n", WSAGetLastError());
		closesocket(g_tSocket_Info.socketServer);
		WSACleanup();
		return -1;
	}
	//��Ϣѭ��
	MSG tMsg;
	while (GetMessage(&tMsg, NULL, 0, 0))
	{
		TranslateMessage(&tMsg);
		DispatchMessageW(&tMsg);
	}

	WSACleanup();
	return 1;
}

int Init()
{
	int nRtn = -1;                  //����ֵ
	WORD word = MAKEWORD(2, 2);     //MAKEWORD(2, 1);
	WSADATA tWSAData;               //������������

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

	g_tSocket_Info.socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == g_tSocket_Info.socketServer)
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

	if (bind(g_tSocket_Info.socketServer, (const struct sockaddr*)&si_Server, sizeof(si_Server)) == SOCKET_ERROR)
	{
		printf("δ�ɹ�bind�Ĵ����룺%d��\n", WSAGetLastError());
		closesocket(g_tSocket_Info.socketServer);
		WSACleanup();
		return -1;
	}

	//SOMAXCONN ����ϵͳ�Զ����ù������ӵ�����
	if (SOCKET_ERROR == listen(g_tSocket_Info.socketServer, SOMAXCONN))
	{
		printf("δ�ɹ�listen�Ĵ����룺%d��\n", WSAGetLastError());
		closesocket(g_tSocket_Info.socketServer);
		WSACleanup();
		return -1;
	}

	return 1;
}

//ÿһ��ֻ��ȡ��һ����Ϣ���д����ʿ���ʹ��״̬��
LRESULT  CALLBACK WinBackFunc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_CREATE:
		Init();
		break;
	case UM_ASYNCSELECTMSG:
	{
		static int nVerPos = 0;

		{
			char chBuf[64] = { 0 };
			sprintf(chBuf, "���յ���һ���ź�:%d", LOWORD(lParam));

			//MessageBox(NULL, TEXT("���յ���һ����Ϣ"), TEXT("������Ϣ"), MB_OKCANCEL);
			TextOutA(GetDC(hWnd), 0, nVerPos, chBuf, strlen(chBuf));
			ReleaseDC(hWnd, GetDC(hWnd));//�ͷ�hdc

			nVerPos += 15;
		}
		
		if (HIWORD(lParam) != NULL)//�ж��Ƿ���������������
		{
			printf("δ�ɹ�WinBackFunc�Ĵ����룺%d��\n", WSAGetLastError());
		}

		switch (LOWORD(lParam))
		{
		case FD_ACCEPT:
		{
			char chBuf[256] = { 0 };
			struct sockaddr_in si_Client;
			int nLength = sizeof(si_Client);

			SOCKET socketClient = accept((SOCKET)wParam, (sockaddr*)&si_Client, &nLength);

			sprintf(chBuf, "һ���ͻ������ӳɹ�����ַΪ = %ul, �˿ں�Ϊ = %d\n", si_Client.sin_addr.S_un.S_addr, si_Client.sin_port);
			
			TextOutA(GetDC(hWnd), 0, nVerPos, chBuf, strlen(chBuf));
			ReleaseDC(hWnd, GetDC(hWnd));//�ͷ�hdc
			nVerPos += 15;

			if (socketClient == INVALID_SOCKET)
			{
				printf("δ�ɹ�accept�Ĵ����룺%d��\n", WSAGetLastError());
				closesocket(g_tSocket_Info.socketServer);
				break;
			}

			//Ͷ�ݵ�������Ϣ����
			if (WSAAsyncSelect(socketClient, hWnd, UM_ASYNCSELECTMSG, FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
			{
				printf("δ�ɹ�WSAAsyncSelect�Ĵ����룺%d��\n", WSAGetLastError());
				closesocket(socketClient);
				break;
			}

			g_tSocket_Info.socketClients[g_tSocket_Info.CurrentIndex] = socketClient;
			g_tSocket_Info.CurrentIndex++;
		}
		break;
		case FD_READ:
		{
			char chBuf[1025] = { 0 };
			if (SOCKET_ERROR == recv((SOCKET)wParam, chBuf, sizeof(chBuf) - 1, 0))
			{
				printf("δ�ɹ�recv�Ĵ����룺%d��\n", WSAGetLastError());
				break;
			}

			TextOutA(GetDC(hWnd), 0, nVerPos, chBuf, strlen(chBuf));
			ReleaseDC(hWnd, GetDC(hWnd));//�ͷ�hdc
			nVerPos += 15;
		}
		break;
		case FD_WRITE:
			send((SOCKET)wParam, "���������ӳɹ�", sizeof("���������ӳɹ�"), 0);
			break;
		case FD_CLOSE:
		{
			char chBuf[1025] = { 0 };

			if (HIWORD(lParam) == WSAECONNABORTED)
				sprintf(chBuf, "һ��Socket ID = %d�����˳���", (SOCKET)wParam);
			else
				sprintf(chBuf, "һ��Socket ID = %dǿ���˳���", (SOCKET)wParam);

			TextOutA(GetDC(hWnd), 0, nVerPos, chBuf, strlen(chBuf));
			ReleaseDC(hWnd, GetDC(hWnd));//�ͷ�hdc
			

			WSAAsyncSelect((SOCKET)wParam, hWnd, NULL, NULL);//ȡ��Ͷ��
			closesocket((SOCKET)wParam);

			for (size_t i = 0; i < g_tSocket_Info.CurrentIndex; i++)
			{
				if (g_tSocket_Info.socketClients[i] == (SOCKET)wParam)
				{
					g_tSocket_Info.socketClients[i] = g_tSocket_Info.socketClients[g_tSocket_Info.CurrentIndex - 1];
					g_tSocket_Info.CurrentIndex--;
				}
			}
		}
		break;
		default:
			break;
		}



	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

