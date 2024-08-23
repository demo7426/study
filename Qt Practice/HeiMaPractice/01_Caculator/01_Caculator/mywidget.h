#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include<QString>
#include<assignedandcaculate.h>
#include<QPushButton>
#include<QLCDNumber>


extern QTextEdit* m_pLCDNumber;

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();


    AssignedAndCaculate* m_pAssignedAndCacul;
};
#endif // MYWIDGET_H
