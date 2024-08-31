#include"windowsSocket_ServerProject_Select.h"

static fd_set g_tTotalSocket;                    //�������е�socket

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
/// ͨ�ŷ����selectģ��
/// </summary>
/// <returns></returns>
int Test_Select()
{
    SetConsoleCtrlHandler(Func, TRUE);//��һ��5s��ϵͳ��ʱ���ƣ������ʱ��ֱ�ӹرտ���̨��������

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

    FD_ZERO(&g_tTotalSocket);                 //����������
    FD_SET(socketServer, &g_tTotalSocket);    //���socket

    while (1)
    {
        fd_set tTotalSocket_RecvTemp = g_tTotalSocket;
        fd_set tTotalSocket_SendTemp = g_tTotalSocket;
        fd_set tTotalSocket_ErrorTemp = g_tTotalSocket;

        struct timeval tTimeval;
        tTimeval.tv_sec = 2;
        tTimeval.tv_usec = 100;//��ʱ2s��100us��ʱ��

        int nRtn = select(0, &tTotalSocket_RecvTemp, &tTotalSocket_SendTemp, &tTotalSocket_ErrorTemp, &tTimeval);

        if (nRtn == 0)//��ʱʱ��ȴ����tTotalSocket��û������һ����Ӧ
            continue;
        else if (nRtn > 0)//����Ӧ
        {
            //�ж��Ƿ��г����쳣��socket
            for (size_t i = 0; i < tTotalSocket_ErrorTemp.fd_count; i++)
            {
                char chBuf[129] = { 0 };
                int nLength = sizeof(chBuf) - 1;
                getsockopt(tTotalSocket_ErrorTemp.fd_array[i], SOL_SOCKET, SO_ERROR, chBuf, &nLength);

                puts(chBuf);
                putchar('\n');
            }

            //�ж��Ƿ���Է�����Ϣ
            for (size_t i = 0; i < tTotalSocket_SendTemp.fd_count; i++)
            {
                if (SOCKET_ERROR == send(tTotalSocket_SendTemp.fd_array[i], "���������͹�������Ϣ", 21, 0))
                {
                    //���ݴ����𣬽�����Ӧ�Ĵ���
                    printf("δ�ɹ�send�Ĵ����룺%d��\n", WSAGetLastError());
                }
            }

            //�ж��Ƿ���Խ�����Ϣ�򴴽��ͻ���
            for (size_t i = 0; i < tTotalSocket_RecvTemp.fd_count; i++)
            {
                if (tTotalSocket_RecvTemp.fd_array[i] == socketServer)
                {
                    SOCKET socketClient = accept(socketServer, NULL, NULL);
                    if (socketClient == INVALID_SOCKET)
                    {
                        printf("δ�ɹ�accept�Ĵ����룺%d��\n", WSAGetLastError());
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
                        printf("һ��%llu\t�ͻ��������Ͽ�����\n", tTotalSocket_RecvTemp.fd_array[i]);
                        FD_CLR(tTotalSocket_RecvTemp.fd_array[i], &g_tTotalSocket);
                        closesocket(tTotalSocket_RecvTemp.fd_array[i]);
                    }
                    else if (nRcvLength == SOCKET_ERROR)
                    {
                        //���ݴ����𣬽�����Ӧ�Ĵ���
                        switch (WSAGetLastError())
                        {
                        case 10054:
                        {
                            printf("һ��%llu\t�ͻ���ǿ�ƶϿ�����\n", tTotalSocket_RecvTemp.fd_array[i]);
                            FD_CLR(tTotalSocket_RecvTemp.fd_array[i], &g_tTotalSocket);
                            closesocket(tTotalSocket_RecvTemp.fd_array[i]);
                        }
                        break;
                        default:
                            printf("δ�ɹ�recv�Ĵ����룺%d��\n", WSAGetLastError());
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
            //��������
            printf("δ�ɹ�select�Ĵ����룺%d��\n", WSAGetLastError());
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