
#include <QMouseEvent>
#include <qgridlayout.h>

#include "xviewer.h"
#include "xcamera_config.h"

CXViewer::CXViewer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    Init();
    InitSignalSlots();
}

CXViewer::~CXViewer()
{}

void CXViewer::mouseMoveEvent(QMouseEvent * event)
{
    if (m_bIsMoving && (event->buttons() & Qt::LeftButton))
    {
        move(event->globalPosition().toPoint() - m_cPointDiffValue);
        m_cPointDiffValue = event->globalPosition().toPoint() - this->pos();
    }

    return QMainWindow::mouseMoveEvent(event);
}

void CXViewer::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_cPointDiffValue = event->globalPosition().toPoint() - this->pos();
        m_bIsMoving = true;
    }

    return QMainWindow::mousePressEvent(event);
}

void CXViewer::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        m_bIsMoving = false;

    return QMainWindow::mouseReleaseEvent(event);
}

void CXViewer::contextMenuEvent(QContextMenuEvent* event)
{
    m_cRightMenu.exec(QCursor::pos());
    event->accept();
}

void CXViewer::Init(void)
{
    this->setMinimumSize(800, 600);

    this->setWindowIcon(QIcon(":/qss/image/xvc.png"));
    this->setWindowTitle("安防软件");

    //this->setWindowFlags(Qt::SplashScreen);
    
    this->ShowViews(4);     //默认为4路数据

    ui.widget->setLayout(&m_cGridLayout);

    for (size_t i = 0; i < 10; i++)
    {
        AddCameraToListWidget();
    }
}

void CXViewer::InitSignalSlots(void)
{
    QMenu* pcViewMenu = nullptr;
    QAction* pcAct = nullptr;

    pcViewMenu = m_cRightMenu.addMenu("视图");

    pcAct = pcViewMenu->addAction("1窗口");
    connect(pcAct, &QAction::triggered, this, [=]() {
        ShowViews(1);
        });

    pcAct = pcViewMenu->addAction("4窗口");
    connect(pcAct, &QAction::triggered, this, [=]() {
        ShowViews(4);
        });

    pcAct = pcViewMenu->addAction("9窗口");
    connect(pcAct, &QAction::triggered, this, [=]() {
        ShowViews(9);
        });

    pcAct = pcViewMenu->addAction("16窗口");
    connect(pcAct, &QAction::triggered, this, [=]() {
        ShowViews(16);
        });

    pcAct = pcViewMenu->addAction("25窗口");
    connect(pcAct, &QAction::triggered, this, [=]() {
        ShowViews(25);
        });

    pcAct = pcViewMenu->addAction("36窗口");
    connect(pcAct, &QAction::triggered, this, [=]() {
        ShowViews(36);
        });

    pcAct = pcViewMenu->addAction("49窗口");
    connect(pcAct, &QAction::triggered, this, [=]() {
        ShowViews(49);
        });

    pcAct = pcViewMenu->addAction("64窗口");
    connect(pcAct, &QAction::triggered, this, [=]() {
        ShowViews(64);
        });
    
    pcAct = pcViewMenu->addAction("81窗口");
    connect(pcAct, &QAction::triggered, this, [=]() {
        ShowViews(81);
        });
    
    pcAct = pcViewMenu->addAction("100窗口");
    connect(pcAct, &QAction::triggered, this, [=]() {
        ShowViews(100);
        });

}

void CXViewer::ShowViews(qint32 _ViewCount)
{
    qint32 nRowCount = m_cGridLayout.rowCount();                //行数量
    qint32 nColumnCount = m_cGridLayout.columnCount();          //列数量

    //先清除所有的窗口
    for (size_t i = 0; i < m_pcVecWidget_GridLayout.size(); i++)
    {
        if (m_pcVecWidget_GridLayout.at(i))
        {
            delete m_pcVecWidget_GridLayout[i];
            m_pcVecWidget_GridLayout[i] = nullptr;
        }
    }

    m_pcVecWidget_GridLayout.clear();

    nRowCount = nColumnCount = qSqrt(_ViewCount);

    for (size_t i = 0; i < nRowCount; i++)
    {
        for (size_t j = 0; j < nColumnCount; j++)
        {
            m_pcVecWidget_GridLayout.push_back(new QWidget());
            m_cGridLayout.addWidget(m_pcVecWidget_GridLayout.back(), i, j);
        }
    }
     //m_cGridLayout.addWidget()

}

void CXViewer::AddCameraToListWidget(void)
{
    QListWidgetItem* pcListWidgetItem = new QListWidgetItem(QIcon(":/qss/image/Camera.png"), QString::asprintf("相机%d", ui.listWidgetCamera->count()));

    ui.listWidgetCamera->addItem(pcListWidgetItem);
}

