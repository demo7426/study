/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.01
描  述:	普通按钮
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

    Button{
        width: 100
        height: 50
        text: qsTr("按钮")
        anchors.centerIn: parent
        display: AbstractButton.TextUnderIcon
        icon.source: "/res/StartCapture.png"

        onClicked: console.log("按钮被单击")
        onDoubleClicked: console.log("按钮被双击")
        onCanceled: console.log("按钮被取消")
        onPressed: console.log("按钮被按下")
        onReleased: console.log("按钮被释放")
    }

}



