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

    ParallelAnimation{
        id: g_parall_ani

        PropertyAnimation{
            target: g_rectandle
            properties: "width"
            from: 80
            to: 400
            duration: 1000
            easing.type: Easing.Linear          //变化速率内部算子
        }

        PropertyAnimation{
            target: g_rectandle
            properties: "height"
            from: 40
            to: 400
            duration: 1000
            easing.type: Easing.Linear          //变化速率内部算子
        }

        PropertyAnimation{
            target: g_rectandle
            properties: "color"
            from: "red"
            to: "yellow"
            duration: 1000
            easing.type: Easing.Linear          //变化速率内部算子
        }

        ScriptAction{
            script: {
                console.log("并行动画启动")
            }
        }
    }

    SequentialAnimation{
        id: g_seq_ani

        PropertyAnimation{                      //重置状态
            target: g_rectandle
            properties: "width"
            to: 80
            duration: 1
        }

        PropertyAnimation{                      //重置状态
            target: g_rectandle
            properties: "height"
            to: 40
            duration: 1
        }

        PropertyAnimation{                      //重置状态
            target: g_rectandle
            properties: "color"
            to: "red"
            duration: 1
        }

        PropertyAnimation{
            target: g_rectandle
            properties: "width"
            from: 80
            to: 400
            duration: 1000
            easing.type: Easing.Linear          //变化速率内部算子
        }

        PropertyAnimation{
            target: g_rectandle
            properties: "height"
            from: 40
            to: 400
            duration: 1000
            easing.type: Easing.Linear          //变化速率内部算子
        }

        PropertyAnimation{
            target: g_rectandle
            properties: "color"
            from: "red"
            to: "yellow"
            duration: 1000
            easing.type: Easing.Linear          //变化速率内部算子
        }

        ScriptAction{
            script: {
                console.log("串行动画结束")
            }
        }
    }

    Rectangle{
        id: g_rectandle
        width: 80
        height: 40
        color: "red"
        anchors.centerIn: parent
        state: "normal"                     //显示设置初始状态为normal，保证第一次鼠标移入时的动画效果

        Text {
            id: g_text
            anchors.centerIn: parent
            text: qsTr("鼠标未移入")
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                g_text.text = qsTr("鼠标移入")
                g_seq_ani.stop()
                g_seq_ani.start()
            }

            onExited: {
                g_text.text = qsTr("鼠标未移入")
                g_seq_ani.stop()
            }
        }
    }

}



