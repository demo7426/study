/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xcamera_config.cpp
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

#include <fstream>

#include "xcamera_config.h"
#include "cJSON.h"
#include "debug.h"

int CXCamera_Config::LoadConfigFile(std::string _FilePath)
{
    std::ifstream ifs(_FilePath, std::ios::in);
    if (!ifs.is_open())
    {
        DEBUG(DEBUG_LEVEL_ERROR, "配置文件不存在");
        return -2;
    }

    std::string strJsonContent((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    ifs.close();
    if (strJsonContent.empty())
    {
        DEBUG(DEBUG_LEVEL_ERROR, "配置文件为空");
        return -2;
    }

    cJSON* ptJSONRoot = cJSON_Parse(strJsonContent.c_str());               //解析数据后的根节点
    if (ptJSONRoot == NULL)
    {
        DEBUG(DEBUG_LEVEL_ERROR, "cJSON_Parse is err");
        return -2;
    }
    
    // 3. 提取 camera_config_list 数组节点
    cJSON* pCameraArray = cJSON_GetObjectItem(ptJSONRoot, "camera_config_list");
    if (pCameraArray == NULL || !cJSON_IsArray(pCameraArray)) 
    {
        DEBUG(DEBUG_LEVEL_ERROR, "未找到 camera_config_list 数组，或类型错误");
        cJSON_Delete(ptJSONRoot); // 释放内存，避免泄漏
        return -2;
    }

    // 4. 遍历数组中的每个相机配置对象
    int nArraySize = cJSON_GetArraySize(pCameraArray);

    std::unique_lock<std::mutex> lock(m_mut);

    m_vecCamera_Config_Info.clear();
    for (int i = 0; i < nArraySize; i++) {
        // 获取数组中的第i个对象
        cJSON* ptCameraObj = cJSON_GetArrayItem(pCameraArray, i);
        if (ptCameraObj == NULL || !cJSON_IsObject(ptCameraObj)) {
            DEBUG(DEBUG_LEVEL_ERROR, "第 %d 个相机配置不是合法对象，跳过", i);
            continue;
        }

        // 5. 提取对象中的每个字段（注意：字段名要和 JSON 完全一致）
        CAMERA_CONFIG_INFO config;

        // 提取 name 字段（字符串类型）
        cJSON* ptName = cJSON_GetObjectItem(ptCameraObj, "name");
        if (ptName != NULL && cJSON_IsString(ptName)) {
            strcpy(config.Name, ptName->valuestring);
        }

        // 提取 url 字段
        cJSON* ptUrl = cJSON_GetObjectItem(ptCameraObj, "url");
        if (ptUrl != NULL && cJSON_IsString(ptUrl)) {
            strcpy(config.Url, ptUrl->valuestring);
        }

        // 提取 sub_url 字段
        cJSON* ptSubUrl = cJSON_GetObjectItem(ptCameraObj, "sub_url");
        if (ptSubUrl != NULL && cJSON_IsString(ptSubUrl)) {
            strcpy(config.SubUrl, ptSubUrl->valuestring);
        }

        // 提取 save_dir 字段
        cJSON* ptSaveDir = cJSON_GetObjectItem(ptCameraObj, "save_dir");
        if (ptSaveDir != NULL && cJSON_IsString(ptSaveDir)) {
            strcpy(config.SaveDir, ptSaveDir->valuestring);
        }

        //将解析结果存入全局列表
        m_vecCamera_Config_Info.push_back(config);

        // 打印解析结果（调试用）
        DEBUG(DEBUG_LEVEL_INFO, "%d:name=%s, url=%s, sub_url=%s, save_dir=%s",
            i, config.Name, config.Url, config.SubUrl, config.SaveDir);
    }

    if (ptJSONRoot)
    {
        cJSON_Delete(ptJSONRoot);
        ptJSONRoot = nullptr;
    }

	return 0;
}

CXCamera_Config::CAMERA_CONFIG_INFO CXCamera_Config::Get(int _Index)
{
    std::unique_lock<std::mutex> lock(m_mut);
    if (_Index >= m_vecCamera_Config_Info.size())
    {
        DEBUG(DEBUG_LEVEL_ERROR, "Input paramer is err");
        return CAMERA_CONFIG_INFO();
    }

    return m_vecCamera_Config_Info[_Index];
}

int CXCamera_Config::Add(CAMERA_CONFIG_INFO _tCameraConfigInfo)
{
    std::unique_lock<std::mutex> lock(m_mut);
    m_vecCamera_Config_Info.push_back(_tCameraConfigInfo);

    return 0;
}

int CXCamera_Config::Delete(int _Index)
{
    std::unique_lock<std::mutex> lock(m_mut);
    if (_Index >= m_vecCamera_Config_Info.size())
    {
        DEBUG(DEBUG_LEVEL_ERROR, "Input paramer is err");
        return -1;
    }

    m_vecCamera_Config_Info.erase(m_vecCamera_Config_Info.begin() + _Index);
    
    return 0;
}

int CXCamera_Config::Modify(int _Index, CAMERA_CONFIG_INFO _tCameraConfigInfo)
{
    std::unique_lock<std::mutex> lock(m_mut);
    if (_Index >= m_vecCamera_Config_Info.size())
    {
        DEBUG(DEBUG_LEVEL_ERROR, "Input paramer is err");
        return -1;
    }

    m_vecCamera_Config_Info[_Index] = _tCameraConfigInfo;

    return 0;
}

int CXCamera_Config::Clear(void)
{
    std::unique_lock<std::mutex> lock(m_mut);
    m_vecCamera_Config_Info.clear();

    return 0;
}

int CXCamera_Config::SaveConfigFile(std::string _FilePath)
{
    cJSON* root = cJSON_CreateObject();             //待组装的数据根节点

    std::ofstream ofs(_FilePath, std::ios::out);
    if (!ofs.is_open())
    {
        DEBUG(DEBUG_LEVEL_ERROR, "配置文件不存在");
        return -2;
    }

    std::string strJSon = AssembleCameraConfigJson(m_vecCamera_Config_Info);

    ofs.write(strJSon.data(), strJSon.size());

    ofs.close();

    return 0;
}

std::string CXCamera_Config::AssembleCameraConfigJson(const std::vector<CXCamera_Config::CAMERA_CONFIG_INFO>& cameraList)
{
    // 1. 创建JSON根对象（最外层{}）
    cJSON* pRoot = cJSON_CreateObject();
    if (pRoot == nullptr) {
        std::cerr << "创建JSON根对象失败！" << std::endl;
        return "";
    }

    // 2. 创建相机配置数组（camera_config_list）
    cJSON* pCameraArray = cJSON_CreateArray();
    if (pCameraArray == nullptr) {
        cJSON_Delete(pRoot);
        std::cerr << "创建相机配置数组失败！" << std::endl;
        return "";
    }

    // 3. 遍历相机列表，逐个创建配置对象并添加到数组
    for (const auto& config : cameraList) {
        // 3.1 创建单个相机配置对象（{}）
        cJSON* pCameraObj = cJSON_CreateObject();
        if (pCameraObj == nullptr) {
            continue;
        }

        // 3.2 为对象添加字段（支持空字符串）
        // name字段
        cJSON_AddStringToObject(pCameraObj, "name", config.Name);
        // url字段
        cJSON_AddStringToObject(pCameraObj, "url", config.Url);
        // sub_url字段
        cJSON_AddStringToObject(pCameraObj, "sub_url", config.SubUrl);
        // save_path字段
        cJSON_AddStringToObject(pCameraObj, "save_dir", config.SaveDir);

        // 3.3 将单个相机对象添加到数组
        cJSON_AddItemToArray(pCameraArray, pCameraObj);
    }

    // 4. 将数组添加到根对象
    cJSON_AddItemToObject(pRoot, "camera_config_list", pCameraArray);

    // 5. 生成JSON字符串（两种方式可选）
    // 方式1：格式化输出（带缩进，易读）
    char* pJsonStr = cJSON_Print(pRoot);
    // 方式2：紧凑输出（无缩进，节省空间）
    // char* pJsonStr = cJSON_PrintUnformatted(pRoot);

    std::string jsonResult;
    if (pJsonStr != nullptr) {
        jsonResult = pJsonStr;
        free(pJsonStr); // 必须释放cJSON_Print分配的内存！
    }

    // 6. 释放根对象（递归释放所有子节点）
    cJSON_Delete(pRoot);

    return jsonResult;
}
