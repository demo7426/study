/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	rgb_qt.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.03.12
��  ��: ��дʹ��RGB������ɫ��ʾ��demo
��  ע:
�޸ļ�¼:

  1.  ����: 2025.03.12
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

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
	qint32 nPixelsNum = 0;								//���ص�����
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
