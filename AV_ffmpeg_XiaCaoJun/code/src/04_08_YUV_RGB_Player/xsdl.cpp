/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	xsdl.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.03.22
��  ��: ʹ��SDL������Ⱦ
��  ע:
�޸ļ�¼:

  1.  ����: 2025.03.22
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

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

    static char chRet = 0;      //��ֻ֤��ʼ��һ��

    //��ʼ��SDL video�⣻���������㷨������������
    if (chRet == 0 && SDL_Init(SDL_INIT_VIDEO) && SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        cout << SDL_GetError() << endl;
        return false;
    }

    chRet = 1;

    //ָ��SDL����
    if (!m_ptSDL_Window)                                    //��ֹ������������
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

    //������Ⱦ��,ʹ��Ӳ������
    m_ptSDL_Renderer = SDL_CreateRenderer(m_ptSDL_Window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_ptSDL_Renderer)
    {
        cout << SDL_GetError() << endl;
        return false;
    }

    //���ɲ���
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

    //��ͼ������д�����
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, _pData, _LineSize);

    //������Ļ
    SDL_RenderClear(m_ptSDL_Renderer);

    SDL_Rect tSDL_Rect;
    SDL_Rect* ptSDL_Rect = nullptr;         //���Ϊ�գ������m_ptSDL_Renderer�仯
    
    if (m_nScale_Width > 0)                 //�û��ֶ���������
    {
        tSDL_Rect.x = 0;
        tSDL_Rect.y = 0;
        tSDL_Rect.w = m_nScale_Width;
        tSDL_Rect.h = m_nScale_Height;

        ptSDL_Rect = &tSDL_Rect;
    }

    //���Ʋ��ʵ���Ⱦ
    SDL_RenderCopy(m_ptSDL_Renderer, m_ptSDL_Texture, NULL, ptSDL_Rect);

    //��Ⱦ
    SDL_RenderPresent(m_ptSDL_Renderer);

    return false;
}

bool CXSDL::Draw(char* _Yplane, int _Ypitch, char* _Uplane, int _Upitch, char* _Vplane, int _Vpitch)
{
    unique_lock<mutex> lock(m_mutex);

    if (!m_ptSDL_Texture)
        return false;

    //��ͼ������д�����
    SDL_UpdateYUVTexture(m_ptSDL_Texture, NULL, (const Uint8*)_Yplane, _Ypitch, (const Uint8*)_Uplane, _Upitch, (const Uint8*)_Vplane, _Vpitch);

    //������Ļ
    SDL_RenderClear(m_ptSDL_Renderer);

    SDL_Rect tSDL_Rect;
    SDL_Rect* ptSDL_Rect = nullptr;         //���Ϊ�գ������m_ptSDL_Renderer�仯

    if (m_nScale_Width > 0)                 //�û��ֶ���������
    {
        tSDL_Rect.x = 0;
        tSDL_Rect.y = 0;
        tSDL_Rect.w = m_nScale_Width;
        tSDL_Rect.h = m_nScale_Height;

        ptSDL_Rect = &tSDL_Rect;
    }

    //���Ʋ��ʵ���Ⱦ
    SDL_RenderCopy(m_ptSDL_Renderer, m_ptSDL_Texture, NULL, ptSDL_Rect);

    //��Ⱦ
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
