import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Item {

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
                source: "file:../done_white_24dp.svg"
                fillMode: Image.Tile
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                anchors.bottomMargin: 10
                anchors.topMargin: 10
            }
            onReleased: {
                stackView.children[1].lyric = "" // Whitout this line, lyric on editorPage won't change if you select a same song for twice. It might be a bug of Qt
                stackView.children[1].lyric = lyric
                stackView.pop(stackView.children[1], StackView.PopTransition)
            }
        }
    }

    Flickable {
        anchors.top: topToolBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        contentHeight: lyricText.contentHeight
        contentWidth: lyricText.contentWidth
        Text {
            id: lyricText
            anchors.fill: parent
            text: lyric
        }
    }


}
