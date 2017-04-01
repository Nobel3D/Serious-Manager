#include <QApplication>
#include <QDebug>
#include <QThread>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "RemoteConsole.h"
#include "QConsole.h"
#include "NetFetch.h"

#define CERROR(check, text) { if(check) { qWarning() << "[ERR] " << text << endl; \
                                          return -1; }                      }

#define OK 0

#define endl "\n"

using namespace std;

QString sysApp;
QString sysVersion = "0.1";
QString netAddress;
QString netPasswd;
QString netPort;

RemoteConsole* rcClient;
NetFetch* netFetch;
QConsole* console;

QString inputBuffer;

int getArgs(int argc, char **argv)
{

    sysApp = argv[0];
    netAddress = argv[1];
    netPort = argv[2];
    netPasswd = argv[3] != nullptr ? argv[3] : QString("");

    return OK;
}

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}


void getPasswd()
{
    char ch;
    if(netPasswd == "")
    {
        while(ch != 13){
            ch = getch();
            if(ch == 10) return;
            netPasswd.append(ch);
            *console << "*";
        }
    }
}

int main(int argc, char **argv)
{
    console = new QConsole;
    CERROR(argc < 3, "Insufficient arguments!");
    getArgs(argc,argv);
    *console << "Serious Manager " << sysVersion << " by Luca \"Nobel3D\" Gasperini" << endl;
    *console << QString("Trying to connect: ") + netAddress + "\n";
    rcClient = new RemoteConsole;
    if(rcClient->Connect(netAddress, netPort.toInt()) != 0)
        return 0;

    *console << "Login -> ";
    getPasswd();
    if(rcClient->Login(netPasswd) != 0)
        return 0;
    *console << endl;

    netFetch = new NetFetch(rcClient);
    netFetch->start();

    while(inputBuffer != "quit")
    {
        sleep(1);
        *console >> inputBuffer;
        rcClient->WriteStream(inputBuffer);
    }
    rcClient->Close();
    return 0;
}
