/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.05
描  述:	使用QVideoWidget实现视频的播放
备  注:	推荐使用Qt5进行编译
修改记录:

  1.  日期: 2024.11.05
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sliderVolumn_valueChanged(int value);

    void on_btnSound_clicked();

    void on_pushButton_clicked();

    void on_sliderPosition_valueChanged(int value);

private:
    QMediaPlayer *m_pcMediaPlayer = nullptr;

    qint64 m_llPosition = 0;
    qint64 m_llDuration = 0;

    Ui::MainWindow *ui;

private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;
};
#endif // MAINWINDOW_H
