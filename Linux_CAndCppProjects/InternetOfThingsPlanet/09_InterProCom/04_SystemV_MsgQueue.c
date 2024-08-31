// Linux消息队列通信（任意进程之间）    System V类型
// 一共5个API，分别为ftok、msgget、msgsnd、msgrcv、msgctl
// ftok：根据传入参数，使用内核内部算法计算出唯一的key值
// msgget：根据key值，计算出消息队列标识ID
// msgsnd：向消息队列发送消息
// msgrcv：从消息队列接收消息
// msgctl：获取指定消息队列的状态信息

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/msg.h>
#include <string.h>

#define MSGPATH "./04_MsgQueue.txt"

struct _MSGBUF
{
    long mtype;
    char mtext[1];
};

int main(int argc, char *argv[], char *envp[])
{
    if (argc < 3)
    {
        perror("缺少命令行参数.\n");
        return 1;
    }

    key_t key;                                         // 消息队列key值
    int nMsgID;                                        // 消息队列标识符
    int nFd = open(MSGPATH, O_CREAT | O_RDONLY, 0644); // 保证文件存在
    if (nFd == -1)
    {
        perror("open failed.\n");
        return 1;
    }

    close(nFd);

    // key = 1;
    // key = IPC_PRIVATE;
    key = ftok(MSGPATH, 1); // 推荐使用内核内部算法计算出唯一的key值
    nMsgID = msgget(key, 0644 | IPC_CREAT);

    if (atoi(argv[1]) == 0) // 接收数据
    {
        struct _MSGBUF tMsgBuf = {0};
        while (1)
        {
            memset(tMsgBuf.mtext, 0, sizeof(tMsgBuf.mtext));

            msgrcv(nMsgID, &tMsgBuf, 513, atoi(argv[2]), 0);

            if (tMsgBuf.mtext[0] != '0')
                printf("%ld, %s\n", tMsgBuf.mtype, tMsgBuf.mtext);
        }
    }
    else if (atoi(argv[1]) == 1) // 发送数据
    {
        struct _MSGBUF tMsgBuf = {0};
        struct msqid_ds tmsqid_ds = {0};
        while (1)
        {
            memset(&tMsgBuf, 0, sizeof(tMsgBuf));
            memset(&tmsqid_ds, 0, sizeof(tmsqid_ds));

            tMsgBuf.mtype = atoi(argv[2]);
            memcpy(tMsgBuf.mtext, "Hello world.", strlen("Hello world."));
            msgsnd(nMsgID, &tMsgBuf, strlen(tMsgBuf.mtext), 0);

            msgctl(nMsgID, IPC_STAT, &tmsqid_ds);
            printf("Write：queue = %ld, byte = %ld\n", tmsqid_ds.msg_qnum, tmsqid_ds.__msg_cbytes);
            sleep(1);
        }
    }
    else
    {
        perror("命令行第二个参数错误.\n");
        return 1;
    }

    return 0;
}