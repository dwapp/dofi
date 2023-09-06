import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow  {
    width: 640
    height: 480
    visible: true
    title: qsTr("qml app launcher")

    background: Rectangle {
        anchors.fill: parent
        color:"White"
    }

    DLauncher {
        id: launch
    }

}
