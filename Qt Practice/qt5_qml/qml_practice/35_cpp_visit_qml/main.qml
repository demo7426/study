/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.12
描  述:	实现cpp-组件相互访问数据
备  注:
修改记录:

  1.  日期: 2025.08.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.14
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQml 2.14
import QtQuick.Layouts 1.14
import CTest 1.0

Window {
    visible: true
    width: 1280
    height: 720
    title: qsTr("Hello World")

    CTest{
        id: g_test
    }

    Button{
        objectName: "g_btn_name"
        width: 100
        height: 100

        signal sig()

        onSig: {
            console.log("onSig is called.")
        }

        function test_arg(arg){
            console.log("qml: " + arg)
            return "recieve"
        }

        // 通过 style 属性自定义样式
        style: ButtonStyle{
            background: Rectangle{
                anchors.fill: parent
                radius: 10

                // 优先级：按下状态 > 悬停状态 > 正常状态
                color: control.pressed ? "blue"    // 按下时变蓝
                       : control.hovered ? "red"  // 悬停时变红
                       : "green"                  // 正常时为绿

                Text {
                    id: g_text
                    anchors.centerIn: parent
                    text: g_test.strName

                    Component.onCompleted: {
                        g_test.setStrName("确认")
                    }
                }
            }
        }

        onClicked: {
            console.log("按钮被单击了")
        }
    }
}
