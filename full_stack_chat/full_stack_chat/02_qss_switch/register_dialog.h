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

private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;

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
};

#endif // REGISTER_DIALOG_H
