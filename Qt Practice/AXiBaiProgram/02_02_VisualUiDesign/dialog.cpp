/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	dialog.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.22
描  述:	使用纯ui设计界面设计ui
备  注:
修改记录:

  1.  日期: 2024.08.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QFont>
#include <QColor>

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    Connected();
}

Dialog::~Dialog()
{
    delete ui;
}

int Dialog::Connected() noexcept
{
    //qt5之前的用法
    connect(ui->radioBtnRed, SIGNAL(clicked()), this, SLOT(SetPlainTextEditColor()));

    //qt5之后的用法
    connect(ui->radioBtnGreen, &QRadioButton::clicked, this, &Dialog::SetPlainTextEditColor);
    connect(ui->radioBtnBlue, &QRadioButton::clicked, this, &Dialog::SetPlainTextEditColor);

    return 0;
}

void Dialog::on_checkBoxUnderline_clicked(bool checked)
{
    QFont cFont = ui->plainTextEdit->font();

    cFont.setUnderline(checked);
    ui->plainTextEdit->setFont(cFont);
}


void Dialog::on_checkBoxItalic_clicked(bool checked)
{
    QFont cFont = ui->plainTextEdit->font();

    cFont.setItalic(checked);
    ui->plainTextEdit->setFont(cFont);
}


void Dialog::on_checkBoxBold_clicked(bool checked)
{
    QFont cFont = ui->plainTextEdit->font();

    cFont.setBold(checked);
    ui->plainTextEdit->setFont(cFont);
}

void Dialog::SetPlainTextEditColor()
{
    QPalette cPalette = ui->plainTextEdit->palette();

    if(ui->radioBtnRed->isChecked())
        cPalette.setColor(QPalette::Text, Qt::red);
    else if(ui->radioBtnBlue->isChecked())
        cPalette.setColor(QPalette::Text, Qt::blue);
    else if(ui->radioBtnGreen->isChecked())
        cPalette.setColor(QPalette::Text, Qt::green);
    else
        cPalette.setColor(QPalette::Text, Qt::black);

    ui->plainTextEdit->setPalette(cPalette);
}

