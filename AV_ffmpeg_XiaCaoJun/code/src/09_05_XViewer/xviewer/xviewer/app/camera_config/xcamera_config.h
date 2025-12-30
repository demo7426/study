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

#include <vector>
#include <mutex>

#include "singleton.h"

class CXCamera_Config : public CSingleton<CXCamera_Config>
{
    friend class CSingleton<CXCamera_Config>;
public:
    CXCamera_Config() = default;
    virtual ~CXCamera_Config() {};

	/// <summary>
	/// 相机相关信息
	/// </summary>
	typedef struct _CAMERA_CONFIG_INFO
	{
		char Name[1024];
		char Url[4096];
		char SubUrl[4096];
		char SaveDir[4096];
	}CAMERA_CONFIG_INFO, * PCAMERA_CONFIG_INFO;

private:
	std::vector<CAMERA_CONFIG_INFO> m_vecCamera_Config_Info;

	std::mutex m_mut;

public:
	//加载配置文件
	int LoadConfigFile(std::string _FilePath);

	/// <summary>
	/// 获取数量
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	inline int GetCount(void)
	{
		std::unique_lock<std::mutex> lock(m_mut);
		return m_vecCamera_Config_Info.size();
	}

	/// <summary>
	/// 获取相机相关的配置信息
	/// </summary>
	/// <param name="_Index"></param>
	/// <returns></returns>
	CAMERA_CONFIG_INFO Get(int _Index);
	
	/// <summary>
	/// 增加配置信息
	/// </summary>
	/// <param name="_tCameraConfigInfo"></param>
	/// <returns></returns>
	int Add(CAMERA_CONFIG_INFO _tCameraConfigInfo);
	
	/// <summary>
	/// 删除对应索引的配置信息
	/// </summary>
	/// <param name="_Index"></param>
	/// <returns></returns>
	int Delete(int _Index);

	/// <summary>
	/// 修改对应索引的配置信息
	/// </summary>
	/// <param name="_Index"></param>
	/// <param name="_tCameraConfigInfo"></param>
	/// <returns></returns>
	int Modify(int _Index, CAMERA_CONFIG_INFO _tCameraConfigInfo);

	/// <summary>
	/// 清空所有的配置信息
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	int Clear(void);

	/// <summary>
	/// 保存当前相机配置信息到对应的文件中
	/// </summary>
	/// <param name="_FilePath"></param>
	/// <returns></returns>
	int SaveConfigFile(std::string _FilePath);

	/*
	 * @brief 组装相机配置JSON字符串
	 * @param cameraList 相机配置列表
	 * @return 组装好的JSON字符串（格式化，带缩进）
	 */
	std::string AssembleCameraConfigJson(const std::vector<CAMERA_CONFIG_INFO>& cameraList);
};
