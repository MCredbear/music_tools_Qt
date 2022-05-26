import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Item {
    id: window
    width: 320
    height: 640
    property string dirPath: "/home/redbear"
    property string filePath

    Toast { }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: fileManagerPage
    }

    Component {
        id: fileManagerPage
        Android_file_manager_page {}
    }

    Component{
        id: editorPage
        Android_editor_page {}
    }


}
