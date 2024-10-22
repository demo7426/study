/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.22
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.10.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>

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

void MainWindow::InitUi(void) noexcept
{
    this->setCentralWidget(ui->splitter);
}

void MainWindow::InitSignalSlots(void) noexcept
{
    connect(ui->actOpenDB, &QAction::triggered, this, &MainWindow::OpenSQLiteFile);

    if(m_pcItemSelectionModel)
        connect(m_pcItemSelectionModel, &QItemSelectionModel::currentChanged, this, &MainWindow::On_CurrentRowChanged);
}

void MainWindow::OpenSQLiteFile(void) noexcept
{
    QString strFilePath = QFileDialog::getOpenFileName(this, tr("选择单个数据库文件"), QApplication::applicationFilePath(), tr("数据库文件(*db *db3)"));
    if(strFilePath.isEmpty())
        return;

    m_cSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    m_cSqlDatabase.setDatabaseName(strFilePath);
    if(!m_cSqlDatabase.open())
    {
        QMessageBox::warning(this, tr("警告"), tr("数据库打开失败"));
        return;
    }

    m_pcSqlQueryModel = new QSqlQueryModel(this);
    m_pcItemSelectionModel = new QItemSelectionModel(m_pcSqlQueryModel);
    m_pcDataWidgetMapper = new QDataWidgetMapper(this);

    m_pcSqlQueryModel->setQuery("SELECT empNo, Name, Gender, Height, Birthday, Mobile, Province, City, Department, "
                                " Education, Salary FROM employee ORDER BY empNo", m_cSqlDatabase);
    if(m_pcSqlQueryModel->lastError().isValid())
    {
        QMessageBox::warning(this, tr("警告"), tr("数据库查询失败: ") + m_pcSqlQueryModel->lastError().text());
        return;
    }

    m_pcSqlQueryModel->setHeaderData(m_pcSqlQueryModel->record().indexOf("empNo"), Qt::Horizontal, tr("工号"));
    m_pcSqlQueryModel->setHeaderData(m_pcSqlQueryModel->record().indexOf("Name"), Qt::Horizontal, tr("名称"));

    ui->tableView->setModel(m_pcSqlQueryModel);
    ui->tableView->setSelectionModel(m_pcItemSelectionModel);

    m_pcDataWidgetMapper->setModel(m_pcSqlQueryModel);
    m_pcDataWidgetMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    m_pcDataWidgetMapper->addMapping(ui->dbSpinEmpNo, m_pcSqlQueryModel->record().indexOf("empNo"));
    m_pcDataWidgetMapper->addMapping(ui->dbEditName, m_pcSqlQueryModel->record().indexOf("Name"));
    m_pcDataWidgetMapper->addMapping(ui->dbComboSex, m_pcSqlQueryModel->record().indexOf("Gender"));
    m_pcDataWidgetMapper->addMapping(ui->dbSpinHeight, m_pcSqlQueryModel->record().indexOf("Height"));
    m_pcDataWidgetMapper->addMapping(ui->dbEditBirth, m_pcSqlQueryModel->record().indexOf("Birthday"));
    m_pcDataWidgetMapper->addMapping(ui->dbEditMobile, m_pcSqlQueryModel->record().indexOf("Mobile"));
    m_pcDataWidgetMapper->addMapping(ui->dbComboProvince, m_pcSqlQueryModel->record().indexOf("Province"));
    m_pcDataWidgetMapper->addMapping(ui->dbEditCity, m_pcSqlQueryModel->record().indexOf("City"));
    m_pcDataWidgetMapper->addMapping(ui->dbEditCity, m_pcSqlQueryModel->record().indexOf("Department"));
    m_pcDataWidgetMapper->addMapping(ui->dbComboEdu, m_pcSqlQueryModel->record().indexOf("Education"));
    m_pcDataWidgetMapper->addMapping(ui->dbSpinSalary, m_pcSqlQueryModel->record().indexOf("Salary"));

    ui->actOpenDB->setEnabled(false);

    InitSignalSlots();
}

void MainWindow::On_CurrentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    m_pcDataWidgetMapper->setCurrentModelIndex(current);

    qint32 nEmpNo = m_pcSqlQueryModel->record(current.row()).value("empNo").toInt();
    QSqlQuery cSqlQuery;
    QVariant var;

    cSqlQuery.prepare("select empNo, Photo from employee where EmpNo = :ID");
    cSqlQuery.bindValue(":ID", nEmpNo);
    cSqlQuery.exec();
    cSqlQuery.first();                  //回到第一条record

    var = cSqlQuery.value("Photo");
    if(var.isNull())
        ui->dbLabPhoto->clear();
    else
    {
        QPixmap cPixmap;
        cPixmap.loadFromData(var.toByteArray());
        ui->dbLabPhoto->setPixmap(cPixmap.scaledToWidth(ui->dbLabPhoto->width()));
    }

    bool bCurFist = (current.row() == 0);
    bool bCurLast = (current.row() == m_pcSqlQueryModel->rowCount() - 1);

    ui->actRecFirst->setEnabled(!bCurFist);
    ui->actRecPrevious->setEnabled(!bCurFist);
    ui->actRecNext->setEnabled(!bCurLast);
    ui->actRecLast->setEnabled(!bCurLast);
}

void MainWindow::RefreshItemSelectionModel()
{
    int nCurRowNo = m_pcDataWidgetMapper->currentIndex();
    QModelIndex cModelIndex = m_pcSqlQueryModel->index(nCurRowNo, 0);

    m_pcItemSelectionModel->clearSelection();
    m_pcItemSelectionModel->setCurrentIndex(cModelIndex, QItemSelectionModel::SelectionFlag::Select);
}

void MainWindow::on_actRecFirst_triggered()
{
    m_pcDataWidgetMapper->toFirst();
    RefreshItemSelectionModel();
}


void MainWindow::on_actRecPrevious_triggered()
{
    m_pcDataWidgetMapper->toPrevious();
    RefreshItemSelectionModel();
}


void MainWindow::on_actRecNext_triggered()
{
    m_pcDataWidgetMapper->toNext();
    RefreshItemSelectionModel();
}


void MainWindow::on_actRecLast_triggered()
{
    m_pcDataWidgetMapper->toLast();
    RefreshItemSelectionModel();
}

