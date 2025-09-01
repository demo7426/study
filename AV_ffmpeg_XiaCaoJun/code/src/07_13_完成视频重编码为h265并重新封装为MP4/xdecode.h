/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	xdecode.h
��  ��:	Ǯ��      �汾: V0.1.2     �½�����: 2025.08.19
��  ��: ʵ�ֶ�ffmpeg������̵ķ�װ
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.08.19
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

  2.  ����: 2025.08.26
	  ����: Ǯ��
	  ����:
		  1) ��չSend_AVPacket��Recv_AVFrame�ӿڣ�����MP4��ʽ��������ݵĽ���;
	  �汾:V0.1.1

  3.  ����: 2025.08.29
	  ����: Ǯ��
	  ����:
		  1) ��չSet_AVCodecParameters�ӿڣ��������ý������;
	  �汾:V0.1.2

*************************************************/

#pragma once

#include <string>
#include <vector>
#include <mutex>

#include "xcodec.h"

class CXDeCode: public CXCodec
{
public:
	CXDeCode();
	~CXDeCode();

	/// <summary>
	/// ����������������
	/// </summary>
	/// <param name="_AVCodecID">���ݱ����ĸ�ʽ</param>
	/// <param name="_IsEnable_HwDecode">�Ƿ�ʹ��Ӳ������;false--��ʹ��;true--ʹ��;</param>
	/// <returns>nullptr--ʧ��;!nullptr--�ɹ�</returns>
	int Create_AVCodecContext(int _AVCodecID, bool _IsEnable_HwDecode);

	/// <summary>
	/// ���ý������
	/// </summary>
	/// <param name="_pAVCodecParameters"></param>
	/// <returns></returns>
	int Set_AVCodecParameters(AVCodecParameters* _pAVCodecParameters);

	/// <summary>
	/// ��ʼ��������������������ģ�AVCodecContext�����������Ӧ�ı��������AVCodec����
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	int Open(void);

	/// <summary>
	/// ����ԭʼ��AVFrame����
	/// </summary>
	/// <param name="_pDataBuf">ԭʼ����</param>
	/// <param name="_Len">ԭʼ���ݳ���</param>
	/// <returns></returns>
	std::vector<AVFrame*> SendData(char* _pDataBuf, int _Len);

	/// <summary>
	/// ���ղ�������������
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	std::vector<AVFrame*> RecvAll_AVFrameData(void);

	/// <summary>
	/// ���ͱ��� Send_AVPacket--Recv_AVFrame����ʹ��
	/// </summary>
	/// <param name="_pAVPacket"></param>
	/// <returns></returns>
	bool Send_AVPacket(const AVPacket* _pAVPacket);

	/// <summary>
	/// ��ȡ���� Send_AVPacket--Recv_AVFrame����ʹ��
	/// </summary>
	/// <param name="_pAVFrame"></param>
	/// <returns></returns>
	bool Recv_AVFrame(AVFrame* _pAVFrame);

	inline AVCodecContext* GetAVCodecContext(void)
	{
		return m_ptAVCodecContext;
	}

private:
	AVCodecContext* m_ptAVCodecContext = nullptr;				//������������
	AVPacket* m_ptAVPacket = nullptr;


	AVCodecParserContext* m_ptAVCodecParserContext = nullptr;

	std::mutex m_mut;

	int m_nFrameNum = 0;

	bool m_bInitFlag = false;
};

