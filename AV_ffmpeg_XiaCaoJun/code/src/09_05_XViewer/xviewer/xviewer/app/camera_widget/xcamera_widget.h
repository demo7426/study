/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xcamera_widget.h
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

#ifndef XCAMERA_WIDGET_H
#define XCAMERA_WIDGET_H

#include <QWidget>

#include "video_capture.h"

namespace Ui {
class CXCamera_Widget;
}

class CXCamera_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit CXCamera_Widget(QWidget *parent = nullptr);
    ~CXCamera_Widget();

protected:
	void paintEvent(QPaintEvent* e) override;

	//拖拽进入
	void dragEnterEvent(QDragEnterEvent* event) override;

	//拖拽松开
	void dropEvent(QDropEvent* event) override;

private:
    Ui::CXCamera_Widget *ui;

	CVideo_Capture m_cVideo_Capture;
};

#endif // XCAMERA_WIDGET_H
