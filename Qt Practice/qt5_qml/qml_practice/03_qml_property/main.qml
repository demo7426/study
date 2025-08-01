/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.01
描  述:	qml属性
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
        id: g_rectangle_00
        width: 100
        height: 100
        color: "red"
        border.color: "yellow"
        border.width: 5
        radius: 15

        default property color default_color: "pink"        // 默认属性，属性类型包括：int，real，double，string，list，color...
        readonly property color readonly_color: "cyan"      // 只读属性，不可以修改

        Component.onCompleted: {
            console.log("第一条日志")
            default_color = "#6495ed"
        }
    }

    Rectangle{
        id: g_rectangle_01
        width: g_rectangle_00.width
        height: g_rectangle_00.height
        color: g_rectangle_00.default_color
        x: 200
    }
}
