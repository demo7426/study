#ifndef CMYBUTTON_H
#define CMYBUTTON_H

#include <QWidget>

class CMyButton : public QWidget
{
    Q_OBJECT
public:
    explicit CMyButton(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    void enterEvent(QEnterEvent* ev) override;
    void leaveEvent(QEvent* ev) override;

    void paintEvent(QPaintEvent* ev) override;              //绘图事件

signals:
    void Pressed();

private:
    QPixmap m_cQPixmap;

signals:
};

#endif // CMYBUTTON_H
