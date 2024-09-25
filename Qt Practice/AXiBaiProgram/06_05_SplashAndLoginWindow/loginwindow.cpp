/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	loginwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.25
描  述:	实现登录窗口
备  注:
修改记录:

  1.  日期: 2024.09.25
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QMessageBox>
#include <QByteArray>
#include <QCryptographicHash>
#include <QSettings>
#include <QMouseEvent>

#include "loginwindow.h"
#include "ui_loginwindow.h"

CLoginWindow::CLoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CLoginWindow)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

CLoginWindow::~CLoginWindow()
{
    delete ui;
}

void CLoginWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bIsMoving && (event->buttons() & Qt::LeftButton))
    {
        move(event->globalPosition().toPoint() - m_cPointDiffValue);
        m_cPointDiffValue = event->globalPosition().toPoint() - this->pos();
    }


    qDebug() << event->button();

    return QDialog::mouseMoveEvent(event);
}

void CLoginWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_cPointDiffValue = event->globalPosition().toPoint() - this->pos();
        m_bIsMoving = true;
    }

    return QDialog::mousePressEvent(event);
}

void CLoginWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        m_bIsMoving = false;

    return QDialog::mouseReleaseEvent(event);
}

void CLoginWindow::InitUi() noexcept
{
    this->setWindowFlags(Qt::FramelessWindowHint);      //实现无边界窗口显示

    m_strPassWord = CryptographicString(m_strPassWord);
    ReadSettings();
}

void CLoginWindow::InitSignalSlots() noexcept
{
    connect(ui->btnOK, &QPushButton::clicked, this, &CLoginWindow::LoginWindow);
    connect(ui->checkBoxSave, &QCheckBox::stateChanged, this, [this](int _State){
        if(_State == Qt::Checked)
            WriteSettings();
    });
}

void CLoginWindow::LoginWindow()
{
    QString strUserName = ui->editUserName->text().simplified();
    QString strPassWord = ui->editPassWord->text().simplified();

    if(strUserName == m_strUserName && CryptographicString(strPassWord) == m_strPassWord)
    {
        accept();
        return;
    }
    else
    {
        QMessageBox::warning(this, tr("警告窗口"), tr("用户名或密码输入错误"));
        m_chLoginFreq++;
    }

    if(m_chLoginFreq >= 3)
        reject();
}

QString CLoginWindow::CryptographicString(QString _Content)
{
    QByteArray cByteArray;
    QCryptographicHash cCryptographicHash(QCryptographicHash::Md5);

    cByteArray = _Content.toUtf8();
    cCryptographicHash.addData(cByteArray);

    return cCryptographicHash.result().toHex();
}

void CLoginWindow::ReadSettings()
{
    QSettings cSettings(tr("qianrui_Qt"), QApplication::applicationName());

    QString strUserName = cSettings.value(tr("UserName"), "").toString();
    QString strPassWord = cSettings.value(tr("PassWord"), "").toString();

    ui->editUserName->setText(strUserName);
    ui->editPassWord->setText(strPassWord);
}

void CLoginWindow::WriteSettings()
{
    QString strUserName = ui->editUserName->text().simplified();
    QString strPassWord = ui->editPassWord->text().simplified();
    QSettings cSettings(tr("qianrui_Qt"), QApplication::applicationName());

    cSettings.setValue(tr("UserName"), strUserName);
    cSettings.setValue(tr("PassWord"), strPassWord);
}
