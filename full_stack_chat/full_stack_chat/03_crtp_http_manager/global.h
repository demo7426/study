/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	global.h
作  者:	钱锐      版本: V0.1.1     新建日期: 2026.05.28
描  述:	公共全局文件
备  注:
修改记录:

  1.  日期: 2026.05.28
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

  2.  日期: 2026.06.14
      作者: 钱锐
      内容:
          1) 新增http相关请求枚举值；
      版本:V0.1.1
*************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <functional>

///
/// \brief The HTTP_REQ_ID enum http相关请求id
///
enum class HTTP_REQ_ID: short{
    ID_GET_VERIFY_CODE = 1001,      //获取验证码
    ID_REG_USER,                    //注册用户
};

///
/// \brief The ERROR_CODE enum 错误代码
///
enum class ERROR_CODE: short{
    SUCCESS = 1,
    ERR_JSON,
    ERR_NETWORK
};

///
/// \brief The HTTP_MODULE_ID enum http相关模块id
///
enum class HTTP_MODULE_ID: short{
    REGITER_MOD = 1001,             //注册模块
};


///
/// \brief repolish 用于ui强制刷新
///
extern std::function<void(QWidget*)> g_cRepolish;

#endif // GLOBAL_H
