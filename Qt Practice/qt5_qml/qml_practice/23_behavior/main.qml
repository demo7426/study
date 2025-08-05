/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.05
描  述:	行为属性字段
备  注:
修改记录:

  1.  日期: 2025.08.05
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "white"

    Rectangle{
        id: g_rectandle
        width: 80
        height: 40
        color: "red"
        anchors.centerIn: parent

        Behavior on width{
             NumberAnimation { duration: 1000 }
        }

        Behavior on color{
            ColorAnimation { duration: 1000 }
        }

        Text {
            id: g_text
            anchors.centerIn: parent
            text: qsTr("鼠标未移入")
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                parent.width = 120
                parent.color = "yellow"
                g_text.text = qsTr("鼠标移入")
            }

            onExited: {
                parent.width = 80
                parent.color = "red"
                g_text.text = qsTr("鼠标未移入")
            }
        }
    }

}



