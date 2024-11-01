/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.01
描  述:	实现UDP的单播
备  注:
修改记录:

  1.  日期: 2024.11.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QHostInfo>
#include <QHostAddress>

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
    m_pcLabel_SocketStatus = new QLabel(this);

    ui->statusbar->addWidget(m_pcLabel_SocketStatus);

    this->setWindowTitle(tr("UDP端: ") + GetHostIPv4());

    //Multicast路由层次，1表示只在同一局域网内
    //组播TTL: 生存时间，每跨1个路由会减1，多播无法跨过大多数路由所以为1
    //默认值是1，表示数据包只能在本地的子网中传送。
    m_cUdpSocket.setSocketOption(QAbstractSocket::MulticastTtlOption,1);
}

void MainWindow::InitSignalSlots(void) noexcept
{
    connect(&m_cUdpSocket, &QUdpSocket::stateChanged, this, [this](QAbstractSocket::SocketState _SocketState){
        switch (_SocketState)
        {
        case QAbstractSocket::UnconnectedState:
            m_pcLabel_SocketStatus->setText("Socket状态: UnconnectedState");
            break;
        case QAbstractSocket::HostLookupState:
            m_pcLabel_SocketStatus->setText("Socket状态: HostLookupState");
            break;
        case QAbstractSocket::ConnectingState:
            m_pcLabel_SocketStatus->setText("Socket状态: ConnectingState");
            break;
        case QAbstractSocket::ConnectedState:
            m_pcLabel_SocketStatus->setText("Socket状态: ConnectedState");
            break;
        case QAbstractSocket::BoundState:
            m_pcLabel_SocketStatus->setText("Socket状态: BoundState");
            break;
        case QAbstractSocket::ClosingState:
            m_pcLabel_SocketStatus->setText("Socket状态: ClosingState");
            break;
        case QAbstractSocket::ListeningState:
            m_pcLabel_SocketStatus->setText("Socket状态: ListeningState");
            break;
        default:
            break;
        }
    });

    connect(&m_cUdpSocket, &QUdpSocket::readyRead, this, [this](){
        QHostAddress cDestHostAddress;
        quint16 usDestPort = 0;
        qint8 *pchBuf = new qint8[m_cUdpSocket.pendingDatagramSize() + 1] { 0 };

        m_cUdpSocket.readDatagram((char*)pchBuf, m_cUdpSocket.pendingDatagramSize(), &cDestHostAddress, &usDestPort);

        ui->plainTextEdit->appendPlainText(QString::asprintf("IPv4地址: %s, 端口: %u",
                                                             cDestHostAddress.toString().toStdString().data(), usDestPort));
        ui->plainTextEdit->appendPlainText(QString::asprintf("数据: %s", pchBuf));

        delete[] pchBuf;
        pchBuf = nullptr;
    });
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_cUdpSocket.abort();

    QMainWindow::closeEvent(event);
}

QString MainWindow::GetHostIPv4()
{
    QString strHostName = QHostInfo::localHostName();
    QHostInfo cHostInfo = QHostInfo::fromName(strHostName);

    QString strHostIPv4;
    QList<QHostAddress> cHostAddrList;

    cHostAddrList = cHostInfo.addresses();
    strHostIPv4.clear();

    foreach (auto addr, cHostAddrList)
    {
        if(addr.protocol() != QAbstractSocket::NetworkLayerProtocol::IPv4Protocol)
            continue;

        strHostIPv4 = addr.toString();
        break;
    }

    return strHostIPv4;
}

void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_actStart_triggered()
{
    quint16 usLocalPort = ui->spinBindPort->value();                                                //本地端口

    m_cUdpSocket.close();       //关闭之前绑定的端口
    if(m_cUdpSocket.bind(usLocalPort))             //绑定主机本地端口
    {
        ui->actStart->setEnabled(false);
        ui->actStop->setEnabled(true);

        ui->plainTextEdit->appendPlainText(tr("**成功绑定: 端口=")  + QString::number(usLocalPort) + tr("**"));
        return;
    }

    ui->plainTextEdit->appendPlainText(tr("**绑定失败**"));
}

void MainWindow::on_actStop_triggered()
{
    m_cUdpSocket.abort();

    ui->actStart->setEnabled(true);
    ui->actStop->setEnabled(false);

    ui->plainTextEdit->appendPlainText(tr("解除绑定"));
}


void MainWindow::on_btnSend_clicked()
{
    QHostAddress cDestHostAddress(ui->comboTargetIP->currentText());
    quint16 usDestPort = ui->spinTargetPort->value();
    QString strContent = ui->editMsg->text();
    QByteArray cByteArray = strContent.toUtf8();

    m_cUdpSocket.writeDatagram(cByteArray, cDestHostAddress, usDestPort);
}


void MainWindow::on_btnBroadcast_clicked()
{
    QHostAddress cDestHostAddress(QHostAddress::Broadcast);
    quint16 usDestPort = ui->spinTargetPort->value();
    QString strContent = ui->editMsg->text();
    QByteArray cByteArray = strContent.toUtf8();

    qDebug() << "广播地址:" << cDestHostAddress.toString();
    m_cUdpSocket.writeDatagram(cByteArray, cDestHostAddress, usDestPort);
}

