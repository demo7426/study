#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_xviewer.h"

class CXViewer : public QMainWindow
{
    Q_OBJECT

public:
    CXViewer(QWidget *parent = nullptr);
    ~CXViewer();

private:
    Ui::CXViewerClass ui;

    QPoint m_cPointDiffValue;           //光标当前位置和当前窗口左上顶点坐标之间的差值
    bool m_bIsMoving = false;           //是否可以移动;true--可以移动;false--不可移动

    QMenu m_cRightMenu;                 //右键菜单栏

    QVector<QWidget*> m_pcVecWidget_GridLayout;

    QGridLayout m_cGridLayout;

    const char* m_pchCameraConfigPaths = "xv_camera_config.json";   //相机默认配置文件路径

protected:
    void mouseMoveEvent(QMouseEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    /// <summary>
    /// 初始化
    /// </summary>
    /// <param name=""></param>
    void Init(void);

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    /// <param name=""></param>
    void InitSignalSlots(void);

    /// <summary>
    /// 显示指定数量的窗口
    /// </summary>
    /// <param name="_ViewCount">窗口数量</param>
    void ShowViews(qint32 _ViewCount);
};

