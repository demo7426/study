/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.01.09
描  述: 实现对自定义封装后，音频类接口的测试
备  注: ffmpeg -i 1.mp4 -f s16le -ar 44100 test.pcm
修改记录:

  1.  日期: 2026.01.09
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <fstream>

#include "xaudio_play.h"

int main()
{
	char chReadBuf[4096];
	CXAudioPlay::AUDIO_SPEC_INFO tAudio_Spec_Info;

	tAudio_Spec_Info.freq = 44100; 
	tAudio_Spec_Info.format = AUDIO_S16LSB;
	tAudio_Spec_Info.silence = 0;
	tAudio_Spec_Info.channels = 2;
	tAudio_Spec_Info.samples = 1024;

	CXAudioPlay::GetInstance()->Open(tAudio_Spec_Info);

	std::ifstream ifs("test.pcm", std::ios::binary);
	if (!ifs.is_open())
	{
		std::cout << "File open is failed" << std::endl;
		return EXIT_FAILURE;
	}

	while (1)
	{
		ifs.read(chReadBuf, sizeof chReadBuf);

		CXAudioPlay::GetInstance()->Push((uint8_t*)chReadBuf, ifs.gcount());

		if (ifs.eof())
		{
			ifs.close();
			break;
		}
	}

	std::cout << "Please input char" << std::endl;
	getchar();
	CXAudioPlay::GetInstance()->SetPalyVolume(32);

	std::cout << "Please input char" << std::endl;
	getchar();
	CXAudioPlay::GetInstance()->SetPalyVolume(128);

	std::cout << "Please input char" << std::endl;
	getchar();
	CXAudioPlay::GetInstance()->SetPalyRate(2.0);
	
	getchar();
	CXAudioPlay::GetInstance()->Close();

	return EXIT_SUCCESS;
}



