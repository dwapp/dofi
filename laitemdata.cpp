#include "laitemdata.h"

LaItemData::LaItemData(QObject *parent)
    : QObject{parent}
{

}

void LaItemData::setName(const QString &newName)
{
    m_name = name();
}

QString LaItemData::name()
{
    return m_name;
}
