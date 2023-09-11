#include "amlistmodel.h"
#include "entry.h"
#include "applicationmanager.h"
#include "application.h"

#include <QProcess>
#include <algorithm>


AmListModel::AmListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

QHash<int, QByteArray> AmListModel::roleNames() const {
     // set role names
     QHash<int, QByteArray> roleNames;
     roleNames[NameRole] = QByteArrayLiteral("name");
     // roleNames[IconRole] = QByteArrayLiteral("icon");

     return roleNames;
}

int AmListModel::rowCount(const QModelIndex& parent) const
{
    return m_filter.size();
}

int AmListModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

QVariant AmListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QString name = m_data[m_filter[index.row()]]->iD();

    // return correct value
    if (role == NameRole)
        return name;
    //else if (role == IconRole)
    //    return user->icon;

    // return empty value
    return QVariant();
}

void AmListModel::setFilterStr(const QString &str)
{
    if (m_filterStr == str)
        return;
    m_filterStr = str;
    m_filter.clear();
    for (int i = 0 ; i < m_data.size(); i++)
     if (m_data[i]->iD().contains(m_filterStr)) {
        m_filter.append(i);
    }
    Q_EMIT layoutChanged();
}

QString AmListModel::filterStr()
{
    return m_filterStr;
}

QString AmListModel::get(size_t index)
{
    if (index >= m_filter.size())
        return "";
    return m_data[m_filter[index]]->iD();
}

void AmListModel::init()
{
    beginResetModel();

    ::registerDBusParam();
    ApplicationManager *manager = new ApplicationManager(this);

    auto rlist = manager->list();
    m_data.resize(rlist.size());
    m_filter.resize(rlist.size());

    for (int i = 0 ; i < rlist.size(); i++) {
        m_data[i] = new Application(rlist[i], manager);
        m_filter[i] = i;

        if (m_data[i]->iD() == "Alacritty") {
            qDebug() << "222333333333";
            m_data[i]->Launch();
        }
    }
    endResetModel();
}

bool AmListModel::react(QVariant index)
{
    bool ok;
    size_t id = index.toUInt(&ok);
    if (ok) {
        qDebug() << m_data[m_filter[id]]->iD();
        qDebug() << m_data[m_filter[id]]->displayName();

        m_data[m_filter[id]]->Launch();
    } else {
        qDebug() << "not index" << index.toString();
    }
    return true;
}
