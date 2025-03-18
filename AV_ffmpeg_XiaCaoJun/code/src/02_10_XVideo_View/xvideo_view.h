/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xvideo_view.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.18
描  述: 实现一个抽象类，支持图像的渲染
备  注: 所有的接口均支持线程安全
修改记录:

  1.  日期: 2025.03.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#pragma once

#include <mutex>

class CXVideo_View
{
protected:
    CXVideo_View() = default;

public:
    enum class Format:char          //像素格式
    {
        RGBA = 1,
        ARGB,
        YUV420P
    };

    enum class RenderType :char     //渲染类型
    {
        SDL = 1
    };

	~CXVideo_View() = default;

    /// <summary>
    /// 创建一个新的类对象
    /// </summary>
    /// <param name="_RenderType"></param>
    /// <returns></returns>
    static CXVideo_View* Create(RenderType _RenderType = RenderType::SDL);

    /// <summary>
    /// 初始化窗口
    /// </summary>
    /// <param name="_Width">窗口宽度</param>
    /// <param name="_Height">窗口高度</param>
    /// <param name="_Fmt">绘制的像素格式</param>
    /// <param name="_pWinID">窗口句柄;如果为空,创建新窗口</param>
    /// <returns>true--创建成功;false--创建失败</returns>
    virtual bool Init(int _Width, int _Height, Format _Fmt = Format::RGBA, void* _pWinID = nullptr) = 0;
         
    /// <summary>
    /// 渲染图像
    /// </summary>
    /// <param name="_pData">渲染的二进制数据</param>
    /// <param name="_LineSize">一行数据的字节数，对于YUV420P就是Y一行字节数；_LineSize<=0，就更具宽度和像素格式自动算出大小</param>
    /// <returns>true--创建成功;false--创建失败</returns>
    virtual bool Draw(char* _pData, int _LineSize = 0) = 0;

    /// <summary>
    /// 重新设置窗口显示大小
    /// </summary>
    /// <param name="_Width"></param>
    /// <param name="_Height"></param>
    /// <returns></returns>
    bool SetScale(int _Width, int _Height);

    /// <summary>
    /// 当前窗口是否退出
    /// </summary>
    /// <param name=""></param>
    /// <returns>true--已经退出;false--未退出</returns>
    virtual bool IsExit(void) = 0;

    /// <summary>
    /// 释放资源
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Close(void) = 0;

protected:
    int m_nWidth = 0;                       //图像宽度
    int m_nHeight = 0;                      //图像高度
    Format m_eFmt = Format::RGBA;           //绘制的像素格式
    std::mutex m_mutex;                     //互斥锁，用于确保接口线程内部安全

    int m_nScale_Width = 0;                 //窗口显示宽度
    int m_nScale_Height = 0;                //窗口显示高度
};


