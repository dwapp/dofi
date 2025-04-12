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
#include <QStringLiteral>

using namespace Qt::StringLiterals;

int main(int argc, char *argv[])
{
    //qputenv("QT_QPA_PLATFORM", "wayland");

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

    const QUrl url(u"qrc:/qt/qml/Dofi/Main.qml"_s);
    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
