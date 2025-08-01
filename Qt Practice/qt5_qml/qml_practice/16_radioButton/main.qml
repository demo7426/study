/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.01
描  述:	单选按钮
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
    color: "white"

    ButtonGroup{
        id: g_btn_grop
        exclusive: false
    }

    RadioButton{
        y: 40
        text: qsTr("苹果")
        ButtonGroup.group: g_btn_grop

        onCheckedChanged: {
            checked? console.log(text, "被选中了"): console.log(text, "取消选中")
        }
    }

    RadioButton{
        y: 80
        text: qsTr("香蕉")
        ButtonGroup.group: g_btn_grop

        onCheckedChanged: {
            checked? console.log(text, "被选中了"): console.log(text, "取消选中")
        }
    }

    RadioButton{
        y: 120
        text: qsTr("荔枝")
        ButtonGroup.group: g_btn_grop

        onCheckedChanged: {
            checked? console.log(text, "被选中了"): console.log(text, "取消选中")
        }
    }

    Item {
        RadioButton{
            y: 220
            text: qsTr("自动化控制")

            onCheckedChanged: {
                checked? console.log(text, "被选中了"): console.log(text, "取消选中")
            }
        }

        RadioButton{
            y: 260
            text: qsTr("通信工程")

            onCheckedChanged: {
                checked? console.log(text, "被选中了"): console.log(text, "取消选中")
            }
        }

    }
}



