/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.27
描  述: YUV格式文件和RGBA格式文件相互转换
备  注: 终端使用 ffmpeg -i lu_fei.mp4 -s 400x300 le_fei_400_300_30.yuv 命令可进行数据转换
修改记录:

  1.  日期: 2025.03.27
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <fstream>
#include <istream>

using namespace std;

extern "C" {
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swscale.lib")

//将YUV格式的视频转换为RGBA格式
static int YUV_To_RGBA(const char* _SrcFilePath, int _SrcWidth, int _SrcHeight, const char* _DstFilePath, int _DstWidth, int _DstHeight)
{
	SwsContext* ptSwsContext_YUVToRGBA = nullptr;

	uint8_t* puchSrcSlice_YUV[3] = { new uint8_t[_SrcWidth * _SrcHeight], new uint8_t[_SrcWidth * _SrcHeight / 4], new uint8_t[_SrcWidth * _SrcHeight / 4] };
	int nSrcLineSize[3] = { _SrcWidth , _SrcWidth / 2, _SrcWidth / 2 };
	uint8_t* puchSrcSlice_RGBA[1] = { new uint8_t[_DstWidth * _DstHeight * 4] };
	int nDstLineSize[1] = { _DstWidth * 4 };

	int nOutputSlice_H = 0;			//输出片的高度

	ifstream cIfstream;				//输入文件
	cIfstream.open(_SrcFilePath, ios::binary);
	if (!cIfstream.is_open())
	{
		delete[] puchSrcSlice_YUV[0];
		delete[] puchSrcSlice_YUV[1];
		delete[] puchSrcSlice_YUV[2];

		delete[] puchSrcSlice_RGBA[0];

		cerr << "cFStream open is failed" << endl;
		return -2;
	}

	ofstream cOfstream;				//输出文件
	cOfstream.open(_DstFilePath, ios::binary);
	if (!cOfstream.is_open())
	{
		delete[] puchSrcSlice_YUV[0];
		delete[] puchSrcSlice_YUV[1];
		delete[] puchSrcSlice_YUV[2];

		delete[] puchSrcSlice_RGBA[0];

		cIfstream.close();

		cerr << "cFStream open is failed" << endl;
		return -2;
	}

	ptSwsContext_YUVToRGBA = sws_getCachedContext(ptSwsContext_YUVToRGBA,
		_SrcWidth, _SrcHeight, AV_PIX_FMT_YUV420P,
		_DstWidth, _DstHeight, AV_PIX_FMT_RGBA,
		SWS_BILINEAR,	//选择支持变化的算法，双线性插值
		0, 0, 0			//过滤器参数
	);
	if (!ptSwsContext_YUVToRGBA)
	{
		delete[] puchSrcSlice_YUV[0];
		delete[] puchSrcSlice_YUV[1];
		delete[] puchSrcSlice_YUV[2];

		delete[] puchSrcSlice_RGBA[0];

		cIfstream.close();
		cOfstream.close();

		cerr << "sws_getCachedContext is failed" << endl;
		return -2;
	}

	//视频原始数据YUV_To_RGBA转换
	while (true)
	{
		if (cIfstream.peek() == EOF)	//判断是否读取到文件的尾部
			break;

		cIfstream.read((char*)puchSrcSlice_YUV[0], _SrcWidth * _SrcHeight);
		cIfstream.read((char*)puchSrcSlice_YUV[1], _SrcWidth * _SrcHeight / 4);
		cIfstream.read((char*)puchSrcSlice_YUV[2], _SrcWidth * _SrcHeight / 4);

		nOutputSlice_H = sws_scale(ptSwsContext_YUVToRGBA,
			puchSrcSlice_YUV,
			nSrcLineSize,
			0,				//用于多层图像，当前输入0忽略
			_SrcHeight,
			puchSrcSlice_RGBA,
			nDstLineSize
		);

		cOfstream.write((char*)puchSrcSlice_RGBA[0], _DstWidth * _DstHeight * 4);
		cout << "YUV_To_RGBA: nOutputSlice_H = " << nOutputSlice_H << endl;
	}

	delete[] puchSrcSlice_YUV[0];
	delete[] puchSrcSlice_YUV[1];
	delete[] puchSrcSlice_YUV[2];

	delete[] puchSrcSlice_RGBA[0];

	cIfstream.close();
	cOfstream.close();

	return 0;
}


//将RGBA格式的视频转换为YUV格式
static int RGBA_To_YUV(const char* _SrcFilePath, int _SrcWidth, int _SrcHeight, const char* _DstFilePath, int _DstWidth, int _DstHeight)
{
	SwsContext* ptSwsContext_RGBAToYUV = nullptr;

	uint8_t* puchSrcSlice_RGBA[1] = { new uint8_t[_SrcWidth * _SrcHeight * 4] };
	int nSrcLineSize[1] = { _SrcWidth * 4 };
	uint8_t* puchDstSlice_YUV[3] = { new uint8_t[_DstWidth * _DstHeight], new uint8_t[_DstWidth * _DstHeight / 4], new uint8_t[_DstWidth * _DstHeight / 4] };
	int nDstLineSize[3] = { _DstWidth , _DstWidth / 2, _DstWidth / 2 };

	int nOutputSlice_H = 0;			//输出片的高度

	ifstream cIfstream;				//输入文件
	cIfstream.open(_SrcFilePath, ios::binary);
	if (!cIfstream.is_open())
	{
		delete[] puchDstSlice_YUV[0];
		delete[] puchDstSlice_YUV[1];
		delete[] puchDstSlice_YUV[2];

		delete[] puchSrcSlice_RGBA[0];

		cerr << "cFStream open is failed" << endl;
		return -2;
	}

	ofstream cOfstream;				//输出文件
	cOfstream.open(_DstFilePath, ios::binary);
	if (!cOfstream.is_open())
	{
		delete[] puchDstSlice_YUV[0];
		delete[] puchDstSlice_YUV[1];
		delete[] puchDstSlice_YUV[2];

		delete[] puchSrcSlice_RGBA[0];

		cIfstream.close();

		cerr << "cFStream open is failed" << endl;
		return -2;
	}

	ptSwsContext_RGBAToYUV = sws_getCachedContext(ptSwsContext_RGBAToYUV,
		_SrcWidth, _SrcHeight, AV_PIX_FMT_RGBA,
		_DstWidth, _DstHeight, AV_PIX_FMT_YUV420P,
		SWS_BILINEAR,	//选择支持变化的算法，双线性插值
		0, 0, 0			//过滤器参数
	);
	if (!ptSwsContext_RGBAToYUV)
	{
		delete[] puchDstSlice_YUV[0];
		delete[] puchDstSlice_YUV[1];
		delete[] puchDstSlice_YUV[2];

		delete[] puchSrcSlice_RGBA[0];

		cIfstream.close();
		cOfstream.close();

		cerr << "sws_getCachedContext is failed" << endl;
		return -2;
	}

	//视频原始数据YUV_To_RGBA转换
	while (true)
	{
		if (cIfstream.peek() == EOF)	//判断是否读取到文件的尾部
			break;

		cIfstream.read((char*)puchSrcSlice_RGBA[0], _SrcWidth * _SrcHeight * 4);

		nOutputSlice_H = sws_scale(ptSwsContext_RGBAToYUV,
			puchSrcSlice_RGBA,
			nSrcLineSize,
			0,				//用于多层图像，当前输入0忽略
			_SrcHeight,
			puchDstSlice_YUV,
			nDstLineSize
		);

		cOfstream.write((char*)puchDstSlice_YUV[0], _DstWidth * _DstHeight);
		cOfstream.write((char*)puchDstSlice_YUV[1], _DstWidth * _DstHeight / 4);
		cOfstream.write((char*)puchDstSlice_YUV[2], _DstWidth * _DstHeight / 4);

		cout << "RGBA_To_YUV: nOutputSlice_H = " << nOutputSlice_H << endl;
	}

	delete[] puchDstSlice_YUV[0];
	delete[] puchDstSlice_YUV[1];
	delete[] puchDstSlice_YUV[2];

	delete[] puchSrcSlice_RGBA[0];

	cIfstream.close();
	cOfstream.close();

	return 0;
}

int main()
{
	//cout << "first_ffmpeg:" << endl;
	//cout << avcodec_configuration() << endl;

	static_assert(sizeof(void*) == 4, "必须使用x86进行编译");

	YUV_To_RGBA("le_fei_400_300_30.yuv", 400, 300, "le_fei_800_600_30.rgba", 800, 600);
	RGBA_To_YUV("le_fei_800_600_30.rgba", 800, 600, "le_fei_400_300_30_01.yuv", 400, 300);

	return 0;
}
