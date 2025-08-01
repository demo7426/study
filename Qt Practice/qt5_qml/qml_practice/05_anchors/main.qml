/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.01
描  述:	anchors锚布局
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

    Item {
        width: 100
        height: 100
    }

    Rectangle{
        id: g_rectangle
        width: 100
        height: 100
        color: "red"
        x: 100
        y: 100
        z: 101              // 层级，层级高的会覆盖低的
    }

    Rectangle{
        width: 50
        height: 50
        color: "cyan"
        z: g_rectangle.z + 1

        anchors.fill: g_rectangle                   // 填充

//        anchors.verticalCenter: g_rectangle.verticalCenter
//        anchors.horizontalCenter: g_rectangle.horizontalCenter

//        anchors.centerIn: g_rectangle

//        anchors.left: g_rectangle.right
//        anchors.top: g_rectangle.top
//        anchors.leftMargin: 10                  // 左边距
    }
}



