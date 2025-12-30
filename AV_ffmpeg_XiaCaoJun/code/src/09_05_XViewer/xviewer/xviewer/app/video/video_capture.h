/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	video_capture.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.18
描  述:	实现音视频数据的采集
备  注:
修改记录:

  1.  日期: 2025.12.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef VIDEO_CAPTURE_H
#define VIDEO_CAPTURE_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>

#include "xdemux_task.h"
#include "xdecode_task.h"
#include "xencode.h"
#include "xdecode.h"
#include "xvideo_view.h"
#include "xdemux.h"
#include "xmux.h"

class CVideo_Capture : public QThread
{
    Q_OBJECT
public:
    explicit CVideo_Capture(QObject *parent = nullptr);

    //视频信息
    typedef struct _AVIDEO_INFO
    {
        int Width;                          //宽度
        int Height;                         //高度
        int FrameRate;                      //帧率
        qint64 Duration;                    //时长;单位:s
        int Video_CodeID;                   //视频编码格式;27--AV_CODEC_ID_H264;173--AV_CODEC_ID_H265
        
        //视频像素格式;0--AV_PIX_FMT_YUV420P;25--AV_PIX_FMT_ARGB;26--AV_PIX_FMT_RGBA;27--AV_PIX_FMT_ABGR;28--AV_PIX_FMT_BGRA
        int PixFmt;                         
    }AVIDEO_INFO, *PAVIDEO_INFO;

    /// <summary>
    /// 开始线程
    /// </summary>
    /// <param name="_URL">源流</param>
    /// <param name="_StoreDir">存储目录;如果为空，则保存文件到当前目录下</param>
    /// <param name="_pWinID">窗口id</param>
    /// <returns>-2--失败;-1--传入参数错误;0--成功;</returns>
    int StartThread(QString _URL, QString _StoreDir, bool _IsSave, void* _pWinID) noexcept;

    ///
    /// \brief StartThread--结束线程
    ///
    void StopThread(void) noexcept;

    /// <summary>
    /// 获取音视频格式信息
    /// </summary>
    /// <param name="_URL">源流</param>
    /// <returns></returns>
    int GetVideoInfo(QString _URL, PAVIDEO_INFO _ptVideo_Info);

protected:
    void run() override;

private:
    QString m_strURL = "";                  //源流
    QString m_strStoreDir = "";             //存储目录
    bool m_bIsSave = "";                    //是否需要转码保存

    bool m_bIsRun = false;                  //线程是否运行的标志;true--运行;false--停止;
    QMutex m_mut;

    void* m_pvWinID = nullptr;              //渲染windows窗口id
    
    CXDemux_Task m_cDemux_Task;
    CXDecode_Task m_cDecode_Task;
    CXEncode m_cXEncode;
    CXMux m_cXMux;
    CXDemux m_cXDemux;

    /// <summary>
    /// 获取本地时间并且拼接成字符串的形式
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetLocalTime(void);

signals:
    ///
    /// \brief SendCurPercent--发送当前回放文件的百分比
    /// \param _Speed--回放速度，单位MB/s
    /// \param _Value--百分比;0~100(100代表回放数据完成,线程正常结束)
    ///
    void SendCurPercent(quint32 _Speed, qint8 _Value);

    void SendCurPacketData(quint8 *_pStartAddr, quint32 _Len);
};

#endif // VIDEO_CAPTURE_H
