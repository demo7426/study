/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.05
描  述:	dialog窗口
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
            g_dialog.open()
        }
    }

    Button{
        x: 300
        text: "关闭"
        onClicked: {
            g_dialog.close()
        }
    }

    Dialog{
        id: g_dialog
        title: qsTr("标准对话框")
        width: 300
        height: 200
        anchors.centerIn: parent
        modal: false                                    //窗口为非模态窗口
        closePolicy: Popup.NoAutoClose                  //设置为无法自动关闭该窗口，必须手动关闭

        Label{
            text: qsTr("这是Qt 5.12.4中的对话框")
            anchors.centerIn: parent
        }

        // 手动添加按钮（指定角色）
        footer: DialogButtonBox {
            Button {
                text: qsTr("确定")
                DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
                onClicked: {
                    console.log("确定被点击")
                    g_dialog.close()
                }
            }

            Button {
                text: qsTr("取消")
                DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
                onClicked: {
                    console.log("取消被点击")
                    g_dialog.close()
                }
            }
        }
    }
}



