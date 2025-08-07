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

    readonly property int g_test_flag: 4        //1--hls图片表面着色测试；2--饱和度测试；3--伽马调整测试；4--hls直接修改图片测试

    Item {
        width: parent.width / 4
        height: parent.height
        //visible: g_test_flag === 1

        Text {
            anchors.horizontalCenter: g_img.horizontalCenter
            anchors.top: g_img.bottom
            anchors.topMargin: 20

            font.pixelSize: 18
            font.bold: true

            text: qsTr("图片表面着色测试")
        }

        Text {
            anchors.right: g_slider_hue.left
            anchors.verticalCenter: g_slider_hue.verticalCenter
            text: qsTr("色调：") + g_slider_hue.value.toFixed(1)
        }

        Slider{
            id: g_slider_hue
            x: (parent.width - width) / 2
            y: 20
            width: parent.width / 3

            minimumValue: 0
            maximumValue: 1
            value: g_colorize.hue

            onValueChanged: {
                g_colorize.hue = value
            }
        }

        Text {
            anchors.right: g_slider_lightness.left
            anchors.verticalCenter: g_slider_lightness.verticalCenter
            text: qsTr("亮度：") + g_slider_lightness.value.toFixed(1)
        }

        Slider{
            id: g_slider_lightness
            x: (parent.width - width) / 2
            y: g_slider_hue.y + 40
            width: parent.width / 3

            minimumValue: -1
            maximumValue: 1
            value: g_colorize.lightness

            onValueChanged: {
                g_colorize.lightness = value
            }
        }

        Text {
            anchors.right: g_slider_saturation.left
            anchors.verticalCenter: g_slider_saturation.verticalCenter
            text: qsTr("饱和度：") + g_slider_saturation.value.toFixed(1)
        }

        Slider{
            id: g_slider_saturation
            x: (parent.width - width) / 2
            y: g_slider_lightness.y + 40
            width: parent.width / 3

            minimumValue: 0
            maximumValue: 1
            value: g_colorize.saturation

            onValueChanged: {
                g_colorize.saturation = value
            }
        }

        Image {
            id: g_img
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height / 2)
            source: "/res/1.png"
        }

        //着色 hsl
        Colorize{
            id: g_colorize
            anchors.fill: g_img
            source: g_img
            hue: 0                  //色调；0~1
            lightness: 0            //亮度；-1~1
            saturation: 1           //饱和度；0~1
        }
    }

    Item {
        width: parent.width / 4
        height: parent.height

        x: parent.width / 4

        //visible: g_test_flag === 2

        Text {
            anchors.horizontalCenter: g_img_01.horizontalCenter
            anchors.top: g_img_01.bottom
            anchors.topMargin: 20

            font.pixelSize: 18
            font.bold: true

            text: qsTr("饱和度测试")
        }

        Text {
            anchors.right: g_slider_desaturate.left
            anchors.verticalCenter: g_slider_desaturate.verticalCenter
            text: qsTr("饱和度：") + g_slider_desaturate.value.toFixed(1)
        }

        Slider{
            id: g_slider_desaturate
            x: (parent.width - width) / 2
            y: 20
            width: parent.width / 3

            minimumValue: 0
            maximumValue: 1
            value: g_desaturate.desaturation

            onValueChanged: {
                g_desaturate.desaturation = value
            }
        }

        Image {
            id: g_img_01
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height / 2)
            source: "/res/1.png"
        }

        //饱和度
        Desaturate{
            id: g_desaturate
            anchors.fill: g_img_01
            source: g_img_01
            desaturation: 0             //饱和度;0~1
        }
    }

    Item {
        width: parent.width / 4
        height: parent.height

        x: parent.width / 4 * 2

        Text {
            anchors.horizontalCenter: g_img_02.horizontalCenter
            anchors.top: g_img_02.bottom
            anchors.topMargin: 20

            font.pixelSize: 18
            font.bold: true

            text: qsTr("伽马系数调整测试")
        }

        Text {
            anchors.right: g_slider_gamma_adjust.left
            anchors.verticalCenter: g_slider_gamma_adjust.verticalCenter
            text: qsTr("伽马调整系数：") + g_slider_gamma_adjust.value.toFixed(1)
        }

        Slider{
            id: g_slider_gamma_adjust
            x: (parent.width - width) / 2
            y: 20
            width: parent.width / 3

            minimumValue: 0
            maximumValue: 2
            value: g_gamma_adjust.gamma

            onValueChanged: {
                g_gamma_adjust.gamma = value
            }
        }

        Image {
            id: g_img_02
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height / 2)
            source: "/res/1.png"
        }

        GammaAdjust{
            id: g_gamma_adjust
            anchors.fill: g_img_02
            source: g_img_02
            gamma: 1
        }
    }

    Item {
        width: parent.width / 4
        height: parent.height

        x: parent.width / 4 * 3

        Text {
            anchors.horizontalCenter: g_img_03.horizontalCenter
            anchors.top: g_img_03.bottom
            anchors.topMargin: 20

            font.pixelSize: 18
            font.bold: true

            text: qsTr("hls直接修改图片测试")
        }

        Text {
            anchors.right: g_slider_hue_01.left
            anchors.verticalCenter: g_slider_hue_01.verticalCenter
            text: qsTr("色调：") + g_slider_hue_01.value.toFixed(1)
        }

        Slider{
            id: g_slider_hue_01
            x: (parent.width - width) / 2
            y: 20
            width: parent.width / 3

            minimumValue: -1
            maximumValue: 1
            value: g_hue_saturation.hue

            onValueChanged: {
                g_hue_saturation.hue = value
            }
        }

        Text {
            anchors.right: g_slider_lightness_01.left
            anchors.verticalCenter: g_slider_lightness_01.verticalCenter
            text: qsTr("亮度：") + g_slider_lightness_01.value.toFixed(1)
        }

        Slider{
            id: g_slider_lightness_01
            x: (parent.width - width) / 2
            y: g_slider_hue_01.y + 40
            width: parent.width / 3

            minimumValue: -1
            maximumValue: 1
            value: g_hue_saturation.lightness

            onValueChanged: {
                g_hue_saturation.lightness = value
            }
        }

        Text {
            anchors.right: g_slider_saturation_01.left
            anchors.verticalCenter: g_slider_saturation_01.verticalCenter
            text: qsTr("饱和度：") + g_slider_saturation_01.value.toFixed(1)
        }

        Slider{
            id: g_slider_saturation_01
            x: (parent.width - width) / 2
            y: g_slider_lightness_01.y + 40
            width: parent.width / 3

            minimumValue: -1
            maximumValue: 1
            value: g_hue_saturation.saturation

            onValueChanged: {
                g_hue_saturation.saturation = value
            }
        }

        Image {
            id: g_img_03
            anchors.centerIn: parent
            sourceSize: Qt.size(parent.width * 9 / 10, parent.height / 2)
            source: "/res/1.png"
        }

        HueSaturation{
            id: g_hue_saturation
            anchors.fill: g_img_03
            source: g_img_03
            hue: 0                  //色调；-1~1
            lightness: 0            //亮度；-1~1
            saturation: 0           //饱和度；-1~1
        }
    }
}
