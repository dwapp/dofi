#ifndef DMENUIMPL_H
#define DMENUIMPL_H

#include "modelhelperimpl.h"

#include <QObject>
#include <QVector>
#include <QStringList>

class DmenuImpl : public ModelHelperImpl
{
    Q_OBJECT

public:
    explicit DmenuImpl(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    bool setFilterStr(const QString &str) override;
    QString filterStr() override;

    QString get(size_t index) override;
    void init() override;
    bool react(QVariant index) override;

private:
    QStringList m_data;
    QVector<int> m_filter;
    QString m_filterStr;
};

#endif // DMENUIMPL_H
