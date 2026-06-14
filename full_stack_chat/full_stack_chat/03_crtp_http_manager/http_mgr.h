/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	http_mgr.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.06.14
描  述:	实现http管理模块
备  注:
修改记录:

  1.  日期: 2026.06.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef CHTTPMGR_H
#define CHTTPMGR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QNetworkReply>

#include "singleton.h"
#include "global.h"

class CHttpMgr : public QObject, public CSingleTon<CHttpMgr>, public std::enable_shared_from_this<CHttpMgr>
{
    Q_OBJECT

public:
    ~CHttpMgr() = default;

private:
    friend class CSingleTon<CHttpMgr>;

    CHttpMgr();

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;

private:
    QNetworkAccessManager m_cNetworkAccessManager;

    ///
    /// \brief PostHttpReq 发送http post请求
    /// \param _Url http url
    /// \param _JsonObj json相关数值
    /// \param _Http_Req_ID 请求id
    /// \param _Http_Module_ID 模块id
    ///
    void PostHttpReq(QUrl _Url, QJsonObject _JsonObj, HTTP_REQ_ID _Http_Req_ID, HTTP_MODULE_ID _Http_Module_ID);

signals:
    ///
    /// \brief Sig_Http_Finish 发送http结束信号
    /// \param _Content 响应内容
    /// \param _Http_Req_ID 响应id
    /// \param _Err_Code 错误码
    /// \param _Http_Module_ID 模块id
    ///
    void Sig_Http_Finish(QString _Content, HTTP_REQ_ID _Http_Req_ID, ERROR_CODE _Err_Code, HTTP_MODULE_ID _Http_Module_ID);

    void Sig_Reg_Mod_Finish(QString _Content, HTTP_REQ_ID _Http_Req_ID, ERROR_CODE _Err_Code);
};

#endif // CHTTPMGR_H
