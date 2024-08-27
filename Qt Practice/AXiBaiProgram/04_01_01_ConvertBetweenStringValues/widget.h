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
    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;

private slots:
    /// <summary>
    /// 计算总价
    /// </summary>
    void CalTotalPrice(void);

    /// <summary>
    /// 数值转换
    /// </summary>
    void NumConversion(void);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
