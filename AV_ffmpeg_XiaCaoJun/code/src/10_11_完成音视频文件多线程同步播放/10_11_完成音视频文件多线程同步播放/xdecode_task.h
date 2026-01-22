/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xdecode_task.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.16
描  述: 线程内部实现解码
备  注:
修改记录:

  1.  日期: 2025.12.16
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#pragma once

#include "xthread.h"
#include "xdecode.h"
#include "xavpacket_list.h"
#include "xlist.h"

class CXDecode_Task : public CXThread
{
public:
    CXDecode_Task() = default;
    ~CXDecode_Task();

    /// <summary>
    /// 打开解码
    /// </summary>
    /// <param name="_AVCodecID">数据编码后的格式</param>
    /// <param name="_IsEnable_HwDecode">是否使能硬件解码;false--不使能;true--使能;</param>
    /// <param name="_tAVCodecParameters"></param>
    /// <returns></returns>
    bool Open(int _AVCodecID, bool _IsEnable_HwDecode, AVCodecParameters _tAVCodecParameters);

    /// <summary>
    /// 执行下一步
    /// </summary>
    /// <param name=""></param>
    void DoNext(AVPacket* _ptAVPacket) override;

    /// <summary>
    /// 获取当前的AVFrame
    /// </summary>
    /// <param name=""></param>
    /// <returns>nullptr--暂时没有解码出AVFrame对象;</returns>
    AVFrame* GetCurAVFrame(void);

    void Close(void);

    inline CXDecode* GetCXDecode()
    {
        return &m_cXDeCode;
    }

private:
    void Main(void) override;

private:
    CXDecode m_cXDeCode;			        //解码对象

    CXAVPacket_List m_cXAVPacket_List;      //解码后的AVPacket数据

    CXList<AVFrame> m_cAVFrame_List;        //解码后的AVFrame数据
};


