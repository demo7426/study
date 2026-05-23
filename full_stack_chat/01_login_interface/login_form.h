/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	login_form.h
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

#ifndef LOGIN_FORM_H
#define LOGIN_FORM_H

#include <QWidget>

namespace Ui {
class CLogin_Form;
}

class CLogin_Form : public QWidget
{
    Q_OBJECT

public:
    explicit CLogin_Form(QWidget *parent = nullptr);
    ~CLogin_Form();

private:
    Ui::CLogin_Form *ui;

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
    /// \brief Clicked_Register 点击注册按钮后发出该信号
    ///
    void Clicked_Register(void);
};

#endif // LOGIN_FORM_H
