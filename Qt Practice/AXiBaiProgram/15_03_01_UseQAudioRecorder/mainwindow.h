/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.04
描  述:	使用QAudioRecoder实现音频的录制
备  注:	推荐使用Qt5进行编译
修改记录:

  1.  日期: 2024.11.04
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioRecorder>
#include <QAudioProbe>

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
    void on_btnGetFile_clicked();

    void on_actRecord_triggered();

    void on_actPause_triggered();

    void on_actStop_triggered();

private:
    QAudioRecorder *m_pcAudioRecorder = nullptr;
    QAudioProbe *m_pcAudioProbe = nullptr;

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

    void On_StateChanged(QMediaRecorder::State _State);

    void On_DurationChanged(qint64 _Duration);

    void On_AudioBufferProbed(const QAudioBuffer &buffer);
};
#endif // MAINWINDOW_H
