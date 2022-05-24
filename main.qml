import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Window {
    id: window
    width: 320
    height: 640
    visible: true
    title: "IDv3 editor"
    Material.theme: Material.Light
    Android_ui {
    anchors.fill: parent
    }
}
