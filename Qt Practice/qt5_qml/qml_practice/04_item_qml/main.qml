/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.01
描  述:	qml基础控件之item，以及介绍一些Rectangle的常用属性
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
    }

    Rectangle{
        width: 100
        height: 100
        color: "red"
        x: 100
        y: 100
        z: 101              // 层级，层级高的会覆盖低的
    }

    Rectangle{
        width: 100
        height: 100
        color: "cyan"
        x: 140
        y: 100
        z: 102              // 层级，层级高的会覆盖低的

        visible: true
        scale: 1.5
        clip: true          // 启用了剪切功能，一个项目将把它自己的绘画以及它的子绘画剪切到它的边界矩形上
        rotation: 80        // 顺时针旋转
        opacity: 0.5        // 透明度

        Rectangle{
            width: 50
            height: 60
            color: "yellow"
            x: -10
        }
    }
}



