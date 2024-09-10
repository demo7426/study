#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

Widget::~Widget()
{
    delete ui;

    if(m_pcStringListModel != nullptr)
    {
        delete m_pcStringListModel;
        m_pcStringListModel = nullptr;
    }
}


void Widget::InitUi(void) noexcept
{
    for (qint32 i = 0; i < 10; ++i)
    {
        m_cStringList << QString::asprintf("Item %d", i);
    }

    m_pcStringListModel= new QStringListModel(this);
}

void Widget::InitSignalSlots(void) noexcept
{
    connect(ui->pushBtnInitList, &QPushButton::clicked, this, &Widget::InitListView);
    connect(ui->pushBtnAddItem, &QPushButton::clicked, this, [this](){
        InsertModelIndexToListView(m_pcStringListModel->rowCount());
    });

    connect(ui->pushBtnInsertItem, &QPushButton::clicked, this, [this](){
        InsertModelIndexToListView(ui->listView->currentIndex().row());
    });

    connect(ui->pushBtnRemoveItem, &QPushButton::clicked, this, [this](){
        m_pcStringListModel->removeRow(ui->listView->currentIndex().row());
    });

    connect(ui->pushBtnClearList, &QPushButton::clicked, this, [this](){
        m_pcStringListModel->removeRows(0, m_pcStringListModel->rowCount());
    });

    connect(ui->pushBtnClearPlainText, &QPushButton::clicked, this, [this](){
        ui->plainTextEdit->clear();
    });

    connect(ui->pushBtnShowPlaintext, &QPushButton::clicked, this, [this](){
        for (qint32 i = 0; i < m_pcStringListModel->rowCount(); ++i) {
            ui->plainTextEdit->appendPlainText(m_pcStringListModel->data(m_pcStringListModel->index(i, 0)).toString());
        }
    });
}

void Widget::InitListView() noexcept
{
    m_pcStringListModel->setStringList(m_cStringList);                      //设置data
    ui->listView->setModel(m_pcStringListModel);                            //设置mode
}

void Widget::InsertModelIndexToListView(quint32 _Row) noexcept
{
    QModelIndex cModelIndex;

    m_pcStringListModel->insertRow(_Row);         //在尾部插入一空行

    cModelIndex = m_pcStringListModel->index(_Row, 0);

    m_pcStringListModel->setData(cModelIndex, "New item", Qt::DisplayRole);

    // ui->listView->setCurrentIndex(cModelIndex);
}
