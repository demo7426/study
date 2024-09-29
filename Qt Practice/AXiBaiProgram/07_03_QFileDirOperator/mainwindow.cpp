/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.29
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QFileDialog>
#include <QFile>

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
    ui->toolBox->setCurrentIndex(0);

    ui->pushButton_48->setEnabled(false);
}

void MainWindow::InitSignalSlots(void) noexcept
{

}

void MainWindow::AppendMsgToplainTextEdit(QPushButton *_pPushBtn, QPlainTextEdit *_pPlainTextEdit)
{
    if(_pPushBtn == nullptr || _pPlainTextEdit == nullptr)
        return;

    _pPlainTextEdit->appendPlainText(tr("按钮内容: ") + _pPushBtn->text());
    _pPlainTextEdit->appendPlainText(tr("按钮提示: ") + _pPushBtn->toolTip() + tr("\n"));
}


void MainWindow::on_pushBtnOpenFile_clicked()
{
    QString strOpenFilePath = QFileDialog::getOpenFileName(this, tr("选择单个文件"), QCoreApplication::applicationFilePath(), tr("所有文件(*.*)"));

    if(strOpenFilePath.isEmpty())
        return;

    ui->editFile->setText(strOpenFilePath);

    ui->pushButton_48->setEnabled(true);
}


void MainWindow::on_pushBtnOpenDir_clicked()
{
    QString strExitDir = QFileDialog::getExistingDirectory(this, tr("选择目录"), QCoreApplication::applicationFilePath());

    if(strExitDir.isEmpty())
        return;

    ui->editDir->setText(strExitDir);
}


void MainWindow::on_pushBtnClearText_clicked()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_pushButton_clicked()
{
    AppendMsgToplainTextEdit(qobject_cast<QPushButton*>(sender()), ui->plainTextEdit);
    ui->plainTextEdit->appendPlainText(QCoreApplication::applicationDirPath());
}

void MainWindow::on_pushButton_48_clicked()
{
    QFile cFile;
    QFileInfo cFileInfo;
    QString strNewFilePath;

    cFileInfo.setFile(ui->editFile->text());

    strNewFilePath = cFileInfo.path() + "/" + cFileInfo.baseName() + "-副本." + cFileInfo.completeSuffix();

    AppendMsgToplainTextEdit(qobject_cast<QPushButton*>(sender()), ui->plainTextEdit);
    cFile.copy(ui->editFile->text(), strNewFilePath);

    ui->plainTextEdit->appendPlainText("源文件: " + ui->editFile->text());
    ui->plainTextEdit->appendPlainText("目标文件: " + strNewFilePath);
}

void MainWindow::on_pushButton_28_clicked()
{
    QFile cFile;
    QFileInfo cFileInfo;
    QString strNewFilePath;

    cFileInfo.setFile(ui->editFile->text());

    AppendMsgToplainTextEdit(qobject_cast<QPushButton*>(sender()), ui->plainTextEdit);

    ui->plainTextEdit->appendPlainText(cFileInfo.absoluteFilePath());
}

