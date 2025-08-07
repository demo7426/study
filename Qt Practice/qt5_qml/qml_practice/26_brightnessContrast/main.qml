/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.07
描  述:	实现亮度、对比度
备  注:
修改记录:

  1.  日期: 2025.08.07
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

    Text {
        anchors.right: g_slider_brightness.left
        anchors.verticalCenter: g_slider_brightness.verticalCenter
        text: qsTr("亮度：") + g_slider_brightness.value.toFixed(1)
    }

    Slider{
        id: g_slider_brightness
        x: (parent.width - width) / 2
        y: 20
        width: parent.width / 3

        minimumValue: -1
        maximumValue: 1
        value: 0

        onValueChanged: {
            g_bri_con.brightness = value
        }
    }

    Text {
        anchors.right: g_slider_contrast.left
        anchors.verticalCenter: g_slider_contrast.verticalCenter
        text: qsTr("对比度：") + g_slider_contrast.value.toFixed(1)
    }

    Slider{
        id: g_slider_contrast
        x: (parent.width - width) / 2
        y: g_slider_brightness.y + 40
        width: parent.width / 3

        minimumValue: -1
        maximumValue: 1
        value: 0

        onValueChanged: {
            g_bri_con.contrast = value
        }
    }

    Image {
        id: g_img
        anchors.centerIn: parent
        sourceSize: Qt.size(parent.width / 2, parent.height / 2)
//        scale: 0.2
        source: "/res/1.png"
    }

    BrightnessContrast{
        id: g_bri_con
        anchors.fill: g_img
        source: g_img
        brightness: 0           //亮度；-1~1
        contrast: 0             //对比度：-1~1
    }

}
