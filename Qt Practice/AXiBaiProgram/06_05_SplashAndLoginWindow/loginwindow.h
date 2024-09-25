/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	loginwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.25
描  述:	实现登录窗口
备  注:
修改记录:

  1.  日期: 2024.09.25
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class CLoginWindow;
}

class CLoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CLoginWindow(QWidget *parent = nullptr);
    ~CLoginWindow();

private:
    quint8 m_chLoginFreq = 0;           //登录次数
    QString m_strUserName = "user";     //用户名称
    QString m_strPassWord = "123456";   //用户密码

    QPoint m_cPointDiffValue;           //光标当前位置和当前窗口左上顶点坐标之间的差值
    bool m_bIsMoving = false;           //是否可以移动;true--可以移动;false--不可移动

    Ui::CLoginWindow *ui;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;

    //登录窗口
    void LoginWindow(void);

    //加密字符串
    QString CryptographicString(QString _Content);

    //读取用户名和密码设置
    void ReadSettings(void);

    //保存用户名和密码配置
    void WriteSettings(void);

};

#endif // LOGINWINDOW_H
