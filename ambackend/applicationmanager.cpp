#include "applicationmanager.h"
#include <qdbusextratypes.h>

#include "ApplicationManager.h"

ApplicationManager::ApplicationManager(QObject *parent)
    : QObject(parent)
    , inter(new OrgDesktopspecApplicationManager1Interface("org.desktopspec.ApplicationManager1", "/org/desktopspec/ApplicationManager1", QDBusConnection::sessionBus(), this))
{

}

QList<QDBusObjectPath> ApplicationManager::list() const {
    return inter->list();
}
