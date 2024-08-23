#include "widget.h"
#include "ui_widget.h"
#include <QPainter>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this); 

    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
        if(m_nPosX >= this->width())
            m_nPosX = 0;
        else
            m_nPosX += 40;

        update();//手动调用绘图事件
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    /*QPainter painter(this);

    //设置画笔
    QPen pen(QColor(255, 0, 0));//设置画笔颜色
    pen.setWidth(4);//设置画笔宽度
    pen.setStyle(Qt::DotLine);//设置画笔风格

    painter.setPen(pen);

    //画刷
    QBrush brush(Qt::Dense1Pattern);//设置画刷风格
    painter.setBrush(brush);

    painter.drawLine(QPoint(0, 0), QPoint(100, 100));//画线

    painter.drawEllipse(QPoint(100, 100), 50, 50);//画圆

    painter.drawRect(150, 150, 50, 50);//画矩形

    painter.drawText(QRect(10, 200, 100, 150), "好好学习，天天向上");*/

    //高级设置/////////////////////////////////
    QPainter painter(this);

    /*painter.drawEllipse(QPoint(100, 100), 50, 50);

    painter.setRenderHint(QPainter::Antialiasing);//设置抗锯齿能力，更加的平滑但是降低了效率
    painter.drawEllipse(QPoint(250, 100), 50, 50);*/

    painter.drawRect(20, 20, 50, 50);//画矩形

    painter.translate(100, 0);//移动原点坐标
    painter.save();//保存原点坐标状态

    painter.drawRect(20, 20, 50, 50);//画矩形

    painter.translate(100, 0);//移动原点坐标
    painter.restore();//取出原点保存的状态

    painter.drawRect(20, 20, 50, 50);//画矩形

    //显示图片
    QPainter painter2(this);
    painter2.drawPixmap(m_nPosX, 150, QPixmap(":/new/prefix2/Image/butterfly.png"));

}

