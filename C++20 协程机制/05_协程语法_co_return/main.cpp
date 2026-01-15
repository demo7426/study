/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2026.01.12
描  述: 实现协程语法_co_return
备  注: 协程机制参考：https://mengbaoliang.cn/archives/131970/
修改记录:

  1.  日期: 2026.01.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#include <iostream>
#include <coroutine>

struct _CORE_RAII
{
    struct promise_type
    {
        int value;
        //创建协程操作管理对象
        _CORE_RAII get_return_object()
        {
            return _CORE_RAII{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        //决定协程创建后是否马上执行
        //std::suspend_never    不挂起
        //std::suspend_always   挂起
        std::suspend_always initial_suspend()
        {
            return {};
        }

#if 0   //是否有返回值为互斥选项
        void return_void()
        {
            std::cout << "协程结束" << std::endl;
        }
#else
        void return_value(int value)
        {
            this->value = value;
        }
#endif

        //协程执行完后是否马上销毁
        //std::suspend_never    不挂起，立即销毁资源
        //std::suspend_always   挂起，不立即销毁，等待外部 destroy 释放资源
        std::suspend_always final_suspend() noexcept
        {
            return {};
        }

        //协程中有未处理的异常时如何处理
        void unhandled_exception()
        {
            std::cout << "未处理的异常" << std::endl;
        }
    };

    std::coroutine_handle<promise_type> handle;

    //构造函数初始化 handle 对象
    _CORE_RAII(std::coroutine_handle<promise_type> _Handle)
    {
        this->handle = _Handle;
    }

    // 封装其它 handle 操作
    void Resume()
    {
        if (!handle.done())
        {
            handle.resume();
        }
    }

    int Return_Value()
    {
        return this->handle.promise().value;
    }

    //析构函数初始化 handle 对象
    ~_CORE_RAII()
    {
        if (handle)
        {
            handle.destroy();
        }
    }

};

_CORE_RAII My_Corotine()
{
    std::cout << "协程执行 00" << std::endl;
    std::cout << "协程执行 01" << std::endl;

    co_return 20;

    std::cout << "协程执行 02" << std::endl;
}

int main()
{
    _CORE_RAII tCoro = My_Corotine();

    tCoro.Resume();

    std::cout << "协程返回值为: " << tCoro.Return_Value() << std::endl;

    return 0;
}

