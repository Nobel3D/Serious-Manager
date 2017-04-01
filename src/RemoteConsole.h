#ifndef REMOTECONSOLE_H
#define REMOTECONSOLE_H
#include <QCoreApplication>
#include <QTcpSocket>
#include <QMessageLogger>
#include "QLog.h"

#define SEC_TIMEOUT 5000
#define LOG(mesg){ QLog::addLog("sm.log", mesg); }
class RemoteConsole
{
private:
    QString sAddress;
    int iPort;
    int iState = 0;
    QTcpSocket socket;
public:
    RemoteConsole();
    RemoteConsole(QString _Address, int _Port);
    int Connect(QString address, int port);
    int Login(QString passwd);
    QString ReadStream();
    int WriteStream(QString send);
    void Close();

    QString getAddress();
    QString getPort();

    bool isOnline();
};

#endif // REMOTECONSOLE_H
