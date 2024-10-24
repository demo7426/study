/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.24
描  述:	实现关系型数据库的使用
备  注:
修改记录:

  1.  日期: 2024.10.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QFileDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRelationalDelegate>

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
    this->setCentralWidget(ui->tableView);
}

void MainWindow::InitSignalSlots(void) noexcept
{
    connect(ui->actOpenDB, &QAction::triggered, this, &MainWindow::OpenSQLiteFile);

    if(m_pcItemSelectionModel)
    {
        connect(m_pcItemSelectionModel, &QItemSelectionModel::currentChanged, this, &MainWindow::On_CurrentChanged);
    }
}

void MainWindow::OpenSQLiteFile(void)
{
    QString strFilePath = QFileDialog::getOpenFileName(this, tr("打开单个文件"), QApplication::applicationFilePath(), tr("数据库文件(*.db *db3)"));

    if(strFilePath.isEmpty())
        return;

    m_cSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    m_cSqlDatabase.setDatabaseName(strFilePath);
    if(!m_cSqlDatabase.open())
    {
        QMessageBox::critical(this, tr("错误窗口"), tr("打开数据库文件错误"));
        return;
    }

    m_pcSqlRelationalTableModel = new QSqlRelationalTableModel(this);
    m_pcItemSelectionModel = new QItemSelectionModel(m_pcSqlRelationalTableModel);

    m_pcSqlRelationalTableModel->setTable("studInfo");                                  //需要放在setRelation函数前面调用

    m_pcSqlRelationalTableModel->setRelation(m_pcSqlRelationalTableModel->fieldIndex("departID"),
                                             QSqlRelation("departments", "departID", "department"));
    m_pcSqlRelationalTableModel->setRelation(m_pcSqlRelationalTableModel->fieldIndex("majorID"),
                                             QSqlRelation("majors", "majorID", "major"));

    m_pcSqlRelationalTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_pcSqlRelationalTableModel->setSort(m_pcSqlRelationalTableModel->fieldIndex("studID"), Qt::AscendingOrder);
    m_pcSqlRelationalTableModel->setHeaderData(m_pcSqlRelationalTableModel->fieldIndex("studID"), Qt::Horizontal, "学生ID");
    m_pcSqlRelationalTableModel->setHeaderData(m_pcSqlRelationalTableModel->fieldIndex("name"), Qt::Horizontal, "名称");
    m_pcSqlRelationalTableModel->setHeaderData(m_pcSqlRelationalTableModel->fieldIndex("gender"), Qt::Horizontal, "性别");
    m_pcSqlRelationalTableModel->setHeaderData(m_pcSqlRelationalTableModel->fieldIndex("departID"), Qt::Horizontal, "学院");
    m_pcSqlRelationalTableModel->setHeaderData(m_pcSqlRelationalTableModel->fieldIndex("majorID"), Qt::Horizontal, "专业");
    m_pcSqlRelationalTableModel->select();

    ui->tableView->setModel(m_pcSqlRelationalTableModel);
    ui->tableView->setSelectionModel(m_pcItemSelectionModel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(this));

    //启用其它按钮
    ui->actOpenDB->setEnabled(false);

    InitSignalSlots();
}

void MainWindow::On_CurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);


    ui->actRecInsert->setEnabled(true);
    ui->actRecAppend->setEnabled(true);
    ui->actRecDelete->setEnabled(true);
    ui->actFields->setEnabled(true);
}

void MainWindow::on_actFields_triggered()
{
    QSqlRecord cSqlRecord = m_pcSqlRelationalTableModel->record();
    QString strMsg = QString();

    for (int i = 0; i < cSqlRecord.count(); ++i) {
        strMsg += (cSqlRecord.fieldName(i) + '\n');
    }
    QMessageBox::information(this, tr("字段列表"), strMsg);
}

void MainWindow::InsertDataToSqlTableModel(quint32 _RowNo)
{
    m_pcSqlRelationalTableModel->insertRow(_RowNo, QModelIndex());                            //类似于widget,插入新的一行之后，对应位置的数据自动生成

    m_pcSqlRelationalTableModel->setData(m_pcSqlRelationalTableModel->index(_RowNo, 0), 4000 + _RowNo);
}

void MainWindow::on_actRecAppend_triggered()
{
    InsertDataToSqlTableModel(m_pcSqlRelationalTableModel->rowCount());

    ui->actSubmit->setEnabled(true);
    ui->actRevert->setEnabled(true);
}

void MainWindow::on_actRecInsert_triggered()
{
    InsertDataToSqlTableModel(m_pcItemSelectionModel->currentIndex().row());

    ui->actSubmit->setEnabled(true);
    ui->actRevert->setEnabled(true);
}

void MainWindow::on_actRecDelete_triggered()
{
    m_pcSqlRelationalTableModel->removeRow(m_pcItemSelectionModel->currentIndex().row());

    ui->actSubmit->setEnabled(true);
    ui->actRevert->setEnabled(true);
}


void MainWindow::on_actSubmit_triggered()
{
    m_pcSqlRelationalTableModel->submitAll();
    m_pcSqlRelationalTableModel->select();

    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
}


void MainWindow::on_actRevert_triggered()
{
    m_pcSqlRelationalTableModel->revertAll();
    m_pcSqlRelationalTableModel->select();

    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
}

