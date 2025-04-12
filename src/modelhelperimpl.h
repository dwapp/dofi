// SPDX-FileCopyrightText: rewine <luhongxu@deepin.org>.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef MODELHELPERIMPL_H
#define MODELHELPERIMPL_H

#include <QObject>
#include <QVariant>

class ModelHelperImpl: public QObject
{
    Q_OBJECT

public:
    explicit ModelHelperImpl(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex& parent) const = 0;
    virtual int columnCount(const QModelIndex& parent) const = 0;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual bool setFilterStr(const QString &str) = 0;
    virtual QString filterStr() = 0;

    virtual QString get(size_t index);
    virtual void init() = 0;
    virtual bool react(QVariant index) = 0;
};

#endif // MODELHELPERIMPL_H
