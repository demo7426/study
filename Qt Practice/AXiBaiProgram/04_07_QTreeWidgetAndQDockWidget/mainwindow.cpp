/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.03
描  述:	实现当前的widget ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.03
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QFileDialog>

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
    delete m_pcLabel_Pixmap;
    delete m_pcPixmap;
    delete m_pcVBoxLayout;
}

void MainWindow::InitUi(void) noexcept
{
    m_pcLabel_Pixmap = new QLabel();
    m_pcPixmap = new QPixmap();
    m_pcVBoxLayout = new QVBoxLayout();

    ui->dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
}


void MainWindow::InitSignalSlots(void) noexcept
{
    connect(ui->actAddFolder, &QAction::triggered, this, &MainWindow::TreeWidgetAddFolder);
    connect(ui->actAddFiles, &QAction::triggered, this, &MainWindow::TreeWidgetAddFiles);
    connect(ui->actScanItems, &QAction::triggered, this, [=](){
        for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i)
        {
            this->TreeWidgetTraversalItems(ui->treeWidget->topLevelItem(i));
        }
    });

    connect(ui->treeWidget, &QTreeWidget::currentItemChanged, this, &MainWindow::CurrentItemChanged);

    connect(ui->actDockVisible, &QAction::triggered, this, [=](bool _Checked){
        if(!_Checked)
            ui->dockWidget->hide();
        else
            ui->dockWidget->show();
    });

    connect(ui->actDockFloat, &QAction::triggered, this, [=](bool _Checked){
        ui->dockWidget->setFloating(_Checked);
    });

    connect(ui->actZoomIn, &QAction::triggered, this, [this](){
        this->ZoomPicture(ZOOMTYPE::IN);
        qDebug() << "2";
    });

    connect(ui->actZoomOut, &QAction::triggered, this, [this](){
        this->ZoomPicture(ZOOMTYPE::OUT);
    });

    connect(ui->actZoomRealSize, &QAction::triggered, this, [this](){
        this->ZoomPicture(ZOOMTYPE::REALSIZE);
    });

    connect(ui->actZoomFitH, &QAction::triggered, this, [this](){
        this->ZoomPicture(ZOOMTYPE::SUITABLEHeIGHT);
    });

    connect(ui->actZoomFitW, &QAction::triggered, this, [this](){
        this->ZoomPicture(ZOOMTYPE::SUITABLEWIDTH);
    });

    connect(ui->actDeleteItem, &QAction::triggered, this, [this](){
        QTreeWidgetItem* pcCurItem = ui->treeWidget->currentItem();
        qint32 nCount = pcCurItem->childCount();

        for (int i = 0; i < nCount; ++i)
        {
            delete pcCurItem->child(i);
        }

        delete pcCurItem;
    });

    connect(ui->dockWidget, &QDockWidget::topLevelChanged, this, [=](bool _TopLevel){
        ui->actDockFloat->setChecked(_TopLevel);
    });

    connect(ui->dockWidget, &QDockWidget::visibilityChanged, this, [=](bool _TopLevel){
        ui->actDockVisible->setChecked(_TopLevel);
    });
}

void MainWindow::TreeWidgetAddFolder() noexcept
{
    QString strOpenDir = QFileDialog::getExistingDirectory(this);
    QTreeWidgetItem* pcCurTreeWidgetItem = nullptr;                          //当前TreeWidgetItem条目
    QTreeWidgetItem* pcChildItem = new QTreeWidgetItem(QTreeWidgetItem::ItemType::UserType);

    pcCurTreeWidgetItem = ui->treeWidget->currentItem();

    pcChildItem->setText(static_cast<qint32>(COLUMNTYPE::VALUE), strOpenDir.right(strOpenDir.count() - strOpenDir.lastIndexOf('/') - 1));
    pcChildItem->setData(static_cast<qint32>(COLUMNTYPE::VALUE), Qt::DisplayRole, strOpenDir);
    pcChildItem->setIcon(static_cast<qint32>(COLUMNTYPE::VALUE), QIcon(tr(":/images/icons/300.bmp")));
    pcChildItem->setCheckState(static_cast<qint32>(COLUMNTYPE::VALUE), Qt::Checked);
    pcChildItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable |Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);

    pcChildItem->setText(static_cast<qint32>(COLUMNTYPE::TYPE), "DIR");
    pcChildItem->setData(static_cast<qint32>(COLUMNTYPE::TYPE), Qt::DisplayRole, strOpenDir);

    if(pcCurTreeWidgetItem == nullptr)                                       //如果为空，则添加到根节点中
    {
        qDebug() << "TreeWidgetAddFolder currentItem is nullptr.";

        ui->treeWidget->addTopLevelItem(pcChildItem);                       //因为没有选择父节点，所以直接添加到根节点中去
        return;
    }

    //将节点添加到指定的节点中
    pcCurTreeWidgetItem->addChild(pcChildItem);
}

void MainWindow::TreeWidgetAddFiles() noexcept
{
    QStringList cStringList_Files;
    QTreeWidgetItem* pcChildItem = nullptr;
    QString strCurFilePath;
    QTreeWidgetItem* pcCurTreeWidgetItem = nullptr;                          //当前TreeWidgetItem条目

    pcCurTreeWidgetItem = ui->treeWidget->currentItem();

    cStringList_Files.clear();
    cStringList_Files = QFileDialog::getOpenFileNames(this, tr("Select one or more files to open"), tr("./"), tr("Images(*.jpg *.png)"));

    for (qsizetype i = 0; i < cStringList_Files.count(); ++i)
    {
        pcChildItem = new QTreeWidgetItem(QTreeWidgetItem::ItemType::UserType);

        strCurFilePath = cStringList_Files.at(i);
        pcChildItem->setText(static_cast<qint32>(COLUMNTYPE::VALUE), strCurFilePath.right(strCurFilePath.count() - strCurFilePath.lastIndexOf('/') - 1));
        pcChildItem->setData(static_cast<qint32>(COLUMNTYPE::VALUE), Qt::DisplayRole, strCurFilePath);
        pcChildItem->setIcon(static_cast<qint32>(COLUMNTYPE::VALUE), QIcon(tr(":/images/icons/301.bmp")));
        pcChildItem->setCheckState(static_cast<qint32>(COLUMNTYPE::VALUE), Qt::Checked);
        pcChildItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);

        pcChildItem->setText(static_cast<qint32>(COLUMNTYPE::TYPE), "IMAGE");
        pcChildItem->setData(static_cast<qint32>(COLUMNTYPE::TYPE), Qt::DisplayRole, strCurFilePath);

        if(pcCurTreeWidgetItem == nullptr)                                      //如果为空，则添加到根节点中
              ui->treeWidget->addTopLevelItem(pcChildItem);                     //因为没有选择父节点，所以直接添加到根节点中去
        else
            pcCurTreeWidgetItem->addChild(pcChildItem);                         //将节点添加到指定的节点中
    }
}

void MainWindow::TreeWidgetTraversalItems(QTreeWidgetItem* _pCurTreeWidgetItem) noexcept
{
    if(_pCurTreeWidgetItem == nullptr)
    {
        qDebug() << "TreeWidgetTraversalItems inputparam is err.";
        return;
    }

    qint32 nChildItemCount = 0;                                             //子节点数量
    QString strValueText = "";
    QString strTypeText = "";

    nChildItemCount = _pCurTreeWidgetItem->childCount();

    strValueText = _pCurTreeWidgetItem->text(static_cast<qint32>(COLUMNTYPE::VALUE));
    strTypeText = _pCurTreeWidgetItem->text(static_cast<qint32>(COLUMNTYPE::TYPE));

    _pCurTreeWidgetItem->setText(static_cast<qint32>(COLUMNTYPE::VALUE), "*" + strValueText);

    for (int i = 0; i < nChildItemCount; ++i)
    {
        this->TreeWidgetTraversalItems(_pCurTreeWidgetItem->child(i));
    }
}

void MainWindow::CurrentItemChanged(QTreeWidgetItem *pCurrent, QTreeWidgetItem *_Previous)
{
    Q_UNUSED(_Previous);

    if(pCurrent == nullptr)
    {
        qDebug() << "CurrentItemChanged inputparam is err.";

        ui->actDeleteItem->setEnabled(false);
        return;
    }

    QString strFilePath = pCurrent->data(static_cast<qint32>(COLUMNTYPE::VALUE), Qt::DisplayRole).toString();

    if(strFilePath.isEmpty())
    {
        qDebug() << "CurrentItemChanged strFilePath is empty.";

        return;
    }

    ui->actDeleteItem->setEnabled(true);

    if(strFilePath.contains(".jpg") || strFilePath.contains(".bmp") || strFilePath.contains(".png"))
    {
        //显示图像
        m_pcPixmap->load(strFilePath);
        m_pcLabel_Pixmap->setPixmap(*m_pcPixmap);
        m_pcVBoxLayout->addWidget(m_pcLabel_Pixmap);
        ui->scrollArea->setLayout(m_pcVBoxLayout);

        ui->actZoomIn->setEnabled(true);
        ui->actZoomOut->setEnabled(true);
        ui->actZoomFitH->setEnabled(true);
        ui->actZoomFitW->setEnabled(true);
        ui->actZoomRealSize->setEnabled(true);
        // ui->scrollAreaWidgetContents->setLayout(m_pcVBoxLayout);
        // ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    }
    else
    {
        ui->actZoomIn->setEnabled(false);
        ui->actZoomOut->setEnabled(false);
        ui->actZoomFitH->setEnabled(false);
        ui->actZoomFitW->setEnabled(false);
        ui->actZoomRealSize->setEnabled(false);
    }

}

void MainWindow::ZoomPicture(ZOOMTYPE _Flag) noexcept
{
    QString strFilePath = ui->treeWidget->currentItem()->data(static_cast<qint32>(COLUMNTYPE::VALUE), Qt::DisplayRole).toString();

    switch (_Flag)
    {
    case ZOOMTYPE::IN:                  //缩小图片
    {
        qDebug() << "1";
        m_cPixmapSize = m_pcPixmap->size() * 0.8;
        m_pcPixmap->load(strFilePath);
        *m_pcPixmap = m_pcPixmap->scaled(m_cPixmapSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        m_pcLabel_Pixmap->setPixmap(*m_pcPixmap);
    }
    break;
    case ZOOMTYPE::OUT:                 //放大图片
    {
        qDebug() << "1";
        m_cPixmapSize = m_pcPixmap->size() / 0.8;
        m_pcPixmap->load(strFilePath);
        *m_pcPixmap = m_pcPixmap->scaled(m_cPixmapSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        m_pcLabel_Pixmap->setPixmap(*m_pcPixmap);
    }
    break;
    case ZOOMTYPE::REALSIZE:            //还原真实大小
    {
        m_pcPixmap->load(strFilePath);
        m_pcLabel_Pixmap->setPixmap(*m_pcPixmap);
    }
    break;
    case ZOOMTYPE::SUITABLEHeIGHT:      //适合的高度
    {
        m_pcPixmap->load(strFilePath);

        if(m_pcLabel_Pixmap->height() < m_pcPixmap->height())
        {
            *m_pcPixmap = m_pcPixmap->scaledToWidth(m_pcPixmap->width() * (m_pcPixmap->height() / m_pcLabel_Pixmap->height()));
            *m_pcPixmap = m_pcPixmap->scaledToHeight(m_pcLabel_Pixmap->height());
        }
        else
        {
            *m_pcPixmap = m_pcPixmap->scaledToWidth(m_pcPixmap->width() * (m_pcLabel_Pixmap->height() / m_pcPixmap->height()));
            *m_pcPixmap = m_pcPixmap->scaledToHeight(m_pcLabel_Pixmap->height());
        }

        m_pcLabel_Pixmap->setPixmap(*m_pcPixmap);
    }
    break;
    case ZOOMTYPE::SUITABLEWIDTH:       //适合宽度
    {
        m_pcPixmap->load(strFilePath);

        if(m_pcLabel_Pixmap->width() < m_pcPixmap->width())
        {
            *m_pcPixmap = m_pcPixmap->scaledToHeight(m_pcPixmap->height() * (m_pcPixmap->width() / m_pcLabel_Pixmap->width()));
            *m_pcPixmap = m_pcPixmap->scaledToWidth(m_pcLabel_Pixmap->width());
        }
        else
        {
            *m_pcPixmap = m_pcPixmap->scaledToHeight(m_pcPixmap->height() * (m_pcLabel_Pixmap->width() / m_pcPixmap->width()));
            *m_pcPixmap = m_pcPixmap->scaledToWidth(m_pcLabel_Pixmap->width());
        }

        m_pcLabel_Pixmap->setPixmap(*m_pcPixmap);
    }
    break;
    default:
        break;
    }
}
