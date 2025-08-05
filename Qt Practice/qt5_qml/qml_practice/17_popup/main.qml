/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.05
描  述:	popup窗口
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

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "white"

    Button{
        text: "打开"
        onClicked: {
            g_popup.open()
        }
    }

    Button{
        x: 300
        text: "关闭"
        onClicked: {
            g_popup.close()
        }
    }


    Popup{
        id: g_popup
        width: 600
        height: 300
        modal: false                                    //窗口为非模态窗口
        closePolicy: Popup.NoAutoClose                  //设置为无法自动关闭该窗口，必须手动关闭
        anchors.centerIn: parent
        background: Rectangle{
            anchors.fill: parent
            color: "red"
        }


        onAboutToHide: {
            console.log("About to hide...")
        }

        onAboutToShow: {
            console.log("About to show...")
        }

        onClosed: {
            console.log("Closed...")
        }

        onOpened: {
            console.log("Opened...")
        }
    }
}



