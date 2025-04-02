/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	sdl_qt_rgb.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.04.02
��  ��: ʹ��SDL��Qt�Ľ�����,������·AVFrame��YUV��RGBA����Ƶ�ļ������ҿ���֡��
��  ע: ֡�ʿ���ʹ�õ��� QElapsedTimer �����ʱ����������ʹ�� clock ���ʱ�侫�Ⱦ�ȷ����֡�ʣ����߶��̷߳����źž�ȷ����֡��
        
        cmd�ն�ִ������ָ��
            ffmpeg lu_fei.mp4 -s 400x300 lu_fei_400x300_30.yuv                      //�������� yuv ��ʽ���ļ�
            ffmpeg lu_fei.mp4 -s 800x400 -pix_fmt rgba lu_fei_800x400_30.rgb        //�������� rgba ��ʽ���ļ�
�޸ļ�¼:

  1.  ����: 2025.04.02
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
#include <qelapsedtimer.h>

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

    int m_nWidth[2] = { 400, 800 };                 //���ڵĿ�
    int m_nHeight[2] = { 300, 400 };                //���ڵĸ�
    qint32 m_nPixSize = 4;                          //���ص��С

    quint64  m_ullFilePathSize = 0;                 //�ļ���С����λByte

    CXVideo_View* m_pcXVideo_View[2] = { nullptr, nullptr };

    std::thread m_cTh01;
    bool m_bIsQuitThread = false;                   //�Ƿ��˳��߳�

    QLabel* m_pcLabel[2] = { nullptr, nullptr };    //������ʾfps֡��

    qint32 m_nRatedFps[2] = { 30, 30 };             //�֡��

    QElapsedTimer m_cElapsedTimer[2];
};
