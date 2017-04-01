#include "QLog.h"
#include <QDateTime>

QLog::QLog(QString filename)
{
    fileLog = new QFile(filename);
}

QString QLog::format(QString message)
{
    return QDateTime::currentDateTime().toString() + " -> " + message + "\n";
}

void QLog::addLog(QString message)
{
    fileLog->open(QFile::Append);
    fileLog->write(format(message).toUtf8());
    lastLog = message;
    fileLog->close();
}

QString QLog::getLog()
{
    return lastLog;
}

void QLog::addLog(QString filename, QString message)
{
    QFile* log = new QFile(filename);
    log->open(QFile::Append);
    log->write(format(message).toUtf8());
    log->close();
}
