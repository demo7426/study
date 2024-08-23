/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	widget.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.23
描  述:	使用纯代码设计ui
备  注:
修改记录:

  1.  日期: 2024.08.23
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QCheckBox* m_pcCheckBoxUnderline = nullptr;
    QCheckBox* m_pcCheckBoxItalic = nullptr;
    QCheckBox* m_pcCheckBoxBold = nullptr;

    QRadioButton* m_pcRadioBtnRed = nullptr;
    QRadioButton* m_pcRadioBtnGreen = nullptr;
    QRadioButton* m_pcRadioBtnBlue = nullptr;

    QPlainTextEdit* m_pcPlainTextEdit = nullptr;

    QPushButton* m_pcPushBtnOK = nullptr;
    QPushButton* m_pcPushBtnCancel = nullptr;
    QPushButton* m_pcPushBtnQuit = nullptr;
private:

    //初始化ui界面
    void InitUi(void) throw();

    //初始化信号槽
    void InitSignalAndSlots(void) throw();

private slots:

    //设置下划线
    void SetUnderline(bool _Checked) noexcept;

    void SetItalic(bool _Checked) noexcept;

    void SetBold(bool _Checked) noexcept;

    //设置PlainTextEdit字体颜色
    void SetPlainTextEditFontColor(void) noexcept;
};
#endif // WIDGET_H
