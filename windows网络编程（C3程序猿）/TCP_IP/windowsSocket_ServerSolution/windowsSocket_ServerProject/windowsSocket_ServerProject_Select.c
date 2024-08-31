#include"windowsSocket_ServerProject_Select.h"

static fd_set g_tTotalSocket;                    //保存所有的socket

BOOL WINAPI Func(DWORD CtrlType)
{
    switch (CtrlType)
    {
    case CTRL_CLOSE_EVENT:
    {
        for (size_t i = 0; i < g_tTotalSocket.fd_count; i++)
        {
            closesocket(g_tTotalSocket.fd_array[i]);
        }

        WSACleanup();
    }
    break;
    default:
        break;
    }

    return TRUE;
}

/// <summary>
/// 通信服务端select模型
/// </summary>
/// <returns></returns>
int Test_Select()
{
    SetConsoleCtrlHandler(Func, TRUE);//有一个5s的系统超时机制，如果超时会直接关闭控制台结束程序

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

    FD_ZERO(&g_tTotalSocket);                 //将数量清零
    FD_SET(socketServer, &g_tTotalSocket);    //添加socket

    while (1)
    {
        fd_set tTotalSocket_RecvTemp = g_tTotalSocket;
        fd_set tTotalSocket_SendTemp = g_tTotalSocket;
        fd_set tTotalSocket_ErrorTemp = g_tTotalSocket;

        struct timeval tTimeval;
        tTimeval.tv_sec = 2;
        tTimeval.tv_usec = 100;//延时2s又100us的时间

        int nRtn = select(0, &tTotalSocket_RecvTemp, &tTotalSocket_SendTemp, &tTotalSocket_ErrorTemp, &tTimeval);

        if (nRtn == 0)//延时时间等待完毕tTotalSocket还没有任意一个响应
            continue;
        else if (nRtn > 0)//有响应
        {
            //判断是否有出现异常的socket
            for (size_t i = 0; i < tTotalSocket_ErrorTemp.fd_count; i++)
            {
                char chBuf[129] = { 0 };
                int nLength = sizeof(chBuf) - 1;
                getsockopt(tTotalSocket_ErrorTemp.fd_array[i], SOL_SOCKET, SO_ERROR, chBuf, &nLength);

                puts(chBuf);
                putchar('\n');
            }

            //判定是否可以发送信息
            for (size_t i = 0; i < tTotalSocket_SendTemp.fd_count; i++)
            {
                if (SOCKET_ERROR == send(tTotalSocket_SendTemp.fd_array[i], "服务器发送过来的消息", 21, 0))
                {
                    //根据错误吗，进行相应的处理
                    printf("未成功send的错误码：%d。\n", WSAGetLastError());
                }
            }

            //判定是否可以接收信息或创建客户端
            for (size_t i = 0; i < tTotalSocket_RecvTemp.fd_count; i++)
            {
                if (tTotalSocket_RecvTemp.fd_array[i] == socketServer)
                {
                    SOCKET socketClient = accept(socketServer, NULL, NULL);
                    if (socketClient == INVALID_SOCKET)
                    {
                        printf("未成功accept的错误码：%d。\n", WSAGetLastError());
                    }
                    else
                        FD_SET(socketClient, &g_tTotalSocket);
                }
                else
                {
                    char chBuf[1025] = { 0 };
                    int nRcvLength = recv(tTotalSocket_RecvTemp.fd_array[i], chBuf, sizeof(chBuf), 0);

                    if (nRcvLength == 0)
                    {
                        printf("一个%llu\t客户端正常断开连接\n", tTotalSocket_RecvTemp.fd_array[i]);
                        FD_CLR(tTotalSocket_RecvTemp.fd_array[i], &g_tTotalSocket);
                        closesocket(tTotalSocket_RecvTemp.fd_array[i]);
                    }
                    else if (nRcvLength == SOCKET_ERROR)
                    {
                        //根据错误吗，进行相应的处理
                        switch (WSAGetLastError())
                        {
                        case 10054:
                        {
                            printf("一个%llu\t客户端强制断开连接\n", tTotalSocket_RecvTemp.fd_array[i]);
                            FD_CLR(tTotalSocket_RecvTemp.fd_array[i], &g_tTotalSocket);
                            closesocket(tTotalSocket_RecvTemp.fd_array[i]);
                        }
                        break;
                        default:
                            printf("未成功recv的错误码：%d。\n", WSAGetLastError());
                            break;
                        }
                    }
                    else
                        printf("%s\n", chBuf);
                }
            }

        }
        else if (nRtn == SOCKET_ERROR)
        {
            //发生错误
            printf("未成功select的错误码：%d。\n", WSAGetLastError());
            break;
        }

    }

    for (size_t i = 0; i < g_tTotalSocket.fd_count; i++)
    {
        closesocket(g_tTotalSocket.fd_array[i]);
    }

    WSACleanup();
    return nRtn;
}