/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xdemux_task.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.14
描  述: 线程内部实现解封装
备  注:
修改记录:

  1.  日期: 2025.12.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#pragma once

#include "xthread.h"
#include "xdemux.h"
#include "xencode.h"

class CXDecode_Task;
class CXEncode;
class CXMux;

class CXDemux_Task: public CXThread
{
public:
	CXDemux_Task() = default;
	~CXDemux_Task() = default;

    /// <summary>
    /// 打开解封装
    /// </summary>
    /// <param name="_pURL">rtsp地址</param>
    /// <param name="_TimeoutMs">超时时间;单位:毫秒</param>
    /// <returns></returns>
    int Open(const char* _pURL, int _TimeoutMs = 1000);
    
    void SetNext(CXThread* _pcXThread) override;

    /// <summary>
    /// 设置编码、封装对象
    /// </summary>
    /// <param name="_pcXEncode"></param>
    /// <param name="_pcXMux"></param>
    void SetXEncode_XMux(CXEncode* _pcXEncode, CXMux* _pcXMux);

private:
    void Main(void) override;

private:
    CXDemux m_cXDemux;			//解封装对象

    const char* m_pURL = "";
    int m_TimeoutMs = 0;

    CXDecode_Task* m_pcXDecode_Task = nullptr;      //下一个数据处理对象

    CXEncode* m_pcXEncode = nullptr;
    CXMux* m_pcXMux = nullptr;
};


