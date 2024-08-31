#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "TcpServer.h"

int main(int argc, char* argv[], char* envp[])
{
    if (argc < 3)
    {
        perror("Please input: exec port path.\n");
        return -1;
    }

    const short sPort = atoi(argv[1]);   //�����˿�

    //�л�����Ĺ���Ŀ¼
    chdir(argv[2]);

    //����������
    PTCPSERVER_INFO ptTcpServer_Info = TcpServerInit(sPort, 4);

    TcpServerRun(ptTcpServer_Info);

	return 0;
}
