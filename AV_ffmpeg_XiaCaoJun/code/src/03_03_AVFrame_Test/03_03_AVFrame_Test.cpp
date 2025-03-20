/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	03_03_AVFrame_Test.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.20
描  述: 测试av_frame的一些基础接口
备  注:
修改记录:

  1.  日期: 2025.03.20
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
#pragma comment(lib, "avutil.lib")

static void Test01()
{
	cout << "first_ffmpeg:" << endl;
	cout << avcodec_configuration() << endl;
}

static void Test02()
{
	int nRet = 0;
	char chBuf[1024] = { 0 };
	AVFrame* ptAVFrame_Src = av_frame_alloc();
	AVFrame* ptAVFrame_Des = av_frame_alloc();

	ptAVFrame_Src->width = 401;
	ptAVFrame_Src->height = 300;
	ptAVFrame_Src->format = AV_PIX_FMT_ARGB;

	//分配空间
	nRet = av_frame_get_buffer(ptAVFrame_Src,
		16										//如果为0，则使用默认的32字节对齐
	);
	if (nRet)
	{
		av_strerror(nRet, chBuf, sizeof(chBuf));
		cout << chBuf << endl;
	}

	if (ptAVFrame_Src->buf[0])
	{
		cout << "ptAVFrame_Src: ref_count = " << av_buffer_get_ref_count(ptAVFrame_Src->buf[0]) << endl;
	}

	cout << "linesize[0] = " << ptAVFrame_Src->linesize[0] << endl;		//打印一行数据字节大小

	av_frame_ref(ptAVFrame_Des, ptAVFrame_Src);							//使ptAVFrame_Des的buf[0]与ptAVFrame_Src一致，他们都指向同一个bug[0]

	cout << "ptAVFrame_Src: ref_count = " << av_buffer_get_ref_count(ptAVFrame_Src->buf[0]) << endl;
	cout << "ptAVFrame_Des: ref_count = " << av_buffer_get_ref_count(ptAVFrame_Des->buf[0]) << endl;

	av_frame_unref(ptAVFrame_Src);										//释放对buf[0]字段的引用计数

	cout << "ptAVFrame_Des: ref_count = " << av_buffer_get_ref_count(ptAVFrame_Des->buf[0]) << endl;

	av_frame_free(&ptAVFrame_Src);
	av_frame_free(&ptAVFrame_Des);
}

int main()
{
	Test01();
	
	cout << endl;

	Test02();

	return 0;
}
