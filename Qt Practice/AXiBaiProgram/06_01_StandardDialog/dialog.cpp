/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	dialog.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.15
描  述:	实现当前的dialog ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.15
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::InitUi() noexcept
{

}

void Dialog::InitSignalSlots() noexcept
{
    connect(ui->btnOpen, &QPushButton::clicked, this, &Dialog::OpenFile);
    connect(ui->btnOpenMulti, &QPushButton::clicked, this, &Dialog::OpenMultiFile);
    connect(ui->btnSelDir, &QPushButton::clicked, this, &Dialog::SelectDir);
    connect(ui->btnSave, &QPushButton::clicked, this, &Dialog::SaveFile);
    connect(ui->btnColor, &QPushButton::clicked, this, &Dialog::SelectTextColor);
    connect(ui->btnFont, &QPushButton::clicked, this, &Dialog::SelectTextFont);

    connect(ui->btnInputString, &QPushButton::clicked, this, &Dialog::InputString);
    connect(ui->btnInputInt, &QPushButton::clicked, this, &Dialog::InputInt);
    connect(ui->btnInputFloat, &QPushButton::clicked, this, &Dialog::InputFloat);
    connect(ui->btnInputItem, &QPushButton::clicked, this, &Dialog::InputSelectItem);

    connect(ui->btnMsgQuestion, &QPushButton::clicked, this, [this](){
        QMessageBox::question(this, "问题窗口", "提示");
    });

    connect(ui->btnMsgInformation, &QPushButton::clicked, this, [this](){
        QMessageBox::information(this, "信息窗口", "提示");
    });

    connect(ui->btnMsgWarning, &QPushButton::clicked, this, [this](){
        QMessageBox::warning(this, "警告窗口", "提示");
    });

    connect(ui->btnMsgCritical, &QPushButton::clicked, this, [this](){
        QMessageBox::critical(this, "错误窗口", "提示");
    });

    connect(ui->btnMsgAbout, &QPushButton::clicked, this, [this](){
        QMessageBox::about(this, "版本窗口", "V0.1.0");
    });

    connect(ui->btnMsgAboutQt, &QPushButton::clicked, this, [this](){
        QMessageBox::aboutQt(this, "Qt版本窗口");
    });

    connect(ui->btnClearText, &QPushButton::clicked, this, [this](){
        ui->plainTextEdit->clear();
    });
}

void Dialog::OpenFile()
{
    QString strCurFilePath = QFileDialog::getOpenFileName(this, "选择文件", QDir::currentPath(),
                                 "文本文件(*.txt);;代码文件(*.c *.cpp *.h);;图片(*.png)");

    if(strCurFilePath.isEmpty())
        return;

    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(strCurFilePath);
}

void Dialog::OpenMultiFile()
{
    QStringList strListCurFilePath = QFileDialog::getOpenFileNames(this, "选择多个文件", QDir::currentPath(),
                                                          "文本文件(*.txt);;代码文件(*.c *.cpp *.h);;图片(*.png)");

    if(strListCurFilePath.isEmpty())
        return;

    ui->plainTextEdit->clear();

    foreach (auto var, strListCurFilePath)
    {
        ui->plainTextEdit->appendPlainText(var);
    }
}

void Dialog::SelectDir()
{
    QString strCurDir = QFileDialog::getExistingDirectory(this, "选择目录", QCoreApplication::applicationDirPath());

    if(strCurDir.isEmpty())
        return;

    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(strCurDir);
}

void Dialog::SaveFile()
{
    QString strCurSaveFile = QFileDialog::getSaveFileName(this, "保存文件", QDir::currentPath(), "文本文件(*.txt);; 代码文件(*.c *.cpp *.h);;图片(*.png)");

    if(strCurSaveFile.isEmpty())
        return;

    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(strCurSaveFile);

}

void Dialog::SelectTextColor()
{
    QPalette cCurPalette = ui->plainTextEdit->palette();
    QColor cCurColor = cCurPalette.color(QPalette::ColorGroup::Normal, QPalette::ColorRole::Text);
    cCurColor = QColorDialog::getColor(cCurColor);

    if(!cCurColor.isValid())
        return;

    cCurPalette.setColor(QPalette::ColorRole::Text, cCurColor);
    ui->plainTextEdit->setPalette(cCurPalette);
}

void Dialog::SelectTextFont()
{
    QFont cFont = ui->plainTextEdit->font();
    bool bOk = false;

    cFont = QFontDialog::getFont(&bOk,  cFont, this);

    if(!bOk)
        return;

    ui->plainTextEdit->setFont(cFont);
}

void Dialog::InputString()
{
    QString strInputContent = QInputDialog::getText(this, "输入文本", "文本内容");
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(strInputContent);
}

void Dialog::InputInt()
{
    bool bOK = false;
    int nInputValue = QInputDialog::getInt(this, "输入整型", "输入", 0, 0, 100, 1, &bOK);

    if(!bOK)
        return;

    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(QString::asprintf("%d", nInputValue));
}

void Dialog::InputFloat()
{
    bool bOK = false;
    qint32 nDecimals = 2;           //浮点数精度
    double dbInputValue = QInputDialog::getDouble(this, "输入浮点", "输入", 0, 0, 100, nDecimals, &bOK);

    if(!bOK)
        return;

    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(QString::asprintf("%.02f", dbInputValue));
}

void Dialog::InputSelectItem()
{
    bool bOK = false;
    QStringList strListItem;

    strListItem << "条目00" << "条目01" << "条目02" << "条目03";

    QString strInputContent = QInputDialog::getItem(this, "选择条目", "条目", strListItem, 0, false, &bOK);

    if(!bOK)
        return;

    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(strInputContent);
}



