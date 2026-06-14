/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	register_dialog.h
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

#ifndef REGISTER_DIALOG_H
#define REGISTER_DIALOG_H

#include <QDialog>
#include <map>
#include <functional>

#include "global.h"

namespace Ui {
class CRegister_Dialog;
}

class CRegister_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit CRegister_Dialog(QWidget *parent = nullptr);
    ~CRegister_Dialog();

private:
    Ui::CRegister_Dialog *ui;

    std::map<HTTP_REQ_ID, std::function<void(const QJsonObject)>> m_mapHandler;            //回调函数

private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;

    ///
    /// \brief InitHandler 初始化回调函数
    ///
    void InitHandler(void) noexcept;
signals:
    ///
    /// \brief Clicked_Register 点击取消按钮后发出该信号
    ///
    void Clicked_Cancel(void);

private:
    ///
    /// \brief ConfirmPassword 确认密码
    ///
    void ConfirmPassword(void);

    void ShowTips(QString _Content, bool _IsOk);

private slots:
    ///
    /// \brief Reg_Mod_Finish 完成注册槽函数
    /// \param _Content
    /// \param _Http_Req_ID
    /// \param _Err_Code
    ///
    void Reg_Mod_Finish(QString _Content, HTTP_REQ_ID _Http_Req_ID, ERROR_CODE _Err_Code);
};

#endif // REGISTER_DIALOG_H
