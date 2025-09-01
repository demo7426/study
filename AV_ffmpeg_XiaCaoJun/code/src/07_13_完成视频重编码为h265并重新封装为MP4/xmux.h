/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	xmux.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.08.29
��  ��: ʵ�ַ�װ
��  ע:
�޸ļ�¼:

  1.  ����: 2025.08.29
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

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
    /// ������Ƶ��ȡ�Ŀ�ʼʱ��
    /// </summary>
    /// <param name="_Sec"></param>
    inline void SetBeginSec(double _Sec)
    {
        m_dbBeginSec = _Sec;
    }

    /// <summary>
    /// ������Ƶ��ȡ�Ľ���ʱ��
    /// </summary>
    /// <param name="_Sec"></param>
    inline void SetEndSec(double _Sec)
    {
        m_dbEndSec = _Sec;  
    }

    /// <summary>
    /// ������Ƶ������������
    /// </summary>
    /// <param name="_pAVRational">�����ʱ��Ļ�����λ</param>
    /// <param name="_pAVCodecParameters">����󣬽������</param>
    /// <returns></returns>
    int SetVideoParameters(const AVRational* _pAVRational, const AVCodecParameters* _pAVCodecParameters);
    
    /// <summary>
    /// ������Ƶ������������
    /// </summary>
    /// <param name="_pAVRational">�����ʱ��Ļ�����λ</param>
    /// <param name="_pAVCodecParameters">����󣬽������</param>
    /// <returns></returns>
    int SetAudioParameters(const AVRational* _pAVRational, const AVCodecParameters* _pAVCodecParameters);

    /// <summary>
    /// ���ñ�������ʽ
    /// </summary>
    /// <param name="_pAVRational"></param>
    /// <param name="codec"></param>
    /// <returns></returns>
    int Set_EncodeFormat(const AVRational* _pAVRational, const AVCodecContext* codec);

    /// <summary>
    /// д��ͷ
    /// </summary>
    /// <param name="_pAVFormatContext">����󣬸�ʽ��I/O������</param>
    /// <param name="_pAVStream_Video">�������Ƶ��</param>
    /// <param name="_pAVStream_Audio">�������Ƶ��</param>
    /// <returns></returns>
    int Write_Header(AVFormatContext* _pAVFormatContext, AVStream* _pAVStream_Video, AVStream* _pAVStream_Audio);

    /// <summary>
    /// ����ʱ��
    /// </summary>
    /// <param name="_pAVPacket"></param>
    /// <returns></returns>
    int RescaleTime(AVPacket* _pAVPacket);

    /// <summary>
    /// д������
    /// </summary>
    /// <param name="_pAVPacket">�����ԭʼ����</param>
    /// <returns>-2--ʧ��;0--�ɹ�;</returns>
    int Write_Frame(AVPacket* _pAVPacket);

    /// <summary>
    /// д���ļ�β�����ͷ���Դ
    /// </summary>
    void Close(void) override;

private:
    const char* m_pchURL;

    double m_dbBeginSec = 0;							//��ȡ��ʼʱ��
    double m_dbEndSec = DBL_MAX;					    //��ȡ����ʱ��

    long long m_llBegin_Video_Pts = 0;								//��Ƶ��ʼ��ʱ��
    long long m_llEnd_Video_Pts = 0;									//��Ƶ������ʱ��	
    long long m_llBegin_Audio_Pts = 0;								//��Ƶ��ʼ��ʱ��
    long long m_llEnd_Audio_Pts = 0;									//��Ƶ������ʱ��	


    AVFormatContext* m_ptAVFormatContext_Demux = nullptr;
    AVStream* m_ptAVStream_Video_Demux = nullptr;						            //��Ƶ��
    AVStream* m_ptAVStream_Audio_Demux = nullptr;						            //��Ƶ��
};

