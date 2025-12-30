/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xviewer.h
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

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_xviewer.h"
#include <qlabel.h>

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

    QLabel m_cLabel;

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

    /// <summary>
    /// 重新加载相机的配置文件信息
    /// </summary>
    /// <param name="_FilePath">文件路径</param>
    /// <returns></returns>
    int ReloadCameraConfigInfo(QString _FilePath);

    /// <summary>
    /// 新增相机配置
    /// </summary>
    /// <param name=""></param>
    void AddCameraConfig(void);

    /// <summary>
    /// 修改相机配置
    /// </summary>
    /// <param name=""></param>
    void ModifyCameraConfig(void);
    
    /// <summary>
    /// 删除相机配置
    /// </summary>
    /// <param name=""></param>
    void DelCameraConfig(void);
};

