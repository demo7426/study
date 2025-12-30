/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xviewer.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.22
描  述: 实现相机主界面的交互
备  注:
修改记录:

  1.  日期: 2025.12.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <QMouseEvent>
#include <qgridlayout.h>
#include <qdialog.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qmessagebox.h>

#include "xviewer.h"
#include "xcamera_config.h"
#include "xcamera_widget.h"

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

    this->ReloadCameraConfigInfo(m_pchCameraConfigPaths);

    ui.pushBtnModify->setEnabled(false);
    ui.pushBtnDel->setEnabled(false);

    m_cLabel.setText("未录制");
    ui.statusBar->addWidget(&m_cLabel, 0);

    ui.listWidgetCamera->setDragEnabled(true);      //使能相机列表的拖拽功能
}

void CXViewer::InitSignalSlots(void)
{
    QMenu* pcViewMenu = nullptr;
    QAction* pcStartRecordAct = nullptr;
    QAction* pcStopRecordAct = nullptr;
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

    pcStartRecordAct = m_cRightMenu.addAction("全部开始录制");
    pcStopRecordAct = m_cRightMenu.addAction("全部停止录制");

    connect(pcStartRecordAct, &QAction::triggered, this, [=]() {
        m_cLabel.setText("全部开始录制");
        });

    connect(pcStopRecordAct, &QAction::triggered, this, [=]() {
        m_cLabel.setText("全部停止录制");
        });

    connect(ui.pushBtnAdd, &QPushButton::clicked, this, &CXViewer::AddCameraConfig);
    connect(ui.pushBtnModify, &QPushButton::clicked, this, &CXViewer::ModifyCameraConfig);
    connect(ui.pushBtnDel, &QPushButton::clicked, this, &CXViewer::DelCameraConfig);

    connect(ui.listWidgetCamera, &QListWidget::currentRowChanged, this, [=](int currentRow) {
        if (currentRow < 0)
        {
            ui.pushBtnModify->setEnabled(false);
            ui.pushBtnDel->setEnabled(false);

            return;
        }

        ui.pushBtnModify->setEnabled(true);
        ui.pushBtnDel->setEnabled(true);
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
            m_pcVecWidget_GridLayout.push_back(new CXCamera_Widget());
            m_cGridLayout.addWidget(m_pcVecWidget_GridLayout.back(), i, j);
        }
    }
#endif
}

int CXViewer::ReloadCameraConfigInfo(QString _FilePath)
{
    CXCamera_Config::GetInstance()->LoadConfigFile(_FilePath.toStdString());

    ui.listWidgetCamera->clear();
    for (size_t i = 0; i < CXCamera_Config::GetInstance()->GetCount(); i++)
    {
        QListWidgetItem* pcListWidgetItem = new QListWidgetItem(
            QIcon(":/qss/image/Camera.png"),
            QString::fromLocal8Bit(CXCamera_Config::GetInstance()->Get(i).Name)
        );

        ui.listWidgetCamera->addItem(pcListWidgetItem);
    }

    return 0;
}

void CXViewer::AddCameraConfig(void)
{
    QDialog cDlg;
    QFormLayout cFormLayout;

    CXCamera_Config::CAMERA_CONFIG_INFO tCamera_Config_Info = { 0 };

    QLineEdit cLineEdit_Name;
    cFormLayout.addRow("名称", &cLineEdit_Name);

    QLineEdit cLineEdit_Url;
    cFormLayout.addRow("主码流", &cLineEdit_Url);
    
    QLineEdit cLineEdit_SubUrl;
    cFormLayout.addRow("辅码流", &cLineEdit_SubUrl);
    
    QLineEdit cLineEdit_SaveDir;
    cFormLayout.addRow("保存目录", &cLineEdit_SaveDir);
    
    QPushButton cPushBtn_Save;      //保存按钮
    cPushBtn_Save.setText("保存配置");
    cFormLayout.addRow("", &cPushBtn_Save);

    cDlg.setLayout(&cFormLayout);

    connect(&cPushBtn_Save, &QPushButton::clicked, &cDlg, &QDialog::accept);

    cDlg.setMinimumWidth(400);
    while (1)
    {
        if (cDlg.exec() != QDialog::Accepted)   //其它操作，直接退出
        {
            break;
        }

        //确定保存配置信息
        if (cLineEdit_Name.text().isEmpty())
        {
            QMessageBox::warning(this, "警告窗口", "请设置相机名称");
            continue;
        }

        if (cLineEdit_Url.text().isEmpty())
        {
            QMessageBox::warning(this, "警告窗口", "请设置相机主码流");
            continue;
        }

        if (cLineEdit_SubUrl.text().isEmpty())
        {
            QMessageBox::warning(this, "警告窗口", "请设置相机辅码流");
            continue;
        }

        if (cLineEdit_SaveDir.text().isEmpty())
        {
            QMessageBox::warning(this, "警告窗口", "请设置相机保存目录");
            continue;
        }

        if (cLineEdit_Name.text().size() > sizeof tCamera_Config_Info.Name)
        {
            QMessageBox::warning(this, "警告窗口", "相机名称过长");
            continue;
        }

        if (cLineEdit_Url.text().size() > sizeof tCamera_Config_Info.Url)
        {
            QMessageBox::warning(this, "警告窗口", "主码流名称过长");
            continue;
        }

        if (cLineEdit_SubUrl.text().size() > sizeof tCamera_Config_Info.SubUrl)
        {
            QMessageBox::warning(this, "警告窗口", "辅码流名称过长");
            continue;
        }

        if (cLineEdit_SaveDir.text().size() > sizeof tCamera_Config_Info.SaveDir)
        {
            QMessageBox::warning(this, "警告窗口", "相机保存目录过长");
            continue;
        }

        strcpy_s(tCamera_Config_Info.Name, sizeof tCamera_Config_Info.Name, cLineEdit_Name.text().toStdString().c_str());
        strcpy_s(tCamera_Config_Info.Url, sizeof tCamera_Config_Info.Url, cLineEdit_Url.text().toStdString().c_str());
        strcpy_s(tCamera_Config_Info.SubUrl, sizeof tCamera_Config_Info.SubUrl, cLineEdit_SubUrl.text().toStdString().c_str());
        strcpy_s(tCamera_Config_Info.SaveDir, sizeof tCamera_Config_Info.SaveDir, cLineEdit_SaveDir.text().toStdString().c_str());

        CXCamera_Config::GetInstance()->Add(tCamera_Config_Info);
        CXCamera_Config::GetInstance()->SaveConfigFile(m_pchCameraConfigPaths);
        
        this->ReloadCameraConfigInfo(m_pchCameraConfigPaths);

        break;
    }

    disconnect(&cPushBtn_Save, &QPushButton::clicked, &cDlg, &QDialog::accept);
}

void CXViewer::ModifyCameraConfig(void)
{
    QDialog cDlg;
    QFormLayout cFormLayout;

    CXCamera_Config::CAMERA_CONFIG_INFO tCamera_Config_Info = { 0 };
    qint32 nCurIndex = ui.listWidgetCamera->currentRow();

    if (nCurIndex >= CXCamera_Config::GetInstance()->GetCount())
    {
        QMessageBox::warning(this, "警告窗口", "请先选择待修改的相机");
        return;
    }

    tCamera_Config_Info = CXCamera_Config::GetInstance()->Get(nCurIndex);

    QLineEdit cLineEdit_Name;
    cLineEdit_Name.setText(tCamera_Config_Info.Name);
    cFormLayout.addRow("名称", &cLineEdit_Name);

    QLineEdit cLineEdit_Url;
    cLineEdit_Url.setText(tCamera_Config_Info.Url);
    cFormLayout.addRow("主码流", &cLineEdit_Url);

    QLineEdit cLineEdit_SubUrl;
    cLineEdit_SubUrl.setText(tCamera_Config_Info.SubUrl);
    cFormLayout.addRow("辅码流", &cLineEdit_SubUrl);

    QLineEdit cLineEdit_SaveDir;
    cLineEdit_SaveDir.setText(tCamera_Config_Info.SaveDir);
    cFormLayout.addRow("保存目录", &cLineEdit_SaveDir);

    QPushButton cPushBtn_Save;      //保存按钮
    cPushBtn_Save.setText("保存配置");
    cFormLayout.addRow("", &cPushBtn_Save);

    cDlg.setLayout(&cFormLayout);

    connect(&cPushBtn_Save, &QPushButton::clicked, &cDlg, &QDialog::accept);

    cDlg.setMinimumWidth(400);
    while (1)
    {
        if (cDlg.exec() != QDialog::Accepted)   //其它操作，直接退出
        {
            break;
        }

        //确定保存配置信息
        if (cLineEdit_Name.text().isEmpty())
        {
            QMessageBox::warning(this, "警告窗口", "请设置相机名称");
            continue;
        }

        if (cLineEdit_Url.text().isEmpty())
        {
            QMessageBox::warning(this, "警告窗口", "请设置相机主码流");
            continue;
        }

        if (cLineEdit_SubUrl.text().isEmpty())
        {
            QMessageBox::warning(this, "警告窗口", "请设置相机辅码流");
            continue;
        }

        if (cLineEdit_SaveDir.text().isEmpty())
        {
            QMessageBox::warning(this, "警告窗口", "请设置相机保存目录");
            continue;
        }

        if (cLineEdit_Name.text().size() > sizeof tCamera_Config_Info.Name)
        {
            QMessageBox::warning(this, "警告窗口", "相机名称过长");
            continue;
        }

        if (cLineEdit_Url.text().size() > sizeof tCamera_Config_Info.Url)
        {
            QMessageBox::warning(this, "警告窗口", "主码流名称过长");
            continue;
        }

        if (cLineEdit_SubUrl.text().size() > sizeof tCamera_Config_Info.SubUrl)
        {
            QMessageBox::warning(this, "警告窗口", "辅码流名称过长");
            continue;
        }

        if (cLineEdit_SaveDir.text().size() > sizeof tCamera_Config_Info.SaveDir)
        {
            QMessageBox::warning(this, "警告窗口", "相机保存目录过长");
            continue;
        }

        strcpy_s(tCamera_Config_Info.Name, sizeof tCamera_Config_Info.Name, cLineEdit_Name.text().toStdString().c_str());
        strcpy_s(tCamera_Config_Info.Url, sizeof tCamera_Config_Info.Url, cLineEdit_Url.text().toStdString().c_str());
        strcpy_s(tCamera_Config_Info.SubUrl, sizeof tCamera_Config_Info.SubUrl, cLineEdit_SubUrl.text().toStdString().c_str());
        strcpy_s(tCamera_Config_Info.SaveDir, sizeof tCamera_Config_Info.SaveDir, cLineEdit_SaveDir.text().toStdString().c_str());

        CXCamera_Config::GetInstance()->Modify(nCurIndex, tCamera_Config_Info);
        CXCamera_Config::GetInstance()->SaveConfigFile(m_pchCameraConfigPaths);

        this->ReloadCameraConfigInfo(m_pchCameraConfigPaths);

        break;
    }

    disconnect(&cPushBtn_Save, &QPushButton::clicked, &cDlg, &QDialog::accept);
}

void CXViewer::DelCameraConfig(void)
{
    qint32 nCurIndex = ui.listWidgetCamera->currentRow();

    if (nCurIndex >= CXCamera_Config::GetInstance()->GetCount())
    {
        QMessageBox::warning(this, "警告窗口", "请先选择待删除的相机");
        return;
    }

    CXCamera_Config::GetInstance()->Delete(nCurIndex);
    CXCamera_Config::GetInstance()->SaveConfigFile(m_pchCameraConfigPaths);

    this->ReloadCameraConfigInfo(m_pchCameraConfigPaths);
}
