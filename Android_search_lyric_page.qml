import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

Item {

    property string keyword

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
    }

    ListView {
        id: songListView
        anchors.top: topToolBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Component.onCompleted: {
            var json = JSON.parse(searcher.search(keyword, 0))
            var songs = json.songs
            for (var song in songs) {
                var _id = songs[song].id
                var _name = songs[song].name
                var artist = ""
                for (var _artist in songs[song].ar)
                    artist += "/" + songs[song].ar[_artist].name
                artist = artist.substr(1)
                var alia = ""
                for (var _alia in songs[song].alia)
                    alia += songs[song].alia[_alia]
                if (songs[song].hasOwnProperty("tns"))
                    for (var tn in songs[song].tns)
                        alia += songs[song].tns[tn]
                var album = songs[song].album.name
                var cover = songs[song].album.picUrl
                model.append({
                                 "id": _id,
                                 "name": _name,
                                 "artist": artist,
                                 "alia": alia,
                                 "album": album,
                                 "cover": cover
                             })
            }
        }

        model: ListModel {}

        delegate: Material_Button {
            width: songListView.width
            height: 45
            color: "#ffffff"
            elevated: false

            onReleased: {
                var lyric = searcher.getLyric(id)
                if (lyric !== "\0") stackView.push(lyricPage, {"lyric": lyric})
                else toast.sendToast("获取歌词失败")
            }

            Material_Image {
                id: songCover
                width: height
                radius: 2
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                source: cover
                elevation: 2
                anchors.leftMargin: 5
                anchors.bottomMargin: 5
                anchors.topMargin: 5
            }

            RowLayout {
                anchors.left: songCover.right
                anchors.leftMargin: 5
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 5
                height: 20
                Text {
                    id: songName
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: contentWidth
                    text: name
                    elide: Text.ElideRight
                    font.pointSize: 12
                }
                Text {
                    id: songAlia
                    color: "#424242"
                    Layout.preferredHeight: parent.height
                    Layout.fillWidth: true
                    text: (alia === "") ? "" : qsTr("（") + alia + qsTr("）")
                    elide: Text.ElideRight
                    font.pointSize: 12
                }
            }
            RowLayout {
                anchors.left: songCover.right
                anchors.leftMargin: 5
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                spacing: 0
                anchors.bottomMargin: 10
                height: 10
                Text {
                    id: songArtist
                    color: "#424242"
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: contentWidth
                    text: artist
                    elide: Text.ElideRight
                }
                Text {
                    id: songAlbum
                    color: "#424242"
                    Layout.preferredHeight: parent.height
                    Layout.fillWidth: true
                    text: qsTr(" - ") + album
                    elide: Text.ElideRight
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
