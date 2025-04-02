/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xsdl.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.22
描  述: 使用SDL进行渲染
备  注:
修改记录:

  1.  日期: 2025.03.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <iostream>
#include <mutex>

#include "xsdl.h"

#pragma comment(lib, "SDL2.lib")
#undef main

using namespace std;

bool CXSDL::Init(int _Width, int _Height, Format _Fmt, void* _pWinID)
{
    unique_lock<mutex> lock(m_mutex);

    if (_Width <= 0 || _Height <= 0)
        return false;

    m_nWidth = _Width;
    m_nHeight = _Height;
    m_eFmt = _Fmt;

    static char chRet = 0;      //保证只初始化一次

    //初始化SDL video库；设置缩放算法，解决锯齿问题
    if (chRet == 0 && SDL_Init(SDL_INIT_VIDEO) && SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        cout << SDL_GetError() << endl;
        return false;
    }

    chRet = 1;

    //指定SDL窗口
    if (!m_ptSDL_Window)                                    //防止反复创建窗口
    {
        if (_pWinID)
        {
            m_ptSDL_Window = SDL_CreateWindowFrom(_pWinID);
            if (!m_ptSDL_Window)
            {
                cout << SDL_GetError() << endl;
                return false;
            }
        }
        else
        {
            m_ptSDL_Window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _Width, _Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
            if (!m_ptSDL_Window)
            {
                cout << SDL_GetError() << endl;
                return false;
            }
        }
    }

    if (m_ptSDL_Texture)
    {
        SDL_DestroyTexture(m_ptSDL_Texture);
        m_ptSDL_Texture = nullptr;
    }

    if (m_ptSDL_Renderer)
    {
        SDL_DestroyRenderer(m_ptSDL_Renderer);
        m_ptSDL_Renderer = nullptr;
    }

    //生成渲染器,使用硬件加速
    m_ptSDL_Renderer = SDL_CreateRenderer(m_ptSDL_Window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_ptSDL_Renderer)
    {
        cout << SDL_GetError() << endl;
        return false;
    }

    //生成材质
    m_ptSDL_Texture = SDL_CreateTexture(m_ptSDL_Renderer, (Uint32)_Fmt, SDL_TEXTUREACCESS_STREAMING, _Width, _Height);
    if (!m_ptSDL_Texture)
    {
        cout << SDL_GetError() << endl;
        return false;
    }

    return false;
}

bool CXSDL::Draw(char* _pData, int _LineSize)
{
    unique_lock<mutex> lock(m_mutex);

    if (!m_ptSDL_Texture)
        return false;

    if (_LineSize == 0)
    {
        switch (m_eFmt)
        {
        case CXVideo_View::Format::ARGB:
        case CXVideo_View::Format::RGBA:
        case CXVideo_View::Format::ABGR:
        case CXVideo_View::Format::BGRA:
            _LineSize = m_nWidth * 4;
            break;
        case CXVideo_View::Format::YUV420P:
            _LineSize = m_nWidth;
            break;
        default:
            break;
        }
    }

    //将图像数据写入材质
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, _pData, _LineSize);

    //清理屏幕
    SDL_RenderClear(m_ptSDL_Renderer);

    SDL_Rect tSDL_Rect;
    SDL_Rect* ptSDL_Rect = nullptr;         //如果为空，则跟随m_ptSDL_Renderer变化
    
    if (m_nScale_Width > 0)                 //用户手动设置缩放
    {
        tSDL_Rect.x = 0;
        tSDL_Rect.y = 0;
        tSDL_Rect.w = m_nScale_Width;
        tSDL_Rect.h = m_nScale_Height;

        ptSDL_Rect = &tSDL_Rect;
    }

    //复制材质到渲染
    SDL_RenderCopy(m_ptSDL_Renderer, m_ptSDL_Texture, NULL, ptSDL_Rect);

    //渲染
    SDL_RenderPresent(m_ptSDL_Renderer);

    return false;
}

bool CXSDL::Draw(char* _Yplane, int _Ypitch, char* _Uplane, int _Upitch, char* _Vplane, int _Vpitch)
{
    unique_lock<mutex> lock(m_mutex);

    if (!m_ptSDL_Texture)
        return false;

    //将图像数据写入材质
    SDL_UpdateYUVTexture(m_ptSDL_Texture, NULL, (const Uint8*)_Yplane, _Ypitch, (const Uint8*)_Uplane, _Upitch, (const Uint8*)_Vplane, _Vpitch);

    //清理屏幕
    SDL_RenderClear(m_ptSDL_Renderer);

    SDL_Rect tSDL_Rect;
    SDL_Rect* ptSDL_Rect = nullptr;         //如果为空，则跟随m_ptSDL_Renderer变化

    if (m_nScale_Width > 0)                 //用户手动设置缩放
    {
        tSDL_Rect.x = 0;
        tSDL_Rect.y = 0;
        tSDL_Rect.w = m_nScale_Width;
        tSDL_Rect.h = m_nScale_Height;

        ptSDL_Rect = &tSDL_Rect;
    }

    //复制材质到渲染
    SDL_RenderCopy(m_ptSDL_Renderer, m_ptSDL_Texture, NULL, ptSDL_Rect);

    //渲染
    SDL_RenderPresent(m_ptSDL_Renderer);

    return false;
}

bool CXSDL::IsExit(void)
{
    SDL_Event uSDL_Event;

    SDL_WaitEventTimeout(&uSDL_Event, 1);

    if (uSDL_Event.type == SDL_QUIT)
        return true;

    return false;
}

bool CXSDL::Close(void)
{
    if (m_ptSDL_Texture)
    {
        SDL_DestroyTexture(m_ptSDL_Texture);
        m_ptSDL_Texture = nullptr;
    }

    if (m_ptSDL_Renderer)
    {
        SDL_DestroyRenderer(m_ptSDL_Renderer);
        m_ptSDL_Renderer = nullptr;
    }

    if (m_ptSDL_Window)
    {
        SDL_DestroyWindow(m_ptSDL_Window);
        m_ptSDL_Window = nullptr;
    }

    if (m_ptAVFrame)
    {
        av_frame_free(&m_ptAVFrame);
        m_ptAVFrame = nullptr;
    }

    if (m_cIfstream.is_open())
        m_cIfstream.close();

    return false;
}
