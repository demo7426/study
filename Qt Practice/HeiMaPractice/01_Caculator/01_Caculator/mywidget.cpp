#include "mywidget.h"
#include<QPushButton>
#include<QString>

QTextEdit* m_pLCDNumber;

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(400, 300);
    this->setWindowTitle("Caculator");

    //设置1-9的数字按钮
    QPushButton *m_pBtn[17];
    for(int i = 0; i < 9; i++)
    {
        m_pBtn[i] = new QPushButton;

        m_pBtn[i]->setParent(this);

        m_pBtn[i]->setText(QString::number(i+1));
        m_pBtn[i]->resize(60, 40);

        m_pBtn[i]->move(50 + (i % 3) * 70, 100 + 50 * (i / 3));
    }

    //设置0的数字按钮
    for(int i = 9; i < 17; i++)
    {
        m_pBtn[i] = new QPushButton;
        m_pBtn[i]->setParent(this);
        m_pBtn[i]->resize(60, 40);
    }

    m_pBtn[9]->setText("0");
    m_pBtn[9]->move(120, 250);

    m_pBtn[10]->setText("/");
    m_pBtn[10]->move(260, 100);

    m_pBtn[11]->setText("*");
    m_pBtn[11]->move(260, 150);

    m_pBtn[12]->setText("-");
    m_pBtn[12]->move(260, 200);

    m_pBtn[13]->setText("+");
    m_pBtn[13]->move(260, 250);

    m_pBtn[14]->setText(".");
    m_pBtn[14]->move(50, 250);

    m_pBtn[15]->setText("=");
    m_pBtn[15]->move(190, 250);

    m_pBtn[16]->resize(60, 190);
    m_pBtn[16]->setText("C");
    m_pBtn[16]->move(330, 100);

    m_pLCDNumber = new QTextEdit;
    m_pLCDNumber->setParent(this);
    m_pLCDNumber->resize(270, 100);
    m_pLCDNumber->move(50, 0);
    m_pLCDNumber->show(); 
    m_pLCDNumber->setReadOnly(true);
    m_pLCDNumber->setFontFamily("Consolas");


    this->m_pAssignedAndCacul = new AssignedAndCaculate(this);

    void (AssignedAndCaculate::*pAssign)() = &AssignedAndCaculate::Assignment;//使用函数指针调用，因为connect不支持带形参
    void (AssignedAndCaculate::*pCaculate)() = &AssignedAndCaculate::Caculate;//计算操作

    for(int i = 0; i < 15; i++)
    {
        connect(m_pBtn[i], &QPushButton::clicked, m_pAssignedAndCacul, pAssign);
    }
    connect(m_pBtn[15], &QPushButton::clicked, m_pAssignedAndCacul, pCaculate);
    connect(m_pBtn[16], &QPushButton::clicked, m_pAssignedAndCacul, &AssignedAndCaculate::Clear);
}

MyWidget::~MyWidget()
{
}
