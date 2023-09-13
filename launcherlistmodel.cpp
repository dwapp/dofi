#include "launcherlistmodel.h"
#include "modelhelperimpl.h"

#include <QProcess>

LauncherListModel::LauncherListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

ModelHelperImpl *LauncherListModel::impl;

QHash<int, QByteArray> LauncherListModel::roleNames() const {
     // set role names
     QHash<int, QByteArray> roleNames;
     roleNames[NameRole] = QByteArrayLiteral("name");
     roleNames[IconRole] = QByteArrayLiteral("icon");

     return roleNames;
}

int LauncherListModel::rowCount(const QModelIndex& parent) const
{
    return impl->rowCount(parent);
}

int LauncherListModel::columnCount(const QModelIndex& parent) const
{
    return impl->columnCount(parent);
}

QVariant LauncherListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QString name = impl->data(index, role).toString();

    // return correct value
    if (role == NameRole)
        return name;
    //else if (role == IconRole)
    //    return user->icon;

    // return empty value
    return QVariant();
}

void LauncherListModel::setFilterStr(const QString &str)
{
    if (impl->setFilterStr(str))
        Q_EMIT layoutChanged();
}

QString LauncherListModel::filterStr()
{
    return impl->filterStr();
}

QString LauncherListModel::get(size_t index)
{
    return impl->get(index);
}

void LauncherListModel::init()
{
    beginResetModel();
    impl->init();
    endResetModel();
}

bool LauncherListModel::react(QVariant index)
{
    return impl->react(index);
}

