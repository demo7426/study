#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

//#include<Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include<WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define UM_ASYNCSELECTMSG WM_USER + 1
#define MAX_SOCKET_NUM 256

//Socket信息
typedef struct _SOCKET_INFO
{
	unsigned int CurrentIndex = 0;							//当前数组索引
	SOCKET socketClients[MAX_SOCKET_NUM] = { 0 };			//客户端socket
	SOCKET socketServer = 0;								//服务器socket
}SOCKET_INFO, * PSOCKET_INFO;

LRESULT  CALLBACK WinBackFunc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam);
int Init();

SOCKET_INFO g_tSocket_Info;

int WINAPI WinMain(HINSTANCE hInstance,	//当前串口的句柄
	HINSTANCE hPrevInstance,			//上一次创建窗口的句柄（该参数已被弃用）
	LPSTR lpCmdLine,					//命令行输入的数据
	int nShowCmd						//显示方式；0--最小化，1--正常显示；默认1正常显示）
)
{
	WNDCLASSEX tWndClassEx;
	tWndClassEx.cbClsExtra = 0;//窗口类的额外空间
	tWndClassEx.cbSize = sizeof(WNDCLASSEX);
	tWndClassEx.cbWndExtra = 0;//窗口的额外空间
	tWndClassEx.hbrBackground = NULL;//默认背景
	tWndClassEx.hCursor = NULL;//光标
	tWndClassEx.hIcon = NULL;//左上角图标
	tWndClassEx.hIconSm = NULL;//任务栏小图标
	tWndClassEx.hInstance = hInstance;//当前实例句柄
	tWndClassEx.lpfnWndProc = WinBackFunc;
	tWndClassEx.lpszClassName = TEXT("MyWindow");
	tWndClassEx.lpszMenuName = NULL;
	tWndClassEx.style = CS_HREDRAW | CS_VREDRAW;

	//注册结构体
	RegisterClassEx(&tWndClassEx);

	//创建窗口
	HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, tWndClassEx.lpszClassName,
		TEXT("我的窗口"), WS_OVERLAPPEDWINDOW, 200, 200, 600, 400,
		NULL, NULL, tWndClassEx.hInstance, NULL);

	if (hWnd == NULL)
		return -1;

	//显示窗口
	ShowWindow(hWnd, nShowCmd);

	//更新窗口
	UpdateWindow(hWnd);

	//投递到窗口消息队列
	if (WSAAsyncSelect(g_tSocket_Info.socketServer, hWnd, UM_ASYNCSELECTMSG, FD_ACCEPT) == SOCKET_ERROR)
	{
		printf("未成功WSAAsyncSelect的错误码：%d。\n", WSAGetLastError());
		closesocket(g_tSocket_Info.socketServer);
		WSACleanup();
		return -1;
	}
	//消息循环
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
	int nRtn = -1;                  //返回值
	WORD word = MAKEWORD(2, 2);     //MAKEWORD(2, 1);
	WSADATA tWSAData;               //函数传出参数

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

	g_tSocket_Info.socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == g_tSocket_Info.socketServer)
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

	if (bind(g_tSocket_Info.socketServer, (const struct sockaddr*)&si_Server, sizeof(si_Server)) == SOCKET_ERROR)
	{
		printf("未成功bind的错误码：%d。\n", WSAGetLastError());
		closesocket(g_tSocket_Info.socketServer);
		WSACleanup();
		return -1;
	}

	//SOMAXCONN 操作系统自动设置挂起连接的数量
	if (SOCKET_ERROR == listen(g_tSocket_Info.socketServer, SOMAXCONN))
	{
		printf("未成功listen的错误码：%d。\n", WSAGetLastError());
		closesocket(g_tSocket_Info.socketServer);
		WSACleanup();
		return -1;
	}

	return 1;
}

//每一次只会取出一条消息进行处理，故可以使用状态机
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
			sprintf(chBuf, "接收到了一个信号:%d", LOWORD(lParam));

			//MessageBox(NULL, TEXT("接收到了一条消息"), TEXT("接收信息"), MB_OKCANCEL);
			TextOutA(GetDC(hWnd), 0, nVerPos, chBuf, strlen(chBuf));
			ReleaseDC(hWnd, GetDC(hWnd));//释放hdc

			nVerPos += 15;
		}
		
		if (HIWORD(lParam) != NULL)//判定是否数据流传输有误
		{
			printf("未成功WinBackFunc的错误码：%d。\n", WSAGetLastError());
		}

		switch (LOWORD(lParam))
		{
		case FD_ACCEPT:
		{
			char chBuf[256] = { 0 };
			struct sockaddr_in si_Client;
			int nLength = sizeof(si_Client);

			SOCKET socketClient = accept((SOCKET)wParam, (sockaddr*)&si_Client, &nLength);

			sprintf(chBuf, "一个客户端连接成功，地址为 = %ul, 端口号为 = %d\n", si_Client.sin_addr.S_un.S_addr, si_Client.sin_port);
			
			TextOutA(GetDC(hWnd), 0, nVerPos, chBuf, strlen(chBuf));
			ReleaseDC(hWnd, GetDC(hWnd));//释放hdc
			nVerPos += 15;

			if (socketClient == INVALID_SOCKET)
			{
				printf("未成功accept的错误码：%d。\n", WSAGetLastError());
				closesocket(g_tSocket_Info.socketServer);
				break;
			}

			//投递到窗口消息队列
			if (WSAAsyncSelect(socketClient, hWnd, UM_ASYNCSELECTMSG, FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
			{
				printf("未成功WSAAsyncSelect的错误码：%d。\n", WSAGetLastError());
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
				printf("未成功recv的错误码：%d。\n", WSAGetLastError());
				break;
			}

			TextOutA(GetDC(hWnd), 0, nVerPos, chBuf, strlen(chBuf));
			ReleaseDC(hWnd, GetDC(hWnd));//释放hdc
			nVerPos += 15;
		}
		break;
		case FD_WRITE:
			send((SOCKET)wParam, "服务器连接成功", sizeof("服务器连接成功"), 0);
			break;
		case FD_CLOSE:
		{
			char chBuf[1025] = { 0 };

			if (HIWORD(lParam) == WSAECONNABORTED)
				sprintf(chBuf, "一个Socket ID = %d正常退出。", (SOCKET)wParam);
			else
				sprintf(chBuf, "一个Socket ID = %d强行退出。", (SOCKET)wParam);

			TextOutA(GetDC(hWnd), 0, nVerPos, chBuf, strlen(chBuf));
			ReleaseDC(hWnd, GetDC(hWnd));//释放hdc
			

			WSAAsyncSelect((SOCKET)wParam, hWnd, NULL, NULL);//取消投递
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

