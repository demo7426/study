#ifndef _THREADPOOL_H
#define _THREADPOOL_H

//线程池结构体
typedef struct _THREADPOOL_INFO THREADPOOL_INFO;

/// <summary>
/// 创建线程池并初始化
/// </summary>
/// <param name="_MinNum">最小线程数</param>
/// <param name="_MaxNum">最大线程数</param>
/// <param name="_Capacity">任务容量</param>
/// <returns>NULL--失败;!NULL--成功</returns>
THREADPOOL_INFO* ThreadPool_Create(int _MinNum, int _MaxNum, int _Capacity);

/// <summary>
/// 向任务队列添加任务
/// </summary>
/// <param name="_pInfo"></param>
/// <param name="Func"></param>
/// <param name="_Arg"></param>
void ThreadPoolAdd(THREADPOOL_INFO* _pInfo, void(*Func)(void*), void* _Arg);

/// <summary>
/// 获取线程池中在忙的线程个数
/// </summary>
/// <param name="_pInfo"></param>
/// <returns></returns>
int GetThreadPool_BusyThreadNum(THREADPOOL_INFO* _pInfo);

/// <summary>
/// 获取线程池中活着的线程个数
/// </summary>
/// <param name="_pInfo"></param>
/// <returns></returns>
int GetThreadPool_AliveThreadNum(THREADPOOL_INFO* _pInfo);

/// <summary>
/// 销毁线程池
/// </summary>
/// <param name="_pInfo"></param>
/// <returns>-1--传入参数错误，0--函数执行失败，1--函数执行成功</returns>
int ThreadPool_Destroy(THREADPOOL_INFO* _pInfo);


#endif _THREADPOOL_H// !_THREADPOOL_H
