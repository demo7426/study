/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.27
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.27
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QFileDialog>
#include <QFile>
#include <QDataStream>
#include <QTextStream>

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
    this->setCentralWidget(ui->tabWidget);

    m_pcStandardItemModel = new QStandardItemModel(this);
    m_pcItemSelectionModel = new QItemSelectionModel(m_pcStandardItemModel, this);

    ui->tableView->setModel(m_pcStandardItemModel);
    ui->tableView->setSelectionModel(m_pcItemSelectionModel);

    ui->tableView->setAlternatingRowColors(true);

    this->SetTabelViewRowAndColumn(m_pcStandardItemModel, m_unRowCount, m_unColumnCount);
}

void MainWindow::InitSignalSlots(void) noexcept
{
    connect(ui->actTabReset, &QAction::triggered, this, [this](){
        this->SetTabelViewRowAndColumn(m_pcStandardItemModel, m_unRowCount, m_unColumnCount);
    });

    connect(ui->actOpen, &QAction::triggered, this, &MainWindow::LoadStmFileToQStandardItemModel);
    connect(ui->actSave, &QAction::triggered, this, &MainWindow::SaveQStandardItemModelDataToStmFile);

    connect(ui->actOpenBin, &QAction::triggered, this, &MainWindow::LoadDatFileToQStandardItemModel);
    connect(ui->actSaveBin, &QAction::triggered, this, &MainWindow::SaveQStandardItemModelDataToDatFile);
}

void MainWindow::SetTabelViewRowAndColumn(QStandardItemModel *_pStandardItemModel, quint32 _RowCount, quint32 _ColumnCount)
{
    if(_pStandardItemModel == nullptr || _RowCount == 0 || _ColumnCount ==0)
    {
        qDebug() << tr("输入参数错误");
        return;
    }

    QStandardItem *pcStandardItem = nullptr;
    QModelIndex cModelIndex;

    //移除现有的表格
    for (qint32 i = 0; i < _pStandardItemModel->rowCount(); ++i)
    {
        for (qint32 j = 0; j < _pStandardItemModel->columnCount(); ++j)
        {
            //先取QModelIndex再转换为QStandardItem，保证数据有效;
            //直接使用item()，如果没有设置过数据，返回为nullptr;
            cModelIndex = _pStandardItemModel->index(i, j);
            pcStandardItem = _pStandardItemModel->itemFromIndex(cModelIndex);

            delete pcStandardItem;
        }
        _pStandardItemModel->removeRow(i);
    }

    //新增表格
    _pStandardItemModel->setRowCount(_RowCount);
    _pStandardItemModel->setColumnCount(_ColumnCount);

    for (quint32 i = 0; i < _RowCount; ++i)
    {
        for (quint32 j = 0; j < _ColumnCount; ++j)
        {
            pcStandardItem = new QStandardItem();
            _pStandardItemModel->setItem(i, j, pcStandardItem);
        }
    }
}

void MainWindow::LoadStmFileToQStandardItemModel()
{
    QFile cFile;
    QDataStream cDataStream;
    QString strCurFilePath = QString();
    QString strFilter = tr("(stm文件(*.stm))");

    qint16 sRowCount = 0;                       //行数
    qint16 sColumnCount = 0;                    //列数
    qint16 sMeasuringDepth = 0;                 //测深
    qreal dbVerticalDepth = 0;                  //垂深
    qreal dbOrientation = 0;                    //方位
    qreal dbDisplacement = 0;                   //位移
    QString strQuality;                         //固井质量
    bool bIsSampled = false;                    //采样

    QModelIndex cModelIndex;

    strCurFilePath = QFileDialog::getOpenFileName(this, tr("选择单个文件"), QCoreApplication::applicationFilePath(), strFilter);
    if(strCurFilePath.isEmpty())
        return;

    cFile.setFileName(strCurFilePath);
    if(!cFile.open(QIODeviceBase::ReadOnly))
        return;

    cDataStream.setDevice(&cFile);
    cDataStream.setVersion(QDataStream::Qt_5_9);

    cDataStream >> sRowCount;
    cDataStream >> sColumnCount;

    SetTabelViewRowAndColumn(m_pcStandardItemModel, sRowCount, sColumnCount);

    for (int i = 0; i < sColumnCount; ++i)
    {
        QString strHeaderData;
        cDataStream >> strHeaderData;
        m_pcStandardItemModel->setHeaderData(i, Qt::Orientation::Horizontal, strHeaderData, Qt::DisplayRole);
    }

    for (int i = 0; i < sRowCount; ++i)
    {
        qint32 nColumnIndex = 0;
        cDataStream >> sMeasuringDepth;
        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        m_pcStandardItemModel->setData(cModelIndex, sMeasuringDepth, Qt::DisplayRole);

        cDataStream >> dbVerticalDepth;
        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        m_pcStandardItemModel->setData(cModelIndex, dbVerticalDepth, Qt::DisplayRole);

        cDataStream >> dbOrientation;
        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        m_pcStandardItemModel->setData(cModelIndex, dbOrientation, Qt::DisplayRole);

        cDataStream >> dbDisplacement;
        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        m_pcStandardItemModel->setData(cModelIndex, dbDisplacement, Qt::DisplayRole);

        cDataStream >> strQuality;
        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        m_pcStandardItemModel->setData(cModelIndex, strQuality, Qt::DisplayRole);

        cDataStream >> bIsSampled;
        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        m_pcStandardItemModel->itemFromIndex(cModelIndex)->setCheckable(true);
        if(bIsSampled)
        {
            m_pcStandardItemModel->itemFromIndex(cModelIndex)->setCheckState(Qt::Checked);
            m_pcStandardItemModel->setData(cModelIndex, "strQuality", Qt::DisplayRole);
        }
        else
        {
            m_pcStandardItemModel->itemFromIndex(cModelIndex)->setCheckState(Qt::Unchecked);
            m_pcStandardItemModel->setData(cModelIndex, "unstrQuality", Qt::DisplayRole);
        }
    }

    cFile.close();

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::SaveQStandardItemModelDataToStmFile()
{
    QFile cFile;
    QDataStream cDataStream;
    QString strCurFilePath = QString();
    QString strFilter = tr("(stm文件(*.stm))");

    qint16 sRowCount = 0;                       //行数
    qint16 sColumnCount = 0;                    //列数
    qint16 sMeasuringDepth = 0;                 //测深
    qreal dbVerticalDepth = 0;                  //垂深
    qreal dbOrientation = 0;                    //方位
    qreal dbDisplacement = 0;                   //位移
    QString strQuality;                         //固井质量
    bool bIsSampled = false;                    //采样

    QModelIndex cModelIndex;

    strCurFilePath = QFileDialog::getSaveFileName(this, tr("保存文件"), QCoreApplication::applicationFilePath(), strFilter);
    if(strCurFilePath.isEmpty())
        return;

    cFile.setFileName(strCurFilePath);
    if(!cFile.open(QIODeviceBase::WriteOnly))
        return;

    cDataStream.setDevice(&cFile);
    cDataStream.setVersion(QDataStream::Qt_5_9);

    sRowCount = m_pcStandardItemModel->rowCount();
    sColumnCount = m_pcStandardItemModel->columnCount();

    cDataStream << sRowCount;
    cDataStream << sColumnCount;

    for (int i = 0; i < sColumnCount; ++i)
    {
        QString strHeaderData;
        strHeaderData = m_pcStandardItemModel->headerData(i, Qt::Orientation::Horizontal, Qt::DisplayRole).toString();
        cDataStream << strHeaderData;
    }

    for (int i = 0; i < sRowCount; ++i)
    {
        qint32 nColumnIndex = 0;

        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        sMeasuringDepth = m_pcStandardItemModel->data(cModelIndex, Qt::DisplayRole).toInt();
        cDataStream << sMeasuringDepth;

        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        dbVerticalDepth = m_pcStandardItemModel->data(cModelIndex, Qt::DisplayRole).toReal();
        cDataStream << dbVerticalDepth;

        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        dbOrientation = m_pcStandardItemModel->data(cModelIndex, Qt::DisplayRole).toReal();
        cDataStream << dbOrientation;

        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        dbDisplacement = m_pcStandardItemModel->data(cModelIndex, Qt::DisplayRole).toReal();
        cDataStream << dbDisplacement;

        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        strQuality = m_pcStandardItemModel->data(cModelIndex, Qt::DisplayRole).toString();
        cDataStream << strQuality;

        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        bIsSampled = m_pcStandardItemModel->itemFromIndex(cModelIndex)->checkState();
        cDataStream << bIsSampled;
    }

    cFile.close();
}

void MainWindow::LoadDatFileToQStandardItemModel()
{
    QFile cFile;
    QDataStream cDataStream;
    QString strCurFilePath = QString();
    QString strFilter = tr("(dat文件(*.dat))");

    qint16 sRowCount = 0;                       //行数
    qint16 sColumnCount = 0;                    //列数
    qint16 sMeasuringDepth = 0;                 //测深
    qreal dbVerticalDepth = 0;                  //垂深
    qreal dbOrientation = 0;                    //方位
    qreal dbDisplacement = 0;                   //位移
    QString strQuality;                         //固井质量
    bool bIsSampled = false;                    //采样

    QModelIndex cModelIndex;

    char* pchStartAddr = nullptr;               //起始地址
    uint unLen = 0;

    strCurFilePath = QFileDialog::getOpenFileName(this, tr("选择单个文件"), QCoreApplication::applicationFilePath(), strFilter);
    if(strCurFilePath.isEmpty())
        return;

    cFile.setFileName(strCurFilePath);
    if(!cFile.open(QIODeviceBase::ReadOnly))
        return;

    cDataStream.setDevice(&cFile);
    cDataStream.setByteOrder(QDataStream::LittleEndian);                           //设置为小端字节序

    cDataStream.readRawData(reinterpret_cast<char*>(&sRowCount), sizeof(sRowCount));
    cDataStream.readRawData(reinterpret_cast<char*>(&sColumnCount), sizeof(sColumnCount));

    SetTabelViewRowAndColumn(m_pcStandardItemModel, sRowCount, sColumnCount);

    qDebug() << sRowCount << " " << sColumnCount;
    for (int i = 0; i < sColumnCount; ++i)
    {
        QString strHeaderData;

        cDataStream.readBytes(pchStartAddr, unLen);
        strHeaderData = QString::fromLocal8Bit(pchStartAddr, unLen);            //支持中文字符

        qDebug() << pchStartAddr << " " << unLen;

        m_pcStandardItemModel->setHeaderData(i, Qt::Orientation::Horizontal, strHeaderData, Qt::DisplayRole);

        delete[] pchStartAddr;
        pchStartAddr = nullptr;
    }

    for (int i = 0; i < sRowCount; ++i)
    {
        qint32 nColumnIndex = 0;

        cDataStream.readRawData(reinterpret_cast<char*>(&sMeasuringDepth), sizeof(sMeasuringDepth));
        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        m_pcStandardItemModel->setData(cModelIndex, sMeasuringDepth, Qt::DisplayRole);

        cDataStream.readRawData(reinterpret_cast<char*>(&dbVerticalDepth), sizeof(dbVerticalDepth));
        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        m_pcStandardItemModel->setData(cModelIndex, dbVerticalDepth, Qt::DisplayRole);

        cDataStream.readRawData(reinterpret_cast<char*>(&dbOrientation), sizeof(dbOrientation));
        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        m_pcStandardItemModel->setData(cModelIndex, dbOrientation, Qt::DisplayRole);

        cDataStream.readRawData(reinterpret_cast<char*>(&dbDisplacement), sizeof(dbDisplacement));
        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        m_pcStandardItemModel->setData(cModelIndex, dbDisplacement, Qt::DisplayRole);

        cDataStream.readBytes(pchStartAddr, unLen);
        strQuality = QString::fromUtf8(pchStartAddr, unLen);            //支持中文字符
        delete[] pchStartAddr;
        pchStartAddr = nullptr;

        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        m_pcStandardItemModel->setData(cModelIndex, strQuality, Qt::DisplayRole);

        cDataStream.readRawData(reinterpret_cast<char*>(&bIsSampled), sizeof(bIsSampled));
        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        m_pcStandardItemModel->itemFromIndex(cModelIndex)->setCheckable(true);
        if(bIsSampled)
        {
            m_pcStandardItemModel->itemFromIndex(cModelIndex)->setCheckState(Qt::Checked);
            m_pcStandardItemModel->setData(cModelIndex, "strQuality", Qt::DisplayRole);
        }
        else
        {
            m_pcStandardItemModel->itemFromIndex(cModelIndex)->setCheckState(Qt::Unchecked);
            m_pcStandardItemModel->setData(cModelIndex, "unstrQuality", Qt::DisplayRole);
        }
    }

    cFile.close();

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::SaveQStandardItemModelDataToDatFile()
{
    QFile cFile;
    QDataStream cDataStream;
    QString strCurFilePath = QString();
    QString strFilter = tr("(dat文件(*.dat))");

    qint16 sRowCount = 0;                       //行数
    qint16 sColumnCount = 0;                    //列数
    qint16 sMeasuringDepth = 0;                 //测深
    qreal dbVerticalDepth = 0;                  //垂深
    qreal dbOrientation = 0;                    //方位
    qreal dbDisplacement = 0;                   //位移
    QString strQuality;                         //固井质量
    bool bIsSampled = false;                    //采样

    QModelIndex cModelIndex;

    strCurFilePath = QFileDialog::getSaveFileName(this, tr("保存文件"), QCoreApplication::applicationFilePath(), strFilter);
    if(strCurFilePath.isEmpty())
        return;

    cFile.setFileName(strCurFilePath);
    if(!cFile.open(QIODeviceBase::WriteOnly))
        return;

    cDataStream.setDevice(&cFile);
    cDataStream.setByteOrder(QDataStream::LittleEndian);                           //设置为小端字节序

    sRowCount = m_pcStandardItemModel->rowCount();
    sColumnCount = m_pcStandardItemModel->columnCount();

    cDataStream.writeRawData((char*)&sRowCount, sizeof(sRowCount));
    cDataStream.writeRawData((char*)&sColumnCount, sizeof(sColumnCount));

    for (int i = 0; i < sColumnCount; ++i)
    {
        QString strHeaderData;
        strHeaderData = m_pcStandardItemModel->headerData(i, Qt::Orientation::Horizontal, Qt::DisplayRole).toString();
        cDataStream.writeBytes((char*)strHeaderData.data(), strHeaderData.length());
    }

    for (int i = 0; i < sRowCount; ++i)
    {
        qint32 nColumnIndex = 0;

        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        sMeasuringDepth = m_pcStandardItemModel->data(cModelIndex, Qt::DisplayRole).toInt();
        cDataStream.writeRawData((char*)&sMeasuringDepth, sizeof(sMeasuringDepth));

        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        dbVerticalDepth = m_pcStandardItemModel->data(cModelIndex, Qt::DisplayRole).toReal();
        cDataStream.writeRawData((char*)&dbVerticalDepth, sizeof(dbVerticalDepth));

        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        dbOrientation = m_pcStandardItemModel->data(cModelIndex, Qt::DisplayRole).toReal();
        cDataStream.writeRawData((char*)&dbOrientation, sizeof(dbOrientation));

        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        dbDisplacement = m_pcStandardItemModel->data(cModelIndex, Qt::DisplayRole).toReal();
        cDataStream.writeRawData((char*)&dbDisplacement, sizeof(dbDisplacement));

        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        strQuality = m_pcStandardItemModel->data(cModelIndex, Qt::DisplayRole).toString();
        cDataStream.writeBytes((char*)strQuality.data(), strQuality.length());

        cModelIndex = m_pcStandardItemModel->index(i, nColumnIndex++);
        bIsSampled = m_pcStandardItemModel->itemFromIndex(cModelIndex)->checkState();
        cDataStream.writeRawData((char*)&bIsSampled, sizeof(bIsSampled));
    }

    cFile.close();
}

