/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	xcodec.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.08.18
��  ��: �ࡢ�������ʵ��
��  ע:
�޸ļ�¼:

  1.  ����: 2025.08.18
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/
#include <iostream>
#include <thread>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/codec.h>
}

#include "xcodec.h"

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

CXCodec::~CXCodec()
{

}

void CXCodec::PrintErr(int _ErrCode)
{
	if (_ErrCode == 0)				//��ȷʱ������ӡ������Ϣ
		return;

	char chBuf[1024] = { 0 };

	av_strerror(_ErrCode, chBuf, sizeof(chBuf) - 1);

	std::cerr << chBuf << std::endl;
}
