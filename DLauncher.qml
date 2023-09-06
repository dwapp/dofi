import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle
{
    id: backgroundPlate
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
            originalModel.filter(searchInput.text)
        }

        Keys.onPressed: function(event) {
            if (event.key === Qt.Key_Up) {
                if (filteredModel.count == 0)
                    return
                listView.currentIndex -= 1
                if (listView.currentIndex < 0)
                    listView.currentIndex += filteredModel.count
                return;
            }
            if (event.key === Qt.Key_Down) {
                if (filteredModel.count == 0)
                    return
                listView.currentIndex += 1
                if (listView.currentIndex >= filteredModel.count)
                    listView.currentIndex -= filteredModel.count
                return
            }
            if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
                if (filteredModel.count != 0) {
                    var progam = filteredModel.get(listView.currentIndex).name
                    console.log(progam)
                }
                backgroundPlate.visible = false
                return;
            }
            if (event.key === Qt.Key_Escape) {
                backgroundPlate.visible = false
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

        color: backgroundPlate.color
        layer.enabled: true

        ListModel {
            id: filteredModel
        }

        ListModel {
            id: originalModel
            ListElement { name: "John"; }
            ListElement { name: "deepin-editor"; }
            ListElement { name: "ls"; }
            ListElement { name: "pwd"; }
            ListElement { name: "cc"; }
            ListElement { name: "lsgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggt"; }
            ListElement { name: "1John"; }
            ListElement { name: "1deepin-editor"; }
            ListElement { name: "1ls"; }
            ListElement { name: "1pwd"; }
            ListElement { name: "1cc"; }
            ListElement { name: "2John"; }
            ListElement { name: "2deepin-editor"; }
            ListElement { name: "2ls"; }
            ListElement { name: "2pwd"; }
            ListElement { name: "2cc"; }

            function filter(subText) {
                filteredModel.clear()
                var regex = new RegExp(subText, 'i');
                for (var i = 0; i < originalModel.count; i++) {
                    if (originalModel.get(i).name.toString().match(regex)) {
                        filteredModel.append(originalModel.get(i))
                    }
                }
            }
        }

        Component.onCompleted: {
            originalModel.filter("")
        }

        ScrollView {
            id: scrollView
            anchors.fill: parent

            clip: true

            ListView {
                id: listView
                anchors.fill: parent

                model: filteredModel
                delegate: itemDelegate
                // highlight: Rectangle { color: "#FFFFFF" }
                highlightFollowsCurrentItem: true
            }

            Component {
                id: itemDelegate

                Rectangle {
                    id: itemRect
                    width: ListView.view.width
                    color: ListView.isCurrentItem ? "#4084D6" : (index%2 ? "#3D424F" : Qt.darker("3D424F", 1.1))
                    height: 26
                    //visible: searchInput.text ? name.match(`(${searchInput.text})`, "i") : true
                    //height: visible ? 26 :0

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
                            var progam = name // filteredModel.get(listView.currentIndex).name
                            console.log(progam)
                            backgroundPlate.visible = false
                        }
                    }
                }
            }
        }

    }

}
