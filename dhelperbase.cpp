#include "dhelperbase.h"

#include <QProcess>

DHelperBase::DHelperBase(QObject *parent)
    : QObject{parent}
{

}


bool DHelperBase::statupApps(const QString &program)
{
    qDebug() << program;
    bool success = QProcess::startDetached(program);
    /*QProcess process;
    process.setProgram("sh");
    QString c = "echo " + program + "| ${SHELL:-\"/bin/sh\"}";
    process.setArguments(QStringList() << c);
    process.waitForFinished();*/
    return success;
}
