/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.23
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.10.23
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QFileDialog>
#include <QMessageBox>
#include <QSqlError>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogdata.h"

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

    m_pcSqlQueryModel = new QSqlQueryModel(this);
    m_pcItemSelectionModel = new QItemSelectionModel(m_pcSqlQueryModel);

    m_pcSqlQueryModel->setQuery("SELECT empNo, Name, Gender, Height, Birthday, Mobile, Province, City, Department, "
                                " Education, Salary, Photo FROM employee ORDER BY empNo", m_cSqlDatabase);
    if(m_pcSqlQueryModel->lastError().isValid())
    {
        QMessageBox::warning(this, tr("警告"), tr("数据库查询失败: ") + m_pcSqlQueryModel->lastError().text());
        return;
    }

    ui->tableView->setModel(m_pcSqlQueryModel);
    ui->tableView->setSelectionModel(m_pcItemSelectionModel);

    //启用其它按钮
    ui->actOpenDB->setEnabled(false);
    ui->actRecInsert->setEnabled(true);
    ui->actRecEdit->setEnabled(true);
    ui->actRecDelete->setEnabled(true);
    ui->actScan->setEnabled(true);
}

void MainWindow::on_actRecInsert_triggered()
{
    QSqlRecord cSqlRecord = m_pcSqlQueryModel->record();
    cSqlRecord.setValue("empNo", 4000 + m_pcSqlQueryModel->rowCount());

    QSqlQuery cSqlQuery;
    CDialogData cDialogData(cSqlRecord, CDialogData::SQLRECORD_FLAG::INSERT);

    if(cDialogData.exec() != QDialog::Accepted)
        return;

    cSqlRecord = cDialogData.GetCurSqlRecord();

    cSqlQuery.prepare("INSERT INTO employee (EmpNo,Name,Gender,Height,Birthday,Mobile,Province,"
                  " City,Department,Education,Salary,Memo,Photo) "
                  " VALUES(:EmpNo,:Name, :Gender,:Height,:Birthday,:Mobile,:Province,"
                  " :City,:Department,:Education,:Salary,:Memo,:Photo)");

    cSqlQuery.bindValue(":EmpNo",cSqlRecord.value("EmpNo"));
    cSqlQuery.bindValue(":Name",cSqlRecord.value("Name"));
    cSqlQuery.bindValue(":Gender",cSqlRecord.value("Gender"));
    cSqlQuery.bindValue(":Height",cSqlRecord.value("Height"));
    cSqlQuery.bindValue(":Birthday",cSqlRecord.value("Birthday"));
    cSqlQuery.bindValue(":Mobile",cSqlRecord.value("Mobile"));

    cSqlQuery.bindValue(":Province",cSqlRecord.value("Province"));
    cSqlQuery.bindValue(":City",cSqlRecord.value("City"));
    cSqlQuery.bindValue(":Department",cSqlRecord.value("Department"));
    cSqlQuery.bindValue(":Education",cSqlRecord.value("Education"));

    cSqlQuery.bindValue(":Salary",cSqlRecord.value("Salary"));
    cSqlQuery.bindValue(":Memo",cSqlRecord.value("Memo"));
    cSqlQuery.bindValue(":Photo",cSqlRecord.value("Photo"));

    if (!cSqlQuery.exec())
        QMessageBox::critical(this, "错误", "插入记录错误\n" + cSqlQuery.lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
    else                                                                    //插入，删除记录后需要重新设置SQL语句查询
    {
        // QString sqlStr = m_pcSqlQueryModel->query().executedQuery();        //执行过的SELECT语句
        // m_pcSqlQueryModel->setQuery(sqlStr);                                //重新查询数据

        //再次加载数据库数据
        m_pcSqlQueryModel->setQuery("SELECT empNo, Name, Gender, Height, Birthday, Mobile, Province, City, Department, "
                                    " Education, Salary, Photo FROM employee ORDER BY empNo", m_cSqlDatabase);
    }

}

void MainWindow::on_actRecEdit_triggered()
{
    QSqlRecord cSqlRecord = m_pcSqlQueryModel->record(m_pcItemSelectionModel->currentIndex().row());
    QSqlQuery cSqlQuery;
    CDialogData cDialogData(cSqlRecord, CDialogData::SQLRECORD_FLAG::EDIT);
    qint32 nEmpNo = cSqlRecord.value("empNo").toInt();

    if(cDialogData.exec() != QDialog::Accepted)
        return;

    cSqlRecord = cDialogData.GetCurSqlRecord();

    cSqlQuery.prepare("update employee set Name=:Name, Gender=:Gender,Height=:Height,"
                  " Birthday=:Birthday, Mobile=:Mobile, Province=:Province,"
                  " City=:City, Department=:Department, Education=:Education,"
                  " Salary=:Salary, Memo=:Memo, Photo=:Photo "
                  " where EmpNo = :ID");

    cSqlQuery.bindValue(":Name",cSqlRecord.value("Name"));
    cSqlQuery.bindValue(":Gender",cSqlRecord.value("Gender"));
    cSqlQuery.bindValue(":Height",cSqlRecord.value("Height"));
    cSqlQuery.bindValue(":Birthday",cSqlRecord.value("Birthday"));
    cSqlQuery.bindValue(":Mobile",cSqlRecord.value("Mobile"));

    cSqlQuery.bindValue(":Province",cSqlRecord.value("Province"));
    cSqlQuery.bindValue(":City",cSqlRecord.value("City"));
    cSqlQuery.bindValue(":Department",cSqlRecord.value("Department"));
    cSqlQuery.bindValue(":Education",cSqlRecord.value("Education"));

    cSqlQuery.bindValue(":Salary",cSqlRecord.value("Salary"));
    cSqlQuery.bindValue(":Memo",cSqlRecord.value("Memo"));
    cSqlQuery.bindValue(":Photo",cSqlRecord.value("Photo"));

    cSqlQuery.bindValue(":ID", nEmpNo);

    if (!cSqlQuery.exec())
        QMessageBox::critical(this, "错误", "记录更新错误\n" + cSqlQuery.lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
    else
        m_pcSqlQueryModel->setQuery("SELECT empNo, Name, Gender, Height, Birthday, Mobile, Province, City, Department, "
                                    " Education, Salary, Photo FROM employee ORDER BY empNo", m_cSqlDatabase); //数据模型重新查询数据，更新tableView显示
}


void MainWindow::on_actScan_triggered()
{
    QSqlRecord cSqlRecord;
    QSqlQuery cSqlQuery;

    cSqlQuery.prepare("UPDATE employee SET Salary=:Salary WHERE EmpNo = :ID");

    for (int i = 0; i < m_pcSqlQueryModel->rowCount(); ++i) {
        cSqlRecord = m_pcSqlQueryModel->record(i);

        cSqlQuery.bindValue(":Salary", cSqlRecord.value("Salary").toInt() + 1000);
        cSqlQuery.bindValue(":ID", cSqlRecord.value("empNo").toInt());

        if(!cSqlQuery.exec())
            QMessageBox::critical(this, "错误", "涨薪错误\n" + cSqlQuery.lastError().text(),
                                  QMessageBox::Ok,QMessageBox::NoButton);
        else
            m_pcSqlQueryModel->setQuery("SELECT empNo, Name, Gender, Height, Birthday, Mobile, Province, City, Department, "
                                        " Education, Salary, Photo FROM employee ORDER BY empNo", m_cSqlDatabase); //数据模型重新查询数据，更新tableView显示

    }
}


void MainWindow::on_actRecDelete_triggered()
{
    QSqlRecord cSqlRecord = m_pcSqlQueryModel->record(m_pcItemSelectionModel->currentIndex().row());
    QSqlQuery cSqlQuery;

    cSqlQuery.prepare("delete from employee where EmpNo = :ID");
    cSqlQuery.bindValue(":ID", cSqlRecord.value("empNo").toInt());

    if(!cSqlQuery.exec())
        QMessageBox::critical(this, "错误", "涨薪错误\n" + cSqlQuery.lastError().text(),
                              QMessageBox::Ok,QMessageBox::NoButton);
    else
        m_pcSqlQueryModel->setQuery("SELECT empNo, Name, Gender, Height, Birthday, Mobile, Province, City, Department, "
                                    " Education, Salary, Photo FROM employee ORDER BY empNo", m_cSqlDatabase); //数据模型重新查询数据，更新tableView显示

}

