/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.07
描  述:	实现颜色渐变
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

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle{
        id: g_rectangle
        width: 400
        height: 300
        anchors.centerIn: parent

        //普通渐变
//        gradient: Gradient{
//            orientation: Gradient.Horizontal
//            GradientStop { position: 0.0; color: "red" }
//            GradientStop { position: 0.33; color: "yellow" }
//            GradientStop { position: 1.0; color: "green" }
//        }
    }

    //线性渐变
//    LinearGradient{
//        anchors.fill: g_rectangle
//        source: g_rectangle             //必须指定待填充的源对象
//        start: Qt.point(0, 0)
//        end: Qt.point(g_rectangle.width, g_rectangle.height)

//        gradient: Gradient {
//            GradientStop {
//                   position: 0.000
//                   color: Qt.rgba(1, 0, 0, 1)
//                }
//                GradientStop {
//                   position: 0.167
//                   color: Qt.rgba(1, 1, 0, 1)
//                }
//                GradientStop {
//                   position: 0.333
//                   color: Qt.rgba(0, 1, 0, 1)
//                }
//                GradientStop {
//                   position: 0.500
//                   color: Qt.rgba(0, 1, 1, 1)
//                }
//                GradientStop {
//                   position: 0.667
//                   color: Qt.rgba(0, 0, 1, 1)
//                }
//                GradientStop {
//                   position: 0.833
//                   color: Qt.rgba(1, 0, 1, 1)
//                }
//                GradientStop {
//                   position: 1.000
//                   color: Qt.rgba(1, 0, 0, 1)
//                }
//          }
//    }

    //锥形渐变
//    ConicalGradient{
//        anchors.fill: g_rectangle
//        source: g_rectangle             //必须指定待填充的源对象
//        angle: 45
//        gradient: Gradient {
//            GradientStop { position: 0.0; color: "white" }
//            GradientStop { position: 1.0; color: "black" }
//        }
//    }

    //辐射渐变
    RadialGradient{
        anchors.fill: g_rectangle
        horizontalRadius: 200
        verticalRadius: 150
        gradient: Gradient {
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 1; color: "black" }
        }
    }

}
