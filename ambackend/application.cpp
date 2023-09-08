#include "application.h"

#include "Application.h"

Application::Application(const QDBusObjectPath &path, QObject *parent)
    : QObject(parent)
    , inter(new OrgDesktopspecApplicationManager1ApplicationInterface("org.desktopspec.ApplicationManager1", path.path(), QDBusConnection::sessionBus(), this))
{

}

PropMap Application::displayName() const {
    return inter->displayName();
}

QString Application::iD() const {
    return inter->iD();
}

PropMap Application::icons() const {
    return inter->icons();
}
