/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUi(void) noexcept
{

}

void MainWindow::InitSignalSlots(void) noexcept
{

}

QString MainWindow::GetProtocolName(QAbstractSocket::NetworkLayerProtocol _Type)
{
    QString strContent = "";

    switch (_Type) {
    case QAbstractSocket::NetworkLayerProtocol::IPv4Protocol:
        strContent = "IPv4Protocol";
        break;
    case QAbstractSocket::NetworkLayerProtocol::IPv6Protocol:
        strContent = "IPv6Protocol";
        break;
    case QAbstractSocket::NetworkLayerProtocol::AnyIPProtocol:
        strContent = "AnyIPProtocol";
        break;
    case QAbstractSocket::NetworkLayerProtocol::UnknownNetworkLayerProtocol:
        strContent = "UnknownNetworkLayerProtocol";
        break;
    default:
        break;
    }

    return strContent;
}

void MainWindow::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_btnGetHostInfo_clicked()
{
    QString strHostName = QHostInfo::localHostName();

    if(strHostName.isEmpty())
        return;

    QHostInfo cHostInfo = QHostInfo::fromName(strHostName);
    QList<QHostAddress> cHostAddressList = cHostInfo.addresses();

    ui->plainTextEdit->appendPlainText("\n获取本机主机名和IP地址");
    ui->plainTextEdit->appendPlainText("主机名: " + strHostName);

    foreach (auto item, cHostAddressList)
    {
        if(ui->chkOnlyIPv4->isChecked() && item.protocol() != QAbstractSocket::NetworkLayerProtocol::IPv4Protocol) //只显示IPv4协议的信息
            continue;

        ui->plainTextEdit->appendPlainText(GetProtocolName(item.protocol()) + ": " + item.toString());
    }
}

void MainWindow::on_btnLookup_clicked()
{
    QString strHostName = ui->editHost->text();

    if(strHostName.isEmpty())
        return;

    QHostInfo cHostInfo = QHostInfo::fromName(strHostName);
    QList<QHostAddress> cHostAddressList = cHostInfo.addresses();

    ui->plainTextEdit->appendPlainText("\n查找域名的IP地址");
    ui->plainTextEdit->appendPlainText("域名: " + strHostName);

    foreach (auto item, cHostAddressList)
    {
        if(ui->chkOnlyIPv4->isChecked() && item.protocol() != QAbstractSocket::NetworkLayerProtocol::IPv4Protocol) //只显示IPv4协议的信息
            continue;

        ui->plainTextEdit->appendPlainText(GetProtocolName(item.protocol()) + ": " + item.toString());
    }
}

void MainWindow::on_btnDetail_clicked()
{
    QList<QHostAddress> cHostAddressList = QNetworkInterface::allAddresses();

    ui->plainTextEdit->appendPlainText("\n查找allAddresses");
    foreach (auto item, cHostAddressList)
    {
        if(ui->chkOnlyIPv4->isChecked() && item.protocol() != QAbstractSocket::NetworkLayerProtocol::IPv4Protocol) //只显示IPv4协议的信息
            continue;

        ui->plainTextEdit->appendPlainText(GetProtocolName(item.protocol()) + ": " + item.toString());
    }
}

void MainWindow::on_btnALLInterface_clicked()
{
    QList<QNetworkInterface> cNetworkInterfaceList =  QNetworkInterface::allInterfaces();

    ui->plainTextEdit->appendPlainText("\n查找allInterfaces");
    foreach (auto cInterface, cNetworkInterfaceList)
    {
        if(!cInterface.isValid())
            continue;

        ui->plainTextEdit->appendPlainText("设备名称: " + cInterface.humanReadableName());
        ui->plainTextEdit->appendPlainText("硬件地址: " + cInterface.hardwareAddress());

        QList<QNetworkAddressEntry> cEntryList = cInterface.addressEntries();
        foreach (auto cEntry, cEntryList)
        {
            ui->plainTextEdit->appendPlainText("IP地址: " + cEntry.ip().toString());
            ui->plainTextEdit->appendPlainText("子网掩码: " + cEntry.netmask().toString());
            ui->plainTextEdit->appendPlainText("广播地址: " + cEntry.broadcast().toString());
        }
    }

}

