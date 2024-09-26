/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.26
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.26
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QFile>
#include <QFileDialog>

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
    this->setCentralWidget(ui->tabWidget);
}


void MainWindow::InitSignalSlots(void) noexcept
{
    connect(ui->actOpen_IODevice, &QAction::triggered, this, &MainWindow::UseQFileToLoadFile);
    connect(ui->actOpen_TextStream, &QAction::triggered, this, &MainWindow::UseQTextStreamToLoadFile);

    connect(ui->actSave_IODevice, &QAction::triggered, this, &MainWindow::UseQFileTopSaveFile);
    connect(ui->actSave_TextStream, &QAction::triggered, this, &MainWindow::UseQTextStreamTopSaveFile);
}

void MainWindow::UseQFileToLoadFile()
{
    QFile cFile;
    QString strCurFilePath;                 //当前文件路径
    QString strFilter = tr("头文件(*.h);;源文件(*.c *.cpp);;所有文件(*.*)");

    strCurFilePath = QFileDialog::getOpenFileName(this, tr("选择单个文件"), QCoreApplication::applicationDirPath(), strFilter);

    cFile.setFileName(strCurFilePath);
    cFile.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!cFile.isOpen())
    {
        qDebug() << "文件打开失败";
        return;
    }

    ui->plainTextEditFile->setPlainText(QString::fromUtf8(cFile.readAll()));
    cFile.close();

    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::UseQTextStreamToLoadFile()
{
    QFile cFile;
    QString strCurFilePath;                 //当前文件路径
    QString strFilter = tr("头文件(*.h);;源文件(*.c *.cpp);;所有文件(*.*)");
    QTextStream cTextStream;

    strCurFilePath = QFileDialog::getOpenFileName(this, tr("选择单个文件"), QCoreApplication::applicationDirPath(), strFilter);

    cFile.setFileName(strCurFilePath);
    cFile.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!cFile.isOpen())
    {
        qDebug() << "文件打开失败";
        return;
    }

    cTextStream.setDevice(&cFile);
    cTextStream.autoDetectUnicode();

    ui->plainTextEditTextStream->setPlainText(cTextStream.readAll());

    cFile.close();

    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::UseQFileTopSaveFile()
{
    QFile cFile;
    QString strCurFilePath;                 //当前文件路径
    QString strFilter = tr("头文件(*.h);;源文件(*.c *.cpp);;所有文件(*.*)");

    strCurFilePath = QFileDialog::getSaveFileName(this, tr("选择单个文件"), QCoreApplication::applicationDirPath(), strFilter);

    cFile.setFileName(strCurFilePath);
    cFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

    if(!cFile.isOpen())
    {
        qDebug() << "文件打开失败";
        return;
    }

    cFile.write(ui->plainTextEditFile->toPlainText().toUtf8());

    cFile.close();
}

void MainWindow::UseQTextStreamTopSaveFile()
{
    QFile cFile;
    QString strCurFilePath;                 //当前文件路径
    QString strFilter = tr("头文件(*.h);;源文件(*.c *.cpp);;所有文件(*.*)");
    QTextStream cTextStream;

    strCurFilePath = QFileDialog::getSaveFileName(this, tr("选择单个文件"), QCoreApplication::applicationDirPath(), strFilter);

    cFile.setFileName(strCurFilePath);
    cFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

    if(!cFile.isOpen())
    {
        qDebug() << "文件打开失败";
        return;
    }

    cTextStream.setDevice(&cFile);
    cTextStream.autoDetectUnicode();

    cTextStream << ui->plainTextEditTextStream->toPlainText();

    cFile.close();
}
