import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Button{
    width: 100
    height: 100

    // 通过 style 属性自定义样式
    style: ButtonStyle{
        background: Rectangle{
            id: g_btn_style
            anchors.fill: parent
            radius: 10

            // 优先级：按下状态 > 悬停状态 > 正常状态
            color: control.pressed ? "blue"    // 按下时变蓝
                   : control.hovered ? "red"  // 悬停时变红
                   : "green"                  // 正常时为绿
        }
    }

    onClicked: {
        console.log("按钮被单击了")
    }
}
