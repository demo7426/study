/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xavpacket_list.cpp
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

#include <iostream>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/codec.h>
}

#include "xavpacket_list.h"
#include "xpublic.h"

CXAVPacket_List::CXAVPacket_List()
{
    //XPUBLIC_DEMUX_MAX_NODE_NUM 必须小于等于 XPUBLIC_LIST_MAX_NODE_NUM，不然会出现异常
    static_assert(XPUBLIC_LIST_MAX_NODE_NUM >= XPUBLIC_DEMUX_MAX_NODE_NUM || XPUBLIC_LIST_MAX_NODE_NUM >= XPUBLIC_ENCODE_MAX_NODE_NUM,
        "相关的常量设置错误");        
}

AVPacket* CXAVPacket_List::Pop(void)
{
    std::unique_lock<std::mutex> lock(m_cMut);

    if(m_listAVPacket.empty())
        return nullptr;

    auto ptAVPacket = m_listAVPacket.front();

    m_listAVPacket.pop_front();

    return ptAVPacket;
}

void CXAVPacket_List::Push(AVPacket* _ptAVPacket)
{
    std::unique_lock<std::mutex> lock(m_cMut);

    auto ptAVPacket = av_packet_alloc();            //生成新的 AVPacket 对象，引用计数 +1

    av_packet_ref(ptAVPacket, _ptAVPacket);         //引用计数 减少数据赋值，线程安全

    m_listAVPacket.push_back(ptAVPacket);

    //超出最大空间，清理数据直到关键帧位置
    if (m_listAVPacket.size() > XPUBLIC_LIST_MAX_NODE_NUM)
    {
        //处理关键帧
        if (m_listAVPacket.front()->flags & AV_PKT_FLAG_KEY)     
        {
            av_packet_free(&m_listAVPacket.front());
            m_listAVPacket.pop_front();
        }

        //清理所有非关键帧之前的数据
        while (!m_listAVPacket.empty())                             
        {
            if (m_listAVPacket.front()->flags & AV_PKT_FLAG_KEY)
                return;

            av_packet_free(&m_listAVPacket.front());
            m_listAVPacket.pop_front();
        }
    }
}
