/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
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
#include <QHostAddress>
#include <QHostInfo>

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
    m_pcTcpSocket = new QTcpSocket(this);
    m_pcLabel = new QLabel(this);

    ui->statusbar->addWidget(m_pcLabel);

    this->setWindowTitle(tr("客户端: ") + GetHostIPv4());
    this->resize(400, 400);

    ui->btnSend->setEnabled(false);
}

void MainWindow::InitSignalSlots(void) noexcept
{
    connect(m_pcTcpSocket, &QTcpSocket::readyRead, this, [this](){
        // while(m_pcTcpSocket->canReadLine())
        //     ui->plainTextEdit->appendPlainText("[接收到的数据]: " + m_pcTcpSocket->readLine());
        ui->plainTextEdit->appendPlainText("[接收到的数据]: " + m_pcTcpSocket->readAll());
    });

    connect(m_pcTcpSocket, &QTcpSocket::stateChanged, this, [this](QAbstractSocket::SocketState _SocketState){
        switch (_SocketState)
        {
        case QAbstractSocket::UnconnectedState:
            m_pcLabel->setText("Socket状态: UnconnectedState");
            break;
        case QAbstractSocket::HostLookupState:
            m_pcLabel->setText("Socket状态: HostLookupState");
            break;
        case QAbstractSocket::ConnectingState:
            m_pcLabel->setText("Socket状态: ConnectingState");
            break;
        case QAbstractSocket::ConnectedState:
            m_pcLabel->setText("Socket状态: ConnectedState");
            break;
        case QAbstractSocket::BoundState:
            m_pcLabel->setText("Socket状态: BoundState");
            break;
        case QAbstractSocket::ClosingState:
            m_pcLabel->setText("Socket状态: ClosingState");
            break;
        case QAbstractSocket::ListeningState:
            m_pcLabel->setText("Socket状态: ListeningState");
            break;
        default:
            break;
        }
    });
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

void MainWindow::on_actConnect_triggered()
{
    QHostAddress cHostAddress(ui->comboServer->currentText());
    m_pcTcpSocket->connectToHost(cHostAddress, ui->spinPort->value());

    if(m_pcTcpSocket->state() == QAbstractSocket::ConnectingState)
    {
        ui->actConnect->setEnabled(false);
        ui->actDisconnect->setEnabled(true);
        ui->btnSend->setEnabled(true);
    }
}

void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_actDisconnect_triggered()
{
    if(m_pcTcpSocket->state() == QAbstractSocket::SocketState::ConnectedState)
        m_pcTcpSocket->disconnectFromHost();

    ui->actConnect->setEnabled(true);
    ui->actDisconnect->setEnabled(false);
    ui->btnSend->setEnabled(false);
}

void MainWindow::on_btnSend_clicked(bool checked)
{
    Q_UNUSED(checked);

    QByteArray cByteArray = ui->editMsg->text().toUtf8();

    m_pcTcpSocket->write(cByteArray);

    //不缓存，直接发送
    m_pcTcpSocket->flush();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_pcTcpSocket->state() == QAbstractSocket::SocketState::ConnectedState)
        m_pcTcpSocket->disconnectFromHost();

    QMainWindow::closeEvent(event);
}

