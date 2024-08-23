#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
public:
    explicit MyLabel(QWidget *parent = nullptr);

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected:
    //重写事件分发器
    bool event(QEvent *e);

signals:

};

#endif // MYLABEL_H
