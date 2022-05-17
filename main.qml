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
    Toast {}
    Component.onCompleted: {
        name.text = editor.getName()
        artist.text = editor.getArtist()
        album.text = editor.getAlbum()
        editor.getCover()
        cover.source = "image://coverImageProvider/cover"
        console.log(editor.getLyric())
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
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 25
            anchors.right: parent.right
            anchors.rightMargin: 25
            height: parent.height
            Rectangle {
                width: 1
                height: 20
                color: "transparent"
            }
            Rectangle {
                width: parent.width
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
                    }
                    Button {
                        id: removeCoverButton
                        width: parent.width
                        height: cover.height / 3
                    }
                    Button {
                        id: exportCoverButton
                        width: parent.width
                        height: cover.height / 3
                    }
                }
            }
            Item {
                width: parent.width
                height: 40
                Text {
                    y: 0
                    width: parent.width
                    height: 20
                    text: qsTr("歌曲名称")
                    color: Material.primaryColor
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.primaryColor
                    }
                }
                TextInput {
                    id: name
                    y: 20
                    width: parent.width
                    height: 20
                    clip: true
                }
                Rectangle {
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: 2
                    color: Material.accentColor
                }
            }
            Item {
                width: parent.width
                height: 40
                Text {
                    y: 0
                    width: parent.width
                    height: 20
                    text: qsTr("歌手")
                    color: Material.primaryColor
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.primaryColor
                    }
                }
                TextInput {
                    id: artist
                    y: 20
                    width: parent.width
                    height: 20
                    clip: true
                }
                Rectangle {
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: 2
                    color: Material.accentColor
                }
            }
            Item {
                width: parent.width
                height: 40
                Text {
                    y: 0
                    width: parent.width
                    height: 20
                    text: qsTr("专辑")
                    color: Material.primaryColor
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.primaryColor
                    }
                }
                TextInput {
                    id: album
                    y: 20
                    width: parent.width
                    height: 20
                    clip: true
                }
                Rectangle {
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: 2
                    color: Material.accentColor
                }
            }
        }

    }


}
