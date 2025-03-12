/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	rgb_qt.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.03.12
��  ��: ��дʹ��RGB_Qt������ɫ��ʾ��demo
��  ע:
�޸ļ�¼:

  1.  ����: 2025.03.12
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

*************************************************/

#pragma once

#include <QtWidgets/QWidget>
#include "ui_rgb_qt.h"

class RGB_Qt : public QWidget
{
    Q_OBJECT

public:
    RGB_Qt(QWidget *parent = nullptr);
    ~RGB_Qt();

protected:
    void paintEvent(QPaintEvent* e) override;

private:
    constexpr static qint32 m_nWidth = 1280;       //���
    constexpr static qint32 m_nHeight = 720;       //�߶�

    Ui::RGB_QtClass ui;
};
