/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.02
描  述:	实现基于http协议的文件下载
备  注:
修改记录:

  1.  日期: 2024.11.02
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QDir>
#include <QMessageBox>
#include <QDesktopServices>

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

void MainWindow::InitUi() noexcept
{
    ui->btnDownload->setEnabled(false);
}

void MainWindow::InitSignalSlots() noexcept
{

}

void MainWindow::on_btnDefaultPath_clicked()
{
    QString strCurFilePath = QDir::currentPath();
    QDir cDir(strCurFilePath);

    cDir.mkdir("temp");

    ui->editPath->setText(strCurFilePath + "/temp/");

    ui->btnDownload->setEnabled(true);
}


void MainWindow::on_btnDownload_clicked()
{
    QString strDownFilePath = ui->editPath->text();                         //下载文件路劲
    QString strUrl = ui->editURL->text();                                   //下载链接
    QUrl cUrl;

    if(strUrl.isEmpty())
    {
        QMessageBox::information(this, tr("提示窗口"), tr("请输入URL"));
        return;
    }

    cUrl = QUrl::fromUserInput(strUrl);
    if(!cUrl.isValid())
    {
        QMessageBox::information(this, tr("提示窗口"), tr("无效的URL"));
        return;
    }

    if(strDownFilePath.trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("提示窗口"), tr("请输入正确的下载文件存储路径"));
        return;
    }

    m_pcNetworkReply = m_cNetworkAccessManager.get(QNetworkRequest(strUrl));

    m_cFile.setFileName(strDownFilePath + cUrl.fileName());
    if(!m_cFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("提示窗口"), tr("未能正确的打开下载文件待存储位置: ") + m_cFile.fileName());
        return;
    }

    connect(m_pcNetworkReply, &QNetworkReply::finished, this, &MainWindow::Finished);
    connect(m_pcNetworkReply, &QNetworkReply::readyRead, this, &MainWindow::ReadyRead);
    connect(m_pcNetworkReply, &QNetworkReply::downloadProgress, this, &MainWindow::On_DownloadProgress);

    ui->btnDownload->setEnabled(false);
    ui->btnDefaultPath->setEnabled(false);
    ui->progressBar->setValue(0);
}

void MainWindow::Finished()
{
    QFileInfo cFileInfo(m_cFile);

    if(m_cFile.isOpen())
        m_cFile.close();

    m_pcNetworkReply->deleteLater();
    m_pcNetworkReply = nullptr;

    ui->btnDownload->setEnabled(true);
    ui->btnDefaultPath->setEnabled(true);

    if(!ui->checkOpen->isChecked())
        return;

    QDesktopServices::openUrl(QUrl::fromLocalFile(cFileInfo.absolutePath()));
}

void MainWindow::ReadyRead()
{
    m_cFile.write(m_pcNetworkReply->readAll());
}

void MainWindow::On_DownloadProgress(qint64 _BytesReceived, qint64 _BytesTotal)
{
    qint32 nMaxValue = ui->progressBar->maximum();
    qint32 nMinValue = ui->progressBar->minimum();

    ui->progressBar->setValue((_BytesReceived / _BytesTotal) * (nMaxValue - nMinValue));
}












