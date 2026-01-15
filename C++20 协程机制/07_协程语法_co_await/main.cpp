/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2026.01.14
描  述: 实现协程语法_co_await
备  注: 在 promise_type 中定义 await_transform，可以拦截 co_await 后的表达式，并将其转换为一个满足 awaitable 协议的对象，无论原始表达式本身是否可等待
修改记录:

  1.  日期: 2026.01.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#include <iostream>
#include <coroutine>

#if 1
struct _MY_AWAITER
{
    bool await_ready() const noexcept
    {
        bool bFlag = false;
        std::cout << "是否执行：" << std::boolalpha << bFlag << std::endl;

        // true--不挂起：直接执行 await_resume 函数
        // false--挂起： 直接执行 await_suspend 函数
        return bFlag;
    }

    void await_suspend(std::coroutine_handle<> h) noexcept
    {
        std::cout << "协程挂起" << std::endl;
    }

    int await_resume() noexcept
    {
        std::cout << "协程执行" << std::endl;
        return 100;
    }

};

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

        //yield返回后的协程状态
        //std::suspend_never    不挂起
        //std::suspend_always   挂起
        std::suspend_always yield_value(int value)
        {
            this->value = value;

            return {};
        }

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
    int nRet = co_await _MY_AWAITER();

    std::cout << __func__ << ", nRet = " << nRet << std::endl;
}

int main()
{
    _CORE_RAII tCoro = My_Corotine();

    tCoro.Resume();
    std::cout << "协程返回值为: " << tCoro.Return_Value() << std::endl;

    tCoro.Resume();
    std::cout << "协程返回值为: " << tCoro.Return_Value() << std::endl;

    return 0;
}

#else //在 promise_type 中定义 await_transform，可以拦截 co_await 后的表达式，并将其转换为一个满足 awaitable 协议的对象，无论原始表达式本身是否可等待

struct _MY_AWAITER
{
    int value;

    bool await_ready() const noexcept
    {
        bool bFlag = false;
        std::cout << "是否执行：" << std::boolalpha << bFlag << std::endl;

        // true--不挂起：直接执行 await_resume 函数
        // false--挂起： 直接执行 await_suspend 函数
        return bFlag;
    }

    void await_suspend(std::coroutine_handle<> h) noexcept
    {
        std::cout << "协程挂起" << std::endl;
    }

    int await_resume() noexcept
    {
        std::cout << "协程执行" << std::endl;
        return value;
    }

};

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

        //yield返回后的协程状态
        //std::suspend_never    不挂起
        //std::suspend_always   挂起
        std::suspend_always yield_value(int value)
        {
            this->value = value;

            return {};
        }

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

        auto await_transform(int _Val)
        {
            return _MY_AWAITER{ _Val };
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
    //co_await _MY_AWAITER();
    int nRet = co_await 100;

    std::cout << __func__ << ", nRet = " << nRet << std::endl;
}

int main()
{
    _CORE_RAII tCoro = My_Corotine();

    tCoro.Resume();
    std::cout << "协程返回值为: " << tCoro.Return_Value() << std::endl;

    tCoro.Resume();
    std::cout << "协程返回值为: " << tCoro.Return_Value() << std::endl;

    return 0;
}

#endif

