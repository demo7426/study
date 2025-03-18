/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	xsdl.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.03.18
��  ��: ʹ��SDL������Ⱦ
��  ע:
�޸ļ�¼:

  1.  ����: 2025.03.18
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

*************************************************/

#pragma once
#include "xvideo_view.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class CXSDL :public CXVideo_View
{
public:
    using CXVideo_View::CXVideo_View;

    /// <summary>
    /// ��ʼ������
    /// </summary>
    /// <param name="_Width">���ڿ��</param>
    /// <param name="_Height">���ڸ߶�</param>
    /// <param name="_Fmt">���Ƶ����ظ�ʽ</param>
    /// <param name="_pWinID">���ھ��;���Ϊ��,�����´���</param>
    /// <returns>true--�����ɹ�;false--����ʧ��</returns>
    bool Init(int _Width, int _Height, Format _Fmt = Format::RGBA, void* _pWinID = nullptr) override;

    /// <summary>
    /// ��Ⱦͼ��
    /// </summary>
    /// <param name="_pData">��Ⱦ�Ķ���������</param>
    /// <param name="_LineSize">һ�����ݵ��ֽ���������YUV420P����Yһ���ֽ�����_LineSize<=0���͸��߿�Ⱥ����ظ�ʽ�Զ������С</param>
    /// <returns>true--�����ɹ�;false--����ʧ��</returns>
    bool Draw(char* _pData, int _LineSize = 0) override;

    /// <summary>
    /// ��ǰ�����Ƿ��˳�
    /// </summary>
    /// <param name=""></param>
    /// <returns>true--�Ѿ��˳�;false--δ�˳�</returns>
    bool IsExit(void) override;

    /// <summary>
    /// �ͷ���Դ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Close(void) override;

private:
    SDL_Window* m_ptSDL_Window;                     //����
    SDL_Renderer* m_ptSDL_Renderer;                 //��Ⱦ��
    SDL_Texture* m_ptSDL_Texture;                   //����
};

