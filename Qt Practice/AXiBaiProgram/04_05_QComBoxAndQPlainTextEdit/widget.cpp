/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	widget.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.31
描  述:	实现当前的widget ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.08.31
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QTextBlock>
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::InitUi() noexcept
{

}

void Widget::InitSignalSlots() noexcept
{
    connect(ui->pushBtnInitList, &QPushButton::clicked, this, &Widget::InitComboBox);
    connect(ui->pushBtnClearList, &QPushButton::clicked, this, [this](){
        ui->comboBoxCity->clear();
    });

    connect(ui->checkBoxIsEdit, &QCheckBox::stateChanged, this, [this](int _State){
        ui->comboBoxCity->setEditable(_State);
    });

    connect(ui->pushBtnInitCityAreaCode, &QPushButton::clicked, this, [this](){
        QString strCityName = ui->comboBoxCityAreaCode->currentText();
        ui->plainTextEdit->appendPlainText(strCityName + ": 06100");
    });

    connect(ui->comboBoxCity, &QComboBox::currentTextChanged, this, [this](const QString& _CityName){
        if(!_CityName.isEmpty())
            ui->plainTextEdit->appendPlainText(_CityName);
    });

    connect(ui->comboBoxCityAreaCode, &QComboBox::currentTextChanged, this, [this](const QString& _CityName){
        if(!_CityName.isEmpty())
            ui->plainTextEdit->appendPlainText(_CityName);
    });

    connect(ui->checkBoxIsWrite, &QCheckBox::stateChanged, this, [this](int _State){
            ui->plainTextEdit->setReadOnly(_State);
    });

    connect(ui->pushBtnAddTextToComboBox, &QPushButton::clicked, this, &Widget::PlainTextToComboBox);

    connect(ui->pushBtnClearText, &QPushButton::clicked, this, [this](){
        ui->plainTextEdit->clear();
    });
}

void Widget::InitComboBox() noexcept
{
    QStringList cStringListCity;

    cStringListCity.clear();
    cStringListCity.insert(cStringListCity.count(), "北京");
    cStringListCity.insert(cStringListCity.count(), "上海");
    cStringListCity.insert(cStringListCity.count(), "广州");
    cStringListCity.insert(cStringListCity.count(), "成都");

    ui->comboBoxCity->clear();

    foreach (auto var, cStringListCity) {
        ui->comboBoxCity->addItem(QIcon(":/icon/imgs/city.png"), var);
    }
}

void Widget::PlainTextToComboBox() noexcept
{
    QTextDocument* pcTextDocument = ui->plainTextEdit->document();
    qint32 nLineNum = pcTextDocument->lineCount();

    for (int i = 0; i < nLineNum; ++i) {
        ui->comboBoxCity->addItem(pcTextDocument->findBlockByLineNumber(i).text());
    }
}
