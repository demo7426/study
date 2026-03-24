/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.24
描  述: opencv自带颜色表操作
备  注: 使用的是opencv4.12.0版本
修改记录:

  1.  日期: 2026.03.24
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "opencv2/opencv.hpp"

int main()
{
	std::string strSrcWinName = "原图";
	std::string strDstWinName = "处理后";

	cv::Mat cMatDst;
	cv::Mat cMat = cv::imread("R-C.png");
	if (cMat.empty())
	{
		std::cout << __func__ << ", file is not exist" << std::endl;
		return EXIT_FAILURE;
	}

	cv::namedWindow(strSrcWinName);
	cv::namedWindow(strDstWinName);

	cv::moveWindow(strSrcWinName, 10, 10);
	cv::moveWindow(strDstWinName, 20 + cMat.cols, 10);

	cv::imshow(strSrcWinName, cMat);

	int nColormapTypes[] = {
		cv::ColormapTypes::COLORMAP_AUTUMN, //!< ![autumn](pics/colormaps/colorscale_autumn.jpg)
		cv::ColormapTypes::COLORMAP_BONE, //!< ![bone](pics/colormaps/colorscale_bone.jpg)
		cv::ColormapTypes::COLORMAP_JET, //!< ![jet](pics/colormaps/colorscale_jet.jpg)
		cv::ColormapTypes::COLORMAP_WINTER, //!< ![winter](pics/colormaps/colorscale_winter.jpg)
		cv::ColormapTypes::COLORMAP_RAINBOW, //!< ![rainbow](pics/colormaps/colorscale_rainbow.jpg)
		cv::ColormapTypes::COLORMAP_OCEAN, //!< ![ocean](pics/colormaps/colorscale_ocean.jpg)
		cv::ColormapTypes::COLORMAP_SUMMER, //!< ![summer](pics/colormaps/colorscale_summer.jpg)
		cv::ColormapTypes::COLORMAP_SPRING, //!< ![spring](pics/colormaps/colorscale_spring.jpg)
		cv::ColormapTypes::COLORMAP_COOL, //!< ![cool](pics/colormaps/colorscale_cool.jpg)
		cv::ColormapTypes::COLORMAP_HSV, //!< ![HSV](pics/colormaps/colorscale_hsv.jpg)
		cv::ColormapTypes::COLORMAP_PINK, //!< ![pink](pics/colormaps/colorscale_pink.jpg)
		cv::ColormapTypes::COLORMAP_HOT, //!< ![hot](pics/colormaps/colorscale_hot.jpg)
		cv::ColormapTypes::COLORMAP_PARULA, //!< ![parula](pics/colormaps/colorscale_parula.jpg)
		cv::ColormapTypes::COLORMAP_MAGMA, //!< ![magma](pics/colormaps/colorscale_magma.jpg)
		cv::ColormapTypes::COLORMAP_INFERNO, //!< ![inferno](pics/colormaps/colorscale_inferno.jpg)
		cv::ColormapTypes::COLORMAP_PLASMA, //!< ![plasma](pics/colormaps/colorscale_plasma.jpg)
		cv::ColormapTypes::COLORMAP_VIRIDIS, //!< ![viridis](pics/colormaps/colorscale_viridis.jpg)
		cv::ColormapTypes::COLORMAP_CIVIDIS, //!< ![cividis](pics/colormaps/colorscale_cividis.jpg)
		cv::ColormapTypes::COLORMAP_TWILIGHT, //!< ![twilight](pics/colormaps/colorscale_twilight.jpg)
		cv::ColormapTypes::COLORMAP_TWILIGHT_SHIFTED, //!< ![twilight shifted](pics/colormaps/colorscale_twilight_shifted.jpg)
		cv::ColormapTypes::COLORMAP_TURBO, //!< ![turbo](pics/colormaps/colorscale_turbo.jpg)
		cv::ColormapTypes::COLORMAP_DEEPGREEN  //!< ![deepgreen](pics/colormaps/colorscale_deepgreen.jpg)
	};

	while (1)
	{
		for (size_t i = 0; i < sizeof nColormapTypes / sizeof(nColormapTypes[0]); i++)
		{
			cv::applyColorMap(cMat, cMatDst, nColormapTypes[i]);

			cv::imshow(strDstWinName, cMatDst);

			cv::waitKey(1000);
		}
	}

	return EXIT_SUCCESS;
}

