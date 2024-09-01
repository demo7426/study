/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.01
描  述:	实现当前的widget ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUi() noexcept
{
    QMenu* pcMenu = new QMenu(this);

    ui->toolBtnInitListWidget->setDefaultAction(ui->actListIni);
    ui->toolBtnClearListWidget->setDefaultAction(ui->actListClear);
    ui->toolBtnInsertItem->setDefaultAction(ui->actListInsert);
    ui->toolBtnAddItem->setDefaultAction(ui->actListAppend);
    ui->toolBtnDeleteItem->setDefaultAction(ui->actListDelete);

    pcMenu->addAction(ui->actListIni);
    pcMenu->addAction(ui->actListClear);
    pcMenu->addAction(ui->actListInsert);
    pcMenu->addAction(ui->actListAppend);

    ui->actSelPopMenu->setMenu(pcMenu);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actSelPopMenu);
    ui->toolBar->addAction(ui->actQuit);

    ui->toolBtnSelectItem->setDefaultAction(ui->actSelPopMenu);
    ui->toolBtnSelectAllItem->setDefaultAction(ui->actSelALL);
    ui->toolBtnSelectNoneItem->setDefaultAction(ui->actSelNone);
    ui->toolBtnSelectInvertItem->setDefaultAction(ui->actSelInvs);
}

void MainWindow::InitSignalSlots() noexcept
{
    connect(ui->toolBox, &QToolBox::currentChanged, this, [=](int _Index){
        ui->tabWidget->setCurrentIndex(_Index);
    });

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, [=](int _Index){
        ui->toolBox->setCurrentIndex(_Index);
    });

    connect(ui->actListIni, &QAction::triggered, this, &MainWindow::InitListWidget);
    connect(ui->actListClear, &QAction::triggered, this, [=](){
        this->ClearListWidget(ui->listWidget);
    });

    connect(ui->actListInsert, &QAction::triggered, this, [=](){
        QListWidgetItem* pcListWidgetItem = new QListWidgetItem(QIcon(":/images/icons/check2.ico"), QString::asprintf("item: insert"));
        pcListWidgetItem->setCheckState(Qt::Checked);

        ui->listWidget->insertItem(ui->listWidget->currentRow(), pcListWidgetItem);
    });

    connect(ui->actListAppend, &QAction::triggered, this, [=](){
        QListWidgetItem* pcListWidgetItem = new QListWidgetItem(QIcon(":/images/icons/check2.ico"), QString::asprintf("item: append"));
        pcListWidgetItem->setCheckState(Qt::Checked);

        ui->listWidget->addItem(pcListWidgetItem);
    });

    connect(ui->actListDelete, &QAction::triggered, this, [=](){
        QListWidgetItem* pcListWidgetItem = ui->listWidget->takeItem(ui->listWidget->currentRow());
        ui->listWidget->removeItemWidget(pcListWidgetItem);
        delete pcListWidgetItem;
    });

    connect(ui->actSelALL, &QAction::triggered, this, [=](){
        QListWidgetItem* pcListWidgetItem = nullptr;
        qint32 nRowCount = ui->listWidget->count();             //必须先取出当前QListWidget的行数

        for (int i = 0; i < nRowCount; ++i)
        {
            pcListWidgetItem = ui->listWidget->item(i);
            pcListWidgetItem->setCheckState(Qt::Checked);
        }
    });

    connect(ui->actSelNone, &QAction::triggered, this, [=](){
        QListWidgetItem* pcListWidgetItem = nullptr;
        qint32 nRowCount = ui->listWidget->count();

        for (int i = 0; i < nRowCount; ++i)
        {
            pcListWidgetItem = ui->listWidget->item(i);
            pcListWidgetItem->setCheckState(Qt::Unchecked);
        }
    });

    connect(ui->actSelInvs, &QAction::triggered, this, [=](){
        QListWidgetItem* pcListWidgetItem = ui->listWidget->currentItem();

        if(pcListWidgetItem == nullptr)
            return;

        if(pcListWidgetItem->checkState())
            pcListWidgetItem->setCheckState(Qt::Unchecked);
        else
            pcListWidgetItem->setCheckState(Qt::Checked);
    });

    connect(ui->listWidget, &QListWidget::customContextMenuRequested, this, [=](const QPoint &pos){
        QMenu* pcMenu = new QMenu(this);

        pcMenu->addAction(ui->actListIni);
        pcMenu->addAction(ui->actListClear);
        pcMenu->addAction(ui->actListInsert);
        pcMenu->addAction(ui->actListAppend);
        pcMenu->addAction(ui->actListDelete);

        pcMenu->exec(QCursor::pos());

        delete pcMenu;
    });
}

void MainWindow::InitListWidget() throw()
{
    bool IsEdit = ui->checkBoxIsEdit->isChecked();

    ClearListWidget(ui->listWidget);

    for (qint32 i = 0; i < 10; ++i) {
        QListWidgetItem* pcListWidgetItem = new QListWidgetItem();

        pcListWidgetItem->setIcon(QIcon(":/images/icons/check2.ico"));
        pcListWidgetItem->setText(QString::asprintf("item: %d", i));

        pcListWidgetItem->setCheckState(Qt::Checked);                    //显示复选框

        if(IsEdit)
            pcListWidgetItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
        else
            pcListWidgetItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable);

        qDebug() <<  "Init QListWidget row is"<< i << " " << pcListWidgetItem;

        ui->listWidget->addItem(pcListWidgetItem);
    }
}

qint32 MainWindow::ClearListWidget(QListWidget *_pListWidget) noexcept
{
    if(_pListWidget == nullptr)
    {
        qDebug() << "ClearListWidget input param is err.";
        return -2;
    }

    _pListWidget->clear();

    return 0;
}
