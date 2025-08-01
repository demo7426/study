/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.01
描  述:	拖拽事件系统
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

    DropArea{
        width: 200
        height: 200
        x: 200

        Rectangle{
            id: g_rectangle
            color: "cyan"
            anchors.fill: parent
        }

        onEntered: {
            g_rectangle.color = "pink"
        }

        onExited: {
            g_rectangle.color = "cyan"
        }
    }

    Rectangle{
        width: 40
        height: 40
        color: "blue"

        Drag.active: g_mouse_area.drag.active

        MouseArea{
            id: g_mouse_area
            drag.target: parent
            drag.axis: Drag.XAndYAxis

            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                parent.color = "blue"
            }

            onExited: {
                parent.color = "blue"
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



