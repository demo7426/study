/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	staticlib.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.25
描  述:	实现计算及其接口
备  注:
修改记录:

  1.  日期: 2024.10.25
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef STATICLIB_H
#define STATICLIB_H

class CStaticlib
{
public:
    CStaticlib();

    template<class T>
    static T Add(T _X, T _Y)
    {
        return _X + _Y;
    }
};

#endif // STATICLIB_H
