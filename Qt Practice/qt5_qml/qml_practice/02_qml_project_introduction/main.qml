/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.01
描  述:	qml项目介绍
备  注:
修改记录:

  1.  日期: 2025.08.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "gray"

    Rectangle{
        id:g_rectangle                              // id，可以理解为Rectangle的实例化后的对象
        width: 100
        height: 100
        color: "red"
        border.color: "yellow"
        border.width: 5
        radius: 15
    }

    Rectangle{
        width: 100
        height: 100
        color: g_rectangle.color
        border.color: g_rectangle.border.color
        border.width: g_rectangle.border.width
        x: 200
    }
}
