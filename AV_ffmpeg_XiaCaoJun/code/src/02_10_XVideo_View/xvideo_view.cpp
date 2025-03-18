/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	xvideo_view.cpp
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

#include <mutex>

#include "xvideo_view.h"
#include "xsdl.h"

using namespace std;

CXVideo_View* CXVideo_View::Create(RenderType _RenderType)
{
    if (_RenderType == RenderType::SDL)
        return new CXSDL();

    return nullptr;
}

bool CXVideo_View::SetScale(int _Width, int _Height)
{
    unique_lock<mutex> lock(m_mutex);

    m_nScale_Width = _Width;
    m_nScale_Height = _Height;

    return false;
}
