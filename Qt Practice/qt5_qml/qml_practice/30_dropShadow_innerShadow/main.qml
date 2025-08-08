/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.08
描  述:	实现内外阴影
备  注:
修改记录:

  1.  日期: 2025.08.08
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/


import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.14
import QtQuick.Controls 1.4
import QtQml 2.14

Window {
    visible: true
    width: 1280
    height: 720
    title: qsTr("Hello World")

    Rectangle{
        id: g_rectangle
        width: 200
        height: 50
        anchors.centerIn: parent
        color: "red"
    }

    //外投影
    DropShadow {
        anchors.fill: g_rectangle
        source: g_rectangle
        horizontalOffset: 10
        verticalOffset: 10
        radius: 8.0
        samples: 17
        color: "#80000000"
    }

    //内阴影
    InnerShadow {
        anchors.fill: g_rectangle
        source: g_rectangle
        radius: 8.0
        samples: 16
        horizontalOffset: -3
        verticalOffset: 3
        color: "#b0000000"
    }

}
