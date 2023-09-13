#ifndef AMIMPL_H
#define AMIMPL_H

#include "modelhelperimpl.h"
#include <QVector>
#include <QString>
#include <types.h>

class Application;

class AmImpl : public ModelHelperImpl
{
    Q_OBJECT
public:
    explicit AmImpl(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    bool setFilterStr(const QString &str) override;
    QString filterStr() override;

    QString get(size_t index) override;
    void init() override;
    bool react(QVariant index) override;

private:
    QVector<Application*> m_data;
    QVector<int> m_filter;
    QString m_filterStr;
    // data
    QVector<QString> m_appId;
    QVector<PropMap> m_displayName;
};

#endif // AMIMPL_H
