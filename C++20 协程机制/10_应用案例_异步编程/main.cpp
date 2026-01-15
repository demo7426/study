/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2026.01.15
描  述: 使用协程实现惰性计算-异步编程
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
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

class CEVENT_LOOP
{
public:

    void Add_Task(std::coroutine_handle<> _Handle)
    {
        std::unique_lock<std::mutex> lock(m_mut);
        m_que.push(_Handle);
    }

    void Post_Task(std::coroutine_handle<> _Handle)
    {
        this->Add_Task(_Handle);
        m_cond.notify_one();
    }
    
    void Run()
    {
        std::coroutine_handle<> handle;

        while (1)
        {
            {
                std::unique_lock<std::mutex> lock(m_mut);
                m_cond.wait(lock, [&]() {
                    return !m_que.empty();
                    });
            }

            handle = m_que.front();
            m_que.pop();

            if (!handle)
                continue;

            handle.resume();
        }
    }

private:
    std::queue<std::coroutine_handle<>> m_que;
    std::mutex m_mut;
    std::condition_variable m_cond;
};

CEVENT_LOOP g_cEvent_Loop;

struct _AWAITER
{
    int m_nDuration;            //时间长度;单位:秒

    bool await_ready() const noexcept
    {
        // true--不挂起：直接执行 await_resume 函数
        // false--挂起： 直接执行 await_suspend 函数
        return false;
    }

    void await_suspend(std::coroutine_handle<> _Handle) noexcept
    {
        std::thread([_Handle, duration = m_nDuration] {
            std::this_thread::sleep_for(std::chrono::milliseconds(duration));
            g_cEvent_Loop.Post_Task(_Handle);
            }).detach();
    }

    int await_resume() noexcept
    {
        return 100;
    }

};

struct _TASK
{
    struct promise_type
    {
        int m_nValue;

        //创建协程操作管理对象
        _TASK get_return_object()
        {
            return _TASK{ std::coroutine_handle<promise_type>::from_promise(*this) };
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

    explicit _TASK(std::coroutine_handle<promise_type> _Handle)
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

    ~_TASK()
    {
        if (m_handle)
            m_handle.destroy();
    }

    operator std::coroutine_handle<>()
    {
        return m_handle;
    }
};

_TASK Task00()
{
    std::cout << __func__ << " 执行开始" << std::endl;
    co_await _AWAITER(5000);
    std::cout << __func__ << " 执行结束" << std::endl;
}

_TASK Task01()
{
    std::cout << __func__ << " 执行开始" << std::endl;
    co_await _AWAITER(3000);
    std::cout << __func__ << " 执行结束" << std::endl;
}

int main()
{
    auto task00 = Task00();
    auto task01 = Task01();

    g_cEvent_Loop.Add_Task(task00);
    g_cEvent_Loop.Add_Task(task01);

    g_cEvent_Loop.Run();

    return 0;
}



