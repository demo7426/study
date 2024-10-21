/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.19
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.10.19
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>

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

}

void MainWindow::InitSignalSlots(void) noexcept
{
    connect(ui->actOpenDB, &QAction::triggered, this, &MainWindow::OpenSQLiteFile);

    if(m_pcItemSelectionModel)
    {
        connect(m_pcItemSelectionModel, &QItemSelectionModel::currentRowChanged, this, &MainWindow::On_CurrentRowChanged);
        connect(m_pcItemSelectionModel, &QItemSelectionModel::currentChanged, this, &MainWindow::On_CurrentChanged);
    }
}

void MainWindow::OpenSQLiteFile(void) noexcept
{
    QString strFilePath = QFileDialog::getOpenFileName(this, tr("选择单个SQLite文件"), QApplication::applicationDirPath(), tr("数据库文件(*.db *.db3)"));

    if(strFilePath.isEmpty())
        return;

    //加载数据库文件

    m_cSqlDb = QSqlDatabase::addDatabase("QSQLITE");            //添加数据库驱动
    m_cSqlDb.setDatabaseName(strFilePath);                      //设置数据库名称
    if(!m_cSqlDb.open())
    {
        QMessageBox::warning(this, tr("错误"), tr("打开数据库错误"));
        return;
    }

    m_pcSqlTableModel = new QSqlTableModel(this, m_cSqlDb);
    m_pcItemSelectionModel = new QItemSelectionModel(m_pcSqlTableModel);

    m_pcSqlTableModel->setTable("employee");
    m_pcSqlTableModel->setSort(m_pcSqlTableModel->fieldIndex("EmpNo"), Qt::AscendingOrder);
    m_pcSqlTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if(!m_pcSqlTableModel->select())
    {
        QMessageBox::critical(this, tr("错误"), tr("打开数据表错误, 错误信息:") + m_pcSqlTableModel->lastError().text());
        return;
    }

    m_pcSqlTableModel->setHeaderData(m_pcSqlTableModel->fieldIndex("EmpNo"), Qt::Horizontal, tr("工号"));

    ui->tableView->setModel(m_pcSqlTableModel);
    ui->tableView->setSelectionModel(m_pcItemSelectionModel);

    //隐藏显示表格信息
    ui->tableView->setColumnHidden(m_pcSqlTableModel->fieldIndex("Memo"), true);
    ui->tableView->setColumnHidden(m_pcSqlTableModel->fieldIndex("Photo"), true);

    //数据库数据映射
    m_pcDataWidgetMapper = new QDataWidgetMapper();
    m_pcDataWidgetMapper->setModel(m_pcSqlTableModel);
    m_pcDataWidgetMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    m_pcDataWidgetMapper->addMapping(ui->dbSpinEmpNo, m_pcSqlTableModel->fieldIndex("EmpNo"));
    m_pcDataWidgetMapper->addMapping(ui->dbEditName, m_pcSqlTableModel->fieldIndex("Name"));
    m_pcDataWidgetMapper->addMapping(ui->dbComboSex, m_pcSqlTableModel->fieldIndex("Gender"));
    m_pcDataWidgetMapper->addMapping(ui->dbSpinHeight, m_pcSqlTableModel->fieldIndex("Height"));
    m_pcDataWidgetMapper->addMapping(ui->dbEditBirth, m_pcSqlTableModel->fieldIndex("Birthday"));
    m_pcDataWidgetMapper->addMapping(ui->dbEditMobile, m_pcSqlTableModel->fieldIndex("Mobile"));
    m_pcDataWidgetMapper->addMapping(ui->dbComboProvince, m_pcSqlTableModel->fieldIndex("Province"));
    m_pcDataWidgetMapper->addMapping(ui->dbEditCity, m_pcSqlTableModel->fieldIndex("City"));
    m_pcDataWidgetMapper->addMapping(ui->dbEditCity, m_pcSqlTableModel->fieldIndex("Department"));
    m_pcDataWidgetMapper->addMapping(ui->dbComboEdu, m_pcSqlTableModel->fieldIndex("Education"));
    m_pcDataWidgetMapper->addMapping(ui->dbSpinSalary, m_pcSqlTableModel->fieldIndex("Salary"));

    //切换按钮显示效果
    ui->actOpenDB->setEnabled(false);
    ui->groupBoxSort->setEnabled(true);
    ui->groupBoxFilter->setEnabled(true);


    QSqlRecord cSqlRecord = m_pcSqlTableModel->record();                            //获取所有表中记录信息
    for (int i = 0; i < cSqlRecord.count(); ++i)
        ui->comboFields->addItem(cSqlRecord.fieldName(i));

    //设置view委托
    m_pcItemDelegate_Sex.setItems({ "男", "女" }, false);
    m_pcItemDelegate_Department.setItems({ "销售部", "行政部", "技术部", "生产部" }, false);
    ui->tableView->setItemDelegateForColumn(m_pcSqlTableModel->fieldIndex("Gender"), &m_pcItemDelegate_Sex);
    ui->tableView->setItemDelegateForColumn(m_pcSqlTableModel->fieldIndex("Department"), &m_pcItemDelegate_Department);

    InitSignalSlots();
}

void MainWindow::InsertDataToSqlTableModel(quint32 _RowNo)
{
    m_pcSqlTableModel->insertRow(_RowNo, QModelIndex());                            //类似于widget,插入新的一行之后，对应位置的数据自动生成

    m_pcSqlTableModel->setData(m_pcSqlTableModel->index(_RowNo, 0), 2000 + _RowNo);
    m_pcSqlTableModel->setData(m_pcSqlTableModel->index(_RowNo, 1), QString::asprintf("新增:%u", _RowNo));
    m_pcSqlTableModel->setData(m_pcSqlTableModel->index(_RowNo, 2), "男");
}

void MainWindow::On_CurrentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)

    m_pcDataWidgetMapper->setCurrentIndex(current.row());

    QSqlRecord cSqlRecord = m_pcSqlTableModel->record(current.row());               //获取对应行中表中记录信息
    if(cSqlRecord.isNull("Photo"))
        ui->dbLabPhoto->clear();
    else
    {
        QByteArray cByteArray = cSqlRecord.value("Photo").toByteArray();
        QPixmap cPixMap;
        cPixMap.loadFromData(cByteArray);
        ui->dbLabPhoto->setPixmap(cPixMap.scaledToWidth(ui->dbLabPhoto->width()));
    }
}

void MainWindow::On_CurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(current)
    Q_UNUSED(previous)

    ui->actRecAppend->setEnabled(true);
    ui->actRecInsert->setEnabled(true);
    ui->actRecDelete->setEnabled(true);
    ui->actPhoto->setEnabled(true);
    ui->actPhotoClear->setEnabled(true);
    ui->actScan->setEnabled(true);
}

void MainWindow::on_actRecAppend_triggered()
{
    InsertDataToSqlTableModel(m_pcSqlTableModel->rowCount());
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
    m_pcSqlTableModel->removeRow(m_pcItemSelectionModel->currentIndex().row());
    ui->actSubmit->setEnabled(true);
    ui->actRevert->setEnabled(true);
}


void MainWindow::on_actSubmit_triggered()
{
    if(!m_pcSqlTableModel->submitAll())
        QMessageBox::warning(this, tr("警告窗口"), tr("保存失败") + m_pcSqlTableModel->lastError().text());

    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
}

void MainWindow::on_actRevert_triggered()
{
    m_pcSqlTableModel->revertAll();
    ui->actRevert->setEnabled(false);
}

void MainWindow::on_actPhoto_triggered()
{
    qint32 nCurRowNo = m_pcItemSelectionModel->currentIndex().row();
    QSqlRecord cSqlRecord = m_pcSqlTableModel->record(nCurRowNo);
    QByteArray cByteArray;

    QString strFilePath = QFileDialog::getOpenFileName(this, tr("选择单个文件"), QDir::currentPath(), tr("图片文件(*.png *.jpg)"));

    if(strFilePath.isEmpty())
        return;

    QFile cFile(strFilePath);
    if(!cFile.open(QIODeviceBase::ReadOnly))
        return;

    cByteArray = cFile.readAll();
    cFile.close();

    cSqlRecord.setValue("Photo", cByteArray);
    m_pcSqlTableModel->setRecord(nCurRowNo, cSqlRecord);

    QPixmap cPixmap;
    cPixmap.loadFromData(cByteArray);
    ui->dbLabPhoto->setPixmap(cPixmap.scaledToWidth(ui->dbLabPhoto->width()));

    ui->actSubmit->setEnabled(true);
    ui->actRevert->setEnabled(true);
}

void MainWindow::on_actPhotoClear_triggered()
{
    qint32 nCurRowNo = m_pcItemSelectionModel->currentIndex().row();
    QSqlRecord cSqlRecord = m_pcSqlTableModel->record(nCurRowNo);

    cSqlRecord.setNull("Photo");
    m_pcSqlTableModel->setRecord(nCurRowNo, cSqlRecord);

    ui->dbLabPhoto->clear();

    ui->actSubmit->setEnabled(true);
    ui->actRevert->setEnabled(true);
}

void MainWindow::on_actScan_triggered()
{
    QSqlRecord cSqlRecord;
    for (int i = 0; i < m_pcSqlTableModel->rowCount(); ++i)
    {
        cSqlRecord = m_pcSqlTableModel->record(i);
        cSqlRecord.setValue("Salary", cSqlRecord.value("Salary").toFloat() * 1.1);
        m_pcSqlTableModel->setRecord(i, cSqlRecord);
    }

    ui->actSubmit->setEnabled(true);
    ui->actRevert->setEnabled(true);
}

void MainWindow::on_radioBtnAscend_clicked()
{
    m_pcSqlTableModel->setSort(m_pcSqlTableModel->fieldIndex(ui->comboFields->currentText()), Qt::SortOrder::AscendingOrder);
    m_pcSqlTableModel->select();
}

void MainWindow::on_radioBtnDescend_clicked()
{
    m_pcSqlTableModel->setSort(m_pcSqlTableModel->fieldIndex(ui->comboFields->currentText()), Qt::SortOrder::DescendingOrder);
    m_pcSqlTableModel->select();
}

void MainWindow::on_radioBtnMan_clicked()
{
    m_pcSqlTableModel->setFilter("Gender='男'");
}

void MainWindow::on_radioBtnWoman_clicked()
{
    m_pcSqlTableModel->setFilter("Gender='女'");
}

void MainWindow::on_radioBtnBoth_clicked()
{
    m_pcSqlTableModel->setFilter("");
}

void MainWindow::on_comboFields_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(ui->radioBtnAscend->isChecked())
        on_radioBtnAscend_clicked();
    else
        on_radioBtnDescend_clicked();
}

