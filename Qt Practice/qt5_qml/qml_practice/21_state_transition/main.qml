/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.05
描  述:	实现状态过渡，以及颜色动画效果
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
        width: 120
        height: 40
        color: "red"
        anchors.centerIn: parent

        // 过渡效果
        transitions: [
            Transition {
                from: "normal"
                to: "hovered"

                ColorAnimation {
                    target: g_rectandle
                    duration: 2000
                }
            },
            Transition {
                from: "hovered"
                to: "normal"

                ColorAnimation {
                    target: g_rectandle
                    duration: 2000
                }
            }
        ]

        // 状态
        states: [
            State {
                name: "normal"
                PropertyChanges {
                    target: g_rectandle
                    color: "red"
                }

                PropertyChanges {
                    target: g_text
                    text: qsTr("鼠标未移入")
                }

                PropertyChanges {
                    target: g_rectandle
                    width: 120
                }
            },
            State {
                name: "hovered"
                PropertyChanges {
                    target: g_rectandle
                    color: "yellow"
                }

                PropertyChanges {
                    target: g_text
                    text: qsTr("鼠标移入")
                }

                PropertyChanges {
                    target: g_rectandle
                    width: 80
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



