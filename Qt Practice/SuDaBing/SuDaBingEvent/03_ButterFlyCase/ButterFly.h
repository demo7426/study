#ifndef CBUTTERFLY_H
#define CBUTTERFLY_H

#include <QWidget>
#include <QPixmap>

class CButterFly : public QWidget
{
    Q_OBJECT
public:
    explicit CButterFly(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;

private:
    void Fly(int _Min = 10, int _Max = 30);

private:
    QPixmap m_cQPixmap;
    QString m_strPicPath[2];                        //待显示图片路径
    int m_nCurPicPath_Index;                        //待显示图片索引

    QPoint m_cQPoint_Relative;                      //用于保存鼠标与图片左上角坐标的相对位置
signals:
};

#endif // CBUTTERFLY_H
