#ifndef AMLISTMODEL_H
#define AMLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>
#include <QVector>

class Application;

class AmListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(AmListModel)
    Q_PROPERTY(QString filterStr READ filterStr WRITE setFilterStr)
    QML_ELEMENT
public:
    explicit AmListModel(QObject *parent = nullptr);

public :
    enum UserRoles {
        NameRole = Qt::UserRole + 10,
        IconRole,
    };
    Q_ENUM(UserRoles)

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void populate();

    void setFilterStr(const QString &str);
    QString filterStr();

    Q_INVOKABLE QString get(size_t index);

    Q_INVOKABLE void init();

    Q_INVOKABLE bool react(QVariant index);

private:
    QVector<Application*> m_data;
    QVector<int> m_filter;
    QString m_filterStr;
};

#endif // AmListModel_H
