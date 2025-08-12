/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.12
描  述:	实现鼠标穿透
备  注:  注意：鼠标最多只能穿透一层
修改记录:

  1.  日期: 2025.08.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.14
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQml 2.14
import QtQuick.Layouts 1.14

Window {
    visible: true
    width: 1280
    height: 720
    title: qsTr("Hello World")


    Rectangle{
        width: 100
        height: 100
        radius: 10
        color: "green"                  // 正常时为绿

        Text {
            anchors.centerIn: parent
            text: "确认"
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log("Rectangle_0 被单击了")
            }
        }
    }

    Rectangle{
        width: 100
        height: 100
        radius: 10
        color: "green"                  // 正常时为绿

        Text {
            anchors.centerIn: parent
            text: "确认"
        }

        MouseArea{
            anchors.fill: parent
            propagateComposedEvents: true               // 使能鼠标传播等事件
            onClicked: {
                console.log("Rectangle_1 被单击了")
                mouse.accepted = false                  // 指定当前未接收鼠标事件，向下进行传播
            }
        }
    }

}
