/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.05
描  述:	实现所有的属性动画效果
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

    Button{
        onClicked: {
            g_anti.restart()
        }
    }

    PropertyAnimation{
        id: g_anti
        target: g_rectandle
        properties: "width"
        from: 120
        to: 400
        duration: 1000
        easing.type: Easing.InQuad          //变化速率内部算子
    }

    Rectangle{
        id: g_rectandle
        width: 0
        height: 40
        color: "red"
        anchors.centerIn: parent
        state: "normal"                     //显示设置初始状态为normal，保证第一次鼠标移入时的动画效果
        PropertyAnimation on width { to: 80; duration: 1000 }      //初始化时的动态效果

        // 过渡效果
        transitions: [
            Transition {
                from: "normal"
                to: "hovered"

                ColorAnimation {
                    target: g_rectandle
                    duration: 1000
                }

                PropertyAnimation {
                    target: g_rectandle
                    properties: "width"
                    to: 120
                    duration: 1000
                    easing.type: Easing.Linear          //变化速率内部算子
                }
            },
            Transition {
                from: "hovered"
                to: "normal"

                ColorAnimation {
                    target: g_rectandle
                    duration: 1000
                }

                PropertyAnimation {
                    target: g_rectandle
                    properties: "width"
                    to: 80
                    duration: 1000
                    easing.type: Easing.Linear          //变化速率内部算子
                }
            }
        ]

        // 状态
        states: [
            State {
                name: "normal"
                PropertyChanges {
                    target: g_text
                    text: qsTr("鼠标未移入")
                }

                PropertyChanges {
                    target: g_rectandle
                    color: "red"
                }
            },
            State {
                name: "hovered"
                PropertyChanges {
                    target: g_text
                    text: qsTr("鼠标移入")
                }

                PropertyChanges {
                    target: g_rectandle
                    color: "yellow"
                }
            }
        ]

        Text {
            id: g_text
            anchors.centerIn: parent
            text: qsTr("鼠标未移入")
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                g_rectandle.state = "hovered"
            }

            onExited: {
                g_rectandle.state = "normal"
            }
        }
    }

}



