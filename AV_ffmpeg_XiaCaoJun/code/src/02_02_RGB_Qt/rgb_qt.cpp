/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	rgb_qt.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.12
描  述: 编写使用RGB控制颜色显示的demo
备  注:
修改记录:

  1.  日期: 2025.03.12
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <qimage.h>
#include <qpainter.h>

#include "rgb_qt.h"

RGB_Qt::RGB_Qt(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    resize(m_nWidth, m_nHeight);
}

RGB_Qt::~RGB_Qt()
{}

void RGB_Qt::paintEvent(QPaintEvent * e)
{
	QImage cImage(m_nWidth, m_nHeight, QImage::Format_RGB888);
	QPainter cPainter;
	auto puchDisplay = cImage.bits();
	qint32 nPixelsNum = 0;								//像素点数量
	quint8 uchRed = 255;			

	for (qint32 i = 0; i < m_nHeight; i++)
	{
		nPixelsNum = i * m_nWidth * 3;

		for (qint32 j = 0; j < m_nWidth * 3; j+=3)
		{
			puchDisplay[nPixelsNum + j] = uchRed;		//R
			puchDisplay[nPixelsNum + j + 1] = 0;		//G
			puchDisplay[nPixelsNum + j + 2] = 0;		//B
		}

		uchRed--;
	}

	cPainter.begin(this);

	cPainter.drawImage(0, 0, cImage);

	cPainter.end();
}
