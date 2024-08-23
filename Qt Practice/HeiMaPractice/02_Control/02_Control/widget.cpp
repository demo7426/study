#include "widget.h"
#include "ui_widget.h"
#include"QDebug"
#include"QStringList"
#include"QMovie"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置默认选中男性、未婚
    ui->radioButton->setChecked(true);
    ui->radioButton_4->setChecked(true);

    connect(ui->radioButton, &QRadioButton::clicked, this, [=](){
        qDebug()<<"选择了男性";
    });

    connect(ui->radioButton_2, &QRadioButton::clicked, this, [=](){
        qDebug()<<"选择了女性";
    });

    connect(ui->checkBox, &QCheckBox::stateChanged, this, [=](int State){
        if(State == 1)
            qDebug()<<"选中了力量+0.5";
        else if(State == 2)
            qDebug()<<"选中了力量+1";
    });

    //listWidget控件
    QListWidgetItem *ListWidgetItem = new QListWidgetItem("悯农");
    ui->listWidget->addItem(ListWidgetItem);
    ListWidgetItem->setTextAlignment(Qt::AlignHCenter);

    QStringList list;
    list<<"锄禾日当午"<<"汗滴禾下土"<<"谁知盘中餐"<<"粒粒皆辛苦";
    ui->listWidget->addItems(list);

    //treeWidget控件
    ui->treeWidget->setHeaderLabels(QStringList()<<"英雄"<<"英雄简介");

    QTreeWidgetItem *StrengthItem = new QTreeWidgetItem(QStringList()<<"亚瑟");
    QTreeWidgetItem *QuickItem = new QTreeWidgetItem(QStringList()<<"白起");
    QTreeWidgetItem *IntelligenceItem = new QTreeWidgetItem(QStringList()<<"芈月");

    ui->treeWidget->addTopLevelItem(StrengthItem);
    ui->treeWidget->addTopLevelItem(QuickItem);
    ui->treeWidget->addTopLevelItem(IntelligenceItem);

    QTreeWidgetItem *StrengthItem_1 = new QTreeWidgetItem(QStringList()<<"战士"<<"上路");
    StrengthItem->addChild(StrengthItem_1);

    QTreeWidgetItem *QuickItem_1 = new QTreeWidgetItem(QStringList()<<"坦克"<<"上路");
    QuickItem->addChild(QuickItem_1);

    //tableWidget控件
    ui->tableWidget->setRowCount(5);//设置行数
    ui->tableWidget->setColumnCount(3);//设置列数
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"性别"<<"年龄");//设置表头

    QStringList nameList ;
    nameList<<"亚瑟"<<"妲己"<<"安琪拉"<<"白起"<<"芈月";
    QStringList sexList;
    sexList<<"男"<<"女"<<"女"<<"男"<<"女";

    for (int i = 0; i < 5; i++)
    {
        int Column = 0;
        ui->tableWidget->setItem(i, Column++, new QTableWidgetItem(nameList[i]));
        ui->tableWidget->setItem(i, Column++, new QTableWidgetItem(sexList.at(i)));
        ui->tableWidget->setItem(i, Column++, new QTableWidgetItem(QString::number(i+18)));
    }


    //切换stackedWidget页面
    connect(ui->pushButton_13, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->pushButton_14, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->pushButton_15, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);
    });

    //设置下拉框
    ui->comboBox->addItem("奔驰");
    ui->comboBox->addItem("宝马");
    ui->comboBox->addItem("奥迪");

    connect(ui->pushButton_16, &QPushButton::clicked,this,[=](){
        ui->comboBox->setCurrentIndex(1);
    });

    ui->label->setPixmap(QPixmap(":/new/prefix1/icon/4.png"));

    QMovie* movie = new QMovie(":/new/prefix1/mario.gif");
    ui->label_2->setMovie(movie);
    movie->start();
}

Widget::~Widget()
{
    delete ui;
}

