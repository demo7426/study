/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	widget.h.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.24
描  述:	实现前后端界面的交互控制
备  注:
修改记录:

  1.  日期: 2024.08.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include "widget.h"
#include "ui_widget.h"

#define RTN_FAILURE -2
#define RTN_SUCCESS 0

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

void Widget::InitUi(void) noexcept
{
    constexpr qint32 nAge[2] { 14, 13 };

    m_cPersonBoy.setProperty("Name", "张三");
    m_cPersonBoy.setProperty("Sex", true);
    m_cPersonBoy.setProperty("Age", nAge[0]);
    m_cPersonBoy.setProperty("Score", 90);

    m_cPersonGirl.setProperty("Name", "翠花");
    m_cPersonGirl.setProperty("Sex", false);
    m_cPersonGirl.setProperty("Age", nAge[1]);
    m_cPersonGirl.setProperty("Score", 60);

    ui->spinBoxBoy->setValue(nAge[0]);
    ui->spinBoxGirl->setValue(nAge[1]);
}

void Widget::InitSignalSlots(void) noexcept
{
    //设置后端数据的的信号槽
    connect(&m_cPersonBoy, &CPerson::NameChanged, this, &Widget::AppendNameToPlainTextEdit);
    connect(&m_cPersonBoy, &CPerson::SexChanged, this, &Widget::AppendSexToPlainTextEdit);
    connect(&m_cPersonBoy, &CPerson::AgeChanged, this, &Widget::AppendAgeToPlainTextEdit);
    connect(&m_cPersonBoy, &CPerson::ScoreChanged, this, &Widget::AppendScoreToPlainTextEdit);

    connect(&m_cPersonGirl, &CPerson::NameChanged, this, &Widget::AppendNameToPlainTextEdit);
    connect(&m_cPersonGirl, &CPerson::SexChanged, this, &Widget::AppendSexToPlainTextEdit);
    connect(&m_cPersonGirl, &CPerson::AgeChanged, this, &Widget::AppendAgeToPlainTextEdit);
    connect(&m_cPersonGirl, &CPerson::ScoreChanged, this, &Widget::AppendScoreToPlainTextEdit);

    //设置ui界面的信号槽
    connect(ui->spinBoxBoy, &QSpinBox::valueChanged, this, [=](int _Value){
        m_cPersonBoy.setProperty("Age", _Value);
    });

    connect(ui->spinBoxGirl, &QSpinBox::valueChanged, this, [=](int _Value){
        m_cPersonGirl.setProperty("Age", _Value);
    });

    connect(ui->pushBtnBoyInc, &QPushButton::clicked, this,[=](){
        qint32 nAge = m_cPersonBoy.property("Age").toInt();

        m_cPersonBoy.setProperty("Age", ++nAge);
        ui->spinBoxBoy->setValue(nAge);
    });

    connect(ui->pushBtnGirlInc, &QPushButton::clicked, this,[=](){
        qint32 nAge = m_cPersonGirl.property("Age").toInt();

        m_cPersonGirl.setProperty("Age", ++nAge);
        ui->spinBoxGirl->setValue(nAge);
    });

    connect(ui->pushBtnMetaObjInfo, &QPushButton::clicked, this, &Widget::RefreshCurPlainTextEditData);
    connect(ui->pushBtnClear, &QPushButton::clicked, this, &Widget::ClearCurPlainTextEditData);
}

int Widget::RefreshCurPlainTextEditData(void) noexcept
{
    QString strName = m_cPersonBoy.property("Name").toString();
    bool bSex = m_cPersonBoy.property("Sex").toBool();
    qint32 nAge = m_cPersonBoy.property("Age").toInt();
    qint32 nScore = m_cPersonBoy.property("Score").toInt();

    ui->plainTextEdit->appendPlainText(QString("姓氏: %1").arg(strName));
    if(bSex)
        ui->plainTextEdit->appendPlainText(QString("性别: 男性"));
    else
        ui->plainTextEdit->appendPlainText(QString("性别: 女性"));
    ui->plainTextEdit->appendPlainText(QString("年龄: %1").arg(nAge));
    ui->plainTextEdit->appendPlainText(QString("分数: %1\n").arg(nScore));

    strName = m_cPersonGirl.property("Name").toString();
    bSex = m_cPersonGirl.property("Sex").toBool();
    nAge = m_cPersonGirl.property("Age").toInt();
    nScore = m_cPersonGirl.property("Score").toInt();

    ui->plainTextEdit->appendPlainText(QString("姓氏: %1").arg(strName));
    if(bSex)
        ui->plainTextEdit->appendPlainText(QString("性别: 男性"));
    else
        ui->plainTextEdit->appendPlainText(QString("性别: 女性"));
    ui->plainTextEdit->appendPlainText(QString("年龄: %1").arg(nAge));
    ui->plainTextEdit->appendPlainText(QString("分数: %1\n").arg(nScore));

    return RTN_SUCCESS;
}

int Widget::ClearCurPlainTextEditData() noexcept
{
    ui->plainTextEdit->clear();
    return RTN_SUCCESS;
}

void Widget::AppendNameToPlainTextEdit() noexcept
{
    CPerson* pcPerson = qobject_cast<CPerson*>(sender());
    QString strName = pcPerson->property("Name").toString();

    ui->plainTextEdit->appendPlainText(QString("姓氏: %1").arg(strName));
}

void Widget::AppendSexToPlainTextEdit() noexcept
{
    CPerson* pcPerson = qobject_cast<CPerson*>(sender());
    bool bSex = pcPerson->property("Sex").toBool();

    if(bSex)
        ui->plainTextEdit->appendPlainText(QString("性别: 男性"));
    else
        ui->plainTextEdit->appendPlainText(QString("性别: 女性"));
}

void Widget::AppendAgeToPlainTextEdit() noexcept
{
    CPerson* pcPerson = qobject_cast<CPerson*>(sender());
    qint32 nAge = pcPerson->property("Age").toInt();

    ui->plainTextEdit->appendPlainText(QString("年龄: %1").arg(nAge));
}

void Widget::AppendScoreToPlainTextEdit() noexcept
{
    CPerson* pcPerson = qobject_cast<CPerson*>(sender());
    qint32 nScore = pcPerson->property("Score").toInt();

    ui->plainTextEdit->appendPlainText(QString("分数: %1").arg(nScore));
}
