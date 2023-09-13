#include "dmenuimpl.h"

#include <QModelIndex>
#include <QProcess>
#include <QStandardPaths>
#include <QCoreApplication>

DmenuImpl::DmenuImpl(QObject *parent)
    : ModelHelperImpl{parent}
{

}

int DmenuImpl::rowCount(const QModelIndex& parent) const
{
    return m_filter.size();
}

int DmenuImpl::columnCount(const QModelIndex& parent) const
{
    return 1;
}

QVariant DmenuImpl::data(const QModelIndex &index, int role) const
{
    return m_data[m_filter[index.row()]];
}

bool DmenuImpl::setFilterStr(const QString &str)
{
    Q_UNUSED(str)
    if (m_filterStr == str)
        return false;
    m_filterStr = str;
    m_filter.clear();
    for (int i = 0 ; i < m_data.size(); i++)
     if (m_data[i].contains(m_filterStr)) {
        m_filter.append(i);
    }
    return true;
}

QString DmenuImpl::filterStr()
{
    return m_filterStr;
}

QString DmenuImpl::get(size_t index)
{
    if (index >= m_filter.size())
        return "";
    return m_data[m_filter[index]];
}

void DmenuImpl::init()
{
    QProcess process;
    auto path = QStandardPaths::findExecutable("dmenu_path",
                    QStringList() << QCoreApplication::applicationDirPath() << LIBEXEC_PATH);
    if (path.isEmpty())
        path = QStandardPaths::findExecutable("dmenu_path");
    process.setProgram(path);
    process.start();
    process.waitForFinished();
    auto output = static_cast<QString>(process.readAll());
    m_data = output.split('\n');
    m_filter.resize(m_data.size());
    for (int i = 0; i < m_data.size(); i++)
        m_filter[i] = i;
}

bool DmenuImpl::react(QVariant index)
{
    QString command;// = index.toString();
    bool ok;
    size_t id = index.toUInt(&ok);
    if (ok) {
        command = m_data[m_filter[id]];
    } else {
        command = index.toString();
    }

#if QT_VERSION >= QT_VERSION_CHECK( 5, 15, 0 )
    auto args = QProcess::splitCommand(command);
    auto const program = args.takeFirst();
    return QProcess::startDetached(program, args);
#else
    return QProcess::startDetached(command);
#endif
//    QProcess process;
//    process.setProgram("sh");
//    QString c = "echo " + program + "| ${SHELL:-\"/bin/sh\"}";
//    process.setArguments(QStringList() << c);
//    process.waitForFinished();
}
