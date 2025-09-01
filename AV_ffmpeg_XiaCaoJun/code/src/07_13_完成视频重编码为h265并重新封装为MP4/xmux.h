/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xmux.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.29
描  述: 实现封装
备  注:
修改记录:

  1.  日期: 2025.08.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#pragma once

#include <format>

#include "xformat.h"

class CXMux: public CXFormat
{
public:
    using CXFormat::CXFormat;

    int Create_AVFormatContext(const char* _pURL) override;

    /// <summary>
    /// 设置视频截取的开始时间
    /// </summary>
    /// <param name="_Sec"></param>
    inline void SetBeginSec(double _Sec)
    {
        m_dbBeginSec = _Sec;
    }

    /// <summary>
    /// 设置视频截取的结束时间
    /// </summary>
    /// <param name="_Sec"></param>
    inline void SetEndSec(double _Sec)
    {
        m_dbEndSec = _Sec;  
    }

    /// <summary>
    /// 设置视频流编码器参数
    /// </summary>
    /// <param name="_pAVRational">解码后，时间的基本单位</param>
    /// <param name="_pAVCodecParameters">解码后，解码参数</param>
    /// <returns></returns>
    int SetVideoParameters(const AVRational* _pAVRational, const AVCodecParameters* _pAVCodecParameters);
    
    /// <summary>
    /// 设置音频流编码器参数
    /// </summary>
    /// <param name="_pAVRational">解码后，时间的基本单位</param>
    /// <param name="_pAVCodecParameters">解码后，解码参数</param>
    /// <returns></returns>
    int SetAudioParameters(const AVRational* _pAVRational, const AVCodecParameters* _pAVCodecParameters);

    /// <summary>
    /// 设置编码器格式
    /// </summary>
    /// <param name="_pAVRational"></param>
    /// <param name="codec"></param>
    /// <returns></returns>
    int Set_EncodeFormat(const AVRational* _pAVRational, const AVCodecContext* codec);

    /// <summary>
    /// 写入头
    /// </summary>
    /// <param name="_pAVFormatContext">解码后，格式化I/O上下文</param>
    /// <param name="_pAVStream_Video">解码后，视频流</param>
    /// <param name="_pAVStream_Audio">解码后，音频流</param>
    /// <returns></returns>
    int Write_Header(AVFormatContext* _pAVFormatContext, AVStream* _pAVStream_Video, AVStream* _pAVStream_Audio);

    /// <summary>
    /// 缩放时间
    /// </summary>
    /// <param name="_pAVPacket"></param>
    /// <returns></returns>
    int RescaleTime(AVPacket* _pAVPacket);

    /// <summary>
    /// 写入数据
    /// </summary>
    /// <param name="_pAVPacket">解码后，原始数据</param>
    /// <returns>-2--失败;0--成功;</returns>
    int Write_Frame(AVPacket* _pAVPacket);

    /// <summary>
    /// 写入文件尾，并释放资源
    /// </summary>
    void Close(void) override;

private:
    const char* m_pchURL;

    double m_dbBeginSec = 0;							//截取开始时间
    double m_dbEndSec = DBL_MAX;					    //截取结束时间

    long long m_llBegin_Video_Pts = 0;								//视频开始的时间
    long long m_llEnd_Video_Pts = 0;									//视频结束的时间	
    long long m_llBegin_Audio_Pts = 0;								//音频开始的时间
    long long m_llEnd_Audio_Pts = 0;									//视频结束的时间	


    AVFormatContext* m_ptAVFormatContext_Demux = nullptr;
    AVStream* m_ptAVStream_Video_Demux = nullptr;						            //视频流
    AVStream* m_ptAVStream_Audio_Demux = nullptr;						            //音频流
};

