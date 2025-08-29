/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xformat.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.29
描  述: 封装、解封装基类
备  注:
修改记录:

  1.  日期: 2025.08.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#pragma once

#include <mutex>

struct AVFormatContext;
struct AVPacket;
struct AVStream;
struct AVFrame;
struct AVRational;

class CXFormat
{
public:
    CXFormat() = default;
    virtual~CXFormat() = 0;

    /// <summary>
    /// 创建格式化I/O上下文
    /// </summary>
    /// <param name="_pURL"></param>
    /// <returns></returns>
    virtual int Create_AVFormatContext(const char* _pURL) = 0;

    inline AVFormatContext* GetAVFormatContext(void)
    {
        std::unique_lock<std::mutex> lock(m_mut);

        return m_ptAVFormatContext;
    }

    inline AVStream* GetAVStream_Video(void)
    {
        std::unique_lock<std::mutex> lock(m_mut);

        return m_ptAVStream_Video;
    }
    
    inline AVStream* GetAVStream_Audio(void)
    {
        std::unique_lock<std::mutex> lock(m_mut);

        return m_ptAVStream_Audio;
    }

    /// <summary>
    /// 释放资源
    /// </summary>
    virtual void Close(void) = 0;

protected:
    /// <summary>
    /// 错误打印
    /// </summary>
    /// <param name="_ErrCode">错误码</param>
    static void PrintErr(int _ErrCode);

    std::mutex m_mut;

    AVFormatContext* m_ptAVFormatContext = nullptr;
    AVStream* m_ptAVStream_Video = nullptr;						            //视频流
    AVStream* m_ptAVStream_Audio = nullptr;						            //音频流
};

