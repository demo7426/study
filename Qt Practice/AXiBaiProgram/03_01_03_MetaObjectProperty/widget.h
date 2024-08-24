/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	widget.h.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.24
描  述:	实现前后端界面的交互控制
备  注:
修改记录:

  1.  日期: 2024.08.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "person.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    CPerson m_cPersonBoy;
    CPerson m_cPersonGirl;

private:
    Ui::Widget *ui;

private:
    //初始化ui界面
    void InitUi(void) noexcept;

    //初始化信号槽
    void InitSignalSlots(void) noexcept;

private slots:
    //刷新当前文本的信息
    int RefreshCurPlainTextEditData(void) noexcept;

    //追加当前文本信息
    int ClearCurPlainTextEditData(void) noexcept;

    //当前文本信息追加姓氏信息
    void AppendNameToPlainTextEdit(void) noexcept;

    //当前文本信息追加性别信息
    void AppendSexToPlainTextEdit(void) noexcept;

    //当前文本信息追加年龄信息
    void AppendAgeToPlainTextEdit(void) noexcept;

    //当前文本信息追加分数信息
    void AppendScoreToPlainTextEdit(void) noexcept;
};
#endif // WIDGET_H
