import QtQuick 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls.Material.impl 2.15
import QtQuick.Controls 6.2
import Qt5Compat.GraphicalEffects

Rectangle {
        id: control
        radius: 4
        property bool elevated: true
        property int elevation: 8
        property bool roundLeftTop: true
        property bool roundRightTop: true
        property bool roundLeftBottom: true
        property bool roundRightBottom: true
        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            visible: !control.roundLeftTop
            width: control.radius * 2
            height: control.radius * 2
            color: control.color
        }
        Rectangle {
            anchors.right: parent.right
            anchors.top: parent.top
            visible: !control.roundRightTop
            width: control.radius * 2
            height: control.radius * 2
            color: control.color
        }
        Rectangle {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            visible: !control.roundLeftBottom
            width: control.radius * 2
            height: control.radius * 2
            color: control.color
        }
        Rectangle {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            visible: !control.roundRightBottom
            width: control.radius * 2
            height: control.radius * 2
            color: control.color
        }
        layer.enabled: control.elevated
        layer.effect: ElevationEffect {
            elevation: control.elevation
        }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
