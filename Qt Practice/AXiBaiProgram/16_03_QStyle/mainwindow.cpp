/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.08
描  述:	使用QStyle设置界面外观
备  注:	推荐使用Qt5进行编译
修改记录:

  1.  日期: 2024.11.08
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QStyleFactory>

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
    QRegExp cRegExp("(.)(.*)Style");
    QString strDefaultStyle = QApplication::style()->metaObject()->className();

    ui->statusBar->showMessage(strDefaultStyle);
    ui->comboSysStyle->addItems(QStyleFactory::keys());

    if(cRegExp.exactMatch(strDefaultStyle))
        strDefaultStyle = cRegExp.cap(2);

    ui->comboSysStyle->setCurrentIndex(ui->comboSysStyle->findText(strDefaultStyle, Qt::MatchContains));
}

void MainWindow::InitSignalSlots(void) noexcept
{

}

void MainWindow::on_comboSysStyle_currentIndexChanged(const QString &arg1)
{
    QStyle *pcStyle = QStyleFactory::create(arg1);

    qApp->setStyle(pcStyle);
    ui->statusBar->showMessage(pcStyle->metaObject()->className());
}

void MainWindow::on_btnStyleSheet_clicked()
{
    //设置样式表
    this->setStyleSheet("QPlainTextEdit{"
                        "color: blue; "
                        "font: 13pt '宋体';}"
                        "QPushButton:hover{background-color:lime;}"
                        "QLineEdit{ border: 2px groove red;"
                        "background-color: rgb(170, 255, 127); "
                        "border-radius: 6px;}"
                        "QCheckBox:checked{color: red;}"
                        "QRadioButton:checked{color:red;}"
                        );
}

void MainWindow::on_btnNormal_clicked()
{
    this->setStyleSheet("");
}
