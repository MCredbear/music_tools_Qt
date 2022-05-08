import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.15

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: "IDv3 editor"
    Material.theme: Material.Light
    Toast {
        id: t
    }
    Component.onCompleted: {
        name.text = editor.getName()
        artist.text = editor.getArtist()
        album.text = editor.getAlbum()
        editor.getCover()
        cover.source = "image://coverImageProvider/cover"
    }
    ToolBar {
        id: topToolBar
        z: 10
        anchors.top: parent.top
        width: parent.width
    }
    Flickable {
        anchors.top: topToolBar.bottom
        anchors.bottom: parent.bottom
        width: parent.width
        Rectangle {
            y: 20
            anchors.left: parent.left
            anchors.leftMargin: 25
            anchors.right: parent.right
            anchors.rightMargin: 25
            height: cover.height

            Image {
                id: cover
                anchors.left: parent.left 
                width: window.width / 2.5
                height: width
                cache: false
            }
            Column {
                anchors.right: parent.right 
                anchors.left: cover.right 
                anchors.leftMargin: 25
                Button {
                    id: replaceCoverButton
                    width: parent.width
                    height: cover.height / 3
                    onReleased: {
                        toast.sendToast("233")
                    }
                }
                Button {
                    id: removeCoverButton
                    width: parent.width
                    height: cover.height / 3
                }
            }
        }
    }

    Text {
        id: name
        height: 20
        x: 0
        y: 0
    }
    Text {
        id: artist
        height: 20
        x: 0
        y: 20
    }
    Text {
        id: album
        height: 20
        x: 0
        y: 40
    }
}
