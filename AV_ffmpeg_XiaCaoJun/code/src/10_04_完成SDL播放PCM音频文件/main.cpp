/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.01.08
描  述: 播放PCM音频文件
备  注: ffmpeg -i 1.mp4 -f s16le -ar 44100 test.pcm
修改记录:

  1.  日期: 2026.01.08
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <fstream>

#include "sdl/SDL.h"

#undef main

#pragma comment(lib, "SDL2.lib")

void MyAudioCallback(void* userdata, Uint8* stream, int len)
{
	std::ifstream* pcIfs = (std::ifstream*)userdata;

	SDL_memset(stream, 0, len);
	
	if (pcIfs->is_open())
		pcIfs->read((char*)stream, len);

	if (pcIfs->eof())
	{
		pcIfs->close();

		SDL_PauseAudio(1);		//停止播放音频
	}

	std::cout << __func__ << ", " << __LINE__ << ", len = " << pcIfs->gcount() << std::endl;
}


int main()
{
	if(SDL_Init(SDL_INIT_AUDIO) != 0)			//初始化
	{
		std::cout << __func__ << ", " << __LINE__ << ", " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	std::ifstream ifs("test.pcm", std::ios::binary);
	if (!ifs.is_open())
	{
		std::cout << "File open is failed" << std::endl;
		return EXIT_FAILURE;
	}

	SDL_AudioSpec tSDL_AudioSpec;

	tSDL_AudioSpec.freq = 44100;						//音频采样率
	tSDL_AudioSpec.format = AUDIO_S16SYS;				//音频样本类型 使用系统字节序
	tSDL_AudioSpec.channels = 2;						//音频通道数量（双声道 立体声）
	tSDL_AudioSpec.silence = 0;							//静音的值
	tSDL_AudioSpec.samples = 1024;						//样本数量，2的n次方，用于分割
														//平面模式的通道数据
														//例如：samples = 8
														//		LLLL RRRR
	tSDL_AudioSpec.callback = MyAudioCallback;			//回调函数
	tSDL_AudioSpec.userdata = &ifs;

	if (SDL_OpenAudio(&tSDL_AudioSpec, nullptr) != 0)
	{
		std::cout << __func__ << ", " << __LINE__ << ", " << SDL_GetError() << std::endl;

		if(ifs.is_open())
			ifs.close();

		return EXIT_FAILURE;
	}

	SDL_PauseAudio(0);		//开始播放音频

	getchar();

	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	if (ifs.is_open())
		ifs.close();

	return EXIT_SUCCESS;
}



