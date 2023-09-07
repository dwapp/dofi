#ifndef DHELPERBASE_H
#define DHELPERBASE_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlContext>
#include <QAbstractListModel>

class DHelperBase : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit DHelperBase(QObject *parent = nullptr);

    //QAbstractListModel *getMode();

    Q_INVOKABLE bool statupApps(const QString &app);

//private:
//    QAbstractListModel *m_mode;
};

QML_DECLARE_TYPE(DHelperBase)

#endif // DHELPERBASE_H
