// SPDX-FileCopyrightText: rewine <luhongxu@deepin.org>.
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import org.kde.layershell as LayerShell

Window {
    LayerShell.Window.anchors: LayerShell.Window.AnchorNone
    LayerShell.Window.layer: LayerShell.Window.LayerOverlay
    LayerShell.Window.keyboardInteractivity: LayerShell.WindowKeyboardInteractivityExclusive
    LayerShell.Window.exclusionZone: -1
    width: 400
    height: 300
    visible: true

    flags: Qt.FramelessWindowHint
    color: "#00000000"

    function centerWindow() {
        // this only work for x11
        var screenWidth = Screen.desktopAvailableWidth
        var screenHeight = Screen.desktopAvailableHeight

        var windowX = (screenWidth - width) / 2
        var windowY = (screenHeight - height) / 2

        x = windowX
        y = windowY
    }

    Component.onCompleted: {
        //centerWindow()
    }

    Timer {
        id: quitTimer
        interval: 1000 // ms
        repeat: false
        onTriggered: {
            Qt.quit()
        }
    }

    DLauncher {
        id: launch
        anchors.fill: parent
        onVisibleChanged: {
            if (!visible)
                quitTimer.start();
        }
    }
}
