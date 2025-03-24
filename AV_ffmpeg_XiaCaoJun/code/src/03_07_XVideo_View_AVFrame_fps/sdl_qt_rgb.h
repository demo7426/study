/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	sdl_qt_rgb.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.03.25
��  ��: ʹ��SDL��Qt�Ľ�����,����AVFrame��YUV��Ƶ�ļ������ҿ���֡��
��  ע:
�޸ļ�¼:

  1.  ����: 2025.03.25
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

*************************************************/

#pragma once

#include <QtWidgets/QWidget>
#include <fstream>
#include <thread>
#include <qspinbox.h>

#include "ui_sdl_qt_rgb.h"

#include "xvideo_view.h"

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

    /// <summary>
    /// ��ʼ���źŲ�
    /// </summary>
    /// <param name=""></param>
    void InitSignalSlots(void);

protected:
    void timerEvent(QTimerEvent* e) override;

    void resizeEvent(QResizeEvent* event) override;

signals:
    void SendViews(void);

private:
    /// <summary>
    /// ��ȡ���ݣ�����ˢ�µ�xvideo_viewģ��
    /// </summary>
    /// <param name=""></param>
    void View(void);

    /// <summary>
    /// �߳�������
    /// </summary>
    /// <param name=""></param>
    void RunThread(void);

private:
    Ui::SDL_Qt_RGBClass ui;

    int m_nWidth = 1280;                            //���ڵĿ�
    int m_nHeight = 720;                            //���ڵĸ�
    qint32 m_nPixSize = 4;                          //���ص��С
    AVFrame* m_ptAVFrame = nullptr;

    constexpr static const char* m_pchFilePath = "../../src/03_07_XVideo_View_AVFrame_fps/1.yuv";
    quint64  m_ullFilePathSize = 0;                 //�ļ���С����λByte
    std::ifstream m_pcIfstream;

    CXVideo_View* m_pcXVideo_View = nullptr;

    std::thread m_cTh01;
    bool m_bIsQuitThread = false;                   //�Ƿ��˳��߳�

    QLabel* m_pcLabel = nullptr;                    //������ʾfps֡��
    QSpinBox* m_pcSpinBox = nullptr;                //����������ʾfps֡��

    qint32 m_nRatedFps = 25;                        //�֡��
};
