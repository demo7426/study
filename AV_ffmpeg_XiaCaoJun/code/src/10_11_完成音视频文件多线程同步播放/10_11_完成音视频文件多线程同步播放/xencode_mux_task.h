/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xencode_mux_task.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.01.17
描  述: 线程内部实现重编码和封装
备  注:
修改记录:

  1.  日期: 2026.01.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#pragma once

#include <mutex>
#include <condition_variable>

#include "xthread.h"
#include "xdemux.h"
#include "xmux.h"
#include "xencode.h"
#include "xdecode.h"
#include "xavpacket_list.h"
#include "xlist.h"

class CXEncode_Mux_Task : public CXThread
{
public:
    CXEncode_Mux_Task() = default;
    ~CXEncode_Mux_Task();

    /// <summary>
    /// 打开编码器、封装器
    /// </summary>
    /// <param name="_AVCodecID">编码格式</param>
    /// <param name="_pOutURL">封装输出文件路径</param>
    /// <param name="_pcXDemux"></param>
    /// <param name="_pcXDecode"></param>
    /// <returns>true--成功;false--失败</returns>
    bool Open(int _AVCodecID, const char* _pOutURL, CXDemux* _pcXDemux, CXDecode* _pcXDecode);

    int Send_AVFrame(AVFrame* _ptAVFrame);

private:
    void Main(void) override;

private:
    CXEncode m_cXEnCode;			        //编码器对象
    CXMux m_cXMux;				            //封装对象

    CXAVPacket_List m_cXAVPacket_List;      //编码后的AVPacket数据

    CXList<AVFrame> m_cAVFrame_List;        //待编码的AVFrame数据

    std::mutex m_mut;
    std::condition_variable m_cond;
};


