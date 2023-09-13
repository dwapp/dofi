#include "modelhelperimpl.h"

ModelHelperImpl::ModelHelperImpl(QObject *parent)
    : QObject{parent}
{

}

int ModelHelperImpl::rowCount(const QModelIndex& parent) const
{
    return 0;
}

int ModelHelperImpl::columnCount(const QModelIndex& parent) const
{
    return 0;
}

QVariant ModelHelperImpl::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

bool ModelHelperImpl::setFilterStr(const QString &str)
{
    Q_UNUSED(str)
    return false;
}

QString ModelHelperImpl::filterStr()
{
    return "";
}

QString ModelHelperImpl::get(size_t index)
{
    return "";
}

void ModelHelperImpl::init()
{

}

bool ModelHelperImpl::react(QVariant index)
{
    return false;
}
