/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.qml
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.12
描  述:	实现自定义组件
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
import "./custom_component"

Window {
    visible: true
    width: 1280
    height: 720
    title: qsTr("Hello World")

    Column{
        spacing: 5

        MyButton{

        }

        MyButton{
            height: 50
        }

        MyRectangle{
            height: 200
        }
    }
}
