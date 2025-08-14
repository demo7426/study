/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.08.14
��  ��: ʵ�ֶԱ���ffmpeg���̵ķ�װs
��  ע:
�޸ļ�¼:

  1.  ����: 2025.08.14
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#pragma once

#include <fstream>
#include <thread>
#include <mutex>

struct AVCodecContext;
struct AVFrame;
struct AVPacket;

class CXEncode
{
public:
	CXEncode();
	~CXEncode();

	/// <summary>
	/// ����������������
	/// </summary>
	/// <param name="_AVCodecID">���ݱ����ĸ�ʽ</param>
	/// <param name="_Output_FilePath">������ļ�·��</param>
	/// <returns>nullptr--ʧ��;!nullptr--�ɹ�</returns>
	int Create_AVCodecContext(int _AVCodecID, std::string _Output_FilePath);

	/// <summary>
	/// ���ñ����������Ĳ���
	/// </summary>
	/// <param name="_Width"></param>
	/// <param name="_Height"></param>
	/// <param name="_FrameRate"></param>
	/// <param name="_AVPixelFormat"></param>
	/// <param name="_ThreadCount"></param>
	AVFrame* Set_AVCodecContext_Param(int _Width, int _Height, int _FrameRate, int _AVPixelFormat, int _ThreadCount = std::thread::hardware_concurrency());

	/// <summary>
	/// Ԥ�����������
	/// </summary>
	/// <param name="_Name"></param>
	/// <param name="_Value"></param>
	/// <returns></returns>
	int AV_Opt_Set(std::string _Name, std::string _Value);

	/// <summary>
	/// Ԥ�����������
	/// </summary>
	/// <param name="_Name"></param>
	/// <param name="_Value"></param>
	/// <returns></returns>
	int AV_Opt_Set_Int(std::string _Name, int _Value);

	/// <summary>
	/// ��ʼ��������������������ģ�AVCodecContext�����������Ӧ�ı��������AVCodec����
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	int Open(void);

	/// <summary>
	/// ����ԭʼ��AVFrame����
	/// </summary>
	/// <param name="_pAVFrame"></param>
	/// <returns></returns>
	int SendFrame(AVFrame* _pAVFrame);

private:
	AVCodecContext* m_ptAVCodecContext = nullptr;				//������������
	AVFrame* m_ptAVFrame = nullptr;
	AVPacket* m_ptAVPacket = nullptr;

	std::ofstream m_ofs;

	std::mutex m_mut;

	int m_nFrameNum = 0;

	/// <summary>
	/// ����������AVFrame��AVPacket
	/// </summary>
	/// <param name="_Width"></param>
	/// <param name="_Height"></param>
	/// <param name="_AVPixelFormat"></param>
	/// <returns></returns>
	AVFrame* Create_AVFrameAndAVPacket(int _Width, int _Height, int _AVPixelFormat);
};


