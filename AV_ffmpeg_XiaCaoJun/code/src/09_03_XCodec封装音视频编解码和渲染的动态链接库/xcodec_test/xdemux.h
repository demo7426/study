/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xdemux.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.29
描  述: 实现解封装
备  注:
修改记录:

  1.  日期: 2025.08.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#pragma once

#include "xformat.h"

class  CXDemux: public CXFormat
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
    /// 释放资源
    /// </summary>
    /// <param name=""></param>
    void Close(void) override;
};

