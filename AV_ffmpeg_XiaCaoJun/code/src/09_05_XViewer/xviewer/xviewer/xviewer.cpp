
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
    
    this->ShowViews(9);     //默认为9路数据

    ui.widget->setLayout(&m_cGridLayout);

    CXCamera_Config::GetInstance()->LoadConfigFile(m_pchCameraConfigPaths);
    
    ui.listWidgetCamera->clear();
    for (size_t i = 0; i < CXCamera_Config::GetInstance()->GetCount(); i++)
    {
        QListWidgetItem* pcListWidgetItem = new QListWidgetItem(
            QIcon(":/qss/image/Camera.png"),
            QString::fromLocal8Bit(CXCamera_Config::GetInstance()->Get(i).Name)
        );

        ui.listWidgetCamera->addItem(pcListWidgetItem);
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

    connect(ui.pushBtnAdd, &QPushButton::clicked, this, [=]() {
        //CXCamera_Config::GetInstance()->SaveConfigFile("./test.txt");
        });
}

void CXViewer::ShowViews(qint32 _ViewCount)
{
#if 0
    // 1. 计算目标行列数（向上取整，确保行列数的平方 ≥ _ViewCount，比如 5 → 3x3）
    qint32 targetRow = qCeil(qSqrt(_ViewCount));
    qint32 targetCol = targetRow;
    qint32 targetWidgetCount = targetRow * targetCol; // 目标窗口总数

    // 2. 先移除布局中所有widget（但不删除，只是解除布局关联）
    QLayoutItem* layoutItem = nullptr;
    while ((layoutItem = m_cGridLayout.takeAt(0)) != nullptr) {
        // 解除布局和widget的关联，保留widget实例
        if (layoutItem->widget()) {
            layoutItem->widget()->setParent(nullptr); // 临时脱离父控件
        }
        delete layoutItem; // 释放布局项（不是widget）
    }

    // 3. 处理窗口数量：保留原有，只新增/删除超出的
    qint32 currentWidgetCount = m_pcVecWidget_GridLayout.size();

    // 情况1：目标数量 > 现有数量 → 新增缺少的窗口
    if (targetWidgetCount > currentWidgetCount) {
        for (int i = currentWidgetCount; i < targetWidgetCount; i++) {
            m_pcVecWidget_GridLayout.push_back(new QWidget());
        }
    }
    // 情况2：目标数量 < 现有数量 → 删除超出的窗口
    else if (targetWidgetCount < currentWidgetCount) {
        for (int i = currentWidgetCount - 1; i >= targetWidgetCount; i--) {
            QWidget* widget = m_pcVecWidget_GridLayout.at(i);
            if (widget) {
                delete widget; // 删除超出的窗口
                widget = nullptr;
            }
            m_pcVecWidget_GridLayout.pop_back(); // 从列表中移除
        }
    }
    // 情况3：数量相等 → 不处理

    // 4. 重新将保留的widget添加到网格布局中（按行列重新排列）
    int widgetIndex = 0;
    for (int i = 0; i < targetRow; i++) {
        for (int j = 0; j < targetCol; j++) {
            if (widgetIndex < m_pcVecWidget_GridLayout.size()) {
                QWidget* widget = m_pcVecWidget_GridLayout[widgetIndex];
                if (widget) {
                    m_cGridLayout.addWidget(widget, i, j); // 重新添加到布局
                    widget->show(); // 确保显示
                }
                widgetIndex++;
            }
        }
    }

    // 可选：调整布局间距，让窗口均匀分布
    m_cGridLayout.setSpacing(2);
    m_cGridLayout.setContentsMargins(0, 0, 0, 0);
#else
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
#endif
}
