/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.12
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QFileDialog>
#include <QRegularExpression>

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

    if(m_pcStyledItemDelegate != nullptr)
        delete m_pcStyledItemDelegate;

    if(m_pcStandardItemModel != nullptr)
        delete m_pcStandardItemModel;

    if(m_pcItemSelectionModel != nullptr)
        delete m_pcItemSelectionModel;

    if(m_pcLabel_FilePath != nullptr)
        delete m_pcLabel_FilePath;

    if(m_pcLabel_Pos != nullptr)
        delete m_pcLabel_Pos;

    if(m_pcLabel_Text != nullptr)
        delete m_pcLabel_Text;
}

void MainWindow::InitUi() noexcept
{
    m_pcStyledItemDelegate = new CSpinIntDelegate(this);
    m_pcStandardItemModel = new QStandardItemModel(m_unRowCount, m_unColumnCount, this);
    m_pcItemSelectionModel = new QItemSelectionModel(m_pcStandardItemModel);                //将QItemSelectionModel和QStandardItemModel联系起来

    ui->tableView->setItemDelegateForColumn(2, m_pcStyledItemDelegate);                     //注册代理
    ui->tableView->setModel(m_pcStandardItemModel);                                         //注册model模型
    ui->tableView->setSelectionModel(m_pcItemSelectionModel);                               //注册选择模型

    m_pcLabel_FilePath = new QLabel("当前路径:", this);
    m_pcLabel_Pos = new QLabel("当前位置:", this);
    m_pcLabel_Text = new QLabel("当前内容:", this);

    ui->statusbar->addWidget(m_pcLabel_FilePath, 1);
    ui->statusbar->addWidget(m_pcLabel_Pos, 1);
    ui->statusbar->addWidget(m_pcLabel_Text, 1);
}

void MainWindow::InitSignalSlots() noexcept
{
    connect(m_pcItemSelectionModel, &QItemSelectionModel::currentChanged, this, &MainWindow::CurrentChanged);

    connect(ui->actOpen, &QAction::triggered, this, &MainWindow::LoadFileData);
    connect(ui->actSave, &QAction::triggered, this, &MainWindow::SaveDataToFile);
    connect(ui->actModelData, &QAction::triggered, this, &MainWindow::ModelDataPreview);

    connect(ui->actInsert, &QAction::triggered, this, [this](){
        InsertRow(m_pcStandardItemModel, m_pcItemSelectionModel->currentIndex());
    });
    connect(ui->actAppend, &QAction::triggered, this, [this](){
        AppendRow(m_pcStandardItemModel, m_pcItemSelectionModel->currentIndex());
    });
    connect(ui->actDelete, &QAction::triggered, this, [this](){
        DeleteRow(m_pcStandardItemModel, m_pcItemSelectionModel->currentIndex());
    });


    connect(ui->actAlignLeft, &QAction::triggered, this, [this](){
        QModelIndexList cModelIndexList = m_pcItemSelectionModel->selectedIndexes();
        QStandardItem* pcStandardItem;

        for (int i = 0; i < cModelIndexList.size(); ++i)
        {
            pcStandardItem = m_pcStandardItemModel->itemFromIndex(cModelIndexList[i]);
            pcStandardItem->setTextAlignment(pcStandardItem->textAlignment() & Qt::AlignVCenter | Qt::AlignLeft);
        }

        ui->actAlignRight->setChecked(Qt::Unchecked);
        ui->actAlignHCenter->setChecked(Qt::Unchecked);
    });

    connect(ui->actAlignHCenter, &QAction::triggered, this, [this](){
        QModelIndexList cModelIndexList = m_pcItemSelectionModel->selectedIndexes();
        QStandardItem* pcStandardItem;

        for (int i = 0; i < cModelIndexList.size(); ++i)
        {
            pcStandardItem = m_pcStandardItemModel->itemFromIndex(cModelIndexList[i]);

            pcStandardItem->setTextAlignment(pcStandardItem->textAlignment() & Qt::AlignVCenter | Qt::AlignHCenter);
        }

        ui->actAlignLeft->setChecked(Qt::Unchecked);
        ui->actAlignRight->setChecked(Qt::Unchecked);
    });

    connect(ui->actAlignVCenter, &QAction::triggered, this, [this](bool _Checked){
        QModelIndexList cModelIndexList = m_pcItemSelectionModel->selectedIndexes();
        QStandardItem* pcStandardItem;

        for (int i = 0; i < cModelIndexList.size(); ++i)
        {
            pcStandardItem = m_pcStandardItemModel->itemFromIndex(cModelIndexList[i]);

            if(_Checked)
                pcStandardItem->setTextAlignment(pcStandardItem->textAlignment() | Qt::AlignVCenter);
            else
                pcStandardItem->setTextAlignment(pcStandardItem->textAlignment() & ~Qt::AlignVCenter);
        }

    });

    connect(ui->actAlignRight, &QAction::triggered, this, [this](){
        QModelIndexList cModelIndexList = m_pcItemSelectionModel->selectedIndexes();
        QStandardItem* pcStandardItem;

        for (int i = 0; i < cModelIndexList.size(); ++i)
        {
            pcStandardItem = m_pcStandardItemModel->itemFromIndex(cModelIndexList[i]);
            pcStandardItem->setTextAlignment(pcStandardItem->textAlignment() & Qt::AlignVCenter | Qt::AlignRight);
        }

        ui->actAlignLeft->setChecked(Qt::Unchecked);
        ui->actAlignHCenter->setChecked(Qt::Unchecked);
    });


    connect(ui->actFontBold, &QAction::triggered, this, [this](bool _Checked){
        QModelIndexList cModelIndexList = m_pcItemSelectionModel->selectedIndexes();
        QStandardItem* pcStandardItem;
        QFont cFont;

        for (int i = 0; i < cModelIndexList.size(); ++i)
        {
            pcStandardItem = m_pcStandardItemModel->itemFromIndex(cModelIndexList[i]);

            cFont = pcStandardItem->font();

            if(_Checked)
                cFont.setBold(true);
            else
                cFont.setBold(false);

            pcStandardItem->setFont(cFont);
        }
    });
}

void MainWindow::CurrentChanged(const QModelIndex &_Current, const QModelIndex &_Previous)
{
    Q_UNUSED(_Previous);

    if(!_Current.isValid())
        return;

    QStandardItem* pcStandardItem = m_pcStandardItemModel->itemFromIndex(_Current);
    QFont cFont = pcStandardItem->font();

    if(cFont.bold())
        ui->actFontBold->setChecked(true);
    else
        ui->actFontBold->setChecked(false);

    if(pcStandardItem->textAlignment() & Qt::AlignLeft)
        ui->actAlignLeft->setChecked(Qt::Checked);
    else
        ui->actAlignLeft->setChecked(Qt::Unchecked);


    if(pcStandardItem->textAlignment() & Qt::AlignHCenter)
        ui->actAlignHCenter->setChecked(Qt::Checked);
    else
        ui->actAlignHCenter->setChecked(Qt::Unchecked);

    if(pcStandardItem->textAlignment() & Qt::AlignVCenter)
        ui->actAlignVCenter->setChecked(Qt::Checked);
    else
        ui->actAlignVCenter->setChecked(Qt::Unchecked);

    if(pcStandardItem->textAlignment() & Qt::AlignRight)
        ui->actAlignRight->setChecked(Qt::Checked);
    else
        ui->actAlignRight->setChecked(Qt::Unchecked);

    m_pcLabel_Pos->setText(QString::asprintf("当前位置: %d行 %d列", _Current.row(), _Current.column()));
    m_pcLabel_Text->setText("当前内容:" + m_pcStandardItemModel->data(_Current).toString());
}

void MainWindow::LoadFileData()
{
    QString strFilePath;                //文件路径
    QString strContent;                 //读取出的每一行数据的内容
    QStringList strList;                //存储解析出的数据
    quint32 unCurColumnCount = 0;       //当前总行数
    QModelIndex cModelIndex;            //
    quint32 unCurRow = 0;               //当前行号

    strFilePath = QFileDialog::getOpenFileName(this, "打开文件", "./", "(*.txt);;(*.c)");

    QFile cFileRead(strFilePath);

    if(!cFileRead.open(QIODeviceBase::ReadOnly | QIODeviceBase::Text))
    {
        qDebug() << "打开文件失败";
        return;
    }

    QTextStream cTextStream(&cFileRead);

    //读取文本第一行信息,设置表头数据显示
    if(cTextStream.atEnd())
        return;

    strContent = cTextStream.readLine();
    strList = strContent.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);     //使用正则表达式切分数据

    unCurColumnCount = m_pcStandardItemModel->columnCount() > strList.size()? strList.size(): m_pcStandardItemModel->columnCount();
    for (quint32 i = 0; i < unCurColumnCount; ++i)                                  //设置表头的数据
    {
        m_pcStandardItemModel->setHeaderData(i, Qt::Horizontal, strList[i], Qt::DisplayRole);
    }

    //读取文本其它信息,设置表格数据显示

    unCurRow = 0;
    while(!cTextStream.atEnd())
    {
        strContent = cTextStream.readLine();
        strList = strContent.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);     //使用正则表达式切分数据

        unCurColumnCount = m_pcStandardItemModel->columnCount() > strList.size()? strList.size(): m_pcStandardItemModel->columnCount();
        for (quint32 i = 0; i < unCurColumnCount; ++i)                                  //设置表格的数据
        {
            cModelIndex = m_pcStandardItemModel->index(unCurRow, i);
            m_pcStandardItemModel->setData(cModelIndex, strList[i], Qt::DisplayRole);

            if(i == unCurColumnCount - 1)                                               //特殊处理最后一列数据
            {
                QStandardItem* pcStandardItem = m_pcStandardItemModel->itemFromIndex(cModelIndex);

                pcStandardItem->setCheckable(true);

                if(pcStandardItem->text() == "党员")
                    pcStandardItem->setCheckState(Qt::Checked);
            }
        }

        unCurRow += 1;
    }

    cFileRead.close();

    ui->actSave->setEnabled(true);
    ui->actModelData->setEnabled(true);
    ui->actAppend->setEnabled(true);
    ui->actDelete->setEnabled(true);
    ui->actInsert->setEnabled(true);

    ui->actAlignLeft->setEnabled(true);
    ui->actAlignHCenter->setEnabled(true);
    ui->actAlignVCenter->setEnabled(true);
    ui->actAlignRight->setEnabled(true);
    ui->actFontBold->setEnabled(true);

    m_pcLabel_FilePath->setText("当前路径:" + strFilePath);
}

void MainWindow::SaveDataToFile()
{
    QString strFilePath;                //文件路径
    QString strContent = "";
    QTextStream cTextStream;

    strFilePath = QFileDialog::getSaveFileName(this, "保存文件", "./", "(*.txt);;(*.c)");

    QFile cFileWrite(strFilePath);

    if(!cFileWrite.open(QIODeviceBase::WriteOnly | QIODeviceBase::Truncate | QIODeviceBase::Text))
    {
        qDebug() << "打开文件失败";
        return;
    }

    cTextStream.setDevice(&cFileWrite);

    //保存表头信息
    for (int i = 0; i < m_pcStandardItemModel->columnCount(); ++i)
    {
        strContent += m_pcStandardItemModel->headerData(i, Qt::Horizontal).toString();
        strContent += '\t';
    }

#ifdef __WIN32
    cTextStream << strContent << "\r\n";
#elif __linux
    cTextStream << strContent << "\n";
#endif
    strContent.clear();

    //保存表格数据
    for (int i = 0; i < m_pcStandardItemModel->rowCount(); ++i)
    {
        for (int j = 0; j < m_pcStandardItemModel->columnCount(); ++j)
        {
            strContent += m_pcStandardItemModel->data(m_pcStandardItemModel->index(i, j)).toString();
            strContent += '\t';
        }
#ifdef __WIN32
        cTextStream << strContent << "\r\n";
#elif __linux
        cTextStream << strContent << "\n";
#endif
        strContent.clear();
    }

    cFileWrite.close();
}

void MainWindow::ModelDataPreview()
{
    QString strContent = "";

    //保存表头信息
    for (int i = 0; i < m_pcStandardItemModel->columnCount(); ++i)
    {
        strContent += m_pcStandardItemModel->headerData(i, Qt::Horizontal).toString();
        strContent += '\t';
    }

    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText(strContent);
    strContent.clear();

    //保存表格数据
    for (int i = 0; i < m_pcStandardItemModel->rowCount(); ++i)
    {
        for (int j = 0; j < m_pcStandardItemModel->columnCount(); ++j)
        {
            strContent += m_pcStandardItemModel->data(m_pcStandardItemModel->index(i, j)).toString();
            strContent += '\t';
        }

        ui->plainTextEdit->appendPlainText(strContent);
        strContent.clear();
    }
}

void MainWindow::InsertRow(QStandardItemModel* _pStandardItemModel, const QModelIndex &_Current)
{
    if(_pStandardItemModel == nullptr)
        return;

    QList<QStandardItem*> cList;

    for(int i = 0; i < _pStandardItemModel->columnCount(); ++i)
    {
        QStandardItem* cStandardItem = new QStandardItem("插入数据");
        cList.push_back(cStandardItem);
    }

    _pStandardItemModel->insertRow(_Current.row(), cList);
}

void MainWindow::AppendRow(QStandardItemModel *_pStandardItemModel, const QModelIndex &_Current)
{
    if(_pStandardItemModel == nullptr)
        return;

    QList<QStandardItem*> cList;

    for(int i = 0; i < _pStandardItemModel->columnCount(); ++i)
    {
        QStandardItem* cStandardItem = new QStandardItem("添加数据");
        cList.push_back(cStandardItem);
    }

    _pStandardItemModel->insertRow(_pStandardItemModel->rowCount(), cList);
}

void MainWindow::DeleteRow(QStandardItemModel *_pStandardItemModel, const QModelIndex &_Current)
{
    qint32 nCurRow = _Current.row();
    qint32 nCurColumn = _Current.column();
    QModelIndex cCurModelIndex;

    _pStandardItemModel->removeRow(nCurRow);

    cCurModelIndex = _pStandardItemModel->index(nCurRow, nCurColumn);

    m_pcItemSelectionModel->setCurrentIndex(cCurModelIndex, QItemSelectionModel::SelectionFlag::SelectCurrent);
}












