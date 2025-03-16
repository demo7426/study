/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	sdl_qt_rgb.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.03.16
��  ��: ʹ��SDL��Qt�Ľ����ϲ���YUV��Ƶ�ļ�
��  ע:
�޸ļ�¼:

  1.  ����: 2025.03.16
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

*************************************************/

#pragma once

#include <QtWidgets/QWidget>
#include <fstream>

#include "ui_sdl_qt_rgb.h"

#include "sdl/SDL.h"

#pragma comment(lib, "SDL2.lib")
#undef main

class SDL_Qt_RGB : public QWidget
{
    Q_OBJECT

public:
    SDL_Qt_RGB(QWidget *parent = nullptr);
    ~SDL_Qt_RGB();

    /// <summary>
    /// ��ʼ��ui����
    /// </summary>
    /// <param name=""></param>
    void InitUi(void);

protected:
    void timerEvent(QTimerEvent* e) override;

private:
    Ui::SDL_Qt_RGBClass ui;

    int m_nWidth = 1280;                            //���ڵĿ�
    int m_nHeight = 720;                            //���ڵĸ�
    qint32 m_nPixSize = 2;                          //���ص��С
    quint8* m_puchYUV = nullptr;                    //ͼ���ڲ�ARGB����

    SDL_Window* m_ptSDL_Window;                     //����
    SDL_Renderer* m_ptSDL_Renderer;                 //��Ⱦ��
    SDL_Texture* m_ptSDL_Texture;                   //����

    std::ifstream m_pcIfstream;
};
