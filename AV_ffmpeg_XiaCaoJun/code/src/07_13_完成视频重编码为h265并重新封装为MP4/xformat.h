/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	xformat.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.08.29
��  ��: ��װ�����װ����
��  ע:
�޸ļ�¼:

  1.  ����: 2025.08.29
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

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
    /// ������ʽ��I/O������
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
    /// �ͷ���Դ
    /// </summary>
    virtual void Close(void) = 0;

protected:
    /// <summary>
    /// �����ӡ
    /// </summary>
    /// <param name="_ErrCode">������</param>
    static void PrintErr(int _ErrCode);

    std::mutex m_mut;

    AVFormatContext* m_ptAVFormatContext = nullptr;
    AVStream* m_ptAVStream_Video = nullptr;						            //��Ƶ��
    AVStream* m_ptAVStream_Audio = nullptr;						            //��Ƶ��
};

