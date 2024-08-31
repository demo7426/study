#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include<WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

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

    if (SOCKET_ERROR == connect(socketServer, (const struct sockaddr*)&si_Server, sizeof(si_Server)))
    {
        closesocket(socketServer);
        WSACleanup();
        return -1;
    }

    char chSendBuf[1024] = "客户发过来的第一条信息。";
    if (send(socketServer, chSendBuf, sizeof(chSendBuf), 0) == SOCKET_ERROR)
    {
        closesocket(socketServer);
        WSACleanup();
        return -1;
    }

    char chBuf[1025] = { 0 };
    //flags有四种参数;
    //  0--读取后IO输入缓冲区自动删除,MSG_PEEK--只读取不删除,MSG_OOB--传输时在每条后面数据追加特殊字符,MSG_WAITALL--满足服务器读取的长度才会读取反之阻塞
    int nRcvLength = recv(socketServer, chBuf, sizeof(chBuf) - 1, 0);

    if (nRcvLength == 0)
        puts("服务端断开连接\n");
    else if (nRcvLength == SOCKET_ERROR)
    {
        //根据错误吗，进行相应的处理
        printf("未成功recv的错误码：%d。\n", WSAGetLastError());
    }
    else
        printf("%s\n", chBuf);

    closesocket(socketServer);
    WSACleanup();

}

int Test02()
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

    if (SOCKET_ERROR == connect(socketServer, (const struct sockaddr*)&si_Server, sizeof(si_Server)))
    {
        closesocket(socketServer);
        WSACleanup();
        return -1;
    }

    char chRecvBuf[1025] = { 0 };
    int nRecvLength = recv(socketServer, chRecvBuf, sizeof(chRecvBuf) - 1, 0);
    if (nRecvLength != 0)
        puts(chRecvBuf);

    while (1)
    {
        char chSendBuf[1025] = { 0 };
        scanf("%s", chSendBuf);

        if (chSendBuf[0] == 'q' && chSendBuf[1] == '\0')
            break;

        if (send(socketServer, chSendBuf, sizeof(chSendBuf), 0) == SOCKET_ERROR)
        {
            closesocket(socketServer);
            WSACleanup();
            return -1;
        }
    }

    closesocket(socketServer);
    WSACleanup();
}

int main()
{
    Test02();
    system("pause");
    return 0;
}
