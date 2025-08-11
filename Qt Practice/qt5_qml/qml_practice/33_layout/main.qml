/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.11
描  述:	实现布局
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
import QtQuick.Layouts 1.14

Window {
    visible: true
    width: 1280
    height: 720
    title: qsTr("Hello World")

    // 1--行布局测试；2--列布局测试；3--网格布局测试；4--横向布局测试；5--纵向布局测试；6--网格布局测试
    readonly property int g_test_flag: 6

    Row{
        visible: g_test_flag === 1
        anchors.centerIn: parent
        spacing: 10
        layoutDirection: Qt.RightToLeft
        topPadding: 300

        Rectangle{
            width: 100
            height: 100
            color: "red"
        }

        Rectangle{
            width: 100
            height: 100
            color: "blue"
        }

        Rectangle{
            width: 100
            height: 100
            color: "green"
        }
    }

    Column{
        visible: g_test_flag === 2
        anchors.centerIn: parent
        spacing: 10
        topPadding: 300

        Rectangle{
            width: 100
            height: 100
            color: "red"
        }

        Rectangle{
            width: 100
            height: 100
            color: "blue"
        }

        Rectangle{
            width: 100
            height: 100
            color: "green"
        }
    }

    Grid{
        visible: g_test_flag === 3
        anchors.centerIn: parent
        spacing: 10
        columns: 2

        Rectangle{
            width: 100
            height: 100
            color: "red"
        }

        Rectangle{
            width: 100
            height: 100
            color: "blue"
        }

        Rectangle{
            width: 100
            height: 100
            color: "green"
        }
    }

    RowLayout{
        visible: g_test_flag === 4
        anchors.fill: parent
        spacing: 10

        Rectangle{
            color: "red"
            Layout.minimumWidth: 50
            Layout.minimumHeight: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Rectangle{
            color: "blue"
            Layout.minimumWidth: 50
            Layout.minimumHeight: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Rectangle{
            color: "green"
            Layout.minimumWidth: 50
            Layout.minimumHeight: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    ColumnLayout{
        visible: g_test_flag === 5
        anchors.fill: parent
        spacing: 10

        Rectangle{
            color: "red"
            Layout.minimumWidth: 50
            Layout.minimumHeight: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Rectangle{
            color: "blue"
            Layout.minimumWidth: 50
            Layout.minimumHeight: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Rectangle{
            color: "green"
            Layout.minimumWidth: 50
            Layout.minimumHeight: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    GridLayout{
        visible: g_test_flag === 6
        anchors.fill: parent
        columnSpacing: 10
        rowSpacing: 10
        columns: 2

        Rectangle{
            color: "red"
            Layout.minimumWidth: 50
            Layout.minimumHeight: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Rectangle{
            color: "blue"
            Layout.minimumWidth: 50
            Layout.minimumHeight: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Rectangle{
            color: "green"
            Layout.minimumWidth: 50
            Layout.minimumHeight: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
