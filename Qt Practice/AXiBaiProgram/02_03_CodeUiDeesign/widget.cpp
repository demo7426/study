/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	widget.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.23
描  述:	使用纯代码设计ui
备  注:
修改记录:

  1.  日期: 2024.08.23
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QLayout>
#include <QGroupBox>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    InitUi();
    InitSignalAndSlots();
}

Widget::~Widget()
{
    delete m_pcCheckBoxUnderline;
    delete m_pcCheckBoxItalic;
    delete m_pcCheckBoxBold;
    delete m_pcRadioBtnRed;
    delete m_pcRadioBtnGreen;
    delete m_pcRadioBtnBlue;
    delete m_pcPlainTextEdit;
    delete m_pcPushBtnOK;
    delete m_pcPushBtnCancel;
    delete m_pcPushBtnQuit;
}

void Widget::InitUi() throw()
{
    //不能使用this指针;
    //比如：QHBoxLayout* pcHBOXLayout_CheckBox = new QHBoxLayout(this);

    QHBoxLayout* pcHBOXLayout_CheckBox = new QHBoxLayout();
    QHBoxLayout* pcHBOXLayout_RadioBtn = new QHBoxLayout();
    QHBoxLayout* pcHBOXLayout_PushBtn = new QHBoxLayout();

    QGroupBox* pcGroupBox = new QGroupBox();

    QVBoxLayout* pcVBoxLayout_Widget = new QVBoxLayout();
    QFont cPlainTextEditFont;

    //设置checkBox格式
    m_pcCheckBoxUnderline = new QCheckBox(tr("Underline"));
    m_pcCheckBoxItalic = new QCheckBox(tr("Italic"));
    m_pcCheckBoxBold = new QCheckBox(tr("Bold"));

    pcHBOXLayout_CheckBox->addWidget(m_pcCheckBoxUnderline);
    pcHBOXLayout_CheckBox->addWidget(m_pcCheckBoxItalic);
    pcHBOXLayout_CheckBox->addWidget(m_pcCheckBoxBold);

    //设置radioButton格式
    m_pcRadioBtnRed = new QRadioButton(tr("Red"));
    m_pcRadioBtnGreen = new QRadioButton(tr("Green"));
    m_pcRadioBtnBlue = new QRadioButton(tr("Blue"));

    pcHBOXLayout_RadioBtn->addWidget(m_pcRadioBtnRed);
    pcHBOXLayout_RadioBtn->addWidget(m_pcRadioBtnGreen);
    pcHBOXLayout_RadioBtn->addWidget(m_pcRadioBtnBlue);
    pcGroupBox->setLayout(pcHBOXLayout_RadioBtn);

    m_pcPlainTextEdit = new QPlainTextEdit(tr("Hello World.\nThis is QPlainTextEdit."));

    cPlainTextEditFont = m_pcPlainTextEdit->font();
    cPlainTextEditFont.setPointSize(19);
    m_pcPlainTextEdit->setFont(cPlainTextEditFont);

    //设置pushButton格式
    m_pcPushBtnOK = new QPushButton(tr("确定"));
    m_pcPushBtnCancel = new QPushButton(tr("取消"));
    m_pcPushBtnQuit = new QPushButton(tr("推出"));

    pcHBOXLayout_PushBtn->addStretch();
    pcHBOXLayout_PushBtn->addWidget(m_pcPushBtnOK);
    pcHBOXLayout_PushBtn->addWidget(m_pcPushBtnCancel);
    pcHBOXLayout_PushBtn->addStretch();
    pcHBOXLayout_PushBtn->addWidget(m_pcPushBtnQuit);

    //设置总体布局
    pcVBoxLayout_Widget->addLayout(pcHBOXLayout_CheckBox);
    pcVBoxLayout_Widget->addWidget(pcGroupBox);
    pcVBoxLayout_Widget->addWidget(m_pcPlainTextEdit);
    pcVBoxLayout_Widget->addLayout(pcHBOXLayout_PushBtn);

    this->setLayout(pcVBoxLayout_Widget);
}

void Widget::InitSignalAndSlots() throw()
{
    connect(m_pcCheckBoxUnderline, SIGNAL(clicked(bool)), this, SLOT(SetUnderline(bool)));
    connect(m_pcCheckBoxItalic, SIGNAL(clicked(bool)), this, SLOT(SetItalic(bool)));
    connect(m_pcCheckBoxBold, SIGNAL(clicked(bool)), this, SLOT(SetBold(bool)));

    connect(m_pcRadioBtnRed, SIGNAL(clicked(bool)), this, SLOT(SetPlainTextEditFontColor()));
    connect(m_pcRadioBtnGreen, SIGNAL(clicked(bool)), this, SLOT(SetPlainTextEditFontColor()));
    connect(m_pcRadioBtnBlue, SIGNAL(clicked(bool)), this, SLOT(SetPlainTextEditFontColor()));

    connect(m_pcPushBtnOK, &QPushButton::clicked, this, &Widget::close);
    connect(m_pcPushBtnCancel, &QPushButton::clicked, this, &Widget::close);
    connect(m_pcPushBtnQuit, &QPushButton::clicked, this, &Widget::close);
}

void Widget::SetUnderline(bool _Checked) noexcept
{
    QFont cFont = m_pcPlainTextEdit->font();

    cFont.setUnderline(_Checked);
    m_pcPlainTextEdit->setFont(cFont);
}

void Widget::SetItalic(bool _Checked) noexcept
{
    QFont cFont = m_pcPlainTextEdit->font();

    cFont.setItalic(_Checked);
    m_pcPlainTextEdit->setFont(cFont);
}

void Widget::SetBold(bool _Checked) noexcept
{
    QFont cFont = m_pcPlainTextEdit->font();

    cFont.setBold(_Checked);
    m_pcPlainTextEdit->setFont(cFont);
}

void Widget::SetPlainTextEditFontColor() noexcept
{
    QPalette cPalette = m_pcPlainTextEdit->palette();

    if(m_pcRadioBtnRed->isChecked())
        cPalette.setColor(QPalette::Text, Qt::red);
    else if(m_pcRadioBtnGreen->isChecked())
        cPalette.setColor(QPalette::Text, Qt::green);
    else if(m_pcRadioBtnBlue->isChecked())
        cPalette.setColor(QPalette::Text, Qt::blue);
    else
        cPalette.setColor(QPalette::Text, Qt::black);

    m_pcPlainTextEdit->setPalette(cPalette);
}
