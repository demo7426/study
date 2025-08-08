/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.08
描  述:	实现颜色覆盖、图片混合
备  注:
修改记录:

  1.  日期: 2025.08.08
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/


import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.14
import QtQuick.Controls 1.4
import QtQml 2.14

Window {
    visible: true
    width: 1280
    height: 720
    title: qsTr("Hello World")

    Item {
        width: parent.width / 4
        height: parent.height / 3

        Text {
            anchors.horizontalCenter: g_img_00.horizontalCenter
            anchors.top: g_img_00.bottom
            anchors.topMargin: 4
            font.bold: true
            text: qsTr("原图")
        }

        Image {
            id: g_img_00
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height * 9 / 10)
            source: "/res/1.png"
        }
    }

    Item {
        width: parent.width / 4
        height: parent.height / 3
        x: parent.width / 4

        Text {
            anchors.horizontalCenter: g_img_01.horizontalCenter
            anchors.top: g_img_01.bottom
            anchors.topMargin: 4
            font.bold: true
            text: qsTr("原图")
        }

        Image {
            id: g_img_01
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height * 9 / 10)
            source: "/res/2.png"
        }
    }

    Item {
        width: parent.width / 4
        height: parent.height / 3
        y: parent.height / 3

        Text {
            anchors.horizontalCenter: g_img_02.horizontalCenter
            anchors.top: g_img_02.bottom
            anchors.topMargin: 4
            font.bold: true
            text: qsTr("颜色覆盖")
        }

        Image {
            id: g_img_02
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height * 9 / 10)
            source: "/res/1.png"
        }

        ColorOverlay {
            anchors.fill: g_img_02
            source: g_img_02
            color: "#80800000"
        }
    }

    Item {
        width: parent.width / 4
        height: parent.height / 3
        x: parent.width / 4
        y: parent.height / 3

        Text {
            anchors.horizontalCenter: g_img_03.horizontalCenter
            anchors.top: g_img_03.bottom
            anchors.topMargin: 4
            font.bold: true
            text: qsTr("图片混合")
        }

        Image {
            id: g_img_03
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height * 9 / 10)
            source: "/res/1.png"
        }

        Blend {
            anchors.fill: g_img_03
            source: g_img_03
            foregroundSource: g_img_01
            mode: average                       //混合模式
        }
    }
}
