/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.08
描  述:	实现对图片的模糊
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
            text: qsTr("快速模糊")
        }

        Image {
            id: g_img_01
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height * 9 / 10)
            source: "/res/1.png"
        }

        FastBlur{
            anchors.fill: g_img_01
            source: g_img_01
            radius: 32
        }
    }

    Item {
        width: parent.width / 4
        height: parent.height / 3
        x: parent.width * 2 / 4

        Text {
            anchors.horizontalCenter: g_img_02.horizontalCenter
            anchors.top: g_img_02.bottom
            anchors.topMargin: 4
            font.bold: true
            text: qsTr("高斯模糊")
        }

        Image {
            id: g_img_02
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height * 9 / 10)
            source: "/res/1.png"
        }

        GaussianBlur{
            anchors.fill: g_img_02
            source: g_img_02
            deviation: 2
            radius: 8
            samples: 16
        }
    }


    Item {
        width: parent.width / 4
        height: parent.height / 3
        x: parent.width * 3 / 4

        Text {
            anchors.horizontalCenter: g_img_03.horizontalCenter
            anchors.top: g_img_03.bottom
            anchors.topMargin: 4
            font.bold: true
            text: qsTr("递归模糊")
        }

        Image {
            id: g_img_03
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height * 9 / 10)
            source: "/res/1.png"
        }

        RecursiveBlur{
            anchors.fill: g_img_03
            source: g_img_03
            radius: 7.5
            loops: 20
        }
    }

    Item {
        width: parent.width / 4
        height: parent.height / 3
        y: parent.height / 3

        Text {
            anchors.horizontalCenter: g_img_04.horizontalCenter
            anchors.top: g_img_04.bottom
            anchors.topMargin: 4
            font.bold: true
            text: qsTr("面罩模糊")
        }

        Image {
            id: g_img_04
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height * 9 / 10)
            source: "/res/1.png"
        }

        LinearGradient {
            id: g_mask
            anchors.fill: g_img_04
            gradient: Gradient {
                GradientStop { position: 0; color: "#ffffffff" }
                GradientStop { position: 1; color: "#00ffffff" }
            }
            start: Qt.point(0, 0)
            end: Qt.point(0, g_img_04.height)
            visible: false
        }

        MaskedBlur {
            anchors.fill: g_img_04
            source: g_img_04
            maskSource: g_mask
            radius: 16
            samples: 24
        }
    }


    Item {
        width: parent.width / 4
        height: parent.height / 3
        x: parent.width / 4
        y: parent.height / 3

        Text {
            anchors.horizontalCenter: g_img_05.horizontalCenter
            anchors.top: g_img_05.bottom
            anchors.topMargin: 4
            font.bold: true
            text: qsTr("运动模糊：方向模糊")
        }

        Image {
            id: g_img_05
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height * 9 / 10)
            source: "/res/1.png"
        }

        DirectionalBlur {
            anchors.fill: g_img_05
            source: g_img_05
            angle: 90
            samples: 24
            length: 32
        }
    }

    Item {
        width: parent.width / 4
        height: parent.height / 3
        x: parent.width * 2 / 4
        y: parent.height / 3

        Text {
            anchors.horizontalCenter: g_img_06.horizontalCenter
            anchors.top: g_img_06.bottom
            anchors.topMargin: 4
            font.bold: true
            text: qsTr("运动模糊：旋转模糊")
        }

        Image {
            id: g_img_06
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height * 9 / 10)
            source: "/res/1.png"
        }

        RadialBlur {
            anchors.fill: g_img_06
            source: g_img_06
            samples: 24
            angle: 15
        }
    }

    Item {
        width: parent.width / 4
        height: parent.height / 3
        x: parent.width * 3 / 4
        y: parent.height / 3

        Text {
            anchors.horizontalCenter: g_img_07.horizontalCenter
            anchors.top: g_img_07.bottom
            anchors.topMargin: 4
            font.bold: true
            text: qsTr("运动模糊：缩放模糊")
        }

        Image {
            id: g_img_07
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height * 9 / 10)
            source: "/res/1.png"
        }

        ZoomBlur {
            anchors.fill: g_img_07
            source: g_img_07
            samples: 24
            length: 48
        }
    }
}
