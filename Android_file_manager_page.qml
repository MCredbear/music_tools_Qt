import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Item {
    id: fileManagerPage
    anchors.fill: parent

    Component.onCompleted: {
        var length = fileManager.readDir(dirPath)
        for (var i = 0; i < length; i++)
    {
        fileListModel.append(
        {
            "name": fileManager.name(i),
            "isFile": fileManager.isFile(i),
            "modifiedTime": fileManager.modifiedTime(i)
        }
    )
}
}

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
            dirPath += "/.."
            var length = fileManager.readDir(dirPath)
            fileListModel.clear()
            for (var i = 0; i < length; i++)
        {
            fileListModel.append(
            {
                "name": fileManager.name(i),
                "isFile": fileManager.isFile(i),
                "modifiedTime": fileManager.modifiedTime(i)
            }
        )
    }
}
}
}

ListView {
    id: fileListView
    anchors.top: topToolBar.bottom
    anchors.bottom: parent.bottom
    width: parent.width
    model: ListModel {id: fileListModel}
    delegate: Button {
    width: parent.width
    height: 50
    onReleased: {
        if (isFile)
        {
            filePath = dirPath + "/" + name
            stackView.push(editorPage)
        }
        else {
            dirPath += "/" + name
            var length = fileManager.readDir(dirPath)
            fileListModel.clear()
            for (var i = 0; i < length; i++)
        {
            fileListModel.append(
            {
                "name": fileManager.name(i),
                "isFile": fileManager.isFile(i),
                "modifiedTime": fileManager.modifiedTime(i)
            }
        )
    }
}
}
Text {
    id: icon
    anchors.left: parent.left
    anchors.leftMargin: 10
    width: 50
    height: 50
    text: isFile? "??????": "??????"
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
