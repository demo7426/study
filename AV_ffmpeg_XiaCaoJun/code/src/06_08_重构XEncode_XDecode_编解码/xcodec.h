/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	xcodec.h
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

#pragma once

struct AVCodecContext;
struct AVFrame;
struct AVPacket;
struct AVCodecParserContext;

class CXCodec
{
public:
	CXCodec() = default;
	virtual ~CXCodec() = 0;

private:

};
