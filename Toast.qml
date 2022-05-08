import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.15
import QtQuick.Controls.Material.impl 2.15

Rectangle {
    id: root
    visible: false
    z: 999
    anchors.horizontalCenter: parent.horizontalCenter
    y: parent.height * 0.8
    width: parent.width * 0.8
    height: 30
    color: Material.backgroundColor
    radius: 4
    layer.enabled : true
    layer.effect: ElevationEffect {
        elevation: 1
        fullWidth: true
        fullHeight: true
    }
    Text {
        id: _text
        anchors.fill: parent
        font.pixelSize: 20
    }
    Timer {
        id: timer
        interval: 2000
        onTriggered: root.visible = false
    }
    Connections {
        target: toast
        function onToastSended(text) {
            _text.text = text
            root.visible = true
            timer.start()
        }
    }
}
