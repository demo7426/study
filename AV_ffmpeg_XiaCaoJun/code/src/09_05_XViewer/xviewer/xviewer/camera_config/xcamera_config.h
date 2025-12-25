/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xcamera_config.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.25
描  述: 实现相机配置文件的增删改查、加载等
备  注:
修改记录:

  1.  日期: 2025.12.25
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#pragma once

#include "singleton.h"

class CXCamera_Config : public CSingleton<CXCamera_Config>
{
    friend class CSingleton<CXCamera_Config>;
public:
    CXCamera_Config() = default;
    virtual ~CXCamera_Config() {};

	//加载配置文件
	int LoadConfigFile(std::string _FilePath);

private:

};
