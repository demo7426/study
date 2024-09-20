/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	dialogheaders.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.20
描  述:	用于设置QTableView的表头
备  注:
修改记录:

  1.  日期: 2024.09.20
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include "dialogheaders.h"
#include "ui_dialogheaders.h"

CDialogHeaders::CDialogHeaders(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CDialogHeaders)
{
    ui->setupUi(this);
    InitUi();
    InitSignalSlots();
}

CDialogHeaders::~CDialogHeaders()
{
    delete ui;

    if(m_pcStringListModel != nullptr)
        delete m_pcStringListModel;
}

void CDialogHeaders::SetListView(const QStringList _StrList)
{
    m_pcStringListModel->setStringList(_StrList);
    ui->listView->setModel(m_pcStringListModel);
}

void CDialogHeaders::InitUi() noexcept
{
    m_pcStringListModel = new QStringListModel;

}

void CDialogHeaders::InitSignalSlots() noexcept
{
    connect(ui->btnOK, &QPushButton::clicked, this, [=](){
        QStringList strList;

        strList.clear();
        strList = m_pcStringListModel->stringList();

        emit ListViewChanged(strList);
        this->hide();
    });
}
