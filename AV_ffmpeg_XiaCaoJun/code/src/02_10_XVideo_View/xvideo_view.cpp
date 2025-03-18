/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xvideo_view.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.18
描  述: 实现一个抽象类，支持图像的渲染
备  注: 所有的接口均支持线程安全
修改记录:

  1.  日期: 2025.03.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

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
