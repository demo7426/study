#ifndef WIDGET_H
#define WIDGET_H

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
    /// 设置ui界面TextEdit的背景色
    /// </summary>
    /// <param name="_Value"></param>
    void SetTextEditBackgroundColor(int _Value);

    /// <summary>
    /// 水平相应值被修改
    /// </summary>
    /// <param name="_Value"></param>
    void HorizontalValueChanged(int _Value);

    /// <summary>
    /// 垂直相应值被修改
    /// </summary>
    /// <param name="_Value"></param>
    void VerticalValueChanged(int _Value);

    /// <summary>
    /// 设置LCD显示屏的值
    /// </summary>
    /// <param name="_Value"></param>
    void SetLCDNum(int _Value);
};
#endif // WIDGET_H
