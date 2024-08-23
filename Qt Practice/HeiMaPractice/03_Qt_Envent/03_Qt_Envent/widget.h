#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    //重写定时器事件
    void timerEvent(QTimerEvent *event);

    //重写过滤器事件
    bool eventFilter(QObject *obj, QEvent *ev);
private:
    Ui::Widget *ui;

    //starttimer返回id
    int m_nId1 = 0;
    int m_nId2 = 0;

    int m_nNum = 0;
};
#endif // WIDGET_H
