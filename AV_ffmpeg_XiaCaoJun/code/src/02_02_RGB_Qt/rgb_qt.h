/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	rgb_qt.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.12
描  述: 编写使用RGB_Qt控制颜色显示的demo
备  注:
修改记录:

  1.  日期: 2025.03.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

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
    constexpr static qint32 m_nWidth = 1280;       //宽度
    constexpr static qint32 m_nHeight = 720;       //高度

    Ui::RGB_QtClass ui;
};
