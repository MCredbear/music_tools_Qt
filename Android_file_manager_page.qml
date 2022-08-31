import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Item {
    id: fileManagerPage
    Component.onCompleted: {
        var length = fileManager.readDir(dirPath)
        for (var i = 0; i < length; i++) {
            fileListModel.append({
                                     "name": fileManager.name(i),
                                     "isFile": fileManager.isFile(i),
                                     "modifiedTime": fileManager.modifiedTime(i)
                                 })
        }
    }

    ToolBar {
        id: topToolBar
        z: 10
        anchors.top: parent.top
        width: parent.width

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
                dirPath += "/.."
                var length = fileManager.readDir(dirPath)
                fileListModel.clear()
                for (var i = 0; i < length; i++) {
                    fileListModel.append({
                                             "name": fileManager.name(i),
                                             "isFile": fileManager.isFile(i),
                                             "modifiedTime": fileManager.modifiedTime(i)
                                         })
                }
            }
        }
    }

    ListView {
        id: fileListView
        anchors.top: topToolBar.bottom
        anchors.bottom: parent.bottom
        width: parent.width
        spacing: 0
        model: ListModel {
            id: fileListModel
        }
        delegate: Material_Button {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 50
            elevated: false
            color: "#ffffff"
            onReleased: {
                if (isFile) {
                    filePath = dirPath + "/" + name
                    stackView.push(editorPage)
                } else {
                    dirPath += "/" + name
                    var length = fileManager.readDir(dirPath)
                    fileListModel.clear()
                    for (var i = 0; i < length; i++) {
                        fileListModel.append({
                                                 "name": fileManager.name(i),
                                                 "isFile": fileManager.isFile(i),
                                                 "modifiedTime": fileManager.modifiedTime(i)
                                             })
                    }
                }
            }
            Material_Image {
                id: icon
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: 50
                height: 50
                source: isFile ? "file:../audiotrack_black_24dp.svg" : "file:../folder_black_24dp.svg"
            }
            Text {
                id: fileName
                anchors.top: parent.top
                anchors.left: icon.right
                anchors.leftMargin: 10
                height: 35
                text: name
            }
            Text {
                id: fileModifiedTime
                anchors.top: fileName.bottom
                anchors.left: icon.right
                anchors.leftMargin: 10
                text: modifiedTime
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.1;height:480;width:640}
}
##^##*/
