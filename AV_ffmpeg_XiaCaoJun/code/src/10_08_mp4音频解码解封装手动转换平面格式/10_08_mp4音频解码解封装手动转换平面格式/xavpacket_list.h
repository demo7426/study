/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xavpacket_list.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.16
描  述: 实现一个线程安全的avpacket链表
备  注:
修改记录:

  1.  日期: 2025.12.16
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#pragma once

#include <mutex>
#include <list>

struct AVPacket;

class CXAVPacket_List
{
public:
    CXAVPacket_List() = default;
	~CXAVPacket_List() = default;
    
    AVPacket* Pop(void);

    void Push(AVPacket* _ptAVPacket);

private:
    std::mutex m_cMut;

    std::list<AVPacket*> m_listAVPacket;

    static constexpr int m_nListMaxNodeNum = 4096;  //链表能存储的最大节点数量
};
