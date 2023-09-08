#include "applicationmanager.h"
#include "application.h"

#include <QDBusConnection>
#include <QCoreApplication>
#include <QList>

#include <algorithm>
#include <QDebug>

int main (int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    ApplicationManager *manager = new ApplicationManager;

    auto rlist = manager->list();
    QList<Application*> list(rlist.size());

    std::transform(rlist.begin(), rlist.end(), list.begin(), [manager](const QDBusObjectPath& path) {
        return new Application(path, manager);
    });

    qDebug() << "begin:" << list.size();
    for (Application* app : list) {
        qDebug() << app->displayName() << " " << app->iD() << " " << app->icons();
    }

    //return app.exec();
}
