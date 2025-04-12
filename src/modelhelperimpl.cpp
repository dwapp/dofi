// SPDX-FileCopyrightText: rewine <luhongxu@deepin.org>.
// SPDX-License-Identifier: GPL-3.0-or-later

#include "modelhelperimpl.h"

ModelHelperImpl::ModelHelperImpl(QObject *parent)
    : QObject{parent}
{

}

QVariant ModelHelperImpl::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QString ModelHelperImpl::get(size_t index)
{
    return "";
}
