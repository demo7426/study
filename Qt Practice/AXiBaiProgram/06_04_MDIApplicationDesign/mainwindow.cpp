/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.24
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QFileDialog>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QTabWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form.h"

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

void MainWindow::InitUi(void) noexcept
{
    this->setCentralWidget(ui->mdiArea);
}

void MainWindow::InitSignalSlots(void) noexcept
{
    connect(ui->actDoc_New, &QAction::triggered, this, &MainWindow::AddNewFormToMdiArea);
    connect(ui->actDoc_Open, &QAction::triggered, this, &MainWindow::OpenFileAndShowForm);
    connect(ui->actCloseALL, &QAction::triggered, this, [this](){
        ui->mdiArea->closeAllSubWindows();

        ui->actCopy->setEnabled(false);
        ui->actPaste->setEnabled(false);
        ui->actCut->setEnabled(false);
        ui->actFont->setEnabled(false);
    });


    connect(ui->actCopy, &QAction::triggered, this, [this](){
        QMdiSubWindow* pcMdiSubWindow = nullptr;
        CForm* pcForm = nullptr;

        pcMdiSubWindow = ui->mdiArea->currentSubWindow();

        if(pcMdiSubWindow == nullptr)
            return;

        pcForm = static_cast<CForm*>(pcMdiSubWindow->widget());
        pcForm->TextCopy();
    });

    connect(ui->actPaste, &QAction::triggered, this, [this](){
        QMdiSubWindow* pcMdiSubWindow = nullptr;
        CForm* pcForm = nullptr;

        pcMdiSubWindow = ui->mdiArea->currentSubWindow();

        if(pcMdiSubWindow == nullptr)
            return;

        pcForm = static_cast<CForm*>(pcMdiSubWindow->widget());
        pcForm->TextPaste();
    });

    connect(ui->actCut, &QAction::triggered, this, [this](){
        QMdiSubWindow* pcMdiSubWindow = nullptr;
        CForm* pcForm = nullptr;

        pcMdiSubWindow = ui->mdiArea->currentSubWindow();

        if(pcMdiSubWindow == nullptr)
            return;

        pcForm = static_cast<CForm*>(pcMdiSubWindow->widget());
        pcForm->TextCut();
    });

    connect(ui->actFont, &QAction::triggered, this, [this](){
        QMdiSubWindow* pcMdiSubWindow = nullptr;
        CForm* pcForm = nullptr;

        pcMdiSubWindow = ui->mdiArea->currentSubWindow();

        if(pcMdiSubWindow == nullptr)
            return;

        pcForm = static_cast<CForm*>(pcMdiSubWindow->widget());
        pcForm->SetTextFont();
    });

    connect(ui->mdiArea, &QMdiArea::subWindowActivated, this, [this](QMdiSubWindow *_pWindow){
        QMdiSubWindow* pcMdiSubWindow = nullptr;
        CForm* pcForm = nullptr;
        QFileInfo cFileInfo;

        if(_pWindow == nullptr)
        {
            ui->actCopy->setEnabled(false);
            ui->actPaste->setEnabled(false);
            ui->actCut->setEnabled(false);
            ui->actFont->setEnabled(false);
        }

        pcMdiSubWindow = ui->mdiArea->currentSubWindow();

        if(pcMdiSubWindow == nullptr)
            return;

        pcForm = static_cast<CForm*>(pcMdiSubWindow->widget());
        cFileInfo.setFile(pcForm->GetLoadFilePath());

        pcForm->setWindowTitle(cFileInfo.fileName());
        ui->statusbar->showMessage(cFileInfo.filePath());
    });

    connect(ui->actViewMode, &QAction::triggered, this, [this](bool _Checked){
        if(_Checked)
        {
            ui->mdiArea->setViewMode(QMdiArea::TabbedView);
            ui->mdiArea->setTabsClosable(true);
            ui->actCascade->setEnabled(false);
            ui->actTile->setEnabled(false);
        }
        else
        {
            ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
            ui->actCascade->setEnabled(true);
            ui->actTile->setEnabled(true);
        }
    });

    connect(ui->actCascade, &QAction::triggered, this, [this](){
        ui->mdiArea->cascadeSubWindows();
    });

    connect(ui->actTile, &QAction::triggered, this, [this](){
        ui->mdiArea->tileSubWindows();
    });
}

void MainWindow::AddNewFormToMdiArea() noexcept
{
    CForm *pcForm = new CForm();

    ui->mdiArea->addSubWindow(pcForm);          //关闭子窗口的时候，mdiArea会自动回收pcForm资源
    pcForm->show();
}

void MainWindow::OpenFileAndShowForm() noexcept
{
    QString strCurFilePath = QFileDialog::getOpenFileName(this, tr("选择单个文件"), QDir::currentPath(), tr("code(*.h *.c *.cpp);;所有文件(*.*)"));
    QMdiSubWindow* pcMdiSubWindow = nullptr;
    CForm* pcForm = nullptr;
    bool IsNewForm = false;                     //是否需要创建新的窗体

    pcMdiSubWindow = ui->mdiArea->currentSubWindow();

    if(pcMdiSubWindow == nullptr)               //若为空，则创建出一个新的窗口，并将数据写入其中
    {
        IsNewForm = true;
    }
    else
    {
        pcForm = static_cast<CForm*>(pcMdiSubWindow->widget());

        if(pcForm->IsLoadFile())                //防止当前的窗口数据被覆盖
            IsNewForm = true;
        else
            IsNewForm = false;
    }

    if(IsNewForm)
    {
        pcForm = new CForm(this);
        ui->mdiArea->addSubWindow(pcForm);
    }
    pcForm->LoadFileToText(strCurFilePath);
    pcForm->show();

    ui->actCopy->setEnabled(true);
    ui->actPaste->setEnabled(true);
    ui->actCut->setEnabled(true);
    ui->actFont->setEnabled(true);
}
