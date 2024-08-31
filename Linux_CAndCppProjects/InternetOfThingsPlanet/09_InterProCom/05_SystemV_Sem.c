// Linux进程间通信有名信号量测试    System V类型
// 一共3个API，分别为：semget、semop、semctl
// semget：根据key值，生成信号量集
// semop：申请、等待、释放信号量
// semctl：设置信号量集（信号量集就是被创建的信号量的数组集合）中对应索引（索引从0开始）的值或删除信号量集

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define FILEPATH "./05_Sem.txt"

union semun
{
    int val;                   // value for SETVAL
    struct semid_ds *buf;      // buffer for IPC_STAT & IPC_SET
    unsigned short int *array; // array for GETALL & SETALL
    struct seminfo *__buf;     // buffer for IPC_INFO
};

int Sem_Init_Value(int _SemID)
{
    union semun un;
    un.val = 0;
    if (semctl(_SemID, 1, SETVAL, un) == -1) // 设置1号索引的信号量值
    {
        perror("semctl failed.\n");
        return -1;
    }

    Sem_Get_Value(_SemID);
    return 0;
}

int Sem_Get_Value(int _SemID)
{
    union semun un;
    un.val = 0;

    int nRet = semctl(_SemID, 1, GETVAL, un); // 获取1号索引的信号量值
    if (nRet == -1)
    {
        perror("semctl failed.\n");
        return -1;
    }

    printf("Sem_Get_Value：%ld\n", nRet);

    return 0;
}

int Sem_P(int _SemID)
{
    struct sembuf tsembuf;
    tsembuf.sem_num = 1;
    tsembuf.sem_op = -1;
    tsembuf.sem_flg = IPC_NOWAIT;
    // tsembuf.sem_flg = SEM_UNDO;   //在当前进程结束后，撤销对信号量的更改，防止进程退出未释放信号量，致使其他进程一直阻塞等待

    if (semop(_SemID, &tsembuf, 1) == -1)
    {
        perror("Sem_P failed.\n");
        return -1;
    }

    Sem_Get_Value(_SemID);
    return 0;
}

int Sem_W(int _SemID)
{
    struct sembuf tsembuf;
    tsembuf.sem_num = 1;
    tsembuf.sem_op = 0;
    // tsembuf.sem_flg = IPC_NOWAIT;

    if (semop(_SemID, &tsembuf, 1) == -1)
    {
        perror("Sem_W failed.\n");
        return -1;
    }

    Sem_Get_Value(_SemID);
    return 0;
}

int Sem_V(int _SemID)
{
    struct sembuf tsembuf;
    tsembuf.sem_num = 1;
    tsembuf.sem_op = 1;
    tsembuf.sem_flg = IPC_NOWAIT;
    // tsembuf.sem_flg = SEM_UNDO;   //在当前进程结束后，撤销对信号量的更改，防止进程退出未释放信号量，致使其他进程一直阻塞等待

    if (semop(_SemID, &tsembuf, 1) == -1)
    {
        perror("Sem_V failed.\n");
        return -1;
    }

    Sem_Get_Value(_SemID);
    return 0;
}

int main(int argc, char *argv[], char *envp)
{
    if (argc < 2)
    {
        perror("命令行缺少传入参数\n");
        return -1;
    }

    key_t key = ftok(FILEPATH, 1);
    int nSemID = semget(key, 4, 0644 | IPC_CREAT);
    printf("nSemID = %ld\n", nSemID);
    if (nSemID == -1)
    {
        perror("semget failed.\n");
        return -1;
    }

    switch (atoi(argv[1]))
    {
    case 0: // 初始化信号量操作
        Sem_Init_Value(nSemID);
        break;
    case 1: // 获取当前的信号量集中索引对应的值
        Sem_Get_Value(nSemID);
        break;
    case 2: // 申请信号量
        Sem_P(nSemID);
        break;
    case 3: // 等待信号量
        Sem_W(nSemID);
        break;
    case 4: // 释放信号量
        Sem_V(nSemID);
        break;
    case 5: // 删除信号量集
    {
        union semun un;
        if (nSemID != -1)
            semctl(nSemID, 1, IPC_RMID, un);
    }
    break;
    default:
        break;
    }

    return 0;
}