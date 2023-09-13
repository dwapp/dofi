import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Dofi

Rectangle
{
    id: base
    anchors.centerIn: parent
    width: 400
    height: 300
    border.color: "#82AAFF"
    border.width: 2
    color: "#465053"
    radius: 5

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
            listModel.filterStr = searchInput.text
            if (listView.currentIndex >= listModel.rowCount())
                listView.currentIndex = listModel.rowCount()-1;
            else if (listView.currentIndex < 0 && listModel.rowCount() > 0)
                listView.currentIndex = 0;
        }

        Keys.onPressed: function(event) {
            if (event.key === Qt.Key_Up) {
                if (listModel.rowCount() === 0)
                    return
                listView.currentIndex -= 1
                if (listView.currentIndex < 0)
                    listView.currentIndex += listModel.rowCount()
                return;
            }
            if (event.key === Qt.Key_Down) {
                if (listModel.rowCount() === 0)
                    return
                listView.currentIndex += 1
                if (listView.currentIndex >= listModel.rowCount())
                    listView.currentIndex -= listModel.rowCount()
                return
            }
            if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
                if (listView.currentIndex < 0) {
                    listModel.react(searchInput.text)
                } else {
                    //var progam = listModel.get(listView.currentIndex)
                    //listModel.react(progam);
                    listModel.react(listView.currentIndex);
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
            margins: 3
        }

        color: base.color
        layer.enabled: true

        LauncherListModel {
            id: listModel
        }

        Component.onCompleted: {
            listModel.init()
            if (listModel.rowCount() > 0)
                listView.currentIndex = 0;
        }

        ScrollView {
            id: scrollView
            anchors.fill: parent

            ListView {
                id: listView
                anchors.fill: parent

                model: listModel
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
                    //radius: base.radius

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
                            //listModel.react(progam);
                            listModel.react(listView.currentIndex);
                            base.visible = false
                        }
                    }
                }
            }
        }

    }

}
