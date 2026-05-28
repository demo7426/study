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

#include <QRegularExpression>
#include <QDebug>

#include "register_dialog.h"
#include "ui_register_dialog.h"
#include "global.h"

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

    ui->line_edit_password->setEchoMode(QLineEdit::Password);
    ui->line_edit_password_confirm->setEchoMode(QLineEdit::Password);

    ui->label_err_tip->setProperty("state", "normal");
    g_cRepolish(ui->label_err_tip);
}

void CRegister_Dialog::InitSignalSlots() noexcept
{
    connect(ui->pushbtn_cancel, &QPushButton::clicked, this, &CRegister_Dialog::Clicked_Cancel);

    connect(ui->push_btn_confirm, &QPushButton::clicked, this, &CRegister_Dialog::ConfirmPassword);
}

void CRegister_Dialog::ConfirmPassword()
{
    QString strEmail = ui->line_edit_email->text();

    QRegularExpression regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    bool bMatch = regex.match(strEmail).hasMatch();

    if(bMatch)
    {
        //发送http验证码

        this->ShowTips(tr("错误提示"), true);
    }
    else
    {
        this->ShowTips(tr("邮箱地址不正确"), false);
    }

}

void CRegister_Dialog::ShowTips(QString _Content, bool _IsOk)
{
    ui->label_err_tip->setText(_Content);

    if(_IsOk)
    {
        ui->label_err_tip->setProperty("state", "normal");
    }
    else
    {
        ui->label_err_tip->setProperty("state", "err");
    }

    g_cRepolish(ui->label_err_tip);
}
