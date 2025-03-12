/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
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

#include "rgb_qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RGB_Qt w;
    w.show();
    return a.exec();
}
