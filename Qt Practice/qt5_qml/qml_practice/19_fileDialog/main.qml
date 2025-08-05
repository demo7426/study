/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.05
描  述:	文件/文件夹选择窗口
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
        text: "选择文件"
        onClicked: {
            g_file_dialog.open()
        }
    }

    Button{
        x: 300
        text: "选择文件夹"
        onClicked: {
            g_folder_dialog.open()
        }
    }

    FileDialog{
        id: g_file_dialog
        title: qsTr("请选择文件")

        nameFilters: [
            qsTr("文本文件 (*.txt)"),
            qsTr("所有文件 (*)")
        ]

        onAccepted: {
            console.log("选中的文件：" + fileUrl)
        }
    }

    FileDialog{
        id: g_folder_dialog
        title: qsTr("请选择文件夹")
        selectFolder: true                          // 设置为选择文件夹模式

        onAccepted: {
            console.log("选中的文件夹：" + fileUrl)
        }
    }
}



