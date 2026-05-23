/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	login_form.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.05.21
描  述:	实现用户登录窗口的数据交互和ui显示
备  注:
修改记录:

  1.  日期: 2026.05.21
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include "login_form.h"
#include "ui_login_form.h"

CLogin_Form::CLogin_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CLogin_Form)
{
    ui->setupUi(this);

    this->InitUi();
    this->InitSignalSlots();
}

CLogin_Form::~CLogin_Form()
{
    delete ui;
}

void CLogin_Form::InitUi() noexcept
{
    ui->label_qr_code->setPixmap(QPixmap(":/img/img/qr_code.png"));
}

void CLogin_Form::InitSignalSlots() noexcept
{
    connect(ui->pushbtn_reg, &QPushButton::clicked, this, &CLogin_Form::Clicked_Register);
}
