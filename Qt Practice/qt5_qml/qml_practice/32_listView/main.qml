/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.11
描  述:	实现列表
备  注:
修改记录:

  1.  日期: 2025.08.11
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

    ListModel{
        id: g_listModel
        ListElement{ name: "赵一"; age: 10 }
        ListElement{ name: "赵一"; age: 10 }
        ListElement{ name: "钱二"; age: 11 }
        ListElement{ name: "钱二"; age: 11 }
        ListElement{ name: "孙三"; age: 12 }
        ListElement{ name: "孙三"; age: 12 }
        ListElement{ name: "李四"; age: 13 }
        ListElement{ name: "李四"; age: 13 }
        ListElement{ name: "赵一"; age: 10 }
        ListElement{ name: "赵一"; age: 10 }
        ListElement{ name: "钱二"; age: 11 }
        ListElement{ name: "钱二"; age: 11 }
        ListElement{ name: "孙三"; age: 12 }
        ListElement{ name: "孙三"; age: 12 }
        ListElement{ name: "李四"; age: 13 }
        ListElement{ name: "李四"; age: 13 }
        ListElement{ name: "赵一"; age: 10 }
        ListElement{ name: "赵一"; age: 10 }
        ListElement{ name: "钱二"; age: 11 }
        ListElement{ name: "钱二"; age: 11 }
        ListElement{ name: "孙三"; age: 12 }
        ListElement{ name: "孙三"; age: 12 }
        ListElement{ name: "李四"; age: 13 }
        ListElement{ name: "李四"; age: 13 }
        ListElement{ name: "赵一"; age: 10 }
        ListElement{ name: "赵一"; age: 10 }
        ListElement{ name: "钱二"; age: 11 }
        ListElement{ name: "钱二"; age: 11 }
        ListElement{ name: "孙三"; age: 12 }
        ListElement{ name: "孙三"; age: 12 }
        ListElement{ name: "李四"; age: 13 }
        ListElement{ name: "李四"; age: 13 }
    }

    ListView{
        id: g_listView
        anchors.fill: parent
        anchors.rightMargin: 208
        model: g_listModel
        spacing: 4
        headerPositioning: ListView.OverlayHeader       //固定表头
        footerPositioning: ListView.OverlayFooter       //固定表尾

        // 设置添加数据的动画效果
        add:Transition {
            NumberAnimation{ properties: "y"; duration: 300 }
        }
        addDisplaced:Transition {
            NumberAnimation{ properties: "y"; duration: 300 }
        }

        // 设置删除数据的动画效果
        remove:Transition {
            NumberAnimation{ properties: "opacity"; from:1; to:0; duration: 300 }
        }
        removeDisplaced:Transition {
            NumberAnimation{ properties: "y"; duration: 300 }
        }

        // 设置区段标签
        section{
            property: "name"
            labelPositioning: ViewSection.CurrentLabelAtStart
            criteria: ViewSection.FirstCharacter
            delegate: Rectangle {
                height: 50
                width: 50
                radius: 25
                Text{
                    anchors.centerIn: parent
                    text: section
                }
            }
        }

        // 高亮显示
        highlight: Item {
            width: parent.width
            height: 50
            z: 2

            // 设置高亮文本显示内容
            function set_text(name, age) {
                g_high_light_name_text.text = name
                g_high_light_age_text.text = age
            }

            Rectangle{
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 2 - 2
                color: "cyan"

                Text{
                    id: g_high_light_name_text
                    anchors.centerIn: parent
                    font.pixelSize: 30
                }
            }

            Rectangle{
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 2 - 2
                color: "cyan"

                Text{
                    id: g_high_light_age_text
                    anchors.centerIn: parent
                    font.pixelSize: 30
                }
            }
        }

        // 表头
        header: Item {
            width: parent.width
            height: 50
            z: 3

            Rectangle{
                id: g_left_header_rectangle
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 2 - 2
                color: "darkturquoise"
                border.color: "yellow"
                border.width: 1

                Text {
                    anchors.centerIn: parent
                    font.pixelSize: 30
                    text: qsTr("姓名")
                }
            }

            Rectangle{
                id: g_right_header_rectangle
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 2 - 2
                color: "darkturquoise"
                border.color: "yellow"
                border.width: 1

                Text {
                    anchors.centerIn: parent
                    font.pixelSize: 30
                    text: qsTr("年龄")
                }
            }
        }

        // 表尾
        footer: Rectangle{
            width: parent.width
            height: 50
            color: "dodgerblue"
            border.color: "yellow"
            border.width: 1
            z: 3

            Text {
                anchors.centerIn: parent
                font.pixelSize: 30
                text: qsTr("表尾")
            }
        }

        //委托
        delegate: Rectangle{
            width: parent.width
            height: 50

            Rectangle{
                id: g_left_rectangle
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 2 - 2
                color: "red"
                border.color: "yellow"
                border.width: 1

                Text{
                    anchors.centerIn: parent
                    font.pixelSize: 30
                    text: name
                }
            }

            Rectangle{
                id: g_right_rectangle
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 2 - 2
                color: "red"
                border.color: "yellow"
                border.width: 1

                Text{
                    anchors.centerIn: parent
                    font.pixelSize: 30
                    text: age
                }
            }

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    g_listView.currentIndex = index
                    g_listView.highlightItem.set_text(name, age)        // 设置高亮文本显示内容
                }
            }
        }
    }

    //插入按钮
    Button {
        id: g_insert_btn
        anchors.left: g_listView.right
        anchors.top: g_listView.top
        anchors.leftMargin: 4
        width: 200
        height: 50

        text: qsTr("插入数据")

        onClicked: {
            g_listModel.insert(g_listView.currentIndex, { name: qsTr("xxx") + g_listModel.count, age: g_listModel.count % 80 })
        }
    }

    //删除按钮
    Button {
        anchors.left: g_listView.right
        anchors.top: g_insert_btn.bottom
        anchors.topMargin: 4
        anchors.leftMargin: 4
        width: 200
        height: 50

        text: qsTr("删除数据")

        onClicked: {
            g_listModel.remove(g_listView.currentIndex)
        }
    }
}
