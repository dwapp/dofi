#pragma once

#include <QObject>
#include <QDBusObjectPath>

#include "types.h"

class OrgDesktopspecApplicationManager1ApplicationInterface;
class Application : public QObject {
    Q_OBJECT
public:
    explicit Application(const QDBusObjectPath &path, QObject *parent = nullptr);
    ~Application() override = default;

    Q_PROPERTY(PropMap DisplayName READ displayName)
    PropMap displayName() const;

    Q_PROPERTY(QString ID READ iD)
    QString iD() const;

    Q_PROPERTY(PropMap Icons READ icons)
    PropMap icons() const;

    void Launch(const QString &action="", const QStringList &fields={}, const QVariantMap &options={});

private:
    OrgDesktopspecApplicationManager1ApplicationInterface *inter;
};

