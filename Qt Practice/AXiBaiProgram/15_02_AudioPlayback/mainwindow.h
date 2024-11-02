/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.02
描  述:	实现多个音频的播放
备  注:	必须使用Qt5进行编译、Qt6对音频播放方法进行了改版
修改记录:

  1.  日期: 2024.11.02
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();

    void On_StateChanged(QMediaPlayer::State _NewState);

    void On_DurationChanged(qint64 duration);

    void On_PositionChanged(qint64 position);

    void On_CurrentIndexChanged(int index);

    void on_btnRemove_clicked();

    void on_btnClear_clicked();

    void on_btnPlay_clicked();

    void on_btnPause_clicked();

    void on_btnStop_clicked();

    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

    void on_sliderVolumn_valueChanged(int value);

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_btnSound_clicked();

private:
    QMediaPlayer m_cMediaPlayer;
    QMediaPlaylist m_cMediaPlaylist;

    QString m_strDuration = "";
    QString m_strPosition = "";
    qint64 m_llCurDuration = 0;

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
