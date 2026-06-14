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
#include <QJsonDocument>

#include "register_dialog.h"
#include "ui_register_dialog.h"
#include "global.h"
#include "http_mgr.h"

CRegister_Dialog::CRegister_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRegister_Dialog)
{
    ui->setupUi(this);

    this->InitUi();
    this->InitSignalSlots();
    this->InitHandler();
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

    connect(CHttpMgr::GetInstance().get(), &CHttpMgr::Sig_Reg_Mod_Finish, this, &CRegister_Dialog::Reg_Mod_Finish);
}

void CRegister_Dialog::InitHandler() noexcept
{
    m_mapHandler.emplace(HTTP_REQ_ID::ID_REG_USER, [this](const QJsonObject _JsonObj){
        int nErr = _JsonObj["error"].toInt();
        if(nErr != (int)ERROR_CODE::SUCCESS)
        {
            this->ShowTips(tr("参数错误"), false);
            return;
        }

        auto strEmail = _JsonObj["email"].toString();
        this->ShowTips(tr("验证码已发送邮箱，请注意查收"), true);
        qDebug() << __func__ << ", email is " << strEmail;
    });
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

void CRegister_Dialog::Reg_Mod_Finish(QString _Content, HTTP_REQ_ID _Http_Req_ID, ERROR_CODE _Err_Code)
{
    if(_Err_Code != ERROR_CODE::SUCCESS)
    {
        this->ShowTips(tr("网络请求错误"), false);
        return;
    }

    QJsonDocument cJsonDocument = QJsonDocument::fromJson(_Content.toUtf8());
    if(cJsonDocument.isNull())
    {
        this->ShowTips(tr("json为空"), false);
        return;
    }

    if(cJsonDocument.isObject())
    {
        this->ShowTips(tr("json解析错误"), false);
        return;
    }

    QJsonObject cJsonObj = cJsonDocument.object();

    m_mapHandler[_Http_Req_ID](cJsonObj);

    return;
}







