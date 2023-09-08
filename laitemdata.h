#ifndef LAITEMDATA_H
#define LAITEMDATA_H

#include <QObject>
#include <QQmlEngine>

class LaItemData : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString name READ name WRITE setName)
public:

    explicit LaItemData(QObject *parent = nullptr);

    void setName(const QString & newName);
    QString name();

private:
    QString m_name;
};

#endif // LAITEMDATA_H
