import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Item {
    id: fileManagerPage
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    width: parent.width

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
ListView {
    id: fileListView
    anchors.fill: parent
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
    text: isFile? "文件": "目录"
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
