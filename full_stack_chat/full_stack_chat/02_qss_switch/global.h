/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	global.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.05.28
描  述:	公共全局文件
备  注:
修改记录:

  1.  日期: 2026.05.28
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <functional>

///
/// \brief repolish 用于ui强制刷新
///
extern std::function<void(QWidget*)> g_cRepolish;

#endif // GLOBAL_H
