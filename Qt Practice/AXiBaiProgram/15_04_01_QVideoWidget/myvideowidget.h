/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	myvideowidget.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.05
描  述:	自定义QVideoWidget子类
备  注:	推荐使用Qt5进行编译
修改记录:

  1.  日期: 2024.11.05
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef CMYVIDEOWIDGET_H
#define CMYVIDEOWIDGET_H

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>

class CMyVideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit CMyVideoWidget(QWidget *parent = nullptr);

    void SetMediaPlayer(QMediaPlayer *_pMediaPlayer);

protected:

    void keyPressEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private:
    QMediaPlayer *m_pcMediaPlayer = nullptr;
signals:

};

#endif // CMYVIDEOWIDGET_H
