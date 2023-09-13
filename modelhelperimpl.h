#ifndef MODELHELPERIMPL_H
#define MODELHELPERIMPL_H

#include <QObject>
#include <QVariant>

class ModelHelperImpl: public QObject
{
    Q_OBJECT

public:
    explicit ModelHelperImpl(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex& parent) const;
    virtual int columnCount(const QModelIndex& parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual bool setFilterStr(const QString &str);
    virtual QString filterStr();

    virtual QString get(size_t index) ;
    virtual void init();
    virtual bool react(QVariant index);
};

#endif // MODELHELPERIMPL_H
