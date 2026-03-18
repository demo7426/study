/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	sfilter.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.18
描  述: 实现过滤器类
备  注:
修改记录:

  1.  日期: 2026.03.18
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#pragma once

namespace cv {
	class Mat;
}

class CSFilter
{
public:
	CSFilter() = default;
	virtual ~CSFilter() = default;

	/// <summary>
	/// 过滤器
	/// </summary>
	/// <param name="_pSrcMat">源数据</param>
	/// <param name="_pDesMat">目的数据</param>
	/// <returns>-2--执行失败;-1--参数错误;0--执行成功</returns>
	virtual int Filter(cv::Mat* _pSrcMat, cv::Mat* _pDesMat) = 0;

	/// <summary>
	/// 设置过滤器相关数值
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	virtual int SetValue(int _Value) = 0;

private:

};

class CSBilateralFilter : public CSFilter
{
public:
	using CSFilter::CSFilter;
	~CSBilateralFilter() {};

	/// <summary>
	/// 过滤器
	/// </summary>
	/// <param name="_pSrcMat">源数据</param>
	/// <param name="_pDesMat">目的数据</param>
	/// <returns>-2--执行失败;-1--参数错误;0--执行成功</returns>
	int Filter(cv::Mat* _pSrcMat, cv::Mat* _pDesMat) override;

	/// <summary>
	/// 设置过滤器相关数值
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	int SetValue(int _Value);

private:
	int m_nDia = 6;			//滤波过程中使用的每个像素邻域直径
};

