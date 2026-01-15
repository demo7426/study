/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2026.01.15
描  述: 使用协程实现惰性计算-斐波那契数列
备  注: 
修改记录:

  1.  日期: 2026.01.15
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#include <iostream>
#include <coroutine>

#if 1

struct _Generator
{
    struct promise_type
    {
        int m_nValue;

        //创建协程操作管理对象
        _Generator get_return_object()
        {
            return _Generator{ std::coroutine_handle<promise_type>::from_promise(*this) };
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
            this->m_nValue = value;
        }
#endif
        //yield返回后的协程状态
        //std::suspend_never    不挂起
        //std::suspend_always   挂起
        std::suspend_always yield_value(int value)
        {
            this->m_nValue = value;

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


    std::coroutine_handle<promise_type> m_handle;

    explicit _Generator(std::coroutine_handle<promise_type> _Handle)
    {
        m_handle = _Handle;
    }

    void Next()
    {
        if (!m_handle.done())
            m_handle.resume();
    }

    int Value()
    {
        return this->m_handle.promise().m_nValue;
    }

    ~_Generator()
    {
        if (m_handle)
            m_handle.destroy();
    }

};

_Generator Fibonacci()
{
    int nPrev0 = 0;
    int nPrev1 = 1;

    while (1)
    {
        int nCur = nPrev0;
        int nNext = nPrev0 + nPrev1;

        nPrev0 = nPrev1;
        nPrev0 = nNext;

        co_yield nCur;
    }
}

int main()
{
    auto t = Fibonacci();

    for (size_t i = 0; i < 5; i++)
    {
        t.Next();

        std::cout << t.Value() << " ";
    }

    std::cout << std::flush;

    return 0;
}
#else

int Fibonacci()
{
    static int nPrev0 = 0;
    static int nPrev1 = 1;

    int nCur = nPrev0;
    int nNext = nPrev0 + nPrev1;

    nPrev0 = nPrev1;
    nPrev0 = nNext;

    return nCur;
}

int main()
{
    int nVal = 0;

    for (size_t i = 0; i < 5; i++)
    {
        nVal = Fibonacci();
        std::cout << nVal << " ";
    }

    std::cout << std::flush;

    return 0;
}

#endif


