import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DLauncher

Rectangle
{
    id: base
    anchors.centerIn: parent
    width: 400
    height: 300
    border.color: "#82AAFF"
    border.width: 2
    color: "#465053"
    radius: 10
    //clip: true

    TextInput {
        id: searchInput
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            topMargin: 3
            leftMargin: 5
        }
        font.pointSize: 12
        color: "#FFFFFF"
        maximumLength: parent.width
        focus: true

        onTextChanged: {
            originalModel.filterStr = searchInput.text
            if (listView.currentIndex >= originalModel.rowCount())
                listView.currentIndex = originalModel.rowCount()-1;
        }

        Keys.onPressed: function(event) {
            if (event.key === Qt.Key_Up) {
                if (originalModel.rowCount() === 0)
                    return
                listView.currentIndex -= 1
                if (listView.currentIndex < 0)
                    listView.currentIndex += originalModel.rowCount()
                return;
            }
            if (event.key === Qt.Key_Down) {
                if (originalModel.rowCount() === 0)
                    return
                listView.currentIndex += 1
                if (listView.currentIndex >= originalModel.rowCount())
                    listView.currentIndex -= originalModel.rowCount()
                return
            }
            if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
                if (listView.currentIndex < 0) {
                    DHelperBase.statupApps(searchInput.text);
                } else {
                    var progam = originalModel.get(listView.currentIndex)
                    DHelperBase.statupApps(progam);
                }

                base.visible = false
                return;
            }
            if (event.key === Qt.Key_Escape) {
                base.visible = false
                return;
            }
        }
    }

    ToolSeparator {
        id: separator
        orientation: Qt.Horizontal
        anchors.top: searchInput.bottom
        width: parent.width
    }

    Rectangle {
        id: btn
        anchors {
            left: parent.left
            right: parent.right
            top: separator.bottom
            bottom: parent.bottom
            margins: 2
        }

        color: base.color
        layer.enabled: true

        LauncherListModel {
            id: originalModel
        }

        Component.onCompleted: {
            originalModel.init()
            if (originalModel.rowCount() > 0)
                listView.currentIndex = 0;
        }

        ScrollView {
            id: scrollView
            anchors.fill: parent

            clip: true

            ListView {
                id: listView
                anchors.fill: parent

                model: originalModel
                delegate: itemDelegate
            }

            Component {
                id: itemDelegate

                Rectangle {
                    id: itemRect
                    width: ListView.view.width
                    color: ListView.isCurrentItem ? "#4084D6" : (index%2 ? "#3D424F" : "#000000")
                    // Qt.darker("3D424F", 1.1) can't work on deepin
                    height: 26

                    Text {
                        id: itemText
                        anchors.fill: parent
                        text: name
                        color: "#FFFFFF"
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 5
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            listView.currentIndex = index
                        }
                        onDoubleClicked: {
                            var progam = name
                            DHelperBase.statupApps(progam);
                            base.visible = false
                        }
                    }
                }
            }
        }

    }

}
