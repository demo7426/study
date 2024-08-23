#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //测试 QVariant 变量类型
    //QVariant可以封装所有的数据类型

    //QVariant封装系统自带的数据类型
    qDebug() << "10 + 20 = "<< this->PlusData(10, 20).toInt();
    qDebug() << "Hello  + world = "<< this->PlusData("Hello ", "world").toString();

    //QVariant封装用户自定义的数据类型
    PERSON_INFO tPerson_Info = {39, "Cristiano Ronaldo"};
    QVariant qVar;
#if 0
    qVar.setValue(tPerson_Info);
#else
    qVar = QVariant::fromValue(tPerson_Info);
#endif

    if(qVar.canConvert<PERSON_INFO>())
    {
        PERSON_INFO tPerson_tmp = qVar.value<PERSON_INFO>();
        qDebug() << "Age: " << tPerson_tmp.Age << " Name: " << tPerson_tmp.Name;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVariant MainWindow::PlusData(QVariant _X, QVariant _Y)
{
    QVariant qVarRtn;
    if(_X.typeId() == QMetaType::Int && _Y.typeId() == QMetaType::Int)
    {
        qVarRtn = QVariant(_X.toInt() + _Y.toInt());
    }
    else if(_X.typeId() == QMetaType::QString && _Y.typeId() == QMetaType::QString)
    {
        qVarRtn.setValue(_X.toString() + _Y.toString());
    }

    return qVarRtn;
}
