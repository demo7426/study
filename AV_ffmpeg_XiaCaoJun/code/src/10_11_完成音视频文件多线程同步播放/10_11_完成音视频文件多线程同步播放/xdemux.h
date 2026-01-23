/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xdemux.h
作  者:	钱锐      版本: V0.1.1     新建日期: 2025.08.29
描  述: 实现解封装
备  注:
修改记录:

  1.  日期: 2025.08.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

  2.  日期: 2026.01.20
      作者: 钱锐
      内容:
          1) 新增 GetVideoId、GetAudioId 函数接口，保证使用流id索引时的正确性;
      版本:V0.1.1

*************************************************/

#pragma once

#include "xformat.h"

class CXDemux: public CXFormat
{
public:
    using CXFormat::CXFormat;

    /// <summary>
    /// 创建AVFormatContext等
    /// </summary>
    /// <param name="_pURL"></param>
    /// <returns></returns>
    int Create_AVFormatContext(const char* _pURL) override;

    /// <summary>
    /// 读取原始的AVPacket数据
    /// </summary>
    /// <param name="_pAVPacket"></param>
    /// <returns></returns>
    int Read_Frame(AVPacket* _pAVPacket);

    /// <summary>
    /// 获取视频流id
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    inline int GetVideoId(void)
    {
        return m_nVideoId;
    }

    /// <summary>
    /// 获取音频流id
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    inline int GetAudioId(void)
    {
        return m_nAudioId;
    }

    /// <summary>
    /// 设置当前播放的时间戳
    /// </summary>
    /// <param name="">时间戳;单位:us</param>
    /// <returns></returns>
    int SetCurPlayTimestamp(long long _Timestamp);

    /// <summary>
    /// 释放资源
    /// </summary>
    /// <param name=""></param>
    void Close(void) override;

private:
    int m_nVideoId = 0;             //视频流id
    int m_nAudioId = 0;             //音频流id

};

