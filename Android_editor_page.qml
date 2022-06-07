import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Item {
    anchors.fill: parent
    width: 320
    height: 640

    ToolBar {
        id: topToolBar
        z: 10
        anchors.top: parent.top
        width: parent.width

        ToolButton {
            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: "back"
            }
            onReleased: {
                stackView.pop()
            }
        }
        ToolButton {
            anchors.right: parent.right
            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: "save"
            }
            onReleased: {
                editor.setName(name.text)
                editor.setArtist(artist.text)
                editor.setAlbum(album.text)
                
                editor.setLyric(lyric.text)
                editor.saveFile()
            }
        }
    }

    Flickable {
        id: flickable
        anchors.top: topToolBar.bottom
        anchors.bottom: parent.bottom
        flickableDirection: Flickable.VerticalFlick
        width: parent.width
        contentHeight: column.height

        Component.onCompleted: {
            editor.readFile(filePath)
            name.text = editor.getName()
            artist.text = editor.getArtist()
            album.text = editor.getAlbum()
            editor.getCover()
            cover.source = "image://coverImageProvider/cover"
            year.text = editor.getYear()
            lyric.text = editor.getLyric()

        }

        Column {
            id: column
            anchors.left: parent.left
            anchors.leftMargin: 25
            anchors.right: parent.right
            anchors.rightMargin: 25

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
            Column {
                width: parent.width
                Text {
                    width: parent.width
                    height: contentHeight
                    text: qsTr("歌曲名称")
                    color: Material.primaryColor
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.primaryColor
                    }
                }
                TextEdit {
                    id: name
                    width: parent.width
                    height: contentHeight
                    selectByMouse: true
                    clip: true
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.accentColor
                    }
                }

            }
            Column {
                width: parent.width
                Text {
                    width: parent.width
                    height: contentHeight
                    text: qsTr("歌手")
                    color: Material.primaryColor
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.primaryColor
                    }
                }
                TextEdit {
                    id: artist
                    width: parent.width
                    height: contentHeight
                    selectByMouse: true
                    clip: true
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.accentColor
                    }
                }

            }
            Column {
                width: parent.width
                Text {
                    width: parent.width
                    height: contentHeight
                    text: qsTr("专辑")
                    color: Material.primaryColor
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.primaryColor
                    }
                }
                TextEdit {
                    id: album
                    width: parent.width
                    height: contentHeight
                    selectByMouse: true
                    clip: true
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.accentColor
                    }
                }

            }
            Column {
                width: parent.width
                Text {
                    width: parent.width
                    height: contentHeight
                    text: qsTr("年份")
                    color: Material.primaryColor
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.primaryColor
                    }
                }
                TextEdit {
                    id: year
                    width: parent.width
                    height: contentHeight
                    selectByMouse: true
                    clip: true
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.accentColor
                    }
                }

            }
            Column {
                width: parent.width
                Text {
                    width: parent.width
                    height: contentHeight
                    text: qsTr("歌词")
                    color: Material.primaryColor
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.primaryColor
                    }
                }
                TextEdit {
                    id: lyric
                    width: parent.width
                    height: contentHeight
                    selectByMouse: true
                    clip: true
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.accentColor
                    }
                }

            }

            Rectangle {
                width: 1
                height: 20
                color: "transparent"
            }
        }
    }
}


