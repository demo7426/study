/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.11
描  述: 编写第一个ffmpeg程序
备  注:
修改记录:

  1.  日期: 2025.03.11
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

using namespace std;

extern "C" {
#include <libavcodec/avcodec.h>
}

#pragma comment(lib, "avcodec.lib")

int main()
{
	cout << "first_ffmpeg:" << endl;
	cout << avcodec_configuration() << endl;

	return 0;
}
