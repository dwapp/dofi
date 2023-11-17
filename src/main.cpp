// SPDX-FileCopyrightText: rewine <luhongxu@deepin.org>.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "launcherlistmodel.h"
#include "dmenuimpl.h"
#include "amimpl.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QQmlComponent>
#include <QQuickView>
#include <QQuickItem>
#include <LayerShellQt/Window>
#include <LayerShellQt/Shell>

int main(int argc, char *argv[])
{
    //qputenv("QT_QPA_PLATFORM", "wayland");
    LayerShellQt::Shell::useLayerShell();

    QGuiApplication app(argc, argv);
    app.setOrganizationName("deepin");
    app.setApplicationName("dofi");
    app.setApplicationVersion("0.1.0");
    app.setApplicationDisplayName("Dofi");
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption modeOpt({"S", "show"}, "Show the mode [run/drun] and exit.", "mode");
    parser.addOption(modeOpt);
    parser.process(app);

    if (parser.isSet(modeOpt)) {
        QString mode = parser.value("S");
        if (mode == "run") {
            LauncherListModel::impl = new DmenuImpl;
        } else if (mode == "drun") {
            LauncherListModel::impl = new AmImpl;
        } else {
            qCritical() << "no known mode: " << mode;
            // TODO: GUI Warning
            return 0;
        }
    } else {
        LauncherListModel::impl = new DmenuImpl;
    }

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    const QUrl url(u"qrc:/qt/qml/Dofi/Main.qml"_qs);
#else
    const QUrl url(u"qrc:/Dofi/Main.qml"_qs);
#endif

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);
    engine.load(url);

    QQuickWindow *window = qobject_cast<QQuickWindow*>(engine.rootObjects().at(0));
    if (!window) {
        qFatal("Error: Your root item has to be a window.");
        return -1;
    }
    auto layerShell = LayerShellQt::Window::get(window);
    layerShell->setCloseOnDismissed(false);
    layerShell->setLayer(LayerShellQt::Window::LayerTop);
    layerShell->setKeyboardInteractivity(LayerShellQt::Window::KeyboardInteractivityExclusive);
    layerShell->setExclusiveZone(-1);
    //layerShell->setAnchors(LayerShellQt::Window::AnchorTop);
    //layerShell->setMargins({100,100,100,100});
    //window->resize(400, 300);
    return app.exec();
}
