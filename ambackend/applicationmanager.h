#pragma once

#include <QObject>
#include <QDBusObjectPath>

class OrgDesktopspecApplicationManager1Interface;
class ApplicationManager : public QObject {
    Q_OBJECT
public:
    explicit ApplicationManager(QObject *parent = nullptr);
    ~ApplicationManager() override = default;

    QList<QDBusObjectPath> list() const;

private:
    OrgDesktopspecApplicationManager1Interface *inter;
};
