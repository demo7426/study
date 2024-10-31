/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.31
描  述:	实现支持TCP协议的客户端
备  注:
修改记录:

  1.  日期: 2024.10.31
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>

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
    void on_actConnect_triggered();

    void on_actClear_triggered();

    void on_actDisconnect_triggered();

    void on_btnSend_clicked(bool checked);

private:
    QLabel *m_pcLabel = nullptr;
    QTcpSocket *m_pcTcpSocket = nullptr;

    Ui::MainWindow *ui;

protected:
    void closeEvent(QCloseEvent *event);

private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;

    ///
    /// \brief GetHostIPv4--获取本地主机IPv4的地址
    /// \return
    ///
    QString GetHostIPv4(void);
};
#endif // MAINWINDOW_H
