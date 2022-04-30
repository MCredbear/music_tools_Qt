import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.14

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("IDv3 editor")
    Component.onCompleted: {
        name.text = editor.getName()
        artist.text = editor.getArtist()
        album.text = editor.getAlbum()
        editor.getCover()
        cover.source = "image://coverImageProvider/cover"
    }
    Image {
        id: cover
        anchors.fill: parent
        cache: false
    Text {
        id: name
        height: 20
        x:0
        y:0
    }
    Text {
        id: artist
        height: 20
        x:0
        y:20
    }
    Text {
        id: album
        height: 20
        x:0
        y:40
    }
    }

}
