#include <QCheckBox>
#include <QLayout>

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
    ui->tableWidget->setAlternatingRowColors(ui->chkBoxRowColor->checkState());

    m_pcLabel_CurPos = new QLabel(this);
    m_pcLabel_Type = new QLabel(this);
    m_pcLabel_ID = new QLabel(this);

    m_pcLabel_CurPos->setMinimumWidth(200);
    m_pcLabel_Type->setMinimumWidth(200);
    m_pcLabel_Type->setMinimumWidth(200);

    ui->statusbar->addWidget(m_pcLabel_CurPos);
    ui->statusbar->addWidget(m_pcLabel_Type);
    ui->statusbar->addWidget(m_pcLabel_ID);
}

void MainWindow::InitSignalSlots() noexcept
{
    connect(ui->btnSetHeader, &QPushButton::clicked, this, [this](){
        this->SetTableWidgetHeader(ui->tableWidget);
    });

    connect(ui->btnSetRows, &QPushButton::clicked, this, [this](){
        this->SetTableWidgetRowCount(ui->tableWidget, ui->spinRowCount->value());
    });

    connect(ui->btnIniData, &QPushButton::clicked, this, [this](){
        TABLEWIDGETROW_INFO tTableWidgetRow_Info;

        for (qint32 i = 0; i < ui->tableWidget->rowCount(); ++i)
        {
            tTableWidgetRow_Info.Name = QString::asprintf("学生 %u", i);
            tTableWidgetRow_Info.Sex = i % 2 == 0? "男": "女";
            tTableWidgetRow_Info.DateOfBirth = QDate(1998, 9, i % 30 + 1);
            tTableWidgetRow_Info.Nation = "汉族";
            tTableWidgetRow_Info.Score = 80 + i % 21;
            tTableWidgetRow_Info.IsParty = i % 3 == 0? true: false;
            tTableWidgetRow_Info.ID = 1000000 + i;

            SetTableWidgetRowOfata(ui->tableWidget, i, tTableWidgetRow_Info);
        }
    });

    connect(ui->btnAutoHeight, &QPushButton::clicked, this, [this](){
        ui->tableWidget->resizeRowsToContents();
    });

    connect(ui->btnAutoWidth, &QPushButton::clicked, this, [this](){
        ui->tableWidget->resizeColumnsToContents();
    });

    connect(ui->btnInsertRow, &QPushButton::clicked, this, [this](){
        TABLEWIDGETROW_INFO tTableWidgetRow_Info;

        tTableWidgetRow_Info.Name = QString::asprintf("学生 插入");
        tTableWidgetRow_Info.Sex = rand() % 2 == 0? "男": "女";
        tTableWidgetRow_Info.DateOfBirth = QDate(1998, 12, rand() % 30 + 1);
        tTableWidgetRow_Info.Nation = "壮族";
        tTableWidgetRow_Info.Score = 80 + rand() % 20;
        tTableWidgetRow_Info.IsParty = rand() % 3 == 0? true: false;
        tTableWidgetRow_Info.ID = 1000000 + rand();

        ui->tableWidget->insertRow(ui->tableWidget->currentRow());

        SetTableWidgetRowOfata(ui->tableWidget, ui->tableWidget->currentRow() - 1, tTableWidgetRow_Info);
    });


    connect(ui->btnAppendRow, &QPushButton::clicked, this, [this](){
        TABLEWIDGETROW_INFO tTableWidgetRow_Info;

        tTableWidgetRow_Info.Name = QString::asprintf("学生 新增");
        tTableWidgetRow_Info.Sex = rand() % 2 == 0? "男": "女";
        tTableWidgetRow_Info.DateOfBirth = QDate(1998, 12, rand() % 30 + 1);
        tTableWidgetRow_Info.Nation = "壮族";
        tTableWidgetRow_Info.Score = 80 + rand() % 20;
        tTableWidgetRow_Info.IsParty = rand() % 3 == 0? true: false;
        tTableWidgetRow_Info.ID = 1000000 + rand();

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        SetTableWidgetRowOfata(ui->tableWidget, ui->tableWidget->rowCount() - 1, tTableWidgetRow_Info);
    });

    connect(ui->btnDelCurRow, &QPushButton::clicked, this, [this](){

        for (qint32 i = 0; i < (qint32)TABLEWIDGETCOLUMNINDEX::ISPARTY_INDEX; ++i)
        {
            delete ui->tableWidget->cellWidget(ui->tableWidget->currentRow(), i);
        }

        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    });

    connect(ui->chkBoxTabEditable, &QCheckBox::stateChanged, this, [=](int _State){

        Qt::ItemFlags flags;

        if(_State == Qt::Checked)
            flags = Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
        else if(_State == Qt::Unchecked)
            flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
        else{}

        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
        {
            for (int j = 0; j < ui->tableWidget->columnCount(); ++j)
            {
                ui->tableWidget->item(i, j)->setFlags(flags);
            }
        }
    });

    connect(ui->chkBoxHeaderH, &QCheckBox::stateChanged, this, [=](int _State){
        ui->tableWidget->horizontalHeader()->setVisible(_State);
    });

    connect(ui->chkBoxHeaderV, &QCheckBox::stateChanged, this, [=](int _State){
        ui->tableWidget->verticalHeader()->setVisible(_State);
    });

    connect(ui->rBtnSelectRow, &QRadioButton::clicked, this, [=](){
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    });

    connect(ui->rBtnSelectItem, &QRadioButton::clicked, this, [=](){
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
    });

    connect(ui->btnReadToEdit, &QPushButton::clicked, this, [=](){
        this->ReadContentToPlainTextEdit(ui->tableWidget, ui->plainTextEdit);
    });

    connect(ui->tableWidget, &QTableWidget::cellClicked, this, [=](int row, int column){
        m_pcLabel_CurPos->setText(QString::asprintf("当前位置: %d行, %d列", row + 1, column + 1));

        m_pcLabel_Type->setText(QString::asprintf("当前类型: %d",
                                                qobject_cast<QTableWidget*>(sender())->item(row, column)->type() ));

        m_pcLabel_ID->setText(QString::asprintf("当前ID: %d",
                                                qobject_cast<QTableWidget*>(sender())->item(row, column)->data(m_nIDRole).toInt() ));

    });

    connect(ui->chkBoxRowColor, &QCheckBox::stateChanged, this, [this](int _State){
            ui->tableWidget->setAlternatingRowColors(_State == Qt::Checked);
    });
}

void MainWindow::SetTableWidgetHeader(QTableWidget *_pTableWidget) noexcept
{
    if(_pTableWidget == nullptr)
        return;

    QTableWidgetItem* pcTableWidgetItem;
    QStringList strListHeader;

    strListHeader << "姓 名" << "性 别" << "出生日期" << "民 族" << "分 数" << "是否是党员";

    for (int i = 0; i < strListHeader.count(); ++i)
    {
        QFont cFont;

        pcTableWidgetItem = new QTableWidgetItem(static_cast<QTableWidgetItem::ItemType>(ItemType::HEADER));

        pcTableWidgetItem->setText(strListHeader[i]);

        cFont = pcTableWidgetItem->font();
        cFont.bold();
        cFont.setPointSize(10);
        pcTableWidgetItem->setFont(cFont);

        pcTableWidgetItem->setForeground(QBrush(QColor(Qt::red)));

        _pTableWidget->setHorizontalHeaderItem(i, pcTableWidgetItem);
    }


}

void MainWindow::SetTableWidgetRowCount(QTableWidget *_pTableWidget, quint32 _RowCount) noexcept
{
    if(_pTableWidget == nullptr)
        return;

    _pTableWidget->setRowCount(_RowCount);
}

void MainWindow::SetTableWidgetRowOfata(QTableWidget *_pTableWidget, const quint32& _RowNo, const TABLEWIDGETROW_INFO& _TableWidgetRow_Info) noexcept
{
    if(_pTableWidget == nullptr)
        return;

    QTableWidgetItem* pcTableWidgetItem;

    //设置姓名显示
    pcTableWidgetItem = new QTableWidgetItem(static_cast<QTableWidgetItem::ItemType>(ItemType::NAME));
    pcTableWidgetItem->setText(_TableWidgetRow_Info.Name);
    pcTableWidgetItem->setData(m_nIDRole, _TableWidgetRow_Info.ID);
    _pTableWidget->setItem(_RowNo, (int)TABLEWIDGETCOLUMNINDEX::NAME_INDEX, pcTableWidgetItem);

    //设置性别显示
    pcTableWidgetItem = new QTableWidgetItem(static_cast<QTableWidgetItem::ItemType>(ItemType::SEX));
    pcTableWidgetItem->setText(_TableWidgetRow_Info.Sex);

    if(_TableWidgetRow_Info.Sex == "男")
        pcTableWidgetItem->setIcon(QIcon(tr(":/images/icons/boy.ico")));
    else if(_TableWidgetRow_Info.Sex == "女")
        pcTableWidgetItem->setIcon(QIcon(tr(":/images/icons/girl.ico")));

    pcTableWidgetItem->setData(m_nIDRole, _TableWidgetRow_Info.ID);
    _pTableWidget->setItem(_RowNo, (int)TABLEWIDGETCOLUMNINDEX::SEX_INDEX, pcTableWidgetItem);


    //设置出生日期显示
    pcTableWidgetItem = new QTableWidgetItem(static_cast<QTableWidgetItem::ItemType>(ItemType::DATEOFBIRTH));
    pcTableWidgetItem->setText(_TableWidgetRow_Info.DateOfBirth.toString("yyyy-MM-dd"));
    pcTableWidgetItem->setData(m_nIDRole, _TableWidgetRow_Info.ID);
    _pTableWidget->setItem(_RowNo, (int)TABLEWIDGETCOLUMNINDEX::DATEOFBIRTH_INDEX, pcTableWidgetItem);

    //设置民族显示
    pcTableWidgetItem = new QTableWidgetItem(static_cast<QTableWidgetItem::ItemType>(ItemType::NATION));
    pcTableWidgetItem->setText(_TableWidgetRow_Info.Nation);
    pcTableWidgetItem->setData(m_nIDRole, _TableWidgetRow_Info.ID);
    _pTableWidget->setItem(_RowNo, (int)TABLEWIDGETCOLUMNINDEX::NATION_INDEX, pcTableWidgetItem);

    //设置分数显示
    pcTableWidgetItem = new QTableWidgetItem(static_cast<QTableWidgetItem::ItemType>(ItemType::SCORE));
    pcTableWidgetItem->setText(QString::number(_TableWidgetRow_Info.Score));
    pcTableWidgetItem->setData(m_nIDRole, _TableWidgetRow_Info.ID);
    _pTableWidget->setItem(_RowNo, (int)TABLEWIDGETCOLUMNINDEX::SCORE_INDEX, pcTableWidgetItem);

    //设置身份显示
    pcTableWidgetItem = new QTableWidgetItem(static_cast<QTableWidgetItem::ItemType>(ItemType::ISPARTY));

    if(_TableWidgetRow_Info.IsParty)                        //根据不同的身份进行显示
        pcTableWidgetItem->setCheckState(Qt::Checked);
    else
        pcTableWidgetItem->setCheckState(Qt::Unchecked);
    pcTableWidgetItem->setText("党员");

    pcTableWidgetItem->setData(m_nIDRole, _TableWidgetRow_Info.ID);
    _pTableWidget->setItem(_RowNo, (int)TABLEWIDGETCOLUMNINDEX::ISPARTY_INDEX, pcTableWidgetItem);
}

void MainWindow::ReadContentToPlainTextEdit(QTableWidget *_pTableWidget, QPlainTextEdit *_pPlainTextEdit)
{
    if(_pTableWidget == nullptr || _pPlainTextEdit == nullptr)
        return;

    QString strContent = "";

    _pPlainTextEdit->clear();

    for (int i = 0; i < _pTableWidget->rowCount(); ++i)
    {
        for (int j = 0; j < _pTableWidget->columnCount() - 1; ++j)
        {
            strContent += _pTableWidget->item(i, j)->text();
            strContent += " ";
        }


        if(_pTableWidget->item(i, _pTableWidget->columnCount() - 1)->checkState())
            strContent += "党员";
        else
            strContent += "群众";

        _pPlainTextEdit->appendPlainText(strContent);
        strContent.clear();
    }
}


