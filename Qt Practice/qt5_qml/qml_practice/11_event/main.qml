/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.01
描  述:	事件系统
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
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "gray"

    Rectangle{
        id: g_rectangle
        width: 100
        height: 100
        color: "cyan"
        x: 100
        y: 100

        focus: true
        Keys.onPressed:{
            if(event.key === Qt.Key_A)
                console.log("a键被按下")
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                parent.color = "yellow"
            }

            onEntered: {
                parent.color = "red"
            }

            onExited: {
                parent.color = "cyan"
            }

            onWheel: {
                if(wheel.angleDelta.y > 0){
                    console.log("鼠标向前滚动")
                }else{
                    console.log("鼠标向后滚动")
                }
            }
        }
    }

}



