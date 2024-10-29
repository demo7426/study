/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.29
描  述:	查询主机名称、网络信息，及指定域名的网络信息
备  注:
修改记录:

  1.  日期: 2024.10.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QHostAddress>

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
    void on_btnClear_clicked();

    void on_btnGetHostInfo_clicked();

    void on_btnLookup_clicked();

    void on_btnDetail_clicked();

    void on_btnALLInterface_clicked();

private:
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

    ///
    /// \brief GetProtocolName--根据协议类型获取名称
    /// \param _Type--协议类型
    /// \return 协议名称
    ///
    QString GetProtocolName(QAbstractSocket::NetworkLayerProtocol _Type);
};
#endif // MAINWINDOW_H
