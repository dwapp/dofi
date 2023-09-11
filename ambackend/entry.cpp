#include "applicationmanager.h"
#include "application.h"

#include <QDBusConnection>
#include <QDBusArgument>
#include <QCoreApplication>
#include <QList>
#include <QDBusMetaType>

#include <algorithm>
#include <QDebug>
#include <types.h>

int main (int argc, char *argv[]) {
    qDBusRegisterMetaType<QMap<QString, QString>>();

    qRegisterMetaType<PropMap>("PropMap");
    qDBusRegisterMetaType<PropMap>();

    qRegisterMetaType<ObjectMap>("ObjectMap");
    qDBusRegisterMetaType<ObjectMap>();

    qRegisterMetaType<ObjectInterfaceMap>("ObjectInterfaceMap");
    qDBusRegisterMetaType<ObjectInterfaceMap>();

    QCoreApplication app(argc, argv);
    ApplicationManager *manager = new ApplicationManager;

    auto rlist = manager->list();
    QList<Application*> list(rlist.size());

    std::transform(rlist.begin(), rlist.end(), list.begin(), [manager](const QDBusObjectPath& path) {
        return new Application(path, manager);
    });

    qDebug() << "begin:" << list.size();
    for (Application* app : list) {
        qDebug() << "name:" << " " << app->displayName() << " id: " << app->iD() << "icons: " << app->icons();
        if (app->iD() == "qq") {
            qDebug() << "!!!!!!!!!!!!";
            qDebug() << app->displayName() << " start";
            app->Launch();
        }
    }

    return app.exec();
}
