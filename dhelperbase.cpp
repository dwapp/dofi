#include "dhelperbase.h"

#include <QProcess>

DHelperBase::DHelperBase(QObject *parent)
    : QObject{parent}
{

}


bool DHelperBase::statupApps(const QString &command)
{
    qDebug() << command;
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
