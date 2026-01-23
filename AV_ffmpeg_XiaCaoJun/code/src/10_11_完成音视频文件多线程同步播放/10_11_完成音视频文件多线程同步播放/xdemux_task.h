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
    
    /// <summary>
    /// 设置责任链下一阶段的解码任务
    /// </summary>
    /// <param name="_pcXThread_Video">视频解码任务;nullptr--代表后续不解码</param>
    /// <param name="_pcXThread_Audio">音频解码任务;nullptr--代表后续不解码</param>
    void SetNext(CXThread* _pcXThread_Video, CXThread* _pcXThread_Audio);

    inline CXDemux* GetCXDemux()
    {
        return &m_cXDemux;
    }

    /// <summary>
    /// 设置当前播放的时间戳
    /// </summary>
    /// <param name="">时间戳;单位:us</param>
    /// <returns></returns>
    int SetCurPlayTimestamp(long long _Timestamp);

    /// <summary>
    /// 获取时长;单位为:us
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    long long GetDuration(void);

private:
    void Main(void) override;

private:
    CXDemux m_cXDemux;			                    //解封装对象

    const char* m_pURL = "";
    int m_TimeoutMs = 0;

    int m_nFrameRate = 1000;                        //当前视频的帧率

    CXDecode_Task* m_pcXDecode_Task_Video = nullptr;      //下一个数据处理对象
    CXDecode_Task* m_pcXDecode_Task_Audio = nullptr;      //下一个数据处理对象
};


