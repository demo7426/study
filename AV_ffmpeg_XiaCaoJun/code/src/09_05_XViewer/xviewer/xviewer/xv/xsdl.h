/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xsdl.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.22
描  述: 使用SDL进行渲染
备  注:
修改记录:

  1.  日期: 2025.03.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#pragma once
#include "xvideo_view.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class CXSDL :public CXVideo_View
{
public:
    using CXVideo_View::CXVideo_View;

    /// <summary>
    /// 初始化窗口
    /// </summary>
    /// <param name="_Width">窗口宽度</param>
    /// <param name="_Height">窗口高度</param>
    /// <param name="_Fmt">绘制的像素格式</param>
    /// <param name="_pWinID">窗口句柄;如果为空,创建新窗口</param>
    /// <returns>true--创建成功;false--创建失败</returns>
    bool Init(int _Width, int _Height, Format _Fmt = Format::RGBA, void* _pWinID = nullptr) override;

    /// <summary>
    /// 渲染图像
    /// </summary>
    /// <param name="_pData">渲染的二进制数据</param>
    /// <param name="_LineSize">一行数据的字节数，对于YUV420P就是Y一行字节数；_LineSize<=0，就更具宽度和像素格式自动算出大小</param>
    /// <returns>true--创建成功;false--创建失败</returns>
    bool Draw(char* _pData, int _LineSize = 0) override;
    
    /// <summary>
    /// 渲染图像
    /// </summary>
    /// <param name="_Yplane">Y的数据</param>
    /// <param name="_Ypitch">Y的一行像素点数量</param>
    /// <param name="_Uplane">U的数据</param>
    /// <param name="_Upitch">U的一行像素点数量</param>
    /// <param name="_Vplane">V的数据</param>
    /// <param name="_Vpitch">V的一行像素点数量</param>
    /// <returns>true--执行成功;false--执行失败</returns>
    bool Draw(char* _Yplane, int _Ypitch, char* _Uplane, int _Upitch, char* _Vplane, int _Vpitch) override;

    /// <summary>
    /// 当前窗口是否退出
    /// </summary>
    /// <param name=""></param>
    /// <returns>true--已经退出;false--未退出</returns>
    bool IsExit(void) override;

    /// <summary>
    /// 释放资源
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Close(void) override;

private:
    SDL_Window* m_ptSDL_Window;                     //窗口
    SDL_Renderer* m_ptSDL_Renderer;                 //渲染器
    SDL_Texture* m_ptSDL_Texture;                   //材质
};

