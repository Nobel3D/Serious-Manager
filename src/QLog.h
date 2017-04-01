#ifndef QLOG_H
#define QLOG_H

#include <QFile>

class QLog
{
private:
    QFile* fileLog;
    QString lastLog;
    static QString format(QString message);
public:
    QLog(QString filename);
    void addLog(QString message);
    QString getLog();
    static void addLog(QString filename, QString message);
};

#endif // QLOG_H
