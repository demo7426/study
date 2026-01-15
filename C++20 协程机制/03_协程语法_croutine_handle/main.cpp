/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2026.01.12
描  述: 实现协程语法_croutine_handle
备  注:	https://mengbaoliang.cn/archives/131970/
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
    std::coroutine_handle<> handle;

    //构造函数初始化 handle 对象
    _CORE_RAII(std::coroutine_handle<> _Handle)
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
    std::cout << "协程执行" << std::endl;
}

int main()
{
    _CORE_RAII tCoro = My_Corotine();

    return 0;
}

