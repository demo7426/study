/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.03.14
��  ��: �������ļ�
��  ע:
�޸ļ�¼:

  1.  ����: 2025.03.14
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

*************************************************/

#include "sdl_qt_rgb.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SDL_Qt_RGB w;
    w.show();
    return a.exec();
}
