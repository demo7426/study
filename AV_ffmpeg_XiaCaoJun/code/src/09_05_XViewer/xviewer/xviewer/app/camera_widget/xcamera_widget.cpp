/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xcamera_widget.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.30
描  述: 自定义相机渲染的widget界面
备  注:
修改记录:

  1.  日期: 2025.12.30
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <QStyleOption>
#include <QPainter>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QListWidget>
#include <QDir>

#include "xcamera_widget.h"
#include "ui_xcamera_widget.h"
#include "xcamera_config.h"
#include "debug.h"

CXCamera_Widget::CXCamera_Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CXCamera_Widget)
{
    ui->setupUi(this);

	this->setAcceptDrops(true);
}

CXCamera_Widget::~CXCamera_Widget()
{
	m_cVideo_Capture.StopThread();

    delete ui;
}

void CXCamera_Widget::paintEvent(QPaintEvent* e)
{
	//从父类继承其qss style信息
	QStyleOption cOpt;
	QPainter cPainter(this);

	cOpt.initFrom(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &cOpt, &cPainter, this);
}

void CXCamera_Widget::dragEnterEvent(QDragEnterEvent* event)
{
	//接收拖拽进入
	event->acceptProposedAction();
}

void CXCamera_Widget::dropEvent(QDropEvent* event)
{
	auto pcListWidget = dynamic_cast<QListWidget*>(event->source());
	qint32 nCurIndex = pcListWidget->currentRow();
	CXCamera_Config::CAMERA_CONFIG_INFO tCameraConfigInfo = { 0 };
	QDir cDir;

	if (nCurIndex >= CXCamera_Config::GetInstance()->GetCount())
	{
		DEBUG(DEBUG_LEVEL_WARN, "当前索引超出相机配置文件信息范围");
		return;
	}

	tCameraConfigInfo = CXCamera_Config::GetInstance()->Get(nCurIndex);

	cDir.mkpath(tCameraConfigInfo.SaveDir);

	m_cVideo_Capture.StartThread(tCameraConfigInfo.Url, tCameraConfigInfo.SaveDir, true, reinterpret_cast<void*>(this->winId()));
}
