#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //启动定时器事件
    m_nId1 = startTimer(1000);
    m_nId2 = startTimer(2000);

    QTimer *cTimer = new QTimer(this);

    cTimer->start(500);

    connect(cTimer, &QTimer::timeout, this, [=](){
        ui->label_4->setText(QString::number(m_nNum++));
    });


    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
        cTimer->stop();
    });

    connect(ui->pushButton_2, &QPushButton::clicked, this, [=](){
        cTimer->start(500);
    });

    //安装过滤器
    ui->label->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

//重写定时器事件
void Widget::timerEvent(QTimerEvent *event)
{
    if(m_nId1 == event->timerId())
    {
        static int nNum = 0;
        ui->label_2->setText(QString::number(nNum++));
    }

    if(m_nId2 == event->timerId())
    {
        static int nNum2 = 0;
        ui->label_3->setText(QString::number(nNum2+=2));
    }

}

//重写过滤器事件
bool Widget::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == ui->label)
    {
        if(ev->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *MouseEv = static_cast<QMouseEvent *>(ev);

            QString str = QString("eventFilter：鼠标按压：x = %1, y = %2").arg(MouseEv->x()). arg(MouseEv->y());
            qDebug() << str;
            return true;
        }
    }

    //其他事件抛给父类
    return QWidget::eventFilter(obj, ev);
}
