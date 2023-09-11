#include <QDBusConnection>
#include <QDBusMetaType>

#include <types.h>

static void registerDBusParam() {
    qDBusRegisterMetaType<QMap<QString, QString>>();

    qRegisterMetaType<PropMap>("PropMap");
    qDBusRegisterMetaType<PropMap>();

    qRegisterMetaType<ObjectMap>("ObjectMap");
    qDBusRegisterMetaType<ObjectMap>();

    qRegisterMetaType<ObjectInterfaceMap>("ObjectInterfaceMap");
    qDBusRegisterMetaType<ObjectInterfaceMap>();
}
