/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	widget.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.08
描  述:	实现当前的widget ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.08
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

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

    if(m_pcFielSystemModel != nullptr)
        delete m_pcFielSystemModel;
}

void Widget::InitUi() noexcept
{
    m_pcFielSystemModel = new QFileSystemModel(this);

    m_pcFielSystemModel->setRootPath(QDir::currentPath());

    ui->treeView->setModel(m_pcFielSystemModel);
    ui->tableView->setModel(m_pcFielSystemModel);
    ui->listView->setModel(m_pcFielSystemModel);

    ui->tableView->verticalHeader()->setVisible(false);
}

void Widget::InitSignalSlots() noexcept
{
    connect(ui->treeView, &QTreeView::clicked, this, [this](const QModelIndex &_Index){
        ui->tableView->setRootIndex(_Index);
        ui->listView->setRootIndex(_Index);

        ui->tableView->resizeColumnsToContents();                   //自适应字符串宽度

        ui->labelModeName->setText(QString::asprintf("文件名:%s", m_pcFielSystemModel->fileName(_Index).toStdString().data()));
        ui->labelModeSize->setText(QString::asprintf("文件大小:%lluKB", m_pcFielSystemModel->size(_Index) / 1024));

        ui->labelModeType->setText(QString::asprintf("文件类型:%s", m_pcFielSystemModel->type(_Index).toStdString().data()));
        ui->labelModePath->setText("文件路径:" + m_pcFielSystemModel->filePath(_Index));

        ui->checkBox->setChecked(!m_pcFielSystemModel->isDir(_Index));
    });


}
