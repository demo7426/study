/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	xvideo_view.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.03.18
��  ��: ʵ��һ�������֧࣬��ͼ�����Ⱦ
��  ע: ���еĽӿھ�֧���̰߳�ȫ
�޸ļ�¼:

  1.  ����: 2025.03.18
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

*************************************************/

#pragma once

#include <mutex>

class CXVideo_View
{
protected:
    CXVideo_View() = default;

public:
    enum class Format:char          //���ظ�ʽ
    {
        RGBA = 1,
        ARGB,
        YUV420P
    };

    enum class RenderType :char     //��Ⱦ����
    {
        SDL = 1
    };

	~CXVideo_View() = default;

    /// <summary>
    /// ����һ���µ������
    /// </summary>
    /// <param name="_RenderType"></param>
    /// <returns></returns>
    static CXVideo_View* Create(RenderType _RenderType = RenderType::SDL);

    /// <summary>
    /// ��ʼ������
    /// </summary>
    /// <param name="_Width">���ڿ��</param>
    /// <param name="_Height">���ڸ߶�</param>
    /// <param name="_Fmt">���Ƶ����ظ�ʽ</param>
    /// <param name="_pWinID">���ھ��;���Ϊ��,�����´���</param>
    /// <returns>true--�����ɹ�;false--����ʧ��</returns>
    virtual bool Init(int _Width, int _Height, Format _Fmt = Format::RGBA, void* _pWinID = nullptr) = 0;
         
    /// <summary>
    /// ��Ⱦͼ��
    /// </summary>
    /// <param name="_pData">��Ⱦ�Ķ���������</param>
    /// <param name="_LineSize">һ�����ݵ��ֽ���������YUV420P����Yһ���ֽ�����_LineSize<=0���͸��߿�Ⱥ����ظ�ʽ�Զ������С</param>
    /// <returns>true--�����ɹ�;false--����ʧ��</returns>
    virtual bool Draw(char* _pData, int _LineSize = 0) = 0;

    /// <summary>
    /// �������ô�����ʾ��С
    /// </summary>
    /// <param name="_Width"></param>
    /// <param name="_Height"></param>
    /// <returns></returns>
    bool SetScale(int _Width, int _Height);

    /// <summary>
    /// ��ǰ�����Ƿ��˳�
    /// </summary>
    /// <param name=""></param>
    /// <returns>true--�Ѿ��˳�;false--δ�˳�</returns>
    virtual bool IsExit(void) = 0;

    /// <summary>
    /// �ͷ���Դ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Close(void) = 0;

protected:
    int m_nWidth = 0;                       //ͼ����
    int m_nHeight = 0;                      //ͼ��߶�
    Format m_eFmt = Format::RGBA;           //���Ƶ����ظ�ʽ
    std::mutex m_mutex;                     //������������ȷ���ӿ��߳��ڲ���ȫ

    int m_nScale_Width = 0;                 //������ʾ���
    int m_nScale_Height = 0;                //������ʾ�߶�
};


