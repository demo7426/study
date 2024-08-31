#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "TcpServer.h"

int main(int argc, char* argv[], char* envp[])
{
    if (argc < 3)
    {
        perror("Please input: exec port path.\n");
        return -1;
    }

    const short sPort = atoi(argv[1]);   //监听端口

    //切换程序的工作目录
    chdir(argv[2]);

    //启动服务器
    CTcpServer* ptTcpServer_Info = new CTcpServer(sPort, 4);

    ptTcpServer_Info->Run();

	return 0;
}
