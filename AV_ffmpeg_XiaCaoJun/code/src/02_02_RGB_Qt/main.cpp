/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.cpp
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

#include "rgb_qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RGB_Qt w;
    w.show();
    return a.exec();
}
