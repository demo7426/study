/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	singleton.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.06.14
描  述:	实现一个单例模板类
备  注:
修改记录:

  1.  日期: 2026.06.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <iostream>
#include <mutex>

template<typename T>
class CSingleTon
{
protected:
    CSingleTon() = default;
    CSingleTon(const CSingleTon<T>&) = default;
    CSingleTon(CSingleTon<T>&&) = default;

    CSingleTon& operator=(const CSingleTon<T>&) = delete;
    CSingleTon&& operator=(CSingleTon<T>&&) = delete;

    static std::shared_ptr<T> m_cInstance;

public:
    ~CSingleTon()
    {
        std::cout << __func__ << " is called." << std::endl;
    }

    static std::shared_ptr<T> GetInstance(void)
    {
        static std::once_flag flag;
        std::call_once(flag, [&](){
            m_cInstance = std::shared_ptr<T>(new T);
        });

        return m_cInstance;
    }

    void PrintAddress(void)
    {
        std::cout << __func__ << " is called, address = " << m_cInstance.get() << std::endl;
    }
};

template<typename T>
std::shared_ptr<T> CSingleTon<T>::m_cInstance = nullptr;



#endif // SINGLETON_H
