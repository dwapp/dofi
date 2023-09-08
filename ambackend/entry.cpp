#include "applicationmanager.h"
#include "application.h"

#include <QDBusConnection>
#include <QCoreApplication>
#include <QList>

#include <algorithm>
#include <QDebug>
#include <types.h>

int main (int argc, char *argv[]) {
    qRegisterMetaType<ObjectInterfaceMap>("ObjectInterfaceMap");
    qRegisterMetaType<ObjectMap>("ObjectMap");
    qRegisterMetaType<PropMap>("PropMap");

    QCoreApplication app(argc, argv);
    ApplicationManager *manager = new ApplicationManager;

    auto rlist = manager->list();
    QList<Application*> list(rlist.size());

    std::transform(rlist.begin(), rlist.end(), list.begin(), [manager](const QDBusObjectPath& path) {
        return new Application(path, manager);
    });

    qDebug() << "begin:" << list.size();
    for (Application* app : list) {
        qDebug() << "name:" << " " << app->displayName() << " id: " << app->iD();
        if (app->iD() == "xterm") {
            app->Launch();
        }
    }

    return app.exec();
}
