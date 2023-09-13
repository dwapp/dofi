#include "amimpl.h"
#include "entry.h"
#include "applicationmanager.h"
#include "application.h"

#include <QModelIndex>
#include <QLocale>

AmImpl::AmImpl(QObject *parent)
    : ModelHelperImpl{parent}
{

}

int AmImpl::rowCount(const QModelIndex& parent) const
{
    return m_filter.size();
}

int AmImpl::columnCount(const QModelIndex& parent) const
{
    return 1;
}

QVariant AmImpl::data(const QModelIndex &index, int role) const
{
    int id = m_filter[index.row()];

    if (m_displayName[id].contains("Name")) {
        const auto &nameMap = m_displayName[id]["Name"];
        QString locale = QLocale::system().name();
        if (nameMap.contains(locale))
            return nameMap[locale] + "  -  " + m_appId[id];
        if (nameMap.contains("default"))
            return nameMap["default"] + "  -  " + m_appId[id];
        if (nameMap.contains("en_GB"))
            return nameMap["en_GB"]  + "  -  " + m_appId[id];
    }

    return m_appId[id];
}

bool AmImpl::setFilterStr(const QString &str)
{
    if (m_filterStr == str)
        return false;
    m_filterStr = str;
    m_filter.clear();

    for (int i = 0 ; i < m_data.size(); i++) {
        bool accept = false;
        accept |= m_appId[i].contains(m_filterStr);
        if (m_displayName[i].contains("Name")) {
           const auto &nameMap = m_displayName[i]["Name"];
           QString locale = QLocale::system().name();
           accept |= nameMap[locale].contains(m_filterStr);
           accept |= nameMap["default"].contains(m_filterStr);
           accept |= nameMap["en_GB"].contains(m_filterStr);
        }
        if (accept)
            m_filter.append(i);
    }

    return true;
}

QString AmImpl::filterStr()
{
    return m_filterStr;
}

QString AmImpl::get(size_t index)
{
    if (index >= m_filter.size())
        return "";
    return m_data[m_filter[index]]->iD();
}

void AmImpl::init()
{
    ::registerDBusParam();
    ApplicationManager *manager = new ApplicationManager(this);

    auto rlist = manager->list();
    m_data.resize(rlist.size());
    m_filter.resize(rlist.size());
    m_appId.resize(rlist.size());
    m_displayName.resize(rlist.size());

    for (int i = 0 ; i < rlist.size(); i++) {
        m_data[i] = new Application(rlist[i], manager);
        m_filter[i] = i;

        m_appId[i] = m_data[i]->iD();
        m_displayName[i] = m_data[i]->displayName();
        //qDebug() << m_data[i]->iD() << " "  << m_data[i]->displayName();
    }
}

bool AmImpl::react(QVariant index)
{
    bool ok;
    size_t id = index.toUInt(&ok);
    if (ok) {
        //qDebug() << m_data[m_filter[id]]->iD();
        //qDebug() << m_data[m_filter[id]]->displayName();

        m_data[m_filter[id]]->Launch();
    } else {
        qDebug() << "not index" << index.toString();
    }
    return true;
}
