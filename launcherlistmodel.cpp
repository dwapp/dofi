#include "launcherlistmodel.h"

#include <QProcess>

LauncherListModel::LauncherListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

QHash<int, QByteArray> LauncherListModel::roleNames() const {
     // set role names
     QHash<int, QByteArray> roleNames;
     roleNames[NameRole] = QByteArrayLiteral("name");
     // roleNames[IconRole] = QByteArrayLiteral("icon");

     return roleNames;
}

int LauncherListModel::rowCount(const QModelIndex& parent) const
{
    return m_filter.size();
}

int LauncherListModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

QVariant LauncherListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QString name = m_data[m_filter[index.row()]];

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
    if (m_filterStr == str)
        return;
    m_filterStr = str;
    m_filter.clear();
    for (int i = 0 ; i < m_data.size(); i++)
     if (m_data[i].contains(m_filterStr)) {
        m_filter.append(i);
    }
    Q_EMIT layoutChanged();
}

QString LauncherListModel::filterStr()
{
    return m_filterStr;
}

QString LauncherListModel::get(size_t index)
{
    if (index >= m_filter.size())
        return "";
    return m_data[m_filter[index]];
}

void LauncherListModel::init()
{
    beginResetModel();
    m_data.clear();
    QProcess process;
    process.setProgram("dmenu_path");
    process.start();
    process.waitForFinished();
    auto output = static_cast<QString>(process.readAll());
    m_data = output.split('\n');
    m_filter.reserve(m_data.size());
    for (int i = 0; i < m_data.size(); i++)
        m_filter.append(i);
    endResetModel();
}
