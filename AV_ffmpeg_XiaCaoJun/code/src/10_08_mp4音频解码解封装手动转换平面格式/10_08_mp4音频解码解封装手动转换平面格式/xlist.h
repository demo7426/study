/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xlist.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.17
描  述: 实现一个线程安全的链表
备  注:
修改记录:

  1.  日期: 2025.01.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/


#pragma once

#include <mutex>
#include <list>

template<class T>
class CXList
{
public:
    CXList() = default;
	~CXList() = default;
    
    T* Pop(void)
    {
        std::unique_lock<std::mutex> lock(m_cMut);

        if (m_list.empty())
            return nullptr;

        auto ptAVPacket = m_list.front();

        m_list.pop_front();

        return ptAVPacket;
    }

    void Push(T* _ptAVPacket)
    {
        std::unique_lock<std::mutex> lock(m_cMut);

        m_list.push_back(_ptAVPacket);

        //超出最大空间，清理数据
        if (m_list.size() > m_nListMaxNodeNum)
        {
            m_list.pop_front();
        }
    }

private:
    std::mutex m_cMut;

    std::list<T*> m_list;

    static constexpr int m_nListMaxNodeNum = 4096;  //链表能存储的最大节点数量
};

