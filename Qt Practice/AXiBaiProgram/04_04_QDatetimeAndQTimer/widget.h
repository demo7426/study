/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	widget.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.30
描  述:	实现当前的widget ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.08.30
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef WIDGET_H
#define WIDGET_H

#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include <QWidget>

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
    QTimer m_cTimer;            //定时器
    QElapsedTimer m_cElapsedTimer;


private:
    Ui::Widget *ui;

private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;

private slots:
    /// <summary>
    /// 初始化当前界面的日期时间
    /// </summary>
    void InitCurDateTime(void) noexcept;

    /// <summary>
    /// 在界面设置当前ui界面的所有日期时间
    /// </summary>
    void SetCurAllDatetime(void) noexcept;

    /// <summary>
    /// 设置LCD的值
    /// </summary>
    void SetLCDNum(void) noexcept;

};
#endif // WIDGET_H
