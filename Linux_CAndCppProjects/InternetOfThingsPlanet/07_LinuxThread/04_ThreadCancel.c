//Linux 线程取消和清理
//一共6个API：分别为线程取消：pthread_cancel、pthread_setcancelstate、pthread_setcanceltype、pthread_testcancel；线程清理：pthread_cleanup_push、pthread_cleanup_pop
//pthread_cancel：向指定的线程发出线程取消信号
//pthread_setcancelstate：设置当前线程是否使能线程取消信号
//pthread_setcanceltype：设置线程取消是否为延迟取消
//pthread_testcancel：线程取消点（同时系统默认sleep、printf等等函数默认为线程取消点）

//pthread_cleanup_push、pthread_cleanup_pop必须成对使用，否则会导致编译报错
//pthread_cleanup_push：线程清理函数入栈
//pthread_cleanup_pop：从栈内部取出线程清理函数，根据线程退出情况，判定是否需要执行取出的清理函数（是否会被调用参考当前目录下的04_ThreadCancel.png图片）

#include <stdio.h>
#include <stdio.h>
#include <pthread.h>

//休眠函数（因为系统sleep、printf等等函数默认为线程取消点）
void MySleep(size_t _SleepTime)
{
    size_t i = 0;
    for (size_t j = 0; j < _SleepTime; j++)
    {
        i++;
    }
}

void *ThreadCancel(void *_Arg)
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);    //使能线程取消信号
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);   //设置线程取消为延迟取消

    MySleep(10);
    pthread_testcancel();

    printf("ThreadCancel printf 01.\n");
    printf("ThreadCancel printf 02.\n");
}

void Cleanup(void *_Arg)
{
    printf("Cleanup called.\n");
}

void *ThreadClean(void *_Arg)
{
    pthread_cleanup_push(Cleanup, NULL);
    pthread_cleanup_pop(1);
    //return NULL;
    pthread_exit(NULL);
}

//线程清理函数测试
int Test_ThreadClean(void)
{
    pthread_t ulpthread_t = 0;
    pthread_attr_t tpthread_attr_t;

    pthread_attr_init(&tpthread_attr_t);
    pthread_attr_setdetachstate(&tpthread_attr_t, PTHREAD_CREATE_JOINABLE);//线程属性默认为PTHREAD_CREATE_JOINABLE，可以不用设置

    if (pthread_create(&ulpthread_t, &tpthread_attr_t, ThreadClean, NULL) != 0)
    {
        perror("pthread_create failed.\n");
        return 0;
    }
   
    pthread_join(ulpthread_t, NULL);

    pthread_attr_destroy(&tpthread_attr_t);
    return 1;
}

//线程取消函数测试
int Test_ThreadCancel(void)
{
    pthread_t ulpthread_t = 0;
    pthread_attr_t tpthread_attr_t;

    pthread_attr_init(&tpthread_attr_t);
    pthread_attr_setdetachstate(&tpthread_attr_t, PTHREAD_CREATE_JOINABLE);//线程属性默认为PTHREAD_CREATE_JOINABLE，可以不用设置

    if (pthread_create(&ulpthread_t, &tpthread_attr_t, ThreadCancel, NULL) != 0)
    {
        perror("pthread_create failed.\n");
        return 0;
    }
    
    MySleep(500);
    pthread_cancel(ulpthread_t);
    pthread_join(ulpthread_t, NULL);

    pthread_attr_destroy(&tpthread_attr_t);
    return 1;
}

int main(int argc, char *argv[], char *envp[])
{
    Test_ThreadClean();
    return 0;
}

