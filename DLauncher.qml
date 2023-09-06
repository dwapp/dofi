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
    radius: 6

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
//        onTextChanged: {
//            originalModel.filter(searchInput.text);
//        }
    }

//    Rectangle {
//        id: separator
//        anchors.top: searchBar.bottom
//        width: parent.width
//        height: 1
//        color: "blue"
//    }
    ToolSeparator {
        id: separator
        orientation: Qt.Horizontal
        anchors.top: searchInput.bottom
        width: parent.width
    }

    // right button #fc1944
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

//        Component.onCompleted: {
//            originalModel.filter("")
//        }


        ScrollView {
            id: scrollView
            anchors.fill: parent

            clip: true

            ListView {
                anchors.fill: parent

                model: originalModel
                delegate: itemDelegate
                // highlight: Rectangle { color: "#FFFFFF" }
                highlightFollowsCurrentItem: true
                highlightRangeMode: ListView.ApplyRange
                //focus: true
            }

            Component {
                id: itemDelegate

                Rectangle {
                    color: ListView.isCurrentItem?"#157efb":"#53d769" //"#3D424F"
                    height: 26

                    Text {
                        anchors.fill: parent
                        text: name
                        color: "#FFFFFF"
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 5
                    }
                    visible: searchInput.text ? name.match(`(${searchInput.text})`, "i") : true
                }
            }
        }

        /*ListView {
            anchors.fill: parent

            model: originalModel
            delegate: Rectangle {
                color: "#3D424F"
                height: 26

                Text {
                    anchors.fill: parent
                    text: name
                    color: "#FFFFFF"
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: 5
                }
                visible: searchInput.text ? name.match(`(${searchInput.text})`, "i") : true
            }
            highlight: Rectangle {
                color: "lightblue"
            }
            highlightFollowsCurrentItem: true
            //focus: true
        }*/
    }

}
