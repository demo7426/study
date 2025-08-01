/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.01
描  述:	item、rectangle互相嵌套
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

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "gray"

    Item {
        width: 100
        height: 100

        clip: true
        anchors.centerIn: parent

        Rectangle{
            width: 100
            height: 100
            color: "red"
            radius: 20
            x: 20
            y: 20
        }
    }
}



