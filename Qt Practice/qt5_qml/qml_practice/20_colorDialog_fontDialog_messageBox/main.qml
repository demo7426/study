/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.05
描  述:	颜色、字体选择窗口，消息窗口
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
        text: "颜色窗口"
        onClicked: {
            g_color_dialog.open()
        }
    }

    Button{
        x: 200
        text: "字体窗口"
        onClicked: {
            g_font_dialog.open()
        }
    }

    Button{
        x: 400
        text: "消息窗口"
        onClicked: {
            g_msg_dialog.open()
        }
    }

    ColorDialog{
        id: g_color_dialog
        onAccepted: {
            console.log(currentColor)
        }
    }

    FontDialog{
        id: g_font_dialog
        onAccepted: {
            console.log(currentFont.bold, currentFont.family)
        }
    }

    MessageDialog{
        id: g_msg_dialog
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        text: qsTr("这是一个消息对话框")
    }

}



