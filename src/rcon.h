#ifndef RCON_H
#define RCON_H
#include <QCoreApplication>
#include <QTcpSocket>
#include <QMessageLogger>
#include <xslib/xslog.h>

#define SEC_TIMEOUT 5000
#define LOG(mesg){ xsLog::addLog("sm.log", mesg); }
class Rcon
{
private:
    QString sAddress;
    int iPort;
    int iState = 0;
    QTcpSocket socket;
public:
    Rcon();
    Rcon(QString _Address, int _Port);
    int Connect(QString address, int port);
    int Login(QString passwd);
    QString ReadStream();
    int WriteStream(QString send);
    void Close();

    QString getAddress();
    QString getPort();

    bool isOnline();
};

#endif // RCON_H
