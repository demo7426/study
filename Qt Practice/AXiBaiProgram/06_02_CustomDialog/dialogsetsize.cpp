/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	dialogsetsize.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.20
描  述:	用于设置QTableView的行数、列数
备  注:
修改记录:

  1.  日期: 2024.09.20
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QMessageBox>

#include "dialogsetsize.h"
#include "ui_dialogsetsize.h"

CDialogSetSize::CDialogSetSize(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CDialogSetSize)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

CDialogSetSize::~CDialogSetSize()
{
    delete ui;
    QMessageBox::warning(this, "提示", "是否关闭设置行号列号对话框");
}

void CDialogSetSize::SetRowAndColumnCount(quint32 _RowCount, quint32 _ColumnCount)
{
    ui->spinBoxRow->setMinimum(0);
    ui->spinBoxRow->setMaximum(9999);
    ui->spinBoxColumn->setMaximum(0);
    ui->spinBoxColumn->setMaximum(9999);

    ui->spinBoxRow->setValue(_RowCount);
    ui->spinBoxColumn->setValue(_ColumnCount);
}

void CDialogSetSize::InitUi() noexcept
{

}

void CDialogSetSize::InitSignalSlots() noexcept
{
    connect(ui->btnOK, &QPushButton::clicked, this, [=](){
        this->hide();
        emit RowAndColumnChanged(ui->spinBoxRow->value(), ui->spinBoxColumn->value());
    });
    connect(ui->btnCancel, &QPushButton::clicked, this, [=](){
        this->hide();
        emit RowAndColumnChanged(ui->spinBoxRow->value(), ui->spinBoxColumn->value(), false);
    });
}
