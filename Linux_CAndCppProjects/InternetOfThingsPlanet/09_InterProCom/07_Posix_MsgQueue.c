// Linux消息队列通信（任意进程之间）    Posix类型
// 一共6个API，分别为：mq_open、mq_receive、mq_send、mq_close、mq_unlink、mq_notify
//mq_open：打开或创建一个相对于 /dev/mqueue/ 路径的消息队列文件，同时设置消息队列的属性
//mq_receive：接收消息
//mq_send：发送消息
//mq_close：关闭消息队列
//mq_unlink：删除消息队列及对于 /dev/mqueue/ 路径的消息队列文件
//mq_notify：向消息队列注册通知

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <mqueue.h>
#include <unistd.h>
#include <string.h>

#define FIFEPATH "/07_Posix_MsgQueue.txt"

//注册通知函数
int DoNotify(int _Fd);

//打印消息队列中的信息
void MyNotifyPrintf(sigval_t _Arg)
{
    char chReaBuf[513] = {0};
    unsigned int unPriority = 2;

    mq_receive(_Arg.sival_int, chReaBuf, sizeof(chReaBuf) - 1, &unPriority);

    if (chReaBuf[0] != '\0')
        printf("MyNotifyPrintf：%s\n", chReaBuf);

    DoNotify(_Arg.sival_int);//通知被使用过一次后会被清零，需重新注册通知
}

int DoNotify(int _Fd)
{
    struct sigevent tsigevent;
    tsigevent.sigev_value.sival_int = _Fd;                        // 向回调函数传参
    tsigevent.sigev_notify = SIGEV_THREAD;                        // 告诉编译器调度一个线程进行处理
    tsigevent._sigev_un._sigev_thread._function = MyNotifyPrintf; // 设置回调函数
    tsigevent._sigev_un._sigev_thread._attribute = NULL;          // 设置线程属性

    if (mq_notify(_Fd, &tsigevent))//向内核注册通知
    {
        perror("mq_notify failed.\n");
        return -1;
    }

    pause();//防止子进程成为僵尸进程
    return 0;
}

int main(int argc, char *argv[], char *envp[])
{
    if (argc < 2)
    {
        perror("缺少传入的命令行参数.\n");
        return -1;
    }

    struct mq_attr tmq_attr;
    tmq_attr.mq_flags = 0; // 消息优先级
    tmq_attr.mq_maxmsg = 10;
    tmq_attr.mq_msgsize = 512;

    mqd_t nFd = mq_open(FIFEPATH, O_CREAT | O_RDWR, 0644, &tmq_attr);
    if (nFd == -1)
    {
        perror("mq_open failed.\n");
        return -1;
    }

    switch (atoi(argv[1]))
    {
    case 0: // 普通读数据
    {
        char chReaBuf[513] = {0};
        unsigned int unPriority = 2;

        while (1)
        {
            memset(chReaBuf, 0, sizeof(chReaBuf));
            mq_receive(nFd, chReaBuf, sizeof(chReaBuf) - 1, &unPriority);

            if (chReaBuf[0] != '\0')
                printf("Read：%s\n", chReaBuf);
        }
    }
    break;
    case 1: // 使用注册通知函数读数据
        DoNotify(nFd);
        break;
    case 2: // 写数据
    {
        while (1)
        {
            printf("1: %ld\n", nFd);
            const char *pchSend = "Hello world";

            if (mq_send(nFd, pchSend, strlen(pchSend), 0) == -1)
            {
                perror("mq_send failed.\n");
                return -1;
            }

            sleep(1);
        }
    }
    break;
    case 3: // 删除消息队列
    {
        mq_close(nFd);
        mq_unlink(FIFEPATH);
        printf("删除 /dev/mqueue/%s 文件成功.\n", FIFEPATH);
    }
    break;
    default:
        break;
    }

    return 0;
}