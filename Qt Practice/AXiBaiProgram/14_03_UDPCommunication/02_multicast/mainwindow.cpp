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

void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}

void MainWindow::InitUi(void) noexcept
{
    m_pcLabel_SocketStatus = new QLabel(this);

    ui->statusbar->addWidget(m_pcLabel_SocketStatus);

    this->setWindowTitle(tr("UDP端: ") + GetHostIPv4());
    // this->resize(600, 500);
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
        qDebug() << "1";
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
    m_cUdpSocket.leaveMulticastGroup(QHostAddress(ui->comboIP->currentText()));
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

void MainWindow::on_actStart_triggered()
{
    quint16 usLocalPort = ui->spinPort->value();                                                //本地端口
    // m_cUdpSocket.close();       //关闭之前绑定的端口

    if(m_cUdpSocket.bind(QHostAddress::AnyIPv4, usLocalPort, QAbstractSocket::ShareAddress))             //绑定主机本地端口
    {
        m_cUdpSocket.joinMulticastGroup(QHostAddress(ui->comboIP->currentText()));

        ui->actStart->setEnabled(false);
        ui->actStop->setEnabled(true);

        ui->plainTextEdit->appendPlainText(tr("**成功加入组播: IPv4=") + ui->comboIP->currentText() +
                                           tr("端口=") + QString::number(usLocalPort) + tr("**"));
        return;
    }

    ui->plainTextEdit->appendPlainText(tr("**加入组播失败**"));
}

void MainWindow::on_actStop_triggered()
{
    m_cUdpSocket.leaveMulticastGroup(QHostAddress(ui->comboIP->currentText()));
    m_cUdpSocket.abort();

    ui->actStart->setEnabled(true);
    ui->actStop->setEnabled(false);

    ui->plainTextEdit->appendPlainText(tr("退出组播"));
}

void MainWindow::on_btnMulticast_clicked()
{
    QHostAddress cDestHostAddress(ui->comboIP->currentText());
    quint16 usDestPort = ui->spinPort->value();
    QString strContent = ui->editMsg->text();
    QByteArray cByteArray = strContent.toUtf8();

    m_cUdpSocket.writeDatagram(cByteArray, cDestHostAddress, usDestPort);
}

