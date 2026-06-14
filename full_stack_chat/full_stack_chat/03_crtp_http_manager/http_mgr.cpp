/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	http_mgr.cpp
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

#include <QDebug>

#include "http_mgr.h"

CHttpMgr::CHttpMgr()
{
    this->InitSignalSlots();
}

void CHttpMgr::InitSignalSlots() noexcept
{
    connect(this, &CHttpMgr::Sig_Http_Finish, this, &CHttpMgr::Sig_Reg_Mod_Finish);
}

void CHttpMgr::PostHttpReq(QUrl _Url, QJsonObject _JsonObj, HTTP_REQ_ID _Http_Req_ID, HTTP_MODULE_ID _Http_Module_ID)
{
    //创建一个http post请求，并设置请求头和请求体
    QByteArray cData = QJsonDocument(_JsonObj).toJson();

    //通过url构造请求
    QNetworkRequest cRequest(_Url);
    cRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    cRequest.setHeader(QNetworkRequest::ContentLengthHeader, cData.length());

    //发送请求，并处理响应
    QNetworkReply* pcNetworkReply = m_cNetworkAccessManager.post(cRequest, cData);

    //获取自己的智能指针，构造伪闭包增加智能指针引用计数
    auto self = shared_from_this();

    QObject::connect(pcNetworkReply, &QNetworkReply::finished, [pcNetworkReply, self, _Http_Req_ID, _Http_Module_ID](){
        //处理错误的情况
        if(pcNetworkReply->error() != QNetworkReply::NoError)
        {
            qDebug() << pcNetworkReply->errorString();

            //发送信号通知完成
            emit self->Sig_Http_Finish("", _Http_Req_ID, ERROR_CODE::ERR_NETWORK,  _Http_Module_ID);
            pcNetworkReply->deleteLater();
            return;
        }

        //无错误则读回请求
        QString strReadAll = pcNetworkReply->readAll();

        //发送信号通知完成
        emit self->Sig_Http_Finish(strReadAll, _Http_Req_ID, ERROR_CODE::SUCCESS, _Http_Module_ID);
        pcNetworkReply->deleteLater();
        return;
    });

}
