/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.01
描  述:	TextField单行输入框
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

    TextField{
        width: 400
        height: 50
        font.family: "宋体"
        font.pixelSize: 30
        placeholderText: "请输入密码"
        echoMode: TextInput.Password
        selectByMouse: true                                 // 是否可以被鼠标选中
        maximumLength: 4                                    // 最大字符数量
        horizontalAlignment: TextInput.AlignHCenter         // 对齐方式

        background: Rectangle{
            anchors.fill: parent
            border.color: "red"
            border.width: 1
            color: "yellow"
            radius: 20
        }
    }
}



