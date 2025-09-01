/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	xdemux.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.08.29
��  ��: ʵ�ֽ��װ
��  ע:
�޸ļ�¼:

  1.  ����: 2025.08.29
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

*************************************************/

#pragma once

#include "xformat.h"

class CXDemux: public CXFormat
{
public:
    using CXFormat::CXFormat;

    /// <summary>
    /// ����AVFormatContext��
    /// </summary>
    /// <param name="_pURL"></param>
    /// <returns></returns>
    int Create_AVFormatContext(const char* _pURL) override;

    /// <summary>
    /// ��ȡԭʼ��AVPacket����
    /// </summary>
    /// <param name="_pAVPacket"></param>
    /// <returns></returns>
    int Read_Frame(AVPacket* _pAVPacket);

    /// <summary>
    /// �ͷ���Դ
    /// </summary>
    /// <param name=""></param>
    void Close(void) override;
};

