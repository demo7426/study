/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	register_dialog.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.05.21
描  述:	实现用户注册的数据交互和ui显示
备  注:
修改记录:

  1.  日期: 2026.05.21
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include "register_dialog.h"
#include "ui_register_dialog.h"

CRegister_Dialog::CRegister_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRegister_Dialog)
{
    ui->setupUi(this);

    this->InitUi();
    this->InitSignalSlots();
}

CRegister_Dialog::~CRegister_Dialog()
{
    delete ui;
}

void CRegister_Dialog::InitUi() noexcept
{
    this->setWindowTitle("注册界面");

}

void CRegister_Dialog::InitSignalSlots() noexcept
{
    connect(ui->pushbtn_cancel, &QPushButton::clicked, this, &CRegister_Dialog::Clicked_Cancel);
}
