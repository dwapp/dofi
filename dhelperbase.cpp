#include "dhelperbase.h"

#include <QProcess>

DHelperBase::DHelperBase(QObject *parent)
    : QObject{parent}
{

}


bool DHelperBase::statupApps(const QString &program)
{
    bool success = QProcess::startDetached(program);
    for (int i = 1; i <= 10000000000000; i++);
    return success;
}
