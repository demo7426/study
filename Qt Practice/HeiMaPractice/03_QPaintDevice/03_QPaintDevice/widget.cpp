#include "widget.h"
#include "ui_widget.h"
#include<QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //QPixmap做绘图设备，对不同平台做了显示优化
    QPixmap pix(300, 300);

    pix.fill(Qt::white);//填充颜色

    QPainter painter(&pix);

    painter.setPen(Qt::red);
    painter.drawEllipse(100, 100, 50, 50);

    pix.save("pix.png");

    //QImage做绘图设备  不同平台下显示效果是一样的，但是可以访问像素
    QImage img(300, 300, QImage::Format_RGB32);

    img.fill(Qt::white);

    QPainter painter2(&img);

    painter2.setPen(Qt::blue);
    painter2.drawEllipse(100, 100, 50, 50);

    img.save("img.png");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QImage img;
    img.load(":/new/prefix1/Image/butterfly.png");

    //修改像素点
    for(int i = 50; i < 100; i++)
    {
        for (int j = 50; j < 100; j++)
        {
            QRgb value = qRgb(255, 0, 0);
            img.setPixel(i, j, value);
        }
    }

    QPainter painter(this);
    painter.drawImage(0, 0, img);

}
