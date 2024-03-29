import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Item {
    width: 320
    height: 640

    property string title
    property string artist
    property string album
    property string disk
    property string track
    property string year
    property string lyric

    ToolBar {
        id: topToolBar
        z: 10
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        ToolButton {
            Image {
                anchors.fill: parent
                source: "file:../arrow_back_ios_white_24dp.svg"
                fillMode: Image.Tile
                anchors.rightMargin: 9
                anchors.leftMargin: 17
                anchors.bottomMargin: 10
                anchors.topMargin: 10
            }
            onReleased: {
                stackView.pop()
            }
        }
        ToolButton {
            anchors.right: parent.right
            Image {
                anchors.fill: parent
                source: "file:../save_white_24dp.svg"
                fillMode: Image.Tile
                anchors.rightMargin: 10
                anchors.leftMargin: 13
                anchors.bottomMargin: 10
                anchors.topMargin: 10
            }
            onReleased: {
                editor.setTitle(title)
                editor.setArtist(artist)
                editor.setAlbum(album)
                editor.setDisk(disk)
                editor.setTrack(track)

                editor.setLyric(lyric)
                if (year.text !== "") editor.setYear(year)
                editor.saveFile()
            }
        }
    }

    Flickable {
        id: flickable
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: topToolBar.bottom
        anchors.bottom: parent.bottom
        flickableDirection: Flickable.VerticalFlick
        contentHeight: column.height

        Component.onCompleted: {
            editor.readFile(filePath)
            title = editor.getTitle()
            artist = editor.getArtist()
            album = editor.getAlbum()
            editor.getCover()
            cover.source = "image://coverImageProvider/cover"
            disk = editor.getDisk()
            track = editor.getTrack()
            year = editor.getYear()
            lyric = editor.getLyric()
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
                Material_Image {
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
                    anchors.left: parent.left
                    anchors.right: parent.right
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
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: contentHeight
                    text: title
                    selectByMouse: true
                    clip: true
                    onTextChanged: {
                        if (text !== title) title = text
                    }
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: Material.accentColor
                    }
                }
            }
            Column {
                anchors.left: parent.left
                anchors.right: parent.right
                Text {
                    anchors.left: parent.left
                    anchors.right: parent.right
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
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: contentHeight
                    text: artist
                    selectByMouse: true
                    clip: true
                    onTextChanged: {
                        if (text !== artist) artist = text
                    }
                    Rectangle {
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: 2
                        color: Material.accentColor
                    }
                }
            }
            Column {
                anchors.left: parent.left
                anchors.right: parent.right
                Text {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: contentHeight
                    text: qsTr("专辑")
                    color: Material.primaryColor
                    Rectangle {
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: 2
                        color: Material.primaryColor
                    }
                }
                TextEdit {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: contentHeight
                    text: album
                    selectByMouse: true
                    clip: true
                    onTextChanged: {
                        if (text !== album) album = text
                    }
                    Rectangle {
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: 2
                        color: Material.accentColor
                    }
                }
            }
            Column {
                anchors.left: parent.left
                anchors.right: parent.right
                Text {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: contentHeight
                    text: qsTr("年份")
                    color: Material.primaryColor
                    Rectangle {
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: 2
                        color: Material.primaryColor
                    }
                }
                TextEdit {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: contentHeight
                    text: year
                    selectByMouse: true
                    clip: true
                    onTextChanged: {
                        if (text !== year) year = text
                    }
                    Rectangle {
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: 2
                        color: Material.accentColor
                    }
                }
            }
            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                height: children[0].height
                Column {
                    anchors.left: parent.left
                    width: parent.width / 2.1
                    Text {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: contentHeight
                        text: qsTr("磁盘号")
                        color: Material.primaryColor
                        Rectangle {
                            anchors.bottom: parent.bottom
                            anchors.left: parent.left
                            anchors.right: parent.right
                            height: 2
                            color: Material.primaryColor
                        }
                    }
                    TextEdit {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: contentHeight
                        text: disk
                        selectByMouse: true
                        clip: true
                        onTextChanged: {
                            if (text !== disk) disk = text
                        }
                        Rectangle {
                            anchors.bottom: parent.bottom
                            anchors.left: parent.left
                            anchors.right: parent.right
                            height: 2
                            color: Material.accentColor
                        }
                    }
                }
                Column {
                    anchors.right: parent.right
                    width: parent.width / 2.1
                    Text {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: contentHeight
                        text: qsTr("音轨号")
                        color: Material.primaryColor
                        Rectangle {
                            anchors.bottom: parent.bottom
                            anchors.left: parent.left
                            anchors.right: parent.right
                            height: 2
                            color: Material.primaryColor
                        }
                    }
                    TextEdit {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: contentHeight
                        text: track
                        selectByMouse: true
                        clip: true
                        onTextChanged: {
                            if (text !== track) track = text
                        }
                        Rectangle {
                            anchors.bottom: parent.bottom
                            anchors.left: parent.left
                            anchors.right: parent.right
                            height: 2
                            color: Material.accentColor
                        }
                    }
                }
            }


            Column {
                anchors.left: parent.left
                anchors.right: parent.right
                Rectangle {
                    id: rectangle
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: lyricLable.height
                    color: "transparent"
                    Text {
                        id: lyricLable
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: contentHeight
                        text: qsTr("歌词")
                        color: Material.primaryColor
                        Rectangle {
                            anchors.bottom: parent.bottom
                            anchors.left: parent.left
                            anchors.right: parent.right
                            height: 2
                            color: Material.primaryColor
                        }
                    }
                    Material_Button {
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        height: lyricLable.height - 4
                        color: "white"
                        radius: 2
                        Text {
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            text: qsTr("搜索歌词")
                        }
                        onReleased: {
                            stackView.push(searchLyricPage, {"keyword": name})
                        }
                    }
                }

                TextEdit {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: contentHeight
                    text: lyric
                    selectByMouse: true
                    clip: true
                    onTextChanged: {
                        if (text !== lyric) lyric = text
                    }
                    Rectangle {
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
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


