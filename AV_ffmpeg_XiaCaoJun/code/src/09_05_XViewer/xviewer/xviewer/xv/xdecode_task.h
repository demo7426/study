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

class CXEncode;
class CXMux;

class CXDecode_Task : public CXThread
{
public:
    CXDecode_Task() = default;
    ~CXDecode_Task() = default;

    /// <summary>
    /// 打开解码
    /// </summary>
    /// <param name="_AVCodecID">数据编码后的格式</param>
    /// <param name="_IsEnable_HwDecode">是否使能硬件解码;false--不使能;true--使能;</param>
    /// <param name="_tAVCodecParameters"></param>
    /// <returns></returns>
    bool Open(int _AVCodecID, bool _IsEnable_HwDecode, AVCodecParameters _tAVCodecParameters);

    /// <summary>
    /// 设置编码、封装对象
    /// </summary>
    /// <param name="_pcXEncode"></param>
    /// <param name="_pcXMux"></param>
    void SetXEncode_XMux(CXEncode* _pcXEncode, CXMux* _pcXMux);

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

    enum AVPixelFormat GetAVPixelFormat(void);

private:
    void Main(void) override;

private:
    CXDeCode m_cXDeCode;			//解码对象

    CXAVPacket_List m_cXAVPacket_List;

    AVFrame* m_ptAVFrame = nullptr;

    bool m_bAVFrameIsValid = false;     //AVFrame 是否有效

    std::mutex m_cMutAVFrame;

    CXEncode* m_pcXEncode = nullptr;
    CXMux* m_pcXMux = nullptr;
};


