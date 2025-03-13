/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.13
描  述: 使用SDL渲染RGB图像
备  注: SDL渲染图像的性能是高于Qt的
修改记录:

  1.  日期: 2025.03.13
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <iostream>
#include <sdl/SDL.h>

using namespace std;

#pragma comment(lib, "SDL2.lib")
#undef main

int main()
{
    constexpr int nWidth = 800;                       //窗口的宽
    constexpr int nHeight = 600;                      //窗口的高
    unsigned char uchRedValue = 255;                  //Red值
    int nReversal = 0;                                //是否反转

    //1、初始化SDL video库
    if (SDL_Init(SDL_INIT_VIDEO))           
    {
        cout << SDL_GetError() << endl;
        return 0;
    }

    //2、生成SDL窗口
    auto ptSDL_Screen =  SDL_CreateWindow(  
        "02_05_SDL_RGB",
        SDL_WINDOWPOS_CENTERED,             //窗口位置居中
        SDL_WINDOWPOS_CENTERED,             //窗口位置居中
        nWidth,
        nHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    if (!ptSDL_Screen)
    {
        cout << SDL_GetError() << endl;
        return 0;
    }

    //3、生成渲染器，渲染器使用硬件加速
    auto ptSDL_Render = SDL_CreateRenderer(ptSDL_Screen, -1, SDL_RENDERER_ACCELERATED);
    if (!ptSDL_Render)
    {
        cout << SDL_GetError() << endl;
        return 0;
    }

    //4、生成材质
    auto ptSDL_Texture = SDL_CreateTexture(ptSDL_Render, 
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING,        //可加锁
        nWidth,
        nHeight
    );
    if (!ptSDL_Texture)
    {
        cout << SDL_GetError() << endl;
        return 0;
    }

    while (1)
    {
        //判断退出
        SDL_Event tSDL_Event;
        SDL_WaitEventTimeout(&tSDL_Event, 2);
        if (tSDL_Event.type == (Uint32)SDL_QUIT)
        {
            SDL_DestroyWindow(ptSDL_Screen);
            break;
        }

        //存放图像数据
        shared_ptr<unsigned char> pspARGB(new unsigned char[nWidth * nHeight * 4]);
        auto puchARGB = pspARGB.get();

        for (int i = 0; i < nHeight; i++)
        {
            int nRowNum = i * nWidth * 4;
            for (int j = 0; j < nWidth * 4; j += 4)
            {
                puchARGB[nRowNum + j] = uchRedValue;  //R
                puchARGB[nRowNum + j + 1] = 0;      //G
                puchARGB[nRowNum + j + 2] = 0;      //B
                puchARGB[nRowNum + j + 3] = 0;      //A
            }
        }

        //让数据循环起来
        nReversal == 0 ? uchRedValue-- : uchRedValue++;
        if (uchRedValue == 0 || uchRedValue == 255)
        {
            nReversal = (nReversal == 0 ? 1 : 0);
        }

        //5、将图像数据写入材质
        SDL_UpdateTexture(ptSDL_Texture, NULL, puchARGB, nWidth * 4);

        //6、清理屏幕
        SDL_RenderClear(ptSDL_Render);

        SDL_Rect tSDL_Rect;
        tSDL_Rect.x = 0;
        tSDL_Rect.y = 0;
        tSDL_Rect.w = nWidth;
        tSDL_Rect.h = nHeight;

        //7、复制材质到渲染
        SDL_RenderCopy(ptSDL_Render,
            ptSDL_Texture,
            NULL,           //原图的位置和尺寸
            &tSDL_Rect      //目标位置和尺寸
        );

        //8、渲染
        SDL_RenderPresent(ptSDL_Render);
    }

    getchar();
    return 0;
}
