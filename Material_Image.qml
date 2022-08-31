import QtQuick 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls.Material.impl 2.15
import QtQuick.Controls 6.2
import Qt5Compat.GraphicalEffects

Image {
    id: control
    property double radius: 0
    property bool elevated: false
    property int elevation: 0
    property bool roundLeftTop: true
    property bool roundRightTop: true
    property bool roundLeftBottom: true
    property bool roundRightBottom: true
    layer.enabled: true
    layer.effect: OpacityMask {
        maskSource: Rectangle {
            width: control.width
            height: control.height
            radius: control.radius
            Rectangle {
                anchors.left: parent.left
                anchors.top: parent.top
                visible: !control.roundLeftTop
                width: control.radius * 2
                height: control.radius * 2
            }
            Rectangle {
                anchors.right: parent.right
                anchors.top: parent.top
                visible: !control.roundRightTop
                width: control.radius * 2
                height: control.radius * 2
            }
            Rectangle {
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                visible: !control.roundLeftBottom
                width: control.radius * 2
                height: control.radius * 2
            }
            Rectangle {
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                visible: !control.roundRightBottom
                width: control.radius * 2
                height: control.radius * 2
            }
        }
        layer.enabled: control.elevated
        layer.effect: ElevationEffect {
            elevation: control.elevation
        }
    }
}
